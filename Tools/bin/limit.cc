#ifdef __CINT__
#include "interface/sampleList.hh"
#else
#include "diphoton-analysis/Tools/interface/sampleList.hh"
#endif

#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"
#include "TMath.h"

bool useLogy = true;
bool drawObservedLimit = false;

void limit(const std::string &directory);
void oneLimit(int ned, int kk, const std::string& directory);
void unparLimit(std::string spin, const std::string &directory);
void setStyle()
{
  gStyle->SetCanvasDefW(600);
  gStyle->SetCanvasDefH(600);
  gStyle->SetTitleOffset(1.2,"x");
  gStyle->SetTitleOffset(1.7,"z");
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadBottomMargin(0.12);
  gStyle->SetPadTopMargin(0.08);

  gStyle->SetLabelFont(42);
  gStyle->SetLabelSize(0.05);
  gStyle->SetTitleFont(42);
  gStyle->SetTitleSize(0.07);
}

void drawHeader(bool isPreliminary = false)
{
  std::string cms("#font[62]{CMS}");
  if(isPreliminary) cms += " #scale[0.8]{#font[52]{Preliminary}}";
  TLatex *lat = new TLatex;
  lat->SetTextSize(0.038);
  lat->DrawLatexNDC(0.12, 0.93, cms.c_str());
  lat->SetTextFont(42);
  lat->DrawLatexNDC(0.66, 0.93, Form("%2.1f fb^{-1} (13 TeV)", luminosity["2016"]+luminosity["2017"]+luminosity["2018"]));
}

double intersection(TGraph *gr, double value)
{
  for(int i=0; i<gr->GetN()-1; i++) {
    double x1, y1, x2, y2;
    gr->GetPoint(i, x1, y1);
    gr->GetPoint(i+1, x2, y2);
    if( (y1 < value && y2 >= value) ||
	(y1 > value && y2 <= value) ) {
      double m = (y2-y1)/(x2-x1);
      double x = x1 + (value - y1)/m;
      return x;
    }
  }
  // did not find an intersection
  return -1;
}

int main(int argc, char *argv[])
{
  std::string limitDirectory = "/uscms/homes/c/cawest/diphoton/egm_test/CMSSW_10_2_16/src/HiggsAnalysis/CombinedLimit";
  if(argc > 2) {
    std::cout << "Syntax: limit.exe [combine directory]" << std::endl;
    return -1;
  }
  else if(argc == 2) {
    limitDirectory = argv[1];
  }

  limit(limitDirectory);
}

void limit(const std::string &directory)
{

  // ADD limits
  // oneLimit(2, 1, directory);
  // oneLimit(2, 4, directory);
  // oneLimit(4, 1, directory);
  //
  // oneLimit(0, 0, directory);
  // oneLimit(0, 1, directory);

  // Unparticles
  unparLimit("0", directory);
  unparLimit("2", directory);


}

std::string kkconvention(int ned, int kk)
{
  if(ned == 0) {
    if(kk == 0) return "Neg. Int.";
    else if(kk == 1)  return "Pos. Int.";
  }
  else {
    if(kk == 1) return "HLZ";
    else if (kk == 4) return "Hewett-";
  }

  return "Non-existent convention";
}

