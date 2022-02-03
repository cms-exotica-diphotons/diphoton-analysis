#ifndef UTILITIES_HH
#define UTILITIES_HH

#include "TMath.h"
#include "TMatrixDSym.h"
#include "TMatrixT.h"
#include "TVectorT.h"
#include "TFitResult.h"
#include "TString.h"
#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include <string>

TF1* eff_scale_factor(const int year, const int etaBinNumber)
{
  const char *cmssw_base = getenv("CMSSW_BASE");
  if(cmssw_base==nullptr) {
    std::cout << "Please issue cmsenv before running" << std::endl;
    exit(-1);
  }

  TFile *f = new TFile(Form("%s/src/diphoton-analysis/Tools/data/eff_scale_factor.root", cmssw_base));
  TF1 *scale_factor;
  f->GetObject(Form("fit_%i_%i", year, etaBinNumber), scale_factor);
  f->Print("v");
  f->Close();

  return scale_factor;
}

TString scale_factor_cut(const int year, double sigma_from_mean)
{

  std::vector<TF1*> functions;
  std::map<int, TString> etaCuts;
  etaCuts[0] = "(abs(Photon1.scEta)<0.8)";
  etaCuts[1] = "(abs(Photon1.scEta)>0.8&&abs(Photon1.scEta)<1.4442)";
  etaCuts[2] = "(abs(Photon1.scEta)>1.566&&abs(Photon1.scEta)<2.5)";

  TString cutString1;
  for(int etaBin : {0, 1, 2}) {
    functions.push_back(eff_scale_factor(year, etaBin));
    double intercept = functions.back()->GetParameter(0);
    double slope = functions.back()->GetParameter(1);
    double slopeError = sigma_from_mean * functions.back()->GetParError(1);
    cutString1 += Form("(%6.6e + (%6.6e + %6.6e *(1+(Photon1.pT>300)) )* (Photon1.pT-200.))*(%s)", intercept, slope, slopeError, etaCuts[etaBin].Data());
    std::cout << etaCuts[etaBin].Data() << std::endl;
    if (etaBin != 2) {
      cutString1 += "+";
    }
  }

  TString cutString2(cutString1);
  cutString2.ReplaceAll("Photon1", "Photon2");
  TString fullCut = "(" + cutString1 + ")*(" + cutString2 + ")";

  return fullCut;
}

struct npv_reweight {
  TString up1sigma;
  TString nominal;
  TString down1sigma;
};

