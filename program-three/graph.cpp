#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <fstream>
#include "graph.h"

using namespace std;

#define HEAP_SIZE 1000
#define HASH_SIZE 1000

graph::graph()
     : knownHash(HASH_SIZE) {
        numVerts = 0;
}

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
        verticies.push_back(parentNode);
        numVerts++;
    } else { 
        parentNode = (Vertex *)knownHash.getPointer(parent, &pExists);
    }

    if (!knownHash.contains(child)) {
        childNode = new Vertex {child, INT_MAX, false, nullptr};
        knownHash.insert(child, childNode);
        verticies.push_back(childNode);
        numVerts++;
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

int graph::dijkstra() {
    bool startExists = false;
    Vertex *startNode;
    string vertex; 

    while (!startExists) {
        cout << "Enter name of starting vertex: ";
        cin >> vertex;
        startNode = (Vertex *)knownHash.getPointer(vertex, &startExists);
    }

    clock_t start = clock();

    startNode->dist   = 0;
    startNode->parent = NULL;

    // Is there a more efficient way to do this?
    heap minHeap(numVerts);
    for (int i = 0; i < numVerts; i++) {
        minHeap.insert(verticies[i]->id, verticies[i]->dist, verticies[i]);
    }

    minHeap.setKey(startNode->id, 0);


    int counter = 0;
    while (counter != numVerts) {
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
                it->eChild->dist   = dist;
                it->eChild->parent = newMin;
                // Update the heap to reflect the new minimum value for future deletion
                minHeap.setKey(it->eChild->id, it->eChild->dist);
            }
        }
        counter++;
    }
    clock_t end = clock();
    double time_elapsed = double(end - start) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << time_elapsed << "\n";
    return 1;
}

void graph::parseDijkstra(string outfile) {
    ofstream output;
    output.open(outfile);
    for (int i = 0; i < numVerts; i++) {
        output << verticies[i]->id << ": ";
        Vertex *tmp = verticies[i]; 
        if (verticies[i]->dist == INT_MAX) {
            output << "NO PATH\n";
        } else {
            output << verticies[i]->dist << " [";
            while (tmp != nullptr) {
                verticies[i]->path.push_front(tmp->id);
                tmp = tmp->parent;
            }
            list<string>::iterator it;
            int j = 0;
            for (it = verticies[i]->path.begin(); it != verticies[i]->path.end(); ++it) {
                output << *it;
                if (j < verticies[i]->path.size()-1) {
                    output << ", ";
                }
                j++;
            }
            output << "]\n";
        }
    }
    output.close();
}