import networkx as nx
import matplotlib.pyplot as plt
import graphviz

class Digraph:
    def __init__(self):
        self.n_vertices = 0
        self.m_edges = 0
        self.nodes = []
        self.edges = []
        self.root = 0
        self.read_data()

    def read_data(self):
        info = input().split()
        self.n_vertices, self.m_edges = int(info[0]), int(info[1])

        # Leitura dos nós
        for u in range(self.n_vertices):
            demand = int(input())
            vertex = Node(u, demand)
            self.nodes.append(vertex)

        # Leitura das arestas
        for e in range(self.m_edges):
            info = input().split()
            tail, head, cost, capacity, flux, is_basic = int(info[0]), int(info[1]), int(info[2]), int(info[3]), int(info[4]), bool(int(info[5]))
            
            head-=1
            tail-=1
            
            edge = Edge(head, tail, capacity, cost, flux, is_basic)
            self.edges.append(edge)

            # Atualiza as arestas de saída e entrada para cada nó
            self.nodes[head].all_edges.append(edge)
            self.nodes[tail].all_edges.append(edge)

        # Lê o nó raiz
        self.root = int(input())-1

class Node:
    def __init__(self, i, demand):
        self.label = i
        self.y = float('inf') 
        self.demand = demand
        self.all_edges = []
        self.depth = 0

    def __repr__(self):  
        return f"Node(label={self.label+1}, demand={self.demand}, y={self.y})"

class Edge:
    def __init__(self, u, v, capacity, cost, flux, is_basic):
        self.head = u
        self.tail = v
        self.capacity = capacity
        self.cost = cost
        self.flux = flux
        self.is_basic = is_basic

    def __repr__(self):  
        return f"Edge(head={self.head+1}, tail={self.tail+1}, capacity={self.capacity}, cost={self.cost}, flux={self.flux}, is_basic={self.is_basic})"

    def final_print(self):
        if self.is_basic:
            print(f"• {self.tail+1} -> {self.head+1} pertence à base com fluxo {self.flux}")
        else: 
            print(f"• {self.tail+1} -> {self.head+1} não pertence à base com fluxo {self.flux}")


# Função para calcular os preços potenciais (y)
def calculate_potentials(digraph: Digraph):
    for u in range(digraph.n_vertices):
        digraph.nodes[u].y = float('inf')

    # O potencial do nó raiz é 0
    digraph.nodes[digraph.root].y = 0

    # Listas para armazenar os forward e backward arcs
    forward_edges = []
    backward_edges = []

    visited = [False] * digraph.n_vertices
    
    def bfs_classify_edges(digraph: Digraph):
        visited[digraph.root] = True
        stack = [digraph.root]

        while len(stack) > 0:

            node = stack.pop()
            
            for edge in digraph.nodes[node].all_edges:
                if edge in forward_edges or edge in backward_edges:
                    continue 

                if edge.tail == node:
                    if edge.is_basic:
                        forward_edges.append(edge)  
                        if not visited[edge.head]:
                            stack.append(edge.head)
                            visited[edge.head] = True
                elif edge.head == node:
                    if edge.is_basic:
                        backward_edges.append(edge)  
                        if not visited[edge.tail]:
                            stack.append(edge.tail)
                            visited[edge.tail] = True

    bfs_classify_edges(digraph)


    visited = [False] * digraph.n_vertices

    # Calcula os potencials/distâncias de cada vértice levando em consideração apenas arcos da árvore
    def bfs_calc_potentials(digraph: Digraph):
        stack = [digraph.root]
        visited[digraph.root] = True
        while len(stack) > 0:

            node = stack.pop()

            for edge in digraph.nodes[node].all_edges:
                if edge.is_basic:  
                    
                    if edge in forward_edges: 
                        if digraph.nodes[edge.tail].y == float('inf'):
                            continue
                        if digraph.nodes[edge.head].y == float('inf') or digraph.nodes[edge.tail].y + edge.cost < digraph.nodes[edge.head].y:
                            digraph.nodes[edge.head].y = digraph.nodes[edge.tail].y + edge.cost
                    else:  
                        if digraph.nodes[edge.head].y == float('inf'):
                            continue
                        if digraph.nodes[edge.head].y == float('inf') or digraph.nodes[edge.head].y + edge.cost < digraph.nodes[edge.tail].y:
                            digraph.nodes[edge.tail].y = digraph.nodes[edge.head].y - edge.cost

                    if not visited[edge.tail]:
                        visited[edge.tail] = True
                        stack.append(edge.tail)
                    if not visited[edge.head]:
                        visited[edge.head] = True
                        stack.append(edge.head)

    bfs_calc_potentials(digraph)

