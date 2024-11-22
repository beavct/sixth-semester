function merge(lista1:: Vector{Float64}, lista2:: Vector{Float64}) :: Vector{Float64}
    ret =  Vector{Float64}()

    for elem in lista1
        if elem in lista2
            push!(ret, elem)
        end
    end

    return ret
end

lista1 = [1.1, 2.3, 3.5, 4.7]
lista2 = [2.3, 3.5, 5.6]

println(merge(lista1, lista2))