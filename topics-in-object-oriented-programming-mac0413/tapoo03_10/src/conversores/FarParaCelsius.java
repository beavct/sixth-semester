package conversores;

public class FarParaCelsius extends Conversor {
    public Conversor clone(){
        return new FarParaCelsius();
    }
    public Double converter(Double temperatura){
        return ((temperatura - 32) * 5) / 9;
    }
}
