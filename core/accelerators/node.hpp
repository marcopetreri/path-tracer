#ifndef _NODE_
#define _NODE_

#include <vector>
#include "aabb.hpp"
#include "../utilities/intersection.hpp"
#include "../geometricObjects/primitive.hpp"

class Node{
public:
  Node(): gen(0), axis(0), bv(new AABB()){}
  Node(int g, int a, AABB * _bv): gen(g), axis(a), bv(_bv){}
  Node(const Node & n): gen(n.gen), axis(n.axis), children(n.children), prims(n.prims){
    *bv = *n.bv;
  }
  ~Node(){
    delete bv;
    for(auto & x : children)
      delete x;
  }

  Node & operator=(const Node & n){
    gen = n.gen; axis = n.axis;
    *bv = *n.bv; children = n.children; prims = n.prims;
    return *this;
  }

  bool isLeaf() const{return prims.size() != 0;}
  void addChild(Node * n){children.push_back(n);}
  void addPrim(Primitive * p){prims.push_back(p);}
  bool intersectPrims(const Ray & ray, Intersection & hit){
    size_t size = prims.size();
    for(size_t i = 0; i < size; ++i){
      prims[i]->hit(ray, hit);
      hit.nHits++;
    }
    return hit.hit;
  }

  int gen, axis;
  AABB * bv;
  std::vector<Node *> children;
  std::vector<Primitive *> prims;
};

inline std::ostream & operator<<(std::ostream & os, const Node & n){
  return os << "Node : { " << *n.bv << ", Nodes: " << n.children.size() << ", Prims: "
            << n.prims.size() << " }";
}


#endif
