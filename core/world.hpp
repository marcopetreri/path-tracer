#ifndef _WORLD_
#define _WORLD_

#include <vector>
#include <unordered_map>
#include "utilities/intersection.hpp"

class Accelerator;
class Camera;
class Film;
class Light;
class Material;
class ObjectGroup;
class Ray;
class Stats;
class Parser;
class Sampler;
class Environment;
class Integrator;

class World{
public:
  World();
  ~World();

  void addLight(Light *);
  void addModel(ObjectGroup *);
  void addMaterial(const std::string &, Material *);
  void buildScene(const std::string &);
  // void buildScene(void (*)(World *));
  Intersection intersectTree(const Ray &) const;
  Intersection intersectTree(const Ray &, double) const;
  Vec3d traceRay(Ray &, int) const;
  void renderScene();
  void displayImage() const;
  void Test();

  std::vector<Light *> lights;
  std::vector<ObjectGroup *> models;
  std::vector<Material *> Materials;
  std::unordered_map<std::string, Material *> materials;
  Environment * env;
  Camera * cam;
  Film * film;
  Accelerator * turbo;
  Stats * stats;
  Parser * parser;
  Sampler * sampler;
  Integrator * integrator;
};


#endif
