#ifndef _TEXTURE_
#define _TEXTURE_

#include "../geometry/vec3d.hpp"
#include "../utilities/math.hpp"
#include <iostream>

#include "pixelBuffer.hpp"

class Texture: public PixelBuffer{
public:
  Texture(): PixelBuffer(){}
  Texture(const std::string & path): PixelBuffer(path){}
  ~Texture(){
    SOIL_free_image_data(map);
  }

  Vec3d getValue(const Vec3d & uv){
    int pos = static_cast<int>(uv.y*heigth)*width + static_cast<int>(uv.x*width);
    pos *= channels;
    // return Vec3d(uv.x, uv.y, 0);
    return Vec3d(to01(map[pos], map[pos+1], map[pos+2]));
  }

  bool load(const std::string & path){
    PixelBuffer::load(path);
    // gammify();
    return true;
  }

  void gammify(){
    for(int i = 0; i < size(); ++i){
      map[i] = static_cast<int>(pow( static_cast<double>(map[i])/255.0, 2.2)*255);
    }
  }

  std::string toString() const{
    return "Texture: " + PixelBuffer::toString() + "]";
  }

};

#endif
