#include <iostream>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <regex>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <sys/resource.h>
#include <cstring>

#include "commands.h"

using namespace std;

void jobs(vector<int> *ptable){
	printf("%s\n", "Running Processes:");

}


void command(vector<int> *pTable, char* cmds[]){
	int new_pid = fork();
	if (new_pid == 0){
		//child
		execvp(cmds[0], cmds);
	}
	else if (new_pid > 0){
		//parent
		pTable->push_back(new_pid);
	}

}

