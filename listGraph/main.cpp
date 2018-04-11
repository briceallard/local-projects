#include "csv.h"
#include "distance.h"
#include "graph.h"
#include <algorithm>

int num_of_lines(std::string);
void closestEdges(Graph&);
void randomEdges(Graph&, int);
Graph loadGraph(std::string, std::string, std::string);
Graph loadGraphCSV(std::string, int);
Graph loadGraphCSV(std::string, std::string, int);

// Test Driver
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
                    << "   - enter State, County, or ZIP\n" 
                    << std::endl;
        exit(0);
    } else if (argc == 2) {
        searchType = argv[1];
    }
    else if(argc == 3){
        searchType = argv[1];
        key = argv[2];
    }

    Graph G = loadGraph(filename, searchType, key);
    closestEdges(G);
    //randomEdges(G, 100);
    //G.printGraph();
    //std::cout << G.graphViz(false);
    //G.printVids();

    //int *size = G.graphSize();

    //std::cout << "V= " << size[0] << " E= " << size[1] << std::endl;

    // for(int i=0;i<G.vertexList.size();i++){
    //     cout<<(*G.vertexList[i])<<endl;
    // }
    return 0;
}

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

    while(std::getline(file, strZip, ',')) {
        std::getline(file, strLat, ',');
        std::getline(file, strLon, ',');
        std::getline(file, city, ',');
        std::getline(file, state, ',');
        std::getline(file, county); 
    
        zip = std::stoi(strZip);
        lat = std::stod(strLat);
        lon = std::stod(strLon);

        if(searchType == "all" || searchType == "ALL") {
            G.addVertex(city, state, lat, lon);
            std::cout << searchType << "::[" << count << "]::" << key << std::endl;
            count++;
        } else if ((searchType == "COUNTY" || searchType == "county") && county == key) {
            G.addVertex(city, state, lat, lon);
            std::cout << searchType << "::[" << count << "]::" << key << std::endl;
            count++;
        } else if ((searchType == "STATE" || searchType == "state") && state == key) {
            G.addVertex(city, state, lat, lon);
            std::cout << searchType << "::[" << count << "]::" << key << std::endl;
            count++;
        } else if ((searchType == "ZIP" || searchType == "zip") && strZip == key) {
            G.addVertex(city, state, lat, lon);
            std::cout << searchType << "::[" << count << "]::" << key << std::endl;
            count++;
        }
    }
    return G;
}

int num_of_lines(std::string filename) {
    int numLines = 0;
    std::string line;
    std::ifstream file(filename);

    while(std::getline(file, line))
        numLines++;

    return numLines;
}

void closestEdges(Graph &G) {
    int edgePerV;
    std::string start;
    double distance;
    latlon from;
    latlon to;

    std::cout << "Center City (Case Sensitive): ";
    std::cin.ignore();
    std::getline(std::cin, start);

    // auto it = std::find(G.vList.begin(), G.vList.end(), start);
    // if(it == G.vList.end()) {
    //     std::cout << "Enter a city name that is located in the graph ensuring case sensitive" << std::endl;
    //     goto beginning;
    // }
    // else {
    //     auto startIndex = std::distance(G.vList.begin(), it);
    //     std::cout << "CENTER CITY::" << G.vList[startIndex]->city << std::endl;
    // }


    std::cout << "Edges per Vertex: ";
    std::cin >> edgePerV;

    if(std::cin.fail()) {
        std::cout << "Enter a proper integer!" << std::endl;
        exit(0);
    }
    else {
        std::cout << "Digit entered!" << std::endl;
    }
}

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

/**
 * loadGraphCSV - loads a graph with the given csv
 * Params:
 *     string filename  - filename to open
 * Returns 
 *     graph
 */
Graph loadGraphCSV(std::string filename, int max = 0)
{
    srand(984325);
    int zip;
    double lat;
    double lon;
    std::string city;
    std::string state;
    std::string county;

    strint cityCheck;

    int i=0;

    Graph G;

    std::ifstream file(filename);

    for (CSVIterator loop(file); loop != CSVIterator(); ++loop)
    {
        zip = std::stoi((*loop)[0]);
        if ((*loop)[1].length() > 0)
        {
            lat = std::stod((*loop)[1]);
        }
        else
        {
            lat = 0.0;
        }

        if ((*loop)[2].length() > 0)
        {
            lon = std::stod((*loop)[2]);
        }
        else
        {
            lon = 0.0;
        }

        city = (*loop)[3];
        state = (*loop)[4];
        county = (*loop)[5];

        
        if (cityCheck.find(city) == cityCheck.end())
        {   
            // Add the city as a key to the map.
            cityCheck[city] = 0;

            if(state != "PR"){
                G.addVertex(city, state, lat, lon);
                i++;
            }
        }

        if(i > max && max != 0){
            return G;
        }
        
    }

    return G;
}