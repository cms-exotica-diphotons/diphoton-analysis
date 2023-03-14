#define clockWorkHistMaker_cxx
#include "clockWorkHistMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <sstream>


#include <memory>

double scale(double kVal, double EvtWeightAll, double GenDiphotonMinv, double M5 = 10000){
    double sc = EvtWeightAll*30/(283*3.14159*pow(M5,3))*sqrt(1-(std::pow(kVal,2)/std::pow(GenDiphotonMinv,2)))*(1/std::pow(GenDiphotonMinv,5));
    return sc;
}

void clockWorkHistMakerBase::Loop() {};

class clockWorkHistMaker : public clockWorkHistMakerBase {

public:
  using clockWorkHistMakerBase::clockWorkHistMakerBase;
  void Loop() {};
  void Loop(std::string run, double lambdaT, int negInt);

};


void clockWorkHistMaker::Loop(std::string run, double lambdaT, int negInt)
{
   std::cout << "\nRun Configuration: " << run << "; lambdaT: " << lambdaT << "; negInt: "  << negInt << std::endl;
   std::ostringstream oss;


   if (lambdaT > 15000) oss << "Test" << run << "_SMGGLOPythia" << ".root";
   else oss << "Test" << run << "_negInt-" << negInt << "_lT-" << lambdaT << ".root";

   TString fileout_name = oss.str().c_str();


   std::cout << fileout_name << std::endl;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   // k = 500
   TH1D* diphotonMinvEBEB_k500 = new TH1D("diphotonMinvEBEB_k500", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEB_k500->Sumw2();

   TH1D* diphotonMinvEBEE_k500 = new TH1D("diphotonMinvEBEE_k500", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEE_k500->Sumw2();

   // k = 1000
   TH1D* diphotonMinvEBEB_k1000 = new TH1D("diphotonMinvEBEB_k1000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000->Sumw2();

   TH1D* diphotonMinvEBEE_k1000 = new TH1D("diphotonMinvEBEE_k1000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000->Sumw2();

   // k = 2000
   TH1D* diphotonMinvEBEB_k2000 = new TH1D("diphotonMinvEBEB_k2000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000->Sumw2();

   TH1D* diphotonMinvEBEE_k2000 = new TH1D("diphotonMinvEBEE_k2000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000->Sumw2();

   // k = 3000
   TH1D* diphotonMinvEBEB_k3000 = new TH1D("diphotonMinvEBEB_k3000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000->Sumw2();

   TH1D* diphotonMinvEBEE_k3000 = new TH1D("diphotonMinvEBEE_k3000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000->Sumw2();

   // k = 5000
   TH1D* diphotonMinvEBEB_k5000 = new TH1D("diphotonMinvEBEB_k5000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000->Sumw2();

   TH1D* diphotonMinvEBEE_k5000 = new TH1D("diphotonMinvEBEE_k5000", "", 100, 500., 4000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000->Sumw2();

   Long64_t nbytes = 0, nb = 0;

   std::cout << "Running event loop... " << std::endl;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry%10000 == 0) std::cout << "Number of processed events: " << jentry << std::endl;
      double M5 = 10000;
      //double scale = Event_weightAll*30*std::pow(lambdaT, 8)/(283*3.14159*pow(M5,3))*sqrt(1-(std::pow(kVal,2)/std::pow(GenDiphoton_Minv,2)))*(1/std::pow(GenDiphoton_Minv,5));
      // double scale = Event_weightAll*30/(283*3.14159*pow(M5,3))*sqrt(1-(std::pow(kVal,2)/std::pow(GenDiphoton_Minv,2)))*(1/std::pow(GenDiphoton_Minv,5));

      // if Diphoton_isEBEB
      if (Diphoton_isEBEB){
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5));
      }

      // if Diphoton_isEBEE or Diphoton_isEEEB
      if (Diphoton_isEBEE or Diphoton_isEEEB){
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5));
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5));
      }
   }

   TFile file_out(fileout_name, "RECREATE");
   diphotonMinvEBEB_k500->Write();
   diphotonMinvEBEB_k1000->Write();
   diphotonMinvEBEB_k2000->Write();
   diphotonMinvEBEB_k3000->Write();
   diphotonMinvEBEB_k5000->Write();

   diphotonMinvEBEE_k500->Write();
   diphotonMinvEBEE_k1000->Write();
   diphotonMinvEBEE_k2000->Write();
   diphotonMinvEBEE_k3000->Write();
   diphotonMinvEBEE_k5000->Write();
}
