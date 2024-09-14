function fatorial_recursivo(n::Int)
    if n == 0 || n == 1
        return 1
    else
        return n * fatorial_recursivo(n - 1)
    end
end

function fatorial_iterativo(n::Int)
    resultado = 1
    while n > 1
        resultado *= n
        n -= 1
    end
    return resultado
end