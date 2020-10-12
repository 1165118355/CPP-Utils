#pragma once
#include<cmath>
#include <map>

class MercatorProj
{
public:
	MercatorProj();
	~MercatorProj();

	///	\brief	WGS84的墨卡托投影
	static std::pair<double, double> WGS84ToMercator(double lon, double lat);
	static std::pair<double, double> mercatorToWGS84(double x, double y);

	//	\brief	设置长半轴和短半轴
	void SetAB(double a, double b);

	//	\brief	设置原始经纬度(填0，0就好了)
	void SetB0(double b0);
	void SetL0(double l0);
	void setBL0(double b0, double l0);
	
	///	\brief	从笛卡尔变换到经纬度
	int FromProj(double X, double Y, double& B, double& L);

	///	\brief	使用墨卡托投影/zip/master
	int ToProj(double B, double L, double &X, double &Y);


	//角度到弧度的转换
	static double DegreeToRad(double degree);
	//弧度到角度的转换
	static double RadToDegree(double rad);

protected:

	//圆周率
	static const double PI;
private:
	int __IterativeTimes;      //反向转换程序中的迭代次数
	double __IterativeValue;  //反向转换程序中的迭代初始值
	double __A;    //椭球体长半轴,米
	double __B;    //椭球体短半轴,米
	double __B0; //标准纬度,弧度
	double __L0; //原点经度,弧度

};

