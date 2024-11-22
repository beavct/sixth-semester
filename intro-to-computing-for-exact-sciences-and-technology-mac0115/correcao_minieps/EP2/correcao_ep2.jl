using Random
using Plots

function gerar_aposta(numeros::Int) ::Vector{Int}
    # Gera uma aposta de tamanho numeros, sem números repetidos 
    aposta = sort!(unique(rand(1:60, 60))[1:numeros])
    return aposta
end

function simular_apostas(numeros_selecionados::Vector{Int}, max_numeros::Int) :: Int64
    total_apostas = 0
    acertou = false
    
    # Continua o loop enquanto o gerador aleatório não acerta a aposta
    while !acertou
        total_apostas += 1

        # Chama a função gerar_aposta com um número aleatório entre 6 e max_numeros
        aposta = gerar_aposta(rand(6:max_numeros))
        
        # Verifica se todos os números da aposta estão em numeros_selecionados
        acertou = all(num -> num in aposta, numeros_selecionados)
    end
    
    return total_apostas
end

function plota_grafico(resultados::Vector{Int})
    # Plotar os resultados

    # Definir intervalos
    intervalos = [0, 10_000, 100_000, 1_000_000, 10_000_000, 100_000_000]
    x_label = ["10^0", "10^4", "10^5", "10^6", "10^7", "10^8"]
    frequencias_intervalos = zeros(Int, length(intervalos))

    # Contar as frequências em intervalos
    for resultado in resultados
        for i in 1:length(intervalos)-1
            if resultado >= intervalos[i] && resultado < intervalos[i+1]
                frequencias_intervalos[i] += 1
            end
        end
    end

    bar(x_label, frequencias_intervalos[1:end], color = [:lightsalmon, :tomato, :crimson, :firebrick, :darkred], xlabel="Número de Apostas", ylabel="Frequência", title="Distribuição do Número de Apostas", label="",  alpha = 0.8)
    
    # Salvar o gráfico como PNG
    savefig("distribuicao_apostas.png")
end


function main()

    # Parâmetros da simulação
    max_numeros = 10
    num_simulacoes = 100

    #= 
        Gera a resposta correta.
        A resposta possui de 6 a max_numeros, que estão entre 1 e 60.
    =#
    numeros_selecionados = gerar_aposta(rand(6:max_numeros))

    # Inicializa um vetor de inteiros vazio para os resultados
    resultados = Int[]

    # Simulação das apostas
    for i in 1:num_simulacoes
        push!(resultados, simular_apostas(numeros_selecionados, max_numeros))
    end

    plota_grafico(resultados)

end

main()