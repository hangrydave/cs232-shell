/*
* path.cpp
*
* Reads in the PATH environment variable and provides easy access to the individual directories.
*
* Author: David Reidsma
* Date: 3/2/2021
*/

#include "path.h"
#include <dirent.h>

Path::Path()
{
	char* path = getenv("PATH");

	std::string directory = "";
	char c;
	while ((c = *path++) != '\0')
	{
		if (c == ':')
		{
			pathDirectories.push_back(directory);
			directory.clear();
		}
		else
		{
			directory += c;
		}
	}

	find("diff");
}

int Path::find(const std::string& program) const
{
	for (int i = 0; i < pathDirectories.size(); i++)
	{
		DIR* directory = opendir(pathDirectories[i].c_str());
		if (directory == NULL) // If the directory doesn't exist, ignore it
		    continue;

		struct dirent* entry;
		while ((entry = readdir(directory)) != NULL)
		{
			// Read the contents of every directory until we find the file
			if (program.compare(entry->d_name) == 0)
			{
				return i;
			}
		}
	}
	return -1;
}

std::string Path::getDirectory(int i) const
{
	return pathDirectories[i];
}