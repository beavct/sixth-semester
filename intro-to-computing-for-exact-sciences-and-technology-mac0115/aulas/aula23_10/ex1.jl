# Concatena as primeiras duas e as últimas duas letras de uma string
function concatena(s::String)::String
    if length(s)<2
        return "Erro: tamanho da string menor do que 2"
    end
    # resposta = s[1:2]*s[end-1:end]
    resposta = s[1]*s[5]*s[end-1:end]
    return resposta
end 

println("Resultado:", concatena(ARGS[1]))