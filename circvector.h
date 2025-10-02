#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

//*************FOR O(1) TIME COMPLEXITY, THERE HAS TO BE DIRECT INSERTION INTO
// THE ARRAY, NO LOOPING************//

template <typename T>
class CircVector {
 private:
  T *data;           // The array of T data
  size_t vec_size;   // size of array
  size_t capacity;   // Capacity of array
  size_t front_idx;  // index of front of the array

  int wrap(size_t index, int difference) const {
    int indx = (this->capacity + index + difference) % this->capacity;
    return indx;
  }

  void resize() {
    T *newData = new T[this->capacity*2];
    for (int i = 0; i < this->vec_size; i++) {
      newData[i] = this->at(i);
    }

    delete[] this->data;
    this->data = newData;
    this->capacity *= 2;
    this->front_idx = 0;
  }

 public:
  /**
   * Default constructor. Creates an empty `CircVector` with capacity 10.
   */
  CircVector() {
    this->vec_size = 0;
    this->capacity = 10;
    this->data = new T[10];
    this->front_idx = 0;
  }

  /**
   * Creates an empty `CircVector` with given capacity. Capacity must exceed 0.
   */
  CircVector(size_t capacity) {
    if (capacity > 0) {
      this->capacity = capacity;
    } else {
      throw out_of_range("invalid capacity. must exceed zero");
    }

    this->front_idx = 0;
    this->vec_size = 0;
    this->data = new T[this->capacity];
  }

  /**
   * Returns whether the `CircVector` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return this->vec_size == 0;
  }

  /**
   * Returns the number of elements in the `CircVector`.
   */
  size_t size() const {
    return this->vec_size;
  }

  /**
   * Adds the given `T` to the front of the `CircVector`.
   */
  void push_front(T elem) {
    if (this->vec_size == this->capacity) {
      resize();
    }

    this->front_idx = wrap(this->front_idx, -1);
    this->data[this->front_idx] = elem;
    this->vec_size++;
  }

  /**
   * Adds the given `T` to the back of the `CircVector`.
   */
  void push_back(T elem) {
    if (this->vec_size == this->capacity) {
      resize();
    }

    this->data[wrap(this->front_idx, this->vec_size)] = elem;
    this->vec_size++;
  }

  /**
   * Removes the element at the front of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (this->vec_size == 0) {
      throw runtime_error("operation can not be performed on empty vector");
    }

    T idxData = data[this->front_idx];
    this->front_idx = wrap(this->front_idx, 1);
    this->vec_size--;
    return idxData;
  }

  /**
   * Removes the element at the back of the `CircVector`.
   *
   * If the `CircVector` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    if (this->vec_size == 0) {
      throw runtime_error("operation can not be performed on empty vector");
    }

    int idx = wrap(this->front_idx, this->vec_size - 1);
    size_t idxData = this->data[idx];
    this->vec_size--;
    return idxData;
  }

  /**
   * Removes all elements from the `CircVector`.
   */
  void clear() {
    this->vec_size = 0;
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~CircVector() {
    delete[] this->data;
  }

  /**
   * Returns the element at the given index in the `CircVector`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T &at(size_t index) const {
    if (index < 0 || index >= this->size()) {
      throw out_of_range("index is out of range");
    }
    int indx = wrap(this->front_idx, index);
  
    return this->data[indx];
  }

  /**
   * Copy constructor. Creates a deep copy of the given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector(const CircVector &other) {
    this->data = new T[other.capacity];
    for (int i = 0; i < other.size(); i++) {
      this->data[i] = other.at(i);
    }

    this->capacity = other.capacity;
    this->vec_size = other.vec_size;
    this->front_idx = 0;
  }

  /**
   * Assignment operator. Sets the current `CircVector` to a deep copy of the
   * given `CircVector`.
   *
   * Must run in O(N) time.
   */
  CircVector &operator=(const CircVector &other) {
    // guard against self assignment
    if (this == &other) {
      return *this;
    }

    delete[] this->data;
    this->data = new T[other.capacity];
    this->capacity = other.capacity;
    this->vec_size = other.vec_size;
    this->front_idx = 0;

    for (int i = 0; i < other.size(); i++) {
      this->data[i] = other.at(i);
    }
    return *this;
  }

  /**
   * Converts the `CircVector` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    stringstream oss;

    oss << '[';
    for (int i = 0; i < this->vec_size; i++) {
      T cvString = this->at(i);
      oss << cvString;
      
      if (i == this->vec_size - 1) {
        break;
      } else {
        oss << ',';
        oss << ' ';
      }
    }
    oss << ']';

    return oss.str();
  }

  /**
   * Searches the `CircVector` for the first matching element, and returns its
   * index in the `CircVector`. If no match is found, returns "-1".
   */
  size_t find(const T &target) {
    for (int i = 0; i < this->vec_size; i++) {
      if (data[wrap(this->front_idx, i)] == target) {
        return i;
      }
    }
    return -1;
  }

  /**
   * Remove the element at the specified index in this list.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  void remove_at(size_t index) {

    if (index >= this->vec_size) {
      throw out_of_range("index is out of range");
    }

    T *newData = new T[this->capacity - 1];
    for (size_t i = 0; i < index; i++) {
      newData[i] = this->data[wrap(this->front_idx, i)];
    }

    for (size_t i = index + 1; i < this->vec_size; i++) {
      newData[i - 1] = this->data[wrap(this->front_idx, i)];
    }
    
    delete[] this->data;
    this->data = newData;
    this->vec_size--;
    this->front_idx = 0;
  }

  /**
   * Inserts the given `T` as a new element in the `CircVector` after
   * the given index. If the index is invalid, throws `out_of_range`.
   */
  void insert_after(size_t index, T elem) {
    if (index > this->vec_size) {
      throw out_of_range("index is out of range");
    }
    if (this->empty()){
      throw out_of_range("cant insert after on an empty vector");
    }

    if (this->vec_size == this->capacity) {
      resize();
    }

    T *newData = new T[this->capacity];
    for (int i = 0; i <= index; i++) {
      newData[i] = this->data[wrap(this->front_idx, i)];
    }

    newData[index + 1] = elem;
    for (int i = index + 1; i < this->vec_size; i++) {
      newData[i + 1] = this->data[wrap(this->front_idx, i)];
    }

    delete[] this->data;
    this->data = newData;
    this->vec_size++;
    this->front_idx = 0;
  }

  /**
   * Remove every other element (alternating) from the
   * `CircVector`, starting at index 1. Must run in O(N). May not reallocate.
   */
  void remove_every_other() {
    if (this->vec_size == 0 || this->vec_size == 1) {
      return;
    }

    int counter = 0;
    for (int i = 0; i < this->vec_size; i++) {
      if (i % 2 == 0) {
        this->at(counter) = this->at(i);
        counter++;
      }
    }
    this->vec_size = counter;
    }
    
  /**
   * Returns a pointer to the underlying memory managed by the `CircVec`.
   * For autograder testing purposes only.
   */
  T *get_data() const {
    return this->data;
  }

  /**
   * Returns the capacity of the underlying memory managed by the `CircVec`. For
   * autograder testing purposes only.
   */
  size_t get_capacity() const {
    return this->capacity;
  }
};
