#ifndef _BLINN_BRDF_
#define _BLINN_BRDF_

#include "brdf.hpp"
#include "../utilities/texture.hpp"
#include "../utilities/intersection.hpp"

class Blinn: public Brdf{
public:
  Blinn(): Brdf(), specular(1.), ks(1.), alpha(2048){}
  Blinn(const Vec3d & s, int a): Brdf(), specular(s), ks(1.), alpha(a){}
  Blinn(const Vec3d & s, double _ks, int a): Brdf(), specular(s), ks(_ks), alpha(a){}
  Blinn(Texture * _txt, int a): Brdf(_txt), ks(1.), alpha(a){}
  Blinn(Texture * _txt, double _ks, int a): Brdf(_txt), ks(_ks), alpha(a){}
  ~Blinn(){}

  Vec3d evaluate(const Vec3d & wo, const Vec3d & wi, Intersection & hit){
    Vec3d H = (wo + wi).hat();
    if(txt)
      return ks*txt->getValue(hit.texture)*pow(hit.normal*H,alpha);
    else
      return ks*specular*pow(hit.normal*H,alpha);
  }

  Vec3d sample(const Vec3d & wo, Vec3d & wi, const Vec3f & xi, Intersection & hit){
    wi = (-wo).reflect(hit.normal);
    return evaluate(wo, wi, hit);
    // wi = (hit.TBN->operator*(Vec4d(toHemisphere(xi), 0.))).xyz().hat();
    // return evaluate(wo, wi, hit)*TWO_PI;
  }

  std::string toString() const{
    return "Blinn: [ Specular: " + specular.toString() + ", Ks: " + std::to_string(ks) + ", Alpha: " + std::to_string(alpha) + ", " + (txt ? txt->toString() : "null") + "]";
  }

  Vec3d specular;
  double ks;
  int alpha;
};


#endif
