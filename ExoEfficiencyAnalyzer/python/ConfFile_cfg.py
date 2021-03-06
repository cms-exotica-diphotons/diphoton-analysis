import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        'file:/uscms/home/bbbam/mc_RunIIAutumn18MiniAOD_ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8_MINIAODSIM_102X_upgrade2018_realistic_v15-v1_70000_5C1E393E-C20D-E84F-9CD0-6399FA05DE2D.root'

    )
)


process.TFileService = cms.Service("TFileService",
                fileName = cms.string("ExoEfficiency.root")
                            )

process.demo = cms.EDAnalyzer('ExoEfficiencyAnalyzer',
    particles = cms.InputTag("prunedGenParticles")
)


process.p = cms.Path(process.demo)
