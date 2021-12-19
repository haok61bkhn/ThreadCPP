#include "include/safequeue.h"
#include <iostream>
#include <string>

SafeQueue<int> MyQueue;

void InsertToQueue() {
  int i = 0;
  while (true) {
    MyQueue.Push(++i);
  }
}

void ConsumeFromQueue() {
  while (true) {
    int number;
    std::cout << "Now try to dequeue" << std::endl;
    bool success = MyQueue.PopSync(number);
    if (success) {
      std::cout << "value is " << number << std::endl;
    } else {
      std::cout << " queue is stopped" << std::endl;
      break;
    }
  }

  std::cout << "Que size is : " << MyQueue.Size() << std::endl;
}

int main() {

  std::cout << "Test Started" << std::endl;

  int endMain;

  std::cin >> endMain;

  return 0;
}