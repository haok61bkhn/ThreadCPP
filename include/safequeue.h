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
  void DecreaseSyncCounter() {
    if (--sync_counter == 0) {
      sync_wait.notify_one();
    }
  };

public:
  SafeQueue(){};
  ~SafeQueue() { Finish(); };
  SafeQueue &operator=(const SafeQueue &t) { return *this; }
  void Push(const T &data) {
    std::lock_guard<std::mutex> lock(mtx);
    queue.push(data);
    cv.notify_one();
  }

  bool Pop(T &item) {
    std::lock_guard<std::mutex> lock(mtx);
    if (queue.empty()) {
      return false;
    }
    item = queue.front();
    queue.pop();
    return true;
  }
  bool PopSync(T &item) {
    std::unique_lock<std::mutex> lock(mtx);
    sync_counter++;
    cv.wait(lock, [&] { return !queue.empty() || finish_processing; });
    if (queue.empty()) {
      DecreaseSyncCounter();
      return false;
    }
    item = queue.front();
    queue.pop();

    DecreaseSyncCounter();
    return true;
  }

  void Finish() {

    std::unique_lock<std::mutex> lock(mtx);

    finish_processing = true;
    cv.notify_all();

    sync_wait.wait(lock, [&]() { return sync_counter == 0; });

    finish_processing = false;
  }
  int Size() {
    std::lock_guard<std::mutex> lock(mtx);
    return queue.size();
  }
};
#endif