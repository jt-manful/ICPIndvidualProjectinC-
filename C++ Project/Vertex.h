//
// Created by JOHN-1 on 24/11/2022.
//

#ifndef C___PROJECT_VERTEX_H
#define C___PROJECT_VERTEX_H
#include <string>
#include <iostream>
using namespace std;

class Vertex {
public:
    int id;
    string name;
    Vertex(int, string);
    int getId() const;
    string getName() const;
    void toString();
};


#endif //C___PROJECT_VERTEX_H
