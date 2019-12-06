#ifndef MATHUTILS_H
#define MATHUTILS_H

namespace MathUtils
{
    /// \brief  把value的值限制在minValue和maxValue之间
    template <class T>
    T clamp(T value, T minValue, T maxValue)
    {
        if(value < minValue)
        {
            return minValue;
        }
        else if(value > maxValue)
        {
            return maxValue;
        }
        return value;
    }

    ///	\brief	随机函数，输入一个正整数，返回一个-1~1的伪随机数
    float rand(int x);
}

#endif // MATHUTILS_H
