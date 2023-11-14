#ifndef _DIJKSTRA_H
#define _DIJKSTRA_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "hash.h"
#include "heap.h"

using namespace std;

// Structure Inspired by: Weiss's DSA in C++ Chp. 9.3

class graph {
    public:
        graph(int verticies);
        void addEdge(const string &parent, const string &child, int cost);
        int  dijkstra(const string &vertex);
        void parseDijkstra();

    private:
        class Vertex {
            public:
                struct edge {
                    int     eCost;
                    Vertex *eChild;
                };

                string         id;
                int            dist;
                bool           known;
                Vertex        *parent;
                vector<string> path;
                vector<edge>   adjVert;
        };

        int numVerts; 
    
        hashTable       knownHash;
        heap            minHeap;
        vector<Vertex*> verticies;
};

#endif //_DIJKSTRA_H