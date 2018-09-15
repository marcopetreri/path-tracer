#include "mat4f.hpp"
#include "../utilities/math.hpp"
#include <utility>

Mat4f & Mat4f::inverse(){
  int i, j, k;
  float a[32] = {m[0], m[4], m[8], m[12], 1.f, 0.f, 0.f, 0.f
                 ,m[1], m[5], m[9], m[13], 0.f, 1.f, 0.f, 0.f
                 ,m[2], m[6], m[10], m[14], 0.f, 0.f, 1.f, 0.f
                 ,m[3], m[7], m[11], m[15], 0.f, 0.f, 0.f, 1.f};
  float d;

  /************** partial pivoting **************/
  for (i = 24; i >= 8; i-= 8){
      if (a[i-8] < a[i])
          for (j = i; j < i + 8; j++){
              std::swap(a[j],a[j-8]);
          }
  }

  /********** reducing to diagonal***********/
  for (k = 0, i = 0; i <= 24; i += 8, k++){
      for (j = 0; j <= 24; j += 8)
          if (j != i){
              d = a[j+k] / a[i+k];
              for (int l = i,k = j; k < j + 8; k++, l++)
                  a[k] -= a[l] * d;
          }
  }

  /************** reducing to unit *************/
  for (k = 0, i = 0; i <= 24; i += 8, k++){
      d = 1.f / a[i + k];
      for (j = i; j < i + 8; j++)
          a[j] *= d;
  }

  return *this = Mat4f( a[4],  a[5], a[6],  a[7]
                      ,a[12], a[13], a[14], a[15]
                      ,a[20], a[21], a[22], a[23]
                      ,a[28], a[29], a[30], a[31]);
}

std::ostream & operator<<(std::ostream & os, const Mat4f & m){
  if(m.m){
    os << "M :\n";
    for(int i = 0; i < 4; ++i)
      os << "|" << m.m[i] << "\t" << m.m[i+4] << "\t" << m.m[i+8] << "\t" << m.m[i+12] << "|" << std::endl;
  }
  else
  os << "empty matrix" << std::endl;
  return os;
}

Mat4f Mat4F::transpose(const Mat4f & m){
  Mat4f t;
  for(int i = 0; i < 16; ++i){
    div_t d = div(i,4);
    t.m[i] = m.m[d.quot + (d.rem)*4];
  }
  return t;
}

Mat4f Mat4F::inverse(const Mat4f & m){
  int i, j, k;
  float a[32] = {m.m[0], m.m[4],  m.m[8], m.m[12], 1.f, 0.f, 0.f, 0.f
                ,m.m[1], m.m[5],  m.m[9], m.m[13], 0.f, 1.f, 0.f, 0.f
                ,m.m[2], m.m[6], m.m[10], m.m[14], 0.f, 0.f, 1.f, 0.f
                ,m.m[3], m.m[7], m.m[11], m.m[15], 0.f, 0.f, 0.f, 1.f};
  float d;

  /************** partial pivoting **************/
  for (i = 24; i >= 8; i-= 8){
      if (a[i-8] < a[i])
          for (j = i; j < i + 8; j++){
              std::swap(a[j],a[j-8]);
          }
  }

  /********** reducing to diagonal***********/
  for (k = 0, i = 0; i <= 24; i += 8, k++){
      for (j = 0; j <= 24; j += 8)
          if (j != i){
              d = a[j+k] / a[i+k];
              for (int l = i,k = j; k < j + 8; k++, l++)
                  a[k] -= a[l] * d;
          }
  }

  /************** reducing to unit *************/
  for (k = 0, i = 0; i <= 24; i += 8, k++){
      d = 1.f / a[i + k];
      for (j = i; j < i + 8; j++)
          a[j] *= d;
  }

  return Mat4f( a[4],  a[5],  a[6],  a[7]
              ,a[12], a[13], a[14], a[15]
              ,a[20], a[21], a[22], a[23]
              ,a[28], a[29], a[30], a[31]);
}

Mat4f Mat4F::translation(float a, float b, float c){
  return Mat4f(1.f, 0.f, 0.f, a
              ,0.f, 1.f, 0.f, b
              ,0.f, 0.f, 1.f, c
              ,0.f, 0.f, 0.f, 1.f);
}

Mat4f Mat4F::scaling(float s){
  return Mat4f(  s, 0.f, 0.f, 0.f
              ,0.f,   s, 0.f, 0.f
              ,0.f, 0.f,   s, 0.f
              ,0.f, 0.f, 0.f, 1.f);
}

Mat4f Mat4F::scaling(float a, float b, float c){
  return Mat4f(  a, 0.f, 0.f, 0.f
              ,0.f,   b, 0.f, 0.f
              ,0.f, 0.f,   c, 0.f
              ,0.f, 0.f, 0.f, 1.f);
}

Mat4f Mat4F::rotationX(float deg){
  float sinT = sin(toRad(deg));
  float cosT = cos(toRad(deg));
  return Mat4f(1.f,  0.f,   0.f,  0.f
              ,0.f, cosT, -sinT,  0.f
              ,0.f, sinT,  cosT,  0.f
              ,0.f,  0.f,   0.f, 1.f);

}

Mat4f Mat4F::rotationY(float deg){
  float sinT = sin(toRad(deg));
  float cosT = cos(toRad(deg));
  return Mat4f( cosT, 0.f, sinT, 0.f
              ,  0.f, 1.f,  0.f, 0.f
              ,-sinT, 0.f, cosT, 0.f
              ,  0.f, 0.f,  0.f, 1.f);

}

Mat4f Mat4F::rotationZ(float deg){
  float sinT = sin(toRad(deg));
  float cosT = cos(toRad(deg));
  return Mat4f(cosT, -sinT, 0.f, 0.f
              ,cosT,  sinT, 0.f, 0.f
              , 0.f,   0.f, 1.f, 0.f
              , 0.f,   0.f, 0.f, 1.f);

}
