#include "HexGrid.h"
float HexGrid::Radius = 1;
double HexGrid::OffsetAngle = 0;
Space::Math::Vec3 HexGrid::m_DescartesCenterPoint;

const double HexGrid::SIN_30 = 0.866025404f;// = sin(PI/6)
const double HexGrid::SIN_60 = 1.047197551f;// = sin(PI/3)
const double HexGrid::SIN_90 = 1.570796326f;// = sin(PI/2)
const double HexGrid::SIN_120 = 2.094395102f;// = sin(PI/2)


Space::Math::Vec3 HexGrid::XAxisN=Space::Math::Vec3(sin(1 *  (SIN_60)), cos(1 *  (SIN_60)), 0);
Space::Math::Vec3 HexGrid::YAxisN=Space::Math::Vec3(sin(-1 * (SIN_60)), cos(-1 * (SIN_60)), 0);
Space::Math::Vec3 HexGrid::ZAxisN=Space::Math::Vec3(sin(0 *  (SIN_60)), cos(0 *  (SIN_60)), 0);


HexGrid HexGrid::Y  (+1, 0, -1);
HexGrid HexGrid::NY = -Y;
HexGrid HexGrid::X  (0, +1, -1);
HexGrid HexGrid::NX = -X;
HexGrid HexGrid::Z  (+1, -1, 0);
HexGrid HexGrid::NZ = -Z;

HexGrid::HexGrid()
{
    init(Space::Math::ivec3(0,0,0));
}

HexGrid::HexGrid(Space::Math::ivec3 position)
{
	init(position);
}

HexGrid::HexGrid(Space::Math::ivec2 position)
{
	init(position);
}

HexGrid::HexGrid(int x, int y, int z)
{
	init(Space::Math::ivec3(x, y, z));
}

HexGrid::HexGrid(int row, int cloumn)
{
    init(Space::Math::ivec2(row, cloumn));
}

Space::Math::ivec3 HexGrid::convertToVec3(int row, int cloumn)
{
    int x = row - (cloumn- (cloumn&1))/2;
    int z = cloumn;
    int y = -x-z;
    return Space::Math::ivec3(x,y,z);
}

Space::Math::ivec2 HexGrid::convertToVec2(int x, int y, int z)
{
    int col = x + (z - (z&1)) / 2;
    int row = z;
    Space::Math::ivec2 result(col, row);
    return result;
}

Space::Math::ivec2 HexGrid::convertToVec2(Space::Math::ivec3 pos)
{
    return convertToVec2(pos.x, pos.y, pos.z);
}

Space::Math::Vec3 HexGrid::getDescartesPosition()
{
    Space::Math::Vec3 outputPosition;
    outputPosition +=  XAxisN * (m_Position.x * (Radius * 1.0));//x
    outputPosition +=  YAxisN * (m_Position.y * (Radius * 1.0));//y
    outputPosition +=  ZAxisN * (m_Position.z * (Radius * 2));//z

    outputPosition += m_DescartesCenterPoint;
    return outputPosition;
}

Space::Math::Vec3 HexGrid::getCornerPosition(int index)
{
	index += 6;
    auto descartesPosition = getDescartesPosition();
    descartesPosition += Space::Math::Vec3(sin(OffsetAngle + index * HexGrid::SIN_60), cos(OffsetAngle + index * HexGrid::SIN_60), 0) * Radius;
	descartesPosition.z = m_Height;
    return descartesPosition;
}

const Space::Math::ivec3 HexGrid::getPosition() const
{
    return m_Position;
}

void HexGrid::setOffsetAngle(double angle)
{
    OffsetAngle = angle;
    XAxisN=Space::Math::Vec3(sin(1 *  (SIN_60+OffsetAngle)), cos(1 *  (SIN_60+OffsetAngle)), 0);
    YAxisN=Space::Math::Vec3(sin(-1 * (SIN_60-OffsetAngle)), cos(-1 * (SIN_60-OffsetAngle)), 0);
    ZAxisN=Space::Math::Vec3(sin(0 *  (SIN_60)+OffsetAngle), cos(0 *  (SIN_60)+OffsetAngle), 0);
}

HexGrid HexGrid::operator -()
{
    auto result = -this->m_Position;
    return HexGrid(result);
}


HexGrid HexGrid::operator +(const HexGrid& a)
{
    Space::Math::ivec3 result = m_Position + a.getPosition();
    return HexGrid(result);
}

HexGrid &HexGrid::operator +=(const HexGrid & a)
{
    HexGrid result(m_Position);
    m_Position = m_Position + a.getPosition();
    return result;
}

HexGrid HexGrid::operator *(const int &a)
{
    auto result = m_Position * a;

    return HexGrid(result);
}


void HexGrid::init(Space::Math::ivec3 position)
{
    m_Position = position;

//    XAxisT=Space::Math::Vec3(sin(-1*  SIN_30), cos(-1*  SIN_30), 0);
//    YAxisT=Space::Math::Vec3(sin(1*   SIN_30), cos(1*   SIN_30), 0);
//    ZAxisT=Space::Math::Vec3(sin(1 *  SIN_60+SIN_30), cos(1 * SIN_60+SIN_30), 0);
}

void HexGrid::init(Space::Math::ivec2 position)
{
    auto result = convertToVec3(position.x, position.y);
    init(result);
}
