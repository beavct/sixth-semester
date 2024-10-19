using DataFrames, CSV, Plots

function plot_movies()

    # Lendo os dados do arquivo CSV
    csv_data = CSV.File("movies.csv")
    df = DataFrame(csv_data)

    # Definindo o intervalo de anos que queremos filtrar
    ano_inicial = 1990
    ano_final = 2000 

    # Filtrando apenas os filmes da década de 90
    filmes_90s = filter(row -> !ismissing(row.year) && !ismissing(row.rating) && 
    row.year >= ano_inicial && row.year < ano_final, df)

    # Criando uma lista para armazenar todas as classificações
    all_ratings = Float64[]

    for year in 1990:1999
        # Filtrando as classificações dos filmes para o ano atual
        ratings = filmes_90s[filmes_90s.year .== year, :rating]
        
        # Adicionando as classificações ao vetor all_ratings
        append!(all_ratings, ratings)
    end

    # Configurando o tamanho da imagem
    plot(size=(1000, 600))

    # Plotando o histograma
    histogram(all_ratings, 
              bins=10,  # Número de bins do histograma
              xlabel="Avaliações", 
              ylabel="Frequência", 
              title="Histograma das avaliações dos filmes nos Anos 90",
              legend=false,
              color=:purple,
              xticks=0:10)

    # Salvando o gráfico gerado
    savefig("histograma_classificacoes_filmes_anos_90.png")

end