#include <iostream>                    // for std::cout and std::endl
#include <algorithm>                   // for std::find_if
#include <vector>
#include "graph.h"
#include "maximal-path.h"

bool is_path (const Path& path, const Graph& graph)
{
  std::vector<bool> visited(boost::num_vertices(graph), false);

  auto vertex_it = path.cbegin(), vertex_end = path.cend();
  Vertex u = *vertex_it++;
  visited[u] = true;

  while (vertex_it != vertex_end) {
    Vertex v = *vertex_it++;
    if (visited[v]) {
      return false;             // repeated vertex
    }
    visited[v] = true;
    auto u_edges = boost::make_iterator_range(boost::out_edges(u, graph));
    using boost::target;
    if (u_edges.end() == std::find_if (u_edges.begin(), u_edges.end(),
                                       [&](const auto& edge) -> bool {
                                         return target (edge, graph) == v;
                                       })) {
      return false;      // consecutive vertices not joined by an edge
    }
    u = v;
}

return true;
}

typedef typename boost::graph_traits<Graph>::degree_size_type Degree;

Degree min_degree (const Graph& graph)
{
  auto verts = boost::make_iterator_range(boost::vertices(graph));
  using boost::degree;
  auto vertex_it = std::min_element (verts.begin(), verts.end(),
                                     [&](const auto& u, const auto& v) -> bool {
                                       return degree(u, graph) < degree(v, graph);
                                     });
  return vertex_it == verts.end() ? 0 : degree(*vertex_it, graph);
}

int main (int argc, char** argv)
{
  Graph graph = read_graph(std::cin);
  Vertex start; std::cin >> start;

  using std::cout;
  using std::endl;

  auto path(maximal_path_from (--start, graph));
  // test path verification with a non-path
  // std::vector<Vertex> path({1,6});
  // test path verification with a short path
  // std::vector<Vertex> path({0,1});

  cout << "Maximal path starting at " << start + 1 << " found:";
  for (const auto& vertex : path) {
    cout << ' ' << vertex + 1;
  }
  cout << endl;

  cout << "Path verification... ";
  if (is_path (path, graph)) {
    cout << "OK" << endl;
  } else {
    cout << "FAILED" << endl;
    return EXIT_SUCCESS;
  }

  /* Exercise: test if the path is maximal */

  // min degree verification
  auto pathlen = path.size() - 1;
  auto mindeg = min_degree(graph);
  if (pathlen >= mindeg) {
    cout << "Path length = " << pathlen << " >= "
         << mindeg << " = min degree" << endl;
  } else {
    cout << "Something must have gone wrong" << endl;
  }

  return EXIT_SUCCESS;
}
