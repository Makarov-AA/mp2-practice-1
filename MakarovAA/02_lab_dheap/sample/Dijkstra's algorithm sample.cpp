#include <iostream>
#include <ctime>

#include "DijkstraAlgorithm.h"
#include "MyException.h"
#include "Distances.h"
#include "Graph.h"

int main() {
	std::cout << "Dijkstra's algorithm test program" << std::endl;
	int mode = 1;
	while (mode == 1 || mode == 2) {
		std::cout << "Input programm mode: 1 - manual input, 2 - random input";
		std::cout << ", any other value to exit programm" << std::endl;
		std::cin >> mode;
		switch (mode) {
		case 1:
		{
			try {
				int startVertex;

				Graph graph(5);
				std::cin >> graph;

				std::cout << std::endl << "Graph:";
				std::cout << std::endl << graph << std::endl;
				std::cout << "Adjacency matrix of graph" << std::endl;
				graph.printAdjMatrix();
				std::cout << std::endl;

				std::cout << std::endl;
				std::cout << "Enter start vertex for Dijkstra's algorithm: ";
				std::cin >> startVertex;
				if ((startVertex < 0) || (startVertex >= graph.getVertsCount()))
					throw MyException("Incorrect start vertex");

				Distances distances = DijkstraAlgorithm::dijkstraAlgorithm(graph, startVertex);
				std::cout << "Result of Dijkstra's algorithm:" << std::endl;
				std::cout << std::endl << distances << std::endl;
			}
			catch (const MyException& excp) {
				std::cout << excp.what() << std::endl;
			}
			break;
		}
		case 2:
			try {
				int minValue;
				int maxValue;
				int vertsCount;
				int startVertex;

				srand((unsigned int)time(0));

				std::cout << std::endl;
				std::cout << "Enter count of vertices: ";
				std::cin >> vertsCount;

				if (vertsCount < 0)
					throw MyException("Count of vertices must be > 0");

				std::cout << std::endl;
				std::cout << "Enter minimal value: ";
				std::cin >> minValue;

				if (minValue <= 0)
					throw MyException("Minimal value must be non-negative for Dijkstra's algorithm");

				std::cout << "Enter maximal value: ";
				std::cin >> maxValue;

				if (minValue > maxValue)
					throw MyException("Minimal value must be lesser than maximal value");

				std::cout << std::endl;
				std::cout << "Enter start vertex for Dijkstra's algorithm: ";
				std::cin >> startVertex;
				if ((startVertex < 0) || (startVertex >= vertsCount))
					throw MyException("Incorrect start vertex");

				Graph graph = Graph::genRandomConnectedGraphNoLoops(vertsCount, minValue, maxValue);
				std::cout << std::endl << std::endl << "Random connected graph without loops:";
				std::cout << std::endl << graph << std::endl;
				std::cout << "Adjacency matrix of random graph" << std::endl;
				graph.printAdjMatrix();
				std::cout << std::endl;

				Distances distances = DijkstraAlgorithm::dijkstraAlgorithm(graph, startVertex);
				std::cout << "Result of Dijkstra's algorithm:" << std::endl;
				std::cout << std::endl << distances << std::endl;
			}
			catch (const MyException& excp) {
				std::cout << excp.what() << std::endl;
			}
			break;
		}
	}
	return 0;
}