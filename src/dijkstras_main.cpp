#include "dijkstras.h"
#include <iostream>
#include <string>

using namespace std;

// g++ dijkstras.cpp dijkstras_main.cpp 
// g++ ladder.cpp ladder_main.cpp

int main() {
    string filename = "small.txt";
    Graph G;
    try {
        file_to_graph(filename, G);
    } catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }
        
    for (int i = 0; i < G.numVertices; i++) {
        cout << "Vertex " << i << " edges: ";
        for (const Edge &e : G[i]) {
            cout << e << " ";
        }
        cout << "\n";
    }
    
    return 0;
}