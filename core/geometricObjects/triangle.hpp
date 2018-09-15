#ifndef _TRIANGLE_
#define _TRIANGLE_

#include "primitive.hpp"

class Triangle: public Primitive{
public:
  Triangle();
  Triangle(const Vec3d & _p0, const Vec3d & _p1, const Vec3d & _p2
          ,const Vec3d & _n0, const Vec3d & _n1, const Vec3d & _n2
          ,const Vec3d & _t0, const Vec3d & _t1, const Vec3d & _t2
          ,const Vec3d & _tn0, const Vec3d & _tn1, const Vec3d & _tn2
          ,Material * m);
  Triangle(const Triangle & t);

  Vec3d operator[](int);
  Triangle & operator=(const Triangle & t);

  bool hit(const Ray &, Intersection &);
  Vec3d calcNormal(Intersection &) const;
  Vec3d calcTangent(Intersection & hit) const;
  Vec3d calcTexture(Intersection &) const;
  void applyTransform(Transform *);
  void setBVertex();

  friend std::ostream & operator<<(std::ostream &, const Triangle &);

  Vec3d p0, p1, p2;
  Vec3d n0, n1, n2;
  Vec3d t0, t1, t2;
  Vec3d tn0, tn1, tn2;
  Vec3d e1, e2, n;

};

std::ostream & operator<<(std::ostream &, const Triangle &);

#endif
