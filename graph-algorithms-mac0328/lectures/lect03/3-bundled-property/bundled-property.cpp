#include <iostream>                    // for std::cout and std::endl
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/range/iterator_range.hpp> // for boost::make_iterator_range
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

using boost::make_iterator_range;

using boost::vecS;
using boost::directedS;

struct EnlargedVertex {
  std::string name;
  size_t outdegree;
};

typedef boost::adjacency_list<vecS, vecS, directedS,
                              // vertex properties
                              EnlargedVertex> Digraph;

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

  for (const auto& vertex : make_iterator_range(boost::vertices(digraph))) {

    // generate and store a label for the vertex
    std::stringstream buffer;
    buffer << "Vertex " << vertex + 1;
    digraph[vertex].name = buffer.str();

    for (const auto& arc : make_iterator_range(boost::out_edges(vertex, digraph))) {
      ++digraph[vertex].outdegree;
      (void)arc;              // silence warning about unused variable
    }

    std::cout << "The outdegree of '" << digraph[vertex].name << "' is "
              << digraph[vertex].outdegree << std::endl;
  }

  return EXIT_SUCCESS;
}
