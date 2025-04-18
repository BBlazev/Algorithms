#include <iostream>
#include <vector>
#include <iomanip>

template <typename T>
class Graph {
private:
	int numVertices;
	bool isDirected;
	T noEdgeValue;
	std::vector<std::vector<T>> adjacencyMatrix;  

public:

	Graph(int numVertices, bool isDirected = false, T noEdgeValue = T())
		: numVertices(numVertices),
		isDirected(isDirected),
		noEdgeValue(noEdgeValue),
		adjacencyMatrix(numVertices, std::vector<T>(numVertices, noEdgeValue)) {}


	void addEdge(int sourceVertex, int destinationVertex, T weight = T(1)) {
		if (sourceVertex < 0 || sourceVertex >= numVertices ||
			destinationVertex < 0 || destinationVertex >= numVertices) {
			std::cerr << "Error: vertex index out of range." << std::endl;
			return;
		}
		adjacencyMatrix[sourceVertex][destinationVertex] = weight;
		if (!isDirected) 
			adjacencyMatrix[destinationVertex][sourceVertex] = weight;
		
	}
	void removeEdge(int sourceVertex, int destinationVertex, T weight = T(1)) {
		if (sourceVertex < 0 || sourceVertex >= numVertices ||
			destinationVertex < 0 || destinationVertex >= numVertices) {
			std::cerr << "Error: vertex index out of range." << std::endl;
			return;
		}
		adjacencyMatrix[sourceVertex][destinationVertex] = noEdgeValue;
		if (!isDirected) 
			adjacencyMatrix[destinationVertex][sourceVertex] = noEdgeValue;
		
	}
	bool isEdge(int sourceVertex, int destinationVertex, T weight = T(1)) {
		if (sourceVertex < 0 || sourceVertex >= numVertices ||
			destinationVertex < 0 || destinationVertex >= numVertices) {
			std::cerr << "Error: vertex index out of range." << std::endl;
			return false;
		}
		return adjacencyMatrix[sourceVertex][destinationVertex] != noEdgeValue;
		
	}
	void printMatrix() const {
		std::cout << "Adjacency Matrix (" << (isDirected ? "Directed" : "Undirected")
			<< "), no-edge value = " << noEdgeValue << ":\n    ";
		for (int col = 0; col < numVertices; ++col) {
			std::cout << std::setw(8) << col;
		}
		std::cout << "\n";
		for (int row = 0; row < numVertices; ++row) {
			std::cout << std::setw(3) << row << " ";
			for (int col = 0; col < numVertices; ++col) {
				std::cout << std::setw(8) << adjacencyMatrix[row][col];
			}
			std::cout << "\n";
		}
	}

};

int main() {

	
	Graph<int> graph(5, true, 0);

	graph.addEdge(0, 1, 5);
	graph.addEdge(0, 4, 2);
	graph.addEdge(1, 2, 3);
	graph.addEdge(1, 3, 4);
	graph.addEdge(2, 3, 6);
	graph.addEdge(3, 4, 7);

	graph.printMatrix();
	std::cout << "\nEdge 1-3 exists? " << (graph.isEdge(1, 3) ? "Yes" : "No") << "\n";
	std::cout << "Edge 1-4 exists? " << (graph.isEdge(1, 4) ? "Yes" : "No") << "\n";

	graph.removeEdge(1, 3);
	std::cout << "\nAfter removing edge 1-3:\n";
	graph.printMatrix();

	return 0;


	return 0;
}
