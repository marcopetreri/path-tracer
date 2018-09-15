#ifndef _MAT_4D_
#define _MAT_4D_

#include "vec3d.hpp"
#include "vec4d.hpp"
#include <string.h>
#include <stdlib.h>

class Mat4d{
public:
  Mat4d(){memset(m, 0., sizeof(double)*16); m[0] = m[5] = m[10] = m[15] = 1.;}
  Mat4d(double s){memset(m, 0., sizeof(double)*16); m[0] = m[5] = m[10] = m[15] = s;}
  Mat4d(double v[16]): m(v){}
  Mat4d(double m0, double m1, double m2, double m3,
        double m4, double m5, double m6, double m7,
        double m8, double m9, double m10, double m11,
        double m12, double m13, double m14, double m15){
          m[0]  = m0; m[1]  = m4; m[2]  =  m8; m[3]  = m12;
          m[4]  = m1; m[5]  = m5; m[6]  =  m9; m[7]  = m13;
          m[8]  = m2; m[9]  = m6; m[10] = m10; m[11] = m14;
          m[12] = m3; m[13] = m7; m[14] = m11; m[15] = m15;
        }
  Mat4d(const Vec3d & u, const Vec3d & v, const Vec3d & z, const Vec3d & w){
    m[0]  = u.x; m[1]  = u.y; m[2]  = u.z; m[3]  = 0.;
    m[4]  = v.x; m[5]  = v.y; m[6]  = v.z; m[7]  = 0.;
    m[8]  = z.x; m[9]  = z.y; m[10] = z.z; m[11] = 0.;
    m[12] = w.x; m[13] = w.y; m[14] = w.z; m[15] = 1.;
  }
  Mat4d(const Vec4d & u, const Vec4d & v, const Vec4d & z, const Vec4d & w){
    m[0]  = u.x; m[1]  = u.y; m[2]  = u.z; m[3]  = u.w;
    m[4]  = v.x; m[5]  = v.y; m[6]  = v.z; m[7]  = v.w;
    m[8]  = z.x; m[9]  = z.y; m[10] = z.z; m[11] = z.w;
    m[12] = w.x; m[13] = w.y; m[14] = w.z; m[15] = w.w;
  }
  Mat4d(const Mat4d & n){memcpy(m, n.m, sizeof(double)*16);}
  Mat4d(Mat4d && n){delete [] m; m = n.m; n.m = nullptr;}
  ~Mat4d(){delete [] m;}

  Mat4d operator*(const Mat4d & n) const{
    Mat4d t;
    for(int i = 0; i < 4; ++i)
      for(int j = 0; j < 4; ++j)
        t(j,i) = n.m[4*i]*m[j] + n.m[4*i+1]*m[j+4] + n.m[4*i+2]*m[j+8] + n.m[4*i+3]*m[j+12];
    return t;
  }
  // Mat4d operator*(const Mat4d & n) const{
  //   Mat4d t;
  //   for(int i = 0, j = 0, k = 0; i < 16; ++i, j = i%4, k = (i/4)*4)
  //     t.m[i] = n.m[0+k]*m[0+j] + n.m[1+k]*m[4+j] + n.m[2+k]*m[8+j] + n.m[3+k]*m[12+j];
  //   return t;
  // }
  Mat4d & operator*=(const Mat4d & n){
    Mat4d t;
    for(int i = 0; i < 4; ++i)
      for(int j = 0; j < 4; ++j)
        t(j,i) = n.m[4*i]*m[j] + n.m[4*i+1]*m[j+4] + n.m[4*i+2]*m[j+8] + n.m[4*i+3]*m[j+12];
    return *this = t;
  }
  Vec4d operator*(const Vec4d & v) const{
    Vec4d t(m[0]*v.x + m[4]*v.y +  m[8]*v.z + m[12]*v.w,
            m[1]*v.x + m[5]*v.y +  m[9]*v.z + m[13]*v.w,
            m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w,
            m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w);
    return t;
  }
  Mat4d & operator=(const Mat4d & n){memcpy(m, n.m, sizeof(double)*16); return *this;}
  Mat4d & operator=(Mat4d && n){delete [] m; m = n.m; n.m = nullptr; return *this;}
  double operator()(int r, int c) const{return m[c*4 + r];}
  double & operator()(int r, int c){return m[c*4 + r];}

  Vec4d row(int i) const{return Vec4d(m[i], m[i+4], m[i+8], m[i+12]);}
  Vec4d col(int i) const{return Vec4d(m[i*4], m[i*4+1], m[i*4+2], m[i*4+3]);}
  Mat4d & transpose(){
    Mat4d t;
    for(int i = 0; i < 16; ++i){
      div_t d = div(i,4);
      t.m[i] = m[d.quot + (d.rem)*4];
    }
    return *this = t;
  }
  Mat4d & inverse();

  double * m = new double[16];
};

std::ostream & operator<<(std::ostream &, const Mat4d &);

namespace Matrix4D{
  Mat4d transpose(const Mat4d &);
  Mat4d inverse(const Mat4d &);
}

#endif
