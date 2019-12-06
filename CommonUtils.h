#ifndef COMMONUTILS_H
#define COMMONUTILS_H

#include<QString>
#include <vector>

namespace CommonUtils
{
    /// \brief  在Vector中查找一个东东
    template<typename T>
    bool hasElementInVector(std::vector<T> vector, T element)
    {
        for(int i=0; i<vector.size(); ++i)
        {
            T vectorElement = vector[i];
            if(vectorElement == element)
            {
                return true;
            }
        }
        return false;
    }


    QString loadFontFamilyFromFiles(const QString &sfontFile);
}

#endif // COMMONUTILS_H
