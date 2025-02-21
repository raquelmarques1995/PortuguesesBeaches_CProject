# Management of Portuguese Beaches - C Project

## Description
This C project aims to manage data about Portuguese beaches, organized by locality. The application allows users to add, list, modify, and search for beaches and localities, as well as export the information to a CSV file.

## Features
The application menu offers the following options:

1. **Inserir Praia**: Allows you to add a new beach to the system.
2. **Inserir Localidade**: Allows you to add a new locality to the system.
3. **Listar Praias**: Displays all registered beaches.
4. **Listar Localidades**: Displays all registered localities.
5. **Listar Praias por Localidade**: Displays the beaches of a specific locality using its IDLocalidade.
6. **Procurar Praia**: Allows you to search for a beach by its name.
7. **Alterar Localidade**: Allows you to modify a locality's data using its IDLocalidade.
8. **Alterar Praia**: Allows you to modify a beach's data using its IDPraia.
9. **Exportar Praias para ficheiro CSV**: Exports the beaches to a CSV file, including the locality name, beach name, and beach type (oceânica or fluvial).

## Data Structure
The project uses two main files to store the data:

- Praias: Contains information about the beaches, including:
  - IDPraia (automatically generated)
  - Tipo (oceânica/fluvial)
  - IDLocalidade (references the ID of the locality)
- Localidades: Contains information about the localities, including:
  - IDLocalidade (automatically generated)

## Technologies Used
- Language: C
- Files: Text files for storing data

## How to Run
1. Compile the code using a C compiler. Example:
```bash
gcc -o gestao_praias programa.c
```

2. Run the program:
```bash
./programa
```
3. Follow the instructions in the menu to manage beaches and localities.
