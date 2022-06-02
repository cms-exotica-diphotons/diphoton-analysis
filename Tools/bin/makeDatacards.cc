// creates combine datacards for all signal points
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "TH1.h"
#include "TFile.h"

#include "diphoton-analysis/Tools/interface/sampleList.hh" // integrated luminosity only defined once
#include "diphoton-analysis/Tools/interface/utilities.hh"

class nuisance {

public:
  nuisance(std::string syst, std::string distribution, std::vector<std::string> contribution) :
    m_syst(syst),
    m_distribution(distribution),
    m_contribution(contribution) {}
  std::string m_syst;
  std::string m_distribution;
  std::vector<std::string> m_contribution;
};

double getYield(const std::string& region, const std::string& sample, const std::string& datacardYear, double& yieldError, const bool useShapeBased = true, const int masscut = 600, const TF1 * scaleFactor = nullptr);
void makeOneDatacard(const std::string& signalPoint, const std::string& region, const std::string& datacardYear, const std::string& interferenceType, const bool useShapeBased = true, const int masscut = 600);
// void makeCutAndCountDatacards(const std::string& signalPoint, const std::string& region, const std::string& datacardYear, double loMass, double hiMass);

bool positiveInterference;
bool useInterference;
bool useShapeBased;
bool useOriginalBinning;

std::string datacardYear;
std::string analysisType;
std::string binningChoice;

