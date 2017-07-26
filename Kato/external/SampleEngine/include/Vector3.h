#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
  public:
    typedef float real;

    real m_x, m_y, m_z;
    Vector3();
    Vector3(real x, real y, real z);

    void Set(real x, real y, real z);
    void Set(const Vector3& rhs);

    void SetZero();

    bool IsZeroVector() const;

    float Length() const;
    float LengthSquared() const;

    float Distance(const Vector3& rhs) const;
    float DistanceSquared(const Vector3& rhs) const;

    Vector3& Normalize();
    Vector3 GetNormalized(const Vector3& rhs) const;

    real DotProduct(const Vector3& rhs) const;
    Vector3 CrossProduct(const Vector3& rhs) const;

    Vector3 operator+(const Vector3& rhs) const;
    Vector3& operator+=(const Vector3& rhs);
    Vector3 operator-(const Vector3& rhs) const;
    Vector3& operator-=(const Vector3& rhs);

    Vector3 operator*(real rhs) const;
    Vector3& operator*=(real rhs);

    //******************************IMTIRED******************************
    //Vector3 operator/(real rhs) const;
    //Vector3& operator/=(real rhs);
    //******************************IMTIRED******************************

    Vector3 operator-() const;
    bool operator==(const Vector3& rhs) const;
    bool operator!=(const Vector3& rhs) const;

  private:
};

#endif