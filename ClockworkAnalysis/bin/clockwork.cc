#include "diphoton-analysis/ClockworkAnalysis/scripts/clockwork_looper.C"

#include <iostream>

int main(int argc, char *argv[])
{
  std::string run;
  double lambdaT;
  int negInt;

  // FIXME
  if(argc != 4) {
    std::cout << "Syntax: clockwork.exe [2016/2017/2018] [0/1] [4000/6000/100000(SM)]" << std::endl;
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
    // kVal = std::atof(argv[2]);
    negInt = std::atoi(argv[2]);
    if(negInt != 0 and negInt != 1){
      std::cout << "Only '0' or '1' are allowed NegIntValues." << std::endl;
      return -1;
    }

    lambdaT = std::atof(argv[3]);
  }
  // CallLooper
  clockwork_looper(run, lambdaT, negInt);

  return 0;
}
