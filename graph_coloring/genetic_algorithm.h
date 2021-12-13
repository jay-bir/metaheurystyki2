#ifndef MHE_GENALG_H
#define MHE_GENALG_H

#include <vector>
#include <functional>
#include <random>

#include "Graph.h"
#include "graph_coloring_problem.h"

//================================================
//TODO refactor everything for graph vertices
//================================================

std::random_device garDevice;
std::mt19937 gaRandgen(garDevice());

double fit_func(Graph g) {
	return 10000.0 / goal_function(g);
}

std::vector<Graph> roulette_selection(std::vector<Graph> pop, std::vector<double> pop_fit) {

	std::vector<Graph> selected_pop;

	double s = 0;
	for (int i = 0; i < pop.size(); i++) {
		s += pop_fit[i];
	}
	std::uniform_real_distribution<double> dist(0, s);
	for (int p = 0; p < pop.size(); p++) {
		double p_sum = 0;
		double r = dist(gaRandgen);
		for (int i = 0; i < pop.size(); i++) {
			p_sum += pop_fit[i];

			if (r < p_sum) {
				selected_pop.push_back(pop[i]);
				break;
			}

		}
	}

	return selected_pop;
}

std::vector<Graph> one_point_crossover(double p_cross, Graph a, Graph b) {


	std::uniform_int_distribution<int> cpdist(0, a.vertices.size() -1);
	int pp = cpdist(gaRandgen);
	for (int i = pp; i < a.vertices.size(); i++) {
		std::swap(a.vertices[i], b.vertices[i]);
	}

	return { a, b };
}

Graph uniform_mutation(double p_mut, Graph g) {
	return g;
}


std::vector<Graph> genetic_algorithm(
	int iterations,
	double mut_prob, double cross_prob,
	std::vector<Graph> population,
	std::function<double(Graph)> fitness,
	std::function<std::vector<Graph>(std::vector<Graph>, std::vector<double>)> par_selection,
	std::function<std::vector<Graph>(double, Graph, Graph)> crossover,
	std::function<Graph(double, Graph)> mutation,
	std::function<bool(int)> finish) {


	std::vector<double> pop_fit;


	while (!finish(iterations--)) {
		for (int i = 0; i < population.size(); i++) {
			pop_fit.push_back(fitness(population[i]));
		}

		std::vector<Graph> parents = par_selection(population, pop_fit);
		std::vector<Graph> children;

		size_t parent_index = 1;
		while ((children.size() < parents.size()) && (parent_index < parents.size())) {

			for (auto e : crossover(cross_prob, parents[parent_index], parents[parent_index - (size_t)1])) {
				children.push_back(e);
			}

			parent_index += 2;
		}

		for (auto& c : children) {
			c = mutation(mut_prob, c);
		}

		population = children;

	}
	return population;
}

#endif // !MHE_GENALG_H

