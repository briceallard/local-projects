//****************************************************************************
// Program Name: Spanning Trees (Not Really)
// Files: graph.h, graph.cpp, distance.h, csv.h, main.cpp, 
//        filtered_cities.csv, and graphViz.dat

// Author: Brice Allard
// Email: briceallard@gmail.com
// Description:
//	- Using an input file with almost 19k cities, we create a weighted graph
//  - based on distances between each location. Ensuring each vertice is
//  - connected to another will open up shortest path and other
//  - algorithmic based operations for later projects.
//****************************************************************************

#include "csv.h"
#include "distance.h"
#include "graph.h"
#include <iomanip>
#include <algorithm>
#include <utility>
#include <queue>

typedef std::pair<double, int> p_dbint;

Graph loadGraph(std::string, std::string, std::string);  // Generates graph
int num_of_lines(std::string);                           // returns # lines in input file
int search(Graph&, std::string, std::string);            // find index of user defined search
bool isValidForEdge(Graph&, int, int, int);              // verify can add edge
void closestEdges(Graph&);                               // adds edges to closest distance
void randomEdges(Graph&, int);                           // adds edges in random

int main(int argc, char *argv[])
{
    int max_vertices = 0;
    int max_edges = 0;
    std::string searchType;
    std::string key;
    std::string filename = "filtered_cities.csv";

    if (argc < 2 || argc > 3) {
        std::cout << "Usage: ./graph search_type search_key" << std::endl;
        std::cout << " - search_type = the state you want to add\n"
                    << "   - enter all for all US states\n" 
                    << "   - enter state to search by state\n" 
                    << "   - enter county to search by county\n" 
                    << "   - enter zip to search by zip\n" 
                    << std::endl;
        std::cout << " - search_key = the term you want to add\n"
                    << "   - enter State or County\n" 
                    << std::endl;
        exit(0);
    } 
    else if (argc == 2) {
        searchType = argv[1];
    }
    else if(argc == 3) {
        searchType = argv[1];
        key = argv[2];
    }

    std::ofstream outfile;
    outfile.open("graphViz.dat");

    Graph G = loadGraph(filename, searchType, key);
    closestEdges(G);
    outfile << G.graphViz(false);
    finished(G);
    //randomEdges(G, 100);
    //G.printGraph();
    //G.printVids();
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
//          loadGraph
// Params:  string filename - name of the input file to open
//          string searchType - county or statewide search
//          string key - location to be searched for
// Returns: Graph - vList is created here
// Desc:    Generates the Graph from input file.
//////////////////////////////////////////////////////////////////////////////
Graph loadGraph(std::string filename, std::string searchType, std::string key) {
    Graph G;
    std::ifstream file(filename);

    int zip;
    double lat;
    double lon;
    std::string strZip;
    std::string strLat;
    std::string strLon;
    std::string city;
    std::string state;
    std::string county;
    int count = 0;

    // Read input file line by line, seperating by ','
    while(std::getline(file, strZip, ',')) {
        std::getline(file, strLat, ',');
        std::getline(file, strLon, ',');
        std::getline(file, city, ',');
        std::getline(file, state, ',');
        std::getline(file, county); 
    
        // Convert to appropriate types
        zip = std::stoi(strZip);
        lat = std::stod(strLat);
        lon = std::stod(strLon);

        //Determine search type and create Vertex
        if(searchType == "all" || searchType == "ALL") {
            G.addVertex(city, state, lat, lon);
            count++;
        } else if ((searchType == "COUNTY" || searchType == "county") && county == key) {
            G.addVertex(city, state, lat, lon);
            count++;
        } else if ((searchType == "STATE" || searchType == "state") && state == key) {
            G.addVertex(city, state, lat, lon);
            count++;
        } else if ((searchType == "ZIP" || searchType == "zip") && strZip == key) {
            G.addVertex(city, state, lat, lon);
            count++;
        }
    }
    // Output search results
    std::cout << "[" << searchType << "::" << key << "] found " 
                << count << " results." << std::endl;

    // Return Graph
    return G;
}

//////////////////////////////////////////////////////////////////////////////
//          num_of_lines
// Params:  string - name of input file
// Returns: int - number of lines
// Desc:    Returns number of lines found in the input file
//////////////////////////////////////////////////////////////////////////////
int num_of_lines(std::string filename) {
    int numLines = 0;
    std::string line;
    std::ifstream file(filename);

    while(std::getline(file, line))
        numLines++;

    return numLines;
}

//////////////////////////////////////////////////////////////////////////////
//          search
// Params:  Graph - list of Vertices to search
//          string city - city to search for
//          string state - state to search for
// Returns: int - index of the location found
// Desc:    Searched the graph vertices for a user defined location and
//          returns the index
//////////////////////////////////////////////////////////////////////////////
int search(Graph &G, std::string city, std::string state) {
    for (std::vector<int>::size_type i = 0; i != G.vList.size(); i++) {
        if (G.vList[i]->city == city && G.vList[i]->state == state) {
            std::cout << G.vList[i]->city << "::" << G.vList[i]->state 
                        << "::" << i << " Found!" << std::endl;
            return i;
        }
    }
    return -1;
}

//////////////////////////////////////////////////////////////////////////////
//          isValidForEdge
// Params:  Graph G - Graph of all vertices
//          int fromID - Location where edge begins
//          int toID - Location where edge ends
//          int edgePerV - how many edges are allowed per Vertex
// Returns: bool
// Desc:    Verifies all conditions are met before adding edge
//          Condition 1 - From location has less than max edges allowed
//          Condition 2 - To location has less than max edges allowed
//          Condition 3 - From location is not itself, meaning no edge to self
//////////////////////////////////////////////////////////////////////////////
bool isValidForEdge(Graph &G, int fromID, int toID, int edgePerV) {
    if(G.vList[fromID]->E.size() < edgePerV) {
        if(G.vList[toID]->E.size() < edgePerV) {
            if(fromID != toID) {
                return true;
            }
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////
//          closestEdges
// Params:  Graph G - Graph of ALL vertices from user search
// Returns: void
// Desc:    Finds closest vertex's to a central location then adds edges
//          between them with restrictions to how many edges per vertex
//          set by user.
//////////////////////////////////////////////////////////////////////////////
void closestEdges(Graph &G) {
    int edgePerV;           // Edges per Vertex
    int index;              // Starting location
    std::string keyCity;    // Search variable - City
    std::string keyState;   // Search variable - State
    double distance;        // Weight of edge
    double totDistance;     // Total distance between all edges
    latlon from;            // From location
    latlon to;              // To location

    // Get starting location from user
    while(1) {
        std::cout << "Enter Starting Location:\n(Ex. Wichita Falls,TX) ";
        std::getline(std::cin, keyCity, ',');
        std::getline(std::cin, keyState);

        index = search(G, keyCity, keyState);

        if(index == -1)
            std::cout << keyCity << ',' << keyState << " not found!" << std::endl;
        else if(index != -1)
            break;
    }

    // Get maximum number of edges allowed per Vertex from user
    while(1) {
        std::cout << "Edges per Vertex: ";
        std::cin >> edgePerV;

        if(std::cin.fail()) {   // Valid input checker
            std::cout << "Enter a proper integer!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            break;
    }

    // Storage Containers
    std::vector<p_dbint> closestV;  // Vector for ordered vertices
    std::queue<p_dbint> q;          // Q of pairs for algorithm

    // Cycle through all vertices
    for(int j = 0; j < G.vList.size(); j++) {
        // Get closest surrounding vertices
        for(int i = 0; i < G.vList.size(); i++) {
            from = G.vList[index]->location;
            to = G.vList[i]->location;
            distance = distanceEarth(from.lat, from.lon, to.lat, to.lon);
            closestV.push_back(std::make_pair(distance, i));
        }
        // Sort them from least to greatest
        std::sort(closestV.begin(), closestV.end());
        q.emplace(closestV[0]);

        // Add edge algorithm
        // if q is empty, no more edges to add
        while(!q.empty()) {
            int qCount = q.size() - 1;  // preventer for edgePerV

            // Update closest surrounding vertices
            for (int i = 0; i < G.vList.size(); i++) {
                from = G.vList[index]->location;
                to = G.vList[i]->location;
                distance = distanceEarth(from.lat, from.lon, to.lat, to.lon);
                closestV.push_back(std::make_pair(distance, i));
            }
            // Sort them from least to greatest
            std::sort(closestV.begin(), closestV.end());

            // loop through list to find closest (eligible) vertices
            for(int i = 1; i < closestV.size(); i++) {
                int fromID = index;
                int toID = G.vList[closestV[i].second]->ID;
                double weight = closestV[i].first;

                // Verify is valid before adding edge
                if(isValidForEdge(G, fromID, toID, edgePerV) && qCount < edgePerV) {
                    q.emplace(closestV[i]);
                    G.addEdge(fromID, toID, weight, false);
                    totDistance += weight;
                    qCount++;
                }
            }
            index = q.front().second;   // update new starting location
            q.pop();    // remove vertex where limit of edges was reached
        }
        closestV.clear();   // clear list to repeat
    }

    // output results
    std::cout << G.getNumEdges() << " edges were created traveling in total "
                << std::fixed << std::setprecision(4) << totDistance 
                << " miles." << std::endl;
}

//////////////////////////////////////////////////////////////////////////////
//          randomEdges
// Params:  Grapg G - list of all vertices
//          int numEdges - total number of edges allowed in graph
// Returns: none
// Desc:    Randomizes edges between as many vertices as possible with the
//          number of edges being passed in
//////////////////////////////////////////////////////////////////////////////
void randomEdges(Graph &G,int numEdges){
    int r1,r2;
    latlon from;
    latlon to;
    double d;
    for(int i=0;i<numEdges;i++){
        r1 = rand() % G.vList.size();
        r2 = rand() % G.vList.size();
        from = G.vList[r1]->location;
        to = G.vList[r2]->location;
        d = distanceEarth(from.lat,from.lon,to.lat,to.lon);
        G.addEdge(r1,r2,(int)d,true);
    }
}