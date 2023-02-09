/*
 * thread.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#include "thread.h"
#include "pcb.h"
#include "Global.h"
#include "declare.h"

Thread::Thread(StackSize stackSize, Time timeSlice) :
		myPCB(0) {
	myPCB = new PCB(stackSize, timeSlice, this);
}

Thread::~Thread() {

}

ID Thread::getId() {
	return myPCB->getID();
}

Thread* Thread::getThreadById(ID id) {
	return PCB::getThreadbyID(id);
}

void Thread::start() {
	myPCB->startPCB();
}

void Thread::waitToComplete() {
	myPCB->waitToCompletePCB();
}

ID Thread::getRunningId() {
	return PCB::getRunningID();
}

void Thread::exit() {
	PCB::exitPCB();
}

void Thread::waitForForkChildren() {
	PCB::waitForForkChildrenPCB();
}

ID Thread::fork() {


	Thread* clonedChild = ((PCB*) Global::running)->myThread->clone();
	if (clonedChild == 0)
		return -1;
	int ret = clonedChild->getId();
	clonedChild->myPCB->parent = (PCB*) Global::running;
	clonedChild->myPCB->flag = READY;

	Global::lockFlag--;

	Global::forkChild = clonedChild->myPCB;
	stack_fork();

	if (getRunningId() == ret)
		return 0;

	return ret;
}
