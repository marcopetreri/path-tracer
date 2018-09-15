#ifndef _SPHERE_
#define _SPHERE_

#include "primitive.hpp"
#include "../geometry/vec3d.hpp"
#include "../utilities/intersection.hpp"

class Sphere: public Primitive{
public:
  Sphere();
  Sphere(const Vec3d &, double, Material *);
  Sphere(const Sphere &);

  Sphere & operator=(const Sphere & s);

  void setCenter(const Vec3d & _c){c = _c;}
  void setRadius(double _r){r = _r;}
  Vec3d getCenter() const{return c;}
  double getRadius() const{return r;}

  bool hit(const Ray &, Intersection &);
  Vec3d calcNormal(Intersection & hit) const{return (hit.hitPoint - c)/r;}
  Vec3d calcTangent(Intersection & hit) const;
  Vec3d calcTexture(Intersection &) const;
  void applyTransform(Transform *);
  void setBVertex(){min = c - r; max = c + r;}

  friend std::ostream & operator<<(std::ostream & os, const Sphere &);

private:
  Vec3d c;
  double r;
};

std::ostream & operator<<(std::ostream & os, const Sphere &);


#endif
