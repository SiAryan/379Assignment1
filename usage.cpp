#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {  
  pid_t pid = fork();    
  if (!pid) { // child
    	int x = 0; 
    	for (int i = 0; i < 1000000000; i ++){
    		x += i;
    	} // do some work here       
     	_exit(0);
    } else { // parent      
    	wait(NULL); // wait for child 
   	}  
/*
    struct rusage usage;    
    getrusage(RUSAGE_CHILDREN, &usage);    
    printf("system time: %d microseconds\n", usage.ru_stime.tv_usec);    
    printf("user time: %ld seconds\n", usage.ru_utime.tv_sec); 
    return 0;
	*/
}