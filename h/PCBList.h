/*
 * PCBList.h
 *
 *  Created on: Sep 16, 2021
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_

class PCB;

class PCBList {

public:

	struct Node {
		Node* next;
		PCB* data;
	};

	PCBList();
	~PCBList();
	void add(PCB* toAdd);
	int remove(PCB* toRemove);
	int IsEmpty();
	int Count();
	void ToStart();
	void Next();
	PCB* Current();
	int InList();
private:

	Node *head, *tail, *curr;
	int numberOfNodes;

};

#endif /* PCBLIST_H_ */
