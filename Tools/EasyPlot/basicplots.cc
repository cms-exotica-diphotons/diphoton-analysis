#include "easyplot.hh"

#include "TMath.h"

void basicplots() 
{
  // configurable information
  double kfactor=1.4;
  std::string cut("Photon1.pt>75&&Photon2.pt>75 && abs(Photon1.eta)<1.4442 && abs(Photon2.eta)<1.4442 && isGood");
  int nbins=100;
  double xmin=0.0; // GeV
  double xmax=2000; // GeV

  // initialize chains and default styles
  init();

  // define samples to be used in histograms
  sample data("data", "Data");
  sample gg("gg", "#gamma#gamma", kfactor);
  sample gj("gj", "#gamma + jets");
  sample jj("jj", "Multijet");
  sample vg("vg", "V#gamma");
  sample w("w", "W");
  sample dy("dy", "DY");
  sample ttg("ttg", "t#bar{t}#gamma");
  std::vector<sample> samples;
  samples.push_back(data);
  samples.push_back(ttg);
  samples.push_back(w);
  samples.push_back(vg);
  samples.push_back(dy);
  //  samples.push_back(jj);
  samples.push_back(gj);
  samples.push_back(gg);

  plot p0(samples, "Minv", cut, nbins/2, xmin, xmax);
  plot p1(samples, "Photon1.pt", cut, nbins/2, xmin, xmax/2);
  plot p2(samples, "Photon2.pt", cut, nbins/2, xmin, xmax/2);
  plot p3(samples, "Diphoton.qt", cut, nbins/2, xmin, xmax/2);
  plot p4(samples, "Diphoton.deltaPhi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p5(samples, "Diphoton.deltaEta", cut, nbins/2, -5, 5);
  plot p6(samples, "abs(Diphoton.cosThetaStar)", cut, 20, 0, 1);

  p0.output("outputdir");
  p1.output("outputdir");
  p2.output("outputdir");
  p3.output("outputdir");
  p4.output("outputdir");
  p5.output("outputdir");
  p6.output("outputdir");

}
