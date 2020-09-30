#ifndef _COMMANDS_H_
#define _COMMANDS_H_ 


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
void jobs(vector<int> *pTable);
void command(vector<int> *pTable, char* cmds[],int x);
void printTime();
#endif