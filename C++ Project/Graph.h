
#ifndef C___PROJECT_GRAPH_H
#define C___PROJECT_GRAPH_H
#include "Vertex.h"
#include "Edge.h"
#include <map>
#include <unordered_map>
#include "vector"



class Graph {
public:
    int max_vertices = 15000;
    double **adjacencyMatrix ;
    vector<Vertex> vertices;
    int vertex_count = 0;
    int edge_count = 0;
    unordered_map<int, int> predecessor;
    unordered_map<int, int> :: iterator  iter;



public:
    Graph();
    void printGraph() const;
    void addVertex(int id, string name);
    void printVertex();
    void addEdge(int source_id, int des_id, double weight);
    bool isAdjecent(int source , int destination) const;
    vector<int> getSuccessors(int source_id);
    vector<string> printPath(int destination);
    vector<string> searchAlgorithm(int source_id, int des_id);


private:
    string getVertexName(int source);
    int getVertexId(const string& source);
};


#endif //C___PROJECT_GRAPH_H
