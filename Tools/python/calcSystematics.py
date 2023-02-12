import ROOT
import argparse

parser = argparse.ArgumentParser(description='rebin options')
#parser.add_argument('-i','--input', help='Input file to rebin.',default="Minv_histos_BB_2018.root", type=str)
parser.add_argument('-y','--year', help='year',default="2018", type=str)
parser.add_argument('-r','--region', help='region',default="BB", type=str)
parser.add_argument('-p','--path', help='Path to input.',default="datacards/datacards/", type=str)
#parser.add_argument('--all', help='Run All Years and Regions')

args = parser.parse_args()

region    = args.region
year      = args.year
inputFile = args.path + "Minv_histos_%s_%s.root" %(region, year)

print "Get systematics from histograms"

f = ROOT.TFile(inputFile, "READ")
f.cd(region)

# gg, gj, jj, vg, dy, ttg, signalPoint
histNamesSyst = ["gg_kfactorStat0Up", #
                 "gg_kfactorStat1Up", #
                 "gg_kfactorStat2Up", #
                 "gg_kfactorStat3Up", #
                 "gg_kfactorStat0Down", #
                 "gg_kfactorStat1Down", #
                 "gg_kfactorStat2Down", #
                 "gg_kfactorStat3Down", #
                 "gg_diphotonkfactorScales%sUp" %(region),    #
                 "gg_diphotonkfactorScales%sDown" %(region),  #
                 "gg_effUp",                                  #
                 "gg_effDown",                                #
                 "gg_energyScaleGainUp",                      #
                 "gg_energyScaleGainDown",                    #
                 "gg_energyScaleStatUp",                      #
                 "gg_energyScaleStatDown",                    #
                 #"gg_energyScaleStatSystUp", # What is this?
                 #"gg_energyScaleStatSystDown",
                 "gg_energySigmaUp",
                 "gg_energySigmaDown",
                 "gg_pileupUp",
                 "gg_pileupDown",
                 "gj_fake_sampleUp",
                 "gj_fake_sampleDown",
                 "jj_effUp",
                 "jj_effDown",
                 "jj_energyScaleGainUp",
                 "jj_energyScaleGainDown",
                 "jj_energyScaleStatUp",
                 "jj_energyScaleStatDown",
                 "jj_energyScaleSystDown",
                 "jj_energyScaleSystUp",
                 "jj_energyScaleSystDown",
                 "jj_energySigmaDown",
                 "jj_energySigmaUp",
                 "jj_pileupDown",
                 "jj_pileupUp",
                 # Ignore minor backgrounds for now 
                 ]

for i in range(50):
    histNamesSyst.append("gg_pdf%dUp" %(i+1))
    histNamesSyst.append("gg_pdf%dDown" %(i+1))


for histName in histNamesSyst:
    histBaseName  = histName[:histName.index('_')]

    histSyst     = ROOT.gDirectory.Get(histName)
    histBase     = ROOT.gDirectory.Get(histBaseName)

    N = histSyst.GetNbinsX()
    # Integrate from 1 TeV to 6 TeV
    mLow = histBase.FindBin(1000)
    mHi  = histBase.FindBin(6000)
    syst = histSyst.Integral(mLow, mHi)/histBase.Integral(mLow, mHi) #why from 21 to 121

    # Average Up and Down (?) but check if average is valid

    print histName, ": ", syst

    # 50 GeV bins ()

# Discuss with Conor about logNormal and logUniform Distributions
# What about the "UP" and "Down'
# Some basics on Uncertainties
