import re
import sys,os
import argparse
from subprocess import call

#Get dev null for call later on
DEVNULL = open(os.devnull, 'wb')

#define the username on the T2 Storage element
USERNAME="akunsken"
#define cmssw exe template
CMSSWCFG="DiMuGun_template.py"
#define crab config template
CRABCFG ="crab_template.cfg"

#Initialize the argparser module
parser = argparse.ArgumentParser(description='Process some integers.')
parser.add_argument('--dr_min', type=float,required=True,
                   help='lower threshold for delta R')
parser.add_argument('--dr_max', type=float,required=True,
                   help='upper threshold for delta R')
parser.add_argument('--pt', type=float,required=True,
                   help='Pt values for the muons')
args = parser.parse_args()

#Create variables for this namespace
dr_min = args.dr_min
dr_max = args.dr_max

if (dr_min > dr_max):
    print "Error! Lower delta R must be smaller than upper delta R."
    sys.exit(1)

pt  = args.pt
dr  = (dr_min + dr_max)/2.
pt_min = args.pt - 0.01
pt_max = args.pt + 0.01

#Create variable for job dir name
#Cast pt to int to get rid of the floating point
JOBDIR=("MuGunPt" + str(int(pt)) + "dR" + str(dr)).replace(".","_")

if not os.path.exists(JOBDIR):
    os.mkdir(JOBDIR)
else:
    print "Error! Directory " + JOBDIR + " already exists. Exit."
    sys.exit(2)
    
# Create output directory
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
    sys.exit(4)

#####
#Generate CMSSW exe file
#####
infile = open(CMSSWCFG)
outfile = open(JOBDIR + "/DiMuGun.py", 'w')

#Create a replacement dictionary for cmssw exe file
replaceDictCmssw = {
                "@pt@":str(pt),
                "@pt_min@":str(pt_min),
                "@pt_max@":str(pt_max),
                "@dr_min@":str(dr_min),
                "@dr_max@":str(dr_max)
               }
print
print "Creating CMSSW exe with following parameters:"
for src, target in replaceDictCmssw.iteritems():
    print "\t" + src.replace("@","") + " -> " + target
print

for line in infile:
    for src, target in replaceDictCmssw.iteritems():
        line = line.replace(src, target)
    outfile.write(line)
infile.close()
outfile.close()

infile = open(CRABCFG)
outfile = open(JOBDIR + "/crab.cfg", 'w')
#Create a replacement dictionary for crab cfg file
replaceDictCrab = {"@t2_dir@":JOBDIR}

print
print "Creating CRAB config with following parameters:"
for src, target in replaceDictCmssw.iteritems():
    print "\t" + src.replace("@","") + " -> " + target
print

for line in infile:
    for src, target in replaceDictCrab.iteritems():
        line = line.replace(src, target)
    outfile.write(line)
infile.close()
outfile.close()

print "Done. You may proceed with copy & paste of these commands:"
print 
print "voms-proxy-init -voms cms:/cms/dcms -valid 164:00"
print "cd $JOBDIR"
print "crab -create"
print "crab -submit"
print "crab -status"
