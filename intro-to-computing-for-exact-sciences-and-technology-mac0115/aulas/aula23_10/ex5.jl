#=
    Recebe uma string s e a inverte
=#

function inverte(s::String)::String
    # Inicializamos uma string vazia
    inversa=""

    # Intervalo de lenght(s) até 1, a passos de -1
    for i in length(s):-1:1
        # Concatena cada caractere na ordem inversa
        inversa*=s[i]
    end

    return inversa
end


println("Resultado 1: ", inverte(ARGS[1]))
println("Resultado 2: ", reverse(ARGS[1]))