// Loop over ADD samples to make datacards for each
int main(int argc, char *argv[])
{
  bool usePythiaADD = false;
  bool usePythiaUnparticles = true;

  std::string interferenceType("");

  positiveInterference=true;
  useShapeBased=true;
  useOriginalBinning=true;

  if(argc!=2 && argc!=3 && argc!=4 && argc!=5 && argc!=6) {
    std::cout << "Syntax: makeDatacards.exe [2015/2016/2017/2018] [old/new] [positive/negative/linear] [cutandcount/shapebased] [rebin/noRebin]\n";
    std::cout << "'old' and 'new' refer to old and new Sherpa ADD samples\n";
    // std::cout << "If 'positive' or 'negative' are not specified,\n";
    // std::cout << "linear scaling will be used for the interference term. \n";
    std::cout << "Shape-based Analysis by default. Rebinning applied only if chosen." << std::endl;
    return -1;
  }
  datacardYear = argv[1];

  if(argc >= 3) {
    std::string whichADD(argv[2]);
    if(whichADD == "old") usePythiaADD = false;
  }
  if(argc==4) {
    interferenceType = argv[3];
    if(interferenceType != "negative" and interferenceType != "positive" and interferenceType != "linear") {
      std::cout << "Only 'negative' and 'positive' are allowed input parameters. " << std::endl;
      return -1;
    }
    if(interferenceType == "negative") positiveInterference = false;
  }

 if(argc==5){
   analysisType = argv[4];
   if(analysisType != "cutandcount" and analysisType != "shapebased"){
     std::cout << "Only 'cutandcount' and 'shapebased' are allowed input parameters. " << std::endl;
     return -1;
   }
   if (analysisType == "cutandcount") useShapeBased = false;
}

if(argc==6){
  binningChoice = argv[5];
  if(binningChoice != "rebin" and binningChoice != "noRebin"){
    std::cout << "Only 'rebin' and 'noRebin' are allowed input parameters. " << std::endl;
    return -1;
  }
  if (binningChoice == "rebin") useOriginalBinning = false;
}

std::cout << "Using the following Configuration..." << std::endl;
std::cout << "Shape-Based Analysis: " << useShapeBased << std::endl;
std::cout << "Original Binning (50 GeV bins): " << useOriginalBinning << std::endl;


  if(usePythiaADD) {
    // string scales
    std::vector<std::string> MS = {"4000", "4500", "5000", "5500", "6000",
				   "6500", "7000", "7500", "8000", "9000",
				   "10000", "11000", "13000"};
    // Use negative interference?
    std::vector<std::string> negInts = {"1", "0"};

    for(const auto& iMS : MS) {
      for(const auto& negInt : negInts) {
	std::string pointName = "ADDGravToGG_NegInt-";
	pointName += negInt;
	pointName += "_LambdaT-";
	pointName += iMS;
	pointName += "_TuneCP2_13TeV-pythia8";
	makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased);
	makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased);
      }
    }
  }
  else {
    // string scales
    std::vector<std::string> MS = {"3000", "3500", "4000", "4500",
				   "5000", "5500", "6000", "7000",
				   "8000", "9000", "10000", "11000"};
    // number of extra dimensions
    std::vector<std::string> NED = {"2", "4"};
    // KK cutoff conventions
    std::vector<std::string> KK = {"1", "4"};

    useInterference = interferenceType == "negative" or interferenceType == "positive";
    // only need to use one NED or KK convention if interference is considered
    if(useInterference) {
      NED.erase(NED.begin()+1);
      KK.erase(KK.begin()+1);
    }

    for(const auto iMS : MS) {
      for(const auto iNED : NED) {
	for(const auto iKK : KK) {
	  // no samples were generated with KK convention 4
	  // and four extra dimensions
	  if(strcmp(iKK.c_str(), "4")==0 && strcmp(iNED.c_str(), "4")==0) continue;
	  // Hewett- convention samples do not extend past Mgg > 6 TeV
	  if(iNED=="2" && iKK=="4" && std::stoi(iMS)>6000) continue;
	  std::string pointName = "ADDGravToGG_MS-";
	  pointName += iMS;
	  if(!useInterference) {
	    pointName += "_NED-";
	    pointName += iNED;
	    pointName += "_KK-";
	  pointName += iKK;
	  }
	  makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased);
	  makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased);
	}
      }
    }
  }

  if (usePythiaUnparticles){

    std::vector<std::string> spins = {"0", "2"};
    std::vector<std::string> dus = {"1p1", "1p5", "1p9"};
    std::map<std::string, std::vector<int>> lambdaUmap = {{"Spin0_du1p1", {10000, 4000, 8000}},
                                                    {"Spin0_du1p5", {2000, 2500, 3500}},
                                                    {"Spin0_du1p9", {2000, 2500, 3500}},
                                                    {"Spin2_du1p1", {2000, 2500, 3000}},
                                                    {"Spin2_du1p5", {2000, 2500, 3000}},
                                                    {"Spin2_du1p9", {2000, 2500, 3500}}
                                                   };
      std::string pointName;
      for(const auto& spin: spins){
        for(const auto& du: dus){
          std::string spin_du = "Spin" + spin + "_du" + du;
          std::vector<int> lambdaUs = lambdaUmap[spin_du];
          for (auto& lambdaU: lambdaUs ){
            pointName = "UnparToGG_";
            pointName += spin_du;
            pointName += "_LambdaU-";
            pointName += std::to_string(lambdaU);
            pointName += "_TuneCP2_13TeV_pythia8";
            // std::cout << pointName << std::endl;

            // ShapeBased DataCards
            makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased);
            makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased);

            // MakeCutAndCount or Rebinnned Histograms
            // makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased=false, 2000);
            // makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased=false, 2000);

            // makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased=false, 1800);
            // makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased=false, 1800);

            // makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased=false, 2500);
            // makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased=false, 2500);

            // makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased=false, 3000);
            // makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased=false, 3000);

            // Negative Interference (can't handle yet)
            // makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased=false, 800);
            // makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased=false, 800);
            //
            // makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased=false, 1000);
            // makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased=false, 1000);
            //
            // makeOneDatacard(pointName, "BB", datacardYear, interferenceType, useShapeBased=false, 1500);
            // makeOneDatacard(pointName, "BE", datacardYear, interferenceType, useShapeBased=false, 1500);

    //         if (lo is None) and (hi is None):
    //     y = hist.Integral()
    // else:
    //     loBin = hist.FindFixBin(lo)
    //     hiBin = hist.FindFixBin(hi)
    //     y = hist.Integral(loBin, hiBin, "")
          }
        }
      }


  }

  std::cout << "Used the following Configuration..." << std::endl;
  std::cout << "Shape-Based Analysis: " << useShapeBased << std::endl;
  std::cout << "Original Binning (50 GeV bins): " << useOriginalBinning << std::endl;
} // end main

