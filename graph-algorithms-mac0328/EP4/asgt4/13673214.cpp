#include <iostream>

#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

#include <vector>
#include <utility>
#include <queue>
#include <set>

// DEFINITION OF STRUCTURES

struct BundledVertex
{
     
};

struct BundledArc
{
  int capacity;
  int order;
  int current_flow = 0; // Certainly a feasible flow
  bool foward = true; // If it is false, the arc is backward
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
            : digraph(num_vertices), arcs_in_order(num_arcs), n_vertices(num_vertices), m_arcs(num_arcs), source(source), target(target) {} 
        Digraph digraph;
        std::vector<Arc> arcs_in_order;
        int n_vertices;
        int m_arcs;
        int source;
        int target;
};

int get_val_f(Geral_Data &data)
{
    int val = 0;
    int target = data.target;

    for (const auto& e : boost::make_iterator_range(edges(data.digraph)))
    {
        int u = boost::source(e, data.digraph);
        int v = boost::target(e, data.digraph);

        if(u == target)
        {
            val-=data.digraph[e].current_flow;
        }
        else if(v == target)
        {
            val+=data.digraph[e].current_flow;
        }
    }

    return val;
}

void print_description_residual_capacities(Geral_Data &data, Digraph &residual_digrah)
{
    for(Arc e : data.arcs_in_order)
    {
        Vertex u = boost::source(e, data.digraph);
        Vertex v = boost::target(e, data.digraph);

        std::pair<Arc, bool> foward = boost::edge(u, v, residual_digrah);
        std::pair<Arc, bool> backward = boost::edge(v, u, residual_digrah);

        std::cout << residual_digrah[foward.first].capacity << " ";
        std::cout << residual_digrah[backward.first].capacity << "\n";
    }
}

// TEM QUE TERMINAR
void print_end_of_edmonds_karp(Geral_Data &data, std::set<int>S){

    std::cout << 1 << " " << get_val_f(data) << " "<< S.size() << "\n";
    for (const int& vertex : S)
    {
        std::cout << vertex+1 << " ";
    }

    std::cout << "\n";
}

void print_non_end_of_edmonds_karp(Digraph &residual_digraph, std::vector<std::pair<int,int>> path, int eps)
{
    std::cout << "0 " << eps << " " << path.size() << "\n"; 
    for(std::pair<int,int> e : path)
    {
        std::pair<Arc, bool> result = boost::edge(e.first, e.second, residual_digraph);

        std::cout << residual_digraph[result.first].order << " ";
    }
    std::cout << "\n";
}

void built_residual_digraph_t(Geral_Data &data, Digraph &residual_digraph)
{
    residual_digraph.clear();
    residual_digraph = Digraph(data.n_vertices);

    // D_^   
    for (const auto& e : boost::make_iterator_range(edges(data.digraph)))
    {
        Vertex u = boost::source(e, data.digraph);
        Vertex v = boost::target(e, data.digraph);

        // Foward arcs
        // If the edge is not saturated, then it must be added to the residual digraph
        if(data.digraph[e].capacity >= data.digraph[e].current_flow)
        {
            std::pair<Arc, bool> result = boost::add_edge(u, v, residual_digraph);

            if(result.second)
            {
                // The residual capacity
                residual_digraph[result.first].capacity = data.digraph[e].capacity - data.digraph[e].current_flow;

                residual_digraph[result.first].order = data.digraph[e].order;
            }
        }

        // Backward arcs => if it has positive flow
        std::pair<Arc, bool> result = boost::add_edge(v, u, residual_digraph);

        if (result.second)
        {
            // The residual capacity
            residual_digraph[result.first].capacity = data.digraph[e].current_flow;
            residual_digraph[result.first].foward = false;

            residual_digraph[result.first].order = -data.digraph[e].order;
        }
    }

    print_description_residual_capacities(data, residual_digraph);
}

