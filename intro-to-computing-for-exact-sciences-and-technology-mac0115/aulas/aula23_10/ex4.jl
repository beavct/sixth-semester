# Recebe um vetor com várias palavras e retorna a maior, e seu tamanho

function maior_palavra(vetor::Vector{String})
    maior_palavra = String[]
    tamanho = 0

    for palavra in vetor
        # Se a palavra é maior do que o maior tamanho salvo, 
        # então todas as palavras que estão no vetor maior_palavra são menores do que a palavra atual
        if length(palavra) > tamanho 
            # Limpa o vetor e salva a palavra atual
            maior_palavra = String[]
            push!(maior_palavra, palavra)
            tamanho = length(palavra)
        # Se é igual ao tamanho salvo, então é do mesmo tamanho que as palavras já salvas em maior_palavra,
        # apenas damos push na palavra
        elseif length(palavra) == tamanho
            push!(maior_palavra, palavra) 
        end
    end

    return maior_palavra, tamanho

end

# Constrói a entrada
print("Digite a quantidade de palavras: ")
n = parse(Int64, readline())
vetor = String[]

for i in 1:n
    palavra = readline()
    push!(vetor, palavra)
end

resultado_palavras, resultado_tamanho = maior_palavra(vetor)


println("Maiores palavras:")
for palavra in resultado_palavras
    println(palavra)
end

println("Com tamanho $resultado_tamanho")