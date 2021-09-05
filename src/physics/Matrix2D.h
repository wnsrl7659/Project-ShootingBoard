#ifndef __MATRIX2D_H
#define __MATRIX2D_H

#include <cstdint>

class Vector2D;

class Matrix2D
{
private:
  float m_Matrix[3][3];

public:
  Matrix2D(float * arr = nullptr);      
  Matrix2D(Matrix2D const &) = default; 
  Matrix2D(Matrix2D &&) = default;      

  ~Matrix2D() = default;                

  Matrix2D & operator=(Matrix2D const &) = default; 
  Matrix2D & operator=(Matrix2D &&) = default;      

  float * operator[](uint32_t);
  float const * operator[](uint32_t) const;

  Vector2D operator*(Vector2D const &);
  Matrix2D operator*(Matrix2D const &);

  void Identity();
  void Transpose();
  void Translate(float x, float y);
  void Translate(Vector2D const &);
  void Scale(float x, float y);
  void Rotate(float rad);

};

#endif