void oneLimit(int ned, int kk, const std::string &directory)
{
  // std::map<int, std::string> kkconvention;
  // kkconvention[1] = "HLZ";
  // kkconvention[4] = "Hewett-";
  // kkconvention[0] = "GRW";

  std::vector<float> stringScales = {4000, 4500, 5000, 5500, 6000,
				     7000, 8000, 9000, 10000};
  std::vector<float> validScales;
  std::vector<float> minus2Sigma, minus1Sigma, mean, plus1Sigma, plus2Sigma;
  std::vector<float> minus2SigmaError, minus1SigmaError, plus1SigmaError, plus2SigmaError;
  std::vector<float> observed;
  std::vector<float> dummy;

  TFile *f;
  for(const auto& stringScale : stringScales) {
    if(ned == 2 && kk == 4 && stringScale > 6000) continue;
    // if we are using the 2017-2018 convention, the lower-mass points are not relevant
    if(ned == 0 && stringScale < 4000) continue;
    TString filename(Form("%s/higgsCombineADDGravToGG_NED-%d_KK-%d.AsymptoticLimits.mH%d.root", directory.c_str(), ned, kk, static_cast<int>(stringScale)));
    // if ned == 0, we are using the Lambda_T convention
    if(ned == 0) filename = Form("%s/higgsCombineADDGravToGG_NegInt-%d_TuneCP2_13TeV-pythia8.AsymptoticLimits.mH%d.root", directory.c_str(), kk, static_cast<int>(stringScale));
    f = TFile::Open(filename);
    if(!f->IsOpen()) {
      std::cout << "Could not open file " << filename << std::endl;
      exit(1);
    }
    TTree *tree = static_cast<TTree*>(f->Get("limit"));
    if(tree == nullptr) {
      std::cout << "Could not get limit tree " << filename << std::endl;
      exit(1);
    }

    double limit;
    double minus2SigmaExpected, minus1SigmaExpected, meanExpected, plus1SigmaExpected, plus2SigmaExpected;
    double obs;
    tree->SetBranchAddress("limit", &limit);
    tree->GetEntry(0);
    minus2SigmaExpected=limit;
    tree->GetEntry(1);
    minus1SigmaExpected=limit;
    tree->GetEntry(2);
    meanExpected=limit;
    tree->GetEntry(3);
    plus1SigmaExpected=limit;
    tree->GetEntry(4);
    plus2SigmaExpected=limit;
    tree->GetEntry(5);
    obs=limit;

    double xSec;
    xSec=1;
    if(tree->GetEntries() > 1) {
      float scale = stringScale*xSec;
      // Hewett- convention has an additional factor relative to the Pythia8 convention
      float lambdaT_to_mS = pow(2/TMath::Pi(), 0.25);
      if(ned==0 && kk==0) scale *= lambdaT_to_mS;
      validScales.push_back(scale);
      mean.push_back(meanExpected*xSec);
      minus2SigmaError.push_back(abs(minus2SigmaExpected-meanExpected)*xSec);
      minus1SigmaError.push_back(abs(minus1SigmaExpected-meanExpected)*xSec);
      plus1SigmaError.push_back(abs(plus1SigmaExpected-meanExpected)*xSec);
      plus2SigmaError.push_back(abs(plus2SigmaExpected-meanExpected)*xSec);
      minus2Sigma.push_back(minus2SigmaExpected);
      minus1Sigma.push_back(minus1SigmaExpected);
      plus1Sigma.push_back(plus1SigmaExpected);
      plus2Sigma.push_back(plus2SigmaExpected);
      observed.push_back(obs*xSec);
      dummy.push_back(0);
    }

    std::cout << "n_{ED} = " << ned << " KK = " << kk << " " << stringScale << std::endl;
    std::cout << "observed: " << observed.back() << " + " << plus1SigmaError.back() << " - " << minus1SigmaError.back() << "\n" << std::endl;

  }

  setStyle();
  TCanvas *c = new TCanvas;
  if(useLogy) c->SetLogy();

  TGraph *gr = new TGraph(mean.size(), validScales.data(), mean.data());
  gr->SetTitle(";M_{S} (GeV);Signal strength");
  gr->SetMarkerStyle(kFullCircle);
  gr->GetYaxis()->SetTitleOffset(1.4);
  gr->GetYaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetTitleSize(0.04);
  gr->GetXaxis()->SetNdivisions(505);
  gr->SetLineWidth(3);
  gr->SetMinimum(0.01);
  gr->SetMaximum(500);
  if(!useLogy) {
    gr->SetMinimum(0);
    gr->SetMaximum(3);
  }
  // expected limit +/- 1 sigma
  TGraphAsymmErrors *grMean = new TGraphAsymmErrors(mean.size(), validScales.data(), mean.data(),
						    dummy.data(), dummy.data(),
						    minus1SigmaError.data(), plus1SigmaError.data());
  grMean->SetLineColor(kBlack);
  grMean->SetFillColor(kGreen+1);

  TGraphAsymmErrors *grPlus1Sigma = new TGraphAsymmErrors(mean.size(), validScales.data(), plus1Sigma.data(),
							  dummy.data(), dummy.data(), dummy.data(), dummy.data());

  TGraphAsymmErrors *grMinus1Sigma = new TGraphAsymmErrors(mean.size(), validScales.data(), minus1Sigma.data(),
							  dummy.data(), dummy.data(), dummy.data(), dummy.data());


  // expected limit +/- 2 sigma
  TGraphAsymmErrors *grMean2Sigma = new TGraphAsymmErrors(mean.size(), validScales.data(), mean.data(),
							  dummy.data(), dummy.data(),
							  minus2SigmaError.data(), plus2SigmaError.data());
  grMean2Sigma->SetFillColor(kYellow);

  TGraph *grObserved = new TGraph(observed.size(), validScales.data(), observed.data());
  grObserved->SetLineWidth(2);
  grObserved->SetMarkerSize(2);

  // draw all limits
  gr->Draw("AL");
  grMean2Sigma->Draw("L3");
  grMean->Draw("L3");
  std::cout << "Expected limit (mu=1): " << intersection(grMean, 1)
	    << " + "
	    << intersection(grPlus1Sigma, 1) - intersection(grMean, 1)
	    << " - "
	    <<  intersection(grMean, 1) - intersection(grMinus1Sigma, 1) << std::endl;

  grMean->Draw("LX,same");
  if(drawObservedLimit) grObserved->Draw("LP");

  TLine * l = new TLine(gr->GetXaxis()->GetXmin(), 1, gr->GetXaxis()->GetXmax(), 1);
  l->SetLineColor(kBlack);
  l->SetLineStyle(kDashed);
  l->Draw();

  TLegend *leg = new TLegend(0.5, 0.6, 0.85, 0.9);
  if(drawObservedLimit) leg->AddEntry(grObserved, "Observed 95% CL limit", "L");
  leg->AddEntry(grMean, "Expected 95% CL limit", "L");
  leg->AddEntry(grMean, "Expected limit #pm 1 #sigma", "F");
  leg->AddEntry(grMean2Sigma, "Expected limit #pm 2 #sigma", "F");
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->Draw();

  TLatex *lat = new TLatex;
  if( ned!=-1 ) {
    const std::string convention(kkconvention(ned, kk));
    lat->DrawLatexNDC(0.2, 0.8, Form("%s", convention.c_str()));
    if( convention == "HLZ") lat->DrawLatexNDC(0.2, 0.7, Form("N_{ED} = %d", ned));
  }

  drawHeader();

  std::vector<std::string> extensions = {"pdf", "png"};
  for (const auto& extension : extensions) {
    if(ned == 0) c->Print(Form("plots/limits_ADDGravToGG_NegInt-%d.%s", kk, extension.c_str()));
    else c->Print(Form("plots/limits_ADDGravToGG_NED-%d_KK-%d.%s", ned, kk, extension.c_str()));
  }
}

