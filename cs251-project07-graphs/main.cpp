
/*main.cpp*/

//
// Hakem Habahbeh
// U. of Illinois, Chicago
// CS 251: Spring 2020
// // 
// Project #07: open street maps, graphs, and Dijkstra's alg
// This project focuses on accessing maps and vectors utilizing structs.
// There is a lot of organization that is used with this program 
// and the most important part was to understand what you were trying to access.
// Also to understand what you are using to search for that specific value.

// // 
// 
// 
// 
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:  
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include "graph.h"
#include <fstream>
#include <limits>
#include <queue>
#include <algorithm>
#include <set>
#include <stack>

// #include "tinyxml2.cpp"
#include "tinyxml2.h"
// #include "dist.cpp"

#include "dist.h"
#include "osm.h"
// #include "osm.cpp"

using namespace std;
using namespace tinyxml2;


class prioritize
{
   public:
      bool operator()(const pair<long long,double>& p1, const pair<long long,double>& p2) {
         
         if(p1.second == p2.second){// checks if the values of the pairs match
               
            return p1.first > p2.first;// if they do print map one's first then map two's first
         
         }
         else{
         
            return p1.second > p2.second;// if they dont match print map second first then map two's second
         
         }
      }
   
   
   
};


void _buildGraph(map<long long, Coordinates>&  Nodes, vector<FootwayInfo>& Footways, graph<long long, double>& G )
{
	for(auto q: Nodes ){//iterates through the number of nodes
		G.addVertex(q.first);//adds the first value in the map Nodes being the unique value
	}

	for(auto& c: Footways ){ // vector footways is used to help get the ID


		for(unsigned int i = 0; i < c.Nodes.size() - 1; i++){ //iterates through the # of maps 

			double lat1 = Nodes[c.Nodes[i]].Lat;//gets the lattitude within the Map Nodes at the specific index
			double lon1 = Nodes[c.Nodes[i]].Lon;//gets the lattitude within the Map Nodes at the specific index

			double lat2 = Nodes[c.Nodes[i+1]].Lat;//gets the lattitude within the Map Nodes at the specific index over one
			double lon2 = Nodes[c.Nodes[i+1]].Lon;//gets the lattitude within the Map Nodes at the specific index over one

			G.addEdge( c.Nodes[i], c.Nodes[i+1] , distBetween2Points(lat1,lon1,lat2,lon2));// sets the weight 
			G.addEdge( c.Nodes[i+1], c.Nodes[i] , distBetween2Points(lat1,lon1,lat2,lon2));// sets the inverse location's weight to the same weight

		}

	}

}



void Dijkstra(graph<long long,double>& G, long long& startV, map<long long , 
			  double>& distances, map<long long, double>& pred)
{
   
  double INF = numeric_limits<double>::max();// initializes infinity

   
   
  priority_queue<pair<long long, double>, vector<pair<long long, double>>, prioritize> PQ; // initializes the queue
  vector<long long>  visited;// a vector used to store all the visited nodes
  
  
  for(auto& c : G.getVertices() ){
	  distances[c] = INF;// sets the distances to infinity
	  
      pred[c] = -1.0;//sets the predecessor to -1.0
	  PQ.push(make_pair(c,INF));//stores into queue
	  
     }
  
  distances[startV] = 0.0;
  PQ.push(make_pair(startV, 0));// pushes a pair into the Queue to initialize the start
  
  
  
  while(!PQ.empty()){ // iterates through the nodes until queue is empty
     
     
     
     long long currentV = PQ.top().first; //  creates a temp variable to help the iteration through the queue
     PQ.pop();
     
     
     auto foundPair = find(visited.begin(), visited.end(), currentV); //searches the vector for the the currentV variable
     
     
     
     if(distances[currentV] == INF){
         break;
      }else if(foundPair != visited.end()){
         continue;
      }else{
         visited.push_back(currentV);   // keeps pushing the nodes until queue is empty
         
      }
     
     for(auto& A: G.neighbors(currentV)){//iterates through neighbors of the current vertex
        
        double edge = 0.0 ;
        G.getWeight(currentV, A, edge);// gets the weight of the edge
        double AD = 0.0;
        AD = distances[currentV] + edge; // adds weight to the current weight
        
        
        if(AD < distances[A]){
			distances[A] = AD;
			pred[A] = currentV;
            PQ.push(make_pair(A, AD));// pushs into queue
           
           
           }
        }
     }
  
	cout << endl;
	cout<< "Navigating with Dijkstra..."<< endl;

}




