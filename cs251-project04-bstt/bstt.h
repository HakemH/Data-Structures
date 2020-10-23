/*bstt.h*/

//
// 
//
// << Hakem Habahbeh >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #04: Threaded binary search tree
//
// Threaded binary search tree isa binary search tree that 
// prints, inserts, searches for values and keys. It is a 
// good way to practice traversing through trees. by organizing
// data and printing it out. 
// 
// 
// 
// 
#pragma once

#include <iostream>

using namespace std;

template<typename KeyT, typename ValueT>
class bstt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded;
  };

  NODE* Root;  // pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)
  NODE* curNext;//global variable to be used in next 
 
 
 void _copy(NODE* cur){// _copy is a helper function for 
					   // the copy constructor
	if (cur == NULL)//if cur is null it returns nothing
       return;
     else
     {
		insert(cur->Key, cur->Value);//calls insert in order to ad a value to the tree
        _copy(cur->Left);//copies the left node and calls itself recursively 
		if(cur->isThreaded == false){// checks if threads are false
			_copy(cur->Right);//copies the right node and calls itself recursively 

		
		}
     }
  }

 NODE* _begin(NODE* cur){
	 if(cur == nullptr){//if cur is null it returns nothing
		 return cur;//returns nullptr
	 }
	 while(cur->Left != nullptr){//loops all the way till it gets to the smallest node
		 cur = cur->Left;// shifts left
	 
	 }
	 return cur;//last node before null
 }

	

  void _postorder(NODE* cur){//deconstructor
							  // keeps going until it deletes the entire tree
    
    if (cur == NULL)//if cur is null it returns nothing
       return;
     else
     {
        _postorder(cur->Left);//calls itself recursively
		if(cur->isThreaded == false){//checks if the current node is threaded
			_postorder(cur->Right);//calls itself recursively
		
		}
		delete cur;// deletes the current node
		
     }
  }

  void _print(NODE* cur, ostream& output) const{// prints the trees nodes inorder
	  
		 if(cur == nullptr)//if cur is null it returns nothing
			 return;
		 else
			_print(cur->Left, output);//calls itself recursively
		 if(cur->isThreaded){//checks if the node is threaded
			 if(cur->Right == nullptr){// checks to see if there is any threads
				 output<<"("<< cur->Key << ","<< cur->Value << ")"<<endl;//prints the without threads 
				 return;
			 }
			 output<< "(" << cur->Key << "," << cur->Value << "," << cur->Right->Key << ")"<<endl;//prints the with threads 

		 }else{
			 output<<"("<< cur->Key << ","<< cur->Value << ")"<<endl;//prints the without threads 

		 }
		 if(cur->isThreaded != true){
		 _print(cur->Right, output);//calls itself recursively
		}
	}

