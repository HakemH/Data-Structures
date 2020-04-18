#include <iostream>
#include <string>
#include "mymatrix.h"

using namespace std;

int main()
{
    cout<< "Matrix 1"<< endl;
    mymatrix<int> M1;
        M1(0,0) = 31; M1(1,0) = 91;
        M1(0,1) = 21; M1(1,1) = 84;
        M1(0,2) = 31; M1(1,2) = 75;
        M1(0,3) = 41; M1(1,3) = 67; 
        M1(2,0) = 71; M1(3,0) = 98;
        M1(2,1) = 11; M1(3,1) = 48;
        M1(2,2) = 45; M1(3,2) = 87;
        M1(2,3) = 74; M1(3,3) = 64; 
        M1._output();
        cout<< endl<< endl;
    
    cout<< "Matrix 2"<< endl;
    mymatrix<int> M2(4, 4);
        M2(0,0) = 1; M2(1,0) = 16;
        M2(0,1) = 2; M2(1,1) = 15;
        M2(0,2) = 3; M2(1,2) = 14;
        M2(0,3) = 4; M2(1,3) = 13; 
        M2(2,0) = 5; M2(3,0) = 12;
        M2(2,1) = 6; M2(3,1) = 11;
        M2(2,2) = 7; M2(3,2) = 10;
        M2(2,3) = 8; M2(3,3) = 9; 
        M2._output();
        cout << endl<< endl;

  
    cout<< "Matrix 3"<< endl;
    mymatrix<int> M3(4, 4);
        M3(0,0) = 1; M3(1,0) = 1;
        M3(0,1) = 2; M3(1,1) = 2;
        M3(0,2) = 3; M3(1,2) = 3;
        M3(0,3) = 1; M3(1,3) = 1; 
        M3(2,0) = 2; M3(3,0) = 2;
        M3(2,1) = 3; M3(3,1) = 3;
        M3(2,2) = 1; M3(3,2) = 1;
        M3(2,3) = 2; M3(3,3) = 2; 
        M3._output();
        cout << endl<< endl;
    
    
    cout<< "Matrix 4"<< endl;
    mymatrix<int> M4(4, 4);
        M4(0,0) = 10; M4(1,0) = 10;
        M4(0,1) = 20; M4(1,1) = 20;
        M4(0,2) = 30; M4(1,2) = 30;
        M4(0,3) = 40; M4(1,3) = 40; 
        M4(2,0) = 50; M4(3,0) = 50;
        M4(2,1) = 60; M4(3,1) = 60;
        M4(2,2) = 70; M4(3,2) = 70;
        M4(2,3) = 80; M4(3,3) = 80; 
        M4._output();
        cout << endl<< endl;
    
    cout<< "Matrix 6"<< endl;
    mymatrix<int> M6(4, 4);
        M6(0,0) = 1; M6(1,0) = 1;
        M6(0,1) = 2; M6(1,1) = 2;
        M6(0,2) = 3; M6(1,2) = 3;
     
        M6(2,0) = 5; M6(3,0) = 5;
        M6(2,1) = 6; M6(3,1) = 6;
        M6(2,2) = 7; M6(3,2) = 7;

        M6._output();
        cout << endl<< endl;

    
        cout<< endl << "Parameterized Constructor Test 3x5" << endl;
        mymatrix<int> MPara(3, 5);
        MPara._output();
        cout << endl<< endl; 

    
        cout<< "Grow Function Test " << endl;
        cout<< "Before Grow Test " <<endl;
        cout<< "# of rows before growing " << M2.numrows() << endl;
        cout<< "Size before " <<M2.size() << endl;
        M2._output();
        M2.grow(6,7);
        cout<< endl << "After grow test "<< endl;
        cout<< "number of rows after growing " << M2.numrows() << endl;
        cout<< "Size after " <<M2.size() << endl;
        M2._output();
        cout<< endl<< endl; 
        
    
        cout<< "Grow Columns Function Test " << endl;
        cout<< "Before Grow Columns Test " <<endl;
        cout << "# of columns in row 3 before growing " << M1.numcols(3)<< endl;
        cout<< "# of rows before growing " << M1.numrows() << endl;
        cout<< "Size before " <<M1.size() << endl;
        M1._output();
        M1.growcols(3,7);
        cout<< endl << "After grow test "<< endl;
        cout << "# of columns in row 3 after growing " << M1.numcols(3)<< endl;
        cout<< "Size after " << M1.size() << endl;
        M1._output();
        cout<< endl<< endl;
    

       cout<< "Scalar multiplication test"<< endl;
       cout<< "Before scaling by 3 " <<endl;
       M3._output();
       M3 = M3 *3; 
       cout<< endl << "after scaling by 3 " <<endl;
       M3._output();

    
      cout<< endl << "Copy constructer test copying matrix 3"<< endl;
      mymatrix<int> M5(M3);
      M5._output();
      cout<< endl<< endl;
    
    
      cout<< "Matrix multiplication test Matrix 4 X Matrix 6"<< endl;
        mymatrix<int> M7;
        M7 = M6 * M4;
        M7._output();
        
    
}
