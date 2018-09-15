#ifndef _CONSTANT_INTEGRATOR_
#define _CONSTANT_INTEGRATOR_

#include "integrator.hpp"


class ConstantIntegrator : public Integrator{
public:
  ConstantIntegrator(World * _w): Integrator(w){}
  ~ConstantIntegrator(){}

  Vec3d solve(const Ray & ray) const{
    return traceRay(ray);
  }

  Vec3d traceRay(const Ray & ray) const{
    Vec3d bias;
    Intersection hit;
    Material * mat;
    hit = w->intersectTree(ray);
    w->stats->hits += hit.nHits;
    if(hit.hit){
      hit.hitPoint = ray(hit.t);
      hit.normal = hit.obj_ptr->calcNormal(hit);
      hit.texture = hit.obj_ptr->calcTexture(hit);
      mat = hit.obj_ptr->getMaterial();
      for(u_int i = 0; i < w->lights.size(); ++i){
        Vec3d L = -w->lights[i]->getDirection(hit.hitPoint);
        bias = hit.hitPoint + hit.normal*D_EPS;
        Ray shadowRay = Ray(bias, L);
        Intersection shadowHit = w->intersectTree(shadowRay, w->lights[i]->getDistance(hit.hitPoint));
        if(shadowHit.hit)
          continue;
        // Vec3d a(abs(hit.normal.x),abs(hit.normal.y),abs(hit.normal.z));
        // hit.radiance += NoL*a%lights[i]->getColor()*lights[i]->getIntensity()*lights[i]->getAttenuation(L);
        hit.radiance += mat->shade(-ray.d, L, hit)%w->lights[i]->getColor()*w->lights[i]->getIntensity()*w->lights[i]->getAttenuation(hit.hitPoint);
      }
    }
    else{
      hit.radiance = w->env->getColor(ray.d);
      return hit.radiance;
    }



    return hit.radiance;
  }

  std::string toString() const{}

};


#endif
