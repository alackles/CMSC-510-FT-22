#include <vector>
#include <list>
#include <string>
#include <iostream>
// Create Vertex class
//      node, color, distance, parent node
class Vertex {
    public:
        int node; 
        std::string color = "white";
        int dist;
        int prev;    
};

// Create Graph class with:
//      addEdge
//      BFS
class Graph {
    int size;
    std::vector<std::list<int>> adj;

    public:
        std::vector<Vertex> V;
        Graph(int size);
        void addEdge(int src, int dest);
        void BFS(int s);
};

Graph::Graph(int size) {
    adj.resize(size);
    V.resize(size);
}

void Graph::addEdge(int src, int dest) {
    adj[src].push_back(dest);
}

void Graph::BFS(int s) {
    V[s].color = "grey";
    V[s].dist = 0;

    std::list<int> queue;
    queue.push_back(s);

    while (!(queue.empty())) {
        int u = queue.front();
        queue.pop_front();
        std::cout << u << "->";
        // std::iterator<int> it
        // for (it = adj[u].begin(); it != adj[u].end(); ++it) {
        //     i = *it
        //}
        for (auto i : adj[u]) {
            if (V[i].color == "white") {
                V[i].color = "grey";
                V[i].dist = V[u].dist + 1;
                V[i].prev = u;
                queue.push_back(i);
            }
        V[u].color = "black";
        }
    }
    std::cout << "END" << std::endl;
}

// define addEdge
// define BFS

// main function: create graph & run BFS

int main() {
    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(2,4);
    g.addEdge(3,1);
    g.BFS(0);
    std::cout << g.V[4].prev << std::endl;
}