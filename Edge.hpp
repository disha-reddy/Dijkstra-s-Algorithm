/*
    Program:  Edge.cpp
    Authors:  Iman Abu-Khdair(navigator), Disha Reddy (driver)
    Purpose:  header file that prints the position, weight, and labels for
            a and b vertices of all relevant edges.
*/

#ifndef EDGE_H
#define EDGE_H

#include <iostream>

#include "Vertex.hpp"

class Edge
{
private:
    int position;
    int weight;
    Vertex *y;           //tracks the first vertex input by the user/file
    Vertex *z;           //tracks the second vertex input by the user/file
    friend class Vertex; //connects Edge class to Vertex class for header files
    friend class Graph;  //connects Edge clss to Graph class for header files

public:
    void printEdge()
    {
        std::cout << "Position: " << position << " Weight: " << weight << " y: " << y->label << " z: " << z->label << std::endl;
    }

};

#endif
