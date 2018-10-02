## Template file for CRAB submission. The script generate_crab_config.py 
## replaces the following two lines with the appropriate values
## Do not edit manually!
dataset = 'DATASETNAME'
nevents = NEVENTS

# CRAB3 task names can no longer be greater than 100 characters; need to shorten task name
taskname = dataset[1:].replace('/','__').replace('RunIISpring15MiniAODv2-74X_mcRun2_asymptotic_v2','MiniAODv2').replace('TuneCUETP8M1_13TeV-madgraphMLM-pythia8','13TeV-MG-PY8')
taskname = taskname.replace('RunIISpring15MiniAODv2-Asympt25ns_74X_mcRun2_asymptotic_v2','MiniAODv2')
taskname = taskname.replace('RunIISpring16MiniAODv1-PUSpring16_80X_mcRun2_asymptotic_2016','80XMiniAODv1')
taskname = taskname.replace('RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v1','80XMiniAODv2')
taskname = taskname.replace('RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2','80XMiniAODv2')
taskname = taskname.replace(':','___')
if(len(taskname)>100): taskname = taskname[0:99]

datasetID = dataset.replace('/','',1).replace('/', '_', 1)
datasetID = datasetID[0:datasetID.find('/')]

from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
#config.General.requestName = taskname
#config.General.requestName = taskname+"_json_toRun2018cv3"
#config.General.requestName = taskname+"_json_Run2018Dv2_320673-322057"
#config.General.requestName = taskname+"_json_Run2018Dv2_322057-322381"
#config.General.requestName = taskname+"_json_toRun2018Dv2_322381"
config.General.requestName = taskname+"_json_Run2018Dv2_322381_322633"
config.General.workArea = 'out_crab'
config.General.transferLogs = False

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'diphoton-analysis/ExoDiPhotonAnalyzer/test/diphoton_cfg.py'
#config.JobType.psetName = '/uscms/home/cuperez/nobackup/CMSSW_10_1_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/diphoton_cfg.py'
config.JobType.pyCfgParams = ['nEventsSample=' + str(nevents), 'outputFile=out_' + datasetID + '.root']

config.section_("Data")
config.Data.inputDataset = dataset
config.Data.inputDBS = 'global'
config.Data.outLFNDirBase = '/store/user/ciperez/DiPhotonAnalysis/EGammaData'

if "Run2018" in taskname:
    config.Data.splitting = 'LumiBased'
    config.Data.unitsPerJob = 10
    #config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions18/13TeV/PromptReco/Cert_314472-319851_13TeV_PromptReco_Collisions18_JSON.txt'
    #config.Data.lumiMask = '/uscms/home/cuperez/nobackup/CMSSW_10_1_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/json_two.json'
    #config.Data.lumiMask = '/uscms/home/cuperez/nobackup/CMSSW_10_1_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/json_toRun2018cv3.json' 
    #config.Data.lumiMask = '/uscms/home/cuperez/nobackup/CMSSW_10_1_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/json_Run2018Dv2_320673-322057.json' 
    #config.Data.lumiMask = '/uscms/home/cuperez/nobackup/CMSSW_10_1_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/json_Run2018Dv2_322057-322381.json'
    #config.Data.lumiMask = '/uscms/home/cuperez/nobackup/CMSSW_10_1_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/Cert_314472-322381_13TeV_PromptReco_Collisions18_JSON.txt'
    #config.Data.lumiMask = '/uscms/home/cuperez/nobackup/CMSSW_10_1_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/json_Run2018Dv2_3220673-322381.json'
    config.Data.lumiMask = '/uscms_data/d3/cuperez/CMSSW_10_2_1/src/diphoton-analysis/ExoDiPhotonAnalyzer/test/json_Run2018Dv2_322381to322633.json'	
    config.Data.runRange = '322381-322633' # 'Run2018Dv2 partial'
elif "Run2017" in taskname:
    config.Data.splitting = 'LumiBased'
    config.Data.unitsPerJob = 100
    if "31Mar2018" in taskname:
        config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/ReReco/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt'
    else:
        config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions17/13TeV/PromptReco/Cert_294927-306126_13TeV_PromptReco_Collisions17_JSON.txt'
elif "Run2016" in taskname:
    config.Data.splitting = 'LumiBased'
    config.Data.unitsPerJob = 100
    if "Prompt" in taskname:
        config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/Final/Cert_271036-284044_13TeV_PromptReco_Collisions16_JSON.txt'
    # otherwise, assume Re-Reco
    else:
        config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
elif "Run2015" in taskname:
    config.Data.splitting = 'LumiBased'
    config.Data.unitsPerJob = 100
    # only use 16Dec2015 ReReco
    config.Data.lumiMask = 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Reprocessing/Cert_13TeV_16Dec2015ReReco_Collisions15_25ns_JSON_Silver_v2.txt'
else:
    config.Data.splitting = 'FileBased'
    config.Data.unitsPerJob = 5

config.section_("Site")
#config.Site.storageSite = 'T2_CH_CERN'
config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.blacklist = ['T1_RU_JINR', 'T2_US_Vanderbilt']
