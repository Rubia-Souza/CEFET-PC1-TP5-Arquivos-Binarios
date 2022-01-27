#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils/fileUtils.h"

#define MAX_PHRASE_SIZE 200

char* getFilePath();
char* getSearchPhrase();
FILE* tryOpenFile();
void toLower(char phrase[]);

int main() {
    FILE* targetFile = tryOpenFile();
    char* phraseToSearch = getSearchPhrase();
    toLower(phraseToSearch);

    char test[MAX_PHRASE_SIZE];
    unsigned int amountOcurrences = 0;
    while(fscanf(targetFile, "%s", &test) == 1) {
        toLower(test);

        if(strstr(test, phraseToSearch) != NULL) {
            amountOcurrences++;
        }
    }
    
    printf("\nA frases: %s ocorreu %d vezes no arquivo", phraseToSearch, amountOcurrences);

    return 0;
}

char* getFilePath() {
    char* filePath = (char*) malloc(_MAX_PATH * sizeof(char));

    printf("\nInforme o caminho do arquivo de entrada: ");
    fgets(filePath, _MAX_PATH, stdin);
    fflush(stdin);

    filePath[strcspn(filePath, "\n")] = '\000';
    return filePath;
}

char* getSearchPhrase() {
    char* phrase = (char*) malloc(MAX_PHRASE_SIZE * sizeof(char));

    printf("\nQual frase devo buscar: ");
    fgets(phrase, MAX_PHRASE_SIZE, stdin);
    fflush(stdin);

    phrase[strcspn(phrase, "\n")] = '\000';
    return phrase;
}

FILE* tryOpenFile() {
    char* filePath = getFilePath();
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
        file = tryOpenFile();
        return file;
    }

    return NULL;
}

void toLower(char phrase[]) {
    for(int i = 0; phrase[i] != '\000'; i++){
        phrase[i] = tolower(phrase[i]);
    }

    return;
}
