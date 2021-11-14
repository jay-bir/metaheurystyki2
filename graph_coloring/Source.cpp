#include <iostream>
#include <chrono>

#include "Graph.h"
#include "graph_coloring_problem.h"
#include "hill_climb.h"

int main() {
	Graph g(8);
	Graph bf_g = g;
	int max_colors = 3;
	g.vertices = generate_random_coloring(g, 3);

	auto start = std::chrono::steady_clock::now();
	Graph hc_steep_solution = hill_climb_steepest(
			goal_function,
			g,
			generate_neighborhood,
				100000);
	auto finish = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = finish - start;
	std::cout << "TIME: " << duration.count() << std::endl
		<< "COST: " << goal_function(hc_steep_solution) << std::endl;
	hc_steep_solution.printGraphVizStruct();


	start = std::chrono::steady_clock::now();
	Graph hc_stochastic_solution = hill_climb_stochastic(
		goal_function,
		g,
		100000);

	finish = std::chrono::steady_clock::now();
	duration = finish - start;
	std::cout << "TIME: " << duration.count() << std::endl
		<< "COST: " << goal_function(hc_stochastic_solution) << std::endl;
	hc_stochastic_solution.printGraphVizStruct();
	
	//g.load_graph_from_file("graph.txt");
	//g.vertices = generate_random_coloring(g, 3);
	//for (auto e : g.edges) {
	//	std::cout << e[0] << "  =====  " << e[1] << std::endl;
	//}
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

	start = std::chrono::steady_clock::now();
	Graph best_solution = bruteForce2(bf_g);

	finish = std::chrono::steady_clock::now();
	std::cout << "TIME: " << duration.count() << std::endl
		<< "COST: " << goal_function(best_solution) << std::endl;
	best_solution.printGraphVizStruct();
	

	return 0;
}