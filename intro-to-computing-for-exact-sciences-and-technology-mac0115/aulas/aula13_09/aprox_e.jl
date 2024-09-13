function aproximacao_e(x::Float64, eps::Float64)
    # Verificar se o valor de eps é maior que 0
    if eps <= 0
        println("O valor de eps deve ser maior que 0.")
        return
    end

    # Inicializando as variáveis
    eul = 0.0
    num = x
    den = 1.0
    i = 1.0

    # Loop para calcular a aproximação de e^x
    while abs(num / den) >= eps
        eul += num / den
        num *= x
        den *= i
        i += 1
    end

    # Adiciona o último termo da série
    eul += num / den
    println("A aproximação é $eul")
    return eul
end