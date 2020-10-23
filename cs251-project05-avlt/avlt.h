/*avlt.h*/

//
// Threaded AVL tree
//
// << Hakem Habahbeh >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #04: Threaded binary search tree
//
// Threaded AVL tree is a binary search tree that rotates 
// in order to stay balanced, by comparing the heights of 
// it's children of specific nodes. This program is inserts,
//  searches for values, keys and heights of a specific node/entry.
//  This program helped with implementing rotations within a BST. 
// 
// 
// 
// 
#pragma once

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

template<typename KeyT, typename ValueT>
class avlt
{
private:
  struct NODE
  {
    KeyT   Key;
    ValueT Value;
    NODE*  Left;
    NODE*  Right;
    bool   isThreaded; // true => Right is a thread, false => non-threaded
    int    Height;     // height of tree rooted at this node
  };

  NODE* Root; 
  NODE* curNext;// pointer to root node of tree (nullptr if empty)
  int   Size;  // # of nodes in the tree (0 if empty)

 NODE* _begin(NODE* cur){
	 if(cur == nullptr){//if cur is null it returns nothing
		 return cur;//returns nullptr
	 }
	 while(cur->Left != nullptr){//loops all the way till it gets to the smallest node
		 cur = cur->Left;// shifts left
	 
	 }
	 return cur;//last node before null
  }
  
  void _copy(NODE* cur){// _copy is a helper function for 
					   // the copy constructor
	if (cur == NULL)//if cur is null it returns nothing
       return;
     else
     {
		_insert(cur->Key, cur->Value);//calls insert in order to ad a value to the tree
        _copy(cur->Left);//copies the left node and calls itself recursively 
		if(cur->isThreaded == false){// checks if threads are false
			_copy(cur->Right);//copies the right node and calls itself recursively 
		}
     }
  }
   //
  //keyFinder function does a search for the key
  // this bool returns true if key is found and is 
  // used to pass the Key's value by reference in 
  // order to access the value of the key later 
  bool _keyFinder(KeyT key, KeyT& newKey) const{

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
		   
		   tempRoot = tempRoot->Left;//moves tempRoot left one node
		  }
	   
