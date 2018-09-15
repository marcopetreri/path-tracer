
#ifndef _CAMERA_
#define _CAMERA_

#include <iostream>
#include "../geometry/vec3f.hpp"
#include "../geometry/mat4f.hpp"

class Mat4f;
class Ray;

class Camera{
public:
  Camera();
  Camera(int, int, double, double, float, const Vec3f &, const Vec3f &, const Vec3f &);
  Camera(const Camera &);
  virtual ~Camera();

  Camera & operator=(const Camera &);

  void buildCamToWorld();
  virtual void buildRasterToCam() = 0;
  virtual void generateRay(Ray &, const Vec3f &) const = 0;

  virtual std::string toString() const;

  int width, heigth;
  double near, far;
  float fov;
  Vec3f eye, lookAt, up;
  Mat4f CamToWorld;
};

#endif
