#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T> class FixedQueue {
private:
  const size_t N;       // 队列的大小，构造时确定
  std::vector<T> data_; // 使用std::vector，可以在运行时resize
  size_t front_;
  size_t back_;
  size_t size_;

public:
  FixedQueue(size_t capacity)
      : N(capacity), data_(capacity), front_(0), back_(0), size_(0) {}
  void push(const T &value) {
    if (isFull()) {
      // 队列已满，覆盖队首元素
      data_[back_] = value; // 覆盖
      back_ = (back_ + 1) % N;
      front_ = (front_ + 1) % N; // front也要移动
      // size_ 不变，因为没有新增元素，只是替换了
    } else {
      // 队列未满，正常添加
      data_[back_] = value;
      back_ = (back_ + 1) % N;
      ++size_;
    }
  }
  T pop() {
    if (isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }
    T value = data_[front_];
    front_ = (front_ + 1) % N;
    --size_;
    return value;
  }
  T front() const {
    if (isEmpty()) {
      throw std::runtime_error("Queue is empty");
    }
    return data_[front_];
  }
  bool isEmpty() const { return size_ == 0; }
  bool isFull() const { return size_ == N; }
  size_t size() const { return size_; }
  std::vector<T> data() const { return data_; }
};
