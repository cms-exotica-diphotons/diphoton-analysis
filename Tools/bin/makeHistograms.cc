#include "diphoton-analysis/Tools/interface/sampleList.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"

#include "TCanvas.h"
#include "TString.h"
#include "TH1.h"
#include "TFile.h"

#include <chrono>

void allSamples(const std::string &region, const std::string &year, TFile * output);
std::string getSampleBase(const std::string & sampleName, const std::string & year);
std::string getBase(const std::string & sampleName);
void addFakePrediction(const std::string &region, const std::string &year, TFile * output);
std::string addCutsPerSample(const std::string &cut, const std::string &sample, const std::string &region, const std::string &year);
std::map<std::string, std::string> reweightingList(std::vector<std::string> &postfixes);
void addTheoryUncertanties(std::map<std::string, TH1F*> &histograms, const std::string &region, TFile * output);
void overflowToLastBin(TH1F* histogram);
void getDiphotonYieldVariations(const std::string& region, const std::string& variation, const std::string& year);

int main(int argc, char *argv[])
{
  std::string region, year;

  if(argc!=3) {
    std::cout << "Syntax: makeHistograms.exe [BB/BE] [2016/2017/2018]" << std::endl;
      return -1;
  }
  else {
    region = argv[1];
    if(region!="BB" and region!="BE") {
      std::cout << "Only 'BB' and 'BE' are allowed regions. " << std::endl;
      return -1;
    }
    year = argv[2];
    if(year!="2016" and year!="2017" and year!="2018") {
      std::cout << "Only '2016', 2017' and '2018' are allowed years. " << std::endl;
      return -1;
    }
  }

  // include signal samples but not unskimmed data samples
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

  init(false, true);

  TFile *output = new TFile(Form("datacards/Minv_histos_%s_%s.root", region.c_str(), year.c_str()), "recreate");
  output->mkdir(region.c_str());

  // add fake rate prediction histograms
  addFakePrediction(region, year, output);

  // // loop over all other samples
  // allSamples(region, year, output);
  output->Write();
  output->Close();

  // // re-open files and add statistical error to files
  // getDiphotonYieldVariations(region, "kfactorStat0", year);
  // getDiphotonYieldVariations(region, "kfactorStat1", year);
  // getDiphotonYieldVariations(region, "kfactorStat2", year);
  // getDiphotonYieldVariations(region, "kfactorStat3", year);

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  std::cout << "Time Elapsed = " << std::chrono::duration_cast<std::chrono::hours>(end - begin).count() << "[hrs]" << std::endl;

  std::cout << "DONE " << std::endl;
}

void addFakePrediction(const std::string &region, const std::string &year, TFile * output)
{
  // add fake rate prediction histograms
  std::vector<std::string> fakeRates = {"average", "doublemuon", "jetht"};
  std::map<std::string, std::string> histPostFix;
  histPostFix["average"] = "";
  histPostFix["jetht"] = "_fake_sampleUp";
  histPostFix["doublemuon"] = "_fake_sampleDown";
  for (const auto& fakeRate : fakeRates) {
    TFile *fakes = new TFile(Form("data/fakes_%s_%s.root", year.c_str(), fakeRate.c_str()));
    TH1F *fakeHist = static_cast<TH1F*>(fakes->Get(Form("%s/gj", region.c_str())));
    output->cd(region.c_str());
    fakeHist->SetName(Form("gj%s", histPostFix[fakeRate].c_str()));
    fakeHist->Write();
  }
}

