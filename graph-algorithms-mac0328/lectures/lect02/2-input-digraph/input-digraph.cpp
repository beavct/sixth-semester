#include <iostream>                    // for std::cout and std::endl
#include <utility>                     // for std::pair
#include <vector>                      // for std::vector
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/range/iterator_range.hpp> // for boost::make_iterator_range

// create the Digraph type
typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS> Digraph;

Digraph read_digraph (std::istream& in)
{
  typedef typename boost::graph_traits<Digraph>::vertices_size_type vertices_size_type;
  vertices_size_type num_vertices; in >> num_vertices;

  size_t num_arcs; in >> num_arcs;

  // accumulate all data before digraph construction
  std::vector<std::pair<int, int> > arcs;
  while (num_arcs--) {
    int u, v; in >> u >> v;
    arcs.push_back(std::make_pair(--u, --v));
  }

  // guarantees copy elision in c++17
  return Digraph(arcs.cbegin(), arcs.cend(), num_vertices);
}

int main (int argc, char** argv)
{
  Digraph digraph = read_digraph(std::cin);

  typedef boost::graph_traits<Digraph>::vertex_iterator vertex_iter_type;
  vertex_iter_type vertex_it, vertex_end;

  using boost::make_iterator_range;
  for (const auto& vertex : make_iterator_range(boost::vertices(digraph))) {
    std::cout << "Arcs that leave " << vertex + 1 << " go to:";
    for (const auto& arc : make_iterator_range(boost::out_edges(vertex, digraph))) {
      std::cout << " " << boost::target(arc, digraph) + 1;
    }

    std::cout << std::endl;
  }

  return EXIT_SUCCESS;
}
