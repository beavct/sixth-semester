#ifndef MAXIMAL_PATH_H
#define MAXIMAL_PATH_H
#include "graph.h"

typedef std::vector<Vertex> Path; // alternatively, std::vector<int> should also work

Path maximal_path_from (const Vertex& start, const Graph& graph);

#endif // #ifndef MAXIMAL_PATH_H
