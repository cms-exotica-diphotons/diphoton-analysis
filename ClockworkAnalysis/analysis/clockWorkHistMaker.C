#define clockWorkHistMaker_cxx
#include "clockWorkHistMaker.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <memory>

void clockWorkHistMakerBase::Loop() {};

class clockWorkHistMaker : public clockWorkHistMakerBase {

public:
  using clockWorkHistMakerBase::clockWorkHistMakerBase;
  void Loop() {};
  void Loop(std::string run, std::string kVal, std::string lambdaT, std::string negInt);

};


void clockWorkHistMaker::Loop(std::string run, std::string kVal, std::string lambdaT, std::string negInt)
{
   std::cout << "\nRun Configuration: " << run << "; kVal: " << kVal << "; lambdaT: " << lambdaT << "; negInt: "  << negInt << std::endl;

   TString fileout_name = "Test" + run + "_k-" + kVal + "_LT-" + negInt + "_LT-" + lambdaT + ".root";
   std::cout << fileout_name << std::endl;

   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
