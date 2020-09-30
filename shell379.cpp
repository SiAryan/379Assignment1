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

const int LINE_LENGHT = 100; 
const int MAX_ARGS = 7;
const int MAX_LENGTH = 20;
const int MAX_PT_ENTRIES = 32;

char input[LINE_LENGHT];
char* cmds[MAX_ARGS + 1];

int main(){

	vector<int> *pTable = new vector<int>;
	bool loop = true;
	//input loop 
	while (loop) {
		//clear command array 
		memset(cmds, 0, sizeof(cmds));
		printf("shell379: ");
		//get input 
		cin.getline(input, sizeof(input));

		//parse input into an array of commands
		char* token = strtok(input, " \t\n");


		int x = 0;
		while (token != NULL){
			//printf("%s\n", token);
			cmds[x++] = token;
			token = strtok(NULL, " \t\n");
		}
		
		cmds[x] = NULL;
		
		if (cmds[0] != NULL){
			if (strcmp(cmds[0],"jobs") == 0){
				//printf("%s\n", cmds[0]);
				jobs(pTable);
			}
			else {
				command(pTable, cmds, x);	
			}
		}
	
	}


}

