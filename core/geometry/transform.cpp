#include "transform.hpp"
#include "../utilities/math.hpp"

Transform::Transform(): m(new Mat4d()), mInv(new Mat4d()), mTrInv(new Mat4d()){}

Transform::Transform(const Vec3d & x, const Vec3d & y, const Vec3d & z, const Vec3d & w): m(new Mat4d(x, y, z, w)){
  mInv = new Mat4d(x, y, z, w); mInv->inverse();
  mTrInv = new Mat4d(*mInv); mTrInv->transpose();
}

Transform::Transform(const Vec4d & x, const Vec4d & y, const Vec4d & z, const Vec4d & w): m(new Mat4d(x, y, z, w)){
  mInv = new Mat4d(x, y, z, w); mInv->inverse();
  mTrInv = new Mat4d(*mInv); mTrInv->transpose();
}

Transform::Transform(Mat4d * _m): m(_m), mInv(new Mat4d(*_m)){
  mInv->inverse();
  mTrInv = new Mat4d(*mInv); mTrInv->transpose();
}

Transform::Transform(Mat4d * _m, Mat4d * _mInv, Mat4d * _mTrInv): m(_m), mInv(_mInv), mTrInv(_mTrInv){}

Transform::Transform(const Transform & tr){
  m = new Mat4d(*tr.m); mInv = new Mat4d(*tr.mInv); mTrInv = new Mat4d(*tr.mTrInv);
}

Transform::~Transform(){
  delete m; delete mInv; delete mTrInv;
}

Transform Transform::operator*(const Transform & tr) const{
  return Transform(new Mat4d(m->operator*(*tr.m))
                  ,new Mat4d(mInv->operator*(*tr.mInv))
                  ,new Mat4d(mTrInv->operator*(*tr.mTrInv)));
}

Transform & Transform::operator*=(const Transform & tr){
  m->operator*=(*tr.m); mInv->operator*=(*tr.mInv); mTrInv->operator*=(*tr.mTrInv);
  return *this;
}

Transform & Transform::operator=(const Transform & tr){
  *m = *tr.m; *mInv = *tr.mInv; *mTrInv = *tr.mTrInv;
  return *this;
}

void Transform::inverse(){
  std::swap(m,mInv);
  *mTrInv = *m; mTrInv->transpose();
}

Transform translation(double a, double b, double c){
  return Transform(new Mat4d(1., 0., 0., a
                            ,0., 1., 0., b
                            ,0., 0., 1., c
                            ,0., 0., 0., 1.)
                  ,new Mat4d(1., 0., 0., -a
                            ,0., 1., 0., -b
                            ,0., 0., 1., -c
                            ,0., 0., 0., 1.)
                  ,new Mat4d(1., 0., 0., 0.
                            ,0., 1., 0., 0.
                            ,0., 0., 1., 0.
                            ,0., 0., 0., 1.) //NOTE: not affects normals
                  );
}

Transform scaling(double s){
  double d = 1./s;
  return Transform(new Mat4d( s, 0., 0., 0.
                            ,0.,  s, 0., 0.
                            ,0., 0.,  s, 0.
                            ,0., 0., 0., 1.)
                  ,new Mat4d( d, 0., 0., 0.
                            ,0.,  d, 0., 0.
                            ,0., 0.,  d, 0.
                            ,0., 0., 0., 1.)
                  ,new Mat4d(1., 0., 0., 0.
                            ,0., 1., 0., 0.
                            ,0., 0., 1., 0.
                            ,0., 0., 0., 1.)
                  );
}

Transform scaling(double a, double b, double c){
  return Transform(new Mat4d( a, 0., 0., 0.
                            ,0.,  b, 0., 0.
                            ,0., 0.,  c, 0.
                            ,0., 0., 0., 1.)
                  ,new Mat4d(1./a,   0.,   0., 0.
                            ,  0., 1./b,   0., 0.
                            ,  0.,   0., 1./c, 0.
                            ,  0.,   0.,   0., 1.)
                  ,new Mat4d(1./a,   0.,   0., 0.
                            ,  0., 1./b,   0., 0.
                            ,  0.,   0., 1./c, 0.
                            ,  0.,   0.,   0., 1.)
                  );
}

Transform rotationX(double deg){
  double sinT = sin(toRad(deg));
  double cosT = cos(toRad(deg));
  return Transform(new Mat4d(1.,  0.,     0.,  0.
                            ,0., cosT, -sinT,  0.
                            ,0., sinT,  cosT,  0.
                            ,0.,   0.,    0.,  1.)
                  ,new Mat4d(1.,   0.,    0.,  0.
                            ,0.,  cosT, sinT,  0.
                            ,0., -sinT, cosT,  0.
                            ,0.,    0.,   0.,  1.)
                  ,new Mat4d(1.,  0.,     0.,  0.
                            ,0., cosT, -sinT,  0.
                            ,0., sinT,  cosT,  0.
                            ,0.,   0.,    0.,  1.)
                  );
}

Transform rotationY(double deg){
  double sinT = sin(toRad(deg));
  double cosT = cos(toRad(deg));
  return Transform(new Mat4d( cosT, 0., sinT, 0.
                            ,   0., 1.,   0., 0.
                            ,-sinT, 0., cosT, 0.
                            ,   0., 0.,   0., 1.)
                  ,new Mat4d(cosT, 0., -sinT, 0.
                            ,  0., 1.,    0., 0.
                            ,sinT, 0.,  cosT, 0.
                            ,  0., 0.,    0., 1.)
                  ,new Mat4d( cosT, 0., sinT, 0.
                            ,   0., 1.,   0., 0.
                            ,-sinT, 0., cosT, 0.
                            ,   0., 0.,   0., 1.)
                  );
}

Transform rotationZ(double deg){
  double sinT = sin(toRad(deg));
  double cosT = cos(toRad(deg));
  return Transform(new Mat4d(cosT, -sinT, 0., 0.
                            ,sinT,  cosT, 0., 0.
                            ,  0.,    0., 1., 0.
                            ,  0.,    0., 0., 1.)
                  ,new Mat4d( cosT, sinT, 0., 0.
                            ,-sinT, cosT, 0., 0.
                            ,   0.,   0., 1., 0.
                            ,   0.,   0., 0., 1.)
                  ,new Mat4d(cosT, -sinT, 0., 0.
                            ,sinT,  cosT, 0., 0.
                            ,  0.,    0., 1., 0.
                            ,  0.,    0., 0., 1.)
                  );
}
