#ifndef fakeRates_hh
#define fakeRates_hh

#include <iostream>
#include <map>
#include <string>
#include "TFile.h"
#include "TGraphAsymmErrors.h"
#include "TString.h"

class fakeRates {
  int m_year;
  std::map<std::string, TGraphAsymmErrors*> m_fakeRates;
  std::map<std::string, TGraphAsymmErrors*> m_fakeRatesClosureTest;
  std::string m_fakeRateType;

 public:
  fakeRates(std::string fakeRateType, int year, std::string chIsoSideband);
  double getFakeRate(double pt, int region, int nPV);
  double getFakeRateClosureTest(double pt, std::string region, int year);

};

fakeRates::fakeRates(std::string fakeRateType, int year, std::string chIsoSideband) : m_year(year)
{
  std::string iso = "chIso" + chIsoSideband;

  m_fakeRateType = fakeRateType;
  bool isClosureTest = (fakeRateType=="all") ? true : false;

  const char *cmssw_base = getenv("CMSSW_BASE");
  if(cmssw_base==nullptr) {
    std::cout << "Please issue cmsenv before running" << std::endl;
    exit(-1);
  }

  if (!isClosureTest){
  std::vector<std::string> datasets = {"jetht", "doublemuon"};
  std::vector<std::string> regions = {"EB", "EE", "EE1", "EE2"};
  std::vector<std::string> pvCuts = {"0-22", "23-27"};
  if(m_year==2016) pvCuts.push_back("28-200");
  else {
    pvCuts.push_back("28-32");
    pvCuts.push_back("33-37");
    pvCuts.push_back("38-200");
  }

  for(auto region : regions) {
    for(auto dataset : datasets) {
      for(auto pvCut : pvCuts) {
        TFile *f = TFile::Open(Form("%s/src/diphoton-analysis/FakeRateAnalysis/fakeRatePlots_%s_%d_nPV%s.root", cmssw_base, dataset.c_str(), m_year, pvCut.c_str()));
        const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
        TGraphAsymmErrors *gr = dynamic_cast<TGraphAsymmErrors*>(f->Get(graphName));
	std::string keyname(region + "_" + dataset + "_" + pvCut);
        m_fakeRates[keyname] = gr;
      }
    }
  }
}

else{
  std::cout << "Closure Test" << std::endl;
  std::vector<std::string> regions = {"EB", "EE"};

    for (auto region : regions){
      TFile *f = TFile::Open(Form("%s/src/fakeRatePlots_all_%d_nPV0-200.root", cmssw_base, year));
      const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
      TGraphAsymmErrors *gr = dynamic_cast<TGraphAsymmErrors*>(f->Get(graphName));
      std::string keyname(region + "_" + "all_0-200" );
      m_fakeRatesClosureTest[keyname] = gr;
    }
  }
}

// type:
// 0 = average of doublemuon and jetht
// 1 = doublemuon
// 2 = jetht
double fakeRates::getFakeRate(double pt, int region, int nPV)
{
  std::vector<std::string> regions = {"EB", "EE", "EE1", "EE2"};
  std::string pvCut = "";
  if(nPV >= 0 && nPV <= 22) pvCut = "0-22";
  else if(nPV >= 23 && nPV <= 27) pvCut = "23-27";
  else if(nPV >= 28 && nPV <=200) {
    if(m_year == 2016) {
      pvCut = "28-200";
    }
    else {
      if(nPV >= 28 && nPV <= 32) pvCut = "28-32";
      else if(nPV >= 33 && nPV <= 37) pvCut = "33-37";
      else if(nPV >= 38 && nPV <= 200) pvCut = "38-200";
    }
  }
  else std::cout << "Anomalous nPV: " << nPV << std::endl;

  std::string keyname_doublemuon(regions[region] + "_doublemuon_" + pvCut);
  std::string keyname_jetht(regions[region] + "_jetht_" + pvCut);

  int nmax_doublemuon = m_fakeRates[keyname_doublemuon]->GetN()-1;
  double pt_max_doublemuon = m_fakeRates[keyname_doublemuon]->GetX()[nmax_doublemuon];
  int nmax_jetht = m_fakeRates[keyname_jetht]->GetN()-1;
  double pt_max_jetht = m_fakeRates[keyname_jetht]->GetX()[nmax_jetht];

  double pt_doublemuon = (pt > pt_max_doublemuon) ? pt_max_doublemuon : pt;
  double pt_jetht = (pt > pt_max_jetht) ? pt_max_jetht : pt;

  if(m_fakeRateType == "average") return 0.5*(m_fakeRates[keyname_doublemuon]->Eval(pt_doublemuon)+m_fakeRates[keyname_jetht]->Eval(pt_jetht));
  else if(m_fakeRateType == "doublemuon") return m_fakeRates[keyname_doublemuon]->Eval(pt_doublemuon);
  else if(m_fakeRateType == "jetht") return m_fakeRates[keyname_jetht]->Eval(pt_jetht);
  else std::cout << "Fake rate type " << m_fakeRateType << "not supported." << std::endl;

  return 0;
}

double fakeRates::getFakeRateClosureTest(double pt, std::string region, int year)
{

  std::string keyname_all(region + "_all_0-200");

  int nmax = m_fakeRatesClosureTest[keyname_all]->GetN()-1;
  double pt_max = m_fakeRatesClosureTest[keyname_all]->GetX()[nmax];
  double pt_closure = (pt > pt_max) ? pt_max : pt;
  double fakeRate = m_fakeRatesClosureTest[keyname_all]->Eval(pt_closure);
  std::cout << "FakeRate for pt: " << pt << "is " << fakeRate << std::endl;
  return fakeRate;

}

#endif // fakeRates_hh
