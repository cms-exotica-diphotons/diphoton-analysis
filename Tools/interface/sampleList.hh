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
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include <linux/limits.h>

#include "diphoton-analysis/Tools/interface/tdrstyle.hh"

const double luminosity2018_newjson = 54.19-52.73;

// 20.3 fb^-1 were acquired in 2018 before loss of HEM15/HEM16
std::map<std::string, double> luminosity { {"2015", 2.62}, {"2016", 35.9}, {"2017", 41.527}, {"2018", 54.19}, {"2018_newjson", 54.19-52.73}};
// 2017 uncertainties currently used for 2018
std::map<std::string, double> luminosityErrorFrac { {"2015", 0.023}, {"2016", 0.026}, {"2017", 0.023}, {"2018", 0.023}, {"2018_newjson", 0.023}};

std::map<std::string, TChain*> chains;
std::map<std::string, int> lineStyles;
std::map<std::string, int> lineColors;
std::map<std::string, int> fillStyles;
std::map<std::string, int> fillColors;
std::map<std::string, int> markerColors;
std::map<std::string, std::string> prettyName;

TString filestring(TString sample);
void init(); // initializes samples
void initADD(); // initializes ADD samples; performed by a loop rather than being listed explicitly
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
  for( auto ichain : chains) {
    std::cout << ichain.first << std::endl;
  }
}

std::vector<std::string> getSampleList()
{
  std::vector<std::string> list;

  for( auto ichain : chains) {
    list.push_back(ichain.first);
  }

  return list;
}

