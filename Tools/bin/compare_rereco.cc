#include "diphoton-analysis/Tools/interface/easyplot.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"

#include "TMath.h"

int main(int argc, char *argv[])
{
  std::string data_year("");

  std::string region;

  if(argc!=2) {
    std::cout << "Syntax: compare.exe [barrel/endcap]" << std::endl;
    return -1;
  }
  else {
    region = argv[1];
    if(region!="barrel" and region!="endcap") {
      std::cout << "Only 'barrel' and 'endcap' are allowed regions. " << std::endl;
      return -1;
    }
  }

  bool endcap = (region=="endcap");

  std::string pt_cut("125");
  //  std::string minv_cut("Diphoton.Minv > 350");
  std::string minv_cut("Diphoton.Minv > 500");
  std::string kinematic_cuts("Photon1.pt>" + pt_cut + " && Photon2.pt>" + pt_cut + "&&" + minv_cut);
  std::string eta_cuts_BB("Photon1.isEB && Photon2.isEB");
  std::string eta_cuts_BE("( (Photon1.isEB && Photon2.isEE) || (Photon2.isEB && Photon1.isEE) )");
  std::string cut(kinematic_cuts + "&&" + eta_cuts_BB + "&& isGood");
  if(endcap) cut = kinematic_cuts + "&&" + eta_cuts_BE + "&& isGood";
  cut += "&& Diphoton.Minv < 1000";

  int nbins = 40;
  double xmin = 0.0; // GeV
  double xmax = 2000; // GeV

  // initialize chains and default styles
  init();

  // define samples to be used in histograms
  sample data_2018ABC_prompt("data", "Data (2018)", "2018ABC_prompt", "(HLT_DoublePhoton70||HLT_ECALHT800)");
  sample data_2018ABC_rereco("data", "Data re-reco (2018)", "2018ABC_rereco", "(HLT_DoublePhoton70||HLT_ECALHT800)");
  data_2018ABC_prompt.drawAsMC = true;
  data_2018ABC_prompt.m_markerColor = kBlue;
  data_2018ABC_rereco.m_markerColor = kRed;
  std::vector<sample> samples;
  samples.push_back(data_2018ABC_prompt);
  samples.push_back(data_2018ABC_rereco);

  plot p0(samples, "Minv", cut, 40, 0, 2000);
  plot p1(samples, "Photon1.pt", cut, nbins/2, xmin, xmax/2);
  plot p2(samples, "Photon2.pt", cut, nbins/2, xmin, xmax/2);
  plot p3(samples, "Diphoton.qt", cut, nbins/2, xmin, xmax/2);
  plot p4(samples, "Diphoton.deltaPhi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p5(samples, "Diphoton.deltaEta", cut, nbins/2, -5, 5);
  plot p6(samples, "abs(Diphoton.cosThetaStar)", cut, 20, 0, 1);
  plot p7(samples, "nPV", cut, 80, 0, 80);
  plot p8(samples, "Diphoton.deltaR", cut, nbins/2, 0, 5);
  plot p9(samples, "Photon1.eta", cut, nbins/2, -5, 5);
  plot p10(samples, "Photon2.eta", cut, nbins/2, -5, 5);
  plot p11(samples, "Photon1.phi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p12(samples, "Photon2.phi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p13(samples, "abs(Diphoton.deltaPhi)", cut, nbins/4, 0, TMath::Pi());

  std::string extraFilenameInfo(region);
  extraFilenameInfo += "_";
  extraFilenameInfo += "compare_rereco";

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
