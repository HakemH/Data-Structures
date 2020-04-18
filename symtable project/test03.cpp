
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


TEST_CASE("(3)symtable test #3 Key check") 
{
  symtable<string, string>  table;
  
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1);
  
  //
  // these lookups should both succeed:
  //
  string symbol;
  

  
  REQUIRE(table.lookup("i", symbol));
  REQUIRE(symbol == "int");
  
  REQUIRE(table.lookup("j", symbol));
  REQUIRE(symbol == "double");
  
  //
  // this lookup should return false:
  table.insert("i", "char");
  REQUIRE(table.size() == 2);
}
