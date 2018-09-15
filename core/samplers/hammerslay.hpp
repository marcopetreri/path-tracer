#ifndef _HAMMERSLAY_SAMPLER_
#define _HAMMERSLAY_SAMPLER_

#include "stratified.hpp"

class HammerslaySampler : public StratifiedSampler{
public:
  HammerslaySampler(): StratifiedSampler(){}
  HammerslaySampler(int s): StratifiedSampler(s){}
  ~HammerslaySampler(){}

  Vec3f sample(){
    return Vec3f(current*invSamples, halton(current, 2), 0.f);
  }

  std::string toString() const{
    return "HammerslaySampler: " + Sampler::toString();
  }

};

#endif