# Função para encontrar o arco de entrada com base nos potenciais (y)
def find_entering_edge(digraph: Digraph):
    
    # Percorre as arestas para encontrar a aresta que vale a pena colocar na base
    for edge in digraph.edges:
        if edge.is_basic:
            continue

        # Se a aresta não está saturada
        # Para aresta u->v: y(u) + c(uv) < y(v) 
        if edge.flux < edge.capacity:  
            if digraph.nodes[edge.tail].y + edge.cost < digraph.nodes[edge.head].y: 
                return edge
        # Aresta saturada
        # Para aresta u->v: y(u) + c(uv) > y(v)
        else:  
            if digraph.nodes[edge.tail].y + edge.cost > digraph.nodes[edge.head].y: 
                return edge

    return None

# Função para encontrar o ciclo de base (todas os arcos exceto o arco de entrada)
def find_base_cycle(digraph: Digraph, entering_edge: Edge):
    cycle_edges = []
    visited = [False] * digraph.n_vertices
    parent = [-1] * digraph.n_vertices

    def dfs_cycle(node: Node):
        visited[node] = True
        for edge in digraph.nodes[node].all_edges:
            if not edge.is_basic:
                continue

            if edge.head == node:
                neighbor = edge.tail
            else:
                neighbor = edge.head
            
            if not visited[neighbor]:
                parent[neighbor] = node
                dfs_cycle(neighbor)

    parent[entering_edge.head] = entering_edge.tail

    dfs_cycle(entering_edge.head)

    # Tendo todos os parents, pegar apenas as arestas do ciclo
    cycle_node = entering_edge.tail
    while cycle_node != entering_edge.head:

        for edge in digraph.nodes[cycle_node].all_edges:

            if (edge.head == parent[cycle_node] or edge.tail == parent[cycle_node]) and edge.is_basic:
                cycle_edges.append(edge) 
                break

        cycle_node = parent[cycle_node]

    cycle_edges.append(entering_edge)

    return cycle_edges