TString npv_reweight_str(int year, int numSigma)
{

  npv_reweight npv_reweight_2016;
  npv_reweight npv_reweight_2017;
  npv_reweight npv_reweight_2018;

  npv_reweight_2016.up1sigma = "((npv_true == 1)* 8.927e-02+ (npv_true == 2)* 3.422e-01+ (npv_true == 3)* 6.687e-01+ (npv_true == 4)* 7.690e-01+ (npv_true == 5)* 9.180e-01+ (npv_true == 6)* 9.464e-01+ (npv_true == 7)* 7.411e-01+ (npv_true == 8)* 8.445e-01+ (npv_true == 9)* 7.987e-01+ (npv_true == 10)* 6.612e-01+ (npv_true == 11)* 6.135e-01+ (npv_true == 12)* 6.251e-01+ (npv_true == 13)* 6.823e-01+ (npv_true == 14)* 7.386e-01+ (npv_true == 15)* 7.837e-01+ (npv_true == 16)* 8.393e-01+ (npv_true == 17)* 9.019e-01+ (npv_true == 18)* 9.421e-01+ (npv_true == 19)* 9.571e-01+ (npv_true == 20)* 9.626e-01+ (npv_true == 21)* 9.663e-01+ (npv_true == 22)* 9.851e-01+ (npv_true == 23)* 1.014e+00+ (npv_true == 24)* 1.052e+00+ (npv_true == 25)* 1.100e+00+ (npv_true == 26)* 1.155e+00+ (npv_true == 27)* 1.207e+00+ (npv_true == 28)* 1.264e+00+ (npv_true == 29)* 1.323e+00+ (npv_true == 30)* 1.358e+00+ (npv_true == 31)* 1.403e+00+ (npv_true == 32)* 1.421e+00+ (npv_true == 33)* 1.427e+00+ (npv_true == 34)* 1.408e+00+ (npv_true == 35)* 1.362e+00+ (npv_true == 36)* 1.280e+00+ (npv_true == 37)* 1.176e+00+ (npv_true == 38)* 1.051e+00+ (npv_true == 39)* 9.210e-01+ (npv_true == 40)* 7.719e-01+ (npv_true == 41)* 6.302e-01+ (npv_true == 42)* 5.065e-01+ (npv_true == 43)* 3.961e-01+ (npv_true == 44)* 3.095e-01+ (npv_true == 45)* 2.358e-01+ (npv_true == 46)* 1.728e-01+ (npv_true == 47)* 1.288e-01+ (npv_true == 48)* 9.414e-02+ (npv_true == 49)* 6.905e-02+ (npv_true == 50)* 4.982e-02+ (npv_true == 51)* 3.645e-02+ (npv_true == 52)* 2.663e-02+ (npv_true == 53)* 1.921e-02+ (npv_true == 54)* 1.502e-02+ (npv_true == 55)* 1.200e-02+ (npv_true == 56)* 9.225e-03+ (npv_true == 57)* 7.401e-03+ (npv_true == 58)* 6.182e-03+ (npv_true == 59)* 5.053e-03+ (npv_true == 60)* 4.943e-03+ (npv_true == 61)* 4.105e-03+ (npv_true == 62)* 3.179e-03+ (npv_true == 63)* 2.313e-03+ (npv_true == 64)* 1.769e-03+ (npv_true == 65)* 1.198e-03+ (npv_true == 66)* 7.834e-04+ (npv_true == 67)* 5.032e-04+ (npv_true == 68)* 3.354e-04+ (npv_true == 69)* 2.179e-04+ (npv_true == 70)* 1.405e-04+ (npv_true == 71)* 8.989e-05+ (npv_true == 72)* 5.719e-05+ (npv_true == 73)* 3.643e-05+ (npv_true == 74)* 2.276e-05+ (npv_true == 75)* 0.000e+00+ (npv_true == 76)* 0.000e+00+ (npv_true == 77)* 0.000e+00+ (npv_true == 78)* 0.000e+00+ (npv_true == 79)* 0.000e+00+ (npv_true == 80)* 0.000e+00+ (npv_true == 81)* 0.000e+00+ (npv_true == 82)* 0.000e+00+ (npv_true == 83)* 0.000e+00+ (npv_true == 84)* 0.000e+00+ (npv_true == 85)* 0.000e+00+ (npv_true == 86)* 0.000e+00+ (npv_true == 87)* 0.000e+00+ (npv_true == 88)* 0.000e+00+ (npv_true == 89)* 0.000e+00+ (npv_true == 90)* 0.000e+00+ (npv_true == 91)* 0.000e+00+ (npv_true == 92)* 0.000e+00+ (npv_true == 93)* 0.000e+00+ (npv_true == 94)* 0.000e+00+ (npv_true == 95)* 0.000e+00+ (npv_true == 96)* 0.000e+00+ (npv_true == 97)* 0.000e+00+ (npv_true == 98)* 0.000e+00+ (npv_true == 99)* 0.000e+00+ (npv_true == 100)* 0.000e+00)";
  npv_reweight_2016.nominal = "((npv_true == 1)* 1.018e-01+ (npv_true == 2)* 4.001e-01+ (npv_true == 3)* 7.359e-01+ (npv_true == 4)* 8.663e-01+ (npv_true == 5)* 1.055e+00+ (npv_true == 6)* 1.212e+00+ (npv_true == 7)* 9.897e-01+ (npv_true == 8)* 1.090e+00+ (npv_true == 9)* 1.030e+00+ (npv_true == 10)* 8.741e-01+ (npv_true == 11)* 8.184e-01+ (npv_true == 12)* 8.232e-01+ (npv_true == 13)* 8.798e-01+ (npv_true == 14)* 9.319e-01+ (npv_true == 15)* 9.686e-01+ (npv_true == 16)* 1.009e+00+ (npv_true == 17)* 1.046e+00+ (npv_true == 18)* 1.057e+00+ (npv_true == 19)* 1.046e+00+ (npv_true == 20)* 1.031e+00+ (npv_true == 21)* 1.020e+00+ (npv_true == 22)* 1.029e+00+ (npv_true == 23)* 1.047e+00+ (npv_true == 24)* 1.068e+00+ (npv_true == 25)* 1.096e+00+ (npv_true == 26)* 1.128e+00+ (npv_true == 27)* 1.156e+00+ (npv_true == 28)* 1.187e+00+ (npv_true == 29)* 1.219e+00+ (npv_true == 30)* 1.227e+00+ (npv_true == 31)* 1.242e+00+ (npv_true == 32)* 1.230e+00+ (npv_true == 33)* 1.205e+00+ (npv_true == 34)* 1.155e+00+ (npv_true == 35)* 1.081e+00+ (npv_true == 36)* 9.784e-01+ (npv_true == 37)* 8.612e-01+ (npv_true == 38)* 7.331e-01+ (npv_true == 39)* 6.084e-01+ (npv_true == 40)* 4.797e-01+ (npv_true == 41)* 3.659e-01+ (npv_true == 42)* 2.729e-01+ (npv_true == 43)* 1.969e-01+ (npv_true == 44)* 1.411e-01+ (npv_true == 45)* 9.820e-02+ (npv_true == 46)* 6.550e-02+ (npv_true == 47)* 4.438e-02+ (npv_true == 48)* 2.947e-02+ (npv_true == 49)* 1.968e-02+ (npv_true == 50)* 1.298e-02+ (npv_true == 51)* 8.743e-03+ (npv_true == 52)* 5.943e-03+ (npv_true == 53)* 4.048e-03+ (npv_true == 54)* 3.047e-03+ (npv_true == 55)* 2.397e-03+ (npv_true == 56)* 1.863e-03+ (npv_true == 57)* 1.551e-03+ (npv_true == 58)* 1.374e-03+ (npv_true == 59)* 1.205e-03+ (npv_true == 60)* 1.268e-03+ (npv_true == 61)* 1.121e-03+ (npv_true == 62)* 9.081e-04+ (npv_true == 63)* 6.779e-04+ (npv_true == 64)* 5.220e-04+ (npv_true == 65)* 3.503e-04+ (npv_true == 66)* 2.242e-04+ (npv_true == 67)* 1.397e-04+ (npv_true == 68)* 8.973e-05+ (npv_true == 69)* 5.595e-05+ (npv_true == 70)* 3.451e-05+ (npv_true == 71)* 2.109e-05+ (npv_true == 72)* 1.280e-05+ (npv_true == 73)* 7.770e-06+ (npv_true == 74)* 4.623e-06+ (npv_true == 75)* 0.000e+00+ (npv_true == 76)* 0.000e+00+ (npv_true == 77)* 0.000e+00+ (npv_true == 78)* 0.000e+00+ (npv_true == 79)* 0.000e+00+ (npv_true == 80)* 0.000e+00+ (npv_true == 81)* 0.000e+00+ (npv_true == 82)* 0.000e+00+ (npv_true == 83)* 0.000e+00+ (npv_true == 84)* 0.000e+00+ (npv_true == 85)* 0.000e+00+ (npv_true == 86)* 0.000e+00+ (npv_true == 87)* 0.000e+00+ (npv_true == 88)* 0.000e+00+ (npv_true == 89)* 0.000e+00+ (npv_true == 90)* 0.000e+00+ (npv_true == 91)* 0.000e+00+ (npv_true == 92)* 0.000e+00+ (npv_true == 93)* 0.000e+00+ (npv_true == 94)* 0.000e+00+ (npv_true == 95)* 0.000e+00+ (npv_true == 96)* 0.000e+00+ (npv_true == 97)* 0.000e+00+ (npv_true == 98)* 0.000e+00+ (npv_true == 99)* 0.000e+00+ (npv_true == 100)* 0.000e+00)";
  npv_reweight_2016.down1sigma = "((npv_true == 1)* 1.164e-01+ (npv_true == 2)* 4.769e-01+ (npv_true == 3)* 8.042e-01+ (npv_true == 4)* 9.768e-01+ (npv_true == 5)* 1.233e+00+ (npv_true == 6)* 1.591e+00+ (npv_true == 7)* 1.307e+00+ (npv_true == 8)* 1.404e+00+ (npv_true == 9)* 1.337e+00+ (npv_true == 10)* 1.165e+00+ (npv_true == 11)* 1.086e+00+ (npv_true == 12)* 1.072e+00+ (npv_true == 13)* 1.120e+00+ (npv_true == 14)* 1.161e+00+ (npv_true == 15)* 1.176e+00+ (npv_true == 16)* 1.182e+00+ (npv_true == 17)* 1.182e+00+ (npv_true == 18)* 1.160e+00+ (npv_true == 19)* 1.122e+00+ (npv_true == 20)* 1.089e+00+ (npv_true == 21)* 1.066e+00+ (npv_true == 22)* 1.062e+00+ (npv_true == 23)* 1.063e+00+ (npv_true == 24)* 1.062e+00+ (npv_true == 25)* 1.067e+00+ (npv_true == 26)* 1.076e+00+ (npv_true == 27)* 1.082e+00+ (npv_true == 28)* 1.088e+00+ (npv_true == 29)* 1.095e+00+ (npv_true == 30)* 1.077e+00+ (npv_true == 31)* 1.064e+00+ (npv_true == 32)* 1.025e+00+ (npv_true == 33)* 9.726e-01+ (npv_true == 34)* 8.989e-01+ (npv_true == 35)* 8.064e-01+ (npv_true == 36)* 6.955e-01+ (npv_true == 37)* 5.795e-01+ (npv_true == 38)* 4.637e-01+ (npv_true == 39)* 3.590e-01+ (npv_true == 40)* 2.622e-01+ (npv_true == 41)* 1.840e-01+ (npv_true == 42)* 1.255e-01+ (npv_true == 43)* 8.235e-02+ (npv_true == 44)* 5.351e-02+ (npv_true == 45)* 3.369e-02+ (npv_true == 46)* 2.033e-02+ (npv_true == 47)* 1.249e-02+ (npv_true == 48)* 7.559e-03+ (npv_true == 49)* 4.639e-03+ (npv_true == 50)* 2.848e-03+ (npv_true == 51)* 1.816e-03+ (npv_true == 52)* 1.195e-03+ (npv_true == 53)* 8.097e-04+ (npv_true == 54)* 6.238e-04+ (npv_true == 55)* 5.162e-04+ (npv_true == 56)* 4.301e-04+ (npv_true == 57)* 3.865e-04+ (npv_true == 58)* 3.673e-04+ (npv_true == 59)* 3.402e-04+ (npv_true == 60)* 3.697e-04+ (npv_true == 61)* 3.306e-04+ (npv_true == 62)* 2.662e-04+ (npv_true == 63)* 1.946e-04+ (npv_true == 64)* 1.453e-04+ (npv_true == 65)* 9.384e-05+ (npv_true == 66)* 5.754e-05+ (npv_true == 67)* 3.423e-05+ (npv_true == 68)* 2.096e-05+ (npv_true == 69)* 1.244e-05+ (npv_true == 70)* 7.293e-06+ (npv_true == 71)* 4.235e-06+ (npv_true == 72)* 2.441e-06+ (npv_true == 73)* 1.406e-06+ (npv_true == 74)* 7.941e-07+ (npv_true == 75)* 0.000e+00+ (npv_true == 76)* 0.000e+00+ (npv_true == 77)* 0.000e+00+ (npv_true == 78)* 0.000e+00+ (npv_true == 79)* 0.000e+00+ (npv_true == 80)* 0.000e+00+ (npv_true == 81)* 0.000e+00+ (npv_true == 82)* 0.000e+00+ (npv_true == 83)* 0.000e+00+ (npv_true == 84)* 0.000e+00+ (npv_true == 85)* 0.000e+00+ (npv_true == 86)* 0.000e+00+ (npv_true == 87)* 0.000e+00+ (npv_true == 88)* 0.000e+00+ (npv_true == 89)* 0.000e+00+ (npv_true == 90)* 0.000e+00+ (npv_true == 91)* 0.000e+00+ (npv_true == 92)* 0.000e+00+ (npv_true == 93)* 0.000e+00+ (npv_true == 94)* 0.000e+00+ (npv_true == 95)* 0.000e+00+ (npv_true == 96)* 0.000e+00+ (npv_true == 97)* 0.000e+00+ (npv_true == 98)* 0.000e+00+ (npv_true == 99)* 0.000e+00+ (npv_true == 100)* 0.000e+00)";

  npv_reweight_2017.up1sigma = "((npv_true == 1)* 2.744e+00+ (npv_true == 2)* 6.635e+00+ (npv_true == 3)* 3.999e+00+ (npv_true == 4)* 4.977e+00+ (npv_true == 5)* 1.910e+00+ (npv_true == 6)* 1.517e+00+ (npv_true == 7)* 9.717e-01+ (npv_true == 8)* 5.497e-01+ (npv_true == 9)* 3.552e-01+ (npv_true == 10)* 2.645e-01+ (npv_true == 11)* 2.522e-01+ (npv_true == 12)* 3.271e-01+ (npv_true == 13)* 4.273e-01+ (npv_true == 14)* 5.097e-01+ (npv_true == 15)* 6.155e-01+ (npv_true == 16)* 7.470e-01+ (npv_true == 17)* 8.980e-01+ (npv_true == 18)* 1.055e+00+ (npv_true == 19)* 1.187e+00+ (npv_true == 20)* 1.274e+00+ (npv_true == 21)* 1.326e+00+ (npv_true == 22)* 1.347e+00+ (npv_true == 23)* 1.341e+00+ (npv_true == 24)* 1.316e+00+ (npv_true == 25)* 1.283e+00+ (npv_true == 26)* 1.250e+00+ (npv_true == 27)* 1.224e+00+ (npv_true == 28)* 1.202e+00+ (npv_true == 29)* 1.176e+00+ (npv_true == 30)* 1.144e+00+ (npv_true == 31)* 1.104e+00+ (npv_true == 32)* 1.058e+00+ (npv_true == 33)* 1.008e+00+ (npv_true == 34)* 9.553e-01+ (npv_true == 35)* 9.005e-01+ (npv_true == 36)* 8.445e-01+ (npv_true == 37)* 7.897e-01+ (npv_true == 38)* 7.389e-01+ (npv_true == 39)* 6.944e-01+ (npv_true == 40)* 6.576e-01+ (npv_true == 41)* 6.294e-01+ (npv_true == 42)* 6.113e-01+ (npv_true == 43)* 6.063e-01+ (npv_true == 44)* 6.184e-01+ (npv_true == 45)* 6.524e-01+ (npv_true == 46)* 7.128e-01+ (npv_true == 47)* 8.030e-01+ (npv_true == 48)* 9.244e-01+ (npv_true == 49)* 1.074e+00+ (npv_true == 50)* 1.244e+00+ (npv_true == 51)* 1.422e+00+ (npv_true == 52)* 1.591e+00+ (npv_true == 53)* 1.732e+00+ (npv_true == 54)* 1.829e+00+ (npv_true == 55)* 1.872e+00+ (npv_true == 56)* 1.856e+00+ (npv_true == 57)* 1.787e+00+ (npv_true == 58)* 1.674e+00+ (npv_true == 59)* 1.532e+00+ (npv_true == 60)* 1.375e+00+ (npv_true == 61)* 1.214e+00+ (npv_true == 62)* 1.059e+00+ (npv_true == 63)* 9.151e-01+ (npv_true == 64)* 7.866e-01+ (npv_true == 65)* 6.741e-01+ (npv_true == 66)* 5.775e-01+ (npv_true == 67)* 4.960e-01+ (npv_true == 68)* 4.281e-01+ (npv_true == 69)* 3.726e-01+ (npv_true == 70)* 3.278e-01+ (npv_true == 71)* 2.923e-01+ (npv_true == 72)* 2.648e-01+ (npv_true == 73)* 2.439e-01+ (npv_true == 74)* 2.285e-01+ (npv_true == 75)* 2.176e-01+ (npv_true == 76)* 2.103e-01+ (npv_true == 77)* 2.059e-01+ (npv_true == 78)* 2.036e-01+ (npv_true == 79)* 2.029e-01+ (npv_true == 80)* 2.030e-01+ (npv_true == 81)* 2.034e-01+ (npv_true == 82)* 2.033e-01+ (npv_true == 83)* 2.019e-01+ (npv_true == 84)* 1.983e-01+ (npv_true == 85)* 1.914e-01+ (npv_true == 86)* 1.803e-01+ (npv_true == 87)* 1.647e-01+ (npv_true == 88)* 1.447e-01+ (npv_true == 89)* 1.218e-01+ (npv_true == 90)* 9.975e-02+ (npv_true == 91)* 7.870e-02+ (npv_true == 92)* 6.004e-02+ (npv_true == 93)* 4.452e-02+ (npv_true == 94)* 3.226e-02+ (npv_true == 95)* 2.296e-02+ (npv_true == 96)* 1.612e-02+ (npv_true == 97)* 1.120e-02+ (npv_true == 98)* 7.727e-03+ (npv_true == 99)* 5.306e-03+ (npv_true == 100)* 0.000e+00)";
  npv_reweight_2017.nominal = "((npv_true == 1)* 2.781e+00+ (npv_true == 2)* 7.958e+00+ (npv_true == 3)* 5.567e+00+ (npv_true == 4)* 4.861e+00+ (npv_true == 5)* 2.264e+00+ (npv_true == 6)* 1.723e+00+ (npv_true == 7)* 1.034e+00+ (npv_true == 8)* 6.072e-01+ (npv_true == 9)* 4.025e-01+ (npv_true == 10)* 3.281e-01+ (npv_true == 11)* 3.638e-01+ (npv_true == 12)* 4.961e-01+ (npv_true == 13)* 6.062e-01+ (npv_true == 14)* 7.229e-01+ (npv_true == 15)* 8.742e-01+ (npv_true == 16)* 1.050e+00+ (npv_true == 17)* 1.237e+00+ (npv_true == 18)* 1.398e+00+ (npv_true == 19)* 1.499e+00+ (npv_true == 20)* 1.551e+00+ (npv_true == 21)* 1.565e+00+ (npv_true == 22)* 1.545e+00+ (npv_true == 23)* 1.502e+00+ (npv_true == 24)* 1.452e+00+ (npv_true == 25)* 1.405e+00+ (npv_true == 26)* 1.366e+00+ (npv_true == 27)* 1.330e+00+ (npv_true == 28)* 1.289e+00+ (npv_true == 29)* 1.240e+00+ (npv_true == 30)* 1.182e+00+ (npv_true == 31)* 1.117e+00+ (npv_true == 32)* 1.049e+00+ (npv_true == 33)* 9.780e-01+ (npv_true == 34)* 9.060e-01+ (npv_true == 35)* 8.347e-01+ (npv_true == 36)* 7.675e-01+ (npv_true == 37)* 7.075e-01+ (npv_true == 38)* 6.564e-01+ (npv_true == 39)* 6.150e-01+ (npv_true == 40)* 5.843e-01+ (npv_true == 41)* 5.668e-01+ (npv_true == 42)* 5.658e-01+ (npv_true == 43)* 5.850e-01+ (npv_true == 44)* 6.277e-01+ (npv_true == 45)* 6.954e-01+ (npv_true == 46)* 7.869e-01+ (npv_true == 47)* 8.969e-01+ (npv_true == 48)* 1.015e+00+ (npv_true == 49)* 1.129e+00+ (npv_true == 50)* 1.221e+00+ (npv_true == 51)* 1.279e+00+ (npv_true == 52)* 1.293e+00+ (npv_true == 53)* 1.261e+00+ (npv_true == 54)* 1.189e+00+ (npv_true == 55)* 1.086e+00+ (npv_true == 56)* 9.654e-01+ (npv_true == 57)* 8.381e-01+ (npv_true == 58)* 7.141e-01+ (npv_true == 59)* 5.998e-01+ (npv_true == 60)* 4.987e-01+ (npv_true == 61)* 4.119e-01+ (npv_true == 62)* 3.389e-01+ (npv_true == 63)* 2.786e-01+ (npv_true == 64)* 2.294e-01+ (npv_true == 65)* 1.898e-01+ (npv_true == 66)* 1.582e-01+ (npv_true == 67)* 1.332e-01+ (npv_true == 68)* 1.137e-01+ (npv_true == 69)* 9.866e-02+ (npv_true == 70)* 8.709e-02+ (npv_true == 71)* 7.827e-02+ (npv_true == 72)* 7.159e-02+ (npv_true == 73)* 6.654e-02+ (npv_true == 74)* 6.274e-02+ (npv_true == 75)* 5.985e-02+ (npv_true == 76)* 5.763e-02+ (npv_true == 77)* 5.589e-02+ (npv_true == 78)* 5.444e-02+ (npv_true == 79)* 5.316e-02+ (npv_true == 80)* 5.189e-02+ (npv_true == 81)* 5.052e-02+ (npv_true == 82)* 4.889e-02+ (npv_true == 83)* 4.687e-02+ (npv_true == 84)* 4.430e-02+ (npv_true == 85)* 4.105e-02+ (npv_true == 86)* 3.704e-02+ (npv_true == 87)* 3.232e-02+ (npv_true == 88)* 2.708e-02+ (npv_true == 89)* 2.168e-02+ (npv_true == 90)* 1.686e-02+ (npv_true == 91)* 1.260e-02+ (npv_true == 92)* 9.095e-03+ (npv_true == 93)* 6.369e-03+ (npv_true == 94)* 4.351e-03+ (npv_true == 95)* 2.914e-03+ (npv_true == 96)* 1.923e-03+ (npv_true == 97)* 1.254e-03+ (npv_true == 98)* 8.111e-04+ (npv_true == 99)* 5.214e-04+ (npv_true == 100)* 0.000e+00)";
  npv_reweight_2017.down1sigma = "((npv_true == 1)* 2.830e+00+ (npv_true == 2)* 9.019e+00+ (npv_true == 3)* 7.933e+00+ (npv_true == 4)* 4.557e+00+ (npv_true == 5)* 2.651e+00+ (npv_true == 6)* 1.934e+00+ (npv_true == 7)* 1.101e+00+ (npv_true == 8)* 6.754e-01+ (npv_true == 9)* 4.721e-01+ (npv_true == 10)* 4.298e-01+ (npv_true == 11)* 5.542e-01+ (npv_true == 12)* 7.226e-01+ (npv_true == 13)* 8.558e-01+ (npv_true == 14)* 1.028e+00+ (npv_true == 15)* 1.234e+00+ (npv_true == 16)* 1.458e+00+ (npv_true == 17)* 1.657e+00+ (npv_true == 18)* 1.781e+00+ (npv_true == 19)* 1.834e+00+ (npv_true == 20)* 1.837e+00+ (npv_true == 21)* 1.798e+00+ (npv_true == 22)* 1.731e+00+ (npv_true == 23)* 1.657e+00+ (npv_true == 24)* 1.589e+00+ (npv_true == 25)* 1.533e+00+ (npv_true == 26)* 1.481e+00+ (npv_true == 27)* 1.421e+00+ (npv_true == 28)* 1.352e+00+ (npv_true == 29)* 1.273e+00+ (npv_true == 30)* 1.187e+00+ (npv_true == 31)* 1.098e+00+ (npv_true == 32)* 1.007e+00+ (npv_true == 33)* 9.170e-01+ (npv_true == 34)* 8.303e-01+ (npv_true == 35)* 7.516e-01+ (npv_true == 36)* 6.835e-01+ (npv_true == 37)* 6.268e-01+ (npv_true == 38)* 5.822e-01+ (npv_true == 39)* 5.515e-01+ (npv_true == 40)* 5.375e-01+ (npv_true == 41)* 5.434e-01+ (npv_true == 42)* 5.715e-01+ (npv_true == 43)* 6.223e-01+ (npv_true == 44)* 6.929e-01+ (npv_true == 45)* 7.765e-01+ (npv_true == 46)* 8.617e-01+ (npv_true == 47)* 9.347e-01+ (npv_true == 48)* 9.816e-01+ (npv_true == 49)* 9.921e-01+ (npv_true == 50)* 9.630e-01+ (npv_true == 51)* 8.978e-01+ (npv_true == 52)* 8.059e-01+ (npv_true == 53)* 6.992e-01+ (npv_true == 54)* 5.893e-01+ (npv_true == 55)* 4.852e-01+ (npv_true == 56)* 3.923e-01+ (npv_true == 57)* 3.132e-01+ (npv_true == 58)* 2.480e-01+ (npv_true == 59)* 1.954e-01+ (npv_true == 60)* 1.538e-01+ (npv_true == 61)* 1.212e-01+ (npv_true == 62)* 9.597e-02+ (npv_true == 63)* 7.655e-02+ (npv_true == 64)* 6.171e-02+ (npv_true == 65)* 5.043e-02+ (npv_true == 66)* 4.189e-02+ (npv_true == 67)* 3.541e-02+ (npv_true == 68)* 3.048e-02+ (npv_true == 69)* 2.672e-02+ (npv_true == 70)* 2.380e-02+ (npv_true == 71)* 2.151e-02+ (npv_true == 72)* 1.968e-02+ (npv_true == 73)* 1.819e-02+ (npv_true == 74)* 1.694e-02+ (npv_true == 75)* 1.587e-02+ (npv_true == 76)* 1.493e-02+ (npv_true == 77)* 1.408e-02+ (npv_true == 78)* 1.328e-02+ (npv_true == 79)* 1.252e-02+ (npv_true == 80)* 1.175e-02+ (npv_true == 81)* 1.097e-02+ (npv_true == 82)* 1.016e-02+ (npv_true == 83)* 9.288e-03+ (npv_true == 84)* 8.354e-03+ (npv_true == 85)* 7.350e-03+ (npv_true == 86)* 6.283e-03+ (npv_true == 87)* 5.182e-03+ (npv_true == 88)* 4.097e-03+ (npv_true == 89)* 3.089e-03+ (npv_true == 90)* 2.258e-03+ (npv_true == 91)* 1.584e-03+ (npv_true == 92)* 1.071e-03+ (npv_true == 93)* 7.018e-04+ (npv_true == 94)* 4.479e-04+ (npv_true == 95)* 2.799e-04+ (npv_true == 96)* 1.720e-04+ (npv_true == 97)* 1.044e-04+ (npv_true == 98)* 6.272e-05+ (npv_true == 99)* 3.742e-05+ (npv_true == 100)* 0.000e+00)";

  npv_reweight_2018.up1sigma = "((npv_true == 1)* 3.505e+00+ (npv_true == 2)* 1.203e+01+ (npv_true == 3)* 7.103e+00+ (npv_true == 4)* 6.040e+00+ (npv_true == 5)* 5.005e+00+ (npv_true == 6)* 3.855e+00+ (npv_true == 7)* 2.864e+00+ (npv_true == 8)* 2.169e+00+ (npv_true == 9)* 1.672e+00+ (npv_true == 10)* 1.322e+00+ (npv_true == 11)* 1.104e+00+ (npv_true == 12)* 9.825e-01+ (npv_true == 13)* 9.205e-01+ (npv_true == 14)* 8.945e-01+ (npv_true == 15)* 8.909e-01+ (npv_true == 16)* 9.033e-01+ (npv_true == 17)* 9.285e-01+ (npv_true == 18)* 9.634e-01+ (npv_true == 19)* 1.004e+00+ (npv_true == 20)* 1.045e+00+ (npv_true == 21)* 1.080e+00+ (npv_true == 22)* 1.105e+00+ (npv_true == 23)* 1.116e+00+ (npv_true == 24)* 1.112e+00+ (npv_true == 25)* 1.097e+00+ (npv_true == 26)* 1.074e+00+ (npv_true == 27)* 1.050e+00+ (npv_true == 28)* 1.027e+00+ (npv_true == 29)* 1.009e+00+ (npv_true == 30)* 9.972e-01+ (npv_true == 31)* 9.914e-01+ (npv_true == 32)* 9.914e-01+ (npv_true == 33)* 9.965e-01+ (npv_true == 34)* 1.006e+00+ (npv_true == 35)* 1.019e+00+ (npv_true == 36)* 1.035e+00+ (npv_true == 37)* 1.052e+00+ (npv_true == 38)* 1.070e+00+ (npv_true == 39)* 1.086e+00+ (npv_true == 40)* 1.099e+00+ (npv_true == 41)* 1.106e+00+ (npv_true == 42)* 1.106e+00+ (npv_true == 43)* 1.098e+00+ (npv_true == 44)* 1.079e+00+ (npv_true == 45)* 1.050e+00+ (npv_true == 46)* 1.011e+00+ (npv_true == 47)* 9.631e-01+ (npv_true == 48)* 9.081e-01+ (npv_true == 49)* 8.477e-01+ (npv_true == 50)* 7.841e-01+ (npv_true == 51)* 7.195e-01+ (npv_true == 52)* 6.558e-01+ (npv_true == 53)* 5.947e-01+ (npv_true == 54)* 5.374e-01+ (npv_true == 55)* 4.848e-01+ (npv_true == 56)* 4.371e-01+ (npv_true == 57)* 3.947e-01+ (npv_true == 58)* 3.571e-01+ (npv_true == 59)* 3.241e-01+ (npv_true == 60)* 2.952e-01+ (npv_true == 61)* 2.697e-01+ (npv_true == 62)* 2.471e-01+ (npv_true == 63)* 2.267e-01+ (npv_true == 64)* 2.081e-01+ (npv_true == 65)* 1.910e-01+ (npv_true == 66)* 1.750e-01+ (npv_true == 67)* 1.599e-01+ (npv_true == 68)* 1.457e-01+ (npv_true == 69)* 1.323e-01+ (npv_true == 70)* 1.198e-01+ (npv_true == 71)* 1.082e-01+ (npv_true == 72)* 9.734e-02+ (npv_true == 73)* 8.739e-02+ (npv_true == 74)* 7.827e-02+ (npv_true == 75)* 6.995e-02+ (npv_true == 76)* 6.236e-02+ (npv_true == 77)* 5.545e-02+ (npv_true == 78)* 4.915e-02+ (npv_true == 79)* 4.338e-02+ (npv_true == 80)* 3.808e-02+ (npv_true == 81)* 3.317e-02+ (npv_true == 82)* 2.860e-02+ (npv_true == 83)* 2.433e-02+ (npv_true == 84)* 2.032e-02+ (npv_true == 85)* 1.656e-02+ (npv_true == 86)* 1.309e-02+ (npv_true == 87)* 9.965e-03+ (npv_true == 88)* 7.249e-03+ (npv_true == 89)* 5.015e-03+ (npv_true == 90)* 3.353e-03+ (npv_true == 91)* 2.144e-03+ (npv_true == 92)* 1.316e-03+ (npv_true == 93)* 7.801e-04+ (npv_true == 94)* 4.485e-04+ (npv_true == 95)* 2.514e-04+ (npv_true == 96)* 1.380e-04+ (npv_true == 97)* 7.448e-05+ (npv_true == 98)* 3.962e-05+ (npv_true == 99)* 2.082e-05+ (npv_true == 100)* 0.000e+00)";
  npv_reweight_2018.nominal = "((npv_true == 1)* 3.771e+00+ (npv_true == 2)* 1.377e+01+ (npv_true == 3)* 8.318e+00+ (npv_true == 4)* 7.028e+00+ (npv_true == 5)* 5.801e+00+ (npv_true == 6)* 4.451e+00+ (npv_true == 7)* 3.347e+00+ (npv_true == 8)* 2.563e+00+ (npv_true == 9)* 1.986e+00+ (npv_true == 10)* 1.588e+00+ (npv_true == 11)* 1.351e+00+ (npv_true == 12)* 1.221e+00+ (npv_true == 13)* 1.154e+00+ (npv_true == 14)* 1.124e+00+ (npv_true == 15)* 1.119e+00+ (npv_true == 16)* 1.132e+00+ (npv_true == 17)* 1.160e+00+ (npv_true == 18)* 1.195e+00+ (npv_true == 19)* 1.233e+00+ (npv_true == 20)* 1.264e+00+ (npv_true == 21)* 1.283e+00+ (npv_true == 22)* 1.286e+00+ (npv_true == 23)* 1.271e+00+ (npv_true == 24)* 1.242e+00+ (npv_true == 25)* 1.207e+00+ (npv_true == 26)* 1.170e+00+ (npv_true == 27)* 1.137e+00+ (npv_true == 28)* 1.109e+00+ (npv_true == 29)* 1.089e+00+ (npv_true == 30)* 1.076e+00+ (npv_true == 31)* 1.068e+00+ (npv_true == 32)* 1.065e+00+ (npv_true == 33)* 1.066e+00+ (npv_true == 34)* 1.070e+00+ (npv_true == 35)* 1.074e+00+ (npv_true == 36)* 1.078e+00+ (npv_true == 37)* 1.081e+00+ (npv_true == 38)* 1.079e+00+ (npv_true == 39)* 1.070e+00+ (npv_true == 40)* 1.054e+00+ (npv_true == 41)* 1.028e+00+ (npv_true == 42)* 9.919e-01+ (npv_true == 43)* 9.456e-01+ (npv_true == 44)* 8.899e-01+ (npv_true == 45)* 8.267e-01+ (npv_true == 46)* 7.579e-01+ (npv_true == 47)* 6.862e-01+ (npv_true == 48)* 6.141e-01+ (npv_true == 49)* 5.438e-01+ (npv_true == 50)* 4.774e-01+ (npv_true == 51)* 4.163e-01+ (npv_true == 52)* 3.614e-01+ (npv_true == 53)* 3.129e-01+ (npv_true == 54)* 2.709e-01+ (npv_true == 55)* 2.350e-01+ (npv_true == 56)* 2.044e-01+ (npv_true == 57)* 1.785e-01+ (npv_true == 58)* 1.565e-01+ (npv_true == 59)* 1.377e-01+ (npv_true == 60)* 1.215e-01+ (npv_true == 61)* 1.074e-01+ (npv_true == 62)* 9.489e-02+ (npv_true == 63)* 8.370e-02+ (npv_true == 64)* 7.360e-02+ (npv_true == 65)* 6.446e-02+ (npv_true == 66)* 5.620e-02+ (npv_true == 67)* 4.875e-02+ (npv_true == 68)* 4.209e-02+ (npv_true == 69)* 3.618e-02+ (npv_true == 70)* 3.098e-02+ (npv_true == 71)* 2.645e-02+ (npv_true == 72)* 2.252e-02+ (npv_true == 73)* 1.914e-02+ (npv_true == 74)* 1.623e-02+ (npv_true == 75)* 1.374e-02+ (npv_true == 76)* 1.160e-02+ (npv_true == 77)* 9.763e-03+ (npv_true == 78)* 8.179e-03+ (npv_true == 79)* 6.812e-03+ (npv_true == 80)* 5.628e-03+ (npv_true == 81)* 4.603e-03+ (npv_true == 82)* 3.715e-03+ (npv_true == 83)* 2.948e-03+ (npv_true == 84)* 2.289e-03+ (npv_true == 85)* 1.730e-03+ (npv_true == 86)* 1.263e-03+ (npv_true == 87)* 8.851e-04+ (npv_true == 88)* 5.910e-04+ (npv_true == 89)* 3.742e-04+ (npv_true == 90)* 2.282e-04+ (npv_true == 91)* 1.328e-04+ (npv_true == 92)* 7.402e-05+ (npv_true == 93)* 3.971e-05+ (npv_true == 94)* 2.062e-05+ (npv_true == 95)* 1.042e-05+ (npv_true == 96)* 5.146e-06+ (npv_true == 97)* 2.493e-06+ (npv_true == 98)* 1.189e-06+ (npv_true == 99)* 5.604e-07+ (npv_true == 100)* 0.000e+00)";
  npv_reweight_2018.down1sigma = "((npv_true == 1)* 4.065e+00+ (npv_true == 2)* 1.582e+01+ (npv_true == 3)* 9.735e+00+ (npv_true == 4)* 8.166e+00+ (npv_true == 5)* 6.717e+00+ (npv_true == 6)* 5.150e+00+ (npv_true == 7)* 3.927e+00+ (npv_true == 8)* 3.034e+00+ (npv_true == 9)* 2.365e+00+ (npv_true == 10)* 1.923e+00+ (npv_true == 11)* 1.667e+00+ (npv_true == 12)* 1.526e+00+ (npv_true == 13)* 1.450e+00+ (npv_true == 14)* 1.413e+00+ (npv_true == 15)* 1.404e+00+ (npv_true == 16)* 1.416e+00+ (npv_true == 17)* 1.441e+00+ (npv_true == 18)* 1.471e+00+ (npv_true == 19)* 1.495e+00+ (npv_true == 20)* 1.505e+00+ (npv_true == 21)* 1.495e+00+ (npv_true == 22)* 1.464e+00+ (npv_true == 23)* 1.418e+00+ (npv_true == 24)* 1.365e+00+ (npv_true == 25)* 1.313e+00+ (npv_true == 26)* 1.266e+00+ (npv_true == 27)* 1.227e+00+ (npv_true == 28)* 1.197e+00+ (npv_true == 29)* 1.175e+00+ (npv_true == 30)* 1.158e+00+ (npv_true == 31)* 1.146e+00+ (npv_true == 32)* 1.137e+00+ (npv_true == 33)* 1.129e+00+ (npv_true == 34)* 1.121e+00+ (npv_true == 35)* 1.110e+00+ (npv_true == 36)* 1.095e+00+ (npv_true == 37)* 1.073e+00+ (npv_true == 38)* 1.042e+00+ (npv_true == 39)* 1.002e+00+ (npv_true == 40)* 9.513e-01+ (npv_true == 41)* 8.907e-01+ (npv_true == 42)* 8.216e-01+ (npv_true == 43)* 7.463e-01+ (npv_true == 44)* 6.673e-01+ (npv_true == 45)* 5.877e-01+ (npv_true == 46)* 5.101e-01+ (npv_true == 47)* 4.371e-01+ (npv_true == 48)* 3.704e-01+ (npv_true == 49)* 3.111e-01+ (npv_true == 50)* 2.597e-01+ (npv_true == 51)* 2.160e-01+ (npv_true == 52)* 1.795e-01+ (npv_true == 53)* 1.494e-01+ (npv_true == 54)* 1.247e-01+ (npv_true == 55)* 1.046e-01+ (npv_true == 56)* 8.804e-02+ (npv_true == 57)* 7.441e-02+ (npv_true == 58)* 6.306e-02+ (npv_true == 59)* 5.350e-02+ (npv_true == 60)* 4.535e-02+ (npv_true == 61)* 3.835e-02+ (npv_true == 62)* 3.230e-02+ (npv_true == 63)* 2.706e-02+ (npv_true == 64)* 2.254e-02+ (npv_true == 65)* 1.866e-02+ (npv_true == 66)* 1.536e-02+ (npv_true == 67)* 1.257e-02+ (npv_true == 68)* 1.024e-02+ (npv_true == 69)* 8.304e-03+ (npv_true == 70)* 6.715e-03+ (npv_true == 71)* 5.415e-03+ (npv_true == 72)* 4.357e-03+ (npv_true == 73)* 3.497e-03+ (npv_true == 74)* 2.799e-03+ (npv_true == 75)* 2.232e-03+ (npv_true == 76)* 1.771e-03+ (npv_true == 77)* 1.397e-03+ (npv_true == 78)* 1.094e-03+ (npv_true == 79)* 8.487e-04+ (npv_true == 80)* 6.507e-04+ (npv_true == 81)* 4.921e-04+ (npv_true == 82)* 3.659e-04+ (npv_true == 83)* 2.665e-04+ (npv_true == 84)* 1.893e-04+ (npv_true == 85)* 1.304e-04+ (npv_true == 86)* 8.657e-05+ (npv_true == 87)* 5.497e-05+ (npv_true == 88)* 3.316e-05+ (npv_true == 89)* 1.892e-05+ (npv_true == 90)* 1.038e-05+ (npv_true == 91)* 5.414e-06+ (npv_true == 92)* 2.700e-06+ (npv_true == 93)* 1.294e-06+ (npv_true == 94)* 5.994e-07+ (npv_true == 95)* 2.703e-07+ (npv_true == 96)* 1.197e-07+ (npv_true == 97)* 5.268e-08+ (npv_true == 98)* 2.363e-08+ (npv_true == 99)* 1.132e-08+ (npv_true == 100)* 0.000e+00)";

  std::map<int, npv_reweight> npv_reweights;
  npv_reweights[2016] = npv_reweight_2016;
  npv_reweights[2017] = npv_reweight_2017;
  npv_reweights[2018] = npv_reweight_2018;

  if(numSigma == 1) {
    return npv_reweights[year].up1sigma;
  }
  else if(numSigma == -1) {
    return npv_reweights[year].down1sigma;
  }
  else {
    return npv_reweights[year].nominal;
  }

}

