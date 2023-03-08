/*
    Program:  Graph.cpp
    Authors:  Iman Abu-Khdair(navigator), Disha Reddy (driver)
    Purpose :  to find the shortest path between two vertices, and implement four operations 
            to construct a graph (add vertices, add edges, remove veritces, and remove edges), 
            as well as an operation to calculate the shoretest distance/path between chosen
            vertices using Dijkstra's Algorithm.
*/

#include <iostream>
#include <climits>
#include <queue>
#include <algorithm>

#include "Graph.hpp"

//Allows vertex label to be inserted into the graph
void Vertex::insertLabel(std::string m)
{
    label = m;
}
//Shows vertex position in each
void Vertex::insertPosition(int n)
{
    position = n;
}
//Takes the edge that connects the two vertces passed and deletes it
void Vertex::deleteEdge(std::string m1, std::string m2)
{
    unsigned int i = 0;
    while (i < e.size())
    {
        if (m2 == e.at(i)->z->label && m1 == e.at(i)->y->label)
        {
            e.erase(e.begin() + i);
            break;
        }
        i++;
    }
}

//Adds new vertex to the graph, and naming it with the label passed into the function
void Graph::addVertex(std::string label)
{
    v.push_back(new Vertex);
    v.back()->insertLabel(label);
    v.back()->insertPosition(v.size() - 1);
}

//Finds the vertex with the same name ("label") and deletes it from the graph
void Graph::removeVertex(std::string label)
{
    unsigned int i = 0;
    while (i < v.size())
    {
        if (label == v.at(i)->label)
        {
            v.erase(v.begin() + i);
            break;
        }
        i++;
    }

    //Repositions already-existing vertices in the graph
    unsigned int j = 0;
    while (j < v.size())
    {
        if (i <= j)
        {
            v.at(j)->position -= 1;
        }
        j++;
    }
}

//Creates an edge to connect to the new vertex added
void Vertex::addEdgetoVertex(unsigned long x, Vertex *c)
{
    e.push_back(new Edge);
    e.back()->position = e.size() - 1;
    e.back()->weight = x;
    e.back()->y = this;
    e.back()->z = c;
}

//Adds a new edge to the specified details that are passed into the function
void Graph::addEdge(std::string label1, std::string label2, unsigned long weight)
{
    unsigned int i = 0;
    //While loop finds the position of the first vertex passed into it
    while (v.size() > i)
    {
        if (label1 == v.at(i)->label)
        {
            break;
        }
        i++;
    }

    //While loop finds the position of the second vertex passed into it
    unsigned int j = 0;
    while (v.size() > j)
    {
        if (label2 == v.at(j)->label)
        {
            break;
        }

        j++; //increments to the next position
    }

    //Adds the new edge connecting each vertex
    v.at(i)->addEdgetoVertex(weight, v.at(j));
    v.at(j)->addEdgetoVertex(weight, v.at(i));
}

//Deletes the edge between the positions of the two vertices passed into the function
void Graph::removeEdge(std::string label1, std::string label2)
{
    unsigned int i = 0; //creates variable to represent first vertex

    //Finds the position of the first vertex and delete the edge it's connected to
    while (v.size() > i)
    {
        if (label1 == v.at(i)->label)
        {
            break;
        }

        i++; //increments to the next position of the first vertex
    }

    v.at(i)->deleteEdge(label1, label2); //actually deletes the edge connecting the first and second vertices

    //Finds the position of the second vertex and deletes the edge it's connected to
    unsigned int j = 0;
    while (v.size() > j)
    {
        if (label2 == v.at(j)->label)
        {
            break;
        }

        j++; //increments to the next position of the second vertex
    }

    v.at(j)->deleteEdge(label2, label1); //actually deletes the edge connecting the first and second vertices
}

//Finds the shortest path between two positions using Dijkstra's Algorithm
unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel, std::vector<string> &path)
{
    unsigned long s = ULONG_MAX;

    //Creates a vector storing the distances between the two vertices passed into the funciton
    vector<unsigned long> d(v.size(), ULONG_MAX);

    //Creates a vector storing the positions of all the unvisited vertices in the graph
    vector<Vertex *> novisit;
    unsigned int i = 0;
    while (v.size() > i)
    {
        novisit.push_back(v.at(i));
        i++; //increments to the next position of the first vertex
    }

    //Creates a vector pointer that points to the previous vertex in the current path
    vector<Vertex *> pre(v.size(), nullptr);

    //Finds the first vertex passed
    Vertex *current;
    i = 0; //reinitializes i to zero
    //While loop finds position of vertex 1
    while (v.size() > i)
    {
        if (startLabel == v.at(i)->label)
        {
            current = v.at(i);
            d.at(i) = 0;
            break;
        }

        i++; //increments to the next position in the graph
    }

    //Find the ending vertex passed
    Vertex *last;
    i = 0; //reintitializes i to zero
    //While loop finds the position of the ending vertex
    while (v.size() > i)
    {
        if (endLabel == v.at(i)->label)
        {
            last = v.at(i);
            break;
        }

        i++; //increments to the next position in the graph
    }

    //While loop iterating through the graph using Dijkstra's Algorithm
    while (!novisit.empty())
    {
        unsigned int j = 0;
        i = 0; //reinitializes i to zero

        //Finds the next unvisited vertex in the graph
        while (novisit.size() > i)
        {
            //Determines if the current position is the closest vertex
            if (d.at(current->position) > d.at(novisit.at(i)->position))
            {
                current = novisit.at(i);
                j = i;
            }

            i++; //increments to the next position in the graph
        }

        //If statement that checks if the desired vertex has been reached
        if (current == last)
        {
            Vertex *f = last;
            path.push_back(last->label);

            //Puts the previous labels into the shortest path in the graph
            while (pre.at(f->position) != nullptr)
            {
                path.push_back(pre.at(f->position)->label);
                f = pre.at(f->position);
            }

            reverse(path.begin(), path.end());

            s = d.at(current->position);
            break;
        }

        //Erases the current vertices from the unvisited vertices in the possible paths
        novisit.erase(novisit.begin() + j);

        i = 0; //reinitializes i to zero for iteration
        //While loop that visits each of the neighbors of the current vertex
        while (current->e.size() > i)
        {
            unsigned int dist = current->e.at(i)->weight + d.at(current->position);
            if (dist < d.at(current->e.at(i)->z->position))
            {
                d.at(current->e.at(i)->z->position) = dist;
                pre.at(current->e.at(i)->z->position) = current;
            }

            i++; //increments to the next position in the graph
        }

        //If statement that assigns the current vertex to the next vertex (that has not been visited yet)
        if (!novisit.empty())
        {
            current = novisit.at(0);
        }
    }

    return s;
}