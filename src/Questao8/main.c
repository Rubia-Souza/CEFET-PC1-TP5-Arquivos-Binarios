#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils/fileUtils.h"
#include "../utils/stringUtils.h"

#define MAX_PHRASE_SIZE 200

/*
 * @description: Pede ao usuário para informar o caminho de um arquivo
 * @return: Uma string contendo o caminho do arquivo informado
 */
char* getFilePath();

/*
 * @description: Pede ao usuário a string que será procurada no arquivo
 * @return: A string que será referência para contar as ocorrências no arquivo
 */
char* getSearchPhrase();

/*
 * @description: Tenta abrir o arquivo informado pelo usuário
 * @return: Retorna um ponteiro para o arquivo aberto ou NULL em caso de erro
 */
FILE* tryOpenFile();

int main() {
    // Abre o arquivo será a referência para fazer a busca pela string
    FILE* targetFile = tryOpenFile();
    if(targetFile == NULL) { // Se o arquivo não foi encotrado
        return 0; // Encerra a execução
    }

    // Define a palavra que será buscada no arquivo
    char* phraseToSearch = getSearchPhrase();
    toLower(phraseToSearch);

    // Percorre cada palavra do arquivo
    char actualWord[MAX_PHRASE_SIZE];
    unsigned int amountOcurrences = 0;
    while(fscanf(targetFile, "%s", &actualWord) == 1) {
        toLower(actualWord);

        // Verifica se a palavra que será buscada é uma substring da palavra atual
        if(strstr(actualWord, phraseToSearch) != NULL) {
            amountOcurrences++; // Se for, o contador é incrementado
        }
    }
    
    // Fecha o arquivo e informa a quantidade de ocorrências da palavra informada
    fclose(targetFile);
    printf("\nA frases: %s ocorreu %d vezes no arquivo", phraseToSearch, amountOcurrences);

    return 0;
}

char* getFilePath() {
    // Aloca a string que terá o caminho do arquivo
    char* filePath = (char*) malloc(_MAX_PATH * sizeof(char));

    // Lê a string informada pelo usuário
    printf("\nInforme o caminho do arquivo de entrada: ");
    fgets(filePath, _MAX_PATH, stdin);
    fflush(stdin);

    // Substitui o \n por fim de string
    filePath[strcspn(filePath, "\n")] = '\000';
    return filePath;
}

char* getSearchPhrase() {
    // Aloca a string que terá a frase a ser buscada
    char* phrase = (char*) malloc(MAX_PHRASE_SIZE * sizeof(char));

    // Lê a palavra informada pelo usuário
    printf("\nQual frase devo buscar: ");
    fgets(phrase, MAX_PHRASE_SIZE, stdin);
    fflush(stdin);

    // Substitui o \n por fim de string
    phrase[strcspn(phrase, "\n")] = '\000';
    return phrase;
}

FILE* tryOpenFile() {
    // Obtem o caminho do arquivo alvo
    char* filePath = getFilePath();
    // Tenta abrir o arquivo
    FILE* file = fopen(filePath, "r");
    bool wasSuccessful = file != NULL;

    if(wasSuccessful) { // Caso tenha sido concluído sem erros
        return file; // retorna o ponteiro do arquivo
    }

    // Caso não tenha sido possível abrir
    // Pergunta ao usuário se deseja tentar novamente
    char input;
    printf("\nArquivo informado não encontrado.");
    printf("\nDeseja tentar novamente (s/n)? ");
    scanf("%c", &input);
    fflush(stdin);

    // Verifica se o input é inválido
    toLower(&input);
    bool isInputInvalid = input != 'n' && input != 's';
    while (isInputInvalid) { // caso seja o sistema pede para informá-lo corretamente
        printf("\nPor favor, informe um valor válido");
        printf("\nDeseja tentar novamente (s/n)? ");

        scanf("%c", &input);
        fflush(stdin);
        
        isInputInvalid = input != 'n' && input != 's';
    }

    // Caso o usuário deseje tentar novamente
    if(input == 's') {
        file = tryOpenFile(); // O sistema tenta de novo abrir o arquivo
        return file;
    }

    // Caso contrário, é retornado NULL
    return NULL;
}
