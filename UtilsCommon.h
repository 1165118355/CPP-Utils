////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-04-27
//  brief:  xxx
//
#pragma once

#include <vector>

namespace UtilsCommon
{
#if defined(_WIN32)
	///	\brief	文件夹操作
	bool isDir(const char *path);
	bool createDir(const char *path, bool makeParent=0);

	///	\brief	是否是文件
	bool isFile(const char *path);
#endif

    template<class vtype>
    bool vectorCheck(std::vector<vtype> &v, vtype value)
    {
        for (int i = 0; i < v.size(); ++i)
        {
            if (v[i] == value) {
                return true;
            }
        }

        return false;
    }

};

