# runtime options

from FWCore.ParameterSet.VarParsing import VarParsing

options = VarParsing ('python')

options.register('globalTag',
                 '76X_mcRun2_asymptotic_v12',
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "Global tag to use when running"
                 )
options.register('nEventsSample',
                 999011, # number of events in GGJets_M-500To1000_Pt-50_13TeV-sherpa sample
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.int,
                 "Total number of events in dataset for event weight calculation."
                 )
options.register('outputFileName',
                 "out_default_GGJets_M-500To1000_Pt-50_13TeV-sherpa.root",
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.string,
                 "Output filename."
                 )

options.setDefault('maxEvents', 1000)

options.parseArguments()

print "Output file name: ", options.outputFileName
print "Number of events in sample: ", options.nEventsSample

import FWCore.ParameterSet.Config as cms

process = cms.Process("ExoDiPhoton")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( options.maxEvents ) )

# for input file
process.source = cms.Source(
    "PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:myfile.root'
        #DiPhotonJets
        # 'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/0070A877-49D0-E511-877D-B083FED03632.root'
        #GGJets
        #'root://eoscms.cern.ch//store/mc/RunIIFall15MiniAODv2/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/04B53B17-24D9-E511-B1ED-00259075D72E.root'
        #'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/GGJets_M-500To1000_Pt-50_13TeV-sherpa/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/129F0188-B9D8-E511-9897-00259073E4F6.root'
        #GJets
        #'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/00C4C9FA-65BB-E511-AB87-50465DE43BAC.root'
        #QCD
        #'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/047F51F9-8CB8-E511-89E5-28924A33B9FE.root'
        'root://cmseos.fnal.gov//store/mc/RunIIFall15MiniAODv2/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/80000/66FA8D56-61D6-E511-BC0B-0002C94D5518.root'
        )
    )

# for global tag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = options.globalTag

# geometry for saturation
process.load("Configuration.StandardSequences.GeometryDB_cff")

# for output file
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(options.outputFileName)
    )

# Setup VID for EGM ID
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
switchOnVIDPhotonIdProducer(process, DataFormat.MiniAOD)
# define which IDs we want to produce
my_id_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring15_25ns_V1_cff']
#add them to the VID producer
for idmod in my_id_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)

## update AK4PFchs jet collection in MiniAOD JECs

from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection

updateJetCollection(
   process,
   jetSource = cms.InputTag('slimmedJets'),
   labelName = 'UpdatedJEC',
   jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None')  # Do not forget 'L2L3Residual' on data!
)

# main analyzer and inputs
process.diphoton = cms.EDAnalyzer(
    'ExoDiPhotonMCFakeRateRealTemplateAnalyzer',
    # photon tag
    photonsMiniAOD = cms.InputTag("slimmedPhotons"),
    # genParticle tag
    genParticlesMiniAOD = cms.InputTag("prunedGenParticles"),
    # ak4 jets
    jetsMiniAOD = cms.InputTag("selectedUpdatedPatJetsUpdatedJEC"),
    jetPtThreshold = cms.double(30.),
    jetEtaThreshold = cms.double(2.5),
    # rho tag
    rho = cms.InputTag("fixedGridRhoAll"),
    # EGM eff. areas
    effAreaChHadFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Spring15/effAreaPhotons_cone03_pfChargedHadrons_25ns_NULLcorrection.txt"),
    effAreaNeuHadFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Spring15/effAreaPhotons_cone03_pfNeutralHadrons_25ns_90percentBased.txt"),
    effAreaPhoFile = cms.FileInPath("RecoEgamma/PhotonIdentification/data/Spring15/effAreaPhotons_cone03_pfPhotons_25ns_90percentBased.txt"),
    # EGM ID decisions
    phoLooseIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-loose"),
    phoMediumIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-medium"),
    phoTightIdMap = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-tight"),
    # out file name
    outputFile = cms.string(options.outputFileName),
    # number of events in the sample (for calculation of event weights)
    nEventsSample = cms.uint32(options.nEventsSample),
    # gen event info
    genInfo = cms.InputTag("generator", "", "SIM")
    )

# analyzer to print cross section
process.xsec = cms.EDAnalyzer("GenXSecAnalyzer")

process.p = cms.Path(process.egmPhotonIDSequence * process.diphoton * process.xsec)
