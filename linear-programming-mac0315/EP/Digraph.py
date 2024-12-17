class Digraph:
    def __init__(self):
        self.n_vertices = 0
        self.m_edges = 0
        self.nodes = []
        self.edges = []
        self.root = 0
        self.tree_edges = []

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
            self.nodes[head].out_edges.append(edge)
            self.nodes[tail].in_edges.append(edge)
            self.nodes[head].all_edges.append(edge)
            self.nodes[tail].all_edges.append(edge)

            if is_basic:
                self.tree_edges.append(edge)

        # Lê o nó raiz
        self.root = int(input())-1

class Node:
    def __init__(self, i, demand):
        self.label = i
        self.y = float('inf')  # Inicializa o preço como infinito
        self.demand = demand
        self.out_edges = []
        self.in_edges = []
        self.all_edges = []
        self.depth = 0

    def edge_to_parent(self):
        if self.edge_to_parent.head == self:
            return self.edge_to_parent.tail
        return self.edge_to_parent.head

    def __repr__(self):  
        return f"Node(label={self.label+1}, demand={self.demand})"

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
            print(f"• {self.head+1} -> {self.tail+1} pertence à base com fluxo {self.flux}")
        else: 
            print(f"• {self.head+1} -> {self.tail+1} não pertence à base com fluxo {self.flux}")

# Função para calcular os preços potenciais (y)
# PARECE ESTAR FUNCIONANDO BEM
def calculate_potentials(digraph):
    digraph.nodes[digraph.root].y = 0

    for _ in range(digraph.n_vertices - 1):
        for edge in digraph.edges:
            if edge.is_basic: 
                # Relaxa no sentido da aresta, i.e., soma o custo
                new_y = digraph.nodes[edge.head].y + edge.cost
                if new_y < digraph.nodes[edge.tail].y:
                    digraph.nodes[edge.tail].y = new_y
            
                # Relaxa no sentido contrário da aresta, i.e., subtraí o custo
                new_y = digraph.nodes[edge.tail].y - edge.cost
                if new_y < digraph.nodes[edge.head].y:
                    digraph.nodes[edge.head].y = new_y

# Função para encontrar a aresta de entrada com base nos preços potenciais (y)
def find_entering_edge(digraph):
    min_cost = float('inf')
    entering_edge = None
    
    # Percorre as arestas para encontrar a aresta que vale a pena colocar na base
    for edge in digraph.edges:
        if edge.is_basic:
            continue

        # Se a aresta não está saturada
        # Para aresta u->v: y(u) + c(uv) < y(v) 
        if edge.flux < edge.capacity:  
            cost_reduced = digraph.nodes[edge.head].y + edge.cost - digraph.nodes[edge.tail].y
            if cost_reduced < min_cost:
                min_cost = cost_reduced
                entering_edge = edge
        # Aresta saturada
        # Para aresta u->v: y(u) + c(uv) > y(v)
        else:  
            cost_reduced = digraph.nodes[edge.head].y + edge.cost - digraph.nodes[edge.tail].y
            if cost_reduced > min_cost:
                min_cost = cost_reduced
                entering_edge = edge
    return entering_edge

# Função para encontrar o ciclo de base (todas as arestas exceto a aresta de entrada)
def find_base_cycle(digraph, entering_edge):
    # Vamos procurar um ciclo entre as arestas que já estão na base (fluxo definido)
    cycle_edges = []
    visited = [False] * digraph.n_vertices
    parent = [-1] * digraph.n_vertices

    def dfs_cycle(node):
        visited[node] = True
        print("olhando", node+1)
        for edge in digraph.nodes[node].all_edges:
            # Verifica se a aresta está na base (é uma aresta básica)
            if not edge.is_basic:
                continue

            if edge.head == node:
                neighbor = edge.tail
            else:
                neighbor = edge.head
            print("vizinho =", neighbor+1)
            
            # Caso 1: Se o vizinho ainda não foi visitado, seguimos com a busca
            if not visited[neighbor]:
                parent[neighbor] = node
                if dfs_cycle(neighbor):
                    return True

            # Caso 2: Se encontramos um ciclo, retornamos ele
            elif neighbor == entering_edge.tail:
                print("ENTROU AQ")
                print("PARENT", parent)
                print("VIS", visited)
                parent[neighbor] = node
                # O ciclo é formado, agora rastreie as arestas do ciclo
                cycle_node = entering_edge.tail
                while cycle_node != entering_edge.head:
                    print("cycle node", cycle_node)
                    print("oii")
                    print("parenttt", parent[cycle_node])
                    for edge in digraph.nodes[cycle_node].all_edges:
                        print("fluu", edge, edge.head, edge.tail)
                        if (edge.head == parent[cycle_node] or edge.tail == parent[cycle_node]) and edge.is_basic:
                            cycle_edges.append(edge) 
                            print("ADD", edge)
                            break
                    # cycle_edges.append(digraph.nodes[cycle_node].edge_to_parent())
                    cycle_node = parent[cycle_node]
                    print("NOVO NO", cycle_node)
                print("AA", cycle_edges)
                # return True
        print("PARENT", parent)
        print("VIS", visited)
        return False

    # Comece o DFS a partir do nó da aresta de entrada
    parent[entering_edge.head] = entering_edge.tail
    if dfs_cycle(entering_edge.head):
        return cycle_edges
    return []


