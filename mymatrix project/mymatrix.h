/*mymatrix.h*/

// 
// << HAKEM HABAHBEH >>
// U. of Illinois, Chicago
// CS 251: Spring 2020
// Project #02
//

//
// mymatrix
//
// The mymatrix class provides a matrix (2D array) abstraction.
// The size can grow dynamically in both directions (rows and 
// cols).  Also, rows can be "jagged" --- i.e. rows can have 
// different column sizes, and thus the matrix is not necessarily 
// rectangular.  All elements are initialized to the default value
// for the given type T.  Example:
//
//   mymatrix<int>  M;  // 4x4 matrix, initialized to 0
//   
//   M(0, 0) = 123;
//   M(1, 1) = 456;
//   M(2, 2) = 789;
//   M(3, 3) = -99;
//
//   M.growcols(1, 8);  // increase # of cols in row 1 to 8
//
//   for (int r = 0; r < M.numrows(); ++r)
//   {
//      for (int c = 0; c < M.numcols(r); ++c)
//         cout << M(r, c) << " ";
//      cout << endl;
//   }
//
// Output:
//   123 0 0 0
//   0 456 0 0 0 0 0 0
//   0 0 789 0
//   0 0 0 -99
//

#pragma once

#include <algorithm>
#include <iostream>
#include <exception>
#include <stdexcept>

using namespace std;

template<typename T>
class mymatrix
{
private:
  struct ROW
  {
    T*  Cols;     // dynamic array of column elements
    int NumCols;  // total # of columns (0..NumCols-1)
  };

