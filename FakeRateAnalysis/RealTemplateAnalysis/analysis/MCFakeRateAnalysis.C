#define MCFakeRateAnalysis_cxx
// use for ntuple structure without systematic variations
//#include "MCFakeRateAnalysis.h"
// use for ntuple structure with systematic variations
#include "MCFakeRateAnalysis_new_ntuple.h"
#include <TH2.h>
#include <TLorentzVector.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <map>
#include <iostream>

#include "diphoton-analysis/FakeRateAnalysis/interface/utilities.hh"

void MCFakeRateAnalysis::Loop(const TString& year, const std::string & sample, int pvCutLow = 0, int pvCutHigh = 500, bool closure_test=false)
{
  if (closure_test) std::cout << "Doing Closure Test" << std::endl;
//   In a ROOT session, you can do:
//      root> .L MCFakeRateAnalysis.C
//      root> MCFakeRateAnalysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  int nbinsSieieEB = 200;
  int nbinsSieieEE = 100;
  int nbinsChIso   = 100;

  TString pv = Form("_nPV%i-%i", pvCutLow, pvCutHigh);
  std::map<TString, TString> filenameMap;
  filenameMap["DiPhotonJets"] = "DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8";
  filenameMap["GGJets"] = "GGJets_M-all_Pt-50_13TeV-sherpa";
  filenameMap["GJets"] = "GJets_HT-all_TuneCUETP8M1_13TeV-madgraphMLM-pythia8";
  filenameMap["all"] = "all_GGJets_GJets";
  std::cout << "year: " << year << std::endl;
  TString filename = "diphoton_fake_rate_real_templates_" + filenameMap[sample] + "_" + year +  pv + "_MiniAOD_histograms.root";

  std::cout << "\nOutput filename: " << filename << std::endl << std::endl;

  // define our pT bin increments
  std::vector<int> ptBinArray({ 50, 70, 90, 110, 130, 150, 200, 250, 300, 600});

  std::vector<int> binLowEdges, binUpperEdges;
  for(unsigned int i = 0; i < ptBinArray.size()-1; i++) {
    binLowEdges.push_back(ptBinArray[i]);
    binUpperEdges.push_back(ptBinArray[i+1]);
  }
  // so that the highest bin can also range from 150 < pT < 600 GeV
  binLowEdges.push_back(150);
  binUpperEdges.push_back(600);
  const int nBins = ptBinArray.size();

  // define vectors of desired histograms
  std::vector<TH1D*> sigmaIetaIetaEB;
  std::vector<TH1D*> sigmaIetaIetaEB1;
  std::vector<TH1D*> sigmaIetaIetaEB2;
  std::vector<TH1D*> sigmaIetaIetaEE;
  std::vector<TH1D*> sigmaIetaIetaEE1;
  std::vector<TH1D*> sigmaIetaIetaEE2;
  std::vector<TH1D*> chIsoEB;
  std::vector<TH1D*> chIsoEE;

  // loop over bins increments and create histograms
  for (int i = 0; i < nBins; i++) {
    int binLowEdge = binLowEdges[i];
    int binUpperEdge = binUpperEdges[i];

    if (closure_test){
      nbinsSieieEB = 50;
      nbinsSieieEE = 25;
      nbinsChIso   = 50;
      std::cout << "Using closure test binning: " << "EB: " << nbinsSieieEB << "; EE: " << nbinsSieieEE << "; ChIso: " << nbinsChIso << std::endl;
    }

    TH1D *hEB = new TH1D(Form("sieieEB_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"sigmaIetaIetaEB",nbinsSieieEB,0.,0.1);
    hEB->Sumw2();
    sigmaIetaIetaEB.push_back(hEB);

    TH1D *hEB1 = new TH1D(Form("sieieEB1_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"sigmaIetaIetaEB1",nbinsSieieEB,0.,0.1);
    hEB1->Sumw2();
    sigmaIetaIetaEB1.push_back(hEB1);

    TH1D *hEB2 = new TH1D(Form("sieieEB2_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"sigmaIetaIetaEB2",nbinsSieieEB,0.,0.1);
    hEB2->Sumw2();
    sigmaIetaIetaEB2.push_back(hEB2);

    TH1D *hEE = new TH1D(Form("sieieEE_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"sigmaIetaIetaEE",nbinsSieieEE,0.,0.1);
    hEE->Sumw2();
    sigmaIetaIetaEE.push_back(hEE);

    TH1D *hEE1 = new TH1D(Form("sieieEE1_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"sigmaIetaIetaEE1",nbinsSieieEE,0.,0.1);
    hEE1->Sumw2();
    sigmaIetaIetaEE1.push_back(hEE1);

    TH1D *hEE2 = new TH1D(Form("sieieEE2_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"sigmaIetaIetaEE2",nbinsSieieEE,0.,0.1);
    hEE2->Sumw2();
    sigmaIetaIetaEE2.push_back(hEE2);

    TH1D *hEB_chIso = new TH1D(Form("chIsoEB_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"chIsoEB",nbinsChIso,0.,50.);
    hEB_chIso->Sumw2();
    chIsoEB.push_back(hEB_chIso);

    TH1D *hEE_chIso = new TH1D(Form("chIsoEE_realtemplate_pt%dTo%d",binLowEdge,binUpperEdge),"chIsoEE",nbinsChIso,0.,50.);
    hEE_chIso->Sumw2();
    chIsoEE.push_back(hEE_chIso);
  }

  TH1D* jetPhoDrEB_realtemplate = new TH1D("jetPhoDrEB_realtemplate","jetPhoDrEB_realtemplate",200,0.,1.);
  TH1D* jetPhoDrEE_realtemplate = new TH1D("jetPhoDrEE_realtemplate","jetPhoDrEE_realtemplate",200,0.,1.);

  TH1D* npv = new TH1D("npv", "", 200, 0, 200);

  // loop over entries
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    if (jentry % 100000 == 0)
      std::cout << "Number of entries looped over: " << jentry << std::endl;

    // fake rate object definitions
    bool is_sieie_numerator_object = Photon_isNumeratorObjCand && Photon_passChIso;
    bool is_chIso_numerator_object = Photon_isNumeratorObjCand && Photon_passSieie;

    // reject beam halo
    //if (Event_beamHaloIDTight2015) continue;
    if (Photon_sigmaIphiIphi5x5 < 0.009) continue;
    // uncomment me?
    if (Photon_r9_5x5 < 0.8) continue; // r9 cut for resonant sync

    // calculate nPV
    int numVtxAfterCut = 0;
    for(unsigned int i=0; i < VertexCollInfo_vx->size(); i++){
      int ndof = VertexCollInfo_ndof->at(i);
      double absZ = fabs(VertexCollInfo_vz->at(i));
      double d0 = VertexCollInfo_d0->at(i);

      if ( (ndof>=4) && (absZ<=24.) && (d0 <= 2.) ) {
        numVtxAfterCut++;
      }
    }
    npv->Fill(numVtxAfterCut);
    if(numVtxAfterCut< pvCutLow || numVtxAfterCut > pvCutHigh) continue;

    // evaluate jet trigger groupings
    // bool singleJetFired = TriggerBit_HLT_AK8DiPFJet280_200_TrimMass30_BTagCSV0p45_v3==1 || TriggerBit_HLT_AK8PFJet360_TrimMass30_v3==1 || TriggerBit_HLT_CaloJet500_NoJetID_v2==1 || TriggerBit_HLT_DiCaloJetAve140_v1==1 || TriggerBit_HLT_DiCaloJetAve200_v1==1 || TriggerBit_HLT_DiCaloJetAve260_v1==1 || TriggerBit_HLT_DiCaloJetAve320_v1==1 || TriggerBit_HLT_DiCaloJetAve400_v1==1 || TriggerBit_HLT_DiCaloJetAve40_v1==1 || TriggerBit_HLT_DiCaloJetAve500_v1==1 || TriggerBit_HLT_DiCaloJetAve60_v1==1 || TriggerBit_HLT_DiCaloJetAve80_v1==1 || TriggerBit_HLT_DiPFJetAve100_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve140_v2==1 || TriggerBit_HLT_DiPFJetAve160_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve200_v2==1 || TriggerBit_HLT_DiPFJetAve220_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve260_v2==1 || TriggerBit_HLT_DiPFJetAve300_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve30_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve320_v2==1 || TriggerBit_HLT_DiPFJetAve400_v2==1 || TriggerBit_HLT_DiPFJetAve40_v2==1 || TriggerBit_HLT_DiPFJetAve500_v2==1 || TriggerBit_HLT_DiPFJetAve60_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve60_v2==1 || TriggerBit_HLT_DiPFJetAve80_HFJEC_v3==1 || TriggerBit_HLT_DiPFJetAve80_v2==1 || TriggerBit_HLT_PFJet140_v4==1 || TriggerBit_HLT_PFJet200_v4==1 || TriggerBit_HLT_PFJet260_v4==1 || TriggerBit_HLT_PFJet320_v4==1 || TriggerBit_HLT_PFJet400_v4==1 || TriggerBit_HLT_PFJet40_v4==1 || TriggerBit_HLT_PFJet450_v4==1 || TriggerBit_HLT_PFJet500_v4==1 || TriggerBit_HLT_PFJet60_v4==1 || TriggerBit_HLT_PFJet80_v4==1;

    // bool htFired = TriggerBit_HLT_AK8PFHT600_TrimR0p1PT0p03Mass50_BTagCSV0p45_v2==1 || TriggerBit_HLT_AK8PFHT650_TrimR0p1PT0p03Mass50_v2==1 || TriggerBit_HLT_AK8PFHT700_TrimR0p1PT0p03Mass50_v3==1 || TriggerBit_HLT_HT2000_v1==1 || TriggerBit_HLT_HT200_v1==1 || TriggerBit_HLT_HT2500_v1==1 || TriggerBit_HLT_HT275_v1==1 || TriggerBit_HLT_HT325_v1==1 || TriggerBit_HLT_HT425_v1==1 || TriggerBit_HLT_HT575_v1==1 || TriggerBit_HLT_L1_TripleJet_VBF_v4==1 || TriggerBit_HLT_PFHT200_v2==1 || TriggerBit_HLT_PFHT250_v2==1 || TriggerBit_HLT_PFHT300_v2==1 || TriggerBit_HLT_PFHT350_v3==1 || TriggerBit_HLT_PFHT400_SixJet30_BTagCSV0p55_2PFBTagCSV0p72_v3==1 || TriggerBit_HLT_PFHT400_SixJet30_v3==1 || TriggerBit_HLT_PFHT400_v2==1 || TriggerBit_HLT_PFHT450_SixJet40_PFBTagCSV0p72_v3==1 || TriggerBit_HLT_PFHT450_SixJet40_v3==1 || TriggerBit_HLT_PFHT475_v2==1 || TriggerBit_HLT_PFHT550_4JetPt50_v1==1 || TriggerBit_HLT_PFHT600_v3==1 || TriggerBit_HLT_PFHT650_4JetPt50_v1==1 || TriggerBit_HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v3==1 || TriggerBit_HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v3==1 || TriggerBit_HLT_PFHT650_v3==1 || TriggerBit_HLT_PFHT750_4JetPt50_v3==1 || TriggerBit_HLT_PFHT800_v2==1 || TriggerBit_HLT_QuadPFJet_VBF_v4==1;

    // bool PFJet80Fired = TriggerBit_HLT_PFJet80_v4 == 1;
    // bool PFJet400Fired = TriggerBit_HLT_PFJet400_v4 == 1;

    // if (!PFJet400Fired) continue;

    /*
    TLorentzVector photon;
    TLorentzVector leadingJet;
    TLorentzVector secondleadingJet;
    TLorentzVector thirdleadingJet;

    double photonLeadingJetDr = -1.;
    bool matched = false;

    if (Jet_nJets >= 2){

      photon.SetPtEtaPhiM(Photon_pt,Photon_scEta,Photon_scPhi,0.);
      leadingJet.SetPtEtaPhiM(Jet_leadingJetPt,Jet_leadingJetEta,Jet_leadingJetPhi,Jet_leadingJetMass);
      secondleadingJet.SetPtEtaPhiM(Jet_secondleadingJetPt,Jet_secondleadingJetEta,Jet_secondleadingJetPhi,Jet_secondleadingJetMass);
      // thirdleadingJet.SetPtEtaPhiM(Jet_thirdleadingJetPt,Jet_thirdleadingJetEta,Jet_thirdleadingJetPhi,Jet_thirdleadingJetMass);

      photonLeadingJetDr = photon.DeltaR(leadingJet);
      double photonSecondLeadingJetDr = photon.DeltaR(secondleadingJet);
      // double photonThirdLeadingJetDr = photon.DeltaR(thirdleadingJet);

      double dRCut = 0.6;
      // these will all work because the jet 4 vectors are filled with dummy information, but I'll only use them if they are real jets
      bool matchedToLeadingJet = (photonLeadingJetDr < dRCut);
      bool matchedToSecondLeadingJet = (photonSecondLeadingJetDr < dRCut);
      // bool matchedToThirdLeadingJet = (photonThirdLeadingJetDr < dRCut);

      matched = matchedToSecondLeadingJet;

    }

    if (matched) continue;
    */

    // loop over pT bin increments
    for (int i = 0; i < nBins; i++) {
      double binLowEdge = binLowEdges[i];
      double binUpperEdge = binUpperEdges[i];
      // use pT bins to cut on photon pT
      if (binLowEdge < Photon_pt && Photon_pt < binUpperEdge) {
	// EB
	if (fabs(Photon_scEta) < 1.4442) {
	  if (is_sieie_numerator_object) sigmaIetaIetaEB.at(i)->Fill(Photon_sigmaIetaIeta5x5,Event_weightAll);
	  if (is_chIso_numerator_object) chIsoEB.at(i)->Fill(Photon_chargedHadIso03,Event_weightAll);
	}
	// EB1
	if (fabs(Photon_scEta) < 0.7221) {
	  if (is_sieie_numerator_object) sigmaIetaIetaEB1.at(i)->Fill(Photon_sigmaIetaIeta5x5,Event_weightAll);
	}
	// EB2
	if (0.7221 < fabs(Photon_scEta) && fabs(Photon_scEta) < 1.4442) {
	  if (is_sieie_numerator_object) sigmaIetaIetaEB2.at(i)->Fill(Photon_sigmaIetaIeta5x5,Event_weightAll);
	}
	// EE
	if (1.566 < fabs(Photon_scEta) && fabs(Photon_scEta) < 2.5) {
	  if (is_sieie_numerator_object) sigmaIetaIetaEE.at(i)->Fill(Photon_sigmaIetaIeta5x5,Event_weightAll);
	  if (is_chIso_numerator_object) chIsoEE.at(i)->Fill(Photon_chargedHadIso03,Event_weightAll);
	}
	// EE1
	if (1.566 < fabs(Photon_scEta) && fabs(Photon_scEta) < 2.033) {
	  if (is_sieie_numerator_object) sigmaIetaIetaEE1.at(i)->Fill(Photon_sigmaIetaIeta5x5,Event_weightAll);
	}
	// EE2
	if (2.033 < fabs(Photon_scEta) && fabs(Photon_scEta) < 2.5) {
	  if (is_sieie_numerator_object) sigmaIetaIetaEE2.at(i)->Fill(Photon_sigmaIetaIeta5x5,Event_weightAll);
	}
      } // end pt cut
    } // end loop over pt bin increments

  } // end loop over entries

  TFile file_out(filename,"RECREATE");

  // normalize histograms and write to file
  std::vector<std::vector<TH1D*>> hists_to_normalize = {chIsoEB, sigmaIetaIetaEB, sigmaIetaIetaEB1, sigmaIetaIetaEB2, // EB
							chIsoEE, sigmaIetaIetaEE, sigmaIetaIetaEE1, sigmaIetaIetaEE2}; // EE

  for(auto& hists : hists_to_normalize) {
    for (auto& it : hists) {
      std::cout << it->GetName() << "\t integral: " << it->Integral() << std::endl;
      it->Scale(1.0/it->Integral());
      it->Write();
    }
  }

  jetPhoDrEB_realtemplate->Write();
  jetPhoDrEE_realtemplate->Write();

  npv->Write();

  file_out.ls();
  file_out.Close();

} // end of Loop()
