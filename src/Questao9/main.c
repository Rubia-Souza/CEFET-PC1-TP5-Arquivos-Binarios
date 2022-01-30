#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../utils/fileUtils.h"
#include "../utils/stringUtils.h"

#define MAX_PHRASE_SIZE 200

/*
 * @description: Define a pasta de arquivos temporários do programa
 */
const char TEMP_COPY_FILE_FOLDER[_MAX_DIR] = ".\\tempFolder\\";

/*
 * @description: Define o nome do arquivo temporário de cópia do programa
 */
const char TEMP_COPY_FILE_NAME[_MAX_FNAME] = "copyTempFile.txt";

/*
 * @description: Pede ao usuário para informar o caminho de um arquivo
 * @return: Uma string contendo o caminho do arquivo informado
 */
char* getFilePath();

/*
 * @description: Pede ao usuário a string que será removida no arquivo
 * @return: A string que será referência para remover as ocorrências no arquivo
 */
char* getRemovePhrase();

/*
 * @description: Tenta abrir o arquivo informado pelo usuário
 * @param: filePath é o caminho do arquivo que tentará ser aberto
 * @return: Retorna um ponteiro para o arquivo aberto ou NULL em caso de erro
 */
FILE* tryOpenFile(char filePath[_MAX_PATH]);

/*
 * @description: Cria um arquivo temporário para cópia de informações
 * @return: O caminho absoluto do arquivo criado
 */
char* createCopyFile();

/*
 * @description: Substitiui o arquivo informado pelo arquivo temporário do programa
 * @param: fileFullPath é o caminho completo do arquivo que será substituido
 */
void replaceFiles(const char fileFullPath[_MAX_PATH]);

int main() {
    // Obtem o caminho do arquivo que será referencia
    char* fileFullPath = getFilePath();
    // Tenta abrir o arquivo no caminho informado
    FILE* targetFile = tryOpenFile(fileFullPath);
    if(targetFile == NULL) { // caso não seja possível
        return 0; // O programa termina a execução
    }

    // Obtem a palavra que será removida do arquivo
    char* phraseToRemove = getRemovePhrase();
    toLower(phraseToRemove);

    // Cria um arquivo temporário para salvar os dados com a palavra removida
    char* copyFilePath = createCopyFile(fileFullPath);
    FILE* copyFile = fopen(copyFilePath, "w");

    // Percorre o arquivo de referência
    char actualWord[MAX_PHRASE_SIZE];
    while(fscanf(targetFile, "%s", &actualWord) == 1) {
        char lowerTest[MAX_PHRASE_SIZE];
        strcpy(lowerTest, actualWord);
        toLower(lowerTest);

        if(strstr(lowerTest, phraseToRemove) == NULL) { // Para cada palavra que não é a alvo
            fprintf(copyFile, "%s ", actualWord); // É copiada para o arquivo temporário
        }
        else { // Para cada palavra que tenha uma substring da palavra a ser removida
            removeSubstring(lowerTest, phraseToRemove); // Remove a substring da referência
            fprintf(copyFile, "%s ", lowerTest); // Escreve no arquivo copia o restante da string
        }
    }

    // Fecha os dois arquivos
    fclose(copyFile);
    fclose(targetFile);
    // Substitui o arquivo original pelo arquivo de cópia com as palavras removidas
    replaceFiles(fileFullPath);

    printf("\nArquivo atualizado!");
    return 0;
}

char* getFilePath() {
    // Aloca espaço para o caminho do arquivo
    char* filePath = (char*) malloc(_MAX_PATH * sizeof(char));

    // Lê o caminho do arquivo informado pelo usuário
    printf("\nInforme o caminho do arquivo de entrada: ");
    fgets(filePath, _MAX_PATH, stdin);
    fflush(stdin);

    // Substitui o \n por fim da string
    filePath[strcspn(filePath, "\n")] = '\000';
    trim(filePath); // Remove possíveis espaços desnecessários
    return filePath;
}

char* getRemovePhrase() {
    // Aloca espaço para a palavra que será removida
    char* phrase = (char*) malloc(MAX_PHRASE_SIZE * sizeof(char));

    // Lê a palavra desejada pelo usuário
    printf("\nQual frase devo remover: ");
    fgets(phrase, MAX_PHRASE_SIZE, stdin);
    fflush(stdin);

    // Substitui o \n por fim da string
    phrase[strcspn(phrase, "\n")] = '\000';
    trim(phrase); // Remove possíveis espaços desnecessários
    return phrase;
}

FILE* tryOpenFile(char filePath[_MAX_PATH]) {
    // Abre o caminho informado
    FILE* file = fopen(filePath, "r");
    bool wasSuccessful = file != NULL;

    if(wasSuccessful) { // Caso tenha ocorrido corretamente
        return file; // Retorna um ponteiro para o arquivo aberto
    }

    // Caso não seja possível
    // O programa pergunta ao usuário se deseja tentar novamente
    char input;
    printf("\nArquivo informado não encontrado.");
    printf("\nDeseja tentar novamente (s/n)? ");
    scanf("%c", &input);
    fflush(stdin);

    // Verifica se o input informado pelo usuário é inválido
    toLower(&input);
    bool isInputInvalid = input != 'n' && input != 's';
    while (isInputInvalid) { // Se sim, ele pede ao usuário para informá-lo corretamente
        printf("\nPor favor, informe um valor válido");
        printf("\nDeseja tentar novamente (s/n)? ");

        scanf("%c", &input);
        fflush(stdin);
        
        isInputInvalid = input != 'n' && input != 's';
    }

    // Caso o usuário deseje tentar novamente
    if(input == 's') {
        strcpy(filePath, getFilePath());
        file = tryOpenFile(filePath); // O programa tenta abrir o novo caminho informado
        return file;
    }

    // Caso contrário, o programa retorna NULL
    return NULL;
}

char* createCopyFile() {
    // Aloca string para o caminho do arquivo criado
    char* copyFilePath = (char*) malloc(_MAX_PATH * sizeof(char));

    // Cria a pasta de arquivos temporários
    strcpy(copyFilePath, TEMP_COPY_FILE_FOLDER);
    createFolder(copyFilePath);

    // Cria o arquivo temporário de copia
    strcat(copyFilePath, TEMP_COPY_FILE_NAME);
    createFile(copyFilePath);

    // Retorna o caminho do arquivo temporário
    return copyFilePath;
}

void replaceFiles(const char fileFullPath[_MAX_PATH]) {
    // Monta o caminho atual do arquivo temporário
    char copyFileActualLocation[_MAX_PATH];
    strcpy(copyFileActualLocation, TEMP_COPY_FILE_FOLDER);
    strcat(copyFileActualLocation, TEMP_COPY_FILE_NAME);

    // Monta o novo caminho do arquivo
    char copyFileNewLocation[_MAX_PATH] = "";
    strcpy(copyFileNewLocation, fileFullPath);

    remove(fileFullPath); // Deleta o arquivo de referência
    rename(copyFileActualLocation, copyFileNewLocation); // Move o arquivo de copia para a nova localização

    return;
}
