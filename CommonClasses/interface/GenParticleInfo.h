#ifndef GEN_PARTICLE_INFO
#define GEN_PARTICLE_INFO

namespace ExoDiPhotons
{

  struct GenMatchingFlags {

    enum MatchCategoryFlags {
      // match category:
      kNoMatchCategory = 0,      // 0 - no match category according to:
      kFinalStatePhotonMatch,    // 1 - final state photon match in desired DeltaR core
      kFinalStateNonPhotonMatch, // 2 - final state match NOT to photon in same DeltaR cone
      kGenParticlePhotonMatch,   // 3 - if no final state match, genParticle match of any status photon in desired DeltaR cone
      kGenParticleNonPhotonMatch // 4 - if no final state match, non-photon genParticle match of any status in desired DeltaR cone
    };
    
    enum MatchTypeFlags {
      // match type:
      kNoMatchType = 0,          // 0 - no match type
      kHadronMother,             // 1 - is hadron final state match or has hadron mother (fake)
      kISRfromProton,            // 2 - photon ISR directly from interacting proton (real)
      kOtherPhotonRadiation,     // 3 - other photon radiation (real)
      kGluonMotherPhotonFrag,    // 4 - photon fragmentation when photon's first mother is a gluon (fake)
      kOtherPhotonFragmentation, // 5 - other photon fragmentation (fake)
      kElectronPairMatch,        // 6 - final state electron match and electron pair found with no hadron mother (real or fake?)
      kPhotonMother,             // 7 - real photon with hard interaction photon mother
      kRealTemplatePhoton        // 8 - real template photon
    };
    
  };
  
  struct genParticleInfo_t {
    // kinematics
    double pt;
    double eta;
    double phi;

    // vertex
    double vx;
    double vy;
    double vz;

    // for matching
    double deltaR_match;
    double deltaR_matchDau;
    double ptDiff_match;
    int matchCategory;
    int matchType;
    int nPhotonMotherDaughters;
    
    // gen info
    int status;
    int motherStatus;
    int grandmotherStatus;
    int pdgId;
    int motherPdgId;
    int grandmotherPdgId;
  };

  const std::string genParticleBranchDefString("pt/D:eta:phi:vx:vy:vz:deltaR_match:deltaR_matchDau:ptDiff_match:matchCategory/I:matchType:nPhotonMotherDaughters:status:motherStatus:grandmotherStatus:pdgId:motherPdgId:grandmotherPdgId");

  void InitGenParticleInfo(genParticleInfo_t &genParticleInfo) {
    // kinematics
    genParticleInfo.pt  = -999999.99;
    genParticleInfo.eta = -999999.99;
    genParticleInfo.phi = -999999.99;

    // vertex
    genParticleInfo.vx  = -999999.99;
    genParticleInfo.vy = -999999.99;
    genParticleInfo.vz = -999999.99;
    
    // for matching
    genParticleInfo.deltaR_match           = -999999.99;
    genParticleInfo.deltaR_matchDau        = -999999.99;
    genParticleInfo.ptDiff_match           = -999999.99;
    genParticleInfo.matchCategory          = -999999;
    genParticleInfo.matchType              = -999999;
    genParticleInfo.nPhotonMotherDaughters = -999999;
    
    // gen info
    genParticleInfo.status            = -999999;
    genParticleInfo.motherStatus      = -999999;
    genParticleInfo.grandmotherStatus = -999999;
    genParticleInfo.pdgId             = -999999;
    genParticleInfo.motherPdgId       = -999999;
    genParticleInfo.grandmotherPdgId  = -999999;
  }

  void FillGenParticleInfo(genParticleInfo_t &genParticleInfo, const reco::GenParticle *genParticle) {
    // gen info
    genParticleInfo.status = genParticle->status();
    genParticleInfo.pdgId  = genParticle->pdgId();

    // gen info
    // mother and grandmother info
    double minMotherDeltaR      = 100000; // consider all mothers
    double minGrandmotherDeltaR = 100000;
    int motherIndex      = 0;
    int grandmotherIndex = 0;

    // if mother exists
    if (genParticle->numberOfMothers() > 0) {
      // find best match in deltaR among all mothers
      for (unsigned int j = 0; j < genParticle->numberOfMothers(); j++) {
	double deltaR = reco::deltaR(genParticle->eta(),genParticle->phi(),genParticle->mother(j)->eta(),genParticle->mother(j)->phi());
	if (deltaR < minMotherDeltaR) {
	  minMotherDeltaR = deltaR;
	  motherIndex = j;
	}
      }
      genParticleInfo.motherStatus = genParticle->mother(motherIndex)->status();
      genParticleInfo.motherPdgId  = genParticle->mother(motherIndex)->pdgId();

      // if grandMother exists
      if (genParticle->mother(motherIndex)->numberOfMothers() > 0) {
	// find best match in deltaR among all mothers
	for (unsigned int j = 0; j < genParticle->mother(motherIndex)->numberOfMothers(); j++) {
	  double deltaR = reco::deltaR(genParticle->mother(motherIndex)->eta(),genParticle->mother(motherIndex)->phi(),
				       genParticle->mother(motherIndex)->mother(j)->eta(),genParticle->mother(motherIndex)->mother(j)->phi());
	  if (deltaR < minGrandmotherDeltaR) {
	    minGrandmotherDeltaR = deltaR;
	    grandmotherIndex = j;
	  }
	}
	genParticleInfo.grandmotherStatus = genParticle->mother(motherIndex)->mother(grandmotherIndex)->status();
	genParticleInfo.grandmotherPdgId  = genParticle->mother(motherIndex)->mother(grandmotherIndex)->pdgId();
      }
      else {
	genParticleInfo.grandmotherStatus = -9999999;
	genParticleInfo.grandmotherPdgId  = -9999999;
      }
    }
    else {
      genParticleInfo.motherStatus      = -9999999;
      genParticleInfo.grandmotherStatus = -9999999;
      genParticleInfo.motherPdgId       = -9999999;
      genParticleInfo.grandmotherPdgId  = -9999999;
    }
    
    // kinematics
    genParticleInfo.pt  = genParticle->pt();
    genParticleInfo.eta = genParticle->eta();
    genParticleInfo.phi = genParticle->phi();

    // vertex
    genParticleInfo.vx = genParticle->vertex().x();
    genParticleInfo.vy = genParticle->vertex().y();
    genParticleInfo.vz = genParticle->vertex().z();

  }
  
}

#endif
