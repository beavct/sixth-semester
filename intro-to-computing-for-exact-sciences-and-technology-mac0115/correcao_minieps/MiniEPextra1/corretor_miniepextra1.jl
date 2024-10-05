function quaseIgual(num1, num2, epsilon)
    return abs(num1-num2)<=epsilon
end

resultado = quaseIgual(sin(pi/4), 0.7071, 0.0001)

println("O resultado foi ", resultado)