#ifndef _POINT_LIGHT_
#define _POINT_LIGHT_

#include "light.hpp"

class PointLight: public Light{
public:
  PointLight(): Light(), p(){}
  PointLight(double i, const Vec3d & _c, const Vec3d & _p): Light(i, _c), p(_p){}
  PointLight(const PointLight & pl): Light(pl), p(pl.p){}

  PointLight & operator=(const PointLight & pl){
    Light::operator=(pl);
    p = pl.p;
    return *this;
  }

  void setPosition(const Vec3d & _p){p = _p;}
  Vec3d getPosition() const{return p;}
  Vec3d getDirection(const Vec3d & p1) const{return (p1 - p).hat();}
  double getAttenuation(const Vec3d & p1) const{return 1./std::max(1.,(p1-p).lengthSq()*.01);}
  double getDistance(const Vec3d & p1) const{return (p1 - p).length();}

  std::string toString() const{
    return "PointLight: " + Light::toString() + ", Position: " + p.toString();
  }

private:
  Vec3d p;
};

#endif
