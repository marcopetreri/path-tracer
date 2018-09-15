#ifndef _PLANE_
#define _PLANE_

#include "primitive.hpp"
#include "../geometry/vec3d.hpp"

class Intersection;

class Plane: public Primitive{
public:
  Plane();
  Plane(const Vec3d _p, const Vec3d & _n, Material * m);
  Plane(const Plane & pl);

  Plane & operator=(const Plane & pl);

  void setPoint(const Vec3d & _p){p = _p;}
  void setNormal(const Vec3d & _n){n = _n;}
  Vec3d getPoint() const{return p;}
  Vec3d getNormal() const{return n;}

  virtual bool hit(const Ray &, Intersection &);
  Vec3d calcNormal(Intersection & hit) const{return n;}
  virtual Vec3d calcTexture(Intersection &) const{}
  virtual void applyTransform(Transform *);
  virtual void setBVertex();

  friend std::ostream & operator<<(std::ostream &, const Plane &);

protected:
  Vec3d p;
  Vec3d n;
};

std::ostream & operator<<(std::ostream &, const Plane &);

#endif
