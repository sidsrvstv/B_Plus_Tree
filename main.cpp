// Name: Siddharth Srivastava
// Last Modified: Nov 20 2017
//
// ADS Project - BPlus Tree implementation
// This is the main file

#include <iostream>
#include <string>

#include "BPlusTree.hpp"
#include "Parsing.hpp"

using namespace std;

int main(int argc, char* argv[]){
  vector<string> treeOperations;
  string FILENAME = argv[1];
  int order;
  order = readInputFile(FILENAME, treeOperations);

  BPlusTree tree(order);

  for(int i=0; i<treeOperations.size(); ++i){
    if (treeOperations[i][0] == 'I') {
      double aKey = getKey(treeOperations[i]);
      string aValue = getValue(treeOperations[i]);
      tree.insert(aKey, aValue);  // INSERT
    } else if (treeOperations[i][0] == 'S'){
      vector<double> aKeys = getKeys(treeOperations[i]);
      if(aKeys.size() == 1) {
	tree.search(aKeys[0]);  // SEARCH
      } else if (aKeys.size() == 2) {
	tree.search(aKeys[0], aKeys[1]); // RANGE SEARCH
      }
    }
  }

  tree.writeToFile();

  return 0;
}
