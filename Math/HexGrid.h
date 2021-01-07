#ifndef HEXGRID_H
#define HEXGRID_H

#include <SpaceMathLib.h>

class HexGrid
{
public:
    /// \brief
	HexGrid();
    HexGrid(Space::Math::ivec3 position);
    HexGrid(Space::Math::ivec2 position);
	HexGrid(int x, int y, int z);
	HexGrid(int row, int cloumn);

    static Space::Math::ivec3 convertToVec3(int row, int cloumn);
    static Space::Math::ivec2 convertToVec2(int x, int y, int z);
    static Space::Math::ivec2 convertToVec2(Space::Math::ivec3 pos);

    /// \brief  获取笛卡尔坐标，返回的是中心点
    Space::Math::Vec3 getDescartesPosition();
    Space::Math::Vec3 getCornerPosition(int index);
    const Space::Math::ivec3 getPosition()const;

    static void setOffsetAngle(double angle);
    static double getOffsetAngle(){return OffsetAngle;}


    HexGrid operator -();
    HexGrid operator +(const HexGrid & a);
    HexGrid &operator +=(const HexGrid & a);
    HexGrid operator *(const int& a);
public:
    static const double SIN_30;// = sin(PI/6)
    static const double SIN_60;// = sin(PI/3)
    static const double SIN_90;// = sin(PI/2)
    static const double SIN_120;// = sin(2PI/3)
    static Space::Math::Vec3 XAxisN;
    static Space::Math::Vec3 YAxisN;
    static Space::Math::Vec3 ZAxisN;
//    Space::Math::Vec3 XAxisT;
//    Space::Math::Vec3 YAxisT;
//    Space::Math::Vec3 ZAxisT;
    static float Radius;

    static HexGrid Y  ;
    static HexGrid NY ;
    static HexGrid X  ;
    static HexGrid NX ;
    static HexGrid Z  ;
    static HexGrid NZ ;
protected:
	void init(Space::Math::ivec3 position);
	void init(Space::Math::ivec2 position);
    static double OffsetAngle; //  弧度
private:
	static Space::Math::Vec3 m_DescartesCenterPoint;
    Space::Math::ivec3 m_Position;
	float m_Height = 0.01;
};

#endif // HEXGRID_H
