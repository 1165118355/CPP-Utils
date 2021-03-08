#include "SDL2_Math.h"
#include <stdlib.h>
#include <time.h>

using namespace WaterBox;
const Math::vec4 Math::vec4::vec4_zero = Math::vec4(0, 0, 0, 0);
const Math::vec2 Math::vec2::vec2_zero = Math::vec2(0, 0);
WaterBox::Math::vec2::vec2()
{
	x = 0;
	y = 0;
}

WaterBox::Math::vec2::vec2(double x, double y) 
{
	vec2::x = x;
	vec2::y = y;
}

Math::vec2 WaterBox::Math::vec2::operator+(const int number)
{
	Math::vec2 v;
	v.x = x + number;
	v.y = y + number;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator-(const int number)
{
	Math::vec2 v;
	v.x = x - number;
	v.y = y - number;
	return v;
}

Math::vec2 Math::vec2::operator/(const int number)
{
	Math::vec2 v;
	v.x = x / number;
	v.y = y / number;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator*(const int number)
{
	Math::vec2 v;
	v.x = x * number;
	v.y = y * number;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator+(const float number)
{
	Math::vec2 v;
	v.x = x + number;
	v.y = y + number;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator-(const float number)
{
	Math::vec2 v;
	v.x = x - number;
	v.y = y - number;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator/(const float number)
{
	Math::vec2 v;
	v.x = x / number;
	v.y = y / number;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator*(const float number)
{
	Math::vec2 v;
	v.x = x * number;
	v.y = y * number;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator+(const vec2 vector)
{
	Math::vec2 v;
	v.x = x + vector.x;
	v.y = y + vector.y;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator-(const vec2 vector)
{
	Math::vec2 v;
	v.x = x - vector.x;
	v.y = y - vector.y;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator*(const vec2 vector)
{
	Math::vec2 v;
	v.x = x * vector.x;
	v.y = y * vector.y;
	return v;
}

Math::vec2 WaterBox::Math::vec2::operator/(const vec2 vector)
{
	Math::vec2 v;
	v.x = x / vector.x;
	v.y = y / vector.y;
	return v;
}

WaterBox::Math::vec3::vec3() 
{
	x = 0;
	y = 0;
	z = 0;

}

WaterBox::Math::vec3::vec3(double x, double y, double z)
{
	vec3::x = x;
	vec3::y = y;
	vec3::z = z;
}

Math::vec3 WaterBox::Math::vec3::operator+(const int number)
{
	Math::vec3 v;
	v.x = x + number;
	v.y = y + number;
	v.z = z + number;
	return v;
}

Math::vec3 WaterBox::Math::vec3::operator-(const int number)
{
	Math::vec3 v;
	v.x = x - number;
	v.y = y - number;
	v.z = z - number;
	return v;
}

Math::vec3 WaterBox::Math::vec3::operator/(const int number)
{
	Math::vec3 v;
	v.x = x / number;
	v.y = y / number;
	v.z = z / number;
	return v;
}

Math::vec3 WaterBox::Math::vec3::operator*(const int number)
{
	Math::vec3 v;
	v.x = x * number;
	v.y = y * number;
	v.z = z * number;
	return v;
}

Math::vec3 WaterBox::Math::vec3::operator+(const vec3 vector)
{
	Math::vec3 v;
	v.x = x + vector.x;
	v.y = y + vector.y;
	v.z = z + vector.z;
	return v;
}

Math::vec3 WaterBox::Math::vec3::operator-(const vec3 vector)
{
	Math::vec3 v;
	v.x = x - vector.x;
	v.y = y - vector.y;
	v.z = z - vector.z;
	return v;
}

Math::vec3 WaterBox::Math::vec3::operator*(const vec3 vector)
{
	Math::vec3 v;
	v.x = x * vector.x;
	v.y = y * vector.y;
	v.z = z * vector.z;
	return v;
}

Math::vec3 WaterBox::Math::vec3::operator/(const vec3 vector)
{
	Math::vec3 v;
	v.x = x / vector.x;
	v.y = y / vector.y;
	v.z = z / vector.z;
	return v;
}

WaterBox::Math::vec4::vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

WaterBox::Math::vec4::vec4(double x, double y, double z, double w)
{
	vec4::x = x;
	vec4::y = y;
	vec4::z = z;
	vec4::w = w;
}

Math::vec4 WaterBox::Math::vec4::operator+(const int number)
{
	Math::vec4 v;
	v.x = x + number;
	v.y = y + number;
	v.z = z + number;
	v.w = w + number;
	return v;
}

Math::vec4 WaterBox::Math::vec4::operator-(const int number)
{
	Math::vec4 v;
	v.x = x - number;
	v.y = y - number;
	v.z = z - number;
	v.w = w - number;
	return v;
}

Math::vec4 WaterBox::Math::vec4::operator/(const int number)
{
	Math::vec4 v;
	v.x = x / number;
	v.y = y / number;
	v.z = z / number;
	v.w = w / number;
	return v;
}

Math::vec4 WaterBox::Math::vec4::operator*(const int number)
{
	Math::vec4 v;
	v.x = x * number;
	v.y = y * number;
	v.z = z * number;
	v.w = w * number;
	return v;
}

Math::vec4 WaterBox::Math::vec4::operator+(const vec4 vector)
{
	Math::vec4 v;
	v.x = x + vector.x;
	v.y = y + vector.y;
	v.z = z + vector.z;
	v.w = w + vector.w;
	return v;
}

Math::vec4 WaterBox::Math::vec4::operator-(const vec4 vector)
{
	Math::vec4 v;
	v.x = x - vector.x;
	v.y = y - vector.y;
	v.z = z - vector.z;
	v.w = w - vector.w;
	return v;
}

Math::vec4 WaterBox::Math::vec4::operator*(const vec4 vector)
{
	Math::vec4 v;
	v.x = x * vector.x;
	v.y = y * vector.y;
	v.z = z * vector.z;
	v.w = w * vector.w;
	return v;
}

Math::vec4 WaterBox::Math::vec4::operator/(const vec4 vector)
{
	Math::vec4 v;
	v.x = x / vector.x;
	v.y = y / vector.y;
	v.z = z / vector.z;
	v.w = w / vector.w;
	return v;
}

float WaterBox::Math::randFloat(float min, float max)
{
	int minInt = (min * 1000);
	int maxInt = (max * 1000);

	return ((rand() % (maxInt - minInt))/1000.0) + min;
}

int WaterBox::Math::clmp(int &value, int left, int right)
{
	if (value < left)
	{
		return left;
	}
	if (value > right)
	{
		return right;
	}
	return value;
}
