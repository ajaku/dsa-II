#ifndef _GRAPH_H
#define _GRAPH_H

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
        graph();
        void addEdge(const string &parent, const string &child, int cost);
        int  dijkstra();
        void parseDijkstra(string outfile);

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
                list<string>   path;
                vector<edge>   adjVert;
        };

        int numVerts; 
    
        hashTable       knownHash;
        vector<Vertex*> verticies;
};

#endif //_GRAPH_H