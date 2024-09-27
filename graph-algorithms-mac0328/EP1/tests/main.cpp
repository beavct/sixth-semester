#include <iostream>
#include <vector>
#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

typedef boost::adjacency_list<boost::vecS,
                              boost::vecS,
                              boost::directedS> Digraph;
typedef boost::graph_traits<Digraph>::vertex_descriptor Vertex;

class Geral_Data {
    public:
        Geral_Data(int debug, int num_vertices, int num_arcs)
            : digraph(num_vertices), digraph_minus(num_vertices), f_vertices(num_vertices), strong_cmp(num_vertices, -1), boolean_values(num_vertices/2), n_vertices(num_vertices), m_arcs(num_arcs), debug_mode(debug), time(0), nscc(0) {}
        Digraph digraph;
        Digraph digraph_minus;
        std::vector<int> f_vertices;
        std::vector<int> strong_cmp;
        std::vector<int> boolean_values;
        int n_vertices;
        int m_arcs;
        int debug_mode;
        int time;
        int nscc;
};

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

Geral_Data read_digraph(std::istream& in)
{
    int aux_debug, aux_vars, aux_clauses;
    std::cin >> aux_debug >> aux_vars >> aux_clauses;

    Geral_Data dig(aux_debug, 2*aux_vars, 2*aux_clauses);

    for(int i=0; i<aux_clauses; i++)
    {
        int u, v;
        std::cin >> u >> v;

        // Compute D
        boost::add_edge(var2index(-1*u),var2index(v),dig.digraph);
        boost::add_edge(var2index(-1*v),var2index(u),dig.digraph);

        // Compute D^{-1}
        boost::add_edge(var2index(v),var2index(-1*u),dig.digraph_minus);
        boost::add_edge(var2index(u),var2index(-1*v),dig.digraph_minus);
    }


    return dig;
}

void normal_dfs(Geral_Data& dig, const Vertex& src, std::vector<bool>& visited)
{
    visited[src]=true;

    // iterate over outgoing arcs
    boost::graph_traits<Digraph>::out_edge_iterator vectex_it, vectex_end;
    for (boost::tie(vectex_it, vectex_end) = boost::out_edges(src, dig.digraph); vectex_it != vectex_end; ++vectex_it) 
    {
        Vertex u = boost::target(*vectex_it, dig.digraph);

        if(!visited[u])
        {
            normal_dfs(dig, u, visited);
        }
    }
        
    dig.f_vertices.push_back(src);
}

void stack_dfs(Geral_Data& dig, const Vertex& src)
{
    dig.strong_cmp[src]=dig.nscc;

    // iterate over outgoing arcs
    boost::graph_traits<Digraph>::out_edge_iterator vectex_it, vectex_end;
    for (boost::tie(vectex_it, vectex_end) = boost::out_edges(src, dig.digraph_minus); vectex_it != vectex_end; ++vectex_it) 
    {
        Vertex u = boost::target(*vectex_it, dig.digraph_minus);

        if(dig.strong_cmp[u] == -1)
            stack_dfs(dig, u);
    }       
}

bool path_dfs(Geral_Data& dig, const Vertex& src, const Vertex& dst, std::vector<bool>& visited, std::vector<int>& path_aux)
{
    visited[src]=true;

    path_aux.push_back(src);

    if(src == dst)
    {
        return true;
    }


    // iterate over outgoing arcs
    boost::graph_traits<Digraph>::out_edge_iterator vectex_it, vectex_end;
    for (boost::tie(vectex_it, vectex_end) = boost::out_edges(src, dig.digraph); vectex_it != vectex_end; ++vectex_it) 
    {
        Vertex u = boost::target(*vectex_it, dig.digraph);

        if(!visited[u])
        {
            if(path_dfs(dig, u, dst, visited, path_aux))
            {
                return true;
            }
        }
    }

    path_aux.pop_back();
    return false;
}


