# Função que busca uma substring em uma lista de strings de forma manual
function grep1(vetor::Vector{String}, substring::String)
    # Inicializa um vetor para armazenar as frases que contêm a substring
    resposta = String[]

    # Itera sobre cada frase na lista de strings
    for frase in vetor
        # Verifica se a frase contém a substring
        if tem_substring(frase, substring) == true
            push!(resposta, frase)
        end
    end

    return resposta
end

# Função auxiliar para verificar se uma linha contém a substring
function tem_substring(frase::String, substring::String)
    # Obtem o comprimento da frase e da substring
    if length(frase) < length(substring)
        return false
    end

    # Se a substring for maior que a frase, não pode conter
    # Considera a última posição da frase que pode conter a substring
    for i in 1:length(frase)-length(substring)
        if frase[i:i+length(substring)-1] == substring
            return true
        end
    end
end

function grep2(vetor::Vector{String}, substring::String)
    # Filtra apenas as linhas que contém a substring
    resposta = filter(frase -> contains(frase, substring), vetor)
    return resposta
end


print("Quantas frases você quer testar: ")
n = parse(Int64, readline())
vetor = String[]

for i in 1:n
    frase = readline()
    push!(vetor, frase)
end

print("Qual substring você deseja procurar: ")

subs = readline()

resposta = grep2(vetor, subs)

for i in 1:length(resposta)
    println("$i: $(resposta[i])")
end