	   else{
		   if(tempRoot->isThreaded){// checks if it is threaded
			 
			  tempRoot = nullptr;
		   }
		   else{// go right
		   
			  tempRoot = tempRoot->Right;//moves tempRoot Right one node
			  }
		}
      }
     
     
    return false;
	
	}
	//
	//
	// This isBalanced function finds the difference in heights
	// between the left and right child in order to help figure 
	// out what rotation case should be used later on.
	//
	//
	//
	int _isBalanced(NODE* cur){
		int HR =0, HL = 0, balHeight;
		if((cur == nullptr)){//if the current node is nullptr then that means it
							// has no children
			return 0;
			
		}
		if( (cur->Left == nullptr)){//if the current node is nullptr then that means it's
								// left child's height is -1
			HL = -1;
		}else{
			HL = cur->Left->Height;
		
		
		}
		if( (cur->isThreaded)){ //if the current node is threaded then that means it's
								// right child's height is -1
			HR = -1;
		}else{
			HR = cur->Right->Height;
		
		}
		
		balHeight = HL-HR; //negative is right heavy 
						  //positive is left heavy
		return balHeight;// returns the difference
		
		
	}
	
  bool _heightSearch(KeyT key, int& keyHeight) const{
	
	 NODE* tempRoot = Root;
     while(tempRoot != nullptr){
        if(tempRoot->Key == key){
           keyHeight = tempRoot->Height;//saves the found key to new key
		   return true;
		   
        }
	   else if(tempRoot->Key > key ){//go left 
		   
		   tempRoot = tempRoot->Left;// moves tempRoot left 
		  }
	   
	   else{
		   if(tempRoot->isThreaded){// checks if it is threaded
			 
			  tempRoot = nullptr;
		   }
		   else{// go right
		   
			  tempRoot = tempRoot->Right;// moves tempRoot Right
			  }
		}
      }
     
     
    return false;
	
	}
	
	
	
	
	

	
	
 void _deconstructor(NODE* cur){//deconstructor
							  // keeps going until it deletes the entire tree
    
	if (cur == NULL)//if cur is null it returns nothing
       return;
     else
     {
        _deconstructor(cur->Left);//calls itself recursively
		if(cur->isThreaded == false){//checks if the current node is threaded
			_deconstructor(cur->Right);//calls itself recursively
		
		}
		delete cur;// deletes the current node
		
     }
  }
  
  
  void _RightRotate(NODE* Parent, NODE* N)
  {
     NODE* L = N->Left;//left child of node 
     NODE* A = L->Left;//L's left child
     NODE* B = nullptr;//B is intialized as nullptr
     NODE* C = N->Right;//N's Right child
	 
 	 if(N->isThreaded == true){
 		 C = nullptr;// since N is threaded C has to be nullptr
 	 }
	 
 	 if(L->isThreaded != true){
 		 B= L->Right;// since L is not threaded B has to be L's Right
	 
  	 }

	 L->Right=N;//since L is threaded it points back to N
 	 L->isThreaded = false;

	 
     N->Left = B;//sets N's left child to B 
	 
	 
      if(Parent == nullptr){
         Root = L;//L becomes the root
		 
		 }
      else if (Parent->Left ==N)//if N is left of Parent
         Parent->Left = L;//sets the Left of parent is L from it being N
      else
         Parent->Right = L;//sets the Right of parent is L from it being N
	  
      int HA, HB, HC;
      
      if(A == nullptr)  //if A is nullptr then the height is -1
         HA = -1;
      else{
         HA = A->Height;// HA is the height of A
		 }
      if(B == nullptr){ //if B is nullptr then the height is -1
         HB = -1;
		 
		 }
      else{
         HB = B->Height;// HB is the height of B
		 }
      if(C==nullptr){ //if C is nullptr then the height is -1
         HC = -1;
		 }
      else{
         HC = C->Height;// HC is the height of C
		}
         
   N->Height = 1 + max(HB, HC);// gets the height of N's children and calculates N's height
   L->Height = 1 + max(HA, N->Height);// gets the height of R's children and calculates R's height
  }
  
  
  
  
  
  void _LeftRotate(NODE* Parent, NODE* N)
  {
     NODE* R = N->Right;//right of the root node N if there is no parent
	 NODE* B = R->Left;//left of the R node
     NODE* A = N->Left;//Left child of N
     NODE* C = R->Right;//the right child of R
			

		R->Left = N;//sets the left of R to N(was the root)
		N->Right=B;//sets the right of N to B since it gets unlinked to R 
		if(B == nullptr){	//checks if B is nullptr
			
			N->Right = R;//if b is nullptr then N is threaded to R which is the new root if there is no parent
			N->isThreaded = true;
		 
		 
		 }
		 
      if(Parent == nullptr)
         Root = R ;//R becomes the root
      else if (Parent->Right == N)//if N is right of Parent
         Parent->Right = R;//sets the Right of parent is R from it being N 
      else//if N is left of Parent
         Parent->Left = R;//sets the left of parent is R from it being N 
      
      int HA, HB, HC;
      
      if(A == nullptr) //if A is nullptr then the height is -1
         HA = -1;
      else{
         HA = A->Height;// HA is the height of A
		 }
      if(B == nullptr) //if B is nullptr then the height is -1
         HB = -1;
      else{
         HB = B->Height;// HB is the height of B
		 }
      if(C->isThreaded) //if C is nullptr then the height is -1
         HC = -1;
      else{
         HC = C->Height;// HC is the height of C
		 }
		 
   N->Height = 1 + max(HA,HB);// gets the height of N's children and calculates N's height
   R->Height = 1 + max(HC, N->Height);// gets the height of R's children and calculates R's height

  }

