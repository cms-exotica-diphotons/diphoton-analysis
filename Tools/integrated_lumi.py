#!/bin/env python
'''Output luminosity for 2015 and 2016 data samples.
   Note that this script only works on lxplus.'''
import os

OFFSITE = False

# set PATH according to option 1 here: 
# http://cms-service-lumi.web.cern.ch/cms-service-lumi/brilwsdoc.html#prerequisite
os.environ["PATH"] = os.environ["HOME"] + "/.local/bin:/cvmfs/cms-bril.cern.ch/brilconda/bin:" + os.environ["PATH"]

CMD_BASE = "brilcalc lumi -u /fb"
NORMTAGS = {'2015': "/afs/cern.ch/user/l/lumipro/public/normtag_file/OfflineNormtagV3_DCSOnly.json",
            '2016': "/afs/cern.ch/user/l/lumipro/public/Normtags/normtag_DATACERT.json",
            '2017': "/cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json",
            '2018': "/cvmfs/cms-bril.cern.ch/cms-lumi-pog/Normtags/normtag_PHYSICS.json"}

DATASETS = []
#DATASETS.append('DoubleEG__Run2015C_25ns-16Dec2015-v1')
#DATASETS.append('DoubleEG__Run2015D-16Dec2015-v2')

#DATASETS.append('DoubleEG__Run2016B-03Feb2017_ver2-v2')
#DATASETS.append('DoubleEG__Run2016C-03Feb2017-v1')
#DATASETS.append('DoubleEG__Run2016D-03Feb2017-v1')
#DATASETS.append('DoubleEG__Run2016E-03Feb2017-v1')
#DATASETS.append('DoubleEG__Run2016F-03Feb2017-v1')
#DATASETS.append('DoubleEG__Run2016G-03Feb2017-v1')
#DATASETS.append('DoubleEG__Run2016H-03Feb2017_ver2-v1')
#DATASETS.append('DoubleEG__Run2016H-03Feb2017_ver3-v1')

#DATASETS.append('EGamma__Run2018A-PromptReco-v1')
#DATASETS.append('EGamma__Run2018A-PromptReco-v2')
#DATASETS.append('EGamma__Run2018A-PromptReco-v3')
#DATASETS.append('EGamma__Run2018B-PromptReco-v1')
#DATASETS.append('EGamma__Run2018B-PromptReco-v2')
#DATASETS.append('EGamma__Run2018C-PromptReco-v1')
#DATASETS.append('EGamma__Run2018C-PromptReco-v2')
#DATASETS.append('EGamma__Run2018C-PromptReco-v3')

# new datasets start here

DATASETS.append('DoubleEG__Run2016B-17Jul2018_ver2-v1')
DATASETS.append('DoubleEG__Run2016C-17Jul2018-v1')
DATASETS.append('DoubleEG__Run2016D-17Jul2018-v1')
DATASETS.append('DoubleEG__Run2016E-17Jul2018-v1')
DATASETS.append('DoubleEG__Run2016F-17Jul2018-v1')
DATASETS.append('DoubleEG__Run2016G-17Jul2018-v1')
DATASETS.append('DoubleEG__Run2016H-17Jul2018-v1')

DATASETS.append('DoubleEG__Run2017B-31Mar2018-v1')
DATASETS.append('DoubleEG__Run2017C-31Mar2018-v1')
DATASETS.append('DoubleEG__Run2017D-31Mar2018-v1')
DATASETS.append('DoubleEG__Run2017E-31Mar2018-v1')
DATASETS.append('DoubleEG__Run2017F-31Mar2018-v1')

DATASETS.append('EGamma__Run2018A-17Sep2018-v2')
DATASETS.append('EGamma__Run2018B-17Sep2018-v1')
DATASETS.append('EGamma__Run2018C-17Sep2018-v1')
DATASETS.append('EGamma__Run2018D-22Jan2019-v2')

# ultra-legacy reprocessing
#DATASETS.append('Run2017C-09Aug2019_UL2017-v1')
#DATASETS.append('Run2017D-09Aug2019_UL2017-v1')
#DATASETS.append('Run2017E-09Aug2019_UL2017-v1')
#DATASETS.append('Run2017F-09Aug2019_UL2017-v1')

DATASETS.append('DoubleEG__Run2017B-UL2017_MiniAODv2-v1')
DATASETS.append('DoubleEG__Run2017C-UL2017_MiniAODv2-v2')
DATASETS.append('DoubleEG__Run2017D-UL2017_MiniAODv2-v1')
DATASETS.append('DoubleEG__Run2017E-UL2017_MiniAODv2-v1')
DATASETS.append('DoubleEG__Run2017F-UL2017_MiniAODv2-v2')

for dataset in DATASETS:
    json = "json/processedLumis_" + dataset + ".json"
    normtag = ''
    trigger = ''
    if 'Run2015' in dataset:
        normtag = NORMTAGS['2015']
        trigger = 'HLT_DoublePhoton60*'
    if 'Run2016' in dataset:
        normtag = NORMTAGS['2016']
        trigger = 'HLT_DoublePhoton60*'
    if 'Run2017' in dataset:
        normtag = NORMTAGS['2017']
        trigger = 'HLT_DoublePhoton70*'
    if 'Run2018' in dataset:
        normtag = NORMTAGS['2018']
        trigger = 'HLT_DoublePhoton70*'
    cmd = CMD_BASE + " --normtag " + normtag + " -i " + json + " --hltpath " + trigger
    if OFFSITE:
        cmd += " -c offsite"
    print cmd
    os.system(cmd)
