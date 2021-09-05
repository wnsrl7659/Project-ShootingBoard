#ifndef __VECTOR2D_H
#define __VECTOR2D_H

#include <cstdint>


class Vector2D
{
private:
  float m_A, m_B;

public:
  Vector2D(float a = 0.f, float b = 0.f); 
  Vector2D(Vector2D const &) = default;   
  Vector2D(Vector2D &&) = default;        

  ~Vector2D() = default;                  


  Vector2D & operator=(Vector2D const &) = default; 
  Vector2D & operator=(Vector2D &&) = default;      

  float & operator[](uint32_t);
  float operator[](uint32_t) const;

  Vector2D operator-() const;
  Vector2D operator+(Vector2D const &) const;
  Vector2D operator-(Vector2D const &) const;
  Vector2D operator*(float) const;
  float operator*(Vector2D const &) const;

  Vector2D & operator+=(Vector2D const &);
  Vector2D & operator-=(Vector2D const &);
  Vector2D & operator*=(float);

  void Zero();
  void Set(float a, float b);
  void Normalize();
  float Length() const;
  float SquareLength() const;
  float Distance(Vector2D const &) const;
  float SquareDistance(Vector2D const &) const;
  void Angle(float);

};

#endif
