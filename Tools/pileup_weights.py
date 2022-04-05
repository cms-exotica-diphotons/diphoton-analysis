#!/usr/bin/env python
"""Calculate pileup weights to make 2016, 2017 or 2018 MC match
data from the respective year. Uses files on CERN afs."""
import FWCore.ParameterSet.Config as cms
from SimGeneral.MixingModule.mix_2016_25ns_Moriond17MC_PoissonOOTPU_cfi import mix as mix_2016
from SimGeneral.MixingModule.mix_2017_25ns_WinterMC_PUScenarioV1_PoissonOOTPU_cfi import mix as mix_2017
from SimGeneral.MixingModule.mix_2018_25ns_JuneProjectionFull18_PoissonOOTPU_cfi import mix as mix_2018

import argparse, os
from ROOT import TFile, TH1D

# recipe from https://twiki.cern.ch/twiki/bin/view/CMS/PileupJSONFileforData
PARSER = argparse.ArgumentParser()
PARSER.add_argument('-y', '--year', required=True)
ARGS = PARSER.parse_args()
YEAR = int(ARGS.year)
GOOD_RUN_JSON = { 2016: "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt",
                  2017 : "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PromptReco/Cert_294927-306126_13TeV_PromptReco_Collisions17_JSON.txt",
                  2018 : "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt"}
PILEUP_JSON = { 2016 : "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/PileUp/pileup_latest.txt",
                2017 : "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/PileUp/pileup_latest.txt",
                2018 : "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/PileUp/pileup_latest.txt"}
MIN_BIAS_XSEC, MIN_BIAS_XSEC_REL_UNCERT = 69200, 0.046
MAX_PILEUP_BIN = 100

def make_mc_hist(year):
    """Generate pileup histogram from MC"""
    pu_mc = TH1D("pileup_mc", "pileup_mc", MAX_PILEUP_BIN, 0, MAX_PILEUP_BIN)
    if year == 2016:
        mix = mix_2016
    elif year == 2017:
        mix = mix_2017
    elif year == 2018:
        mix = mix_2018
    else:
        print("Invalid year: {}".format(year))
    for i, val in enumerate(mix.input.nbPileupEvents.probValue):
        pu_mc.SetBinContent(i, val)
    pu_mc.Scale(1./pu_mc.Integral())
    return pu_mc

def calculate_data_pileup(xsec_scaling):
    """Calculate data pileup distribution"""
    xsec = MIN_BIAS_XSEC
    if xsec_scaling == "down":
        xsec = xsec / (1 + MIN_BIAS_XSEC_REL_UNCERT)
    elif xsec_scaling == "up":
        xsec = xsec * (1 + MIN_BIAS_XSEC_REL_UNCERT)

    cmd = "pileupCalc.py"
    cmd += " -i " + GOOD_RUN_JSON[YEAR]
    cmd += " --inputLumiJSON " + PILEUP_JSON[YEAR]
    cmd += " --calcMode true"
    cmd += " --minBiasXsec " + str(xsec)
    cmd += " --maxPileupBin " + str(MAX_PILEUP_BIN)
    cmd += " --numPileupBins " + str(MAX_PILEUP_BIN)
    cmd += " pileup_" + xsec_scaling + "_" + str(YEAR) + ".root"

    print(cmd)
    os.system(cmd)


def print_weights(xsec_scaling, mc_pileup_hist):
    """Print weights to apply to MC to match data"""
    pu_file = TFile("pileup_" + xsec_scaling + "_" + str(YEAR) + ".root")
    hist = pu_file.Get("pileup")
    hist.Scale(1./hist.Integral())
    hist.Divide(mc_pileup_hist)
    print(hist.Integral(), mc_pileup_hist.Integral())
    weight = [hist.GetBinContent(i+1) for i in range(hist.GetNbinsX())]

    print "std::vector<float> pileup::m_pileupWeights" + xsec_scaling,
    print " = std::vector<float>({"+', '.join('{:.3e}'.format(x) for x in weight)+"});"
    print "("+'+ '.join('(npv_true == {})* {:.3e}'.format(i+1, x) for i, x in enumerate(weight))+")"

hist_mc = make_mc_hist(YEAR)
scalings = ["up", "down", "nominal"]
for scaling in scalings:
    calculate_data_pileup(scaling)
    print_weights(scaling, hist_mc)
