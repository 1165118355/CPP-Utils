///////////////////////////////
//	this class is a Math in SDL2. oh no
//	数学类（实际上就是为了方便才弄的）
//	《数学类》
//	2018年6月24日 00:12:07
//	by	水华宝箱

#ifndef _SDL2_MATH_H_BOX
#define _SDL2_MATH_H_BOX
namespace WaterBox
{
	namespace Math
	{
		///	\brief	产生一个随机数，数值范围是min <= return <=max
		float randFloat(float min, float max);
		class vec2
		{
		public :
			vec2();
			vec2(double x, double y);
			vec2 operator +(const int number);
			vec2 operator -(const int number);
			vec2 operator /(const int number);
			vec2 operator *(const int number);

			vec2 operator +(const float number);
			vec2 operator -(const float number);
			vec2 operator /(const float number);
			vec2 operator *(const float number);

			vec2 operator +(const vec2 vector);
			vec2 operator -(const vec2 vector);
			vec2 operator *(const vec2 vector);
			vec2 operator /(const vec2 vector);
		public:
			static const vec2 vec2_zero;
			double x;
			double y;
		};

		class vec3
		{
		public:
			vec3();
			vec3(double x, double y, double z); 
			vec3 operator +(const int number);
			vec3 operator -(const int number);
			vec3 operator /(const int number);
			vec3 operator *(const int number);

			vec3 operator +(const vec3 vector);
			vec3 operator -(const vec3 vector);
			vec3 operator *(const vec3 vector);
			vec3 operator /(const vec3 vector);
		
			double x;
			double y;
			double z;
		};

		class vec4
		{
		public:
			vec4();
			vec4(double x, double y, double z, double w); 
			vec4 operator +(const int number);
			vec4 operator -(const int number);
			vec4 operator /(const int number);
			vec4 operator *(const int number);

			vec4 operator +(const vec4 vector);
			vec4 operator -(const vec4 vector);
			vec4 operator *(const vec4 vector);
			vec4 operator /(const vec4 vector);
		public:
			static const vec4 vec4_zero;
			double x;
			double y;
			double z;
			double w;
		};

		///	\brief	把传进来的value的值限制在left与right之间
		int clmp(int &value, int left, int right);
	}
}

#endif	//	!_SDL2_MATH_H_BOX