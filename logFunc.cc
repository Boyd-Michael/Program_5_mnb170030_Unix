/*
  Filename:  logFunc.cc
  Date:      4/18/2020
  Author:    Michael Boyd
  Email:     mnb170030@utdallas.edu
  Version:   1.1
  Copyright: 2020, All Rights Reserved

  Description:
 logs information from inotify.
 */
#include <iostream>
#include <ios>
#include <stdio.h>
#include <string.h>
#include <rude/config.h>
#include <fstream>
#include "program5.h"

using namespace std;

extern bool Verb;
extern const char* logVal;

void logFunc(string name, int state)
{
  string str;

  ofstream logFile(logVal, ofstream::app | ofstream::out);

  if(logFile.is_open())
    cout << "Good\n";
  else
    cout << "NOPE\n";

  if(Verb)
    {
      switch(state)
	{
	case 1:
	  str = " was modified.\n";
	  break;
	case 2:
	  str = "Creating Daemon\n";
	  break;
	case 3:
	  str = "Error: Creation of fork() failed\n";
	  break;
	case 4:
	  str = "Creating PID file\n";
	  break;
	case 5:
	  str = "Error: Creation of PID file failed\n";
	  break;
	case 6:
	  str = "Starting Inotify Function\n";
	  break;
	case 7:
	  str = "Closing and removing PID File\n";
	  break;
	case 8:
	  str = "Error: Deleting PID File has failed\n";
	  break;
	case 9:
	  str = "Error: Initiliazing Inotiyfy failed\n";
	  break;
	case 10:
	  str = "Startng Watch List\n";
	  break;
	case 11:
	  str = "Error: Watch List, Failed to add directory: ";
	  break;
	case 12:
	  str = "Closing and removing Watch list and inotify\n";
	  break;
	case 13:
	  str = "Checking Signals\n";
	  break;
	case 14:
	  str = "Starting watch for events.\n";
	  break;
	case 15:
	  str = "Logging Modifications made\n";
	  break;
	case 16:
	  str = "Error: Read Failed\n";
	  break;
	case 17:
	  str = "Shutting Down Program\n\t\tClosing Watch List down\n\t\tClosing PID File\n\t\tRemoving PID File\nPROGRAM HAS ENDED!";
	  break;
	case 18:
	  str = "Checking Configuration File\n";
	  break;
	case 19:
	  str = "Configuration Complete!\n";
	  break;
	case 20:
	  str = ".versions Directory was created.\n";
	  break;
	case 21:
	  str = "Directory was found or unable to be created.\n";
	default:
	  str = "Error: Logging Function.\n";
	}
      if(state == 1)
	logFile << name << str;
      else
	logFile << "\t" << str;
    }
  else;
  logFile.close();
  return;
}

