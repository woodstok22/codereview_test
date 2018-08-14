// Copyright 2018 <Author>
#include "node.h"

Node::Node(char data) {
  mNodeData = data;
  mPrevPtr = nullptr;
  mNextPtr = nullptr;
  return;
}

char Node::GetData() {
  return mNodeData;
}

Node* Node::GetPreviousNode() {
  return mPrevPtr;
}

Node* Node::GetNextNode() {
  return mNextPtr;
}

Node* Node::InsertPreviousNode(char data) {
  Node* newNode = new Node(data);
  newNode->mPrevPtr = mPrevPtr;
  newNode->mNextPtr = this;
  if(mPrevPtr != nullptr) mPrevPtr->mNextPtr = newNode;
  mPrevPtr = newNode;
  return newNode;
}

Node* Node::InsertNextNode(char data) {
  Node* newNode = new Node(data);
  newNode->mPrevPtr = this;
  newNode->mNextPtr = mNextPtr;
  if(mNextPtr != nullptr) mNextPtr->mPrevPtr = newNode;
  mNextPtr = newNode;
  return newNode;
}

bool Node::ErasePreviousNode() {
  Node *removeNode = mPrevPtr;
  if (removeNode == nullptr) return false;

  mPrevPtr = removeNode->mPrevPtr;
  if(mPrevPtr != nullptr) mPrevPtr->mNextPtr = this;
  delete removeNode;
  return true;
}

bool Node::EraseNextNode() {
  Node *removeNode = mNextPtr;
  if (removeNode == nullptr) return false;

  mNextPtr = removeNode->mNextPtr;
  if(mNextPtr != nullptr) mNextPtr->mPrevPtr = this;
  delete removeNode;
  return true;
}