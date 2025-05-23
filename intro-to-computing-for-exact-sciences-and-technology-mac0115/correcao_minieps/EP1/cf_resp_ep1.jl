# Função auxiliar para resolver o problema das Torres de Hanoi
function hanoi_rec(n::Int64, dep::Int64, origem::String, auxiliar::String, destino::String) :: Int64
    if n <= 0
        return 0
    end
    
    movimentos = 0
    
    # Resolver o subproblema de mover n-1 discos do pino de origem para o pino auxiliar
    movimentos += hanoi_rec(n - 1, dep, origem, destino, auxiliar)
    
    # Mover o disco n do pino de origem para o pino destino
    movimentos += 1
    
    if dep == 1
        println("Mova o disco $n do pino $origem para o pino $destino")
    end
    
    # Resolver o subproblema de mover n-1 discos do pino auxiliar para o pino destino
    movimentos += hanoi_rec(n - 1, dep, auxiliar, origem, destino)
    
    return movimentos
end

# Função principal para iniciar o cálculo das Torres de Hanoi
function hanoi(n::Int64, dep::Int64) :: Nothing
    movs = hanoi_rec(n, dep, "A", "B", "C")

    if movs == 0
        println("Não foi preciso nenhum movimento")
    elseif movs == 1
        println("Foi preciso $movs movimento")
    else
        println("Foram precisos $movs movimentos")
    end
end

#=
    Chamada da função para testes
    No terminal basta digitar 
    > julia cf_resp_ep1.jl <n> <dep>
    Sendo n um número natural e dep 0 ou 1
=#
n=parse(Int64,ARGS[1])
dep=parse(Int64,ARGS[2])
hanoi(n,dep)