TF1* kfactor(const std::string & region, const std::string & scales)
{
  std::map<std::string, std::string> fitFuncs;
  fitFuncs["BB"] = "pol3";
  fitFuncs["BE"] = "pol3";
  const char *cmssw_base = getenv("CMSSW_BASE");
  if(cmssw_base==nullptr) {
    std::cout << "Please issue cmsenv before running" << std::endl;
    exit(-1);
  }

  TFile *f = new TFile(Form("%s/src/diphoton-analysis/Tools/data/kfactor_%s_%s.root", cmssw_base, region.c_str(), scales.c_str()));
  TF1 *kfactorFunction;
  f->GetObject(fitFuncs[region].c_str(), kfactorFunction);
  f->Close();
  return kfactorFunction;
}

std::string kfactorString(const std::string & region, const std::string & scales, const std::string& reweightVariable = "qscale")
{
  TF1 *kfactorFunction = kfactor(region, scales);

  const std::string squared = reweightVariable + "*" + reweightVariable;
  const std::string cubed = squared + "*" + reweightVariable;

  TString kfactorWeight;
  if(region == "BB") kfactorWeight = Form("(%6.6e + %6.6e*%s + %6.6e*%s + %6.6e*%s)",
					  kfactorFunction->GetParameter(0), kfactorFunction->GetParameter(1), reweightVariable.c_str(),
					  kfactorFunction->GetParameter(2),  squared.c_str(), kfactorFunction->GetParameter(3), cubed.c_str());
  else kfactorWeight = Form("(%6.6e + %6.6e*%s + %6.6e*%s + %6.6e*%s)",
			    kfactorFunction->GetParameter(0), kfactorFunction->GetParameter(1), reweightVariable.c_str(),
			    kfactorFunction->GetParameter(2),  squared.c_str(), kfactorFunction->GetParameter(3), cubed.c_str());
  
  return kfactorWeight.Data();
}

