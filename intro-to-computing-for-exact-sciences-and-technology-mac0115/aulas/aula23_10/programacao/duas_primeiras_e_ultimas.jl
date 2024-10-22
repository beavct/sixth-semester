function twofirst_twolast(s::String)::String
    # Se o tamanho for menor do que 2, não tem como pegar as duas primerias e as duas últimas
    if length(s) < 2
        return ""
    else
        return s[1:2] * s[end-1:end]
    end
end

println("Resultado: ", twofirst_twolast(ARGS[1]))
