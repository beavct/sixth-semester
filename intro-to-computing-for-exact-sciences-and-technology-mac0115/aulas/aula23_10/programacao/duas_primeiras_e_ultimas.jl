using Test

function twofirst_twolast(s::String)::String
    # Se o tamanho for menor do que 2, não tem como pegar as duas primerias e as duas últimas
    if length(s) < 2
        return ""
    else
        return s[1:2] * s[end-1:end]
    end
end

function test_twofirst_twolast()
    # Casos de teste: cada elemento é um par (entrada, saída esperada)
    test_cases = [
        ("a", ""),               # Teste 1: Menos de 2 caracteres
        ("ab", "abab"),          # Teste 2: Exatamente 2 caracteres
        ("abcdef", "abef"),      # Teste 3: Mais de 2 caracteres
        ("!@#%^&*()", "!@()"),   # Teste 4: Com caracteres especiais
        ("", "")                 # Teste 5: String vazia
    ]

    # Executa os testes
    for (input, expected) in test_cases
        @test twofirst_twolast(input) == expected
    end
end

test_twofirst_twolast()