TH1D* getHists(const std::string & base, const std::string & region, const std::string & type)
{
  unsigned int nfiles=10;
  if(type.find("NNLO") != std::string::npos) nfiles = 50;
  TH1D *sum = nullptr;
  for(unsigned int i=1; i<=nfiles; i++) {
    TString filename(Form("%s/%s_%s_R1F1_Mass0p23To2TeV_13TeV/Job%d/bin/ReRoot.root", base.c_str(), region.c_str(), type.c_str(), i));
    TFile *f = TFile::Open(filename);
    TH1D *tempHist = static_cast<TH1D*>(f->Get("hist1"));
    if(tempHist==nullptr) continue;
    if(sum == nullptr) {
      sum = static_cast<TH1D*>(tempHist->Clone());
      sum->SetDirectory(nullptr);
      sum->SetBit(TH1::kIsAverage);
    }
    else {
      tempHist->SetBit(TH1::kIsAverage);
      sum->Add(tempHist);
    }

    f->Close();
  }

  return sum;
}


TH1D* getHistsMCFM(const std::string & base, const std::string & type, const std::string & histName = "id1", const int binLow = 0, const int binHigh = 0 )
{
  unsigned int seedBase = 1189;
  unsigned int nfiles=10;
  if(type.find("nnlo") != std::string::npos) nfiles = 50;
  TH1D *sum = nullptr;
  for(unsigned int i=1; i<=nfiles; i++) {
    unsigned int seed = seedBase + i;
    // commented out 20NOV2018
    //    TString filename(Form("%s/%s_seed%d.root", base.c_str(), type.c_str(), seed));
    TString filename(Form("%s/%s_%d.root", base.c_str(), type.c_str(), seed));
    // later jobs have a different format
    if(binHigh!=0) {
      TString jobName(Form("%s_%d_%d_%d", type.c_str(), seed, binLow, binHigh));
      // MCFM truncates job names longer than 66 characters
      if(jobName.Length()>66) jobName.Resize(66);
      filename = Form("%s/%s.root", base.c_str(), jobName.Data());
    }
    else if(base.find("otherpdfs")!=std::string::npos) {
      TString jobName(Form("%s_%d", type.c_str(), seed));
      // MCFM truncates job names longer than 66 characters
      if(jobName.Length()>66) jobName.Resize(66);
      filename = Form("%s/%s.root", base.c_str(), jobName.Data());
    }
    TFile *f = TFile::Open(filename);
    if(!f) continue;
    if(!f->IsOpen()) continue;
    TString histID("id1");
    // need to change histogram ID if looking at barrel-endcap region
    if(base.find("_witheta")!=std::string::npos) histID = "id15";
    std::cout << histID << std::endl;
    TH1D *tempHist = static_cast<TH1D*>(f->Get(histID));
    if(tempHist==nullptr) continue;
    if(sum == nullptr) {
      sum = static_cast<TH1D*>(f->Get(histID));
      sum->SetBit(TH1::kIsAverage);
    }
    else {
      tempHist->SetBit(TH1::kIsAverage);
      sum->Add(tempHist);
    }
  }
  // scale to pb
  double fbtopb = 0.001;
  // scale by bin width
  double binWidth = (sum->GetXaxis()->GetXmax()-sum->GetXaxis()->GetXmin())/sum->GetNbinsX();
  std::cout << "binWidth: " << binWidth << std::endl;
  std::cout << "integral*binWidth: " << sum->Integral()*binWidth*fbtopb << std::endl;
  //  sum->Scale(binWidth*fbtopb);
  sum->Scale(1/binWidth);

  return sum;
}

