#include <iostream>
#include <vector>
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

// DEFINITION OF STRUCTURES

struct BundledVertex
{

};

struct BundledArc
{
  int capacity;
  int order;
};

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::directedS,
                              BundledVertex, 
                              BundledArc> Digraph;
typedef boost::graph_traits<Digraph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Digraph>::edge_descriptor Arc;

class Geral_Data {
    public:
        Geral_Data(int num_vertices, int num_arcs, int source, int target)
            : digraph(num_vertices), n_vertices(num_vertices), m_arcs(num_arcs), source(source), target(target) {}
        Digraph digraph;
        int n_vertices;
        int m_arcs;
        int source;
        int target;
};

// READ DIGRAPH FROM INPUT
Geral_Data read_digraph(std::istream& in)
{
    int n, m;
    std::cin >> n >> m ;

    int source, target;
    std::cin >> source >> target;

    Geral_Data data(n, m, source, target); 

    for(int i=0; i<m; i++)
    {
        int u, v, c;
        std::cin >> u >> v >> c;


        std::pair<Arc, bool> result = boost::add_edge(--u, --v, data.digraph);
        if(bool bool_ret = result.second)
        {
            Arc arc = result.first;
            data.digraph[arc].capacity=c;
            data.digraph[arc].order=i+1;
        }
    }


    return data;
}

int main(int argc, char** argv)
{
    Geral_Data data = read_digraph(std::cin);

    return EXIT_SUCCESS;
}