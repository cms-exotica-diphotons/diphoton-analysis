#ifndef PHOTON_ID_INC
#define PHOTON_ID_INC

// for pat::Photons
#include "DataFormats/PatCandidates/interface/Photon.h"

// for saturation
#include "RecoCaloTools/Navigation/interface/CaloNavigator.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

// for the data/mc correction to phoIso
#include "diphoton-analysis/CommonClasses/interface/IsoCorrections.h"

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

  // top function needed for higgs diphotons where chIso must be recalculated
  bool passChargedHadronCut(double chIso) {
    double chIsoCut = 5.;
    if (chIso < chIsoCut) return true;
    else return false;
  }
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
    return 1.76;
      }
      else {
    return 1.76;
      }
    } // end EB
    else if (1.566 < phoEta && phoEta < 2.5) {
      if (phoEta < 2.0) {
    return 1.23;
      }
      else if (phoEta < 2.2) {
    return 1.23;
      }
      else {
    return 1.23;
      }
    } // end EE
    else {
      return 99999.99;
    }
  }
  
  double phoKappaHighPtID(const pat::Photon *photon) {
    double phoEta = fabs(photon->superCluster()->eta());
    if (phoEta < 1.4442) {
      if (phoEta < 0.9) {
    return 0.0016;
      }
      else {
    return 0.0016;
      }
    } // end EB
    else if (1.566 < phoEta && phoEta < 2.5) {
      if (phoEta < 2.0) {
    return 0.00075;
      }
      else if (phoEta < 2.2) {
    return 0.00075;
      }
      else {
    return 0.00075;
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
    return 0.15;
      }
      else {
    return 0.13;
      }
    } // end EB
    else if (1.566 < phoEta && phoEta < 2.5) {
      if (phoEta < 2.0) {
    return 0.093;
      }
      else if (phoEta < 2.2) {
    return 0.15;
      }
      else {
    return 0.21;
      }
    } // end EE
    else {
      return -99999.99;
    }
  }
  // data/mc correction to photon isolation from the resonant group
  double getExtra(float eta, float rho, float extraMult=0) {

    // make sure eta is |eta|
    eta = fabs(eta);

    std::vector<float> eta_centers_ = ExoDiPhotons::eta_centers_;
    std::vector<float> rho_centers_eb_ = ExoDiPhotons::rho_centers_eb_;
    std::vector<float> rho_centers_ee_ = ExoDiPhotons::rho_centers_ee_;
    std::vector<float> extra_multiplicity_ = ExoDiPhotons::extra_multiplicity_;
    std::vector<float> extra_multiplicity_slope_ = ExoDiPhotons::extra_multiplicity_slope_;
    std::vector<TH1*> histograms_ = ExoDiPhotons::histograms_;

    int n_rho_centers_ = std::max(rho_centers_eb_.size(),rho_centers_ee_.size());
        
    int ieta = ExoDiPhotons::findIndex(eta,eta_centers_);
        
    if( extraMult <= 0 ) {
      extraMult = extra_multiplicity_[ieta] + ( ! extra_multiplicity_slope_.empty() ? extra_multiplicity_slope_[ieta] * rho : 0. );
    }
    float floor = std::floor(extraMult);
    int ngen = int(floor);
    // std::cout << extraMult << " " << floor << " " << ngen << std::endl;
    float rnd = gRandom->Uniform();
    if( rnd < extraMult - floor ) { ngen += 1; }
    // std::cout << extraMult << " " << floor << " " << rnd << " " << ngen << std::endl;

    if( ngen == 0 ) { return 0.; }


    auto & rho_centers = eta_centers_[ieta] < 1.5 ? rho_centers_eb_ : rho_centers_ee_;
    int irho = ExoDiPhotons::findIndex(rho, rho_centers);
    if ( ! multiplicity_offset_.empty() ) {
      irho = std::max(0,( multiplicity_offset_[ieta] < 10 ? irho - multiplicity_offset_[ieta] : 0 ));
    }

    auto ibin = ExoDiPhotons::index(ieta,irho,n_rho_centers_);        
    auto * hist = histograms_[ibin];
        
    float extra = 0.;
    float thr = hist->GetXaxis()->GetBinLowEdge(2);
    while( ngen > 0 ) {
      --ngen;
      float gen = hist->GetRandom();
      if( gen > thr ) extra += gen;
    }
    // want to return a double to match all other values!
    double extraD = 1.*extra; // not sure if the 1.* is needed for the conversion, but certainly doesn't hurt
    return extraD;
  }
  double corPhoIsoHighPtID(const pat::Photon* photon, double rho, bool isMC) {
    double phoIso = photon->photonIso();
    double eta = fabs(photon->superCluster()->eta());
    // the "extra" correction is only to correct MC to data, so only needed for MC!
    double extra = 0.;
    if (isMC) extra  = getExtra(eta,rho);
    return (phoIso + extra - rho*phoEAHighPtID(photon) );
  }
  
  bool passCorPhoIsoHighPtID(const pat::Photon* photon, double rho, bool isMC) {
    // double phoEta = fabs(photon->superCluster()->eta());
    double phoPt = photon->pt();
    double corPhoIsoCut = -999.9;
    double corPhoIso = corPhoIsoHighPtID(photon,rho,isMC);

    corPhoIsoCut = phoAlphaHighPtID(photon)+phoKappaHighPtID(photon)*phoPt;

    if (corPhoIso < corPhoIsoCut) return true;
    else return false;
  }

  bool passCorPhoIsoDenom(const pat::Photon* photon, double rho, bool isMC) {
    // double phoEta = fabs(photon->superCluster()->eta());
    // double corPhoIsoCut = -999.9;
    double corPhoIso = corPhoIsoHighPtID(photon,rho,isMC);

    // if (phoEta < 1.4442) corPhoIsoCut = 2.75;
    // if (1.560 < phoEta && phoEta < 2.5) corPhoIsoCut = 2.00;
    
    // if ( corPhoIso < std::min((double)5.*corPhoIsoCut, (double)0.2*photon->pt()) ) return true;
    if ( corPhoIso < (double)0.2*photon->pt() ) return true; // updated denominator definition
    else return false;
  }

  bool passHighPtID(const pat::Photon* photon, double rho, bool isMC, bool isSat) {
    if (
      passHadTowerOverEmCut(photon) &&
      passChargedHadronCut(photon) &&
      passSigmaIetaIetaCut(photon,isSat) &&
      passCorPhoIsoHighPtID(photon,rho,isMC) &&
      photon->passElectronVeto()
    ) return true;

    else return false;
  }
  bool passHighPtID_HiggsChIso(const pat::Photon* photon, double rho, bool isMC, bool isSat, double chIso) {
    if (
      passHadTowerOverEmCut(photon) &&
      passChargedHadronCut(chIso) &&
      passSigmaIetaIetaCut(photon,isSat) &&
      passCorPhoIsoHighPtID(photon,rho,isMC) &&
      photon->passElectronVeto()
    ) return true;

    else return false;
  }

  // must pass all cuts in the High pT ID except for the Sieie cut and chIso cut
  // NOTE: enforce chIso and sieie cuts offline depending on if this is used for numerator or fake template
  bool passNumeratorCandCut(const pat::Photon* photon, double rho, bool isMC) {
    if (
      passHadTowerOverEmCut(photon) &&
      passCorPhoIsoHighPtID(photon,rho,isMC) &&
      photon->passElectronVeto()
    ) return true;

    else return false;
  }

  bool passDenominatorCut(const pat::Photon* photon, double rho, bool isMC, bool isSat) {

    double phoEta = fabs( photon->superCluster()->eta() );
    bool isEB = phoEta < 1.4442;
    bool isEE = 1.566 < phoEta && phoEta < 2.5;
    
    // first check if the photon fails at least one of the high pT ID cuts
    bool failID = (
      !passHadTowerOverEmCut(photon) ||
      !passChargedHadronCut(photon) ||
      !passSigmaIetaIetaCut(photon,isSat)

    );

    if (isEB)
      failID = failID || !passCorPhoIsoHighPtID(photon,rho,isMC);
    
    // now check if it pass the looser ID
    bool passLooseIso = passChargedHadronDenomCut(photon) && passCorPhoIsoDenom(photon,rho,isMC);
    
    // require object to pass CSEV
    bool passCSEV = photon->passElectronVeto();

    // require object to pass an additional reco::Photon::hadronicOverEm cut
    bool passHadOverEmCut = photon->hadronicOverEm() < 0.1;

    bool passCorIso = passCorPhoIsoHighPtID(photon,rho,isMC);
    
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
