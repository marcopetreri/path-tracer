#ifndef _LABERT_BRDF_
#define _LABERT_BRDF_

#include "brdf.hpp"
#include "../utilities/intersection.hpp"
#include "../utilities/constants.hpp"

class Lambert: public Brdf{
public:
  Lambert(): Brdf(), albedo(1.), kd(1.){}
  Lambert(const Vec3d & a): Brdf(), albedo(a), kd(1.){}
  Lambert(const Vec3d & a, double _kd): Brdf(), albedo(a), kd(_kd){}
  Lambert(Texture *_txt): Brdf(_txt), kd(1.){}
  Lambert(Texture *_txt, double _kd): Brdf(_txt), kd(_kd){}
  ~Lambert(){}

  Vec3d evaluate(const Vec3d & wo, const Vec3d & wi, Intersection & hit){
    if(txt)
      return kd*txt->getValue(hit.texture)*invPI;
    else
      return kd*albedo*invPI;
  }

  Vec3d sample(const Vec3d & wo, Vec3d & wi, const Vec3f & xi, Intersection & hit){
    wi = (hit.TBN->operator*(Vec4d(toCosineHemisphere(xi), 0.))).xyz().hat();
    return evaluate(wo, wi, hit)*PI;
  }

  std::string toString() const{
    return "Lambert: [ Albedo: " + albedo.toString() + ", Kd: " + std::to_string(kd) + ", " + (txt ? txt->toString() : "null") + "]";
  }

  Vec3d albedo;
  double kd;
};

#endif
