// ENTREGAR

#include "asgt.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

void biconnected_comp_visit(Infos& info, int u)
{
    info.color[u] = 1;
    info.d[u] = ++info.time;

    //std::cout << "d["<<u+1<<"] = ll["<<u+1<<"]" << " = " << info.d[u] << "\n";

    // iterate over outgoing arcs
    boost::graph_traits<Graph>::out_edge_iterator vectex_it, vectex_end;
    for (boost::tie(vectex_it, vectex_end) = boost::out_edges(u, info.G); vectex_it != vectex_end; ++vectex_it) 
    {
        Vertex v = boost::target(*vectex_it, info.G);
        bool ok = false;

        if(info.S_set.find(std::make_pair(u, v)) == info.S_set.end() && info.S_set.find(std::make_pair(v, u)) == info.S_set.end())
        {
            info.S.push(std::make_pair(u, v));
            //std::cout << "empilhando" << u << "-" << v << "\n";
            info.S_set.insert(std::make_pair(u, v));
            ok = true;
        }


        if(info.color[v] == 0)
        {
            info.pi[v] = u;
            biconnected_comp_visit(info, v);
        }
        else if((int)v != info.pi[u] && ok)
        {
            //std::cout << "v= " << v+1 << " já tinha sido visitado\n";
            ++info.nscc;

            std::pair<int, int> e;
            do
            {
                if (info.S.empty()) break;
                e = info.S.top();
                info.S.pop();
                //std::cout << "desempilhando " << e.first << "-" << e.second << "\n";

                Edge edge;
                bool found;
                boost::tie(edge, found) = boost::edge(e.first, e.second, info.G);
                if (found)
                {
                    info.G[edge].bcc = info.nscc;
                    //std::cout << "Atualizando bcc para a aresta " << e.first << "-" << e.second << " com valor " << info.G[edge].bcc << "\n";
                }

                //std::cout << "MUDANDO1 ll["<<u+1<<"]" << " = " << info.lowlink[u] << "\n";

            } while (e.first != (int)v); // Continue até encontrar a aresta que leva a v

            Edge edge;
            bool found;
            boost::tie(edge, found) = boost::edge(u, v, info.G);
            if (found)
            {
                info.G[edge].bcc = info.nscc;
                //std::cout << "Atualizando bcc para a aresta " << u << "-" << v << " com valor " << info.G[edge].bcc << "\n";
            }


        }
    } 

    info.color[u] = 2;
    info.f[u] = ++info.time;


    if(!info.S.empty())
    {
        ++info.nscc;
    }
    while(!info.S.empty())
    {
        Edge e;
        bool found;


        boost::tie(e, found) = boost::edge(info.S.top().first, info.S.top().second, info.G);
        //std::cout << "Atualizando bcc para a aresta " << info.S.top().first << "-" << info.S.top().second << " com valor " << info.G[e].bcc << "\n";

        info.S.pop();

        if(found)
        {
            info.G[e].bcc = info.nscc;
        }

    }
}

void biconnected_comp(Infos& info)
{
    boost::graph_traits<Graph>::vertex_iterator vertex_it, vertex_end;
    for (boost::tie(vertex_it, vertex_end) = boost::vertices(info.G); vertex_it != vertex_end; ++vertex_it)
    {
        Vertex u = *vertex_it;

        if(info.color[u] == 0)
        {
            info.pi[u] = -1;
            biconnected_comp_visit(info, u);
        }
    }   
}

// Must label all the edges of an input graph according to its biconnected components
void debugging_level_0(Infos& info)
{

}

