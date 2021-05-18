/*
  Filename:    daemonRun.cc
  Date:        4/17/2020
  Author:      Michael Boyd
  Email:       mnb170030@utdallas.edu
  Version:     1.8
  Copyright:   2020, All Rights Reserved

  Description:
 Starts a daemon and handles signals that come via the cmd line.
 */

#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "program5.h"

#define GetCurrentDir getcwd

using namespace std;

void daemonRun();
void signalHandle(int sig);

int pidFilehandle;
string cDir;

void daemonRun()
{

  int pid;
  int i;
  int check;

  string q = "Joker";

  char str[10];
  const char *rundir = "./";
  const char *pidfile = "./cs3377dirmond.pid";
  const char* versions;
  char buff[FILENAME_MAX];
  GetCurrentDir(buff, FILENAME_MAX);
  cDir = buff;
  cDir = cDir + "/.versions/";
  //cout << cDir << endl;
  versions = cDir.c_str();

  if(getppid() == 1)
    return;
  else;

  logFunc(q, 2);
  pid = fork();

  if(pid < 0)
    {
      logFunc(q, 3);
      return;
    }
  else if(pid > 0)
    {
      std::cout << "Child created, PID: " <<  pid << std::endl;
      return;
    }
  else;
  umask(027);

  i = open("/dev/null", O_RDWR);
  dup(i);
  dup(i);

  chdir(rundir);

  logFunc(q, 4);
  pidFilehandle = open(pidfile, O_RDWR|O_CREAT, 0600);
  if(pidFilehandle == -1)
    {
      logFunc(q, 5);
      return;
    }

  check = mkdir(versions, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  if(check == -1)
    logFunc(q, 21);
  else
    logFunc(q, 20);

  sprintf(str, "%d\n", getpid());
  write(pidFilehandle, str, strlen(str));

  logFunc(q, 6);
  inotifyFunc();
      
  logFunc(q, 7);
  close(pidFilehandle);
  if(remove("cs3377dirmond.pid") != 0)
    logFunc(q, 8);
  else;
    

}
