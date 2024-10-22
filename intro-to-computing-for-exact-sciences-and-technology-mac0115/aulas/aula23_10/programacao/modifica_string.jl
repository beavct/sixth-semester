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

function compare_modify_string()
    inputs = [
        "a",            # Teste 1
        "ab",           # Teste 2
        "run",          # Teste 3
        "ing",          # Teste 4
        "running",      # Teste 5
        "play",         # Teste 6
        "swimming",     # Teste 7
        "singing!",     # Teste 8
        "!@#ing",       # Teste 9
        "#hello",       # Teste 10
        ""               # Teste 11
    ]

    for s in inputs
        result_direct = modify_string_manual(s)
        result_builtin = modify_string_builtin(s)
        println("Input: '$s' => Manual: '$result_direct' | Built-in: '$result_builtin'")
    end
end

compare_modify_string()
