/* the definition of HeadStart may be changed in this file; the rest
 * MUST NOT be changed
 */

/*
    - This file must be sumitted

    - We must change only the declaration of the class HeadStart

    - This class should store whatever info. you deem useful to be returned by the preprocess function.

    - Cannot store a matrix with the answer to all possible queries.

*/

#ifndef ARB_H
#define ARB_H

#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::directedS> Arb;
typedef boost::graph_traits<Arb>::vertex_descriptor Vertex;

/* Students must adapt this class for their needs; the innards of
   these objects are only accessed by the student's code */
class HeadStart {
  public:
    HeadStart(int num_vertices) 
        : n_vertices(num_vertices), d(num_vertices, -1), f(num_vertices, -1), cur_time(0) {}
    int n_vertices;
    std::vector<int> d; // discovery time 
    std::vector<int> f; // finishing time
    int cur_time; // used in dfs() function
};

#endif // #ifndef ARB_H
