#!/usr/bin/python

import re
import sys,os
import argparse
from subprocess import call

#Initialize the argparser module
parser = argparse.ArgumentParser(description='Tool for copying files from dCache, merging to one root file and moving to net_scratch.')
parser.add_argument('--copy'
                    ,dest='copy'
                    ,action='store_true'
                    ,help='Copy files from dCache.')
parser.add_argument('--merge'
                    ,dest='merge'
                    ,action='store_true'
                    ,help='Merge files to one edm root file.')
parser.add_argument('--remove-originals'
                    ,dest='removeOriginals'
                    ,action='store_true'
                    ,help='If --merge option is given, remove the source files after merging.')
parser.add_argument('--merge-list'
                    ,dest='mergeList'
                    ,help='Give a list of files that are used for merging instead of using the default list.')
parser.add_argument('--move'
                    ,dest='move'
                    ,action='store_true'
                    ,help='Move files to directory under net_scratch')
parser.add_argument('--all'
                    ,dest='all'
                    ,action='store_true'
                    ,help='Enable all of the options')
args = parser.parse_args()

#local variables for storing arg switches
copy = args.copy
merge = args.merge
removeOriginals = args.removeOriginals
mergeList = args.mergeList
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

#Find out, where the script is running
curDir = str(os.getcwd())
curDirParts = curDir.split('/')
sampleName = curDirParts[-1]
print 'Found program running in directory: ' + sampleName

#Get dev null for call later on
DEVNULL = open(os.devnull, 'wb')

if copy:
    #define the username on the T2 Storage element
    USERNAME="akunsken"
    
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
    
    print 'Creating local directory for root files'
    if not os.path.exists('rootfiles'):
        os.mkdir('rootfiles')
    else:
        print "Already exists!"
    
    #Create a file that stores the names of the copied files
    copiedFiles = open('copiedRootFiles','w')
    
    for sourceFile in sourceFiles:
        if os.path.exists('rootfiles/' + sourceFile.split('/')[-1]):
            print 'File ' + sourceFile.split('/')[-1] + ' exists. Skipping!'
            continue
        print 'Copying file ' + sourceFile.split('/')[-1]
        copiedFiles.write('file:rootfiles/' + sourceFile.split('/')[-1] + '\n')
        copyCmd = 'srmcp ' + STORAGE_SERVER + sourceFile + ' file://./rootfiles'
        ret = call(copyCmd, shell=True, stdout=DEVNULL,stderr=DEVNULL)
        if ret != 0:
             print 'Something went wrong on copying. Abort!'
             sys.exit(7)

#If the merge option is required, the root input files are merged to one large root file
if merge:
    #Look for the list of the files copied from dCache
    #TODO:Do not require the file but perform an ls on the rootfiles directory and create the source file
    if mergeList != None:
        if not os.path.exists(mergeList):
            print 'Cannot merge the files. The given file with the copied files doesn\'t exist!'
            sys.exit(8)
    else:
        if not os.path.exists('copiedRootFiles'):
            print 'Cannot merge the files. The file with the copied files is missing!'
            sys.exit(4)
    mergeCmd = 'edmCopyPickMerge inputFiles_load='
    #Check for an optional file list
    if mergeList != None:
        mergeCmd += mergeList
    else:
        mergeCmd +=  'copiedRootFiles'
    mergeCmd += ' outputFile=DeltaPhi.root'
    
    if os.path.exists('DeltaPhi.root'):
        print 'File DeltaPhi.root already exists. Abort Merging!'
        sys.exit(9)
    
    print 'Merging root files...'
    ret = call(mergeCmd, shell=True,stderr=DEVNULL)
    if ret != 0: 
        print 'Something went wrong on merging. Abort!'
        sys.exit(6)
    #if this option is given, the smaller source files are being removed
    if removeOriginals:
        print 'Removing source files for merging...'
        mergedFiles = None
        if mergeList != None:
            mergedFiles = open(mergeList,'r')
        else:
            mergedFiles = open('copiedRootFiles','r')
        for line in mergedFiles:
            print 'Removing ' + line.split(':')[-1]
            os.remove(line.split(':')[-1].replace('\n',""))

#If the move option is selected, moce the merged root file to a directory on net_scratch
if move:
    netScratchPath = '/net/scratch_cms/institut_3b/kuensken/' + sampleName
    #Find, whether the target directory exists
    if not os.path.exists(netScratchPath):
        print 'Target directory ' + netScratchPath + ' does not exist. Creating... '
        os.mkdir(netScratchPath)
    else:
        print 'Target directory ' + netScratchPath + ' exists.'
    #Abort, in case there is already a root file
    if os.path.exists(netScratchPath + '/DeltaPhi.root'):
        print 'Target file ' + netScratchPath + '/DeltaPhi.root exists. Exiting. '
        sys.exit(5)
    moveCmd = 'mv DeltaPhi.root ' + netScratchPath
    print 'Moving DeltaPhi.root to ' + netScratchPath
    ret = call(moveCmd, shell=True, stdout=DEVNULL,stderr=DEVNULL)
    if ret != 0:
        print 'Something went wrong on moving file to net_scratch. Abort!'
        sys.exit(8)

print 'All done.'



    
