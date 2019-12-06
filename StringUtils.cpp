#include "StringUtils.h"

std::string StringUtils::basename(const char *string, bool isRejectSuffix)
{
    std::string str = string;
    if(str.empty())
    {
        return str;
    }
    int posStart=0;
    int posEnd=str.size();
    for(int i=str.size()-1; i >=0; --i)
    {
        if(0 == posStart && (str[i] == '/' || str[i] == '\\') && i != str.size() - 1)
        {
            posStart = i+1;
        }
        if(isRejectSuffix && str.size() == posEnd && str[i] == '.')
        {
            posEnd = i;
        }
    }
    int offsetSize = posEnd - posStart;
    return str.substr(posStart, offsetSize);
}

std::string StringUtils::dirname(const char *string)
{
    std::string str = string;
    if(str.empty())
    {
        return str;
    }
    int posStart=0;
    int posEnd=str.size();
    for(int i=str.size()-1; i >=0; --i)
    {
        if(posEnd == str.size() && i != str.size()-1 && (str[i] == '/' || str[i] == '\\'))
        {
            posEnd = i;
        }
    }
    int offsetSize = posEnd - posStart;
    if(posEnd == str.size())
    {
        offsetSize = 0;
    }
    std::string outputDir = str.substr(posStart, offsetSize);
    outputDir = checkDir(outputDir.c_str());
    return outputDir;
}

std::string StringUtils::getSuffix(const char *string, const char *suffix)
{
    std::string stdString = string;
    int pos = stdString.find_last_of(suffix);
    if(pos == stdString.npos)
    {
        return std::string("");
    }
    return stdString.substr(pos);
}

std::string StringUtils::backupPath(const char *string, bool inverse)
{
    std::string str = string;
    int startPos = 0;
    int endPos = str.size();
    if(!inverse)
    {
        for(int i=str.size()-1; i>=0; --i)
        {
            if((str[i] == '\\' || str[i] == '/') && str.size()-1 != i)
            {
                endPos = i;
                break;
            }
        }
    }
    else
    {
        for(int i=0; i<str.size(); ++i)
        {
            if((str[i] == '\\' || str[i] == '/') && 0 != i)
            {
                startPos = i+1;
                break;
            }
        }
    }
    return str.substr(startPos, endPos - startPos);
}

std::string StringUtils::rejectPath(const char *srcString, const char *absolutePath)
{
    std::string stdPath = srcString;
    for(int i=0; i<stdPath.size(); ++i)
    {
        if(stdPath[i] == '\\')
        {
            stdPath[i] = '/';
        }
    }
    int pos = stdPath.find(absolutePath);
    std::string stdAbsolutePath = absolutePath;
    if(pos == std::string::npos)
    {
        return stdPath;
    }
    int dataPathLength = stdAbsolutePath.size();
    stdPath = stdPath.substr(pos+dataPathLength, stdPath.size() - pos);
    return stdPath;
}

std::string StringUtils::checkDir(const char *dir)
{
    std::string stdDir = dir;
    if(!(stdDir[stdDir.size() - 1] == '/' || stdDir[stdDir.size() - 1] == '\\'))
    {
        stdDir = stdDir + "/";
    }
    return stdDir;
}

std::string StringUtils::wstringToString(std::wstring wstr)
{
	size_t convertedChars = 0;
	std::string curLocale = setlocale(LC_ALL, NULL); //curLocale="C"
	setlocale(LC_ALL, "chs");
	const wchar_t* wcs = wstr.c_str();
	size_t stringLength = sizeof(wchar_t)*wstr.size() + 1;

	char* dest = new char[stringLength];
	wcstombs_s(&convertedChars, dest, stringLength, wcs, _TRUNCATE);
	std::string result = dest;
	delete[] dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

std::wstring StringUtils::stringToWstring(std::string str)
{
	size_t convertedChars = 0;
	size_t stringLength = sizeof(char)*str.size() + 1;

	wchar_t* dest = new wchar_t[stringLength];
	mbstowcs_s(&convertedChars, dest, stringLength, str.c_str(), _TRUNCATE);
	std::wstring outputString = dest;
	delete dest;
	return outputString;
}
