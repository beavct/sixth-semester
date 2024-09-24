#include <iostream>                    // for std::cout and std::endl
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/range/iterator_range.hpp> // for boost::make_iterator_range
#include "digraph.h"                      // TODO: see new definition of Digraph

int main (int argc, char** argv)
{
  Digraph digraph = read_digraph(std::cin);

  // get the property map for out_degrees
  // see https://www.boost.org/doc/libs/1_76_0/libs/graph/doc/using_adjacency_list.html#sec:adjacency-list-properties
  auto outdeg = boost::get(boost::vertex_out_degree, digraph);

  using boost::make_iterator_range;
  for (const auto& vertex : make_iterator_range(boost::vertices(digraph))) {
    for (const auto& arc : make_iterator_range(boost::out_edges(vertex, digraph))) {
      ++outdeg[vertex];
      (void)arc;              // silence warning about unused variable
    }
    std::cout << "The outdegree of " << vertex + 1 << " is "
              << outdeg[vertex] << std::endl;
  }

  return EXIT_SUCCESS;
}
