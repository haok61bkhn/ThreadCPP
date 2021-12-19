#include "include/safequeue.h"
template <typename T> SafeQueue<T>::SafeQueue(){};
template <typename T> SafeQueue<T>::~SafeQueue() { Finish(); };
template <typename T> void SafeQueue<T>::DecreaseSyncCounter() {
  if (--sync_counter == 0) {
    sync_wait.notify_one();
  }
}

template <typename T> void SafeQueue<T>::Push(const T &data) {
  std::lock_guard<std::mutex> lock(mtx);
  queue.push(data);
  cv.notify_one();
}

template <typename T> bool SafeQueue<T>::Pop(T &item) {
  std::lock_guard<std::mutex> lock(mtx);
  if (queue.empty()) {
    return false;
  }
  item = queue.front();
  queue.pop();
  return true;
}

template <typename T> bool SafeQueue<T>::PopSync(T &item) {

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

template <typename T> void SafeQueue<T>::Finish() {

  std::unique_lock<std::mutex> lock(mtx);

  finish_processing = true;
  cv.notify_all();

  sync_wait.wait(lock, [&]() { return sync_counter == 0; });

  finish_processing = false;
}

template <typename T> int SafeQueue<T>::Size() {
  std::lock_guard<std::mutex> lock(mtx);
  return queue.size();
}
