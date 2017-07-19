import FWCore.ParameterSet.Config as cms

flashggVertexMapUnique = cms.EDProducer('FlashggDzVertexMapProducer',
                                        PFCandidatesTag=cms.InputTag('packedPFCandidates'),
                                        VertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'),
                                        MaxAllowedDz=cms.double(0.2),
                                        UseEachTrackOnce=cms.bool(True)
                                        )

flashggVertexMapNonUnique = cms.EDProducer('FlashggDzVertexMapProducer',
                                           PFCandidatesTag=cms.InputTag('packedPFCandidates'),
                                           VertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'),
                                           MaxAllowedDz=cms.double(0.2), 
                                           UseEachTrackOnce=cms.bool(False)
                                           )

flashggVertexMapForCHSOld = cms.EDProducer('FlashggDzVertexMapProducerForCHS',
                                       PFCandidatesTag=cms.InputTag('packedPFCandidates'),
                                       VertexTag=cms.InputTag('offlineSlimmedPrimaryVertices'),
                                       MaxAllowedDz=cms.double(0.1)
                                       )

# SK Note: bottom two are commented out, don't think we need them.
                                          
