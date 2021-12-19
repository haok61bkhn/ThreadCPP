#include "include/demothread.h"
#include "include/safequeue.h"
#include <iostream>
#include <string>
SafeQueue<int> MyQueue;

// void InsertToQueue() {
//   int i = 0;
//   while (true) {
//     MyQueue.Push(++i);
//   }
// }

// void ConsumeFromQueue() {
//   while (true) {
//     int number;
//     std::cout << "Now try to dequeue" << std::endl;
//     bool success = MyQueue.PopSync(number);
//     if (success) {
//       std::cout << "value is " << number << std::endl;
//     } else {
//       std::cout << " queue is stopped" << std::endl;
//       break;
//     }
//   }

//   std::cout << "Que size is : " << MyQueue.Size() << std::endl;
// }

int main() {
  bool stop = false;
  int item;
  DemoThread thread1(MyQueue);
  thread1.start();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  thread1.queue.PopSync(item);
  std::cout<<item;
  thread1.stop();
  thread1.join();

  return 0;
}