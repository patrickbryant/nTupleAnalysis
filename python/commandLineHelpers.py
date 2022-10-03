from __future__ import print_function
import time
import textwrap
from copy import copy
import os, re
import sys
import subprocess
import shlex
from pyxrootd import client
import optparse
import numpy as np
from threading import Thread
try:
    from queue import Queue, Empty
except ImportError:
    from Queue import Queue, Empty  # python 2.x

try:
    ROWS, COLUMNS = os.popen('stty size', 'r').read().split()
    ROWS, COLUMNS = int(ROWS), int(COLUMNS)
except ValueError: # condor jobs don't have screen dimensions
    ROWS, COLUMNS = 100, 100

ON_POSIX = 'posix' in sys.builtin_module_names

def getCMSSW():
    CMSSW = os.getenv('CMSSW_VERSION')
    if CMSSW is None: CMSSW = ''
    return CMSSW

def getUSER():
    return os.getenv('USER')

DEFAULTCMSSW   = getCMSSW()
USER           = getUSER()
try:
    DEFAULTTARBALL = "root://cmseos.fnal.gov//store/user/"+USER+"/condor/"+DEFAULTCMSSW+".tgz"
except:
    DEFAULTTARBALL = None

def enqueue_output(out, queue, logFile):
    for line in iter(out.readline, b''):
        if logFile: logFile.write(line)
        queue.put(line)
        if queue.qsize()>1: queue.get_nowait()

        
    out.close()


def execute(command, doExecute=True, condor_dag=None): # use to run command like a normal line of bash
    if type(command) is str and condor_dag is None:
        print(command)
        if doExecute: os.system(command)
    if type(command) is list and condor_dag is None:
        babySit(command, doExecute)
    if condor_dag is not None:
        if command is str:
            command = [command]
        for cmd in command:
            thisJDL = jdl(cmd=cmd)
            condor_dag.addJob(thisJDL)
        


def watch(command, doExecute=True, stdout=None, doPrint=True, logFile=None): # use to run a command and keep track of the thread, ie to run something when it is done
    if doPrint: print(command)
    if doExecute:
        p = subprocess.Popen(shlex.split(command), stdout=stdout, universal_newlines=(True if stdout else False), bufsize=1, close_fds=ON_POSIX)
        if stdout:
            q = Queue()
            t = Thread(target=enqueue_output, args=(p.stdout, q, logFile))
            t.daemon = True
            t.start()
            return (command, p, q)
        return (command, p)


# \033[<L>;<C>H # Move the cursor to line L, column C
# \033[<N>A     # Move the cursor up N lines
# \033[<N>B     # Move the cursor down N lines
# \033[<N>C     # Move the cursor forward N columns
# \033[<N>D     # Move the cursor backward N columns
# \033[2J       # Clear the screen, move to (0,0)
# \033[K        # Erase to end of line
def placeCursor(L,C):
    print('\033['+str(L)+';'+str(C)+'H', end='')
def moveCursorUp(N=''):
    if N<1: 
        print('\r', end='')
        return
    print('\r\033['+str(N)+'A', end='')
def moveCursorDown(N=''):
    print('\r\033['+str(N)+'B', end='')