std::string addCutsPerSample(const std::string &cut, const std::string &sample, const std::string &region, const std::string &year)
{
  std::string sampleCut(cut);

  // apply weights for all samples except data
  bool is2015 = sample.find("2015") != std::string::npos || sample.find("ADDGravToGG_MS") != std::string::npos;
  bool is2016 = sample.find("2016") != std::string::npos || sample.find("ADDGravToGG_MS") != std::string::npos;
  bool is2015or2016 =  is2015 || is2016;
  if( is2015or2016 ) {
    sampleCut += "*(HLT_DoublePhoton60>0 || HLT_ECALHT800>0)";
  }
  else {
    sampleCut += "*(HLT_DoublePhoton70>0 || HLT_ECALHT800>0)";
  }
  if( sample.find("data") == std::string::npos ) {
    sampleCut+="*weightAll*" + std::to_string(luminosity[year]);
    // add photon efficiency scale factor, zero sigma from mean
    sampleCut+="*" + std::string(scale_factor_cut(atoi(year.c_str()), 0).Data());
    // add pileup weights, zero sigma from mean
    sampleCut+="*" + std::string(npv_reweight_str(atoi(year.c_str()), 0).Data());

    if( sample.find("gg70_2016") != std::string::npos
	or sample.find("gg70_2017") != std::string::npos
	or sample.find("gg70_2018") != std::string::npos) {
      // GG Pythia samples include box diagram but signal does not
      sampleCut += "*(pdf_id1 != 21 && pdf_id2 != 21)";
    }

    // // need to increase selection for Pythia ADD cuts to avoid negative weights
    // // from background subtraction
    if( sample.find("ADD") != std::string::npos or sample.find("Unpar")!= std::string::npos
	or sample.find("gg70") != std::string::npos ) {
      if( sample.find("ADDGravToGG_NegInt") != std::string::npos or sample.find("Unpar")!= std::string::npos
          || sample.find("gg70_2016") != std::string::npos
          || sample.find("gg70_2017") != std::string::npos
          || sample.find("gg70_2018") != std::string::npos ) sampleCut += "*(Diphoton.Minv > 600)";
      else sampleCut += "*(Diphoton.Minv > 600)";
    }
  }
  else {
    sampleCut += "*(Diphoton.Minv < 1000)";
  }
  // apply k-factor to Sherpa GG sample
  if( sample.find("gg_R2F2_") != std::string::npos) {
    if( is2015 ) sampleCut += "*" + kfactorString(region, "R2F2_125GeV_CT10");
    else sampleCut += "*" + kfactorString(region, "R2F2_125GeV_NNPDF");
  }
  else if( sample.find("gg_R0p5F0p5_") != std::string::npos) {
    if( is2015 ) sampleCut += "*" + kfactorString(region, "R0p5F0p5_125GeV_CT10");
    else sampleCut += "*" + kfactorString(region, "R0p5F0p5_125GeV_NNPDF");
  }
  else if( sample.find("gg_") != std::string::npos) {
    if( is2015 ) sampleCut += "*" + kfactorString(region, "R1F1_125GeV_CT10");
    else sampleCut += "*" + kfactorString(region, "R1F1_125GeV_NNPDF");
  }

  return sampleCut;
}

std::map<std::string, std::string> reweightingList(std::vector<std::string> &postfixes)
{
  std::map<std::string, std::string> reweightings;
  std::vector<std::string> variations = {"energyScaleStat", "energyScaleSyst", "energyScaleGain", "energySigma"};
  std::vector<std::string> directions = {"Up", "Down"};
  // std::vector<std::string> variations = {"energyScaleStat"};
  // std::vector<std::string> directions = {"Up"};

  // without additional variations
  reweightings[""] = "";
  postfixes = {""};

  for(const auto& variation : variations) {
    for(const auto& direction : directions) {
      std::string postfix("_");
      postfix += variation;
      postfix += direction;
      postfixes.push_back(postfix);
      std::string reweighting = "*(Photon1.";
      reweighting += variation + direction;
      reweighting += "*Photon2.";
      reweighting += variation + direction;
      reweighting += ")";
      reweightings[postfix] = reweighting;
    }
  }

  return reweightings;
}

