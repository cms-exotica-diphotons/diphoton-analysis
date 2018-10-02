#!/usr/bin/env python
"""Submit a set of crab jobs, passing the total number
of events in the sample as a parameter to CRAB so that
the event weight can be computed."""

import subprocess
import json
import os

def get_number_of_events(dataset):
  """Get number of events for dataset from DAS"""
  query = "file dataset=" + dataset + " | sum(file.nevents)"

  cmd = "dasgoclient --format=json --query='" + query + "'"
  print "Executing: " + cmd
  data = subprocess.check_output(cmd, shell=True)

  if isinstance(data, basestring):
    dasjson = json.loads(data)
  else:
    dasjson = data
  status  = dasjson.get('status')
  sumevents = 0
  if  status == 'ok':
    data = dasjson.get('data')
    for idata in data:
      sumevents += idata.get('file')[0]['nevents']
  return sumevents

do2018data = True
do2017data = False
do2017datarereco = False
do2016data = False
do2017mc = False
do2017mcv1 = False
do2016mc = False
dospring2016ggmc = False
do2016ggmc = False
do2015data = False
do2015mc = False
do2015signal = False
do2015signalint = False
do2016signal = False
do2016signalint = False


DATASETS = [[]]
# each entry contains a list of datasets, including extensions
# the extensions should be included so that the weight is calculated properly
# datasets with extensions should be added following this example:
#   datasets.append(["/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2-v1/MINIAODSIM",
#                   "/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15MiniAODv2-Asympt25ns_74X_mcRun2_asymptotic_v2_ext1-v1/MINIAODSIM"])


if do2018data:
#  DATASETS.append(["/EGamma/Run2018A-PromptReco-v1/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018A-PromptReco-v2/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018A-PromptReco-v3/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018B-PromptReco-v1/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018B-PromptReco-v2/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018C-PromptReco-v1/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018C-PromptReco-v2/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018C-PromptReco-v3/MINIAOD"])
#  DATASETS.append(["/EGamma/Run2018D-PromptReco-v1/MINIAOD"])
  DATASETS.append(["/EGamma/Run2018D-PromptReco-v2/MINIAOD"])
# diphoton samples (2017 data)
if do2017data:
### no good lumisections are present in Run2017A
##  DATASETS.append(["/DoubleEG/Run2017A-PromptReco-v2/MINIAOD"])
##  DATASETS.append(["/DoubleEG/Run2017A-PromptReco-v3/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017B-PromptReco-v1/MINIAOD"])
### re-recos overlap with prompt; do not use for now
##  DATASETS.append(["/DoubleEG/Run2017B-23Jun2017-v1/MINIAOD"])
##  DATASETS.append(["/DoubleEG/Run2017B-22Jun2017-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017B-PromptReco-v2/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017C-PromptReco-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017C-PromptReco-v2/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017C-PromptReco-v3/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017D-PromptReco-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017E-PromptReco-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017F-PromptReco-v1/MINIAOD"])
if do2017datarereco:
  DATASETS.append(["/DoubleEG/Run2017B-31Mar2018-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017C-31Mar2018-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017D-31Mar2018-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017E-31Mar2018-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2017F-31Mar2018-v1/MINIAOD"])
# diphoton samples (2016 data)
if do2016data:
# The /DoubleEG/Run2016B-03Feb2017_ver1-v1 dataset does not contain any lumisections
# passing the good run JSON
#  DATASETS.append(["/DoubleEG/Run2016B-03Feb2017_ver1-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016B-03Feb2017_ver2-v2/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016C-03Feb2017-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016D-03Feb2017-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016E-03Feb2017-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016F-03Feb2017-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016G-03Feb2017-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016H-03Feb2017_ver2-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2016H-03Feb2017_ver3-v1/MINIAOD"])
# the following datasets are only for the pre-re-miniaod data
#  DATASETS.append(["/DoubleEG/Run2016B-23Sep2016-v3/MINIAOD"])
#  DATASETS.append(["/DoubleEG/Run2016C-23Sep2016-v1/MINIAOD"])
#  DATASETS.append(["/DoubleEG/Run2016D-23Sep2016-v1/MINIAOD"])
#  DATASETS.append(["/DoubleEG/Run2016E-23Sep2016-v1/MINIAOD"])
#  DATASETS.append(["/DoubleEG/Run2016F-23Sep2016-v1/MINIAOD"])
#  DATASETS.append(["/DoubleEG/Run2016G-23Sep2016-v1/MINIAOD"])
#  DATASETS.append(["/DoubleEG/Run2016H-PromptReco-v2/MINIAOD"])
#  DATASETS.append(["/DoubleEG/Run2016H-PromptReco-v3/MINIAOD"])

if do2017mc:
  DATASETS.append(["/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-200To500_Pt-50_13TeV-sherpa/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-500To1000_Pt-50_13TeV-sherpa/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-60To200_Pt-50_13TeV-sherpa/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_1core_94X_mc2017_realistic_v14_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM"])
  DATASETS.append(['/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM'])
  DATASETS.append(['/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v2/MINIAODSIM'])
  DATASETS.append(['/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc2017_realistic_v14-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14-v1/MINIAODSIM'])

if do2017mcv1:
  DATASETS.append(["/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-200To500_Pt-50_13TeV-sherpa/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-500To1000_Pt-50_13TeV-sherpa/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-60To200_Pt-50_13TeV-sherpa/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM","/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-1core_94X_mc2017_realistic_v10_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/MINIAODSIM"])


