package conversores;

public class CelsiusParaKelvin extends Conversor {
    public Conversor clone(){
        return new CelsiusParaKelvin();
    }
    public Double converter(Double temperatura){
        return temperatura+273;
    }
}
