// Name: Siddharth Srivastava
// Last Modified: Nov 16 2017
//
// ADS Project - BPlus Tree implementation
// This header file contains the definition of the Node class
// The Node class shall serve as the Base class for InternalNode and LeafNode classes

#pragma once

class Node{
 private:
  const int order_;
  Node* parent_;
 public:
  Node(int aOrder) : order_{aOrder}, parent_{nullptr} {
  }
  Node(int aOrder, Node* aParent) : order_{aOrder}, parent_{aParent} {
  }
  virtual ~Node(){
  }
  void setParent(Node* aParent){
    parent_ = aParent;
  }
  int order() const{
    return order_;
  }
  bool isRoot(){
    return (parent_ == nullptr);
  }
  Node* parent(){
    return parent_;
  }
  // The following methods are not defined in this class but shall be used in
  // LeafNode and InternalNode classes
  virtual bool isLeaf() const = 0;
  virtual int size() const = 0;
  virtual int minSize() const = 0;
  virtual int maxSize() const = 0;
  
};
