#ifndef MHE_HILL_CLIMB_H
#define MHE_HILL_CLIMB_H

#include <iostream>
#include <functional>

#include "graph_coloring_problem.h"

auto hill_climb_steepest = [](auto cost, auto initial_point, auto neighborhood, int n) {
	auto best_p = initial_point;
	double best_goal_val = cost(best_p);
	bool better_n = true;

	while (n-- > 0 && better_n) {
		better_n = false;
		for (auto n : neighborhood(best_p)) {
			const double n_cost = cost(n);
			if (n_cost < best_goal_val) {
				better_n = true;
				best_p = n;
				best_goal_val = n_cost;
				std::cout << "# better: " << best_goal_val << std::endl;
			}
		}
	}
	return best_p;
};

//auto hill_climb_stochastic = [](auto cost, auto initial_point, auto best_neighbor, int n) {
//	auto best_p = initial_point;
//	double best_goal_val = cost(best_p);
//	bool better_n = true;
//
//	while (n-- > 0 && better_n) {
//		better_n = false;
//		Graph random_best_neighbor = best_neighbor(better_neighbors(generate_neighborhood(best_p), best_p));
//		if (!random_better_neighbor.vertices.empty()) {
//			best_p = random_best_neighbor;
//			std::cout << "# better: " << best_goal_val << std::endl;
//			better_n = true;
//		}
//		
//	}
//	return best_p;
//};

Graph hill_climb_stochastic(std::function<double(Graph)> cost, Graph initial_point, int n) {
	Graph best_p = initial_point;
	double best_goal_val = cost(best_p);
	bool better_n = true;

	while (n-- > 0 && better_n) {
		better_n = false;
		Graph random_better_neighbor = get_random_better_neighbor(better_neighbors(generate_neighborhood(best_p), best_p));
		if (!random_better_neighbor.vertices.empty()) {
			best_p = random_better_neighbor;
			std::cout << "# better: " << best_goal_val << std::endl;
			better_n = true;
		}
	}
	return best_p;
}

#endif
