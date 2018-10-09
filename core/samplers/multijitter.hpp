#ifndef _MULTIJITTER_SAMPLER_
#define _MULTIJITTER_SAMPLER_

#include "stratified.hpp"

class MultijitterSampler : public StratifiedSampler{
public:
  MultijitterSampler(): StratifiedSampler(), seed(0){}
  MultijitterSampler(int s): StratifiedSampler(s), seed(0){}
  ~MultijitterSampler(){}

  Vec3f sample(){
    div_t xy = div((int)current, (int)n);
    u_int px = permute(xy.rem, n, seed*0xa511e9b3);
    u_int py = permute(xy.quot, n, seed*0x63d83595);
    float jx = randfloat(current, seed*0xa399d265);
    float jy = randfloat(current, seed*0x711ad6a5);
    return Vec3f((xy.rem + (py+jx)*invN), (xy.quot + (px+jy)*invN), 0)*invN;
  }

  void setSeed(int s){
    seed = s;
  }

  std::string toString() const{
    return "MultijitterSampler: " + Sampler::toString();
  }

  int seed;
};


#endif
