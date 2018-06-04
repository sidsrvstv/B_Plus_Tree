// Name: Siddharth Srivastava
// Last Modified: Nov 18 2017
//
// ADS Project - BPlus Tree implementation
// This header file contains the BPlusTree class


#include <string>
#include <utility>
#include <vector>
#include <fstream>

#include "Node.hpp"
#include "InternalNode.hpp"
#include "LeafNode.hpp"

#define DEBUG 0

class BPlusTree{
private:
  int order;
  Node* root;
  std::vector<std::string> output_file;
public:
  BPlusTree(int aOrder){
    order = aOrder;
    root = nullptr;
  }
  //~BPlusTree(){

  bool isEmpty(){
    return (root == nullptr);
  }

  void insert(double aKey, std::string aValue){
    // This is the method for insert
    // creates a new tree if empty or inserts data into corresponding leaf
    if( isEmpty() ){
      createTree(aKey, aValue);
    } else {
      insertInLeaf(aKey, aValue);
    }
  }

  void createTree(double aKey, std::string aValue){
    LeafNode* newNode = new LeafNode(order);
    newNode->insert(aKey, aValue);
    root = newNode;
  }

  void insertInLeaf(double aKey, std::string aValue){
    // Finds corresponsing lead where pair is to be inserted and inserts
    // if max size exceeded, split operatio is performed
    // the new leaf is doubly linked list to original leaf
    LeafNode* newNode = findLeafNode(aKey);
    newNode->insert(aKey, aValue);
    int size = newNode->size();
    if(size > newNode->maxSize() ){
      LeafNode* newnewNode = split(newNode);
      if(DEBUG){
	std::cout << newnewNode << std::endl;
      }
      newnewNode->setNext(newNode->next());
      newnewNode->setPrev(newNode);
      newNode->setNext(newnewNode);
      if(DEBUG){
	std::cout << "newnewNode: " << newnewNode << std::endl;
	std::cout << "newNode: " << newNode << std::endl;
	std::cout << "newNode->next: " << newNode->next() << std::endl;
	std::cout << "newnewNode->prev: " << newnewNode->prev() << std::endl; 		
      }
      double newKey = newnewNode->getFirstKey();
      insertInParent(newNode, newKey, newnewNode);
    } 
  }

  void insertInParent(Node* aOldNode, double aKey, Node* aNewNode){
    // after split operation in leafnode, insertion in parent
    // if required split operation in parent too. The split happens recursively as the tree grows upwards
    InternalNode* parent = static_cast<InternalNode*>(aOldNode->parent());
    if(parent == nullptr){
      root = new InternalNode(order);
      parent = static_cast<InternalNode*>(root);
      aOldNode->setParent(parent);
      aNewNode->setParent(parent);
      parent->insertInNewRoot(aOldNode, aKey, aNewNode);
    } else {
      parent->insertInExistingNode(aOldNode, aKey, aNewNode);
      int size = parent->size();
      if(size > parent->maxSize()) {
	InternalNode* newNode = split(parent);
	double newKey = newNode->getFirstKeyAndReplace();
	insertInParent(parent,  newKey, newNode);
      }
    }
  }

  LeafNode* findLeafNode(double aKey){
    // find leaf node for given key
    auto node = root;
    while(!node->isLeaf()){
      auto internalNode = static_cast<InternalNode*>(node);
      node = internalNode->findNode(aKey);
    }
    return static_cast<LeafNode*>(node);
  }

  void search(double aKey){
    // value written to output file for corresponding key
    LeafNode* node = findLeafNode(aKey);
    if(DEBUG){
      std::cout << aKey << std::endl;
      std::cout << node << std::endl;
      node->printLeaf();
      node->printDictionary();
      LeafNode* newNode = node->next();
      newNode->printDictionary();
    }
    std::string result = "";
    result = node->search(aKey);
    if(result.back() == ','){
      result.pop_back();
    }
    output_file.push_back(result);    
  }

  void search(double aKey1, double aKey2){
    // range of values written to output file for corresponding key range
    // startleaf and endleaf calculated
    // until startleaf becomes equal to endleaf, node pairs printed to output file
    LeafNode* startLeaf = findLeafNode(aKey1);
    LeafNode* endLeaf = findLeafNode(aKey2);
    std::string result = "";
    if (startLeaf == endLeaf){
      result += startLeaf->searchRange(aKey1, aKey2);
    } else {
      result += startLeaf->getFromKey(aKey1);
      startLeaf = startLeaf->next();
      while(startLeaf!=endLeaf){
	result += startLeaf->getAllKeys();
	startLeaf = startLeaf->next();
      }
      result += startLeaf->getTillKey(aKey2);
    }
    if (result == "") {
      result = "Null";
    } else {
      if(result.back() == ','){
	result.pop_back();
      }
    }
    output_file.push_back(result);
  }

  // generic template for split, so as to split both internal nodes and leaf nodes using this 
  template<typename T>
  T* split(T* aNode){
    T* newNode = new T(order, aNode->parent());
    aNode->moveSecondHalfTo(newNode);
    return newNode;
  }

  void writeToFile(){
    // writes to output file
    // search results have been pushed to vector which is dumped here
    std::ofstream outfile;
    outfile.open("output_file.txt");
    for(int i=0; i<output_file.size();++i){
      outfile << output_file[i] << std::endl;
    }
    outfile.close();
  }

  void printAllLeafs(){
    // DEBUG method for printing all leaf data
    double min = -100000.00;
    double max = 100000000.00;
    LeafNode* startLeaf = findLeafNode(min);
    LeafNode* endLeaf = findLeafNode(max);
    if(DEBUG){
      std::cout << startLeaf << std::endl;
      std::cout << endLeaf << std::endl;
    }
    while(startLeaf!=endLeaf){
      startLeaf->printLeaf();
      startLeaf = startLeaf->next();
    }
    startLeaf->printLeaf();
  }
  
};
    
