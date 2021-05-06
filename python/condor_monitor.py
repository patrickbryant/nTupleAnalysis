from __future__ import print_function
import os
import subprocess
import time
import re
from commandLineHelpers import *

ROWS, COLUMNS = os.popen('stty size', 'r').read().split()
ROWS, COLUMNS = int(ROWS), int(COLUMNS)

class condor_job:
    def __init__(self, schedd, ID):
        self.schedd = schedd
        self.ID = ID
        self.done = False
        self.line = ''
        self.maxLines = 1
        self.res = None
    
    def fetch(self):
        if self.done: return# self.line
        if self.res is not None: return
        args = ['condor_tail -maxbytes 256 -name %s %s'%(self.schedd, self.ID)]
        self.res = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, executable='/bin/bash', universal_newlines=True)

    def check(self):
        if self.done: return self.line
        # args = ['condor_tail -maxbytes 256 -name %s %s'%(self.schedd, self.ID)]
        # self.res = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True, executable='/bin/bash', universal_newlines=True)
        # self.res.wait()
        if self.res is None: 
            self.fetch()
        self.res.wait()

        if self.res.returncode:
            self.done = True
            #self.line = '%s %10s >> %s %d'%(self.schedd, self.ID, 'FINISHED: return code', res.returncode)
            self.line = self.line.replace('||','-|')
            #self.line += ' | FINISHED'#: return code %d'%(res.returncode)
        else:
            tail = self.res.stdout.read()
            self.res = None
            split = [line for line in tail.split('\n') if line]
            try:
                line = split[-1]
            except IndexError:
                line = ''
            self.line = '%s %10s || %s'%(self.schedd, self.ID, line)
            #time.sleep(0.05)

        if len(self.line)>(COLUMNS-1):
            self.line = self.line[:COLUMNS-1]

        nLines = 1 + int(len(self.line)/COLUMNS)
        self.maxLines = max(nLines, self.maxLines)
        self.line += ('\n'+' '*COLUMNS)*(self.maxLines-nLines)

        return self.line

    def watch(self, timeout=1):
        start = time.time()
        while time.time()-start < timeout:
            line = self.check()
            if self.done:
                break
            sys.stdout.write('\r'+line)
            sys.stdout.flush()
            #print split[-1]
            
        
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
            #print schedd, ID
            jobs.append( condor_job(schedd, ID) )

    print('-'*20)
    if not jobs:
        print("No Jobs")

    if len(jobs)>(ROWS-1): 
        print('WARNING: %d jobs but only %d rows on screen'%(len(jobs),ROWS-1))
        jobs = jobs[:ROWS-1]
    # else:
    #     print '-'*20
    return jobs

    
try:
    jobs = get_jobs()
    while jobs:

        nDone=0
        nJobs=len(jobs)
        while nDone < nJobs:
            nDone = 0
            nLines = 0
            for i,job in enumerate(jobs):
                job.fetch()
                # do some pre-fetching of next job outputs to make updates faster (these run as parallel subprocesses and we wait for results in job.check())
                if nJobs>1: jobs[(i+1)%nJobs].fetch()
                if nJobs>2: jobs[(i+2)%nJobs].fetch()
                if nJobs>3: jobs[(i+3)%nJobs].fetch()
                if nJobs>4: jobs[(i+4)%nJobs].fetch()
                if nJobs>5: jobs[(i+5)%nJobs].fetch()
                if nJobs>6: jobs[(i+6)%nJobs].fetch()
                if nJobs>7: jobs[(i+7)%nJobs].fetch()
                if job.done: 
                    nDone += 1
                line = job.check()
                nLines += job.maxLines
                print("\r\033[K"+line, end='' if (i+1)==nJobs else '\n')
                # print("\r\033[K"+line)
                #time.sleep(1)
            moveCursorUp(nLines-1)
        moveCursorDown(ROWS)
        print()
        print('-'*20)
        time.sleep(10)
        jobs = get_jobs()
except KeyboardInterrupt:
    moveCursorDown(ROWS)
    print()
    pass
