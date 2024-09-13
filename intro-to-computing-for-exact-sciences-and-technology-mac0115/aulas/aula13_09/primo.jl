function verifica_primo(num :: Int64)
    if num <= 1
        return false
    end

    i=2

    # pode ser melhorado com i<=num/2
    # ou também com num <= sqrt(num): baseado no fato que um número composto deve ter um ftor menor ou igual a raiz desse número

    while i<num
        if num % i == 0
            return false
        end
        i+=1
    end

    return true

end


#=
num = parse(Int64,ARGS[1])
res = verifica_primo(num)

if res
    println("$num é primo")
else
    println("$num não é primo")
end

=#