/*
 * KSem.h
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#ifndef H_KSEM_H_
#define H_KSEM_H_

class Semaphore;
typedef unsigned int Time;
class KSemList;
class PCBTList;

class KernelSem{

public:

	KernelSem(int init);
	~KernelSem();

	int wait(Time maxTimeToWait);
	void signal();
	void TickTheBlocked();

	int val () const;

	static KSemList* sem_list;
	static void TickTheKSem();

private:

	PCBTList* blocked_list;
	int value;
};


#endif /* H_KSEM_H_ */
