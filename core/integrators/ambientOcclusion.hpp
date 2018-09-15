#ifndef _AO_INTEGRATOR_
#define _AO_INTEGRATOR_

#include "integrator.hpp"
#include "../samplers/sampler.hpp"

class AmbientOcclusionIntegrator : public Integrator{
public:
  AmbientOcclusionIntegrator(World * w): Integrator(w), depth(2){}

  Vec3d solve(const Ray & ray) const{
    return traceRay(ray, depth);
  }

  Vec3d traceRay(const Ray & ray, int _depth) const{
    // Vec3d bias;
    Intersection hit;
    // Material * mat;
    // Mat4d TBN;
    // Vec3d t;
    // hit = w->intersectTree(ray);
    // w->stats->hits += hit.nHits;
    // if(hit.hit){
    //   hit.hitPoint = ray(hit.t);
    //   hit.normal = hit.obj_ptr->calcNormal(hit);
    //   hit.texture = hit.obj_ptr->calcTexture(hit);
    //   mat = hit.obj_ptr->getMaterial();
    //   t = hit.obj_ptr->calcTangent(hit);
    //   TBN = Mat4d(t, hit.normal^t, hit.normal, Vec3d(0));
    //   // if(mat->normalMap)
    //   // hit.normal = (hit.TBN.m->operator*(Vec4d(mat->normalMap->getValue(hit.texture)*2. - 1., 0.))).xyz().hat();
    //   for(u_int i = 0; i < w->lights.size(); ++i){
    //     Vec3d L = -w->lights[i]->getDirection(hit.hitPoint);
    //     double NoL = L*hit.normal;
    //     bias = hit.hitPoint + hit.normal*D_EPS;
    //     if(NoL < D_EPS)
    //       continue;
    //     Ray shadowRay = Ray(bias, L);
    //     Intersection shadowHit = w->intersectTree(shadowRay, w->lights[i]->getDistance(hit.hitPoint));
    //     if(shadowHit.hit)
    //       continue;
    //     // hit.radiance += NoL*mat->shade(-ray.d, L, hit)%w->lights[i]->getColor()*w->lights[i]->getIntensity()*w->lights[i]->getAttenuation(hit.hitPoint);
    //   }
    //
    //   --_depth;
    //
    //   if(_depth > 0){
    //     ++w->stats->rays;
    //     Vec3d smpDir = (TBN*(Vec4d(w->sampler->sampleHemisphere(hit.normal), 0))).xyz();
    //     smpDir.normalize();
    //     Ray rayInd(bias, smpDir);
    //     double NoD = hit.normal*smpDir;
    //     if(NoD < D_EPS)
    //       return hit.radiance;
    //     // hit.radiance += traceRay(rayInd, _depth)%mat->shade(-ray.d, smpDir, hit)*PI;
    //     hit.radiance += traceRay(rayInd, depth)*PI/NoD;
    //   }
    //
    // }
    // else{
    //   // hit.radiance += w->env->getColor(ray.d);
    //   hit.radiance += Vec3d(1);
    // }
    //
    return hit.radiance;
  }


  // Vec3d traceRay(const Ray & ray, int _depth) const{
  //   Vec3d bias;
  //   Intersection hit;
  //   Mat4d TBN;
  //   Vec3d t;
  //   hit = w->intersectTree(ray);
  //   w->stats->hits += hit.nHits;
  //   if(hit.hit){
  //     hit.hitPoint = ray(hit.t);
  //     hit.normal = hit.obj_ptr->calcNormal(hit);
  //     t = hit.obj_ptr->calcTangent(hit);
  //     TBN = Mat4d(t, hit.normal^t, hit.normal, Vec3d(0));
  //     --_depth;
  //
  //     if(_depth > 0){
  //       ++w->stats->rays;
  //       Vec3d smpDir = (TBN*(Vec4d(w->sampler->sampleHemisphere(hit.normal), 0))).xyz();
  //       smpDir.normalize();
  //       bias = hit.hitPoint + hit.normal*D_EPS;
  //       Ray rayInd(bias, smpDir);
  //       double NoD = hit.normal*smpDir;
  //       if(NoD < D_EPS)
  //         return hit.radiance;
  //       hit.radiance += traceRay(rayInd, depth)*PI/NoD;
  //     }
  //
  //   }
  //   else{
  //     hit.radiance += Vec3d(1);
  //   }
  //
  //   return hit.radiance;
  // }

  std::string toString() const{
    return "AmbientOcclusionIntegrator: [ depth: " + std::to_string(depth) + "]";
  }

  int depth;
};

#endif