# 8_0_X MC
if dospring2016ggmc:
  DATASETS.append(["/GGJets_M-60To200_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-200To500_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-500To1000_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])

if do2016ggmc:
  DATASETS.append(["/GGJets_M-60To200_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-200To500_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-500To1000_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])

if do2016mc:
#  DATASETS.append(["/GGGJets_13TeV-sherpa/RunIISpring16MiniAODv2-PUSpring16_80X_mcRun2_asymptotic_2016_miniAODv2_v0-v1/MINIAODSIM"])
  DATASETS.append(["/DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"])

  DATASETS.append(["/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v2/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"])

  DATASETS.append(['/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM','/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM', '/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v3/MINIAODSIM'])

  # minor backgrounds (true photon)
  DATASETS.append(["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM", "/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1/MINIAODSIM"])
  DATASETS.append(["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  DATASETS.append(["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM", "/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  # minor backgrounds (fake photon)
  DATASETS.append(["/WToLNu_0J_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  # not sure what "backup" means below
  DATASETS.append(["/WToLNu_1J_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_backup_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM"])
  DATASETS.append(["/WToLNu_2J_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/MINIAODSIM"])
  # should check that this is a sensible set of conditions
  DATASETS.append(["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISummer16MiniAODv2-BS2016_BSandPUSummer16_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM"])


# diphoton samples (2015 data)
if do2015data:
  DATASETS.append(["/DoubleEG/Run2015C_25ns-16Dec2015-v1/MINIAOD"])
  DATASETS.append(["/DoubleEG/Run2015D-16Dec2015-v2/MINIAOD"])

# diphoton samples (2015 MC)
if do2015mc:
  DATASETS.append(["/DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-60To200_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-200To500_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-500To1000_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v3/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-20to30_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-30to50_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-50to80_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-80to120_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-120to170_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-170to300_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/QCD_Pt-300toInf_EMEnriched_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])

  DATASETS.append(['/QCD_Pt_5to10_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_10to15_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])

  # minor backgrounds (true photon)
  DATASETS.append(["/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  # minor backgrounds (fake photon)
  DATASETS.append(["/WToLNu_0J_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/WToLNu_1J_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/WToLNu_2J_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(["/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])

# ADD samples
if do2015signal:
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-1_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-4_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-1_M-2000To3500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-4_M-2000To3500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-2000To3500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-4_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-3000To4500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-3000To4500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-3000To4500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-3000To5000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(["/ADDGravToGG_MS-5000_NED-2_KK-4_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM"])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-4_M-3000To5000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-2000To3000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-3000To5000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-4000To5500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-4000To5500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-4000To5500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-4000To6000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-4000To6000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-4000To6000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])

# SM diphoton background, needed to take into account interference between ADDGravToGG and SM background
if do2015signalint:
  DATASETS.append(['/GG_M-200To500_Pt-70_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-500To1000_Pt-70_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-1000To2000_Pt-70_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-2000To4000_Pt-70_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-4000To8000_Pt-70_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-8000To13000_Pt-70_13TeV-sherpa/RunIIFall15MiniAODv2-PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/MINIAODSIM'])

if do2016signal:
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-1_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-4_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-1_M-2000To3500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-4_M-2000To3500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-2000To3500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-3500_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-4_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-3000To4500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-3000To4500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-3000To4500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-4500_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-3000To5000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-4_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-4_M-3000To5000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-2000To3000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-3000To5000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-4000To5500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-4000To5500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-4000To5500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-5500_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-4000To6000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-4000To6000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-2_KK-4_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-200To500_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-4000To6000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-6000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-2_KK-1_M-4000To7000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-4_KK-1_M-4000To7000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-7000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-2_KK-1_M-4000To8000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-4_KK-1_M-4000To8000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-8000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-2_KK-1_M-4000To9000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-4_KK-1_M-4000To9000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-9000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-2_KK-1_M-4000To10000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-4_KK-1_M-4000To10000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-10000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-2_KK-1_M-4000To11000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-2_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-4_KK-1_M-4000To11000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/ADDGravToGG_MS-11000_NED-4_KK-1_M-500To1000_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])

if do2016signalint:
  DATASETS.append(['/GG_M-1000To2000_Pt-70_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-2000To4000_Pt-70_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-200To500_Pt-70_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-4000To8000_Pt-70_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-500To1000_Pt-70_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])
  DATASETS.append(['/GG_M-8000To13000_Pt-70_13TeV-sherpa/RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1/MINIAODSIM'])


for ilist in DATASETS:
  nevents = 0
  print ""
  for ids in ilist:
    nevents += get_number_of_events(ids)
    print "running nevents is " + str(nevents)

  for ids in ilist:
    cmssw_base = os.getenv("CMSSW_BASE")
    datasetID = ids.replace('/', '', 1).replace('/', '_', 1)
    datasetID = datasetID[0:datasetID.find('/')]
    inputfile = cmssw_base + "/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/crab_cfg_template.py"
    outputfile = "crab_cfg_" + datasetID + ".py"

    s = open(inputfile).read()
    s = s.replace('DATASETNAME', ids)
    s = s.replace('NEVENTS', str(nevents))
    f = open(outputfile, 'w')
    f.write(s)
    f.close()
    print "Wrote crab configuration file " + outputfile

    cmd = "crab submit -c " + outputfile
    os.system(cmd)
    print "Submitted ", ids