# Função para encontrar o valor de alpha
def find_alpha(digraph, entering_edge):
    # Encontra o ciclo de base
    cycle_edges = find_base_cycle(digraph, entering_edge)

    print("CICLO", cycle_edges)
    
    same_direction_edges = []
    opposite_direction_edges = []
    
    visited = [False] * digraph.n_vertices

    def dfs(node):
        visited[node] = True
        for edge in digraph.nodes[node].all_edges:
            if not visited[edge.tail]:
                if edge.tail == entering_edge.head:
                    # Aresta no mesmo sentido que entering_edge
                    same_direction_edges.append(edge)
                elif edge.head == entering_edge.tail:
                    # Aresta no sentido contrário de entering_edge
                    opposite_direction_edges.append(edge)
                dfs(edge.tail)
    
    # Comece a DFS no nó do head do entering_edge
    dfs(entering_edge.head)
    
    # Determina o valor de alpha, com base nas arestas no ciclo
    min_alpha = float('inf')

    const = 1 if entering_edge.flux == entering_edge.capacity else -1

    limiting_edge = None

    # Verifique as arestas no ciclo para calcular o alpha
    for edge in cycle_edges:
        # Se estamos tentando adicionar uma aresta não saturada, somamos alpha nas de mesmo sentido e substraímos caso contrário
        if entering_edge.flux != entering_edge.capacity:
            if edge in same_direction_edges:
                available_capacity = edge.capacity - edge.flux
                min_alpha = min(min_alpha, available_capacity)
            elif edge in opposite_direction_edges:
                min_alpha = min(min_alpha, edge.flux)
        # Se estamos tentando adicionar uma aresta saturada, subtraímos alpha nas de mesmo sentido e somamos caso contrário
        else:
            if edge in same_direction_edges:
                min_alpha = min(min_alpha, edge.flux)
            elif edge in opposite_direction_edges:
                available_capacity = edge.capacity - edge.flux
                min_alpha = min(min_alpha, available_capacity)

        if limiting_edge is None or min_alpha == edge.flux or min_alpha == (edge.capacity - edge.flux):
            limiting_edge = edge

    # Agora, marque a aresta de saída (limiting_edge) como não pertencente à base
    if limiting_edge:
        entering_edge.is_basic = True
        limiting_edge.is_basic = False

    # Atualiza o fluxo das arestas
    for edge in cycle_edges:
        if edge in same_direction_edges:
            edge.flux += const * min_alpha
        elif edge in opposite_direction_edges:
            edge.flux -= const * min_alpha
    
    return min_alpha

# Função para rodar o algoritmo Simplex
def simplex_algorithm(digraph):
    # Iterações do algoritmo Simplex
    while True:
        # Calcula os preços potenciais para cada nó
        calculate_potentials(digraph)

    # # Para cada vértice no grafo
        # for v in digraph.nodes:
        #     print(f"Vértice {v.label+1} com demanda {v.demand} e potencial {v.y}")

        # Encontre a aresta de menor custo para aumentar o fluxo
        entering_edge = find_entering_edge(digraph)
        break
        if not entering_edge:
            break  # Se não encontrar mais arestas para aumentar o fluxo, a solução é ótima
        

        print("ARESTA DE ENTRADA", entering_edge)

        # Encontre o maior valor de alpha possível para a aresta de entrada
        alpha = find_alpha(digraph, entering_edge)

        # print("ALPHA", alpha)

        # for edge in digraph.edges:
        #     print(edge)
        
        #if alpha == 0:
        #    break  # Não há mais fluxo possível, a solução é ótima

    # Exibe os resultados
    for edge in digraph.edges:
        edge.final_print()

# Exemplo de uso do algoritmo Simplex:
G = Digraph()

# for u in range(G.n_vertices):
#     print(u)
#     for edge in G.nodes[u].all_edges:
#         print(edge)

simplex_algorithm(G)

# ## FUNÇÕES DO ROD
# def cycle(a: Node,b: Node):
#     ca = []
#     cb = []

#     while a.depth < b.depth:
#         ca.append(a)
#         a = a.edge_to_parent

#     while b.depth < a.depth:
#         cb.append(b)
#         b = b.edge_to_parent

#     while a!=b:
#         ca.append(a)
#         cb.append(b)
#         a = a.edge_to_parent
#         b = b.edge_to_parent