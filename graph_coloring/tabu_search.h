#ifndef MHE_TABU_SEARCH_H
#define MHE_TABU_SEARCH_H
#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <set>

Graph tabu_search(std::function<double(Graph)> cost,
	Graph initial_point,
	std::function<std::vector<Graph>(Graph)> neighborhood,
	int n,
	int tabu_size) {

	auto best_p = initial_point;
	std::set<Graph> tabu_set;
	std::list<Graph> tabu_list;

	auto p = best_p;
	for (int i = 0; i < n; i++) {
		std::cout << "iteration: " << i << std::endl;

		auto neighbors = neighborhood(best_p);
		neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(),
			[&](auto g) {
				return tabu_set.count(g);
			}), neighbors.end());

		std::cout << "size of neighbors: " << neighbors.size() << std::endl;
		
		if (neighbors.size() == 0)
			break;

		p = *std::max_element(neighbors.begin(), neighbors.end(), [&](auto a, auto b) {
			return cost(a) > cost(b);
			});

		if (tabu_set.count(p) == 0) {
			tabu_set.insert(p);
			tabu_list.push_back(p);
		}
		double cost_value = cost(p);
		if (cost_value < cost(best_p)) {
			best_p = p;
			std::cout << "TS better: " << cost_value << std::endl;
		}


		//shrink tabu
		if (tabu_set.size() > tabu_size) {
			tabu_set.erase(tabu_list.front());
			tabu_list.pop_front();
		}

		std::cout << "tabu set size: " << tabu_set.size() << std::endl;
		std::cout << "tabu list size: " << tabu_list.size() << std::endl;
	}
	return best_p;
}

#endif
