#include "world.hpp"
#include "geometry/ray.hpp"
#include "accelerators/accelerator.hpp"
#include "samplers/sampler.hpp"
#include "integrators/integrator.hpp"
#include "cameras/camera.hpp"
#include "geometricObjects/objectGroup.hpp"
#include "lights/light.hpp"
#include "materials/material.hpp"
#include "utilities/constants.hpp"
#include "utilities/math.hpp"
#include "utilities/stats.hpp"
#include "utilities/parser.hpp"
#include "utilities/film.hpp"
#include "utilities/environment.hpp"

using namespace std;

int px, py;

World::World(): stats(new Stats(this)), parser(new Parser(this)){}

World::~World(){
  delete env;
  delete cam;
  delete film;
  delete turbo;
  delete stats;
  delete parser;
  delete sampler;
  delete integrator;
  for(auto & x : lights)
  delete x;
  for(auto & x : models)
  delete x;
  for(auto it = materials.begin(); it != materials.end(); ++it)
  delete it->second;
}

void World::addLight(Light * l){
  lights.push_back(l);
}

void World::addModel(ObjectGroup * s){
  models.push_back(s);
}

void World::addMaterial(const std::string & name, Material * m){
  materials[name] = m;
}

void World::buildScene(const std::string & scene){
  cout << "< Building Scene >" << endl;

  // buildFunction(this);

  parser->parseScene(scene);

  turbo->init();

  std::cout << integrator->toString() << "\n";

  cout << "</ Scene Builded >" << endl;
}

Intersection World::intersectTree(const Ray & ray) const{
  Intersection hit;
  hit.t = cam->far;

  turbo->startTraversing(ray, hit);

  return hit;
}

Intersection World::intersectTree(const Ray & ray, double tFar) const{
  Intersection hit;
  hit.t = tFar;

  turbo->startTraversing(ray, hit);

  return hit;
}


void World::renderScene(){
  cout << "< Rendering Scene >" << endl;
  Ray ray;
  Vec3d Lo;

  stats->initialize();
  stats->timer->start();

  // #pragma omp parallel for
  for(int s = 1; s <= sampler->samples; ++s){
    cout << "\tsample : " << s << "\n";
    stats->openProgressBar();
    double n = 1./s;
    for(int i = 0; i < film->area(); ++i){
      px = i%film->width; py = i/film->width;
      sampler->setSeed(i);
      cam->generateRay(ray, sampler->sampleScreen(i, film->width));
      Lo = integrator->solve(ray);
      film->impressAdd(i, Lo);
      stats->next();
      stats->checkProgress();
    }
    sampler->nextSample();
    stats->closeProgressBar();
    film->finalize(0., 1., n);
    film->save();
  }
  stats->timer->stop();
  stats->printStats();
  cout << "</ Scene Rendered >" << endl;
}

// void World::renderScene(){
//   cout << "< Rendering Scene >" << endl;
//   Ray ray;
//   Vec3d Lo;
//   double n = 1./sampler->samples;
//
//   stats->initialize();
//   stats->timer->start();
//   stats->openProgressBar();
//
//   for(int i = 0; i < film->area(); ++i){
//     sampler->setSeed(i);
//     Lo = bgColor;
//     for(int s = 0; s < sampler->samples; ++s){
//       cam->generateRay(ray, i);
//       Lo += traceRay(ray, 1);
//       sampler->nextSample();
//     }
//     film->impress(i, clamp(Lo*n, 0, 1));
//     stats->next();
//     stats->checkProgress();
//   }
//   stats->closeProgressBar();
//   stats->timer->stop();
//   stats->printStats();
//   cout << "</ Scene Rendered >" << endl;
//   film->save("rendering.bmp");
// }

void World::Test(){


  // int samples = 625;
  // // int n = sqrt(samples);
  // Film * img = new Film(100+samples,100+samples,3);
  // MultijitterSampler s(samples);

  // cout << img->map[0] << endl;
  // img->impressAdd(0, WHITE);
  // cout << img->map[0] << endl;
  // img->impressAdd(0, WHITE);
  // cout << img->map[0] << endl;

  // for(int i = 0; i < samples; i++){
  //   img->impress( floor(halton(i, 2)*samples) + i*samples, WHITE);
  // }
  // img->save("hammerslay.bmp");

  // for(int i = 0; i < samples; ++i){
  //   Vec3d smp = s.sampleHemisphere();
  //   std::cout << smp << "\n";
  //   s.nextSample();
  // }


  // u_int p = 4;
  //
  // for(int i = 0; i < samples; i++){
  //   u_int px = permute(i%n, n, p*0xa511e9b3);
  //   u_int py = permute(i/n, n, p*0x63d83595);
  //   float jx = randfloat(i, p*0xa399d265);
  //   float jy = randfloat(i, p*0x711ad6a5);
  //   Vec3f p((i%n + (py+jx)/n)/n, (i/n + (px+jy)/n)/n, 0);
  //   img->impress(i%n*n + i*samples + py + px*samples, WHITE);
  //   cout << px << " "<< py << " " << p  << endl;
  // }
  // img->save("correlated_multijitter.bmp");

  // Parser p(this);
  //
  // Transform * tr = new Transform();
  //
  // std::vector<std::string> res;
  //
  // // std::string s = "*tr(0,-35,11.2)*rz(90)*sc(.18)*";
  // std::string s = "*tr(10,10,10e1)*rz(90)*rz(-90)*rx(-180)*rx(180)*";
  // std::cout << s << "\n";
  //
  // p.parseTransform(s, tr);
  //
  // std::cout << *tr->m << "\n";

}
