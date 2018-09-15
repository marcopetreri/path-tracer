#ifndef _OBJECT_GROUP_
#define _OBJECT_GROUP_

#include <vector>
#include "primitive.hpp"
#include "../geometry/transform.hpp"
#include "../accelerators/aabb.hpp"

class ObjectGroup{
public:
  ObjectGroup(): nPrims(0), nTotPrims(0), nChilds(0), o2w(new Transform()), bbox(new AABB(Vec3d(0))){}
  ObjectGroup(Transform * t): nPrims(0), nTotPrims(0), nChilds(0), o2w(t), bbox(new AABB(Vec3d(0))){}
  ObjectGroup(const ObjectGroup & og): nPrims(og.nPrims), nTotPrims(og.nTotPrims), nChilds(og.nChilds){
    objs.reserve(og.nPrims);
    for(u_int i = 0; i < og.nPrims; ++i){
      *objs[i] = *og.objs[i];
    }
    childs.reserve(og.nChilds);
    for(u_int i = 0; i < og.nChilds; ++i){
      *childs[i] = *og.childs[i];
    }
    *o2w = *og.o2w;
    *bbox = *og.bbox;
  }
  ~ObjectGroup(){
    for(auto & x : objs)
      delete x;
    for(auto & x : childs)
      delete x;
    delete o2w;
    delete bbox;
  }

  ObjectGroup & operator=(const ObjectGroup & og){
    for(auto & x : objs)
      delete x;
    for(auto & x : childs)
      delete x;
    objs.clear();
    childs.clear();
    if(og.nPrims > 0)
      objs.reserve(og.nPrims);
    if(og.nChilds > 0)
    childs.reserve(og.nChilds);
    for(u_int i = 0; i < og.nPrims; ++i){
      *objs[i] = *og.objs[i];
    }
    for(u_int i = 0; i < og.nChilds; ++i){
      *childs[i] = *og.childs[i];
    }
    nPrims = og.nPrims;
    nTotPrims = og.nTotPrims;
    nChilds = og.nChilds;
    *o2w = *og.o2w;
    *bbox = *og.bbox;
    return *this;
  }

  void addObject(Primitive * p){
    objs.push_back(p);
    ++nPrims;
    ++nTotPrims;
  }

  void addChild(ObjectGroup * og){
    childs.push_back(og);
    nTotPrims += og->nPrims;
    ++nChilds;
  }

  // AABB setBVertex(){
  //   if(nPrims > 0){
  //     for(u_int i = 0; i < nPrims; ++i){
  //       objs[i]->setBVertex();
  //       AABB primBox(objs[i]->getMin(), objs[i]->getMax());
  //       bbox->operator+=(primBox);
  //     }
  //   }
  //   else if(nChilds > 0){
  //     for(u_int i = 0; i < nChilds; ++i){
  //       bbox->operator+=(childs[i]->setBVertex());
  //     }
  //   }
  //   return *bbox;
  // }

  AABB setBVertex(){
    AABB tbox;
    if(nPrims > 0){
      objs[0]->setBVertex();
      tbox = AABB(objs[0]->getMin(), objs[0]->getMax());
      for(u_int i = 1; i < nPrims; ++i){
        objs[i]->setBVertex();
        AABB primBox(objs[i]->getMin(), objs[i]->getMax());
        tbox += primBox;
      }
    }
    else if(nChilds > 0){
      tbox = childs[0]->setBVertex();
      for(u_int i = 1; i < nChilds; ++i){
        tbox += childs[i]->setBVertex();
      }
    }
    *bbox = tbox;
    return *bbox;
  }

  void toWorld(Transform * tr){
    Transform comp = tr ? tr->operator*(*o2w) : *o2w;
    if(nPrims > 0){
      for(auto & x : objs){
        x->applyTransform(&comp);
      }
    }
    else if(nChilds > 0){
      for(auto & x : childs){
        x->toWorld(&comp);
      }
    }
  }

  std::string toString() const{
    if(nPrims > 0){
      return "Object: [ nTotPrims: " + std::to_string(nTotPrims) + ", nPrims: " + std::to_string(nPrims) + ", BBox: " + bbox->toString() + "]";
    }
    else if(nChilds > 0){
      std::string s = "Group: [ ";
      for(auto & i : childs)
        s += i->toString() + ",\n\t\t";
      s += ", BBox: " + bbox->toString() + "]";
      return s;
    }
  }

  u_int nPrims, nTotPrims, nChilds;
  std::vector<Primitive *> objs;
  std::vector<ObjectGroup *> childs;
  Transform * o2w;
  AABB * bbox;
};

#endif
