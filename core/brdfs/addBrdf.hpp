#ifndef _ADD_BRDF_
#define _ADD_BRDF_

#include "multipleBrdf.hpp"
#include "../geometry/vec3d.hpp"

class AddBrdf : public MultipleBrdf{
public:
  AddBrdf(){}
  AddBrdf(Brdf * b): MultipleBrdf(b){}
  AddBrdf(const std::vector<Brdf *> & bv): MultipleBrdf(bv){}
  ~AddBrdf(){}

  Vec3d evaluate(const Vec3d & wo, const Vec3d & wi, Intersection & hit) const{
    Vec3d out;
    for(auto & x : brdfs){
      out += x->evaluate(wo, wi, hit);
    }
    return out;
  }

  std::string toString() const{
    return "AddBrdf: " + MultipleBrdf::toString();
  }

};

#endif
