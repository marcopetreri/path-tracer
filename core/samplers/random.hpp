#ifndef _RANDOM_SAMPLER_
#define _RANDOM_SAMPLER_

#include "sampler.hpp"

class RandomSampler : public Sampler{
public:
  RandomSampler(): Sampler(){}
  RandomSampler(int s): Sampler(s){}
  ~RandomSampler(){}

  Vec3f sample(){
    return Vec3f(dist(gen), dist(gen), 0.f);
  }

  void nextSample(){}

  std::string toString() const{
    return "RandomSampler: " + Sampler::toString();
  }

};

#endif
