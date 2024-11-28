function merge(lista1:: Vector{Float64}, lista2:: Vector{Float64}) :: Vector{Float64}
    ret =  Vector{Float64}()

    for elem in lista1
        if elem in lista2 && !(elem in ret)
            push!(ret, elem)
        end
    end

    return ret
end

# Nenhum elemento em comum
#=
lista1 = [-121.1, 34.5, 56.8]
lista2 = [0.3, 45.6, 98,7]
=#

# Todos os elementos em comum
#=
lista1 = [2, 3.4, 5.6, 7, 122]
lista2 = [2, 3.4, 5.6, 7, 122]
=#

# Exclusão de elementos repetidos
#=
lista1 = [1.1, 2.2, 2.2, 4.4]
lista2 = [2.2, 4.4, 4.4, 5.5, 6.6]
=#

# Alguns elementos em comum
lista1 = [1.1, 2.3, 3.5, 4.7]
lista2 = [2.3, 3.5, 5.6]
#=
SAÍDA:
[2.3, 3.5]
=#

println("Resultado do merge: $(merge(lista1, lista2))")