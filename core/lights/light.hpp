#ifndef _LIGHT_
#define _LIGHT_

#include "../geometry/vec3d.hpp"

class Light{
public:
  Light(): intensity(1.), c(1.){}
  Light(double i, const Vec3d & _c): intensity(i), c(_c){}
  Light(const Light & l): intensity(l.intensity), c(l.c){}
  virtual ~Light(){}

  Light & operator=(const Light & l){
    intensity = l.intensity; c = l.c;
    return *this;
  }

  void setIntensity(double i){intensity = i;}
  void setColor(const Vec3d & _c){c = _c;}
  double getIntensity() const{return intensity;}
  Vec3d getColor() const{return c;}
  virtual Vec3d getDirection(const Vec3d &) const = 0;
  virtual double getAttenuation(const Vec3d &) const = 0;
  virtual double getDistance(const Vec3d &) const = 0;

  virtual std::string toString() const{
    return "Power: " + std::to_string(intensity) + ", Color: " + c.toString();
  }

protected:
  double intensity;
  Vec3d c;
};

#endif
