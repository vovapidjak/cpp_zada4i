#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <set>
#include <string>
#include <fstream>
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

#endif // GRAPH_H
