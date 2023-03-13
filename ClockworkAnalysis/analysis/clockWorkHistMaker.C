#define clockWorkHistMaker_cxx
#include "clockWorkHistMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <sstream>


#include <memory>

void clockWorkHistMakerBase::Loop() {};

class clockWorkHistMaker : public clockWorkHistMakerBase {

public:
  using clockWorkHistMakerBase::clockWorkHistMakerBase;
  void Loop() {};
  void Loop(std::string run, double kVal, double lambdaT, int negInt);

};


void clockWorkHistMaker::Loop(std::string run, double kVal, double lambdaT, int negInt)
{
   std::cout << "\nRun Configuration: " << run << "; kVal: " << kVal << "; lambdaT: " << lambdaT << "; negInt: "  << negInt << std::endl;
   std::ostringstream oss;

   oss << "Test" << run << "_negInt-" << negInt << "_k-" << kVal << "_lT-" << lambdaT << ".root";

   TString fileout_name = oss.str().c_str();
   std::cout << fileout_name << std::endl;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   // TH1D* gendiphotonMinv = new TH1D("gendiphotonMinv", "", 100, 500., 4000.);// 100, 0, 10000
   // gendiphotonMinv->Sumw2();

   TH1D* diphotonMinv = new TH1D("diphotonMinv", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinv->Sumw2();

   Long64_t nbytes = 0, nb = 0;

   std::cout << "Running event loop... " << std::endl;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry%10000 == 0) std::cout << "Number of processed events: " << jentry << std::endl;
      if (GenDiphoton_Minv > kVal){
         double M5 = 10000;
         //double scale = Event_weightAll*30*std::pow(lambdaT, 8)/(283*3.14159*pow(M5,3))*sqrt(1-(std::pow(kVal,2)/std::pow(GenDiphoton_Minv,2)))*(1/std::pow(GenDiphoton_Minv,5));
         double scale = Event_weightAll*30/(283*3.14159*pow(M5,3))*sqrt(1-(std::pow(kVal,2)/std::pow(GenDiphoton_Minv,2)))*(1/std::pow(GenDiphoton_Minv,5));
         diphotonMinv->Fill(Diphoton_Minv, scale);
      }

   }

   TFile file_out(fileout_name, "RECREATE");
   diphotonMinv->Write();
}
