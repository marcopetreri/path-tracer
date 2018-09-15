#include "accelerator.hpp"
#include "../geometricObjects/objectGroup.hpp"
#include "../world.hpp"
#include <algorithm>

Accelerator::Accelerator(World * _w): genMax(6), nPrimsMax(4), w(_w){}

Accelerator::Accelerator(int g, int n, World * _w): genMax(g), nPrimsMax(n), w(_w){}

Accelerator::Accelerator(const Accelerator & a): genMax(a.genMax), nPrimsMax(a.nPrimsMax), w(a.w), root(a.root){}

Accelerator::~Accelerator(){
  delete root;
}

Accelerator & Accelerator::operator=(const Accelerator & a){
  genMax = a.genMax; nPrimsMax = a.nPrimsMax; w = a.w; root = a.root;
  return *this;
}

void Accelerator::setGenMax(int g){genMax = g;}

void Accelerator::setNPrimsMax(int n){nPrimsMax = n;}

void Accelerator::setWorld(World * _w){w = _w;}

int Accelerator::getGenMax() const{return genMax;}

int Accelerator::getNPrimsMax() const{return nPrimsMax;}

World * Accelerator::getWorld() const{return w;}

Node * Accelerator::getRoot() const{return root;}

void Accelerator::init(){
  if(w->models.size() == 0){
    root = new Node(0, 0, new AABB());
    return;
  }
  buildRoot();
  buildSceneTree(root);
}

void Accelerator::buildRoot(){
  // Vec3d min, tmin, tmax, max;
  // min = w->models[0]->min;
  // max = w->models[0]->max;
  // for(auto & x : w->models){
  //   tmin = x->min;
  //   tmax = x->max;
  //   for(int i = 0; i < 3; ++i){
  //     min[i] = tmin[i] < min[i] ? tmin[i] : min[i];
  //     max[i] = tmax[i] > max[i] ? tmax[i] : max[i];
  //   }
  // }

  AABB * bbox = new AABB(Vec3d(0));
  for(auto & x : w->models){
    bbox->operator+=(*x->bbox);
  }

  Vec3d boxDiag = bbox->diag()*.5;
  int axis = 0;
  for(int i = 1; i < 3; ++i)
    if(boxDiag[i] > boxDiag[i-1])
      axis = i;

  root = new Node(0, axis, bbox);

  for(auto & model : w->models)
    importPrims(model);
}

bool Accelerator::buildSceneTree(Node * node){
  if(node->gen == genMax || node->prims.size() <= nPrimsMax ){
    return false;
  }

  Vec3d min = node->bv->min, max = node->bv->max;
  int axis = node->axis;

  // std::sort(node->prims.begin(), node->prims.end(),
  //           [&](Primitive * p1, Primitive * p2){
  //             // return (p1->getMax() + p1->getMin())[axis] < (p2->getMax() + p2->getMin())[axis];
  //             return p1->getMax()[axis] <= p2->getMax()[axis];
  //           });

  // double cutAxis = node->prims[node->prims.size()*.5]->getMin()[axis];
  double cutAxis = ((max - min)*.5)[axis];


  Vec3d leftMax = max, rightMin = min;
  leftMax[axis] -= cutAxis + D_EPS;
  rightMin[axis] += cutAxis - D_EPS;

  int nextAxis = (axis+1)%3;
  node->addChild(new Node(node->gen + 1, nextAxis, new AABB(min,leftMax)));
  node->addChild(new Node(node->gen + 1, nextAxis, new AABB(rightMin,max)));

  for(auto & x : node->prims){
    if(x->getMin()[axis] <= node->children[0]->bv->max[axis]){
      node->children[0]->addPrim(x);
      if(x->getMax()[axis] >= node->children[1]->bv->min[axis])
        node->children[1]->addPrim(x);
    }
    else
      node->children[1]->addPrim(x);
  }

  node->prims.clear();

  // std::cout << "----------------------\n";
  // std::cout << "gen: " << node->gen << "\nprim: \n" << node->children[0]->prims.size() << " - " << node->children[1]->prims.size() << "\n";

  buildSceneTree(node->children[0]);
  buildSceneTree(node->children[1]);

  return true;
}

void Accelerator::startTraversing(const Ray & ray, Intersection & hit){
  double tN, tF;
  if(root->bv->hit(ray, tN, tF)){
    ++hit.nHits;
    pN = ray(tN);
    pF = ray(tF);
    traverse(ray, hit, root);
  }
}

bool Accelerator::traverse(const Ray & ray, Intersection & hit, Node * node) const{

  if(node->isLeaf())
    return node->intersectPrims(ray, hit);
  else if(node->children.size() == 0)
    return false;

  // double cutValue = node->children[1]->bv->min[node->axis];
  // int idxN = (pN[node->axis] > cutValue) ? 1 : 0;
  // int idxF = (pF[node->axis] > cutValue && !idxN) ? 1 : 0;

  // if(traverse(ray, hit, node->children[idxN]))
  //   return true;
  // else if(idxF)
  //   return traverse(ray, hit, node->children[idxF]);
  // else
  //   return false;

  double x,y;

  if(node->children[0]->bv->hit(ray, x, y))
    traverse(ray, hit, node->children[0]);

  if(node->children[1]->bv->hit(ray, x, y))
    traverse(ray, hit, node->children[1]);


  // traverse(ray, hit, node->children[0]);
  // traverse(ray, hit, node->children[1]);

}

void Accelerator::importPrims(ObjectGroup * model){
    if(model->nPrims > 0)
      for(auto & obj : model->objs)
        root->prims.push_back(obj);
    else if(model->nChilds > 0){
      for(auto & child : model->childs)
        importPrims(child);
    }
}

std::ostream & operator<<(std::ostream & os, const Accelerator & acc){
  return os << "Accelerator : { GenMax: " << acc.genMax << ", nPrimsMax: " << acc.nPrimsMax
            << ", Root: " << *acc.root << " }";
}
