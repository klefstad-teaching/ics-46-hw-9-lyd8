#include "dijkstras.h"
#include <algorithm>

using namespace std;

struct Node {
    int vertex;
    int weight;
    Node(int v, int w) : vertex(v), weight(w) {}
    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);
    previous.assign(G.numVertices, -1);

    distances[source] = 0;

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;
        if (visited[u])
            continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distances[v]));
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    if (distances[destination] == INF) {
        return path;
    }

    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    for (int vertex : v) {
        cout << vertex << " ";
    }
    cout << "\nTotal cost is " << total << "\n";
}