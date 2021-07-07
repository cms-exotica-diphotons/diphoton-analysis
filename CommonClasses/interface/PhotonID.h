#ifndef PHOTON_ID_INC
#define PHOTON_ID_INC

// for pat::Photons
#include "DataFormats/PatCandidates/interface/Photon.h"

// for saturation
#include "RecoCaloTools/Navigation/interface/CaloNavigator.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

namespace ExoDiPhotons{

  // checking for saturated photons in 5x5 around seed crystal
  // considered saturated if any crystal is marked as saturated
  bool isSaturated(const pat::Photon *photon, const EcalRecHitCollection *recHitsEB, const EcalRecHitCollection *recHitsEE,
		   const CaloSubdetectorTopology* subDetTopologyEB_, const CaloSubdetectorTopology* subDetTopologyEE_) {
    using namespace std;
    
    bool isSat = false;
    DetId seedDetId = ((photon->superCluster())->seed())->seed();
    
    // check EB
    if (seedDetId.subdetId()==EcalBarrel) {
      CaloNavigator<DetId> cursor = CaloNavigator<DetId>(seedDetId,subDetTopologyEB_);
      for (int i = -2; i <= 2; ++i) {
      	for (int j = -2; j <= 2; ++j) {
      	  cursor.home();
      	  cursor.offsetBy(i,j);
      	  EcalRecHitCollection::const_iterator it = recHitsEB->find(*cursor);
      	  if(it != recHitsEB->end()) {
      	    /*cout << "Energy of (" << i << ", " << j << "): " << it-> energy()
	      << ", kSaturated: " << it->checkFlag(EcalRecHit::kSaturated)
	      << ", kDead: " << it->checkFlag(EcalRecHit::kDead)
	      << ", kKilled: " << it->checkFlag(EcalRecHit::kKilled)
	      << endl;*/
      	    if (it->checkFlag(EcalRecHit::kSaturated) && !it->checkFlag(EcalRecHit::kDead) && !it->checkFlag(EcalRecHit::kKilled)) {
      	      isSat = true;
      	    }
      	  }	  
      	}
      }
    }
    // check EE
    else if (seedDetId.subdetId()==EcalEndcap) {
      CaloNavigator<DetId> cursor = CaloNavigator<DetId>(seedDetId,subDetTopologyEE_);
      for (int i = -2; i <= 2; ++i) {
      	for (int j = -2; j <= 2; ++j) {
      	  cursor.home();
      	  cursor.offsetBy(i,j);
      	  EcalRecHitCollection::const_iterator it = recHitsEE->find(*cursor);
      	  if(it != recHitsEE->end()) {
      	    /*cout << "Energy of (" << i << ", " << j << "): " << it->energy()
	      << ", kSaturated: " << it->checkFlag(EcalRecHit::kSaturated)
	      << ", kDead: " << it->checkFlag(EcalRecHit::kDead)
	      << ", kKilled: " << it->checkFlag(EcalRecHit::kKilled)
	      << endl;*/
      	    if (it->checkFlag(EcalRecHit::kSaturated) && !it->checkFlag(EcalRecHit::kDead) && !it->checkFlag(EcalRecHit::kKilled)) {
      	      isSat = true;
      	    }
      	  }
      	}
      }
    }
    return isSat;
  }

  // ========================
  // Using High pT ID V2 cuts
  // ========================

  // H/E
  bool passHadTowerOverEmCut(const pat::Photon* photon) {
    double hOverE = photon->hadTowOverEm();
    if (hOverE < 0.05) return true;
    else return false;
  }

  // CH ISO
  bool passChargedHadronCut(const pat::Photon* photon) {
    double chIsoCut = 5.;
    double chIso = photon->chargedHadronIso();
    if (chIso < chIsoCut) return true;
    else return false;
  }

  bool passChargedHadronSideBandCut(const pat::Photon* photon, double sideBandLow, double sideBandHigh){
    double chIso = photon->chargedHadronIso();
    if ( (sideBandLow < chIso) && (chIso < sideBandHigh) ) return true;
    else return false;
  }

  bool passChargedHadronDenomCut(const pat::Photon* photon) {
    // double chIsoCut = 5.;
    double chIso = photon->chargedHadronIso();
    // if ( chIso < std::min((double)5.*chIsoCut, (double)0.2*photon->pt()) ) return true;
    if ( chIso < (double)0.2*photon->pt() ) return true; // updated denominator definition
    else return false;
  }

  bool passR9Cut(const pat::Photon* photon)
  {
    if(photon->full5x5_r9() > 0.8) return true;
    else return false;
  }

  // SIGMAiETAiETA
  bool passSigmaIetaIetaCut(const pat::Photon* photon, bool isSaturated) {
    double phoEta = fabs(photon->superCluster()->eta());
    double sIeIe = photon->full5x5_sigmaIetaIeta();
    double sIeIeCut = -1.;
    
    if (phoEta < 1.4442 && !isSaturated) sIeIeCut = 0.0105; 
    else if (phoEta < 1.4442 && isSaturated) sIeIeCut = 0.0112;
    else if (1.566 < phoEta && phoEta < 2.5 && !isSaturated) sIeIeCut = 0.0280; 
    else if (1.566 < phoEta && phoEta < 2.5 && isSaturated) sIeIeCut = 0.0300;

    if (sIeIe < sIeIeCut) return true;
    else return false;
  }

