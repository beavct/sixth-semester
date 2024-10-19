using Random
using Plots

function gerar_aposta(numeros::Int) ::Vector{Int}
    return sort(rand(1:60, numeros))
end

function simular_apostas(numeros_selecionados::Vector{Int}, max_numeros::Int) :: Int64
    total_apostas = 0
    acertou = false
    
    # Continua o loop enquanto o gerador aleatório não acerta a aposta
    while !acertou
        total_apostas += 1

        # Chama a função gerar_aposta com um número aleatório entre 6 e max_numeros
        aposta = gerar_aposta(rand(6:max_numeros))
        
        
        # Assume que acertou, até provar o contrário
        acertou = true  
        
        # Comparar se todos os números selecionados estão na aposta
        for num in numeros_selecionados
            #= 
                Se o número gerado aleatóriamente não está na aposta correta, 
                então o gerador de apostas não acertou
            =#
            if !(num in aposta)
                acertou = false  
                break  
            end
        end
    end
    
    return total_apostas
end

function plota_grafico(resultados::Vector{Int})
    # Plotar os resultados

    # Definir intervalos
    intervalos = [0, 10000, 100000, 1000000, 10000000, 100000000]
    x_label = ["10^0", "10^4", "10^5", "10^6", "10^7", "10^8"]
    frequencias_intervalos = zeros(Int, length(intervalos) - 1)

    # Contar as frequências em intervalos
    for resultado in resultados
        for i in 1:length(intervalos)-1
            if resultado >= intervalos[i] && resultado < intervalos[i+1]
                frequencias_intervalos[i] += 1
            end

            if resultado >= intervalos[end]
                frequencias_intervalos[end] += 1
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
    numeros_selecionados = sort(rand(1:60, rand(6:max_numeros)))

    # Inicializa um vetor de inteiros vazio para os resultados
    resultados = Int[]

    # Simulação das apostas
    for i in 1:num_simulacoes
        push!(resultados, simular_apostas(numeros_selecionados, max_numeros))
        #println(resultados)
    end

    plota_grafico(resultados)

end

main()