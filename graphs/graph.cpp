#include "graph.h"

vertex::vertex() {
    city = "";
    state = "";
    visited = false;
}

vertex::vertex(std::string c, std::string s) {
    city = c;
    state = s;
    visited = false;
}

Graph::Graph() {
    numVertices = 0;
    maxVertices = vertices.max_size() - 1000;
    vertices.resize(0);
    edges.resize(maxVertices, std::vector<int>(maxVertices, 0));
    std::cout << "Graph created of size [" << maxVertices << "]." << std::endl;
}

Graph::Graph(int size) {
    numVertices = 0;
    maxVertices = size;
    vertices.resize(size);
    edges.resize(size, std::vector<int>(size, 0));
    std::cout << "Graph created of size [" << size << "]." << std::endl;
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        delete vertices[i];
    }
    std::cout << "All vertices (" << numVertices << ") have been deleted." << std::endl;
}

void Graph::addVertices(vertex* v) {
    vertices[numVertices] = v;
     for(int i = 0; i < maxVertices; i++) {
         edges[numVertices][i] = 0;
         edges[i][numVertices] = 0;
     }
     numVertices++;
     std::cout << "Vertex added. There are now " << numVertices << " vertices." << std::endl;
}

int Graph::get_index(vertex* v) {
    for (int i = 0; i < numVertices; i++) {
        if(vertices[i] == v)
            return i;
    }
    return -1;
}

void Graph::addEdge(int start, int end, int weight) {
    int row = get_index(vertices[start]);
    int col = get_index(vertices[end]);

    edges[row][col] = weight;
    edges[col][row] = weight;

    std::cout << "Edge added between [" << start << "] and [" << end 
                << "] with a weight of " << weight << "." << std::endl;
}

int Graph::get_weight(int start, int end) {
    int row = get_index(vertices[start]);
    int col = get_index(vertices[end]);

    return edges[row][col];
}
