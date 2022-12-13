#include "diphoton-analysis/Tools/interface/sampleList.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"

#include "TCanvas.h"
#include "TString.h"
#include "TH1.h"
#include "TFile.h"

void allSamples(const std::string &region, const std::string &year, TFile * output);
std::string getSampleBase(const std::string & sampleName, const std::string & year);
std::string getBase(const std::string & sampleName);
std::string addCutsPerSample(const std::string &cut, const std::string &sample, const std::string &region, const std::string &year);
std::map<std::string, std::string> reweightingList(std::vector<std::string> &postfixes);
void addTheoryUncertanties(std::map<std::string, TH1F*> &histograms, const std::string &region, TFile * output);

// TH1F* clockworkConversion(TH1F* hGRW, TH1F* hHew);
// void clockworkHistograms(const std::string &region, const std::string &year, TFile * output);
// TH1F* clockworkConversion(TH1F* hGRW, TH1F* hHew);

void clockworkConversion(std::string nameCCW, std::map<std::string, TH1F*> histosGRW, std::map<std::string, TH1F*> histosHew);


int main(int argc, char *argv[])
{
  std::string region, year;

  if(argc!=3) {
    std::cout << "Syntax: makeHistClockwork.exe [BB/BE] [2016/2017/2018]" << std::endl;
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

  std::cout << "Making clockwork histograms" << std::endl;
  std::cout << "Initializing ADD histograms" << std::endl;

  //TFile *output = new TFile(Form("datacards/Minv_histosCW_%s_%s.root", region.c_str(), year.c_str()), "recreate");
  TFile *output = new TFile(Form("datacards/Minv_histos_CW_%s_%s.root", region.c_str(), year.c_str()), "recreate");
  output->mkdir(region.c_str());

  TString baseDirectory("root://cmseos.fnal.gov/");
  initADD(baseDirectory);
  allSamples(region, year, output);
  // clockworkHistograms(region, year, output);
  std::cout << "======================================="<< std::endl;
  std::cout << "Written " << Form("datacards/Minv_histos_CW_%s_%s.root", region.c_str(), year.c_str()) << std::endl;
}

void allSamples(const std::string &region, const std::string &year, TFile * output){

  std::cout << "Initializing ADD histograms" << std::endl;
  std::vector<std::string> samples = getSampleList();

  int nBins = 120;
  double xMin = 0.0;
  double xMax = 6000.;
  //
  std::map<std::string, TH1F*> histograms;
  std::map<std::string, std::string> cuts;

  // FIXME: Maybe to write in a separate function
  //
  cuts["BB"] = "(GenDiphoton.deltaR > 0.45 && GenPhoton1.pt>125 && GenPhoton2.pt>125 && GenPhoton1.isEB && GenPhoton2.isEB)";
  cuts["BE"] = "(GenDiphoton.deltaR > 0.45 && GenPhoton1.pt>125 && GenPhoton2.pt>125 && ( (GenPhoton1.isEB && GenPhoton2.isEE) || (GenPhoton2.isEB &&  GenPhoton1.isEE )))";

  // std::vector<int> lambdaTs = {4000, 4500, 5000, 5500, 6000,
  //              6500, 7000, 7500, 8000, 8500,
  //              9000, 10000, 11000, 13000};

  // std::vector<int> lambdaTs = {4000};
  std::vector<int> lambdaTs = {4000, 8000, 11000};

  for (int lambdaT: lambdaTs){

    std::string lambdaTName = "LambdaT-" + std::to_string(lambdaT);
    std::string histGRWname = "GRW-" + lambdaTName;
    std::string histHewname = "Hew-" + lambdaTName;
    std::string histCWname  = lambdaTName + "k";
    // std::map<std::string, TH1F*> histGRW;
    // std::map<std::string, TH1F*> histHew;

    TH1F *histGRW = new TH1F(histGRWname.c_str(), histGRWname.c_str(), nBins, xMin, xMax);
    TH1F *histHew = new TH1F(histHewname.c_str(), histHewname.c_str(), nBins, xMin, xMax);

    TH1F *histCW = new TH1F(histCWname.c_str(), histCWname.c_str(), nBins, xMin, xMax);

    for(auto sample : samples) {
      if (sample.find("ADDGravToGG_NegInt") != std::string::npos && sample.find(year) != std::string::npos && sample.find(lambdaTName) != std::string::npos ){
        // std::cout << sample << std::endl;
        std::string baseName(getSampleBase(sample, year));
        std::string sampleCut = addCutsPerSample(cuts[region], sample, region, year);
        std::string fullCut(sampleCut);

        std::cout << baseName << "with cut" << fullCut << std::endl;

        TH1F *hist = new TH1F(baseName.c_str(), baseName.c_str(), nBins, xMin, xMax);
        histograms[baseName] = hist;
        std::string varname("GenDiphoton.Minv");

        chains[getBase(sample)]->Project(baseName.c_str(), varname.c_str(),  fullCut.c_str());
        //std::cout << hist->GetName() << " Integral: " << histograms[baseName]->Integral() << std::endl;
        // std::cout << hist->Integral() << " Integral: " << histograms[baseName]->Integral() << std::endl
        // hist->Write();

        //FIXME: Maybe to write in a separate function that accepts histogram std::map<key, value> map;
        if ( sample.find("NegInt-1") != std::string::npos ) histGRW = hist;
        if ( sample.find("NegInt-0") != std::string::npos ) histHew = hist;
      }
    }

    double sf=(30.0*pow(((double) points[j])/1000.0,8)/(283*TMath::Pi()*pow(10,3)))*pow(10,15);

    histGRW->Add(histHew, 1);
    histGRW->Scale(0.5);
    histGRW->Scale(sf);
    histCW = (TH1F*) histGRW->Clone();
    std::cout << histCWname.c_str() << " Integral:" <<  histCW->Integral() << std::endl;
    output->cd(region.c_str());
    histCW->Write(histCWname.c_str());
  }
}

// // std::map<std::string, TH1F*> clockworkConversion(std::string nameCCW, std::map<std::string, TH1F*> histosGRW, std::map<std::string, TH1F*> histosHew){
// void clockworkConversion(std::string nameCCW, std::map<std::string, TH1F*> histosGRW, std::map<std::string, TH1F*> histosHew){
//
//   int nBins = 120;
//   double xMin = 0.0;
//   double xMax = 6000.;
//
//   std::vector<int> lambdaTs = {4000, 4500, 5000, 5500, 6000,
//                6500, 7000, 7500, 8000, 8500,
//                9000, 10000, 11000, 13000};
//
//
//   for (int lambdaT : lambdaTs){
//     for (auto hGRW : histosGRW){
//       for (auto hHew : histosHew)
//     }
//   }
//
//   return histosCW;
// }



std::string addCutsPerSample(const std::string &cut, const std::string &sample, const std::string &region, const std::string &year)
{
  std::string sampleCut(cut);
  sampleCut += "*(GenDiphoton.Minv > 600)*weightAll";

  return sampleCut;
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
//
// void clockworkHistograms(const std::string &region, const std::string &year, TFile * output){
//
//   std::cout << "Initializing ADD histograms" << std::endl;
//   std::vector<std::string> samples = getSampleList();
//
//   int nBins = 120;
//   double xMin = 0.0;
//   double xMax = 6000.;
//   //
//   std::map<std::string, TH1F*> histograms;
//   std::map<std::string, std::string> cuts;
//
//   // FIXME: Maybe to write in a separate function
//
//   cuts["BB"] = "(GenDiphoton.deltaR > 0.45 && GenPhoton1.pt>125 && GenPhoton2.pt>125 && GenPhoton1.isEB && GenPhoton2.isEB)";
//   cuts["BE"] = "(GenDiphoton.deltaR > 0.45 && GenPhoton1.pt>125 && GenPhoton2.pt>125 && ( (GenPhoton1.isEB && GenPhoton2.isEE) || (GenPhoton2.isEB &&  GenPhoton1.isEE )))";
//
//   std::vector<int> lambdaTs = {4000, 4500, 5000, 5500, 6000,
//              6500, 7000, 7500, 8000, 8500,
//              9000, 10000, 11000, 13000};
//
//   //
//   for (int lambdaT: lambdaTs){
//
//     std::cout << lambdaT << std::endl;
//     // std::string nameCCW = "LambdaT-" + std::to_string(lambdaT) + "_k";
//     // TH1F *hCW = new TH1F(nameCCW.c_str(), nameCCW.c_str(), nBins, xMin, xMax);
//
//     for (auto sample : samples ){
//       if ( sample.find("ADDGravToGG_NegInt") != std::string::npos && sample.find(year) != std::string::npos ){
//         std::string baseName(getSampleBase(sample, year));
//         std::string sampleCut = addCutsPerSample(cuts[region], sample, region, year);
//         std::string fullCut(sampleCut);
//
//         // std::cout << baseName << std::endl;
//         TH1F *hist = new TH1F(baseName.c_str(), baseName.c_str(), nBins, xMin, xMax);
//         std::string varname("GenDiphoton.Minv");
//
//         chains[getBase(sample)]->Project(baseName.c_str(), varname.c_str(),  fullCut.c_str());
//         // std::cout << hist->GetName() << " Integral: " << histograms[baseName]->Integral() << " = " << hist->Integral()<<std::endl;
//         std::cout << hist->GetName() << " Integral: " << histograms[baseName]->Integral() << " = " << hist->Integral()<<std::endl;
//         output->cd(region.c_str());
//         histograms[baseName] = hist;
//         // hist->Write();
//
//         // if ( sample.find(std::to_string(lambdaT)) != std::string::npos ){
//         //   if ( sample.find("NegInt-0") ) hCW = hist;
//         //   if ( sample.find("NegInt-1") )
//         // }
//
//     }
//   }
// }

  ///======= Scratch

  // Sorting GRW and Hewett- histograms
  // for(auto sample : samples) {
  //   if (sample.find("ADDGravToGG_NegInt") != std::string::npos && sample.find(year) != std::string::npos ){
  //     // std::cout << sample << std::endl;
  //     std::string baseName(getSampleBase(sample, year));
  //     std::string sampleCut = addCutsPerSample(cuts[region], sample, region, year);
  //     std::string fullCut(sampleCut);
  //
  //     std::cout << baseName << std::endl;
  //
  //     TH1F *hist = new TH1F(baseName.c_str(), baseName.c_str(), nBins, xMin, xMax);
  //     std::string varname("GenDiphoton.Minv");
  //
  //     chains[getBase(sample)]->Project(baseName.c_str(), varname.c_str(),  fullCut.c_str());
  //     std::cout << hist->GetName() << " Integral: " << histograms[baseName]->Integral() << std::endl;
  //     output->cd(region.c_str());
  //     histograms[baseName] = hist;
  //     hist->Write();
  //
  //     //FIXME: Maybe to write in a separate function that accepts histogram std::map<key, value> map;
  //     // if ( sample.find("NegInt-1") != std::string::npos ) histGRW[baseName]    = hist;
  //     // if ( sample.find("NegInt-0") != std::string::npos ) histNegInt[baseName] = hist;
  //   }
  // }
  //
  // std::map<std::string, TH1F*> histGRW;
  // std::map<std::string, TH1F*> histNegInt;
  // std::map<std::string, TH1F*> histMapCW;
  //
  // for (int lambdaT : lambdaTs){
  //   std::cout << lambdaT << std::endl;
  //   std::string nameCCW = "LambdaT-" + std::to_string(lambdaT) + "_k";
  //   TH1F *hCW = new TH1F(nameCCW.c_str(), nameCCW.c_str(), nBins, xMin, xMax);
  //
  //   std::string hGRW_tempName = "GRW" + lambdaT;
  //   std::string hHew_tempName = "Hew" + lambdaT;
  //   TH1F *hGRW_temp = new TH1F(hGRW_tempName.c_str(), hGRW_tempName.c_str(), nBins, xMin, xMax);
  //   TH1F *hHew_temp = new TH1F(hHew_tempName.c_str(), hHew_tempName.c_str(), nBins, xMin, xMax);
  //
  //   for (auto h : histograms){
  //
  //     std::string modelPoint = h.first;
  //     if ( modelPoint.find(std::to_string(lambdaT)) != std::string::npos ){
  //          std::cout << modelPoint << std::endl;
  //     }
  //
  //     if ( modelPoint.find("NegInt-1") )  hGRW_temp = h.second;
  //     if ( modelPoint.find("NegInt-0") )  hHew_temp = h.second;
  //
  //   }
  //
  //   hGRW_temp->Add(hHew_temp);
  //   std::cout <<  hGRW_temp->Integral() << std::endl;
  //   hCW = (TH1F*)hGRW_temp->Clone();
  //
  //   std::cout << "Writing " << nameCCW.c_str() << std::endl;
  //   hCW->Write(nameCCW.c_str());
  // }

  // for (int lambdaT : lambdaTs){
  //   std::cout << lambdaT << std::endl;
  //   for (auto h : histograms){
  //     std::string modelPoint = h.first;
  //     std::vector<std::string> mPointvec;
  //     if ( modelPoint.find(std::to_string(lambdaT)) != std::string::npos ){
  //         // std::cout << modelPoint << std::endl;
  //         mPointvec.push_back(modelPoint);
  //         lambdaTgrwHew[lambdaT] = hist;
  //         lambdaTgrwHew[lambdaT] = mPointvec;
  //     }
  //     if (mPointvec.Size() > 2) mPointvec.clear();
  //     std::cout << lambdaTgrwHew[lambdaT] << std::endl;
  //   }
  // }

 // auto it = histGRW.find('ADDGravToGG_NegInt-1_LambdaT-8500_TuneCP2_13TeV-pythia8');
 // std::cout << "Iterator points to " << it->first <<  std::endl;

// }
