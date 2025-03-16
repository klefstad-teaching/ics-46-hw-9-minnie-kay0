#include "dijkstras.h"
#include <iostream>
using namespace std;

int main() {
	Graph G;
	file_to_graph("src/small.txt", G);

	vector<int> prev;
	vector<int> distances = dijkstra_shortest_path(G, 0, prev);

	for (int dest = 0; dest < G.numVertices; ++dest) {
		vector<int> v = extract_shortest_path(distances, prev, dest);
		print_path(v, distances[dest]);
	}

	return 0;
}