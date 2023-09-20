#include <iostream>
#include "TFile.h"
#include "TTree.h"


void makeClass() {
  // load representative file
 
  // root://eos<experiment>.cern.ch  
  ///eos/cms/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2017

  TFile *f = TFile::Open("root://eoscms//eos/cms/store/group/phys_exotica/diphoton/fullRun2/hsinyeh/Data/Data2016/Run2016H_v1_0.root"); 
       
  //TFile *f = TFile::Open("root://cmseos.fnal.gov//store/user/cawest/diphoton/516280d/ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAO/220327_195505/0000/out_ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8_RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1_numEvent100_1.root");

  f->ls();

  TTree *tree = (TTree *) f->Get("diphoton/fTree");

  tree->Print();

  cout << "Entries: " << tree->GetEntries() << endl;

  tree->MakeClass("fullDataHistMaker");
}
