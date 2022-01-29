#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../utils/fileUtils.h"

#define MAX_INT_ARRAY_SIZE 100

#define FIRST_TEST_START_VALUE 0
#define FIRST_TEST_END_VALUE 9

#define SECOND_TEST_START_VALUE 1000
#define SECOND_TEST_END_VALUE 9999

#define THIRD_TEST_START_VALUE 10000
#define THIRD_TEST_END_VALUE 99999

const char OUTPUT_FILE_FOLDER[_MAX_DIR] = ".\\output\\";
const char OUTPUT_TEXT_FILE_NAME[_MAX_FNAME] = "test%d.txt";
const char OUTPUT_BINARY_FILE_NAME[_MAX_FNAME] = "test%d.bin";

enum MENU_OPTIONS {
    TEST_ONE = 1,
    TEST_TWO = 2,
    TEST_THREE = 3,
    EXIT = 4,
} MENU_OPTIONS;

void printMenu();
unsigned int getChosenOption();
void testRange(const unsigned int start, const unsigned int end, const unsigned int testNumber);
FILE* writeTextFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]);
FILE* writeBinaryFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]);
void printFileSize(FILE* file, const char fileName[_MAX_FNAME]);
unsigned int* createFilledArray(const unsigned int start, const unsigned int end);

int main() {
    unsigned int chosenOption = 0;
    
    do {
        printMenu();
        chosenOption = getChosenOption();

        switch (chosenOption) {
            case (TEST_ONE):
                testRange(FIRST_TEST_START_VALUE, FIRST_TEST_END_VALUE, TEST_ONE);
            break;
            
            case (TEST_TWO):
                testRange(SECOND_TEST_START_VALUE, SECOND_TEST_END_VALUE, TEST_TWO);
            break;
            
            case (TEST_THREE):
                testRange(THIRD_TEST_START_VALUE, THIRD_TEST_END_VALUE, TEST_THREE);
            break;
        }
    } while(chosenOption != EXIT);

    return 0;
}

void printMenu() {
    printf("\n------ Testes Array ------");
    printf("\n[1] Testar array entre %d e %d", FIRST_TEST_START_VALUE, FIRST_TEST_END_VALUE);
    printf("\n[2] Testar array entre %d e %d", SECOND_TEST_START_VALUE, SECOND_TEST_END_VALUE);
    printf("\n[3] Testar array entre %d e %d", THIRD_TEST_START_VALUE, THIRD_TEST_END_VALUE);
    printf("\n[4] Sair");

    return;
}

unsigned int getChosenOption() {
    unsigned int chosenOption = 0;
    bool isInputValid = false;
    printf("\n\nEscolha uma das opções: ");

    do {
        scanf("%d", &chosenOption);
        fflush(stdin);

        isInputValid = chosenOption >= TEST_ONE && chosenOption <= EXIT;
        if(!isInputValid) {
            printf("\nPor favor digite um valor válid (entre %d e %d): ", TEST_ONE, EXIT);
        }
    } while(!isInputValid);

    return chosenOption;
}

void testRange(const unsigned int start, const unsigned int end, const unsigned int testNumber) {
    unsigned int* testArray = createFilledArray(start, end);
    
    char* textFileName = (char*) malloc(_MAX_FNAME * sizeof(char));
    sprintf(textFileName, OUTPUT_TEXT_FILE_NAME, testNumber);

    char* binaryFileName = (char*) malloc(_MAX_FNAME * sizeof(char));
    sprintf(binaryFileName, OUTPUT_BINARY_FILE_NAME, testNumber);

    FILE* textFile = writeTextFile(testArray, textFileName);
    printFileSize(textFile, textFileName);
    free(textFileName);
    fclose(textFile);

    FILE* binaryFile = writeBinaryFile(testArray, binaryFileName);
    printFileSize(binaryFile, binaryFileName);
    free(binaryFileName);
    fclose(binaryFile);

    return;
}

unsigned int* createFilledArray(const unsigned int start, const unsigned int end) {
    unsigned int* resultArray = (int*) malloc(MAX_INT_ARRAY_SIZE * sizeof(unsigned int));

    for(int i = 0, number = start; i < MAX_INT_ARRAY_SIZE; i++) {
        resultArray[i] = number;

        if(number == end) {
            number = start;
        }
        else {
            number++;
        }
    }
    
    return resultArray;
}

FILE* writeTextFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]) {
    createFolder(OUTPUT_FILE_FOLDER);

    char fileFullPath[_MAX_PATH];
    strcpy(fileFullPath, OUTPUT_FILE_FOLDER);
    strcat(fileFullPath, fileName);

    createFile(fileFullPath);
    FILE* textFile = fopen(fileFullPath, "w");

    for(int i = 0; i < MAX_INT_ARRAY_SIZE; i++) {
        if(i != MAX_INT_ARRAY_SIZE-1) {
            fprintf(textFile, "%d ", testArray[i]);
        }
        else {
            fprintf(textFile, "%d", testArray[i]);
        }
    }

    return textFile;
}

FILE* writeBinaryFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]) {
    createFolder(OUTPUT_FILE_FOLDER);

    char fileFullPath[_MAX_PATH];
    strcpy(fileFullPath, OUTPUT_FILE_FOLDER);
    strcat(fileFullPath, fileName);

    createFile(fileFullPath);
    FILE* binaryFile = fopen(fileFullPath, "wb");

    for(int i = 0; i < MAX_INT_ARRAY_SIZE; i++) {
        fwrite(&testArray, MAX_INT_ARRAY_SIZE * sizeof(unsigned int), 1, binaryFile);
    }

    return binaryFile;
}

void printFileSize(FILE* file, const char fileName[_MAX_FNAME]) {
    fseek(file, 0L, SEEK_END);
    long int fileSize = ftell(file);

    printf("\nO arquivo %s possui o tamanho: %ld.", fileName, fileSize);
    return;
}
