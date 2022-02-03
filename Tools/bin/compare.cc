#include "diphoton-analysis/Tools/interface/easyplot.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"

#include "TMath.h"

int main(int argc, char *argv[])
{
  std::string region, data_year;

  if(argc!=3) {
    std::cout << "Syntax: compare.exe [barrel/endcap] [2016/2018/2018AB/2018ABC/2018D]" << std::endl;
    return -1;
  }
  else {
    region = argv[1];
    if(region!="barrel" and region!="endcap") {
      std::cout << "Only 'barrel' and 'endcap' are allowed regions. " << std::endl;
      return -1;
    }
    data_year = argv[2];
    if(data_year!="2016" && data_year!="2018" && data_year!="2018AB" &&
       data_year!="2018ABC" && data_year!="2018CD" && data_year!="2018D") {
      std::cout << "Only '2016', '2018', '2018AB', '2018ABC', '2018CD', and '2018D' are allowed data years. " << std::endl;
      return -1;
    }

  }

  bool endcap = (region=="endcap");

  std::string pt_cut("125");
  std::string minv_cut("Diphoton.Minv > 500");
  std::string kinematic_cuts("Photon1.pt>" + pt_cut + " && Photon2.pt>" + pt_cut + "&&" + minv_cut);
  std::string eta_cuts_BB("Photon1.isEB && Photon2.isEB");
  std::string eta_cuts_BE("( (Photon1.isEB && Photon2.isEE) || (Photon2.isEB && Photon1.isEE) )");
  std::string cut(kinematic_cuts + "&&" + eta_cuts_BB + "&& isGood");
  if(endcap) cut = kinematic_cuts + "&&" + eta_cuts_BE + "&& isGood";
  cut += "&& Diphoton.Minv < 1000";
  std::cout << cut << std::endl;

  int nbins = 40;
  double xmin = 0.0; // GeV
  double xmax = 2000; // GeV

  // initialize chains and default styles
  init();

  // define samples to be used in histograms
  std::string trigger(data_year == "2016" ? "(HLT_DoublePhoton60||HLT_ECALHT800)" : "(HLT_DoublePhoton70||HLT_ECALHT800)");
  sample data("data", "Data (" + data_year + ")", data_year, "(HLT_DoublePhoton70||HLT_ECALHT800)");
  sample data_2017("data", "Data (2017)", "2017", std::to_string(luminosity[data_year]/luminosity["2017"]) + "*(HLT_DoublePhoton70||HLT_ECALHT800)");
  data_2017.drawAsMC = true;
  data_2017.m_markerColor = kRed;
  data.m_markerColor = kBlue;
  std::vector<sample> samples;
  samples.push_back(data);
  samples.push_back(data_2017);

  plot p0(samples, "Minv", cut, 40, 0, 2000);
  plot p1(samples, "Photon1.pt", cut, nbins/2, xmin, xmax/2);
  plot p2(samples, "Photon2.pt", cut, nbins/2, xmin, xmax/2);
  plot p3(samples, "Diphoton.qt", cut, nbins/2, xmin, xmax/2);
  plot p4(samples, "Diphoton.deltaPhi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p5(samples, "Diphoton.deltaEta", cut, nbins/2, -5, 5);
  plot p6(samples, "abs(Diphoton.cosThetaStar)", cut, 20, 0, 1);
  plot p7(samples, "nPV", cut, 60, 0, 60);
  plot p8(samples, "Diphoton.deltaR", cut, nbins/2, 0, 5);
  plot p9(samples, "Photon1.scEta", cut, nbins/2, -5, 5);
  plot p10(samples, "Photon2.scEta", cut, nbins/2, -5, 5);
  plot p11(samples, "Photon1.phi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p12(samples, "Photon2.phi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p13(samples, "abs(Diphoton.deltaPhi)", cut, nbins/4, 0, TMath::Pi());

  std::string extraFilenameInfo(region);
  extraFilenameInfo += "_";
  extraFilenameInfo += "compare_" + data_year;

  p0.output("plots", extraFilenameInfo);
  p1.output("plots", extraFilenameInfo);
  p2.output("plots", extraFilenameInfo);
  p3.output("plots", extraFilenameInfo);
  p4.output("plots", extraFilenameInfo);
  p5.output("plots", extraFilenameInfo);
  p6.output("plots", extraFilenameInfo);
  p7.output("plots", extraFilenameInfo);
  p8.output("plots", extraFilenameInfo);
  p9.output("plots", extraFilenameInfo);
  p10.output("plots", extraFilenameInfo);
  p11.output("plots", extraFilenameInfo);
  p12.output("plots", extraFilenameInfo);
  p13.output("plots", extraFilenameInfo);

}