void makeTable(const std::string& region)
{
  std::map<std::string, std::string> regionString;
  regionString["BB"] = "barrel-barrel";
  regionString["BE"] = "barrel-endcap";

  std::string filename("data/yields_");
  filename+=region;
  filename+=".tex";

  std::ofstream tableFile;
  tableFile.open(filename.c_str());
  if(tableFile.is_open()) {
    tableFile << "\\documentclass[12pt]{article}\n";
    tableFile << "\\usepackage{graphicx}\n";
    tableFile << "\\begin{document}\n";

    tableFile << "\\begin{table}[!htb]\n";
    tableFile << "\\begin{center}\n";
    tableFile << "\\caption{\\label{tab:" << region << "_yield}Event yields for " << regionString[region] << ".}\n";
    tableFile << "\\begin{tabular}{l ";
    tableFile << " c";
    tableFile << "}\\hline\n";

    tableFile << "\\end{tabular}\n";
    tableFile << "\\end{center}\n";
    tableFile << "\\end{table}\n";

    tableFile << "\\end{document}\n" << std::endl;
    tableFile.close();
  }
  else {
    std::cout << "Could not open " << filename << std::endl;
  }
}

void makeOneDatacard(const std::string& signalPoint, const std::string& region, const std::string& datacardYear, const std::string& interferenceType, const bool useShapeBased, const int masscut)
{
  // If useRateParam is set, the diphoton normalizations will be set using rateParam parameters.
  // Otherwise, the older behavior of using a diphotonNormB* nuisance parameter will be used.
  const bool useRateParam = false;

  //  makeTable(region);

  std::string signalPointInt = signalPoint;
  signalPointInt += "_int";
  //  std::vector<std::string> processes = {signalPoint, "gg", "gj", "other"};
  std::vector<std::string> processes = {signalPoint, "gg", "gj", "vg", "dy", "ttg"};
  if(useInterference) {
    // need to include a separate column for interference term
    processes.insert(processes.begin()+1, signalPointInt);
  }

  std::vector<nuisance> allNuisances;
  std::vector<nuisance*> pdf_nuisances;

  if (useShapeBased){

    nuisance diphotonkfactorStat0("kfactorStat0", "shape", {"-", "1", "-", "-", "-", "-"});
    nuisance diphotonkfactorStat1("kfactorStat1", "shape", {"-", "1", "-", "-", "-", "-"});
    nuisance diphotonkfactorStat2("kfactorStat2", "shape", {"-", "1", "-", "-", "-", "-"});
    nuisance diphotonkfactorStat3("kfactorStat3", "shape", {"-", "1", "-", "-", "-", "-"});
    nuisance diphotonkfactorScalesBB("diphotonkfactorScalesBB", "shape", {"-", "1", "-", "-", "-", "-"});
    nuisance diphotonkfactorScalesBB_dummy("diphotonfactorScalesBB", "shape", {"-", "-", "-", "-", "-", "-"});
    nuisance diphotonkfactorScalesBE("diphotonkfactorScalesBE", "shape", {"-", "1", "-", "-", "-", "-"});
    nuisance diphotonkfactorScalesBE_dummy("diphotonkfactorScalesBE", "shape", {"-", "-", "-", "-", "-", "-"});
    nuisance diphotonNormBB("diphotonNormBB", "lnU", {"-", "1.75", "-", "-", "-", "-"});
    nuisance diphotonNormBB_dummy("diphotonNormBB_dummy", "lnU", {"-", "-", "-", "-", "-", "-"});
    nuisance diphotonNormBE("diphotonNormBE", "lnU", {"-", "1.5", "-", "-", "-", "-"});
    nuisance diphotonNormBE_dummy("diphotonNormBE_dummy", "lnU", {"-", "-", "-", "-", "-", "-"});
    std::string lumiError = std::to_string(1 + luminosityErrorFrac[datacardYear]);
    nuisance lumi("lumi", "lnN", {lumiError, lumiError, "-", lumiError, lumiError, lumiError});
    nuisance pileup("pileup", "shape", {"-", "1", "-", "1", "1", "1"});
    nuisance fake_sample("fake_sample", "shape", {"-", "-", "1.0", "-", "-", "-"});
    //  nuisance fake_closure("fake_closure", "lnN", {"-", "-", "1.3", "-", "-", "-"});
    nuisance eff("eff", "shape", {"-", "1", "-", "1", "1", "1"});
    //  nuisance xsec_minor_bkg("xsec_minor_bkg", "lnN", {"-", "-", "-", "1.5"});
    nuisance xsec_vg("xsec_vg", "lnN", {"-", "-", "-", "1.5", "-", "-"});
    nuisance xsec_dy("xsec_dy", "lnN", {"-", "-", "-", "-", "1.5", "-"});
    nuisance xsec_ttg("xsec_ttg", "lnN", {"-", "-", "-", "-", "-", "1.5"});
    // "energyScale" would be used only for an overall scaling
    // but we subdivide EGM systematic uncertainties further
    //  nuisance energyScale("energyScale", "shape", {"1", "1", "-", "1"});
    nuisance energyScaleStat("energyScaleStat", "shape", {"-", "1", "-", "1", "1", "1"});
    nuisance energyScaleSyst("energyScaleSyst", "shape", {"-", "1", "-", "1", "1", "1"});
    nuisance energyScaleGain("energyScaleGain", "shape", {"-", "1", "-", "1", "1", "1"});
    nuisance energySigma("energySigma", "shape", {"-", "1", "-", "1", "1", "1"});

    // std::vector<nuisance> allNuisances;
    allNuisances.push_back(diphotonkfactorStat0);
    allNuisances.push_back(diphotonkfactorStat1);
    allNuisances.push_back(diphotonkfactorStat2);
    allNuisances.push_back(diphotonkfactorStat3);
    if(region == "BB") {
      allNuisances.push_back(diphotonkfactorScalesBB);
      allNuisances.push_back(diphotonkfactorScalesBE_dummy);
      if(!useRateParam) {
        allNuisances.push_back(diphotonNormBB);
        allNuisances.push_back(diphotonNormBE_dummy);
      }
    }
    else {
      allNuisances.push_back(diphotonkfactorScalesBB_dummy);
      allNuisances.push_back(diphotonkfactorScalesBE);
      if(!useRateParam) {
        allNuisances.push_back(diphotonNormBE);
        allNuisances.push_back(diphotonNormBB_dummy);
      }
    }
    allNuisances.push_back(lumi);
    allNuisances.push_back(pileup);
    allNuisances.push_back(fake_sample);
    allNuisances.push_back(eff);
    //  allNuisances.push_back(xsec_minor_bkg);
    allNuisances.push_back(xsec_vg);
    allNuisances.push_back(xsec_dy);
    allNuisances.push_back(xsec_ttg);
    allNuisances.push_back(energyScaleStat);
    allNuisances.push_back(energyScaleSyst);
    allNuisances.push_back(energyScaleGain);
    allNuisances.push_back(energySigma);
    // add pdf uncertainties

    for(int i = 1; i < 51; i++) {
      pdf_nuisances.push_back(new nuisance("pdf" + std::to_string(i), "shape", {"-", "1", "-", "-", "-", "-"}));
      pdf_nuisances.push_back(new nuisance("pdf" + std::to_string(i), "shape", {"-", "1", "-", "-", "-", "-"}));
      allNuisances.push_back(*(pdf_nuisances.back()));
    }

    if(useInterference) {
      for(std::vector<nuisance>::iterator inuisance = allNuisances.begin();
    inuisance != allNuisances.end();  ++inuisance) {
        // use same systematics as signal for interference term
        (*inuisance).m_contribution.insert((*inuisance).m_contribution.begin()+1, (*inuisance).m_contribution.front());
      }
    }
  } //end shapeBased nuisances

  else if (!useShapeBased){

    // FIXME: Need to recalculate cut and count systematics

    nuisance diphotonNormBB("diphotonNormBB", "lnU", {"-", "1.75", "-", "-", "-", "-"});
    nuisance diphotonNormBB_dummy("diphotonNormBB_dummy", "lnU", {"-", "-", "-", "-", "-", "-"});
    nuisance diphotonNormBE("diphotonNormBE", "lnU", {"-", "1.5", "-", "-", "-", "-"});
    nuisance diphotonNormBE_dummy("diphotonNormBE_dummy", "lnU", {"-", "-", "-", "-", "-", "-"});
    std::string lumiError = std::to_string(1 + luminosityErrorFrac[datacardYear]);
    nuisance lumi("lumi", "lnN", {lumiError, lumiError, "-", lumiError, lumiError, lumiError});
    nuisance xsec_vg("xsec_vg", "lnN", {"-", "-", "-", "1.5", "-", "-"});
    nuisance xsec_dy("xsec_dy", "lnN", {"-", "-", "-", "-", "1.5", "-"});
    nuisance xsec_ttg("xsec_ttg", "lnN", {"-", "-", "-", "-", "-", "1.5"});


    if(region == "BB") {
      if(!useRateParam) {
        allNuisances.push_back(diphotonNormBB);
        allNuisances.push_back(diphotonNormBE_dummy);
      }
    }
    else {
      if(!useRateParam) {
        allNuisances.push_back(diphotonNormBE);
        allNuisances.push_back(diphotonNormBB_dummy);
      }
    }
    allNuisances.push_back(lumi);
    allNuisances.push_back(xsec_vg);
    allNuisances.push_back(xsec_dy);
    allNuisances.push_back(xsec_ttg);
  }

  unsigned int nchannels = 1;
  unsigned int nbackgrounds = processes.size()-1;

  std::ofstream output;
  std::string filename("datacards/");
  filename+=signalPoint;
  if(useInterference) {
    filename+="_";
    filename+=interferenceType;
  }
  if(!useOriginalBinning) {
    filename+="_rebinned";
  }
  if(!useShapeBased){
    filename+="_m";
    std::string massCutStr = std::to_string(masscut);
    filename+=massCutStr;
  }
  filename+="_";
  filename+=datacardYear;
  filename+="_" + region;
  filename+=".dat";
  output.open(filename);
  if (output.is_open()) {
    double yieldError = 0.0;

    // header
    output << "imax " << nchannels << " number of channels" << std::endl;
    output << "jmax " << nbackgrounds << " number of backgrounds" << std::endl;
    output << "kmax " << allNuisances.size() << " number of nuisance parameters" << std::endl;
    if (useOriginalBinning and useShapeBased){
        output << "-------------------" << std::endl;
        output << "shapes * " << region << " datacards/Minv_histos_$CHANNEL_" << datacardYear << ".root $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC" << std::endl;
    }
    else if (!useOriginalBinning and useShapeBased){
        output << "-------------------" << std::endl;
        output << "shapes * " << region << " datacards/Minv_histos_$CHANNEL_" << datacardYear << "_rebinned.root $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC" << std::endl;
    }
    output << "-------------------" << std::endl;

    // definition of bins and rates
    output << "bin          ";
    for(unsigned int i=0; i<nchannels; i++) {
      output << region << "   ";
    }
    output << "\n";
    output << "observation  ";
    output << getYield(region, "data_obs", datacardYear, yieldError, useShapeBased, masscut) << " " ;
    output << "\n";

    output << "-------------------" << std::endl;
    output << "bin            ";

    for(auto iprocess : processes) {
      output << region << "    ";
    }
    output << "\n";
    output << "process    ";
    for(int iprocess=0; iprocess<static_cast<int>(processes.size()); iprocess++) {
      if(useInterference) output << iprocess-1 << "    ";
      else output << iprocess << "    ";
    }
    output << "\n";
    output << "process    ";

    for(auto iprocess : processes) {
      output << iprocess << "    ";
    }

    output << "\n";
    // output rates
    output << "rate        ";
    for(auto iprocess : processes) {
      output << getYield(region, iprocess, datacardYear, yieldError, useShapeBased, masscut) << "    ";
    }
    output << "\n-------------------" << std::endl;

    // output systematics
    for(auto inuisance : allNuisances) {
      output << inuisance.m_syst  << "      " << inuisance.m_distribution << "  ";
      for( auto icontrib : inuisance.m_contribution) {
	output << icontrib << " ";
      }
      output << "\n";
    }
    if(useRateParam) {
      output << "diphotonNormBB rateParam BB_20* gg 1\n";
      output << "diphotonNormBE rateParam BE_20* gg 1" << std::endl;
    }
  } // closes is_open()
  else {
    std::cout << "Could not open output file " << filename << std::endl;
  }
}

