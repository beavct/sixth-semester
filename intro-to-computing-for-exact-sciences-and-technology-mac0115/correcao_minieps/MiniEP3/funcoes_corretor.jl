function calculaArea_corretor(tipo, base, altura)
    if tipo == 0
        return calculaAreaTriangulo_corretor(base, altura)
    elseif tipo == 1
        return calculaAreaRetangulo_corretor(base, altura)
    end

end

function calculaAreaTriangulo_corretor(base, altura)
    base = parse(Float64, base)
    altura = parse(Float64, altura)

    return (base*altura)/2
end

function calculaAreaRetangulo_corretor(base, altura)
    base = parse(Float64, base)
    altura = parse(Float64, altura)

    return base*altura
end

tipo = 1
base = "2.0"      
altura = "3.0"    
area = calculaArea_corretor(tipo, base, altura)
println(area)