//
// Created by JOHN-1 on 24/11/2022.
//

#include "Graph.h"
#include <bits/stdc++.h>


Graph::Graph() {
    this->adjacencyMatrix = new double* [max_vertices];
    for(int i= 0; i < max_vertices; i++){
        adjacencyMatrix[i] = new double [max_vertices];
    }
}


/**
 * The function takes in an integer id and a string name and creates a new Vertex object with the given id and name and
 * adds it to the vertices array
 *
 * @param id The id of the Vertex.
 * @param name The name of the Vertex
 */
void Graph::addVertex(int id, string name) {
    vertices.emplace_back(id, name); // more efficient for user defined types than push back
    vertex_count++;
}


/**
* This function prints the vertices of the Graph
 */
void Graph :: printVertex(){
    for(int i = 0; i < vertex_count ; i++) {
        vertices[i].toString();
    }
}


/**
     * > Given a Vertex name, return the Vertex id
     *
     * @param source The source Vertex from which the shortest path is to be found.
     * @return The id of the Vertex.
     */
int Graph::getVertexId(const string& source) {
    for(int i = 0; i < vertex_count ; i++) {
        if (source == vertices[i].name) {
            return vertices[i].getId();
        }
    }
    return 0;
}


/**
     * > Given a Vertex id, return the Vertex name
     *
     * @param source The source Vertex from which the shortest path is to be found.
     * @return The name of the Vertex.
     */
string Graph::getVertexName(int source) {
    for(int i = 0; i < vertex_count ; i++) {
        if (source == vertices[i].getId()) {
            return vertices[i].getName();
        }
    }
    return " ";
}


/**
     * The function takes in the source and destination node ids and the weight of the Edge as input and adds the Edge to
     * the adjacency matrix
     *
     * @param source_id the id of the source node
     * @param des_id the destination Vertex
     * @param weight the weight of the Edge
     */
void Graph::addEdge(int source_id, int des_id, double  weight) {
    if(source_id != des_id) {
        adjacencyMatrix[source_id][des_id] = weight;
        edge_count ++;
    }

}


/**
    * If the value in the adjacency matrix at the intersection of the source and destination is not zero, then the source
    * and destination are adjacent.
    *
    * @param source The source node
    * @param destination The destination node.
    * @return The adjacency matrix.
    */
bool Graph::isAdjecent(int source, int destination) const {
    if (adjacencyMatrix[source][destination] != 0 ){
        return true;
    }
    return false;
}



/**
    * The function takes in a Vertex id and returns an array list of all the vertices that are adjacent to the Vertex
    *
    * @param vertex_id The id of the Vertex whose successors you want to find.
    * @return The successors of the Vertex with the given id.
    */
vector<int> Graph::getSuccessors(int source_id) {
    vector<int> successors;
    for (int i = 0; i < vertex_count ; i++) {
        if (isAdjecent(source_id, vertices[i].getId())){
            successors.push_back(vertices[i].getId());
        }
    }
    return successors;
}


/**
    * It prints the path from the source to the destination.
    *
    * @param destnation the destination node
    * @return The path from the source to the destination.
    */
vector<string> Graph::printPath(int destination) {
    vector<string> solutionPath;
    solutionPath.push_back(getVertexName(destination));
    int current_node = destination;

    while (predecessor.find(current_node) != predecessor.end()){
        current_node = predecessor.find(current_node)->second;
        if (current_node == 0){
            break;
        }
        solutionPath.push_back(getVertexName(current_node));
    }
    reverse(solutionPath.begin(),solutionPath.end());
    return solutionPath;
}



/**
* The function takes in a source and destination Vertex and returns a list of vertices that form the shortest path
* between the source and destination Vertex
*
* @param source_id the id of the source Vertex
* @param des_id The destination Vertex
* @return The method returns a list of strings that contains the path from the source to the destination.
*/
vector<string> Graph::searchAlgorithm(int source_id, int des_id) {
    predecessor.insert({source_id, 0});

    if(source_id == des_id){
        return printPath(des_id);
    }

    vector<bool> isVisited;
    isVisited.resize(max_vertices,false);

    isVisited[source_id] = true;
    list<int>  queue;
    queue.push_back(source_id);

    while(!queue.empty()){
        int currentvertex = queue.front();
        queue.pop_front();


        if (currentvertex == des_id){
            return printPath(des_id);
        }

        vector<int> successors = getSuccessors(currentvertex);
        for (auto successor : successors) {

            bool found = std::find(queue.begin(), queue.end(), successor) != queue.end();
            if (!found && !isVisited[successor]) {
                iter = predecessor.begin();
                for( ; iter != predecessor.end(); iter ++){
                        if(iter->first != successor){
                            predecessor.insert({successor,currentvertex});
                        }else{
                            predecessor[successor] = currentvertex;
                        }
                }

                queue.push_back(successor);
                isVisited[successor] = true;
            }
        }
        }
    return printPath(0);
}

void Graph::printGraph() const {
    cout << "lets print";
    for (int i = 0; i < vertex_count; i++){
        for(int j =0; j < vertex_count; j++){
            cout << to_string(adjacencyMatrix[i][j]) << " ";
        }
        cout << endl;
    }
}