void init()
{
  TString treeType("diphoton/fTree");
  TString baseDirectory("root://cmseos.fnal.gov/");
  TChain *chData2018_newjson = new TChain(treeType);
  chData2018_newjson->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_325114_sub_324420/181105_162007/*.root");

  // skimmed version of chData2018_unskimmed
  TChain *chData2018 = new TChain(treeType);
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180919_202214/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD_resubmit/180928_191037/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD/180919_202243/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180919_202259/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v2__MINIAOD/180919_202313/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v1__MINIAOD/180919_202326/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD/180919_202340/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD/180919_202355/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD_to322381/180920_173238/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_323523_minus_322633/181008_184249/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD324209_sub_323523/181018_194050/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_324420_sub_324209/181025_162725/*.root");
  chData2018->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_325114_sub_324420/181105_162007/*.root");

  TChain *chData2018_unskimmed = new TChain(treeType);
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180919_202214/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180919_202214/0001/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180919_202214/0002/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180919_202214/0003/*.root");
  //  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD/180919_202229/0000/*.root");
  // reprocess to take into account removed lumisections:  https://hypernews.cern.ch/HyperNews/CMS/get/physics-validation/3202.html
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD_resubmit/180928_191037/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD/180919_202243/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD/180919_202243/0001/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180919_202259/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180919_202259/0001/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180919_202259/0002/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v2__MINIAOD/180919_202313/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v1__MINIAOD/180919_202326/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD/180919_202340/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD/180919_202340/0001/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD/180919_202355/0000/*.root");

  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD_to322381/180920_173238/0000/*.root");

  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0001/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0002/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0003/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0004/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0005/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0006/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_resubmit/180928_191057/0007/*.root");

  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_323523_minus_322633/181008_184249/0000/*.root");

  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD324209_sub_323523/181018_194050/0000/*.root");
  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD324209_sub_323523/181018_194050/0001/*.root");

  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_324420_sub_324209/181025_162725/0000/*.root");

  chData2018_unskimmed->Add(baseDirectory + "/store/user/cawest/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_325114_sub_324420/181105_162007/0000/*.root");

  TChain *chDataJetHT2018_unskimmed = new TChain(treeType);
  chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181106_044509/0000/*.root");
  chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181106_044509/0001/*.root");
  chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181106_044509/0002/*.root");
  chDataJetHT2018_unskimmed->Add(baseDirectory + "/store/user/cawest/JetHT/crab_JetHT__Run2018A-PromptReco-v1__MINIAOD/181106_044509/0003/*.root");

  TChain *chData = new TChain(treeType);
  chData->Add(filestring("DoubleEG__Run2015D"));
  chData->Add(filestring("DoubleEG__Run2015C_25ns"));
  TChain *chData2016_preREMINIAOD = new TChain(treeType);
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016B"));
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016C"));
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016D"));
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016E"));
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016F"));
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016G"));
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016H"));
  // // both -v2 and -v3 should be included
  // chData2016_preREMINIAOD->Add(filestring("DoubleEG__Run2016H-PromptReco-v2"));
  TChain *chData2017Prompt = new TChain(treeType);
  chData2017Prompt->Add(filestring("DoubleEG__Run2017B-v1"));
  chData2017Prompt->Add(filestring("DoubleEG__Run2017B-v2"));
  chData2017Prompt->Add(filestring("DoubleEG__Run2017C-v1"));
  chData2017Prompt->Add(filestring("DoubleEG__Run2017C-v2"));
  chData2017Prompt->Add(filestring("DoubleEG__Run2017C-v3"));
  chData2017Prompt->Add(filestring("DoubleEG__Run2017D-v1"));
  chData2017Prompt->Add(filestring("DoubleEG__Run2017E-v1"));
  chData2017Prompt->Add(filestring("DoubleEG__Run2017F-v1"));

  TChain *chData2017_unskimmed = new TChain(treeType);
  chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017B-31Mar2018-v1__MINIAOD/180614_045620/0000/*.root");
  chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017C-31Mar2018-v1__MINIAOD/180614_042811/0000/*.root");
  chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017D-31Mar2018-v1__MINIAOD/180614_042828/0000/*.root");
  chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017E-31Mar2018-v1__MINIAOD/180614_042850/0000/*.root");
  chData2017_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017F-31Mar2018-v1__MINIAOD/180615_235936/0000/*.root");

  TChain *chData2017 = new TChain(treeType);
  chData2017->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017B-31Mar2018-v1__MINIAOD/180614_045620/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017C-31Mar2018-v1__MINIAOD/180614_042811/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017D-31Mar2018-v1__MINIAOD/180614_042828/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017E-31Mar2018-v1__MINIAOD/180614_042850/*.root");
  chData2017->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017F-31Mar2018-v1__MINIAOD/180615_235936/*.root");

  TChain *chData2016_unskimmed = new TChain(treeType);
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016H-03Feb2017_ver3-v1__MINIAOD/180412_014155/0000/*.root");
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016F-03Feb2017-v1__MINIAOD/180412_013649/0000/*.root");
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016B-03Feb2017_ver2-v2__MINIAOD/180410_215122/0000/*.root");
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016D-03Feb2017-v1__MINIAOD/180412_013334/0000/*.root");
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016C-03Feb2017-v1__MINIAOD/180412_013202/0000/*.root");
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016E-03Feb2017-v1__MINIAOD/180412_013513/0000/*.root");
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016H-03Feb2017_ver2-v1__MINIAOD/180412_013955/0000/*.root");
  chData2016_unskimmed->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016G-03Feb2017-v1__MINIAOD/180412_013820/0000/*.root");

  TChain *chData2016 = new TChain(treeType);
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016H-03Feb2017_ver3-v1__MINIAOD/180412_014155/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016F-03Feb2017-v1__MINIAOD/180412_013649/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016B-03Feb2017_ver2-v2__MINIAOD/180410_215122/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016D-03Feb2017-v1__MINIAOD/180412_013334/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016C-03Feb2017-v1__MINIAOD/180412_013202/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016E-03Feb2017-v1__MINIAOD/180412_013513/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016H-03Feb2017_ver2-v1__MINIAOD/180412_013955/*.root");
  chData2016->Add(baseDirectory + "/store/user/cawest/DoubleEG/crab_DoubleEG__Run2016G-03Feb2017-v1__MINIAOD/180412_013820/*.root");
  // chData2016->Add(filestring("DoubleEG__Run2016B-03Feb2017"));
  // chData2016->Add(filestring("DoubleEG__Run2016C-03Feb2017"));
  // chData2016->Add(filestring("DoubleEG__Run2016D-03Feb2017"));
  // chData2016->Add(filestring("DoubleEG__Run2016E-03Feb2017"));
  // chData2016->Add(filestring("DoubleEG__Run2016F-03Feb2017"));
  // chData2016->Add(filestring("DoubleEG__Run2016G-03Feb2017"));
  // both _ver2 and _ver3 should be included, corresponding to -v2 and -v3
  // of the PromptReco
  // chData2016->Add(filestring("DoubleEG__Run2016H-03Feb2017_ver2"));
  // chData2016->Add(filestring("DoubleEG__Run2016H-03Feb2017_ver3"));

  TChain *chData2017_2018 = new TChain(treeType);
  chData2017_2018->Add(chData2017);
  chData2017_2018->Add(chData2018);

  TChain *chData2016_2017_2018 = new TChain(treeType);
  chData2016_2017_2018->Add(chData2016);
  chData2016_2017_2018->Add(chData2017_2018);


  TChain *chGG = new TChain(treeType);
  // MINIAODv2
  // chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14/180531_184256/0000/*.root");
  // chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v1/180531_184217/0000/*.root");
  // chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v/180531_184235/0000/*.root");
  // chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_/180531_184157/0000/*.root");
  // chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_/180531_182940/0000/*.root");

  // MINIAODv1
  chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINI/180608_201708/0000/*.root");
  chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINIAO/180608_201724/0000/*.root");
  chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINIA/180608_195438/0000/*.root");
  chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINI/180608_201740/0000/*.root");
  chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINIAOD/180608_201756/0000/*.root");
  chGG->Add(baseDirectory + "/store/user/cawest/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MIN/180608_201812/0000/*.root");
  TChain *chGG_aMC_2015 = new TChain(treeType);
  chGG_aMC_2015->Add(filestring("DiPhotonJets_MGG-80toInf_2015"));
  TChain *chGG_2016 = new TChain(treeType);
  chGG_2016->Add(filestring("GGJets_M-60To200_Pt-50_13TeV-sherpa"));
  chGG_2016->Add(filestring("GGJets_M-200To500_Pt-50_13TeV-sherpa"));
  chGG_2016->Add(filestring("GGJets_M-500To1000_Pt-50_13TeV-sherpa"));
  chGG_2016->Add(filestring("GGJets_M-1000To2000_Pt-50_13TeV-sherpa"));
  chGG_2016->Add(filestring("GGJets_M-2000To4000_Pt-50_13TeV-sherpa"));
  chGG_2016->Add(filestring("GGJets_M-4000To6000_Pt-50_13TeV-sherpa"));
  chGG_2016->Add(filestring("GGJets_M-6000To8000_Pt-50_13TeV-sherpa"));
  TChain *chGJ = new TChain(treeType);
  chGJ->Add(baseDirectory + "/store/user/cawest/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-1core_94X_mc2017_realistic_v/180614_043058/0000/*.root");
  chGJ->Add(baseDirectory + "/store/user/cawest/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_/180614_043037/0000/*.root");
  chGJ->Add(baseDirectory + "/store/user/cawest/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180614_042933/0000/*.root");
  chGJ->Add(baseDirectory + "/store/user/cawest/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180614_042955/0000/*.root");
  chGJ->Add(baseDirectory + "/store/user/cawest/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180614_043017/0000/*.root");
  chGJ->Add(baseDirectory + "/store/user/cawest/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180614_043115/0000/*.root");

  TChain *chGJ_2016 = new TChain(treeType);
  chGJ_2016->Add(filestring("GJets_HT-40To100"));
  chGJ_2016->Add(filestring("GJets_HT-100To200"));
  chGJ_2016->Add(filestring("GJets_HT-200To400"));
  chGJ_2016->Add(filestring("GJets_HT-400To600"));
  chGJ_2016->Add(filestring("GJets_HT-600ToInf"));
  chGJ_2016->Add(filestring("GJets_HT-40To100_ext1"));
  chGJ_2016->Add(filestring("GJets_HT-100To200_ext1"));
  chGJ_2016->Add(filestring("GJets_HT-200To400_ext1"));
  chGJ_2016->Add(filestring("GJets_HT-400To600_ext1"));
  chGJ_2016->Add(filestring("GJets_HT-600ToInf_ext1"));

  TChain *chJJ = new TChain(treeType);
  // chJJ->Add(filestring("QCD_Pt-20to30_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-30to50_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-50to80_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-80to120_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-120to170_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-170to300_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-300toInf_EMEnriched"));

  chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_r/180618_121732/0000/*.root");
  chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_r/180618_121732/0000/*.root");
  chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_re/180618_121752/0000/*.root");
  chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc/180618_121859/0000/*.root");
  chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_r/180618_121713/0000/*.root");
  chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_re/180618_121925/0000/*.root");
  // no 200-300 events pass the selection; 300-500 has only a single high-weight event
  // chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_rea/180618_121815/0000/*.root");
  // chJJ->Add(baseDirectory + "/store/user/cawest/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_rea/180618_121837/0000/*.root");
  TChain *chVG = new TChain(treeType);
  chVG->Add(filestring("WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX"));
  chVG->Add(filestring("ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX"));
  TChain *chW = new TChain(treeType);
  // The following samples have a bug and should be excluded.
  // Should switch to a different W sample.
  //  chW->Add(filestring("WToLNu_0J_13TeV-amcatnloFXFX"));
  //  chW->Add(filestring("WToLNu_1J_13TeV-amcatnloFXFX"));
  chW->Add(filestring("WToLNu_2J_13TeV-amcatnloFXFX"));
  TChain *chDY = new TChain(treeType);
  //  chDY->Add(filestring("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX"));
  chDY->Add(baseDirectory + "/store/user/cawest/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__Fall17_PU2017_ext1-v1__MINIAODSIM/180719_182748/0000/*.root");
  chDY->Add(baseDirectory + "/store/user/cawest/DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8/crab_DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc201/180719_180041/0000/*.root");
  TChain *chTTG = new TChain(treeType);
  // chTTG->Add(filestring("TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX"));

  // sum of minor backgrounds for use in limit setting
  TChain *chOther = new TChain(treeType);
  chOther->Add(chVG);
  chOther->Add(chW);
  chOther->Add(chDY);
  chOther->Add(chTTG);
  TChain *chGGGen = new TChain("diphoton/fSherpaGenTree");
  chGGGen->Add(filestring("GGJets_M-60To200_Pt-50_13TeV-sherpa"));
  chGGGen->Add(filestring("GGJets_M-200To500_Pt-50_13TeV-sherpa"));
  chGGGen->Add(filestring("GGJets_M-500To1000_Pt-50_13TeV-sherpa"));
  chGGGen->Add(filestring("GGJets_M-1000To2000_Pt-50_13TeV-sherpa"));
  chGGGen->Add(filestring("GGJets_M-2000To4000_Pt-50_13TeV-sherpa"));
  chGGGen->Add(filestring("GGJets_M-4000To6000_Pt-50_13TeV-sherpa"));
  chGGGen->Add(filestring("GGJets_M-6000To8000_Pt-50_13TeV-sherpa"));
  // These samples are defined in the same way as the SM background in the signal samples.
  // They are needed to take into account interference of the signal with SM backgrounds.
  TChain *chGG70 = new TChain(treeType);
  chGG70->Add(filestring("GG_M-200To500_Pt-70_13TeV-sherpa"));
  chGG70->Add(filestring("GG_M-500To1000_Pt-70_13TeV-sherpa"));
  chGG70->Add(filestring("GG_M-1000To2000_Pt-70_13TeV-sherpa"));
  chGG70->Add(filestring("GG_M-2000To4000_Pt-70_13TeV-sherpa"));
  chGG70->Add(filestring("GG_M-4000To8000_Pt-70_13TeV-sherpa"));
  chGG70->Add(filestring("GG_M-8000To13000_Pt-70_13TeV-sherpa"));

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
  chains["data_2016"] = chData2016;
  chains["data_2016_unskimmed"] = chData2016_unskimmed;
  chains["data_2016_preREMINIAOD"] = chData2016_preREMINIAOD;
  chains["data_2017"] = chData2017;
  chains["data_2017_unskimmed"] = chData2017_unskimmed;
  chains["data_2018"] = chData2018;
  chains["data_jetht_2018_unskimmed"] = chDataJetHT2018_unskimmed;
  chains["data_2018_unskimmed"] = chData2018_unskimmed;
  chains["data_2018_newjson"] = chData2018_newjson;
  chains["data_2017_2018"] = chData2017_2018;
  chains["data_2016_2017_2018"] = chData2016_2017_2018;
  chains["gg_aMC_2015"] = chGG_aMC_2015;
  chains["gg_2018"] = chGG;
  chains["gg_2017"] = chGG;
  chains["gg_2016"] = chGG_2016;
  chains["ggGen"] = chGGGen;
  chains["gj_2018"] = chGJ;
  chains["gj_2017"] = chGJ;
  chains["gj_2016"] = chGJ_2016;
  chains["jj_2018"] = chJJ;
  chains["jj_2017"] = chJJ;
  chains["jj_2016"] = chJJ;
  chains["vg_2018"] = chVG;
  chains["vg_2017"] = chVG;
  chains["vg_2016"] = chVG;
  chains["w_2018"] = chW;
  chains["w_2017"] = chW;
  chains["w_2016"] = chW;
  chains["dy_2018"] = chDY;
  chains["dy_2017"] = chDY;
  chains["dy_2016"] = chDY;
  chains["ttg_2018"] = chTTG;
  chains["ttg_2017"] = chTTG;
  chains["ttg_2016"] = chTTG;
  chains["gg70_2018"] = chGG70;
  chains["gg70_2017"] = chGG70;
  chains["gg70_2016"] = chGG70;
  chains["other_2018"] = chOther;
  chains["other_2017"] = chOther;
  chains["other_2016"] = chOther;

  // ADD initialization done separately to avoid clutter
  initADD();

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
  fillColors["data_2016_preREMINIAOD"] = kWhite;
  fillColors["gg"] = kCyan;
  // fillColors["gg_2018"] = kCyan;
  // fillColors["gg_2017"] = kCyan;
  // fillColors["gg_2016"] = kCyan;
  fillColors["gg_aMC_2015"] = kCyan;
  fillColors["gj"] = kBlue;
  fillColors["gj_2018"] = kBlue;
  fillColors["gj_2017"] = kBlue;
  fillColors["gj_2016"] = kBlue;
  fillColors["jj"] = kSpring;
  fillColors["jj_2018"] = kSpring;
  fillColors["jj_2017"] = kSpring;
  fillColors["jj_2016"] = kSpring;
  fillColors["vg"] = kOrange;
  fillColors["vg_2018"] = kOrange;
  fillColors["vg_2017"] = kOrange;
  fillColors["vg_2016"] = kOrange;
  fillColors["w"] = kBlack;
  fillColors["w_2018"] = kBlack;
  fillColors["w_2017"] = kBlack;
  fillColors["w_2016"] = kBlack;
  fillColors["dy"] = kYellow;
  fillColors["dy_2018"] = kYellow;
  fillColors["dy_2017"] = kYellow;
  fillColors["dy_2016"] = kYellow;
  fillColors["ttg"] = kMagenta;
  fillColors["ttg_2018"] = kMagenta;
  fillColors["ttg_2017"] = kMagenta;
  fillColors["ttg_2016"] = kMagenta;
  fillColors["gg70"] = kCyan;
  fillColors["gg70_2018"] = kCyan;
  fillColors["gg70_2017"] = kCyan;
  fillColors["gg70_2016"] = kCyan;

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
  prettyName["data_2016_preREMINIAOD"]="Data (2016, pre-reMINIAOD)";
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

void initADD()
{
  // ADD samples
  std::vector<std::string> MS = {"3000", "3500", "4000", "4500",
				 "5000", "5500", "6000"};
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
  MggBins["6000"] = {"250To500", "500To1000", "1000To2000", "2000To4000", "4000To6000"};

  for(const auto iMS : MS) {
    for(const auto iNED : NED) {
      for(const auto iKK : KK) {
	// no samples were generated with KK convention 4
	// and four extra dimensions
	if(strcmp(iKK.c_str(), "4")==0 && strcmp(iNED.c_str(), "4")==0) continue;
	std::string pointName = "ADDGravToGG_MS-";
	pointName += iMS;
	pointName += "_NED-";
	pointName += iNED;
	pointName += "_KK-";
	pointName += iKK;
	chains[pointName] = new TChain("diphoton/fTree");
	for(std::string iMgg : MggBins[iMS] ) {
	  // the 200To500 bins are only present for the NED=4 samples
	  if(strcmp(iNED.c_str(), "2")==0 && strcmp(iMgg.c_str(), "250To500")==0) continue;
	  std::string sampleName(pointName);
	  sampleName += "_M-";
	  sampleName += iMgg;
	  sampleName += "_13TeV-sherpa";
	  chains[pointName]->Add(filestring(sampleName));
	  lineColors[pointName] = kBlack;
	  fillStyles[pointName] = 1001;
	  lineStyles[pointName] = kSolid;
	}
      }
    }
  }

}

#endif
