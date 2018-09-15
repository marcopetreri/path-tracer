#ifndef _PIXEL_BUFFER_
#define _PIXEL_BUFFER_

#include "../geometry/vec3d.hpp"
#include "../utilities/math.hpp"
#include <SOIL/SOIL.h>
#include <iostream>


class PixelBuffer{
public:
  PixelBuffer(): width(0), heigth(0), channels(0), map(nullptr){}
  PixelBuffer(int w, int h, int c): width(w), heigth(h), channels(c){
    map = new unsigned char [size()];
    for(int i = 0; i < size(); ++i)
      map[i] = 0;
  }
  PixelBuffer(const std::string & path){
    load(path);
  }
  virtual ~PixelBuffer(){}

  int size(){
    return heigth*width*channels;
  }

  int area(){
    return heigth*width;
  }

  virtual bool load(const std::string & path){
    map = SOIL_load_image(path.c_str(), &width, &heigth, &channels, SOIL_LOAD_AUTO);
    if(map){
      std::cout << "\t<Map>\n\t\tSuccesfully imported " << path << ", Size: " << width << "x" << heigth
      << ", channels: " << channels << "\n\t</Map>\n";
      return true;
    }
    else{
      std::cout << "\t\t[ERROR] File reading failed, maybe invalid path?\n";
      return false;
    }
  }

  virtual std::string toString() const{
    return "[ Res: " + std::to_string(width) + "x" + std::to_string(heigth);
  }

  int width, heigth, channels;
  unsigned char * map;
};

#endif
