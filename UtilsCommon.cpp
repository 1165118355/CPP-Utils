#include "UtilsCommon.h"
#include "UtilsString.h"
#pragma warning(disable:4996)

#include <fstream>
#if defined(_WIN32)
#include <io.h>   
#include <direct.h>
#endif

#if defined(_WIN32)
bool UtilsCommon::isDir(const char * path)
{
	return _access(path, 0) != -1;
}

bool UtilsCommon::createDir(const char * path, bool makeParent)
{
	std::string stdPath = path;
	if (!isDir(stdPath.c_str()))
	{
        std::string parentPath = UtilsString::backupPath(stdPath.c_str());
		if (!createDir(parentPath.c_str(), true))
		{
			return false;
		}
	}
    mkdir(path);
    return true;
}

bool UtilsCommon::isFile(const char * path)
{
	std::fstream reader;
	reader.open(path);
	bool isOpen = reader.is_open();
	if (isOpen)
	{
		reader.close();
	}
	return isOpen;
}
#endif
