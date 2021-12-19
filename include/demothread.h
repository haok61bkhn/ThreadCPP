

#ifndef DEMO_THREAD_H
#define DEMO_THREAD_H

#include "include/cppthread.h"
#include "include/safequeue.h"

class DemoThread : public CppThread {

public:
  DemoThread(SafeQueue<int> &queue){this->queue=queue;};
  void stop();
  SafeQueue<int> queue;

private:
  void run();

private:
  bool thread_stop = false;
  
};

#endif
