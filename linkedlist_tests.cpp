#include <gmock/gmock.h>  
#include <gtest/gtest.h>

#include "linkedlist.h"

using namespace std;
using namespace testing;

TEST(LinkedListCore, Constructor_Starting_Size) {
  LinkedList<int> myList;

  EXPECT_THAT(myList.size(), Eq(0));
}

TEST(LinkedListCore, Is_Empty) {
  LinkedList<int> myList;

  EXPECT_THAT(myList.empty(), Eq(true));
}

TEST(LinkedListCore, Is_NotEmpty) {
  LinkedList<int> myList;

  myList.push_back(2);
  EXPECT_THAT(myList.empty(), Eq(false));
}

// Check size after using pushback function
TEST(LinkedListCore, push_back_no_size) {
  LinkedList<int> myList;

  myList.push_back(200);
  myList.push_back(19);

  EXPECT_THAT(myList.size(), Eq(2));
}

TEST(LinkedListCore, push_back) {
  LinkedList<int> myList;

  myList.push_back(10);
  myList.push_back(200);

  int data = myList.at(1);

  EXPECT_THAT(data, Eq(200));
}

TEST(LinkedListCore, push_front) {
  LinkedList<int> myList;

  myList.push_back(4);
  myList.push_back(10);
  myList.push_front(11);
  myList.push_front(13);

  int data = myList.at(0);

  EXPECT_THAT(data, Eq(13));
}

TEST(LinkedListCore, clear) {
  LinkedList<int> myList;

  myList.push_back(4);
  myList.push_back(10);
  myList.push_front(11);
  myList.push_front(13);

  myList.clear();

  EXPECT_THAT(myList.size(), Eq(0));
}

TEST(LinkedListCore, at) {
  LinkedList<int> myList;

  myList.push_back(4);
  myList.push_back(10);
  myList.push_back(4);
  myList.push_back(200);

  EXPECT_THAT(myList.at(2), Eq(4));
}

TEST(LinkedListCore, at_Throw) {
  LinkedList<int> myList;

  myList.push_back(434);
  myList.push_back(10);
  myList.push_back(5);

  EXPECT_THROW(myList.at(6), out_of_range);
}

TEST(LinkedListCore, pop_back_throw) {
  LinkedList<int> myList;

  EXPECT_THROW(myList.pop_back(), runtime_error);
}

TEST(LinkedListCore, pop_back) {
  LinkedList<int> myList;

  myList.push_back(434);
  myList.push_back(10);
  myList.push_back(5);

  myList.pop_back();

  EXPECT_THAT(myList.pop_back(), Eq(10));
}

TEST(LinkedListCore, pop_back_on_one) {
  LinkedList<int> myList;

  myList.push_back(434);

  EXPECT_THAT(myList.pop_back(), Eq(434));
}

TEST(LinkedListCore, pop_front_throw) {
  LinkedList<int> myList;

  EXPECT_THROW(myList.pop_front(), runtime_error);
}

TEST(LinkedListCore, pop_front) {
  LinkedList<int> myList;

  myList.push_back(194);
  myList.push_back(10);
  myList.push_back(17);

  myList.pop_back();

  EXPECT_THAT(myList.pop_front(), Eq(194));
}

TEST(LinkedListAugmented, copy_constructor) {
  LinkedList<int> myList;

  myList.push_back(194);
  myList.push_back(10);
  myList.push_back(17);

  LinkedList<int> myList2(myList);
  

  EXPECT_THAT(myList.size(), Eq(myList2.size()));
}

TEST(LinkedListAugmented, assignment_operator) {
  LinkedList<int> myList;
  LinkedList<int> myList2;

  myList.push_back(194);
  myList.push_back(10);
  myList.push_back(17);

  myList2 = myList;

  EXPECT_THAT(myList.size(), Eq(myList2.size()));
}

TEST(LinkedListAugmented, to_string) {
  LinkedList<int> myList;

  myList.push_back(44);
  myList.push_back(345);
  myList.push_back(6556);
  myList.push_front(3545);
  myList.push_back(23);
  myList.push_back(111);

  EXPECT_THAT(myList.to_string(),
              StrEq("[3545, 44, 345, 6556, 23, 111]")); 
}

TEST(LinkedListAugmented, find) {
  LinkedList<int> myList;

  myList.push_back(304);
  myList.push_back(228);
  myList.push_back(37);  

  EXPECT_THAT(myList.find(37), Eq(2));
}

TEST(LinkedListAugmented, remove_at) {
  LinkedList<int> myList;

  myList.push_back('a');
  myList.push_back('b');
  myList.push_back('c');
  myList.push_back('d');

  myList.remove_at(3);

  EXPECT_THAT(myList.size(), Eq(3));
}

TEST(LinkedListAugmented, assign_self) {
  LinkedList<int> myList;

  myList.push_back(194);
  myList.push_back(10);
  myList.push_back(17);

  LinkedList<int> myList2 = myList;
  LinkedList<int> &currptr = myList;

  myList = currptr;

  EXPECT_THAT(myList.size(), Eq(myList2.size()));
}

TEST(LinkedListAugmented, assign_empty) {
  LinkedList<int> myList;
  LinkedList<int> myList2;

  myList.push_back(194);
  myList.push_back(10);
  myList.push_back(17);

  myList = myList2;

  EXPECT_THAT(myList.size(), Eq(myList.size()));
}

TEST(LinkedListAugmented, find_not_found) {
  LinkedList<int> myList;

  myList.push_back(304);
  myList.push_back(228);
  myList.push_back(37);  

  EXPECT_THAT(myList.find(400), Eq(-1));
}

TEST(LinkedListAugmented, copy_of_empty) {
  LinkedList<int> myList;

  LinkedList<int> myList2 = myList;

  EXPECT_THAT(myList.size(), Eq(myList2.size()));
}

TEST(LinkedListExtras, Remove_Every_Other) {
  LinkedList<int> myList;

  myList.push_back(34553);
  myList.push_back(23);
  myList.push_back(490);
  myList.push_back(313);
  myList.push_back(10000);

  myList.remove_every_other();

  EXPECT_THAT(myList.size(), Eq(3));
}

TEST(LinkedListExtras, Insert_After) {
  LinkedList<int> myList;

  myList.push_back(23);   // 0
  myList.push_back(490);  // 1
  myList.push_back(317);  // 2

  myList.insert_after(2, 999);

  EXPECT_THAT(myList.find(999), Eq(3));
}

TEST(LinkedListExtras, Insert_After_Indx_0) {
  LinkedList<int> myList;

  myList.push_back(23);   // 
  myList.push_back(490);  // 
  myList.push_back(317);

  myList.insert_after(0, 999); 

  EXPECT_THAT(myList.find(999), Eq(1));
}

TEST(LinkedListExtras, Insert_Throw) {
  LinkedList<int> myList;

  myList.push_back(23);    
  myList.push_back(490);   
  myList.push_back(317);

  EXPECT_THROW(myList.insert_after(6, 999), out_of_range);
}

TEST(LinkedListExtras, Remove_Every_Other_Elements) {
  LinkedList<int> myList;

  myList.push_back(34553);
  myList.push_back(23);
  myList.push_back(490);
  myList.push_back(313);
  myList.push_back(10000);

  myList.remove_every_other();

  EXPECT_THAT(myList.to_string(), StrEq("[34553, 490, 10000]"));
}

TEST(LinkedListExtras, Remove_Every_Other_Elements_empty) {
  
  LinkedList<int> myList;

  myList.remove_every_other();

  EXPECT_THAT(myList.size(), Eq(0));
}
