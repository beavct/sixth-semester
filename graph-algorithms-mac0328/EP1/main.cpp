#include <iostream>

#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::directedS> Digraph;
typedef boost::graph_traits<Digraph>::vertex_descriptor Vertex;

class Aux_Digraph {
    public:
        Aux_Digraph(int debug, int num_vertices, int num_arcs)
            : digraph(2*num_vertices), n_vertices(num_vertices), m_arcs(num_arcs), debug_mode(debug), time(0) {}
        Digraph digraph;
        int n_vertices;
        int m_arcs;
        int debug_mode;
        int time;
};

/*

0
2 2
1 2 
2 -1


-2: 3
-1: 2
1: 0
2: 1


*/

int var2index(int var)
{
    if(var > 0)
        return (var-1)*2;

    return (-2*var)-1;
}

int index2var(int index)
{
    if(index % 2 == 1)
        return -1*(index+1)/2;

    return (index/2)+1;
}


Aux_Digraph read_digraph(std::istream& in)
{
    int aux_debug, aux_vars, aux_clauses;
    std::cin >> aux_debug >> aux_vars >> aux_clauses;

    Aux_Digraph dig(aux_debug, 2*aux_vars, 2*aux_clauses);

    for(int i=0; i<aux_clauses; i++)
    {
        int u, v;
        std::cin >> u >> v;

        //std:: cout << u << " " << v << "\n";
//
        //std::cout << var2index(-1*u) << " -> " << var2index(v) << "\n";
        //std::cout << var2index(-1*v) << " -> " << var2index(u) << "\n";

        boost::add_edge(var2index(-1*u),var2index(v),dig.digraph);
        boost::add_edge(var2index(-1*v),var2index(u),dig.digraph);
    }


    return dig;
}


// Debugging Level 2
void digraph_construction(const Aux_Digraph& dig)
{
    std::cout << dig.n_vertices << " " << dig.m_arcs << "\n";

    // Iterar sobre todos os vértices
    boost::graph_traits<Digraph>::vertex_iterator vertex_it, vertex_end;

    for (boost::tie(vertex_it, vertex_end) = boost::vertices(dig.digraph); vertex_it != vertex_end; ++vertex_it)
    {
        Vertex u = *vertex_it;

        // Iterar sobre os arcos (arestas de saída) do vértice atual
        boost::graph_traits<Digraph>::out_edge_iterator out_edge_it, out_edge_end;
        for (boost::tie(out_edge_it, out_edge_end) = boost::out_edges(u, dig.digraph); out_edge_it != out_edge_end; ++out_edge_it)
        {
            Vertex v = boost::target(*out_edge_it, dig.digraph);

            std::cout << index2var(u) << " " << index2var(v) << "\n";
        }
    }
}



int main(int argc, char** argv)
{
    Aux_Digraph aux_dig = read_digraph(std::cin);

    digraph_construction(aux_dig);

    return EXIT_SUCCESS;
}