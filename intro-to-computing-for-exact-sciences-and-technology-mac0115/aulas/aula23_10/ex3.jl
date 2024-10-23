#=
    Recebe uma string s e devolve uma string que contem as letras minúsculas de s primeiro e depois as maiúsculas, em ordem.
    Ex: s = "BoM diA"
        saída = "odiBMA"
=#

# Utilizando a tabela ASCII
function rearranja1(s::String)::String
    maiusculos=""
    minusculos=""

    for i in 1:length(s)
        if Int(s[i]) >= 65 && Int(s[i]) <= 90 
            maiusculos = maiusculos*s[i]
        elseif Int(s[i]) >= 97 && Int(s[i]) <= 122
            minusculos = minusculos*s[i]
        end 
    end

    return minusculos*maiusculos
     
end

function rearranja2(s::String)::String
    maiusculos=""
    minusculos=""

    # Usa as funções isuppercase() e  islowercase() de Julia
    for i in 1:length(s)
        if isuppercase(s[i]) 
            maiusculos = maiusculos*s[i]
        elseif islowercase(s[i])
            minusculos = minusculos*s[i]
        end 
    end

    return minusculos*maiusculos
     
end

function rearranja3(s::String)::String
    #= 
        • filter é uma função que aplica uma condição a cada elemento de uma coleção (nesse caso uma Stirng)
        • c -> islowercase(c) é uma função que verifica se o caractere c é uma letra minúscula.
            filter aplica essa função a cada caractere da string s, e salva esse valor na string final lowercase_letters, em ordem.
        • Mesma coisa para isuppercase().
    =#
    maiusculos = filter(c -> isuppercase(c), s)
    minusculos = filter(c -> islowercase(c), s)

    return minusculos*maiusculos
     
end