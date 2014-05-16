#!/usr/bin/python

import re
import sys,os
import argparse
from subprocess import call

#Get dev null for call later on
DEVNULL = open(os.devnull, 'wb')
#define the username on the T2 Storage element
USERNAME="akunsken"
#define cmssw exe template
CMSSWCFG="DeltaPhiGun_template.py"
#define crab config template
CRABCFG ="crab_template.cfg"
#define TrigTest template
TRIGTESTCFG = 'TrigTestDeltaPhiGun_template.py'

def replaceWithDict(input, output, dict):
    #####
    #Generate CMSSW exe for Trig Test file
    #####
    infile = open(input)
    outfile = open(output,'w')
    #print
    print 'Creating script file ' + output + ' with following parameters:'
    for src, target in dict.iteritems():
        print "\t" + src.replace("@","") + " -> " + target
    print
    
    for line in infile:
        for src, target in dict.iteritems():
            line = line.replace(src, target)
        outfile.write(line)
    infile.close()
    outfile.close()

#Initialize the argparser module
parser = argparse.ArgumentParser(description='Process some integers.')
crabGroup = parser.add_argument_group()
crabGroup.add_argument('--dPhi_min', type=float, help='lower threshold for delta phi')
crabGroup.add_argument('--dPhi_max', type=float, help='upper threshold for delta phi')
crabGroup.add_argument('--pt', type=float, help='Pt values for the muons')
trigTestGroup = parser.add_argument_group()
trigTestGroup.add_argument('--trig-test'
                           ,dest='trigTest'
                           ,action='store_true'
                           ,help='Use when just processing of the trig test template is needed')
trigTestGroup.add_argument('--target-dir'
                           ,dest='targetDir'
                           ,help='Give the target directory for which the template should be processed.')
args = parser.parse_args()

#Create variables for this namespace
dPhi_min = args.dPhi_min
dPhi_max = args.dPhi_max
pt  = args.pt
trigTest = args.trigTest
targetDir = args.targetDir

if not trigTest:
    if not (dPhi_min != 0 and dPhi_max != 0 and pt != 0):
        print 'Error! Normal running mode requires --dPhi_min, --dPhi_max and --pt!'
        sys.exit(1)
    if (dPhi_min > dPhi_max):
        print "Error! Lower delta Phi must be smaller than upper delta Phi."
        sys.exit(1)

else:
    if targetDir == None:
        print 'Error! Processing trig test template requires --target-dir'
        sys.exit(2)


if not trigTest:
    dPhi  = (dPhi_min + dPhi_max)/2.
    #Create variable for job dir name
    #Cast pt to int to get rid of the floating point
    JOBDIR=("DeltaPhiGunPt" + str(int(pt)) + "dPhi" + str(dPhi)).replace(".","_")
        
    # Create output directory variable
    STORAGE_SERVER="srm://grid-srm.physik.rwth-aachen.de:8443"
    STORAGE_DIR="pnfs/physik.rwth-aachen.de/cms/store/user/" + USERNAME + "/" + JOBDIR
    OUTPUT_DIR=STORAGE_SERVER + "/" + STORAGE_DIR
    
    #Build command to check for dir on T2
    cmd = "srmls " + OUTPUT_DIR
    ret = call(cmd, shell=True, stdout=DEVNULL, stderr=DEVNULL)
    
    #If the ls command returns 0, the dir exists
    if ret == 0:
        print "Directory " + OUTPUT_DIR + " does exist, exiting..."
        sys.exit(3)
    
    #Create the dir, if it doesn't exist
    print "Creating output directory " + OUTPUT_DIR
    cmd = "srmmkdir " + OUTPUT_DIR
    ret = call(cmd, shell=True, stdout=DEVNULL, stderr=DEVNULL)
    #If the mkdir command returns != 0, something went wrong
    if ret != 0:
        print "Something went wrong on creating the output directory on T2!"
        print "Did you try"
        print "voms-proxy-init -voms cms:/cms/dcms -valid 164:00"
        sys.exit(4)
    
    #Now create local directory
    print 'Creating local dir ' + JOBDIR
    if not os.path.exists(JOBDIR):
        os.mkdir(JOBDIR)
    else:
        print "Error! Directory " + JOBDIR + " already exists. Exit."
        sys.exit(2)
    
    #####
    #Generate CMSSW exe file
    #####
    #Create a replacement dictionary for cmssw exe file
    replaceDictCmssw = {
                    "@pt@":str(pt),
                    "@dPhi_min@":str(dPhi_min),
                    "@dPhi_max@":str(dPhi_max)
                   }
    replaceWithDict(CMSSWCFG, JOBDIR + "/DeltaPhiGun.py", replaceDictCmssw)
    
    #####
    #Generate crab config file
    #####
    #Create a replacement dictionary for crab cfg file
    replaceDictCrab = {"@t2_dir@":JOBDIR}
    replaceWithDict(CRABCFG,JOBDIR + "/crab.cfg", replaceDictCrab)

#####
#Generate Trig test cmssw file
#####
#Create a replacement dictionary for crab cfg file
replaceDictTrigTest = {"@jobdir@" : targetDir}
replaceWithDict(TRIGTESTCFG, targetDir + "/TrigTestDeltaPhiGun.py", replaceDictTrigTest)

if not trigTest:
    print "Done. You may proceed with copy & paste of these commands:"
    print 
    print "voms-proxy-init -voms cms:/cms/dcms -valid 164:00"
    print "cd " + JOBDIR
    print "crab -create"
    print "crab -submit"
    print "crab -status"
