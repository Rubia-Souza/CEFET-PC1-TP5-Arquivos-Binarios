#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/fileUtils.h"

#define MAX_AMOUNT_COLUMNS 5
#define MAX_AMOUNT_ROWS 5


/*
 * @description: Cria a pasta que terá os arquivos de saida
 */
const char OUTPUT_FOLDER[_MAX_DIR] = ".\\output\\";

/*
 * @description: Define o nome do arquivo de saida
 */
const char OUTPUT_MATRIX_FILE_NAME[_MAX_FNAME] = "distance_matrix.bin";

/*
 * @description: Configura a criação da pasta e do arquivo de saida
 * @return: Retorna o caminho completo para o arquivo de saida
 */
char* setupFile();

int main() {
    // Define a matriz de distâncias entre as cidades
    const unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS] = {
        {0, 15, 30, 5, 12},
        {15, 0, 10, 17, 28},
        {30, 10, 0, 3, 11},
        {5, 17, 3, 0, 80},
        {12, 28, 11, 80, 0}
    };

    // Cria a pasta e o arquivo de saida
    char* fullFilePath = setupFile();
    FILE* binFile = fopen(fullFilePath, "wb");

    // Preenche o arquivo de saida binário com a matriz de distância entre as cidades
    for(int i = 0; i < MAX_AMOUNT_ROWS; i++) {
        for(int j = 0; j < MAX_AMOUNT_COLUMNS; j++) {
            fwrite(&distanceBetweenCities[i][j], sizeof(unsigned int), 1, binFile);
        }
    }

    // Fecha o arquivo de saida
    fclose(binFile);
    return 0;
}

char* setupFile() {
    // Aloca a string para o caminho completo do arquivo de saida
    char* fullFilePath = (char*) malloc(_MAX_PATH * sizeof(char));

    // Cria a pasta dos arquvios de saida
    createFolder(OUTPUT_FOLDER);
    // Monta o caminho completo do arquivo de saida
    strcpy(fullFilePath, OUTPUT_FOLDER);
    strcat(fullFilePath, OUTPUT_MATRIX_FILE_NAME);
    // Cria o arquivo de saida
    createFile(fullFilePath);

    // Retorna o caminho completo do arquivo de saida
    return fullFilePath;
}
