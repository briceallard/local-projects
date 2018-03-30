#include "list_graph.h"

int main () {
    vertex V1("Dallas", "TX");
    vertex V2("Austin", "TX");
    V1.add_edge(V1, V2, 36);
    V2.add_edge(V2, V1, 42);
    V1.print_graph();
}