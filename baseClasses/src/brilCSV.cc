#include "nTupleAnalysis/baseClasses/interface/brilCSV.h"

/*
 * Parses through csv file line by line and returns the data
 * in vector of vector of strings.
 */
std::map<edm::LuminosityBlockID, float> brilCSV::GetData()
{
  std::cout<<"brilCSV::GetData() fileName: "<<fileName<<std::endl;
  std::ifstream file(fileName);
 
  std::string line = "";
  float intLumi = 0;
  // Iterate through each line and split the content using delimeter
  int lineNumber = 0;
  if (!file.is_open())
    perror("error while opening file");
  while (getline(file, line))
    {
      lineNumber += 1;
      if(line.substr(0,1)=="#") continue; //comment, skip this line

      //line format is run:fill,lumiBlock:lumiBlock,date hh:mm:ss,hltpath,delivered(/pb),recorded(/pb),avgpu,source
      // Example:
      //299368:5962,42:42,07/18/17 16:11:20,HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0_v1,0.325128513,0.043635043,40.5,HFET
      std::vector<std::string> vecLine;
      boost::algorithm::split(vecLine, line, boost::is_any_of(",:"));

      unsigned int run;
      unsigned int lumiBlock;
      run       = std::stoul(vecLine[0]);
      lumiBlock = std::stoul(vecLine[2]);
      edm::LuminosityBlockID lumiID(run, lumiBlock);
      float lumi;
      lumi      = std::stof (vecLine[9]);
      intLumi+=lumi;
      lumiData[lumiID] = lumi;
      lumiData_runs[run] += lumi;
      //std::cout << run << " " << lumiBlock << " " << lumi << " " << intLumi << std::endl;
      if(lineNumber<10){
	int i = 0;
	for(std::string v: vecLine){ std::cout<<"("<<i<<":"<<v<<") "; i++; }
	std::cout<<std::endl;
      }
    }
  std::cout<<"brilCSV::GetData() read "<<lineNumber<<" lines"<<std::endl;
  std::cout<<"brilCSV::GetData() intLumi: "<<intLumi/1000<<"/fb"<<std::endl;
  // Close the File
  file.close();
 
  return lumiData;
}
