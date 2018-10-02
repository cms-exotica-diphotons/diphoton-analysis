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


double luminosity = 2.62; // fb^-1
const double luminosity2016 = 35.9; // fb^-1
const double luminosityRatio = 35.9/2.62;
const double luminosityError = 0.023;
const double luminosity2016Error = 0.026;
//const double luminosity2017 = 38.72;
const double luminosity2017 = 41.527;
//const double luminosity2018 = 7.93;
//const double luminosity2018 = 10.33;
//const double luminosity2018 = 14.383;
//const double luminosity2018 = 16.594;
//const double luminosity2018 = 24.089;
//const double luminosity2018 = 26.928;
const double luminosity2018 = 43.704;
//const double luminosity2018_newjson = 16.594-14.383;
//const double luminosity2018_newjson = 2.839;
//const double luminosity2018_newjson = 12.806;
//const double luminosity2018_newjson = 3.969;
const double luminosity2018_newjson = 2.341;

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

  TChain *chData2018 = new TChain(treeType);
  // for PPD presentation 21JUN2018
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180526_200444/0000/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180526_200444/0001/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180526_200444/0002/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180526_200444/0003/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180526_200444/0004/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180526_200444/0005/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180526_200444/0006/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD/180526_200502/0000/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_third_json/180604_210901/0000/*.root");
  // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD_third_json/180604_210920/0000/*.root");

  // from Chris
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180620_213402/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180620_213402/0001/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180620_213402/0002/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180620_213402/0003/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD/180620_213423/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD/180620_213449/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD/180620_213449/0001/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180620_213530/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_six/180622_174624/0000/*.root");

  // Run2018A-Cv2
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180806_202207/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180806_202207/0001/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180806_202207/0002/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD/180806_202207/0003/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD/180806_202225/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD/180806_202250/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD/180806_202250/0001/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180806_202325/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180806_202325/0001/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD/180806_202325/0002/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v2__MINIAOD/180806_202348/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v1__MINIAOD/180806_202407/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD/180806_202429/0000/*.root");
 //  chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD/180806_202429/0001/*.root");

 // Run2018A-Cv3
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172033/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172033/0001/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172033/0002/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172033/0003/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD_json_toRun2018cv3/180904_172143/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD_json_toRun2018cv3/180904_172259/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD_json_toRun2018cv3/180904_172259/0001/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172410/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172410/0001/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172410/0002/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v2__MINIAOD_json_toRun2018cv3/180904_172520/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v1__MINIAOD_json_toRun2018cv3/180904_172642/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD_json_toRun2018cv3/180904_172759/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD_json_toRun2018cv3/180904_172759/0001/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD_json_toRun2018cv3/180904_172917/0000/*.root");
 // chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD_json_toRun2018cv3/180904_172917/0001/*.root");

 // Run2018A-Dv2: 322381
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062744/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062744/0001/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062744/0002/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062744/0003/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180924_062801/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD_json_toRun2018Dv2_322381/180924_062818/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018A-PromptReco-v3__MINIAOD_json_toRun2018Dv2_322381/180924_062818/0001/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062841/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062841/0001/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062841/0002/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018B-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180924_062905/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v1__MINIAOD_json_toRun2018Dv2_322381/180924_062924/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180924_062942/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180924_062942/0001/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD_json_toRun2018Dv2_322381/180926_053702/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD_json_toRun2018Dv2_322381/180926_053702/0001/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180926_053722/0000/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180926_053722/0001/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180926_053722/0002/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180926_053722/0003/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180926_053722/0004/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180926_053722/0005/*.root");
chData2018->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_toRun2018Dv2_322381/180926_053722/0006/*.root");

 TChain *chData2018_newjson = new TChain(treeType);
  //chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/EGamma/crab_EGamma__Run2018B-PromptReco-v1__MINIAOD_json_six/180622_174624/0000/*.root");
  // chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD/180825_225216/0000/*.root");
  // chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/ciperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018C-PromptReco-v3__MINIAOD/180825_225216/0001/*.root");

  //Run2018Dv2_320673-322057
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180915_175734/0000/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180915_175734/0001/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180915_175734/0002/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180915_175734/0003/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180915_175734/0004/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180915_175734/0005/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180918_074933/0000/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180918_074933/0001/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180918_074933/0002/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180918_074933/0003/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180918_074933/0004/*.root");
// chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_320673-322057/180918_074933/0005/*.root");

chData2018_newjson->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cuperez/DiPhotonAnalysis/EGammaData/EGamma/crab_EGamma__Run2018D-PromptReco-v2__MINIAOD_json_Run2018Dv2_322057-322381/180924_061130/0000/*.root");

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

  TChain *chData2017 = new TChain(treeType);
  chData2017->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017B-31Mar2018-v1__MINIAOD/180614_045620/0000/*.root");
  chData2017->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017C-31Mar2018-v1__MINIAOD/180614_042811/0000/*.root");
  chData2017->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017D-31Mar2018-v1__MINIAOD/180614_042828/0000/*.root");
  chData2017->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017E-31Mar2018-v1__MINIAOD/180614_042850/0000/*.root");
  chData2017->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/DoubleEG/crab_DoubleEG__Run2017F-31Mar2018-v1__MINIAOD/180615_235936/0000/*.root");

  TChain *chData2016 = new TChain(treeType);
  chData2016->Add(filestring("DoubleEG__Run2016B-03Feb2017"));
  chData2016->Add(filestring("DoubleEG__Run2016C-03Feb2017"));
  chData2016->Add(filestring("DoubleEG__Run2016D-03Feb2017"));
  chData2016->Add(filestring("DoubleEG__Run2016E-03Feb2017"));
  chData2016->Add(filestring("DoubleEG__Run2016F-03Feb2017"));
  chData2016->Add(filestring("DoubleEG__Run2016G-03Feb2017"));
  // both _ver2 and _ver3 should be included, corresponding to -v2 and -v3
  // of the PromptReco
  chData2016->Add(filestring("DoubleEG__Run2016H-03Feb2017_ver2"));
  chData2016->Add(filestring("DoubleEG__Run2016H-03Feb2017_ver3"));
  TChain *chGG = new TChain(treeType);
  // chGG->Add(filestring("GGJets_M-60To200_Pt-50_13TeV-sherpa"));
  // chGG->Add(filestring("GGJets_M-200To500_Pt-50_13TeV-sherpa"));
  // chGG->Add(filestring("GGJets_M-500To1000_Pt-50_13TeV-sherpa"));
  // chGG->Add(filestring("GGJets_M-1000To2000_Pt-50_13TeV-sherpa"));
  // chGG->Add(filestring("GGJets_M-2000To4000_Pt-50_13TeV-sherpa"));
  // chGG->Add(filestring("GGJets_M-4000To6000_Pt-50_13TeV-sherpa"));
  // chGG->Add(filestring("GGJets_M-6000To8000_Pt-50_13TeV-sherpa"));
  // MINIAODv2
  // chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v14/180531_184256/0000/*.root");
  // chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v1/180531_184217/0000/*.root");
  // chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_v/180531_184235/0000/*.root");
  // chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_/180531_184157/0000/*.root");
  // chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_realistic_/180531_182940/0000/*.root");

  // MINIAODv1
  chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-1000To2000_Pt-50_13TeV-sherpa/crab_GGJets_M-1000To2000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINI/180608_201708/0000/*.root");
  chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-200To500_Pt-50_13TeV-sherpa/crab_GGJets_M-200To500_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINIAO/180608_201724/0000/*.root");
  chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-500To1000_Pt-50_13TeV-sherpa/crab_GGJets_M-500To1000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINIA/180608_195438/0000/*.root");
  chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-6000To8000_Pt-50_13TeV-sherpa/crab_GGJets_M-6000To8000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINI/180608_201740/0000/*.root");
  chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-60To200_Pt-50_13TeV-sherpa/crab_GGJets_M-60To200_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MINIAOD/180608_201756/0000/*.root");
  chGG->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GGJets_M-8000To13000_Pt-50_13TeV-sherpa/crab_GGJets_M-8000To13000_Pt-50_13TeV-sherpa__RunIIFall17MiniAOD-PU2017_94X_mc2017_realistic_v11-v1__MIN/180608_201812/0000/*.root");
  TChain *chGG_aMC_2015 = new TChain(treeType);
  chGG_aMC_2015->Add(filestring("DiPhotonJets_MGG-80toInf_2015"));
  TChain *chGG_2016 = new TChain(treeType);
  chGG_2016->Add(filestring("DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa"));
  TChain *chGJ = new TChain(treeType);
  // chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_DR-0p4_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_9/180604_221231/0000/*.root");
  // chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc20/180601_192514/0000/*.root");
  // chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc20/180601_192534/0000/*.root");
  // chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_1core_94X/180601_192552/0000/*.root");

  chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-1core_94X_mc2017_realistic_v/180614_043058/0000/*.root");
  chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1_/180614_043037/0000/*.root");
  chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180614_042933/0000/*.root");
  chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180614_042955/0000/*.root");
  chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v2/180614_043017/0000/*.root");
  chGJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8__RunIIFall17MiniAOD-94X_mc2017_realistic_v10-v1/180614_043115/0000/*.root");

  // chGJ->Add(filestring("GJets_HT-40To100"));
  // chGJ->Add(filestring("GJets_HT-100To200"));
  // chGJ->Add(filestring("GJets_HT-200To400"));
  // chGJ->Add(filestring("GJets_HT-400To600"));
  // chGJ->Add(filestring("GJets_HT-600ToInf"));
  // chGJ->Add(filestring("GJets_HT-40To100_ext1"));
  // chGJ->Add(filestring("GJets_HT-100To200_ext1"));
  // chGJ->Add(filestring("GJets_HT-200To400_ext1"));
  // chGJ->Add(filestring("GJets_HT-400To600_ext1"));
  // chGJ->Add(filestring("GJets_HT-600ToInf_ext1"));

  TChain *chJJ = new TChain(treeType);
  // chJJ->Add(filestring("QCD_Pt-20to30_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-30to50_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-50to80_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-80to120_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-120to170_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-170to300_EMEnriched"));
  // chJJ->Add(filestring("QCD_Pt-300toInf_EMEnriched"));

  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_r/180618_121732/0000/*.root");
  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_r/180618_121732/0000/*.root");
  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_re/180618_121752/0000/*.root");
  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_old_pmx_94X_mc/180618_121859/0000/*.root");
  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_r/180618_121713/0000/*.root");
  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_rea/180618_121815/0000/*.root");
  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_re/180618_121925/0000/*.root");
  chJJ->Add("root://cmseos.fnal.gov//eos/uscms/store/user/cawest/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8__RunIIFall17MiniAODv2-PU2017_12Apr2018_94X_mc2017_rea/180618_121837/0000/*.root");
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
  chDY->Add(filestring("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX"));
  TChain *chTTG = new TChain(treeType);
  chTTG->Add(filestring("TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX"));
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

  std::vector<std::string> sampleNames = {"data", "data_2015", "data_2016", "data_2017", "data_2018", "data_2018_newjson", "gg", "gj", "jj", "vg", "w", "dy", "ttg", "gg70"};

  chains["data_2015"] = chData;
  chains["data_2016"] = chData2016;
  chains["data_2016_preREMINIAOD"] = chData2016_preREMINIAOD;
  chains["data_2017"] = chData2017;
  chains["data_2018"] = chData2018;
  chains["data_2018_newjson"] = chData2018_newjson;
  chains["gg"] = chGG;
  chains["gg_aMC_2015"] = chGG_aMC_2015;
  chains["gg_2016"] = chGG_2016;
  chains["ggGen"] = chGGGen;
  chains["gj"] = chGJ;
  chains["jj"] = chJJ;
  chains["vg"] = chVG;
  chains["w"] = chW;
  chains["dy"] = chDY;
  chains["ttg"] = chTTG;
  chains["gg70"] = chGG70;
  chains["other"] = chOther;

  // ADD initialization done separately to avoid clutter
  initADD();

  // set default styles
  for( auto isample : sampleNames ) {
    lineColors[isample] = kBlack;
    fillStyles[isample] = 1001;
    lineStyles[isample] = kSolid;
    markerColors[isample] = kBlack;
  }

  fillColors["data"]=kWhite;
  fillColors["data_2016"]=kWhite;
  fillColors["data_2016_preREMINIAOD"]=kWhite;
  fillColors["gg"]=kCyan;
  fillColors["gg_2016"]=kCyan;
  fillColors["gg_aMC_2015"]=kCyan;
  fillColors["gj"]=kBlue;
  fillColors["jj"]=kSpring;
  fillColors["vg"]=kOrange;
  fillColors["w"]=kBlack;
  fillColors["dy"]=kYellow;
  fillColors["ttg"]=kMagenta;
  fillColors["gg70"]=kCyan;

  prettyName["data_2015"]="Data (2015)";
  prettyName["data_2016"]="Data (2016)";
  prettyName["data_2017"]="Data (2017)";
  prettyName["data_2018"]="Data (2018)";
  prettyName["data_2018_newjson"]="Data (2018, new JSON)";
  prettyName["data_2016_preREMINIAOD"]="Data (2016, pre-reMINIAOD)";
  prettyName["gg"]="#gamma#gamma";
  prettyName["gg_2016"]="#gamma#gamma (2016)";
  prettyName["gg_aMC_2015"]="#gamma#gamma (aMC@NLO)";
  prettyName["gj"]="#gamma + jets";
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
