#include "UtilsMath.h"
#if defined(SPACE_DOUBLE)
#include <SpaceMathLib.h>
#include <SpaceGeometry.h>
#endif

namespace UtilsMath
{

double UtilsMath::rad(double d)
{
    return d * SPACE_PI / 180.00; //角度转换成弧度
}

double UtilsMath::longitudeAndLatitudeDistance(double longitude1, double latitude1, double longitude2, double latitude2)
{
    double Lat1 = rad(latitude1);                       // 纬度
    double Lat2 = rad(latitude2);
    double a = Lat1 - Lat2;                             //两点纬度之差
    double b = rad(longitude1) - rad(longitude2);       //经度之差
    double s = 2 * Space::Math::asin(sqrt(pow(Space::Math::sin(a / 2), 2) + Space::Math::cos(Lat1) * Space::Math::cos(Lat2) * pow(Space::Math::sin(b / 2), 2)));//计算两点距离的公式
    s = s * 6378137.0;                                  //弧长乘地球半径（半径为米）
    s = Space::Math::round(s * 10000) / 10000;        //精确距离的数值
    return s;
}

float rand(int x)
{
    int seed = 2;
    x = (x << 13) ^ x;
    //float randomVlaue = (1.0 - ((x * (x * x * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
    float randomVlaue = (1.0f - ((x * (x * x * seed + 3) + 1376312589) & 0x7fffffff) / 1073741824.0f);
    return randomVlaue;
}

float calcTriangleArea(float a, float b, float c)
{
	float s = (a + b + c) * 0.5;
	s = sqrt(s * (s - a) * (s - b) * (s - c));
	return s;
}


#if defined(SPACE_DOUBLE)
Space::Math::quat directorToQuat(Space::Math::vec3 dir)
{                                     
//	Space::Math::vec3 theFront = Space::Math::vec3(0, 1, 0);
//	Space::Math::vec3 axiRot = Space::Math::cross(theFront, dir);						//	获取旋转轴

//	int angleDir = (axiRot.z > 0) ? 1 : -1;
//	int angle = Space::Math::getAngle(Space::Math::vec3(theFront), Space::Math::vec3(dir)) * angleDir;
//	Space::Math::quat quat = Space::Math::quat(axiRot, angle);

//	return quat;

    Space::Math::vec3 yAxis = dir;
    Space::Math::vec3 xAxis = Space::Math::cross(yAxis, Space::Math::vec3(0, 0, 1));
    Space::Math::vec3 zAxis = Space::Math::cross(xAxis, yAxis);
    Space::Math::quat quat(xAxis, yAxis, zAxis);
    return quat;
}

float calcTriangleArea(Space::Math::Vec3 p0, Space::Math::Vec3 p1, Space::Math::Vec3 p2)
{
	auto a = p0 - p1;

	auto b = p1 - p2;

	auto c = p2 - p0;
	float s = calcTriangleArea(a.length(), b.length(), c.length());
	return s;
}

bool sortPoints(std::vector<Space::Math::Vec3> &points)
{
	bool isSort = false;
	//顺时针排序(先找到一个凸点p，然后得到(p-1,p) , (p, p+1)两个向量进行叉乘得到多边形绕序)
	if (points.size() >= 3)
	{
		int p = 0;
		for (int i = 0; i < points.size(); ++i)
		{
			Space::Math::Vec3 posMax = points[p];
			Space::Math::Vec3 pos = points[i];
			if (pos.x != 0 && pos.y != 0 && pos.x > posMax.x)
			{
				p = i;
			}
		}

		int ps1 = p == 0 ? (points.size() - 1) : (p - 1);
		int pp1 = p == (points.size() - 1) ? 0 : (p + 1);

		Space::Math::Vec3 pPos = points[p];
		Space::Math::Vec3 ps1Pos = points[ps1];
		Space::Math::Vec3 pp1Pos = points[pp1];

		ps1Pos = ps1Pos - pPos;
		pp1Pos = pPos - pp1Pos;

		Space::Math::Vec3 crossResult = Space::Math::cross(ps1Pos, pp1Pos);
		if (crossResult.z > 0)
		{
			std::vector<Space::Math::Vec3> copy = points;
			for (int i = 0; i < copy.size(); ++i)
			{
				points[i] = copy[copy.size() - i - 1];
			}
			isSort = true;
		}
	}
	return isSort;
}

std::vector<int> calcPolygon(std::vector<Space::Math::Vec3> &points)
{
	//顺时针排序(先找到一个凸点p，然后得到(p-1,p) , (p, p+1)两个向量进行叉乘得到多边形绕序)
	sortPoints(points);

	//	构建三角面
	std::vector<int> indexes;
	std::vector<std::pair<int, Space::Math::Vec3>> vetricesMap;
	for (int i = 0; i < points.size(); ++i)
	{
		vetricesMap.push_back(std::pair<int, Space::Math::Vec3>(i, points[i]));
	}
	bool isActivity = true;
	while (isActivity)
	{
		isActivity = false;
		for (int i = 0; i < (vetricesMap.size() - 2); ++i)
		{
			Space::Math::Vec3 p0 = vetricesMap[i + 0].second;
			Space::Math::Vec3 p1 = vetricesMap[i + 1].second;
			Space::Math::Vec3 p2 = vetricesMap[i + 2].second;

			Space::Math::Vec3 A = p1 - p0;
			Space::Math::Vec3 B = p2 - p1;
			Space::Math::Vec3 result = Space::Math::cross(A, B);

			//	如果三角面中有其他的点，则不处理
			int isHaveTriangular = false;
			for (int j = 0; j < points.size(); ++j)
			{
				if (j == vetricesMap[i + 0].first ||
					j == vetricesMap[i + 1].first ||
					j == vetricesMap[i + 2].first)
				{
					continue;
				}
				isHaveTriangular = Space::Geometry::pointTriangleInside(points[j], p0, p1, p2);
				if (isHaveTriangular)
				{
					break;
				}
			}
			if (result.z <= 0 && !isHaveTriangular)
			{
				indexes.push_back(vetricesMap[i + 2].first);
				indexes.push_back(vetricesMap[i + 1].first);
				indexes.push_back(vetricesMap[i + 0].first);
				vetricesMap.erase(vetricesMap.begin() + (i + 1));
				isActivity = true;
			}
		}
	}
	return indexes;
}

std::vector<Space::Math::Vec3> convertBizer(std::vector<Space::Math::Vec3> points, float simpleRate, float camber, float length)
{
	std::vector<Space::Math::Vec3> newPoints;
	if (points.size() < 3)
	{
		return points;
	}

	for (int i = 1; i < (points.size() - 1); ++i)
	{
		auto p0 = points[i - 1];
		auto p1 = points[i];
		auto p2 = points[i + 1];

		auto a = Space::Math::normalize(p1 - p0);
		auto b = Space::Math::normalize(p1 - p2);
		auto aLength = (p1 - p0).length();
		auto bLength = (p1 - p2).length();
		auto dirT = -Space::Math::normalize(a + b);
		auto dir = Space::Math::cross(dirT, Space::Math::Vec3(0, 0, 1));
		if (Space::Math::cross(a, b).z < 0)
		{
			dir = -dir;
		}
		auto pc0 = p1 + dir * (aLength / camber);
		auto pc1 = p1 - dir * (bLength / camber);

		int simpleValue = aLength * simpleRate;
		simpleValue = (simpleValue < 3 ? 3 : simpleValue);
		if (i == 1)
		{
			for (int j = 0; j <= simpleValue; ++j)
			{
				auto lerpPos = UtilsMath::bezier2(p0, p1, pc0, (float)j / simpleValue);
				newPoints.push_back(lerpPos);
			}
		}
		else
		{
			for (int j = 0; j <= simpleValue; ++j)
			{
				float lerpValue = (float)j / simpleValue;
				auto lerpPos = UtilsMath::bezier2(p0, p1, pc0, lerpValue);
				newPoints[newPoints.size() - simpleValue + j] = (newPoints[newPoints.size() - simpleValue + j] * (1 - lerpValue) + lerpPos * (lerpValue));
			}
		}

		simpleValue = bLength * simpleRate;
		simpleValue = (simpleValue < 1 ? 2 : simpleValue);
		for (int j = 1; j < (int)simpleValue+1; ++j)
		{
			auto lerpPos = UtilsMath::bezier2(p1, p2, pc1, (float)j / simpleValue);
			newPoints.push_back(lerpPos);
		}
	}

	//	均长
	if (length > 0 && newPoints.size() > 2)
	{
		float currentLengt = length;
		std::vector<Space::Math::Vec3>newLengthPoints;
		newLengthPoints.push_back(newPoints[0]);
		auto p0 = newPoints[0];
		for (int i=1; i<newPoints.size(); ++i)
		{
			auto p1 = newPoints[i];
			while (true)
			{
				auto distanceVec3 = p1 - p0;
				auto allLength = distanceVec3.length();
				if (allLength > currentLengt)
				{
					float lerpValue = currentLengt / distanceVec3.length();
					p0 = Space::Math::lerp(p0, p1, lerpValue);
					allLength -= currentLengt;
					currentLengt = length;
					newLengthPoints.push_back(p0);
				}
				else
				{
					currentLengt = currentLengt - allLength;
					p0 = p1;
					break;
				}
			}
		}
		return newLengthPoints;
	}
	return newPoints;
}

Space::Math::Vec3 bezier2(Space::Math::Vec3 p0, Space::Math::Vec3 p1, Space::Math::Vec3 contorlP, double t)
{
     return (p0 * pow(1 - t, 2.0)) + contorlP*((2.0*t) * (1.0-t)) + p1* pow(t, 2.0);
}
#endif
}
