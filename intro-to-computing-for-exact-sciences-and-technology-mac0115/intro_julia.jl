#= 
    para rodar no terminal 
    $ julia intro_julia.jl
=#

#=
    para carregar o arquivo no julia> para depois rodar uma função especifica
    include("intro_julia.jl")
=#

# print
# println("Olá mundo")

# input
# nome = readline("Qual o seu nome?")
# println("Seu nome é " + nome)

# a aritmética funciona normal
# println(1+2)
# println(2*4/2) 

# nome de variável tem que seguir as regras normais: não ter caracteres inválidos, não iniciar com números e não ter o mesmo nome de métodos já existentes

# funções iniciadas por "function" e terminadas por "end"

function fat(n)
    res = 1

    for i in 2:n
        res *= i
    end

    return res
end

function pos_neg()
    numero = readline("Digite um número")
    
    if numero < 0
        println(numero + " é negativo")
    else
        println(numero + " é positivo")
    end 

end