#include "diphoton-analysis/ClockworkAnalysis/scripts/clockwork_looper.C"

#include <iostream>

int main(int argc, char *argv[])
{
  std::string run;
  double kVal, lambdaT;
  int negInt;

  // FIXME
  if(argc != 5) {
    std::cout << "Syntax: clockwork.exe [2016/2017/2018] [500/1000/3000/5000] [NegInt0/NegInt1] [4000/6500/10000]" << std::endl;
    return -1;
  }
  else {
    run = argv[1];
    if(run.find("2016") != std::string::npos
       and run.find("2017") != std::string::npos
       and run.find("2018") != std::string::npos) {
      std::cout << "Only '2016', '2017', and '2018' are allowed years." << std::endl;
      return -1;
    }
    kVal = std::atof(argv[2]);
    negInt = std::atoi(argv[3]);
    if(negInt != 0 and negInt != 1){
      std::cout << "Only '0' or '1' are allowed NegIntValues." << std::endl;
      return -1;
    }

    lambdaT = std::atof(argv[4]);
  }
  // CallLooper
  clockwork_looper(run, kVal, lambdaT, negInt);

  return 0;
}
