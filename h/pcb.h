/*
 * pcb.h
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#ifndef H_PCB_H_
#define H_PCB_H_

class PCBList;
class Thread;
typedef unsigned long StackSize;
typedef unsigned int Time; // time, x 55ms
typedef int ID;

Time const mainTimeSlice = 3;
StackSize const maximumStackSize = 65536;

enum Flag {
	FINISHED, TO_START, READY, BLOCKED, BUSYWAIT, SIGNAL
};

class PCB {

public:

	friend class Thread;
	friend void interrupt stack_fork();
	PCB(StackSize stacksize, Time timesl, Thread* myT);
	PCB();
	~PCB();

	ID getID();
	static ID getRunningID();
	static void exitPCB();
	static void waitForForkChildrenPCB();
	void startPCB();
	void waitToCompletePCB();
	static Thread* getThreadbyID(ID toFind);
	static ID newID;
	static PCBList* process_list;
	static PCB* busyWaitPCB;
	unsigned ss, sp, bp;
	Time timeslice;
	Flag flag;

private:

	unsigned *stack;
	ID pcbID;
	Thread* myThread;
	PCBList* waiting;
	PCB* parent;
	StackSize stackSize;

	static void wrappper();
	static void busyWait();
	static void freeWaiting();
	void deletePCB();
	PCB(void (*body)(), Flag startFlag);

};

#endif /* H_PCB_H_ */
