#!/usr/bin/python

import re
import sys,os
import argparse
from subprocess import call

#Initialize the argparser module
parser = argparse.ArgumentParser(description='Tool for copying files from dCache, merging to one root file and moving to net_scratch.')
parser.add_argument('--copy',dest='copy',action='store_true',help='Copy files from dCache.')
parser.add_argument('--merge',dest='merge',action='store_true',help='Merge files to one edm root file.')
parser.add_argument('--move',dest='move',action='store_true',help='Move files to directory under net_scratch')
parser.add_argument('--all',dest='all',action='store_true',help='Enable all of the options')
args = parser.parse_args()

#local variables for storing arg switches
copy = args.copy
merge = args.merge
move = args.move
all = args.all

if all:
    copy = True
    merge = True
    move = True
else:
    if not (copy or merge or move):
        print 'Error! Program requires at least one parameter!'
        parser.print_help()
        sys.exit(3)

if copy:
    #Get dev null for call later on
    DEVNULL = open(os.devnull, 'wb')
    #define the username on the T2 Storage element
    USERNAME="akunsken"
    #define cmssw exe template
    CMSSWCFG="DeltaPhiGun_template.py"
    #define crab config template
    CRABCFG ="crab_template.cfg"
    
    curDir = str(os.getcwd())
    curDirParts = curDir.split('/')
    sampleName = curDirParts[-1]
    
    print 'Found program running in dir : ' + sampleName
    
    # Create output directory variable
    STORAGE_SERVER="srm://grid-srm.physik.rwth-aachen.de:8443"
    STORAGE_DIR="pnfs/physik.rwth-aachen.de/cms/store/user/" + USERNAME + "/" + sampleName
    OUTPUT_DIR=STORAGE_SERVER + "/" + STORAGE_DIR
    print OUTPUT_DIR
    
    #Build command to check for dir on T2
    print 'Testing whether sample name directory exists on dcache...' 
    cmd = "srmls " + OUTPUT_DIR
    
    #Get the list of files in the source directory
    lsResults = open('dcacheFiles','r+')
    ret = call(cmd, shell=True, stdout=lsResults,stderr=DEVNULL)
    lsResults.seek(0)
    
    if ret != 0 :
        print 'Fail! Are you sure to be inside a sample name directory (e.g. DeltaPhiGunPt100dPhi0_3)?'
        sys.exit(1)
    else:
        print 'Success!'
    
    sourceFiles = []
    
    #create an array with just the paths to the sources
    for line in lsResults:
        lineStr = str(line)
        if lineStr.count('.root'):
            fileName = lineStr.split(' ')[-1].rstrip('\n')
            sourceFiles.append(fileName)
    
    print 'Creating local dir for root files'
    if not os.path.exists('rootfiles'):
        os.mkdir('rootfiles')
    else:
        print "Error! Directory for root files already exists. Exit."
        sys.exit(2)
    
    #Create a file that stores the names of the copied files
    copiedFiles = open('copiedRootFiles','w')
    
    for sourceFile in sourceFiles:
        print 'Copying file ' + sourceFile.split('/')[-1]
        copiedFiles.write('file:rootfiles/' + sourceFile.split('/')[-1] + '\n')
        copyCmd = 'srmcp ' + STORAGE_SERVER + sourceFile + ' file://./rootfiles'
        ret = call(copyCmd, shell=True, stdout=DEVNULL,stderr=DEVNULL)

if merge:
    if not os.path.exists('copiedRootFiles'):
        print 'Cannot merge the files. The file with the copied files is missing!'
        sys.exit(4)
    mergeCmd = 'edmCopyPickMerge inputFiles=copiedRootFiles outputFile=DeltaPhi.root'
    print mergeCmd

if move:
	moveCmd = 'mv DeltaPhi.root /net/scratch_cms/institut_3b/kuensken/' + sampleName
	print moveCmd

print 'All done.'



    
