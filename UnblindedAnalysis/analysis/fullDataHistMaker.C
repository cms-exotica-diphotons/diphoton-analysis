#define fullDataHistMaker_cxx
#include "fullDataHistMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <sstream>
#include <memory>
#include "../../Tools/interface/utilities.hh"

// TString getLastTwoCharacters(const std::string& str) {
//     // Make sure the string has at least two characters
//     if (str.length() >= 2) {
//         // Use substr() to get the last two characters
//         return TString( str.substr(str.length() - 2).Data() );
//     } else {
//         // If the string has less than two characters, return the whole string
//         return TString(str).Data();
//     }
// }

int getLastTwoDigitsRun(int number) {
    // Take the modulo of the number by 100 to get the last two digits
    return number % 100;
}

void fullDataHistMakerBase::Loop() {};

class fullDataHistMaker : public fullDataHistMakerBase {

public:
  using fullDataHistMakerBase::fullDataHistMakerBase;
  void Loop() {};
  void Loop(int run);

};

void fullDataHistMaker::Loop(int run)
{
//   In a ROOT session, you can do:
//      root> .L fullDataHistMaker.C
//      root> fullDataHistMaker t
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

  std::cout << "\n Run Configuration: " << run << std::endl;
  std::ostringstream oss;

  oss << "data" << run << ".root";
  TString fileout_name = oss.str().c_str();

  std::map<std::string, double> lumiNum = {
      {"2018",   59.7},
      {"2017",   41.5},
      {"2016",   36.3},
      {"161718", 137.6}
  };
  double luminosity = lumiNum[std::to_string(run)];
  std::cout << "Luminosity: " << luminosity << std::endl;
  double mggCut = 500.;
  std::cout << "Diphoton Minv cut: " << mggCut << std::endl;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   int yr = getLastTwoDigitsRun(run);



   //TH1D* data_obsBB = new TH1D(Form("BB%d__DATA",(int)yr), "", 120, 0., 6000.);// 100, 0, 10000
   TH1D* data_obsBB = new TH1D(Form("BB%d__DATA",(int)yr), "", 160, 500., 8500.);// 100, 0, 10000
   data_obsBB->Sumw2();

   //TH1D* data_obsBE = new TH1D(Form("BE%d__DATA",(int)yr), "", 120, 0., 6000.);// 100, 0, 10000
   TH1D* data_obsBE = new TH1D(Form("BE%d__DATA",(int)yr), "", 160, 500., 8500.);// 100, 0, 10000 To match with Hsin-Yeh's 8000 max and 160 Nbins
   data_obsBE->Sumw2();


   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry%10000 == 0) std::cout << "Number of processed events: " << jentry << std::endl;

      // cuts["BB"] = "isGood*(Diphoton.deltaR > 0.45 && Photon1.pt>125 && Photon2.pt>125 && Photon1.isEB && Photon2.isEB)";
      // cuts["BE"] = "isGood*(Diphoton.deltaR > 0.45 && Photon1.pt>125 && Photon2.pt>125 && ( (Photon1.isEB && Photon2.isEE) || (Photon2.isEB &&  Photon1.isEE )))";
      //
      bool passHLTcut;
      if( run == 2016 ) {
        passHLTcut = ( TriggerBit_HLT_DoublePhoton60 > 0 || TriggerBit_HLT_ECALHT800>0);
      }
      else {
        passHLTcut = (TriggerBit_HLT_DoublePhoton70 >0 || TriggerBit_HLT_ECALHT800>0);
      }

      // Do not apply to data..?
      // TString sfCut = scale_factor_cut(run, 0);
      // TString nPV_reweight = npv_reweight_str(run, 0); // numSigma = 0 for nominal

      // if (Diphoton_Minv > 600){

      if (isGood && Diphoton_deltaR > 0.45 && Photon1_pt>125 && Photon2_pt>125 && Diphoton_Minv > mggCut ){
        if (passHLTcut){

          if (Diphoton_isEBEB){
            // data_obsBB->Fill(Diphoton_Minv, Event_weightAll*luminosity);
            data_obsBB->Fill(Diphoton_Minv, 1);
          }
          if (Diphoton_isEBEE or Diphoton_isEEEB){
            // data_obsBE->Fill(Diphoton_Minv, Event_weightAll*luminosity);
            data_obsBE->Fill(Diphoton_Minv, 1);
          }
        } // HLT cut
      }

      // } // Minv Cut


      // if (Diphoton_isEBEB){
      //   data_obsBB->Fill(Diphoton_Minv, Event_weightAll*luminosity*(HLT_DoublePhoton60>0 || HLT_ECALHT800>0)*);
      // }
      // if (Diphoton_isEBEE or Diphoton_isEEEB){
      //   data_obsBE->Fill(Diphoton_Minv, Event_weightAll;
      // }
   }

   TFile file_out(fileout_name, "RECREATE");

   data_obsBB->Write();
   data_obsBE->Write();
}
