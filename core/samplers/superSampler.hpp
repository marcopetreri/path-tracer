#ifndef _SUPER_SAMPLER_
#define _SUPER_SAMPLER_

#include "stratified.hpp"

class SuperSampler : public StratifiedSampler{
public:
  SuperSampler(): StratifiedSampler(){}
  SuperSampler(int s): StratifiedSampler(s){}
  ~SuperSampler(){}

  Vec3f sample(){
    div_t xy = div((int)current, (int)n);
    return Vec3f(xy.rem , xy.quot, 0.f)*invN;
  }

  std::string toString() const{
    return "SuperSampler: " + Sampler::toString();
  }

};


#endif
