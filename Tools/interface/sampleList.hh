// This file defines the samples that are used, the chains that specify their
// locations and basic formatting for the samples.
// It can be used by including the header and then calling
// init()
// to initialize the chains.
#ifndef SAMPLELIST_HH
#define SAMPLELIST_HH

#include "TChain.h"
#include "TSystem.h"

#include <string>
#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include <sys/stat.h>

#include <linux/limits.h>

#include "diphoton-analysis/Tools/interface/tdrstyle.hh"

// 20.3 fb^-1 were acquired in 2018 before loss of HEM15/HEM16
// 59.97 fb^-1 are validated but only 59.28 fb^-1 available in EGamma dataset
std::map<std::string, double> luminosity { {"2015", 2.62}, {"2016", 35.9}, {"2016_legacy", 34.71263}, {"2017", 41.527}, {"2017_legacy", 41.46}, {"2018", 59.67}, {"2018_legacy", 59.83}, {"2018_newjson", 14.00}, {"2018ABC_prompt", 28.04}, {"2018ABC_rereco", 28.04}, {"2018AB", 14.00+7.10}, {"2018ABC", 14.00+7.10+6.94}, {"2018CD", 6.94+31.93}, {"2018D", 31.93}};
//std::map<std::string, double> luminosity { {"2015", 2.62}, {"2016", 35.9}, {"2017", 41.527}, {"2018", 59.67}, {"2018_newjson", 14.00}, {"2018ABC_prompt", 28.04}, {"2018ABC_rereco", 28.04}, {"2018AB", 14.00+7.10}, {"2018ABC", 14.00+7.10+6.94}, {"2018CD", 6.94+31.93}, {"2018D", 31.93}};
std::map<std::string, double> luminosityErrorFrac { {"2015", 0.023}, {"2016", 0.025}, {"2017", 0.023}, {"2018", 0.025}, {"2018_newjson", 0.025}, {"2018ABC_prompt", 0.025}, {"2018ABC_rereco", 0.025}, {"2018AB", 0.025}, {"2018ABC", 0.025}, {"2018CD", 0.025}, {"2018D", 0.025}};

std::map<std::string, TChain*> chains;
std::map<std::string, int> lineStyles;
std::map<std::string, int> lineColors;
std::map<std::string, int> fillStyles;
std::map<std::string, int> fillColors;
std::map<std::string, int> markerColors;
std::map<std::string, std::string> prettyName;

TString filestring(TString sample);
void init(bool includeUnskimmmed, bool includeSignal); // initializes samples; can skip long initialization of unskimmed samples
void initADD2016(const TString & baseDirectory); // initializes 2016 ADD samples; performed by a loop rather than being listed explicitly
void initADD(const TString & baseDirectory); // initializes ADD samples; performed by a loop rather than being listed explicitly
void initRSG(const TString & baseDirectory); // initializes RSG samples; performed by a loop rather than being listed explicitly
void initHeavyHiggs(const TString & baseDirectory); // initializes Heavy Higgs samples; performed by a loop rather than being listed explicitly
void listSamples(); // list the available samples

TString filestring(TString sample)
{
  // paths are defined as symbolic links here
  TString directory(Form("/uscms/homes/c/cawest/links/%s", sample.Data()));
  char resolved_path[PATH_MAX];

  // resolve the symbolic link
  ssize_t r = readlink(directory.Data(), resolved_path, PATH_MAX);
  // if it fails, try filename directly
  if(r==-1) {
    return Form("%s/*.root", directory.Data());
  }
  // if we were successful, convert symbolic link to xrootd path
  else {
    // have to null terminate manually
    resolved_path[r] = '\0';

    // convert AFS path to xrootd path
    TString mypath(resolved_path);
    //    mypath.ReplaceAll("/afs/cern.ch/user/c/cawest/eos/cms", "root://eoscms.cern.ch/");
    mypath.ReplaceAll("/uscms/homes/c/cawest", "root://cmseos.fnal.gov/");
    mypath += "/*.root";
    return mypath;
  }
}

void listSamples()
{
  for(const auto& ichain : chains) {
    std::cout << ichain.first << std::endl;
  }
}

std::vector<std::string> getSampleList()
{
  std::vector<std::string> list;

  for(const auto& ichain : chains) {
    list.push_back(ichain.first);
  }

  return list;
}

