/*
  Filename:    program5.cc
  Date:        4/17/2020
  Author:      Michael Boyd
  Email:       mnb170030@utdallas.edu
  Version:     1.2
  Copyright:   2020, All Rights Reserved

  Description: 
 Main function locations, the starting point of Assignment 5
Where tclaps handles arguments.
 */

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <stdlib.h>
#include <tclap/CmdLine.h>
#include <tclap/SwitchArg.h>
#include <tclap/ValueArg.h>
#include <tclap/UnlabeledValueArg.h>
#include <rude/config.h>
#include "program5.h"

using namespace std;
using namespace rude;

int main(int argc, char* argv[])
{

  //createing variables
  map<int, std::string> dOption;
  enum list {DAEMON, INFILE};
  ifstream inputFile;
  Config config;

  
  //TCLAP
  //Command Line
  TCLAP::CmdLine cmd("CS3377.501 Program 5", ' ', "1.0");
 
  //Switch Arguments
  //Daemon
  TCLAP::SwitchArg dSwitch("d", "daemon", "Run in daemon mode(forks to run as a daemon)", cmd, false);

  //Unlabeled Arguments
  //Infile
  TCLAP::UnlabeledValueArg<std::string> infile("infile", "The name of the configuration file. Deafults to cs3377dirmond.conf", false, "cs3377dirmond.conf", "configuration filename", false);

  
  cmd.add(infile);
  cmd.parse(argc, argv);

  //Gaining bool statement
  bool daemonBool = dSwitch.getValue();
  
  //Mapping
  if(daemonBool)
    //if -d, --daemon was choosen
    dOption[DAEMON] = "1";
  else
    //if no Switch Arg was choosen
    dOption[DAEMON] = "0";
  dOption[INFILE] = infile.getValue();

  //Opening File
  inputFile.open(dOption[INFILE].c_str(), std::ios::in);

  configFile(3);

  if(daemonBool)
    daemonRun();
  else
    cerr << "Error: no arguments, use ./prog5 -h for further information.\n";

  return 0;

}
