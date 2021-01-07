#ifndef MATHUTILS_H
#define MATHUTILS_H

//	SpaceEngine的API
#if defined(SPACE_DOUBLE)
#include <SpaceMathLib.h>
#include <SpaceNode.h>
#endif
#include <vector>

namespace UtilsMath
{
    /// \brief  角度转换成弧度
    double rad(double d);

    /// \brief 两点纬度之差
    double longitudeAndLatitudeDistance(double longitude1, double latitude1, double longitude2, double latitude2);

    ///	\brief	随机函数，输入一个正整数，返回一个-1~1的伪随机数
    float rand(int x);

	///	\brief	计算三角形面积
	float calcTriangleArea(float a, float b, float c);
#if defined(SPACE_DOUBLE)
	///	\brief	将方向向量转换成四元数
    Space::Math::quat directorToQuat(Space::Math::vec3 dir, int axis = Space::Node::AXIS_NY);

	/// \brief  贝塞尔曲线
	Space::Math::Vec3 bezier2(Space::Math::Vec3 p0, Space::Math::Vec3 p1, Space::Math::Vec3 contorlP, double t);

	///	\brief	计算三角形面积
	float calcTriangleArea(Space::Math::Vec3 p0, Space::Math::Vec3 p1, Space::Math::Vec3 p2);

	//	\brief	将点进行顺时针排序
	bool sortPoints(std::vector<Space::Math::Vec3> &points);

	//	\brief	根据多边形顶点计算多边形三角面索引
	std::vector<int> calcPolygon(std::vector<Space::Math::Vec3> &points);

	/// \brief	将一组点集，曲线化
	std::vector<Space::Math::Vec3> convertBizer(std::vector<Space::Math::Vec3> points, float simpleRate=10, float camber=2, float length = -1);

	/// \brief	计算一个方向的垂直方向
	Space::Math::Vec3 calcVertical(Space::Math::Vec3 dir);

	///	\brief	获取两条线的交点
	Space::Math::Vec2 getIntersectionByTwoLine(Space::Math::Vec2 p0a, Space::Math::Vec2 p1a, Space::Math::Vec2 p0b, Space::Math::Vec2 p1b);
	Space::Math::Vec3 getIntersectionByTwoLine(Space::Math::Vec3 p0a, Space::Math::Vec3 p1a, Space::Math::Vec3 p0b, Space::Math::Vec3 p1b);

	///	\brief	判断点是否在矩形内
	bool isRectangleInside2D(Space::Math::vec2 p, Space::Math::vec2 p0, Space::Math::vec2 p1, Space::Math::vec2 p2, Space::Math::vec2 p3);
	bool isRectangleInside2D(Space::Math::Vec3 p, Space::Math::Vec3 p0, Space::Math::Vec3 p1, Space::Math::Vec3 p2, Space::Math::Vec3 p3);


    bool isPolygonInside2D(Space::Math::Vec3 p, std::vector<Space::Math::Vec3> points);
#endif 


	/// \brief  把value的值限制在minValue和maxValue之间
	template <class T>
	T clamp(T value, T minValue, T maxValue)
	{
		if (value < minValue)
		{
			return minValue;
		}
		else if (value > maxValue)
		{
			return maxValue;
		}
		return value;
	}

    ///	\brief	插值算法
    float lerpSine(float a, float b, float x);

	Space::Math::Vec3 GeographyToCartesian(const Space::Math::Vec3 position);
	Space::Math::Vec3 CartesianToGeography(const Space::Math::Vec3 point);
}

#endif // MATHUTILS_H