void _print(NODE* cur, ostream& output) const{// prints the trees nodes inorder
	  
		 if(cur == nullptr)//if cur is null it returns nothing
			 return;
		 else
		 {
		 
		_print(cur->Left,output);//calls itself left
	     output<<"("<< cur->Key << ","<< cur->Value << "," << cur->Height;//visits the node part 1 
		 
		 if((!cur->isThreaded) || (cur->Right==nullptr))//checks if cur is not threaded 
			 output<<")"<<endl;//part 2 if there is no threads and the right is not nullptr
		 else
			 output<<","<<cur->Right->Key<<")"<<endl;//part 2 if there are threads and prints out the threads
			 
		 if(!(cur->isThreaded))//if the current node is not threaded then it calls the right side of the inorder
			 _print(cur->Right,output);//calls itself right
		}
	}

  //
  // _insert
  //
  // Inserts the given key into the tree; if the key has already been insert then
  // The whole purpose of this insert function is for it to be used in copy
  // so it can copy a tree without the rotations
  //
  void _insert(KeyT key, ValueT value)
  {
  
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //

    stack<NODE*> nodes;//a stack for all the 
	while (cur != nullptr){
		if(cur->Key == key){
			   return;
		}
		 nodes.push(cur);
		 if(cur->Key > key ){
				  prev = cur;
				  cur = cur->Left;
				  }

		else{
			prev = cur;
			if(cur->isThreaded){
					 prev = cur;
					 cur = nullptr;
				   }
		   else{
			   prev= cur; 
			   cur = cur->Right;
			  }
		}
    }

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
   
    Size++;

    //
    // 5. walk back up tree using stack and update heights.
    
    while (!nodes.empty())//continues running until stack is empty
    {
     cur = nodes.top();//sets the current to the top of the stack
     nodes.pop();
	 
	 int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;//checks if left is null
															 // if so height is -1 default
     
	 int hR =((cur->Right == nullptr) || (cur->isThreaded))? -1 : cur->Right->Height;//checks if right is null
															 // if so height is -1 default
    
	
	 int hCur = 1 + std::max(hL, hR);// find the max between the left and right child
	 
      

      if (cur->Height == hCur)  // didn't change, so no need to go further:
        break;
      else  // height changed, update and keep going:
        cur->Height = hCur;// sets trees height  equal to the hCur
	
	
	
	}//while


    return;
	
  }


public:
  //
  // default constructor:
  //
  // Creates an empty tree.
  //
  avlt()
  {
    Root = nullptr;
    Size = 0;
  }

  //
  // copy constructor
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt (const avlt& other)
  {
	  Root = nullptr;
	  Size = 0;
	  _copy(other.Root);// calls copy helper function
  }

	//
  // destructor:
  //
  // Called automatically by system when tree is about to be destroyed;
  // this is our last chance to free any resources / memory used by
  // this tree.
  //
  virtual ~avlt()
  {
    //
     _deconstructor(Root);//calls deconstructor helper function
    //
  }

  //
  // operator=
  //
  // Clears "this" tree and then makes a copy of the "other" tree.
  //
  // NOTE: makes an exact copy of the "other" tree, such that making the
  // copy requires no rotations.
  //
  avlt& operator=(const avlt& other)
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
	_deconstructor(Root);//calls the deconstructor helper
	Root = nullptr;//sets root to null since we deleted it
	Size = 0;//sets size to 0 since we deleted all the nodes
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
  // height:
  //
  // Returns the height of the tree, -1 if empty.
  //
  // Time complexity:  O(1) 
  //
  int height() const
  {
    if (Root == nullptr)
      return -1;
    else
      return Root->Height;
  }





  // 
  // search:
  //
  // Searches the tree for the given key, returning true if found
  // and false if not.  If the key is found, the corresponding value
  // is returned via the reference parameter.
  //
  // Time complexity:  O(lgN) worst-case
  //
 bool search(KeyT key, ValueT& value) const
  {
      NODE* cur = Root;
	

    while (cur != nullptr)// runs until it hits null
    {

      if (key == cur->Key) { // found 
		  value = cur->Value;//sets value equal to the current nodes value
		  return true;
		} 
		

      if (key < cur->Key)  // search left 
      {

        cur = cur->Left;//moves cur Left one

      }
      else
      {
		  if(cur->isThreaded){//checks for threads
			  cur = nullptr;
		  }else{           
			  cur = cur->Right;//moves cur right one

		  }
		  
      }
    }//while  
     
    return false;// not found
  }

  
  
  // range_search
  //
  // Searches the tree for all keys in the range [lower..upper], inclusive.
  // It is assumed that lower <= upper.  The keys are returned in a vector;
  // if no keys are found, then the returned vector is empty.
  //
  // Time complexity: O(lgN + M), where M is the # of keys in the range
  // [lower..upper], inclusive.
  //
  // NOTE: do not simply traverse the entire tree and select the keys
  // that fall within the range.  That would be O(N), and thus invalid.
  // Be smarter, you have the technology.


