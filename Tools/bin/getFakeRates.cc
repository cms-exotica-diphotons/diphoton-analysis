// Fits fake rate plots and creates an output file 
// containing a TF1 for each plot
// To generate the input files for this code:
// cd ${CMSSW_BASE}/src/diphoton-analysis/FakeRateAnalysis/RooFitTemplateFitting/analysis
// root -l -q ../scripts/fakeRateCalculation.C
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TString.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "TFitResult.h"
#include "TLatex.h"

#include <string>
#include <map>
#include <cstdlib> // getenv()

#include "diphoton-analysis/Tools/interface/tdrstyle.hh"

TF1* getFakeRateFunction(const std::string& isolation, const std::string& region, const std::string& year);

int main(int argc, char *argv[])
{
  std::string year, dataset;

  if(argc!=3) {
    std::cout << "Syntax: getFakeRates.exe [2015/2016/2017/2018] [jetht/doublemuon]" << std::endl;
    return -1;
  }
  else {
    year = argv[1];
    if(year!="2015" and year!="2016" and year!="2017" and year!="2018") {
      std::cout << "Only '2015', '2016', '2017' and '2018' are allowed input parameters." << std::endl;
      return -1;
    }
    dataset = argv[2];
    if(dataset!="jetht" && dataset!="doublemuon") {
      std::cout << "Only 'jetht' and 'doublemuon' are allowed datasets." << std::endl;
    }
  }

  setTDRStyle();
  gROOT->ForceStyle();

  const char *cmssw_base = getenv("CMSSW_BASE");
  if(cmssw_base==nullptr) {
    std::cout << "Please issue cmsenv before running" << std::endl;
    return -1;
  }
  const std::string cmssw_base_string(cmssw_base);
  const std::string directory("/src/diphoton-analysis/FakeRateAnalysis/RooFitTemplateFitting/analysis/");
  std::string fakeRateFile(cmssw_base_string + directory + "fakeRatePlots_" + dataset + "_" + year + ".root");
  std::string fakeRateOutputFile(cmssw_base_string + "/src/diphoton-analysis/Tools/data/fakeRateFunctions_" + year + "_" + dataset +  ".root");

  std::vector<std::pair<int, int> > isolationRanges;
  isolationRanges.push_back(std::pair<int, int>(5, 10));
  isolationRanges.push_back(std::pair<int, int>(6, 11));
  isolationRanges.push_back(std::pair<int, int>(7, 12));
  isolationRanges.push_back(std::pair<int, int>(8, 13));
  isolationRanges.push_back(std::pair<int, int>(9, 14));
  isolationRanges.push_back(std::pair<int, int>(10, 15));
  isolationRanges.push_back(std::pair<int, int>(15, 20));
  isolationRanges.push_back(std::pair<int, int>(10, 20));

  // to create nice looking plots
  std::map<std::string, std::string> displayDictionary;
  displayDictionary["EB"] = "Barrel";
  displayDictionary["EE"] = "Endcap";

  std::vector<std::string> isolationSidebands;
  for(auto irange : isolationRanges) {
    std::string iso("chIso");
    iso+=std::to_string(irange.first);
    iso+="To";
    iso+=std::to_string(irange.second);
    isolationSidebands.push_back(iso);
  }

  std::vector<std::string> regions = {"EB", "EE"};

  TFile *input = TFile::Open(fakeRateFile.c_str());
  TFile *output = new TFile(fakeRateOutputFile.c_str(), "recreate");

  for(unsigned int iIso = 0; iIso<isolationSidebands.size(); iIso++) {
    for(unsigned int iRegion = 0; iRegion<regions.size(); iRegion++) {
      TString histName(Form("fakeRate%s_%s", regions[iRegion].c_str(), isolationSidebands[iIso].c_str()));
      TGraphAsymmErrors *graph;
      std::cout << "Getting fake rate graph " << histName << " from file " << fakeRateFile << std::endl;
      input->GetObject(histName, graph);
      TCanvas *c = new TCanvas;
      c->SetLeftMargin(0.18);
      std::cout << "Getting fake rate function for isolation sideband " << isolationSidebands[iIso]
		<< " and region " << regions[iRegion] << std::endl;
      TF1 * func = getFakeRateFunction(isolationSidebands[iIso], regions[iRegion], year);
      TFitResultPtr fitResult = graph->Fit(func, "vse");
      graph->SetMarkerStyle(kFullCircle);
      graph->SetMarkerSize(0.5);
      graph->SetTitle(";Photon p_{T} (GeV);Fake rate");
      graph->GetYaxis()->SetTitleOffset(1.5); // times the standard value
      graph->SetMinimum(0.0);
      if(regions[iRegion] == "EB") graph->SetMaximum(0.25);
      else graph->SetMaximum(0.6);
      graph->Draw("AP");

      TLatex *latex = new TLatex;
      latex->SetNDC(true);
      latex->DrawLatex(0.5, 0.7, Form("%s, %s", displayDictionary[regions[iRegion]].c_str(), year.c_str()));
      TString isoString(Form("%d < Iso_{ch} < %d GeV", isolationRanges[iIso].first, isolationRanges[iIso].second));
      latex->DrawLatex(0.5, 0.65, isoString);
      std::map<std::string, TString> prettyDatasetString;
      prettyDatasetString["jetht"] = "JetHT";
      prettyDatasetString["doublemuon"] = "DoubleMuon";
      latex->DrawLatex(0.5, 0.6, prettyDatasetString[dataset]);
      output->cd();
      fitResult->Write();
      graph->Write();
      func->Write();
      c->Print(Form("plots/%s_%s_%s.pdf", histName.Data(), year.c_str(), dataset.c_str()));
    }
  }

  output->Close();
  input->Close();

}

