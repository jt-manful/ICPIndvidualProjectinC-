//
// Created by JOHN-1 on 24/11/2022.
//

#ifndef C___PROJECT_EDGE_H
#define C___PROJECT_EDGE_H


#include "Vertex.h"

class Edge {
public:
    Vertex *source;
    Vertex *destination;
    double weight = 0 ;
    Edge(Vertex , Vertex , double );
};


#endif //C___PROJECT_EDGE_H
