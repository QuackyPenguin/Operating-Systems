/*
 * declare.h
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#ifndef H_DECLARE_H_
#define H_DECLARE_H_

#define lock() asm cli
#define unlock() asm sti

void tick();
void startProgram();
void endProgram();
int syncPrintf(const char *format, ...);
int userMain(int argc, char** argv);
void dispatch();
void interrupt stack_fork();



#endif /* H_DECLARE_H_ */
