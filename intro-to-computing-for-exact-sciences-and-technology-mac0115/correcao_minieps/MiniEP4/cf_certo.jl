# código-fonte que funciona corretamente

function Fibo(n)
    #=
        Fibo(n: Int64) -> Int64
        Esta função deve calcular o n-ésimo número da sequência de Fibonacci.
        Exemplo: Fibo(0) == 0, Fibo(1) == 1, Fibo(5) == 5.
    =#

    # Início da implementação da função
    if n == 0
        return 0
    elseif n == 1
        return 1
    else
        return Fibo(n - 1) + Fibo(n - 2)
    end
end

function verificaFibo()
    #=
        verificaFibo() -> Void
        Esta função deve testar a função Fibo com pelo menos 3 valores diferentes.
    =#

    # Testes automatizados da função Fibo
    println("Teste 1: Fibo(0) == 0")
    println(Fibo(0) == 0 ? "Passou" : "Falhou")

    println("Teste 2: Fibo(1) == 1")
    println(Fibo(1) == 1 ? "Passou" : "Falhou")

    println("Teste 3: Fibo(5) == 5")
    println(Fibo(5) == 5 ? "Passou" : "Falhou")

    println("Teste 4: Fibo(7) == 13")
    println(Fibo(7) == 13 ? "Passou" : "Falhou")


    println("Teste 5: Fibo(8) == 21")
    println(Fibo(8) == 21 ? "Passou" : "Falhou")

    println("Teste 6: Fibo(10) == 55")
    println(Fibo(10) == 55 ? "Passou" : "Falhou")


    # Você pode adicionar mais testes para validar a função
end

#=
    Você pode testar a função Fibo utilizando a função verificaFibo.
=#

verificaFibo()
