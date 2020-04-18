
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


TEST_CASE("(2)symtable test # 2 insert") 
{
  symtable<string, string>  table;
   string symbol;
  REQUIRE(table.size() == 0);
  REQUIRE(table.numscopes() == 0);

  table.enterScope("global");
  
  table.insert("i", "int");
  table.insert("j", "double");
  
  REQUIRE(table.size() == 2);
  REQUIRE(table.numscopes() == 1);
  
  table.enterScope("scopeDos");
  table.insert("k", "char");
    
  REQUIRE(table.lookup("k", symbol));
  REQUIRE(symbol == "char");
  REQUIRE(table.size() == 3);
	
  REQUIRE(table.numscopes() == 2);
  table.exitScope();
  REQUIRE(table.size() == 2);

  REQUIRE(table.numscopes() == 1);
 


  
  REQUIRE(table.lookup("i", symbol));
  REQUIRE(symbol == "int");
  
  REQUIRE(table.lookup("j", symbol));
  REQUIRE(symbol == "double");
  
  //
  // this lookup should return false:
  //
}