void addTheoryUncertanties(std::map<std::string, TH1F*> &histograms, const std::string &region, TFile * output)
{
  // create additional histograms for scale variations only in BB or BE
  TH1F *scaleUp = dynamic_cast<TH1F*>(histograms["gg_diphotonkfactorScalesUp"]->Clone());
  std::string histNameBase("gg_diphotonkfactorScales");
  std::string histName = histNameBase + region + "Up";
  scaleUp->SetName(histName.c_str());
  histograms[histName] = scaleUp;
  TH1F *scaleDown = dynamic_cast<TH1F*>(histograms["gg_diphotonkfactorScalesDown"]->Clone());
  histName = histNameBase + region + "Down";
  scaleDown->SetName(histName.c_str());
  histograms[histName] = scaleDown;

  overflowToLastBin(histograms["gg"]);
  histograms["gg"]->Write();
  // create histograms for PDF uncertainties
  const int bin_offset = 10; // MCFM output starts at 500 GeV
  std::string pdfFile("data/pdf_uncert_nlo_" + region + ".root");
  TFile *fPDF = TFile::Open(pdfFile.c_str());
  std::vector<std::string> variations = {"Up", "Down"};
  for(const auto &  variation : variations) {
    for(int i = 1; i <= 50; i++) {
      fPDF->cd("");
      std::string pdfHistName(region + "/" + "gg_pdf" + std::to_string(i) + variation);
      TH1F* tmp_pdf_hist = dynamic_cast<TH1F*>(fPDF->Get(pdfHistName.c_str()));
      // convert PDF fractional uncertainty to a variation on gg histogram
      std::string newPdfHistName("gg_pdf" + std::to_string(i) + variation);
      TH1F* variation = dynamic_cast<TH1F*>(histograms["gg"]->Clone(newPdfHistName.c_str()));
      for(int i = 0; i < tmp_pdf_hist->GetNbinsX(); i++) {
	float newValue = (1 + tmp_pdf_hist->GetBinContent(i))*histograms["gg"]->GetBinContent(i+bin_offset);
	variation->SetBinContent(i+bin_offset, newValue);
      }
      output->cd(region.c_str());
      overflowToLastBin(variation);
      variation->Write();
      histograms[pdfHistName] = variation;
    }
  }
}

void overflowToLastBin(TH1F* histogram)
{
  int nbins = histogram->GetNbinsX();
  float lastBin = histogram->GetBinContent(nbins);
  float overflow = histogram->GetBinContent(nbins+1);
  histogram->SetBinContent(nbins, lastBin + overflow);
  histogram->SetBinContent(nbins+1, 0.0);
}

