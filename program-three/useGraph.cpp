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
    cout << "Enter name of graph file: ";
    string inp;
    cin >> inp;
    inpFile.open(inp, ios::in);

    string line;
    while (getline(inpFile, line)) {
        stringstream ss(line);
        string s;
        vector<string> v;
        while (getline(ss, s, ' ')) {
            v.push_back(s);
        }
        int cost = stoi(v[2]);

        myGraph->addEdge(v[0], v[1], cost);
    }
    inpFile.close();
}

int main() {
    graph myGraph;
    parse_doc(&myGraph);
	myGraph.dijkstra();
    cout << "Enter name of output file: ";
    string outfile;
    cin >> outfile;
	myGraph.parseDijkstra(outfile);
    return 0;
}