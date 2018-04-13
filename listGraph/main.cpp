#include "csv.h"
#include "distance.h"
#include "graph.h"
#include <algorithm>
#include <utility>
#include <queue>

typedef std::pair<double, int> p_dbint;

Graph loadGraph(std::string, std::string, std::string);
int num_of_lines(std::string);
int search(Graph&, std::string);
bool isValidForEdge(Graph&, int, int, int);
void closestEdges(Graph&);
void randomEdges(Graph&, int);

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
    //randomEdges(G, 100);
    G.printGraph();

    outfile << G.graphViz(false);
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
    std::cout << "[" << searchType << "::" << key << "] found " 
                << count << " results." << std::endl;

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

int search(Graph &G, std::string key) {
    for (std::vector<int>::size_type i = 0; i != G.vList.size(); i++)
    {
        if (G.vList[i]->city == key)
        {
            std::cout << G.vList[i]->city << "::" << G.vList[i]->state 
                        << "::" << i << " Found!" << std::endl;
            return i;
        }
    }
    return -1;
}

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

void closestEdges(Graph &G) {
    int edgePerV;
    int index;
    std::string key;
    double distance;
    double totDistance;
    latlon from;
    latlon to;

    while(1) {
        std::cout << "Center City (Case Sensitive): ";
        std::getline(std::cin, key);

        index = search(G, key);

        if(index == -1)
            std::cout << key << " not found!" << std::endl;
        else if(index != -1)
            break;
    }

    while(1) {
        std::cout << "Edges per Vertex: ";
        std::cin >> edgePerV;

        if(std::cin.fail()) {
            std::cout << "Enter a proper integer!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            break;
    }

    std::vector<vertex *> list = G.vList;
    std::vector<p_dbint> closestV;
    std::queue<p_dbint> q;

    for(int j = 0; j < G.vList.size(); j++) {
        // Get closest surrounding vertices
        for(int i = 0; i < G.vList.size(); i++) {
            from = G.vList[index]->location;
            to = G.vList[i]->location;
            distance = distanceEarth(from.lat, from.lon, to.lat, to.lon);
            closestV.push_back(std::make_pair(distance, i));
        }
        std::sort(closestV.begin(), closestV.end());
        q.emplace(closestV[0]);

        while(!q.empty()) {
            int qCount = q.size() - 1;
            index = q.front().second;

            for(int i = 1; i <= closestV.size(); i++) {
                // std::cout << "LOOP" << std::endl;
                int fromID = index;
                int toID = G.vList[closestV[i].second]->ID;
                double weight = closestV[i].first;

                if(isValidForEdge(G, fromID, toID, edgePerV) && qCount < edgePerV) {
                    q.emplace(closestV[i]);
                    G.addEdge(fromID, toID, weight, false);
                    totDistance += weight;
                    qCount++;
                }
            }
            q.pop();
        }
        closestV.clear();
    }

    std::cout << G.getNumEdges() << " edges were created traveling in total "
                << totDistance << " miles." << std::endl;
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