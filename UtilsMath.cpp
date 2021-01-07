#include "UtilsMath.h"
#include "MercatorProj.h"
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
Space::Math::quat directorToQuat(Space::Math::vec3 dir, int axis)
{                                     
//	Space::Math::vec3 theFront = Space::Math::vec3(0, 1, 0);
//	Space::Math::vec3 axiRot = Space::Math::cross(theFront, dir);						//	获取旋转轴

//	int angleDir = (axiRot.z > 0) ? 1 : -1;
//	int angle = Space::Math::getAngle(Space::Math::vec3(theFront), Space::Math::vec3(dir)) * angleDir;
//	Space::Math::quat quat = Space::Math::quat(axiRot, angle);

//	return quat;
    Space::Math::vec3 up(0,0,1);
    if(dir == Space::Math::vec3(0,0,1))
        up = Space::Math::vec3(0.1,0,0.9);

    Space::Math::vec3 yAxis = dir;
    Space::Math::vec3 xAxis = Space::Math::cross(yAxis, up);
    Space::Math::vec3 zAxis = Space::Math::cross(xAxis, yAxis);
    Space::Math::quat quat;
    switch(axis)
    {
    case Space::Node::AXIS_X:
        quat = Space::Math::quat (yAxis, xAxis, zAxis);
        break;
    case Space::Node::AXIS_NX:
        quat = Space::Math::quat (-yAxis, xAxis, zAxis);
        break;
    case Space::Node::AXIS_Y:
        quat = Space::Math::quat (xAxis, yAxis, zAxis);
        break;
    case Space::Node::AXIS_NY:
        quat = Space::Math::quat (xAxis, -yAxis, zAxis);
        break;
    case Space::Node::AXIS_Z:
        quat = Space::Math::quat (xAxis, zAxis, yAxis);
        break;
    case Space::Node::AXIS_NZ:
        quat = Space::Math::quat (xAxis, zAxis, -yAxis);
        break;
    }


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

bool UtilsMath::sortPoints(std::vector<Space::Math::Vec3> &points)
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
            for (int j = 0; j < simpleValue; ++j)
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

Space::Math::Vec3 calcVertical(Space::Math::Vec3 dir)
{
	Space::Math::Vec3 up (0,0,1);
	if (dir == up)
		up.x += 0.001;
	auto vertical = Space::Math::cross(dir, up);
	return vertical;
}

Space::Math::Vec2 getIntersectionByTwoLine(Space::Math::Vec2 p0a, Space::Math::Vec2 p1a, Space::Math::Vec2 p0b, Space::Math::Vec2 p1b)
{
	//	先判断两条线是否有交点的可能
	if (Space::Math::min(p0a[0], p1a[0]) > Space::Math::max(p0b[0], p1b[0]))
		return Space::Math::Vec2();
	if (Space::Math::min(p0a[1], p1a[1]) > Space::Math::max(p0b[1], p1b[1]))
		return Space::Math::Vec2();
	if (Space::Math::min(p0b[0], p1b[0]) > Space::Math::max(p0a[0], p1a[0]))
		return Space::Math::Vec2();
	if (Space::Math::min(p0b[1], p1b[1]) > Space::Math::max(p0a[1], p1a[1]))
		return Space::Math::Vec2();


	//Space::Math::vec2 base = Space::Math::vec2(p1b - p0b);
	//double d1 = abs (Space::Math::cross(base, Space::Math::vec2(p0a - p0b)));
	//double  d2 = abs(Space::Math::cross(base, Space::Math::vec2(p1a - p0b)));
	//double t = d1 / (d1 + d2);
	//Space::Math::Vec2 temp = (p1a - p0a)*t;
	//return p0a + temp;

	double x1 = p0a.x, y1 = p0a.y;
	double x2 = p1a.x, y2 = p1a.y;
	double x3 = p0b.x, y3 = p0b.y;
	double x4 = p1b.x, y4 = p1b.y;
	double t = ((x2 - x1)*(y3 - y1) - (x3 - x1)*(y2 - y1)) / ((x2 - x1)*(y3 - y4) - (x3 - x4)*(y2 - y1));
	return Space::Math::Vec2(x3 + t*(x4 - x3), y3 + t*(y4 - y3));
}

Space::Math::Vec3 getIntersectionByTwoLine(Space::Math::Vec3 p0a, Space::Math::Vec3 p1a, Space::Math::Vec3 p0b, Space::Math::Vec3 p1b)
{
	auto result = getIntersectionByTwoLine(Space::Math::Vec2(p0a.x, p0a.y), Space::Math::Vec2(p1a.x, p1a.y), Space::Math::Vec2(p0b.x, p0b.y), Space::Math::Vec2(p1b.x, p1b.y));
    return Space::Math::Vec3(result.x, result.y, p1b.z);
}

bool isRectangleInside2D(Space::Math::vec2 p, Space::Math::vec2 p0, Space::Math::vec2 p1, Space::Math::vec2 p2, Space::Math::vec2 p3)
{
	if (Space::Math::dot((p1 - p0), (p - p0)) >= 0 &&
		Space::Math::dot((p3 - p0), (p - p0)) >= 0 &&
		Space::Math::dot((p3 - p2), (p - p2)) >= 0 &&
		Space::Math::dot((p1 - p2), (p - p2)) >= 0)
	{
		return true;
	}
	return false;
}

bool isRectangleInside2D(Space::Math::Vec3 p, Space::Math::Vec3 p0, Space::Math::Vec3 p1, Space::Math::Vec3 p2, Space::Math::Vec3 p3)
{
	return isRectangleInside2D(Space::Math::vec2(p.x, p.y), Space::Math::vec2(p0.x, p0.y), Space::Math::vec2(p1.x, p1.y), Space::Math::vec2(p2.x, p2.y), Space::Math::vec2(p3.x, p3.y));
}

Space::Math::Vec3 bezier2(Space::Math::Vec3 p0, Space::Math::Vec3 p1, Space::Math::Vec3 contorlP, double t)
{
//    auto p0xy = p0;
//    auto p1xy = p1;
//    auto contorlPxy = p1;
//    p0xy.z=0;
//    p1xy.z=0;
//    contorlPxy.z=0;
//    auto xy = (p0xy * pow(1 - t, 2.0)) + contorlPxy*((2.0*t) * (1.0-t)) + p1xy* pow(t, 2.0);
//    xy.z = Space::Math::lerp(p0.z, p1.z, t);
    return (p0 * pow(1 - t, 2.0)) + contorlP*((2.0*t) * (1.0-t)) + p1* pow(t, 2.0);
}

bool isPolygonInside2D(Space::Math::Vec3 p, std::vector<Space::Math::Vec3> points)
{
    auto indexes = calcPolygon(points);

    for(int i=2; i<indexes.size(); ++i)
    {
        Space::Math::Vec3 p0 = points[indexes[i-2]];
        Space::Math::Vec3 p1 = points[indexes[i-1]];
        Space::Math::Vec3 p2 = points[indexes[i]];

        if(Space::Geometry::pointTriangleInside(p, p0, p1, p2))
        {
            return true;
        }
    }
    return false;
}


Space::Math::Vec3 GeographyToCartesian(const Space::Math::Vec3 position)
{
	std::pair<double, double> tempPair = MercatorProj::WGS84ToMercator(position[1],position[0]);
	return Space::Math::Vec3(tempPair.first,tempPair.second,position[2]);
}

Space::Math::Vec3 CartesianToGeography(const Space::Math::Vec3 point)
{
	std::pair<double, double> tempPair = MercatorProj::mercatorToWGS84(point[0], point[1]);
	return Space::Math::Vec3(tempPair.first, tempPair.second, point[2]);
}

#endif
}
