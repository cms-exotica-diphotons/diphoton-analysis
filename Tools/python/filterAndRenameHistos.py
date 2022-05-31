import ROOT
import argparse
import re
from itertools import imap

parser = argparse.ArgumentParser(description='rebin options')
#parser.add_argument('-i','--input', help='Input file to rebin.',default="Minv_histos_BB_2018.root", type=str)
parser.add_argument('-y','--year', help='year',default="2018", type=str)
parser.add_argument('-r','--region', help='region',default="BB", type=str)
parser.add_argument('-p','--path', help='Path to input.',default="datacards/datacards/", type=str)

args = parser.parse_args()

region     = args.region
year       = args.year
inputFile  = args.path + "Minv_histos_%s_%s.root" %(region, year)


f = ROOT.TFile(inputFile, "READ")

###################

# Helper functions

###################

###

contents_keep = [
"gj",
"data",
# "data_obs",
# "data_2017_2018",
# "data_legacy",
"dy",
"gg",
"jj",
"other",
"ttg",
"vg",
#"w",
"ADDGravToGG_NegInt",
];

w_contents = [
"w",
"w_effDown",
"w_effUp",
"w_energyScaleGainDown",
"w_energyScaleGainUp",
"w_energyScaleStatDown",
"w_energyScaleStatUp",
"w_energyScaleSystDown",
"w_energyScaleSystUp",
"w_energySigmaDown",
"w_energySigmaUp",
"w_pileupDown",
"w_pileupUp"
]

# negint, exclude MS



def ADD_string_rename(ADD_old_name, region):
    # ADD with MS are 2016 samples
    # MS   = re.search('MS-(.*)_NED', ADD_old_name).group(1)
    # NED  = re.search('NED-(.*)_KK', ADD_old_name).group(1)
    # KK   = re.search('KK-(.*)', ADD_old_name).group(1)

    NegInt    = re.search('NegInt-(.*)_LambdaT', ADD_old_name).group(1)
    LambdaT   = re.search('LambdaT-(.*)_TuneCP2', ADD_old_name).group(1)

    #ADD_new_name = "%s__ADD%sned%s" %(region, MS, NED)
    ADD_new_name = "%s%s__ADD%slambdaT%s" %(region, year[2:], NegInt, LambdaT)

    if "Down" in ADD_old_name:
        systDown  = re.search('pythia8_(.*)Down', ADD_old_name).group(1)
        ADD_new_name = ADD_new_name + "__%s__minus" %(systDown)
    if "Up" in ADD_old_name:
        systUp    = re.search('pythia8_(.*)Up', ADD_old_name).group(1)
        ADD_new_name = ADD_new_name + "__%s__plus" %(systUp)

    return ADD_new_name

print ADD_string_rename("ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_energyScaleGainDown", region)

def background_rename(orig_bkgstring, region):
    new_name = "%s%s__%s" %(region, year[2:], orig_bkgstring)
    trailing_subStr = orig_bkgstring.split('_')[-1]

    if "Up" in trailing_subStr:
        systUp = re.search('(.*)Up', trailing_subStr).group(1)
        new_name = new_name.replace("%sUp" %(systUp), "_%s__plus" %(systUp))
    if "Down" in trailing_subStr:
        systDown = re.search('(.*)Down', trailing_subStr).group(1)
        new_name = new_name.replace("%sDown" %(systDown), "_%s__plus" %(systDown))

    return new_name

#print background_rename("other_effUp", region)
#print background_rename("gj", region)
#print background_rename("data", region)

def getall(d, basepath="/"):
    "Generator function to recurse into a ROOT file/dir and yield (path, obj) pairs"
    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)


###################

# Renaming

###################

index = inputFile.find('.root')
outfileName = inputFile[:index] + '_filtered_renamed' + inputFile[index:]

outfile = ROOT.TFile(outfileName, "RECREATE")
# outfile.mkdir(region)

for k, o in getall(f):
    f.cd(region)
    if ("/%s/" %(region) in k):

        histName = k[4:]
        hist = ROOT.gDirectory.Get(histName)

        #### Background
        #if histName in contents_keep:
        if any(imap(histName.__contains__, contents_keep)):
            if "ADD" in histName and "NegInt" in histName:
                newHistName = ADD_string_rename(histName, region)
                #print "Renaming %s to %s" %(histName, newHistName)
            else:
                newHistName = background_rename(histName, region)
                if "vg" in histName:
                    print "Renaming %s to %s" %(histName, newHistName)

            outfile.WriteObject(hist, newHistName)

        elif histName in w_contents:
            newHistName = background_rename(histName, region)
            # print "Renaming %s to %s" %(histName, newHistName)


        #### Rename Signal
        # - Keep only ADD (and maybe Unparticles Later)
        # if "ADD" in histName and "NegInt" in histName:
        #     newHistName = ADD_string_rename(histName, region)
        #     print "Renaming %s to %s" %(histName, newHistName)
        #     outfile.WriteObject(hist, newHistName)

        ## FIXME/TODO:
        # 1.) If written twice - remove (Write a separate for loop for this?)
        # 2.) Ask Chris what dataABC are for..

print "Histograms rewritten to new file: %s" %(outfileName)
