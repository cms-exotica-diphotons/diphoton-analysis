#include "diphoton-analysis/FakeRateAnalysis/RealTemplateAnalysis/analysis/MCFakeRateAnalysis.C"
#include "diphoton-analysis/Tools/interface/sampleList.hh"
#include "TChain.h"
#include "TStopwatch.h"

#include <iostream>
#include <map>
#include <string>

void diphoton_looper(int year, const std::string & sample, int nPVLow, int nPVHigh, bool isClosureTest=false) {
  TString old_ntuple_path =  "root://cmseos.fnal.gov//store/user/abuccill/diphoton-analysis/fake_rate_real_templates";
  if (isClosureTest) std::cout << "Running Closure Test settings" << std::endl;

  // use stopwatch to time
  TStopwatch sw;
  sw.Start();

  // initialize sample list
  init();

  // create tchain of all files to loop over
  TChain *chain = new TChain("diphoton/fTree");

  // wildcard not supported when using xrootd
  // added ",0" to print correct number of entries, not entries=1234567890
  if (sample == "all" || sample == "GGJets") {
    chain->Add(chains["gg_fake_" + std::to_string(year)]);
  }

  if (sample == "all" || sample == "GJets") {
    chain->Add(chains["gj_fake_" + std::to_string(year)]);
  }

  if (year==2016 && sample == "DiPhotonJets") {
    chain->Add(old_ntuple_path+"/diphoton_fake_rate_real_templates_DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8_76X_MiniAOD_merged.root",0);
  }

  // list chain and entries
  chain->ls();
  std::cout << "Total number of entries: " << chain->GetEntries() << std::endl;

  // create instance of class, passing our chain
  MCFakeRateAnalysis loop(chain);

  // loop over all entries of our tree
  loop.Loop(std::to_string(year), sample, nPVLow, nPVHigh, isClosureTest);

  // stop stopwatch
  sw.Stop();

  // convert total time to minutes
  std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
