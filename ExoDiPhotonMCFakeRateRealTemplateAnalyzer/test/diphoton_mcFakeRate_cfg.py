from os.path import basename
# runtime options

diphoton_analysis = __import__("diphoton-analysis.CommonClasses.submit_utils")

from FWCore.ParameterSet.VarParsing import VarParsing
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
import importlib
submit_utils = importlib.import_module("diphoton-analysis.CommonClasses.submit_utils")

options = VarParsing ('python')

options.register('nEventsSample',
                 # 999011, # number of events in GGJets_M-500To1000_Pt-50_13TeV-sherpa 2015 sample
                 999921,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.int,
                 "Total number of events in dataset for event weight calculation."
                 )

options.setDefault('maxEvents', 1000)

options.parseArguments()

outName = options.outputFile
print("Default output name: " + outName)
if "output" in outName: # if an input file name is specified, event weights can be determined
    outName = "out_" + basename(options.inputFiles[0])
    print("Output root file name: " + outName)
else:
    options.inputFiles = "file:GGJets_M-1000To2000_Pt-50_13TeV-sherpa.root"


print "Output file name: ", outName
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
        #'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/0070A877-49D0-E511-877D-B083FED03632.root'
        #GGJets
        'root://cmsxrootd.fnal.gov//store/mc/RunIISummer16MiniAODv2/GGJets_M-500To1000_Pt-50_13TeV-sherpa/MINIAODSIM/PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6-v2/20000/18641080-BCCA-E711-B52C-0025907277FE.root'
        #'root://eoscms.cern.ch//store/mc/RunIIFall15MiniAODv2/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/04B53B17-24D9-E511-B1ED-00259075D72E.root'
        #'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/GGJets_M-500To1000_Pt-50_13TeV-sherpa/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/129F0188-B9D8-E511-9897-00259073E4F6.root'
        #GJets
        #'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/00C4C9FA-65BB-E511-AB87-50465DE43BAC.root'
        #QCD
        #'root://cmsxrootd.fnal.gov//store/mc/RunIIFall15MiniAODv2/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/047F51F9-8CB8-E511-89E5-28924A33B9FE.root'
        )
    )

# for global tag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
globalTag = diphoton_analysis.CommonClasses.submit_utils.get_global_tag(outName)
process.GlobalTag.globaltag = globalTag
print("Using global tag: " + globalTag)

# geometry for saturation
process.load("Configuration.StandardSequences.GeometryDB_cff")

# for output file
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(outName)
    )


# summary of information needed for e/gamma corrections
egm_info = submit_utils.egamma_info(outName)
setupEgammaPostRecoSeq(process,
                       applyEnergyCorrections=True,
                       applyVIDOnCorrectedEgamma=True,
                       runVID=True,
                       runEnergyCorrections=True,
                       era=egm_info['era'])

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
    jetsMiniAOD = cms.InputTag("updatedPatJetsUpdatedJEC"),
    jetPtThreshold = cms.double(30.),
    jetEtaThreshold = cms.double(2.5),
    # rho tag
    rho = cms.InputTag("fixedGridRhoAll"),
    # EGM eff. areas
    effAreaChHadFile = cms.FileInPath(egm_info['effAreaChHad']),
    effAreaNeuHadFile = cms.FileInPath(egm_info['effAreaNeuHad']),
    effAreaPhoFile = cms.FileInPath(egm_info['effAreaPhoHad']),
    # EGM ID decisions
    phoLooseIdMap = cms.InputTag("egmPhotonIDs:" + egm_info['loosePhoId']),
    phoMediumIdMap = cms.InputTag("egmPhotonIDs:" + egm_info['mediumPhoId']),
    phoTightIdMap = cms.InputTag("egmPhotonIDs:" + egm_info['tightPhoId']),
    # out file name
    outputFile = cms.string(outName),
    # number of events in the sample (for calculation of event weights)
    nEventsSample = cms.uint32(options.nEventsSample),
    # gen event info
    genInfo = cms.InputTag("generator", "", "SIM")
    )

# analyzer to print cross section
process.xsec = cms.EDAnalyzer("GenXSecAnalyzer")

process.p = cms.Path(process.egammaPostRecoSeq * process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC * process.diphoton * process.xsec)