vector<KeyT> range_search(KeyT lower, KeyT upper)
  {
     vector<KeyT>  keys;
	
	 NODE* cur = Root;// upper key's Node
	 NODE* prev = Root;//lower key's Node
	 
	 if(lower > upper){//makes sure lower is not bigger than upper
		 return keys;
	 }

    while (prev != nullptr)// runs until it hits null
    { 
	  cur = prev;//sets cur's starting poing as prev
      if (lower == prev->Key) { // found 
		  break;
		  
		}
		
      if (lower < prev->Key)  // search left 
      {
        prev = prev->Left;//moves prev left
      }
      else
      {
		  if(prev->isThreaded){//checks for threads
			  break;
		  }else{                  //go right
			  prev = prev->Right;//moves prev right

		  }

      }
    }//end while
	
		while((cur!= nullptr)  && (cur->Key <= upper)){//makes sure the cur when traversing is not nullptr
													   // keeps going until it's equal to or less than upper 
													   // in order to 
													   
			if(cur->Key >= lower){//checks if the value is greater than lower every time the while loop runs
				keys.push_back(cur->Key);//pushes key into the vector
			
			}
          if(cur->isThreaded){//checks if it is not threaded then goes right
			  
              cur = cur->Right;// pushes key into the vector

          }
          else{
              cur = cur->Right;//goes right
			
			  while(cur->Left !=nullptr){//goes through left until null
				  cur=cur->Left;//moves current node left

			  }//end while
          }

		}//end while


    return keys;//returns the vector we pushed all the keys into
  }



