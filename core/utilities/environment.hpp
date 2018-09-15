#ifndef _ENVIRONMENT_
#define _ENVIRONMENT_

#include "../geometry/vec3d.hpp"
#include "../utilities/texture.hpp"

class Environment{
public:
  Environment(): color(), map(nullptr){}
  Environment(const Vec3d & c): color(c), map(nullptr){}
  Environment(const std::string & path): color(), map(new Texture(path)){}
  ~Environment(){
    delete map;
  }

  Vec3d getUV(const Vec3d & n) const{
    return Vec3d(.5 + atan2(n.x,n.y)*invTWO_PI
                ,.5 - asin(n.z)*invPI
                ,1.);
  }

  Vec3d getColor(const Vec3d & n) const{
    if(map)
      return map->getValue(getUV(n));
    else
      return color;
  }

  std::string toString() const{
    std::string s;
    if(map)
      s = "Map: " + map->toString();
    else
      s = "Color: " + color.toString();
    return "Environment: [ " + s + "]";
  }

  Vec3d color;
  Texture * map;
};



#endif