void init(bool includeUnskimmed = false, bool includeSignal = false)
{
  TString treeType("diphoton/fTree");
  TString baseDirectory("root://cmseos.fnal.gov/");

  TChain *chData2018_legacy = new TChain(treeType);
  chData2018_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/32581c2/EGamma/crab_EGamma__Run2018A-UL2018_MiniAODv2-v1__MINIAOD_recovery/210621_015117/*.root");
  chData2018_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/32581c2/EGamma/crab_EGamma__Run2018B-UL2018_MiniAODv2-v1__MINIAOD/210618_195040/*.root");
  chData2018_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/32581c2/EGamma/crab_EGamma__Run2018C-UL2018_MiniAODv2-v1__MINIAOD/210618_195114/*.root");
  chData2018_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/32581c2/EGamma/crab_EGamma__Run2018D-UL2018_MiniAODv2-v1__MINIAOD/210618_195149/*.root");

  TChain *chData2018AB_rereco = new TChain(treeType);
  chData2018AB_rereco->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191115_212609/*.root");
  chData2018AB_rereco->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018B-17Sep2018-v1__MINIAOD/191115_212444/*.root");

  TChain *chData2018ABC_rereco = new TChain(treeType);
  chData2018ABC_rereco->Add(chData2018AB_rereco);
  chData2018ABC_rereco->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018C-17Sep2018-v1__MINIAOD/191115_212505/*.root");

  TChain *chData2018_newjson = new TChain(treeType);
  chData2018_newjson->Add(baseDirectory + "/store/user/cawest/diphoton/1d2157e/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191107_231838/*.root");

  TChain *chData2018CD = new TChain(treeType);
  chData2018CD->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018C-17Sep2018-v1__MINIAOD/191115_212505/*.root");
  chData2018CD->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/*.root");

  TChain *chData2018D = new TChain(treeType);
  chData2018D->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/*.root");

  // skimmed version of chData2018_unskimmed
  TChain *chData2018 = new TChain(treeType);
  chData2018->Add(chData2018ABC_rereco);
  chData2018->Add(chData2018D);

  TChain *chData2018ABC_rereco_unskimmed = new TChain(treeType);
  if(includeUnskimmed) {
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191115_212609/0000/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191115_212609/0001/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191115_212609/0002/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191115_212609/0003/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191115_212609/0004/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018A-17Sep2018-v2__MINIAOD/191115_212609/0005/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018B-17Sep2018-v1__MINIAOD/191115_212444/0000/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018B-17Sep2018-v1__MINIAOD/191115_212444/0001/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018B-17Sep2018-v1__MINIAOD/191115_212444/0002/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018C-17Sep2018-v1__MINIAOD/191115_212505/0000/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018C-17Sep2018-v1__MINIAOD/191115_212505/0001/*.root");
    chData2018ABC_rereco_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018C-17Sep2018-v1__MINIAOD/191115_212505/0002/*.root");
  }

  TChain *chData2018_unskimmed = new TChain(treeType);
  if(includeUnskimmed) {
    chData2018_unskimmed->Add(chData2018ABC_rereco_unskimmed);
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0000/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0001/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0002/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0003/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0004/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0005/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0006/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0007/*.root");
    chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/EGamma/crab_EGamma__Run2018D-22Jan2019-v2__MINIAOD/191115_212527/0008/*.root");
  }

  TChain *chDataJetHT2018_unskimmed = new TChain(treeType);
  if(includeUnskimmed) {
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018A-PromptReco-v2__MINIAOD/181109_025710/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018A-PromptReco-v3__MINIAOD/181109_025728/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018A-PromptReco-v3__MINIAOD/181109_025728/0001/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018B-PromptReco-v1__MINIAOD/181109_025746/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018B-PromptReco-v1__MINIAOD/181109_025746/0001/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018B-PromptReco-v1__MINIAOD/181109_025746/0002/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018B-PromptReco-v2__MINIAOD/181109_025803/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018C-PromptReco-v1__MINIAOD/181109_025819/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018C-PromptReco-v2__MINIAOD/181109_025836/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018C-PromptReco-v2__MINIAOD/181109_025836/0001/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018C-PromptReco-v3__MINIAOD/181109_025852/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018C-PromptReco-v3__MINIAOD/181109_025852/0001/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0000/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0001/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0002/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0003/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0004/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0005/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0006/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0007/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0008/*.root");
    chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018D-PromptReco-v2__MINIAOD/181109_025928/0009/*.root");
  }

  TChain *chData = new TChain(treeType);
  chData->Add(filestring("DoubleEG__Run2015D"));
  chData->Add(filestring("DoubleEG__Run2015C_25ns"));

  TChain *chData2017_legacy = new TChain(treeType);
  chData2017_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/9159835/DoubleEG/crab_DoubleEG__Run2017B-UL2017_MiniAODv2-v1__MINIAOD/210808_193425/Run2017B_v1_0.root");
  chData2017_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/9159835/DoubleEG/crab_DoubleEG__Run2017C-UL2017_MiniAODv2-v2__MINIAOD/210808_193452/Run2017C_v2_0.root");
  chData2017_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/9159835/DoubleEG/crab_DoubleEG__Run2017D-UL2017_MiniAODv2-v1__MINIAOD/210808_193519/Run2017D_v1_0.root");
  chData2017_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/9159835/DoubleEG/crab_DoubleEG__Run2017E-UL2017_MiniAODv2-v1__MINIAOD/210808_193546/Run2017E_v1_0.root");
  chData2017_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/9159835/DoubleEG/crab_DoubleEG__Run2017F-UL2017_MiniAODv2-v2__MINIAOD/210808_193612/Run2017F_v2_0.root");

  TChain *chData2017_unskimmed = new TChain(treeType);
  if(includeUnskimmed) {
    chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017B-31Mar2018-v1__MINIAOD/191204_035400/0000/*.root");
    chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017C-31Mar2018-v1__MINIAOD/191204_035423/0000/*.root");
    chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017D-31Mar2018-v1__MINIAOD/191204_035439/0000/*.root");
    chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017E-31Mar2018-v1__MINIAOD/191204_035516/0000/*.root");
    chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017F-31Mar2018-v1__MINIAOD/191204_035540/0000/*.root");
  }

  TChain *chData2017 = new TChain(treeType);
  chData2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017B-31Mar2018-v1__MINIAOD/191204_035400/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017C-31Mar2018-v1__MINIAOD/191204_035423/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017D-31Mar2018-v1__MINIAOD/191204_035439/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017E-31Mar2018-v1__MINIAOD/191204_035516/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2017F-31Mar2018-v1__MINIAOD/191204_035540/*.root");

  TChain *chDataJetHT2017_unskimmed = new TChain(treeType);
  if(includeUnskimmed) {
    chDataJetHT2017_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2017B-31Mar2018-v1__MINIAOD/181109_031018/0000/*.root");
    chDataJetHT2017_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2017C-31Mar2018-v1__MINIAOD/181109_153510/0000/*.root");
    chDataJetHT2017_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2017D-31Mar2018-v1__MINIAOD/181109_153529/0000/*.root");
    chDataJetHT2017_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2017E-31Mar2018-v1__MINIAOD/181109_153547/0000/*.root");
    chDataJetHT2017_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2017F-31Mar2018-v1__MINIAOD/181109_153620/0000/*.root");
  }

  TChain *chData2016_unskimmed = new TChain(treeType);
  if(includeUnskimmed) {
    chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016B-17Jul2018_ver2-v1__MINIAOD/191204_035607/0000/*.root");
    chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016H-17Jul2018-v1__MINIAOD/191204_035845/0000/*.root");
    chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016D-17Jul2018-v1__MINIAOD/191204_035709/0000/*.root");
    chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016E-17Jul2018-v1__MINIAOD/191204_035739/0000/*.root");
    chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016F-17Jul2018-v1__MINIAOD/191204_035805/0000/*.root");
    chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016G-17Jul2018-v1__MINIAOD/191204_035827/0000/*.root");
    chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016C-17Jul2018-v1__MINIAOD/191204_035636/0000/*.root");
  }

  TChain *chData2016 = new TChain(treeType);
  chData2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016B-17Jul2018_ver2-v1__MINIAOD/191204_035607/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016H-17Jul2018-v1__MINIAOD/191204_035845/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016D-17Jul2018-v1__MINIAOD/191204_035709/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016E-17Jul2018-v1__MINIAOD/191204_035739/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016F-17Jul2018-v1__MINIAOD/191204_035805/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016G-17Jul2018-v1__MINIAOD/191204_035827/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DoubleEG/crab_DoubleEG__Run2016C-17Jul2018-v1__MINIAOD/191204_035636/*.root");

  TChain *chData2016_legacy = new TChain(treeType);
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016B-ver2_HIPM_UL2016_MiniAODv2-v1__MINIAOD/210815_152200/Run2016B_ve_0.root");
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016C-HIPM_UL2016_MiniAODv2-v1__MINIAOD/210815_152228/Run2016C_v1_0.root");
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016D-HIPM_UL2016_MiniAODv2-v1__MINIAOD/210815_152254/Run2016D_v1_0.root");
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016E-HIPM_UL2016_MiniAODv2-v1__MINIAOD/210815_152320/Run2016E_v1_0.root");
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016F-HIPM_UL2016_MiniAODv2-v1__MINIAOD/210815_152414/Run2016F_v1_0.root");
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016F-UL2016_MiniAODv2-v1__MINIAOD/210815_152347/Run2016F_v1_0.root");
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016G-UL2016_MiniAODv2-v1__MINIAOD/210818_161240/Run2016G_v1_0.root");
  chData2016_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/acbc6e8/DoubleEG/crab_DoubleEG__Run2016H-UL2016_MiniAODv2-v1__MINIAOD/210815_152441/Run2016H_v1_0.root");

  TChain *chData2017_2018 = new TChain(treeType);
  chData2017_2018->Add(chData2017);
  chData2017_2018->Add(chData2018);

  TChain *chData2016_2017_2018 = new TChain(treeType);
  chData2016_2017_2018->Add(chData2016);
  chData2016_2017_2018->Add(chData2017_2018);

  TChain *chGG_2018 = new TChain(treeType);
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223346/0000/*.root");
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223403/0000/*.root");
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223421/0000/*.root");
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223438/0000/*.root");
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223455/0000/*.root");
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223529/0000/*.root");
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223512/0000/*.root");
  chGG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223548/0000/*.root");

  TChain *chGG_2018_legacy = new TChain(treeType);
  chGG_2018_legacy->Add(baseDirectory + "/store/user/cawest/diphoton/9a8fcf8/DiPhotonJetsBox_MGG-80toInf_13TeV-sherpa/crab_DiPhotonJetsBox_MGG-80toInf_13TeV-sherpa__RunIISummer19UL18MiniAODv2-106X_upgrade2018_realistic_v16/210728_190937/0000/*.root");

  TChain *chGG_fake_2018 = new TChain(treeType);
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MINIAO/191004_223508/0000/*.root");
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MINIA/191004_223521/0000/*.root");
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MINI/191004_220535/0000/*.root");
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MIN/191004_223539/0000/*.root");
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MIN/191004_223551/0000/*.root");
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MIN/191004_223603/0000/*.root");
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MIN/191004_223616/0000/*.root");
  chGG_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic_v15-v1__MI/191004_223627/0000/*.root");

  TChain *chGG_2017 = new TChain(treeType);
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192641/0000/*.root");
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192538/0000/*.root");
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192602/0000/*.root");
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192516/0000/*.root");
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__Fall17_PU2017-v2__MINIAODSIM/191204_192703/0000/*.root");
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__Fall17_PU2017-v2__MINIAODSIM/191204_192721/0000/*.root");
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192620/0000/*.root");
  chGG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192744/0000/*.root");

  TChain *chGG_fake_2017 = new TChain(treeType);
  chGG_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14/191004_223920/0000/*.root");
  chGG_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v1/191004_223843/0000/*.root");
  chGG_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v/191004_223855/0000/*.root");
  chGG_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_/191004_223830/0000/*.root");
  chGG_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_/191004_223934/0000/*.root");
  chGG_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_/191004_223947/0000/*.root");


  TChain *chGG_aMC_2015 = new TChain(treeType);
  chGG_aMC_2015->Add(filestring("DiPhotonJets_MGG-80toInf_2015"));
  TChain *chGG_2016 = new TChain(treeType);
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132250/0000/*.root");
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132307/0000/*.root");
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132321/0000/*.root");
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132340/0000/*.root");
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132354/0000/*.root");
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132412/0000/*.root");
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132427/0000/*.root");
  chGG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/0c6885d/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/201027_132441/0000/*.root");

  TChain *chGG_2016_80X = new TChain(treeType);
  chGG_2016_80X->Add(baseDirectory + "/store/user/cawest/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_/171130_184611/0000/*.root");
  chGG_2016_80X->Add(baseDirectory + "/store/user/cawest/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016/171130_184632/0000/*.root");
  chGG_2016_80X->Add(baseDirectory + "/store/user/cawest/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_201/171130_184657/0000/*.root");
  chGG_2016_80X->Add(baseDirectory + "/store/user/cawest/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184716/0000/*.root");
  chGG_2016_80X->Add(baseDirectory + "/store/user/cawest/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184733/0000/*.root");
  chGG_2016_80X->Add(baseDirectory + "/store/user/cawest/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184751/0000/*.root");
  chGG_2016_80X->Add(baseDirectory + "/store/user/cawest/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184811/0000/*.root");

  TChain *chGG_fake_2016 = new TChain(treeType);
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/201110_050305/0000/*.root");
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v/201110_050319/0000/*.root");
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-/201110_050332/0000/*.root");
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3/201110_050346/0000/*.root");
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3/201110_050400/0000/*.root");
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3/201110_050416/0000/*.root");
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3/201110_050436/0000/*.root");
  chGG_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/20eed6b/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v/201110_050449/0000/*.root");

  TChain *chGG_fake_2016_76X = new TChain(treeType);
  TString old_directory("root://cmseos.fnal.gov//store/user/abuccill/diphoton-analysis/fake_rate_real_templates");
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-60To200_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-200To500_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-500To1000_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-1000To2000_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-2000To4000_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-4000To6000_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-6000To8000_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);
  chGG_fake_2016_76X->Add(old_directory + "/diphoton_fake_rate_real_templates_GGJets_M-8000To13000_Pt-50_13TeV-sherpa_76X_MiniAOD_merged.root",0);

  TChain *chGJ_2018 = new TChain(treeType);
  chGJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18MiniAOD-4cores5k_102X_upgrade2018/191115_223609/0000/*.root");
  chGJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191115_223714/0000/*.root");
  chGJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191115_223627/0000/*.root");
  chGJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191115_223653/0000/*.root");
  chGJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18_ext1-v2__MINIAODSIM/191115_223731/0000/*.root");

  TChain *chGJ_fake_2018 = new TChain(treeType);
  chGJ_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18MiniAOD-102X_upgrade2018_realistic/191004_223718/0000/*.root");
  chGJ_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18MiniAOD-4cores5k_102X_upgrade2018/191004_223640/0000/*.root");
  chGJ_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18MiniAOD-102X_upgrade2018_realisti/191004_223653/0000/*.root");
  chGJ_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18MiniAOD-102X_upgrade2018_realisti/191004_223705/0000/*.root");
  chGJ_fake_2018->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIAutumn18MiniAOD-102X_upgrade2018_realisti/191004_223731/0000/*.root");

  TChain *chGJ_2017 = new TChain(treeType);
  chGJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v2__MINIAODSIM/191204_192805/0000/*.root");
  chGJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_1core_94X/191204_192823/0000/*.root");
  chGJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_192844/0000/*.root");
  chGJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_192908/0000/*.root");
  chGJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_192948/0000/*.root");
  chGJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v2__MINIAODSIM/191204_192931/0000/*.root");

  TChain *chGJ_fake_2017 = new TChain(treeType);
  chGJ_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_1core_94X/191004_224024/0000/*.root");
  chGJ_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc201/191004_224012/0000/*.root");
  chGJ_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc20/191004_224038/0000/*.root");
  chGJ_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc20/191004_224117/0000/*.root");
  chGJ_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc20/191004_224051/0000/*.root");
  chGJ_fake_2017->Add(baseDirectory + "/store/user/cawest/diphoton_fake/14a6c5e/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc20/191004_224105/0000/*.root");

  TChain *chGJ_2016 = new TChain(treeType);
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_194236/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_194212/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_194018/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_193955/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_194107/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_194044/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_194150/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191210_195232/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_194322/0000/*.root");
  chGJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_194257/0000/*.root");

  TChain *chGJ_fake_2016 = new TChain(treeType);
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2_/210608_020235/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2__MINI/210608_020140/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/210608_020438/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2__MIN/210608_020336/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/210608_020629/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2__MIN/210608_020540/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2__MIN/210608_020730/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/210608_020828/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/210608_021025/0000/*.root");
  chGJ_fake_2016->Add(baseDirectory + "/store/user/cawest/diphoton_fake/d41f48f/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_13TeV-MG-PY8__RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2__MIN/210608_020927/0000/*.root");

  TChain *chJJ_2016 = new TChain(treeType);
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT100to200_13TeV-MG-PY8__Summer16MiniAODv3-v1__MINIAODSIM/191204_194710/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT200to300_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_204816/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT200to300_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_204756/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT300to500_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_204904/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT300to500_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_204839/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT500to700_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_204941/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT500to700_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_204925/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT700to1000_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_205004/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT700to1000_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_205020/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1000to1500_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_205051/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1000to1500_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_205108/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1500to2000_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_205146/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1500to2000_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_205128/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT2000toInf_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_205203/0000/*.root");
  chJJ_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT2000toInf_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_205221/0000/*.root");


  TChain *chJJ_2017 = new TChain(treeType);
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017_ext1-v1__MINIAODSIM/191204_193346/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v2__MINIAODSIM/191204_193326/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_193411/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc/191204_193431/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_193452/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_mc/191204_193513/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v2__MINIAODSIM/191204_193541/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc/191204_193559/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_m/191204_193639/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_193620/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_193749/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_new_pmx_94X_/191204_193809/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v2__MINIAODSIM/191204_193830/0000/*.root");
  chJJ_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8__Fall17_PU2017-v2__MINIAODSIM/191204_193852/0000/*.root");

  TChain *chJJ_2018 = new TChain(treeType);
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193415/0000/*.root");
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193433/0000/*.root");
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193452/0000/*.root");
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193512/0000/*.root");
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193531/0000/*.root");
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193555/0000/*.root");
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193613/0000/*.root");
  chJJ_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/191120_193632/0000/*.root");

  TChain *chVG_NLO_2016 = new TChain(treeType);
  chVG_NLO_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__Summer16MiniAODv3_ext1-v1__MINIAODSIM/191204_194508/0000/*.root");
  chVG_NLO_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__Summer16MiniAODv3_ext2-v1__MINIAODSIM/191204_194525/0000/*.root");
  chVG_NLO_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__Summer16MiniAODv3_ext3-v1__MINIAODSIM/191204_194546/0000/*.root");
  chVG_NLO_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__Summer16MiniAODv3_ext1-v1__MINIAODSIM/191204_194604/0000/*.root");

  TChain *chVG_2016 = new TChain(treeType);
  chVG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph/crab_WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph__Summer16MiniAODv3-v2__MINIAODSIM/191204_194648/0000/*.root");
  chVG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph/crab_WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph__Summer16MiniAODv3-v1__MINIAODSIM/191204_194624/0000/*.root");
  chVG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__Summer16MiniAODv3_ext1-v1__MINIAODSIM/191204_194604/0000/*.root");

  TChain *chVG_NLO_2017 = new TChain(treeType);
  chVG_NLO_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8__Fall17_PU2017-v3__MINIAODSIM/191204_193210/0000/*.root");
  chVG_NLO_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8__Fall17_PU2017-v3__MINIAODSIM/191204_193302/0000/*.root");

  TChain *chVG_2017 = new TChain(treeType);
  chVG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph/crab_WGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph__Fall17_PU2017-v3__MINIAODSIM/191204_193008/0000/*.root");
  chVG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph/crab_WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph__Fall17_PU2017-v1__MINIAODSIM/191204_193031/0000/*.root");
  chVG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8__Fall17_PU2017-v3__MINIAODSIM/191204_193302/0000/*.root");

  TChain *chVG_NLO_2018 = new TChain(treeType);
  chVG_NLO_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8__Autumn18_ext1-v1__MINIAODSIM/191120_193213/0000/*.root");
  chVG_NLO_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8__Autumn18_ext1-v2__MINIAODSIM/191120_193251/0000/*.root");

  TChain *chVG_2018 = new TChain(treeType);
  chVG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph/crab_WGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph__Autumn18-v1__MINIAODSIM/191120_193135/0000/*.root");
  chVG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph/crab_WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph__Autumn18-v1__MINIAODSIM/191120_193154/0000/*.root");
  chVG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8__Autumn18_ext1-v2__MINIAODSIM/191120_193251/0000/*.root");

  TChain *chW_2016 = new TChain(treeType);
  chW_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/191204_205240/0000/*.root");
  chW_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_13TeV-MG-PY8__Summer16MiniAODv3_ext2-v2__MINIAODSIM/191204_205304/0000/*.root");

  TChain *chW_2017 = new TChain(treeType);
  chW_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017_ext1-v2__MINIAODSIM/191204_193934/0000/*.root");
  chW_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v3__MINIAODSIM/191204_193914/0000/*.root");

  TChain *chW_2018 = new TChain(treeType);
  chW_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8__Autumn18-v2__MINIAODSIM/191120_193829/0000/*.root");

  TChain *chDY_NLO_2016 = new TChain(treeType);
  chDY_NLO_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8__Summer16MiniAODv3_ext2-v1__MINIAODSIM/191204_194350/0000/*.root");

  TChain *chDY_2016 = new TChain(treeType);
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/200206_144153/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/200206_144153/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/200206_144208/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/200206_144222/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_13TeV-MG-PY8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/200206_144251/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/200206_144237/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600to800_13TeV-MG-PY8__Summer16MiniAODv3-v2__MINIAODSIM/200206_144304/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-800to1200_13TeV-MG-PY8__Summer16MiniAODv3-v1__MINIAODSIM/200206_144320/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-1200to2500_13TeV-MG-PY8__Summer16MiniAODv3-v1__MINIAODSIM/200206_144333/0000/*.root");
  chDY_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-2500toInf_13TeV-MG-PY8__Summer16MiniAODv3-v1__MINIAODSIM/200206_144347/0000/*.root");

  TChain *chDY_NLO_2017 = new TChain(treeType);
  chDY_NLO_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_193132/0000/*.root");
  chDY_NLO_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__Fall17_PU2017_ext1-v1__MINIAODSIM/191204_193148/0000/*.root");

  TChain *chDY_2017 = new TChain(treeType);
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-40to70_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-40to70_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v1__MINIAODSIM/200206_144525/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v1__MINIAODSIM/200206_144541/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr201/200206_144555/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v2__MINIAODSIM/200206_144608/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr201/200206_144623/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr201/200206_144637/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr20/200206_144652/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8__Fall17_PU2017-v1__MINIAODSIM/200206_144706/0000/*.root");
  chDY_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr20/200206_144721/0000/*.root");

  TChain *chDY_NLO_2018 = new TChain(treeType);
  chDY_NLO_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__Autumn18-v1__MINIAODSIM/191120_193318/0000/*.root");
  chDY_NLO_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__Autumn18_ext2-v1__MINIAODSIM/191120_193335/0000/*.root");

  TChain *chDY_2018 = new TChain(treeType);
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v1__MINIAODSIM/200206_025122/0000/*.root");
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v2__MINIAODSIM/200206_025147/0000/*.root");
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v2__MINIAODSIM/200206_025213/0000/*.root");
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v7__MINIAODSIM/200206_025242/0000/*.root");
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v2__MINIAODSIM/200206_025306/0000/*.root");
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v2__MINIAODSIM/200207_163039/0000/*.root");
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v2__MINIAODSIM/200207_162922/0000/*.root");
  chDY_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8__Autumn18-v2__MINIAODSIM/200207_162946/0000/*.root");

  TChain *chTTG_NLO_2016 = new TChain(treeType);
  chTTG_NLO_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/191204_194423/0000/*.root");
  chTTG_NLO_2016->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8__Summer16MiniAODv3_ext1-v2__MINIAODSIM/191204_194445/0000/*.root");

  TChain *chTTG_2016 = new TChain(treeType);
  chTTG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Hadronic_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Hadronic_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8__Summer16MiniAODv3-v1__MIN/200206_144431/0000/*.root");
  chTTG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Hadronic_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Hadronic_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8__Summer16MiniAODv3-v1__MINI/200206_144444/0000/*.root");
  chTTG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_SingleLept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_SingleLept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8__Summer16MiniAODv3-v1__M/200206_144458/0000/*.root");
  chTTG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_SingleLept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_SingleLept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8__Summer16MiniAODv3-v1__MI/200206_144512/0000/*.root");
  chTTG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Dilept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Dilept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8__Summer16MiniAODv3-v1__MINIA/200206_144401/0000/*.root");
  chTTG_2016->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Dilept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Dilept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8__Summer16MiniAODv3-v1__MINIAO/200206_144415/0000/*.root");

  TChain *chTTG_NLO_2017 = new TChain(treeType);
  chTTG_NLO_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__Fall17_PU2017_ext1-v1__MINIAODSIM/191204_193110/0000/*.root");
  chTTG_NLO_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__Fall17_PU2017-v1__MINIAODSIM/191204_193051/0000/*.root");

  TChain *chTTG_2017 = new TChain(treeType);
  chTTG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Hadronic_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Hadronic_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAOD/200206_144805/0000/*.root");
  chTTG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Hadronic_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Hadronic_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAODS/200206_144819/0000/*.root");
  chTTG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_SingleLept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_SingleLept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIA/200206_144833/0000/*.root");
  chTTG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_SingleLept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_SingleLept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAO/200206_144846/0000/*.root");
  chTTG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Dilept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Dilept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAODSIM/200206_144735/0000/*.root");
  chTTG_2017->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Dilept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8/crab_TTGamma_Dilept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8__Fall17_PU2017-v1__MINIAODSIM/200206_144748/0000/*.root");

  TChain *chTTG_NLO_2018 = new TChain(treeType);
  chTTG_NLO_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8/crab_TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8__Autumn18-v1__MINIAODSIM/191120_193353/0000/*.root");

  TChain *chTTG_2018 = new TChain(treeType);
  chTTG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Hadronic_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/crab_TTGamma_Hadronic_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8__Autumn18-v1__MINIAODSIM/200207_171510/0000/*.root");
  chTTG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Hadronic_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/crab_TTGamma_Hadronic_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8__Autumn18-v1__MINIAODSIM/200207_162754/0000/*.root");
  chTTG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_SingleLept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/crab_TTGamma_SingleLept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8__Autumn18-v1__MINIAODSIM/200206_034251/0000/*.root");
  chTTG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_SingleLept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/crab_TTGamma_SingleLept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8__Autumn18-v1__MINIAODSIM/200207_162839/0000/*.root");
  chTTG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Dilept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8/crab_TTGamma_Dilept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8__Autumn18-v1__MINIAODSIM/200206_034106/0000/*.root");
  chTTG_2018->Add(baseDirectory + "/store/user/cawest/diphoton/b399c31/TTGamma_Dilept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8/crab_TTGamma_Dilept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8__Autumn18-v1__MINIAODSIM/200207_162720/0000/*.root");

  // sum of minor backgrounds for use in limit setting
  TChain *chOther_2016 = new TChain(treeType);
  chOther_2016->Add(chVG_2016);
  chOther_2016->Add(chDY_2016);
  chOther_2016->Add(chTTG_2016);
  TChain *chOther_2017 = new TChain(treeType);
  chOther_2017->Add(chVG_2017);
  chOther_2017->Add(chDY_2017);
  chOther_2017->Add(chTTG_2017);
  TChain *chOther_2018 = new TChain(treeType);
  chOther_2018->Add(chVG_2018);
  chOther_2018->Add(chDY_2018);
  chOther_2018->Add(chTTG_2018);

  TChain *chGGGen_2017 = new TChain("diphoton/fSherpaGenTree");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192641/0000/*.root");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192538/0000/*.root");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192602/0000/*.root");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192516/0000/*.root");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__Fall17_PU2017-v2__MINIAODSIM/191204_192703/0000/*.root");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__Fall17_PU2017-v2__MINIAODSIM/191204_192721/0000/*.root");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192620/0000/*.root");
  chGGGen_2017->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__Fall17_PU2017-v1__MINIAODSIM/191204_192744/0000/*.root");

  TChain *chGGGen_2018 = new TChain("diphoton/fSherpaGenTree");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223346/0000/*.root");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223403/0000/*.root");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223421/0000/*.root");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223438/0000/*.root");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223455/0000/*.root");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223529/0000/*.root");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223512/0000/*.root");
  chGGGen_2018->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__Autumn18-v1__MINIAODSIM/191115_223548/0000/*.root");

  TChain *chGGGen_2016 = new TChain("diphoton/fSherpaGenTree");
  chGGGen_2016->Add(baseDirectory + "/store/user/cawest/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184716/0000/*.root");
  chGGGen_2016->Add(baseDirectory + "/store/user/cawest/GGJets_M-2000To4000_Pt-50_13TeV-sherpa/crab_GGJets_M-2000To4000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184733/0000/*.root");
  chGGGen_2016->Add(baseDirectory + "/store/user/cawest/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016/171130_184632/0000/*.root");
  chGGGen_2016->Add(baseDirectory + "/store/user/cawest/GGJets_M-4000To6000_Pt-50_13TeV-sherpa/crab_GGJets_M-4000To6000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184751/0000/*.root");
  chGGGen_2016->Add(baseDirectory + "/store/user/cawest/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_201/171130_184657/0000/*.root");
  chGGGen_2016->Add(baseDirectory + "/store/user/cawest/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_20/171130_184811/0000/*.root");
  chGGGen_2016->Add(baseDirectory + "/store/user/cawest/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_/171130_184611/0000/*.root");

  // These samples are defined in the same way as the SM background in the signal samples.
  // They are needed to take into account interference of the signal with SM backgrounds.
  TChain *chGG70_2016 = new TChain(treeType);
  chGG70_2016->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/GG_M-200To500_Pt-70_13TeV-sherpa/crab_GG_M-200To500_Pt-70_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_015949/0000/*.root");
  chGG70_2016->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/GG_M-500To1000_Pt-70_13TeV-sherpa/crab_GG_M-500To1000_Pt-70_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020043/0000/*.root");
  chGG70_2016->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/GG_M-1000To2000_Pt-70_13TeV-sherpa/crab_GG_M-1000To2000_Pt-70_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_015936/0000/*.root");
  // 94X version of this sample doesn't exist
  chGG70_2016->Add(baseDirectory + "/store/user/cawest/GG_M-2000To4000_Pt-70_13TeV-sherpa/crab_GG_M-2000To4000_Pt-70_13TeV-sherpa__80XMiniAODv2__MINIAODSIM/181106_183756/0000/*.root");
  chGG70_2016->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/GG_M-4000To8000_Pt-70_13TeV-sherpa/crab_GG_M-4000To8000_Pt-70_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020027/0000/*.root");
  chGG70_2016->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/GG_M-8000To13000_Pt-70_13TeV-sherpa/crab_GG_M-8000To13000_Pt-70_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020100/0000/*.root");

  TChain *chGG70_2017 = new TChain(treeType);
  chGG70_2017->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_233628/0000/*.root");
  chGG70_2017->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_213442/0000/*.root");
  chGG70_2017->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_213509/0000/*.root");
  chGG70_2017->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/210715_213535/0000/*.root");

  TChain *chGG70_2018 = new TChain(treeType);
  chGG70_2018->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213601/0000/*.root");
  chGG70_2018->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213628/0000/*.root");
  chGG70_2018->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213653/0000/*.root");
  chGG70_2018->Add(baseDirectory + "/store/user/cawest/diphoton/cba3996/GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8/crab_GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/210715_213719/0000/*.root");

  std::vector<std::string> sampleNames = {"data", "data_2015", "data_2016", "data_2017", "data_2018", "data_2018_newjson", "data_2017_2018", "gg", "gj", "jj", "vg", "w", "dy", "ttg", "gg70", "gg_2016", "gj_2016"};
  // std::vector<std::string> sampleNames = {"data_2018_newjson", "data_2017_2018",  "gg70"};
  // std::vector<std::string> sampleTypes = {"data", "gg", "gj", "jj", "vg", "w", "dy", "ttg"};
  // std::vector<std::string> years = {"2016", "2017", "2018"};
  // for(auto year : years) {
  //   for(auto sampleType : sampleTypes) {
  //     sampleNames.push_back(sampleType + "_" + year);
  //     std::cout << sampleNames.back() << std::endl;
  //   }
  // }

  chains["data_2015"] = chData;
  chains["data_2016_legacy"] = chData2016_legacy;
  chains["data_2016"] = chData2016;
  chains["data_2016_unskimmed"] = chData2016_unskimmed;
  chains["data_2017_legacy"] = chData2017_legacy;
  chains["data_2017"] = chData2017;
  chains["data_2017_unskimmed"] = chData2017_unskimmed;
  chains["data_2018_legacy"] = chData2018_legacy;
  chains["data_2018"] = chData2018;
  chains["data_2018AB"] = chData2018AB_rereco;
  chains["data_2018ABC"] = chData2018ABC_rereco;
  chains["data_2018CD"] = chData2018CD;
  chains["data_2018D"] = chData2018D;
  chains["data_jetht_2017_unskimmed"] = chDataJetHT2017_unskimmed;
  chains["data_jetht_2018_unskimmed"] = chDataJetHT2018_unskimmed;
  chains["data_2018_unskimmed"] = chData2018_unskimmed;
  chains["data_2018_newjson"] = chData2018_newjson;
  chains["data_2017_2018"] = chData2017_2018;
  chains["data_2016_2017_2018"] = chData2016_2017_2018;
  chains["gg_aMC_2015"] = chGG_aMC_2015;
  chains["gg_2018"] = chGG_2018;
  chains["gg_2017"] = chGG_2017;
  chains["gg_2016"] = chGG_2016;
  chains["gg_fake_2018"] = chGG_fake_2018;
  chains["gg_fake_2017"] = chGG_fake_2017;
  chains["gg_fake_2016"] = chGG_fake_2016;
  chains["ggGen"] = chGGGen_2016;
  chains["gg_gen_2016"] = chGGGen_2016;
  chains["gg_gen_2017"] = chGGGen_2017;
  chains["gg_gen_2018"] = chGGGen_2018;
  chains["gj_2018"] = chGJ_2018;
  chains["gj_2017"] = chGJ_2017;
  chains["gj_2016"] = chGJ_2016;
  chains["gj_fake_2018"] = chGJ_fake_2018;
  chains["gj_fake_2017"] = chGJ_fake_2017;
  chains["gj_fake_2016"] = chGJ_fake_2016;
  chains["jj_2018"] = chJJ_2018;
  chains["jj_2017"] = chJJ_2017;
  chains["jj_2016"] = chJJ_2016;
  chains["vg_2018"] = chVG_2018;
  chains["vg_2017"] = chVG_2017;
  chains["vg_2016"] = chVG_2016;
  chains["vg_nlo_2018"] = chVG_NLO_2018;
  chains["vg_nlo_2017"] = chVG_NLO_2017;
  chains["vg_nlo_2016"] = chVG_NLO_2016;
  chains["w_2018"] = chW_2018;
  chains["w_2017"] = chW_2017;
  chains["w_2016"] = chW_2016;
  chains["dy_2018"] = chDY_2018;
  chains["dy_2017"] = chDY_2017;
  chains["dy_2016"] = chDY_2016;
  chains["dy_nlo_2018"] = chDY_NLO_2018;
  chains["dy_nlo_2017"] = chDY_NLO_2017;
  chains["dy_nlo_2016"] = chDY_NLO_2016;
  chains["ttg_2018"] = chTTG_2018;
  chains["ttg_2017"] = chTTG_2017;
  chains["ttg_2016"] = chTTG_2016;
  chains["ttg_nlo_2018"] = chTTG_NLO_2018;
  chains["ttg_nlo_2017"] = chTTG_NLO_2017;
  chains["ttg_nlo_2016"] = chTTG_NLO_2016;
  chains["gg70_2018"] = chGG70_2018;
  chains["gg70_2017"] = chGG70_2017;
  chains["gg70_2016"] = chGG70_2016;
  chains["other_2018"] = chOther_2018;
  chains["other_2017"] = chOther_2017;
  chains["other_2016"] = chOther_2016;

  // signal initialization done separately to avoid clutter
  if(includeSignal) {
    initADD(baseDirectory);
    initRSG(baseDirectory);
    initHeavyHiggs(baseDirectory);
  }

  // set default styles
  for( auto isample : sampleNames ) {
    lineColors[isample] = kBlack;
    fillStyles[isample] = 1001;
    lineStyles[isample] = kSolid;
    markerColors[isample] = kBlack;
  }

  fillColors["data"] = kWhite;
  fillColors["data_2018"] = kWhite;
  fillColors["data_2017"] = kWhite;
  fillColors["data_2016"] = kWhite;
  fillColors["gg"] = kCyan;
  fillColors["gg_aMC_2015"] = kCyan;
  fillColors["gj"] = kBlue;
  fillColors["jj"] = kSpring;
  fillColors["vg"] = kOrange;
  fillColors["w"] = kBlack;
  fillColors["dy"] = kYellow;
  fillColors["ttg"] = kMagenta;
  fillColors["gg70"] = kCyan;

  prettyName["data"]="Data";
  prettyName["data_2015"]="Data (2015)";
  prettyName["data_2016"]="Data (2016)";
  prettyName["data_2017"]="Data (2017)";
  prettyName["data_2018"]="Data (2018)";
  prettyName["data_2017_2018"]="Data (2017+2018)";
  prettyName["data_2016_2017_2018"]="Data (2016-2018)";
  prettyName["data_2016_unskimmed"]="Data (2016)";
  prettyName["data_2017_unskimmed"]="Data (2017)";
  prettyName["data_2018_unskimmed"]="Data (2018)";
  prettyName["data_2018_newjson"]="Data (2018, new JSON)";
  prettyName["gg"]="#gamma#gamma";
  //  prettyName["gg_2016"]="#gamma#gamma (2016)";
  prettyName["gg_aMC_2015"]="#gamma#gamma (aMC@NLO)";
  prettyName["gj"]="#gamma + jets";
  //  prettyName["gj_2016"]="#gamma + jets (2016)";
  prettyName["jj"]="Multijet";
  prettyName["vg"]="V#gamma";
  prettyName["w"]="W";
  prettyName["dy"]="DY";
  prettyName["ttg"]="t#bar{t}#gamma";
  prettyName["gg70"]="Diphoton, p_{T,#gamma} > 70";

  setTDRStyle();
}

void initADD2016(const TString & baseDirectory)
{
  // ADD samples
  std::vector<std::string> MS = {"3000", "3500", "4000", "4500",
				 "5000", "5500", "6000", "7000",
				 "8000", "9000", "10000", "11000"};
  std::vector<std::string> NED = {"2", "4"};
  std::vector<std::string> KK = {"1", "4"};
  std::map<std::string, std::vector<std::string>> MggBins;
  // the 250To500 mass bin is only present for the NED=4, KK=1 sample
  // but it is skipped manually later
  MggBins["3000"] = {"250To500", "500To1000", "1000To2000", "2000To3000"};
  MggBins["3500"] = {"250To500", "500To1000", "1000To2000", "2000To3500"};
  MggBins["4000"] = {"250To500", "500To1000", "1000To2000", "2000To4000"};
  MggBins["4500"] = {"250To500", "500To1000", "1000To2000", "2000To3000", "3000To4500"};
  MggBins["5000"] = {"250To500", "500To1000", "1000To2000", "2000To3000", "3000To5000"};
  MggBins["5500"] = {"250To500", "500To1000", "1000To2000", "2000To4000", "4000To5500"};
  MggBins["6000"] = {"500To1000", "1000To2000", "2000To4000", "4000To6000"};
  MggBins["7000"] = {"500To1000", "1000To2000", "2000To4000", "4000To7000"};
  MggBins["8000"] = {"500To1000", "1000To2000", "2000To4000", "4000To8000"};
  MggBins["9000"] = {"500To1000", "1000To2000", "2000To4000", "4000To9000"};
  MggBins["10000"] = {"500To1000", "1000To2000", "2000To4000", "4000To10000"};
  MggBins["11000"] = {"500To1000", "1000To2000", "2000To4000", "4000To11000"};

  for(const auto& iMS : MS) {
    for(const auto& iNED : NED) {
      for(const auto& iKK : KK) {
	// no samples were generated with KK convention 4
	// and four extra dimensions
	if(strcmp(iKK.c_str(), "4")==0 && strcmp(iNED.c_str(), "4")==0) continue;
	// no samples were generated with negative interference above MS = 6 TeV
	if(iNED=="2" && iKK=="4" && std::stoi(iMS)>6000) continue;
	std::string pointName = "ADDGravToGG_MS-";
	pointName += iMS;
	pointName += "_NED-";
	pointName += iNED;
	pointName += "_KK-";
	pointName += iKK;
	chains[pointName] = new TChain("diphoton/fTree");
	for(std::string iMgg : MggBins[iMS] ) {
	  // the 200To500 bins are only present for the NED=4 samples
	  if(iNED=="2" && iMgg=="250To500") continue;
	  // Hewett- convention samples do not extend past Mgg > 6 TeV
	  std::string sampleName(pointName);
	  sampleName += "_M-";
	  sampleName += iMgg;
	  sampleName += "_13TeV-sherpa";
	  // the following line only works for 80X samples
	  //	  chains[pointName]->Add(filestring(sampleName));
	  lineColors[pointName] = kBlack;
	  fillStyles[pointName] = 1001;
	  lineStyles[pointName] = kSolid;
	}
      }
    }
  }

  chains["ADDGravToGG_MS-10000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191006_233205/0000/*.root");
  chains["ADDGravToGG_MS-10000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020115/0000/*.root");
  chains["ADDGravToGG_MS-10000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-2_KK-1_M-4000To10000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-2_KK-1_M-4000To10000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020128/0000/*.root");
  chains["ADDGravToGG_MS-10000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_020147/0000/*.root");
  chains["ADDGravToGG_MS-10000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020205/0000/*.root");
  chains["ADDGravToGG_MS-10000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_020218/0000/*.root");
  chains["ADDGravToGG_MS-10000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-4_KK-1_M-4000To10000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-4_KK-1_M-4000To10000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020230/0000/*.root");
  chains["ADDGravToGG_MS-10000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-10000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-10000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020243/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191008_123031/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020309/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-2_KK-1_M-4000To11000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-2_KK-1_M-4000To11000_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_020322/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020335/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_020350/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020405/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-4_KK-1_M-4000To11000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-4_KK-1_M-4000To11000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020418/0000/*.root");
  chains["ADDGravToGG_MS-11000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-11000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-11000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020431/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020447/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-2_KK-1_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-2_KK-1_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020504/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020518/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-2_KK-4_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020531/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-2_KK-4_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-2_KK-4_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020545/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-2_KK-4_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-2_KK-4_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020558/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020610/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-4_KK-1_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-4_KK-1_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020625/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-4_KK-1_M-200To500_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-4_KK-1_M-200To500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020640/0000/*.root");
  chains["ADDGravToGG_MS-3000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-3000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020654/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020706/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-2_KK-1_M-2000To3500_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-2_KK-1_M-2000To3500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020719/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020733/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/ADDGravToGG_MS-3500_NED-2_KK-4_M-2000To3500_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-2_KK-4_M-2000To3500_13TeV-sherpa__80XMiniAODv2__MINIAODSIM/181106_181242/0000/*.root");
  // Use old sample because the 94X sample is broken
  chains["ADDGravToGG_MS-3500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-2_KK-4_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_020746/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-2_KK-4_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-2_KK-4_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020817/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020829/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-4_KK-1_M-2000To3500_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-4_KK-1_M-2000To3500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020845/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-4_KK-1_M-200To500_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-4_KK-1_M-200To500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020858/0000/*.root");
  chains["ADDGravToGG_MS-3500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-3500_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-3500_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020910/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020934/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_020951/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_021004/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-2_KK-4_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021034/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-2_KK-4_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-2_KK-4_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021052/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-2_KK-4_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-2_KK-4_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021105/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021117/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021129/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-4_KK-1_M-200To500_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-4_KK-1_M-200To500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021143/0000/*.root");
  chains["ADDGravToGG_MS-4000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-4000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021157/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021210/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-1_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-1_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021225/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-1_M-3000To4500_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-1_M-3000To4500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021242/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021310/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-4_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021327/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-4_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-4_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021355/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-4_M-3000To4500_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-4_M-3000To4500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021407/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-2_KK-4_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-2_KK-4_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021421/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_021437/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-4_KK-1_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-4_KK-1_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021450/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-4_KK-1_M-200To500_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-4_KK-1_M-200To500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021503/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-4_KK-1_M-3000To4500_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-4_KK-1_M-3000To4500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021515/0000/*.root");
  chains["ADDGravToGG_MS-4500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-4500_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-4500_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021528/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021542/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-1_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-1_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021554/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-1_M-3000To5000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-1_M-3000To5000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021607/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021620/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-4_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021634/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-4_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-4_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021647/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-4_M-3000To5000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-4_M-3000To5000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021700/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-2_KK-4_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-2_KK-4_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021712/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021725/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-4_KK-1_M-2000To3000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-4_KK-1_M-2000To3000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021738/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-4_KK-1_M-200To500_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-4_KK-1_M-200To500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021752/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-4_KK-1_M-3000To5000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-4_KK-1_M-3000To5000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021804/0000/*.root");
  chains["ADDGravToGG_MS-5000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-5000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021817/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021829/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021843/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-1_M-4000To5500_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-1_M-4000To5500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021857/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021910/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-4_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-4_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021924/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-4_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-4_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021937/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-4_M-4000To5500_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-4_M-4000To5500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_021950/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-2_KK-4_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-2_KK-4_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022004/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022027/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022103/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-4_KK-1_M-200To500_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-4_KK-1_M-200To500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022117/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-4_KK-1_M-4000To5500_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-4_KK-1_M-4000To5500_13TeV-sherpa__Summer16MiniAODv3-v1__MINIAODSIM/191007_022130/0000/*.root");
  chains["ADDGravToGG_MS-5500_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-5500_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-5500_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022145/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022157/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022210/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-1_M-4000To6000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-1_M-4000To6000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022224/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022237/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-4_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-4_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022250/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-4_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-4_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022303/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-4_M-4000To6000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-4_M-4000To6000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022316/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-2_KK-4"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-2_KK-4_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-2_KK-4_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022330/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022342/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022355/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-4_KK-1_M-200To500_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-4_KK-1_M-200To500_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022411/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-4_KK-1_M-4000To6000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-4_KK-1_M-4000To6000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022424/0000/*.root");
  chains["ADDGravToGG_MS-6000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-6000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-6000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022439/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022506/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022518/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-2_KK-1_M-4000To7000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-2_KK-1_M-4000To7000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022531/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022545/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022558/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022611/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-4_KK-1_M-4000To7000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-4_KK-1_M-4000To7000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022640/0000/*.root");
  chains["ADDGravToGG_MS-7000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-7000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-7000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022654/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022708/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022722/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-2_KK-1_M-4000To8000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-2_KK-1_M-4000To8000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022740/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022753/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022815/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022834/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-4_KK-1_M-4000To8000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-4_KK-1_M-4000To8000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022846/0000/*.root");
  chains["ADDGravToGG_MS-8000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-8000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-8000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022900/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-2_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-2_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022920/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-2_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-2_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022932/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-2_KK-1_M-4000To9000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-2_KK-1_M-4000To9000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_022944/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-2_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-2_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-2_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_023009/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-4_KK-1_M-1000To2000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-4_KK-1_M-1000To2000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_023024/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-4_KK-1_M-2000To4000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-4_KK-1_M-2000To4000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_023036/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-4_KK-1_M-4000To9000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-4_KK-1_M-4000To9000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_023049/0000/*.root");
  chains["ADDGravToGG_MS-9000_NED-4_KK-1"]->Add(baseDirectory + "/store/user/cawest/diphoton/6a01524/ADDGravToGG_MS-9000_NED-4_KK-1_M-500To1000_13TeV-sherpa/crab_ADDGravToGG_MS-9000_NED-4_KK-1_M-500To1000_13TeV-sherpa__Summer16MiniAODv3-v2__MINIAODSIM/191007_023102/0000/*.root");

}

void initADD(const TString & baseDirectory)
{
  initADD2016(baseDirectory);

  // 2017 and 2018 datasets have a different dataset string
  std::vector<int> years = {2017, 2018};
  std::vector<std::string> negint_values = {"0", "1"};
  std::vector<int> lambdaTs = {4000, 4500, 5000, 5500, 6000,
			       6500, 7000, 7500, 8000, 8500,
			       9000, 10000, 11000, 13000};

  for(const auto& year : years) {
    for(const auto& negint_value : negint_values) {
      for(const auto& lambdaT : lambdaTs) {
	// there is no point with neg_int = "0" and lambdaT == 8500
	if(negint_value == "0" && lambdaT == 8500 ) continue;
	std::string pointName = "ADDGravToGG_NegInt-";
	pointName += negint_value;
	pointName += "_LambdaT-";
	pointName += std::to_string(lambdaT);
	pointName += "_TuneCP2_13TeV-pythia8_";
	pointName += std::to_string(year);
	chains[pointName] = new TChain("diphoton/fTree");
	lineColors[pointName] = kBlack;
	fillStyles[pointName] = 1001;
	lineStyles[pointName] = kSolid;
      }
    }
  }

  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003250/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003306/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003321/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003337/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003353/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003420/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003437/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003454/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003509/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003524/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003540/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003559/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003615/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003631/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003646/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003706/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003721/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003737/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003759/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003816/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003832/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003851/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003908/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003924/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_003941/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004001/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004017/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004033/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004101/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004117/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004136/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004151/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004217/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004233/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004258/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004315/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004331/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004347/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004410/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004426/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004442/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004503/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004520/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004538/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004553/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004611/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004628/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004651/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004709/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004724/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004744/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004758/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004815/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004834/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004850/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004905/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004920/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004942/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_004958/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005021/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005039/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005054/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005111/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-13000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005125/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005141/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005156/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005212/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005230/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005247/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005303/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005319/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005334/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005350/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005405/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005421/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005437/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005452/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005509/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005525/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005541/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005556/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005612/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005632/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005656/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005723/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005742/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005758/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005815/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005831/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005849/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005904/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005920/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005937/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_005955/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010015/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010040/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010059/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010115/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010130/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010146/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010203/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010219/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010234/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010249/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010306/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010322/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010337/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010354/0000/*.root");

  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184742/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184815/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184849/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_184921/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185006/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185037/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185106/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185129/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185200/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185224/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-13000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185318/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185415/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185452/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185534/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185605/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185639/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185706/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185748/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185840/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185910/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_185958/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190041/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190118/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190212/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190253/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190344/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190412/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190509/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190546/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190632/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190653/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190759/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190835/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190859/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_190939/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191014/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191046/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191118/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191153/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191243/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191315/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191403/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191435/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191541/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191615/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191716/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191747/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191852/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_191926/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192022/0000/*.root");
  chains["ADDGravToGG_NegInt-0_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192101/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192146/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192227/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192307/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-10000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192347/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192428/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192458/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192558/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-11000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192641/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-13000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192719/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-13000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192759/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-13000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192920/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_192944/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193049/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193145/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193254/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193351/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193446/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193600/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-4500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193645/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193745/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193827/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_193914/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194020/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194113/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194145/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194222/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-5500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194301/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194353/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194431/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194523/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194605/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194653/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194740/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194807/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-6500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_194856/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191218_025216/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195022/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195107/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195205/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195301/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195348/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195424/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-7500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195531/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195607/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195725/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195829/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_195929/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200038/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200147/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200253/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200351/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200519/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200610/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200738/0000/*.root");
  chains["ADDGravToGG_NegInt-1_LambdaT-9000_TuneCP2_13TeV-pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8/crab_ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8__Autumn18-v1__MINIAODSIM/191203_200837/0000/*.root");


}

void initRSG(const TString & baseDirectory)
{
  std::string pointNameBase = "RSGravitonToGammaGamma_kMpl";
  std::vector<std::string> years = {"2016", "2017", "2018"};
  std::vector<std::string> kMpl_values = {"001", "01", "02"};
  std::map<std::string, std::vector<int> > M_bins;
  M_bins["001"] = {750, 1000, 1250, 1500, 1750,
		   2000, 2250, 2500, 2750, 3000,
		   3250, 3500, 4000, 5000};
  M_bins["01"] = {750, 1000, 1250, 1500, 1750,
		  2000, 2250, 2500, 3000, 3500,
		  4000, 4250, 4500, 4750, 5000,
		  5250, 5500, 5750, 6000, 6500,
		  7000, 8000};
  M_bins["02"] = {750, 1000, 1250, 1500, 1750,
		  2000, 2250, 2500, 3000, 3500,
		  4000, 4500, 4750, 5000, 5250,
		  5500, 5750, 6000, 6500, 7000,
		  8000};

  for(const auto& year : years) {
    for(const auto& kMpl_value : kMpl_values) {
      for(const auto& M_bin : M_bins[kMpl_value]) {
	if(year == "2016" && M_bin > 7000) {
	  continue;
	}
	std::string pointName = pointNameBase;
	pointName += kMpl_value;
	pointName += "_M_";
	pointName += std::to_string(M_bin);
	pointName += "_13TeV_pythia8_";
	pointName += year;
	chains[pointName] = new TChain("diphoton/fTree");
	lineColors[pointName] = kBlack;
	fillStyles[pointName] = 1001;
	lineStyles[pointName] = kSolid;
      }
    }
  }
  // comment out 2016 samples with no 2017/2018 counterpart
  // chains["RSGravitonToGammaGamma_kMpl001_M_500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154719/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_740_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-740_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-740_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154843/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_745_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-745_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-745_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154858/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154914/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_755_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-755_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-755_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154930/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_760_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-760_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-760_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154944/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_765_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-765_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-765_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154959/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_770_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-770_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-770_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155014/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-1000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-1000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154335/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1250_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-1250_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-1250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154351/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-1500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-1500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201105_154405/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-1750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-1750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154422/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-2000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-2000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154437/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2250_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-2250_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-2250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154452/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-2500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-2500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154506/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-2750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-2750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154520/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-3000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-3000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154534/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3250_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-3250_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-3250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154549/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-3500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-3500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154603/0000/*.root");
  //  chains["RSGravitonToGammaGamma_kMpl001_M_3750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-3750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-3750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154618/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_4000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-4000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-4000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154634/0000/*.root");
  //  chains["RSGravitonToGammaGamma_kMpl001_M_4500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-4500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-4500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154649/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_5000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-5000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-5000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154703/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_5500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-5500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-5500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154733/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_6000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-6000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-6000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154749/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_6500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-6500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-6500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154805/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl001_M_7000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-001_M-7000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-001_M-7000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_154824/0000/*.root");

  // chains["RSGravitonToGammaGamma_kMpl01_M_500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155351/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl01_M_740_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-740_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-740_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201105_155507/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl01_M_745_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-745_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-745_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155522/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155538/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl01_M_755_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-755_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-755_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155555/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl01_M_760_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-760_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-760_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155609/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl01_M_765_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-765_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-765_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155628/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl01_M_770_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-770_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-770_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155642/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-1000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-1000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155029/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1250_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-1250_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-1250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155043/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-1500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-1500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155058/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-1750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-1750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155113/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-2000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-2000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155129/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2250_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-2250_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-2250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155143/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-2500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-2500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155157/0000/*.root");
  //  chains["RSGravitonToGammaGamma_kMpl01_M_2750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-2750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-2750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155211/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_3000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-3000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-3000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155229/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_3500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-3500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-3500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155245/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-4000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-4000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201105_155259/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-4500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-4500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155316/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-5000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-5000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155335/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-5500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-5500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155406/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_6000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-6000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-6000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155422/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_6500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-6500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-6500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155436/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_7000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-01_M-7000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-01_M-7000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201105_155452/0000/*.root");

  // chains["RSGravitonToGammaGamma_kMpl02_M_500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155824/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl02_M_740_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-740_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-740_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155915/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl02_M_745_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-745_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-745_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155932/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_750_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-750_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155950/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl02_M_755_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-755_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-755_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_160006/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl02_M_760_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-760_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-760_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_160027/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl02_M_765_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-765_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-765_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201105_160043/0000/*.root");
  // chains["RSGravitonToGammaGamma_kMpl02_M_770_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-770_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-770_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_160057/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-1000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-1000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201105_155657/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1500_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-1500_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-1500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155711/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_2000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-2000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-2000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155726/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_3000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-3000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-3000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155740/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_4000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-4000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-4000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155755/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-5000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-5000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155810/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_6000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-6000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-6000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155841/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_7000_13TeV_pythia8_2016"]->Add(baseDirectory + "/store/user/cawest/diphoton/5cf7dd6/RSGravToGG_kMpl-02_M-7000_TuneCUEP8M1_13TeV-pythia8/crab_RSGravToGG_kMpl-02_M-7000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201105_155859/0000/*.root");

  chains["RSGravitonToGammaGamma_kMpl001_M_1000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010412/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010427/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010441/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010457/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010513/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010528/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010543/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010558/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_3000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_3000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010615/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_3250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_3250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010630/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_3500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_3500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010645/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_4000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_4000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_4000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010700/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_5000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_5000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_5000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010718/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010733/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010748/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010808/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010825/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010844/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_2000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_2000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010859/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_2250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_2250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191210_195423/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_2500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_2500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010931/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_3000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_3000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_3000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_010947/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_3500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_3500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_3500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011002/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011018/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011034/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011049/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011104/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011120/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011138/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011154/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011210/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_6000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_6000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_6000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011226/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_6500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_6500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_6500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011248/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_7000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_7000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_7000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011303/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011318/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_8000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_8000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_8000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011335/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011351/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011405/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011421/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011437/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_2000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_2000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_2000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011454/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_2250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_2250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_2250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011508/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_2500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_2500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_2500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011523/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_3000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_3000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_3000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011539/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_3500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_3500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_3500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011556/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_4000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_4000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_4000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011611/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_4500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_4500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_4500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011627/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_4750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_4750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_4750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011644/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011659/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011714/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011731/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011747/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_6000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_6000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_6000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011805/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_6500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_6500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_6500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011821/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_7000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_7000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_7000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011836/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011852/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_8000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_8000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_8000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011909/0000/*.root");

  chains["RSGravitonToGammaGamma_kMpl001_M_1000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_200930/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201033/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201151/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_1750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_1750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_1750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201250/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201339/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201453/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201545/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_2750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_2750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_2750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201629/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_3000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_3000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201722/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_3250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_3250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201759/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_3500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_3500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_3500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201839/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_4000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_4000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_4000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_201954/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_5000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_5000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_5000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202039/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl001_M_750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl001_M_750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl001_M_750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202123/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202200/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202249/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202352/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_1750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_1750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_1750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202455/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_2000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_2000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202535/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_2250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_2250_TuneCP2_13TeV_pythia8__Autumn18-v2__MINIAODSIM/191203_202620/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_2500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_2500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_2500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202801/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_3000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_3000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_3000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202901/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_3500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_3500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_3500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_202949/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203031/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203116/0000/*.root");
  // old version
  chains["RSGravitonToGammaGamma_kMpl01_M_4500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011049/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_4750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_4750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_4750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203313/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203421/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203507/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203558/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_5750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_5750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_5750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203657/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_6000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_6000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_6000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203720/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_6500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_6500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_6500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203820/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_7000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_7000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_7000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_203856/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_204005/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl01_M_8000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl01_M_8000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl01_M_8000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_204123/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_204231/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_204404/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_204450/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_1750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_1750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_1750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_204545/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_2000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_2000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_2000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191203_211018/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_2250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_2250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_2250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191210_035614/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_2500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_2500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_2500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001722/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_3000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_3000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_3000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001741/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_3500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_3500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_3500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001758/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_4000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_4000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_4000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001817/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_4500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_4500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_4500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001839/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_4750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_4750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_4750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001858/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001916/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5250_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001935/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_001953/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_5750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_5750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_5750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_002014/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_6000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_6000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_6000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_002033/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_6500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_6500_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_6500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_002050/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_7000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_7000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_7000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_002109/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_750_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_002128/0000/*.root");
  chains["RSGravitonToGammaGamma_kMpl02_M_8000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/RSGravitonToGammaGamma_kMpl02_M_8000_TuneCP2_13TeV_pythia8/crab_RSGravitonToGammaGamma_kMpl02_M_8000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_002145/0000/*.root");

}

void initHeavyHiggs(const TString & baseDirectory)
{
  std::vector<std::string> years = {"2016", "2017", "2018"};
  std::vector<std::string> W_values = {"0p014", "1p4", "5p6"};
  std::map<std::string, std::vector<int> > M_bins;
  M_bins["0p014"] = {750, 1000, 1250, 1500, 1750,
		     2000, 2250, 2500, 2750, 3000,
		     3250, 3500, 4000, 4500, 5000};
  M_bins["1p4"] = {750, 1000, 1250, 1500, 1750,
		   2000, 2250, 2500, 3000, 3500,
		   4000, 4250, 4500, 4750, 5000};
  M_bins["5p6"] = {750, 1000, 1250, 1500, 1750,
		   2000, 2250, 2500, 3000, 3500,
		   4000, 4500, 4750, 5000};

  for(const auto& year : years) {
    for(const auto& W_value : W_values) {
      for(const auto& M_bin : M_bins[W_value]) {
	std::string pointName = "GluGluSpin0ToGammaGamma_W_";
	pointName += W_value;
	pointName += "_M_";
	pointName += std::to_string(M_bin);
	// tune removed from name as it is different for 2016 and 2017/2018
	pointName += "_13TeV_pythia8_";
	pointName += year;
	chains[pointName] = new TChain("diphoton/fTree");
	lineColors[pointName] = kBlack;
	fillStyles[pointName] = 1001;
	lineStyles[pointName] = kSolid;
      }
    }
  }

  // comment out 2016 samples with no 2017/2018 counterpart
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M_500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031802/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_740_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-740_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-740_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031913/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_745_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-745_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-745_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031926/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_750_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-750_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160019/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_755_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-755_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-755_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201203_031954/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_760_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-760_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-760_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032007/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-1000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-1000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031437/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1250_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-1250_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-1250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031452/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-1500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-1500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_155916/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1750_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-1750_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-1750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_155930/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-2000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-2000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031531/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2250_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-2250_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-2250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_155944/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-2500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-2500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031558/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2750_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-2750_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-2750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031614/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-3000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-3000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031627/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3250_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-3250_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-3250_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031640/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-3500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-3500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031654/0000/*.root");
  //  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3750_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-3750_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-3750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031707/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_4000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-4000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-4000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031721/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_4500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-4500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-4500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031734/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_5000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-5000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-5000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031747/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_5500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-5500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-5500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031815/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_6000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-6000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-6000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031830/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_6500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-6500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-6500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_155959/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_0p014_M_7000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-0p014_M-7000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-0p014_M-7000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_031859/0000/*.root");
  //  chains["GluGluSpin0ToGammaGamma_W_1p4_M_500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160114/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-1000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-1000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032021/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-1500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-1500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160032/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_2000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-2000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-2000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160046/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_3000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-3000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-3000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160059/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-4000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-4000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032113/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_1p4_M_6000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-6000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-6000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160127/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_1p4_M_7000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-1p4_M-7000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-1p4_M-7000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032208/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032519/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_740_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-740_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-740_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160247/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_745_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-745_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-745_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032613/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_750_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-750_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-750_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032626/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_755_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-755_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-755_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032640/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_760_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-760_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-760_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201204_163039/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_760_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-760_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-760_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160300/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_765_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-765_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-765_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032708/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_770_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-770_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-770_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_021200/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-1000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-1000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160220/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1500_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-1500_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-1500_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v1__MINIAODSIM/201203_032411/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_2000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-2000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-2000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032425/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_3000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-3000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-3000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032438/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_4000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-4000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-4000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201217_160234/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_5000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-5000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-5000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032505/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_6000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-6000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-6000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032532/0000/*.root");
  // chains["GluGluSpin0ToGammaGamma_W_5p6_M_7000_13TeV_pythia8_2016"]->Add(baseDirectory+"/store/user/cawest/diphoton/188f9ce/GluGluSpin0ToGG_W-5p6_M-7000_TuneCUEP8M1_13TeV-pythia8/crab_GluGluSpin0ToGG_W-5p6_M-7000_TuneCUEP8M1_13TeV-pythia8__Summer16MiniAODv3-v2__MINIAODSIM/201203_032545/0000/*.root");

  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011924/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_011940/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012002/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012018/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012035/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191210_195341/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012106/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012124/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_3000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_3000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012144/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_3250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_3250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012201/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_3500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_3500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012217/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_4000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_4000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_4000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012234/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_4500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_4500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_4500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012250/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_5000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_5000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_5000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012305/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012322/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012341/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012357/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012416/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012433/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_2000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_2000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_2000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012449/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_2250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_2250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_2250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012506/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_2500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_2500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_2500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012524/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_3000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_3000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_3000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012542/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_3500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_3500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_3500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012559/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012617/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012632/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012650/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012708/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_5000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_5000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_5000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012725/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012742/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012758/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1250_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1250_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012822/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012840/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012858/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_2000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_2000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_2000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012913/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_2500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_2500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_2500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_012949/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_3000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_3000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_3000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_013010/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_3500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_3500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_3500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_013029/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_4000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_4000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_4000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_013046/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_4500_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_4500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_4500_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_013102/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_4750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_4750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_4750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_013119/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_5000_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_5000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_5000_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_013135/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_750_13TeV_pythia8_2017"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_750_TuneCP2_13TeV_pythia8__Fall17_PU2017-v1__MINIAODSIM/191206_013155/0000/*.root");

  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015405/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015423/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015441/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_1750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_1750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_1750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015500/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015519/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015537/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015555/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_2750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_2750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_2750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015615/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_3000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_3000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015633/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_3250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_3250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015652/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_3500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_3500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_3500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015710/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_4000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_4000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_4000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015729/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_4500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_4500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_4500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015748/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_5000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_5000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_5000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015805/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_0p014_M_750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_0p014_M_750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_0p014_M_750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015823/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015842/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015902/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015926/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_1750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_1750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_1750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_015945/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_2000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_2000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_2000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020003/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_2250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_2250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_2250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020024/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_2500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_2500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_2500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020042/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_3000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_3000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_3000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020101/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_3500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_3500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_3500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020118/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020137/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020200/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020223/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_4750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_4750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_4750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020240/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_5000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_5000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_5000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020258/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_1p4_M_750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_1p4_M_750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_1p4_M_750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020315/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020335/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020357/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020414/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_1750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_1750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_1750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020432/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_2000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_2000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_2000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020458/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_2500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_2500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_2500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020535/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_3000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_3000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_3000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020554/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_3500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_3500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_3500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020612/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_4000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_4000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_4000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020630/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_4500_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_4500_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_4500_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020647/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_4750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_4750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_4750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020705/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_5000_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_5000_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_5000_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020722/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_750_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_750_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_750_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020739/0000/*.root");
  chains["GluGluSpin0ToGammaGamma_W_5p6_M_2250_13TeV_pythia8_2018"]->Add(baseDirectory + "/store/user/cawest/diphoton/969aff9/GluGluSpin0ToGammaGamma_W_5p6_M_2250_TuneCP2_13TeV_pythia8/crab_GluGluSpin0ToGammaGamma_W_5p6_M_2250_TuneCP2_13TeV_pythia8__Autumn18-v1__MINIAODSIM/191218_020517/0000/*.root");


}


#endif
