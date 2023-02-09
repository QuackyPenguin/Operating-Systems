/*
 * semaphor.h
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#ifndef H_SEMAPHOR_H_
#define H_SEMAPHOR_H_

typedef unsigned int Time;

class KernelSem;

class Semaphore{
public:
	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual int wait(Time maxTimeToWait);
	virtual void signal();

	int val() const;

private:
	KernelSem* myImpl;
};



#endif /* H_SEMAPHOR_H_ */
