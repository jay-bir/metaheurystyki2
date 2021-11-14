#ifndef MHE_GRAPH_H
#define MHE_GRAPH_H

#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using inc_matrix_graph_t = std::vector<std::vector<int>>;
const std::vector<std::string> colors{ 
	"red", "blue", "yellow", "green","pink", 
	"lightgrey", "crimson", "blueviolet", "coral", 
	"greenyellow", "magenta", "moccasin", "salmon",
	"seagreen", "turquoise", "violet"};


class Graph
{
public:
	std::vector<int> vertices;
	std::vector<std::array<int, 2>> edges;
	void load_graph_from_file(std::string path);
	inc_matrix_graph_t toInMatrix();
	void printGraphVizStruct();
	void setVertices(std::vector<int> v);
	Graph(int vertex_n);
	Graph();
};

inc_matrix_graph_t transpose_graph_matrix(inc_matrix_graph_t g);

std::ostream& operator<<(std::ostream& o, inc_matrix_graph_t g);

std::ostream& operator<<(std::ostream& o, Graph ig);

#endif
