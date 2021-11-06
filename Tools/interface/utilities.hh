#ifndef UTILITIES_HH
#define UTILITIES_HH

#include "TMath.h"
#include "TMatrixDSym.h"
#include "TMatrixT.h"
#include "TVectorT.h"
#include "TFitResult.h"
#include "TString.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include <string>

TF1* kfactor(const std::string & region, const std::string & scales)
{
  std::map<std::string, std::string> fitFuncs;
  fitFuncs["BB"] = "pol3";
  fitFuncs["BE"] = "pol3";
  const char *cmssw_base = getenv("CMSSW_BASE");
  if(cmssw_base==nullptr) {
    std::cout << "Please issue cmsenv before running" << std::endl;
    exit(-1);
  }

  TFile *f = new TFile(Form("%s/src/diphoton-analysis/Tools/data/kfactor_%s_%s.root", cmssw_base, region.c_str(), scales.c_str()));
  TF1 *kfactorFunction;
  f->GetObject(fitFuncs[region].c_str(), kfactorFunction);
  f->Close();
  return kfactorFunction;
}

std::string kfactorString(const std::string & region, const std::string & scales, const std::string& reweightVariable = "qscale")
{
  TF1 *kfactorFunction = kfactor(region, scales);

  const std::string squared = reweightVariable + "*" + reweightVariable;
  const std::string cubed = squared + "*" + reweightVariable;

  TString kfactorWeight;
  if(region == "BB") kfactorWeight = Form("(%6.6e + %6.6e*%s + %6.6e*%s + %6.6e*%s)",
					  kfactorFunction->GetParameter(0), kfactorFunction->GetParameter(1), reweightVariable.c_str(),
					  kfactorFunction->GetParameter(2),  squared.c_str(), kfactorFunction->GetParameter(3), cubed.c_str());
  else kfactorWeight = Form("(%6.6e + %6.6e*%s + %6.6e*%s + %6.6e*%s)",
			    kfactorFunction->GetParameter(0), kfactorFunction->GetParameter(1), reweightVariable.c_str(),
			    kfactorFunction->GetParameter(2),  squared.c_str(), kfactorFunction->GetParameter(3), cubed.c_str());

  return kfactorWeight.Data();
}

TH1D* getHists(const std::string & base, const std::string & region, const std::string & type)
{
  unsigned int nfiles=10;
  if(type.find("NNLO") != std::string::npos) nfiles = 50;
  TH1D *sum = nullptr;
  for(unsigned int i=1; i<=nfiles; i++) {
    TString filename(Form("%s/%s_%s_R1F1_Mass0p23To2TeV_13TeV/Job%d/bin/ReRoot.root", base.c_str(), region.c_str(), type.c_str(), i));
    TFile *f = TFile::Open(filename);
    TH1D *tempHist = static_cast<TH1D*>(f->Get("hist1"));
    if(tempHist==nullptr) continue;
    if(sum == nullptr) {
      sum = static_cast<TH1D*>(tempHist->Clone());
      sum->SetDirectory(nullptr);
      sum->SetBit(TH1::kIsAverage);
    }
    else {
      tempHist->SetBit(TH1::kIsAverage);
      sum->Add(tempHist);
    }

    f->Close();
  }

  return sum;
}


