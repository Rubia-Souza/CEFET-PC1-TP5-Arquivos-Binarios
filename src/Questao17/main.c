#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../utils/fileUtils.h"

#define MAX_AMOUNT_COLUMNS 5
#define MAX_AMOUNT_ROWS 5
#define MAX_CITIES 10

const char OUTPUT_FOLDER[_MAX_DIR] = "..\\Questao16\\output\\";
const char OUTPUT_MATRIX_FILE_NAME[_MAX_FNAME] = "distance_matrix.bin";

int fillMatrixFromFile(unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const char filePath[_MAX_PATH]);
unsigned int getAmountCitiesCount();
unsigned int* getCitiesVector(const unsigned int amountVisitedCities);
unsigned int distance(const unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const unsigned int cities[MAX_CITIES], const unsigned int amountCitesCount);

int main() {
    unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS];

    char fileFullPath[_MAX_PATH];
    strcpy(fileFullPath, OUTPUT_FOLDER);
    strcat(fileFullPath, OUTPUT_MATRIX_FILE_NAME);

    int hasError = fillMatrixFromFile(distanceBetweenCities, fileFullPath);
    if(hasError == -1) {
        printf("\nArquivo com a distância entre as cidades não encontrado.");
        return 0;
    }

    unsigned int amountVisitedCities = getAmountCitiesCount();
    unsigned int* cities = getCitiesVector(amountVisitedCities);
    unsigned int totalDistance = distance(distanceBetweenCities, cities, amountVisitedCities);

    printf("\nA distancia total percorrida entre as cidades foi de: %d", totalDistance);

    return 0;
}

int fillMatrixFromFile(unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const char filePath[_MAX_PATH]) {
    FILE* matrixFile = fopen(filePath, "rb");
    if(matrixFile == NULL) {
        return -1;
    }
    
    for(int i = 0; i < MAX_AMOUNT_ROWS; i++) {
        for(int j = 0; j < MAX_AMOUNT_COLUMNS; j++) {
            fread(&distanceBetweenCities[i][j], sizeof(unsigned int), 1, matrixFile);
            printf("%d ", distanceBetweenCities[i][j]);
        }

        printf("\n");
    }

    return 0;
}

unsigned int* getCitiesVector(const unsigned int amountVisitedCities) {
    unsigned int* cities = (unsigned int*) malloc(MAX_AMOUNT_ROWS * sizeof(unsigned int));
    int input = 0;
    bool isInputValid = false;

    printf("\nInforme as cidades visitadas ou 0 para parar de informá-las");
    for(int i = 0; i < amountVisitedCities; i++) {
        printf("\n[Entrada %d de %d] Digite uma cidade visitada entre 1 e %d: ", i+1, amountVisitedCities, MAX_AMOUNT_ROWS);

        do {
            scanf("%d", &input);
            fflush(stdin);

            isInputValid = input >= 1 && input <= MAX_AMOUNT_ROWS;
            if(!isInputValid) {
                printf("\n[Entrada %d de %d] Por favor, digite um número de cidade válido (entre 1 e %d): ", i+1, amountVisitedCities, MAX_AMOUNT_ROWS);
            }
        } while(!isInputValid);
        
        cities[i] = input;
    }

    return cities;
}

unsigned int getAmountCitiesCount() {
    unsigned int input = 0;
    bool isInputValid = false;

    printf("\nInforme a quantidade de cidades que foram visitadas: ");
    do {
        scanf("%d", &input);
        fflush(stdin);

        isInputValid = input >= 1 && input <= MAX_CITIES;
        if(!isInputValid) {
            printf("\nPor favor, informe um valor válido (entre 1 e 10): ");
        }
    } while(!isInputValid);

    return input;
}

unsigned int distance(const unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS], const unsigned int cities[MAX_CITIES], const unsigned int amountCitesCount) {
    unsigned int totalDistance = 0;

    for(int i = 0, j = 1; j < amountCitesCount; i++, j++) {
        unsigned int citie1 = cities[i]-1;
        unsigned int citie2 = cities[j]-1;
        totalDistance += distanceBetweenCities[citie1][citie2];
    }

    return totalDistance;
}
