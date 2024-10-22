#=
    Recebe uma string s e a inverte
=#

function reverse_string_manual(s::String)::String
    # Inicializamos uma string vazia
    reversed = ""

    # Intervalo de lenght(s) até 1, a passos de -1
    for i in length(s):-1:1
        # Concatena cada caractere na ordem inversa
        reversed *= s[i]  
    end
    return reversed
end

function reverse_string_builtin(s::String)
    return reverse(s)  # Usando a função reverse embutida
end

s = ARGS[1]

println("Saída da função manual: ", reverse_string_manual(s))

println("Saída da função built-in: ", reverse_string_builtin(s))  