#pragma once

#include <unistd.h>
#include <sys/wait.h>
#include "path.h"

class Shell
{
public:
	void run();
private:
	Path path;
};

