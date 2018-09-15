#ifndef _MULTIPLE_BRFD_
#define _MULTIPLE_BRFD_

#include "brdf.hpp"
#include <vector>
#include <string>

class Vec3d;
class Intersection;

class MultipleBrdf{
public:
  MultipleBrdf(){}
  MultipleBrdf(Brdf * b){addBrdf(b);}
  MultipleBrdf(const std::vector<Brdf *> & bv): brdfs(bv){}
  virtual ~MultipleBrdf(){
    for(auto & x : brdfs)
      delete x;
  }

  void addBrdf(Brdf * b){
    brdfs.push_back(b);
  }

  virtual Vec3d evaluate(const Vec3d & wo, const Vec3d & wi, Intersection & hit) const = 0;

  double pdf() const{
    return static_cast<double>(brdfs.size());
  }

  virtual std::string toString() const{
    std::string s;
    s += brdfs[0]->toString();
    for(u_int i = 1; i < brdfs.size(); ++i){
      s += " - " + brdfs[i]->toString();
    }
    return s;
  }

  std::vector<Brdf *> brdfs;
};

#endif
