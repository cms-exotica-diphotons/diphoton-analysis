#include "diphoton-analysis/Tools/interface/easyplot.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"

#include "TMath.h"

int main(int argc, char *argv[])
{
  std::string data_year("");

  std::string region;

  if(argc!=3) {
    std::cout << "Syntax: basicplots.exe [barrel/endcap] [2015/2016/2017/2018/2017_2018/2016_2017_2018/2018_newjson]" << std::endl;
    return -1;
  }
  else {
    region = argv[1];
    if(region!="barrel" and region!="endcap") {
      std::cout << "Only 'barrel' and 'endcap' are allowed regions. " << std::endl;
      return -1;
    }
    data_year = argv[2];
    if(data_year !="2015" && data_year != "2016" && data_year != "2017"
       && data_year != "2018" && data_year.compare("2017_2018") && data_year != "2018_newjson"  ) {
      std::cout << "Only '2015', '2016', '2017', '2018', and '2017_2018' are allowed years, plus '2018_newjson' for the data from the latest JSON." << std::endl;
      return -1;
    }
  }

  bool endcap = (region=="endcap");

  std::string kfactor;
  if(data_year == "2015") {
    kfactor = endcap ? kfactorString("BE", "R1F1_125GeV_CT10") : kfactorString("BB", "R1F1_125GeV_CT10");
  }
  else {
    kfactor = endcap ? kfactorString("BE", "R1F1_125GeV_NNPDF") : kfactorString("BB", "R1F1_125GeV_NNPDF");
  }

  std::string pt_cut("125");
  if(data_year == "2016") pt_cut = "125";
  std::string minv_cut("Diphoton.Minv > 500");
  std::string hlt_cut("HLT_DoublePhoton70 > 0");
  if(data_year == "2016") hlt_cut = "HLT_DoublePhoton60 > 0";
  std::string kinematic_cuts("Photon1.pt>" + pt_cut + " && Photon2.pt>" + pt_cut + "&&" + minv_cut);
  std::string eta_cuts_BB("Photon1.isEB && Photon2.isEB");
  std::string eta_cuts_BE("( (Photon1.isEB && Photon2.isEE) || (Photon2.isEB && Photon1.isEE) )");
  std::string basic_cuts = hlt_cut + "&&" + kinematic_cuts + "&& isGood";
  std::string cut_no_Minv(basic_cuts + "&&" + eta_cuts_BB);
  if(endcap) cut_no_Minv = basic_cuts + "&&" + eta_cuts_BE;
  std::string cut(cut_no_Minv);
  cut += "&& Diphoton.Minv < 1000";
  int nbins=100;
  double xmin=0.0; // GeV
  double xmax=2000; // GeV

  // initialize chains and default styles
  init();

  std::string trigger("(HLT_DoublePhoton70 || HLT_ECALHT800)");
  if(data_year == "2015" or data_year == "2016") trigger = "(HLT_DoublePhoton60 || HLT_ECALHT800)";
  // define samples to be used in histograms
  sample data("data", "Data", data_year, trigger);
  data.isData = true;
  TString weights(Form("(%s*%s)", scale_factor_cut(atoi(data_year.c_str()), 0).Data(), npv_reweight_str(atoi(data_year.c_str()), 0).Data()));
  sample gg("gg", "#gamma#gamma", data_year, kfactor + std::string("*") + weights.Data());
  sample gj("gj", "#gamma + jets", data_year, weights.Data());
  sample jj("jj", "QCD", data_year, weights.Data());
  sample vg("vg", "V#gamma", data_year, weights.Data());
  sample w("w", "W", data_year, weights.Data());
  sample dy("dy", "DY", data_year, weights.Data());
  sample ttg("ttg", "t#bar{t}#gamma", data_year, weights.Data());
  std::vector<sample> samples;
  samples.push_back(data);
  samples.push_back(ttg);
  samples.push_back(w);
  samples.push_back(vg);
  samples.push_back(dy);
  samples.push_back(jj);
  samples.push_back(gj);
  samples.push_back(gg);

  plot p0(samples, "Minv", cut_no_Minv, 40, 0, 2000);
  plot p1(samples, "Photon1.pt", cut, 40, xmin, xmax/2);
  plot p2(samples, "Photon2.pt", cut, 40, xmin, xmax/2);
  plot p3(samples, "Diphoton.qt", cut, nbins/2, xmin, xmax/2);
  plot p4(samples, "Diphoton.deltaPhi", cut, nbins/2, -TMath::Pi(), TMath::Pi());
  plot p5(samples, "Diphoton.deltaEta", cut, nbins/2, -5, 5);
  plot p6(samples, "abs(Diphoton.cosThetaStar)", cut, 20, 0, 1);
  plot p7(samples, "nPV", cut, 80, 0, 80);
  plot p8(samples, "Diphoton.deltaR", cut, 60, 0, 6);
  plot p9(samples, "Photon1.scEta", cut, nbins/2, -5, 5);
  plot p10(samples, "Photon2.scEta", cut, nbins/2, -5, 5);
  plot p11(samples, "Photon1.phi", cut, nbins/4, -TMath::Pi(), TMath::Pi());
  plot p12(samples, "Photon2.phi", cut, nbins/4, -TMath::Pi(), TMath::Pi());
  plot p13(samples, "abs(Diphoton.deltaPhi)", cut, nbins/4, 0, TMath::Pi());
  plot p14(samples, "Photon1.sigmaIphiIphi5x5", cut, 40, 0, 0.04);
  plot p15(samples, "Photon2.sigmaIphiIphi5x5", cut, 40, 0, 0.04);
  plot p16(samples, "Photon1.r9_5x5", cut, nbins/2, 0., 1.0);
  plot p17(samples, "Photon2.r9_5x5", cut, nbins/2, 0., 1.0);
  plot p18(samples, "Photon1.chargedHadIso03", cut, nbins/2, 0., 10);
  plot p19(samples, "Photon2.chargedHadIso03", cut, nbins/2, 0., 10);
  plot p20(samples, "Photon1.hadTowerOverEm", cut, nbins/2, 0., 1.);
  plot p21(samples, "Photon2.hadTowerOverEm", cut, nbins/2, 0., 1.);
  plot p22(samples, "Photon1.hadronicOverEm", cut, nbins/2, 0., 1.);
  plot p23(samples, "Photon2.hadronicOverEm", cut, nbins/2, 0., 1.);
  plot p24(samples, "Photon1.corPhotonIso03", cut, nbins/2, -5., 5.);
  plot p25(samples, "Photon2.corPhotonIso03", cut, nbins/2, -5., 5.);
  plot p26(samples, "Photon1.rhoCorPhotonIso03", cut, nbins/2, 0., 5.);
  plot p27(samples, "Photon2.rhoCorPhotonIso03", cut, nbins/2, 0., 5.);
  plot p28(samples, "Photon1.sigmaIetaIeta", cut, nbins, 0., region=="barrel" ? 0.02 : 0.04);
  plot p29(samples, "Photon2.sigmaIetaIeta", cut, nbins, 0., region=="barrel" ? 0.02 : 0.04);

  std::string extraFilenameInfo(region);
  extraFilenameInfo += "_";
  extraFilenameInfo += data_year;

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
  p14.output("plots", extraFilenameInfo);
  p15.output("plots", extraFilenameInfo);
  p16.output("plots", extraFilenameInfo);
  p17.output("plots", extraFilenameInfo);
  p18.output("plots", extraFilenameInfo);
  p19.output("plots", extraFilenameInfo);
  p20.output("plots", extraFilenameInfo);
  p21.output("plots", extraFilenameInfo);
  p22.output("plots", extraFilenameInfo);
  p23.output("plots", extraFilenameInfo);
  p24.output("plots", extraFilenameInfo);
  p25.output("plots", extraFilenameInfo);
  p26.output("plots", extraFilenameInfo);
  p27.output("plots", extraFilenameInfo);
  p28.output("plots", extraFilenameInfo);
  p29.output("plots", extraFilenameInfo);

}
