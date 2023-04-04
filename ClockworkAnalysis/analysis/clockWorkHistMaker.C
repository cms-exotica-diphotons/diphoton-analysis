#define clockWorkHistMaker_cxx
#include "clockWorkHistMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <sstream>


#include <memory>

double scale(double kVal, double EvtWeightAll, double GenDiphotonMinv, double M5 = 10000){
    double sc1 = EvtWeightAll*30./(283.*3.14159*pow(M5,3.))*sqrt(1.-(std::pow(kVal,2.)/std::pow(GenDiphotonMinv,2.)))*(1./std::pow(GenDiphotonMinv,5.));
    double sc2 = 1 + 0.04106393551236749*std::pow(1-(kVal/GenDiphotonMinv),9.)*sqrt(GenDiphotonMinv/kVal);
    double sc = sc1/sc2;
    return sc;
}

void clockWorkHistMakerBase::Loop() {};

class clockWorkHistMaker : public clockWorkHistMakerBase {

public:
  using clockWorkHistMakerBase::clockWorkHistMakerBase;
  void Loop() {};
  void Loop(int run, double lambdaT, int negInt);

};


void clockWorkHistMaker::Loop(int run, double lambdaT, int negInt)
{
   std::cout << "\nRun Configuration: " << run << "; lambdaT: " << lambdaT << "; negInt: "  << negInt << std::endl;
   std::ostringstream oss;


   if (lambdaT > 15000) oss << "Test" << run << "_SMGGLOPythia" << ".root";
   else oss << "Test" << run << "_negInt-" << negInt << "_lT-" << lambdaT << ".root";

   TString fileout_name = oss.str().c_str();

   // vector<TString> kvalue = {"0p1", "1", "10", "100", "500", "1000", "2000", "3000", "4000", "5000"};
   //
   std::cout << fileout_name << std::endl;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   // int nBins = 100.; //120; // 100
   // double xMin = 500.; //0.0; // 500
   // double xMax = 4000.;//6000.; // 4000
   // k = 0p1

   TH1D* diphotonMinvEBEB_k0p1 = new TH1D("diphotonMinvEBEB_k0p1", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1->Sumw2();

   TH1D* diphotonMinvEBEE_k0p1 = new TH1D("diphotonMinvEBEE_k0p1", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1->Sumw2();

   // Syst k = 0p1
   TH1D* diphotonMinvEBEB_k0p1_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k0p1_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k0p1_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k0p1_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k0p1_energySigmaDown = new TH1D("diphotonMinvEBEB_k0p1_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k0p1_energySigmaUp = new TH1D("diphotonMinvEBEB_k0p1_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k0p1_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k0p1_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k0p1_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k0p1_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k0p1_pileupUp = new TH1D("diphotonMinvEBEB_k0p1_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k0p1_pileupDown = new TH1D("diphotonMinvEBEB_k0p1_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k0p1_pileupNom = new TH1D("diphotonMinvEBEB_k0p1_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k0p1_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k0p1_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k0p1_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k0p1_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k0p1_energySigmaDown = new TH1D("diphotonMinvEBEE_k0p1_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k0p1_energySigmaUp = new TH1D("diphotonMinvEBEE_k0p1_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k0p1_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k0p1_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k0p1_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k0p1_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k0p1_pileupUp = new TH1D("diphotonMinvEBEE_k0p1_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k0p1_pileupDown = new TH1D("diphotonMinvEBEE_k0p1_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k0p1_pileupNom = new TH1D("diphotonMinvEBEE_k0p1_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k0p1_effUp = new TH1D("diphotonMinvEBEB_k0p1_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k0p1_effDown = new TH1D("diphotonMinvEBEB_k0p1_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k0p1_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k0p1_effUp = new TH1D("diphotonMinvEBEE_k0p1_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k0p1_effDown = new TH1D("diphotonMinvEBEE_k0p1_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k0p1_effDown->Sumw2();

   // k = 1

   TH1D* diphotonMinvEBEB_k1 = new TH1D("diphotonMinvEBEB_k1", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1->Sumw2();

   TH1D* diphotonMinvEBEE_k1 = new TH1D("diphotonMinvEBEE_k1", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1->Sumw2();

   // syst k = 1
   TH1D* diphotonMinvEBEB_k1_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k1_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k1_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k1_energySigmaDown = new TH1D("diphotonMinvEBEB_k1_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k1_energySigmaUp = new TH1D("diphotonMinvEBEB_k1_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k1_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k1_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k1_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k1_pileupUp = new TH1D("diphotonMinvEBEB_k1_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1_pileupDown = new TH1D("diphotonMinvEBEB_k1_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k1_pileupNom = new TH1D("diphotonMinvEBEB_k1_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k1_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k1_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k1_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k1_energySigmaDown = new TH1D("diphotonMinvEBEE_k1_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k1_energySigmaUp = new TH1D("diphotonMinvEBEE_k1_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k1_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k1_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k1_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k1_pileupUp = new TH1D("diphotonMinvEBEE_k1_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1_pileupDown = new TH1D("diphotonMinvEBEE_k1_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k1_pileupNom = new TH1D("diphotonMinvEBEE_k1_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k1_effUp = new TH1D("diphotonMinvEBEB_k1_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1_effDown = new TH1D("diphotonMinvEBEB_k1_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k1_effUp = new TH1D("diphotonMinvEBEE_k1_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1_effDown = new TH1D("diphotonMinvEBEE_k1_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1_effDown->Sumw2();

   // k = 10
   TH1D* diphotonMinvEBEB_k10 = new TH1D("diphotonMinvEBEB_k10", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10->Sumw2();

   TH1D* diphotonMinvEBEE_k10 = new TH1D("diphotonMinvEBEE_k10", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10->Sumw2();

   TH1D* diphotonMinvEBEB_k10_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k10_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k10_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k10_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k10_energySigmaDown = new TH1D("diphotonMinvEBEB_k10_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k10_energySigmaUp = new TH1D("diphotonMinvEBEB_k10_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k10_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k10_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k10_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k10_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k10_pileupUp = new TH1D("diphotonMinvEBEB_k10_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k10_pileupDown = new TH1D("diphotonMinvEBEB_k10_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k10_pileupNom = new TH1D("diphotonMinvEBEB_k10_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k10_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k10_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k10_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k10_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k10_energySigmaDown = new TH1D("diphotonMinvEBEE_k10_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k10_energySigmaUp = new TH1D("diphotonMinvEBEE_k10_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k10_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k10_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k10_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k10_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k10_pileupUp = new TH1D("diphotonMinvEBEE_k10_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k10_pileupDown = new TH1D("diphotonMinvEBEE_k10_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k10_pileupNom = new TH1D("diphotonMinvEBEE_k10_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k10_effUp = new TH1D("diphotonMinvEBEB_k10_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k10_effDown = new TH1D("diphotonMinvEBEB_k10_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k10_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k10_effUp = new TH1D("diphotonMinvEBEE_k10_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k10_effDown = new TH1D("diphotonMinvEBEE_k10_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k10_effDown->Sumw2();

   // k = 100
   TH1D* diphotonMinvEBEB_k100 = new TH1D("diphotonMinvEBEB_k100", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100->Sumw2();

   TH1D* diphotonMinvEBEE_k100 = new TH1D("diphotonMinvEBEE_k100", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100->Sumw2();

   TH1D* diphotonMinvEBEB_k100_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k100_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k100_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k100_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k100_energySigmaDown = new TH1D("diphotonMinvEBEB_k100_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k100_energySigmaUp = new TH1D("diphotonMinvEBEB_k100_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k100_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k100_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k100_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k100_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k100_pileupUp = new TH1D("diphotonMinvEBEB_k100_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k100_pileupDown = new TH1D("diphotonMinvEBEB_k100_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k100_pileupNom = new TH1D("diphotonMinvEBEB_k100_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k100_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k100_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k100_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k100_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k100_energySigmaDown = new TH1D("diphotonMinvEBEE_k100_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k100_energySigmaUp = new TH1D("diphotonMinvEBEE_k100_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k100_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k100_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k100_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k100_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k100_pileupUp = new TH1D("diphotonMinvEBEE_k100_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k100_pileupDown = new TH1D("diphotonMinvEBEE_k100_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k100_pileupNom = new TH1D("diphotonMinvEBEE_k100_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k100_effUp = new TH1D("diphotonMinvEBEB_k100_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k100_effDown = new TH1D("diphotonMinvEBEB_k100_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k100_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k100_effUp = new TH1D("diphotonMinvEBEE_k100_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k100_effDown = new TH1D("diphotonMinvEBEE_k100_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k100_effDown->Sumw2();

   // k = 500
   TH1D* diphotonMinvEBEB_k500 = new TH1D("diphotonMinvEBEB_k500", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500->Sumw2();

   TH1D* diphotonMinvEBEE_k500 = new TH1D("diphotonMinvEBEE_k500", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500->Sumw2();

   TH1D* diphotonMinvEBEB_k500_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k500_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k500_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k500_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k500_energySigmaDown = new TH1D("diphotonMinvEBEB_k500_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k500_energySigmaUp = new TH1D("diphotonMinvEBEB_k500_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k500_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k500_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k500_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k500_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k500_pileupUp = new TH1D("diphotonMinvEBEB_k500_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k500_pileupDown = new TH1D("diphotonMinvEBEB_k500_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k500_pileupNom = new TH1D("diphotonMinvEBEB_k500_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k500_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k500_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k500_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k500_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k500_energySigmaDown = new TH1D("diphotonMinvEBEE_k500_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k500_energySigmaUp = new TH1D("diphotonMinvEBEE_k500_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k500_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k500_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k500_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k500_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k500_pileupUp = new TH1D("diphotonMinvEBEE_k500_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k500_pileupDown = new TH1D("diphotonMinvEBEE_k500_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k500_pileupNom = new TH1D("diphotonMinvEBEE_k500_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k500_effUp = new TH1D("diphotonMinvEBEB_k500_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k500_effDown = new TH1D("diphotonMinvEBEB_k500_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k500_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k500_effUp = new TH1D("diphotonMinvEBEE_k500_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k500_effDown = new TH1D("diphotonMinvEBEE_k500_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k500_effDown->Sumw2();

   // k = 1000
   TH1D* diphotonMinvEBEB_k1000 = new TH1D("diphotonMinvEBEB_k1000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000->Sumw2();

   TH1D* diphotonMinvEBEE_k1000 = new TH1D("diphotonMinvEBEE_k1000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000->Sumw2();

   TH1D* diphotonMinvEBEB_k1000_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k1000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1000_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k1000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k1000_energySigmaDown = new TH1D("diphotonMinvEBEB_k1000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k1000_energySigmaUp = new TH1D("diphotonMinvEBEB_k1000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k1000_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k1000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1000_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k1000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k1000_pileupUp = new TH1D("diphotonMinvEBEB_k1000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1000_pileupDown = new TH1D("diphotonMinvEBEB_k1000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k1000_pileupNom = new TH1D("diphotonMinvEBEB_k1000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k1000_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k1000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1000_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k1000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k1000_energySigmaDown = new TH1D("diphotonMinvEBEE_k1000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k1000_energySigmaUp = new TH1D("diphotonMinvEBEE_k1000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k1000_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k1000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1000_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k1000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k1000_pileupUp = new TH1D("diphotonMinvEBEE_k1000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1000_pileupDown = new TH1D("diphotonMinvEBEE_k1000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k1000_pileupNom = new TH1D("diphotonMinvEBEE_k1000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k1000_effUp = new TH1D("diphotonMinvEBEB_k1000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k1000_effDown = new TH1D("diphotonMinvEBEB_k1000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k1000_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k1000_effUp = new TH1D("diphotonMinvEBEE_k1000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k1000_effDown = new TH1D("diphotonMinvEBEE_k1000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k1000_effDown->Sumw2();

   // k = 2000
   TH1D* diphotonMinvEBEB_k2000 = new TH1D("diphotonMinvEBEB_k2000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000->Sumw2();

   TH1D* diphotonMinvEBEE_k2000 = new TH1D("diphotonMinvEBEE_k2000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000->Sumw2();

   TH1D* diphotonMinvEBEB_k2000_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k2000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k2000_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k2000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k2000_energySigmaDown = new TH1D("diphotonMinvEBEB_k2000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k2000_energySigmaUp = new TH1D("diphotonMinvEBEB_k2000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k2000_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k2000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k2000_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k2000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k2000_pileupUp = new TH1D("diphotonMinvEBEB_k2000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k2000_pileupDown = new TH1D("diphotonMinvEBEB_k2000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k2000_pileupNom = new TH1D("diphotonMinvEBEB_k2000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k2000_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k2000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k2000_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k2000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k2000_energySigmaDown = new TH1D("diphotonMinvEBEE_k2000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k2000_energySigmaUp = new TH1D("diphotonMinvEBEE_k2000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k2000_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k2000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k2000_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k2000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k2000_pileupUp = new TH1D("diphotonMinvEBEE_k2000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k2000_pileupDown = new TH1D("diphotonMinvEBEE_k2000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k2000_pileupNom = new TH1D("diphotonMinvEBEE_k2000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k2000_effUp = new TH1D("diphotonMinvEBEB_k2000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k2000_effDown = new TH1D("diphotonMinvEBEB_k2000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k2000_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k2000_effUp = new TH1D("diphotonMinvEBEE_k2000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k2000_effDown = new TH1D("diphotonMinvEBEE_k2000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k2000_effDown->Sumw2();

   // k = 3000
   TH1D* diphotonMinvEBEB_k3000 = new TH1D("diphotonMinvEBEB_k3000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000->Sumw2();

   TH1D* diphotonMinvEBEE_k3000 = new TH1D("diphotonMinvEBEE_k3000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000->Sumw2();

   TH1D* diphotonMinvEBEB_k3000_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k3000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k3000_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k3000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k3000_energySigmaDown = new TH1D("diphotonMinvEBEB_k3000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k3000_energySigmaUp = new TH1D("diphotonMinvEBEB_k3000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k3000_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k3000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k3000_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k3000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k3000_pileupUp = new TH1D("diphotonMinvEBEB_k3000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k3000_pileupDown = new TH1D("diphotonMinvEBEB_k3000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k3000_pileupNom = new TH1D("diphotonMinvEBEB_k3000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k3000_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k3000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k3000_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k3000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k3000_energySigmaDown = new TH1D("diphotonMinvEBEE_k3000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k3000_energySigmaUp = new TH1D("diphotonMinvEBEE_k3000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k3000_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k3000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k3000_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k3000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k3000_pileupUp = new TH1D("diphotonMinvEBEE_k3000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k3000_pileupDown = new TH1D("diphotonMinvEBEE_k3000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k3000_pileupNom = new TH1D("diphotonMinvEBEE_k3000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k3000_effUp = new TH1D("diphotonMinvEBEB_k3000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k3000_effDown = new TH1D("diphotonMinvEBEB_k3000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k3000_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k3000_effUp = new TH1D("diphotonMinvEBEE_k3000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k3000_effDown = new TH1D("diphotonMinvEBEE_k3000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k3000_effDown->Sumw2();

   // k = 4000
   TH1D* diphotonMinvEBEB_k4000 = new TH1D("diphotonMinvEBEB_k4000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000->Sumw2();

   TH1D* diphotonMinvEBEE_k4000 = new TH1D("diphotonMinvEBEE_k4000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000->Sumw2();

   TH1D* diphotonMinvEBEB_k4000_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k4000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k4000_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k4000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k4000_energySigmaDown = new TH1D("diphotonMinvEBEB_k4000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k4000_energySigmaUp = new TH1D("diphotonMinvEBEB_k4000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k4000_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k4000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k4000_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k4000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k4000_pileupUp = new TH1D("diphotonMinvEBEB_k4000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k4000_pileupDown = new TH1D("diphotonMinvEBEB_k4000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k4000_pileupNom = new TH1D("diphotonMinvEBEB_k4000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k4000_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k4000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k4000_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k4000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k4000_energySigmaDown = new TH1D("diphotonMinvEBEE_k4000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k4000_energySigmaUp = new TH1D("diphotonMinvEBEE_k4000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k4000_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k4000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k4000_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k4000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k4000_pileupUp = new TH1D("diphotonMinvEBEE_k4000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k4000_pileupDown = new TH1D("diphotonMinvEBEE_k4000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k4000_pileupNom = new TH1D("diphotonMinvEBEE_k4000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k4000_effUp = new TH1D("diphotonMinvEBEB_k4000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k4000_effDown = new TH1D("diphotonMinvEBEB_k4000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k4000_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k4000_effUp = new TH1D("diphotonMinvEBEE_k4000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k4000_effDown = new TH1D("diphotonMinvEBEE_k4000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k4000_effDown->Sumw2();

   // k = 5000
   TH1D* diphotonMinvEBEB_k5000 = new TH1D("diphotonMinvEBEB_k5000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000->Sumw2();

   TH1D* diphotonMinvEBEE_k5000 = new TH1D("diphotonMinvEBEE_k5000", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000->Sumw2();

   TH1D* diphotonMinvEBEB_k5000_energyScaleSystUp = new TH1D("diphotonMinvEBEB_k5000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEB_k5000_energyScaleSystDown = new TH1D("diphotonMinvEBEB_k5000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEB_k5000_energySigmaDown = new TH1D("diphotonMinvEBEB_k5000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEB_k5000_energySigmaUp = new TH1D("diphotonMinvEBEB_k5000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEB_k5000_energyScaleGainUp = new TH1D("diphotonMinvEBEB_k5000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEB_k5000_energyScaleGainDown = new TH1D("diphotonMinvEBEB_k5000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEB_k5000_pileupUp = new TH1D("diphotonMinvEBEB_k5000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEB_k5000_pileupDown = new TH1D("diphotonMinvEBEB_k5000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEB_k5000_pileupNom = new TH1D("diphotonMinvEBEB_k5000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_pileupNom->Sumw2();

   //
   TH1D* diphotonMinvEBEE_k5000_energyScaleSystUp = new TH1D("diphotonMinvEBEE_k5000_energyScaleSystUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_energyScaleSystUp->Sumw2();
   TH1D* diphotonMinvEBEE_k5000_energyScaleSystDown = new TH1D("diphotonMinvEBEE_k5000_energyScaleSystDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_energyScaleSystDown->Sumw2();

   TH1D* diphotonMinvEBEE_k5000_energySigmaDown = new TH1D("diphotonMinvEBEE_k5000_energySigmaDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_energySigmaDown->Sumw2();
   TH1D* diphotonMinvEBEE_k5000_energySigmaUp = new TH1D("diphotonMinvEBEE_k5000_energySigmaUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_energySigmaUp->Sumw2();

   TH1D* diphotonMinvEBEE_k5000_energyScaleGainUp = new TH1D("diphotonMinvEBEE_k5000_energyScaleGainUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_energyScaleGainUp->Sumw2();
   TH1D* diphotonMinvEBEE_k5000_energyScaleGainDown = new TH1D("diphotonMinvEBEE_k5000_energyScaleGainDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_energyScaleGainDown->Sumw2();

   TH1D* diphotonMinvEBEE_k5000_pileupUp = new TH1D("diphotonMinvEBEE_k5000_pileupUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_pileupUp->Sumw2();
   TH1D* diphotonMinvEBEE_k5000_pileupDown = new TH1D("diphotonMinvEBEE_k5000_pileupDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_pileupDown->Sumw2();
   TH1D* diphotonMinvEBEE_k5000_pileupNom = new TH1D("diphotonMinvEBEE_k5000_pileupNom", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_pileupNom->Sumw2();

   TH1D* diphotonMinvEBEB_k5000_effUp = new TH1D("diphotonMinvEBEB_k5000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_effUp->Sumw2();
   TH1D* diphotonMinvEBEB_k5000_effDown = new TH1D("diphotonMinvEBEB_k5000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEB_k5000_effDown->Sumw2();

   TH1D* diphotonMinvEBEE_k5000_effUp = new TH1D("diphotonMinvEBEE_k5000_effUp", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_effUp->Sumw2();
   TH1D* diphotonMinvEBEE_k5000_effDown = new TH1D("diphotonMinvEBEE_k5000_effDown", "", 120, 0., 6000.);// 100, 0, 10000
   diphotonMinvEBEE_k5000_effDown->Sumw2();

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

      // vector<TString> kvalue = {"0p1", "1", "10", "100", "500", "1000", "2000", "3000", "4000", "5000"};
      // if Diphoton_isEBEB

      double energyScaleSystUp = Photon1_energyScaleSystUp * Photon2_energyScaleSystUp;
      double energyScaleSystDown = Photon1_energyScaleSystDown * Photon2_energyScaleSystDown;
      double energySigmaUp = Photon1_energySigmaUp * Photon2_energySigmaUp;
      double energySigmaDown = Photon1_energySigmaDown * Photon2_energySigmaDown;
      double energyScaleGainUp = Photon1_energyScaleGainUp * Photon2_energyScaleGainUp;
      //if (Diphoton_Minv  > 0) std::cout << Diphoton_isEBEB << " " << Diphoton_isEBEE << " " << Diphoton_isEEEB << " " << Photon1_energySigmaUp << " " << Photon2_energySigmaUp << " " <<  Photon1_energySigmaDown << " " << Photon2_energySigmaDown << std::endl;
      double energyScaleGainDown = Photon1_energyScaleGainDown * Photon2_energyScaleGainDown;
      double effBBUp    = 0.98+6e-5*Diphoton_Minv;
      double effBBDown  = 0.98-4.5e-5*Diphoton_Minv;
      double effBEUp    = 0.98+4e-5*Diphoton_Minv;
      double effBEDown  = 1.0-3.2e-5*Diphoton_Minv;
      int npv_true = Event_npv_true;
      double pileupUP2016 = ((npv_true == 1)* 8.927e-02+ (npv_true == 2)* 3.422e-01+ (npv_true == 3)* 6.687e-01+ (npv_true == 4)* 7.690e-01+ (npv_true == 5)* 9.180e-01+ (npv_true == 6)* 9.464e-01+ (npv_true == 7)* 7.411e-01+ (npv_true == 8)* 8.445e-01+ (npv_true == 9)* 7.987e-01+ (npv_true == 10)* 6.612e-01+ (npv_true == 11)* 6.135e-01+ (npv_true == 12)* 6.251e-01+ (npv_true == 13)* 6.823e-01+ (npv_true == 14)* 7.386e-01+ (npv_true == 15)* 7.837e-01+ (npv_true == 16)* 8.393e-01+ (npv_true == 17)* 9.019e-01+ (npv_true == 18)* 9.421e-01+ (npv_true == 19)* 9.571e-01+ (npv_true == 20)* 9.626e-01+ (npv_true == 21)* 9.663e-01+ (npv_true == 22)* 9.851e-01+ (npv_true == 23)* 1.014e+00+ (npv_true == 24)* 1.052e+00+ (npv_true == 25)* 1.100e+00+ (npv_true == 26)* 1.155e+00+ (npv_true == 27)* 1.207e+00+ (npv_true == 28)* 1.264e+00+ (npv_true == 29)* 1.323e+00+ (npv_true == 30)* 1.358e+00+ (npv_true == 31)* 1.403e+00+ (npv_true == 32)* 1.421e+00+ (npv_true == 33)* 1.427e+00+ (npv_true == 34)* 1.408e+00+ (npv_true == 35)* 1.362e+00+ (npv_true == 36)* 1.280e+00+ (npv_true == 37)* 1.176e+00+ (npv_true == 38)* 1.051e+00+ (npv_true == 39)* 9.210e-01+ (npv_true == 40)* 7.719e-01+ (npv_true == 41)* 6.302e-01+ (npv_true == 42)* 5.065e-01+ (npv_true == 43)* 3.961e-01+ (npv_true == 44)* 3.095e-01+ (npv_true == 45)* 2.358e-01+ (npv_true == 46)* 1.728e-01+ (npv_true == 47)* 1.288e-01+ (npv_true == 48)* 9.414e-02+ (npv_true == 49)* 6.905e-02+ (npv_true == 50)* 4.982e-02+ (npv_true == 51)* 3.645e-02+ (npv_true == 52)* 2.663e-02+ (npv_true == 53)* 1.921e-02+ (npv_true == 54)* 1.502e-02+ (npv_true == 55)* 1.200e-02+ (npv_true == 56)* 9.225e-03+ (npv_true == 57)* 7.401e-03+ (npv_true == 58)* 6.182e-03+ (npv_true == 59)* 5.053e-03+ (npv_true == 60)* 4.943e-03+ (npv_true == 61)* 4.105e-03+ (npv_true == 62)* 3.179e-03+ (npv_true == 63)* 2.313e-03+ (npv_true == 64)* 1.769e-03+ (npv_true == 65)* 1.198e-03+ (npv_true == 66)* 7.834e-04+ (npv_true == 67)* 5.032e-04+ (npv_true == 68)* 3.354e-04+ (npv_true == 69)* 2.179e-04+ (npv_true == 70)* 1.405e-04+ (npv_true == 71)* 8.989e-05+ (npv_true == 72)* 5.719e-05+ (npv_true == 73)* 3.643e-05+ (npv_true == 74)* 2.276e-05+ (npv_true == 75)* 0.000e+00+ (npv_true == 76)* 0.000e+00+ (npv_true == 77)* 0.000e+00+ (npv_true == 78)* 0.000e+00+ (npv_true == 79)* 0.000e+00+ (npv_true == 80)* 0.000e+00+ (npv_true == 81)* 0.000e+00+ (npv_true == 82)* 0.000e+00+ (npv_true == 83)* 0.000e+00+ (npv_true == 84)* 0.000e+00+ (npv_true == 85)* 0.000e+00+ (npv_true == 86)* 0.000e+00+ (npv_true == 87)* 0.000e+00+ (npv_true == 88)* 0.000e+00+ (npv_true == 89)* 0.000e+00+ (npv_true == 90)* 0.000e+00+ (npv_true == 91)* 0.000e+00+ (npv_true == 92)* 0.000e+00+ (npv_true == 93)* 0.000e+00+ (npv_true == 94)* 0.000e+00+ (npv_true == 95)* 0.000e+00+ (npv_true == 96)* 0.000e+00+ (npv_true == 97)* 0.000e+00+ (npv_true == 98)* 0.000e+00+ (npv_true == 99)* 0.000e+00+ (npv_true == 100)* 0.000e+00);
      double pileupNom2016 = ((npv_true == 1)* 1.018e-01+ (npv_true == 2)* 4.001e-01+ (npv_true == 3)* 7.359e-01+ (npv_true == 4)* 8.663e-01+ (npv_true == 5)* 1.055e+00+ (npv_true == 6)* 1.212e+00+ (npv_true == 7)* 9.897e-01+ (npv_true == 8)* 1.090e+00+ (npv_true == 9)* 1.030e+00+ (npv_true == 10)* 8.741e-01+ (npv_true == 11)* 8.184e-01+ (npv_true == 12)* 8.232e-01+ (npv_true == 13)* 8.798e-01+ (npv_true == 14)* 9.319e-01+ (npv_true == 15)* 9.686e-01+ (npv_true == 16)* 1.009e+00+ (npv_true == 17)* 1.046e+00+ (npv_true == 18)* 1.057e+00+ (npv_true == 19)* 1.046e+00+ (npv_true == 20)* 1.031e+00+ (npv_true == 21)* 1.020e+00+ (npv_true == 22)* 1.029e+00+ (npv_true == 23)* 1.047e+00+ (npv_true == 24)* 1.068e+00+ (npv_true == 25)* 1.096e+00+ (npv_true == 26)* 1.128e+00+ (npv_true == 27)* 1.156e+00+ (npv_true == 28)* 1.187e+00+ (npv_true == 29)* 1.219e+00+ (npv_true == 30)* 1.227e+00+ (npv_true == 31)* 1.242e+00+ (npv_true == 32)* 1.230e+00+ (npv_true == 33)* 1.205e+00+ (npv_true == 34)* 1.155e+00+ (npv_true == 35)* 1.081e+00+ (npv_true == 36)* 9.784e-01+ (npv_true == 37)* 8.612e-01+ (npv_true == 38)* 7.331e-01+ (npv_true == 39)* 6.084e-01+ (npv_true == 40)* 4.797e-01+ (npv_true == 41)* 3.659e-01+ (npv_true == 42)* 2.729e-01+ (npv_true == 43)* 1.969e-01+ (npv_true == 44)* 1.411e-01+ (npv_true == 45)* 9.820e-02+ (npv_true == 46)* 6.550e-02+ (npv_true == 47)* 4.438e-02+ (npv_true == 48)* 2.947e-02+ (npv_true == 49)* 1.968e-02+ (npv_true == 50)* 1.298e-02+ (npv_true == 51)* 8.743e-03+ (npv_true == 52)* 5.943e-03+ (npv_true == 53)* 4.048e-03+ (npv_true == 54)* 3.047e-03+ (npv_true == 55)* 2.397e-03+ (npv_true == 56)* 1.863e-03+ (npv_true == 57)* 1.551e-03+ (npv_true == 58)* 1.374e-03+ (npv_true == 59)* 1.205e-03+ (npv_true == 60)* 1.268e-03+ (npv_true == 61)* 1.121e-03+ (npv_true == 62)* 9.081e-04+ (npv_true == 63)* 6.779e-04+ (npv_true == 64)* 5.220e-04+ (npv_true == 65)* 3.503e-04+ (npv_true == 66)* 2.242e-04+ (npv_true == 67)* 1.397e-04+ (npv_true == 68)* 8.973e-05+ (npv_true == 69)* 5.595e-05+ (npv_true == 70)* 3.451e-05+ (npv_true == 71)* 2.109e-05+ (npv_true == 72)* 1.280e-05+ (npv_true == 73)* 7.770e-06+ (npv_true == 74)* 4.623e-06+ (npv_true == 75)* 0.000e+00+ (npv_true == 76)* 0.000e+00+ (npv_true == 77)* 0.000e+00+ (npv_true == 78)* 0.000e+00+ (npv_true == 79)* 0.000e+00+ (npv_true == 80)* 0.000e+00+ (npv_true == 81)* 0.000e+00+ (npv_true == 82)* 0.000e+00+ (npv_true == 83)* 0.000e+00+ (npv_true == 84)* 0.000e+00+ (npv_true == 85)* 0.000e+00+ (npv_true == 86)* 0.000e+00+ (npv_true == 87)* 0.000e+00+ (npv_true == 88)* 0.000e+00+ (npv_true == 89)* 0.000e+00+ (npv_true == 90)* 0.000e+00+ (npv_true == 91)* 0.000e+00+ (npv_true == 92)* 0.000e+00+ (npv_true == 93)* 0.000e+00+ (npv_true == 94)* 0.000e+00+ (npv_true == 95)* 0.000e+00+ (npv_true == 96)* 0.000e+00+ (npv_true == 97)* 0.000e+00+ (npv_true == 98)* 0.000e+00+ (npv_true == 99)* 0.000e+00+ (npv_true == 100)* 0.000e+00);
      double pileupDown2016 = ((npv_true == 1)* 1.164e-01+ (npv_true == 2)* 4.769e-01+ (npv_true == 3)* 8.042e-01+ (npv_true == 4)* 9.768e-01+ (npv_true == 5)* 1.233e+00+ (npv_true == 6)* 1.591e+00+ (npv_true == 7)* 1.307e+00+ (npv_true == 8)* 1.404e+00+ (npv_true == 9)* 1.337e+00+ (npv_true == 10)* 1.165e+00+ (npv_true == 11)* 1.086e+00+ (npv_true == 12)* 1.072e+00+ (npv_true == 13)* 1.120e+00+ (npv_true == 14)* 1.161e+00+ (npv_true == 15)* 1.176e+00+ (npv_true == 16)* 1.182e+00+ (npv_true == 17)* 1.182e+00+ (npv_true == 18)* 1.160e+00+ (npv_true == 19)* 1.122e+00+ (npv_true == 20)* 1.089e+00+ (npv_true == 21)* 1.066e+00+ (npv_true == 22)* 1.062e+00+ (npv_true == 23)* 1.063e+00+ (npv_true == 24)* 1.062e+00+ (npv_true == 25)* 1.067e+00+ (npv_true == 26)* 1.076e+00+ (npv_true == 27)* 1.082e+00+ (npv_true == 28)* 1.088e+00+ (npv_true == 29)* 1.095e+00+ (npv_true == 30)* 1.077e+00+ (npv_true == 31)* 1.064e+00+ (npv_true == 32)* 1.025e+00+ (npv_true == 33)* 9.726e-01+ (npv_true == 34)* 8.989e-01+ (npv_true == 35)* 8.064e-01+ (npv_true == 36)* 6.955e-01+ (npv_true == 37)* 5.795e-01+ (npv_true == 38)* 4.637e-01+ (npv_true == 39)* 3.590e-01+ (npv_true == 40)* 2.622e-01+ (npv_true == 41)* 1.840e-01+ (npv_true == 42)* 1.255e-01+ (npv_true == 43)* 8.235e-02+ (npv_true == 44)* 5.351e-02+ (npv_true == 45)* 3.369e-02+ (npv_true == 46)* 2.033e-02+ (npv_true == 47)* 1.249e-02+ (npv_true == 48)* 7.559e-03+ (npv_true == 49)* 4.639e-03+ (npv_true == 50)* 2.848e-03+ (npv_true == 51)* 1.816e-03+ (npv_true == 52)* 1.195e-03+ (npv_true == 53)* 8.097e-04+ (npv_true == 54)* 6.238e-04+ (npv_true == 55)* 5.162e-04+ (npv_true == 56)* 4.301e-04+ (npv_true == 57)* 3.865e-04+ (npv_true == 58)* 3.673e-04+ (npv_true == 59)* 3.402e-04+ (npv_true == 60)* 3.697e-04+ (npv_true == 61)* 3.306e-04+ (npv_true == 62)* 2.662e-04+ (npv_true == 63)* 1.946e-04+ (npv_true == 64)* 1.453e-04+ (npv_true == 65)* 9.384e-05+ (npv_true == 66)* 5.754e-05+ (npv_true == 67)* 3.423e-05+ (npv_true == 68)* 2.096e-05+ (npv_true == 69)* 1.244e-05+ (npv_true == 70)* 7.293e-06+ (npv_true == 71)* 4.235e-06+ (npv_true == 72)* 2.441e-06+ (npv_true == 73)* 1.406e-06+ (npv_true == 74)* 7.941e-07+ (npv_true == 75)* 0.000e+00+ (npv_true == 76)* 0.000e+00+ (npv_true == 77)* 0.000e+00+ (npv_true == 78)* 0.000e+00+ (npv_true == 79)* 0.000e+00+ (npv_true == 80)* 0.000e+00+ (npv_true == 81)* 0.000e+00+ (npv_true == 82)* 0.000e+00+ (npv_true == 83)* 0.000e+00+ (npv_true == 84)* 0.000e+00+ (npv_true == 85)* 0.000e+00+ (npv_true == 86)* 0.000e+00+ (npv_true == 87)* 0.000e+00+ (npv_true == 88)* 0.000e+00+ (npv_true == 89)* 0.000e+00+ (npv_true == 90)* 0.000e+00+ (npv_true == 91)* 0.000e+00+ (npv_true == 92)* 0.000e+00+ (npv_true == 93)* 0.000e+00+ (npv_true == 94)* 0.000e+00+ (npv_true == 95)* 0.000e+00+ (npv_true == 96)* 0.000e+00+ (npv_true == 97)* 0.000e+00+ (npv_true == 98)* 0.000e+00+ (npv_true == 99)* 0.000e+00+ (npv_true == 100)* 0.000e+00);
      double pileupUP2017 = ((npv_true == 1)* 5.004e+00+ (npv_true == 2)* 1.940e+01+ (npv_true == 3)* 6.483e+00+ (npv_true == 4)* 5.621e+00+ (npv_true == 5)* 2.397e+00+ (npv_true == 6)* 1.759e+00+ (npv_true == 7)* 1.071e+00+ (npv_true == 8)* 5.652e-01+ (npv_true == 9)* 3.687e-01+ (npv_true == 10)* 4.026e-01+ (npv_true == 11)* 5.382e-01+ (npv_true == 12)* 6.387e-01+ (npv_true == 13)* 7.517e-01+ (npv_true == 14)* 7.827e-01+ (npv_true == 15)* 8.155e-01+ (npv_true == 16)* 8.758e-01+ (npv_true == 17)* 9.712e-01+ (npv_true == 18)* 1.092e+00+ (npv_true == 19)* 1.199e+00+ (npv_true == 20)* 1.269e+00+ (npv_true == 21)* 1.305e+00+ (npv_true == 22)* 1.316e+00+ (npv_true == 23)* 1.302e+00+ (npv_true == 24)* 1.273e+00+ (npv_true == 25)* 1.237e+00+ (npv_true == 26)* 1.202e+00+ (npv_true == 27)* 1.175e+00+ (npv_true == 28)* 1.151e+00+ (npv_true == 29)* 1.125e+00+ (npv_true == 30)* 1.093e+00+ (npv_true == 31)* 1.055e+00+ (npv_true == 32)* 1.011e+00+ (npv_true == 33)* 9.632e-01+ (npv_true == 34)* 9.144e-01+ (npv_true == 35)* 8.645e-01+ (npv_true == 36)* 8.143e-01+ (npv_true == 37)* 7.656e-01+ (npv_true == 38)* 7.211e-01+ (npv_true == 39)* 6.825e-01+ (npv_true == 40)* 6.511e-01+ (npv_true == 41)* 6.278e-01+ (npv_true == 42)* 6.149e-01+ (npv_true == 43)* 6.160e-01+ (npv_true == 44)* 6.360e-01+ (npv_true == 45)* 6.801e-01+ (npv_true == 46)* 7.530e-01+ (npv_true == 47)* 8.585e-01+ (npv_true == 48)* 9.974e-01+ (npv_true == 49)* 1.166e+00+ (npv_true == 50)* 1.356e+00+ (npv_true == 51)* 1.553e+00+ (npv_true == 52)* 1.737e+00+ (npv_true == 53)* 1.888e+00+ (npv_true == 54)* 1.989e+00+ (npv_true == 55)* 2.029e+00+ (npv_true == 56)* 2.004e+00+ (npv_true == 57)* 1.921e+00+ (npv_true == 58)* 1.790e+00+ (npv_true == 59)* 1.628e+00+ (npv_true == 60)* 1.450e+00+ (npv_true == 61)* 1.269e+00+ (npv_true == 62)* 1.096e+00+ (npv_true == 63)* 9.373e-01+ (npv_true == 64)* 7.963e-01+ (npv_true == 65)* 6.742e-01+ (npv_true == 66)* 5.707e-01+ (npv_true == 67)* 4.844e-01+ (npv_true == 68)* 4.136e-01+ (npv_true == 69)* 3.565e-01+ (npv_true == 70)* 3.110e-01+ (npv_true == 71)* 2.754e-01+ (npv_true == 72)* 2.480e-01+ (npv_true == 73)* 2.275e-01+ (npv_true == 74)* 2.125e-01+ (npv_true == 75)* 2.019e-01+ (npv_true == 76)* 1.949e-01+ (npv_true == 77)* 1.906e-01+ (npv_true == 78)* 1.884e-01+ (npv_true == 79)* 1.877e-01+ (npv_true == 80)* 1.878e-01+ (npv_true == 81)* 1.881e-01+ (npv_true == 82)* 1.880e-01+ (npv_true == 83)* 1.867e-01+ (npv_true == 84)* 1.833e-01+ (npv_true == 85)* 1.770e-01+ (npv_true == 86)* 1.667e-01+ (npv_true == 87)* 1.523e-01+ (npv_true == 88)* 1.338e-01+ (npv_true == 89)* 1.126e-01+ (npv_true == 90)* 9.224e-02+ (npv_true == 91)* 7.277e-02+ (npv_true == 92)* 5.552e-02+ (npv_true == 93)* 4.117e-02+ (npv_true == 94)* 2.983e-02+ (npv_true == 95)* 2.123e-02+ (npv_true == 96)* 1.490e-02+ (npv_true == 97)* 1.036e-02+ (npv_true == 98)* 7.144e-03+ (npv_true == 99)* 4.907e-03+ (npv_true == 100)* 0.000e+00);
      double pileupNom2017 = ((npv_true == 1)* 5.165e+00+ (npv_true == 2)* 2.245e+01+ (npv_true == 3)* 7.917e+00+ (npv_true == 4)* 5.592e+00+ (npv_true == 5)* 2.783e+00+ (npv_true == 6)* 1.986e+00+ (npv_true == 7)* 1.109e+00+ (npv_true == 8)* 6.177e-01+ (npv_true == 9)* 4.576e-01+ (npv_true == 10)* 6.203e-01+ (npv_true == 11)* 7.547e-01+ (npv_true == 12)* 9.173e-01+ (npv_true == 13)* 9.898e-01+ (npv_true == 14)* 1.011e+00+ (npv_true == 15)* 1.063e+00+ (npv_true == 16)* 1.157e+00+ (npv_true == 17)* 1.291e+00+ (npv_true == 18)* 1.418e+00+ (npv_true == 19)* 1.495e+00+ (npv_true == 20)* 1.529e+00+ (npv_true == 21)* 1.529e+00+ (npv_true == 22)* 1.501e+00+ (npv_true == 23)* 1.453e+00+ (npv_true == 24)* 1.400e+00+ (npv_true == 25)* 1.350e+00+ (npv_true == 26)* 1.310e+00+ (npv_true == 27)* 1.273e+00+ (npv_true == 28)* 1.233e+00+ (npv_true == 29)* 1.185e+00+ (npv_true == 30)* 1.129e+00+ (npv_true == 31)* 1.067e+00+ (npv_true == 32)* 1.003e+00+ (npv_true == 33)* 9.374e-01+ (npv_true == 34)* 8.717e-01+ (npv_true == 35)* 8.072e-01+ (npv_true == 36)* 7.471e-01+ (npv_true == 37)* 6.937e-01+ (npv_true == 38)* 6.485e-01+ (npv_true == 39)* 6.123e-01+ (npv_true == 40)* 5.868e-01+ (npv_true == 41)* 5.751e-01+ (npv_true == 42)* 5.812e-01+ (npv_true == 43)* 6.095e-01+ (npv_true == 44)* 6.631e-01+ (npv_true == 45)* 7.437e-01+ (npv_true == 46)* 8.496e-01+ (npv_true == 47)* 9.746e-01+ (npv_true == 48)* 1.107e+00+ (npv_true == 49)* 1.232e+00+ (npv_true == 50)* 1.332e+00+ (npv_true == 51)* 1.392e+00+ (npv_true == 52)* 1.404e+00+ (npv_true == 53)* 1.365e+00+ (npv_true == 54)* 1.281e+00+ (npv_true == 55)* 1.165e+00+ (npv_true == 56)* 1.029e+00+ (npv_true == 57)* 8.867e-01+ (npv_true == 58)* 7.491e-01+ (npv_true == 59)* 6.231e-01+ (npv_true == 60)* 5.123e-01+ (npv_true == 61)* 4.181e-01+ (npv_true == 62)* 3.397e-01+ (npv_true == 63)* 2.757e-01+ (npv_true == 64)* 2.243e-01+ (npv_true == 65)* 1.834e-01+ (npv_true == 66)* 1.513e-01+ (npv_true == 67)* 1.263e-01+ (npv_true == 68)* 1.071e-01+ (npv_true == 69)* 9.236e-02+ (npv_true == 70)* 8.119e-02+ (npv_true == 71)* 7.275e-02+ (npv_true == 72)* 6.640e-02+ (npv_true == 73)* 6.164e-02+ (npv_true == 74)* 5.807e-02+ (npv_true == 75)* 5.537e-02+ (npv_true == 76)* 5.331e-02+ (npv_true == 77)* 5.168e-02+ (npv_true == 78)* 5.034e-02+ (npv_true == 79)* 4.915e-02+ (npv_true == 80)* 4.798e-02+ (npv_true == 81)* 4.671e-02+ (npv_true == 82)* 4.521e-02+ (npv_true == 83)* 4.334e-02+ (npv_true == 84)* 4.096e-02+ (npv_true == 85)* 3.796e-02+ (npv_true == 86)* 3.425e-02+ (npv_true == 87)* 2.988e-02+ (npv_true == 88)* 2.504e-02+ (npv_true == 89)* 2.005e-02+ (npv_true == 90)* 1.559e-02+ (npv_true == 91)* 1.165e-02+ (npv_true == 92)* 8.410e-03+ (npv_true == 93)* 5.889e-03+ (npv_true == 94)* 4.023e-03+ (npv_true == 95)* 2.695e-03+ (npv_true == 96)* 1.778e-03+ (npv_true == 97)* 1.160e-03+ (npv_true == 98)* 7.500e-04+ (npv_true == 99)* 4.821e-04+ (npv_true == 100)* 0.000e+00);
      double pileupDown2017 = ((npv_true == 1)* 5.389e+00+ (npv_true == 2)* 2.475e+01+ (npv_true == 3)* 1.021e+01+ (npv_true == 4)* 5.415e+00+ (npv_true == 5)* 3.188e+00+ (npv_true == 6)* 2.205e+00+ (npv_true == 7)* 1.154e+00+ (npv_true == 8)* 6.879e-01+ (npv_true == 9)* 6.483e-01+ (npv_true == 10)* 9.068e-01+ (npv_true == 11)* 1.083e+00+ (npv_true == 12)* 1.257e+00+ (npv_true == 13)* 1.278e+00+ (npv_true == 14)* 1.312e+00+ (npv_true == 15)* 1.398e+00+ (npv_true == 16)* 1.540e+00+ (npv_true == 17)* 1.690e+00+ (npv_true == 18)* 1.781e+00+ (npv_true == 19)* 1.810e+00+ (npv_true == 20)* 1.796e+00+ (npv_true == 21)* 1.747e+00+ (npv_true == 22)* 1.675e+00+ (npv_true == 23)* 1.597e+00+ (npv_true == 24)* 1.527e+00+ (npv_true == 25)* 1.470e+00+ (npv_true == 26)* 1.417e+00+ (npv_true == 27)* 1.359e+00+ (npv_true == 28)* 1.292e+00+ (npv_true == 29)* 1.215e+00+ (npv_true == 30)* 1.134e+00+ (npv_true == 31)* 1.051e+00+ (npv_true == 32)* 9.671e-01+ (npv_true == 33)* 8.844e-01+ (npv_true == 34)* 8.058e-01+ (npv_true == 35)* 7.348e-01+ (npv_true == 36)* 6.734e-01+ (npv_true == 37)* 6.225e-01+ (npv_true == 38)* 5.832e-01+ (npv_true == 39)* 5.581e-01+ (npv_true == 40)* 5.509e-01+ (npv_true == 41)* 5.650e-01+ (npv_true == 42)* 6.031e-01+ (npv_true == 43)* 6.652e-01+ (npv_true == 44)* 7.482e-01+ (npv_true == 45)* 8.439e-01+ (npv_true == 46)* 9.398e-01+ (npv_true == 47)* 1.020e+00+ (npv_true == 48)* 1.071e+00+ (npv_true == 49)* 1.080e+00+ (npv_true == 50)* 1.045e+00+ (npv_true == 51)* 9.704e-01+ (npv_true == 52)* 8.669e-01+ (npv_true == 53)* 7.479e-01+ (npv_true == 54)* 6.260e-01+ (npv_true == 55)* 5.112e-01+ (npv_true == 56)* 4.094e-01+ (npv_true == 57)* 3.232e-01+ (npv_true == 58)* 2.528e-01+ (npv_true == 59)* 1.966e-01+ (npv_true == 60)* 1.527e-01+ (npv_true == 61)* 1.188e-01+ (npv_true == 62)* 9.293e-02+ (npv_true == 63)* 7.332e-02+ (npv_true == 64)* 5.856e-02+ (npv_true == 65)* 4.749e-02+ (npv_true == 66)* 3.921e-02+ (npv_true == 67)* 3.300e-02+ (npv_true == 68)* 2.833e-02+ (npv_true == 69)* 2.477e-02+ (npv_true == 70)* 2.204e-02+ (npv_true == 71)* 1.991e-02+ (npv_true == 72)* 1.821e-02+ (npv_true == 73)* 1.682e-02+ (npv_true == 74)* 1.567e-02+ (npv_true == 75)* 1.468e-02+ (npv_true == 76)* 1.381e-02+ (npv_true == 77)* 1.302e-02+ (npv_true == 78)* 1.228e-02+ (npv_true == 79)* 1.157e-02+ (npv_true == 80)* 1.087e-02+ (npv_true == 81)* 1.015e-02+ (npv_true == 82)* 9.391e-03+ (npv_true == 83)* 8.589e-03+ (npv_true == 84)* 7.725e-03+ (npv_true == 85)* 6.796e-03+ (npv_true == 86)* 5.809e-03+ (npv_true == 87)* 4.792e-03+ (npv_true == 88)* 3.788e-03+ (npv_true == 89)* 2.857e-03+ (npv_true == 90)* 2.088e-03+ (npv_true == 91)* 1.465e-03+ (npv_true == 92)* 9.906e-04+ (npv_true == 93)* 6.489e-04+ (npv_true == 94)* 4.141e-04+ (npv_true == 95)* 2.588e-04+ (npv_true == 96)* 1.591e-04+ (npv_true == 97)* 9.652e-05+ (npv_true == 98)* 5.800e-05+ (npv_true == 99)* 3.460e-05+ (npv_true == 100)* 0.000e+00);
      double pileupUP2018   = ((npv_true == 1)* 3.505e+00+ (npv_true == 2)* 1.203e+01+ (npv_true == 3)* 7.103e+00+ (npv_true == 4)* 6.040e+00+ (npv_true == 5)* 5.005e+00+ (npv_true == 6)* 3.855e+00+ (npv_true == 7)* 2.864e+00+ (npv_true == 8)* 2.169e+00+ (npv_true == 9)* 1.672e+00+ (npv_true == 10)* 1.322e+00+ (npv_true == 11)* 1.104e+00+ (npv_true == 12)* 9.825e-01+ (npv_true == 13)* 9.205e-01+ (npv_true == 14)* 8.945e-01+ (npv_true == 15)* 8.909e-01+ (npv_true == 16)* 9.033e-01+ (npv_true == 17)* 9.285e-01+ (npv_true == 18)* 9.634e-01+ (npv_true == 19)* 1.004e+00+ (npv_true == 20)* 1.045e+00+ (npv_true == 21)* 1.080e+00+ (npv_true == 22)* 1.105e+00+ (npv_true == 23)* 1.116e+00+ (npv_true == 24)* 1.112e+00+ (npv_true == 25)* 1.097e+00+ (npv_true == 26)* 1.074e+00+ (npv_true == 27)* 1.050e+00+ (npv_true == 28)* 1.027e+00+ (npv_true == 29)* 1.009e+00+ (npv_true == 30)* 9.972e-01+ (npv_true == 31)* 9.914e-01+ (npv_true == 32)* 9.914e-01+ (npv_true == 33)* 9.965e-01+ (npv_true == 34)* 1.006e+00+ (npv_true == 35)* 1.019e+00+ (npv_true == 36)* 1.035e+00+ (npv_true == 37)* 1.052e+00+ (npv_true == 38)* 1.070e+00+ (npv_true == 39)* 1.086e+00+ (npv_true == 40)* 1.099e+00+ (npv_true == 41)* 1.106e+00+ (npv_true == 42)* 1.106e+00+ (npv_true == 43)* 1.098e+00+ (npv_true == 44)* 1.079e+00+ (npv_true == 45)* 1.050e+00+ (npv_true == 46)* 1.011e+00+ (npv_true == 47)* 9.631e-01+ (npv_true == 48)* 9.081e-01+ (npv_true == 49)* 8.477e-01+ (npv_true == 50)* 7.841e-01+ (npv_true == 51)* 7.195e-01+ (npv_true == 52)* 6.558e-01+ (npv_true == 53)* 5.947e-01+ (npv_true == 54)* 5.374e-01+ (npv_true == 55)* 4.848e-01+ (npv_true == 56)* 4.371e-01+ (npv_true == 57)* 3.947e-01+ (npv_true == 58)* 3.571e-01+ (npv_true == 59)* 3.241e-01+ (npv_true == 60)* 2.952e-01+ (npv_true == 61)* 2.697e-01+ (npv_true == 62)* 2.471e-01+ (npv_true == 63)* 2.267e-01+ (npv_true == 64)* 2.081e-01+ (npv_true == 65)* 1.910e-01+ (npv_true == 66)* 1.750e-01+ (npv_true == 67)* 1.599e-01+ (npv_true == 68)* 1.457e-01+ (npv_true == 69)* 1.323e-01+ (npv_true == 70)* 1.198e-01+ (npv_true == 71)* 1.082e-01+ (npv_true == 72)* 9.734e-02+ (npv_true == 73)* 8.739e-02+ (npv_true == 74)* 7.827e-02+ (npv_true == 75)* 6.995e-02+ (npv_true == 76)* 6.236e-02+ (npv_true == 77)* 5.545e-02+ (npv_true == 78)* 4.915e-02+ (npv_true == 79)* 4.338e-02+ (npv_true == 80)* 3.808e-02+ (npv_true == 81)* 3.317e-02+ (npv_true == 82)* 2.860e-02+ (npv_true == 83)* 2.433e-02+ (npv_true == 84)* 2.032e-02+ (npv_true == 85)* 1.656e-02+ (npv_true == 86)* 1.309e-02+ (npv_true == 87)* 9.965e-03+ (npv_true == 88)* 7.249e-03+ (npv_true == 89)* 5.015e-03+ (npv_true == 90)* 3.353e-03+ (npv_true == 91)* 2.144e-03+ (npv_true == 92)* 1.316e-03+ (npv_true == 93)* 7.801e-04+ (npv_true == 94)* 4.485e-04+ (npv_true == 95)* 2.514e-04+ (npv_true == 96)* 1.380e-04+ (npv_true == 97)* 7.448e-05+ (npv_true == 98)* 3.962e-05+ (npv_true == 99)* 2.082e-05+ (npv_true == 100)* 0.000e+00);
      double pileupNom2018  = ((npv_true == 1)* 3.771e+00+ (npv_true == 2)* 1.377e+01+ (npv_true == 3)* 8.318e+00+ (npv_true == 4)* 7.028e+00+ (npv_true == 5)* 5.801e+00+ (npv_true == 6)* 4.451e+00+ (npv_true == 7)* 3.347e+00+ (npv_true == 8)* 2.563e+00+ (npv_true == 9)* 1.986e+00+ (npv_true == 10)* 1.588e+00+ (npv_true == 11)* 1.351e+00+ (npv_true == 12)* 1.221e+00+ (npv_true == 13)* 1.154e+00+ (npv_true == 14)* 1.124e+00+ (npv_true == 15)* 1.119e+00+ (npv_true == 16)* 1.132e+00+ (npv_true == 17)* 1.160e+00+ (npv_true == 18)* 1.195e+00+ (npv_true == 19)* 1.233e+00+ (npv_true == 20)* 1.264e+00+ (npv_true == 21)* 1.283e+00+ (npv_true == 22)* 1.286e+00+ (npv_true == 23)* 1.271e+00+ (npv_true == 24)* 1.242e+00+ (npv_true == 25)* 1.207e+00+ (npv_true == 26)* 1.170e+00+ (npv_true == 27)* 1.137e+00+ (npv_true == 28)* 1.109e+00+ (npv_true == 29)* 1.089e+00+ (npv_true == 30)* 1.076e+00+ (npv_true == 31)* 1.068e+00+ (npv_true == 32)* 1.065e+00+ (npv_true == 33)* 1.066e+00+ (npv_true == 34)* 1.070e+00+ (npv_true == 35)* 1.074e+00+ (npv_true == 36)* 1.078e+00+ (npv_true == 37)* 1.081e+00+ (npv_true == 38)* 1.079e+00+ (npv_true == 39)* 1.070e+00+ (npv_true == 40)* 1.054e+00+ (npv_true == 41)* 1.028e+00+ (npv_true == 42)* 9.919e-01+ (npv_true == 43)* 9.456e-01+ (npv_true == 44)* 8.899e-01+ (npv_true == 45)* 8.267e-01+ (npv_true == 46)* 7.579e-01+ (npv_true == 47)* 6.862e-01+ (npv_true == 48)* 6.141e-01+ (npv_true == 49)* 5.438e-01+ (npv_true == 50)* 4.774e-01+ (npv_true == 51)* 4.163e-01+ (npv_true == 52)* 3.614e-01+ (npv_true == 53)* 3.129e-01+ (npv_true == 54)* 2.709e-01+ (npv_true == 55)* 2.350e-01+ (npv_true == 56)* 2.044e-01+ (npv_true == 57)* 1.785e-01+ (npv_true == 58)* 1.565e-01+ (npv_true == 59)* 1.377e-01+ (npv_true == 60)* 1.215e-01+ (npv_true == 61)* 1.074e-01+ (npv_true == 62)* 9.489e-02+ (npv_true == 63)* 8.370e-02+ (npv_true == 64)* 7.360e-02+ (npv_true == 65)* 6.446e-02+ (npv_true == 66)* 5.620e-02+ (npv_true == 67)* 4.875e-02+ (npv_true == 68)* 4.209e-02+ (npv_true == 69)* 3.618e-02+ (npv_true == 70)* 3.098e-02+ (npv_true == 71)* 2.645e-02+ (npv_true == 72)* 2.252e-02+ (npv_true == 73)* 1.914e-02+ (npv_true == 74)* 1.623e-02+ (npv_true == 75)* 1.374e-02+ (npv_true == 76)* 1.160e-02+ (npv_true == 77)* 9.763e-03+ (npv_true == 78)* 8.179e-03+ (npv_true == 79)* 6.812e-03+ (npv_true == 80)* 5.628e-03+ (npv_true == 81)* 4.603e-03+ (npv_true == 82)* 3.715e-03+ (npv_true == 83)* 2.948e-03+ (npv_true == 84)* 2.289e-03+ (npv_true == 85)* 1.730e-03+ (npv_true == 86)* 1.263e-03+ (npv_true == 87)* 8.851e-04+ (npv_true == 88)* 5.910e-04+ (npv_true == 89)* 3.742e-04+ (npv_true == 90)* 2.282e-04+ (npv_true == 91)* 1.328e-04+ (npv_true == 92)* 7.402e-05+ (npv_true == 93)* 3.971e-05+ (npv_true == 94)* 2.062e-05+ (npv_true == 95)* 1.042e-05+ (npv_true == 96)* 5.146e-06+ (npv_true == 97)* 2.493e-06+ (npv_true == 98)* 1.189e-06+ (npv_true == 99)* 5.604e-07+ (npv_true == 100)* 0.000e+00);
      double pileupDown2018 = ((npv_true == 1)* 4.065e+00+ (npv_true == 2)* 1.582e+01+ (npv_true == 3)* 9.735e+00+ (npv_true == 4)* 8.166e+00+ (npv_true == 5)* 6.717e+00+ (npv_true == 6)* 5.150e+00+ (npv_true == 7)* 3.927e+00+ (npv_true == 8)* 3.034e+00+ (npv_true == 9)* 2.365e+00+ (npv_true == 10)* 1.923e+00+ (npv_true == 11)* 1.667e+00+ (npv_true == 12)* 1.526e+00+ (npv_true == 13)* 1.450e+00+ (npv_true == 14)* 1.413e+00+ (npv_true == 15)* 1.404e+00+ (npv_true == 16)* 1.416e+00+ (npv_true == 17)* 1.441e+00+ (npv_true == 18)* 1.471e+00+ (npv_true == 19)* 1.495e+00+ (npv_true == 20)* 1.505e+00+ (npv_true == 21)* 1.495e+00+ (npv_true == 22)* 1.464e+00+ (npv_true == 23)* 1.418e+00+ (npv_true == 24)* 1.365e+00+ (npv_true == 25)* 1.313e+00+ (npv_true == 26)* 1.266e+00+ (npv_true == 27)* 1.227e+00+ (npv_true == 28)* 1.197e+00+ (npv_true == 29)* 1.175e+00+ (npv_true == 30)* 1.158e+00+ (npv_true == 31)* 1.146e+00+ (npv_true == 32)* 1.137e+00+ (npv_true == 33)* 1.129e+00+ (npv_true == 34)* 1.121e+00+ (npv_true == 35)* 1.110e+00+ (npv_true == 36)* 1.095e+00+ (npv_true == 37)* 1.073e+00+ (npv_true == 38)* 1.042e+00+ (npv_true == 39)* 1.002e+00+ (npv_true == 40)* 9.513e-01+ (npv_true == 41)* 8.907e-01+ (npv_true == 42)* 8.216e-01+ (npv_true == 43)* 7.463e-01+ (npv_true == 44)* 6.673e-01+ (npv_true == 45)* 5.877e-01+ (npv_true == 46)* 5.101e-01+ (npv_true == 47)* 4.371e-01+ (npv_true == 48)* 3.704e-01+ (npv_true == 49)* 3.111e-01+ (npv_true == 50)* 2.597e-01+ (npv_true == 51)* 2.160e-01+ (npv_true == 52)* 1.795e-01+ (npv_true == 53)* 1.494e-01+ (npv_true == 54)* 1.247e-01+ (npv_true == 55)* 1.046e-01+ (npv_true == 56)* 8.804e-02+ (npv_true == 57)* 7.441e-02+ (npv_true == 58)* 6.306e-02+ (npv_true == 59)* 5.350e-02+ (npv_true == 60)* 4.535e-02+ (npv_true == 61)* 3.835e-02+ (npv_true == 62)* 3.230e-02+ (npv_true == 63)* 2.706e-02+ (npv_true == 64)* 2.254e-02+ (npv_true == 65)* 1.866e-02+ (npv_true == 66)* 1.536e-02+ (npv_true == 67)* 1.257e-02+ (npv_true == 68)* 1.024e-02+ (npv_true == 69)* 8.304e-03+ (npv_true == 70)* 6.715e-03+ (npv_true == 71)* 5.415e-03+ (npv_true == 72)* 4.357e-03+ (npv_true == 73)* 3.497e-03+ (npv_true == 74)* 2.799e-03+ (npv_true == 75)* 2.232e-03+ (npv_true == 76)* 1.771e-03+ (npv_true == 77)* 1.397e-03+ (npv_true == 78)* 1.094e-03+ (npv_true == 79)* 8.487e-04+ (npv_true == 80)* 6.507e-04+ (npv_true == 81)* 4.921e-04+ (npv_true == 82)* 3.659e-04+ (npv_true == 83)* 2.665e-04+ (npv_true == 84)* 1.893e-04+ (npv_true == 85)* 1.304e-04+ (npv_true == 86)* 8.657e-05+ (npv_true == 87)* 5.497e-05+ (npv_true == 88)* 3.316e-05+ (npv_true == 89)* 1.892e-05+ (npv_true == 90)* 1.038e-05+ (npv_true == 91)* 5.414e-06+ (npv_true == 92)* 2.700e-06+ (npv_true == 93)* 1.294e-06+ (npv_true == 94)* 5.994e-07+ (npv_true == 95)* 2.703e-07+ (npv_true == 96)* 1.197e-07+ (npv_true == 97)* 5.268e-08+ (npv_true == 98)* 2.363e-08+ (npv_true == 99)* 1.132e-08+ (npv_true == 100)* 0.000e+00);

      double pileupUp, pileupNom, pileupDown;

      if (run == 2016){
        pileupUp = pileupUP2016;
        pileupNom = pileupNom2016;
        pileupDown = pileupDown2016;
      }

      if (run == 2017){
        pileupUp = pileupUP2017;
        pileupNom = pileupNom2017;
        pileupDown = pileupDown2017;
      }

      if (run == 2018){
        pileupUp = pileupUP2018;
        pileupNom = pileupNom2018;
        pileupDown = pileupDown2018;
      }

      // std::cout << pileupUp << " " << pileupDown << s

      if (Diphoton_isEBEB){
        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);


        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_energyScaleSystUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_energyScaleSystUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_energyScaleSystUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_energyScaleSystUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_energyScaleSystUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_energyScaleSystUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_energyScaleSystUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_energyScaleSystUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_energyScaleSystUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_energyScaleSystUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_energyScaleSystDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_energyScaleSystDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_energyScaleSystDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_energyScaleSystDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_energyScaleSystDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_energyScaleSystDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_energyScaleSystDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_energyScaleSystDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_energyScaleSystDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_energyScaleSystDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_energySigmaDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_energySigmaDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_energySigmaDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_energySigmaDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_energySigmaDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_energySigmaDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_energySigmaDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_energySigmaDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_energySigmaDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_energySigmaDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_energySigmaUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_energySigmaUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_energySigmaUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_energySigmaUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_energySigmaUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_energySigmaUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_energySigmaUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_energySigmaUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_energySigmaUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_energySigmaUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_energyScaleGainUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_energyScaleGainUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_energyScaleGainUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_energyScaleGainUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_energyScaleGainUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_energyScaleGainUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_energyScaleGainUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_energyScaleGainUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_energyScaleGainUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_energyScaleGainUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_energyScaleGainDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_energyScaleGainDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_energyScaleGainDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_energyScaleGainDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_energyScaleGainDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_energyScaleGainDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_energyScaleGainDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_energyScaleGainDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_energyScaleGainDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_energyScaleGainDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_pileupUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_pileupUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_pileupUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_pileupUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_pileupUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_pileupUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_pileupUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_pileupUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_pileupUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_pileupUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_pileupDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_pileupDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_pileupDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_pileupDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_pileupDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_pileupDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_pileupDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_pileupDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_pileupDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_pileupDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_effUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_effUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_effUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_effUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_effUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_effUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_effUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_effUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_effUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_effUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBUp);

        if (GenDiphoton_Minv > 0.1) diphotonMinvEBEB_k0p1_effDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEB_k1_effDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEB_k10_effDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEB_k100_effDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEB_k500_effDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEB_k1000_effDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEB_k2000_effDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEB_k3000_effDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEB_k4000_effDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEB_k5000_effDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBBDown);


      }

      // if Diphoton_isEBEE or Diphoton_isEEEB
      if (Diphoton_isEBEE or Diphoton_isEEEB){
        if (GenDiphoton_Minv > 0.1)  diphotonMinvEBEE_k0p1->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);
        if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom);


                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_energyScaleSystUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_energyScaleSystUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_energyScaleSystUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_energyScaleSystUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_energyScaleSystUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_energyScaleSystUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_energyScaleSystUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_energyScaleSystUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_energyScaleSystUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_energyScaleSystUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystUp);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_energyScaleSystDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_energyScaleSystDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_energyScaleSystDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_energyScaleSystDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_energyScaleSystDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_energyScaleSystDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_energyScaleSystDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_energyScaleSystDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_energyScaleSystDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_energyScaleSystDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleSystDown);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_energySigmaDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_energySigmaDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_energySigmaDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_energySigmaDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_energySigmaDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_energySigmaDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_energySigmaDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_energySigmaDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_energySigmaDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_energySigmaDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaDown);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_energySigmaUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_energySigmaUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_energySigmaUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_energySigmaUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_energySigmaUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_energySigmaUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_energySigmaUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_energySigmaUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_energySigmaUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_energySigmaUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energySigmaUp);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_energyScaleGainUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_energyScaleGainUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_energyScaleGainUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_energyScaleGainUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_energyScaleGainUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_energyScaleGainUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_energyScaleGainUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_energyScaleGainUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_energyScaleGainUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_energyScaleGainUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainUp);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_energyScaleGainDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_energyScaleGainDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_energyScaleGainDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_energyScaleGainDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_energyScaleGainDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_energyScaleGainDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_energyScaleGainDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_energyScaleGainDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_energyScaleGainDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_energyScaleGainDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*energyScaleGainDown);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_pileupUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_pileupUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_pileupUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_pileupUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_pileupUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_pileupUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_pileupUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_pileupUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_pileupUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_pileupUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupUp);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_pileupDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_pileupDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_pileupDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_pileupDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_pileupDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_pileupDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_pileupDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_pileupDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_pileupDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_pileupDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupDown);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_effUp->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_effUp->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_effUp->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_effUp->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_effUp->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_effUp->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_effUp->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_effUp->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_effUp->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_effUp->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEUp);

                if (GenDiphoton_Minv > 0.1) diphotonMinvEBEE_k0p1_effDown->Fill(Diphoton_Minv, scale(0.1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 1)  diphotonMinvEBEE_k1_effDown->Fill(Diphoton_Minv, scale(1, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 10)  diphotonMinvEBEE_k10_effDown->Fill(Diphoton_Minv, scale(10, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 100)  diphotonMinvEBEE_k100_effDown->Fill(Diphoton_Minv, scale(100, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 500)  diphotonMinvEBEE_k500_effDown->Fill(Diphoton_Minv, scale(500, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 1000) diphotonMinvEBEE_k1000_effDown->Fill(Diphoton_Minv, scale(1000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 2000) diphotonMinvEBEE_k2000_effDown->Fill(Diphoton_Minv, scale(2000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 3000) diphotonMinvEBEE_k3000_effDown->Fill(Diphoton_Minv, scale(3000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 4000)  diphotonMinvEBEE_k4000_effDown->Fill(Diphoton_Minv, scale(4000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);
                if (GenDiphoton_Minv > 5000) diphotonMinvEBEE_k5000_effDown->Fill(Diphoton_Minv, scale(5000, Event_weightAll, GenDiphoton_Minv, M5)*pileupNom*effBEDown);


      }
   }

   // vector<TString> kvalue = {"0p1", "1", "10", "100", "500", "1000", "2000", "3000", "4000", "5000"};
   TFile file_out(fileout_name, "RECREATE");

   diphotonMinvEBEB_k0p1->Write();
   diphotonMinvEBEB_k1->Write();
   diphotonMinvEBEB_k10->Write();
   diphotonMinvEBEB_k100->Write();
   diphotonMinvEBEB_k500->Write();
   diphotonMinvEBEB_k1000->Write();
   diphotonMinvEBEB_k2000->Write();
   diphotonMinvEBEB_k3000->Write();
   diphotonMinvEBEB_k4000->Write();
   diphotonMinvEBEB_k5000->Write();


   diphotonMinvEBEE_k0p1->Write();
   diphotonMinvEBEE_k1->Write();
   diphotonMinvEBEE_k10->Write();
   diphotonMinvEBEE_k100->Write();
   diphotonMinvEBEE_k500->Write();
   diphotonMinvEBEE_k1000->Write();
   diphotonMinvEBEE_k2000->Write();
   diphotonMinvEBEE_k3000->Write();
   diphotonMinvEBEE_k4000->Write();
   diphotonMinvEBEE_k5000->Write();

   // Systematics:

   diphotonMinvEBEB_k0p1_energyScaleSystUp->Write();
   diphotonMinvEBEB_k1_energyScaleSystUp->Write();
   diphotonMinvEBEB_k10_energyScaleSystUp->Write();
   diphotonMinvEBEB_k100_energyScaleSystUp->Write();
   diphotonMinvEBEB_k500_energyScaleSystUp->Write();
   diphotonMinvEBEB_k1000_energyScaleSystUp->Write();
   diphotonMinvEBEB_k2000_energyScaleSystUp->Write();
   diphotonMinvEBEB_k3000_energyScaleSystUp->Write();
   diphotonMinvEBEB_k4000_energyScaleSystUp->Write();
   diphotonMinvEBEB_k5000_energyScaleSystUp->Write();

   diphotonMinvEBEE_k0p1_energyScaleSystUp->Write();
   diphotonMinvEBEE_k1_energyScaleSystUp->Write();
   diphotonMinvEBEE_k10_energyScaleSystUp->Write();
   diphotonMinvEBEE_k100_energyScaleSystUp->Write();
   diphotonMinvEBEE_k500_energyScaleSystUp->Write();
   diphotonMinvEBEE_k1000_energyScaleSystUp->Write();
   diphotonMinvEBEE_k2000_energyScaleSystUp->Write();
   diphotonMinvEBEE_k3000_energyScaleSystUp->Write();
   diphotonMinvEBEE_k4000_energyScaleSystUp->Write();
   diphotonMinvEBEE_k5000_energyScaleSystUp->Write();

   diphotonMinvEBEB_k0p1_energyScaleSystDown->Write();
   diphotonMinvEBEB_k1_energyScaleSystDown->Write();
   diphotonMinvEBEB_k10_energyScaleSystDown->Write();
   diphotonMinvEBEB_k100_energyScaleSystDown->Write();
   diphotonMinvEBEB_k500_energyScaleSystDown->Write();
   diphotonMinvEBEB_k1000_energyScaleSystDown->Write();
   diphotonMinvEBEB_k2000_energyScaleSystDown->Write();
   diphotonMinvEBEB_k3000_energyScaleSystDown->Write();
   diphotonMinvEBEB_k4000_energyScaleSystDown->Write();
   diphotonMinvEBEB_k5000_energyScaleSystDown->Write();

   diphotonMinvEBEE_k0p1_energyScaleSystDown->Write();
   diphotonMinvEBEE_k1_energyScaleSystDown->Write();
   diphotonMinvEBEE_k10_energyScaleSystDown->Write();
   diphotonMinvEBEE_k100_energyScaleSystDown->Write();
   diphotonMinvEBEE_k500_energyScaleSystDown->Write();
   diphotonMinvEBEE_k1000_energyScaleSystDown->Write();
   diphotonMinvEBEE_k2000_energyScaleSystDown->Write();
   diphotonMinvEBEE_k3000_energyScaleSystDown->Write();
   diphotonMinvEBEE_k4000_energyScaleSystDown->Write();
   diphotonMinvEBEE_k5000_energyScaleSystDown->Write();

   diphotonMinvEBEB_k0p1_energySigmaUp->Write();
   diphotonMinvEBEB_k1_energySigmaUp->Write();
   diphotonMinvEBEB_k10_energySigmaUp->Write();
   diphotonMinvEBEB_k100_energySigmaUp->Write();
   diphotonMinvEBEB_k500_energySigmaUp->Write();
   diphotonMinvEBEB_k1000_energySigmaUp->Write();
   diphotonMinvEBEB_k2000_energySigmaUp->Write();
   diphotonMinvEBEB_k3000_energySigmaUp->Write();
   diphotonMinvEBEB_k4000_energySigmaUp->Write();
   diphotonMinvEBEB_k5000_energySigmaUp->Write();

   diphotonMinvEBEE_k0p1_energySigmaUp->Write();
   diphotonMinvEBEE_k1_energySigmaUp->Write();
   diphotonMinvEBEE_k10_energySigmaUp->Write();
   diphotonMinvEBEE_k100_energySigmaUp->Write();
   diphotonMinvEBEE_k500_energySigmaUp->Write();
   diphotonMinvEBEE_k1000_energySigmaUp->Write();
   diphotonMinvEBEE_k2000_energySigmaUp->Write();
   diphotonMinvEBEE_k3000_energySigmaUp->Write();
   diphotonMinvEBEE_k4000_energySigmaUp->Write();
   diphotonMinvEBEE_k5000_energySigmaUp->Write();

   diphotonMinvEBEB_k0p1_energySigmaDown->Write();
   diphotonMinvEBEB_k1_energySigmaDown->Write();
   diphotonMinvEBEB_k10_energySigmaDown->Write();
   diphotonMinvEBEB_k100_energySigmaDown->Write();
   diphotonMinvEBEB_k500_energySigmaDown->Write();
   diphotonMinvEBEB_k1000_energySigmaDown->Write();
   diphotonMinvEBEB_k2000_energySigmaDown->Write();
   diphotonMinvEBEB_k3000_energySigmaDown->Write();
   diphotonMinvEBEB_k4000_energySigmaDown->Write();
   diphotonMinvEBEB_k5000_energySigmaDown->Write();

   diphotonMinvEBEE_k0p1_energySigmaDown->Write();
   diphotonMinvEBEE_k1_energySigmaDown->Write();
   diphotonMinvEBEE_k10_energySigmaDown->Write();
   diphotonMinvEBEE_k100_energySigmaDown->Write();
   diphotonMinvEBEE_k500_energySigmaDown->Write();
   diphotonMinvEBEE_k1000_energySigmaDown->Write();
   diphotonMinvEBEE_k2000_energySigmaDown->Write();
   diphotonMinvEBEE_k3000_energySigmaDown->Write();
   diphotonMinvEBEE_k4000_energySigmaDown->Write();
   diphotonMinvEBEE_k5000_energySigmaDown->Write();

   diphotonMinvEBEB_k0p1_energyScaleGainUp->Write();
   diphotonMinvEBEB_k1_energyScaleGainUp->Write();
   diphotonMinvEBEB_k10_energyScaleGainUp->Write();
   diphotonMinvEBEB_k100_energyScaleGainUp->Write();
   diphotonMinvEBEB_k500_energyScaleGainUp->Write();
   diphotonMinvEBEB_k1000_energyScaleGainUp->Write();
   diphotonMinvEBEB_k2000_energyScaleGainUp->Write();
   diphotonMinvEBEB_k3000_energyScaleGainUp->Write();
   diphotonMinvEBEB_k4000_energyScaleGainUp->Write();
   diphotonMinvEBEB_k5000_energyScaleGainUp->Write();

   diphotonMinvEBEE_k0p1_energyScaleGainUp->Write();
   diphotonMinvEBEE_k1_energyScaleGainUp->Write();
   diphotonMinvEBEE_k10_energyScaleGainUp->Write();
   diphotonMinvEBEE_k100_energyScaleGainUp->Write();
   diphotonMinvEBEE_k500_energyScaleGainUp->Write();
   diphotonMinvEBEE_k1000_energyScaleGainUp->Write();
   diphotonMinvEBEE_k2000_energyScaleGainUp->Write();
   diphotonMinvEBEE_k3000_energyScaleGainUp->Write();
   diphotonMinvEBEE_k4000_energyScaleGainUp->Write();
   diphotonMinvEBEE_k5000_energyScaleGainUp->Write();

   diphotonMinvEBEB_k0p1_energyScaleGainDown->Write();
   diphotonMinvEBEB_k1_energyScaleGainDown->Write();
   diphotonMinvEBEB_k10_energyScaleGainDown->Write();
   diphotonMinvEBEB_k100_energyScaleGainDown->Write();
   diphotonMinvEBEB_k500_energyScaleGainDown->Write();
   diphotonMinvEBEB_k1000_energyScaleGainDown->Write();
   diphotonMinvEBEB_k2000_energyScaleGainDown->Write();
   diphotonMinvEBEB_k3000_energyScaleGainDown->Write();
   diphotonMinvEBEB_k4000_energyScaleGainDown->Write();
   diphotonMinvEBEB_k5000_energyScaleGainDown->Write();

   diphotonMinvEBEE_k0p1_energyScaleGainDown->Write();
   diphotonMinvEBEE_k1_energyScaleGainDown->Write();
   diphotonMinvEBEE_k10_energyScaleGainDown->Write();
   diphotonMinvEBEE_k100_energyScaleGainDown->Write();
   diphotonMinvEBEE_k500_energyScaleGainDown->Write();
   diphotonMinvEBEE_k1000_energyScaleGainDown->Write();
   diphotonMinvEBEE_k2000_energyScaleGainDown->Write();
   diphotonMinvEBEE_k3000_energyScaleGainDown->Write();
   diphotonMinvEBEE_k4000_energyScaleGainDown->Write();
   diphotonMinvEBEE_k5000_energyScaleGainDown->Write();

   diphotonMinvEBEB_k0p1_pileupUp->Write();
   diphotonMinvEBEB_k1_pileupUp->Write();
   diphotonMinvEBEB_k10_pileupUp->Write();
   diphotonMinvEBEB_k100_pileupUp->Write();
   diphotonMinvEBEB_k500_pileupUp->Write();
   diphotonMinvEBEB_k1000_pileupUp->Write();
   diphotonMinvEBEB_k2000_pileupUp->Write();
   diphotonMinvEBEB_k3000_pileupUp->Write();
   diphotonMinvEBEB_k4000_pileupUp->Write();
   diphotonMinvEBEB_k5000_pileupUp->Write();

   diphotonMinvEBEE_k0p1_pileupUp->Write();
   diphotonMinvEBEE_k1_pileupUp->Write();
   diphotonMinvEBEE_k10_pileupUp->Write();
   diphotonMinvEBEE_k100_pileupUp->Write();
   diphotonMinvEBEE_k500_pileupUp->Write();
   diphotonMinvEBEE_k1000_pileupUp->Write();
   diphotonMinvEBEE_k2000_pileupUp->Write();
   diphotonMinvEBEE_k3000_pileupUp->Write();
   diphotonMinvEBEE_k4000_pileupUp->Write();
   diphotonMinvEBEE_k5000_pileupUp->Write();

   diphotonMinvEBEB_k0p1_pileupDown->Write();
   diphotonMinvEBEB_k1_pileupDown->Write();
   diphotonMinvEBEB_k10_pileupDown->Write();
   diphotonMinvEBEB_k100_pileupDown->Write();
   diphotonMinvEBEB_k500_pileupDown->Write();
   diphotonMinvEBEB_k1000_pileupDown->Write();
   diphotonMinvEBEB_k2000_pileupDown->Write();
   diphotonMinvEBEB_k3000_pileupDown->Write();
   diphotonMinvEBEB_k4000_pileupDown->Write();
   diphotonMinvEBEB_k5000_pileupDown->Write();

   diphotonMinvEBEE_k0p1_pileupDown->Write();
   diphotonMinvEBEE_k1_pileupDown->Write();
   diphotonMinvEBEE_k10_pileupDown->Write();
   diphotonMinvEBEE_k100_pileupDown->Write();
   diphotonMinvEBEE_k500_pileupDown->Write();
   diphotonMinvEBEE_k1000_pileupDown->Write();
   diphotonMinvEBEE_k2000_pileupDown->Write();
   diphotonMinvEBEE_k3000_pileupDown->Write();
   diphotonMinvEBEE_k4000_pileupDown->Write();
   diphotonMinvEBEE_k5000_pileupDown->Write();

   diphotonMinvEBEB_k0p1_effUp->Write();
   diphotonMinvEBEB_k1_effUp->Write();
   diphotonMinvEBEB_k10_effUp->Write();
   diphotonMinvEBEB_k100_effUp->Write();
   diphotonMinvEBEB_k500_effUp->Write();
   diphotonMinvEBEB_k1000_effUp->Write();
   diphotonMinvEBEB_k2000_effUp->Write();
   diphotonMinvEBEB_k3000_effUp->Write();
   diphotonMinvEBEB_k4000_effUp->Write();
   diphotonMinvEBEB_k5000_effUp->Write();

   diphotonMinvEBEE_k0p1_effUp->Write();
   diphotonMinvEBEE_k1_effUp->Write();
   diphotonMinvEBEE_k10_effUp->Write();
   diphotonMinvEBEE_k100_effUp->Write();
   diphotonMinvEBEE_k500_effUp->Write();
   diphotonMinvEBEE_k1000_effUp->Write();
   diphotonMinvEBEE_k2000_effUp->Write();
   diphotonMinvEBEE_k3000_effUp->Write();
   diphotonMinvEBEE_k4000_effUp->Write();
   diphotonMinvEBEE_k5000_effUp->Write();

   diphotonMinvEBEB_k0p1_effDown->Write();
   diphotonMinvEBEB_k1_effDown->Write();
   diphotonMinvEBEB_k10_effDown->Write();
   diphotonMinvEBEB_k100_effDown->Write();
   diphotonMinvEBEB_k500_effDown->Write();
   diphotonMinvEBEB_k1000_effDown->Write();
   diphotonMinvEBEB_k2000_effDown->Write();
   diphotonMinvEBEB_k3000_effDown->Write();
   diphotonMinvEBEB_k4000_effDown->Write();
   diphotonMinvEBEB_k5000_effDown->Write();

   diphotonMinvEBEE_k0p1_effDown->Write();
   diphotonMinvEBEE_k1_effDown->Write();
   diphotonMinvEBEE_k10_effDown->Write();
   diphotonMinvEBEE_k100_effDown->Write();
   diphotonMinvEBEE_k500_effDown->Write();
   diphotonMinvEBEE_k1000_effDown->Write();
   diphotonMinvEBEE_k2000_effDown->Write();
   diphotonMinvEBEE_k3000_effDown->Write();
   diphotonMinvEBEE_k4000_effDown->Write();
   diphotonMinvEBEE_k5000_effDown->Write();
}
