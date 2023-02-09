/*
 * ivtentry.h
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#ifndef H_IVTENTRY_H_
#define H_IVTENTRY_H_

class KernelEv;
typedef unsigned char IVTNo;
const int IVTNumber = 256;
typedef void interrupt (*pInterrupt)(...);

#define PREPAREENTRY(numEntry, OldFlag)\
void interrupt inter##numEntry(...); \
IVTEntry newEntry##numEntry(numEntry, inter##numEntry); \
void interrupt inter##numEntry(...) {\
newEntry##numEntry.signal();\
if (OldFlag == 1)\
newEntry##numEntry.callOld();\
}

class IVTEntry {

public:

	IVTEntry(IVTNo ivtNo, pInterrupt newRout);
	~IVTEntry();

	void signal();
	void setMyEvent(KernelEv* kernelEv);
	void callOld();

	static IVTEntry* IVTEntries[IVTNumber];

private:

	KernelEv *myKernelEv;
	IVTNo myIVTNo;
	pInterrupt oldRout;
};

#endif /* H_IVTENTRY_H_ */
