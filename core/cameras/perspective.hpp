#ifndef _PERSPECTIVE_CAMERA_
#define _PERSPECTIVE_CAMERA_

#include "camera.hpp"

class PerspCamera: public Camera{
public:
  PerspCamera();
  PerspCamera(int, int, double, double, float, const Vec3f &, const Vec3f &, const Vec3f &);
  PerspCamera(const PerspCamera &);
  ~PerspCamera();

  PerspCamera & operator=(const PerspCamera &);

  void buildRasterToCam();
  void generateRay(Ray &, const Vec3f &) const;

  std::string toString() const;

  Mat4f RasterToCam;
};

std::ostream & operator<<(std::ostream &, const PerspCamera &);


#endif
