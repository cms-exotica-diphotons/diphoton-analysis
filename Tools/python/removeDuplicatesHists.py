import ROOT
import argparse

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

def getall(d, basepath="/"):
    "Generator function to recurse into a ROOT file/dir and yield (path, obj) pairs"
    for key in d.GetListOfKeys():
        kname = key.GetName()
        if key.IsFolder():
            for i in getall(d.Get(kname), basepath+kname+"/"):
                yield i
        else:
            yield basepath+kname, d.Get(kname)

index = inputFile.find('.root')
outfileName = inputFile[:index] + '_light' + inputFile[index:]

outfile = ROOT.TFile(outfileName, "RECREATE")
outfile.mkdir(region)

histDuplicateContainer = []

for k, o in getall(f):
    f.cd(region)
    if ("/%s/" %(region) in k):

        histName = k[4:]

        if histName not in histDuplicateContainer:
            histDuplicateContainer.append(histName)
            hist = ROOT.gDirectory.Get(histName)
            outfile.cd(region)
            hist.SetName(histName)
            hist.Write()
            print "Writing %s to %s" %(histName, outfileName)

print "Removed Duplicates. Histograms rewritten to new file: %s" %(outfileName)
