import csv

def process_csv(input_filename, output_filename):
    categories = {}
    
    # Leitura do arquivo CSV
    with open(input_filename, mode='r', encoding='utf-8') as csvfile:
        csvreader = csv.reader(csvfile)
        
        # Processa o CSV linha a linha
        for row in csvreader:
            if len(row) == 2:
                category = row[0]
                count = int(row[1])
                categories[category] = []
                
                # Lê as próximas 'count' linhas
                for _ in range(count):
                    event_row = next(csvreader)
                    year = int(event_row[0])
                    description = event_row[1]
                    categories[category].append((year, description))
    
    # Ordena os eventos de cada categoria por ano
    for category in categories:
        categories[category].sort(key=lambda x: x[0])
    
    # Escreve os resultados em um arquivo de texto
    with open(output_filename, mode='w', encoding='utf-8') as txtfile:
        for category, events in categories.items():
            txtfile.write(f"{category}:\n")
            for year, description in events:
                txtfile.write(f"{year}: {description}\n")
            txtfile.write("\n")

# Exemplo de uso
input_filename = 'exemplo.csv'
output_filename = 'resultado.txt'
process_csv(input_filename, output_filename)
