function e_palindromo(n::Int64)
    # Guarda os dígitos de n que ainda devem ser invertidos
    aux = n
    # Guarda a inversão do número n 
    n_inv = 0


    # Continuamos o while enquanto ainda há números a serem invertidos
    while aux > 0 
        # Coloca o último dígito de aux na variável que guarda a inversão
        resto = aux % 10
        n_inv= n_inv * 10 + resto

        # Retira o último dígito de aux
        aux = div(aux,10)
    end


    if n == n_inv
        println("O número $n é palíndromo")
    else
        println("O número $n não é palíndromo")
    end 

end

num = parse(Int64,ARGS[1])
e_palindromo(num)