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
    std::cout << "The outdegree of " << vertex + 1 << " is "
              << boost::out_degree(vertex, digraph) << std::endl;
  }

  return EXIT_SUCCESS;
}