TH1D* getHistsMCFMSumNNLO(const std::string & base, const std::string & type)
{
  TString histID("id1");
  // need to change histogram ID if looking at barrel-endcap region
  if(base.find("_witheta")!=std::string::npos) histID = "id15";

  TH1D *nnlo_500_750 = getHistsMCFM(base, type, histID.Data(), 500, 750);
  TH1D *nnlo_750_1000 = getHistsMCFM(base, type, histID.Data(), 750, 1000);
  TH1D *nnlo_1000_1500 = getHistsMCFM(base, type, histID.Data(), 1000, 1500);
  TH1D *nnlo_1500_4000 = getHistsMCFM(base, type, histID.Data(), 1500, 4000);

  nnlo_500_750->ResetBit(TH1::kIsAverage);
  nnlo_750_1000->ResetBit(TH1::kIsAverage);
  nnlo_1000_1500->ResetBit(TH1::kIsAverage);
  nnlo_1500_4000->ResetBit(TH1::kIsAverage);

  // TH1D *nnlo_sum = static_cast<TH1D*>(nnlo_500_750->Clone());
  // nnlo_sum->Add(nnlo_750_1000);
  // nnlo_sum->Add(nnlo_1000_1500);
  // nnlo_sum->Add(nnlo_1500_4000);

  TH1D *nnlo_sum = static_cast<TH1D*>(nnlo_500_750->Clone());
  for(int i=0; i<=nnlo_500_750->GetNbinsX(); i++) {

    double binContent_500_750 = nnlo_500_750->GetBinContent(i);
    double binContent_750_1000 = nnlo_750_1000->GetBinContent(i);
    double binContent_1000_1500 = nnlo_1000_1500->GetBinContent(i);
    double binContent_1500_4000 = nnlo_1500_4000->GetBinContent(i);

    double binContent = binContent_500_750 + binContent_750_1000 + binContent_1000_1500 + binContent_1500_4000;

    double binError_500_750 = nnlo_500_750->GetBinError(i);
    double binError_750_1000 = nnlo_750_1000->GetBinError(i);
    double binError_1000_1500 = nnlo_1000_1500->GetBinError(i);
    double binError_1500_4000 = nnlo_1500_4000->GetBinError(i);

    double binError = binError_500_750;
    if(binContent_750_1000 > binContent_500_750) binError = binError_750_1000;
    if(binContent_1000_1500 > binContent_750_1000) binError = binError_1000_1500;
    if(binContent_1500_4000 > binContent_1000_1500) binError = binError_1500_4000;

    nnlo_sum->SetBinContent(i, binContent);
    nnlo_sum->SetBinError(i, binError);
  }
  return nnlo_sum;
}


