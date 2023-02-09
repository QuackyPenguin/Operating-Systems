/*
 * KSem.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#include "KSem.h"
#include "KSemList.h"
#include "PCBTList.h"
#include "Global.h"
#include "SCHEDULE.H"
#include "pcb.h"
#include "declare.h"

KSemList* KernelSem::sem_list = new KSemList();

KernelSem::KernelSem(int init) {
	this->value = init;
	blocked_list = new PCBTList();
	sem_list->add(this);
}

KernelSem::~KernelSem() {
	sem_list->remove(this);
	if (blocked_list) {
		delete blocked_list;
		blocked_list = 0;
	}
}

int KernelSem::wait(Time maxTimeToWait) {

	Global::lockFlag--;

	int ret = 1;

	if (--value >= 0) { //onda nit samo nastavlja dalje

		Global::lockFlag++;

		return ret;
	}

	blocked_list->add((PCB*) Global::running, maxTimeToWait);
	((PCB*) Global::running)->flag = BLOCKED;

	Global::lockFlag++;
	dispatch();

	ret=0;

	if (((PCB*) Global::running)->flag == SIGNAL) {
		ret = 1;
		((PCB*) Global::running)->flag = READY;
	}

	return ret;
}

void KernelSem::signal() {

	Global::lockFlag--;

	if (++value <= 0) {
		blocked_list->ToStart();
		PCB* tmp = blocked_list->Current();
		tmp->flag = SIGNAL;
		blocked_list->remove(tmp);
		Scheduler::put(tmp);
	}

	Global::lockFlag++;

}

int KernelSem::val() const {
	return value;
}

void KernelSem::TickTheKSem() {
	for (sem_list->ToStart(); sem_list->InList(); sem_list->Next())
		sem_list->Current()->TickTheBlocked();
}

void KernelSem::TickTheBlocked() {
	blocked_list->ToStart();
	while (blocked_list->InList()) {
		if (blocked_list->getTime() != 0) {
			blocked_list->Reduce();
			if (blocked_list->getTime() == 0) {
				PCB* tmp = blocked_list->Current();
				tmp->flag = READY;
				Scheduler::put(tmp);
				blocked_list->remove(tmp);
				continue;
			}
		}
		blocked_list->Next();
	}
}
