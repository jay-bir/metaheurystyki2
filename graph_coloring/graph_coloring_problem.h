#ifndef GRAPH_COLORING_PROBLEM_H
#define GRAPH_COLORING_PROBLEM_H

#include "Graph.h"
#include <random>
#include <vector>
#include <iostream>
#include <cmath>

double goal_function(Graph g) {
	double cost = 0;
	for (auto e : g.edges) {
		double a = g.vertices[e[0]], b = g.vertices[e[1]];
		if (a != b)
			cost += ((a - b) * (a - b)) + a + b;
		else
			cost += 10.0 * g.edges.size();
	}
	return cost;
}
/*
	Returns a vector of ints (vertices) with values (colors) from 1 to max_chrom_number 
*/

std::vector<int> generate_random_coloring(Graph g, int max_colors) {
	std::random_device rd;
	std::mt19937 mt_generator(rd());
	max_colors = max_colors <= g.vertices.size() ? max_colors : g.vertices.size();
	std::uniform_int_distribution<int> distr(1, max_colors);
	std::vector<int> colored_vertices;
	for (auto v : g.vertices) {
		colored_vertices.push_back(distr(mt_generator));
	}
	return colored_vertices;
}
//wrong!!!!
//Graph generate_random_neighbor(Graph g) {
//	std::random_device rd;
//	std::mt19937 mt_generator(rd());
//	std::uniform_int_distribution<int> distr(-1, 1);
//	for (auto &v : g.vertices) {
//		v = (v + distr(mt_generator))%g.vertices.size();
//		if (v == 0)
//			++v;
//	}
//	return g;
//}
std::vector<Graph> better_neighbors(std::vector<Graph> neighborhood, Graph g) {
	std::vector<Graph> b_neighbors;
	const double cost_g = goal_function(g);
	for (auto n : neighborhood) {
		if (goal_function(n) < cost_g)
			b_neighbors.push_back(n);
	}
	return b_neighbors;
}

Graph get_random_better_neighbor(std::vector<Graph> b_neighborhood) {
	if (b_neighborhood.empty())
		return Graph();
	std::random_device rd;
	std::mt19937 mt_generator(rd());
	std::uniform_int_distribution<int> distr(0, b_neighborhood.size() -1);
	return b_neighborhood[distr(mt_generator)];
}

std::vector<Graph> generate_neighborhood(Graph g) {
	std::vector<Graph> neighborhood;
	for (int i = 0; i < g.vertices.size(); i++) {
		Graph n1 = g;
		Graph n2 = g;
		n1.vertices[i] = n1.vertices[i] % n1.vertices.size() + 1;
		n2.vertices[i] -= 1;
		if (n2.vertices[i] == 0)
			n2.vertices[i] = n2.vertices.size();
		neighborhood.push_back(n1);
		neighborhood.push_back(n2);
	}
	return neighborhood;
}

Graph next_coloring(Graph g) {
	for (int i = 0; i < g.vertices.size(); i++) {
		if (g.vertices[i] == g.vertices.size()) {
			g.vertices[i] = 1;
		}
		else {
			++g.vertices[i];
			break;
		}
	}
	return g;
}

bool isColoredCorrectly(Graph g) {
	for (auto e : g.edges) {
		if (g.vertices[e[0]] == g.vertices[e[1]]) {
				return false;
		}
	}
	return true;
}

Graph bruteForce(Graph g) {
	unsigned long long upperBound = std::pow(g.vertices.size(), g.vertices.size());
	std::cout << std::endl << upperBound << std::endl;
	while (upperBound-- > 0) {
		if (isColoredCorrectly(g)) {
			std::cout << std::endl << upperBound << std::endl;
			return g;
		}
		g = next_coloring(g);
	}
	return g;
}

Graph bruteForce2(Graph g) {
	unsigned long long upperBound = std::pow(g.vertices.size(), g.vertices.size());
	std::cout << std::endl << upperBound << std::endl;
	Graph best_coloring = g;
	double best_cost = goal_function(best_coloring);
	while (upperBound-- > 0) {
		double cur_cost = goal_function(g);
		if (cur_cost < best_cost) {
			//std::cout << std::endl << upperBound << std::endl;
			best_coloring = g;
			best_cost = cur_cost;
			std::cout << best_cost << std::endl;
			//g.printGraphVizStruct();
		}
		g = next_coloring(g);
	}
	return best_coloring;
}


#endif // !GRAPH_COLORING_PROBLEM_H

