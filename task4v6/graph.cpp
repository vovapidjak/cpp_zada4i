#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <stdexcept>

class Graph {
public:
    Graph(const std::string& filename);
    void findMinimumSpanningTree(const std::string& outputFilename);
    void logActivity(const std::string& message, const std::string& level = "INFO");

private:
    std::vector<std::list<int>> adjList;
    std::ofstream logFile;

    void readGraph(const std::string& filename);
    void writeGraph(const std::string& filename, const std::vector<std::list<int>>& graph);
};

Graph::Graph(const std::string& filename) {
    logFile.open("log.txt", std::ios::app);
    if (!logFile) {
        throw std::runtime_error("Unable to open log file");
    }
    readGraph(filename);
}

void Graph::logActivity(const std::string& message, const std::string& level) {
    logFile << "[" << level << "] " << message << std::endl;
}

void Graph::readGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        logActivity("Unable to open input file", "ERROR");
        throw std::runtime_error("Unable to open input file");
    }

    int numVertices;
    file >> numVertices;
    adjList.resize(numVertices);

    int vertex, neighbor;
    while (file >> vertex >> neighbor) {
        adjList[vertex].push_back(neighbor);
        adjList[neighbor].push_back(vertex);
    }

    logActivity("Graph successfully read from file");
}

void Graph::writeGraph(const std::string& filename, const std::vector<std::list<int>>& graph) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        logActivity("Unable to open output file", "ERROR");
        throw std::runtime_error("Unable to open output file");
    }

    file << graph.size() << std::endl;
    for (size_t i = 0; i < graph.size(); ++i) {
        for (int neighbor : graph[i]) {
            file << i << " " << neighbor << std::endl;
        }
    }

    logActivity("Minimum spanning tree successfully written to file");
}

void Graph::findMinimumSpanningTree(const std::string& outputFilename) {
    std::vector<bool> visited(adjList.size(), false);
    std::set<std::pair<int, int>> mstEdges;
    std::vector<std::list<int>> mst(adjList.size());

    visited[0] = true;
    for (int neighbor : adjList[0]) {
        mstEdges.insert({0, neighbor});
    }

    while (!mstEdges.empty()) {
        auto edge = *mstEdges.begin();
        mstEdges.erase(mstEdges.begin());

        int u = edge.first, v = edge.second;
        if (visited[u] && visited[v]) continue;

        if (!visited[v]) std::swap(u, v);

        visited[v] = true;
        mst[u].push_back(v);
        mst[v].push_back(u);

        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                mstEdges.insert({v, neighbor});
            }
        }
    }

    writeGraph(outputFilename, mst);
    logActivity("Minimum spanning tree found");
}
