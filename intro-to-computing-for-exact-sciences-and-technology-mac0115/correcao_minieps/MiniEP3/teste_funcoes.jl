# teste_funcoes.jl

# Obtém o nome do arquivo a ser testado da linha de comando
if length(ARGS) != 1
    println("Uso: julia teste_funcoes.jl arquivo_a_ser_corrigido.jl")
    exit(1)
end

arquivo_a_ser_corrigido = ARGS[1]

# Inclui as funções do arquivo que será corrigido
include(arquivo_a_ser_corrigido.jl)

# Inclui as funções do arquivo 'funcoes_corretor.jl' para verificação
include("funcoes_corretor.jl")

# Define uma função para testar e gravar os resultados
function testar_funcoes(arquivo_testado::String)
    # Abre o arquivo resultados.txt para escrita
    open("resultados.txt", "w") do file
        # Nome do arquivo testado
        arquivo_testado = "funcoes.jl"
        # Inicializa contadores para testes
        total_testes = 0
        testes_passados = 0

        # Funções de teste
        function testa_calculaAreaTriangulo(base, altura, esperado)
            global total_testes += 1
            resultado = calculaAreaTriangulo_corretor(base, altura)
            esperado_corretor = calculaAreaTriangulo(base, altura)
            if resultado == esperado_corretor
                global testes_passados += 1
                println(file, "calculaAreaTriangulo($base, $altura) PASSOU")
            else
                println(file, "calculaAreaTriangulo($base, $altura) FALHOU - Esperado: $esperado_corretor, Obtido: $resultado")
            end
        end

        function testa_calculaAreaRetangulo(base, altura, esperado)
            global total_testes += 1
            resultado = calculaAreaRetangulo_corretor(base, altura)
            esperado_corretor = calculaAreaRetangulo(base, altura)
            if resultado == esperado_corretor
                global testes_passados += 1
                println(file, "calculaAreaRetangulo($base, $altura) PASSOU")
            else
                println(file, "calculaAreaRetangulo($base, $altura) FALHOU - Esperado: $esperado_corretor, Obtido: $resultado")
            end
        end

        function testa_calculaArea(tipo, base, altura, esperado)
            global total_testes += 1
            resultado = calculaArea_corretor(tipo, base, altura)
            esperado_corretor = calculaArea(tipo, base, altura)
            if resultado == esperado_corretor
                global testes_passados += 1
                println(file, "calculaArea($tipo, $base, $altura) PASSOU")
            else
                println(file, "calculaArea($tipo, $base, $altura) FALHOU - Esperado: $esperado_corretor, Obtido: $resultado")
            end
        end

        # Execute testes
        # Testes para calculaAreaTriangulo
        testa_calculaAreaTriangulo("2.0", "3.0", calculaAreaTriangulo_corretor("2.0", "3.0"))
        testa_calculaAreaTriangulo("4.0", "5.0", calculaAreaTriangulo_corretor("4.0", "5.0"))
        testa_calculaAreaTriangulo("7.0", "8.0", calculaAreaTriangulo_corretor("7.0", "8.0"))
        testa_calculaAreaTriangulo("10.0", "20.0", calculaAreaTriangulo_corretor("10.0", "20.0"))
        testa_calculaAreaTriangulo("45.2", "12.4", calculaAreaTriangulo_corretor("45.2", "12.4"))
        testa_calculaAreaTriangulo("123.1", "55.0", calculaAreaTriangulo_corretor("123.1", "55.0"))

        
        # Testes para calculaAreaRetangulo
        testa_calculaAreaRetangulo("4.0", "5.0", calculaAreaRetangulo_corretor("4.0", "5.0"))
        testa_calculaAreaRetangulo("7.0", "8.0", calculaAreaRetangulo_corretor("7.0", "8.0"))
        testa_calculaAreaRetangulo("10.0", "20.0", calculaAreaRetangulo_corretor("10.0", "20.0"))
        testa_calculaAreaRetangulo("1.0", "1.0", calculaAreaRetangulo_corretor("1.0", "1.0"))
        testa_calculaAreaRetangulo("204.0", "67.0", calculaAreaRetangulo_corretor("204.0", "67.0"))
        testa_calculaAreaRetangulo("153.7", "98.0", calculaAreaRetangulo_corretor("153.7", "98.0"))


        # Testes para calculaArea
        testa_calculaArea(0, "2.0", "3.0", calculaArea_corretor(0, "2.0", "3.0"))
        testa_calculaArea(0, "4.0", "5.0", calculaArea_corretor(0, "4.0", "5.0"))
        testa_calculaArea(0, "7.0", "8.0", calculaArea_corretor(0, "7.0", "8.0"))
        testa_calculaArea(0, "10.0", "20.0", calculaArea_corretor(0, "10.0", "20.0"))


        testa_calculaArea(1, "4.0", "5.0", calculaArea_corretor(1, "4.0", "5.0"))
        testa_calculaArea(1, "7.0", "8.0", calculaArea_corretor(1, "7.0", "8.0"))
        testa_calculaArea(1, "10.0", "20.0", calculaArea_corretor(1, "10.0", "20.0"))
        testa_calculaArea(1, "1.0", "1.0", calculaArea_corretor(1, "1.0", "1.0"))
        
        # Relatório final
        println(file, "\nResultados dos Testes:")
        println(file, "Arquivo testado: $arquivo_testado")
        println(file, "Total de testes: $total_testes")
        println(file, "Testes passados: $testes_passados")
    end
end

# Executa os testes
testar_funcoes(arquivo_a_ser_corrigido)
