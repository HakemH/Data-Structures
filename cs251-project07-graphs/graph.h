/*graph.h*/

//
// << Hakem habahbeh >>
//
//This project demonstrates on how to use maps in place of 
//matrix organization. It helps teach the basic concepts of 
//how a graph works and how to utilize it. 
//
//
//
//
// original author: Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>


using namespace std;


template<typename VertexT, typename WeightT>
class graph
{
private:

	int count= 0;//initializes count




  //
  // We are using adjacency matrix implementation, where rows
  // are the starting vertex and cols are the ending vertex.
  // We keep track of the vertices in the Vertices vector,
  // where the vertex's position in the vector --- 0, 1, 2, 
  // 3, 4, 5, ... --- denotes the row in the adjacency matrix
  // where their edges are found.  Example: if vertex "ORD" is
  // in position 1 of the Vertices vector, then row 1 of
  // AdjMatrix are the edges that start at "ORD" and lead to
  // other vertices.
  //


	bool _addedge(VertexT& from, VertexT& to, WeightT& weight){
	
	if(bigMap.count(from) != 0 && bigMap.count(to) != 0){//checks for values if they are already inserted
	
		if( bigMap.at(from).count(to) == 0  ){//checks for values within the map in the map
			bigMap[from][to] = weight;//sets a weight to an edge
			++count;//counts 

			return true;
		}else{
			bigMap[from][to] = weight;

			return true;
			
		}
	}
	return false;
	
	
	}


 
 map<VertexT, map<VertexT, WeightT> > bigMap;

  //
  // _LookupVertex
  //
  // Finds the vertex in the Vertices vector and returns it's 
  // index position if found, otherwise returns 0.
  //
  int _LookupVertex(VertexT v) const
  {

		if(bigMap.count(v) !=  0){			
			return 1;	//it exists
		}
		return 0;//it does not exist
  }


public:
 
  int NumVertices() const
  {
	return bigMap.size();// returns the size of the map aka the # of verticies
	
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const
  {
    return count;// returns the number of edges
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v)
  {
	if(_LookupVertex(v) != 0){// looks up the  the vertex v
		return false;// if v already exists return false
	
	}else{
		bigMap[v] = map<VertexT, WeightT>();//since v does not exist it inserts the vertex into the map

		return true;
	}
  }





  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight)
  {

	return _addedge( from,  to,  weight);//created a helper function to make more readable
   
  }




  //
  // getWeight
  //
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const
  {
  //this if statement checks that there is data stored in the from and to vertices
  //checks if there is a value from the "from" vertice to the "to" aka checks for weight
		if(bigMap.count(from) != 0 && bigMap.count(to) != 0 && bigMap.at(from).count(to) !=0 ){
			weight = bigMap.at(from).at(to);//sets the edge to a weight
			return true; 
		}
		else{
			return false;
		}
  }



  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const
  {
    set<VertexT>  S;
	if(_LookupVertex(v)){//looks up vertex v to see if it exists within the map
		for(auto mapIter: bigMap.at(v)){//iterates through the vertex given's map

			S.insert(mapIter.first);//inserts the first value of the map into the set to get rid of duplicates

		}
	}
	return S; // returns the set 
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const
  {
  vector<VertexT> vectVert;
	  for(auto& iter: bigMap ){//iterates through the bigMap 

		  vectVert.push_back(iter.first);// pushes the values of iter which is the first of the map

	  }

  return vectVert;
  }







  //
  // dump
  // 
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const
  {
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
	
	
	for(auto& firstMap: bigMap){//iterates through the bigMap
		output << " " << firstMap.first << endl;
	}
	
	
	

    output << endl;
    output << "**Edges:" << endl;
	
	for(auto& firstMap: bigMap){//iterates throughh the bigMap
		for(auto& secondMap: firstMap.second){//iterates through the second map in the bigMap
			output << "(" << firstMap.first << "," << secondMap.first << "," << secondMap.second << ") " << endl;
		}
	
	
	}
	
	

    output << "**************************************************" << endl;
  }

};