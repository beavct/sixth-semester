using Random
using Plots

#=
    Gera uma aposta aleatória com um número de seleções especificado pela variável `numeros`, 
    que deve estar entre 6 e 10. A função escolhe números inteiros únicos aleatórios 
    no intervalo de 1 a 60.

    # Parâmetros
    - `numeros::Int`: O número de seleções que devem ser feitas, deve ser um inteiro 
    entre 6 e 10.

    # Retorno
    - Retorna um vetor de inteiros (`Vector{Int}`) contendo os números selecionados, 
    ordenados em ordem crescente.

    # Exemplo
    ```julia
    aposta = gerar_aposta(6)  # Gera uma aposta com 6 número
=#
function gerar_aposta(numeros::Int) ::Vector{Int}

end

#=
    Simula a quantidade de apostas necessárias para acertar todos os números 
    selecionados em uma aposta aleatória.

    # Parâmetros
    - `numeros_selecionados::Vector{Int}`: Um vetor contendo os números que devem ser acertados. 
    Os números devem estar no intervalo de 1 a 60.
    
    - `max_numeros::Int`: O número máximo de seleções permitidas para a aposta, deve ser um inteiro 
    entre 6 e 10.

    # Retorno
    - Retorna um inteiro (`Int64`) representando o total de apostas realizadas até que 
    todos os números selecionados sejam acertados.

    # Exemplo
    ```julia
    apostas_necessarias = simular_apostas([5, 12, 23, 34, 45, 56], 10)
=#
function simular_apostas(numeros_selecionados::Vector{Int}, max_numeros::Int) :: Int64

end


#= 
    Função responsável por plotar um gráfico da distribuição dos resultados das simulações de apostas.
    A função recebe um vetor de inteiros, onde cada inteiro representa o número de apostas realizadas para acertar todos os números selecionados em uma simulação. A função deve definir intervalos para categorizar os resultados e contar a frequência de apostas em cada intervalo. Em seguida, um gráfico de barras deve ser gerado para visualizar a distribuição, e o gráfico deve ser salvo como um arquivo PNG.
=#
function plota_grafico(resultados::Vector{Int})


end

#= 
    Função principal que coordena a execução do programa.
    A função deve definir os parâmetros necessários para a simulação, como o número máximo de seleções permitidas e o número de simulações a serem realizadas. 
    Ela invocará as funções necessárias, incluindo a simulação de apostas e a plotagem do gráfico de resultados. 
    O objetivo é executar o fluxo completo do programa, desde a geração das apostas até a visualização dos resultados. A função não deve retornar nenhum valor.
=#
function main()

end

main()