#include <iostream>
#include <vector>
#include <string>

#define my2dVect std::vector< std::vector<int> >

struct vertex {
    std::string city;
    std::string state;
    bool visited;

    vertex();
    vertex(std::string, std::string);
};

class Graph{
public:
    Graph();
    Graph(int);
    ~Graph();

    void addVertices(vertex*);
    int get_index(vertex*);
    void addEdge(int, int, int);
    int get_weight(int, int);

protected:
    my2dVect edges;
    std::vector<vertex*> vertices;
    vertex* root;
    vertex* pVert;
    int numVertices;
    int maxVertices;
};