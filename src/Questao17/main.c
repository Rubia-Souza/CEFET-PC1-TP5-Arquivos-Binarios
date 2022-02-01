#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../utils/fileUtils.h"

#define MAX_AMOUNT_COLUMNS 5
#define MAX_AMOUNT_ROWS 5
#define MAX_CITIES 10

/*
 * @description: Define a pasta onde está o arquivo da distância entre as cidades
 */
const char OUTPUT_FOLDER[_MAX_DIR] = "..\\Questao16\\output\\";

/*
 * @description: Define o nome do arquivo da distância entre as cidades
 */
const char OUTPUT_MATRIX_FILE_NAME[_MAX_FNAME] = "distance_matrix.bin";

/*
 * @description: Preenche a matriz da distância entre as cidades por um arquivo binário
 * @param: distanceBetweenCities é a matriz que será preenchida com a distancia entre as cidades
 * @param: filePath é o caminho completo do arquivo que será lido para preencher a matriz
 * @return: Um inteiro positivo caso tenha conseguido ou -1 em caso de erro
 */
int fillMatrixFromFile(unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const char filePath[_MAX_PATH]);

/*
 * @description: Pede ao usuário a quantidade de cidades que foram visitadas
 * @return: Um inteiro positivo que é a quantidade de cidades visitadas
 */
unsigned int getAmountCitiesCount();

/*
 * @description: Pede ao usuário o número das cidades que foram visitadas
 * @param: amountVisitedCities é a quantidade de cidades visitadas
 * @return: Um array contendo as cidades visitadas em ordem
 */
unsigned int* getCitiesVector(const unsigned int amountVisitedCities);

/*
 * @description: Calcula a distância percorrida entre as cidades visitadas
 * @param: distancebetweenCities é um array com a distância entre cidades
 * @param: cities é um array que contem as cidades visitadas
 * @param: amountCitiesCount é a quantidade de cidades que foram visitadas
 * @return: Um inteiro positivo que é a distancia total percorrida para visitar as cidades
 */
unsigned int distance(const unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const unsigned int cities[MAX_CITIES], const unsigned int amountCitesCount);

int main() {
    unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS];

    // Monta o caminho do arquivo de leitura com a matriz de distância entre as cidades
    char fileFullPath[_MAX_PATH];
    strcpy(fileFullPath, OUTPUT_FOLDER);
    strcat(fileFullPath, OUTPUT_MATRIX_FILE_NAME);

    // Preenche a matriz de distância entre as cidades
    int hasError = fillMatrixFromFile(distanceBetweenCities, fileFullPath);
    if(hasError == -1) { // Caso ocorra algum erro
        printf("\nArquivo com a distância entre as cidades não encontrado.");
        return 0; // Programa encerra a execução
    }

    // Pede ao usuário a quantidade de cidades visitadas
    unsigned int amountVisitedCities = getAmountCitiesCount();
    // Pede ao usuário as cidades que foram visitadas
    unsigned int* cities = getCitiesVector(amountVisitedCities);
    // Calcula a distância total percorrida na vista das cidades
    unsigned int totalDistance = distance(distanceBetweenCities, cities, amountVisitedCities);

    // Exibe a distância total
    printf("\nA distancia total percorrida entre as cidades foi de: %d", totalDistance);

    return 0;
}

int fillMatrixFromFile(unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const char filePath[_MAX_PATH]) {
    // Abre o arquivo que contem a matriz com a distância entre as cidades
    FILE* matrixFile = fopen(filePath, "rb");
    if(matrixFile == NULL) { // Se não for possível
        return -1; // Retorna um código de errro
    }
    
    // Lê as entradas do arquivo e preenche a matriz de distância
    for(int i = 0; i < MAX_AMOUNT_ROWS; i++) {
        for(int j = 0; j < MAX_AMOUNT_COLUMNS; j++) {
            fread(&distanceBetweenCities[i][j], sizeof(unsigned int), 1, matrixFile);
            printf("%d ", distanceBetweenCities[i][j]);
        }

        printf("\n");
    }

    // Retorna o código de sucesso
    return 0;
}

unsigned int* getCitiesVector(const unsigned int amountVisitedCities) {
    // Aloca espaço para o array de inteiros de cidades
    unsigned int* cities = (unsigned int*) malloc(MAX_AMOUNT_ROWS * sizeof(unsigned int));
    int input = 0;
    bool isInputValid = false;

    // Pede ao usuário que informe quais cidades foram visitadas
    printf("\nInforme as cidades visitadas");
    for(int i = 0; i < amountVisitedCities; i++) {
        printf("\n[Entrada %d de %d] Digite uma cidade visitada entre 1 e %d: ", i+1, amountVisitedCities, MAX_AMOUNT_ROWS);

        do {
            scanf("%d", &input);
            fflush(stdin);

            // Verifica se o número da cidade é um número válido
            isInputValid = input >= 1 && input <= MAX_AMOUNT_ROWS;
            if(!isInputValid) { // Caso não seja, o programa pede para informá-lo novamente
                printf("\n[Entrada %d de %d] Por favor, digite um número de cidade válido (entre 1 e %d): ", i+1, amountVisitedCities, MAX_AMOUNT_ROWS);
            }
        } while(!isInputValid);
        
        cities[i] = input;
    }

    // Retorna o array de cidades
    return cities;
}

unsigned int getAmountCitiesCount() {
    unsigned int input = 0;
    bool isInputValid = false;

    // Pede ao usuário a quantidade de cidades visitadas
    printf("\nInforme a quantidade de cidades que foram visitadas: ");
    do {
        scanf("%d", &input);
        fflush(stdin);

        // Verifica se a quantidade informada é um valor válido
        isInputValid = input >= 1 && input <= MAX_CITIES;
        if(!isInputValid) { // Se for um valor inválido, o programa pede para informá-lo novamente
            printf("\nPor favor, informe um valor válido (entre 1 e 10): ");
        }
    } while(!isInputValid);

    // Retorna a quantidade de cidades visitadas
    return input;
}

unsigned int distance(const unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const unsigned int cities[MAX_CITIES], const unsigned int amountCitesCount) {
    unsigned int totalDistance = 0;

    // Percorre o array de cidades visitadas
    for(int i = 0, j = 1; j < amountCitesCount; i++, j++) {
        unsigned int citie1 = cities[i]-1; // Pega a cidade de saida
        unsigned int citie2 = cities[j]-1; // Pega a cidade de chegada
        totalDistance += distanceBetweenCities[citie1][citie2]; // Soma com o valor entre elas definido na matriz de distâncias
    }

    // Retorna o valor da distância total percorrida
    return totalDistance;
}
