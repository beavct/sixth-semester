function gera_entrada_aleatoria(linhas::Int, colunas::Int, probabilidade::Float64)::Matrix{Int}
    # Gera uma matriz de números aleatórios entre 0 e 1
    matriz_aleatoria = rand(linhas, colunas)
    
    # Para cada célula, se o valor gerado for menor que a probabilidade, a célula fica viva (1), caso contrário, fica morta (0)
    return matriz_aleatoria .< probabilidade
end

# Printa a matriz
function printa_matriz(matriz::Matrix{Int})::Nothing
	for linha in eachrow(matriz)
		println(join(linha, " "))
	end
end

# Conta o número de células vivas
function contabiliza_celulas(matriz::Matrix{Int})::Int
	soma = 0
	linhas, colunas = size(matriz)


	for i in 1:linhas
		for j in 1:colunas
			soma += matriz[i, j]
		end
	end

	return soma

	# Forma mais concisa de pegar a soma de todas as células da matriz
	# return sum(matriz)
end

# Atualiza a matriz seguindo as regras do jogo da vida
function atualiza_matriz(matriz::Matrix{Int}, debug::Bool = false)::Matrix{Int}
    # Você deve desenvolver essa função
end

# Função principal
function main()::Nothing
	print("Digite o tamanho da matriz (linhas e colunas): ")
	entrada = split(readline())
	linhas = parse(Int, entrada[1])
	colunas = parse(Int, entrada[2])

	print("Digite o número de iterações: ")
	iteracoes = parse(Int, readline())

	print("Digite a probabilidade: ")
	prob = parse(Float64, readline())

	print("(0) Sem debug (1) Com debug: ")
	debug = parse(Int, readline()) == 1

	# Gera a matriz inicial
	matriz = gera_entrada_aleatoria(linhas, colunas, prob)

    # Você deve terminar de escrever essa função
end

# Executa o programa
main()
