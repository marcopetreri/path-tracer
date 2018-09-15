#ifndef _TRANSFORM_
#define _TRANSFORM_

#include "mat4d.hpp"

class Vec3d;

class Transform{
public:
  Transform();
  Transform(const Vec3d &, const Vec3d &, const Vec3d &, const Vec3d &);
  Transform(const Vec4d &, const Vec4d &, const Vec4d &, const Vec4d &);
  Transform(Mat4d *);
  Transform(Mat4d *, Mat4d *, Mat4d *);
  Transform(const Transform &);
  ~Transform();

  Transform operator*(const Transform &) const;
  Transform & operator*=(const Transform &);
  Transform & operator=(const Transform &);

  void inverse();

  Mat4d * m, * mInv, * mTrInv;
};

Transform translation(double, double, double);
Transform scaling(double);
Transform scaling(double, double, double);
Transform rotationX(double);
Transform rotationY(double);
Transform rotationZ(double);



#endif
