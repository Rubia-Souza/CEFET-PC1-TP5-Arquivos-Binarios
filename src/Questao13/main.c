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

/*
 * @description: Define a pasta do arquivo de saida
 */
const char OUTPUT_FILE_FOLDER[_MAX_DIR] = ".\\output\\";

/*
 * @description: Define o nome do arquivo texto de saida
 */
const char OUTPUT_TEXT_FILE_NAME[_MAX_FNAME] = "test%d.txt";

/*
 * @description: Define o nome do arquivo binário de saida
 */
const char OUTPUT_BINARY_FILE_NAME[_MAX_FNAME] = "test%d.bin";

/*
 * @description: Define uma enumeração para as opções do menu
 */
enum MENU_OPTIONS {
    TEST_ONE = 1,
    TEST_TWO = 2,
    TEST_THREE = 3,
    EXIT = 4,
} MENU_OPTIONS;

/*
 * @description: Renderiza o menu de opções
 */
void printMenu();

/*
 * @description: Obtem a opção escolhida pelo usuário
 * @return: retorna o inteiro correspondente a opção escolhida
 */
unsigned int getChosenOption();

/*
 * @description: Prenche um array de inteiros, que é escrito, tanto em um arquivo binário quanto texto, e depois informa o tamanho dos dois arquivos
 * @param: start é o número incial da sequência que será preenchida no array
 * @param: end é o número final da sequência que será preenchida no array
 * @param: testNumber é o caso de teste escolhido pelo usuário no menu
 */
void testRange(const unsigned int start, const unsigned int end, const unsigned int testNumber);

/*
 * @description: Grava um array de inteiros em um arquivo texto
 * @param: testArray é o array de inteiros que será gravado no arquivo
 * @param: fileName é o nome do arquivo que será criado
 * @return: Um poteiro para o arquivo criado
 */
FILE* writeTextFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]);

/*
 * @description: Grava um array de inteiros em um arquivo binário
 * @param: testArray é o array de inteiros que será gravado no arquivo
 * @param: fileName é o nome do arquivo que será criado
 * @return: Um poteiro para o arquivo criado
 */
FILE* writeBinaryFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]);

/*
 * @description: Exibe o tamanho de um arquivo com base na posição final do ponteiro
 * @param: file é o arquivo que será avaliado
 * @param: fileName é o nome do arquivo que será avaliado
 */
void printFileSize(FILE* file, const char fileName[_MAX_FNAME]);

/*
 * @description: Cria um array de inteiros com números variando entre uma faixa definida
 * @param: start é o começo dos números que serão usados para preencher o array
 * @param: end é o maior número que o array poderá conter
 * @return: Um array de inteiros não nulos
 */
unsigned int* createFilledArray(const unsigned int start, const unsigned int end);

int main() {
    unsigned int chosenOption = 0;
    
    do {
        // Pede ao usuário para escolher um caso de teste
        printMenu();
        chosenOption = getChosenOption();

        // Verifica qual caso de teste foi escolhido
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
    // Printa as opções do menu
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

    // Lê a opção escolhida pelo usuário
    do {
        scanf("%d", &chosenOption);
        fflush(stdin);

        isInputValid = chosenOption >= TEST_ONE && chosenOption <= EXIT; // Caso o usuário informe uma opção inválida
        if(!isInputValid) { // O sistema pede para infomá-la corretamente
            printf("\nPor favor digite um valor válido (entre %d e %d): ", TEST_ONE, EXIT);
        }
    } while(!isInputValid);

    // Retorna a oção escolhida pelo usuário
    return chosenOption;
}

void testRange(const unsigned int start, const unsigned int end, const unsigned int testNumber) {
    // Cria o array de teste na faixa definida
    unsigned int* testArray = createFilledArray(start, end);
    
    // Define o nome do arquivo texto que terá o resultado
    char* textFileName = (char*) malloc(_MAX_FNAME * sizeof(char));
    sprintf(textFileName, OUTPUT_TEXT_FILE_NAME, testNumber);

    // Define o nome do arquivo binário que terá o resultado
    char* binaryFileName = (char*) malloc(_MAX_FNAME * sizeof(char));
    sprintf(binaryFileName, OUTPUT_BINARY_FILE_NAME, testNumber);

    // Cria o arquivo texto com o array de inteiros
    FILE* textFile = writeTextFile(testArray, textFileName);
    printFileSize(textFile, textFileName); // Exibe o tamanho do arquivo texto criado
    free(textFileName);
    fclose(textFile);


    // Cria o arquivo binário com o array de inteiros
    FILE* binaryFile = writeBinaryFile(testArray, binaryFileName);
    printFileSize(binaryFile, binaryFileName); // Exibe o tamanho do arquivo binário criado
    free(binaryFileName);
    fclose(binaryFile);

    return;
}

unsigned int* createFilledArray(const unsigned int start, const unsigned int end) {
    // Aloca o array de interios
    unsigned int* resultArray = (int*) malloc(MAX_INT_ARRAY_SIZE * sizeof(unsigned int));

    // Preenche o array de interios a partir do valor inicial até o final
    for(int i = 0, number = start; i < MAX_INT_ARRAY_SIZE; i++) {
        resultArray[i] = number;

        if(number == end) { // Caso atinja o valor final
            number = start; // A variável number volta para o inicial
        }
        else {
            number++;
        }
    }
    
    // Retorna o array de inteiros criado
    return resultArray;
}

FILE* writeTextFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]) {
    // Cria a pasta do arquivo
    createFolder(OUTPUT_FILE_FOLDER);

    // Monta o caminho do arquivo
    char fileFullPath[_MAX_PATH];
    strcpy(fileFullPath, OUTPUT_FILE_FOLDER);
    strcat(fileFullPath, fileName);

    // Cria o arquivo de texto
    createFile(fileFullPath);
    FILE* textFile = fopen(fileFullPath, "w");

    // Preenhce o arquivo texto com os valores do array de interios
    for(int i = 0; i < MAX_INT_ARRAY_SIZE; i++) {
        if(i != MAX_INT_ARRAY_SIZE-1) {
            fprintf(textFile, "%d ", testArray[i]);
        }
        else {
            fprintf(textFile, "%d", testArray[i]);
        }
    }

    // Retorna o ponteiro para o arquivo criado
    return textFile;
}

FILE* writeBinaryFile(const unsigned int* testArray, const char fileName[_MAX_FNAME]) {
    // Cria a pasta do arquivo
    createFolder(OUTPUT_FILE_FOLDER);

    // Monta o caminho do arquivo
    char fileFullPath[_MAX_PATH];
    strcpy(fileFullPath, OUTPUT_FILE_FOLDER);
    strcat(fileFullPath, fileName);

    // Cria o arquivo binário
    createFile(fileFullPath);
    FILE* binaryFile = fopen(fileFullPath, "wb");

    // Preenche o arquivo binário com os valores do array de interios
    for(int i = 0; i < MAX_INT_ARRAY_SIZE; i++) {
        fwrite(&testArray, sizeof(unsigned int), 1, binaryFile);
    }

    // Retorna um ponteiro para o arquivo criado
    return binaryFile;
}

void printFileSize(FILE* file, const char fileName[_MAX_FNAME]) {
    // Move o ponteiro para a posição final do arquvio
    fseek(file, 0L, SEEK_END);
    long int fileSize = ftell(file); // Verifica o tamanho total do arquivo

    printf("\nO arquivo %s possui o tamanho: %ld.", fileName, fileSize); // Exibe o tamanho total do arquivo
    return;
}
