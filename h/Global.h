/*
 * Global.h
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#ifndef H_GLOBAL_H_
#define H_GLOBAL_H_

class PCB;
typedef unsigned int Time;

class Global{

public:

	static volatile PCB* running;
	static PCB* main;
	static volatile int lockFlag;
	static volatile int change_context;
	static Time counter;
	static PCB* forkChild;
};



#endif /* H_GLOBAL_H_ */
