/*
 * kernelev.cpp
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#include "kernelev.h"
#include "ivtentry.h"
#include "Global.h"
#include "SCHEDULE.H"
#include "pcb.h"
#include "declare.h"

KernelEv::KernelEv(IVTNo ivtNo){
	value=0;
	holderPCB=(PCB*)Global::running;
	this->ivtNo=ivtNo;
	IVTEntry::IVTEntries[ivtNo]->setMyEvent(this);
	blockedPCB=0;
}

KernelEv::~KernelEv()
{
	holderPCB=0;
}

void KernelEv::signal(){
	if(blockedPCB){
		blockedPCB->flag=READY;
		Scheduler::put(blockedPCB);
		blockedPCB=0;
	}
	else value=1;
}

void KernelEv::wait(){
	if((PCB*)Global::running==holderPCB){
		if(value) value=0;
		else {
			blockedPCB=holderPCB;
			blockedPCB->flag=BLOCKED;
			dispatch();
		}
	}
}
