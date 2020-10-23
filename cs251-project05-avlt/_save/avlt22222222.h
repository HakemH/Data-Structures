// /*avlt.h*/

// //
// // Threaded AVL tree
// //

// #pragma once

// #include <iostream>
// #include <vector>

// using namespace std;

// template<typename KeyT, typename ValueT>
// class avlt
// {
// private:
//   struct NODE
//   {
//     KeyT   Key;
//     ValueT Value;
//     NODE*  Left;
//     NODE*  Right;
//     bool   isThreaded; // true => Right is a thread, false => non-threaded
//     int    Height;     // height of tree rooted at this node
//   };

//   NODE* Root;  // pointer to root node of tree (nullptr if empty)
//   int   Size;  // # of nodes in the tree (0 if empty)



// 	void _deconstructor(NODE* cur){//deconstructor
// 							  // keeps going until it deletes the entire tree
    
//     if (cur == NULL)//if cur is null it returns nothing
//        return;
//      else
//      {
//         _postorder(cur->Left);//calls itself recursively
// 		if(cur->isThreaded == false){//checks if the current node is threaded
// 			_postorder(cur->Right);//calls itself recursively
		
// 		}
// 		delete cur;// deletes the current node
		
//      }
//   }

// public:
//   //
//   // default constructor:
//   //
//   // Creates an empty tree.
//   //
//   avlt()
//   {
//     Root = nullptr;
//     Size = 0;
//   }

//   //
//   // copy constructor
//   //
//   // NOTE: makes an exact copy of the "other" tree, such that making the
//   // copy requires no rotations.
//   //
//   avlt (const avlt& other)
//   {
//     //
//     // TODO
//     //
//   }

// 	//
//   // destructor:
//   //
//   // Called automatically by system when tree is about to be destroyed;
//   // this is our last chance to free any resources / memory used by
//   // this tree.
//   //
//   virtual ~avlt()
//   {
//     //
//     // _deconstructor(Root);
//     //
//   }

//   //
//   // operator=
//   //
//   // Clears "this" tree and then makes a copy of the "other" tree.
//   //
//   // NOTE: makes an exact copy of the "other" tree, such that making the
//   // copy requires no rotations.
//   //
//   avlt& operator=(const avlt& other)
//   {
//     //
//     // TODO:
//     //

//     return *this;
//   }

//   //
//   // clear:
//   //
//   // Clears the contents of the tree, resetting the tree to empty.
//   //
//   void clear()
//   {
//     //
//     // TODO
//     //
//   }

//   // 
//   // size:
//   //
//   // Returns the # of nodes in the tree, 0 if empty.
//   //
//   // Time complexity:  O(1) 
//   //
//   int size() const
//   {
//     return Size;
//   }

//   // 
//   // height:
//   //
//   // Returns the height of the tree, -1 if empty.
//   //
//   // Time complexity:  O(1) 
//   //
//   int height() const
//   {
//     if (Root == nullptr)
//       return -1;
//     else
//       return Root->Height;
//   }

//   // 
//   // search:
//   //
//   // Searches the tree for the given key, returning true if found
//   // and false if not.  If the key is found, the corresponding value
//   // is returned via the reference parameter.
//   //
//   // Time complexity:  O(lgN) worst-case
//   //
//   bool search(KeyT key, ValueT& value) const
//   {
//     NODE* cur = Root;
	

//     while (cur != nullptr)// runs until it hits null
//     {

//       if (key == cur->Key) { // found 
// 		  value = cur->Value;
// 		  return true;
// 		} 
		

//       if (key < cur->Key)  // search left 
//       {

//         cur = cur->Left;
//       }
//       else
//       {
// 		  if(cur->isThreaded){//checks for threads
// 			  cur = nullptr;
// 		  }else{           //go right
// 			  cur = cur->Right;//goes right

// 		  }
		  
//       }
//     }//while  
     
//     return false;// not found
//   }

//   //
//   // range_search
//   //
//   // Searches the tree for all keys in the range [lower..upper], inclusive.
//   // It is assumed that lower <= upper.  The keys are returned in a vector;
//   // if no keys are found, then the returned vector is empty.
//   //
//   // Time complexity: O(lgN + M), where M is the # of keys in the range
//   // [lower..upper], inclusive.
//   //
//   // NOTE: do not simply traverse the entire tree and select the keys
//   // that fall within the range.  That would be O(N), and thus invalid.
//   // Be smarter, you have the technology.
//   //
//   vector<KeyT> range_search(KeyT lower, KeyT upper)
//   {
//     vector<KeyT>  keys;

//     //
//     // TODO
//     //

//     return keys;
//   }

//   //
//   // insert
//   //
//   // Inserts the given key into the tree; if the key has already been insert then
//   // the function returns without changing the tree.  Rotations are performed
//   // as necessary to keep the tree balanced according to AVL definition.
//   //
//   // Time complexity:  O(lgN) worst-case
//   //
//   void insert(KeyT key, ValueT value)
//   {
//     //
//     // TODO
//     //
//   }