// O(n+m)
void kosaraju_algorithm(Geral_Data& dig)
{
    dig.f_vertices.clear();
    std::vector<bool> visited(dig.n_vertices, false);

    for(int i=0; i<dig.n_vertices; i++)
    {
        if(!visited[i])
            normal_dfs(dig, i, visited);
    }

    for(int i=0; i<dig.n_vertices; i++)
    {
        int v = dig.f_vertices[dig.n_vertices - i -1];

        if(dig.strong_cmp[v] == -1){
            dig.nscc++;
            stack_dfs(dig, v);       
        }
    }

}

void print_path(Geral_Data& dig, int var)
{
    std::vector<bool> visited_direct(dig.n_vertices, false);
    std::vector<bool> visited_inverse(dig.n_vertices, false);
    
    std::vector<int> path_going;
    std::vector<int> path_back;

    path_dfs(dig, var2index(var), var2index(-1*var), visited_direct, path_going);
    path_dfs(dig, var2index(-1*var), var2index(var), visited_inverse, path_back);

    std::cout << path_going.size()-1 << " ";
    for(auto vertex : path_going)
    {
        std::cout << index2var(vertex) << " ";
    }
    std::cout << "\n";

    std::cout << path_back.size()-1 << " ";
    for(auto vertex : path_back)
    {
        std::cout << index2var(vertex) << " ";
    }
    std::cout << "\n";
}

// Debugging Level 0
void satisfiability(Geral_Data& dig)
{
    kosaraju_algorithm(dig);

    bool sat=true;
    int var=-1;

    // If a and b are in the same strong component, then a->b and b->a
    for(int i=1; i<=dig.n_vertices/2; i++)
    {
        int u = var2index(i);
        int v = var2index(-1*i);

        if(dig.strong_cmp[u] == dig.strong_cmp[v])
        {
            sat=false;
            var=i;
            break;
        }
    }

    if(sat) 
    {

        // Assign the right value for each variable
        for(int i = 0; i < dig.n_vertices; i+=2)
        {
            int u = i;
            int v = i+1;

            if(dig.strong_cmp[u] < dig.strong_cmp[v])
            {
                dig.boolean_values[u/2] = 0;
            }
            else
            {
                dig.boolean_values[u/2] = 1;
            }
        }

        std::cout << "YES\n";
        for(int i = 0; i < dig.n_vertices / 2; i++) {
            std::cout << dig.boolean_values[i] << " ";
        }
        std::cout << "\n";
    }

    else
    {
        std::cout << "NO\n";
        std::cout << var << "\n";
        print_path(dig, var);
    }
}

// Debugging Level 1
void strong_components(Geral_Data& dig)
{
    kosaraju_algorithm(dig);

    // isso daqui ta errado, ler melhor depois
    for(int i=0; i<dig.n_vertices; i+=2)
    {
        std::cout << dig.strong_cmp[i] << " ";
    }
    for(int i=1; i<dig.n_vertices; i+=2)
    {
        std::cout << dig.strong_cmp[i] << " ";
    }
    std::cout << "\n";
}

// Debugging Level 2
void digraph_construction(const Geral_Data& dig)
{
    std::cout << dig.n_vertices << " " << dig.m_arcs << "\n";

    boost::graph_traits<Digraph>::vertex_iterator vertex_it, vertex_end;

    for (boost::tie(vertex_it, vertex_end) = boost::vertices(dig.digraph); vertex_it != vertex_end; ++vertex_it)
    {
        Vertex u = *vertex_it;

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
    Geral_Data aux_dig = read_digraph(std::cin);

    if(aux_dig.debug_mode==0)
    {
        satisfiability(aux_dig);
    }
    else if(aux_dig.debug_mode==1)
    {
        strong_components(aux_dig);
    }
    else if(aux_dig.debug_mode==2)
    {
        digraph_construction(aux_dig);
    }

    return EXIT_SUCCESS;
}