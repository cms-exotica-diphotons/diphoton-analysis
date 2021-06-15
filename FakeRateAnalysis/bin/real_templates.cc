#include "diphoton-analysis/FakeRateAnalysis/RealTemplateAnalysis/scripts/diphoton_looper.C"

#include <iostream>

int main(int argc, char *argv[])
{
  int data_year, nPVLow, nPVHigh;
  std::string samples, isClosureTestOption;
  bool isClosureTest;

  if(argc!=6) {
    std::cout << "Syntax: real_templates.exe [2015/2016/2017/2018] [DiPhotonJets/GGJets/GJets/all] [PV_low] [PV_high] [isClosureTest(true/false)]" << std::endl;
    return -1;
  }
  else {
    data_year = std::atoi(argv[1]);
    if(data_year != 2015 and data_year != 2016 and data_year != 2017 and data_year != 2018) {
      std::cout << "Only '2015', '2016', '2017', and '2018' are allowed years." << std::endl;
      return -1;
    }
    samples = argv[2];
    if(samples != "DiPhotonJets" and samples != "GGJets"
       and samples!= "GJets" and samples != "all") {
      std::cout << "Only 'DiPhotonJets', 'GGJets', 'GJets' and 'all' are allowed samples. " << std::endl;
      return -1;
    }
    nPVLow = std::atoi(argv[3]);
    nPVHigh = std::atoi(argv[4]);
    isClosureTestOption = argv[5];
    if (isClosureTestOption != "true" and isClosureTestOption != "false"){
      std::cout << "Only 'true' or 'false' allowed for isClosureTest boolean value.";
      return -1;
    }
    else {
      isClosureTest = (isClosureTestOption == "true");
    }

  }

  std::cout << "Closure Test Setting: " << isClosureTest << std::endl;
  if (isClosureTest == true) std::cout << "Closure Test Setting " << std::endl;
  else if (!isClosureTest) std::cout << "Not closure test" << std::endl;
  diphoton_looper(data_year, samples, nPVLow, nPVHigh, isClosureTest);

  return 0;
}
