#include "diphoton-analysis/Tools/interface/easyplot.hh"
#include "diphoton-analysis/Tools/interface/utilities.hh"

#include "TMath.h"

int main(int argc, char *argv[])
{
  std::string data_year("");

  std::string region;

  if(argc!=3) {
    std::cout << "Syntax: datadriven.exe [barrel/endcap] [2015/2016/2017/2018/2017_2018/2016_2017_2018/2018_newjson]" << std::endl;
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
  if(data_year == "2015" or data_year == "2016" ) {
    kfactor = endcap ? kfactorString("BE", "R1F1_125GeV_CT10") : kfactorString("BB", "R1F1_125GeV_CT10");
  }
  else {
    kfactor = endcap ? kfactorString("BE", "R1F1_125GeV_NNPDF") : kfactorString("BB", "R1F1_125GeV_NNPDF");
  }

  std::string pt_cut("125");
  std::string hlt_cut("HLT_DoublePhoton70 > 0");
  if(data_year == "2016") hlt_cut = "HLT_DoublePhoton60 > 0";
  std::string minv_cut("Diphoton.Minv > 500");
  std::string kinematic_cuts("Photon1.pt>" + pt_cut + " && Photon2.pt>" + pt_cut + "&&" + minv_cut);
  std::string eta_cuts_BB("Photon1.isEB && Photon2.isEB");
  std::string eta_cuts_BE("( (Photon1.isEB && Photon2.isEE) || (Photon2.isEB && Photon1.isEE) )");
  std::string basic_cuts = hlt_cut + "&&" + kinematic_cuts + "&& isGood";
  std::string cut_no_Minv(basic_cuts + "&&" + eta_cuts_BB);
  if(endcap) cut_no_Minv = basic_cuts + "&&" + eta_cuts_BE;
  std::string cut(cut_no_Minv);
  cut += "&& Diphoton.Minv < 1000";

  // initialize chains and default styles
  init();

  std::string trigger("(HLT_DoublePhoton70 || HLT_ECALHT800)");
  if(data_year == "2016") trigger = "(HLT_DoublePhoton60 || HLT_ECALHT800)";
  // define samples to be used in histograms
  sample data("data", "Data", data_year, trigger);
  data.isData = true;
  TString weights(Form("(%s*%s)", scale_factor_cut(atoi(data_year.c_str()), 0).Data(), npv_reweight_str(atoi(data_year.c_str()), 0).Data()));
  sample gg("gg", "#gamma#gamma", data_year, kfactor + std::string("*") + weights.Data());
  sample gj("gj", "#gamma + jets", data_year, weights.Data());
  if(region == "barrel") gj.isDataDrivenBarrel = true;
  if(region == "endcap") gj.isDataDrivenEndcap = true;
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
  samples.push_back(gj);
  samples.push_back(gg);

  plot p0(samples, "Minv", cut_no_Minv, 40, 0, 2000);
  plot p1(samples, "Photon1.pt", cut, 40, 0, 1000);
  plot p2(samples, "Photon2.pt", cut, 40, 0, 1000);
  plot p3(samples, "abs(Diphoton.deltaPhi)", cut, 25, 0, TMath::Pi());
  plot p4(samples, "Diphoton.deltaEta", cut, 50, -5, 5);
  plot p5(samples, "Diphoton.deltaR", cut, 60, 0, 6);
  plot p6(samples, "Photon1.scEta", cut, 25, -2.5, 2.5);
  plot p7(samples, "Photon1.phi", cut, 50, -TMath::Pi(), TMath::Pi());
  plot p8(samples, "Photon2.scEta", cut, 25, -2.5, 2.5);
  plot p9(samples, "Photon2.phi", cut, 50, -TMath::Pi(), TMath::Pi());
  plot p10(samples, "Diphoton.qt", cut, 50, 0, 1000);

  std::string extraFilenameInfo(region);
  extraFilenameInfo += "_datadriven_";
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

}
