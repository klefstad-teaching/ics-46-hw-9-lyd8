#include "dijkstra.h"

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    return vector<int>();
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    return vector<int>();
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v) {
        cout << vertex << " ";
    }
    cout << "\ntotal: " << total << endl;
}