#include <vector>                      // for std::vector
#include <utility>                     // for std::pair
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include "digraph.h"

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
