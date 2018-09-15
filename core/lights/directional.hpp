#ifndef _DIRECTIONAL_LIGHT_
#define _DIRECTIONAL_LIGHT_

#include "light.hpp"
#include <limits>


class DirectionalLight: public Light{
public:
  DirectionalLight(): Light(), dir(-1., 0., 0.){}
  DirectionalLight(double i, const Vec3d & _c, const Vec3d & _dir): Light(i, _c), dir(_dir.hat()){}
  DirectionalLight(const DirectionalLight & dl): Light(dl.intensity, dl.c), dir(dl.dir){}

  DirectionalLight & operator=(const DirectionalLight & dl){
    Light::operator=(dl);
    dir = dl.dir;
    return *this;
  }

  void setDirection(const Vec3d & d){dir = d.hat();}
  Vec3d getDirection(const Vec3d & p) const{return dir;}
  double getAttenuation(const Vec3d & d) const{return 1.f;}
  double getDistance(const Vec3d & p) const{return std::numeric_limits<double>::max();}

  std::string toString() const{
    return "DirectionalLight: " + Light::toString() + ", Direction: " + dir.toString();
  }

private:
  Vec3d dir;
};


#endif
