#=
    Recebe uma string s e devolve uma string que contem as letras minúsculas de s primeiro e depois as maiúsculas, em ordem.
    Ex: s = "BoM diA"
        saída = "odiBMA"
=#

function arrange_case_manual(s::String)::String
    lowercase_letters = ""
    uppercase_letters = ""
    
    for c in s
        if islowercase(c)
            lowercase_letters *= c
        elseif isuppercase(c)
            uppercase_letters *= c
        end
    end
    
    return lowercase_letters * uppercase_letters
end

function arrange_case(s::String)::String
    #= 
        • filter é uma função que aplica uma condição a cada elemento de uma coleção (nesse caso uma Stirng)
        • c -> islowercase(c) é uma função que verifica se o caractere c é uma letra minúscula.
            filter aplica essa função a cada caractere da string s, e salva esse valor na string final lowercase_letters, em ordem.
        • Mesma coisa para isuppercase().

    =#
    lowercase_letters = filter(c -> islowercase(c), s)
    uppercase_letters = filter(c -> isuppercase(c), s)
    return lowercase_letters * uppercase_letters
end

s = ARGS[1]

println("Saída da função manual: ", arrange_case_manual(s))

println("Saída da função built-in: ", arrange_case(s))