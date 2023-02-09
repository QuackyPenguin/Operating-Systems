/*
 * main.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#include "declare.h"
#include "thread.h"

static int argumentNo, ret;
static char** arguments;

class UserThread:public Thread{
public:
	UserThread():Thread(){}
	~UserThread(){waitToComplete();}

	Thread* clone() const { return new UserThread();}

protected:
	void run(){
		ret = userMain(argumentNo, arguments);
	}
};

int main(int argc, char **argv) {

	argumentNo=argc;
	arguments=argv;
	startProgram();

	UserThread* exe=new UserThread();
	exe->start();
	exe->waitToComplete();


	endProgram();

	return ret;
}

