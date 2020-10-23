




#include <iostream>
#include <vector>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


// TEST_CASE("3 Left rotate")
// {

//  avlt<int, int>  tree;

//   vector<int> keys = { 200, 150, 100};
//   vector<int> heights = {0, 1, 0};

//   for (int key : keys)
//   {
//     tree.insert(key, -key);
//   }

//   //
//   // size and height?  after rebalance should be 1:
//   //
//   REQUIRE(tree.size() == keys.size());

//   auto maxH = std::max_element(heights.begin(), heights.end());

// 	REQUIRE(tree.height() == *maxH);
//   // 
//   // values inserted?
//   //
//   int value;

//   for (int key : keys)
//   {
//     REQUIRE(tree.search(key, value));
//     REQUIRE(value == -key);
//   }

//   //
//   // heights correct after rebalance?
//   //
//   for (size_t i = 0; i < keys.size(); ++i)
//   {
//     REQUIRE((tree % keys[i]) == heights[i]);
//   }



//   }


// TEST_CASE("4 double rotation left then right")
// {

//   avlt<int, int>  tree;

//   vector<int> keys = {100, 90, 150, 75, 130, 175, 85};
//   //vector<int> heights = {3, 2, 1, 1, 0, 0, 0 };
//   vector<int> heights = {2, 0, 1, 0, 0, 0, 1 };

//   for (int key : keys)
//   {
//     tree.insert(key, -key);
//   }
// 	tree.dump(cout);
//   //
//   // size and height?  after rebalance should be 1:
//   //
//   REQUIRE(tree.size() == keys.size());

//  auto maxH = std::max_element(heights.begin(), heights.end());
//  REQUIRE(tree.height() == *maxH);
  
// //  values inserted?
  
//   int value;

//   for (int key : keys)
//   {
//     REQUIRE(tree.search(key, value));
//     REQUIRE(value == -key);
//   }

  
//  // heights correct after rebalance?
  
//   for (size_t i = 0; i < keys.size(); ++i)
//   {
//     REQUIRE((tree % keys[i]) == heights[i]);
//   }


	
	
	
//  }

// TEST_CASE("5 right then left")
// {

	
//   avlt<int, int>  tree;

//   vector<int> keys = {100, 90, 150, 75, 95, 175, 160};
//   vector<int> heights = {2, 1, 0, 0, 0, 0, 1 };

//   for (int key : keys)
//   {
//     tree.insert(key, -key);
// 	//tree.dump(cout);
//   }

//   //
//   // size and height?  after rebalance should be 1:
//   //
//   REQUIRE(tree.size() == keys.size());

//   auto maxH = std::max_element(heights.begin(), heights.end());
//   REQUIRE(tree.height() == *maxH);
//   // 
//   // values inserted?
//   //
//   int value;

//   for (int key : keys)
//   {
//     REQUIRE(tree.search(key, value));
//     REQUIRE(value == -key);
//   }

//   //
//   // heights correct after rebalance?
//   //
//   for (size_t i = 0; i < keys.size(); ++i)
//   {
//     REQUIRE((tree % keys[i]) == heights[i]);
//   }
// //   avlt<int, int>  tree2(tree);
//  	tree.dump(cout);

// // 	tree2.dump(cout);

	
// 	tree.range_search(50,150);
	
// }


TEST_CASE("(18) range search")
{
    avlt<int, int>  tree;

    vector<int> keys = { 30, 15, 50, 45, 10, 70, 13, 28 };
    vector<int> heights = { 3, 1, 1, 0, 0, 0, 2, 0};

//    vector<int> keys = { 30 };
//    vector<int> heights = { 0 };

    for (int key : keys)
    {
        tree.insert(key, -key);
    }

    //
    // size and height?  after rebalance should be 2:
    //
    REQUIRE(tree.size() == keys.size());

    auto maxH = std::max_element(heights.begin(), heights.end());
    REQUIRE(tree.height() == *maxH);
    //
    // values inserted?
    //
    int value;

    for (int key : keys)
    {
        REQUIRE(tree.search(key, value));
        REQUIRE(value == -key);
    }

    //
    // heights correct after rebalance?
    //
    for (size_t i = 0; i < keys.size(); ++i)
    {
        REQUIRE((tree % keys[i]) == heights[i]);
    }

    // testing range search with cout statement in range search
    tree.range_search(14, 90);
	tree.dump(cout);


}