public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  bstt()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor
  //
  bstt(const bstt& other)
  {
	  Root = nullptr;
	  Size = 0;
	  _copy(other.Root);
  }

  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~bstt()
  {
    
	 _postorder(Root);//this postorder helper fuction is my deconstructor
    
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  bstt& operator=(const bstt& other)
  {
    this->clear();// clears this tree

    _copy(other.Root);//calls the copy constructor with the other tree's root
	
    return *this;
  }

  //
  // clear:
  //
  // Clears the contents of the tree, resetting the tree to empty.
  //
  void clear()
  {
    
		_postorder(Root);//calls the deconstructor helper
		Root = nullptr;//sets root to null since we deleted it
		Size = 0;//sets size to 0 since we deleted all the nodes

  }
  //
  //keyFinder function does a search for the key
  //
  bool keyFinder(KeyT key, KeyT& newKey) const{

	 NODE* tempRoot = Root;
     while(tempRoot != nullptr){
        if(tempRoot->Key == key){
			if(tempRoot->Right == nullptr){// checks if there is a value at the right of the key
			   return false;
		     }
           newKey = tempRoot->Right->Key;//saves the found key to new key
		   return true;
		   
        }
	   else if(tempRoot->Key > key ){//go left 
		   
		   tempRoot = tempRoot->Left;
		  }
	   
	   else{
		   if(tempRoot->isThreaded){// checks if it is threaded
			 
			  tempRoot = nullptr;
		   }
		   else{// go right
		   
			  tempRoot = tempRoot->Right;
			  }
		}
      }
     
     
    return false;
	
	}


  // 
  // size:
  //
  // Returns the # of nodes in the tree, 0 if empty.
  //
  // Time complexity:  O(1) 
  //
  int size() const
  {
    return Size;
  }

  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) on average
  //
   bool search(KeyT key, ValueT& value) const
  {
      NODE* cur = Root;
	

    while (cur != nullptr)// runs until it hits null
    {

      if (key == cur->Key) { // found 
		  value = cur->Value;
		  return true;
		} 
		

      if (key < cur->Key)  // search left 
      {

        cur = cur->Left;
      }
      else
      {
		  if(cur->isThreaded){//checks for threads
			  cur = nullptr;
		  }else{           //go right
			  cur = cur->Right;//goes right

		  }
		  
      }
    }//while  
     
    return false;// not found
  }

  //
  // insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // the function returns without changing the tree.
  //
  // Time complexity:  O(lgN) on average
  //
  void insert(KeyT key, ValueT value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;
    //searches the tree to see if it exists
    while (cur != nullptr){
		if(cur->Key == key){
			   return;
			   }
		else if(cur->Key > key ){
				  prev = cur;
				  cur = cur->Left;
				  }
		else{
			if(cur->isThreaded){
					 prev = cur;
					 cur = nullptr;
				   }
				   else{
					   prev= cur; 
					   cur = cur->Right;
					  }
				}

    }// end of while therefore it doesnt exist
	
    NODE* newNode = new NODE();// initializes new Node
    newNode->Key = key;//Sets key
    newNode->Left = nullptr;//sets left child to null
    newNode->Right = nullptr;//sets right child to null
	newNode->Value = value;//sets value
	newNode->isThreaded = false; //initializes threads

   if (prev == nullptr){// checks if prev was null
	   newNode->isThreaded = true;
	   Root = newNode;// sets the root equal to the newNode
   }
   
   else if (key < prev->Key){//left child
   
      prev->Left = newNode;//left node is set to newNode
	  newNode->Right = prev;//sets the nodes right to the prev
	  newNode->isThreaded = true;//left child is threaded
   }
   
   else if (key > prev->Key) {// right child
	  newNode->isThreaded= true;//sets newNode threads to true
	  newNode->Right = prev->Right;//sets previous right node equalto the newNode right child
	  prev->Right = newNode; //prev right is set equal to newNode
	  prev->isThreaded = false;// sets prev threads = to false since we input a child
	  
   }
    Size++;// increment size


  }






  //
  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  ValueT operator[](KeyT key) const
  {
    ValueT temp;//temp value
    if(search(key, temp)){//calls the search function to find the value
 		return temp;//returns the value that was found
	}
	
    return ValueT{ };//returns default value
  }
  

  //
  // ()
  //
  // Finds the key in the tree, and returns the key to the "right".
  // If the right is threaded, this will be the next inorder key.
  // if the right is not threaded, it will be the key of whatever
  // node is immediately to the right.
  //
  // If no such key exists, or there is no key to the "right", the
  // default key value KeyT{} is returned.
  //
  // Time complexity:  O(lgN) on average
  //
  KeyT operator()(KeyT key) const{
	
	KeyT temp;//temp key 
	 
	 if(keyFinder(key, temp)){//calls the keyFinder function to find the key to the right
		  return temp;//returns the key that was found
	  }
    
	return KeyT{ };//returns default value
  }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  //
  //
  void begin(){

	curNext = _begin(Root);//initializes the global variable curNext to the furthest most left node
							//calls the helper function _begin
	}

  //
  // next
  //
  // Uses the internal state to return the next inorder key, and 
  // then advances the internal state in anticipation of future
  // calls.  If a key is in fact returned (via the reference 
  // parameter), true is also returned.
  //
  // False is returned when the internal state has reached null,
  // meaning no more keys are available.  This is the end of the
  // inorder traversal.
  //
  // Space complexity: O(1)
  // Time complexity:  O(lgN) on average
 
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {

      if(curNext != nullptr){// checks to see if curNext is a nullptr

          key = curNext->Key;//sets key 
          if(curNext->isThreaded){//checks if it is not threaded then goes right
              curNext = curNext->Right;// goes right

          }
          else{
              curNext = curNext->Right;//goes right
			  while(curNext->Left !=nullptr){//goes through left until null
				  curNext=curNext->Left;
			  }
          }
        return true;

        }

    return false;
  }

  //
  // dump
  // 
  // Dumps the contents of the tree to the output stream, using a
  // recursive inorder traversal.
  //
  void dump(ostream& output) const
  {
    output << "**************************************************" << endl;
    output << "********************* BSTT ***********************" << endl;

    output << "** size: " << this->size() << endl;

	   _print(Root, output);//calls the helper function to dump

    // inorder traversal, with one output per line: either 
    // (key,value) or (key,value,THREAD)
    //
    // (key,value) if the node is not threaded OR thread==nullptr
    // (key,value,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //

    //
    // TODO
    //

    output << "**************************************************" << endl;
  }
	
};