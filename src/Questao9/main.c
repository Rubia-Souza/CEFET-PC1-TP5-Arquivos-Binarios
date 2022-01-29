#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../utils/fileUtils.h"
#include "../utils/stringUtils.h"

#define MAX_PHRASE_SIZE 200

const char TEMP_COPY_FILE_FOLDER[_MAX_DIR] = ".\\tempFolder\\";
const char TEMP_COPY_FILE_NAME[_MAX_FNAME] = "copyTempFile.txt";

char* getFilePath();
char* getRemovePhrase();
FILE* tryOpenFile(char filePath[_MAX_PATH]);
char* createCopyFile();
void replaceFiles(const char fileFullPath[_MAX_PATH]);

int main() {
    char* fileFullPath = getFilePath();
    FILE* targetFile = tryOpenFile(fileFullPath);
    if(targetFile == NULL) {
        return 0;
    }

    char* phraseToRemove = getRemovePhrase();
    toLower(phraseToRemove);

    char* copyFilePath = createCopyFile(fileFullPath);
    FILE* copyFile = fopen(copyFilePath, "w");

    char actualWord[MAX_PHRASE_SIZE];
    while(fscanf(targetFile, "%s", &actualWord) == 1) {
        char lowerTest[MAX_PHRASE_SIZE];
        strcpy(lowerTest, actualWord);
        toLower(lowerTest);

        if(strstr(lowerTest, phraseToRemove) == NULL) {
            fprintf(copyFile, "%s ", actualWord);
        }
        else {
            removeSubstring(lowerTest, phraseToRemove);
            fprintf(copyFile, "%s ", lowerTest);
        }
    }

    fclose(copyFile);
    fclose(targetFile);
    replaceFiles(fileFullPath);

    printf("\nArquivo atualizado!");
    return 0;
}

char* getFilePath() {
    char* filePath = (char*) malloc(_MAX_PATH * sizeof(char));

    printf("\nInforme o caminho do arquivo de entrada: ");
    fgets(filePath, _MAX_PATH, stdin);
    fflush(stdin);

    filePath[strcspn(filePath, "\n")] = '\000';
    trim(filePath);
    return filePath;
}

char* getRemovePhrase() {
    char* phrase = (char*) malloc(MAX_PHRASE_SIZE * sizeof(char));

    printf("\nQual frase devo remover: ");
    fgets(phrase, MAX_PHRASE_SIZE, stdin);
    fflush(stdin);

    phrase[strcspn(phrase, "\n")] = '\000';
    trim(phrase);
    return phrase;
}

FILE* tryOpenFile(char filePath[_MAX_PATH]) {
    FILE* file = fopen(filePath, "r");
    bool wasSuccessful = file != NULL;

    if(wasSuccessful) {
        return file;
    }

    char input;
    printf("\nArquivo informado não encontrado.");
    printf("\nDeseja tentar novamente (s/n)? ");
    scanf("%c", &input);
    fflush(stdin);

    toLower(&input);
    bool isInputInvalid = input != 'n' && input != 's';
    while (isInputInvalid) {
        printf("\nPor favor, informe um valor válido");
        printf("\nDeseja tentar novamente (s/n)? ");

        scanf("%c", &input);
        fflush(stdin);
        
        isInputInvalid = input != 'n' && input != 's';
    }

    if(input == 's') {
        strcpy(filePath, getFilePath());
        file = tryOpenFile(filePath);
        return file;
    }

    return NULL;
}

char* createCopyFile() {
    char* copyFilePath = (char*) malloc(_MAX_PATH * sizeof(char));

    strcpy(copyFilePath, TEMP_COPY_FILE_FOLDER);
    createFolder(copyFilePath);

    strcat(copyFilePath, TEMP_COPY_FILE_NAME);
    createFile(copyFilePath);

    return copyFilePath;
}

void replaceFiles(const char fileFullPath[_MAX_PATH]) {
    char copyFileActualLocation[_MAX_PATH];
    strcpy(copyFileActualLocation, TEMP_COPY_FILE_FOLDER);
    strcat(copyFileActualLocation, TEMP_COPY_FILE_NAME);

    char copyFileNewLocation[_MAX_PATH] = "";
    strcpy(copyFileNewLocation, fileFullPath);

    remove(fileFullPath);
    if(rename(copyFileActualLocation, copyFileNewLocation) != 0){
        printf("\nfuck!");
    }

    return;
}
