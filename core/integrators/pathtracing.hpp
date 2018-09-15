#ifndef _PATHTRACING_INTEGRATOR_
#define _PATHTRACING_INTEGRATOR_

#include "integrator.hpp"
#include "../samplers/sampler.hpp"

extern int px, py;

class PathTracingIntegrator : public Integrator{
public:
  PathTracingIntegrator(World * w): Integrator(w){}
  PathTracingIntegrator(World * w, int d): Integrator(w), depth(d){}

  Vec3d solve(const Ray & ray) const{
    return traceRay(ray, depth);
  }

  Vec3d traceRay(const Ray & ray, int _depth) const{
    Vec3d bias;
    Intersection hit;
    Material * mat;
    Vec3d t;
    hit = w->intersectTree(ray);
    w->stats->hits += hit.nHits;
    if(hit.hit){
      hit.hitPoint = ray(hit.t);
      hit.normal = hit.obj_ptr->calcNormal(hit);
      t = hit.obj_ptr->calcTangent(hit);
      hit.texture = hit.obj_ptr->calcTexture(hit);
      mat = hit.obj_ptr->getMaterial();
      hit.TBN = new Mat4d(t, hit.normal^t, hit.normal, Vec3d(0));
      if(mat->normalMap){
        Vec3d n = mat->normalMap->getValue(Vec3d(hit.texture.x, 1. - hit.texture.y, 0.));
        n.x = n.x*2 - 1;
        n.y = n.y*2 - 1;
        hit.normal = (hit.TBN->operator*(Vec4d(n, 0.))).xyz().hat();
        // *hit.TBN = Mat4d(t, hit.normal^t, hit.normal, Vec3d(0));
      }
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
        // hit.radiance = hit.normal;
        // hit.radiance = t;
        // hit.radiance = hit.normal^t;
      }

      --_depth;

      if(_depth > 0){
        ++w->stats->rays;
        Vec3d smpDir;
        Vec3d f = mat->sampleMaterial(-ray.d, smpDir, w->sampler->sample(),  hit);
        if(f == Vec3d())
          return hit.radiance;
        // smpDir.normalize();
        Ray rayInd(bias, smpDir);
        double NoD = hit.normal*smpDir;
        if(NoD < D_EPS)
          return hit.radiance;
        hit.radiance += NoD*traceRay(rayInd, _depth)%f;
      }

    }
    else{
      hit.radiance += w->env->getColor(ray.d);
    }

    return hit.radiance;
  }

  std::string toString() const{
    return "PathTracingIntegrator: [ depth: " + std::to_string(depth) + "]";
  }


  int depth;
};

#endif