  ROW* Rows;     // dynamic array of ROWs
  int  NumRows;  // total # of rows (0..NumRows-1)

public:
  //
  // default constructor:
  //
  // Called automatically by C++ to construct a 4x4 matrix.  All 
  // elements are initialized to the default value of T.
  //
  mymatrix()
  {
    Rows = new ROW[4];  // an array with 4 ROW structs:
    NumRows = 4;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[4];  // an array with 4 elements of type T:
      Rows[r].NumCols = 4;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  // this sets the default constructor value of 0 to the newly added array indexes
    }
  }
  }

  //
  // parameterized constructor:
  //
  // Called automatically by C++ to construct a matrix with R rows, 
  // where each row has C columns. All elements are initialized to 
  // the default value of T.
  //
  mymatrix(int R, int C){
    if (R < 1){
      throw invalid_argument("mymatrix::constructor: # of rows");
    }
    if (C < 1){
      throw invalid_argument("mymatrix::constructor: # of cols");
      }
    Rows = new ROW[R];  // an array with 4 ROW structs:
    NumRows = R;
      
    for (int r = 0; r < NumRows; ++r)
    {
      Rows[r].Cols = new T[C];  //sets the new size of the cols at row r to int C given by user
      Rows[r].NumCols = C;//sets the number of columns at row r to int C given by user

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)
      {
        Rows[r].Cols[c] = T{};  
      }
    }
  }


  //
  // copy constructor:
  //
  // Called automatically by C++ to construct a matrix that contains a 
  // copy of an existing matrix.  Example: this occurs when passing 
  // mymatrix as a parameter by value
  //
  //   void somefunction(mymatrix<int> M2)  <--- M2 is a copy:
  //   { ... }
  //
  mymatrix(const mymatrix<T>& other)
  {
       this->Rows = new ROW[other.NumRows];
       this->NumRows = other.NumRows;

    // initialize each row to have 4 columns:
    for (int r = 0; r < NumRows; ++r)
    {
      this->Rows[r].Cols = new T[other.Rows[r].NumCols];  
      this->Rows[r].NumCols = other.Rows[r].NumCols;

      // initialize the elements to their default value:
      for (int c = 0; c < Rows[r].NumCols; ++c)//goes through each column in specific row r
      {
        Rows[r].Cols[c] = other.Rows[r].Cols[c];   //stores the values from the newly made matrix into the old
      }
    }  
  }

  
  int numrows() const
  {
    return NumRows;
  }
  
  //
  // numcols
  //
  // Returns the # of columns in row r.  The indices for these columns
  // are 0..numcols-1.  Note that the # of columns can be different 
  // row-by-row since "jagged" rows are supported --- matrices are not
  // necessarily rectangular.
  //
  int numcols(int r) const
  {
    if (r < 0 || r >= NumRows){
     throw invalid_argument("mymatrix::numcols: row");
     }
     
    return Rows[r].NumCols;//returns the Number of columns at row r
  }


  //
  // growcols
  //
  // Grows the # of columns in row r to at least C.  If row r contains 
  // fewer than C columns, then columns are added; the existing elements
  // are retained and new locations are initialized to the default value 
  // for T.  If row r has C or more columns, then all existing columns
  // are retained -- we never reduce the # of columns.
  //
  // Jagged rows are supported, i.e. different rows may have different
  // column capacities -- matrices are not necessarily rectangular.
  //
  void growcols(int r, int C)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::growcols: row");
    if (C < 1)
      throw invalid_argument("mymatrix::growcols: columns");
    if(Rows[r].NumCols< C){
       T* temp = new T[C];//creates a new pointer array with the size of C which is inputed by the user
       
       for(int i = 0; i <Rows[r].NumCols; ++i){
          temp[i] = Rows[r].Cols[i];//copys over every single value of the columns in the specific Row R

       }
       for(int i = Rows[r].NumCols; i<C;++i){
           temp[i] = T{}; // this sets the default constructor value of 0 to the newly added array indexes

       }

       Rows[r].Cols =temp; //setting the new values of columns to Cols at Row r
       Rows[r].NumCols= C;// the number of columns at Row R being set to C 
   
   }
   
  }


  //
  // grow
  //
  // Grows the size of the matrix so that it contains at least R rows,
  // and every row contains at least C columns.
  // 
  // If the matrix contains fewer than R rows, then rows are added
  // to the matrix; each new row will have C columns initialized to 
  // the default value of T.  If R <= numrows(), then all existing
  // rows are retained -- we never reduce the # of rows.
  //
  // If any row contains fewer than C columns, then columns are added
  // to increase the # of columns to C; existing values are retained
  // and additional columns are initialized to the default value of T.
  // If C <= numcols(r) for any row r, then all existing columns are
  // retained -- we never reduce the # of columns.
  // 
  void grow(int R, int C)
  {
    if (R < 1){
      throw invalid_argument("mymatrix::grow: # of rows");
    }
    if (C < 1){
      throw invalid_argument("mymatrix::grow: # of cols");
    }
    
    mymatrix<T> Temp(max(R, NumRows), C);//this initializes the size of the Temp matrix in order to 
                                        //keep the rows from shrinking by taking the max    
   
   if(R > NumRows){
        for(int k = 0; k< NumRows; k++){//goes through each row 
           
            if(Rows[k].NumCols > C){//compares to see if the number of colums at that specific row is bigger
                Temp.growcols(k,Rows[k].NumCols);//maintaininfg the size of the original function
            }
            else {
               Temp.growcols(k,C);//if the number input is larger than the number of existing columns youll grow it by C 
            }
        }
    }
    else{
        for(int i = 0; i < R; i++){//since R is greater than NumRows you go through each new Row
            
            if(Rows[i].NumCols < C){//compares the number of colums at row[i] to 
                Temp.growcols(i, C);//grows the columns to size C
            }
            else{
                for(int j = 0; j < NumRows; ++j){
                    Temp.growcols(j, Rows[j].NumCols);//mantains the original size of the number of columns for that row
                }
             }
          }
    }
    
      for(int i = 0; i < NumRows; i++){
          for(int k = 0; k < Rows[i].NumCols; k++){
              Temp.Rows[i].Cols[k] = Rows[i].Cols[k];//copying over all the value of each column of each row
          
           }
        }
   
    *this = Temp;//this points back to the original matrix

}

  //
  // size
  //
  // Returns the total # of elements in the matrix.
  //
  int size() const{
    //loops through each row and each rows number of columns and counts
  int count = 0;
  for(int i = 0; i< NumRows; ++i){
      for(int j = 0; j < Rows[i].NumCols; ++j){
          ++count;
      }
  }
    return count;
  }


  //
  // at
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M.at(r, c) = ...
  //    cout << M.at(r, c) << endl;
  //
  T& at(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::at: row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::at: col");

    //
    // TODO
    //

    return Rows[r].Cols[c];//returns the specific column value at that specific row
  }


  //
  // 
  //
  // Returns a reference to the element at location (r, c); this
  // allows you to access the element or change it:
  //
  //    M(r, c) = ...
  //    cout << M(r, c) << endl;
  //
  T& operator()(int r, int c)
  {
    if (r < 0 || r >= NumRows)
      throw invalid_argument("mymatrix::(): row");
    if (c < 0 || c >= Rows[r].NumCols)
      throw invalid_argument("mymatrix::(): col");

    return Rows[r].Cols[c];//returns the specific column value at that specific row
  }

  //
  // scalar multiplication
  //
  // Multiplies every element of this matrix by the given scalar value,
  // producing a new matrix that is returned.  "This" matrix is not
  // changed.
  //
  // Example:  M2 = M1 * 2;
  //
  mymatrix<T> operator*(T scalar)
  {
    mymatrix<T> result(NumRows,1);//sets the intial bounds of the result matrix
    
    for(int i = 0; i< NumRows; i++){
        result.growcols(i, Rows[i].NumCols);// grows the matrix to the size of the original matrix

      for(int j = 0; j < Rows[i].NumCols; j++){
          result.Rows[i].Cols[j] = Rows[i].Cols[j] * scalar;// sets the new values in a specific spot in the result matrix
      }
  }
  
    return result;
  }

  // matrix multiplication
  //
  // Performs matrix multiplication M1 * M2, where M1 is "this" matrix and
  // M2 is the "other" matrix.  This produces a new matrix, which is returned.
  // "This" matrix is not changed, and neither is the "other" matrix.
  //
  // Example:  M3 = M1 * M2;
  //
  // NOTE: M1 and M2 must be rectangular, if not an exception is thrown.  In
  // addition, the sizes of M1 and M2 must be compatible in the following sense:
  // M1 must be of size RxN and M2 must be of size NxC.  In this case, matrix
  // multiplication can be performed, and the resulting matrix is of size RxC.
  //
  //
  //
  
  mymatrix<T> operator*(const mymatrix<T>& other)
  {
    mymatrix<T> result(this->NumRows, other.Rows[0].NumCols);//initializes the result matrix rows becomes the original number of rows
                                                             // and for the columns to become the second matrix's number of columns in it's first row
                                                             
    for(int i = 0; i < NumRows; i++){//goes through each row
          
        if (Rows[i].NumCols != Rows[0].NumCols){// checking every rows number of columns and comparing it to 
              throw runtime_error("mymatrix::*: this not rectangular");//the first row to make sure no jagged matrix
        }
        if(Rows[i].NumCols != other.NumRows){//checks the number of columns at each row to see if 
              throw runtime_error("mymatrix::*: size mismatch");//it matches the number of rows in the second matrix
        }
        if(Rows[i].NumCols != other.Rows[0].NumCols){//checks the rumber of columns through each row to make sure 
              throw runtime_error("mymatrix::*: other not rectangular");//that the matrix is rectangular

        }
     }
     
    //
    // both matrices must be rectangular for this to work:
      for(int i = 0; i <NumRows;++i){//number of rows of the first matrix
         for(int j = 0; j< other.Rows[0].NumCols; ++j){//number of columns at row 0 in the second matrix
             for(int k = 0; k < other.NumRows; ++k){//number of columns of the second matrix 
             //the equation below multiplies a specific element from the first matrix
             //to the other matrix incrementing by 1 each time and then adds all the values 
             //and sets it to a specific location to the result matrix
                    result.Rows[i].Cols[j] += (Rows[i].Cols[k] * other.Rows[k].Cols[j]);
             
          }        
         }     
        }

    //
    // Okay, both matrices are rectangular.  Can we multiply?  Only
    // if M1 is R1xN and M2 is NxC2.  This yields a result that is
    // R1xC2.
    // 
    // Example: 3x4 * 4x2 => 3x2
    //

    //
    // TODO
    //
    //if ()//this matrix's # of columns != other matrix's # of rows)

    //
    // Okay, we can multiply:
    //

    //
    // TODO
    //

    return result;
  }


  //
  // _output
  //
  // Outputs the contents of the matrix; for debugging purposes.
  //
  void _output()
  {
    for (int r = 0; r < this->NumRows; ++r)
    {
      for (int c = 0; c < this->Rows[r].NumCols; ++c)
      {
        cout << this->Rows[r].Cols[c] << " ";
      }
      cout << endl;
    }
  }

};