void printDijkstra(long long destID, map<long long , double>& pred, 
	map<long long, double>& distances){
	
	stack<long long> infoPrint; 
	long long curV= destID;
	double INF = numeric_limits<double>::max();

	if( distances[destID] == INF ){// checks if the distance is reachable by comparing to infinity
		cout<< "Sorry, destination unreachable"<< endl;
		return;
	}else{
		cout<< "Distance to dest: " << distances[destID] << " miles" << endl;// outputs the distance 
		
		while(curV != -1.0){     //iterates throught the predecessors and pushes them into a vector
	
			infoPrint.push(curV);// pushes into vector
			curV = pred[curV];
			
		}
		cout<< endl;
		cout<< "Path: ";
		while(!infoPrint.empty()){// iterates throught the entire stack in order to print out all the verticies visted
			
			cout<<infoPrint.top();//outputs the verticie
			infoPrint.pop();
			
			
			if(!infoPrint.empty()){//checks if the stack is empty to know when to stop outputting "->"
				cout<< "->";

			}else{
				cout<< endl;
			}
		}
	}
}










void _voidNum8( long long& startIndex,  map<long long, Coordinates>&  Nodes,
			   vector<FootwayInfo>& Footways, vector<BuildingInfo>& Buildings,
			   long long& destIndex,long long& startID, long long& destID ){
	
		
	double lat1, lat2, lon1, lon2, dist, lat3, lon3, destDist; //
	double INF = numeric_limits<double>::max();
	double tempINF = numeric_limits<double>::max();
	
	//gets coordinates for lat and long of the start vertex and destination vertex
	lat2 = Buildings[startIndex].Coords.Lat;
	lon2 = Buildings[startIndex].Coords.Lon;

	lat3 = Buildings[destIndex].Coords.Lat;
	lon3 = Buildings[destIndex].Coords.Lon;

	for(unsigned int i = 0; i < Footways.size(); i++){// iterates through the footway vector because 
		for(unsigned int j = 0; j < Footways[i].Nodes.size(); j++){
			
				// gets the coordinates and sets the lat and long
				lat1 = Nodes[Footways[i].Nodes[j]].Lat;
				lon1 = Nodes[Footways[i].Nodes[j]].Lon;
	
				dist = distBetween2Points(lat2,lon2,lat1,lon1);// calculates the distances
				destDist = distBetween2Points(lat1,lon1,lat3,lon3 );
		
			
			if(INF > dist){// checks if the start distance is less than infinity
			
				INF =dist;
				startID = Nodes[Footways[i].Nodes[j]].ID;// sets the start ID
				
			}
			if(tempINF >destDist){// checks if the end distance is less than infinity
				
				tempINF = destDist;
				destID = Nodes[Footways[i].Nodes[j]].ID;// sets the destination ID

			}	
		}
	}
	
	
	
	
	cout << endl;
	cout<< "Nearest start node: " << endl;
	cout << " " << startID << endl;// outputs the starting vertex
	cout << " (" << Nodes[startID].Lat << ", " <<Nodes[startID].Lon << ") " << endl;
	
	cout<< "Nearest destination node: " << endl;
	cout << " " << destID << endl;// outputs the destination vertex
	cout << " (" << Nodes[destID].Lat << ", " <<Nodes[destID].Lon << ") " << endl;
	
	

}



