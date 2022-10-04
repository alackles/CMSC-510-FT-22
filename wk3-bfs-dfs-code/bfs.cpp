#include <vector>
#include <list>
#include <string>
#include <iostream>
// Create Vertex class
//      node, color, distance, parent node
class Vertex {
    public:
        std::string color = "white";
        int dist;
        int prev;
        int t_discover;
        int t_finished;    
};

// Create Graph class with:
//      addEdge
//      BFS
class Graph {
    int size;

    public:
        std::vector<std::list<int>> adj;
        std::vector<Vertex> V;
        Graph(int size);
        void addEdge(int src, int dest);
        void BFS(int s);
        void DFS();
        void DFS_Visit(int s);
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
        // adj[u] = <2, 3, 4>
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

void Graph::DFS() {
    int time = 0;
    for (int i = 0; i != adj.size(); i++) {
        if (V[i].color == "white") {
            DFS_Visit(i);
        }
    }
}

void Graph::DFS_Visit(int s) {

}

// define addEdge
// define BFS

// main function: create graph & run BFS

int main() {
    int i;
    i = 0;

    std::vector<std::vector<int>> my_vec(5);
    my_vec[0].push_back(1);
    my_vec[0].push_back(3);
    

    Graph g(5);
    g.addEdge(0,1);
    g.addEdge(0,3);
    g.addEdge(1,2);
    g.addEdge(2,4);
    g.addEdge(3,1);
    std::cout << g.V[4].prev << std::endl;
}