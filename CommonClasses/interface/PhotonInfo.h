#ifndef PHOTON_INFO_INC
#define PHOTON_INFO_INC

#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"

// for EGM ID
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

namespace ExoDiPhotons
{
  struct photonInfo_t {
    // kinematics
    double pt; // filled
    double eta; // filled
    double phi; // filled
    double scEta; // filled
    double scPhi; // filled

    // isolation
    double rho; // filled
    double chargedHadIso; // filled
    double chargedHadIso03; // filled
    double neutralHadIso03; // filled
    double photonIso03; // filled
    double rhoCorChargedHadIso03; // filled
    double rhoCorNeutralHadIso03; // filled
    double rhoCorPhotonIso03; // filled
    double corPhotonIso03; // filled
    double hadTowerOverEm; // filled
    double hadronicOverEm; // filled

    // shower shape variables
    double r9; // filled
    double r9_5x5; // filled
    double sigmaIetaIeta; // filled
    double sigmaIetaIeta5x5; // filled
    double sigmaEtaEta; // filled
    double sigmaIphiIphi; // filled
    double sigmaIphiIphi5x5; // filled
    double sigmaIetaIphi; // filled
    double sigmaIetaIphi5x5; // filled
    double maxEnergyXtal; // filled

    // detector channel info
    double iEta; // filled
    double iPhi; // filled
    
    // high pT ID
    double alphaHighPtID; // filled
    double kappaHighPtID; // filled
    double phoEAHighPtID; // filled
    double phoIsoExtraHighPtID; 

    // EGM ID
    double chEAegmID; // filled
    double nhEAegmID; // filled
    double phoEAegamID; // filled

    bool passEGMLooseID;
    bool passEGMMediumID;
    bool passEGMTightID;
    
    // fiducial flags
    bool isEB; // filled
    bool isEE; // filled
    bool isEBEtaGap; // filled
    bool isEBPhiGap; // filled
    bool isEERingGap; // filled
    bool isEEDeeGap; // filled
    bool isEBEEGap; // filled

    // electron veto and high pT ID checks
    bool passElectronVeto; // filled
    bool passHTowOverE; // filled
    bool passChIso; // filled
    bool passCorPhoIso; // filled
    bool passSieie; // filled
    bool passHighPtID; // filled

    // for fake rate
    bool passChIsoDenom; // filled
    bool passCorPhoIsoDenom; // filled
    bool isFakeable;
    bool isNumeratorObjCand; // filled
    bool isDenominatorObj; // filled

    // saturation
    bool isSaturated; // filled in analyzer and passed to FillPhotonIDInfo

    // mc truth info
    bool isMCTruthFake; // filled in analyzer
  };

  std::string photonBranchDefString("pt/D:eta:phi:scEta:scPhi:rho:chargedHadIso:chargedHadIso03:neutralHadIso03:photonIso03:rhoCorChargedHadIso03:rhoCorNeutralHadIso03:rhoCorPhotonIso03:corPhotonIso03:hadTowerOverEm:hadronicOverEm:r9:r9_5x5:sigmaIetaIeta:sigmaIetaIeta5x5:sigmaEtaEta:sigmaIphiIphi:sigmaIphiIphi5x5:sigmaIetaIphi:sigmaIetaIphi5x5:maxEnergyXtal:iEta:iPhi:alphaHighPtID:kappaHighPtID:phoEAHighPtID:phoIsoExtraHighPtID:chEAegmID:nhEAegmID:phoEAegmID:passEGMLooseID/O:passEGMMediumID:passEGMTightID:isEB:isEE:isEBEtaGap:isEBPhiGap:isEERingGap:isEEDeeGap:isEBEEGap:passElectronVeto:passHTowOverE:passChIso:passCorPhoIso:passSieie:passHighPtID:passChIsoDenom:passCorPhoIsoDenom:isFakeable:isNumeratorObjCand:isDenominatorObj:isSaturated:isMCTruthFake");