# Função para encontrar o valor de alpha
def find_alpha(digraph: Digraph, entering_edge: Edge):
    cycle_edges = find_base_cycle(digraph, entering_edge)

    same_direction_edges = [entering_edge]
    opposite_direction_edges = []
    
    visited = [False] * digraph.n_vertices

    def dfs(node: Node, head: Node, tail: Node):
        visited[node] = True

        for edge in digraph.nodes[node].all_edges:
            if edge == entering_edge or edge in opposite_direction_edges or edge in same_direction_edges or edge not in cycle_edges:
                continue
            
            if edge.head == head:
                opposite_direction_edges.append(edge)

                if not visited[edge.tail]:
                    dfs(edge.tail, edge.tail, edge.head)
            elif edge.tail == head:
                same_direction_edges.append(edge)

                if not visited[edge.head]:
                    dfs(edge.head, edge.head, edge.tail)
    
    dfs(entering_edge.head, entering_edge.head, entering_edge.tail)
    
    min_alpha = float('inf')
    limiting_edge = Edge(-1, -1, -1, -1, -1, 0)

    def deal_alpha(min_alpha: float, available_capacity: int, limiting_edge: Edge, new_edge: Edge):
        if available_capacity < min_alpha:
            min_alpha = available_capacity
            limiting_edge = new_edge
        elif available_capacity == min_alpha and limiting_edge.is_basic and not new_edge.is_basic:
            limiting_edge = new_edge

        return min_alpha, limiting_edge

    # Verifique as arestas no ciclo para calcular o alpha
    for edge in cycle_edges:
        # Se estamos tentando adicionar uma aresta não saturada, somamos alpha nas de mesmo sentido e substraímos caso contrário
        if entering_edge.flux < entering_edge.capacity:
            if edge in same_direction_edges:
                available_capacity = edge.capacity - edge.flux
                min_alpha, limiting_edge = deal_alpha(min_alpha, available_capacity, limiting_edge, edge)

            elif edge in opposite_direction_edges:
                min_alpha, limiting_edge = deal_alpha(min_alpha, edge.flux, limiting_edge, edge)

        # Se estamos tentando adicionar uma aresta saturada, subtraímos alpha nas de mesmo sentido e somamos caso contrário
        else:
            if edge in same_direction_edges:
                min_alpha, limiting_edge = deal_alpha(min_alpha, edge.flux, limiting_edge, edge)

            elif edge in opposite_direction_edges:
                available_capacity = edge.capacity - edge.flux
                min_alpha, limiting_edge =deal_alpha(min_alpha, available_capacity, limiting_edge, edge)


    # O arco de entrada entra na base, e o arco de saída (que limitou o alpha), sai da base
    if limiting_edge:
        entering_edge.is_basic = True
        limiting_edge.is_basic = False

    const = 1 if entering_edge.flux != entering_edge.capacity else -1

    # Atualiza o fluxo das arestas
    for edge in cycle_edges:
        if edge in same_direction_edges:
            edge.flux += const * min_alpha
        elif edge in opposite_direction_edges:
            edge.flux -= const * min_alpha
    
    return min_alpha

# Função para rodar o algoritmo Simplex
def simplex_algorithm(digraph: Digraph):

    while True:
        # Calcula os potenciais para cada vértice
        calculate_potentials(digraph)

        # Encontra arco que vale a pena colocar na base
        entering_edge = find_entering_edge(digraph)
        if not entering_edge:
            break  # Se não encontrar mais arcos, a solução é ótima
        
        find_alpha(digraph, entering_edge)

    print("------------------------------------------")
    for edge in digraph.edges:
        edge.final_print()
    print("\n")

    total_cost=0

    for edge in digraph.edges:
        total_cost += edge.cost*edge.flux

    print(f"Custo total da rede = {total_cost}")
    print("------------------------------------------")

def gerar_grafo_latex(digraph: Digraph):
    # Criar um grafo com Graphviz
    graph = graphviz.Digraph(format='png', engine='dot')
    graph.attr(dpi='300', rankdir='LR', nodesep='1', ranksep='1', splines='true') 

    # Adicionar os nós ao grafo
    for node in digraph.nodes:
        label = f'{node.demand}'  # Adicionando a demanda do nó
        graph.node(str(node.label), label=label, shape='circle')

    # Adicionar as arestas ao grafo
    for edge in digraph.edges:
        label = f'{edge.flux}'  
        # Aresta básica em azul
        if edge.is_basic:
            graph.edge(str(edge.tail), str(edge.head), label=label, color='blue', penwidth='2')  
        # Aresta saturada em vermelho
        elif edge.flux == edge.capacity:
            graph.edge(str(edge.tail), str(edge.head), label=label, color='red', penwidth='2')  
        # Aresta com fluxo 0 em cinza
        else:
            graph.edge(str(edge.tail), str(edge.head), label=label, color='gray')  

    # Salvar o arquivo de imagem .png
    image_path = "resultado"
    graph.render(image_path, cleanup=True)  # Gera o grafo e o salva como 'grafo.png'

    print(f"Imagem gerada com sucesso: {image_path}.png")

def main():
    # Realiza a leitura do digrafo
    D = Digraph()

    # Executa o algoritmo do simplex em fluxo de rede
    simplex_algorithm(D)

    # Gera png do resultado final da rede
    gerar_grafo_latex(D)

if __name__ == "__main__":
    main()