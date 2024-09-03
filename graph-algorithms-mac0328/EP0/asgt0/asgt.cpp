/* This is the main file that the students must work on to submit; the
 * other one is arb.h
 */

/*
  - Must be submitted
*/

#include "asgt.h"

Arb read_arb(std::istream& in){
  int num_vertices;
  std::cin >> num_vertices;

  Arb arb(num_vertices);

  int num_arcs=num_vertices-1;
  while(num_arcs--){
    int u, v;
    std::cin >> u >> v;

    boost::add_edge(--u,--v,arb);
  }

  return arb;
}

void dfs(const Arb& arb, const Vertex& src, HeadStart& data){
  data.d[src] = ++data.cur_time;

  // iterate over outgoing arcs
  boost::graph_traits<Arb>::out_edge_iterator vectex_it, vectex_end;
  for (boost::tie(vectex_it, vectex_end) = boost::out_edges(src, arb); vectex_it != vectex_end; ++vectex_it) {
      Vertex u = boost::target(*vectex_it, arb);
      dfs(arb, u, data);
  }
    
    data.f[src] = ++data.cur_time;
}

HeadStart preprocess (Arb &arb, const Vertex& root){
  int num_vertices = boost::num_vertices(arb);


  HeadStart hs(num_vertices);

  dfs(arb, root, hs);

  return hs;
}

bool is_ancestor (const Vertex& u, const Vertex& v, const HeadStart& data){
  return (data.d[v]>=data.d[u] && data.f[v]<=data.f[u]);
}
