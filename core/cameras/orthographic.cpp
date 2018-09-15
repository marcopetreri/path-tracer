#include "orthographic.hpp"
#include "../geometry/mat4f.hpp"
#include "../geometry/ray.hpp"
#include "../utilities/math.hpp"
#include "../samplers/sampler.hpp"
#include <math.h>

using namespace Mat4F;

OrthoCamera::OrthoCamera(): Camera(){
  buildRasterToCam();
}

OrthoCamera::OrthoCamera(int w, int h, double n, double f, float FOV
                        , const Vec3f & e, const Vec3f & l, const Vec3f & u):
                        Camera(w, h, n, f, FOV, e, l, u){
                          buildRasterToCam();
                        }

OrthoCamera::OrthoCamera(const OrthoCamera & o): Camera(o){
  RasterToCam = o.RasterToCam;
}

OrthoCamera::~OrthoCamera(){}

OrthoCamera & OrthoCamera::operator=(const OrthoCamera & o){
  Camera::operator=(o);
  RasterToCam = o.RasterToCam;
  return *this;
}

void OrthoCamera::buildRasterToCam(){
  float ratio = static_cast<float>(width)/heigth, alpha = toRad(fov*.5);
  float sw[4];
  if(ratio >= 1.f){
    sw[0] = -ratio; sw[1] = ratio; sw[2] = -1.f; sw[3] = 1.f;
  }
  else{
    sw[0] = -1.f; sw[1] = 1.f; sw[2] = -1.f/ratio; sw[3] = 1.f/ratio;
  }
  RasterToCam =  inverse(scaling(width, heigth, 1.f)*
                  scaling(1.f/(sw[1]-sw[0]), 1.f/(sw[2]-sw[3]), 1.f)*
                  translation(-sw[0], -sw[3], 0.f)*
                  scaling(1.f/tanf(alpha), 1.f/tanf(alpha), 1.f));
}

void OrthoCamera::generateRay(Ray & ray,const Vec3f & sp) const{
  Vec4f p(sp.x, sp.y, 0.f, 1.f);
  Vec4f d(0.f, 0.f, -1.f, 0.f);
  Vec4f pc = RasterToCam*p;
  Vec4f dc = RasterToCam*d;
  Vec4f pw = CamToWorld*pc;
  Vec4f dw = CamToWorld*dc;
  ray.o = Vec3d(pw.x, pw.y, pw.z);
  ray.d = Vec3d(dw.x, dw.y, dw.z);
  ray.refresh();
}

std::ostream & operator<<(std::ostream & os, const OrthoCamera & o){
  return os << "Perspective Camera: { Res: " << o.width << "x" << o.heigth
            << "\nNear: " << o.near << ", Far: " << o.far << ", FOV: " << o.fov
            << "\nEye: " << o.eye << ", LookAt: " << o.lookAt << ", Up: " << o.up << " }";
}
