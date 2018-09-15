#ifndef _SAMPLER_
#define _SAMPLER_

#include "../geometry/vec3f.hpp"
#include "../utilities/constants.hpp"
#include <random>

class Sampler{
public:
  Sampler(): samples(4), gen(0), dist(0.f, 1.f){}
  Sampler(int s): samples(s), gen(0), dist(0.f, 1.f){}
  virtual ~Sampler(){}

  virtual Vec3f sample() = 0;

  virtual void nextSample() = 0;

  virtual void setSeed(int s){
    gen.seed(s);
  }

  Vec3f sampleScreen(int i, int width){
    div_t px = div(i, width);
    Vec3f sp = sample();
    return Vec3f(px.rem + sp.x, px.quot + sp.y, 0.f);
  }

  virtual std::string toString() const{
    return "{Samples: " + std::to_string(samples) + "}";
  }

  int samples;
  std::mt19937_64 gen;
  std::uniform_real_distribution<float> dist;
};

#endif
