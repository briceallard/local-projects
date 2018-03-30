//****************************************************************************
// Program Name: Djiktra's Path Finder
// Files: graph.cpp, graph.h, BSTree.cpp, uscities.dat
//
// Author: Brice Allard
// Email: briceallard@gmail.com
// Description:
// 	Part 1:
//	- Creates a variety of different types of graphs (adjacent matrix or list)
//  - and reads information from the infile (initially setup to read city and
//  - state) which will then load into the undirected weighted graph.
//  Part 2:
//  - Takes the graph generated from part 1 and applies Djisktra's Path Finding
//  - algorithm to find the shortest path between two given vertices.
//****************************************************************************

#include "graph.h"
#include <iostream>
#include <fstream>
#include <string>

int get_size(std::ifstream&);
bool load_graph(std::ifstream&, Graph&);

int main () {
    std::ifstream infile;
    infile.open("uscities.dat");

    int size = get_size(infile);

    Graph adjMatrix(size);

    load_graph(infile, adjMatrix);

    vertex* root;
    vertex* pVertex;

    root = new vertex("Amarillo", "TX");
    adjMatrix.addVertices(root);
    pVertex = new vertex("Dallas", "TX");
    adjMatrix.addVertices(pVertex);

    adjMatrix.addEdge(0,1,15);

    infile.close();
    return 0;
}

//************************************************************************
// Function Name:	get_size
// Parameter:		none
// Returns:			int number_of_lines
// Description:
//		Reads line by line from fistream and increments int num_of_lines
//      then returns the number.
//************************************************************************
int get_size(std::ifstream& infile) {

    int num_of_lines = 0;
    std::string line;

    while(std::getline(infile, line)) ++num_of_lines;

    return num_of_lines;
}

bool load_graph(std::ifstream&, Graph& adjMatrix) {
    std::cout << "Function (load_graph) called." << std::endl;
    return true;
}