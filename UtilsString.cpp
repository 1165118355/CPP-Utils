#include "UtilsString.h"

std::string UtilsString::basename(const char *string, bool isRejectSuffix)
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
            isRejectSuffix = false;
        }
    }
    int offsetSize = posEnd - posStart;
    return str.substr(posStart, offsetSize);
}

std::string UtilsString::dirname(const char *string)
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

std::string UtilsString::replace(const char* string, const char* subString, const char* replaceString)
{
    std::string stdString = string;
    std::string stdSubString = subString;
    int pos=0;
    while (1)
    {
        pos = stdString.find(subString);
        if (pos != std::string::npos)
        {
            stdString.replace(pos, stdSubString.size(), replaceString);
            continue;
        }
        break;
    }
    return stdString;
}

std::vector<std::string> UtilsString::splite(const char * string, const char * splite)
{
    std::vector<std::string> retrunList;
    std::string stdString = string;
    std::string stdSplite = splite;
    int firstPos=0;
    int pos=0;
    while (true)
    {
        pos = stdString.find_first_of(stdSplite.c_str(), firstPos);
        if (pos != std::string::npos)
        {
            std::string item = stdString.substr(firstPos, pos- firstPos);
            retrunList.push_back(item);
            firstPos = pos+ stdSplite.size();
        }
        else
        {
			if (firstPos < stdString.size()-2)
			{
				pos = stdString.size()-1;
				std::string item = stdString.substr(firstPos, pos - firstPos);
				retrunList.push_back(item);
			}
            break;
        }

    }
    return retrunList;
}

std::string UtilsString::getSuffix(const char *string, const char *suffix)
{
    std::string stdString = string;
    int pos = stdString.find_last_of(suffix);
    if(pos == stdString.npos)
    {
        return std::string("");
    }
    pos += 1;
    return stdString.substr(pos);
}

std::string UtilsString::backupPath(const char *string, bool inverse)
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

std::string UtilsString::rejectPath(const char *srcString, const char *absolutePath)
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

std::string UtilsString::checkDir(const char *dir)
{
    std::string stdDir = dir;
    if(!(stdDir[stdDir.size() - 1] == '/' || stdDir[stdDir.size() - 1] == '\\'))
    {
        stdDir = stdDir + "/";
    }
    return stdDir;
}

std::string UtilsString::checkFilePath(const char *filePath, char ch)
{
    std::string stdFilePath = filePath;

    for(int i=0; i<stdFilePath.size(); ++i)
    {
        if(
                (stdFilePath[i] == ':' && i != 1) ||
                stdFilePath[i] == '*' ||
                stdFilePath[i] == '?' ||
                stdFilePath[i] == '"' ||
                stdFilePath[i] == '<' ||
                stdFilePath[i] == '>' ||
                stdFilePath[i] == '|')
        {
            stdFilePath[i] = ch;
        }
    }
    return stdFilePath;
}

std::string UtilsString::checkFileName(const char *filePath, char ch)
{
    std::string stdFilePath = filePath;

    for(int i=0; i<stdFilePath.size(); ++i)
    {
        if(
                stdFilePath[i] == '/' ||
                stdFilePath[i] == '\\' ||
                stdFilePath[i] == ':' ||
                stdFilePath[i] == '*' ||
                stdFilePath[i] == '?' ||
                stdFilePath[i] == '"' ||
                stdFilePath[i] == '<' ||
                stdFilePath[i] == '>' ||
                stdFilePath[i] == '|')
        {
            stdFilePath[i] = ch;
        }
    }
    return stdFilePath;
}

std::string UtilsString::relname(const char *path, const char *str)
{
    std::string ret;
    const char *p = path;
    const char *s = str;
    while(*p && *p == *s)
    {
        p++;
        s++;
    }
    if((*p == '/') != (*s == '/'))
    {
        if(*p == '/' && p > path)
            p--;
        if(*s == '/' && s > str)
            s--;
    }
    while(p > path && *p != '/')
        p--;
    while(s > str && *s != '/')
        s--;
    if(*p != '/' || *s != '/')
        return std::string(str);
    while(*p)
    {
        while(*p == '/')
            p++;
        if(*p)
            ret += "../";
        while(*p && *p != '/')
            p++;
    }
    ret += s + 1;
    return ret;
}

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static bool is_base64(unsigned char c)
{
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string UtilsString::encode(unsigned char const* bytes_to_encode, unsigned int in_len)
{
    std::string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            ret += '=';

    }

    return ret;

}


std::string UtilsString::decode(std::string const& encoded_string)
{
    int in_len = encoded_string.size();
    int i = 0;
    int j = 0;
    int in_ = 0;
    unsigned char char_array_4[4], char_array_3[3];
    std::string ret;

    while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_]))
    {
        char_array_4[i++] = encoded_string[in_]; in_++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                char_array_4[i] = base64_chars.find(char_array_4[i]);

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (i = 0; (i < 3); i++)
                ret += char_array_3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 4; j++)
            char_array_4[j] = 0;

        for (j = 0; j < 4; j++)
            char_array_4[j] = base64_chars.find(char_array_4[j]);

        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
    }

    return ret;
}

std::string UtilsString::wstringToString(std::wstring wstr)
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

std::wstring UtilsString::stringToWstring(std::string str)
{
    size_t convertedChars = 0;
    size_t stringLength = sizeof(char)*str.size() + 1;

    wchar_t* dest = new wchar_t[stringLength];
    mbstowcs_s(&convertedChars, dest, stringLength, str.c_str(), _TRUNCATE);
    std::wstring outputString = dest;
    delete dest;
    return outputString;
}