//   //
//   // []
//   //
//   // Returns the value for the given key; if the key is not found,
//   // the default value ValueT{} is returned.
//   //
//   // Time complexity:  O(lgN) worst-case
//   //
//   ValueT operator[](KeyT key) const
//   {
//     ValueT temp;//temp value
//     if(search(key, temp)){//calls the search function to find the value
//  		return temp;//returns the value that was found
// 	}
//     return ValueT{ };
//   }








// bool heightSearch(KeyT key, int& keyHeight) const{
	
// 	 NODE* tempRoot = Root;
//      while(tempRoot != nullptr){
//         if(tempRoot->Key == key){
			
//            keyHeight = tempRoot->Height;//saves the found key to new key
// 		   return true;
		   
//         }
// 	   else if(tempRoot->Key > key ){//go left 
		   
// 		   tempRoot = tempRoot->Left;
// 		  }
	   
// 	   else{
// 		   if(tempRoot->isThreaded){// checks if it is threaded
			 
// 			  tempRoot = nullptr;
// 		   }
// 		   else{// go right
		   
// 			  tempRoot = tempRoot->Right;
// 			  }
// 		}
//       }
     
     
//     return false;
	
// 	}






//  bool keyFinder(KeyT key, KeyT& newKey) const{

// 	 NODE* tempRoot = Root;
//      while(tempRoot != nullptr){
//         if(tempRoot->Key == key){
// 			if(tempRoot->Right == nullptr){// checks if there is a value at the right of the key
// 			   return false;
// 		     }
//            newKey = tempRoot->Right->Key;//saves the found key to new key
// 		   return true;
		   
//         }
// 	   else if(tempRoot->Key > key ){//go left 
		   
// 		   tempRoot = tempRoot->Left;
// 		  }
	   
// 	   else{
// 		   if(tempRoot->isThreaded){// checks if it is threaded
			 
// 			  tempRoot = nullptr;
// 		   }
// 		   else{// go right
		   
// 			  tempRoot = tempRoot->Right;
// 			  }
// 		}
//       }
     
     
//     return false;
	
// 	}







//   //
//   // ()
//   //
//   // Finds the key in the tree, and returns the key to the "right".
//   // If the right is threaded, this will be the next inorder key.
//   // if the right is not threaded, it will be the key of whatever
//   // node is immediately to the right.
//   //
//   // If no such key exists, or there is no key to the "right", the
//   // default key value KeyT{} is returned.
//   //
//   // Time complexity:  O(lgN) worst-case
//   //
//   KeyT operator()(KeyT key) const
//   {
//     KeyT temp;//temp key 
	 
// 	 if(keyFinder(key, temp)){//calls the keyFinder function to find the key to the right
// 		  return temp;//returns the key that was found
// 	  }

//     return KeyT{ };
//   }

//   //
//   // %
//   //
//   // Returns the height stored in the node that contains key; if key is
//   // not found, -1 is returned.
//   //
//   // Example:  cout << tree%12345 << endl;
//   //
//   // Time complexity:  O(lgN) worst-case
//   //
//   int operator%(KeyT key) const
//   {
//     int keyHeight;//height of the spcific key 
	 
// 	 if(heightSearch(key, keyHeight)){//calls the keyFinder function to find the key to the right
// 		  return keyHeight;//returns the key that was found
// 	  } 

//     return -1;
//   }

//   //
//   // begin
//   //
//   // Resets internal state for an inorder traversal.  After the 
//   // call to begin(), the internal state denotes the first inorder
//   // key; this ensure that first call to next() function returns
//   // the first inorder key.
//   //
//   // Space complexity: O(1)
//   // Time complexity:  O(lgN) worst-case
//   //
//   // Example usage:
//   //    tree.begin();
//   //    while (tree.next(key))
//   //      cout << key << endl;
//   //
//   void begin()
//   {
//     //
//     // TODO
//     //
//   }

//   //
//   // next
//   //
//   // Uses the internal state to return the next inorder key, and 
//   // then advances the internal state in anticipation of future
//   // calls.  If a key is in fact returned (via the reference 
//   // parameter), true is also returned.
//   //
//   // False is returned when the internal state has reached null,
//   // meaning no more keys are available.  This is the end of the
//   // inorder traversal.
//   //
//   // Space complexity: O(1)
//   // Time complexity:  O(lgN) worst-case
//   //
//   // Example usage:
//   //    tree.begin();
//   //    while (tree.next(key))
//   //      cout << key << endl;
//   //
//   bool next(KeyT& key)
//   {
//     //
//     // TODO
//     //

//     return false;
//   }

//   //
//   // dump
//   // 
//   // Dumps the contents of the tree to the output stream, using a
//   // recursive inorder traversal.
//   //
//   void dump(ostream& output) const
//   {
//     output << "**************************************************" << endl;
//     output << "********************* AVLT ***********************" << endl;

//     output << "** size: " << this->size() << endl;
//     output << "** height: " << this->height() << endl;

//     //
//     // inorder traversal, with one output per line: either 
//     // (key,value,height) or (key,value,height,THREAD)
//     //
//     // (key,value,height) if the node is not threaded OR thread==nullptr
//     // (key,value,height,THREAD) if the node is threaded and THREAD denotes the next inorder key
//     //

//     //
//     // TODO
//     //

//     output << "**************************************************" << endl;
//   }
	
// };

