#include <iostream>
#include <chrono>

#include "Graph.h"
#include "graph_coloring_problem.h"
#include "hill_climb.h"
#include "tabu_search.h"
#include "genetic_algorithm.h"

int main() {
	Graph g(8);
	Graph bf_g = g;
	int max_colors = 3;
	g.vertices = generate_random_coloring(g, 3);
// HILL CLIMB
	std::cout << std::endl << "HILL CLIMB" << std::endl;
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

// STOCHASTIC HILL CLIMB
	std::cout << std::endl << "STOCHASTIC HILL CLIMB" << std::endl;
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

//TABOO SEARCH
	std::cout << std::endl << "TABU SEARCH" << std::endl;
	start = std::chrono::steady_clock::now();
	Graph tabus_solution = tabu_search(goal_function, g, generate_neighborhood, 100000, 100);
	finish = std::chrono::steady_clock::now();
	duration = finish - start;
	std::cout << "TIME: " << duration.count() << std::endl
		<< "COST: " << goal_function(tabus_solution) << std::endl;
	tabus_solution.printGraphVizStruct();


// GENETIC ALGORITHM

	std::vector<Graph> start_population;
	for (int i = 0; i < 10; i++) {
		Graph ga = g;
		ga.setVertices(generate_random_coloring(ga, 4));
		start_population.push_back(ga);

		std::cout << "FIT:   " << fit_func(ga) << std::endl
			<< "GOAL:   " << goal_function(ga) << std::endl;
		ga.printGraphVizStruct();

	}

	std::cout << std::endl << "GENETIC ALGORITHM" << std::endl;
	std::vector<Graph> end_pop = genetic_algorithm(
		1000, 0.1, 0.3, start_population,
		fit_func,
		roulette_selection,
		one_point_crossover,
		uniform_mutation, [](int i, std::vector<Graph> g){
		return !(i > 0);
	});

	for (auto p : end_pop) {
		std::cout << "FIT:   " << fit_func(p) << std::endl
			<< "GOAL:   " << goal_function(p) << std::endl;
		p.printGraphVizStruct();
	}



//============BRUTE FORCE
	//std::cout << std::endl << "BRUTE FORCE" << std::endl;
	//start = std::chrono::steady_clock::now();
	//Graph best_solution = bruteForce2(bf_g);
	//finish = std::chrono::steady_clock::now();
	//duration = finish - start;
	//std::cout << "TIME: " << duration.count() << std::endl
	//	<< "COST: " << goal_function(best_solution) << std::endl;
	//best_solution.printGraphVizStruct();
	

	return 0;
}