# Se s termina com "ing" -> concatena "ly" no final
# Caso contrário, concatena "ing"
function modifica(s::String)::String
    if length(s) < 3
        return "Erro: tamanho da string menor do que 3"
    end
    
    if s[end-2:end] == "ing"
        s = s*"ly"
    else    
        s = s*"ing"                
    end


    return s
end


# Usamos a função endswith()
function modifica_builtin(s::String)::String
    if length(s) < 3
        return "Erro: tamanho da string menor do que 3"
    end
    
    if endswith(s, "ing")
        s = s*"ly"
    else    
        s = s*"ing"                
    end


    return s
end



println("Resultado: ", modifica_builtin(ARGS[1]))