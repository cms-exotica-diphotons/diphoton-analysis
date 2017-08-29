from WMCore.Configuration import Configuration
config = Configuration()
config.section_('General')
config.General.transferOutputs = True
config.General.requestName = 'crab3test'
config.section_('JobType')
config.JobType.psetName = 'diphoton_fakeRate_cfg.py'
config.JobType.pyCfgParams = ['globalTag=80X_dataRun2_2016SeptRepro_v7',]
config.JobType.pluginName = 'Analysis'
#config.JobType.inputFiles = ['PileupDataAug10thHistogram.root', 'PileUpMC.root', 'Cert_13TeV_16Dec2015ReReco_Collisions15_25ns_JSON_Silver_v2.txt']
#config.JobType.outputFiles = ['ExoDiPhotonAnalyzer.root']
config.section_('Data')
config.Data.inputDataset = '/QCD_Pt_20_30_EMEnriched_TuneZ2star_8TeV_pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM'
config.Data.outputDatasetTag = ''
config.Data.outLFNDirBase = '/store/user/agarabag/noreplica/FakeRate/'
config.Data.publication = False
config.Data.unitsPerJob = 100
config.Data.totalUnits = -1
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt'
config.section_('User')
config.section_('Site')
config.Site.storageSite = 'T3_US_FNALLPC'


if __name__ == '__main__':

    from CRABAPI.RawCommand import crabCommand
    from CRABClient.ClientExceptions import ClientException
    from httplib import HTTPException

    # We want to put all the CRAB project directories from the tasks we submit here into one common directory.
    # That's why we need to set this parameter (here or above in the configuration file, it does not matter, we will not overwrite it).
    config.General.workArea = 'crab3fakeratedatajobs'

    def submit(config):
        try:
            crabCommand('submit', config = config)
        except HTTPException as hte:
            print "Failed submitting task: %s" % (hte.headers)
        except ClientException as cle:
            print "Failed submitting task: %s" % (cle)

    #############################################################################################
    ## From now on that's what users should modify: this is the a-la-CRAB2 configuration part. ##
    #############################################################################################

    config.General.requestName = 'JetHT_Run2016B_V1'
    config.Data.inputDataset = '/JetHT/Run2016B-03Feb2017_ver1-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016B_V2'
    config.Data.inputDataset = '/JetHT/Run2016B-03Feb2017_ver2-v2/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016C'
    config.Data.inputDataset = '/JetHT/Run2016C-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016D'
    config.Data.inputDataset = '/JetHT/Run2016D-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016E'
    config.Data.inputDataset = '/JetHT/Run2016E-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016F'
    config.Data.inputDataset = '/JetHT/Run2016F-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016G'
    config.Data.inputDataset = '/JetHT/Run2016G-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016H_V2'
    config.Data.inputDataset = '/JetHT/Run2016H-03Feb2017_ver2-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'JetHT_Run2016H_V3'
    config.Data.inputDataset = '/JetHT/Run2016H-03Feb2017_ver3-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016B_V1'
    config.Data.inputDataset = '/DoubleMuon/Run2016B-03Feb2017_ver1-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016B_V2'
    config.Data.inputDataset = '/DoubleMuon/Run2016B-03Feb2017_ver2-v2/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016C'
    config.Data.inputDataset = '/DoubleMuon/Run2016C-03Feb2017-v2/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016D'
    config.Data.inputDataset = '/DoubleMuon/Run2016D-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016E'
    config.Data.inputDataset = '/DoubleMuon/Run2016E-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016F'
    config.Data.inputDataset = '/DoubleMuon/Run2016F-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016G'
    config.Data.inputDataset = '/DoubleMuon/Run2016G-03Feb2017-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016H_V2'
    config.Data.inputDataset = '/DoubleMuon/Run2016H-03Feb2017_ver2-v1/MINIAOD'
    submit(config)

    config.General.requestName = 'DoubleMuon_Run2016H_V3'
    config.Data.inputDataset = '/DoubleMuon/Run2016H-03Feb2017_ver3-v1/MINIAOD'
    submit(config)
