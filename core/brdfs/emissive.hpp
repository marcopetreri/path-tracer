#ifndef _EMISSIVE_BRDF_
#define _EMISSIVE_BRDF_

#include "brdf.hpp"
#include "../utilities/texture.hpp"
#include "../utilities/intersection.hpp"

class Emissive : public Brdf{
public:
  Emissive(): Brdf(), emission(0.), ke(1.){}
  Emissive(const Vec3d & e): Brdf(), emission(e), ke(1.){}
  Emissive(const Vec3d & e, double _ke): Brdf(), emission(e), ke(_ke){}
  Emissive(Texture * _txt): Brdf(_txt), ke(1.){}
  Emissive(Texture * _txt, double _ke): Brdf(_txt), ke(_ke){}
  ~Emissive(){}

  Vec3d evaluate(const Vec3d & wo, const Vec3d & wi, Intersection & hit) const{
    if(txt)
      return ke*txt->getValue(hit.texture);
    else
      return ke*emission;
  }

  std::string toString() const{
    return "Emissive: [ Emission: " + emission.toString() + ", Ke: " + std::to_string(ke) + ", " + (txt ? txt->toString() : "null") + "]";
  }

  Vec3d emission;
  double ke;
};

#endif
