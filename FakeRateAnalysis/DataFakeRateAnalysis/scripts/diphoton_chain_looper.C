#include "diphoton-analysis/FakeRateAnalysis/DataFakeRateAnalysis/analysis/FakeRateAnalysis.C"

#include "TChain.h"
#include "TStopwatch.h"

#include <iostream>

void diphoton_chain_looper(TString run, TString dataset, int npvLow = 0, int npvHigh = 2000) {

  TString ntuple_path("root://cmseos.fnal.gov//store/user/cawest/");

  // use stopwatch to time
  TStopwatch sw;
  sw.Start();

  // create tchain of all files to loop over
  TChain *chain = new TChain("diphoton/fTree");
  // wildcard not supported when using xrootd
  // added ",0" to print correct number of entries, not entries=1234567890
  // chain->Add("root://cmsxrootd.fnal.gov//store/user/skaplan/noreplica/FakeRateMerged/JetHT_Run2015C_25ns-16Dec2015-v1_MINIAOD/mergedFakeRateNtuple.root",0);
  // chain->Add("root://cmsxrootd.fnal.gov//store/user/skaplan/noreplica/FakeRateMerged/JetHT_Run2015D-16Dec2015-v1_MINIAOD/mergedFakeRateNtuple.root",0);
  // chain->Add("root://cmseos.fnal.gov//store/user/abuccill/DiPhotonAnalysis/FakeRateMerged/diphoton_fakeRate_JetHT_Run2015C_25ns-16Dec2015-v1_MINIAOD_merged.root",0);
  // chain->Add("root://cmseos.fnal.gov//store/user/abuccill/DiPhotonAnalysis/FakeRateMerged/diphoton_fakeRate_JetHT_Run2015D-16Dec2015-v1_MINIAOD_merged.root",0);
  // chain->Add("root://cmseos.fnal.gov//store/user/skaplan/noreplica/AlternativeDenomDefNtuples/Merged/JetHT_Run2015C_25ns-16Dec2015-v1_MINIAOD_DENOM2/merged.root",0);
  // chain->Add("root://cmseos.fnal.gov//store/user/skaplan/noreplica/AlternativeDenomDefNtuples/Merged/JetHT_Run2015D-16Dec2015-v1_MINIAOD_DENOM2/merged.root",0);
  // chain->Add("root://cmseos.fnal.gov//store/user/skaplan/noreplica/FakeRate/WithTriggerAndJetInfo/JetHT_Run2015C_15Dec2015ReReco.root",0);
  // chain->Add("root://cmseos.fnal.gov//store/user/skaplan/noreplica/FakeRate/WithTriggerAndJetInfo/JetHT_Run2015D_15Dec2015ReReco.root",0);
  if(dataset=="jetht") {
    if(run=="2015") {
      chain->Add("root://cmseos.fnal.gov//store/user/skaplan/noreplica/FakeRate/crab3_morejets/JetHT_Run2015C.root",0);
      chain->Add("root://cmseos.fnal.gov//store/user/skaplan/noreplica/FakeRate/crab3_morejets/JetHT_Run2015D.root",0);
    }
    if(run=="Run2016B" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2016B-17Jul2018_ver2-v2__MINIAOD/191215_031812/0000/*.root");
    }
    if(run=="Run2016C" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2016C-17Jul2018-v1__MINIAOD/191215_031829/0000/*.root");
    }
    if(run=="Run2016D" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2016D-17Jul2018-v1__MINIAOD/191215_031844/0000/*.root");
    }
    if(run=="Run2016E" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2016E-17Jul2018-v1__MINIAOD/191215_031901/0000/*.root");
    }
    if(run=="Run2016F" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2016F-17Jul2018-v1__MINIAOD/191215_031931/0000/*.root");
    }
    if(run=="Run2016G" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2016G-17Jul2018-v1__MINIAOD/191215_031946/0000/*.root");
    }
    if(run=="Run2016H" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2016H-17Jul2018-v1__MINIAOD/191215_032003/0000/*.root");
    }
    if(run=="Run2017B" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2017B-31Mar2018-v1__MINIAOD/191215_024050/0000/*.root");
    }
    if(run=="Run2017C" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2017C-31Mar2018-v1__MINIAOD/191215_024106/0000/*.root");
    }
    if(run=="Run2017D" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2017D-31Mar2018-v1__MINIAOD/191215_024123/0000/*.root");
    }
    if(run=="Run2017E" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2017E-31Mar2018-v1__MINIAOD/191215_024141/0000/*.root");
    }
    if(run=="Run2017F" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2017F-31Mar2018-v1__MINIAOD/191215_024158/0000/*.root");
    }
    if(run=="Run2018A" or run=="2018") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018A-17Sep2018-v1__MINIAOD/191211_030324/0000/*.root",0);
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018A-17Sep2018-v1__MINIAOD/191211_030324/0001/*.root",0);
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018A-17Sep2018-v1__MINIAOD/191211_030324/0002/*.root",0);
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018A-17Sep2018-v1__MINIAOD/191211_030324/0003/*.root",0);
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018A-17Sep2018-v1__MINIAOD/191211_030324/0004/*.root",0);
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018A-17Sep2018-v1__MINIAOD/191211_030324/0005/*.root",0);
    }
    if(run=="Run2018Aprompt" or run=="2018prompt") {
      chain->Add(ntuple_path + "JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181130_211700/0000/*.root");
      chain->Add(ntuple_path + "JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181130_211700/0001/*.root");
      chain->Add(ntuple_path + "JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181130_211700/0002/*.root");
      chain->Add(ntuple_path + "JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181130_211700/0003/*.root");
      chain->Add(ntuple_path + "JetHT/crab_JetHT__Run2018A-PromptReco-v2__MINIAOD/181130_211716/0000/*.root");
      chain->Add(ntuple_path + "JetHT/crab_JetHT__Run2018A-PromptReco-v3__MINIAOD/181130_211731/0000/*.root");
      chain->Add(ntuple_path + "JetHT/crab_JetHT__Run2018A-PromptReco-v3__MINIAOD/181130_211731/0001/*.root");
    }
    if(run=="Run2018B" or run=="2018") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018B-17Sep2018-v1__MINIAOD/191211_030359/0000/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018B-17Sep2018-v1__MINIAOD/191211_030359/0001/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018B-17Sep2018-v1__MINIAOD/191211_030359/0002/*.root");
    }
    if(run=="Run2018Bprompt" or run=="2018prompt") {
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018B-PromptReco-v1__MINIAOD/181130_211747/0000/*.root");
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018B-PromptReco-v1__MINIAOD/181130_211747/0001/*.root");
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018B-PromptReco-v1__MINIAOD/181130_211747/0002/*.root");
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018B-PromptReco-v2__MINIAOD/181130_211801/0000/*.root");
    }
    if(run=="Run2018C" or run=="2018") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018C-17Sep2018-v1__MINIAOD/191211_030430/0000/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018C-17Sep2018-v1__MINIAOD/191211_030430/0001/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/JetHT/crab_JetHT__Run2018C-17Sep2018-v1__MINIAOD/191211_030430/0002/*.root");
    }
    if(run=="Run2018Cprompt" or run=="2018prompt") {
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018C-PromptReco-v1__MINIAOD/181130_211816/0000/*.root");
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018C-PromptReco-v2__MINIAOD/181130_211830/0000/*.root");
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018C-PromptReco-v2__MINIAOD/181130_211830/0001/*.root");
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018C-PromptReco-v3__MINIAOD/181130_211845/0000/*.root");
      chain->Add(ntuple_path + "/JetHT/crab_JetHT__Run2018C-PromptReco-v3__MINIAOD/181130_211845/0001/*.root");
    }
    if(run=="Run2018D" or run=="2018" or run=="2018prompt") {
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0000/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0001/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0002/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0003/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0004/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0005/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0006/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0007/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/211012_034356/0008/*.root");
    }
  }
  if(dataset=="doublemuon") {
    if(run=="Run2016B" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2016B-17Jul2018_ver2-v1__MINIAOD/191215_031623/0000/*.root");
    }
    if(run=="Run2016C" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2016C-17Jul2018-v1__MINIAOD/191215_031638/0000/*.root");
    }
    if(run=="Run2016D" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2016D-17Jul2018-v1__MINIAOD/191215_031653/0000/*.root");
    }
    if(run=="Run2016E" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2016E-17Jul2018-v1__MINIAOD/191215_031708/0000/*.root");
    }
    if(run=="Run2016F" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2016F-17Jul2018-v1__MINIAOD/191215_031725/0000/*.root");
    }
    if(run=="Run2016G" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2016G-17Jul2018-v1__MINIAOD/191215_031741/0000/*.root");
    }
    if(run=="Run2016H" or run=="2016") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2016H-17Jul2018-v1__MINIAOD/191215_031755/0000/*.root");
    }
    if(run=="Run2017B" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2017B-31Mar2018-v1__MINIAOD/191215_024217/0000/*.root");
    }
    if(run=="Run2017C" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2017C-31Mar2018-v1__MINIAOD/191215_024233/0000/*.root");
    }
    if(run=="Run2017D" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2017D-31Mar2018-v1__MINIAOD/191215_024251/0000/*.root");
    }
    if(run=="Run2017E" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2017E-31Mar2018-v1__MINIAOD/191215_024310/0000/*.root");
    }
    if(run=="Run2017F" or run=="2017") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2017F-31Mar2018-v1__MINIAOD/191215_024328/0000/*.root");
    }
    if(run=="Run2018A" or run=="2018") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018A-17Sep2018-v2__MINIAOD/191211_030607/0000/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018A-17Sep2018-v2__MINIAOD/191211_030607/0001/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018A-17Sep2018-v2__MINIAOD/191211_030607/0002/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018A-17Sep2018-v2__MINIAOD/191211_030607/0003/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018A-17Sep2018-v2__MINIAOD/191211_030607/0004/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018A-17Sep2018-v2__MINIAOD/191211_030607/0005/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018A-17Sep2018-v2__MINIAOD_recovery/191220_180437/0000/*.root");
    }
    if(run=="Run2018Aprompt" or run=="2018prompt") {
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018A-PromptReco-v1__MINIAOD/181128_204823/0000/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018A-PromptReco-v1__MINIAOD/181128_204823/0001/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018A-PromptReco-v1__MINIAOD/181128_204823/0002/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018A-PromptReco-v1__MINIAOD/181128_204823/0003/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018A-PromptReco-v2__MINIAOD/181128_213957/0000/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018A-PromptReco-v3__MINIAOD/181128_214013/0000/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018A-PromptReco-v3__MINIAOD/181128_214013/0001/*.root");
    }
    if(run=="Run2018B" or run=="2018") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018B-17Sep2018-v1__MINIAOD/191211_030628/0000/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018B-17Sep2018-v1__MINIAOD/191211_030628/0001/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018B-17Sep2018-v1__MINIAOD/191211_030628/0002/*.root");
    }
    if(run=="Run2018Bprompt" or run=="2018prompt") {
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018B-PromptReco-v1__MINIAOD/181128_214030/0000/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018B-PromptReco-v1__MINIAOD/181128_214030/0001/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018B-PromptReco-v1__MINIAOD/181128_214030/0002/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018B-PromptReco-v2__MINIAOD/181128_214045/0000/*.root");
    }
    if(run=="Run2018C" or run=="Run2018Ctest" or run=="2018") {
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018C-17Sep2018-v1__MINIAOD/191211_030652/0000/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018C-17Sep2018-v1__MINIAOD/191211_030652/0001/*.root");
      chain->Add(ntuple_path + "diphoton_fake/23eed66/DoubleMuon/crab_DoubleMuon__Run2018C-17Sep2018-v1__MINIAOD/191211_030652/0002/*.root");
    }
    if(run=="Run2018Cprompt" or run=="2018prompt") {
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018C-PromptReco-v1__MINIAOD/181128_214100/0000/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018C-PromptReco-v2__MINIAOD/181206_015946/0000/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018C-PromptReco-v2__MINIAOD/181206_015946/0001/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018C-PromptReco-v3__MINIAOD/181128_214629/0000/*.root");
      chain->Add(ntuple_path + "/DoubleMuon/crab_DoubleMuon__Run2018C-PromptReco-v3__MINIAOD/181128_214629/0001/*.root");
    }
    if(run=="Run2018D" or run=="2018" or run=="2018prompt") {
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0000/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0001/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0002/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0003/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0004/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0005/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0006/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0007/*.root");
      chain->Add(ntuple_path + "diphoton_fake/012603c/DoubleMuon/crab_DoubleMuon__Run2018D-PromptReco-v2__MINIAOD/211012_045843/0008/*.root");
    }
  }
  chain->ls();
  std::cout << "Total number of entries: " << chain->GetEntries() << std::endl;

  // create instance of class, passing our chain
  FakeRateAnalysis ptl(chain);

  // loop over all entries of our tree
  if(dataset=="jetht") {
    // use matching to leading jet
    //    ptl.Loop(1, run, dataset, npvLow, npvHigh);
    ptl.Loop(0, run, dataset, npvLow, npvHigh);
  }
  else {
    ptl.Loop(0, run, dataset, npvLow, npvHigh);
  }
  // stop stopwatch
  sw.Stop();

  // convert total time to minutes
  std::cout << "RealTime : " << sw.RealTime() / 60.0 << " minutes" << std::endl;
  std::cout << "CPUTime  : " << sw.CpuTime()  / 60.0 << " minutes" << std::endl;
}
