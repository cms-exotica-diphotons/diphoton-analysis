#include "diphoton-analysis/Tools/interface/easyplot.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"

#include "TMath.h"

int main(int argc, char *argv[])
{
  std::string data_year("");

  std::string region;

  if(argc!=2) {
    std::cout << "Syntax: compareGenerators.exe [barrel/endcap]" << std::endl;
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

  std::string cut("Photon1.pt>75&&Photon2.pt>75 && Photon1.isEB && Photon2.isEB && Diphoton.Minv > 230 && Diphoton.Minv < 1000 && isGood");
  if(endcap) cut = "Photon1.pt>75&&Photon2.pt>75 && Diphoton.Minv > 320 && Diphoton.Minv < 1000 && isGood && ( (Photon1.isEB && Photon2.isEE) || (Photon2.isEB && Photon1.isEE) )";
  int nbins=100;
  double xmin=0.0; // GeV
  double xmax=2000; // GeV

  // initialize chains and default styles
  init();

  // define samples to be used in histograms
  sample gg("gg", "#gamma#gamma (Sherpa)", "2016");
  gg.drawAsData = true; // display as if it is data
  sample gg_aMC("gg_aMC", "#gamma#gamma (aMC@NLO)", "2015");
  std::vector<sample> samples;
  samples.push_back(gg);
  samples.push_back(gg_aMC);

  plot p0(samples, "Diphoton.Minv", cut, nbins/2, xmin, xmax);
  plot p1(samples, "Photon1.pt", cut, nbins/2, xmin, xmax/2);
  plot p2(samples, "Photon2.pt", cut, nbins/2, xmin, xmax/2);
  plot p3(samples, "Diphoton.qt", cut, nbins/2, xmin, xmax/2);
  plot p4(samples, "Diphoton.deltaPhi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p5(samples, "Diphoton.deltaEta", cut, nbins/2, -5, 5);
  plot p6(samples, "abs(Diphoton.cosThetaStar)", cut, 20, 0, 1);
  plot p7(samples, "nPV", cut, 50, 0, 50);
  plot p8(samples, "Diphoton.deltaR", cut, nbins/2, 0, 5);

  std::string extraFilenameInfo(region);
  extraFilenameInfo += "_comparison";

  p0.output("plots", extraFilenameInfo);
  p1.output("plots", extraFilenameInfo);
  p2.output("plots", extraFilenameInfo);
  p3.output("plots", extraFilenameInfo);
  p4.output("plots", extraFilenameInfo);
  p5.output("plots", extraFilenameInfo);
  p6.output("plots", extraFilenameInfo);
  p7.output("plots", extraFilenameInfo);
  p8.output("plots", extraFilenameInfo);

}