// get variation (up or down by 1 sigma) for parameter
// given the nominal function and the fitResult (from which the covariance
// matrix is obtained)

TF1 * eigenvectorVariation(bool up, int parameter, TF1* nominal, TFitResult* fitResult)
{
  TMatrixDSym cov = fitResult->GetCovarianceMatrix();
  TVectorT<double> eigenValues;
  TMatrixT<double> eigenVectors = cov.EigenVectors(eigenValues);
  double eigenvalue = sqrt(fabs(eigenValues[parameter]));

  TF1* func;
  if(up) {
    func = static_cast<TF1*>(nominal->Clone(Form("fUp_par%d", parameter)));
  }
  else {
    eigenvalue = -eigenvalue; // change sign for negative variations
    func = static_cast<TF1*>(nominal->Clone(Form("fDown_par%d", parameter)));
  }
  for(int i=0; i<nominal->GetNpar(); i++) {
    func->SetParameter(i, nominal->GetParameter(i) + eigenvalue*eigenVectors[i][parameter]);
  }

  return func;
}

// needed to convert from Hewett-minus convention to GRW
double k = 2/TMath::Pi();

void getSignalAndInterference(std::string pointNameBase, std::string region, TH1D*& background, TH1D *& signal, TH1D *&interference, bool update=false)
{
  TFile *f;
  // if(update) f = new TFile("data/Minv_histos_with_interference.root", "update");
  // else f = new TFile("data/Minv_histos_with_interference.root");
  f = new TFile("data/Minv_histos.root");

  // KK conventions for HLZ and Hewett- conventions are 1 and 4, respectively
  std::string pointNamePositiveInt = pointNameBase;
  pointNamePositiveInt += "_NED-4_KK-1";
  std::string pointNameNegativeInt = pointNameBase;
  pointNameNegativeInt += "_NED-2_KK-4";

  std::string backgroundHistname(region);
  backgroundHistname += "/gg70";
  background = static_cast<TH1D*>(f->Get(backgroundHistname.c_str()));
  TH1D *histPositiveInt = static_cast<TH1D*>(f->Get(pointNamePositiveInt.c_str()));
  TH1D *histNegativeInt = static_cast<TH1D*>(f->Get(pointNameNegativeInt.c_str()));

  histPositiveInt->SetMarkerColor(kRed);
  histPositiveInt->SetLineColor(kRed);
  histNegativeInt->SetMarkerColor(kBlue);

  background->Draw();
  histPositiveInt->Draw("same");
  histNegativeInt->Draw("same");

  TH1D *histPositiveInt_sub = static_cast<TH1D*>(histPositiveInt->Clone("histPositiveInt_sub"));
  histPositiveInt_sub->Add(background, -1.0);
  TH1D *histNegativeInt_sub = static_cast<TH1D*>(histNegativeInt->Clone("histNegativeInt_sub"));
  histNegativeInt_sub->Add(background, -1.0);

  histPositiveInt_sub->Draw();
  histPositiveInt_sub->GetXaxis()->SetRangeUser(500, 6000);
  histNegativeInt_sub->Draw("same");
  
  
  signal = static_cast<TH1D*>(histPositiveInt_sub->Clone(pointNameBase.c_str()));
  signal->SetName(pointNameBase.c_str());
  signal->SetTitle(pointNameBase.c_str());
  signal->Scale(k);
  signal->Add(histNegativeInt_sub);
  signal->Scale(1/(k+k*k));

  interference = static_cast<TH1D*>(histPositiveInt_sub->Clone());
  interference->SetName(Form("%s_int", pointNameBase.c_str()));
  interference->SetTitle(Form("%s_int", pointNameBase.c_str()));
  interference->Scale(k*k);
  interference->Add(histNegativeInt_sub, -1.0);
  interference->Scale(1/(k+k*k));
  interference->SetMarkerColor(kBlack);

}

#endif
