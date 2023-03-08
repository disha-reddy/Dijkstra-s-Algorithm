/*
    Program:  Vertex.hpp
    Authors:  Iman Abu-Khdair(navigator), Disha Reddy (driver)
    Purpose:  header file to Graph.hpp and Edge.hpp
*/

#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include <vector>

using namespace std; //namespace is used just for simplification and shortening of the code

class Edge; //Declaing Edge class to be used in header and source files

//Class for a vertex containing edges
class Vertex
{
private:
    string label;       //to be used for the name of each vertex
    int position;       //to track the positions of each vertex
    vector<Edge *> e;   //Edge pointer object
    friend class Graph; //connects Vertex to Graph class for header files
    friend class Edge;  //connects Vertex to Edge class for header files
    
public:
    void insertLabel(string m);
    void insertPosition(int n);
    void addEdgetoVertex(unsigned long x, Vertex *c);
    void deleteEdge(string m1, string m2);
    void printsEdges();
};

#endif
