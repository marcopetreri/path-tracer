#include "perspective.hpp"
#include "../geometry/mat4f.hpp"
#include "../geometry/ray.hpp"
#include "../utilities/math.hpp"
#include "../samplers/sampler.hpp"
#include <math.h>

using namespace Mat4F;

PerspCamera::PerspCamera(): Camera(){
  buildRasterToCam();
}

PerspCamera::PerspCamera(int w, int h, double n, double f, float FOV
                        , const Vec3f & e, const Vec3f & l, const Vec3f & u):
                        Camera(w, h, n, f, FOV, e, l, u){
                          buildRasterToCam();
                        }

PerspCamera::PerspCamera(const PerspCamera & p): Camera(p){
  RasterToCam = p.RasterToCam;
}

PerspCamera::~PerspCamera(){}

PerspCamera & PerspCamera::operator=(const PerspCamera & p){
  Camera::operator=(p);
  RasterToCam = p.RasterToCam;
  return *this;
}

void PerspCamera::buildRasterToCam(){
  float ratio = static_cast<float>(width)/heigth, alpha = toRad(fov*.5);
  float sw[4];
  if(ratio >= 1.f){
    sw[0] = -ratio; sw[1] = ratio; sw[2] = -1.f; sw[3] = 1.f;
  }
  else{
    sw[0] = -1.f; sw[1] = 1.f; sw[2] = -1.f/ratio; sw[3] = 1.f/ratio;
  }
  Mat4f R2S = inverse(scaling(width, heigth, 1.f)*
                      scaling(1.f/(sw[1]-sw[0]), 1.f/(sw[2]-sw[3]), 1.f)*
                      translation(-sw[0],-sw[3],0.f));
  Mat4f Persp(1.f, 0.f,            0.f,                  0.f,
              0.f, 1.f,            0.f,                  0.f,
              0.f, 0.f, far/(far-near), -far*near/(far-near),
              0.f, 0.f,            1.f,                  0.f);
  Mat4f S2C = inverse(scaling(1.f/tanf(alpha), 1.f/tanf(alpha), 1.f)*
                      Persp);
  RasterToCam = S2C*R2S;
}

void PerspCamera::generateRay(Ray & ray, const Vec3f & sp) const{
  Vec4f p(sp, 1.f);
  Vec4f pc = RasterToCam*p;
  pc /= pc.w;
  Vec4f pw = CamToWorld*Vec4f(pc.x, pc.y, pc.z, 0.f);
  ray.o = Vec3d(eye.x, eye.y, eye.z);
  ray.d = Vec3d(pw.x, pw.y, pw.z).hat();
  ray.refresh();
}

std::string PerspCamera::toString() const{
  return "Perspective Camera: " + Camera::toString();
}

std::ostream & operator<<(std::ostream & os, const PerspCamera & p){
  return os << "Perspective Camera: { Res: " << p.width << "x" << p.heigth
            << "\nNear: " << p.near << ", Far: " << p.far << ", FOV: " << p.fov
            << "\nEye: " << p.eye << ", LookAt: " << p.lookAt << ", Up: " << p.up << " }";
}
