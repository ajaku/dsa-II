#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include "graph.h"

using namespace std;

graph::graph(int verticies)
    : minHeap(verticies), knownHash(verticies) {
    numVerts = verticies;
}


/* Possibilites:
 * 1. First time adding edge, insert into verticies then add child
 * to adjacency list. Add node to hash to quickly find, but set known
 * to false.
 * 2. Already in verticies, so just append child to adjacency list
 * No need to add to hash as it is already there
 */
void graph::addEdge(string &parent, string &child, int cost) {
    // If hashTable already contains item, get the pointer from the heap
    // and set the edge cost to cost and parent of that vertex to be 

    Vertex *parentNode;
    Vertex *childNode;

    if (!knownHash.contains(parent)) {
        parentNode = new Vertex {parent, INT_MAX, false, nullptr};
        knownHash.insert(parent, parentNode);
        verticies.push_back(parentNode);
    }


    if (!knownHash.contains(child)) {
        childNode = new Vertex {child, INT_MAX, false, nullptr};
        knownHash.insert(child, childNode);
        verticies.push_back(childNode);
    }

    struct Vertex::edge newEdge = { .eCost = cost, .eChild = childNode};
    parentNode->adjVert.push_back(newEdge);
}

int graph::dijkstra(string &vertex) {
    cout << vertex << "\n";
    return 1;
}