// -*- C++ -*-

#if !defined(initBranch_H)
#define initBranch_H

#include <iostream>
#include <TChain.h>
#include <TChainElement.h>
#include <TDataType.h>
#include <TClass.h>


static inline int connectBranch(bool isInput, TTree *tree, std::string name, auto& variable, std::string typeKey){
  if(isInput) return inputBranch(tree, name, variable);
  return outputBranch(tree, name, variable, typeKey);
}


static inline int outputBranch(TTree *tree, std::string name, auto& variable, std::string typeKey){
  const char *bname = name.c_str();
  if(tree->FindBranch(bname)){
    std::cout << "outputBranch(TTree *tree, std::string name, auto& variable, std::string typeKey)::INFO " << bname << " already exists" << std::endl;
    return -1;
  }
  tree->Branch(bname, &variable, (name+"/"+typeKey).c_str());
  return 0;
}



static inline int connectBranchArr(bool isInput, TTree *tree, std::string name, auto& variable, std::string indexName, std::string typeKey){
  if(isInput) return inputBranch(tree, name, variable);
  return outputBranchArr(tree, name, variable, indexName, typeKey);
}


static inline int outputBranchArr(TTree *tree, std::string name, auto& variable, std::string indexName, std::string typeKey){
  const char *bname = name.c_str();
  if(tree->FindBranch(bname)){
    std::cout << "outputBranchArr(TTree *tree, std::string name, auto& variable, std::string indexName, std::string typeKey)::INFO " << bname << " already exists" << std::endl;
    return -1;
  }
  tree->Branch(bname, variable, (name+"["+indexName+"]/"+typeKey).c_str() );
  return 0;
}


static inline int inputBranch(TTree *tree, std::string name, auto& variable){
  const char *bname = name.c_str();
  if(!tree->FindBranch(bname)){
    std::cout << "inputBranch(TTree *tree, std::string name, auto& variable)::WARNING " << bname << " does not exist" << std::endl;
    return -1;
  }

  tree->SetBranchStatus(bname, 1);
  int code = tree->SetBranchAddress(bname, &variable);
  if(code != 0) std::cout << "inputBranch(TTree *tree, std::string name, auto& variable)::WARNING " << bname << " " << code << std::endl;
  return code;
}

static inline int inputBranch(TTree *tree, std::string name, void* add){
  const char *bname = name.c_str();
  if(!tree->FindBranch(bname)){
    std::cout << "inputBranch(TTree *tree, std::string name, void* add)::WARNING " << bname << " does not exist" << std::endl;
    return -1;
  }
  tree->SetBranchStatus(bname, 1);
  int code = tree->SetBranchAddress(bname, add);
  if(code != 0) std::cout << "inputBranch(TTree *tree, std::string name, void* add)::WARNING " << bname << " " << code << std::endl;
  return code;
}

#endif // initBranch_H