  void InitPhotonInfo(photonInfo_t &photonInfo)
  {
    // kinematics
    photonInfo.pt    = -9999.99;
    photonInfo.eta   = -9999.99;
    photonInfo.phi   = -9999.99;
    photonInfo.scEta = -9999.99;
    photonInfo.scPhi = -9999.99;

    // isolation
    photonInfo.rho                   = -9999.99;
    photonInfo.chargedHadIso         = -9999.99;
    photonInfo.chargedHadIso03       = -9999.99;
    photonInfo.neutralHadIso03       = -9999.99;
    photonInfo.photonIso03           = -9999.99;
    photonInfo.rhoCorChargedHadIso03 = -9999.99;
    photonInfo.rhoCorNeutralHadIso03 = -9999.99;
    photonInfo.rhoCorPhotonIso03     = -9999.99;
    photonInfo.corPhotonIso03        = -9999.99;
    photonInfo.hadTowerOverEm        = -9999.99;
    photonInfo.hadronicOverEm        = -9999.99;

    // shower shape variables 
    photonInfo.r9               = -9999.99;
    photonInfo.r9_5x5           = -9999.99;
    photonInfo.sigmaIetaIeta    = -9999.99;
    photonInfo.sigmaIetaIeta5x5 = -9999.99;
    photonInfo.sigmaEtaEta      = -9999.99;
    photonInfo.sigmaIphiIphi    = -9999.99;
    photonInfo.sigmaIphiIphi5x5 = -9999.99;
    photonInfo.sigmaIetaIphi    = -9999.99;
    photonInfo.sigmaIetaIphi5x5 = -9999.99;
    photonInfo.maxEnergyXtal    = -9999.99;

    // detector channel info
    photonInfo.iEta =  -9999.99;
    photonInfo.iPhi =  -9999.99;
    
    // high pT ID
    photonInfo.alphaHighPtID       = -9999.99;
    photonInfo.kappaHighPtID       = -9999.99;
    photonInfo.phoEAHighPtID       = -9999.99;
    photonInfo.phoIsoExtraHighPtID = -9999.99;

    // EGM ID
    photonInfo.chEAegmID       = -9999.99;
    photonInfo.nhEAegmID       = -9999.99;
    photonInfo.phoEAegamID     = -9999.99;
    photonInfo.passEGMLooseID  = false;
    photonInfo.passEGMMediumID = false;
    photonInfo.passEGMTightID  = false;
    
    // fiducial flags 
    photonInfo.isEB        = false;        
    photonInfo.isEE        = false;   
    photonInfo.isEBEtaGap  = false;   
    photonInfo.isEBPhiGap  = false;   
    photonInfo.isEERingGap = false; 
    photonInfo.isEEDeeGap  = false;   
    photonInfo.isEBEEGap   = false;

    // electron veto and high pT ID checks
    photonInfo.passElectronVeto = false;
    photonInfo.passHTowOverE    = false;
    photonInfo.passChIso        = false;
    photonInfo.passCorPhoIso    = false;
    photonInfo.passSieie        = false;
    photonInfo.passHighPtID     = false;

    // for fake rate
    photonInfo.passChIsoDenom     = false;
    photonInfo.passCorPhoIsoDenom = false;
    photonInfo.isFakeable         = false;
    photonInfo.isNumeratorObjCand = false;
    photonInfo.isDenominatorObj   = false;

    // saturation
    photonInfo.isSaturated = false;

    // mc truth info
    photonInfo.isMCTruthFake = false;
  }
  
  void FillBasicPhotonInfo(photonInfo_t &photonInfo, const pat::Photon *photon)
  {
    double photon_eta = std::abs(photon->superCluster()->eta());
    
    // kinematics
    photonInfo.pt          = photon->pt();
    photonInfo.eta         = photon->eta();
    photonInfo.phi         = photon->phi();
    photonInfo.scEta       = photon->superCluster()->eta();
    photonInfo.scPhi       = photon->superCluster()->phi();
    
    // fiducial flags
    photonInfo.isEB        = photon_eta < 1.4442; //photon->isEB();
    photonInfo.isEE        = 1.566 < photon_eta && photon_eta < 2.5; //photon->isEE();
    photonInfo.isEBEtaGap  = photon->isEBEtaGap();
    photonInfo.isEBPhiGap  = photon->isEBPhiGap();
    photonInfo.isEERingGap = photon->isEERingGap();
    photonInfo.isEEDeeGap  = photon->isEEDeeGap();
    photonInfo.isEBEEGap   = photon->isEBEEGap();
  }
  
