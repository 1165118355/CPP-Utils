#include "MercatorProj.h"

const double MercatorProj::PI = 3.1415926535897932;

//构造函数中赋予参数默认值
MercatorProj::MercatorProj() :__IterativeTimes(10), __IterativeValue(0), __A(0), __B(0), __B0(0), __L0(0)
{
}
//设定__A与__B
void MercatorProj::SetAB(double a, double b)//原程序的参数写作double a, double b
{
	if (a <= 0 || b <= 0)
	{
		return;
	}
	__A = a;
	__B = b;
}
//设定__B0
void MercatorProj::SetB0(double b0)
{
	if (b0<-PI / 2 || b0>PI / 2)
	{
		return;
	}
	__B0 = b0;//设定标准纬度，标准纬度线和原点经度线的交点组成了投影后的平面坐标的原点
}
//设定__L0
void MercatorProj::SetL0(double l0)
{
	if (l0<-PI || l0>PI)
	{
		return;
	}
	__L0 = l0;//设定原点经度
}

void MercatorProj::setBL0(double b0, double l0)
{
	SetB0(b0);
	SetL0(l0);
}


/*******************************************
投影正向转换程序
double B: 维度,弧度
double L: 经度,弧度
double& X:     纵向直角坐标
double& Y:      横向直角坐标
*******************************************/
int MercatorProj::ToProj(double B, double L, double& X, double& Y)
{
	double f/*扁率*/, e/*第一偏心率*/, e_/*第二偏心率*/, NB0/*卯酉圈曲率半径*/, K, dtemp;
	double E = exp(1);
	if (L<-PI || L>PI || B<-PI / 2 || B>PI / 2)
	{
		return 1;
	}

	if (__A <= 0 || __B <= 0)
	{
		return 1;
	}

	f = (__A - __B) / __A;

	dtemp = 1 - (__B / __A) * (__B / __A);
	if (dtemp < 0)
	{
		return 1;
	}
	e = sqrt(dtemp);

	dtemp = (__A / __B) * (__A / __B) - 1;
	if (dtemp < 0)
	{
		return 1;
	}
	e_ = sqrt(dtemp);

	NB0 = ((__A * __A) / __B) / sqrt(1 + e_ * e_ * cos(__B0) * cos(__B0)); //NB0=N, 法线长（《大地测量学基础》第二版第103页，或109、110页）

	K = NB0 * cos(__B0);//平行圈半径

	Y = K * (L - __L0);

	X = K * log(tan(PI / 4 + B / 2) * pow((1 - e * sin(B)) / (1 + e * sin(B)), e / 2));

	return 0;
}
double MercatorProj::DegreeToRad(double degree)
{
	return PI * ((double)degree / (double)180);
}
double MercatorProj::RadToDegree(double rad)
{
	return (180 * rad) / PI;
}
/*******************************************
投影反向转换程序
double X: 纵向直角坐标
double Y: 横向直角坐标
double& B:     维度,弧度
double& L:     经度,弧度
*******************************************/
int MercatorProj::FromProj(double X, double Y, double& B, double& L)
{
	double f/*扁率*/, e/*第一偏心率*/, e_/*第二偏心率*/, NB0/*卯酉圈曲率半径*/, K, dtemp;
	double E = exp(1);

	if (__A <= 0 || __B <= 0)
	{
		return 1;
	}

	f = (__A - __B) / __A;

	dtemp = 1 - (__B / __A) * (__B / __A);
	if (dtemp < 0)
	{
		return 1;
	}
	e = sqrt(dtemp);

	dtemp = (__A / __B) * (__A / __B) - 1;
	if (dtemp < 0)
	{
		return 1;
	}
	e_ = sqrt(dtemp);

	NB0 = ((__A * __A) / __B) / sqrt(1 + e_ * e_ * cos(__B0) * cos(__B0));

	K = NB0 * cos(__B0);

	L = Y / K + __L0;
	B = __IterativeValue;
	for (int i = 0; i < __IterativeTimes; i++)
	{
		B = PI / 2 - 2 * atan(pow(E, (-X / K)) * pow(E, (e / 2) * log((1 - e * sin(B)) / (1 + e * sin(B)))));
	}


	return 0;
}

MercatorProj::~MercatorProj()
{
}

std::pair<double, double> MercatorProj::WGS84ToMercator(double lat, double lon)
{
	double a = 6378137;//长半轴
	double b = 6356752.3142;//短半轴
	MercatorProj m_mp;
	m_mp.SetAB(a, b); // WGS 84
	m_mp.SetB0(m_mp.DegreeToRad(0));
	m_mp.SetL0(m_mp.DegreeToRad(0));

	double x = 0, y = 0;
	m_mp.ToProj(m_mp.DegreeToRad(lat), m_mp.DegreeToRad(lon), y, x);
	return std::pair<double, double>(x, y);
}

std::pair<double, double> MercatorProj::mercatorToWGS84(double x, double y)
{
	double a = 6378137;//长半轴
	double b = 6356752.3142;//短半轴
	MercatorProj m_mp;
	m_mp.SetAB(a, b); // WGS 84
	m_mp.SetB0(0);
	m_mp.SetL0(0);

	double lat = 0, lon = 0;
	m_mp.FromProj(x, y, lat, lon);
	return std::pair<double, double>(RadToDegree(lat), RadToDegree(lon));
}
