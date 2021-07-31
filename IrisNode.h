#pragma once
#include "Iris.h"
class IrisNode
{
private:
	Iris iris;
	IrisNode* next;
	IrisNode* prev;
public:
	IrisNode();
	IrisNode(Iris iris);
	IrisNode* getNext();
	IrisNode* getPrev();
	void setNext(IrisNode next);
	void setPrev(IrisNode prev);
};