void unparLimit(std::string spin, const std::string &directory)
{

  std::vector<std::string> dus = {"1p1", "1p5", "1p9"};
  std::map<std::string, std::vector<int>> lambdaUmap = {{"Spin0_du1p1", {10000, 4000, 8000}},
                                                  {"Spin0_du1p5", {2000, 2500, 3500}},
                                                  {"Spin0_du1p9", {2000, 2500, 3500}},
                                                  {"Spin2_du1p1", {2000, 2500, 3000}},
                                                  {"Spin2_du1p5", {2000, 2500, 3000}},
                                                  {"Spin2_du1p9", {2000, 2500, 3500}}
                                                 };

  std::vector<float> lambdaUvec;
  std::vector<float> minus2Sigma, minus1Sigma, mean, plus1Sigma, plus2Sigma;
  std::vector<float> minus2SigmaError, minus1SigmaError, plus1SigmaError, plus2SigmaError;
  std::vector<float> observed;
  std::vector<float> dummy;


  TFile *f;
  for(const auto& du: dus ){
      std::string spin_du = "Spin" + spin + "_du" + du;
      std::vector<int> lambdaUs = lambdaUmap[spin_du];

      for (auto& lambdaU: lambdaUs ){
        std::string pointName = "UnparToGG_";
        pointName += spin_du;
        pointName += "_LambdaU-";
        pointName += std::to_string(lambdaU);
        pointName += "_TuneCP2_13TeV_pythia8";
        //std::cout << pointName << std::endl;
        TString filename(Form("%s/higgsCombine%s.AsymptoticLimits.mH%d.root", directory.c_str(), pointName.c_str(), lambdaU));
        std::cout << filename << std::endl;

        f = TFile::Open(filename);

        if(!f->IsOpen()) {
          std::cout << "Could not open file " << filename << std::endl;
          exit(1);
        }

        TTree *tree = static_cast<TTree*>(f->Get("limit"));
        if(tree == nullptr) {
          std::cout << "Could not get limit tree " << filename << std::endl;
          exit(1);
        }

        double limit;
        double minus2SigmaExpected, minus1SigmaExpected, meanExpected, plus1SigmaExpected, plus2SigmaExpected;
        double obs;
        tree->SetBranchAddress("limit", &limit);
        tree->GetEntry(0);
        minus2SigmaExpected=limit;
        tree->GetEntry(1);
        minus1SigmaExpected=limit;
        tree->GetEntry(2);
        meanExpected=limit;
        tree->GetEntry(3);
        plus1SigmaExpected=limit;
        tree->GetEntry(4);
        plus2SigmaExpected=limit;
        tree->GetEntry(5);
        obs=limit;

        double xSec;
        xSec=1;
        if(tree->GetEntries() > 1) {
          float scale = lambdaU*xSec;
          lambdaUvec.push_back(scale);
          mean.push_back(meanExpected*xSec);
          minus2SigmaError.push_back(abs(minus2SigmaExpected-meanExpected)*xSec);
          minus1SigmaError.push_back(abs(minus1SigmaExpected-meanExpected)*xSec);
          plus1SigmaError.push_back(abs(plus1SigmaExpected-meanExpected)*xSec);
          plus2SigmaError.push_back(abs(plus2SigmaExpected-meanExpected)*xSec);
          minus2Sigma.push_back(minus2SigmaExpected);
          minus1Sigma.push_back(minus1SigmaExpected);
          plus1Sigma.push_back(plus1SigmaExpected);
          plus2Sigma.push_back(plus2SigmaExpected);
          observed.push_back(obs*xSec);
          dummy.push_back(0);
        }

        std::cout << pointName << std::endl;
        std::cout << "observed: " << observed.back() << " + " << plus1SigmaError.back() << " - " << minus1SigmaError.back() << "\n" << std::endl;
        std::cout << "meanExpected: " << mean.back() << " + " << plus1SigmaError.back() << " - " << minus1SigmaError.back() << "\n" << std::endl;
    } // end loop over lambdaUs

    setStyle();
    TCanvas *c = new TCanvas;
    if(useLogy) c->SetLogy();

    TGraph *gr = new TGraph(mean.size(), lambdaUvec.data(), mean.data());
    gr->SetTitle(";#Lambda_{U} (GeV);Signal strength");
    gr->SetMarkerStyle(kFullCircle);
    gr->GetYaxis()->SetTitleOffset(1.4);
    gr->GetYaxis()->SetTitleSize(0.04);
    gr->GetXaxis()->SetTitleSize(0.04);
    gr->GetXaxis()->SetNdivisions(505);
    gr->SetLineWidth(3);
    gr->SetMinimum(0.01);
    gr->SetMaximum(500);
    if(!useLogy) {
      gr->SetMinimum(0);
      gr->SetMaximum(3);
    }

    // expected limit +/- 1 sigma
    TGraphAsymmErrors *grMean = new TGraphAsymmErrors(mean.size(), lambdaUvec.data(), mean.data(),
                  dummy.data(), dummy.data(),
                  minus1SigmaError.data(), plus1SigmaError.data());
    grMean->SetLineColor(kBlack);
    grMean->SetFillColor(kGreen+1);

    TGraphAsymmErrors *grPlus1Sigma = new TGraphAsymmErrors(mean.size(), lambdaUvec.data(), plus1Sigma.data(),
  							  dummy.data(), dummy.data(), dummy.data(), dummy.data());

    TGraphAsymmErrors *grMinus1Sigma = new TGraphAsymmErrors(mean.size(), lambdaUvec.data(), minus1Sigma.data(),
  							  dummy.data(), dummy.data(), dummy.data(), dummy.data());

    // expected limit +/- 2 sigma
    TGraphAsymmErrors *grMean2Sigma = new TGraphAsymmErrors(mean.size(), lambdaUvec.data(), mean.data(),
                							  dummy.data(), dummy.data(),
                							  minus2SigmaError.data(), plus2SigmaError.data());
    grMean2Sigma->SetFillColor(kYellow);

    TGraph *grObserved = new TGraph(observed.size(), lambdaUvec.data(), observed.data());
    grObserved->SetLineWidth(2);
    grObserved->SetMarkerSize(2);

    // draw all limits
    gr->Draw("AL");
    grMean2Sigma->Draw("L3");
    grMean->Draw("L3");
    std::cout << "Expected limit (mu=1): " << intersection(grMean, 1)
        << " + "
        << intersection(grPlus1Sigma, 1) - intersection(grMean, 1)
        << " - "
        <<  intersection(grMean, 1) - intersection(grMinus1Sigma, 1) << std::endl;

    grMean->Draw("LX,same");
    if(drawObservedLimit) grObserved->Draw("LP");

    TLine * l = new TLine(gr->GetXaxis()->GetXmin(), 1, gr->GetXaxis()->GetXmax(), 1);
    l->SetLineColor(kBlack);
    l->SetLineStyle(kDashed);
    l->Draw();

    TLegend *leg = new TLegend(0.5, 0.6, 0.85, 0.9);
    if(drawObservedLimit) leg->AddEntry(grObserved, "Observed 95% CL limit", "L");
    leg->AddEntry(grMean, "Expected 95% CL limit", "L");
    leg->AddEntry(grMean, "Expected limit #pm 1 #sigma", "F");
    leg->AddEntry(grMean2Sigma, "Expected limit #pm 2 #sigma", "F");
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->Draw();

    TLatex *lat = new TLatex;
    lat->DrawLatexNDC(0.2, 0.8, Form("%s", spin_du.c_str()));

    drawHeader();

    std::vector<std::string> extensions = {"pdf", "png"};
    for (const auto& extension : extensions) {
      c->Print(Form("plots/limits_%s.%s", spin_du.c_str(), extension.c_str()));
    }

    lambdaUvec.clear();
    minus2Sigma.clear();
    minus1Sigma.clear();
    mean.clear();
    plus1Sigma.clear();
    plus2Sigma.clear();
    minus2SigmaError.clear();
    minus1SigmaError.clear();
    plus1SigmaError.clear();
    plus2SigmaError.clear();
    observed.clear();
    dummy.clear();
  } // end loop over du and spin
}
