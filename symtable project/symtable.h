 /*symtable.h*/

// 
// << Hakem Haabahbeh>>
// UIN: 669327508
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #03: symtable
//
// Symbol Table: a symbol table is a stack of scopes, typically used by a
// compiler to keep track of symbols in a program (functions, variables,
// types, etc.).  In most programming languages, you "enter scope" when you 
// see {, and "exit scope" when you see the corresponding }.  Example:
//
// int main()
// {              <-- enterScope()
//    int i;      <-- enter "i" into symbol table as type "int"
//    .
//    .
//    while (true)
//    {              <-- enterScope()
//       char i;     <-- enter "i" into symbol table as type "char"
//
// Notice there are two variables named "i", which is legal because
// they are in different scopes.
//

#pragma once

#include <iostream>
#include <deque>
#include <map>

using namespace std;

template<typename KeyT, typename SymbolT>
class symtable
{
public:
  //
  // A symbol table is a stack of scopes.  Every scope has a name, and 
  // we use a map to hold the symbols in that scope.  You can *add* to
  // this class, but you must use the Name and Symbols as given to store
  // the scope name, and scope symbols, respectively.
  //
  class Scope
  {
  public:
    string              Name;
    map<KeyT, SymbolT>  Symbols;

    // constructors:
    Scope()
    {
      // default empty string and an empty map:
    }

    Scope(string name)
    {
      this->Name = name;
      // empty map created by map's constructor:
    }
  };

private:
	
  deque<Scope> scopeStore;// deque declaration
  int count = 0; 
  

public:
  enum class ScopeOption
  {
    ALL, 
    CURRENT,
    GLOBAL
  };

  //
  // default constructor:
  //
  // Creates a new, empty symbol table.  No scope is open.
  //
  symtable()
  {
    //
    // TODO: note that member variables will have their default constructor 
    // called automatically, so there may be nothing to do here.
  }

  //
  // size
  //
  // Returns total # of symbols in the symbol table.
  //
  // Complexity: O(1)
  //
  int size() const
  {
   
    return count;//counter used to count the number of maps in each scope
  }

  //
  // numscopes
  //
  // Returns the # of open scopes.
  //
  // Complexity: O(1)
  //
  int numscopes() const
  {
    return scopeStore.size();// counts the size of the deque and returns
  }

  //
  // enterScope
  //
  // Enters a new, open scope in the symbol table, effectively "pushing" on
  // a new scope.  You must provide a name for the new scope, although
  // the name is currently used only for debugging purposes.
  //
  // NOTE: the first scope you enter is known as the GLOBAL scope, since this
  // is typically where GLOBAL symbols are stored.  
  //
  // Complexity: O(1)
  //
  void enterScope(string name)
  {
    Scope newScope(name);//declares a new scope to push into the deque
	scopeStore.push_front(newScope);//pushes the newly created scope into the deque
  }

  //
  // exitScope
  //
  // Exits the current open scope, discarding all symbols in this scope.
  // This effectively "pops" the symbol table so that it returns to the 
  // previously open scope.  A runtime_error is thrown if no scope is 
  // currently open.  
  //
  // Complexity: O(1)
  //
  void exitScope()
  {
    //
    // TODO:
    if(numscopes() == 0){
	//throw runtime error
		throw runtime_error("symtable::exitScope: empty");
	
	}
	else{
		count = count - scopeStore.front().Symbols.size();// subtracts the number of Symbols from the counted ones from the insert function
		scopeStore.pop_front();// pops the current scope aka the front/top
	}
	
  }

  //
  // curScope
  //
  // Returns a the current scope.  A runtime_error is thrown if
  // no scope is currently open.
  //
  // Complexity: O(N) where N is the # of symbols in the current scope
  //
  Scope curScope() const
  {
  
  if(numscopes() <= 0){
		throw runtime_error("symtable::curScope: empty");
	}
	return scopeStore.front();//returns the front of the deque since we are using it like a stack

  }

  //
  // insert
  //
  // Inserts the (key, symbol) pair in the *current* scope.  If the key
  // already exists in the current scope, the associated symbol is replaced
  // by this new symbol.
  //
  // Complexity: O(lgN) where N is the # of symbols in current scope
  //
  void insert(KeyT key, SymbolT symbol)
  {
		if(scopeStore.front().Symbols.count(key) == 1 ){ //checks if there is a value stored in the specific key location
			scopeStore.front().Symbols[key] = symbol;//overwrites the stored value with symbol
		} 
		else{
			scopeStore.front().Symbols[key] = symbol; // sets a value at the location key where there wasnt one before
			++count;//counts the amount of added maps 

		}
    }

