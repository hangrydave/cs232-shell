/*
* shell.h
*
* Provides functionality to run commands from a terminal.
*
* Author: David Reidsma
* Date: 3/3/2021
*/

#ifndef __CS232_SHELL_H__
#define __CS232_SHELL_H__

#include "path.h"
#include "commandline.h"
#include "prompt.h"

class Shell
{
public:
	Shell(char** envp);
	~Shell();
	void run();
private:
	char** envp;
	Path path;
	Prompt prompt;
	char* homeDirectory;
	void printPrompt();
	void readAndExecuteCommand();
	bool tryPredefinedCommands(const char* command, char* const* args, const int argCount);
	void cd(char* const* args, const int argCount);
	void exit();
	void forkProcess(const char* commandPath, const char* command, char* const* args, const bool runAsync);
};

#endif
