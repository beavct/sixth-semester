package conversores;

public class KelvinParaCelsius extends Conversor {
    public Conversor clone(){
        return new KelvinParaCelsius();
    }
    public Double converter(Double temperatura){
        return temperatura-273;
    }

}
