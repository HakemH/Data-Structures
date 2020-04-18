
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


TEST_CASE("(5) basic symtable test") 
{
  symtable<string, string>  table;
	  string symbol;
  try{
	  table.exitScope();
	  REQUIRE(false);
  }
	catch(...){
		REQUIRE(true);
		
	}
	try{
	  auto scopesave= table.curScope();
	  REQUIRE(false);
  }
	catch(...){
		REQUIRE(true);
		
	}

	
  table.enterScope("x");
  table.insert("Q", "char");
  table.insert("i", "int");
  table.insert("j", "double");
 

 	REQUIRE(!table.lookup("p", symbol, symtable<string, string> :: ScopeOption::CURRENT));
 	REQUIRE(table.lookup("Q", symbol, symtable<string, string> :: ScopeOption::GLOBAL));
 	REQUIRE(table.lookup("j", symbol, symtable<string, string> :: ScopeOption::ALL));


  table.enterScope("New");
  table.insert("f", "double");
  table.insert("o", "int");
  table.insert("t", "double");

	REQUIRE(table.lookup("o", symbol, symtable<string, string> :: ScopeOption::CURRENT));
 	REQUIRE(!table.lookup("p", symbol, symtable<string, string> :: ScopeOption::GLOBAL));
 	REQUIRE(table.lookup("t", symbol, symtable<string, string> :: ScopeOption::ALL));

table.enterScope("New");

  table.insert("a", "char");
  table.insert("o", "int");
  table.insert("t", "double");

	REQUIRE(table.lookup("o", symbol, symtable<string, string> :: ScopeOption::CURRENT));
 	REQUIRE(!table.lookup("a", symbol, symtable<string, string> :: ScopeOption::GLOBAL));
 	REQUIRE(table.lookup("t", symbol, symtable<string, string> :: ScopeOption::ALL));

	
	REQUIRE(table.curScope().Name == "New");
	
	table.insert("i", "int");
	table.insert("i", "double");
	
	REQUIRE(table.size() == 10 );

	
	
	
	
	
	
	
	
 }
