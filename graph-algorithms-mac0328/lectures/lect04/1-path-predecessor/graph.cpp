#include <vector>                      // for std::vector
#include <utility>                     // for std::pair
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include "graph.h"

Graph read_graph (std::istream& in)
{
  typename boost::graph_traits<Graph>::vertices_size_type num_vertices; in >> num_vertices;

  Graph graph(num_vertices);

  size_t num_edges; in >> num_edges;

  // accumulate all data before graph construction
  std::vector<std::pair<int, int> > edges;
  while (num_edges--) {
    int u, v; in >> u >> v;
    edges.push_back(std::make_pair(--u, --v));
  }

  // guarantees copy elision in c++17
  return Graph (edges.cbegin(), edges.cend(), num_vertices);
}
