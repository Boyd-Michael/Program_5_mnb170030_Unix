/*
  Filename:   inotifyFunc.cc
  Date:       4/18/2020
  Author:     Michael Boyd
  Email:      mnb170030@utdallas.edu
  Version:    1.8
  Copyright:  2020, All Rights Reserved

  Description:
 Watches a directory for any modification in the directory.
*/
#include <iostream>
#include <stdio.h>
#include <rude/config.h>
#include <fstream>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <limits.h>
#include <unistd.h>
#include "program5.h"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024*(EVENT_SIZE + 16))

using namespace std;

int fd = 10;
int wd = 10;
extern int pidFilehandle;
extern string cDir;
extern const char* wDirVal;

void checkSignal();
void signalHand(int sig);
int get_event(int x);

int get_event(int x)
{
  char buffer[BUF_LEN];
  int length = 0;
  int i = 0;
  string fileName;
  string D = "%m.%d.%y.%H:%M:%S";
  string Date = ".$(date +"+D+")";
  string oLocation = configFile(2);
  //string nLocation = "~/.versions/";
  string nFileName;
  string commandS;
  string j = "Joker";
  const char* cmd;


  length = read(x, buffer, BUF_LEN);
  if(length < 0)
    logFunc(j, 16);
 
 while(i < length)
    {
      struct inotify_event *event = (struct inotify_event *) &buffer[i];
      if(event->len)
	{
	  if(event->mask & IN_MODIFY)
	    {
	      if(event->mask & IN_ISDIR)
		{
		  logFunc(j, 15);
		  fileName = event->name;
		  logFunc(fileName, 1);
		}
	      else
		{
		  logFunc(j, 15);
		  fileName = event->name;
		  logFunc(fileName, 1);
		  nFileName = cDir+fileName+Date;
		  commandS = "cp "+oLocation+fileName+" "+nFileName;
		  cmd = commandS.c_str();
		  system(cmd);
		}
	    }
	  i += EVENT_SIZE + event->len;
	}
    }
 return 0;
}

int inotifyFunc()
{
  int fd;
  int wd;  
  const char* wDir = wDirVal;
  string j = "Joker";

  fd = inotify_init();
  if(fd < 0)
    logFunc(j, 9);

  logFunc(j, 10);
  wd = inotify_add_watch(fd, wDir, IN_MODIFY);
  if(wd == -1)
    logFunc(j, 11);

  checkSignal();

  logFunc(j, 14);
  while(1)
    get_event(fd);
 

  logFunc(j, 12);
  inotify_rm_watch(fd, wd);
  close(fd);

  return 0;
}

void checkSignal()
{
  string j = "Joker";
  logFunc(j, 13);

  signal(SIGHUP, signalHand);
  signal(SIGINT, signalHand);
  signal(SIGTERM, signalHand);
}

void signalHand(int sig)
{
  string j = "Joker";

  switch(sig)
    {
    case SIGHUP:
      logFunc(j, 18);
      configFile(4);
      logFunc(j, 19);
      break;
    case SIGINT:
    case SIGTERM:
      inotify_rm_watch(fd, wd);
      close(fd);
      close(pidFilehandle);
      logFunc(j, 17);
      if(remove("cs3377dirmond.pid") != 0)
	perror("Error: PID removal failed.\n");
      exit(EXIT_SUCCESS);
      break;
    default:
      perror("Error: signalHandle, inotify\n");
    }
}