void allSamples(const std::string &region, const std::string &year, TFile * output)
{

  int nBins = 120;
  double xMin = 0.0;
  double xMax = 6000.;

  std::map<std::string, std::string> cuts;
  // photon Minv selection needs to come later
  cuts["BB"] = "isGood*(Diphoton.deltaR > 0.45 && Photon1.pt>125 && Photon2.pt>125 && Photon1.isEB && Photon2.isEB)";
  cuts["BE"] = "isGood*(Diphoton.deltaR > 0.45 && Photon1.pt>125 && Photon2.pt>125 && ( (Photon1.isEB && Photon2.isEE) || (Photon2.isEB &&  Photon1.isEE )))";

  std::vector<std::string> samples = getSampleList();

  // add scale variations
  std::vector<std::string> years = {"2016", "2017", "2018"};
  std::vector<std::string> scaleVariations = {"R2F2", "R0p5F0p5"};
  for (const auto &year : years) {
    for (const auto &scaleVariation : scaleVariations) {
      samples.push_back("gg_" + scaleVariation + "_" + year);
    }
  }

  for(auto sample : samples) {
    std::cout << sample << std::endl;
  }

  std::map<std::string, TH1F*> histograms;
  for(auto sample : samples) {
    // skip the Sherpa GEN trees
    if( sample.find("gg_gen") != std::string::npos) continue;
    // skip the Sherpa trees with the fake rate ntuple format
    if( sample.find("gg_fake") != std::string::npos) continue;
    // skimmed samples give equivalent results
    if( sample.find("unskimmed") != std::string::npos ) continue;
    // use data-driven gamma+jets prediction instead
    if( sample.find("gj") != std::string::npos ) continue;
    // skip most samples that do not include the year
    // 2016 ADD sample names do not encode year and so should not be skipped
    if (sample.find("gg70") == std::string::npos and sample.find("ADDGravToGG_MS") == std::string::npos) {
      // only consider the year of interest
      if( sample.find(year) == std::string::npos ) continue;
    }
    // enable for testing only!
    //if( sample.find("ADDGravToGG_NegInt-0_LambdaT-9000") == std::string::npos
    //and sample.find("ADDGravToGG_MS-9000_NED-4_KK-1") == std::string::npos
    //	) continue;
    //and sample.find("gg") == std::string::npos) continue;

    // add additional sample-specific cuts (MC weights or year-dependent trigger)
    std::string sampleCut = addCutsPerSample(cuts[region], sample, region, year);

    // add reweightings for energy scale systematics
    std::vector<std::string> postfixes;
    std::map<std::string, std::string> reweightings = reweightingList(postfixes);
    postfixes.push_back("_effUp");
    postfixes.push_back("_effDown");
    postfixes.push_back("_pileupUp");
    postfixes.push_back("_pileupDown");

    //    TEntryList *elist;
    for(const auto& postfix : postfixes) {
      std::string baseName(getSampleBase(sample, year));
      baseName += postfix;
      // do not perform additional systematic variations on k-factor scale variations
      if(baseName.find("diphotonkfactorScale") != std::string::npos and
	 (baseName.find("energy") != std::string::npos or
	  baseName.find("eff") != std::string::npos or
	  baseName.find("pileup") != std::string::npos)) {
	continue;
      }
      TH1F *hist = new TH1F(baseName.c_str(), baseName.c_str(), nBins, xMin, xMax);
      histograms[baseName] = hist;
      std::string varname("Diphoton.Minv");
      // efficiency scale factors are applied to the cut rather than the plotting variable
      bool eff_scale_factor = postfix.find("_eff") != std::string::npos
	or postfix.find("_pileup") != std::string::npos;
      if(!eff_scale_factor) {
	varname += reweightings[postfix];
      }
      std::string cut("*(");
      cut += varname;
      std::string minv_cut("500");
      if(sample.find("UnparToGG") != std::string::npos or sample.find("ADDGravToGG") != std::string::npos or sample.find("gg70") != std::string::npos) {
	minv_cut = "600";
      }
      cut += ">" + minv_cut + ")";
      std::string fullCut(sampleCut);
      fullCut += cut;

      // do not apply reweightings to data, only MC
      if( sample.find("data") == std::string::npos ) {
	int year_int = atoi(year.c_str());
	if(postfix == "_effUp") {
	  std::string old_str(scale_factor_cut(year_int, 0).Data());
	  fullCut.replace(fullCut.find(old_str), old_str.size(), scale_factor_cut(year_int, 1).Data());
	}
	else if(postfix == "_effDown") {
	  std::string old_str(scale_factor_cut(year_int, 0).Data());
	  fullCut.replace(fullCut.find(old_str), old_str.size(), scale_factor_cut(year_int, -1).Data());
	}
	else if(postfix == "_pileupUp") {
	  std::string old_str(npv_reweight_str(year_int, 0).Data());
	  fullCut.replace(fullCut.find(old_str), old_str.size(), npv_reweight_str(year_int, 1).Data());
	}
	else if(postfix == "_pileupDown") {
	  std::string old_str(npv_reweight_str(year_int, 0).Data());
	  fullCut.replace(fullCut.find(old_str), old_str.size(), npv_reweight_str(year_int, -1).Data());
	}
      }
      std::cout << "Making histograms for sample " << hist->GetName()
		<< " with basename " << baseName
		<< " with cut\n" << fullCut
		<< " and variable " << varname << std::endl;
      chains[getBase(sample)]->Project(baseName.c_str(), varname.c_str(),  fullCut.c_str());
      std::cout << "Integral: " << histograms[baseName]->Integral() << std::endl;
      output->cd(region.c_str());
    }
  }

  // subtract nonresonant background
  for(auto histogram : histograms) {
    std::string title(histogram.second->GetTitle());
    if(title.find("ADDGravToGG_") != std::string::npos or title.find("UnparToGG_") != std::string::npos) {
      std::size_t systPosition = title.find("_energy");
      std::string syst;

      if(systPosition != std::string::npos) {
	       syst = title.substr(systPosition);
      }
      systPosition = title.find("_pileup");

      if(systPosition != std::string::npos) {
	       syst = title.substr(systPosition);
      }
      systPosition = title.find("_eff");

      if(systPosition != std::string::npos) {
	       syst = title.substr(systPosition);
      }

      // Actual Background Subtraction
      std::string histName;
      if(title.find("ADDGravToGG_NegInt") != std::string::npos or title.find("UnparToGG_") != std::string::npos) {
          histName = "gg70_" + year;
      }
      else {
	       histName = "gg70_sherpa_2016";
      }
      if(!syst.empty()) {
	       histName += syst;
      }

      histogram.second->Add(histograms[histName], -1);
    }
    histogram.second->Write();
  }

  // add PDF uncertainty histograms
  addTheoryUncertanties(histograms, region, output);

  // move overflow to last bin
  for(auto histogram : histograms) {
    overflowToLastBin(histogram.second);
  }

}

