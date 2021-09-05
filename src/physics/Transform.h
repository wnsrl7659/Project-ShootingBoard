#ifndef __TRANSFORM_H
#define __TRANSFORM_H

#include "Vector2D.h"
#include "Matrix2D.h"

class Transform
{
private:
  Vector2D m_Translation;
  Vector2D m_Scale;
  float m_Angle;

  Vector2D oldTranslation;
  Vector2D oldScale;
  float oldAngle;

  Matrix2D oldMatrix;

  Matrix2D m_Matrix;

  bool m_MatrixDirty;

public:
  Transform();

  Transform(Transform const &) = default; 
  Transform(Transform &&) = default;      

  ~Transform() = default;                 

  Transform & operator=(Transform const &) = default; 
  Transform & operator=(Transform &&) = default;      

  operator Matrix2D();

  Vector2D const & Translation() const;
  Vector2D const& OldTranslation() const {
	  return oldTranslation;
  };
  float Rotation() const;
  float OldRotation() const {
	  return oldAngle;
  };
  Vector2D const & Scale() const;
  Vector2D const& OldScale() const { return oldScale; };
  void Translation(Vector2D const &);
  void OldTranslation(Vector2D const& t) { oldTranslation = t; };
  void Rotation(float);
  void OldRotation(float r) { oldAngle; };
  void Scale(Vector2D const &);
  void OldScale(Vector2D const& s) { oldScale = s; };

  bool isDirty() const { return m_MatrixDirty; };

private:

}; 

#endif
