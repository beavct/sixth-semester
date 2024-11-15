package conversores;

public class KelvinParaFar extends Conversor {
    public Conversor clone(){
        return new KelvinParaFar();
    }
    public Double converter(Double temperatura){
        return (9 * (temperatura - 273) / 5) + 32;
    }
}
