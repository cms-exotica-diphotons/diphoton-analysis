#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TSystem.h"
#include "TString.h"
#include "TStopwatch.h"
#include <iostream>

// MakeClass Scripts For Rescaling Event by Event
#include "diphoton-analysis/ClockworkAnalysis/analysis/clockWorkHistMaker.C"

using namespace std;

void clockwork_looper(int run, double lambdaT, int negInt){
  // cout << "\nRun Configuration: " << run << "; kVal: " << kVal << "; lambdaT: " << lambdaT << "; negInt: "  << negInt << endl;

  // use stopwatch for timing
  TStopwatch sw;
  sw.Start();

  // select tree
  TString tree = "diphoton/fTree";
  cout << "Using tree: " << tree << endl;
  // ntuple path (change as needed)
  // TString ntuple_path("root://cmseos.fnal.gov//store/user/cawest/");
  TString baseDirectory("root://cmseos.fnal.gov/");

  // create tchain of all files to loop over
  TChain *chain = new TChain(tree);
  // double lT = std::stod(lambdaT);
  double lT = lambdaT;

  if (run == 2016) {
      std::cout << "Chaining 2016 files: " << std::endl;
      if (negInt == 0 && lT == 10000) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_195505/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_195527/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIA/220327_195548/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_195611/0000/*.root");
      }
      if (negInt == 0 && lT == 11000) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_195632/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_195654/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIA/220327_195716/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_195738/0000/*.root");
      }
      if (negInt == 0 && lT == 13000) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_195800/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_195821/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIA/220327_195843/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_195904/0000/*.root");
      }
      if (negInt == 0 && lT == 4000) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_195926/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_195948/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200009/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_200031/0000/*.root");
      }
      if (negInt == 0 && lT == 4500) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200053/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200114/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200138/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_200200/0000/*.root");
      }
      if (negInt == 0 && lT == 5000) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200221/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200243/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200306/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_200327/0000/*.root");
      }
      if (negInt == 0 && lT == 5500) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200348/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200410/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200430/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_200456/0000/*.root");
      }
      if (negInt == 0 && lT == 6000) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200517/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200537/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200601/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_200622/0000/*.root");
      }
      if (negInt == 0 && lT == 6500) {
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200642/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200704/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200726/0000/*.root");
        chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_200746/0000/*.root");
     }
     if (negInt == 0 && lT == 7000) {
       chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200808/0000/*.root");
       chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200829/0000/*.root");
       chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200850/0000/*.root");
       chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_200911/0000/*.root");
     }
     if (negInt == 0 && lT == 7500) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200932/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_200953/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201015/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_201036/0000/*.root");
     }
    if (negInt == 0 && lT == 8000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201057/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201119/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201140/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_201201/0000/*.root");
    }
    if (negInt == 0 && lT == 9000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201222/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201244/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201305/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_201327/0000/*.root");
    }
    if (negInt == 1 && lT == 10000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_201350/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_201411/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIA/220327_201433/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201456/0000/*.root");
    }
    if (negInt == 1 && lT == 11000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_201519/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_201542/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIA/220327_201604/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201624/0000/*.root");
    }
    if (negInt == 1 && lT == 13000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_201647/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_201708/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIA/220327_201729/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201751/0000/*.root");
    }
    if (negInt == 1 && lT == 4000) {
      std::cout << "Chaining NegInt1 LambdaT=4000 files. " << std::endl;
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201812/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201833/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201855/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_201916/0000/*.root");
    }
    if (negInt == 1 && lT == 4500) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_201938/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202001/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202023/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_202044/0000/*.root");
    }
    if (negInt == 1 && lT == 5000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202106/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202127/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202148/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_202210/0000/*.root");
    }
    if (negInt == 1 && lT == 5500) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202232/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202252/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202314/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_202334/0000/*.root");
    }
    if (negInt == 1 && lT == 6000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202355/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202416/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202437/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_202459/0000/*.root");
    }
    if (negInt == 1 && lT == 6500) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202521/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202545/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202606/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_202627/0000/*.root");
    }
    if (negInt == 1 && lT == 7000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202648/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202708/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202732/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_202754/0000/*.root");
    }
    if (negInt == 1 && lT == 7500) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202815/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202837/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202859/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_202919/0000/*.root");
    }
    if (negInt == 1 && lT == 8000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_202950/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203011/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203032/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_203054/0000/*.root");
    }
    if (negInt == 1 && lT == 8500) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203115/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203135/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203157/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_203219/0000/*.root");
    }
    if (negInt == 1 && lT == 9000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203239/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203301/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAOD/220327_203323/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODS/220327_203343/0000/*.root");
    }

    // SM LO background
    if (negInt == 1 && lT == 100000) {
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/efcd821/GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/220523_204152/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/efcd821/GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/220518_194439/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/efcd821/GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/220517_043247/0000/*.root");
      chain->Add(baseDirectory + "/store/user/cawest/diphoton/efcd821/GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/220517_043812/0000/*.root");

    // // this sample contains an ad-hoc modification of the weights from TuneCUETPM1 to TuneCP2
    // TChain *chGG70_2016_reweight = new TChain(treeType);
    // chGG70_2016_reweight->Add(baseDirectory + "/store/user/cawest/diphoton/a847742/GG_M-500To1000_Pt70_TuneCUEP8M1_13TeV-pythia8/crab_GG_M-500To1000_Pt70_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM_resub/220422_071406/output_no_gg_v2.root");
    // chGG70_2016_reweight->Add(baseDirectory + "/store/user/cawest/diphoton/8e010ef/GG_M-1000To2000_Pt70_TuneCUEP8M1_13TeV-pythia8/crab_GG_M-1000To2000_Pt70_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/220228_152825/output_no_gg_v2.root");
    // chGG70_2016_reweight->Add(baseDirectory + "/store/user/cawest/diphoton/8e010ef/GG_M-2000To4000_Pt70_TuneCUEP8M1_13TeV-pythia8/crab_GG_M-2000To4000_Pt70_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/220228_152847/output_no_gg_v2.root");
    // chGG70_2016_reweight->Add(baseDirectory + "/store/user/cawest/diphoton/8e010ef/GG_M-4000To13000_Pt70_TuneCUEP8M1_13TeV-pythia8/crab_GG_M-4000To13000_Pt70_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/220311_193622/output_no_gg_v2.root");
  }
}

if (run == 2017) {
  if (negInt == 0 && lT == 10000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003250/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003306/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003321/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003337/0000/*.root");
  }
  if (negInt == 0 && lT == 11000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003353/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003420/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003437/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003454/0000/*.root");
  }
  if (negInt == 0 && lT == 13000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003509/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003524/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003540/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003559/0000/*.root");
  }
  if (negInt == 0 && lT == 4000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003615/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003631/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003646/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003706/0000/*.root");
  }
  if (negInt == 0 && lT == 4500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003721/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003737/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003759/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003816/0000/*.root");
  }
  if (negInt == 0 && lT == 5000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003832/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003851/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003908/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003924/0000/*.root");
  }
  if (negInt == 0 && lT == 5500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003941/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004001/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004017/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004033/0000/*.root");
  }
  if (negInt == 0 && lT == 6000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004101/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004117/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004136/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004151/0000/*.root");
  }
  if (negInt == 0 && lT == 6500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004217/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004233/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004258/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004315/0000/*.root");
  }
  if (negInt == 0 && lT == 7000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004331/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004347/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004410/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004426/0000/*.root");
  }
  if (negInt == 0 && lT == 7500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004442/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004503/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004520/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004538/0000/*.root");
  }
  if (negInt == 0 && lT == 8000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004553/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004611/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004628/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004651/0000/*.root");
  }
  if (negInt == 0 && lT == 9000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004709/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004724/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004744/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004758/0000/*.root");
  }
  if (negInt == 1 && lT == 10000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004815/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004834/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004850/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004905/0000/*.root");
  }
  if (negInt == 1 && lT == 11000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004920/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004942/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004958/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005021/0000/*.root");
  }
  if (negInt == 1 && lT == 13000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005039/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005054/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005111/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005125/0000/*.root");
  }
  if (negInt == 1 && lT == 4000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005141/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005156/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005212/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005230/0000/*.root");
  }
  if (negInt == 1 && lT == 4500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005247/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005303/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005319/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005334/0000/*.root");
  }
  if (negInt == 1 && lT == 5000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005350/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005405/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005421/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005437/0000/*.root");
  }
  if (negInt == 1 && lT == 5500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005452/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005509/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005525/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005541/0000/*.root");
  }
  if (negInt == 1 && lT == 6000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005556/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005612/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005632/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005656/0000/*.root");
  }
  if (negInt == 1 && lT == 6500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005723/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005742/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005758/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005815/0000/*.root");
  }
  if (negInt == 1 && lT == 7000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005831/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005849/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005904/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005920/0000/*.root");
  }
  if (negInt == 1 && lT == 7500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005937/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005955/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010015/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010040/0000/*.root");
  }
  if (negInt == 1 && lT == 8000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010059/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010115/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010130/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010146/0000/*.root");
  }
  if (negInt == 1 && lT == 8500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010203/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010219/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010234/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010249/0000/*.root");
  }
  if (negInt == 1 && lT == 9000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010306/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010322/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010337/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010354/0000/*.root");
  }

  // SM LO background
  if (negInt == 1 && lT == 100000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_233628/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_213442/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_213509/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_213535/0000/*.root");
  }
}

if (run == 2018) {
  if (negInt == 0 && lT == 10000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184742/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184815/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184849/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184921/0000/*.root");
  }
  if (negInt == 0 && lT == 11000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185006/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185037/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185106/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185129/0000/*.root");
  }
  if (negInt == 0 && lT == 13000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185200/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185224/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185318/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To12990_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To12990_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185246/0000/*.root");
  }
  if (negInt == 0 && lT == 4000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185415/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185452/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185534/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185605/0000/*.root");
  }
  if (negInt == 0 && lT == 4500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185639/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185706/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185748/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185840/0000/*.root");
  }
  if (negInt == 0 && lT == 5000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185910/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185958/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190041/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190118/0000/*.root");
  }
  if (negInt == 0 && lT == 5500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190212/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190253/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190344/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190412/0000/*.root");
  }
  if (negInt == 0 && lT == 6000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190509/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190546/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190632/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190653/0000/*.root");
  }
  if (negInt == 0 && lT == 6500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190759/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190835/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190859/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190939/0000/*.root");
  }
  if (negInt == 0 && lT == 7000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191014/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191046/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191118/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191153/0000/*.root");
  }
  if (negInt == 0 && lT == 7500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191243/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191315/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191403/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191435/0000/*.root");
  }
  if (negInt == 0 && lT == 8000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191541/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191615/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191716/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191747/0000/*.root");
  }
  if (negInt == 0 && lT == 9000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191852/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191926/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192022/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192101/0000/*.root");
  }
  if (negInt == 1 && lT == 10000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192146/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192227/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192307/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192347/0000/*.root");
  }
  if (negInt == 1 && lT == 11000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192428/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192458/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192558/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192641/0000/*.root");
  }
  if (negInt == 1 && lT == 13000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192719/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192759/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192920/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To12990_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To12990_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192832/0000/*.root");
  }
  if (negInt == 1 && lT == 4000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192944/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193049/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193145/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193254/0000/*.root");
  }
  if (negInt == 1 && lT == 4500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193351/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193446/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193600/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193645/0000/*.root");
  }
  if (negInt == 1 && lT == 5000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193745/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193827/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193914/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194020/0000/*.root");
  }
  if (negInt == 1 && lT == 5500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194113/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194145/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194222/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194301/0000/*.root");
  }
  if (negInt == 1 && lT == 6000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194353/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194431/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194523/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194605/0000/*.root");
  }
  if (negInt == 1 && lT == 6500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194653/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194740/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194807/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194856/0000/*.root");
  }
  if (negInt == 1 && lT == 7000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191218_025216/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195022/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195107/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195205/0000/*.root");
  }
  if (negInt == 1 && lT == 7500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195301/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195348/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195424/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195531/0000/*.root");
  }
  if (negInt == 1 && lT == 8000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195607/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195725/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195829/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195929/0000/*.root");
  }
  if (negInt == 1 && lT == 8500) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200038/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200147/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200253/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200351/0000/*.root");
  }
  if (negInt == 1 && lT == 9000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200519/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200610/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200738/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200837/0000/*.root");
  }
  // SM LO background
  if (lT == 100000) {
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213601/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213628/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213653/0000/*.root");
    chain->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213719/0000/*.root");
  }

}
  // list chain and entries
  chain->ls();
  std::cout << "Total number of entries: " << chain->GetEntries() << std::endl;
  std::cout << "Finished chaining files..." << std::endl;
  std::cout << "Running Event Loop..." << std::endl;


  clockWorkHistMaker loop(chain);
  loop.Loop(run, lambdaT, negInt);

  // stop stopwatch
  sw.Stop();

  // convert total time to minutes
  std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
