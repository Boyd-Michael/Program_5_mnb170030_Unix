/*
  Filename:    program5.h
  Date:        4/17/2020
  Author:      Michael Boyd
  Email:       mnb170030@utdallas.edu
  Version:     1.0
  Copyright:   2020, All Rights Reserved

  Description:
 The Header file

 */

#include <string>

void daemonRun();

std::string configFile(int state);

void logFunc(std::string name, int state);

int get_event(int x);
int inotifyFunc();

