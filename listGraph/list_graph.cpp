#include "list_graph.h"

vertex::vertex() {
    city = "";
    state = "";
    visited = false;
    std::cout << "Initialized empty vertex." << std::endl;
}

vertex::vertex(std::string c, std::string s) {
    city = c;
    state = s;
    visited = false;
    std::cout << "Initialized vertex with [" << c 
                << "] and [" << s << "]." << std::endl;
}

void vertex::print_graph() {
    std::cout << city << ", " << state << std::endl;
    visited = true;
    for (int i = 0; i < edge.size(); i++)
    {
        if (!edge[i].first->visited)
        {
            edge[i].first->print_graph();
        }
    }
    visited = false;
}

void vertex::add_edge(vertex& V1, vertex& V2, int weight) {
    adj temp;
    temp.first = &V1;
    temp.second = weight;
    edge.push_back(temp);
}

Graph::Graph() {
    numVertex = 0;
    maxVertex = vertices.max_size();
    numEdges = 0;
    std::cout << "Initialized empty Graph." << std::endl;
}

Graph::Graph(int size) {
    numVertex = 0;
    maxVertex = size;
    numEdges = 0;
    std::cout << "Initialized Graph of size [" << size 
                << "]." << std::endl;
}

std::ostream& operator<<(std::ostream& stream, const vertex& v) {
    stream << v.city << ", " << v.state;
    return stream;
}