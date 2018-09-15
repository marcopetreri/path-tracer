#ifndef _MATERIAL_
#define _MATERIAL_

#include "../brdfs/brdf.hpp"
#include "../brdfs/multipleBrdf.hpp"
#include "../brdfs/addBrdf.hpp"
#include "../geometry/vec3d.hpp"
#include "../utilities/intersection.hpp"
#include <vector>

class Material{
public:
  Material(): mBrdf(new AddBrdf()), reflective(false), emissive(false), reflection(0.)
  ,emission(0.), reflMap(nullptr), emisMap(nullptr), normalMap(nullptr){}
  Material(MultipleBrdf * mb): mBrdf(mb), reflective(false), emissive(false), reflection(0.)
  ,emission(0.), reflMap(nullptr), emisMap(nullptr), normalMap(nullptr){}
  virtual ~Material(){
    delete mBrdf;
    delete reflMap;
    delete emisMap;
    delete normalMap;
  }

  Vec3d shade(const Vec3d & wo, const Vec3d & wi, Intersection & hit) const{
    return mBrdf->evaluate(wo, wi, hit);
  }

  Vec3d sampleMaterial(const Vec3d & wo, Vec3d & wi, const Vec3f & xi, Intersection & hit) const{
    int n = rand()%mBrdf->brdfs.size();
    return mBrdf->brdfs[n]->sample(wo, wi, xi, hit)*mBrdf->pdf();
  }

  void setReflection(const Vec3d & r){
    reflective = true;
    reflection = r;
  }

  void setEmission(const Vec3d & r){
    emissive = true;
    emission = r;
  }

  void setReflMap(const std::string & path){
    reflective = true;
    delete reflMap;
    reflMap = new Texture(path);
  }

  void setEmisMap(const std::string & path){
    emissive = true;
    delete emisMap;
    emisMap = new Texture(path);
  }

  void setNormalMap(const std::string & path){
    delete normalMap;
    normalMap = new Texture(path);
  }

  Vec3d getReflection(const Vec3d & uv) const{
    if(reflMap)
      return reflMap->getValue(uv);
    else
      return reflection;
  }

  Vec3d getEmission(const Vec3d & uv) const{
    if(emisMap)
      return emisMap->getValue(uv);
    else
      return emission;
  }

  bool isReflective() const{
    return reflective;
  }

  bool isEmissive() const{
    return emissive;
  }

  virtual std::string toString() const{
    std::string s, t;
    if(reflective){
      if(reflMap)
        s = "[ RefMap: " + reflMap->toString();
      else
        s = "[ Amount: " + reflection.toString();
    }
    else
      s = "none";
    if(emissive){
      if(emisMap)
        t = "[ EmisMap: " + emisMap->toString();
      else
        t = "[ Amount: " + emission.toString();
    }
    else
      t = "none";
    return "Material: [Refl: " + s + ", Emis:" + t + ", " + mBrdf->toString() + "]";
  }


  MultipleBrdf * mBrdf;
  bool reflective, emissive;
  Vec3d reflection, emission;
  Texture * reflMap, * emisMap,* normalMap;
};

#endif
