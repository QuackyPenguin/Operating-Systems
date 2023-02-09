/*
 * PCBTList.h
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#ifndef H_PCBTLIST_H_
#define H_PCBTLIST_H_

class PCB;
typedef unsigned int Time;

class PCBTList {

public:

	struct Node {
		Node* next;
		PCB* data;
		Time time;
	};

	PCBTList();
	~PCBTList();
	void add(PCB* toAdd, Time t);
	int remove(PCB* toRemove);
	int IsEmpty();
	int Count();
	void ToStart();
	void Next();
	PCB* Current();
	int InList();
	Time Reduce();
	Time getTime();

private:

	Node *head, *tail, *curr;
	int numberOfNodes;

};

#endif /* H_PCBTLIST_H_ */
