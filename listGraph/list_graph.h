#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

class vertex {
public:
    std::string city;
    std::string state;
    bool visited;

    // Constructors
    vertex();                           // Initialize with blank values
    vertex(std::string, std::string);   // Initialize passed in values
    
    void print_graph();
    void add_edge(vertex&, vertex&, int);

protected:
    typedef std::pair<vertex*, int> adj;
    std::vector<adj> edge;
};

class Graph : public vertex {
public:
    // Constructors
    Graph();    //initialize with max size
    Graph(int); //initialize with given size

    friend std::ostream& operator<<(std::ostream&, const vertex&);
private:
    std::vector<vertex> vertices;
    int numVertex;
    int maxVertex;
    int numEdges;
};