TH1D* getHistsMCFM(const std::string & base, const std::string & type, const std::string & histName = "id1", const int binLow = 0, const int binHigh = 0 )
{
  unsigned int seedBase = 1189;
  unsigned int nfiles=10;
  if(type.find("nnlo") != std::string::npos) nfiles = 50;
  TH1D *sum = nullptr;
  for(unsigned int i=1; i<=nfiles; i++) {
    unsigned int seed = seedBase + i;
    // commented out 20NOV2018
    //    TString filename(Form("%s/%s_seed%d.root", base.c_str(), type.c_str(), seed));
    TString filename(Form("%s/%s_%d.root", base.c_str(), type.c_str(), seed));
    // later jobs have a different format
    if(binHigh!=0) {
      TString jobName(Form("%s_%d_%d_%d", type.c_str(), seed, binLow, binHigh));
      // MCFM truncates job names longer than 66 characters
      if(jobName.Length()>66) jobName.Resize(66);
      filename = Form("%s/%s.root", base.c_str(), jobName.Data());
    }
    else if(base.find("otherpdfs")!=std::string::npos) {
      TString jobName(Form("%s_%d", type.c_str(), seed));
      // MCFM truncates job names longer than 66 characters
      if(jobName.Length()>66) jobName.Resize(66);
      filename = Form("%s/%s.root", base.c_str(), jobName.Data());
    }
    TFile *f = TFile::Open(filename);
    if(!f) continue;
    if(!f->IsOpen()) continue;
    TString histID("id1");
    // need to change histogram ID if looking at barrel-endcap region
    if(base.find("_witheta")!=std::string::npos) histID = "id15";
    std::cout << histID << std::endl;
    TH1D *tempHist = static_cast<TH1D*>(f->Get(histID));
    if(tempHist==nullptr) continue;
    if(sum == nullptr) {
      sum = static_cast<TH1D*>(f->Get(histID));
      sum->SetBit(TH1::kIsAverage);
    }
    else {
      tempHist->SetBit(TH1::kIsAverage);
      sum->Add(tempHist);
    }
  }
  // scale to pb
  double fbtopb = 0.001;
  // scale by bin width
  double binWidth = (sum->GetXaxis()->GetXmax()-sum->GetXaxis()->GetXmin())/sum->GetNbinsX();
  std::cout << "binWidth: " << binWidth << std::endl;
  std::cout << "integral*binWidth: " << sum->Integral()*binWidth*fbtopb << std::endl;
  //  sum->Scale(binWidth*fbtopb);
  sum->Scale(1/binWidth);

  return sum;
}

TH1D* getHistsMCFMSumNNLO(const std::string & base, const std::string & type)
{
  TString histID("id1");
  // need to change histogram ID if looking at barrel-endcap region
  if(base.find("_witheta")!=std::string::npos) histID = "id15";

  TH1D *nnlo_500_750 = getHistsMCFM(base, type, histID.Data(), 500, 750);
  TH1D *nnlo_750_1000 = getHistsMCFM(base, type, histID.Data(), 750, 1000);
  TH1D *nnlo_1000_1500 = getHistsMCFM(base, type, histID.Data(), 1000, 1500);
  TH1D *nnlo_1500_4000 = getHistsMCFM(base, type, histID.Data(), 1500, 4000);

  nnlo_500_750->ResetBit(TH1::kIsAverage);
  nnlo_750_1000->ResetBit(TH1::kIsAverage);
  nnlo_1000_1500->ResetBit(TH1::kIsAverage);
  nnlo_1500_4000->ResetBit(TH1::kIsAverage);

  // TH1D *nnlo_sum = static_cast<TH1D*>(nnlo_500_750->Clone());
  // nnlo_sum->Add(nnlo_750_1000);
  // nnlo_sum->Add(nnlo_1000_1500);
  // nnlo_sum->Add(nnlo_1500_4000);

  TH1D *nnlo_sum = static_cast<TH1D*>(nnlo_500_750->Clone());
  for(int i=0; i<=nnlo_500_750->GetNbinsX(); i++) {

    double binContent_500_750 = nnlo_500_750->GetBinContent(i);
    double binContent_750_1000 = nnlo_750_1000->GetBinContent(i);
    double binContent_1000_1500 = nnlo_1000_1500->GetBinContent(i);
    double binContent_1500_4000 = nnlo_1500_4000->GetBinContent(i);

    double binContent = binContent_500_750 + binContent_750_1000 + binContent_1000_1500 + binContent_1500_4000;

    double binError_500_750 = nnlo_500_750->GetBinError(i);
    double binError_750_1000 = nnlo_750_1000->GetBinError(i);
    double binError_1000_1500 = nnlo_1000_1500->GetBinError(i);
    double binError_1500_4000 = nnlo_1500_4000->GetBinError(i);

    double binError = binError_500_750;
    if(binContent_750_1000 > binContent_500_750) binError = binError_750_1000;
    if(binContent_1000_1500 > binContent_750_1000) binError = binError_1000_1500;
    if(binContent_1500_4000 > binContent_1000_1500) binError = binError_1500_4000;

    nnlo_sum->SetBinContent(i, binContent);
    nnlo_sum->SetBinError(i, binError);
  }
  return nnlo_sum;
}


