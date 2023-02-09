/*
 * semaphor.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#include "KSem.h"
#include "semaphor.h"

Semaphore::Semaphore(int init)
{
	myImpl=new KernelSem(init);
}

Semaphore::~Semaphore(){
	if(myImpl) {
		delete myImpl;
		myImpl=0;
	}
}

void Semaphore::signal()
{
	myImpl->signal();
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::val() const {
	return myImpl->val();
}
