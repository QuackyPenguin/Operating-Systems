/*
 * controle.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#include "Global.h"
#include "pcb.h"
#include "SCHEDULE.H"
#include "declare.h"
#include "PCBList.h"
#include "KSem.h"
#include "KSemList.h"
#include <DOS.H>
#include <STRING.H>

void init();
void restore();

void startProgram() {
	Global::running = Global::main;

	init();
}

void endProgram() {

	delete Global::main;
	delete PCB::busyWaitPCB;
	delete PCB::processes_list;
	delete KernelSem::sem_list;

	restore();
}

int tss, tsp, tbp;

void interrupt timer() {	// prekidna rutina

	if (Global::change_context == 0) {
		Global::counter--;
		asm int 60h
		tick();
		KernelSem::TickTheKSem();
	}

	if ((Global::counter == 0 && ((PCB*) Global::running)->timeslice != 0)
			|| Global::change_context == 1) {
		if (Global::lockFlag > 0) {

			Global::change_context = 0;
		asm {
			//uzima registre
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
		//cuva kontekst
		((PCB*) Global::running)->sp = tsp;
		((PCB*) Global::running)->ss = tss;
		((PCB*) Global::running)->bp = tbp;

		if (((PCB*) Global::running)->flag == READY)
			Scheduler::put(((PCB*) Global::running));

		if (((PCB*) Global::running = Scheduler::get()) == 0)
			(PCB*) Global::running = PCB::busyWaitPCB;

		//postavljanje konteksta
		tbp = ((PCB*) Global::running)->bp;
		tsp = ((PCB*) Global::running)->sp;
		tss = ((PCB*) Global::running)->ss;

		Global::counter = ((PCB*) Global::running)->timeslice;

	asm {
		//vracanje registara
		mov bp, tbp
		mov sp, tsp
		mov ss, tss
	}
}
else {
	Global::change_context = 1;
}
}
}

void dispatch() { // sinhrona promena konteksta
lock();
Global::change_context = 1;
timer();
unlock();
}

unsigned oldTimerOFF, oldTimerSEG; // stara prekidna rutina

// postavlja novu prekidnu rutinu
void init() {
asm {
cli
push es
push ax

mov ax,0   //  ; inicijalizuje rutinu za tajmer
mov es,ax

mov ax, word ptr es:0022h//; pamti staru rutinu
mov word ptr oldTimerSEG, ax
mov ax, word ptr es:0020h
mov word ptr oldTimerOFF, ax

mov word ptr es:0022h, seg timer//postavlja
mov word ptr es:0020h, offset timer//novu rutinu

mov ax, oldTimerSEG//	postavlja staru rutinu
mov word ptr es:0182h, ax//; na int 60h
mov ax, oldTimerOFF
mov word ptr es:0180h, ax

pop ax
pop es
sti
}
}

// vraca staru prekidnu rutinu
void restore() {
asm {
cli
push es
push ax

mov ax,0
mov es,ax

mov ax, word ptr oldTimerSEG
mov word ptr es:0022h, ax
mov ax, word ptr oldTimerOFF
mov word ptr es:0020h, ax

pop ax
pop es
sti
}
}
static unsigned *tmpbp;
static unsigned x;
void interrupt stack_fork() {


memcpy(Global::forkChild->stack, Global::running->stack, Global::forkChild->stackSize*sizeof(unsigned));
#ifndef BCC_BLOCK_IGNORE
x=(unsigned)(Global::forkChild->stack)-(unsigned)(((PCB*)Global::running)->stack);
tmpbp=(unsigned*)MK_FP(_SS, _SP);
Global::forkChild->sp=_SP+FP_OFF(Global::forkChild->stack)-FP_OFF(((PCB*)Global::running)->stack);
#endif

while (*tmpbp != 0) {
*(tmpbp + x) = (*tmpbp) + x;
#ifndef BCC_BLOCK_IGNORE
tmpbp=(unsigned *)MK_FP(_SS, *tmpbp);
#endif
}
static int i, j;
Scheduler::put(Global::forkChild);

Global::lockFlag++;
}
