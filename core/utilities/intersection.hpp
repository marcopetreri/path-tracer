#ifndef _INTERSECTION_
#define _INTERSECTION_

#include "../geometry/vec3d.hpp"
#include "../geometry/transform.hpp"

class Primitive;

class Intersection{
public:
  Intersection(): hit(false), nHits(0), t(0.), u(0.), v(0.), hitPoint(), normal()
                  , radiance(), texture(), obj_ptr(nullptr), TBN(nullptr){}
  Intersection(const Intersection & i): hit(i.hit), nHits(i.nHits), t(i.t), u(i.u)
                                      , v(i.v), hitPoint(i.hitPoint)
                                      , normal(i.normal), radiance(i.radiance)
                                      , texture(i.texture), obj_ptr(i.obj_ptr), TBN(i.TBN){}
  ~Intersection(){
    delete TBN;
  }

  Intersection & operator=(const Intersection & i){
    t = i.t; u = i.u; v = i.v; hit = i.hit; nHits = i.nHits; hitPoint = i.hitPoint;
    normal = i.normal; radiance = i.radiance; texture = i.texture; obj_ptr = i.obj_ptr;
    delete TBN;
    TBN = i.TBN;
    return *this;
  }

  bool hit;
  long int nHits;
  double t, u, v;
  Vec3d hitPoint, normal, radiance, texture;
  Primitive * obj_ptr;
  Mat4d * TBN;
};

inline std::ostream & operator<<(std::ostream & os, const Intersection & it){
  return os << "Inters - " << "hit: " << it.hit << " - nHits: " << it.nHits << " - t: "
            << it.t << " - uv: [" << it.u << ", " << it.v << "]" << " - HitPoint: "
            << it.hitPoint << " - Normal: " << it.normal << " - Radiance: " << it.radiance
            << " - Ptr: " << it.obj_ptr;
}


#endif
