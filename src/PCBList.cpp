/*
 * PCBList.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#include "PCBList.h"
#include "pcb.h"

PCBList::PCBList() {
	head = 0;
	tail = 0;
	curr = 0;
	numberOfNodes = 0;
}

PCBList::~PCBList() {
	curr = head;
	while (head != 0) {
		head = head->next;
		delete curr;
		curr = head;
	}
	numberOfNodes = 0;
	tail = 0;
}

void PCBList::add(PCB* toAdd) {
	Node *tmp = new Node();
	tmp->data = toAdd;
	tmp->next = 0;

	if (!head)
		head = tmp;
	else
		tail->next = tmp;
	tail = tmp;

	numberOfNodes++;
}

int PCBList::remove(PCB* toRemove) {
	Node* tmp = head, *prev = 0;
	for (; tmp != 0; prev = tmp, tmp = tmp->next)
		if (tmp->data == toRemove)
			break;

	if (tmp == 0)
		return 1;
	if (curr == tmp)
		curr = curr->next;
	if (prev != 0)
		prev->next = tmp->next;
	else
		head = tmp->next;
	if (tail == tmp)
		tail = prev;

	numberOfNodes--;
}

int PCBList::IsEmpty() {
	if (numberOfNodes == 0)
		return 1;
	return 0;
}

int PCBList::Count() {
	return numberOfNodes;
}

void PCBList::ToStart() {
	curr = head;
}

void PCBList::Next() {
	if (curr != 0)
		curr = curr->next;
}

PCB* PCBList::Current() {
	if (curr != 0)
		return curr->data;
	return 0;
}

int PCBList::InList() {
	if (curr != 0)
		return 1;
	return 0;
}




