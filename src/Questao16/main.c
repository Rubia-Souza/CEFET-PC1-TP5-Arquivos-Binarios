#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utils/fileUtils.h"

#define MAX_AMOUNT_COLUMNS 5
#define MAX_AMOUNT_ROWS 5

const char OUTPUT_FOLDER[_MAX_DIR] = ".\\output\\";
const char OUTPUT_MATRIX_FILE_NAME[_MAX_FNAME] = "distance_matrix.bin";

char* setupFile();

int main() {
    const unsigned int distanceBetweenCities[MAX_AMOUNT_COLUMNS][MAX_AMOUNT_ROWS] = {
        {0, 15, 30, 5, 12},
        {15, 0, 10, 17, 28},
        {30, 10, 0, 3, 11},
        {5, 17, 3, 0, 80},
        {12, 28, 11, 80, 0}
    };

    char* fullFilePath = setupFile();
    FILE* binFile = fopen(fullFilePath, "wb");

    for(int i = 0; i < MAX_AMOUNT_ROWS; i++) {
        for(int j = 0; j < MAX_AMOUNT_COLUMNS; j++) {
            fwrite(&distanceBetweenCities[i][j], sizeof(unsigned int), 1, binFile);
        }
    }

    fclose(binFile);
    return 0;
}

char* setupFile() {
    char* fullFilePath = (char*) malloc(_MAX_PATH * sizeof(char));

    createFolder(OUTPUT_FOLDER);
    strcpy(fullFilePath, OUTPUT_FOLDER);
    strcat(fullFilePath, OUTPUT_MATRIX_FILE_NAME);
    createFile(fullFilePath);

    return fullFilePath;
}
