#pragma once

#include <string>
#include <vector>
#include <dirent.h>
#include <stdlib.h>
#include <iostream>

class Path
{
public:
	Path();
	int find(const std::string& program) const;
	std::string getDirectory(int i) const;
private:
	std::vector<std::string> pathDirectories;
};