  void FillPhotonIDInfo(photonInfo_t &photonInfo, const pat::Photon *photon, double rho, bool isMC, double isSat)
  {
    // isolation
    photonInfo.rho              = rho;
    photonInfo.chargedHadIso03  = photon->chargedHadronIso();
    photonInfo.neutralHadIso03  = photon->neutralHadronIso();
    photonInfo.photonIso03      = photon->photonIso();
    photonInfo.corPhotonIso03   = ExoDiPhotons::corPhoIsoHighPtID(photon,rho,isMC);
    photonInfo.hadTowerOverEm   = photon->hadTowOverEm();
    photonInfo.hadronicOverEm   = photon->hadronicOverEm();

    // shower shape variables
    photonInfo.r9               = photon->r9();
    photonInfo.r9_5x5           = photon->full5x5_r9();
    photonInfo.sigmaIetaIeta    = photon->sigmaIetaIeta();
    photonInfo.sigmaIetaIeta5x5 = photon->full5x5_sigmaIetaIeta();
    photonInfo.sigmaEtaEta      = photon->sigmaEtaEta();
    photonInfo.sigmaIphiIphi    = photon->showerShapeVariables().sigmaIphiIphi;
    photonInfo.sigmaIphiIphi5x5 = photon->full5x5_showerShapeVariables().sigmaIphiIphi;
    photonInfo.sigmaIetaIphi    = photon->showerShapeVariables().sigmaIetaIphi;
    photonInfo.sigmaIetaIphi5x5 = photon->full5x5_showerShapeVariables().sigmaIetaIphi;
    photonInfo.maxEnergyXtal    = photon->maxEnergyXtal();

    // detector channel info
    photonInfo.iEta             = photon->iEta();
    photonInfo.iPhi             = photon->iPhi();
    
    // high pT ID
    photonInfo.alphaHighPtID       = ExoDiPhotons::phoAlphaHighPtID(photon);
    photonInfo.kappaHighPtID       = ExoDiPhotons::phoKappaHighPtID(photon);
    photonInfo.phoEAHighPtID       = ExoDiPhotons::phoEAHighPtID(photon);
    photonInfo.phoIsoExtraHighPtID = ExoDiPhotons::getExtra(photonInfo.scEta,rho);
    
    // electron veto and high pT ID checks
    photonInfo.passElectronVeto = photon->passElectronVeto();
    photonInfo.passHTowOverE    = ExoDiPhotons::passHadTowerOverEmCut(photon);
    photonInfo.passChIso        = ExoDiPhotons::passChargedHadronCut(photon);
    photonInfo.passCorPhoIso    = ExoDiPhotons::passCorPhoIsoHighPtID(photon,rho,isMC);
    photonInfo.passSieie        = ExoDiPhotons::passSigmaIetaIetaCut(photon,isSat);
    photonInfo.passHighPtID     = ExoDiPhotons::passHighPtID(photon,rho,isMC,isSat);

    // for fake rate
    photonInfo.passChIsoDenom     = ExoDiPhotons::passChargedHadronDenomCut(photon);
    photonInfo.passCorPhoIsoDenom = ExoDiPhotons::passCorPhoIsoDenom(photon,rho,isMC);
    photonInfo.isNumeratorObjCand = ExoDiPhotons::passNumeratorCandCut(photon,rho,isMC);
    photonInfo.isDenominatorObj   = ExoDiPhotons::passDenominatorCut(photon,rho,isMC,isSat);
  }

  void FillPhotonEGMidInfo(photonInfo_t &photonInfo, const pat::Photon *photon, double rho, EffectiveAreas eaCH, EffectiveAreas eaNH, EffectiveAreas eaPho)
  {
    double chEA  = eaCH.getEffectiveArea(std::abs(photon->superCluster()->eta()));
    double nhEA  = eaNH.getEffectiveArea(std::abs(photon->superCluster()->eta()));
    double phoEA = eaPho.getEffectiveArea(std::abs(photon->superCluster()->eta()));
    
    photonInfo.chEAegmID   = chEA;
    photonInfo.nhEAegmID   = nhEA;
    photonInfo.phoEAegamID = phoEA;

    photonInfo.rhoCorChargedHadIso03 = std::max((double)0.0, (double)photon->chargedHadronIso()-rho*chEA);
    photonInfo.rhoCorNeutralHadIso03 = std::max((double)0.0, (double)photon->neutralHadronIso()-rho*nhEA);
    photonInfo.rhoCorPhotonIso03     = std::max((double)0.0, (double)photon->photonIso()       -rho*phoEA);
  }

  // sort two photons by highest pt
  bool comparePhotonsByPt(const edm::Ptr<const reco::Candidate> photon1, const edm::Ptr<const reco::Candidate> photon2) {
    return(photon1->pt()>=photon2->pt());
  }
  // alternate version for considering true and fake photons simultaneously
  bool comparePhotonPairsByPt(const std::pair<edm::Ptr<pat::Photon>, int> photon1, const std::pair<edm::Ptr<pat::Photon>, int> photon2) {
    return(photon1.first->pt()>=photon2.first->pt());
  }
  
} // end of namespace

#endif
