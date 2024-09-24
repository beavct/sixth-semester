#include "maximal-path.h"
#include <vector>
#include <numeric>                        // for std::iota
#include <algorithm>                      // for std::reverse
#define BOOST_ALLOW_DEPRECATED_HEADERS    // silence warnings
#include <boost/range/iterator_range.hpp> // for boost::make_iterator_range

Vertex reach_path_from (const Vertex& start, const Graph& graph,
                        std::vector<Vertex>& pred, std::vector<bool>& visited)
{
  visited[start] = true;

  for (const auto& edge : boost::make_iterator_range(boost::out_edges (start, graph))) {
    auto vertex = boost::target (edge, graph);
    if (!visited[vertex]) {
      pred[vertex] = start;
      return reach_path_from (vertex, graph, pred, visited);
    }
  }

  return start;
}

Path maximal_path_from (const Vertex& start, const Graph& graph)
{
  const auto& num_vertices = boost::num_vertices(graph);
  std::vector<bool> visited (num_vertices, false);
  std::vector<Vertex> pred(num_vertices); // predecessors
  std::iota(pred.begin(), pred.end(), 0); // each vertex is its own pred

  Vertex end = reach_path_from (start, graph, pred, visited);

  // build path from predecessors
  Path path;
  while (pred[end] != end) {
    path.push_back(end);
    end = pred[end];
  }
  path.push_back(end);

  std::reverse (path.begin(), path.end());

  return path;
}
