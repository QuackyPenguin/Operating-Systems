/*
 * event.cpp
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#include "event.h"
#include "kernelev.h"

Event::Event(IVTNo ivtno):myImpl(0){
	myImpl=new KernelEv(ivtno);
}

Event::~Event(){
	delete myImpl;
}

void Event::signal(){

}

void Event::wait(){
	myImpl->wait();
}
