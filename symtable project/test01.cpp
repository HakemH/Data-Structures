
//
// << hakem habahbeh >>
// U. of Illinois, Chicago
// CS 251, Spring 2020
// Project #03: symtable test cases
//

#include <iostream>

#include "symtable.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(1) basic symtable test") 
{
  symtable<string, string>  table;
  
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("h", "int");
  table.insert("g", "double");
  table.insert("Q", "int");
  table.insert("R", "double");


  REQUIRE(table.size() == 4);
  REQUIRE(table.numscopes() == 1);
  
  table.enterScope("x");
  table.insert("k", "char");
  
  REQUIRE(table.size() == 5);
  REQUIRE(table.numscopes() == 2); 
  
  //
  // these lookups should both succeed:
  //
  string symbol;
  
  REQUIRE(table.lookup("k", symbol));
  REQUIRE(symbol == "char");
  
  REQUIRE(table.lookup("h", symbol));
  REQUIRE(symbol == "int");
  
  REQUIRE(table.lookup("g", symbol));
  REQUIRE(symbol == "double");
  
  REQUIRE((!table.lookup("x", symbol)));
}
