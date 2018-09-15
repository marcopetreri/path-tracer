#ifndef _MAT_4F_
#define _MAT_4F_

#include "vec4f.hpp"
#include <string.h>
#include <stdlib.h>

class Mat4f{
public:
  Mat4f(){memset(m, 0.f, sizeof(float)*16); m[0] = m[5] = m[10] = m[15] = 1.f;}
  Mat4f(float s){memset(m, 0.f, sizeof(float)*16); m[0] = m[5] = m[10] = m[15] = s;}
  Mat4f(float v[16]): m(v){}
  Mat4f(float m0, float m1, float m2, float m3,
        float m4, float m5, float m6, float m7,
        float m8, float m9, float m10, float m11,
        float m12, float m13, float m14, float m15){
          m[0]  = m0; m[1]  = m4; m[2]  =  m8; m[3]  = m12;
          m[4]  = m1; m[5]  = m5; m[6]  =  m9; m[7]  = m13;
          m[8]  = m2; m[9]  = m6; m[10] = m10; m[11] = m14;
          m[12] = m3; m[13] = m7; m[14] = m11; m[15] = m15;
        }
  Mat4f(const Vec3f & u, const Vec3f & v, const Vec3f & z, const Vec3f & w){
    m[0]  = u.x; m[1]  = u.y; m[2]  = u.z; m[3]  = 0.f;
    m[4]  = v.x; m[5]  = v.y; m[6]  = v.z; m[7]  = 0.f;
    m[8]  = z.x; m[9]  = z.y; m[10] = z.z; m[11] = 0.f;
    m[12] = w.x; m[13] = w.y; m[14] = w.z; m[15] = 1.f;
  }
  Mat4f(const Vec4f & u, const Vec4f & v, const Vec4f & z, const Vec4f & w){
    m[0]  = u.x; m[1]  = u.y; m[2]  = u.z; m[3]  = u.w;
    m[4]  = v.x; m[5]  = v.y; m[6]  = v.z; m[7]  = v.w;
    m[8]  = z.x; m[9]  = z.y; m[10] = z.z; m[11] = z.w;
    m[12] = w.x; m[13] = w.y; m[14] = w.z; m[15] = w.w;
  }
  Mat4f(const Mat4f & n){memcpy(m, n.m, sizeof(float)*16);}
  Mat4f(Mat4f && n){delete [] m; m = n.m; n.m = nullptr;}
  ~Mat4f(){delete [] m;}

  Mat4f operator*(const Mat4f & n) const{
    Mat4f t;
    for(int i = 0; i < 4; ++i)
      for(int j = 0; j < 4; ++j)
        t(j,i) = n.m[4*i]*m[j] + n.m[4*i+1]*m[j+4] + n.m[4*i+2]*m[j+8] + n.m[4*i+3]*m[j+12];
    return t;
  }
  // Mat4f operator*(const Mat4f & n) const{
  //   Mat4f t;
  //   for(int i = 0, j = 0, k = 0; i < 16; ++i, j = i%4, k = (i/4)*4)
  //     t.m[i] = n.m[0+k]*m[0+j] + n.m[1+k]*m[4+j] + n.m[2+k]*m[8+j] + n.m[3+k]*m[12+j];
  //   return t;
  // }
  Mat4f & operator*=(const Mat4f & n){
    Mat4f t;
    for(int i = 0; i < 4; ++i)
      for(int j = 0; j < 4; ++j)
        t(j,i) = n.m[4*i]*m[j] + n.m[4*i+1]*m[j+4] + n.m[4*i+2]*m[j+8] + n.m[4*i+3]*m[j+12];
    return *this = t;
  }
  Vec4f operator*(const Vec4f & v) const{
    Vec4f t(m[0]*v.x + m[4]*v.y +  m[8]*v.z + m[12]*v.w,
            m[1]*v.x + m[5]*v.y +  m[9]*v.z + m[13]*v.w,
            m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w,
            m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w);
    return t;
  }
  Mat4f & operator=(const Mat4f & n){memcpy(m, n.m, sizeof(float)*16); return *this;}
  Mat4f & operator=(Mat4f && n){delete [] m; m = n.m; n.m = nullptr; return *this;}
  float operator()(int r, int c) const{return m[c*4 + r];}
  float & operator()(int r, int c){return m[c*4 + r];}

  Vec4f row(int i) const{return Vec4f(m[i], m[i+4], m[i+8], m[i+12]);}
  Vec4f col(int i) const{return Vec4f(m[i*4], m[i*4+1], m[i*4+2], m[i*4+3]);}
  Mat4f & transpose(){
    Mat4f t;
    for(int i = 0; i < 16; ++i){
      div_t d = div(i,4);
      t.m[i] = m[d.quot + (d.rem)*4];
    }
    return *this = t;
  }
  Mat4f & inverse();

  float * m = new float[16];
};

std::ostream & operator<<(std::ostream &, const Mat4f &);

namespace Mat4F{
  Mat4f transpose(const Mat4f &);
  Mat4f inverse(const Mat4f &);
  Mat4f translation(float, float, float);
  Mat4f scaling(float);
  Mat4f scaling(float, float, float);
  Mat4f rotationX(float);
  Mat4f rotationY(float);
  Mat4f rotationZ(float);
}

#endif
