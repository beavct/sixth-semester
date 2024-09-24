#include <iostream>                    // for std::cout and std::endl
#include <algorithm>                   // for std::for_each
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/range/iterator_range.hpp> // for boost::make_iterator_range
#include "digraph.h"

int main (int argc, char** argv)
{
  Digraph digraph = read_digraph(std::cin);

  using boost::make_iterator_range;
  for (const auto& vertex : make_iterator_range(boost::vertices(digraph))) {
    size_t outdegree = 0;
    for (const auto& arc : make_iterator_range(boost::out_edges(vertex, digraph))) {
      ++outdegree;
      (void)arc;                // silence warning about unused variable
    }
    std::cout << "The outdegree of " << vertex + 1 << " is "
              << outdegree << std::endl;
  }

  return EXIT_SUCCESS;
}
