#include <gmock/gmock.h>  
#include <gtest/gtest.h>

#include "circvector.h"

using namespace std;
using namespace testing;

TEST(CircVectorCore, ConstructorSize) {
  CircVector<int> myVec;

  EXPECT_THAT(myVec.size(), Eq(0));
}

// Make sure empty isnt always true or always false
TEST(CircVectorCore, Is_empty) {
  CircVector<int> myVec;

  EXPECT_THAT(myVec.empty(), Eq(true));
}

TEST(CircVectorCore, push_back) {
  CircVector<int> myVec;

  myVec.push_back(3);
  myVec.push_back(1);

  EXPECT_THAT(myVec.at(1), Eq(1));
}

TEST(CircVectorCore, push_front) {
  CircVector<int> myVec;

  myVec.push_back(3);   // index 0
  myVec.push_back(17);  // index 1
  myVec.push_front(1);  // new index 0
  myVec.push_front(3);  // new index 0

  EXPECT_THAT(myVec.at(0), Eq(3));
}

TEST(CircVectorCore, pop_front) {
  CircVector<int> myVec;

  myVec.push_back(3);   // index 0
  myVec.push_back(27);  // index 1
  myVec.push_back(18);  // index 2

  EXPECT_THAT(myVec.pop_front(), Eq(3));
}

TEST(CircVectorCore, pop_back) {
  CircVector<int> myVec;

  myVec.push_back(3);    // index 0
  myVec.push_back(27);   // index 1
  myVec.push_back(100);  // index 2

  EXPECT_THAT(myVec.pop_back(), Eq(100));
}

TEST(CircVectorCore, pop_back_size) {
  CircVector<int> myVec;

  myVec.push_back(3);    // index 0
  myVec.push_back(27);   // index 1
  myVec.push_back(100);  // index 2

  myVec.pop_back();

  EXPECT_THAT(myVec.size(), Eq(2));
}

TEST(CircVectorCore, pop_front_size) {
  CircVector<int> myVec;

  myVec.push_back(3);    // index 0
  myVec.push_back(27);   // index 1
  myVec.push_back(100);  // index 2

  myVec.pop_front();

  EXPECT_THAT(myVec.size(), Eq(2));
}

TEST(CircVectorCore, size) {
  CircVector<int> myVec;

  myVec.push_back(3);    // index 0
  myVec.push_back(27);   // index 1
  myVec.push_back(100);  // index 2

  EXPECT_THAT(myVec.size(), Eq(3));
}

// Should reset the size
// Needs to clean up memory
TEST(CircVectorCore, clear) {
  CircVector<int> myVec;

  myVec.push_back(3);    // index 0
  myVec.push_back(27);   // index 1
  myVec.push_back(100);  // index 2

  myVec.clear();

  EXPECT_THAT(myVec.size(), Eq(0));
}

TEST(CircVectorCore, at_throw) {
  CircVector<int> myVec;

  myVec.push_back(3);    // index 0
  myVec.push_back(27);   // index 1
  myVec.push_back(100);  // index 2

  EXPECT_THROW(myVec.at(11), out_of_range);
}

TEST(CircVectorCore, pop_front_on_empty_vector) {
  CircVector<int> myVec;

  EXPECT_THROW(myVec.pop_front(), runtime_error);
}

TEST(CircVectorCore, pop_back_on_empty_vector) {
  CircVector<int> myVec;

  EXPECT_THROW(myVec.pop_back(), runtime_error);
}

TEST(CircVectorCore, push_back_resize) {
  CircVector<int> myVec;

  myVec.push_back(3);      // 1
  myVec.push_back(27);     // 2
  myVec.push_back(12100);  // 3
  myVec.push_back(13);     // 4
  myVec.push_back(227);    // 5
  myVec.push_back(234);    // 6
  myVec.push_back(312);    // 7
  myVec.push_back(254);    // 8
  myVec.push_back(1030);   // 9
  myVec.push_back(2);      // 10
  myVec.push_back(11);     // 11

  EXPECT_THAT(myVec.at(0), Eq(3));
}

TEST(CircVectorCore, push_front_resize) {
  CircVector<int> myVec(5);

  myVec.push_front(3);     // 0   5      1
  myVec.push_front(27);    // 1   4      2
  myVec.push_front(1210);  // 2   3      3
  myVec.push_front(13);    // 3   2      4
  myVec.push_front(227);   // 4   1      5
  myVec.push_front(234);   // 5   0      6

  EXPECT_THAT(myVec.at(5), Eq(3));
}

TEST(CircVectorCore, pop_back_wrap) {
  CircVector<int> myVec(5);

  myVec.push_back(3);
  myVec.push_back(27);
  myVec.push_front(32);
  myVec.push_back(28);

  EXPECT_THAT(myVec.pop_back(), Eq(28));
}

