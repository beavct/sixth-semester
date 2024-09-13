function palindromo(num::Int)

    reverso=0
    auxiliar=num_str
    
    while auxiliar>0
        reverso = reverso*10 + auxiliar%10
        auxiliar = auxiliar/10
    end

    if reverse == num
        println("O número $num é palíndromo")
    else
        println("O número $num não é palíndromo")
    end

end