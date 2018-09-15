#ifndef _PRIMITIVE_
#define _PRIMITIVE_

#include "../geometry/vec3d.hpp"
#include "../materials/material.hpp"
#include <memory>

class Ray;
class Intersection;
class Transform;

class Primitive{
public:
  Primitive(): mat_ptr(new Material()), min(), max(){}
  Primitive(Material * m): mat_ptr(m){}
  Primitive(const Primitive & p): mat_ptr(p.mat_ptr), min(p.min), max(p.max){}
  virtual ~Primitive(){} // NOTE: serve o no?

  Primitive & operator=(const Primitive & p){
    mat_ptr = p.mat_ptr; min = p.min; max = p.max;
    return *this;
  }

  void setMaterial(Material * m){mat_ptr = m;}
  void setMin(const Vec3d & m){min = m;}
  void setMax(const Vec3d & m){max = m;}
  Material * getMaterial() const{return mat_ptr;}
  Vec3d getMin() const{return min;}
  Vec3d getMax() const{return max;}

  virtual bool hit(const Ray &, Intersection & ) = 0; //NOTE: forse non serve piu il return bool
  virtual Vec3d calcNormal(Intersection &) const = 0;
  virtual Vec3d calcTangent(Intersection &) const = 0;
  virtual Vec3d calcTexture(Intersection &) const = 0;
  virtual void setBVertex() = 0;
  virtual void applyTransform(Transform *) = 0;

protected:
  Material * mat_ptr;
  Vec3d min, max;
};

#endif
