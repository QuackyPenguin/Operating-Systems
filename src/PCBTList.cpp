/*
 * PCBTList.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#include "pcb.h"
#include "PCBTList.h"

PCBTList::PCBTList() {
	head = 0;
	tail = 0;
	curr = 0;
	numberOfNodes = 0;
}
PCBTList::~PCBTList() {
	curr = head;
	while (head != 0) {
		head = head->next;
		delete curr->data;
		delete curr;
		curr = head;
	}
	numberOfNodes = 0;
	tail = 0;
}
void PCBTList::add(PCB* toAdd, Time t) {
	Node *tmp = new Node();
	tmp->data = toAdd;
	tmp->time = t;
	tmp->next = 0;

	if (!head)
		head = tmp;
	else
		tail->next = tmp;
	tail = tmp;

	numberOfNodes++;
}
int PCBTList::remove(PCB* toRemove) {

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
int PCBTList::IsEmpty() {
	if (numberOfNodes == 0)
		return 1;
	return 0;
}
int PCBTList::Count() {
	return numberOfNodes;
}
void PCBTList::ToStart(){
	curr=head;
}
void PCBTList::Next(){
	if(curr!=0)
		curr=curr->next;
}
PCB* PCBTList::Current() {
	if (curr != 0)
		return curr->data;
	return 0;
}
int PCBTList::InList(){
		if (curr != 0)
			return 1;
		return 0;
}
Time PCBTList::Reduce()
{
	if(curr!=0)
		return --(curr->time);
	return 0;
}
Time PCBTList::getTime(){
	if(curr) return curr->time;
	return 0;
}
