import conversores.Conversor;
import conversores.FabricaConversor;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        FabricaConversor fabricaConversor = new FabricaConversor();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("Escala de origem: ");
            String origem_escala = scanner.nextLine().toLowerCase();

            System.out.print("Valor de origem: ");
            double valor = scanner.nextDouble();
            scanner.nextLine();

            System.out.print("Escala de destino: ");
            String destino_escala = scanner.nextLine().toLowerCase();

            String tipoConversor = origem_escala + "-" + destino_escala;

            Conversor conversor = fabricaConversor.create(tipoConversor);
            
            System.out.printf("%n%.2f %s é igual a %.2f %s%n", valor, origem_escala, conversor.converter(valor), destino_escala);
        }

    }
}
