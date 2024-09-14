function aproxima_raiz(x::Float64, epsilon::Float64)::Float64
    if x < 0
        return nothing
    end

    # Chute inicial 
    aproximacao = x/2
    melhor_aproximicao = aproximacao

    while true
        # Fórmula para aproximação de raiz quadrada utilizando o método de Newthon-Raphson
        melhor_aproximicao = 0.5 * (aproximacao + x/aproximacao)

        # Se a distância absoluta entre os dois pontos é menor do que epsilon, então podemos parar o método
        if abs(aproximacao - melhor_aproximicao) <= epsilon
            break
        end

        # Se a aproximação ainda não for boa o sufuciente, então atualizamos a aproximação para a próxima iteração
        aproximacao = melhor_aproximicao
    end

    return melhor_aproximicao

end