// Name: Siddharth Srivastava
// Last Modified: Nov 17 2017
//
// ADS Project - BPlus Tree implementation
// This header file contains the LeafNode class
// The LeafNode has been implemented as a vector of pairs <double, string>
// Nodes have been implemented as a doubly LinkedList

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "Node.hpp"

typedef std::pair<double, std::string> dict;

class LeafNode : public Node {
private:
  int order_;
  std::vector<std::pair<double, std::string>> Dictionary;
  LeafNode* next_;
  LeafNode* prev_;
  
public:
  LeafNode(int aOrder): Node(aOrder), next_{nullptr}, prev_{nullptr}  {
  }

  LeafNode(int aOrder, Node* aParent) :  Node(aOrder, aParent), next_{nullptr}, prev_{nullptr} {
  }

  ~LeafNode(){
  }

  LeafNode* next(){
    return next_;
  }

  LeafNode* prev(){
    return prev_;
  }

  void setNext(LeafNode *aNext){
      next_ = aNext;
  }

  void setPrev(LeafNode *aPrev){
      prev_ = aPrev;
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
    return order() - 1;
  }

  bool isLeaf() const{
    return true;
  }

  void insert(double aKey, std::string aValue){
    auto iter = Dictionary.begin();
    while(iter!=Dictionary.end() && iter->first<aKey){
      ++iter;
    }
    Dictionary.insert(iter, dict(aKey, aValue));    
  }

  double getFirstKey() {
    double newKey = Dictionary[0].first;
    return newKey;
  }

  void printDictionary(){
    for(auto iter:Dictionary){
      std::cout << iter.first << " " << iter.second << std::endl;
    }
  }

  std::string search(double aKey){
    std::string result = "";
    for(auto iter:Dictionary){
      if(iter.first==aKey){
	result += iter.second + ",";
      }
    }
    if(result != ""){
      return result;
    } else {
      return "Null";
    }
  }

  std::string searchRange(double aKey1, double aKey2){
    std::string result = "";
    for(auto iter:Dictionary){
      if(iter.first>=aKey1 && iter.first<=aKey2){
	result += "(" + std::to_string(iter.first) + "," + iter.second + "),";
      }
    }
    return result;
  }

  std::string getFromKey(double aKey){
    std::string result = "";
    for(auto iter:Dictionary){
      if(iter.first>=aKey){
	result += "(" + std::to_string(iter.first) + "," + iter.second + "),";
      }
    }
    return result;
  }    

  std::string getAllKeys(){
    std::string result = "";
    for(auto iter:Dictionary){
      result += "(" + std::to_string(iter.first) + "," + iter.second + "),";
    }
    return result;
  }

  std::string getTillKey(double aKey){
    std::string result = "";
    for(auto iter:Dictionary){
      if(iter.first<=aKey){
	result += "(" + std::to_string(iter.first) + "," + iter.second + "),";
      }
    }
    return result;
  }

  void printLeaf(){
      for(auto iter:Dictionary){
      std::cout << "(" << iter.first << " " <<iter.second << ") " << std::endl;
    }
  }

  void moveSecondHalfTo(LeafNode* aNewNode){
    aNewNode->copySecondHalfFrom(Dictionary);
    int size = Dictionary.size();
    for(int i=minSize(); i<size; ++i){
      Dictionary.pop_back();
    }
  }

  void copySecondHalfFrom(std::vector<std::pair<double, std::string>>& oldDictionary){
    for(int i=minSize(); i<oldDictionary.size(); ++i){
      Dictionary.push_back(oldDictionary[i]);
    }
  }

};
  
    
