#include <iostream>                    // for std::cout and std::endl
#include <utility>                     // for std::pair
#include <tuple>                       // for std::tie
#include <algorithm>                   // for std::for_each
#include <array>                       // for std::array
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/range/iterator_range.hpp> // for boost::make_iterator_range

int main (int argc, char** argv)
{
  // create the Digraph type
  typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS> Digraph;

  typename boost::graph_traits<Digraph>::vertices_size_type num_vertices = 5;

  // hardcode vertices in [1,num_vertices] in an array
  std::array<std::pair<int, int>, 9> arcs { { {1, 2},
                                              {1, 3},
                                              {2, 3},
                                              {3, 1},
                                              {4, 2},
                                              {4, 3},
                                              {4, 5},
                                              {5, 1},
                                              {5, 5} } };

  for (auto& a : arcs) {
    --a.first;
    --a.second;
  }

  // Construct a digraph with arcs
  Digraph digraph(arcs.cbegin(), arcs.cend(), num_vertices);

  typedef boost::graph_traits<Digraph>::vertex_iterator vertex_iter_type;
  vertex_iter_type vertex_it, vertex_end;

  // alternatively: typename boost::graph_traits<Digraph>::vertex_iterator vertex_it, vertex_end;

  // boost::vertices(digraph) returns an std::pair p; unpack it using std::tie
  // valid vertices are in the range [p.first, p.second)
  for (std::tie(vertex_it, vertex_end) = boost::vertices(digraph);
       vertex_it != vertex_end; ++vertex_it) { // iterate over the vertices

    std::cout << "Arcs that leave " << *vertex_it + 1 << " go to:";

    typename boost::graph_traits<Digraph>::out_edge_iterator out_edge_it, out_edge_end;

    for (std::tie(out_edge_it, out_edge_end) = boost::out_edges(*vertex_it, digraph);
         out_edge_it != out_edge_end; ++out_edge_it) { // iterate over outgoing arcs

      std::cout << " " << boost::target(*out_edge_it, digraph) + 1;
      // `target` gets the head of the arc, `source` gets the tail
    }

    std::cout << std::endl;     // newline (plus flushing)
  }

  /*
  // alternatively: use C++11 auto
  for (auto vp = boost::vertices(digraph); vp.first != vp.second; ++vp.first) {
    const auto& vertex = *vp.first;
    std::cout << "Arcs that leave " << vertex + 1 << " go to:";
    for (auto ep = boost::out_edges(vertex, digraph); ep.first != ep.second; ++ep.first) {
      const auto& arc = *ep.first;
      std::cout << " " << boost::target(arc, digraph) + 1;
    }
    std::cout << std::endl;
  }
  */

  /*
  // alternatively: use std::for_each with a lambda
  std::for_each(boost::vertices(digraph).first,
                boost::vertices(digraph).second,
                [&](const auto& vertex) { // a C++14 lambda; captures context by reference
                  std::cout << "Arcs that leave " << vertex + 1 << " go to:";

                  std::for_each(boost::out_edges(vertex, digraph).first,
                                boost::out_edges(vertex, digraph).second,
                                [&](const auto& arc) {
                                  std::cout << " " << boost::target(arc, digraph) + 1;
                                });

                  std::cout << std::endl;
                });
  */

  /*
  // alternatively: use range for with boost::make_iterator_range
  using boost::make_iterator_range;
  for (const auto& vertex : make_iterator_range(boost::vertices(digraph))) {
    std::cout << "Arcs that leave " << vertex + 1 << " go to:";
    for (const auto& arc : make_iterator_range(boost::out_edges(vertex, digraph))) {
      std::cout << " " << boost::target(arc, digraph) + 1;
    }

    std::cout << std::endl;
  }
  */

  return EXIT_SUCCESS;
}
