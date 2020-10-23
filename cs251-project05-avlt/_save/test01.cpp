/*test01.cpp*/

//
// Unit tests for threaded AVL tree
//

#include <iostream>
#include <vector>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) empty tree") 
{
  avlt<int, int>  tree;

  REQUIRE(tree.size() == 0);
  REQUIRE(tree.height() == -1);
}
