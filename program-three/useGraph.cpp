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
  	parse_doc(&myGraph);

  	return 0;
}