bool _boolLookup(string& startBuilding, string& destBuilding,
				 vector<BuildingInfo>& Buildings, long long& startIndex,
				 long long& destIndex, long long& startID, long long& destID)
{
	int countUno = 0, countDos = 0;
	double lat1, lon1, lat2, lon2;
	string fullname1, fullname2, abbrev1, abbrev2;
	
	for(unsigned int i = 0; i < Buildings.size(); i++){
		
		if(startBuilding == Buildings[i].Abbrev ){ //check if fullname
			
			
			fullname1 = Buildings[i].Fullname;// gets the full name
			abbrev1 = Buildings[i].Abbrev;// gets the abbreviation
			startIndex = i;// sets the start index
			startID = Buildings[i].Coords.ID;// sets the start ID
			//sets the coordinates for lat and long
			lat1 = Buildings[i].Coords.Lat;
			lon1 = Buildings[i].Coords.Lon;
			countUno++;
			break;
			
		}
		
		
		else if(Buildings[i].Fullname.find(startBuilding) != std::string::npos){ //checks for string within the string to help searching 
			
			fullname1 = Buildings[i].Fullname;// gets the fullname
			abbrev1 = Buildings[i].Abbrev;//gets the abbreviation
			startIndex = i;// sets the start index
			startID = Buildings[i].Coords.ID;// gets the start ID
			//sets the coordinates for lat and long
			lat1 = Buildings[i].Coords.Lat;
			lon1 = Buildings[i].Coords.Lon;
			
			countUno++;//count to know when to stop
			break;
			
		}
	}

	
	for(unsigned int j = 0; j < Buildings.size(); j++){
		if(destBuilding == Buildings[j].Abbrev ){ //check if fullname
			fullname2 = Buildings[j].Fullname;//gets the fullname
			abbrev2 = Buildings[j].Abbrev;//gets the abbreviation
			
			destIndex = j;// sets the destination index
			destID = Buildings[j].Coords.ID;
			//sets the coordinates for lat and long
			lat2 = Buildings[j].Coords.Lat;
			lon2 = Buildings[j].Coords.Lon;
			countDos++;
			break;
			
		}
		else if(Buildings[j].Fullname.find(destBuilding) != std::string::npos ){ //checks for string within the string to help searching 
			fullname2 = Buildings[j].Fullname;// gets the full name
			abbrev2 = Buildings[j].Abbrev; // gets the Abbreviation
			
			destIndex = j;// sets the destination index
			destID = Buildings[j].Coords.ID;// gets the destination ID
			//sets the coordinates for lat and long
			lat2 = Buildings[j].Coords.Lat;
			lon2 = Buildings[j].Coords.Lon;
			countDos++;// count to help know when to stop
			break;
			
		}
		
	}
	
	
	int total = countDos + countUno;// adds the counts




	if(total == 2 ){// if there exists a start and a destination then print
		
		
		cout<< "Starting point: "<< endl;
		cout<< " " <<fullname1<< endl;// prints the full name of the start
		cout << " "<<"(" << lat1 << ", " << lon1 << ") " << endl;// outputs the coordinates
	
		
		cout<< "Destination point: "<< endl;
		cout<<" "<<fullname2 << endl;// prints the full name of the destination
		cout << " " <<"(" << lat2 << ", " << lon2 << ") " << endl;// outputs the coordinates
		
		
	}else{
		
		if(countUno != 1){// if there is no start vertex 

			cout << "Start building not found" << endl;
			return false;
		}
		if(countDos != 1 ){// if there is no destination vertex 
			
			cout << "Destination building not found" << endl;
			return false;
		}
		
		
		return false;
	}

	return true;
}




//////////////////////////////////////////////////////////////////


// main


int main()
{
  map<long long, Coordinates>  Nodes;     // maps a Node ID to it's coordinates (lat, lon)
  vector<FootwayInfo>          Footways;  // info about each footway, in no particular order
  vector<BuildingInfo>         Buildings; // info about each building, in no particular order
  XMLDocument                  xmldoc;
  long long startIndex, destIndex, startID,destID;// initializes the indexes 
  graph<long long, double> G; //verticies, weight creates the graph
	
 map<long long, double> pred;// createss these maps to be used later in the dijkstra
 map<long long , double> distances;
	
  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

	

	
  string def_filename = "map.osm";
  string filename;

	
	
  cout << "Enter map filename> ";
  getline(cin, filename);

	
	
	
  if (filename == "")
  {
    filename = def_filename;
  }

  //
  // Load XML-based map file 
  //
  if (!LoadOpenStreetMap(filename, xmldoc))
  {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }
	
	
	
	
	
  //
  // Read the nodes, which are the various known positions on the map:
  //
  
  unsigned int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  unsigned int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  unsigned int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == Nodes.size());
  assert(footwayCount == Footways.size());
  assert(buildingCount == Buildings.size());

	
	  _buildGraph(Nodes, Footways, G );// calls the build graph funciton

	
	
	
  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;
  cout << "# of vertices: " << G.NumVertices() << endl;
  cout << "# of edges: " << G.NumEdges() << endl;
  
  
  cout << endl;

  //
  // Navigation from building to building
  //
  string startBuilding, destBuilding;

  cout << "Enter start (partial name or abbreviation), or #> ";
  getline(cin, startBuilding);

  while (startBuilding != "#")
  {
    cout << "Enter destination (partial name or abbreviation)> ";
    getline(cin, destBuilding);

	
    
    // TODO: lookup buildings, find nearest start and dest nodes,
    // run Dijkstra's alg, output distance and path to destination:
    //
	
	if(_boolLookup(startBuilding, destBuilding, Buildings, startIndex, destIndex, startID, destID)){//if the start and destinations exist
			_voidNum8(startIndex, Nodes, Footways, Buildings, destIndex, startID, destID);// calls the funciton inorder to search the footways

			Dijkstra(G, startID, distances, pred);// calls the dijkstra 
			printDijkstra(destID,pred, distances);// prints the dijkstra
	}
	
	  
	  
    // another navigation?
    //
    cout << endl;
    cout << "Enter start (partial name or abbreviation), or #> ";
    getline(cin, startBuilding);
  }

  //
  // done:
  //
  cout << "** Done **" << endl;

  return 0;
}