double getYield(const std::string& region, const std::string& sample, const std::string& datacardYear, double& yieldError, const bool useShapeBased, const int masscut, const TF1 * scaleFactor)
{
  double integral = 0.0;

  std::string histName(region);
  histName+="/";

  // histograms for photon fakes from data-driven method are in a different file
  if(sample.find("gj") != std::string::npos) {
    TFile *inputFakes = TFile::Open(Form("data/fakes_%s_average.root", datacardYear.c_str()));
    histName+=sample;
    histName+="DataDriven";
    histName+=region;

    TH1D *hist = static_cast<TH1D*>(inputFakes->Get(histName.c_str()));
    integral = hist->Integral();
    if (masscut != 600){
      integral = hist->Integral(hist->FindFixBin(masscut), hist->FindFixBin(13000), "");
    }
    inputFakes->Close();
  }
  else {
    TString filename(Form("datacards/datacards/Minv_histos_%s_%s.root", region.c_str(), datacardYear.c_str()));
    if(useInterference) {
      filename = "data/Minv_histos_with_interference.root";
    }
    if(!useOriginalBinning){
      TString filename(Form("datacards/datacards/Minv_histos_%s_%s_rebinned.root", region.c_str(), datacardYear.c_str()));
    }
    TFile *input = TFile::Open(filename);
    histName+=sample;

    std::cout << "Getting histogram " << histName << std::endl;
    if (masscut != 600){
      std::cout << "With masscut: " << masscut  << std::endl;
    }
    TH1D *hist = static_cast<TH1D*>(input->Get(histName.c_str()));
    // take max to avoid negative entries arising from
    // negative weights in NLO samples
    integral = hist->Integral();
    if (masscut != 600){
      integral = hist->Integral(hist->FindFixBin(masscut), hist->FindFixBin(13000), "");
    }
    if(useInterference) {
      // in the case of negative interference, multiply inteference term by -k
      // and signal by k^2 to adjust to Hewett- convention
      // We're not doing cut and count for ADD
      if(sample.find("ADD") != std::string::npos && !positiveInterference) {
	double k = 2/TMath::Pi();
	if(sample.find("int") != std::string::npos) integral *= -k;
	else integral *= k*k;
      }
    }
    input->Close();
  }
  return integral;
}
