#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class AdjecencyList {
private:
	std::unordered_map<T, std::vector<T>> adjList;

public:

	void addVertex(const T& v) {

		if (adjList.find(v) == adjList.end())
			adjList[v] = {};
	}
	void addEdge(const T& u, const T& v, bool directed) {
		addVertex(u);
		addVertex(v);
		adjList[u].push_back(v);
		if (!directed) adjList[v].push_back(u);
	}

	void removeEdge(const T& u, const T& v, bool directed) {

		auto it = adjList.find(u);
		if (it != adjList.end()) {
			auto& x = it->second;
			x.erase(std::remove(x.begin(), x.end(), v), x.end());
		}
		if (!directed) {
			auto it2 = adjList.find(v);
			if (it2 != adjList.end()) {
				auto& x2 = it2->second;
				x2.erase(std::remove(x2.begin(), x2.end(), u), x2.end());
			}
		}
	}
	void print() const {
		for (const auto& p : adjList) {
			std::cout << p.first << ": ";
			for (const auto& x : p.second)
				std::cout << x << " ";
			std::cout << std::endl;
		}
		
	}



};





int main() {
	AdjecencyList<std::string> graph;
	graph.addEdge("A", "B", false);
	graph.addEdge("A", "C", true);
	graph.print();

	return 0;
}
