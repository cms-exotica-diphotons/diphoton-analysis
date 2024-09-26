import ROOT
import argparse
import re
from itertools import imap, izip

parser = argparse.ArgumentParser(description='rebin options')
#parser.add_argument('-i','--input', help='Input file to rebin.',default="Minv_histos_BB_2018.root", type=str)
parser.add_argument('-y','--year', help='year',default="2018", type=str)
parser.add_argument('-r','--region', help='region',default="BB", type=str)
parser.add_argument('-p','--path', help='Path to input.',default="datacards/datacards/", type=str)
parser.add_argument('--all', help='Run All Years and Regions')

args = parser.parse_args()
region     = args.region
year       = args.year
inputFile  = args.path + "Minv_histos_%s_%s.root" %(region, year)


###################

# Helper functions

###################

contents_keep = [
"gj",
"data_obs",
"dy",
"gg",
"jj",
#"other", #drellyan, ttgamma, vgamma - to study whether it was stable to put them all together. Default to separated
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

skip_contents = [
"dataAB",
"dataCD",
"dataABC",
"dataD",
"data_2017_2018",
"data_2018",
"gg70",
"other",
"data_legacy",
"data_newjson",
"RSGrav",
"UnparToGG",
"GluGluSpin0ToGammaGamma",
"ADDGravToGG_MS"
];

def ADD_string_rename(ADD_old_name, region, year):
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

def background_rename(orig_bkgstring, region, year):
    new_name = "%s%s__%s" %(region, year[2:], orig_bkgstring)
    trailing_subStr = orig_bkgstring.split('_')[-1]

    if "Up" in trailing_subStr:
        systUp = re.search('(.*)Up', trailing_subStr).group(1)
        new_name = new_name.replace("%sUp" %(systUp), "_%s__plus" %(systUp))
    if "Down" in trailing_subStr:
        systDown = re.search('(.*)Down', trailing_subStr).group(1)
        new_name = new_name.replace("%sDown" %(systDown), "_%s__plus" %(systDown))

    return new_name

def getall(d, basepath="/"):
    "Generator function to recurse into a ROOT file/dir and yield (path, obj) pairs"
    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)


def main(region, year, inputFile):
    ###################

    # Renaming

    ###################

    f = ROOT.TFile(inputFile, "READ")

    index = inputFile.find('.root')
    outfileName = inputFile[:index] + '_filtered_renamed' + inputFile[index:]

    outfile = ROOT.TFile(outfileName, "RECREATE")
    # outfile.mkdir(region)

    histDuplicateContainer = []

    # Loop over all histograms in input file
    for k, o in getall(f):
        f.cd(region)
        if ("/%s/" %(region) in k):

            histName = k[4:]

            if histName not in histDuplicateContainer:
                histDuplicateContainer.append(histName)
                hist = ROOT.gDirectory.Get(histName)

                #### Background
                if any(imap(histName.__contains__, skip_contents)):
                    continue

                if any(imap(histName.__contains__, contents_keep)):
                    if "ADD" in histName and "NegInt" in histName:
                        newHistName = ADD_string_rename(histName, region, year)
                        #print "Renaming %s to %s" %(histName, newHistName)
                    else:
                        newHistName = background_rename(histName, region, year)

                elif histName in w_contents:
                    newHistName = background_rename(histName, region, year)

                outfile.WriteObject(hist, newHistName)
                print "Renaming %s to %s" %(histName, newHistName)

    print "Removed duplicates and Renamed Histograms. Filtered Contents rewritten to new file: %s" %(outfileName)

if __name__ == "__main__":

    if args.all:
        region_list = ["BE", "BB"]
        year_list = ["2016", "2017", "2018"]

        for i in year_list:
            for j in region_list:
                inFile = args.path + "Minv_histos_%s_%s.root" %(j, i)
                #print i, j
                print "####################"
                print "Renaming and filtering inputFile: %s" %(inFile)
                print "####################"
                main(j, i, inFile)
    else:
        main(region, year, inputFile)
