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
			cost += 10.0 * g.vertices.size();
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

Graph next_coloring(Graph g) {
	//for (auto v : g.vertices) {
	//	std::cout << "som wierzcholki" << std::endl;
	//	if (v == g.vertices.size()){
	//		std::cout << g.vertices.size() << std::endl;
	//		v = 1;
	//	}
	//	else {
	//		
	//		++v;
	//		std::cout << g.vertices.size() << "====" << v << std::endl;
	//		break;
	//	}
	//}
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
		if (isColoredCorrectly(g))
			return g;
		g = next_coloring(g);
	}
	return g;
}


#endif // !GRAPH_COLORING_PROBLEM_H

