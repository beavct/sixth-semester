#!/bin/bash

# Define o diretório onde estão os arquivos a serem testados
DIRETORIO_ENTREGAS="./entregas"

# Nome dos arquivos que não devem ser testados
EXCLUIR=("teste_funcoes.jl" "funcoes_corretor.jl" "miniEP3.jl")

# Caminho para o arquivo de teste
ARQUIVO_TESTE="teste_funcoes.jl"

# Verifica se o arquivo de teste existe
if [ ! -f "$ARQUIVO_TESTE" ]; then
    echo "Erro: O arquivo de teste '$ARQUIVO_TESTE' não foi encontrado."
    exit 1
fi

# Entra no diretório onde os arquivos a serem testados estão localizados
cd "$DIRETORIO_ENTREGAS" || { echo "Diretório não encontrado: $DIRETORIO_ENTREGAS"; exit 1; }

# Para cada arquivo .jl no diretório de entregas
for ARQUIVO in *.jl; do
    # Verifica se o arquivo não está na lista de exclusão
    if [[ ! " ${EXCLUIR[@]} " =~ " ${ARQUIVO} " ]]; then
        echo "Testando o arquivo: $ARQUIVO"
        julia "../$ARQUIVO_TESTE" "./entregas/$ARQUIVO"
    else
        echo "Ignorando o arquivo: $ARQUIVO"
    fi
done

echo "Testes concluídos."
