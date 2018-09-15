#ifndef _STRATIFIED_SAMPLER_
#define _STRATIFIED_SAMPLER_

#include "sampler.hpp"
#include "../utilities/math.hpp"

class StratifiedSampler : public Sampler{
public:
  StratifiedSampler(): Sampler(), current(0), n(sqrt(samples)), invN(1.f/n), invSamples(1.f/samples){}
  StratifiedSampler(int s): Sampler(s), current(0), n(sqrt(s)), invN(1.f/n), invSamples(1.f/samples){}
  virtual ~StratifiedSampler(){}

  void nextSample(){
    ++current %= samples;
  }

  u_int current;
  u_int n;
  float invN, invSamples;
};


#endif
