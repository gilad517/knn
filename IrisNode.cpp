#include "IrisNode.h"
class IrisNode
{
private:
	Iris iris;
	IrisNode* next;
	IrisNode* prev;
public:
	IrisNode(Iris iris) {
		this->iris = iris;
		this->next = nullptr;
		this->prev = nullptr;
	}
	IrisNode() = default;
	~IrisNode() {}
	IrisNode* getNext() {
		return this->next;
	}
	IrisNode* getPrev() {
		return this->prev;
	}
	void setNext(IrisNode next) {
		this->next = &next;
	}
	void setPrev(IrisNode prev) {
		this->prev = &prev;
	}
};

