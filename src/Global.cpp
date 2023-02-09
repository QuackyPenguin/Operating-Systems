/*
 * Global.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#include "pcb.h"
#include "Global.h"

volatile PCB* Global::running=0;
PCB* Global::main=new PCB();
volatile int Global::lockFlag=1;
volatile int Global::change_context=0;
Time Global::counter=0;
PCB* Global::forkChild=0;