TF1* getFakeRateFunction(const std::string& isolation, const std::string& region, const std::string& year)
{
  // fit range
  double xmin = 50.;
  double xmax = 2000.;

  std::string functionType(region);
  functionType += "_";
  functionType += year;

  // list of possible fit functions
  std::map<std::string, std::string> fitFunc;
  fitFunc["EB_2015"] = "[0]+[1]/(x^[2])";
  fitFunc["EB_2016"] = "[0]+[1]/(x^[2])";
  fitFunc["EB_2017"] = "[0]+[1]/(x^[2])";
  fitFunc["EB_2018"] = "[0]+[1]/(x^[2])";
  fitFunc["EE_2015"] = "(x<175)*([0]+[1]*(x-175)+[2]*(x-175)^2)+(x>175)*([0]+(x-175)*[1])";
  fitFunc["EE_2016"] = "[0]+[1]/(x^[2])";
  fitFunc["EE_2017"] = "[0]+[1]/(x^[2])";
  fitFunc["EE_2018"] = "[0]+[1]/(x^[2])";

  TString fitName(Form("fakeRate%s_%s_fit", region.c_str(), isolation.c_str()));

  TF1* fakeRate = new TF1(fitName, fitFunc[functionType].c_str(), xmin, xmax);

  // decent initial guesses are needed for the fit to converge
  if(region=="EB") fakeRate->SetParameters(0.02695594369285, 337.46692070018906, 2.10557989223267);
  if(region=="EE" && year=="2015") fakeRate->SetParameters(0.07583295145724, 0.00003927399330, 0.00000255676015);
  if(region=="EB" && year=="2016") fakeRate->SetParameters(0.0297647, 205.612, 1.76173);
  if(region=="EE" && year=="2016") fakeRate->SetParameters(0.282890, 6.37370, 0.863015);
  if(region=="EE" && (year=="2017" || year=="2018")) {
    fakeRate->SetParameters(0., 2.3, 0.1);
    fakeRate->SetParLimits(2, 0.1, 3.5);
  }
  return fakeRate;
}