def babySit(commands, doExecute, maxAttempts=1, maxJobs=4, logFiles=None):
    attempts={}
    nCommands = len(commands)
    jobs=[]
    logs=[]
    outs=[]
    waiting=[]
    waitinglogs=[]
    done=[]
    for c in range(nCommands):
        command = commands[c]
        attempts[command] = 1
        done.append(0)
        print("# ",c)
        if len(jobs)<maxJobs:
            logs.append(open(logFiles[c],"w") if (logFiles and doExecute) else None)
            jobs.append(watch(command, doExecute, stdout=subprocess.PIPE,logFile=logs[-1]))
                
            outs.append("LAUNCHING")
        else:
            print(command)
            waiting.append(command)
            waitinglogs.append(open(logFiles[c],"w") if (logFiles and doExecute) else None)
            outs.append("IN QUEUE")

    if not doExecute: return
    
    nDone = 0
    while nDone < nCommands:
        time.sleep(0.2)
        failure=False
        nJobs = len(jobs)
        nDone = sum(done)
        nToLaunch = 0
        for j in range(nJobs):
            code = jobs[j][1].poll()
            #if code == None: # job is still running
            #    done=False
            if code==0: # job finished
                if done[j]==0: nToLaunch += 1
                done[j] = 1
            elif code: # job crashed, try resubmitting
                moveCursorDown(1000)
                outs[j] = "CRASHED AT <"+outs[j]+">"
                crash = ["",
                         "# "+"-"*200,
                         "# "+jobs[j][0],
                         "# "+outs[j],
                         "# Exited with: "+str(code),
                         "# Attempt: "+str(attempts[jobs[j][0]]),
                         "# "+"-"*200,
                         ""]
                time.sleep(1)
                for line in crash: print(line)
                if attempts[jobs[j][0]] > maxAttempts: 
                    if done[j]==0: nToLaunch += 1
                    done[j] = 1
                    continue # don't resubmit, already tried maxAttempts times
                attempts[jobs[j][0]] += 1
                time.sleep(10)
                #done=False
                jobs[j] = watch(jobs[j][0], doExecute, stdout=subprocess.PIPE, logFile=logs[j])

        nWaiting = len(waiting)
        for w in range(nJobs, nJobs+min(nToLaunch, nWaiting)):
            jobs.append(watch(waiting.pop(0), doExecute, stdout=subprocess.PIPE, doPrint=False,logFile=waitinglogs.pop(0)))
            outs[w] = "LAUNCHING"

        nJobs = len(jobs)
        nLines = 1+nCommands#3
        print("\033[K")
        for c in range(nCommands):
            if c < nJobs:
                try:          
                    outs[c]=jobs[c][2].get_nowait().replace('\n','').replace('\r','')
                except Empty: 
                    outs[c]=outs[c]
            print("\033[K# "+str(c).rjust(2)+" >>",outs[c])

        moveCursorUp(nLines)
    moveCursorDown(1000)
            

def waitForJobs(jobs,failedJobs):
    for job in jobs:
        code = job[1].wait()
        if code: failedJobs.append(job)
    return failedJobs

def relaunchJobs(jobs, doExecute=True):
    print("# "+"-"*200)
    print("# RELAUNCHING JOBS")
    newJobs = []
    for job in jobs: newJobs.append(watch(job[0], doExecute))
    return newJobs


def parseXRD(xrdFile):
    xrdFileSplit = xrdFile.split("//")
    url = "//".join(xrdFileSplit[0:2])+"/"
    path = "/".join(xrdFileSplit[2:])
    if path[0] != "/": path = "/"+path
    return url, path

def exists(path):
    if "root://" in path:
        url, path = parseXRD(path)
        fs=client.FileSystem(url)
        return not fs.stat(path)[0]['status'] # status is 0 if file exists
    else:
        return os.path.exists(path)
    

def mkdir(directory, doExecute=True, xrd=False, url="root://cmseos.fnal.gov/", debug=False):
    if exists(directory) and debug: 
        print("#",directory,"already exists")
        return
        
    if "root://" in directory or xrd:
        url, path = parseXRD(directory)
        cmd = "xrdfs "+url+" mkdir "+path
        execute(cmd, doExecute)
    else:
        if not os.path.isdir(directory):
            print("mkdir",directory)
            if doExecute: os.mkdir(directory)


def mkpath(path, doExecute=True, debug=False):
    if exists(path) and debug:
        print("#",path,"already exists")
        return
        
    url = ''
    if "root://" in path:
        url, path = parseXRD(path)
    dirs = [x for x in path.split("/") if x]
    thisDir = url+'/' if url else ''
    if not url and path[0]=='/':
        thisDir = '/'+thisDir
    for d in dirs:
        thisDir = thisDir+d+"/"
        mkdir(thisDir, doExecute)
        

def rmdir(directory, doExecute=True):
    if exists(directory):
        execute("rm -r "+directory, doExecute)
    else:
        print("#",directory,"does not exist")




