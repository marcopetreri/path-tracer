#ifndef _COOK_TORRANCE_BRDF_
#define _COOK_TORRANCE_BRDF_

#include "brdf.hpp"
#include "../utilities/texture.hpp"
#include "../utilities/intersection.hpp"

extern int px, py;

class CookTorrance: public Brdf{
public:
  CookTorrance(): Brdf(), F0(1.), r(1.), kf(1.), rmap(nullptr){}
  CookTorrance(const Vec3d & s, double _r): Brdf(), F0(s), r(_r), kf(1.), rmap(nullptr){}
  CookTorrance(Texture * _smap, double _r, double _kf): Brdf(_smap), r(_r), kf(_kf), rmap(nullptr){}
  CookTorrance(const Vec3d & s, Texture * _rmap, double _kr): Brdf(), F0(s), kr(_kr), rmap(_rmap){}
  CookTorrance(Texture * _smap, Texture * _rmap, double _kf, double _kr): Brdf(_smap), kf(_kf), kr(_kr), rmap(_rmap){}
  ~CookTorrance(){
    delete rmap;
  }

  Vec3d evaluate(const Vec3d & wo, const Vec3d & wi, Intersection & hit){
    Vec3d H = (wo + wi).hat();
    double NoWi = hit.normal*wi, NoWo = hit.normal*wo;
    return D(hit.normal*H, hit.texture)*F(wi*H, hit.texture)*G(NoWi, NoWo, hit.texture)/(4*NoWi*NoWo);
  }

  Vec3d sample(const Vec3d & wo, Vec3d & wi, const Vec3f & xi, Intersection & hit){
    double a = getR(hit.texture);
    a *= a;
    double phi = TWO_PI*xi.x;
    double costheta = sqrt((1. - xi.y)/((a*a - 1.)*xi.y + 1.));
    double sintheta = sqrt(1. - costheta*costheta);
    Vec3d H(sintheta*cos(phi), sintheta*sin(phi), costheta);
    H = (hit.TBN->operator*(Vec4d(H, 0.))).xyz().hat();
    double HoWo = H*wo;
    if(HoWo < D_EPS)
      return Vec3d();
    wi = (-wo).reflect(H);
    double NoH = hit.normal*H;
    return evaluate(wo, wi, hit)/(D(NoH, hit.texture)*NoH)*(4.*HoWo);
  }

  double D(double NoH, const Vec3d & uv) const{
    double a = getR(uv);
    a *= a;
    double x = a/(NoH*NoH*(a*a - 1.) + 1.);
    return x*x*invPI;
  }

  Vec3d F(double WioH, const Vec3d & uv) const{
    Vec3d f0 = getS(uv);
    return f0 + (Vec3d(1.) - f0)*pow(1. - WioH, 5);
  }

  double G(double NoWi, double NoWo, const Vec3d & uv) const{
    double k = getR(uv);
    k *= k*.5;
     return G1(NoWi, k)*G1(NoWo, k);
  }

  double G1(double NoW, double k) const{
    return NoW/(NoW*(1. - k) + k);
  }

  Vec3d getS(const Vec3d & uv) const{
    if(txt)
      return txt->getValue(uv)*kf;
    else
      return F0;
  }

  double getR(const Vec3d & uv) const{
    if(rmap)
      return rmap->getValue(uv)[0]*kr;
    else
      return r;
  }

  std::string toString() const{
    std::string s;
    if(txt)
      s += "sMap: " + txt->toString() + ", kf: " + std::to_string(kf);
    else
      s += "Specular: " + F0.toString();
    if(rmap)
      s += ", rMap: " + rmap->toString() + ", kr: " + std::to_string(kr);
    else
      s += ", Roughness: " + std::to_string(r);

    return "CookTorrance: [ " + s + "]";
  }

  Vec3d F0;
  double r, kf, kr;
  Texture * rmap;
};


#endif
