function aproximacao_raiz(x::Float64, epsilon::Float64)
    # Verificar se o número é negativo
    if x < 0
        println("A raiz quadrada de um número negativo não é um número real.")
        return nothing
    end

    # Escolha inicial (chute inicial para a raiz quadrada)
    aproximacao = x / 2.0  # Um chute inicial razoável

    while true
        # Novo valor usando o método de Newton-Raphson
        melhor_aproximacao = (aproximacao + x / aproximacao) / 2

        # Verificar se a diferença é menor que a tolerância
        if abs(melhor_aproximacao - aproximacao) < epsilon
            break
        end

        # Atualizar a aproximação para a próxima iteração
        aproximacao = melhor_aproximacao
    end

    return melhor_aproximacao
end