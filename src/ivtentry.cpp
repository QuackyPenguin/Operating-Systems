/*
 * ivtentry.cpp
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#include "ivtentry.h"
#include "kernelev.h"
#include <DOS.H>
#include "Global.h"

IVTEntry* IVTEntry::IVTEntries[IVTNumber];

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt newRout) {

	myIVTNo = ivtNo;
	myKernelEv=0;
	oldRout=0;

	Global::lockFlag--;

#ifndef BCC_BLOCK_IGNORE
	oldRout=getvect(ivtNo);
	setvect(ivtNo, newRout);
#endif

	IVTEntries[myIVTNo] = this;

	Global::lockFlag++;

}

IVTEntry::~IVTEntry() {
	callOld();
	myKernelEv = 0;

	Global::lockFlag--;

	IVTEntries[myIVTNo] = 0;

#ifndef BCC_BLOCK_IGNORE
	setvect(myIVTNo, oldRout);
#endif

	Global::lockFlag++;

}

void IVTEntry::callOld() {
	oldRout();
}

void IVTEntry::signal() {
	if (myKernelEv)
		myKernelEv->signal();
}

void IVTEntry::setMyEvent(KernelEv* kernelEv) {
	myKernelEv = kernelEv;
}
