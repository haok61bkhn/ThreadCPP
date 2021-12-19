#include "include/demothread.h"

#include <chrono>
#include <stdio.h>
#include <thread>
#include<iostream>

void DemoThread::run() {
  int d=0;
  while (!thread_stop){
    // std::cout<<d<<"\n";
    d+=1;
    this->queue.Push(d);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}
void DemoThread::stop(){
    this->thread_stop=true;
}