// ENTREGAR

#ifndef GRAPH_H
#define GRAPH_H

#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <vector>
#include <stack>
#include <utility>

/* Students may add any number of fields and methods to this struct;
 * however the cutvertex field must be preserved unchanged, and it
 * must be filled with the appropriate boolean value according to the
 * debug level. */
struct BundledVertex {
  bool cutvertex = false;


};

/* Students may add any number of fields and methods to this struct;
 * however the bcc and bridge fields must be preserved unchanged, and
 * they must be filled with the appropriate values according to the
 * debug level. */
struct BundledEdge {
  size_t bcc = 0;                   // biconnected component label
  bool bridge = false;
};

/* color: 
*   0 -> white
*   1 -> gray
*   2 -> black
*
*  pi[u] = -1 = nil
*/

/* the remainder of the file must not be changed */
typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::undirectedS,
                              BundledVertex,
                              BundledEdge> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph>::edge_descriptor Edge;

#endif // #ifndef GRAPH_H

class Infos {
  public:
    Infos(int num_vertices, Graph& G)
      : n_vertices(num_vertices), label(0), nscc(0), time(0), G(G), d(num_vertices), f(num_vertices), color(num_vertices, 0), pi(num_vertices), id(num_vertices), lowlink(num_vertices), S_set(), S() {}

  int n_vertices;
  int label;
  int nscc;
  int time;
  Graph& G;
  std::vector<int> d;
  std::vector<int> f;
  std::vector<int> color;
  std::vector<int> pi;
  // vertices visiting order
  std::vector<int> id; 
  // The low-link value of a node is the smallest discovery time reachable from that node when doing a depth-first search (DFS), including itself, considering the back-edges.
  std::vector<int> lowlink; 
  std::set<std::pair<int,int>> S_set;
  std::stack<std::pair<int,int>> S;
};

