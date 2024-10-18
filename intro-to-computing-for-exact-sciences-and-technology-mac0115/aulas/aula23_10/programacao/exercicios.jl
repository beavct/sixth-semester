function twofirst_twolast(s::String)::String
    if length(s) < 2
        return ""
    else
        return s[1:2] * s[end-1:end]
    end
end

function modify_string(s::String)::String
    if length(s) < 3
        return s  
    elseif endswith(s, "ing")
        return s * "ly"  
    else
        return s * "ing" 
    end
end

#=
    TESTES PARA MODIFY_STRING

    println(modify_string("run"))      
    println(modify_string("jumping"))  
    println(modify_string("go"))       
    println(modify_string("play"))     
    println(modify_string("doing"))    
=#

function arrange_case(s::String)::String
    lowercase_letters = filter(c -> islowercase(c), s)
    uppercase_letters = filter(c -> isuppercase(c), s)
    return lowercase_letters * uppercase_letters
end

function reverse_string_direct(s::String)::String
    reversed = ""
    for i in length(s):-1:1
        reversed *= s[i]  # Adiciona cada caractere na ordem inversa
    end
    return reversed
end

function reverse_string_builtin(s::String)
    return reverse(s)  # Usando a função reverse embutida
end

function longest_word(words::Vector{String})
    longest = ""
    max_length = 0
    
    for word in words
        if length(word) > max_length
            longest = word
            max_length = length(word)
        end
    end
    
    return longest, max_length
end

#=
    TESTE PARA LONGEST_WORD

    words_list = ["apple", "banana", "cherry", "blueberry", "kiwi"]
    longest, length_of_longest = longest_word(words_list)
    println("Longest word: $longest, Length: $length_of_longest")
=#

# Função que busca uma substring em uma lista de strings de forma manual
function grep_madein(substring::String, lines::Vector{String})
    # Inicializa um vetor para armazenar as linhas que contêm a substring
    matching_lines = String[]

    # Itera sobre cada linha na lista de strings
    for line in lines
        # Verifica se a linha contém a substring
        if contains_substring(line, substring)
            push!(matching_lines, line)
        end
    end
    
    return matching_lines
end

# Função auxiliar para verificar se uma linha contém a substring
function contains_substring(line::String, substring::String)
    # Obtem o comprimento da linha e da substring
    line_len = length(line)
    substring_len = length(substring)

    # Se a substring for maior que a linha, não pode conter
    if substring_len > line_len
        return false
    end

    # Itera sobre a linha, verificando a substring
    # Considera a última posição da line que pode conter a substring
    for i in 1:(line_len - substring_len + 1)
        if line[i:(i + substring_len - 1)] == substring
            return true
        end
    end

    return false
end


# Função que busca uma substring em uma lista de strings
function grep_direto(substring::String, lines::Vector{String})
    return filter(line -> contains(line, substring), lines)
end

# Exemplo de uso
function teste_grep()
    # Lista de strings (pode ser substituída por qualquer input)
    lines = [
        "Aprendendo Julia é divertido.",
        "A linguagem Julia é poderosa.",
        "Esta é uma string de exemplo.",
        "Grep em Julia é fácil de implementar."
    ]

    # Perguntar ao usuário pela substring
    println("Digite a substring que deseja buscar:")
    substring = readline()

    # Chamar a função grep
    resultados = grep(substring, lines)

    # Exibir os resultados
    println("Resultados da busca:")
    for resultado in resultados
        println(resultado)
    end
end