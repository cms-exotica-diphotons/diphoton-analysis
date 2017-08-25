#ifndef CROSSSECTIONS_INC
#define CROSSSECTIONS_INC

namespace ExoDiPhotons {

  // provides cross sections (in pb) that are used to calculate event weights
  double crossSection(const TString& sample) {
    double xsec = -1.0;
    if(sample.Contains("DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8")) xsec = 135.1;
    if(sample.Contains("DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa")) xsec = 82.81; // +/- 0.12
    if(sample.Contains("GGJets_M-60To200_Pt-50_13TeV-sherpa")) xsec = 5.785e+00;
    if(sample.Contains("GGJets_M-200To500_Pt-50_13TeV-sherpa")) xsec = 2.244e+00;
    if(sample.Contains("GGJets_M-500To1000_Pt-50_13TeV-sherpa")) xsec = 1.510e-01;
    if(sample.Contains("GGJets_M-1000To2000_Pt-50_13TeV-sherpa")) xsec = 1.084e-02;
    if(sample.Contains("GGJets_M-2000To4000_Pt-50_13TeV-sherpa")) xsec = 3.690e-04;
    if(sample.Contains("GGJets_M-4000To6000_Pt-50_13TeV-sherpa")) xsec = 2.451e-06;
    if(sample.Contains("GGJets_M-6000To8000_Pt-50_13TeV-sherpa")) xsec = 1.753e-08;
    if(sample.Contains("GGJets_M-8000To13000_Pt-50_13TeV-sherpa")) xsec = 7.053e-11;
    // cross sections from Table 2 of AN2015_241
    if(sample.Contains("GJets_HT-40To100")) xsec = 2.121e+04;
    if(sample.Contains("GJets_HT-100To200")) xsec = 9.863e+03;
    if(sample.Contains("GJets_HT-200To400")) xsec = 2.298e+03;
    if(sample.Contains("GJets_HT-400To600")) xsec = 2.816e+02;
    if(sample.Contains("GJets_HT-600ToInf")) xsec = 9.465e+01;
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
    // cross sections from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns
    if(sample.Contains("WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) xsec = 405.271;
    if(sample.Contains("ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) xsec = 117.864;
    if(sample.Contains("TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8")) xsec = 3.697;
    if(sample.Contains("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) xsec = 1921.8*3;
    // MCM cross sections (NLO)
    if(sample.Contains("WToLNu_0J_13TeV-amcatnloFXFX-pythia8")) xsec = 5.844e+04; // +- 7.676e+01 pb
    if(sample.Contains("WToLNu_1J_13TeV-amcatnloFXFX-pythia8")) xsec = 1.128e+04; // +- 3.873e+02 pb
    if(sample.Contains("WToLNu_2J_13TeV-amcatnloFXFX-pythia8")) xsec = 2.544e+03; // +- 2.485e+02 pb
    // from https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    if(sample.Contains("TTJets_")) xsec = 815.96 ;
    // from running GenXsecAnalyzer on full sample
    if(sample.Contains("GGGJets_13TeV-sherpa")) xsec = 1.814e-01;
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

    //RSGrav sample for synching study
    if(sample.Contains("RSGravToGG_kMpl-001_M-5000")) xsec = 1.425e-07;
    
    // do not use weights for data
    if(sample.Contains("Run2015") || sample.Contains("Run2016")) xsec = 1.0;

    if(xsec < 0) throw cms::Exception("Could not determine cross section from output file name");
    
    std::cout << "Using cross section " << xsec << " for sample " << sample << std::endl;
    
    return xsec;
  }

  double averageWeight(const TString& sample) {
    double average = 1.0;
    
    // average weight is non-zero for these samples because 
    // of the njet weighting in Sherpa
    if(sample.Contains("GGJets_M-60To200_Pt-50_13TeV-sherpa")) average = 3.895719e-01;
    if(sample.Contains("GGJets_M-200To500_Pt-50_13TeV-sherpa")) average = 2.818643e-01;
    if(sample.Contains("GGJets_M-500To1000_Pt-50_13TeV-sherpa")) average = 2.094533e-01;
    if(sample.Contains("GGJets_M-1000To2000_Pt-50_13TeV-sherpa")) average = 1.749053e-01;
    if(sample.Contains("GGJets_M-2000To4000_Pt-50_13TeV-sherpa")) average = 1.638999e-01;
    if(sample.Contains("GGJets_M-4000To6000_Pt-50_13TeV-sherpa")) average = 1.673106e-01;
    if(sample.Contains("GGJets_M-6000To8000_Pt-50_13TeV-sherpa")) average = 1.816810e-01;
    if(sample.Contains("GGJets_M-8000To13000_Pt-50_13TeV-sherpa")) average = 1.972643e-01;
    if(sample.Contains("DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa")) average = 4.730018e-01;

    // Madgraph5_aMC@NLO samples at NLO have a non-zero average weight
    // that should be removed, as well as negative weights
    if(sample.Contains("DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8")) average = 2.80907981496934667e+02*5.50762575783666608e-01;
    if(sample.Contains("WGToLNuG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) average = 1.501086e+03*6.283186e-01;
    if(sample.Contains("ZGTo2LG_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) average = 3.479100e+02*7.019238e-01;
    if(sample.Contains("DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8")) average = 2.344342e+04*6.286050e-01;
    if(sample.Contains("WToLNu_0J_13TeV-amcatnloFXFX-pythia8")) average = 7.143788e+04*8.534599e-01;
    if(sample.Contains("WToLNu_1J_13TeV-amcatnloFXFX-pythia8")) average = 9.293282e+04*5.323924e-01;
    if(sample.Contains("WToLNu_2J_13TeV-amcatnloFXFX-pythia8")) average = 7.667901e+04*3.120579e-01;
    if(sample.Contains("TTGJets_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8")) average = 2.115439e+01*3.198633e-01;

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

    if(sample.Contains("RSGravToGG_kMpl-001_M-5000")) average=100000./100000.;
    
    return average;
  }
}
#endif
