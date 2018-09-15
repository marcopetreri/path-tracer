#ifndef _WHITTED_INTEGRATOR_
#define _WHITTED_INTEGRATOR_

#include "integrator.hpp"

class WhittedIntegrator : public Integrator{
public:
  WhittedIntegrator(World * w): Integrator(w), depth(1){}
  WhittedIntegrator(World * w, int d): Integrator(w), depth(d){}
  ~WhittedIntegrator(){}


  Vec3d solve(const Ray & ray) const{
    return traceRay(ray, depth);
  }

  Vec3d traceRay(const Ray & ray, int _depth) const{
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
     if(mat->isEmissive())
      hit.radiance += mat->getEmission(hit.texture);
     for(u_int i = 0; i < w->lights.size(); ++i){
       Vec3d L = -w->lights[i]->getDirection(hit.hitPoint);
       double NoL = L*hit.normal;
       bias = hit.hitPoint + hit.normal*D_EPS;
       if(NoL < D_EPS)
         continue;
       Ray shadowRay = Ray(bias, L);
       Intersection shadowHit = w->intersectTree(shadowRay, w->lights[i]->getDistance(hit.hitPoint));
       if(shadowHit.hit)
         continue;
       hit.radiance += NoL*mat->shade(-ray.d, L, hit)%w->lights[i]->getColor()*w->lights[i]->getIntensity()*w->lights[i]->getAttenuation(hit.hitPoint);
     }

     --_depth;

     if(_depth > 0 && mat->isReflective()){
       ++w->stats->rays;
      //  bias += hit.normal*D_EPS;
       Vec3d R = ray.d.reflect(hit.normal);
       Ray reflection(bias, R);
       hit.radiance += traceRay(reflection, _depth)%mat->getReflection(hit.texture);
     }

    }
    else{
     hit.radiance += w->env->getColor(ray.d);
    }

    return hit.radiance;
  }

  std::string toString() const{
    return "WhittedIntegrator: [ depth: " + std::to_string(depth) + "]";
  }

  int depth;
};

#endif
