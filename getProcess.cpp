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

regex pat{ "(\\d+:   \\d+ Z )" };

void time(){
	struct rusage usage;
	getrusage(RUSAGE_CHILDREN, &usage);
	printf("%s\n", "Completed processes:");
	printf("User time =     %ld seconds\n", usage.ru_utime.tv_sec);
	printf("Sys  time =     %ld seconds\n", usage.ru_stime.tv_sec);
	//printf("%s\n", "check");
}

int killZombie(int pid){

	FILE * file;
	int w;

	string spid = to_string(pid);
	string out;

	string argv =  "ps -p " + spid + " -o sched=#,pid,s,cputime=SEC,command | awk -F'[: ]+' '/:/ {t=d$4+60*(d$5+60*d$6); printf (\"%s:   %s %s   %s %s\",d$2,d$3,d$4,t,d$8)}'";
	int len = argv.length();

	char ch[len + 1];

	strcpy(ch, argv.c_str());

	if ((file = popen(ch, "r")) == NULL){
		perror("Pipe error\n");
	}else{
		while((w = fgetc(file)) != EOF){
			out += (char)w;
		}
	}

	bool match = regex_search(out, pat);
	if (match){
		waitpid(pid, NULL, 0);
		return 0;
	} else {

	}	


	if (pclose(file)){
		perror("Pipe error\n");
	}

	printf("\n");
	return 1;
} 


int processInfo(int pid){

	FILE * file;
	int w;

	string spid = to_string(pid);
	string out;

	string argv =  "ps -p " + spid + " -o sched=#,pid,s,cputime=SEC,command | awk -F'[: ]+' '/:/ {t=d$4+60*(d$5+60*d$6); printf (\"%s:   %s %s   %s %s\",d$2,d$3,d$4,t,d$8)}'";
	int len = argv.length();

	char ch[len + 1];

	strcpy(ch, argv.c_str());

	if ((file = popen(ch, "r")) == NULL){
		perror("Pipe error\n");
	}else{
		while((w = fgetc(file)) != EOF){
			out += (char)w;
		}
	}
	cout << out << ends;
	
	if (pclose(file)){
		perror("Pipe error\n");
	}

	printf("\n");
	return 1;

}