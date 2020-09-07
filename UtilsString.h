#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

class UtilsString
{
public:
    /// \brief  只留下路径的文件名，如果object/meshes/tree/redtree.node的话，则会变成redtree.node
    /// \parm isRejectSuffix    如果isRejectSuffix=1，的话则会去掉后缀变成redtree
    static std::string basename(const char *string, bool isRejectSuffix = 0);

    /// \brief  只留下路径的目录
    static std::string dirname(const char *string);

    ///	\brief	分隔
    static std::vector<std::string> splite(const char *string, const char *splite);

    static std::string getSuffix(const char *string, const char *suffix=".");

    /// \brief  路径回退一格 object/meshes/tree/变成object/meshes
    /// \parm inverse   如果inverse=1 object/meshes/tree/则会变成meshes/tree/
    static std::string backupPath(const char *string, bool inverse = 0);

    /// \brief  减去一个绝对路径
    static std::string rejectPath(const char *srcString, const char *absolutePath);

    /// \brief  检查路径（默认会给字符串后面加上一个/号）
    static std::string checkDir(const char *dir);

    /// \brief  检查非法字符，将非法字符替换为ch
    static std::string checkFilePath(const char *filePath, char ch='_');
    static std::string checkFileName(const char *filePath, char ch='_');

    static std::string relname(const char *path, const char *str);

    static std::string encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    static std::string decode(std::string const& encoded_string);

    ///	\brief	宽字符转换
    static std::string wstringToString(std::wstring wstr);
    static std::wstring stringToWstring(std::string str);
};

#endif // STRINGUTILS_H
