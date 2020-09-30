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

using namespace std;

const int LINE_LENGHT = 100; 
const int MAX_ARGS = 7;
const int MAX_LENGTH = 20;
const int MAX_PT_ENTRIES = 32;

int main(){

	char input[LINE_LENGHT];
	char* args[MAX_ARGS+1];
	
	bool loop = true;
	//input loop 
	while (loop){

		printf("shell379: ");
		cin.getline(input, sizeof(input));
		char* arg = strtok(input, " \t\n");


		int x = 0;
		

		while (arg != NULL){
			arg = strtok(NULL, " \t\n");
			printf("%s\n", arg);
			args[x] = arg;
			x++;
		}
		if (strcmp(arg, "exit") == 0){
			loop = false;

		}		
	}
	
}

