#ifndef _INTEGRATOR_
#define _INTEGRATOR_

#include "../geometry/vec3d.hpp"
#include "../geometry/ray.hpp"
#include "../lights/light.hpp"
#include "../utilities/environment.hpp"
#include "../utilities/stats.hpp"
#include "../world.hpp"

class Integrator{
public:
  Integrator(World * _w): w(_w){}
  virtual ~Integrator(){}

  virtual Vec3d solve(const Ray &) const = 0;

  virtual std::string toString() const = 0;

  World * w;
};


#endif
