#ifndef _DISK_
#define _DISK_

#include "plane.hpp"

class Disk: public Plane{
public:
  Disk();
  Disk(const Vec3d & _p, const Vec3d & _n, double _r, Material * m);
  Disk(const Disk & d);

  Disk & operator=(const Disk & d);

  void setRadius(double _r){r = _r;}
  double getRadius() const{return r;}

  bool hit(const Ray &, Intersection &);
  void setBVertex(){min = p - r; max = p + r;}
  virtual void applyTransform(Transform *);

  friend std::ostream & operator<<(std::ostream &, const Disk &);

protected:
  double r;
};

std::ostream & operator<<(std::ostream &, const Disk &);


#endif
