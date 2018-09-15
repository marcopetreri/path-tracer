#ifndef _BOX_
#define _BOX_

#include "primitive.hpp"
#include <limits>

class Box: public Primitive{
public:
  Box();
  Box(const Vec3d &, Material *);
  Box(const Vec3d &, const Vec3d &, Material *);
  Box(const Box &);

  Box & operator=(const Box &);

  bool hit(const Ray &, Intersection & );
  Vec3d calcNormal(Intersection & hit) const;
  Vec3d calcTexture(Intersection &) const{}
  void setBVertex(){}
  void applyTransform(Transform *);
  Vec3d calcCenter() const{return min + (max - min)*.5;}

  friend std::ostream & operator<<(std::ostream &, const Box & b);

private:
  Vec3d c;
};

std::ostream & operator<<(std::ostream &, const Box & b);

#endif
