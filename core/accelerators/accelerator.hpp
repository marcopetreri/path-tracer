#ifndef _ACCELERATOR_
#define _ACCELERATOR_

#include "node.hpp"

class World;
class Intersection;
class ObjectGroup;

class Accelerator{
public:
  Accelerator(World *);
  Accelerator(int, int, World *);
  Accelerator(const Accelerator &);
  ~Accelerator();

  Accelerator & operator=(const Accelerator &);

  void setGenMax(int);
  void setNPrimsMax(int);
  void setWorld(World *);
  int getGenMax() const;
  int getNPrimsMax() const;
  World * getWorld() const;
  Node * getRoot() const;

  void init();
  void buildRoot();
  bool buildSceneTree(Node *);
  void startTraversing(const Ray &, Intersection &);
  bool traverse(const Ray &, Intersection &, Node *) const;
  void importPrims(ObjectGroup *);

  friend std::ostream & operator<<(std::ostream &, const Accelerator &);

private:
  int genMax;
  uint nPrimsMax;
  World * w;
  Node * root;
  Vec3d pN, pF;
};

std::ostream & operator<<(std::ostream &, const Accelerator &);

#endif
