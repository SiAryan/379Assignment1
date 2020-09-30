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

void jobs(vector<int> *pTable){
	printf("%s\n", "Running Processes:");
	int num_jobs = 0;

	for (int i = 0; i < pTable->size(); i++){
		num_jobs = (kill((*pTable)[i], 0) == 0) ? num_jobs++ : num_jobs; 

	}

	printf("Processes =     %d active\n", num_jobs);
	printTime();
}

void printTime(){
	struct rusage rusage;
	int who = RUSAGE_CHILDREN;
	getrusage(who, &rusage);
	printf("%s\n", "Completed processes:");
	printf("User time =     %ld seconds\n", rusage.ru_utime.tv_sec);
	printf("Sys  time =     %ld seconds\n", rusage.ru_stime.tv_sec);
}


void command(vector<int> *pTable, char* cmds[],int x){
	int wstatus;
	pid_t waitNewProcess;
				
	int new_pid = fork();
	if (new_pid == 0){
		//child
		execvp(cmds[0], cmds);	
	}
	else if (new_pid > 0){
		//parent
		pTable->push_back(new_pid);
		if (strcmp(cmds[x-1], "&") == 0){

		} else {
			
			do{
				//waitpid(pid_t pid, int *wwstatus, int options)
				waitNewProcess = waitpid(new_pid, &wstatus, WUNTRACED);
			}while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));

			pTable->pop_back();
		}
	} else if (new_pid < 0){
		perror("An error has occured when attempting to fork.");
	}

}

