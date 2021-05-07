from __future__ import print_function
import os
import subprocess
import time
import re
import numpy as np
from commandLineHelpers import *

ROWS, COLUMNS = os.popen('stty size', 'r').read().split()
ROWS, COLUMNS = int(ROWS), int(COLUMNS)

class condor_job:
    def __init__(self, schedd, ID):
        self.schedd = schedd
        self.ID = ID
        self.done = False
        self.line = '%s %10s || '%(self.schedd, self.ID)
        self.maxLines = 1
        self.res = None
        self.fetching = False
    
    def fetch(self):
        if self.done: return# self.line
        if self.res is not None: return
        args = ['condor_tail -maxbytes 256 -name %s %s'%(self.schedd, self.ID)]
        self.res = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, executable='/bin/bash', universal_newlines=True)
        self.fetching = True

    def check(self):
        if self.done: return
        if self.res is None:
            self.fetch()
        if self.res.poll() is not None:
            self.fetching = False

        if self.res.returncode:
            self.done = True
            self.line = self.line.replace('||','-|')
        else:
            tail = self.res.stdout.read()
            self.res = None
            split = [line for line in tail.split('\n') if line]
            try:
                line = split[-1]
            except IndexError:
                line = ''
            self.line = '%s %10s || %s'%(self.schedd, self.ID, line)

        # truncate output so that it never excedes one line for now
        if len(self.line)>(COLUMNS-1):
            self.line = self.line[:COLUMNS-1]

        nLines = 1 + int(len(self.line)/COLUMNS)
        self.maxLines = max(nLines, self.maxLines)
        self.line += ('\n'+' '*COLUMNS)*(self.maxLines-nLines)

        return 

    def watch(self, timeout=1):
        start = time.time()
        while time.time()-start < timeout:
            line = self.check()
            if self.done:
                break
            sys.stdout.write('\r'+line)
            sys.stdout.flush()
            
        
def get_jobs():
    USER = getUSER()
    q = os.popen('condor_q').read()
    lines = q.split('\n')
    jobs = []
    for line in lines:
        print(line)
        split = line.split()
        if not split: continue
        if "-- Schedd:" in line:
            schedd = split[2]
        if "dagman" in line: continue
        if USER == split[1]:
            ID = split[0]
            jobs.append( condor_job(schedd, ID) )

    print('-'*20)
    if not jobs:
        print("No Jobs")

    if len(jobs)>(ROWS-2): 
        print('WARNING: %d jobs but only %d rows on screen'%(len(jobs),ROWS-2))
        jobs = jobs[:ROWS-2]

    return jobs

    
try:
    jobs = get_jobs()
    while jobs:

        nJobs=len(jobs)
        for i, job in enumerate(jobs): print(job.line)

        fetching = np.array([0 for job in jobs])            
        i, nDone, nLines = 0, 0, 0
        while nDone < nJobs:
            job = jobs[i]
            if not job.fetching and fetching.sum()<16:
                job.fetch()
                fetching[i] = 1
            if job.res is not None:
                if job.res.poll() is not None:
                    job.check()
                    placeCursor(i+ROWS-nJobs, 0)
                    print('\033[K', end='') # clear row
                    print(job.line, end='' if (i+1)==nJobs else '\n')
                    fetching[i] = 0
            nLines += job.maxLines
            time.sleep(0.01)
            if job.done:
                nDone += 1
            i += 1
            if i == nJobs:
                placeCursor(ROWS-1,COLUMNS-5)
                print('%02d/%02d'%(nDone,nJobs))
                i, nDone, nLines = 0, 0, 0
                
        placeCursor(ROWS,0)
        print()
        print('-'*20)
        time.sleep(10)
        jobs = get_jobs()

except KeyboardInterrupt:
    moveCursorDown(ROWS)
    print()
    pass
