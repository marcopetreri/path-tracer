#ifndef _RING_
#define _RING_

#include "disk.hpp"

class Ring: public Disk{
public:
  Ring();
  Ring(const Vec3d & _p, const Vec3d & _n, double _r, double _r1, Material * m);
  Ring(const Ring & r);

  Ring & operator=(const Ring & r);

  void setRadius1(double _r1){r1 = _r1;}
  double getRadius1() const{return r1;}

  bool hit(const Ray &, Intersection &);
  void applyTransform(Transform *);

  friend std::ostream & operator<<(std::ostream &, const Ring &);

private:
  double r1;
};

std::ostream & operator<<(std::ostream &, const Ring &);

#endif
