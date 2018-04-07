#include "csv.h"
#include "distance.h"
#include "graph.h"

typedef std::map<std::string, int> StateAbb;

StateAbb fillMap(std::string);
std::string get_user_input(int);
int num_of_lines(std::string);
void randomEdges(Graph&, int);
Graph loadGraphCSV(std::string, int);
Graph loadGraphCSV(std::string, std::string, int);

// Test Driver
int main(int argc, char **argv)
{
    int max_vertices = 0;
    int max_edges = 0;
    std::string search;
    std::string filename = "filtered_cities.csv";

    if(argc > 1){
        //max_vertices = std::stoi(argv[1]);
        //max_edges = std::stoi(argv[2]);
        search = argv[1];
    }else{
        std::cout << "Usage: ./graph search_state" << std::endl;
        std::cout << " - search_state = the state you want to add\n"
                    << "   - enter ALL for all US states or abbreviation\n" 
                    << std::endl;
        exit(0);
    }

    StateAbb stmap = fillMap(filename);
    StateAbb::iterator mit = stmap.begin();

    if(search == "all" || search == "ALL") {
        max_vertices = num_of_lines(filename);
        Graph G = loadGraphCSV(filename, max_vertices);
        std::cout << "[" << max_vertices << "] vertices loaded into Graph" << std::endl;
    }
    else {
        while(mit != stmap.end()) {
            if(mit->first == search) {
                std::cout << mit->first << "::" << mit->second << std::endl;
                max_vertices = mit->second;
            }
            mit++;
        }
        Graph G = loadGraphCSV(filename, search);
    }
    
    //Graph G = loadGraphCSV("filtered_cities.csv", search, max_vertices);
    //randomEdges(G,max_edges);
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

int num_of_lines(std::string filename) {
    int numLines = 0;
    std::string line;
    std::ifstream file(filename);

    while(std::getline(file, line))
        numLines++;

    return numLines;
}
StateAbb fillMap(std::string filename) {
    StateAbb stMap;
    std::ifstream file(filename);
    std::string zip;
    std::string lat;
    std::string lon;
    std::string city;
    std::string state;
    std::string county;

    while(std::getline(file, zip, ',')) {
        std::getline(file, lat, ',');
        std::getline(file, lon, ',');
        std::getline(file, city, ',');
        std::getline(file, state, ',');
        std::getline(file, county);

        if(stMap.find(state) != stMap.end())
            stMap[state]++;
        else
            stMap.insert(StateAbb::value_type(state, 1));
    }

    return stMap;
}

std::string get_user_input(int max) {
    beginning:
    int selection = 0;
    std::string user_instructions;

    std::cout << "Would you like to add all [" << max << "] Vertices or a specific state?"
            << std::endl << " 1. All Vertices\n 2. Add by State\n (1-2): ";
    std::cin >> selection;
    
    switch(selection) {
        case 1:
            std::cout << "All Vertices from file will be added" <<std::endl;
            return user_instructions = "all";
        case 2:
            std::cout << "Which state would you like to add?\nEx. 'TX' or 'NC' w/o the ' '" << std::endl;
            std::cin.ignore();
            std::getline (std::cin, user_instructions);
            return user_instructions;
    }    
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

Graph loadGraphCSV(std::string filename, std::string, int max = 0) {

}