// remove year
std::string getSampleBase(const std::string & sampleName, const std::string & year)
{
  // background subtraction samples need to be handled separately
  if( sampleName.find("gg70") != std::string::npos) {
    return sampleName;
  }

  std::string newString(sampleName);
  if( sampleName.find("_201") != std::string::npos) {
    newString.replace(newString.find("_201"), 5, "");
  }
  if(sampleName.find("_R2F2") != std::string::npos) {
    newString.replace(newString.find("_R2F2"), 5, "_diphotonkfactorScalesUp");
  }
  if(sampleName.find("_R0p5F0p5") != std::string::npos) {
    newString.replace(newString.find("_R0p5F0p5"), 9, "_diphotonkfactorScalesDown");
  }
  // "data_obs" is always the name of the data observation histogram
  std::string data("data_" + year);
  if( sampleName == data) newString = "data_obs";
  return newString;
}

// ignore variations to get dataset name
std::string getBase(const std::string & sampleName)
{
  if(sampleName == "gg_R2F2_2016" ) return "gg_2016";
  if(sampleName == "gg_R0p5F0p5_2016" ) return "gg_2016";
  if(sampleName == "gg_R2F2_2017" ) return "gg_2017";
  if(sampleName == "gg_R0p5F0p5_2017" ) return "gg_2017";
  if(sampleName == "gg_R2F2_2018" ) return "gg_2018";
  if(sampleName == "gg_R0p5F0p5_2018" ) return "gg_2018";
  return sampleName;
}


void getDiphotonYieldVariations(const std::string& region, const std::string& variation, const std::string& year)
{
  TString histID("id1");
  // barrel-endcap fit has a different histogram ID in MCFM
  if(region == "BE") histID = "id15";

  TString histogramFile(Form("datacards/Minv_histos_%s_%s.root", region.c_str(), year.c_str()));
  // put dummy values here for now
  if(variation.find("kfactorStat") != std::string::npos) {
    std::string varString(variation);
    // remove string "kfactorStat" from variation name; number afterwards is the fit parameter
    int parameter = atoi(varString.replace(0, 11, "").c_str());
    TFile *input = TFile::Open(histogramFile, "update");
    TH1D* diphoton = static_cast<TH1D*>(input->Get(Form("%s/gg", region.c_str())));
    TH1D* diphotonStatUp = static_cast<TH1D*>(diphoton->Clone(Form("gg_kfactorStat%dUp", parameter)));
    TH1D* diphotonStatDown = static_cast<TH1D*>(diphoton->Clone(Form("gg_kfactorStat%dDown", parameter)));
    TF1 *kfactorFunction = kfactor(region, "R1F1_125GeV_NNPDF");
    TString fitFunc("pol3");
    TString filename="data/kfactor_" + region + "_R1F1_125GeV_NNPDF.root";
    TFile *file = TFile::Open(filename);
    TFitResult* fitResult = static_cast<TFitResult*>(file->Get(Form("TFitResult-%s-%s", histID.Data(), fitFunc.Data())));

    TF1 *kfactorStatUp = eigenvectorVariation(true, parameter, kfactorFunction, fitResult);
    TF1 *kfactorStatDown = eigenvectorVariation(false, parameter, kfactorFunction, fitResult);
    for(int i=0; i <= diphotonStatUp->GetNbinsX(); i++) {
      float binContent = diphoton->GetBinContent(i);
      float binCenter = diphoton->GetBinCenter(i);
      float statUp = kfactorStatUp->Eval(binCenter)/kfactorFunction->Eval(binCenter);
      float statDown = kfactorStatDown->Eval(binCenter)/kfactorFunction->Eval(binCenter);
      diphotonStatUp->SetBinContent(i, binContent*statUp);
      diphotonStatDown->SetBinContent(i, binContent*statDown);
    }

    bool exists = input->cd(region.c_str());
    if(!exists) {
      input->mkdir(region.c_str());
      input->cd(region.c_str());
    }
    diphotonStatUp->Write();
    diphotonStatDown->Write();
    input->Write();
    input->Close();
    file->Close();
  }
}
