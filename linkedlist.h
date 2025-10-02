#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

template <typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node *next;

    Node(T data) {
      this->data = data;
      this->next = nullptr;
    }

    Node(T data, Node *next) {
      this->data = data;
      this->next = next;
    }
  };

  size_t list_size;
  Node *list_front;

 public:
  /**
   * Default constructor. Creates an empty `LinkedList`.
   */
  LinkedList() {
    this->list_size = 0;
    this->list_front = nullptr;
  }

  /**
   * Returns whether the `LinkedList` is empty (i.e. whether its
   * size is 0).
   */
  bool empty() const {
    return this->list_size == 0;
  }

  /**
   * Returns the number of elements in the `LinkedList`.
   */
  size_t size() const {
    return this->list_size;
  }

  /**
   * Adds the given `T` to the front of the `LinkedList`.
   */
  void push_front(T data) {
    Node *newNode = new Node(data);
    newNode->next = list_front;  
    list_front = newNode;
    this->list_size++;
  }

  /**
   * Adds the given `T` to the back of the `LinkedList`.
   */
  void push_back(T data) {
    Node *newNode = new Node(data);
    if (this->list_size == 0) {
      list_front = newNode;
      this->list_size++;
      return;
    }

    Node *currptr = list_front;
    while (currptr->next != nullptr) {
      currptr = currptr->next;
    }

    currptr->next = newNode;
    this->list_size++;
  }

  /**
   * Removes the element at the front of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_front() {
    if (this->empty()) {
      throw runtime_error("operation can not be performed on empty list");
    }

    Node *temp = this->list_front;
    this->list_front = temp->next;
    T data_to_remove = temp->data;
    delete temp;
    this->list_size--;
    return data_to_remove;
  }

  /**
   * Removes the element at the back of the `LinkedList`.
   *
   * If the `LinkedList` is empty, throws a `runtime_error`.
   */
  T pop_back() {
    T data;
    // If list is empty
    if (list_front == nullptr) {
      throw runtime_error("operation can not be performed on empty list");
    }

    // If list only has one element
    if (list_front->next == nullptr) {
      data = list_front->data;
      delete list_front;
      list_front = nullptr;
      this->list_size = 0;
      return data;
    }

    Node *currptr = list_front;
    Node *secondLastNode = nullptr;

    // Loop through the list to get to second to last node and the last node
    while (currptr->next != nullptr) {
      secondLastNode = currptr;
      currptr = currptr->next;
    }

    // Set data at currptr
    data = currptr->data;
    delete currptr;
    secondLastNode->next = nullptr;
    this->list_size--;
    return data;
  }

  /**
   * Empties the `LinkedList`, releasing all allocated memory, and resetting
   * member variables appropriately.
   */
  void clear() {
    while (!this->empty()) {
      this->pop_front();
    }
  }

  /**
   * Destructor. Clears all allocated memory.
   */
  ~LinkedList() {
    this->clear();
  }

  /**
   * Returns the element at the given index in the `LinkedList`.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  T &at(size_t index) const {
    if (index >= this->list_size) {
      throw out_of_range("index is out of range");
    }

    Node *currptr = this->list_front;
    for (int i = 0; i < index; i++) {
      currptr = currptr->next;
    }

    return currptr->data;
  }

  /**
   * Copy constructor. Creates a deep copy of the given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList(const LinkedList &other) {    

    this->list_front = nullptr;
    this->list_size = 0;

    if (other.empty()) {
      return;
    }

    Node *curr = new Node(T{}); 
    Node *prev = curr ;
    Node *other_curr = other.list_front; 

    while (other_curr != nullptr) {
      curr->next = new Node(other_curr->data);
      curr = curr->next;
      other_curr = other_curr->next;
    }
    this->list_front = prev->next;
    this->list_size = other.list_size;
    delete prev;
  }

  /**
   * Assignment operator. Sets the current `LinkedList` to a deep copy of the
   * given `LinkedList`.
   *
   * Must run in O(N) time.
   */
  LinkedList &operator=(const LinkedList &other) {
    // Guard against self assignment
    if (this == &other) {
      return *this;
    }

    // If list is empty
    if (other.list_front == nullptr) {
      this->clear();
      return *this;
    }

    this->clear();

    this->list_front = new Node(other.list_front->data);
    Node *currptr = this->list_front;
    Node *otherptr = other.list_front->next;

    while (otherptr != nullptr) {
      currptr->next = new Node(otherptr->data);
      currptr = currptr->next;
      otherptr = otherptr->next;
    }
    this->list_size = other.size();

    return *this;
  }

  /**
   * Converts the `LinkedList` to a string. Formatted like `[0, 1, 2, 3, 4]`
   * (without the backticks -- hover the function name to see). Runs in O(N)
   * time.
   */
  string to_string() const {
    Node *currptr = this->list_front;
    stringstream oss;
    string llString;

    oss << '[';
    while (currptr != nullptr) {
      T nodeData = currptr->data;
      oss << nodeData;

      if (currptr->next) {
        oss <<  ',';
        oss << ' ';
       
      }
      currptr = currptr->next;
    }
    oss << ']';
    return oss.str();
  }

  /**
   * Searches the `LinkedList` for the first matching element, and returns its
   * index. If no match is found, returns "-1".
   */
  size_t find(const T &data) {
    Node *currptr = this->list_front;
    int counter = 0;

    while (currptr != nullptr) {
      if (currptr->data == data) {
        return counter;
      } else {
        counter++;
      }
      currptr = currptr->next;
    }
    return -1;
  }

  /**
   * Remove the element at the specified index in this list.
   *
   * If the index is invalid, throws `out_of_range`.
   */
  void remove_at(size_t index) {

    if (index > this->list_size) {
      throw out_of_range("index is out of range");
    }

    if (this->empty()) {
      return;
    }

    if (index == 0) {
      Node *temp = this->list_front;
      this->list_front = this->list_front->next;
      delete temp;
      this->list_size--;
      return;
    }

    Node *currptr = this->list_front;
    Node *prevptr = nullptr;

    for (int i = 0; i < index; i++) {
      prevptr = currptr;
      currptr = currptr->next;
      if (currptr == nullptr) {
        break;
      }
    }

    if (currptr != nullptr) {
      prevptr->next = currptr->next;
      delete currptr;
      this->list_size--;
    }
  }

  /**
   * Inserts the given `T` as a new element in the `LinkedList` after
   * the given index. If the index is invalid, throws `out_of_range`.
   */
  void insert_after(size_t index, T data) {
    if (index > this->list_size) {
      throw out_of_range("index is out of range");
    }

    if (this->list_size == 0 && index == 0) {
        throw out_of_range("Cannot insert after on an empty list");
    }

    Node *newNode = new Node(data);
    Node *currptr = this->list_front;

    if (index == 0){
      if(currptr == nullptr) {
        this->list_front = newNode;
        newNode->next = nullptr;
      }
      else {
    newNode->next = currptr->next;
    currptr->next = newNode;
      }
    this->list_size++;
      return;
    }

    for (int i = 0; i < index; i++) {
      currptr = currptr->next;
    }

    newNode->next = currptr->next;
    currptr->next = newNode;
    this->list_size++;
  }

  /**
   * Remove every other element (alternating) from the
   * `LinkedList`, starting at index 1. Must run in O(N).
   *
   * For example, if a list was `[0, 1, 2, 3, 4]`, removing every other element
   * would change the list to `[0, 2, 4]`.
   */
  void remove_every_other() {
    if (this->list_size == 0 || this->list_size == 1) {
      return;
    }

    Node *currptr = this->list_front->next;  // skip first node
    Node *prevptr = this->list_front;

    while (currptr != nullptr) {
      prevptr->next = currptr->next;
      delete currptr;
      currptr = prevptr->next;

      if (currptr != nullptr) {
        prevptr = currptr;
        currptr = prevptr->next;
      }
      this->list_size--;
    }
  }

  /**
   * Returns a pointer to the node at the front of the `LinkedList`. For
   * autograder testing purposes only.
   */
  void *front() const {
    return this->list_front;
  }
};