void insert(KeyT key, ValueT value)
  {
    NODE* prev = nullptr;
    NODE* cur = Root;

    //
    // stack the nodes we visit so we can walk back up
    // the search path later, adjusting heights:
    //
    stack<NODE*> nodes;
	while (cur != nullptr){
		if(cur->Key == key){
			   return;
			   }
			   nodes.push(cur);// pushes the value we are about to insert into the stack
		 if(cur->Key > key ){//checks if the current key being inserted is smaller than the current
				  prev = cur;
				  cur = cur->Left; //places cur to the left since it's smaller
				  }
		else{
			prev=cur;
			if(cur->isThreaded){//if it is threaded we break 
					 break;
				   }
				   else{
					   cur = cur->Right;//places cur to the right since it is not threaded
					  }
				}

    }
	
    NODE* newNode = new NODE();// initializes new Node
    newNode->Key = key;//Sets key
    newNode->Left = nullptr;//sets left child to null
    newNode->Right = nullptr;//sets right child to null
	newNode->Value = value;//sets value
	newNode->Height=0;//initializes height of the newNode to 0
	newNode->isThreaded = false; //initializes threads

   if (prev == nullptr){// checks if prev was null
	   
	   Root = newNode;// sets the root equal to the newNode
	   newNode->isThreaded = true;
	   newNode->Right = nullptr;// since root has no right child it is threaded to nullptr
   }
   
   else if (key < prev->Key){//left child
   
      prev->Left = newNode;//left node is set to newNode
	  newNode->Right = prev;//sets the nodes right to the prev
	  newNode->isThreaded = true;//left child is threaded
   }
   
   else //if (key > prev->Key) {// right child
	{ 
	   newNode->Right = prev->Right;//sets previous right node equalto the newNode right child
	   prev->Right = newNode; //prev right is set equal to newNode
	   prev->isThreaded = false;// sets prev threads = to false since we input a child
	   newNode->isThreaded= true;//sets newNode threads to true
	  
   }
   
    Size++;//increment size



    while (!nodes.empty())
    {

      cur = nodes.top();//sets cur to the top of the stack
      nodes.pop();
	  NODE* parent = nullptr;
	  if(!nodes.empty()){//checks the stack to make sure it's not empty after we pop 
		  parent = nodes.top();//
	  }
	 int hL = (cur->Left == nullptr) ? -1 : cur->Left->Height;//checks if left is null
															 // if so height is -1 default
     
	 int hR = (cur->isThreaded) ? -1 : cur->Right->Height;//checks if right is null
															 // if so height is -1 default
     
	 int hCur = 1 + std::max(hL, hR);//height of tree is determined by finding the max between left and right child
	 
     
      if (cur->Height == hCur)  // didn't change, so no need to go further:
        break;
      else  // height changed, update and keep going:
        cur->Height = hCur;//sets the new value for the height of the tree

	int Hdiff =_isBalanced(cur);//returns height difference between the children
		 
		 if((Hdiff<-1)  && (key < cur->Right->Key)){//right side is left heavy case 3 
			   _RightRotate(cur, cur->Right);//calls the right rotate helper
			   _LeftRotate(parent, cur);//calls the left rotate helper
			  
		  }
		  else if((Hdiff <-1) && (key > cur->Right->Key )){//right side is right heavy case 4

			  _LeftRotate(parent, cur);//calls the left rotate helper
		  
		  }
		  
		  		 
		 else if((Hdiff > 1) && (key < cur->Left->Key )){//Left side is left heavy case 1
			 
			  _RightRotate(parent, cur);//calls the left rotate helper

			  
		  }else if((Hdiff>1)  && (key > cur->Left->Key)){ // left side is right heavy case 2

			  _LeftRotate(cur , cur->Left);//calls the left rotate helper
			  _RightRotate(parent, cur);//calls the right rotate helper

  		  }
//////////////////////
		
		
		
		
    }//while















    return;
	
  }







  // []
  //
  // Returns the value for the given key; if the key is not found,
  // the default value ValueT{} is returned.
  //
  // Time complexity:  O(lgN) worst-case
  //
  ValueT operator[](KeyT key) const
  {
    ValueT temp;//temp value
    if(search(key, temp)){//calls the search function to find the value
 		return temp;//returns the value that was found
	}
	
    return ValueT{ };
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
  // Time complexity:  O(lgN) worst-case
  //
  KeyT operator()(KeyT key) const
  {
    KeyT temp;//temp key 
	 
	 if(_keyFinder(key, temp)){//calls the keyFinder helper function to find the key to the right
		  return temp;//returns the key that was found
	  }

    return KeyT{ };
  }

  //
  // %
  //
  // Returns the height stored in the node that contains key; if key is
  // not found, -1 is returned.
  //
  // Example:  cout << tree%12345 << endl;
  //
  // Time complexity:  O(lgN) worst-case
  //
  int operator%(KeyT key) const
  {
   int keyHeight;//height of the spcific key 
	 
	 if(_heightSearch(key, keyHeight)){//calls the keyFinder function to find the key to the right

		 return keyHeight;//returns the key that was found
	  }

    return -1;
  }

  //
  // begin
  //
  // Resets internal state for an inorder traversal.  After the 
  // call to begin(), the internal state denotes the first inorder
  // key; this ensure that first call to next() function returns
  // the first inorder key.
  //
  // Space complexity: O(1)q
  // 
  // Time complexity:  O(lgN) worst-case
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  void begin()
  {
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
  // Time complexity:  O(lgN) worst-case
  //
  // Example usage:
  //    tree.begin();
  //    while (tree.next(key))
  //      cout << key << endl;
  //
  bool next(KeyT& key)
  {
    if(curNext != nullptr){// checks to see if curNext is a nullptr

          key = curNext->Key;//sets key 
          if(curNext->isThreaded){//checks if it is not threaded then goes right
              curNext = curNext->Right;// moves curNext right

          }
          else{
              curNext = curNext->Right;//goes right
			  while(curNext->Left !=nullptr){//goes through left until null
				  curNext=curNext->Left;//moves curNext left
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
    output << "********************* AVLT ***********************" << endl;

    output << "** size: " << this->size() << endl;
    output << "** height: " << this->height() << endl;
	_print(Root, output);//calls printer helper function
    
	
	
	//
    // inorder traversal, with one output per line: either 
    // (key,value,height) or (key,value,height,THREAD)
    //
    // (key,value,height) if the node is not threaded OR thread==nullptr
    // (key,value,height,THREAD) if the node is threaded and THREAD denotes the next inorder key
    //

    //
    // TODO
    //

    output << "**************************************************" << endl;
  }
	
};


