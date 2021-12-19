#ifndef SAFEQUEUE
#define SAFEQUEUE
#include <condition_variable>
#include <mutex>
#include <queue>
template <typename T> class SafeQueue {
private:
  std::queue<T> queue; // Use STL queue to store data
  std::mutex mtx;      // The mutex to synchronise on
  std::condition_variable cv;
  std::condition_variable sync_wait;
  bool finish_processing = false;
  int sync_counter = 0;
  void DecreaseSyncCounter();

public:
  SafeQueue();
  ~SafeQueue();
  void Push(const T &data);
  bool Pop(T &item);
  bool PopSync(T &item);
  void Finish();
  int Size();
};
#endif