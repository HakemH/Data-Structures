
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


TEST_CASE("(6) testing the painful numero 10") 
{
	  symtable<string, string>  table;

  	  string symbol;

  table.enterScope("opo");
  table.insert("Q", "char");
  table.insert("i", "int");
  table.insert("j", "double");
 

 	REQUIRE(!table.lookup("p", symbol, symtable<string, string> :: ScopeOption::CURRENT));
 	REQUIRE(table.lookup("Q", symbol, symtable<string, string> :: ScopeOption::GLOBAL));
 	REQUIRE(table.lookup("j", symbol, symtable<string, string> :: ScopeOption::ALL));
	
	REQUIRE(table.size() == 3);
	REQUIRE(table.numscopes() == 1);

	table.exitScope();
	
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 0);
	
	table.enterScope("spaghetti");
	 table.insert("noodles", "int");
	 table.insert("sauce", "double");


 	REQUIRE(table.lookup("sauce", symbol, symtable<string, string> :: ScopeOption::CURRENT));
 	REQUIRE(table.lookup("noodles", symbol, symtable<string, string> :: ScopeOption::GLOBAL));
 	REQUIRE(!table.lookup("j", symbol, symtable<string, string> :: ScopeOption::ALL));
	
	table.exitScope();
 	
	REQUIRE(!table.lookup("sauce", symbol, symtable<string, string> :: ScopeOption::CURRENT));
 	REQUIRE(!table.lookup("noodles", symbol, symtable<string, string> :: ScopeOption::GLOBAL));
 	REQUIRE(!table.lookup("j", symbol, symtable<string, string> :: ScopeOption::ALL));
	
	
	
	REQUIRE(table.size() == 0);
	REQUIRE(table.numscopes() == 0);
	
	
	
 }
