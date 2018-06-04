// Name: Siddharth Srivastava
// Last Modified: Nov 18 2017
//
// ADS Project - BPlus Tree implementation
// This is the input file read and parse file

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

// gets the key to insert
double getKey(std::string input){
  input = input.substr(7, input.size());
  std::string key;
  int i = 0;
  while( input[i] != ','){
    key  = key + input[i];
    i++;
  }
  return stod(key);
}

// gets the keys for range search and search
std::vector<double> getKeys(std::string input){
  std::vector<double> keys;
  std::string key1, key2;
  input = input.substr(7, input.size());
  int i = 0;
  int keyFlag = 0;
  while(input[i] != ')'){
    if(!keyFlag){
      if(input[i] != ','){
	key1 += input[i];
      } else {
	keyFlag = 1;
      }
    } else if(keyFlag){
      key2 += input[i];
    }
    i++;
  }
  keys.push_back(stod(key1));
  if (keyFlag){
    keys.push_back(stod(key2));
  }
  return keys;
}

// gets the string value to be inserted for key
std::string getValue(std::string input){
  input = input.substr(7, input.size());
  std::string value = "";
  int i = 0;
  int flag = 0;
  while(input[i] != ')'){
    if(flag){
      value += input[i];
    }
    if(input[i] == ','){
      flag = 1;
    }
    i++;
  }
  return value;
}

int getOrder(std::string line){
  return (std::stoi(line));
}

// reads input file, gets the operations to be performed in a vector pushed as strings
int readInputFile(std::string FILENAME,   std::vector<std::string>& treeOperations){
  std::string line;
  std::ifstream inputFile(FILENAME);
  bool firstLineRead = false;
  int order{1};
  if(inputFile.is_open()){
    while(getline(inputFile, line)){
      if (!firstLineRead){
	order = getOrder(line);
	firstLineRead = true;
      } else {
	treeOperations.push_back(line);
      }
    }
    inputFile.close();
  } else {
    std::cout << "Unable to open the file\n";
  }
  return order;
}

