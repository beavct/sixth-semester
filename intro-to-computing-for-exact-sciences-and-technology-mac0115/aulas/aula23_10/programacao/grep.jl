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

print("Quantas frases você deseja testar? ")
n = parse(Int64, readline())

frases = String[]

for i in 1:n
    print("Digite uma frase: ")
    push!(frases, readline())
end

print("Qual substring você deseja buscar? ")
subs = readline()


res_m = grep_manual(subs, frases)

res_b = grep_builtin(subs, frases)

println("Resposta do manual: ")
for i in 1:length(res_m)
    println("$i: $(res_m[i])")
end


println("\nResposta do built-in: ")
for i in 1:length(res_b)
    println("$i: $(res_m[i])")
end