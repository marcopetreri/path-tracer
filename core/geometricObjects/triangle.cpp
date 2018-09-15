#include "triangle.hpp"
#include "../geometry/ray.hpp"
#include "../geometry/transform.hpp"
#include "../utilities/intersection.hpp"
#include "../utilities/constants.hpp"

Triangle::Triangle(): Primitive(), p0(), p1(), p2(), n0(), n1(), n2(), t0(), t1(), t2(), e1(), e2(), n(){}
Triangle::Triangle(const Vec3d & _p0, const Vec3d & _p1, const Vec3d & _p2
        ,const Vec3d & _n0, const Vec3d & _n1, const Vec3d & _n2
        ,const Vec3d & _t0, const Vec3d & _t1, const Vec3d & _t2
        ,const Vec3d & _tn0, const Vec3d & _tn1, const Vec3d & _tn2
        ,Material * m)
        : Primitive(m), p0(_p0), p1(_p1), p2(_p2), n0(_n0), n1(_n1), n2(_n2),
        t0(_t0), t1(_t1), t2(_t2), tn0(_tn0), tn1(_tn1), tn2(_tn2), e1(_p1-_p0), e2(_p2-_p0), n(e1^e2){
          setBVertex();
        }
Triangle::Triangle(const Triangle & t): Primitive(t), p0(t.p0), p1(t.p1), p2(t.p2), n0(t.n0),
                                        n1(t.n1), n2(t.n2), t0(t.t0), t1(t.t1), t2(t.t2),
                                        tn0(t.tn0), tn1(t.tn1), tn2(t.tn2), e1(t.e1), e2(t.e2), n(t.n){}

Vec3d Triangle::operator[](int i){
  return (&p0)[i];
}

Triangle & Triangle::operator=(const Triangle & t){
  Primitive::operator=(t);
  p0 = t.p0; p1 = t.p1; p2 = t.p2;
  e1 = t.e1; e2 = t.e2;
  n = t.n; n0 = t.n0; n1 = t.n1; n2 = t.n2;
  t0 = t.t0; t1 = t.t1; t2 = t.t2;
  tn0 = t.t0; tn1 = t.t1; tn2 = t.t2;
  return *this;
}

bool Triangle::hit(const Ray & ray, Intersection & hit){
  double det = -n*ray.d;
  if(det < D_EPS)
    return false;
  Vec3d s = ray.o - p0;
  Vec3d m = s^ray.d;
  double u = m*e2;
  if(u < 0. || u > det)
    return false;
  double v = -m*e1;
  if(v < 0. || u+v > det)
    return false;
  double t = n*s;
  if(t > D_EPS){
    double invDet = 1./det;
    double tf = t*invDet;
    if(tf < hit.t){
      hit.t = tf;
      hit.u = u*invDet;
      hit.v = v*invDet;
      hit.hit = true;
      hit.obj_ptr = this;
      return true;
    }
  }
  else
    return false;
}

Vec3d Triangle::calcNormal(Intersection & hit) const{
  return (n0*(1.-hit.u-hit.v) + n1*hit.u + n2*hit.v).hat();
}

Vec3d Triangle::calcTangent(Intersection & hit) const{
  Vec3d t = (tn0*(1.-hit.u-hit.v) + tn1*hit.u + tn2*hit.v).hat();
  t = (t - hit.normal*(hit.normal*t)).hat();
  // std::cout << tn0 << " "  << tn1 << " " << tn2 << "\n";
  // std::cout << t << "\n";
  return t;
}

Vec3d Triangle::calcTexture(Intersection & hit) const{
  return (t0*(1.-hit.u-hit.v) + t1*hit.u + t2*hit.v);
}

void Triangle::applyTransform(Transform * tr){
  p0 = (tr->m->operator*(Vec4d(p0,1.))).xyz();
  p1 = (tr->m->operator*(Vec4d(p1,1.))).xyz();
  p2 = (tr->m->operator*(Vec4d(p2,1.))).xyz();
  n0 = (tr->mTrInv->operator*(Vec4d(n0,0.))).xyz();
  n1 = (tr->mTrInv->operator*(Vec4d(n1,0.))).xyz();
  n2 = (tr->mTrInv->operator*(Vec4d(n2,0.))).xyz();
  tn0 = (tr->mTrInv->operator*(Vec4d(tn0,0.))).xyz();
  tn1 = (tr->mTrInv->operator*(Vec4d(tn1,0.))).xyz();
  tn2 = (tr->mTrInv->operator*(Vec4d(tn2,0.))).xyz();
  e1 = p1-p0;
  e2 = p2-p0;
  n = e1^e2;
}

void Triangle::setBVertex(){
  min = max = p0;
  for(int i = 0; i < 3; ++i)
    for(int j = 1; j < 3; ++j){
      double val = (*this)[j][i];
      min[i] = val < min[i] ? val : min[i];
      max[i] = val > max[i] ? val : max[i];
    }
  min -= D_EPS; //HACK: evitare che esca un bbox 2d
  max += D_EPS;
}

std::ostream & operator<<(std::ostream & os, const Triangle & t){
  return os << "Triangle : { " << t.p0 << ", " << t.p1 << ", " << t.p2
            << "\n\t\t" << t.n0 << ", " << t.n1 << ", " << t.n2 << "\n\t\t"
            << t.min << ", " << t.max << " }";
}