  // PHO ISO
  double phoAlphaHighPtID(const pat::Photon *photon) {
    double phoEta = fabs(photon->superCluster()->eta());
    if (phoEta < 1.4442) {
      if (phoEta < 0.9) {
	return 2.5;
      }
      else {
	return 2.5;
      }
    } // end EB
    else if (1.566 < phoEta && phoEta < 2.5) {
      if (phoEta < 2.0) {
	return 2.5;
      }
      else if (phoEta < 2.2) {
	return 2.5;
      }
      else {
	return 2.5;
      }
    } // end EE
    else {
      return -99999.99;
    }
  }
  
  double phoKappaHighPtID(const pat::Photon *photon) {
    double phoEta = fabs(photon->superCluster()->eta());
    if (phoEta < 1.4442) {
      if (phoEta < 0.9) {
	return 0.0045;
      }
      else {
	return 0.0045;
      }
    } // end EB
    else if (1.566 < phoEta && phoEta < 2.5) {
      if (phoEta < 2.0) {
	return 0.003;
      }
      else if (phoEta < 2.2) {
	return 0.003;
      }
      else {
	return 0.003;
      }
    } // end EE
    else {
      return -99999.99;
    }
  }
  
  double phoEAHighPtID(const pat::Photon* photon) {
    double phoEta = fabs(photon->superCluster()->eta());
    if (phoEta < 1.4442) {
      if (phoEta < 0.9) {
	return 0.17;
      }
      else {
	return 0.14;
      }
    } // end EB
    else if (1.566 < phoEta && phoEta < 2.5) {
      if (phoEta < 2.0) {
	return 0.11;
      }
      else if (phoEta < 2.2) {
	return 0.14;
      }
      else {
	return 0.22;
      }
    } // end EE
    else {
      return -99999.99;
    }
  }
  
  double corPhoIsoHighPtID(const pat::Photon* photon, double rho) {
    double phoIso = photon->photonIso();
    return (phoAlphaHighPtID(photon) + phoIso - rho*phoEAHighPtID(photon) - phoKappaHighPtID(photon)*photon->pt());
  }
  
  bool passCorPhoIsoHighPtID(const pat::Photon* photon, double rho) {
    double phoEta = fabs(photon->superCluster()->eta());
    double corPhoIsoCut = -999.9;
    double corPhoIso = corPhoIsoHighPtID(photon,rho);

    if (phoEta < 1.4442) corPhoIsoCut = 2.75;
    if (1.566 < phoEta && phoEta < 2.5) corPhoIsoCut = 2.00;

    if (corPhoIso < corPhoIsoCut) return true;
    else return false;
  }

  bool passCorPhoIsoDenom(const pat::Photon* photon, double rho) {
    // double phoEta = fabs(photon->superCluster()->eta());
    // double corPhoIsoCut = -999.9;
    double corPhoIso = corPhoIsoHighPtID(photon,rho);

    // if (phoEta < 1.4442) corPhoIsoCut = 2.75;
    // if (1.560 < phoEta && phoEta < 2.5) corPhoIsoCut = 2.00;
    
    // if ( corPhoIso < std::min((double)5.*corPhoIsoCut, (double)0.2*photon->pt()) ) return true;
    if ( corPhoIso < (double)0.2*photon->pt() ) return true; // updated denominator definition
    else return false;
  }

  bool passHighPtID(const pat::Photon* photon, double rho, bool isSat) {
    if (
      passHadTowerOverEmCut(photon) &&
      passChargedHadronCut(photon) &&
      passSigmaIetaIetaCut(photon,isSat) &&
      passCorPhoIsoHighPtID(photon,rho) &&
      photon->passElectronVeto() &&
      passR9Cut(photon)
    ) return true;

    else return false;
  }

  // must pass all cuts in the High pT ID except for the Sieie cut and chIso cut
  // NOTE: enforce chIso and sieie cuts offline depending on if this is used for numerator or fake template
  bool passNumeratorCandCut(const pat::Photon* photon, double rho) {
    if (
      passHadTowerOverEmCut(photon) &&
      passCorPhoIsoHighPtID(photon,rho) &&
      photon->passElectronVeto() &&
      passR9Cut(photon)
    ) return true;

    else return false;
  }

  bool passDenominatorCut(const pat::Photon* photon, double rho, bool isSat) {

    double phoEta = fabs( photon->superCluster()->eta() );
    bool isEB = phoEta < 1.4442;
    bool isEE = 1.566 < phoEta && phoEta < 2.5;
    
    // first check if the photon fails at least one of the high pT ID cuts
    bool failID = (
      !passHadTowerOverEmCut(photon) ||
      !passChargedHadronCut(photon) ||
      !passSigmaIetaIetaCut(photon,isSat) ||
      !passR9Cut(photon)
    );

    if (isEB)
      failID = failID || !passCorPhoIsoHighPtID(photon,rho);
    
    // now check if it pass the looser ID
    bool passLooseIso = passChargedHadronDenomCut(photon) && passCorPhoIsoDenom(photon,rho);
    
    // require object to pass CSEV
    bool passCSEV = photon->passElectronVeto();

    // require object to pass an additional reco::Photon::hadronicOverEm cut
    bool passHadOverEmCut = photon->hadronicOverEm() < 0.1;

    bool passCorIso = passCorPhoIsoHighPtID(photon,rho);
    
    bool retVal = false;
    if (isEB && failID && passLooseIso && passCSEV && passHadOverEmCut){
      retVal = true;
      // return true;
    }
    else if (isEE && failID && passLooseIso && passCSEV && passHadOverEmCut && passCorIso){
      retVal = true;
    }

    return retVal;
  }
  
}


#endif
