import argparse,os,sys

parser = argparse.ArgumentParser(description='Simple helper for creating plotting scripts.')
parser.add_argument('--sample'
                    ,dest='sampleName'
                    ,help='Sample for which the script is created')
args = parser.parse_args()

sampleName = args.sampleName

if not os.path.exists(sampleName):
    print 'Sample ' + sampleName + ' does not exist. Exit!'
    sys.exit(1)

TEMPLATENAME = 'TrigTestPlots_template.py'

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

replaceDict = {
                    "@sampleName@":sampleName
                   }
replaceWithDict(TEMPLATENAME, sampleName + "/TrigTestPlots.py", replaceDict)