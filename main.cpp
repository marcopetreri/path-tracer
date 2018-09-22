#include <iostream>
// #include "core/appGui.hpp"
#include "core/world.hpp"
#include "core/utilities/buildFunctions.hpp"

int main(int argc, char const * argv[]){

  std::string scene;

  if(argc > 0)
    scene = argv[1];
  else{
    std::cout << "[ERROR] scene's file path not provided. Exit.\n";
    return 0;
  }

  World w;
  w.buildScene(scene);
  w.renderScene();
  // w.Test();

  return 0;
}
