#include "dijkstras.h"
#include <algorithm>
using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
	int n = G.numVertices;
	vector<int> distance(n, INF);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

	distance[source] = 0;
	pq.emplace(0, source);
	previous.assign(n, -1);

	while (!pq.empty()) {
		auto [dist, u] = pq.top();
		pq.pop();
		
		if (dist > distance[u]) { continue; }
		
		for (const auto& edge : G[u]) {
			int v = edge.dst
			int weight = edge.weight;
			if (distance[u] + weight < distance[v]) {
				distance[v] = distance[u] + weight;
				previous[v] = u;
				pq.emplace(distance[v], v);
			}
		}
	}
	return distance;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
	vector<int> path;
	if (distances[destination] == INF) {
		return path; 
	}
	for (int v = destination; v != -1; v = previous[v]) {
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	return path;
}
void print_path(const vector<int>& v, int total) {  
	for (size_t i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}
	cout << endl;
	cout << "Total cost is " << total << endl;
}
