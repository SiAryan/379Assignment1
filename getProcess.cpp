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

void time(){
	struct rusage usage;
	getrusage(RUSAGE_CHILDREN, &usage);
	printf("%s\n", "Completed processes:");
	printf("User time =     %ld seconds\n", usage.ru_utime.tv_sec);
	printf("Sys  time =     %ld seconds\n", usage.ru_stime.tv_sec);
	//printf("%s\n", "check");
}

