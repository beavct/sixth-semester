# EP: Algoritmo de Fluxo Mínimo em um Digrafo

Este programa resolve o problema de fluxo mínimo em um digrafo, utilizando o método simplex para redes. A solução é obtida através de uma árvore inicial fornecida como entrada. Este programa **não** trata casos onde não há solução ou quando a solução é ilimitada. É necessário fornecer uma árvore inicial válida como entrada para que o algoritmo funcione corretamente.

## Informações
    Nome: Beatriz Viana Costa
    NUSP: 13673214

## Descrição do Problema

O objetivo deste programa é encontrar a solução ótima para um problema de fluxo mínimo em um digrafo. O algoritmo considera as demandas dos vértices, as arestas do digrafo, os fluxos existentes e a árvore inicial fornecida como entrada. O programa busca minimizar o fluxo total dos vértices enquanto respeita as restrições de capacidade das arestas.

## Formato da Entrada

A entrada deve ser fornecida no seguinte formato:

1. **Número de Vértices e Arestas**:
   - A primeira linha do arquivo de entrada contém dois números inteiros: `n` (número de vértices) e `m` (número de arestas). Exemplo: `4 5`.

2. **Demandas dos Vértices**:
   - Seguem-se `n` linhas, cada uma descrevendo a demanda de um vértice. As demandas podem ser positivas (consomem fluxo), negativas (criam fluxo) ou zero. Exemplo:
     ```
     0
     1
     -1
     0
     ```

3. **Descrição das Arestas**:
   - Seguem-se `m` linhas, cada uma descrevendo uma aresta no digrafo. Cada linha possui os seguintes valores:
     ```
     <tail> <head> <custo> <capacidade> <fluxo atual> <1 se pertencer à árvore inicial, 0 caso contrário>
     ```
   - Onde:
     - `tail` é o vértice de origem da aresta (u).
     - `head` é o vértice de destino da aresta (v).
     - `custo` é o custo associado ao transporte de fluxo nesta aresta.
     - `capacidade` é a capacidade máxima de fluxo nesta aresta.
     - `fluxo atual` é o fluxo existente na aresta.
     - `1` se a aresta pertencer à árvore inicial, `0` caso contrário.

4. **Raiz do Digrafo**
   - A última linha do arquivo de entrada contém o rótulo do vértice que será a raiz do digrafo. Exemplo:
     ```
     1
     ```

## Modo de Uso

Para executar o programa com uma entrada fornecida em um arquivo, siga os passos abaixo:

1. Salve a entrada no formato descrito acima em um arquivo de texto (por exemplo, `entrada.txt`).
2. Execute o programa no terminal com o comando:

```
python3 main.py < entrada.txt
```

Junto do código-fonte, foram dispinibilizadas 6 entradas, que correspondem aos problemas da terceira lista de exercícios.

## Saída do Programa

Após a execução do algoritmo, o programa imprimirá informações detalhadas sobre cada aresta do digrafo, indicando se está na base ou não e o seu fluxo atual.

Além disso, uma imagem `.png` será gerada representando o digrafo resultante com as seguintes características:

- **Arestas em azul**: representam arestas que pertencem à árvore inicial e podem estar saturadas.
- **Arestas em vermelho**: representam arestas saturadas que não estão na base.
- **Arestas em cinza**: representam as demais arestas não pertencentes à árvore e não saturadas.

O valor do fluxo da aresta estará próximo dela.

* OBS: Foi necessária a consulta em sites na internet para realizar a implementação da geração da imagem em PNG. 