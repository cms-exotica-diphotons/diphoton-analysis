## Template file for CRAB submission. The script generate_crab_config.py 
## replaces the following two lines with the appropriate values
## Do not edit manually!
import importlib
import os
import subprocess
submit_utils = importlib.import_module("diphoton-analysis.CommonClasses.submit_utils")

dataset = 'DATASETNAME'
nevents = NEVENTS
user = os.environ['USER']

# CRAB3 task names can no longer be greater than 100 characters; need to shorten task name
taskname = dataset[1:].replace('/','__').replace('RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2','MiniAODv2').replace('TuneCUETP8M1_13TeV-madgraphMLM-pythia8','13TeV-MG-PY8')
taskname = taskname.replace('RunIISpring15MiniAODv2-Asympt25ns_74X_mcRun2_asymptotic_v2','MiniAODv2')
taskname = taskname.replace('RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016','80XMiniAODv1')
taskname = taskname.replace('RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1','80XMiniAODv2')
taskname = taskname.replace('RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2','80XMiniAODv2')
taskname = taskname.replace('RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3', 'Summer16MiniAODv3')
taskname = taskname.replace('RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14', 'Fall17_PU2017')
taskname = taskname.replace('RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15', 'Autumn18')
taskname = taskname.replace(':','___')
if(len(taskname)>100): taskname = taskname[0:99]

datasetID = dataset.replace('/','',1).replace('/', '_', 1)
datasetID = datasetID[0:datasetID.find('/')]

from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = taskname
config.General.workArea = 'out_crab'
config.General.transferLogs = False

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'diphoton-analysis/ExoDiPhotonAnalyzer/test/diphoton_cfg.py'
config.JobType.pyCfgParams = ['nEventsSample=' + str(nevents), 'outputFile=out_' + datasetID + '.root']

config.section_("Data")
config.Data.inputDataset = dataset
config.Data.inputDBS = 'global'
if user == "cawest":
    cmssw_base = os.environ['CMSSW_BASE']
    commit_hash = subprocess.check_output(['git', '--git-dir=' + cmssw_base + '/src/diphoton-analysis/.git',  'rev-parse', '--short', 'HEAD']).replace('\n', '')
    config.Data.outLFNDirBase = '/store/user/' + user + '/diphoton/' + commit_hash
else:
    config.Data.outLFNDirBase = '/store/user/ciperez/DiPhotonAnalysis/ExoANDiphoton'

config.Data.lumiMask = submit_utils.get_good_run_JSON(taskname)
print('Using lumiMask: ' + config.Data.lumiMask)
# real data always has a dataset with "Run20" in the name
if "Run20" in taskname:
    config.Data.splitting = 'LumiBased'
    if "Run2018" in taskname:
        config.Data.unitsPerJob = 10
        if "Run2018D" in taskname:
            config.Data.unitsPerJob = 15
    else:
        config.Data.unitsPerJob = 100
else:
    config.Data.splitting = 'FileBased'
    config.Data.unitsPerJob = 2

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.blacklist = ['T1_RU_JINR', 'T2_US_Vanderbilt']
