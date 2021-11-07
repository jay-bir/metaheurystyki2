#include "Graph.h"
#include "graph_coloring_problem.h"

#include <iostream>

int main() {
	Graph g(10);
	//g.load_graph_from_file("graph.txt");
	g.vertices = generate_random_coloring(g, 3);
	for (auto e : g.edges) {
		std::cout << e[0] << "  =====  " << e[1] << std::endl;
	}
	//for (auto e : g.edges) {
	//	std::cout << e[0] << "=====" << e[1] << std::endl;
	//}

	//for (auto v : g.vertices) {
	//	std::cout << v << "==" << std::endl;
	//}



	//std::cout << g << std::endl;
	//g = next_coloring(g);
	//for (auto v : g.vertices) {
	//	std::cout << v << "==" << std::endl;
	//}
	//double cost = goal_function(g);
	//std::cout << "Cost of current colored graph: " << cost << std::endl;
	//std::cout << g << std::endl;
	g = bruteForce(g);
	g.printGraphVizStruct();
	std::cout<< std::endl << g << std::endl;

	return 0;
}