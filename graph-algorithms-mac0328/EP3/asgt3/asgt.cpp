#include "asgt.h"

#include <utility> // for std::get
#include <tuple>
#include <vector>

#define BOOST_ALLOW_DEPRECATED_HEADERS // silence warnings
#include <boost/graph/adjacency_list.hpp>
#include <boost/optional.hpp>

#include "cycle.h"
#include "digraph.h"
#include "potential.h"

// Bibliotecas adicionadas
#include <cmath>
//#include <limits>
#include <utility>

#define LARGE_DOUBLE 1e18

/* The code in this template file is all "bogus". It just illustrates
 * how to return answers back to main.cpp. */

/* The following declarations shorten the bogus code below. Feel free
 * to change/drop them. */
using boost::add_edge;
using boost::num_vertices;
using boost::out_edges;
using boost::in_edges;
using std::vector;
using std::pair;

// Should take time O(nm)
std::tuple<bool,
           boost::optional<NegativeCycle>,
           boost::optional<FeasiblePotential>>
has_negative_cycle(Digraph &digraph)    
{
    // INICIALIZATION

    // Number of vertices
    int n = num_vertices(digraph);

    // Paths
    vector<vector<vector<Vertex>>> W = vector<vector<vector<Vertex>>>(n, vector<vector<Vertex>>(n, vector<Vertex>()));
    // Paths cost
    vector<vector<double>> d(n, vector<double>(n, LARGE_DOUBLE));
    
    W[0][n-1].push_back(n-1);
    d[0][n-1] = 0;

    vector<vector<Arc>> arcs(n);
    for(const auto& arc : make_iterator_range(edges(digraph)))
    {
        arcs[target(arc,digraph)].push_back(arc);
    }

    // BELLMAN-FORD ALGORITHM
    
    // Distance 0 til number of vertices in digraph
    for(int l=1; l<n; l++)
    {
        // For each vertex in the digraph
        for (const auto& v : boost::make_iterator_range(vertices(digraph)))
        {
            d[l][v] = d[l-1][v];
            W[l][v] = W[l-1][v];

            // For every edge pertences to \delta_{in}(v)
            for (const auto& e: arcs[v])
            {
                // source vertex
                Vertex u = boost::source(e, digraph);
                double cost = digraph[e].cost;

                if (d[l - 1][u] != LARGE_DOUBLE && d[l][v] > d[l - 1][u] + cost)
                {
                    d[l][v] = d[l - 1][u] + cost;
                    W[l][v] = W[l - 1][u];
                    W[l][v].push_back(v);
                }
            }

        }
    }

    // VERIFY NEGATIVE CYCLES

    vector<Vertex> cycle;
    for(const auto& v : boost::make_iterator_range(vertices(digraph)))
    {
        if(d[n-2][v] != d[n-1][v])
        {
            cycle = W[n-1][v];
            break;
        }
    }

    // FINAL RESPONSE

    if (!cycle.empty())
    {
        std::unordered_set<Vertex> seen;
        std::vector<Vertex> adjusted_cycle;
        
        for (auto it = cycle.rbegin(); it != cycle.rend(); ++it)
        {
            // Ignore the auxiliary vertex
            if ((int)*it == n-1) 
                continue;

            // Get vertex repetition to identify the cycle
            if (seen.count(*it))
            {
                // Get the first ocurrence of *it, and then remove all the vertices that occurs before this vertex 
                auto cycle_start = std::find(adjusted_cycle.begin(), adjusted_cycle.end(), *it);
                adjusted_cycle.erase(adjusted_cycle.begin(), cycle_start);
                break;
            }

            adjusted_cycle.push_back(*it);
            seen.insert(*it);
        }
        reverse(adjusted_cycle.begin(), adjusted_cycle.end());

        // Build Walk for NegativeCycle function
        // Inicialize with the first vertex of the walk  
        Walk negative_cycle_walk(digraph, adjusted_cycle.front());
        for (size_t i = 0; i < adjusted_cycle.size(); ++i)
        {
            // Add the arcs
            Vertex u = adjusted_cycle[i];
            Vertex v = adjusted_cycle[(i + 1) % adjusted_cycle.size()];

            auto edge_pair = out_edges(u, digraph);
            for (auto edge = edge_pair.first; edge != edge_pair.second; ++edge)
            {
                if (target(*edge, digraph) == v)
                {
                    negative_cycle_walk.extend(*edge);
                    break;
                }
            }
        }

        return {true, NegativeCycle(negative_cycle_walk), boost::none};
    }
    else
    {
        // Feasible potentials: y(v) <= y(u) + c(uv)
        // The distances calculated bt Bellman Ford algorithm also satisfies this inequation'
        return {false, boost::none, FeasiblePotential(digraph, d[n-1])};
    }

}

// Should take time O(n+m)
Digraph build_digraph(const Digraph& market)
{
    Digraph digraph(num_vertices(market)+1);

    // Iterating over the edges of the market graph
    for (const auto& arc: make_iterator_range(edges(market)))
    {
        Vertex source_vertex = boost::source(arc, market);
        Vertex target_vertex = boost::target(arc, market);

        double arc_cost = market[arc].cost;

        std::pair<Arc, bool> result = boost::add_edge(source_vertex, target_vertex, digraph);

        Arc new_edge = result.first;
        bool inserted = result.second;

        if (inserted)
        {
            digraph[new_edge].cost = -log(arc_cost);
        }
    }

    // For the case in which the digraph has more than one connected component
    for(const auto& v : boost::make_iterator_range(vertices(market)))
    {
        std::pair<Arc, bool> result = boost::add_edge(num_vertices(market), v, digraph);

        if(result.second)
        {
            digraph[result.first].cost = 0;
        }
    }

    return digraph;
}

// Should take time O(n+m)
// Traversed the cycle arcs
Loophole build_loophole(const NegativeCycle &negcycle,
                        const Digraph &aux_digraph,
                        const Digraph &market)
{

    //std::cout<<"LOOPHOLE\n";
    // Access the cycle from the NegativeCycle object
    // Using get() from Cycle base class
    const vector<Arc>& cycle_arcs = negcycle.get();

    // Create a Walk in the market graph
    Vertex init_vertex = cycle_arcs[0].m_source;
    Walk w(market, init_vertex);

    // For each arc in the negative cycle, extend the walk in the market graph
    for (size_t i = 0; i < cycle_arcs.size(); ++i)
    {
        const Arc& arc = cycle_arcs[i];
        const BundledArc& arc_data = boost::get(boost::edge_bundle, aux_digraph, arc);

        // Get the original cost of the arc
        double modified_cost = std::exp(-arc_data.cost);
        const_cast<BundledArc&>(arc_data).cost = modified_cost;

        w.extend(arc);
    }

    return Loophole(w);
}

// Should take time O(n)
// Just iterate throught the vertices
FeasibleMultiplier build_feasmult(const FeasiblePotential &feaspot,
                                  const Digraph &aux_digraph,
                                  const Digraph &market)
{
    //std::cout<<"FEASIBLE MULTIPLIERS\n";
    vector<double> z(num_vertices(market), 1.0);
    vector<double> y = feaspot.potential();

    int n = num_vertices(market);
    for(int i=0; i< n; i++)
    {
        z[i] = 1/exp(y[i]);
    }

    // encourage RVO
    return FeasibleMultiplier(market, z);
}
