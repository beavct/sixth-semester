#include <iostream>                    // for std::cout and std::endl
#include "graph.h"
#include "maximal-path.h"

int main (int argc, char** argv)
{
  Graph graph = read_graph(std::cin);

  Vertex start; std::cin >> start;

  auto path(maximal_path_from (--start, graph));

  std::cout << "Maximal path starting at " << start + 1 << " found:";
  for (const auto& vertex : path) {
    std::cout << ' ' << vertex + 1;
  }

  std::cout << std::endl;

  return EXIT_SUCCESS;
}
