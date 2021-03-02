#include "path.h"

Path::Path()
{
	char* path = getenv("PATH");

	std::string directory = "";
	char c;
	while ((c = *path++) != NULL)
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
		struct dirent* entry;
		while ((entry = readdir(directory)) != NULL)
		{
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