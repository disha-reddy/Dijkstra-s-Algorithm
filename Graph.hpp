/*
    Program:  Graph.hpp
    Authors:  Iman Abu-Khdair(navigator), Disha Reddy (driver)
    Purpose:  header file to Graph.cpp, Vertex.hpp, Edge.hpp, and GraphBase.hpp; 
            provides all necessary functions for all other header and source files; 
            includes a vertex object pointer.
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include "GraphBase.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

class Graph : public GraphBase
{
public:
    void addVertex(std::string label);
    void removeVertex(std::string label);
    void addEdge(std::string label1, std::string label2, unsigned long weight);
    void removeEdge(std::string label1, std::string label2);
    unsigned long shortestPath(string startLabel, string endLabel, std::vector<string> &path);
    void printVertices();

private:
    vector<Vertex *> v; //Vertex object pointer for the graph
};

#endif

