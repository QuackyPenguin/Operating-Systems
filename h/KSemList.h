/*
 * KSemList.h
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#ifndef H_KSEMLIST_H_
#define H_KSEMLIST_H_

class KernelSem;

class KSemList {

public:

	struct Node {
		Node* next;
		KernelSem* data;
	};

	KSemList();
	~KSemList();
	void add(KernelSem* toAdd);
	int remove(KernelSem* toRemove);
	int IsEmpty();
	int Count();
	void ToStart();
	void Next();
	KernelSem* Current();
	int InList();
private:

	Node *head, *tail, *curr;
	int numberOfNodes;

};



#endif /* H_KSEMLIST_H_ */
