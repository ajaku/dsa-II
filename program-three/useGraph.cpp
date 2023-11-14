#include <iostream>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <string>
#include <cstdlib>

#include "graph.h"

using namespace std;

void parse_doc(graph *myGraph) {
    fstream inpFile;
    inpFile.open("g.txt", ios::in);

    string line;
    while (getline(inpFile, line)) {
        cout << "Hello\n";
        stringstream ss(line);
        string s;
        vector<string> v;
        while (getline(ss, s, ' ')) {
            v.push_back(s);
        }
        int cost = stoi(v[2]);
        //cout << "Adding edge: " << v[0] << " " << v[1] << " " << cost << "\n";
        //string &src = v[0];
        //string &des = v[1];
        myGraph->addEdge(v[0], v[1], cost);
    }
    inpFile.close();
}

int main() {
    int verticies = 0;

    // Create the graph 
    graph myGraph(8);
    //parse_doc(&myGraph);
    myGraph.addEdge("v1", "v2", 2);
    myGraph.addEdge("v1", "v4", 1);
    myGraph.addEdge("v2", "v4", 3);
    myGraph.addEdge("v2", "v5", 10);
    myGraph.addEdge("v3", "v1", 4);
    myGraph.addEdge("v3", "v6", 5);
    myGraph.addEdge("v4", "v3", 2);
    myGraph.addEdge("v4", "v5", 2);
    myGraph.addEdge("v4", "v6", 8);
    myGraph.addEdge("v4", "v7", 4);
    myGraph.addEdge("v5", "v7", 6);
    myGraph.addEdge("v7", "v6", 1);
	myGraph.dijkstra("v5");
	myGraph.parseDijkstra();
    
    return 0;
}