TEST(CircVectorCore, push_back_wrap) {
  CircVector<int> myVec(10);

  myVec.push_back(3);    // index 1
  myVec.push_back(27);   // index 2
  myVec.push_front(37);  // index 0
  myVec.push_back(627);  // index 3

  EXPECT_THAT(myVec.at(2), Eq(27));
}

TEST(CircVectorAugmented, copy_constructor) {
  CircVector<int> myVec(10);

  myVec.push_back(3);
  myVec.push_back(27);
  myVec.push_back(1300);

  CircVector<int> myVec2(myVec);

for (int i = 0; i < myVec.size(); i++) {
    EXPECT_THAT(myVec.at(i), Eq(myVec2.at(i)));
      
    }
  }

TEST(CircVectorAugmented, assignment_operator) {
  CircVector<int> myVec(10);
  CircVector<int> myVec2(10);

  myVec.push_back(3);
  myVec.push_back(27);
  myVec.push_back(1300);

  myVec2 = myVec;

  for (int i = 0; i < myVec.size(); i++) {
    EXPECT_THAT(myVec.at(i), Eq(myVec2.at(i)));
      
    }
  }

TEST(CircVectorAugmented, assign_self) {  
  CircVector<int> myVec(10);

  myVec.push_back(3);
  myVec.push_back(27);
  myVec.push_back(1300);

  CircVector<int> myVec2 = myVec;
  CircVector<int> &vec = myVec;

  myVec = vec;

for (int i = 0; i < myVec.size(); i++) {
    EXPECT_THAT(myVec.at(i), Eq(myVec2.at(i)));
    }
  }

TEST(CircVectorAugmented, to_string) {
  CircVector<char> myVec(5);

  myVec.push_back('a');
  myVec.push_back('b');
  myVec.push_back('c');
  myVec.push_front('d');
  myVec.push_back('e'); 

  EXPECT_THAT(myVec.to_string(), StrEq("[d, a, b, c, e]"));
}


TEST(CircVectorAugmented, find) {
  CircVector<int> myVec(10);

  myVec.push_back(3);
  myVec.push_back(27);
  myVec.push_back(1300);
  myVec.push_front(203);
  myVec.push_back(333);

  EXPECT_THAT(myVec.find(333), Eq(4));
}

TEST(CircVectorAugmented, not_find) {
  CircVector<int> myVec(10);

  myVec.push_back(3);
  myVec.push_back(27);
  myVec.push_back(1300);
  myVec.push_front(203);
  myVec.push_back(333);

  EXPECT_THAT(myVec.find(423), Eq(-1));
}

TEST(CircVectorAugmented, remove_at) {
  CircVector<int> myVec(10);

  myVec.push_front(3);
  myVec.push_front(27);
  myVec.push_front(1300);
  myVec.push_front(203);
  myVec.push_front(333);

  myVec.remove_at(2);

  EXPECT_THAT(myVec.size(), Eq(4));
}

TEST(CircVectorExtras, insert_after) {
  CircVector<int> myVec(10);

  myVec.push_back(3);   //0
  myVec.push_back(27);  //1
  myVec.push_back(1300); //2

  myVec.insert_after(2, 333);   //3

  EXPECT_THAT(myVec.find(333), Eq(3));
}

TEST(CircVectorExtras, insert_after_0) {
  CircVector<int> myVec(10);

  myVec.push_back(3);   //0
  myVec.push_back(27);  //1
  myVec.push_back(1300); //2

  myVec.insert_after(0, 333);   //3

  EXPECT_THAT(myVec.find(333), Eq(1));
}

TEST(CircVectorExtras, remove_every_other) {
  CircVector<int> myVec(10);

  myVec.push_back(3);   //0
  myVec.push_back(27);  //1
  myVec.push_back(1300); //2
  myVec.push_back(3);   //3
  myVec.push_back(27);  //4
  myVec.push_back(1300); //5
  myVec.push_back(423);  //6

  myVec.remove_every_other();

  EXPECT_THAT(myVec.size(), Eq(4));
}

TEST(CircVectorExtras, insert_after_size) {
  CircVector<int> myVec(10);

  
  myVec.push_back(3);   //0
  myVec.push_back(27);  //1
  myVec.push_back(1760); //2
  myVec.push_back(1300); //2


  myVec.insert_after(2, 333);   //3

  EXPECT_THAT(myVec.size(), Eq(5));
}

TEST(CircVectorExtras, insert_throw) {
  CircVector<int> myVec(10);
  
  myVec.push_back(3);   //0
  myVec.push_back(27);  //1
  myVec.push_back(1300); //2

  EXPECT_THROW(myVec.insert_after(5, 333), out_of_range);
}

TEST(CircVectorExtras, insert_resize) {
  CircVector<int> myVec(5);
  
  myVec.push_back(3);   
  myVec.push_back(27);  
  myVec.push_back(1800); 
  myVec.push_back(1900);
  myVec.push_back(13);

  myVec.insert_after(4, 999);

  EXPECT_THAT(myVec.size(), Eq(6));
}
