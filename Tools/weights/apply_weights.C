#define apply_weights_cxx
#include "apply_weights.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "TLorentzVector.h"

bool apply_weights::isEBEBGen()
{
  const double eta_max_EB = 1.4442;

  return abs(GenPhoton1_eta) < eta_max_EB and abs(GenPhoton2_eta) < eta_max_EB;
}

void apply_weights::Loop()
{
  TFile *weights = new TFile("tune_ratio.root");

  TH1F* ratio_BB = (TH1F*)weights->Get("ratio_BB");
  TH1F* ratio_BE = (TH1F*)weights->Get("ratio_BE");

//   In a ROOT session, you can do:
//      root> .L apply_weights.C
//      root> apply_weights t
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
  fChain->SetBranchStatus("*",1);  // disable all branches
  //  fChain->SetBranchStatus("Event",1);  // activate branchname
  //  fChain->SetBranchStatus("Photon1",1);  // activate branchname
  //  fChain->SetBranchStatus("Photon2",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   TFile *g = new TFile("output.root", "recreate");
   g->mkdir("diphoton");
   g->cd("diphoton");
   TTree *outTree = fChain->CloneTree(0);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry % 1000 == 0) {
	std::cout << jentry << std::endl;
      }
      TLorentzVector p1, p2;
      p1.SetPtEtaPhiM(GenPhoton1_pt, GenPhoton1_eta, GenPhoton1_phi, 0.);
      p2.SetPtEtaPhiM(GenPhoton2_pt, GenPhoton2_eta, GenPhoton2_phi, 0.);
      double q2 = (p1 + p2).M();
      double sampleWeight = Diphoton_isEBEB ? ratio_BB->GetBinContent(ratio_BB->FindBin(q2)) : ratio_BE->GetBinContent(ratio_BE->FindBin(q2));
      Event_weightAll *= sampleWeight;
      outTree->Fill();

   }
   outTree->AutoSave();
}
