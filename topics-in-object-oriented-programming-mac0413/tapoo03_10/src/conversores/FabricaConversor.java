package conversores;

import java.util.HashMap;

public class FabricaConversor {
    HashMap<String, Conversor> prototipoDeConversor = new HashMap<>();

    public FabricaConversor()
    {
        prototipoDeConversor.put("celsius-fahrenheit", new CelsiusParaFar());
        prototipoDeConversor.put("celsius-kelvin", new CelsiusParaKelvin());

        prototipoDeConversor.put("fahrenheit-celsius", new FarParaCelsius());
        prototipoDeConversor.put("fahrenheit-kelvin", new FarParaKelvin());

        prototipoDeConversor.put("kelvin-fahrenheit", new KelvinParaFar());
        prototipoDeConversor.put("kelvin-celsius", new KelvinParaCelsius());
    }

    public Conversor create(String tipoConversor){
        return prototipoDeConversor.get(tipoConversor).clone();
    }
}
