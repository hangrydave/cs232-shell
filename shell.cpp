/*
* shell.cpp
* 
* Provides functionality to run commands from a terminal.
* 
* Author: David Reidsma
* Date: 3/3/2021
*/

#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

Shell::Shell(char** envp)
{
	homeDirectory = getenv("HOME");
	this->envp = envp;
}

Shell::~Shell()
{
	delete envp;
	delete homeDirectory;
}

void Shell::printPrompt()
{
	prompt.set();
	cout << prompt.get() << flush;
}

void Shell::forkProcess(const char* commandPath, const char* command, char* const* args, const bool runAsync)
{
	pid_t pid = fork();
	switch (pid)
	{
	case -1: // fork failure
		perror("fork");
	case 0: // child process
		execve(commandPath, args, envp);
		perror(command);
	default: // parent process
		if (runAsync)
			break;

		// we're running synchronously; wait for the process to finish
		int status;
		pid_t wait = waitpid(pid, &status, 0);
		if (wait < 0)
		{
			perror("waitpid");
		}
	}
}

void Shell::cd(char* const* args, const int argCount)
{
	const char* dir;
	if (argCount == 1)
	{
		dir = homeDirectory;
	}
	else
	{
		dir = args[1];
		if (dir[0] == '~')
		{
			// Replace the tilde with the home directory
			string expanded = dir;
			expanded = homeDirectory + expanded.substr(1, expanded.size() - 1);
			dir = expanded.c_str();
		}
	}
	
	int result = chdir(dir);
	if (result == -1)
		perror("cd");
}

void Shell::exit()
{
	std::exit(0);
}

bool Shell::tryPredefinedCommands(const char* command, char* const* args, const int argCount)
{
	if (strcmp(command, "cd") == 0)
	{
		cd(args, argCount);
		return true;
	}
	else if (strcmp(command, "exit") == 0)
	{
		exit();
		return true;
	}
	return false;
}

void Shell::readAndExecuteCommand()
{
	CommandLine commandLine(cin);
	char* command = commandLine.getCommand();
	int dirIndex = path.find(command);
	if (dirIndex == -1)
	{
		/// If the command isn't in the path, try running the shell-defined commands
		if (!tryPredefinedCommands(command, commandLine.getArgVector(), commandLine.getArgCount()))
		{
			cout << command << ": command not found" << endl;
		}
	}
	else
	{
		string commandPath = path.getDirectory(dirIndex) + '/' + command;
		forkProcess(commandPath.c_str(), command, commandLine.getArgVector(), !commandLine.noAmpersand());
	}
}

void Shell::run()
{
	cout << flush;
	while (true)
	{
		printPrompt();
		readAndExecuteCommand();
	}
}