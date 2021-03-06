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
#include "getProcess.h"
using namespace std;


void jobs(vector<int> *pTable){
	printf("%s\n", "Running Processes:");
	int num_jobs = 0;

	for (int i = 0; i < pTable->size(); i++){
		int w = kill((*pTable)[i], 0);
		
		if (w==0){
			int x = killZombie((*pTable)[i]);
			num_jobs = (x == 1) ? 1 + num_jobs : num_jobs; 	
		}
	}
	
	if (num_jobs > 0){
		printf("%s\n", "#    PID S SEC COMMAND");
		for (int i = 0; i < pTable->size(); i++){
			int w = kill((*pTable)[i],0);
			if (w==0){
				processInfo((*pTable)[i]);
			}else if (w == ESRCH){
				pTable->erase(pTable->begin() + i);
			}else{
				//printf("%s\n", "pipe info error\n");
			}
		}
	}
	

	//printf("%d\n",num_jobs);
	printf("Processes =     %d active\n", num_jobs);
	time();
}

void sleepProcess(char *cmds[]){
	sleep(stoi(cmds[1]));
}

void suspendProcess(char *cmds[]){
	kill(stoi(cmds[1]), SIGSTOP);
}

void resumeProcess(char *cmds[]){
	kill(stoi(cmds[1]), SIGCONT);
}

void waitProcess(char *cmds[]){
	waitpid(stoi(cmds[1]), NULL, 0);
}

void killProcess(char *cmds[]){
	kill(stoi(cmds[1]) ,SIGKILL);
}


void command(vector<int> *pTable, char* cmds[],int x){
	int wstatus;
	pid_t waitfornew;

	//int stime;
	//int utime;

				
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
			
			do {waitfornew = waitpid(new_pid, &wstatus, WUNTRACED);}
			while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
			pTable->pop_back();
		
		} 
	}
		
	else if (new_pid < 0){
		perror("Forking error!");
	}
	//printf("%s\n", "shell379: ");	

}

void exitshell(vector<int> *pTable){
	int wstatus;
	pid_t waitfornew;
	for(int i = 0; i < pTable->size(); i++){
		int w = kill((*pTable)[i],0);
		if (w == 0){
			do {waitfornew = waitpid((*pTable)[i], &wstatus, WUNTRACED);}
			while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
			
		}else if (w == ESRCH){
			pTable->erase(pTable->begin() + i);
		}
		else{
			//printf("%s\n", "error");
			kill((*pTable)[i], SIGKILL);
		}
	}	
	exit(0);
}
