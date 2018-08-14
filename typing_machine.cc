// Copyright 2018 <Author>

#include "typing_machine.h"

TypingMachine::TypingMachine() {
	mStartNode = nullptr;
	mEndNode = nullptr;
	mCursor = nullptr;
  mStrLen = 0;
  return;
}

void TypingMachine::HomeKey() {
  mCursor = nullptr;
  return;
}

void TypingMachine::EndKey() {
  mCursor = mEndNode;
  return;
}

void TypingMachine::LeftKey() {
	mCursor = (mCursor != nullptr) ? mCursor->GetPreviousNode() : nullptr;
  return;
}

void TypingMachine::RightKey() {
	if (mCursor == nullptr)
		mCursor = mStartNode;
	else
		mCursor = (mCursor->GetNextNode() != nullptr) ? mCursor->GetNextNode() : mCursor;
  return;
}

bool TypingMachine::TypeKey(char key) {
  if (key < 0x20 || key > 0x7E) return false;
  if (mStrLen >= 100) return false;

  if (mCursor == nullptr) {
	  if (mStartNode == nullptr) {
		  mCursor = new Node(key);
		  mStartNode = mEndNode = mCursor;
	  }
	  else {
		  mStartNode = mStartNode->InsertPreviousNode(key);
		  mCursor = mStartNode;
	  }
  }
  else {
	  Node *newNode = mCursor->InsertNextNode(key);
	  if (mCursor == mEndNode)
		  mEndNode = newNode;
	  mCursor = newNode;

  }

  mStrLen++;

  return true;
}

bool TypingMachine::EraseKey() {
	if (mStrLen == 0 || mCursor == nullptr) return false;

	Node *prevNode = mCursor->GetPreviousNode();
	Node *nextNode = mCursor->GetNextNode();
	if (prevNode != nullptr) {
		prevNode->EraseNextNode();
		if (mCursor == mEndNode) mEndNode = prevNode;
		mCursor = prevNode;
	}
	else if (nextNode != nullptr) {
		nextNode->ErasePreviousNode();
		mCursor = nullptr;
		mStartNode = nextNode;
	}
	else {
		delete mCursor;
		mCursor = mStartNode = mEndNode = nullptr;
	}

  mStrLen--;
  return true;
}

std::string TypingMachine::Print(char separator) {
	std::string sResult;

	if (mStrLen > 0) {
		Node *node = mStartNode;
		if ((mCursor == nullptr) && (separator != 0))
			sResult += separator;

		while (node != nullptr) {
			if(node->GetData() != 0) 
				sResult += node->GetData();
			if ((node == mCursor) && (separator != 0))
				sResult += separator;
			node = node->GetNextNode();
		}
	}
	else {
		if (separator != 0) 
			sResult += separator;
	}

	return sResult;
}
