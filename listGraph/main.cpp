#include "csv.h"
#include "distance.h"
#include "graph.h"

void randomEdges(Graph&, int);
Graph loadGraphCSV(std::string,int);

// Test Driver
int main(int argc, char **argv)
{
    int max_vertices = 0;
    int max_edges = 0;

    if(argc > 2){
        max_vertices = std::stoi(argv[1]);
        max_edges = std::stoi(argv[2]);
    }else{
        std::cout<<"Usage: ./graph max_vertices max_edges"<<std::endl;
        exit(0);
    }

    Graph G = loadGraphCSV("cities.csv", max_vertices);

    std::cout << "Graph created" << std::endl;
    
    randomEdges(G,max_edges);

    //G.printGraph();

    std::cout << G.graphViz(false);

    //G.printVids();

    int *size = G.graphSize();

    std::cout << "V= " << size[0] << " E= " << size[1] << std::endl;

    // for(int i=0;i<G.vertexList.size();i++){
    //     cout<<(*G.vertexList[i])<<endl;
    // }
    return 0;
}

void randomEdges(Graph &g,int numEdges){
    int r1,r2;
    latlon from;
    latlon to;
    double d;
    for(int i=0;i<numEdges;i++){
        r1 = rand() % g.vList.size();
        r2 = rand() % g.vList.size();
        from = g.vList[r1]->location;
        to = g.vList[r2]->location;
        d = distanceEarth(from.lat,from.lon,to.lat,to.lon);
        g.addEdge(r1,r2,(int)d,true);
    }
}

/**
 * loadGraphCSV - loads a graph with the given csv
 * Params:
 *     string filename  - filename to open
 * Returns 
 *     graph
 */
Graph loadGraphCSV(std::string filename,int max=0)
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