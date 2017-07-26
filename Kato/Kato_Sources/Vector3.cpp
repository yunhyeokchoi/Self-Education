#include "Vector3.h"

//YJK : Include cmath file to use sqrt function?
#include <cmath>


Vector3::Vector3()
  : m_x(0), m_y(0), m_z(0)
{}

Vector3::Vector3(real x, real y, real z)
  : m_x(x), m_y(y), m_z(z)
{}

void Vector3::Set(real x, real y, real z)
{
  m_x = x;
  m_y = y;
  m_z = z;
}

void Vector3::Set(const Vector3& rhs)
{
  m_x = rhs.m_x;
  m_y = rhs.m_y;
  m_z = rhs.m_z;
}

void Vector3::SetZero()
{
  m_x = 0;
  m_y = 0;
  m_z = 0;
}

bool Vector3::IsZeroVector() const
{
  return (m_x == 0) && (m_y == 0) && (m_z == 0);
}

float Vector3::Length() const
{
  return sqrt(LengthSquared());
}

float Vector3::LengthSquared() const
{
  return m_x * m_x + m_y * m_y + m_z * m_z;
}

float Vector3::Distance(const Vector3& rhs) const
{
  return sqrt(DistanceSquared(rhs));
}

float Vector3::DistanceSquared(const Vector3& rhs) const
{
  //rhs - lhs
  Vector3 rhsmlhs(rhs.m_x - m_x,
                  rhs.m_y - m_y,
                  rhs.m_z - m_z);

  return rhsmlhs.LengthSquared();
}

Vector3& Vector3::Normalize()
{
  Vector3 normv = GetNormalized(*this);

  *this = normv;

  return *this;
}

Vector3 Vector3::GetNormalized(const Vector3& rhs) const
{
  real len = rhs.Length();

  Vector3 ret = Vector3(rhs);

  if (len != 0)
  {
    ret.m_x *= (1 / len);
    ret.m_y *= (1 / len);
    ret.m_z *= (1 / len);
  }

  return ret;
}

Vector3::real Vector3::DotProduct(const Vector3& rhs) const
{
  return m_x * rhs.m_x + m_y * rhs.m_y + m_z * rhs.m_z;
}

Vector3 Vector3::CrossProduct(const Vector3& rhs) const
{
  /*
    x1 x2
    y1 y2
    z1 z2
  */
  return Vector3(m_y * rhs.m_z - m_z * rhs.m_y,
               -(m_x * rhs.m_z - m_z * rhs.m_y),
                 m_x * rhs.m_y - m_y * rhs.m_x);
}

Vector3 Vector3::operator+(const Vector3& rhs) const
{
  return Vector3(m_x + rhs.m_x,
                 m_y + rhs.m_y,
                 m_z + rhs.m_z);
}

Vector3& Vector3::operator+=(const Vector3& rhs)
{
  m_x += rhs.m_x;
  m_y += rhs.m_y;
  m_z += rhs.m_z;

  return *this;
}

Vector3 Vector3::operator-(const Vector3& rhs) const
{
  return Vector3(m_x - rhs.m_x,
                 m_y - rhs.m_y,
                 m_z - rhs.m_z);
}

Vector3& Vector3::operator-=(const Vector3& rhs)
{
  m_x -= rhs.m_x;
  m_y -= rhs.m_y;
  m_z -= rhs.m_z;

  return *this;
}

Vector3 Vector3::operator*(real rhs) const
{
  return Vector3(m_x * rhs, m_y * rhs, m_z * rhs);
}

Vector3& Vector3::operator*=(real rhs)
{
  m_x *= rhs;
  m_y *= rhs;
  m_z *= rhs;

  return *this;
}

//******************************IMTIRED******************************
//Vector3 Vector3::operator/(real rhs) const
//{
//  return Vector3(m_x / rhs, m_y / rhs, m_z / rhs);
//}
//
//Vector3& Vector3::operator/=(real rhs)
//{
//  m_x /= rhs;
//  m_y /= rhs;
//  m_z /= rhs;
//
//  return *this;
//}
//******************************IMTIRED******************************

Vector3 Vector3::operator-() const
{
  return Vector3(-m_x, -m_y, -m_z);
}

bool Vector3::operator==(const Vector3& rhs) const
{
  return (m_x == rhs.m_x) && (m_y == rhs.m_y) && (m_z == rhs.m_z);
}

bool Vector3::operator!=(const Vector3& rhs) const
{
  return (m_x != rhs.m_x) || (m_y != rhs.m_y) || (m_z != rhs.m_z);
}