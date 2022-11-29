

#include "Edge.h"
Edge::Edge(Vertex source, Vertex destination, double weight) {
    this->source = &source;
    this->destination = &destination;
    this->weight = weight;
}
