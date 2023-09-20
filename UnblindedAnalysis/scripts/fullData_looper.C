#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TSystem.h"
#include "TString.h"
#include "TStopwatch.h"
#include <iostream>

//#include "diphoton-analysis/UnblindedAnalysis/analysis/fullDataHistMaker.C"
#include "../analysis/fullDataHistMaker.C"

using namespace std;

void fullData_looper(int run){

  // use stopwatch for timing
  TStopwatch sw;
  sw.Start();

  // select tree
  TString tree = "diphoton/fTree";
  cout << "Using tree: " << tree << endl;

  // ntuple path (change as needed)
  // TString ntuple_path("root://cmseos.fnal.gov//store/user/cawest/");
  //TString baseDirectory("root://cmseos.fnal.gov/");
  TString baseDirectory("root://eoscms//eos/cms"); // lxplus baseDir
      ///store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016H_v1_0.root

  // create tchain of all files to loop over
  TChain *chain = new TChain(tree);

  if (run == 2016) {
      std::cout << "Chaining 2016 files: " << std::endl;
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016B_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016C_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016D_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016E_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016F_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016G_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016H_v1_0.root*");
  }

  if (run == 2017) {
     std::cout << "Chaining 2017 files: " << std::endl;
     chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2017/Run2017B_v1_0.root*");
     chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2017/Run2017C_v1_0.root*");
     chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2017/Run2017D_v1_0.root*");
     chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2017/Run2017E_v1_0.root*");
     chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2017/Run2017F_v1_0.root*");
  }

  if (run == 2018) {
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018A_v2_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018A_v2_1.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018A_v2_2.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018A_v2_3.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018A_v2_4.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018A_v2_5.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018B_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018B_v1_1.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018B_v1_2.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018C_v1_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018C_v1_1.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018C_v1_2.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_0.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_1.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_2.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_3.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_4.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_5.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_6.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_7.root*");
      chain->Add(baseDirectory + "/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2018/Run2018D_v2_8.root*");
  }

// list chain and entries
  chain->ls();
  std::cout << "Total number of entries: " << chain->GetEntries() << std::endl;
  std::cout << "Finished chaining files..." << std::endl;
  std::cout << "Running Event Loop..." << std::endl;

  fullDataHistMaker loop(chain);
  loop.Loop(run);

  // stop stopwatch
  sw.Stop();

  // convert total time to minutes
  std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
