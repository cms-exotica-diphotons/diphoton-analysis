#include "diphoton-analysis/ClockworkAnalysis/scripts/clockwork_looper.C"

#include <iostream>

int main(int argc, char *argv[])
{
  std::string run, negInt, kVal, lambdaT;

  if(argc != 5) {
    std::cout << "Syntax: clockwork.exe [2016/2017/2018] [500/1000/3000/5000] [NegInt0/NegInt1] [4000/6500/11000]" << std::endl;
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
    kVal = argv[2];
    if(kVal.find("500") != std::string::npos
       and kVal.find("1000") != std::string::npos
       and kVal.find("3000") != std::string::npos
       and kVal.find("5000") != std::string::npos) {
      std::cout << "Only '500', '1000', '3000' and '5000' are allowed kValues." << std::endl;
      return -1;
    }
    negInt = argv[3];
    if(negInt.find("NegInt0")  != std::string::npos
       and negInt.find("NegInt1") != std::string::npos) {
      std::cout << "Only 'NegInt0' or 'NegInt1' are allowed NegIntValues." << std::endl;
      return -1;
    }
    lambdaT = argv[4];
    if(lambdaT.find("4000") != std::string::npos
       and lambdaT.find("6500") != std::string::npos
       and lambdaT.find("11000") != std::string::npos) {
      std::cout << "Only '500', '1000', '3000' and '5000' are allowed kValues." << std::endl;
      return -1;
    }
  }
  // CallLooper
  clockwork_looper(run, kVal, lambdaT, negInt);

  return 0;
}
