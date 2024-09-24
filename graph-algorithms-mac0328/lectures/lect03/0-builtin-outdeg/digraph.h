#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <iostream>                    // for std::istream
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS> Digraph;

Digraph read_digraph (std::istream& in);

#endif // #ifndef DIGRAPH_H