// get variation (up or down by 1 sigma) for parameter
// given the nominal function and the fitResult (from which the covariance
// matrix is obtained)

TF1 * eigenvectorVariation(bool up, int parameter, TF1* nominal, TFitResult* fitResult)
{
  TMatrixDSym cov = fitResult->GetCovarianceMatrix();
  TVectorT<double> eigenValues;
  TMatrixT<double> eigenVectors = cov.EigenVectors(eigenValues);
  double eigenvalue = sqrt(fabs(eigenValues[parameter]));

  TF1* func;
  if(up) {
    func = static_cast<TF1*>(nominal->Clone(Form("fUp_par%d", parameter)));
  }
  else {
    eigenvalue = -eigenvalue; // change sign for negative variations
    func = static_cast<TF1*>(nominal->Clone(Form("fDown_par%d", parameter)));
  }
  for(int i=0; i<nominal->GetNpar(); i++) {
    func->SetParameter(i, nominal->GetParameter(i) + eigenvalue*eigenVectors[i][parameter]);
  }

  return func;
}

// needed to convert from Hewett-minus convention to GRW
double k = 2/TMath::Pi();

void getSignalAndInterference(std::string pointNameBase, std::string region, TH1D*& background, TH1D *& signal, TH1D *&interference, bool update=false)
{
  TFile *f;
  // if(update) f = new TFile("data/Minv_histos_with_interference.root", "update");
  // else f = new TFile("data/Minv_histos_with_interference.root");
  f = new TFile("data/Minv_histos.root");

  // KK conventions for HLZ and Hewett- conventions are 1 and 4, respectively
  std::string pointNamePositiveInt = pointNameBase;
  pointNamePositiveInt += "_NED-4_KK-1";
  std::string pointNameNegativeInt = pointNameBase;
  pointNameNegativeInt += "_NED-2_KK-4";

  std::string backgroundHistname(region);
  backgroundHistname += "/gg70";
  background = static_cast<TH1D*>(f->Get(backgroundHistname.c_str()));
  TH1D *histPositiveInt = static_cast<TH1D*>(f->Get(pointNamePositiveInt.c_str()));
  TH1D *histNegativeInt = static_cast<TH1D*>(f->Get(pointNameNegativeInt.c_str()));

  histPositiveInt->SetMarkerColor(kRed);
  histPositiveInt->SetLineColor(kRed);
  histNegativeInt->SetMarkerColor(kBlue);

  background->Draw();
  histPositiveInt->Draw("same");
  histNegativeInt->Draw("same");

  TH1D *histPositiveInt_sub = static_cast<TH1D*>(histPositiveInt->Clone("histPositiveInt_sub"));
  histPositiveInt_sub->Add(background, -1.0);
  TH1D *histNegativeInt_sub = static_cast<TH1D*>(histNegativeInt->Clone("histNegativeInt_sub"));
  histNegativeInt_sub->Add(background, -1.0);

  histPositiveInt_sub->Draw();
  histPositiveInt_sub->GetXaxis()->SetRangeUser(500, 6000);
  histNegativeInt_sub->Draw("same");


  signal = static_cast<TH1D*>(histPositiveInt_sub->Clone(pointNameBase.c_str()));
  signal->SetName(pointNameBase.c_str());
  signal->SetTitle(pointNameBase.c_str());
  signal->Scale(k);
  signal->Add(histNegativeInt_sub);
  signal->Scale(1/(k+k*k));

  interference = static_cast<TH1D*>(histPositiveInt_sub->Clone());
  interference->SetName(Form("%s_int", pointNameBase.c_str()));
  interference->SetTitle(Form("%s_int", pointNameBase.c_str()));
  interference->Scale(k*k);
  interference->Add(histNegativeInt_sub, -1.0);
  interference->Scale(1/(k+k*k));
  interference->SetMarkerColor(kBlack);

}

#endif
