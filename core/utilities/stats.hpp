#ifndef _STATS_
#define _STATS_

#include "timer.hpp"
#include "../world.hpp"
#include "../utilities/film.hpp"
#include "../geometricObjects/objectGroup.hpp"

class Stats{
public:
  Stats(World * _w): timer(new Timer), w(_w){}
  ~Stats(){
    delete timer;
  }

  void initialize(){
    for(auto & x : w->models)
      totalPrims += x->nTotPrims;
    totalHits = w->film->width*w->film->heigth*totalPrims;
    rays = totalPixel = w->film->width*w->film->heigth;
    step = 20;
    increment = totalPixel/step;
  }

  void openProgressBar() const{
    std::cout << "\t0\%";
    for(int i = 0; i < step/2 - 2; ++i)
      std::cout << " ";
    std::cout << "50\%";
    for(int i = 0; i < step/2 - 3; ++i)
      std::cout << " ";
    std::cout << "100\%\n\t[";
    std::cout.flush();
  }

  void closeProgressBar() const{
    std::cout << "]\n";
  }

  void printStats() const{
    std::cout << "\tTempo di rendering: "; timer->print(); std::cout << " ms\n";
    std::cout << "\tNumero di intersezioni teoriche: " << totalHits << "\n";
    std::cout << "\tNumero di intersezioni lanciate: " << hits << "\n";
    std::cout << "\tNumero di raggi tracciati: " << rays << "\n";
    std::cout << "\tNumero di primitive: " << totalPrims << "\n";
    std::cout << "\tRapporto: " << totalHits/hits << "\n";
  }

  void next(){
    ++current;
  }

  void checkProgress(){
    if(current > progress){
      std::cout << "=";
      std::cout.flush();
      progress += increment;
    }
  }

  double hits, totalHits;
  double rays, totalPrims = 0;
  double totalPixel, increment, progress = 0, current = 0, step;
  Timer * timer;
  World * w;
};


#endif
