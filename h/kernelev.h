/*
 * kernelev.h
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#ifndef H_KERNELEV_H_
#define H_KERNELEV_H_

class IVTEntry;
typedef unsigned char IVTNo;
class PCB;

class KernelEv{

public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();

	void wait();
	void signal();

private:
	IVTNo ivtNo;
	PCB* holderPCB;
	int value;
	PCB* blockedPCB;
};

#endif /* H_KERNELEV_H_ */
