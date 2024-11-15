package conversores;

public class CelsiusParaFar extends Conversor {
    public Conversor clone(){
        return new CelsiusParaFar();
    }
    public Double converter(Double temperatura){
        return ((temperatura * 9) / 5) + 32;
    }
}
