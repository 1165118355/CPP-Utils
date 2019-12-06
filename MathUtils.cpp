#include "MathUtils.h"

namespace MathUtils
{

float rand(int x)
{
    int seed = 2;
    x = (x << 13) ^ x;
    //float randomVlaue = (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    float randomVlaue = (1.0f - ((x * (x * x * seed + 3) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    return randomVlaue;
}

}
