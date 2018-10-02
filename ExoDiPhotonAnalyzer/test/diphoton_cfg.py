# runtime options
from FWCore.ParameterSet.VarParsing import VarParsing
import FWCore.ParameterSet.Config as cms
from os.path import basename
import os
import sys

options = VarParsing ('python')

options.register('nEventsSample',
                 100,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.int,
                 "Total number of events in dataset for event weight calculation.")
## 'maxEvents' is already registered by the Framework, changing default value 
options.setDefault('maxEvents', 100)

options.parseArguments()

outName = options.outputFile
print "Default output name: " + outName
if "output" in outName: # if an input file name is specified, event weights can be determined
    outName = "out_" + basename(options.inputFiles[0])
    print "Output root file name: " + outName
else:
    options.inputFiles = "file:GGJets_M-1000To2000_Pt-50_13TeV-sherpa.root"
#    outName = "ExoDiphotonAnalyzer.root"

isMC = True
# data always has "Run201" in its filename
if "Run201" in outName:
    isMC = False

# to avoid processing with an incorrect global tag, don't set a valid default
globalTag = 'notset'

jetLabel = "selectedUpdatedPatJetsUpdatedJEC"
# options for data
JEC = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute', 'L2L3Residual'])
# necessary because in re-MINIAOD the process labels are "PAT", not "RECO"
isReMINIAOD = False
if "Run2015" in outName:
    globalTag = '76X_dataRun2_16Dec2015_v0'
if "Run2016" in outName:
#    Do not use ICHEP global tag
#    globalTag = '80X_dataRun2_Prompt_ICHEP16JEC_v0'
    if 'PromptReco' in outName:
        globalTag = '80X_dataRun2_Prompt_v14'
    elif '03Feb2017' in outName:
        globalTag = '80X_dataRun2_2016SeptRepro_v7'
        isReMINIAOD = True
    else:
        globalTag = '80X_dataRun2_2016SeptRepro_v4'
if "Run2017" in outName:
    if "31Mar2018" in outName:
        isReMINIAOD = True
        globalTag = '94X_dataRun2_v6'
        jetLabel = "updatedPatJetsUpdatedJEC"
    else:
        globalTag = '92X_dataRun2_Prompt_v8'
        jetLabel = "updatedPatJetsUpdatedJEC"
if "Run2018" in outName:
    #globalTag = '101X_dataRun2_Prompt_v9'
    globalTag = '101X_dataRun2_Prompt_v11'
    jetLabel = "updatedPatJetsUpdatedJEC"
# override options for MC
if isMC:
    version = os.getenv("CMSSW_VERSION")
    if "CMSSW_9" in version:
        globalTag = '94X_mc2017_realistic_v14'
        jetLabel = "slimmedJets"
    elif "CMSSW_8" in version:
        if "Spring16" in outName:
            globalTag = '80X_mcRun2_asymptotic_2016_miniAODv2'
        if "Summer16" in outName:
            #globalTag = '80X_mcRun2_asymptotic_2016_TrancheIV_v6'
            # the previous tag should only be used when to process
            # samples intended to match data previous to the
            # 03Feb2017 re-miniAOD
            globalTag = '80X_mcRun2_asymptotic_2016_TrancheIV_v8'
    elif "CMSSW_7" in version:
        globalTag = '76X_mcRun2_asymptotic_v12'
    else:
        print "Could not determine appropriate MC global tag from filename"
        sys.exit()
    JEC = cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute'])


process = cms.Process("ExoDiPhoton")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.suppressWarning.append('ExoDiPhotonAnalyzer')

process.options = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )
process.options.allowUnscheduled = cms.untracked.bool(True)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( options.maxEvents ) )

process.source = cms.Source(
    "PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        options.inputFiles
        )
    )

# for global tag
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = globalTag
print "Using global tag: " + globalTag

# geometry for saturation
process.load("Configuration.StandardSequences.GeometryDB_cff")

# for output file
process.TFileService = cms.Service(
    "TFileService",
    fileName = cms.string(outName)
    )

process.primaryVertexFilter = cms.EDFilter("GoodVertexFilter",
                                           vertexCollection = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                           minimumNDOF = cms.uint32(4),
                                           maxAbsZ = cms.double(24),
                                           maxd0 = cms.double(2)
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
   jetCorrections = ('AK4PFchs', JEC, 'None')  # Do not forget 'L2L3Residual' on data!
)

# main analyzer and inputs
process.diphoton = cms.EDAnalyzer(
    'ExoDiPhotonAnalyzer',
    # photon tag
    photonsMiniAOD = cms.InputTag("slimmedPhotons"),
    minPhotonPt = cms.double(75.),
    # genParticle tag
    genParticlesMiniAOD = cms.InputTag("prunedGenParticles"),
    # vertex tag
    vertices = cms.InputTag("offlineSlimmedPrimaryVertices"),
    # beam spot tag
    beamSpot = cms.InputTag("offlineBeamSpot", "", "RECO"),
    # ak4 jets
    jetsMiniAOD = cms.InputTag(jetLabel),
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
    # gen event info
    genInfo = cms.InputTag("generator", "", "SIM"),
    # output file name
    outputFile = cms.string(outName),
    # number of events in the sample (for calculation of event weights)
    nEventsSample = cms.uint32(options.nEventsSample),
    isMC = cms.bool(isMC),
    isClosureTest = cms.bool(False),
    isReMINIAOD = cms.bool(isReMINIAOD),
    isolationConeR = cms.double(0.3)
    )

# analyzer to print cross section
process.xsec = cms.EDAnalyzer("GenXSecAnalyzer")
if isMC:
    process.p = cms.Path(process.egmPhotonIDSequence * process.diphoton * process.xsec)
else:
    if "Run2017" in outName or "Run2018" in outName:
        process.p = cms.Path(process.egmPhotonIDSequence * process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC * process.diphoton)
    else:
        process.p = cms.Path(process.egmPhotonIDSequence * process.patJetCorrFactorsUpdatedJEC * process.updatedPatJetsUpdatedJEC * process.diphoton)
