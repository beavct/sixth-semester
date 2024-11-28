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
	linhas, colunas = size(matriz)
	nova_matriz = zeros(Int, linhas, colunas)

	# Itera sobre cada célula da matriz
	for i in 1:linhas
		for j in 1:colunas
			# Calcula o número de vizinhos vivos
			vizinhos = 0
			for di in -1:1
				for dj in -1:1
					# se di == dj == 0, então estamos olhando a célula que queremos atualizar
					if di == 0 && dj == 0
						continue
					end

					# Calculando os índices do vizinho que vamos olhar
					vizinho_i = i + di
					vizinho_j = j + dj

					# Se os vizinhos estão dentro do intervalo de índices da matriz, então verificamos se está vivo ou morto
					if 1 <= vizinho_i <= linhas && 1 <= vizinho_j <= colunas
						vizinhos += matriz[vizinho_i, vizinho_j]
					end
				end
			end

			# Aplica as regras
			if matriz[i, j] == 1 # Célula viva
				if vizinhos < 2 || vizinhos > 3
					nova_matriz[i, j] = 0 # Morre por isolamento ou superpopulação
				end
			else # Célula morta
				if vizinhos == 3
					nova_matriz[i, j] = 1 # Torna-se viva por nascimento
				end
			end
		end
	end

	return nova_matriz
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

    println()
	println("Estado inicial:")
	printa_matriz(matriz)
	println()

	for t in 1:iteracoes
		matriz = atualiza_matriz(matriz, debug)
		if contabiliza_celulas(matriz) == 0
			println("Todas as células morreram na iteração $t.")
			break
		elseif t != 1 && t != iteracoes
			println("Matriz na $(t)º iteração:")
			printa_matriz(matriz)
			println()

		end
	end

	println("Estado final:")
	printa_matriz(matriz)
end

# Executa o programa
main()
