#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>             // for std::istream
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;

Graph read_graph (std::istream& in);

#endif // #ifndef GRAPH_H
