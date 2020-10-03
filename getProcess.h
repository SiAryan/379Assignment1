#ifndef _EXIT_H
#define _EXIT_H

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
void time();
int killZombie(int pid);
int processInfo(int pid);
#endif
