







// // /*test01.cpp*/

// //
// // Unit tests for threaded binary search tree
// //

// #include <iostream>
// #include <vector>

// #include "bstt.h"

// #include "catch.hpp"

// using namespace std;


// TEST_CASE("(1) empty tree") 
// {
//     bstt<int, int>  tree;
// 	tree.insert(200,33);
// 	REQUIRE(tree.size()==1);
// 	tree.insert(100, 13);
// 	REQUIRE(tree.size()==2);
// 	tree.insert(150,15);
//  	REQUIRE(tree.size()==3);
	
// 		tree.dump(cout);

	
// 	int check; 
	
// 	REQUIRE(tree.search(200,check));
// 	REQUIRE(check == 33);
// 	REQUIRE(tree.search(100,check));
//  	REQUIRE(check == 13);
//     REQUIRE(tree.search(150,check));
// 	REQUIRE(check == 15);
// 	int key = 125;
// 	tree.begin();
// 	while (tree.next(key)){
// 		cout << key << ' '<<endl;
		
// 	}
//   	bstt<int, int>  tree2;
	
//   	tree2=tree;
	
//   	REQUIRE(tree2.size()==3);
//  	REQUIRE(tree.size()==3);
	
// 	REQUIRE(tree[100] == 13);
// 	REQUIRE(tree[150] == 15);

// 	REQUIRE(tree[200] == 33);
// 	REQUIRE(tree(100) == 150);
// 	bstt<int, int>  tree1(tree);
// 	REQUIRE(tree1.size() == 3);
	
// // 	tree.begin();
	
// }
// /*test01.cpp*/

// //
// // Unit tests for threaded binary search tree
// //
// //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// //carlos



// // #include <iostream>
// // #include <vector>

// // #include "bstt.h"

// // #include "catch.hpp"

// // using namespace std;


// // TEST_CASE("(1) empty tree") 
// // {
// //     bstt<int, int>  tree1;

// //     REQUIRE(tree1.size() == 0);
// // 	tree1.insert(30, 1);
// // 	tree1.insert(15, 2);
// // 	tree1.insert(25, 3);
// // 	tree1.insert(50, 4);
// // 	tree1.insert(8, 5);
// // 	tree1.insert(15, 6);
	
// // 	int x;
// // 	tree1.dump(cout);
// // 	tree1.begin();
// // 	while (tree1.next(x)) {
// // 		cout<< x << ' ';
// // 	}
// // 	cout << endl;
	
// // 	REQUIRE(tree1.size() == 5);
// // 	REQUIRE(tree1.search(30, x));
// // 	REQUIRE(x == 1);
// // 	REQUIRE(tree1.search(15, x));
// // 	REQUIRE(x == 2);
// // 	REQUIRE(!tree1.search(23, x));
	
// // 	REQUIRE(tree1[8] == 5);
// // 	REQUIRE(tree1(15) == 25);
// // 	REQUIRE(tree1(50) == 0);
// // 	REQUIRE(tree1(8) == 15);
	
// // 	bstt<int, int> tree2 = tree1;
// // 	tree1.clear();
// // 	tree2.dump(cout);
// // 	tree2.begin();
// // 	while (tree2.next(x)) {
// // 		cout<< x << ' ';
// // 	}
// // 	cout << endl;
// // 	REQUIRE(tree2[8] == 5);
// // 	REQUIRE(tree2(15) == 25);
// // 	REQUIRE(tree2(50) == 0);
// // 	REQUIRE(tree2(8) == 15);
	
	
	
// // }


// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// /*test16.cpp*/


// // Unit tests for threaded binary search tree


// // #include <iostream>
// // #include "bstt.h"
// // #include "catch.hpp"

// // using namespace std;

// // TEST_CASE("(16) test begin & next ")
// // {

// //     bstt<int,int> bstt1;

// //     int value = 0;

// //     REQUIRE(bstt1.size() == 0);

// //     bstt1.insert(30,1);
// //     REQUIRE(bstt1.size() == 1);

// //     REQUIRE(bstt1.search(30,value));
// //     REQUIRE(!bstt1.search(5,value));

// //     REQUIRE(value == 1);

// //     bstt1.insert(15,2);
// //     REQUIRE(bstt1.size() == 2);

// //     REQUIRE(bstt1.search(15,value));
// //     REQUIRE(value == 2);

// //     bstt1.insert(8,3);
// //     REQUIRE(bstt1.size() == 3);

// //     REQUIRE(bstt1.search(8,value));
// //     REQUIRE(value == 3);

// //     bstt1.insert(25,6);
// //     REQUIRE(bstt1.size() == 4);

// //     REQUIRE(bstt1.search(25,value));
// //     REQUIRE(value == 6);

// //     bstt1.insert(20,4);
// //     REQUIRE(bstt1.size() == 5);

// //     REQUIRE(bstt1.search(20,value));
// //     REQUIRE(value == 4);

// //     bstt1.insert(28,5);
// //     REQUIRE(bstt1.size() == 6);

// //     REQUIRE(bstt1.search(28,value));
// //     REQUIRE(value == 5);

// //     bstt1.insert(50,6);
// //     REQUIRE(bstt1.size() == 7);

// //     REQUIRE(bstt1.search(50,value));
// //     REQUIRE(value == 6);

// //     bstt1.insert(70,6);
// //     REQUIRE(bstt1.size() == 8);

// //     REQUIRE(bstt1.search(70,value));
// //     REQUIRE(value == 6);

// //     bstt1.insert(60,7);
// //     REQUIRE(bstt1.size() == 9);

// //     REQUIRE(bstt1.search(60,value));
// //     REQUIRE(value == 7);

// //     int key;

// // //     bstt1.begin();

// // //     while (bstt1.next(key)) {
// // //         cout << key << " ";
// // //     }

// //     cout << endl;

// //     //bstt1.begin();
// //     bstt1.begin();

// // //    bstt1.insert(90,7);
// // //    REQUIRE(bstt1.size() == 10);
// // //
// // //    REQUIRE(bstt1.search(90,value));
// // //    REQUIRE(value == 7);
// // //
// // //    bstt1.insert(35,7);
// // //    REQUIRE(bstt1.size() == 11);
// // //
// // //    REQUIRE(bstt1.search(35,value));
// // //    REQUIRE(value == 7);
// // //
// // //    bstt1.insert(43,7);
// // //    REQUIRE(bstt1.size() == 12);
// // //
// // //    REQUIRE(bstt1.search(43,value));
// // //    REQUIRE(value == 7);
// // 	int count;

// //     while (bstt1.next(key)) {
// //         cout << key << " ";
// // 		++count;
// // 		if(count == 5){
// // 			break;
// // 		}
// //     }

// //     cout << endl;

// //     bstt1.dump(cout);
// // }