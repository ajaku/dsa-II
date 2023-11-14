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
void graph::addEdge(const string &parent, const string &child, int cost) {
    // If hashTable already contains item, get the pointer from the heap
    // and set the edge cost to cost and parent of that vertex to be 

    Vertex *parentNode;
    Vertex *childNode;
    bool pExists = true;
    bool cExists = true;

    if (!knownHash.contains(parent)) {
        parentNode = new Vertex {parent, INT_MAX, false, nullptr};
        knownHash.insert(parent, parentNode);
        minHeap.insert(parent, parentNode->dist, parentNode);
        verticies.push_back(parentNode);
    } else { 
        parentNode = (Vertex *)knownHash.getPointer(parent, &pExists);
    }


    if (!knownHash.contains(child)) {
        childNode = new Vertex {child, INT_MAX, false, nullptr};
        knownHash.insert(child, childNode);
        minHeap.insert(child, childNode->dist, childNode);
        verticies.push_back(childNode);
    } else {
        childNode = (Vertex *)knownHash.getPointer(child, &cExists);
    } 

    if (pExists && cExists) {
        struct Vertex::edge newEdge; //= new Vertex::edge;
        newEdge.eCost = cost;
        newEdge.eChild = childNode;
        parentNode->adjVert.push_back(newEdge);
    } else { /*What do we do here? Seems like an error condition*/ }
}

int graph::dijkstra(const string &vertex) {
    bool startExists;
    Vertex *startNode = (Vertex *)knownHash.getPointer(vertex, &startExists);

    if (!startExists) { return -1; }

    startNode->dist   = 0;
    startNode->parent = NULL;
    startNode->path.push_back(startNode->id);
    minHeap.setKey(startNode->id, 0);


    int counter = 0;
    while (counter != numVerts-1) {
        cout << "Counter : " << counter << "\n";
        string heapVal;
        bool minExists = false;
        Vertex* newMin;

        while (!minExists) {
            minHeap.deleteMin(&heapVal, nullptr, nullptr);
            newMin = (Vertex*)knownHash.getPointer(heapVal, &minExists);            
        }

        newMin->known = true;

        vector<Vertex::edge>::iterator it;
        for (it = newMin->adjVert.begin(); it != newMin->adjVert.end(); ++it) {
            int dist = newMin->dist + it->eCost;
            // Goal is to prevent overflow math
            if (dist < 0) { dist = INT_MAX; }
            if (dist < it->eChild->dist) {
                newMin->path.push_back(it->eChild->id);
                it->eChild->dist   = dist;
                it->eChild->parent = newMin;
                // Update the heap to reflect the new minimum value for future deletion
                minHeap.setKey(it->eChild->id, it->eChild->dist);
            }
        }
        counter++;
    }
    return 1;
}

void graph::parseDijkstra() {
    for (int i = 0; i < numVerts - 1; i++) {
        cout << verticies[i]->id << ": ";
        if (verticies[i]->dist == INT_MAX) {
            cout << "NO PATH\n";
        } else {
            cout << "[";
            for (auto &s : verticies[i]->path) {
                cout << s << ",";
            }
            cout << "]\n";
        }
    }
}