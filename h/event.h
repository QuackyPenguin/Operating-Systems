/*
 * event.h
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#ifndef H_EVENT_H_
#define H_EVENT_H_

typedef unsigned char IVTNo;
class KernelEv;

class Event {
public:
	Event(IVTNo ivtno);
	~Event();

	void wait();

protected:
	friend class KernelEv;
	void signal(); // can call KernelEv

private:
	KernelEv* myImpl;
};

#include "ivtentry.h"

#endif /* H_EVENT_H_ */
