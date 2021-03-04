/*
* path.h
*
* Reads in the PATH environment variable and provides easy access to the individual directories.
*
* Author: David Reidsma
* Date: 3/2/2021
*/

#ifndef __CS232_PATH_H__
#define __CS232_PATH_H__

#include <string>
#include <vector>

class Path
{
public:
	Path();
	int find(const std::string& program) const;
	std::string getDirectory(int i) const;
private:
	std::vector<std::string> pathDirectories;
};

#endif
