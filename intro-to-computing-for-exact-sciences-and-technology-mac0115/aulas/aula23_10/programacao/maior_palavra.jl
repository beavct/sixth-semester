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

print("Quantas palavras você quer testar? ")
n = parse(Int64, readline())

palavras = String[]

i = 0
# Poderia ser um while
for i in 1:n
#while i<n
    print("Digite a palavra: ")
    push!(palavras, readline())
    # pro julia parar de encher o sacoz
    #global i+=1
end

maior_p, tamanho_p = longest_word(palavras)
println("Resultado: $maior_p ($tamanho_p)" )