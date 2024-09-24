#include <iostream>                    // for std::cout and std::endl
#include <vector>
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/range/iterator_range.hpp> // for boost::make_iterator_range
#include "graph.h"                        // TODO: updated headers

using boost::make_iterator_range;

typedef std::vector<Vertex> Path; // alternatively, std::vector<int> should also work

void extend_path_from (const Vertex& start, const Graph& graph,
                       Path& path, std::vector<bool>& visited)
{
  path.push_back(start);
  visited[start] = true;

  for (const auto& edge : make_iterator_range(boost::out_edges (start, graph))) {
    auto vertex = boost::target (edge, graph);
    if (!visited[vertex]) {
      extend_path_from (vertex, graph, path, visited);
      return;
    }
  }
}

Path maximal_path_from (const Vertex& start, const Graph& graph)
{
  std::vector<bool> visited (boost::num_vertices(graph), false);
  Path path;
  extend_path_from (start, graph, path, visited);
  return path;
}

int main (int argc, char** argv)
{
  Graph graph = read_graph(std::cin);

  Vertex start; std::cin >> start;

  Path path(maximal_path_from (--start, graph));

  std::cout << "Maximal path starting at " << start + 1 << " found:";
  for (const auto& vertex : path) {
    std::cout << ' ' << vertex + 1;
  }

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
