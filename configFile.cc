/*
  Filename:   configFile.cc
  Date:       4/17/2020
  Author:     Michael Boyd
  Email:      mnb170030@utdallas.edu
  Version     1.3
  CopyRight:  2020, All Rights Reserved

  Description:
 Opens cs3377dirmond.conf file and reads the three parameters
that are needed.
 */

#include <iostream>
#include <rude/config.h>
#include <string.h>
#include "program5.h"

using namespace std;
using namespace rude;

bool Verb;
const char* logVal;
const char* wDirVal;

string configFile(int state)
{
  Config config;
  //const char *logVal;
  //const char *wDirVal;
  string rtrnVal;
  //bool Verb;
  enum info{VERBOSE, LOGFILE, WATCHDIR, ALL, UPDATE};

  config.load("cs3377dirmond.conf");
  config.setSection("Parameters");

  switch(state)
    {
    case VERBOSE:
      Verb = config.getBoolValue("Verbose");
      config.save("cs3377dirmond.conf");
      if(Verb == true)
	return "t";
      else
	return "f";
      break;
    case LOGFILE:
      logVal = config.getStringValue("LogFile");      
      config.save("cs3377dirmond.conf");
      rtrnVal = logVal;
      return rtrnVal;
      break;
    case WATCHDIR:
      wDirVal = strdup(config.getStringValue("WatchDir"));
      config.save("cs3377dirmond.conf");
      rtrnVal = wDirVal;
      return rtrnVal;
      break;
    case ALL:
      Verb = config.getBoolValue("Verbose");
      logVal = config.getStringValue("LogFile");
      wDirVal = strdup(config.getStringValue("WatchDir"));
      config.save("cs3377dirmond.conf");
      return logVal;
      break;
    case UPDATE:
      Verb = config.getBoolValue("Verbose");
      logVal = config.getStringValue("LogFile");
      config.save("cs3377dirmond.conf");
      return logVal;
      break;
    }
  return "ERROR";
}
