# Função para verificar se um número é primo
function eh_primo(n::Int64)::Bool
    if n < 2
        return false
    end
    i = 2
    while i < n
        if n % i == 0
            return false
        end
        i += 1
    end
    return true
end

# Função para somar os n primeiros primos
function soma_primos(n::Int64)::Int64
    soma = 0
    i = 2
    cont = 0
    while cont <= n
        if eh_primo(i)
            soma += i
            cont += 1
        end
        i += 1
    end
    return soma
end

# Exemplo de uso

#= 
    Para a primeira chamada do @time ... soma_primos(n) a função soma_primos é compilada
    Por esse motivo ela demora mais do que as demais execuções, e assim, esse primeiro resultado deve ser descartado
    Quando for testar o tempo da sua função não esqueça dessa primeira execução de descarte
=#

println("Início dos testes da função eh_primo()")
@time println("- Teste de descarte para função eh_primo(), n=1, resultado: ", eh_primo(1))
@time println("- Teste para n=1, resultado: ", eh_primo(1))
@time println("- Teste para n=47, resultado: ", eh_primo(47))
@time println("- Teste para n=72, resultado: ", eh_primo(72))
@time println("- Teste para n=163, resultado: ", eh_primo(163))
@time println("- Teste para n=736847597, resultado: ", eh_primo(736847597))
println("Fim dos testes da função eh_primo()")

println("\n------------------------------------------------------\n")

println("Início dos testes da função soma_primos()")
@time println("- Teste de descarte para função soma_primos(), n=1, soma=", soma_primos(1))
@time println("- Teste para n=1, soma=", soma_primos(1))
@time println("- Teste para n=10, soma=", soma_primos(10))
@time println("- Teste para n=20, soma=", soma_primos(20))
@time println("- Teste para n=100, soma=", soma_primos(100))
@time println("- Teste para n=10001, soma=", soma_primos(10000))
println("Fim dos testes da função soma_primos()")
