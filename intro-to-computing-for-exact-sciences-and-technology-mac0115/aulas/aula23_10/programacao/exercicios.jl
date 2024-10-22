function twofirst_twolast(s::String)::String
    # Se o tamanho for menor do que 2, não tem como pegar as duas primerias e as duas últimas
    if length(s) < 2
        return ""
    else
        return s[1:2] * s[end-1:end]
    end
end

#println("Resultado: ", twofirst_twolast(ARGS[1]))

##################################################

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

#=
    TESTES PARA MODIFY_STRING

    println(modify_string("run"))      
    println(modify_string("jumping"))  
    println(modify_string("go"))       
    println(modify_string("play"))     
    println(modify_string("doing"))    
=#

##################################################

#=
    Recebe uma string s e devolve uma string que contem as letras minúsculas de s primeiro e depois as maiúsculas, em ordem.
    Ex: s = "BoM diA"
        saída = "odiBMA"
=#
function arrange_case_manual1(s::String)::String
    lowercase_letters = ""
    uppercase_letters = ""
    
    # Falar da tabela ASCII
    for c in s
        if Int(c) >= 97
            lowercase_letters *= c
        else
            uppercase_letters *= c
        end
    end
    
    return lowercase_letters * uppercase_letters
end

function arrange_case_manual2(s::String)::String
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

#s = ARGS[1]
#println("Saída da função manual: ", arrange_case_manual(s))
#println("Saída da função built-in: ", arrange_case(s))

##################################################

function reverse_string_manual(s::String)::String
    reversed = ""
    for i in length(s):-1:1
        reversed *= s[i]  # Adiciona cada caractere na ordem inversa
    end
    return reversed
end

function reverse_string_builtin(s::String)
    return reverse(s)  # Usando a função reverse embutida
end

#s = ARGS[1]
#println("Saída da função manual: ", reverse_string_manual(s))
#println("Saída da função built-in: ", reverse_string_builtin(s))  

##################################################

# Recebe um vetor com várias palavras e retorna a maior, e seu tamanho
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

#print("Quantas palavras você quer testar? ")
#n = parse(Int64, readline())
#
#palavras = String[]
#
#i = 0
## Poderia ser um while
#for i in 1:n
##while i<n
#    print("Digite a palavra: ")
#    push!(palavras, readline())
#    # pro julia parar de encher o sacoz
#    #global i+=1
#end
#
#maior_p, tamanho_p = longest_word(palavras)
#println("Resultado: $maior_p ($tamanho_p)" )

##################################################

# Função que busca uma substring em uma lista de strings de forma manual
function grep_builtin(substring::String, lines::Vector{String})
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
function grep_manual(substring::String, lines::Vector{String})
    # Filtra apenas as linhas que contém a substring
    return filter(line -> contains(line, substring), lines)
end

#print("Quantas frases você deseja testar? ")
#n = parse(Int64, readline())
#
#frases = String[]
#
#for i in 1:n
#    print("Digite uma frase: ")
#    push!(frases, readline())
#end
#
#print("Qual substring você deseja buscar? ")
#subs = readline()
#
#
#res_m = grep_manual(subs, frases)
#
#res_b = grep_builtin(subs, frases)
#
#println("Resposta do manual: ")
#for i in 1:length(res_m)
#    println("$i: $(res_m[i])")
#end
#
#
#println("\nResposta do built-in: ")
#for i in 1:length(res_b)
#    println("$i: $(res_m[i])")
#end