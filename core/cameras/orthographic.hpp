#ifndef _ORTHOGRAPHIC_CAMERA_
#define _ORTHOGRAPHIC_CAMERA_

#include "camera.hpp"

class OrthoCamera: public Camera{
public:
  OrthoCamera();
  OrthoCamera(int, int, double, double, float, const Vec3f &, const Vec3f &, const Vec3f &);
  OrthoCamera(const OrthoCamera &);
  ~OrthoCamera();

  OrthoCamera & operator=(const OrthoCamera &);

  void buildRasterToCam();
  void generateRay(Ray &, const Vec3f &) const;

  Mat4f RasterToCam;
};

std::ostream & operator<<(std::ostream &, const OrthoCamera &);


#endif
