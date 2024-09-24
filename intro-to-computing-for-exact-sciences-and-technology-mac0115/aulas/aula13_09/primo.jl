function verifica_primo(num :: Int64)
    if num <= 1
        return false
    end

    i=2

    # pode ser melhorado com i<=num/2
    # ou também com i<= sqrt(num): baseado no fato que um número composto deve ter um fator menor ou igual a raiz desse número

    while i<num
        if num % i == 0
            return false
        end
        i+=1
    end

    return true

end
