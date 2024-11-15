package conversores;

public class FarParaKelvin extends Conversor {
    public Conversor clone(){
        return new FarParaKelvin();
    }
    public Double converter(Double temperatura){
        return (5 * (temperatura - 32) / 9) + 273;
    }
}
