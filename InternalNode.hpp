// Name: Siddharth Srivastava
// Last Modified: Nov 16 2017
//
// ADS Project - BPlus Tree implementation
// This header file contains the InternalNode class : Inherited from Node
// The InternalNode has been implemented as a vector of pairs <double, Node*>

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Node.hpp"

#define DUMMY_KEY -10000000.00

class InternalNode : public Node {
private:
  std::vector<std::pair<double, Node*>> Dictionary;
public:
  InternalNode(int aOrder):     Node(aOrder) {
  }

  InternalNode(int aOrder, Node* aParent):     Node(aOrder, aParent) {
  }

  ~InternalNode(){
    for(auto iter: Dictionary){
      delete iter.second;
    }
  } 

  int size() const{
    return Dictionary.size();
  }

  int minSize() const{
    // implemented ceil[m/2] - 1
    if(order()%2 == 0) {
      return order()/2 -1;
    } else {
      return order()/2;
    }
  }

  int maxSize() const{
    // the order is one more as it includes block for dummy key
    // dummy key is inserted for pairing the one extra node (n keys, n+1 nodes), the leftmost node is stored with dummy key
    return order();
  }

  bool isLeaf() const{
    return false;
  }

  void insertInNewRoot(Node* aOldNode, double aKey, Node* aNewNode){
    Dictionary.push_back(std::make_pair(DUMMY_KEY, aOldNode));
    Dictionary.push_back(std::make_pair(aKey, aNewNode));
  }

  void insertInExistingNode(Node* aOldNode,  double aKey, Node* aNewNode){
    auto iter = Dictionary.begin();
    while(iter!=Dictionary.end() && aKey > iter->first){
      ++iter;
    }
    Dictionary.insert(iter, std::make_pair(aKey,aNewNode));
  }

  void printNode(){
    for(auto iter:Dictionary){
      std::cout << iter.first << " " << iter.second << std::endl;
    }
  }

  double getFirstKeyAndReplace() {
    double newKey = Dictionary[0].first;
    Dictionary[0].first = DUMMY_KEY;
    return newKey;
  }

  void moveSecondHalfTo(InternalNode* aNewNode){
    aNewNode->copySecondHalfFrom(Dictionary);
    int size = Dictionary.size();
    for(int i=minSize(); i<size; ++i){
      Dictionary.pop_back();
    }
  }

  void copySecondHalfFrom(std::vector<std::pair<double, Node*>> oldDictionary){
    for(int i=minSize(); i<oldDictionary.size(); ++i){
      oldDictionary[i].second->setParent(this);
      Dictionary.push_back(oldDictionary[i]);
    }
  }

  Node* findNode(double aKey){
    auto iter = Dictionary.begin();
    while(iter!=Dictionary.end() && aKey>=iter->first){
      iter++;
    }
    iter--;
    return iter->second;
  }
};


