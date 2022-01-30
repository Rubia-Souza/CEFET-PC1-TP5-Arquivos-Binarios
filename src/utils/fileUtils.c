#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include ".\fileUtils.h"

void createFolder(const char path[_MAX_PATH]) {
    struct stat directory = {0};

    // Verifica se já existe o diretório de save do jogo
    if (stat(path, &directory) == -1) { // Se não, ele é criado
        mkdir(path);
    }

    return;
}

void createFile(const char path[_MAX_PATH]) {
    // Tenta abrir o arquivo em modo a, pois caso já exista ele é apenas aberto. Por outro lado, caso não exista, ele é criado
    FILE *fileRef = fopen(path, "a");
    fclose(fileRef);

    return;
}

char* getFolderPath(const char filePath[_MAX_PATH]) {
    // Cria uma cópia do caminho fornecido para evitar modificações na variável original
    char copyFilePath[_MAX_PATH];
    strcpy(copyFilePath, filePath);

    // Verifica se o caminho está vazio
    const size_t filePathSize = strlen(filePath);
    if(filePathSize == 0) { // Se o caminho estiver vazio, não há nada a ser feito
        return NULL;
    }

    // Aloca a string que terá o caminho da pasta
    char* path = (char*) malloc(_MAX_PATH * sizeof(char));

    // Percorre a string do final até encontrar o primeiro caracter \\ ou até chegar ao final dela
    int finalIndex = 0;
    for(finalIndex = filePathSize-1; filePath[finalIndex] != '\\' && finalIndex >= 0; finalIndex--);

    // Caso não tenha encontrado o caracter \\ ou ele já está ao final da string
    if(finalIndex < 0 || finalIndex+1 >= filePathSize) {
        return NULL; // Apenas retorna, pois não é um caminho válido
    }

    // Copia para o resultado todo o conteudo do começo da string copyFilePath até a poisção encontrada
    strncpy(path, copyFilePath, finalIndex+1);
    path[finalIndex+1] = '\000'; // Marca o final da string após o finalIndex
    return path;
}

char* getFileNameFromPath(const char filePath[_MAX_PATH]) {
    // Cria uma cópia do aruqivo fornecido para evitar modificações na variável original
    char copyFilePath[_MAX_PATH];
    strcpy(copyFilePath, filePath);

    // Verifica se o caminho está vazio
    const size_t filePathSize = strlen(filePath);
    if(filePathSize == 0) { // Se estiver vazio não há nada a ser feito
        return NULL;
    }

    // Aloca a string que terá o nome do arquivo
    char* fileName = (char*) malloc(_MAX_PATH * sizeof(char));

    // Percorre a string do final até encontrar o ultimo caracter \\ ou chegar ao final da string
    int startIndex = 0;
    for(startIndex = filePathSize-1; filePath[startIndex] != '\\' && startIndex >= 0; startIndex--);

    // Caso não tenha encontardo o caracter \\ ou ele já está no final da string
    if(startIndex < 0 || startIndex+1 >= filePathSize) {
        return NULL; // Apenas retorna
    }

    // Copia para o resultado a partir do ultimo caracter \\ ate a ultima posição da string
    strncpy(fileName, &copyFilePath[startIndex+1], filePathSize - startIndex);
    fileName[filePathSize - startIndex+1] = '\000'; // Adiciona o final da string na ultima posição
    return fileName;
}