class jdl:
    def __init__(self, cmd=None, CMSSW=DEFAULTCMSSW, EOSOUTDIR="None", TARBALL=DEFAULTTARBALL, fileName=None, logPath = './', logName = '', executable = 'nTupleAnalysis/scripts/condor.sh'):
        self.randName = str(np.random.uniform())[2:]
        self.humanReadableName = ''
        self.fileName = fileName if fileName else self.randName+".jdl"
        if cmd:
            fileList = [c for c in cmd.split() if '.txt' in c]
            if fileList:
                self.humanReadableName = fileList[0].split('/')[-1].replace('.txt','')
                if not fileName: self.fileName = '%s_%s.jdl'%(self.humanReadableName, self.randName)
            if 'hadd' in cmd:
                self.humanReadableName = cmd.replace('-f','').split()[1].split('/')[-2]
                if not fileName: self.fileName = 'hadd_%s_%s.jdl'%(self.humanReadableName, self.randName)
        print('#', self.fileName, cmd)

        if self.humanReadableName and not logName:
            logName = 'condor_log_%s_$(Cluster)_$(Process)'%self.humanReadableName            
        elif not logName:
            logName = 'condor_log_$(Cluster)_$(Process)'

        self.CMSSW = CMSSW
        self.EOSOUTDIR = EOSOUTDIR # specify this to have condor.sh manually xrdcp command output to an EOS location
        self.TARBALL = TARBALL

        self.universe = "vanilla"
        self.use_x509userproxy = "true"
        self.Executable = executable
        #self.x509userproxy = "x509up_forCondor"
        self.should_transfer_files = "YES"
        self.when_to_transfer_output = "ON_EXIT"
        self.Output = logPath+logName+".stdout"
        self.Error = logPath+logName+".stderr"
        self.Log = logPath+logName+".log"
        self.Arguments = CMSSW+" "+EOSOUTDIR+" "+TARBALL+" "+cmd
        self.Queue = "1" # no equals sign in .jdl file
        
        self.made = False

    def make(self):
        attributes=["universe",
                    "use_x509userproxy",
                    "Executable",
                    #"x509userproxy",
                    "should_transfer_files",
                    "when_to_transfer_output",
                    "Output",
                    "Error",
                    "Log",
                    "Arguments",
                ]
        f=open(self.fileName,'w')
        for attr in attributes:
            f.write(attr+" = "+str(getattr(self, attr))+"\n")

        f.write('+DesiredOS="SL7"\n')
        f.write("Queue "+str(self.Queue)+"\n")    
        f.close()

        self.made = True

    
class dag:
    def __init__(self, parents=[], children=[], fileName=None):
        self.fileName = fileName if fileName else str(np.random.uniform())[2:]+".jdl"
        self.iJ = 0
        self.iG = 0
        self.iGMax = 0
        self.jobs = [[]]
        self.generations = ' ABCDEFGHIJKLMNOPQRSTUVWXYZ'
        
        self.jobLines=[]
        self.genLines=[]

        self.written = False

    def setGeneration(self, generation):
        self.iG = generation
        while len(self.jobs) <= self.iG:
            self.jobs.append([])

    def addJob(self, JDL):
        if not JDL.made: JDL.make()
        self.iJ = len(self.jobs[self.iG])
        self.jobs[self.iG].append( "%s%d"%(self.generations[self.iG], self.iJ) )
        self.jobLines.append( "JOB %s %s\n"%(self.jobs[self.iG][self.iJ], JDL.fileName) )
        if self.iG > self.iGMax: self.iGMax = copy( self.iG ) # keeps track of the latest non-empty generation
    
    def addJobs(self, JDLs):
        for JDL in JDLs: self.addJobs(JDL)

    def addGeneration(self):
        self.iG += 1
        while len(self.jobs) <= self.iG:
            self.jobs.append([])

    def write(self):
        f = open(self.fileName, 'w')

        for line in self.jobLines:
            f.write(line)

        for iG in range(len(self.jobs)-1):
            if not self.jobs[iG]:   continue
            if not self.jobs[iG+1]: continue
            self.genLines.append( "PARENT "+" ".join(self.jobs[iG])+" CHILD "+" ".join(self.jobs[iG+1])+"\n" )

        for line in self.genLines:
            f.write(line)

        self.written = True
        
    def submit(self, doExecute=False):
        if not self.jobLines: return
        if not self.written: self.write()
        cmd = "condor_submit_dag -f "+self.fileName
        execute(cmd, doExecute)
        
        
