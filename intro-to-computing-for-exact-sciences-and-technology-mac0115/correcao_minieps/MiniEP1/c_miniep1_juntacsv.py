import os
import csv

def process_csv_files(directory, output_filename):
    hardware_data = []
    software_data = []

    # Percorre todos os arquivos no diretório
    for filename in os.listdir(directory):
        if filename.endswith(".csv"):
            filepath = os.path.join(directory, filename)
            with open(filepath, mode='r', encoding='utf-8') as csvfile:
                csvreader = csv.reader(csvfile)
                current_category = None
                
                for row in csvreader:
                    if row:
                        if row[0] == "Hardware":
                            current_category = "Hardware"
                        elif row[0] == "Software":
                            current_category = "Software"
                        else:
                            if current_category == "Hardware":
                                hardware_data.append(row)
                            elif current_category == "Software":
                                software_data.append(row)

    # Escreve os dados combinados no arquivo de saída
    with open(output_filename, mode='w', newline='', encoding='utf-8') as csvfile:
        csvwriter = csv.writer(csvfile)
        if hardware_data:
            csvwriter.writerow(["Hardware"])
            csvwriter.writerows(hardware_data)
        if software_data:
            csvwriter.writerow(["Software"])
            csvwriter.writerows(software_data)

# Exemplo de uso
directory = '.'
output_filename = 'saida_combinada.csv'
process_csv_files(directory, output_filename)
