#ifndef CROSSSECTIONS_INC
#define CROSSSECTIONS_INC

namespace ExoDiPhotons {

  bool is2017or2018(const TString& sample) {
    if(sample.Contains("mc2017") || sample.Contains("upgrade2018")) return true;
    else return false;
  }

  // provides cross sections (in pb) that are used to calculate event weights
  double crossSection(const TString& sample) {
    double xsec = -1.0;
    if(sample.Contains("DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8")) xsec = 135.1;
    // UL naming convention
    if(sample.Contains("DiPhotonJetsBox_MGG-80toInf_13TeV-sherpa")) xsec = 87.5659749906; // +/-  0.00976657717338 (from GenXsecAnalyzer)
    if(sample.Contains("DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa")) xsec = 82.81; // +/- 0.12
    if(sample.Contains("GGJets_Pt-15_13TeV-sherpa")) xsec = 1.368e+02; // +/- 5.124e-02
    if(sample.Contains("GGJets_M-60To200_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 6.278e+00;
      else xsec = 5.785e+00;
    }
    if(sample.Contains("GGJets_M-200To500_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 2.451e+00;
      else xsec = 2.244e+00;
    }
    if(sample.Contains("GGJets_M-500To1000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 1.739e-01;
      else xsec = 1.510e-01;
    }
    if(sample.Contains("GGJets_M-1000To2000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 1.445e-02;
      else xsec = 1.084e-02;
    }
    if(sample.Contains("GGJets_M-2000To4000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 5.115e-04;
      else xsec = 3.690e-04;
    }
    if(sample.Contains("GGJets_M-4000To6000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 3.394e-06;
      else xsec = 2.451e-06;
    }
    if(sample.Contains("GGJets_M-6000To8000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 4.117e-08;
      else xsec = 1.753e-08;
    }
    if(sample.Contains("GGJets_M-8000To13000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) xsec = 5.754e-10;
      else xsec = 7.053e-11;
    }
    // 2017 Sherpa, from running GenXsecAnalyzer on full sample
    if(sample.Contains("GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 1.862e+04;
    if(sample.Contains("GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 8.625e+03;
    if(sample.Contains("GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 2.194e+03;
    if(sample.Contains("GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 2.583e+02;
    if(sample.Contains("GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 8.520e+01;
    // cross sections from Table 2 of AN2015_241
    if(sample.Contains("GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 2.121e+04;
    if(sample.Contains("GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 9.863e+03;
    if(sample.Contains("GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 2.298e+03;
    if(sample.Contains("GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 2.816e+02;
    if(sample.Contains("GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 9.465e+01;
    if(sample.Contains("GJets_DR-0p4_HT-400To600")) xsec = 1.560e+04;
    // from xsdb
    if(sample.Contains("WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 50260.0;
    if(sample.Contains("WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 52940.0;
    if(sample.Contains("QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 246300000.0;
    if(sample.Contains("QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 28060000.0;
    if(sample.Contains("QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 1710000.0;
    if(sample.Contains("QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 347500.0;
    if(sample.Contains("QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 32060.0;
    if(sample.Contains("QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 6829.0;
    if(sample.Contains("QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 1207.0;
    if(sample.Contains("QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 120.0;
    if(sample.Contains("QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 25.25;
    if(sample.Contains("QCD_HT50to100_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT50to100_TuneCP5_13TeV-madgraph-pythia8")) xsec = 28060000.0;
    if(sample.Contains("QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8")) xsec = 23700000.0;
    // from running GenXsecAnalyzer on full sample
    if(sample.Contains("QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8")) xsec = 1.554e+06;
    if(sample.Contains("QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8")) xsec = 3.234e+05;
    if(sample.Contains("QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8")) xsec = 3.004e+04;
    if(sample.Contains("QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8")) xsec = 6.353e+03;
    if(sample.Contains("QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8")) xsec = 1.095e+03;
    if(sample.Contains("QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8")) xsec = 9.913e+01;
    if(sample.Contains("QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8")
       or sample.Contains("QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8")) xsec = 2.019e+01;
    if(sample.Contains("WGJets_MonoPhoton_PtG-40to130_TuneCUETP8M1_13TeV-madgraph")) xsec = 1.270e+01; // +/- 4.610e-03
    if(sample.Contains("WGJets_MonoPhoton_PtG-130_TuneCUETP8M1_13TeV-madgraph")) xsec = 6.565e-01; // +/- 7.876e-04
    // the following cross section is taken from GenXsecAnalyzer on the v3 dataset; the number given in the XSDB is for the invalid
    // v2 dataset
    if(sample.Contains("WGJets_MonoPhoton_PtG-40to130_TuneCP5_13TeV-madgraph")) xsec = 1.293e+01; // +/- 4.640e-03
    if(sample.Contains("WGJets_MonoPhoton_PtG-130_TuneCP5_13TeV-madgraph")) xsec = 7.152e-01; // +/- 2.628e-04
    if(sample.Contains("TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8")) xsec = 4.108e+00; // +/- 8.777e-03
    if(sample.Contains("DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8")) xsec = 6.491e+03; // +/- 1.045e+01
    // cross sections and filter efficiencies from MCM
    if(sample.Contains("QCD_Pt-20to30_EMEnriched")) xsec = 557600000*0.0096; // filter efficiency error (MCM): 0.0003
    if(sample.Contains("QCD_Pt-30to50_EMEnriched")) xsec = 136000000*0.073; // filter efficiency error (MCM): 0.015
    if(sample.Contains("QCD_Pt-50to80_EMEnriched")) xsec = 19800000*0.146; // filter efficiency error (MCM): 0.021
    if(sample.Contains("QCD_Pt-80to120_EMEnriched")) xsec = 2800000*0.125; // filter efficiency error (MCM): 0.019
    if(sample.Contains("QCD_Pt-120to170_EMEnriched")) xsec = 477000*0.132; // filter efficiency error (MCM): 0.02
    if(sample.Contains("QCD_Pt-170to300_EMEnriched")) xsec = 114000*0.165; // filter efficiency error (MCM): 0.026
    if(sample.Contains("QCD_Pt-300toInf_EMEnriched")) xsec = 9000*0.15; // filter efficiency error (MCM): 0.036
    if(sample.Contains("QCD_Pt_5to10_TuneCUETP8M1")) xsec = 61018300000.;
    if(sample.Contains("QCD_Pt_10to15_TuneCUETP8M1")) xsec = 5887580000.;
    if(sample.Contains("QCD_Pt_15to30_TuneCUETP8M1")) xsec = 1837410000.;
    if(sample.Contains("QCD_Pt_30to50_TuneCUETP8M1")) xsec = 140932000.;
    if(sample.Contains("QCD_Pt_50to80_TuneCUETP8M1")) xsec = 19204300.;
    if(sample.Contains("QCD_Pt_80to120_TuneCUETP8M1")) xsec = 2762530.;
    if(sample.Contains("QCD_Pt_120to170_TuneCUETP8M1")) xsec = 471100.;
    if(sample.Contains("QCD_Pt_170to300_TuneCUETP8M1")) xsec = 117276.;
    if(sample.Contains("QCD_Pt_300to470_TuneCUETP8M1")) xsec = 7823.;
    if(sample.Contains("QCD_Pt_470to600_TuneCUETP8M1")) xsec = 648.2;
    if(sample.Contains("QCD_Pt_600to800_TuneCUETP8M1")) xsec = 186.9;
    if(sample.Contains("QCD_Pt_800to1000_TuneCUETP8M1")) xsec = 32.293;
    if(sample.Contains("QCD_Pt_1000to1400_TuneCUETP8M1")) xsec = 9.4183;
    if(sample.Contains("QCD_Pt_1400to1800_TuneCUETP8M1")) xsec = 0.84265;
    if(sample.Contains("QCD_Pt_1800to2400_TuneCUETP8M1")) xsec = 0.114943;
    if(sample.Contains("QCD_Pt_2400to3200_TuneCUETP8M1")) xsec = 0.00682981;
    if(sample.Contains("QCD_Pt_3200toInf_TuneCUETP8M1")) xsec = 0.000165445;
    // cross sections from xsdb
    if(sample.Contains("QCD_Pt_15to30_TuneCP5_13TeV_pythia8")) xsec = 1246000000.0;
    if(sample.Contains("QCD_Pt_30to50_TuneCP5_13TeV_pythia8")) xsec = 106900000.0;
    if(sample.Contains("QCD_Pt_50to80_TuneCP5_13TeV_pythia8")) xsec = 15710000.0;
    if(sample.Contains("QCD_Pt_80to120_TuneCP5_13TeV_pythia8")) xsec = 2336000.0;
    if(sample.Contains("QCD_Pt_120to170_TuneCP5_13TeV_pythia8")) xsec = 407300.0;
    if(sample.Contains("QCD_Pt_170to300_TuneCP5_13TeV_pythia8")) xsec = 103500.0;
    if(sample.Contains("QCD_Pt_300to470_TuneCP5_13TeV_pythia8")) xsec = 6830.0;
    if(sample.Contains("QCD_Pt_470to600_TuneCP5_13TeV_pythia8")) xsec = 552.1;
    if(sample.Contains("QCD_Pt_600to800_TuneCP5_13TeV_pythia8")) xsec = 156.5;
    if(sample.Contains("QCD_Pt_800to1000_TuneCP5_13TeV_pythia8")) xsec = 26.28;
    if(sample.Contains("QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8")) xsec = 7.47;
    if(sample.Contains("QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8")) xsec = 0.6484;
    if(sample.Contains("QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8")) xsec = 0.08743;
    if(sample.Contains("QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8")) xsec = 0.005236;
    if(sample.Contains("QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8")) xsec = 0.0001357;
    // cross sections from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
    if(sample.Contains("WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) xsec = 405.271;
    if(sample.Contains("WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8")) xsec = 1.916e+02; // +/- 2.954e-01
    if(sample.Contains("WGToLNuG_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 4.647e+02; // +/- 1.423e-01
    if(sample.Contains("ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) xsec = 117.864;
    if(sample.Contains("ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8")) xsec = 5.559e+01; // +/- 8.293e-02
    if(sample.Contains("TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8")) xsec = 3.697;
    if(sample.Contains("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) xsec = 1921.8*3;
    // MCM cross sections (NLO)
    if(sample.Contains("WToLNu_0J_13TeV-amcatnloFXFX-pythia8")) xsec = 5.844e+04; // +- 7.676e+01 pb
    if(sample.Contains("WToLNu_1J_13TeV-amcatnloFXFX-pythia8")) xsec = 1.128e+04; // +- 3.873e+02 pb
    if(sample.Contains("WToLNu_2J_13TeV-amcatnloFXFX-pythia8")) xsec = 2.544e+03; // +- 2.485e+02 pb
    // from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    if(sample.Contains("TTJets_")) xsec = 815.96 ;
    // from running GenXsecAnalyzer on full sample
    if(sample.Contains("DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 8.096e+02; // +- 1.718e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 1.609e+02; // +- 4.384e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 4.858e+01; // +- 1.360e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 6.978e+00; // +- 2.120e-03 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 1.757e+00; // +- 5.599e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 8.098e-01; // +- 4.354e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 1.930e-01; // +- 2.526e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8")) xsec = 3.513e-03; // +- 5.263e-06 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-40to70_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 3.105e+02; // +- 3.212e-01 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 1.471e+02; // +- 4.371e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 1.609e+02; // +- 4.454e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 4.867e+01; // +- 1.395e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 6.984e+00; // +- 2.070e-03 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 1.744e+00; // +- 5.613e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 8.048e-01; // +- 4.359e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 1.880e+00; // +- 1.597e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8")) xsec = 3.476e-03; // +- 5.443e-06 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-70to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 1.704e+02; // +- 5.046e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 1.475e+02; // +- 8.438e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 4.104e+01; // +- 4.009e-02 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 5.675e+00; // +- 5.273e-03 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 1.358e+00; // +- 4.539e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 6.236e-01; // +- 3.671e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 1.512e-01; // +- 1.884e-04 pb
    if(sample.Contains("DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8")) xsec = 3.659e-03; // +- 5.548e-06 pb
    if(sample.Contains("TTGamma_Dilept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8")) xsec = 3.427e-02; // +- 6.371e-06 pb
    if(sample.Contains("TTGamma_Dilept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8")) xsec = 6.800e-03; // +- 1.598e-06 pb
    if(sample.Contains("TTGamma_Hadronic_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8")) xsec = 1.256e-01; // +- 2.998e-05 pb
    if(sample.Contains("TTGamma_Hadronic_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8")) xsec = 2.678e-02; // +- 6.561e-06 pb
    if(sample.Contains("TTGamma_SingleLept_ptGamma100-200_TuneCP5_13TeV-madgraph-pythia8")) xsec = 1.320e-01; // +- 1.011e-05 pb
    if(sample.Contains("TTGamma_SingleLept_ptGamma200inf_TuneCP5_13TeV-madgraph-pythia8")) xsec = 2.703e-02; // +- 2.680e-06 pb
    if(sample.Contains("TTGamma_Dilept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8")) xsec = 3.428e-02; // +- 5.993e-06 pb
    if(sample.Contains("TTGamma_Dilept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8")) xsec = 6.797e-03; // +- 8.939e-07 pb
    if(sample.Contains("TTGamma_Hadronic_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8")) xsec = 1.251e-01; // +- 2.912e-05 pb
    if(sample.Contains("TTGamma_Hadronic_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8")) xsec = 2.687e-02; // +- 6.644e-06 pb
    if(sample.Contains("TTGamma_SingleLept_ptGamma100-200_TuneCP5_PSweights_13TeV-madgraph-pythia8")) xsec = 1.320e-01; // +- 9.733e-06 pb
    if(sample.Contains("TTGamma_SingleLept_ptGamma200inf_TuneCP5_PSweights_13TeV-madgraph-pythia8")) xsec = 2.703e-02; // +- 2.555e-06 pb
    if(sample.Contains("GGGJets_13TeV-sherpa")) xsec = 1.814e-01;
    if(sample.Contains("GGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8")) xsec = 1.720e+00;
    // from running GenXsecAnalyzer on full sample
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 9.139e-02;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-1_M-2000To3000_13TeV-sherpa")) xsec = 1.160e-02;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 1.397e-01;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) xsec = 1.752e-02;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-4_M-2000To3000_13TeV-sherpa")) xsec = 2.020e-02;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) xsec = 7.331e-02;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 5.164e-02;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-2000To3000_13TeV-sherpa")) xsec = 5.518e-02;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-200To500_13TeV-sherpa")) xsec = 8.985e-01;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 8.966e-02;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 4.510e-02;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-1_M-2000To3500_13TeV-sherpa")) xsec = 9.442e-03;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 1.026e-01;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) xsec = 8.453e-03;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-4_M-2000To3500_13TeV-sherpa")) xsec = 8.239e-03;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-4_M-500To1000_13TeV-sherpa")) xsec = 7.398e-02;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 2.126e-02;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-2000To3500_13TeV-sherpa")) xsec = 2.365e-02;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-200To500_13TeV-sherpa")) xsec = 8.924e-01;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 8.104e-02;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 2.553e-02;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 6.604e-03;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 8.981e-02;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) xsec = 6.494e-03;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-4_M-2000To4000_13TeV-sherpa")) xsec = 3.474e-03;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) xsec = 7.427e-02;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 1.234e-02;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 1.050e-02;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-200To500_13TeV-sherpa")) xsec = 8.894e-01;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 7.821e-02;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 1.661e-02;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-2000To3000_13TeV-sherpa")) xsec = 3.809e-03;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-3000To4500_13TeV-sherpa")) xsec = 6.004e-04;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 8.373e-02;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) xsec = 6.033e-03;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-2000To3000_13TeV-sherpa")) xsec = 7.721e-04;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-3000To4500_13TeV-sherpa")) xsec = 7.878e-04;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-500To1000_13TeV-sherpa")) xsec = 7.485e-02;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 9.129e-03;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-2000To3000_13TeV-sherpa")) xsec = 2.688e-03;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-200To500_13TeV-sherpa")) xsec = 8.966e-01;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-3000To4500_13TeV-sherpa")) xsec = 2.270e-03;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 7.703e-02;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 1.221e-02;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-2000To3000_13TeV-sherpa")) xsec = 2.423e-03;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-3000To5000_13TeV-sherpa")) xsec = 5.167e-04;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 8.025e-02;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) xsec = 5.999e-03;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-2000To3000_13TeV-sherpa")) xsec = 3.925e-04;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-3000To5000_13TeV-sherpa")) xsec = 3.902e-04;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) xsec = 7.471e-02;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 7.829e-03;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-2000To3000_13TeV-sherpa")) xsec = 1.382e-03;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-3000To5000_13TeV-sherpa")) xsec = 1.193e-03;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-200To500_13TeV-sherpa")) xsec = 8.940e-01;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 7.640e-02;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 9.948e-03;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 1.969e-03;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-4000To5500_13TeV-sherpa")) xsec = 4.542e-05;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 7.911e-02;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) xsec = 6.047e-03;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-2000To4000_13TeV-sherpa")) xsec = 3.688e-04;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-4000To5500_13TeV-sherpa")) xsec = 8.207e-05;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-500To1000_13TeV-sherpa")) xsec = 7.522e-02;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 7.209e-03;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 1.218e-03;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-4000To5500_13TeV-sherpa")) xsec = 2.419e-04;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-200To500_13TeV-sherpa")) xsec = 8.947e-01;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 7.599e-02;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 8.717e-03;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 1.382e-03;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-4000To6000_13TeV-sherpa")) xsec = 4.460e-05;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 7.819e-02;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) xsec = 6.090e-03;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-2000To4000_13TeV-sherpa")) xsec = 2.640e-04;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-4000To6000_13TeV-sherpa")) xsec = 4.472e-05;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) xsec = 7.535e-02;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 6.887e-03;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 7.727e-04;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-4000To6000_13TeV-sherpa")) xsec = 1.393e-04;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-200To500_13TeV-sherpa")) xsec = 9.004e-01;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 7.598e-02;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.076390000;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006598000;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000435100;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-4000To7000_13TeV-sherpa")) xsec = 0.000048420;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.077180000;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.007501000;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000784200;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-4000To7000_13TeV-sherpa")) xsec = 0.000032810;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.076230000;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006437000;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000324700;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-4000To8000_13TeV-sherpa")) xsec = 0.000019740;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.076270000;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006941000;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000517900;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-4000To8000_13TeV-sherpa")) xsec = 0.000021400;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.075690000;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006386000;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000280200;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-4000To9000_13TeV-sherpa")) xsec = 0.000009672;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.076270000;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006734000;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000395900;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-4000To9000_13TeV-sherpa")) xsec = 0.000013940;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.075890000;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006377000;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000259000;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-4000To10000_13TeV-sherpa")) xsec = 0.000005716;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.076080000;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006554000;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000331300;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-4000To10000_13TeV-sherpa")) xsec = 0.000009366;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.075590000;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006361000;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000250400;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-4000To11000_13TeV-sherpa")) xsec = 0.000003906;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) xsec = 0.075970000;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) xsec = 0.006527000;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) xsec = 0.000299700;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-4000To11000_13TeV-sherpa")) xsec = 0.000006698;
    // from running GenXsecAnalyzer on full sample
    if(sample.Contains("GG_M-200To500_Pt-70_13TeV-sherpa")) xsec = 8.923e-01;
    if(sample.Contains("GG_M-500To1000_Pt-70_13TeV-sherpa")) xsec = 7.592e-02;
    if(sample.Contains("GG_M-1000To2000_Pt-70_13TeV-sherpa")) xsec = 6.292e-03;
    if(sample.Contains("GG_M-2000To4000_Pt-70_13TeV-sherpa")) xsec = 2.315e-04;
    if(sample.Contains("GG_M-4000To8000_Pt-70_13TeV-sherpa")) xsec = 1.669e-06;
    if(sample.Contains("GG_M-8000To13000_Pt-70_13TeV-sherpa")) xsec = 5.430e-11;
    if(sample.Contains("GG_M-500To1000_Pt70_TuneCP2_13TeV-pythia8")) xsec = 1.344e-01;
    if(sample.Contains("GG_M-1000To2000_Pt70_TuneCP2_13TeV-pythia8")) xsec = 1.357e-02;
    if(sample.Contains("GG_M-2000To4000_Pt70_TuneCP2_13TeV-pythia8")) xsec = 6.736e-04;
    if(sample.Contains("GG_M-4000To13000_Pt70_TuneCP2_13TeV-pythia8")) xsec = 8.627e-06;
    // 500To1000 xsec calculated on partial dataset, ~ 81% complete
    if(sample.Contains("GG_M-500To1000_Pt70_TuneCUEP8M1_13TeV-pythia8")) xsec = 0.109534;
    if(sample.Contains("GG_M-1000To2000_Pt70_TuneCUEP8M1_13TeV-pythia8")) xsec = 0.0101229;
    if(sample.Contains("GG_M-2000To4000_Pt70_TuneCUEP8M1_13TeV-pythia8")) xsec = 0.000474448;
    if(sample.Contains("GG_M-4000To13000_Pt70_TuneCUEP8M1_13TeV-pythia8")) xsec = 5.505e-06;
    // use cross sections for corresponding 2017 samples in order to handle differences in tune
    if(sample.Contains("RSGravToGG_kMpl-001_M-750_TuneCUEP8M1_13TeV-pythia8")) xsec =  4.850e-02;
    if(sample.Contains("RSGravToGG_kMpl-001_M-1000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.133e-02;
    if(sample.Contains("RSGravToGG_kMpl-001_M-1250_TuneCUEP8M1_13TeV-pythia8")) xsec =  3.428e-03;
    if(sample.Contains("RSGravToGG_kMpl-001_M-1500_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.234e-03;
    if(sample.Contains("RSGravToGG_kMpl-001_M-1750_TuneCUEP8M1_13TeV-pythia8")) xsec =  4.981e-04;
    if(sample.Contains("RSGravToGG_kMpl-001_M-2000_TuneCUEP8M1_13TeV-pythia8")) xsec =  2.201e-04;
    if(sample.Contains("RSGravToGG_kMpl-001_M-2250_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.036e-04;
    if(sample.Contains("RSGravToGG_kMpl-001_M-2500_TuneCUEP8M1_13TeV-pythia8")) xsec =  5.074e-05;
    if(sample.Contains("RSGravToGG_kMpl-001_M-2750_TuneCUEP8M1_13TeV-pythia8")) xsec =  2.613e-05;
    if(sample.Contains("RSGravToGG_kMpl-001_M-3000_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.384e-05;
    if(sample.Contains("RSGravToGG_kMpl-001_M-3250_TuneCUEP8M1_13TeV-pythia8")) xsec =  7.548e-06;
    if(sample.Contains("RSGravToGG_kMpl-001_M-3500_TuneCUEP8M1_13TeV-pythia8")) xsec =  4.226e-06;
    if(sample.Contains("RSGravToGG_kMpl-001_M-4000_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.439e-06;
    if(sample.Contains("RSGravToGG_kMpl-001_M-5000_TuneCUEP8M1_13TeV-pythia8")) xsec =  2.150e-07;
    if(sample.Contains("RSGravToGG_kMpl-01_M-750_TuneCUEP8M1_13TeV-pythia8")) xsec =  4.870e+00;
    if(sample.Contains("RSGravToGG_kMpl-01_M-1000_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.120e+00;
    if(sample.Contains("RSGravToGG_kMpl-01_M-1250_TuneCUEP8M1_13TeV-pythia8")) xsec =  3.413e-01;
    if(sample.Contains("RSGravToGG_kMpl-01_M-1500_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.224e-01;
    if(sample.Contains("RSGravToGG_kMpl-01_M-1750_TuneCUEP8M1_13TeV-pythia8")) xsec = 4.940e-02;
    if(sample.Contains("RSGravToGG_kMpl-01_M-2000_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.180e-02;
    if(sample.Contains("RSGravToGG_kMpl-01_M-2250_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.025e-02;
    if(sample.Contains("RSGravToGG_kMpl-01_M-2500_TuneCUEP8M1_13TeV-pythia8")) xsec = 5.051e-03;
    if(sample.Contains("RSGravToGG_kMpl-01_M-3000_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.373e-03;
    if(sample.Contains("RSGravToGG_kMpl-01_M-3500_TuneCUEP8M1_13TeV-pythia8")) xsec = 4.229e-04;
    if(sample.Contains("RSGravToGG_kMpl-01_M-4000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.435e-04;
    if(sample.Contains("RSGravToGG_kMpl-01_M-4250_TuneCUEP8M1_13TeV-pythia8")) xsec =  8.663e-05;
    if(sample.Contains("RSGravToGG_kMpl-01_M-4500_TuneCUEP8M1_13TeV-pythia8")) xsec =  5.367e-05;
    if(sample.Contains("RSGravToGG_kMpl-01_M-4750_TuneCUEP8M1_13TeV-pythia8")) xsec =  3.368e-05;
    if(sample.Contains("RSGravToGG_kMpl-01_M-5000_TuneCUEP8M1_13TeV-pythia8")) xsec =  2.163e-05;
    if(sample.Contains("RSGravToGG_kMpl-01_M-5250_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.398e-05;
    if(sample.Contains("RSGravToGG_kMpl-01_M-5500_TuneCUEP8M1_13TeV-pythia8")) xsec = 9.145e-06;
    if(sample.Contains("RSGravToGG_kMpl-01_M-5750_TuneCUEP8M1_13TeV-pythia8")) xsec =  6.022e-06;
    if(sample.Contains("RSGravToGG_kMpl-01_M-6000_TuneCUEP8M1_13TeV-pythia8")) xsec =  3.967e-06;
    if(sample.Contains("RSGravToGG_kMpl-01_M-6500_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.742e-06;
    if(sample.Contains("RSGravToGG_kMpl-01_M-7000_TuneCUEP8M1_13TeV-pythia8")) xsec =  7.583e-07;
    if(sample.Contains("RSGravToGG_kMpl-01_M-8000_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.269e-07;
    if(sample.Contains("RSGravToGG_kMpl-02_M-750_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.905e+01;
    if(sample.Contains("RSGravToGG_kMpl-02_M-1000_TuneCUEP8M1_13TeV-pythia8")) xsec =  4.403e+00;
    if(sample.Contains("RSGravToGG_kMpl-02_M-1250_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.328e+00;
    if(sample.Contains("RSGravToGG_kMpl-02_M-1500_TuneCUEP8M1_13TeV-pythia8")) xsec = 4.750e-01;
    if(sample.Contains("RSGravToGG_kMpl-02_M-1750_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.919e-01;
    if(sample.Contains("RSGravToGG_kMpl-02_M-2000_TuneCUEP8M1_13TeV-pythia8")) xsec =  8.481e-02;
    if(sample.Contains("RSGravToGG_kMpl-02_M-2250_TuneCUEP8M1_13TeV-pythia8")) xsec =  3.981e-02;
    if(sample.Contains("RSGravToGG_kMpl-02_M-2500_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.967e-02;
    if(sample.Contains("RSGravToGG_kMpl-02_M-3000_TuneCUEP8M1_13TeV-pythia8")) xsec = 5.410e-03;
    if(sample.Contains("RSGravToGG_kMpl-02_M-3500_TuneCUEP8M1_13TeV-pythia8")) xsec =  1.669e-03;
    if(sample.Contains("RSGravToGG_kMpl-02_M-4000_TuneCUEP8M1_13TeV-pythia8")) xsec =  5.707e-04;
    if(sample.Contains("RSGravToGG_kMpl-02_M-4500_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.157e-04;
    if(sample.Contains("RSGravToGG_kMpl-02_M-4750_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.364e-04;
    if(sample.Contains("RSGravToGG_kMpl-02_M-5000_TuneCUEP8M1_13TeV-pythia8")) xsec =  8.732e-05;
    if(sample.Contains("RSGravToGG_kMpl-02_M-5250_TuneCUEP8M1_13TeV-pythia8")) xsec =  5.709e-05;
    if(sample.Contains("RSGravToGG_kMpl-02_M-5500_TuneCUEP8M1_13TeV-pythia8")) xsec =  3.748e-05;
    if(sample.Contains("RSGravToGG_kMpl-02_M-5750_TuneCUEP8M1_13TeV-pythia8")) xsec =  2.479e-05;
    if(sample.Contains("RSGravToGG_kMpl-02_M-6000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.652e-05;
    if(sample.Contains("RSGravToGG_kMpl-02_M-6500_TuneCUEP8M1_13TeV-pythia8")) xsec =  7.426e-06;
    if(sample.Contains("RSGravToGG_kMpl-02_M-7000_TuneCUEP8M1_13TeV-pythia8")) xsec =  3.360e-06;
    if(sample.Contains("RSGravToGG_kMpl-02_M-8000_TuneCUEP8M1_13TeV-pythia8")) xsec =  6.570e-07;
    // use cross sections for corresponding 2017 samples in order to handle differences in tune
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-1000_TuneCUEP8M1_13TeV-pythia8")) xsec = 5.945e-12;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-1250_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.132e-12;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-1500_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.432e-13;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-1750_TuneCUEP8M1_13TeV-pythia8")) xsec = 5.951e-14;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-2000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.624e-14;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-2250_TuneCUEP8M1_13TeV-pythia8")) xsec = 4.882e-15;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-2500_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.574e-15;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-2750_TuneCUEP8M1_13TeV-pythia8")) xsec = 5.413e-16;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-3000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.962e-16;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-3250_TuneCUEP8M1_13TeV-pythia8")) xsec = 7.432e-17;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-3500_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.933e-17;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-4000_TuneCUEP8M1_13TeV-pythia8")) xsec = 7.510e-15;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-4500_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.143e-18;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-5000_TuneCUEP8M1_13TeV-pythia8")) xsec = 3.283e-19;
    if(sample.Contains("GluGluSpin0ToGG_W-0p014_M-750_TuneCUEP8M1_13TeV-pythia8")) xsec = 3.035e-11;
    if(sample.Contains("GluGluSpin0ToGG_W-1p4_M-1000_TuneCUEP8M1_13TeV-pythia8")) xsec = 6.140e-10;
    if(sample.Contains("GluGluSpin0ToGG_W-1p4_M-1500_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.704e-11;
    if(sample.Contains("GluGluSpin0ToGG_W-1p4_M-2000_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.120e-12;
    if(sample.Contains("GluGluSpin0ToGG_W-1p4_M-3000_TuneCUEP8M1_13TeV-pythia8")) xsec = 6.077e-14;
    if(sample.Contains("GluGluSpin0ToGG_W-1p4_M-4000_TuneCUEP8M1_13TeV-pythia8")) xsec = 7.510e-15;
    if(sample.Contains("GluGluSpin0ToGG_W-1p4_M-5000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.816e-15;
    if(sample.Contains("GluGluSpin0ToGG_W-1p4_M-750_TuneCUEP8M1_13TeV-pythia8")) xsec = 3.042e-09;
    if(sample.Contains("GluGluSpin0ToGG_W-5p6_M-1000_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.681e-09;
    if(sample.Contains("GluGluSpin0ToGG_W-5p6_M-1500_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.406e-10;
    if(sample.Contains("GluGluSpin0ToGG_W-5p6_M-2000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.451e-11;
    if(sample.Contains("GluGluSpin0ToGG_W-5p6_M-3000_TuneCUEP8M1_13TeV-pythia8")) xsec = 7.361e-13;
    if(sample.Contains("GluGluSpin0ToGG_W-5p6_M-4000_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.144e-13;
    if(sample.Contains("GluGluSpin0ToGG_W-5p6_M-5000_TuneCUEP8M1_13TeV-pythia8")) xsec = 2.890e-14;
    if(sample.Contains("GluGluSpin0ToGG_W-5p6_M-750_TuneCUEP8M1_13TeV-pythia8")) xsec = 1.247e-08;
    // from running GenXsecAnalyzer on full sample (2017)
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_750_TuneCP2_13TeV_pythia8")) xsec =  3.035e-11;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_1000_TuneCP2_13TeV_pythia8")) xsec =  5.945e-12;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_1250_TuneCP2_13TeV_pythia8")) xsec =  1.132e-12;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_1500_TuneCP2_13TeV_pythia8")) xsec =  2.432e-13;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_1750_TuneCP2_13TeV_pythia8")) xsec = 5.951e-14;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_2000_TuneCP2_13TeV_pythia8")) xsec = 1.624e-14;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_2250_TuneCP2_13TeV_pythia8")) xsec =  4.882e-15;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_2500_TuneCP2_13TeV_pythia8")) xsec =  1.574e-15;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_2750_TuneCP2_13TeV_pythia8")) xsec = 5.413e-16;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_3000_TuneCP2_13TeV_pythia8")) xsec =  1.962e-16;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_3250_TuneCP2_13TeV_pythia8")) xsec = 7.432e-17;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_3500_TuneCP2_13TeV_pythia8")) xsec =  2.933e-17;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_4000_TuneCP2_13TeV_pythia8")) xsec =  5.239e-18;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_4500_TuneCP2_13TeV_pythia8")) xsec = 1.143e-18;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_0p014_M_5000_TuneCP2_13TeV_pythia8")) xsec =  3.283e-19;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_750_TuneCP2_13TeV_pythia8")) xsec =  3.042e-09;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_1000_TuneCP2_13TeV_pythia8")) xsec =  6.140e-10;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_1250_TuneCP2_13TeV_pythia8")) xsec = 1.202e-10;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_1500_TuneCP2_13TeV_pythia8")) xsec =  2.704e-11;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_1750_TuneCP2_13TeV_pythia8")) xsec =  7.066e-12;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_2000_TuneCP2_13TeV_pythia8")) xsec =  2.120e-12;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_2250_TuneCP2_13TeV_pythia8")) xsec =  7.305e-13;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_2500_TuneCP2_13TeV_pythia8")) xsec =  2.835e-13;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_3000_TuneCP2_13TeV_pythia8")) xsec =  6.077e-14;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_3500_TuneCP2_13TeV_pythia8")) xsec = 1.874e-14;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_4000_TuneCP2_13TeV_pythia8")) xsec =  7.510e-15;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_4250_TuneCP2_13TeV_pythia8")) xsec = 5.052e-15;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_4500_TuneCP2_13TeV_pythia8")) xsec = 3.501e-15;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_4750_TuneCP2_13TeV_pythia8")) xsec =  2.501e-15;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_1p4_M_5000_TuneCP2_13TeV_pythia8")) xsec = 1.816e-15;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_750_TuneCP2_13TeV_pythia8")) xsec =  1.247e-08;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_1000_TuneCP2_13TeV_pythia8")) xsec =  2.681e-09;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_1250_TuneCP2_13TeV_pythia8")) xsec =  5.652e-10;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_1500_TuneCP2_13TeV_pythia8")) xsec =  1.406e-10;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_1750_TuneCP2_13TeV_pythia8")) xsec =  4.166e-11;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_2000_TuneCP2_13TeV_pythia8")) xsec =  1.451e-11;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_2250_TuneCP2_13TeV_pythia8")) xsec =  5.826e-12;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_2500_TuneCP2_13TeV_pythia8")) xsec =  2.652e-12;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_3000_TuneCP2_13TeV_pythia8")) xsec =  7.361e-13;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_3500_TuneCP2_13TeV_pythia8")) xsec =  2.657e-13;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_4000_TuneCP2_13TeV_pythia8")) xsec =  1.144e-13;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_4500_TuneCP2_13TeV_pythia8")) xsec =  5.519e-14;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_4750_TuneCP2_13TeV_pythia8")) xsec =  3.954e-14;
    if(sample.Contains("GluGluSpin0ToGammaGamma_W_5p6_M_5000_TuneCP2_13TeV_pythia8")) xsec =  2.890e-14;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_750_TuneCP2_13TeV_pythia8")) xsec =  4.850e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_1000_TuneCP2_13TeV_pythia8")) xsec = 1.133e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_1250_TuneCP2_13TeV_pythia8")) xsec =  3.428e-03;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_1500_TuneCP2_13TeV_pythia8")) xsec =  1.234e-03;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_1750_TuneCP2_13TeV_pythia8")) xsec =  4.981e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_2000_TuneCP2_13TeV_pythia8")) xsec =  2.201e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_2250_TuneCP2_13TeV_pythia8")) xsec =  1.036e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_2500_TuneCP2_13TeV_pythia8")) xsec =  5.074e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_2750_TuneCP2_13TeV_pythia8")) xsec =  2.613e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_3000_TuneCP2_13TeV_pythia8")) xsec =  1.384e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_3250_TuneCP2_13TeV_pythia8")) xsec =  7.548e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_3500_TuneCP2_13TeV_pythia8")) xsec =  4.226e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_4000_TuneCP2_13TeV_pythia8")) xsec =  1.439e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl001_M_5000_TuneCP2_13TeV_pythia8")) xsec =  2.150e-07;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_750_TuneCP2_13TeV_pythia8")) xsec =  4.870e+00;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_1000_TuneCP2_13TeV_pythia8")) xsec =  1.120e+00;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_1250_TuneCP2_13TeV_pythia8")) xsec =  3.413e-01;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_1500_TuneCP2_13TeV_pythia8")) xsec =  1.224e-01;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_1750_TuneCP2_13TeV_pythia8")) xsec = 4.940e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_2000_TuneCP2_13TeV_pythia8")) xsec = 2.180e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_2250_TuneCP2_13TeV_pythia8")) xsec = 1.025e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_2500_TuneCP2_13TeV_pythia8")) xsec = 5.051e-03;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_3000_TuneCP2_13TeV_pythia8")) xsec =  1.373e-03;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_3500_TuneCP2_13TeV_pythia8")) xsec = 4.229e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_4000_TuneCP2_13TeV_pythia8")) xsec = 1.435e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_4250_TuneCP2_13TeV_pythia8")) xsec =  8.663e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_4500_TuneCP2_13TeV_pythia8")) xsec =  5.367e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_4750_TuneCP2_13TeV_pythia8")) xsec =  3.368e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_5000_TuneCP2_13TeV_pythia8")) xsec =  2.163e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_5250_TuneCP2_13TeV_pythia8")) xsec =  1.398e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_5500_TuneCP2_13TeV_pythia8")) xsec = 9.145e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_5750_TuneCP2_13TeV_pythia8")) xsec =  6.022e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_6000_TuneCP2_13TeV_pythia8")) xsec =  3.967e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_6500_TuneCP2_13TeV_pythia8")) xsec =  1.742e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_7000_TuneCP2_13TeV_pythia8")) xsec =  7.583e-07;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl01_M_8000_TuneCP2_13TeV_pythia8")) xsec =  1.269e-07;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_750_TuneCP2_13TeV_pythia8")) xsec =  1.905e+01;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_1000_TuneCP2_13TeV_pythia8")) xsec =  4.403e+00;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_1250_TuneCP2_13TeV_pythia8")) xsec =  1.328e+00;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_1500_TuneCP2_13TeV_pythia8")) xsec = 4.750e-01;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_1750_TuneCP2_13TeV_pythia8")) xsec =  1.919e-01;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_2000_TuneCP2_13TeV_pythia8")) xsec =  8.481e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_2250_TuneCP2_13TeV_pythia8")) xsec =  3.981e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_2500_TuneCP2_13TeV_pythia8")) xsec =  1.967e-02;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_3000_TuneCP2_13TeV_pythia8")) xsec = 5.410e-03;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_3500_TuneCP2_13TeV_pythia8")) xsec =  1.669e-03;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_4000_TuneCP2_13TeV_pythia8")) xsec =  5.707e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_4500_TuneCP2_13TeV_pythia8")) xsec = 2.157e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_4750_TuneCP2_13TeV_pythia8")) xsec = 1.364e-04;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_5000_TuneCP2_13TeV_pythia8")) xsec =  8.732e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_5250_TuneCP2_13TeV_pythia8")) xsec =  5.709e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_5500_TuneCP2_13TeV_pythia8")) xsec =  3.748e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_5750_TuneCP2_13TeV_pythia8")) xsec =  2.479e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_6000_TuneCP2_13TeV_pythia8")) xsec = 1.652e-05;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_6500_TuneCP2_13TeV_pythia8")) xsec =  7.426e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_7000_TuneCP2_13TeV_pythia8")) xsec =  3.360e-06;
    if(sample.Contains("RSGravitonToGammaGamma_kMpl02_M_8000_TuneCP2_13TeV_pythia8")) xsec =  6.570e-07;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.249e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.286e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8")) xsec =  3.370e-03;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8")) xsec =  3.021e-03;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.260e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.245e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8")) xsec =  1.443e-03;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8")) xsec =  1.605e-03;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.267e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.254e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8")) xsec =  8.234e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8")) xsec =  8.481e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.269e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.273e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  8.460e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8")) xsec =  2.306e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.272e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.284e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.759e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8")) xsec =  1.383e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.272e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.301e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.195e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8")) xsec =  8.238e-05;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.272e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.305e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.033e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8")) xsec =  4.982e-05;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.273e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.315e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.057e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8")) xsec =  3.128e-05;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.274e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.319e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.115e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8")) xsec =  2.061e-05;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.277e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.325e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.269e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8")) xsec =  1.120e-05;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.277e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.328e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.403e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8")) xsec =  8.330e-06;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.274e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.332e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.500e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8")) xsec =  7.580e-06;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.277e-01;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.331e-02;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.594e-04;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8")) xsec =  7.635e-06;
    if(sample.Contains("ADDGravToGG_NegInt-0_LambdaT-13000_M-4000To12990_TuneCP2_13TeV-pythia8")) xsec =  7.623e-06;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.311e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.903e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4000_M-2000To3000_TuneCP2_13TeV-pythia8")) xsec =  5.572e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4000_M-3000To4000_TuneCP2_13TeV-pythia8")) xsec =  3.809e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.296e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.630e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4500_M-2000To3000_TuneCP2_13TeV-pythia8")) xsec =  2.800e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-4500_M-3000To4500_TuneCP2_13TeV-pythia8")) xsec =  2.166e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.291e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.507e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5000_M-2000To3000_TuneCP2_13TeV-pythia8")) xsec =  1.707e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5000_M-3000To5000_TuneCP2_13TeV-pythia8")) xsec =  1.239e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.287e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.443e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5500_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  1.643e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-5500_M-4000To5500_TuneCP2_13TeV-pythia8")) xsec =  3.124e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.282e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.409e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  1.234e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6000_M-4000To6000_TuneCP2_13TeV-pythia8")) xsec =  2.006e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.284e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.386e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6500_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  1.028e-03;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-6500_M-4000To6500_TuneCP2_13TeV-pythia8")) xsec =  1.296e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.280e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.372e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  9.073e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7000_M-4000To7000_TuneCP2_13TeV-pythia8")) xsec =  8.497e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.280e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.362e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7500_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  8.364e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-7500_M-4000To7500_TuneCP2_13TeV-pythia8")) xsec =  5.808e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.280e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.354e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  7.903e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8000_M-4000To8000_TuneCP2_13TeV-pythia8")) xsec =  4.137e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8500_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.277e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8500_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.350e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8500_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  7.583e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-8500_M-4000To8500_TuneCP2_13TeV-pythia8")) xsec =  3.088e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-9000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.278e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-9000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.351e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-9000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  7.384e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-9000_M-4000To9000_TuneCP2_13TeV-pythia8")) xsec =  2.410e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-10000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.280e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-10000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.347e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-10000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  7.144e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-10000_M-4000To10000_TuneCP2_13TeV-pythia8")) xsec =  1.679e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-11000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.275e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-11000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec =  1.342e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-11000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.984e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-11000_M-4000To11000_TuneCP2_13TeV-pythia8")) xsec =  1.336e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-13000_M-500To1000_TuneCP2_13TeV-pythia8")) xsec =  1.278e-01;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-13000_M-1000To2000_TuneCP2_13TeV-pythia8")) xsec = 1.340e-02;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-13000_M-2000To4000_TuneCP2_13TeV-pythia8")) xsec =  6.859e-04;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To13000_TuneCP2_13TeV-pythia8")) xsec =  1.059e-05;
    if(sample.Contains("ADDGravToGG_NegInt-1_LambdaT-13000_M-4000To12990_TuneCP2_13TeV-pythia8")) xsec =  1.061e-05;
    // do not use weights for data
    //    if(sample.Contains("Run2015") || sample.Contains("Run2016") || sample.Contains("Run2017")) xsec = 1.0;
    if(sample.Contains("Run2015") || sample.Contains("Run2016") || sample.Contains("Run2017") || sample.Contains("Run2018")) xsec = 1.0;

    if(xsec < 0) throw cms::Exception("Could not determine cross section from output file name");

    //    std::cout << "Using cross section " << xsec << " for sample " << sample << std::endl;

    return xsec;
  }

  double averageWeight(const TString& sample) {
    double average = 1.0;

    // average weight is non-zero for these samples because
    // of the njet weighting in Sherpa
    if(sample.Contains("GGJets_M-60To200_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 3.52301168809078302e-01;
      else average = 3.895719e-01;
    }
    if(sample.Contains("GGJets_M-200To500_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 2.63880645720520890e-01;
      else average = 2.818643e-01;
    }
    if(sample.Contains("GGJets_M-500To1000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 1.97343491858191583e-01;
      else average = 2.094533e-01;
    }
    if(sample.Contains("GGJets_M-1000To2000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 1.65930493374440380e-01;
      else average = 1.749053e-01;
    }
    if(sample.Contains("GGJets_M-2000To4000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 1.53686513958987775e-01;
      else average = 1.638999e-01;
    }
    if(sample.Contains("GGJets_M-4000To6000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 1.54441035528284226e-01;
      else average = 1.673106e-01;
    }
    if(sample.Contains("GGJets_M-6000To8000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 1.68124672498689981e-01;
      else average = 1.816810e-01;
    }
    if(sample.Contains("GGJets_M-8000To13000_Pt-50_13TeV-sherpa")) {
      if(is2017or2018(sample)) average = 1.90791526332210665e-01;
      else average = 1.972643e-01;
    }
    if(sample.Contains("DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa")) average = 4.730018e-01;
    // legacy samples
    if(sample.Contains("DiPhotonJetsBox_MGG-80toInf_13TeV-sherpa")) average = 0.432438293267;
    if(sample.Contains("GGJets_Pt-15_13TeV-sherpa")) average = 461187./991295.;

    // Madgraph5_aMC@NLO samples at NLO have a non-zero average weight
    // that should be removed, as well as negative weights
    if(sample.Contains("DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8")) average = 2.80907981496934667e+02*5.50762575783666608e-01;
    if(sample.Contains("WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) average = 1.501086e+03*6.283186e-01;
    if(sample.Contains("WGToLNuG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8")) average = 3.56378496224989874e+02*6.00800000000000001e-01;
    if(sample.Contains("ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) average = 3.479100e+02*7.019238e-01;
    if(sample.Contains("ZGToLLG_01J_5f_TuneCP5_13TeV-amcatnloFXFX-pythia8")) average = 1.08567085412723003e+02*6.32200000000000095e-01;
    if(sample.Contains("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) average = 2.344342e+04*6.286050e-01;
    if(sample.Contains("WToLNu_0J_13TeV-amcatnloFXFX-pythia8")) average = 7.143788e+04*8.534599e-01;
    if(sample.Contains("WToLNu_1J_13TeV-amcatnloFXFX-pythia8")) average = 9.293282e+04*5.323924e-01;
    if(sample.Contains("WToLNu_2J_13TeV-amcatnloFXFX-pythia8")) average = 7.667901e+04*3.120579e-01;
    if(sample.Contains("TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8")) average = 2.115439e+01*3.198633e-01;

    // 2017 samples
    if(sample.Contains("TTGJets_TuneCP5_13TeV-amcatnloFXFX-madspin-pythia8")) average = (3.29523e+07/4.62334e+06)*3.88374434527382240e-01;
    if(sample.Contains("DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8")) average = (4.89145e+11/2.74131e+07)*6.77654580082289737e-01;

    // from running GenXsecAnalyzer on full sample
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 77795.8/98040;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-1_M-2000To3000_13TeV-sherpa")) average = 11252.6/95346;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 255994./99080;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) average = 35458.9/96447;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-4_M-2000To3000_13TeV-sherpa")) average = 14915.4/97712;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) average = 164945./100000;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 70920./95112;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-2000To3000_13TeV-sherpa")) average = 39084.2/100000;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-200To500_13TeV-sherpa")) average = 1.39693e+06/100000;
    if(sample.Contains("ADDGravToGG_MS-3000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 176282./100000;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 46276.4/99769;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-1_M-2000To3500_13TeV-sherpa")) average = 8738.87/98374;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 211467./99714;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) average = 21258.5/99490;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-4_M-2000To3500_13TeV-sherpa")) average = 6337.18/99352;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-2_KK-4_M-500To1000_13TeV-sherpa")) average = 165282./99665;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 33728.1/99638;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-2000To3500_13TeV-sherpa")) average = 16369.8/99595;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-200To500_13TeV-sherpa")) average = 1.40807e+06/99544;
    if(sample.Contains("ADDGravToGG_MS-3500_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 169794./99999;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 31259.4/100000;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 5803.46/99999;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 197862./100000;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) average = 14467.5/99999;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-4_M-2000To4000_13TeV-sherpa")) average = 2726.55/99008;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) average = 173853./94919;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 21977.6/99337;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 7118.14/99683;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-200To500_13TeV-sherpa")) average = 1.42956e+06/100000;
    if(sample.Contains("ADDGravToGG_MS-4000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 184721./100000;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 24014.6/97750;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-2000To3000_13TeV-sherpa")) average = 4113.85/95680;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-3000To4500_13TeV-sherpa")) average = 679.93/99274;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 192283./100000;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) average = 12852.7/98902;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-2000To3000_13TeV-sherpa")) average = 1355.27/99872;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-3000To4500_13TeV-sherpa")) average = 525.859/97620;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-2_KK-4_M-500To1000_13TeV-sherpa")) average = 171581./96108;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 17844.1/100000;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-2000To3000_13TeV-sherpa")) average = 3016.36/99488;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-200To500_13TeV-sherpa")) average = 1.46046e+06/100000;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-3000To4500_13TeV-sherpa")) average = 1410.83/99250;
    if(sample.Contains("ADDGravToGG_MS-4500_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 169324./94432;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 20676.8/99893;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-2000To3000_13TeV-sherpa")) average = 2789.94/99997;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-3000To5000_13TeV-sherpa")) average = 549.056/95643;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 191065./99999;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) average = 12631.3/99999;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-2000To3000_13TeV-sherpa")) average = 911.252/93574;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-3000To5000_13TeV-sherpa")) average = 275.282/98081;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) average = 188312./100000;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 17038.3/99999;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-2000To3000_13TeV-sherpa")) average = 1671.08/99566;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-3000To5000_13TeV-sherpa")) average = 748.184/97972;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-200To500_13TeV-sherpa")) average = 1.45482e+06/98914;
    if(sample.Contains("ADDGravToGG_MS-5000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 184316./97668;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 19539.3/99999;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 1824.98/97064;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-4000To5500_13TeV-sherpa")) average = 58.0748/99999;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 185781./99998;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) average = 12739.9/100000;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-2000To4000_13TeV-sherpa")) average = 731.727/98545;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-4000To5500_13TeV-sherpa")) average = 61.8908/97678;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-2_KK-4_M-500To1000_13TeV-sherpa")) average = 190496./100000;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 17083.2/97598;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 1194.2/99899;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-4000To5500_13TeV-sherpa")) average = 179.182/99920;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-200To500_13TeV-sherpa")) average = 1.47938e+06/100000;
    if(sample.Contains("ADDGravToGG_MS-5500_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 190734./99998;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 17914.8/99472;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 1464.92/99744;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-4000To6000_13TeV-sherpa")) average = 57.5828/99406;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 182633./97928;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-1000To2000_13TeV-sherpa")) average = 12763.1/99998;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-2000To4000_13TeV-sherpa")) average = 533.16/99998;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-4000To6000_13TeV-sherpa")) average = 37.7734/99684;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-2_KK-4_M-500To1000_13TeV-sherpa")) average = 190089./100000;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 17099.2/100000;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 907.075/97600;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-4000To6000_13TeV-sherpa")) average = 112.4/98973;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-200To500_13TeV-sherpa")) average = 1.49119e+06/100000;
    if(sample.Contains("ADDGravToGG_MS-6000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 188536./99098;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 186206.00000/95030;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 17534.80000/99590;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 788.14500/99999;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-4_KK-1_M-4000To7000_13TeV-sherpa")) average = 41.49720/97123;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 190286.00000/96879;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 18078.30000/99235;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 1036.35000/100000;
    if(sample.Contains("ADDGravToGG_MS-7000_NED-2_KK-1_M-4000To7000_13TeV-sherpa")) average = 41.58770/99999;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 197780.00000/99999;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 17510.20000/99630;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 621.37600/99999;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-4_KK-1_M-4000To8000_13TeV-sherpa")) average = 18.71860/98940;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 189821.00000/95864;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 18171.00000/100000;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 924.38200/99781;
    if(sample.Contains("ADDGravToGG_MS-8000_NED-2_KK-1_M-4000To8000_13TeV-sherpa")) average = 26.51870/99754;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 198399.00000/99613;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 18471.50000/99999;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 586.68300/97444;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-4_KK-1_M-4000To9000_13TeV-sherpa")) average = 9.72142/97811;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 199297.00000/100000;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 18267.20000/99716;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 840.59400/100000;
    if(sample.Contains("ADDGravToGG_MS-9000_NED-2_KK-1_M-4000To9000_13TeV-sherpa")) average = 16.13620/95133;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 200235.00000/100000;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 18112.40000/99999;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 617.51600/99999;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-4_KK-1_M-4000To10000_13TeV-sherpa")) average = 7.96023/98502;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 199482.00000/99586;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 18362.60000/100000;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 664.88000/99998;
    if(sample.Contains("ADDGravToGG_MS-10000_NED-2_KK-1_M-4000To10000_13TeV-sherpa")) average = 11.18940/96530;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-500To1000_13TeV-sherpa")) average = 199632.00000/99238;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-1000To2000_13TeV-sherpa")) average = 18168.70000/99180;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-2000To4000_13TeV-sherpa")) average = 599.68900/99999;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-4_KK-1_M-4000To11000_13TeV-sherpa")) average = 6.07773/99719;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-500To1000_13TeV-sherpa")) average = 200196.00000/99494;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-1000To2000_13TeV-sherpa")) average = 18762.90000/100000;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-2000To4000_13TeV-sherpa")) average = 617.52800/97490;
    if(sample.Contains("ADDGravToGG_MS-11000_NED-2_KK-1_M-4000To11000_13TeV-sherpa")) average = 8.78796/96895;
    // from running GenXsecAnalyzer on full sample
    if(sample.Contains("GG_M-200To500_Pt-70_13TeV-sherpa")) average = 1.26654e+06/100000;
    if(sample.Contains("GG_M-500To1000_Pt-70_13TeV-sherpa")) average = 149032./100000;
    if(sample.Contains("GG_M-1000To2000_Pt-70_13TeV-sherpa")) average = 13459.8/99999;
    if(sample.Contains("GG_M-2000To4000_Pt-70_13TeV-sherpa")) average = 476.126/99999;
    if(sample.Contains("GG_M-4000To8000_Pt-70_13TeV-sherpa")) average = 3.85555/97816;
    if(sample.Contains("GG_M-8000To13000_Pt-70_13TeV-sherpa")) average = 0.00022662/99274;

    return average;
  }
}
#endif