  //
  // lookup
  //
  // Searches the symbol table for the first (key, symbol) pair that 
  // matches the given key.  The search starts in the current scope, and 
  // proceeds "outward" to the GLOBAL scope.  If a matching (key, symbol)
  // pair is found, true is returned along with a copy of the symbol (via 
  // "symbol" reference parameter).  If not found, false is returned and
  // the "symbol" parameter is left unchanged.
  //
  // NOTE: the search can be controlled by the "option" parameter.  By 
  // default, the entire symbol table is searched as described above.
  // However, the search can also be limited to just the current scope, 
  // or just the GLOBAL scope, via the "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   string                   symbol;
  //   bool                     found;
  //   ...
  //   found = table.lookup("i", 
  //                        symbol, 
  //                        symtable<string,string>::ScopeOption::CURRENT);
  //
  // Complexity: O(SlgN) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  bool lookup(KeyT key, 
              SymbolT& symbol, 
              ScopeOption option = ScopeOption::ALL) const
  {
	if (scopeStore.empty()) {//checks if the deque is emppty and returns false if it is empty
		return false;
	}
    if(option == ScopeOption:: GLOBAL){
		try{//acts as a check to make sure the scope isnt empty if it is it sends it to catch and then returns false
			
			symbol = scopeStore.back().Symbols.at(key);// sets symbol equal to the current scope's maps key
			return true;
		}
		catch (...) {//catches all the exception cases and returns false in order to keep it from crashing
			return false;
		}
	}
	else if (option == ScopeOption:: CURRENT){
		
		try{//acts as a check to make sure the scope isnt empty if it is it sends it to catch and then returns false
			symbol = scopeStore.front().Symbols.at(key);// sets symbol equal to the current scope's maps key
			return true;
		
		}
		catch(...){//catches all the exception cases and returns false in order to keep it from crashing
			return false;
		}
	}
	else if(option == ScopeOption:: ALL){

		for(auto& scope : scopeStore){//iterates through the entire deque
			
			auto iter = scope.Symbols.find(key);//sets an iterator equal to a key
			if(iter != scope.Symbols.end()){//iterates through the Maps of the the scope that is currently being used
				
				symbol = iter->second;// sets the key of the map equal to a symbol value
				return true;
			}
		}
		return false;
	}
	return false;

  }

  //
  // dump
  // 
  // Dumps the contents of the symbol table to the output stream, 
  // starting with the current scope and working "outward" to the GLOBAL
  // scope.  You can dump the entire symbol table (the default), or dump
  // just the current scope or global scope; this is controlled by the 
  // "option" parameter.
  //
  // Example:
  //   symtable<string,string>  table;
  //   ...
  //   table.dump(std::cout, symtable<string,string>::ScopeOption::GLOBAL);
  //
  // Complexity: O(S*N) where S is the # of scopes and N is the largest #
  // of symbols in any one scope
  //
  void dump(ostream& output, ScopeOption option = ScopeOption::ALL) const
  {
    output << "**************************************************" << endl;

    if (option == ScopeOption::ALL){
		output << "*************** SYMBOL TABLE (ALL) ***************" << endl;
		output << "** # of scopes: " << this->numscopes() << endl;//prints the number of scopes in the deque aka the size of the deque
		output << "** # of symbols: " << this->size() << endl;
		
		for(auto& scope : scopeStore){// iterates through the scopes
			
			output << "** " << scope.Name<< " **"<< endl;//prints the name of the current scope open
			
			for(auto& scope2 : scope.Symbols){//iterates through the symbols of a map
				
				output<< scope2.first << ": "<< scope2.second<< endl;//prints all the maps in the current scope being accessed
			 }
		  }
	  }
    else if (option == ScopeOption::CURRENT){
      output << "*************** SYMBOL TABLE (CUR) ***************" << endl;
	  output << "** # of scopes: " << this->numscopes() << endl;
      output << "** # of symbols: " << this->size() << endl;
	  output << "** " << scopeStore.front().Name<<" **"<< endl;// prints the name of the front/current scope open

	  	  for(auto& scopeCur : scopeStore.front().Symbols){// iterates through the first scopes maps
			
			output<< scopeCur.first << ": "<< scopeCur.second<< endl;//prints out all the maps in the front/current scope
		  }
	  }
    else if(option == ScopeOption::GLOBAL){// global:
		output << "*************** SYMBOL TABLE (GBL) ***************" << endl;
		output << "** # of scopes: " << this->numscopes() << endl;
		output << "** # of symbols: " << this->size() << endl;
		output << "** " << scopeStore.back().Name<<" **"<< endl;//outputs the names starting from the back of the deque

	  	  for(auto& scopeback : scopeStore.back().Symbols){// iterates through the back end of the deck's symbols
			  
			  output<< scopeback.first <<": "  << scopeback.second<< endl;// prints out all the maps in the back/last scope in the deque  
		  }
	}

    //
    // output format per scope:
    //
    // ** scopename **
    // key: symbol
    // key: symbol
    // ...
    //

    output << "**************************************************" << endl;
  }

};
