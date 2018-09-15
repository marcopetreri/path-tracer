
#ifndef _TIMER
#define _TIMER

#include <chrono>
#include <thread>
#include <iostream>

class Timer{
public:
  Timer(): t1(), t2(), dur(){}

  void start(){
    t1 = std::chrono::high_resolution_clock::now();
  }

  void stop(){
    t2 = std::chrono::high_resolution_clock::now();
    dur = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  }

  void sleep(u_int s){
    std::this_thread::sleep_for(std::chrono::milliseconds(s));
  }

  void print(){
    std::cout << dur.count();
  }

  std::chrono::high_resolution_clock::time_point t1, t2;
  std::chrono::milliseconds dur;
};

  // std::ostream & operator<<(std::ostream & os, const Timer & t){
  //   return os << std::chrono::duration_cast<std::chrono::milliseconds>( t.t2 - t.t1 ).count();
  // }

#endif
