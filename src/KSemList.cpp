/*
 * KSemList.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#include "KSemList.h"
#include "KSem.h"

KSemList::KSemList() {
	head = 0;
	tail = 0;
	curr = 0;
	numberOfNodes = 0;
}

KSemList::~KSemList() {
	curr = head;
	while (head != 0) {
		head = head->next;
		delete curr;
		curr = head;
	}
	numberOfNodes = 0;
	tail = 0;
}

void KSemList::add(KernelSem* toAdd) {
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

int KSemList::remove(KernelSem* toRemove) {
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
	delete tmp;
	numberOfNodes--;
}

int KSemList::IsEmpty() {
	if (numberOfNodes == 0)
		return 1;
	return 0;
}

int KSemList::Count() {
	return numberOfNodes;
}

void KSemList::ToStart() {
	curr = head;
}

void KSemList::Next() {
	if (curr != 0)
		curr = curr->next;
}

KernelSem* KSemList::Current() {
	if (curr != 0)
		return curr->data;
	return 0;
}

int KSemList::InList() {
	if (curr != 0)
		return 1;
	return 0;
}
