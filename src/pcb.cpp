/*
 * pcb.cpp
 *
 *  Created on: Sep 13, 2021
 *      Author: OS1
 */

#include "pcb.h"
#include "thread.h"
#include "PCBList.h"
#include "SCHEDULE.H"
#include <DOS.H>
#include "Global.h"
#include "IOSTREAM.H"
#include "declare.h"

PCBList* PCB::process_list = new PCBList();
ID PCB::newID = 0;
PCB* PCB::busyWaitPCB = new PCB(&(PCB::busyWait), BUSYWAIT);

PCB::PCB(StackSize stacksize, Time timesl, Thread* myT) {

	Global::lockFlag--;

	if (stacksize > maximumStackSize)
		stacksize = maximumStackSize;

	stacksize = stacksize / sizeof(unsigned);
	stackSize = stacksize;
	stack = new unsigned[stacksize];

	bp = sp = ss = 0;
	timeslice = timesl;
	myThread = myT;
	flag = TO_START;
	pcbID = ++newID;
	parent = 0;
	waiting = new PCBList();

#ifndef BCC_BLOCK_IGNORE

	stack[stacksize-2]=FP_SEG(&(PCB::wrappper));
	stack[stacksize-3]=FP_OFF(&(PCB::wrappper));
	stack[stacksize-1]=0x0200; //PSW I flag je 1
	stack[stacksize-12]=0;

	ss=FP_SEG(stack+stacksize-12);
	bp=sp=FP_OFF(stack+stacksize-12);

#endif

	process_list->add(this);

	Global::lockFlag++;

}

PCB::PCB(void (*body)(), Flag startFlag) {

	stackSize = 1024 / sizeof(unsigned);
	stack = new unsigned[stackSize];
	bp = sp = ss = 0;
	timeslice = 1;
	myThread = 0;
	parent = 0;
	flag = startFlag;
	pcbID = ++newID;
	waiting = 0;

#ifndef BCC_BLOCK_IGNORE
	stack[stackSize-2]=FP_SEG(body);
	stack[stackSize-3]=FP_OFF(body);
	stack[stackSize-1]=0x0200;	//PSW I flag je 1

	ss=FP_SEG(stack+stackSize-12);
	bp=sp=FP_OFF(stack+stackSize-12);
#endif

	process_list->add(this); //mozda da se izbaci
}

PCB::PCB() {

	Global::lockFlag--;

	myThread = 0;
	stack = 0;
	parent = 0;
	stackSize = 0;
	timeslice = mainTimeSlice;
	Global::counter = mainTimeSlice;
	ss = sp = bp = 0;
	waiting = 0;
	flag = READY;
	pcbID = 0;

	Global::lockFlag++;

}

ID PCB::getID() {
	return pcbID;
}

ID PCB::getRunningID() {
	return ((PCB*) Global::running)->pcbID;
}

Thread* PCB::getThreadbyID(ID toFind) {

	Global::lockFlag--;

	Thread* ret = 0;
	process_list->ToStart();
	while (process_list->InList() != 0) {
		if (process_list->Current()->getID() == toFind) {
			ret = process_list->Current()->myThread;
			break;
		}
		process_list->Next();
	}

	Global::lockFlag++;

	return ret;

}

void PCB::wrappper() {
	((PCB*) Global::running)->myThread->run();

	Global::lockFlag--;
	freeWaiting();
	Global::lockFlag++;

	dispatch();
}

void PCB::startPCB() {

	Global::lockFlag--;

	flag = READY;
	Scheduler::put(this);

	Global::lockFlag++;
}

void PCB::waitToCompletePCB() {

	Global::lockFlag--;

	if (this->flag != FINISHED) {
		((PCB*) Global::running)->flag = BLOCKED;
		this->waiting->add((PCB*) Global::running);

		Global::lockFlag++;

		dispatch();
	} else {

		Global::lockFlag++;

		return;
	}
}

PCB::~PCB() {
	deletePCB();
}

void PCB::busyWait() {
	while (1)
		;
}

void PCB::waitForForkChildrenPCB() {
	for (process_list->ToStart(); process_list->InList();
			process_list->Next()) {
		if (process_list->Current()->parent == (PCB*) Global::running)
			process_list->Current()->waitToCompletePCB();
	}
}

void PCB::exitPCB() {

	Global::lockFlag--;
	freeWaiting();
	((PCB*) Global::running)->deletePCB();
	Global::lockFlag++;

	dispatch();
}

void PCB::freeWaiting() {
	((PCB*) Global::running)->flag = FINISHED;
	((PCB*) Global::running)->waiting->ToStart();
	while (((PCB*) Global::running)->waiting->InList()) {
		((PCB*) Global::running)->waiting->Current()->flag = READY;
		Scheduler::put(((PCB*) Global::running)->waiting->Current());
		((PCB*) Global::running)->waiting->Next();
	}

}

void PCB::deletePCB() {
	if (waiting) {
		waitToCompletePCB();
		delete waiting;
		waiting = 0;
	}
	if (stack)
		delete stack;
	stack = 0;
	myThread = 0;

	Global::lockFlag--;
	process_list->remove(this);
	Global::lockFlag++;
}
