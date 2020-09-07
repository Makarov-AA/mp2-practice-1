#include "KruskalAlgorithm.h"
#include <ctime>
#include "MyException.h"

int main() {

	int mode = 1;
	std::cout << "Kruskal's algorithm test" << std::endl;

	while (mode == 1 || mode == 2) {
		std::cout << "Enter programm mode: 1 - manual graph input,"
			<< "2 - random graph input, any other value to exit" << std::endl;
		std::cin >> mode;
		switch (mode) {
		case 1:
		{
			try
			{
				Graph graph(5);
				std::cin >> graph;

				std::cout << std::endl << "Graph:";
				std::cout << std::endl << graph << std::endl;
				std::cout << "Adjacency matrix of graph" << std::endl;
				graph.printAdjMatrix();
				std::cout << std::endl;

				Graph spanningTree = KruskalAlgorithm::kruskalAlgorithm(graph);
				std::cout << "Spanning tree of graph: " << std::endl;
				std::cout << spanningTree << std::endl;
				std::cout << "Adjacency matrix of spanning tree" << std::endl;
				spanningTree.printAdjMatrix();
				std::cout << std::endl;
			}
			catch (MyException const& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		}
		case 2:
		{
			int minValue;
			int maxValue;
			int vertsCount;

			srand((unsigned int)time(0));

			std::cout << std::endl;
			std::cout << "Enter count of vertices: ";
			std::cin >> vertsCount;
			while (vertsCount < 0)
			{
				std::cout << std::endl;
				std::cout << "Count of vertices must be > 0!" << std::endl;
				std::cout << "Enter count of vertices: ";
				std::cin >> vertsCount;
			};

			std::cout << std::endl;
			std::cout << "Enter minimal weight value: ";
			std::cin >> minValue;
			std::cout << "Enter maximal weight value: ";
			std::cin >> maxValue;

			while (minValue > maxValue)
			{
				std::cout << std::endl;
				std::cout << "Minimal value must be lesser than maximal value!" << std::endl;
				std::cout << "Enter minimal weight value: ";
				std::cin >> minValue;
				std::cout << "Enter maximal weight value: ";
				std::cin >> maxValue;
			};
			try
			{
				Graph graph = Graph::genRandomConnectedGraphNoLoops(vertsCount, minValue, maxValue);
				std::cout << "Random connected graph without loops:";
				std::cout << std::endl << graph << std::endl;
				std::cout << "Adjacency matrix of random graph:" << std::endl;
				graph.printAdjMatrix();
				std::cout << std::endl;

				Graph spanningTree = KruskalAlgorithm::kruskalAlgorithm(graph);
				std::cout << "Spanning tree of random graph:" << std::endl;
				std::cout << spanningTree << std::endl;
				std::cout << "Adjacency matrix of spanning tree " << std::endl;
				spanningTree.printAdjMatrix();
				std::cout << std::endl;
			}
			catch (MyException const& exp)
			{
				std::cout << exp.what() << std::endl;
			}
			break;
		}
		}
		

	}
	return 0;
}