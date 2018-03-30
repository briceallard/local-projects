#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>

int main () {
    std::ifstream infile;
    infile.open("uscities.dat");

    int size;
    std::string line;

    while(getline(infile, line)) ++size;

    std::cout << "Infile has [" << size << "] lines." << std::endl;

    Graph adjMatrix(50);
    vertex* root;
    vertex* pVertex;

    root = new vertex("Amarillo", "TX");
    adjMatrix.addVertices(root);
    pVertex = new vertex("Dallas", "TX");
    adjMatrix.addVertices(pVertex);

    adjMatrix.addEdge(0,1,15);

    return 0;
}