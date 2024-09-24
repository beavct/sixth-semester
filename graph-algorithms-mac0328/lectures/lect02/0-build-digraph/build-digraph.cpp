#include <utility>                     // for std::pair
#include <array>                       // for std::array
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

int main (int argc, char** argv)
{
  // create the Digraph type
  typedef boost::adjacency_list<boost::vecS, // std::vector's for arcs on each vertex
                                boost::vecS, // std::vector for vertices
                                boost::directedS> Digraph;
  // see https://www.boost.org/doc/libs/1_37_0/libs/graph/doc/using_adjacency_list.html#sec:choosing-graph-type

  typename boost::graph_traits<Digraph>::vertices_size_type num_vertices = 5;
  // int num_vertices = 5; // alternatively, this also works

  // Construct a digraph with no arcs
  Digraph digraph(num_vertices);

  // add arcs; vertex numbers are in the half-open range [0,num_vertices)
  boost::add_edge(0, 1, digraph);
  boost::add_edge(0, 2, digraph);
  boost::add_edge(1, 2, digraph);
  boost::add_edge(2, 0, digraph);
  boost::add_edge(3, 1, digraph);
  boost::add_edge(3, 2, digraph);
  boost::add_edge(3, 4, digraph);
  boost::add_edge(4, 0, digraph);
  boost::add_edge(4, 4, digraph);

  /*
  // alternatively, hardcode vertices in [1,num_vertices] in an array
  std::array<std::pair<int, int>, 9> arcs { {
                                             {1, 2},
                                             {1, 3},
                                             {2, 3},
                                             {3, 1},
                                             {4, 2},
                                             {4, 3},
                                             {4, 5},
                                             {5, 1},
                                             {5, 5} } };

  for (const auto& arc: arcs) {
    boost::add_edge(arc.first - 1, arc.second - 1, digraph);
  }
  */

  return EXIT_SUCCESS;
}
