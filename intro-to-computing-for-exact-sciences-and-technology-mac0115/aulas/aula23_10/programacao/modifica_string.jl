# Se s termina com "ing" -> concatena "ly" no final
# Caso contrário, concatena "ing"

# Nesse caso olhamos a lista resultante de [end-3:end]
function modify_string_manual(s::String)::String
    # Se a palavra tem menos que 3 letras, não tem como olhar suas últimas 3 letras
    if length(s) < 3
        return s  
    # end-2, pois ai eu começo a olhar do terceiro caracter de trás pra frente
    elseif s[end-2:end] == "ing"
        return s * "ly"  
    else
        return s * "ing" 
    end
end

# Usamos a função endswith()
function modify_string_builtin(s::String)::String
    if length(s) < 3
        return s  
    elseif endswith(s, "ing")
        return s * "ly"  
    else
        return s * "ing" 
    end
end
