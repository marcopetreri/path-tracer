#ifndef _BRDF_
#define _BRDF_

#include <string>
#include "../utilities/texture.hpp"

class Vec3d;
class Intersection;

class Brdf{
public:
  Brdf():  txt(nullptr){}
  Brdf(Texture * _txt): txt(_txt){}
  virtual ~Brdf(){
    delete txt;
  }

  virtual Vec3d evaluate(const Vec3d &, const Vec3d &, Intersection &) = 0;

  virtual Vec3d sample(const Vec3d &, Vec3d &, const Vec3f &, Intersection &) = 0;

  virtual std::string toString() const{return "";}

  Texture * txt;

};

#endif
