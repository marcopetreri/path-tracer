#ifndef _FILM_
#define _FILM_

#include "pixelBuffer.hpp"
#include "../utilities/math.hpp"

class Film: public PixelBuffer{
public:
  Film(): PixelBuffer(), path("rendering.png"), temp_map(nullptr){}
  Film(int w, int h, int c): PixelBuffer(w,h,c), path("rendering.png"){
    temp_map = new double[size()];
    for(int i = 0; i < size(); ++i)
      temp_map[i] = 0.;
  }
  Film(int w, int h, int c, const std::string & p): PixelBuffer(w, h, c), path(p){
    temp_map = new double[size()];
    for(int i = 0; i < size(); ++i)
      temp_map[i] = 0.;
  }
  ~Film(){
    delete [] map;
    delete [] temp_map;
  }

  void impress(int i, const Vec3d & c){
    i *= channels;
    Vec3d val = to255(c);
    map[i] = static_cast<int>(val.x);
    map[i+1] = static_cast<int>(val.y);
    map[i+2] = static_cast<int>(val.z);
  }

  void impressAdd(int i, const Vec3d & c){
    i *= channels;
    temp_map[i] += c.x;
    temp_map[i+1] += c.y;
    temp_map[i+2] += c.z;
  }

  void finalize(double a, double b, double n){
    for(int i = 0; i < size(); ++i){
      map[i] = static_cast<int>(pow(clamp(temp_map[i]*n, a, b), .4545)*255);
    }
  }

  int save(){
    if(SOIL_save_image(path.c_str(), SOIL_SAVE_TYPE_PNG, width, heigth, channels, map)){
      std::cout << "\tImage succesfully saved to " << path << "\n";
      return true;
    }
    else{
      std::cout << "\t[ERROR] File saving failed.\n";
    }
  }

  int save(const std::string & path){
    if(SOIL_save_image(path.c_str(), SOIL_SAVE_TYPE_PNG, width, heigth, channels, map)){
      std::cout << "\tImage succesfully saved to " << path << "\n";
      return true;
    }
    else{
      std::cout << "\t[ERROR] File saving failed.\n";
    }
  }

  std::string toString() const{
    return "Film: " + PixelBuffer::toString() + ", Path: " + path + "]";
  }

  std::string path;
  double * temp_map;
};

inline std::ostream & operator<<(std::ostream & os, const Film & f){
  return os << "Film: {Res: " << f.width << "x" << f.heigth << " - Path: " << f.path << "}";
}

#endif
