#include "camera.hpp"
#include "../geometry/mat4f.hpp"

using namespace Mat4F;

Camera::Camera(): width(800), heigth(600), near(1e-5), far(1e5), fov(90)
                , eye(100.f, 0.f, 0.f), lookAt(0.f), up(0.f, 0.f, 1.f){
  buildCamToWorld();
}

Camera::Camera(int w, int h, double n, double f, float FOV, const Vec3f & e,
              const Vec3f & l, const Vec3f & u): width(w), heigth(h), near(n)
              , far(f), fov(FOV), eye(e), lookAt(l), up(u.hat()){
  buildCamToWorld();
}

Camera::Camera(const Camera & c): width(c.width), heigth(c.heigth), near(c.near), far(c.far)
              , fov(c.fov), eye(c.eye), lookAt(c.lookAt), up(c.up){
  CamToWorld = c.CamToWorld;
}

Camera::~Camera(){}

Camera & Camera::operator=(const Camera & c){
  width = c.width; heigth = c.heigth; near = c.near; far = c.far; fov = c.fov;
  eye = c.eye; lookAt = c.lookAt; up = c.up; CamToWorld = c.CamToWorld;
  return *this;
}

void Camera::buildCamToWorld(){
  Vec3f w = (eye - lookAt).hat();
  Vec3f t = up^w;
  Vec3f u = (t == Vec3f()) ? (up - Vec3f(1e-6).hat())^w : t;
  Vec3f v = w^u;
  CamToWorld = Mat4f(u,v,w,eye)*scaling(1.f,1.f,-1.f);
}

std::string Camera::toString() const{
  return  "{ Res: " + std::to_string(width) + "x" + std::to_string(heigth)
          + "\nNear: " + std::to_string(near) + ", Far: " + std::to_string(far) + ", FOV: " + std::to_string(fov)
          + "\nEye: " + eye.toString() + ", LookAt: " + lookAt.toString() + ", Up: " + up.toString() + " }";
}