void bfs_augmenting_path(Digraph &digraph, int source, int target, std::vector<int> &pred, std::set<int> &S)
{
    std::vector<bool> visited(boost::num_vertices(digraph), false);
    std::queue<int> q;

    // Start BFS from the source
    visited[source] = true;
    q.push(source);
    S.insert(source);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        // Explore all outgoing edges from u
        boost::graph_traits<Digraph>::out_edge_iterator edge_it, edge_end;
        for (boost::tie(edge_it, edge_end) = boost::out_edges(u, digraph); edge_it != edge_end; ++edge_it)
        {
            Vertex v = boost::target(*edge_it, digraph);

            // Get arc information
            std::pair<Arc, bool> result = boost::edge(u, v, digraph);

            if(result.second)
            {
                bool saturated_arc = digraph[result.first].capacity <= digraph[result.first].current_flow;
                bool positive_cap = digraph[result.first].capacity > 0;

                // Only visit unvisited and non-saturated arcs
                if (!visited[v] && !saturated_arc && (positive_cap))
                {
                    visited[v] = true;
                    q.push(v);
                    S.insert(v);

                    // Update pred[v] = u
                    pred[v] = u;
                }
            }
        }
    }

    // If we finish and didn't find the target, pred[target] == -1
}

// Runs in time O((n+m)nm)
// Ford-Fulkerson algorithm + shortes st-augmenting path
// In the end of lecture 25
void edmonds_karp(Geral_Data &data)
{
    std::vector<bool> visited(data.n_vertices);
    std::vector<int> pred(data.n_vertices, 0);
    Digraph residual_digraph;
    std::set<int> S;

    do
    {   
        built_residual_digraph_t(data, residual_digraph);

        // Get a shortest st-path in the residual digraph D_f
        S.clear();
        fill(pred.begin(), pred.end(), -1);
        bfs_augmenting_path(residual_digraph, data.source, data.target, pred, S);

        if(S.find(data.target) != S.end())
        {
            // Get the max. value for eps
            int eps = INT32_MAX;
            std::vector<std::pair<int,int>> path;
            for(int v = data.target; v != data.source; v = pred[v])
            {
                int u = pred[v];
                std::pair<Arc, bool> result = boost::edge(u, v, residual_digraph);
                if (result.second) 
                {
                    eps = std::min(eps, residual_digraph[result.first].capacity - residual_digraph[result.first].current_flow);
                }

                path.push_back({u,v});
            }

            std::reverse(path.begin(), path.end());

            print_non_end_of_edmonds_karp(residual_digraph, path, eps);

            // Update flow in arcs that are traversed by the st-path
            for(int v = data.target; v != data.source; v = pred[v])
            {
                int u = pred[v];
                std::pair<Arc, bool> result1 = boost::edge(u, v, residual_digraph);
                if (result1.second) 
                {
                    if(residual_digraph[result1.first].foward)
                    {
                        std::pair<Arc, bool> result2 = boost::edge(u, v, data.digraph);
                        if(result2.second)
                        {
                            data.digraph[result2.first].current_flow += eps; 
                        }
                    }
                    else
                    {
                        std::pair<Arc, bool> result2 = boost::edge(v, u, data.digraph);
                        if(result2.second)
                        {
                            data.digraph[result2.first].current_flow -= eps; 
                        }
                    }
                }
            }

        }
        else
        {
            print_end_of_edmonds_karp(data, S);
            break;
        }
        

    } while (pred[data.target] != -1);

}

// Read digraph from input
Geral_Data read_digraph(std::istream& in)
{
    int n, m;
    std::cin >> n >> m ;

    int source, target;
    std::cin >> source >> target;

    Geral_Data data(n, m, --source, --target); 

    for(int i=0; i<m; i++)
    {
        int u, v, c;
        std::cin >> u >> v >> c;


        std::pair<Arc, bool> result = boost::add_edge(--u, --v, data.digraph);
        if(result.second)
        {
            Arc arc = result.first;

            data.arcs_in_order[i] = arc;
            data.digraph[arc].capacity=c;
            data.digraph[arc].order=i+1;
        }
    }


    return data;
}

int main(int argc, char** argv)
{
    Geral_Data data = read_digraph(std::cin);

    edmonds_karp(data);

    return EXIT_SUCCESS;
}