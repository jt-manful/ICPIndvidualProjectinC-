//
// Created by JOHN-1 on 24/11/2022.
//

#include "Vertex.h"

Vertex::Vertex(int id, string name) {
    this->id = id;
    this->name = name;
}

int Vertex :: getId() const{
    return id;
}

string Vertex :: getName() const{
    return name;
}
void Vertex::toString() {
    cout << "ID: "+ to_string(getId()) + " Name " + getName() << endl;
}