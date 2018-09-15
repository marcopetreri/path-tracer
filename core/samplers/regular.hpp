#ifndef _REGULAR_SAMPLER_
#define _REGULAR_SAMPLER_

#include "sampler.hpp"

class RegularSampler : public Sampler{
public:
  RegularSampler(): Sampler(1){}
  ~RegularSampler(){}

  Vec3f sample(){
    return Vec3f(0.f);
  }

  void nextSample(){}

  std::string toString() const{
    return "RegularSampler: " + Sampler::toString();
  }

};

#endif