void dfs_cutvertex(Infos& info, int u, int p)
{
    int tree_edges=0;
    info.color[u]=1;
    info.lowlink[u] = info.d[u] = ++info.time;
    bool is_cut_vertex=false;

    boost::graph_traits<Graph>::out_edge_iterator vectex_it, vectex_end;
    for (boost::tie(vectex_it, vectex_end) = boost::out_edges(u, info.G); vectex_it != vectex_end; ++vectex_it) 
    {
        Vertex v = boost::target(*vectex_it, info.G);

        // Dont't repeat same edges
        if(info.S_set.find(std::make_pair(u, v)) == info.S_set.end() && 
        info.S_set.find(std::make_pair(v, u)) == info.S_set.end())
        {
            info.S_set.insert(std::make_pair(u, v));
        }
        else
        {
            continue;    
        }


        if((int)v == u)
        {
            continue;
        }

        if(!info.color[v])
        {
            tree_edges++;
            dfs_cutvertex(info, v, u);

            // Just reach vertices that came after u
            // i.e, there is no back arc

            if(info.d[u] <= info.lowlink[v] && p!=-1)
            {
                info.G[u].cutvertex = true;
            }

            info.lowlink[u] = std::min(info.lowlink[u], info.lowlink[v]);

        }
        else{
            // i.e, v is an ancestor
            info.lowlink[u] = std::min(info.lowlink[u], info.d[v]);

            // The root children connects -> root isn't a cut vertex
            if (p == -1) {
                is_cut_vertex = true; 
            }
        }
    }

    info.color[u]=2;
    info.f[u] = ++info.time;

    if(p==-1)
    {
        info.G[u].cutvertex = (tree_edges > 1 && !is_cut_vertex);
    }

}

// Must fill the cutvertex field for each vertex correctly
void debugging_level_1(Infos& info)
{
    boost::graph_traits<Graph>::vertex_iterator vertex_it, vertex_end;
    for (boost::tie(vertex_it, vertex_end) = boost::vertices(info.G); vertex_it != vertex_end; ++vertex_it)
    {
        Vertex u = *vertex_it;

        if(info.color[u] == 0)
        {
            dfs_cutvertex(info, u, -1);
        }
    }   
}

// Every bridge must be a tree edge
void dfs_brigde(Infos& info, int u, int p)
{
    info.color[u]=1;
    info.lowlink[u] = info.d[u] = ++info.time;

    boost::graph_traits<Graph>::out_edge_iterator vectex_it, vectex_end;
    for (boost::tie(vectex_it, vectex_end) = boost::out_edges(u, info.G); vectex_it != vectex_end; ++vectex_it) 
    {
        Vertex v = boost::target(*vectex_it, info.G);
        if((int)v == u)
        {
            continue;
        }

        // Dont't repeat same edges
        if(info.S_set.find(std::make_pair(u, v)) == info.S_set.end() && 
        info.S_set.find(std::make_pair(v, u)) == info.S_set.end())
        {
            info.S_set.insert(std::make_pair(u, v));
        }
        else
        {
            continue;    
        }

        if(!info.color[v])
        {
            dfs_brigde(info, v, u);

            // Just reach vertices that came after u
            // i.e, there is no back arc
            if(info.d[u] < info.lowlink[v])
            {
                bool found;
                Edge edge;
                boost::tie(edge, found) = boost::edge(u, v, info.G);
                if (found)
                {
                    info.G[edge].bridge = true;
                }
            }

            info.lowlink[u] = std::min(info.lowlink[u], info.lowlink[v]);
        }
        else{
            // i.e, v is an ancestor
            info.lowlink[u] = std::min(info.lowlink[u], info.d[v]);
        }
    }
}

// Must fill the bridge field for each edge correctly
void debugging_level_2(Infos& info)
{
    boost::graph_traits<Graph>::vertex_iterator vertex_it, vertex_end;
    for (boost::tie(vertex_it, vertex_end) = boost::vertices(info.G); vertex_it != vertex_end; ++vertex_it)
    {
        Vertex u = *vertex_it;

        if(info.color[u] == 0)
        {
            dfs_brigde(info, u, -1);
        }
    }   
}

void compute_bcc (Graph &g, bool fill_cutvxs, bool fill_bridges)
{
    Infos info(boost::num_vertices(g), g);

    //biconnected_comp(info); 

    // debug mode 1
    if(fill_cutvxs)
    {
        debugging_level_1(info);
    }
    // debug mode 2
    else if(fill_bridges)
    {
        debugging_level_2(info);
    }
    // debug mode 0
    else
    {
        debugging_level_0(info);
    }
}