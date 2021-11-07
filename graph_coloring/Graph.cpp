#include "Graph.h"
#include <vector>
#include <string>
#include <random>
#include <array>

Graph::Graph(int vertex_n) {
	std::random_device rd;
	std::mt19937 mt_generator(rd());
	std::uniform_int_distribution<> edge_prob(0, 1);
	for (int i = 0; i < vertex_n; i++) {
		this->vertices.push_back(1);
		for (int j = 0; j < vertex_n; j++) {
			if (edge_prob(mt_generator) && i != j) {
				std::array<int, 2> edge;
				edge[0] = i;
				edge[1] = j;
				this->edges.push_back(edge);
			}
		}

	}
}

Graph::Graph()
{
}



void Graph::load_graph_from_file(std::string path) {

	inc_matrix_graph_t graph;
	std::ifstream infile(path);
	std::string line;

	while (std::getline(infile, line))
	{
		vertices.push_back(0);
		std::istringstream iss(line);
		int n;
		std::vector<int> row;
		while (!iss.eof())
		{
			iss >> n;
			row.push_back(n);
		}
		graph.push_back(row);
	}
	vertices = std::vector<int>(graph.size(), 1);
	graph = transpose_graph_matrix(graph);
	for (auto e : graph) {
		int i = 0, vi = 0;
		std::array<int, 2> edge;
		for (auto v : e) {
			if (v != 0) {
				edge[i] = vi;
					i++;
			}
			vi++;
		}
		edges.push_back(edge);
	}

}

inc_matrix_graph_t Graph::toInMatrix() {
	inc_matrix_graph_t graph(vertices.size(), std::vector<int>(edges.size(), 0));
	int i = 0;
	for (auto edge : edges) {
		graph[edge[0]][i] = vertices[edge[0]];
		graph[edge[1]][i] = vertices[edge[1]];
		i++;
	}
	return graph;
}

void Graph::printGraphVizStruct() {
	std::cout << "graph G {" << std::endl;
	for (auto e : edges) {
		std::cout << "\t" << e[0] << " -- " << e[1] << ";" << std::endl;
	}
	for (int i = 0; i < vertices.size(); i++) {
		std::cout << "\t" << i << " [color=" << colors[vertices[i]] << ",style=filled];" << std::endl;
	}
	std::cout << "}";
}


inc_matrix_graph_t transpose_graph_matrix(inc_matrix_graph_t g) {
	inc_matrix_graph_t gT;
	for (unsigned int i = 0; i < g.at(0).size(); i++) {
		std::vector<int> row;
		for (auto c : g) {
			row.push_back(c.at(i));
		}
		gT.push_back(row);
	}
	return gT;
}

std::ostream& operator<<(std::ostream& o, inc_matrix_graph_t g) {
	for (auto r : g) {
		for (auto c : r) {
			std::cout << "-" << c << "-";
		}
		std::cout << std::endl;
	}
	return o;
}

std::ostream& operator<<(std::ostream& o, Graph ig) {
	std::cout << ig.toInMatrix();
	return o;
}

