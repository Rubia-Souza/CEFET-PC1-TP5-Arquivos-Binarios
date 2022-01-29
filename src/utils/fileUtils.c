#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include ".\fileUtils.h"

void createFolder(const char path[]) {
    struct stat directory = {0};

    // Verifica se já existe o diretório de save do jogo
    if (stat(path, &directory) == -1) { // Se não, ele é criado
        mkdir(path);
    }

    return;
}

void createFile(const char path[]) {
    // Tenta abrir o arquivo em modo a, pois caso já exista ele é apenas aberto. Por outro lado, caso não exista, ele é criado
    FILE *fileRef = fopen(path, "a");
    fclose(fileRef);

    return;
}

char* getFolderPath(const char filePath[_MAX_PATH]) {
    char copyFilePath[_MAX_PATH];
    strcpy(copyFilePath, filePath);

    const size_t filePathSize = strlen(filePath);
    if(filePathSize == 0) {
        return NULL;
    }

    char* path = (char*) malloc(_MAX_PATH * sizeof(char));

    int finalIndex = 0;
    for(finalIndex = filePathSize-1; filePath[finalIndex] != '\\' && finalIndex >= 0; finalIndex--);
    if(finalIndex < 0 || finalIndex+1 >= filePathSize) {
        return NULL;
    }

    strncpy(path, copyFilePath, finalIndex+1);
    path[finalIndex+1] = '\000';
    return path;
}

char* getFileNameFromPath(const char filePath[_MAX_PATH]) {
    char copyFilePath[_MAX_PATH];
    strcpy(copyFilePath, filePath);

    const size_t filePathSize = strlen(filePath);
    if(filePathSize == 0) {
        return NULL;
    }

    char* fileName = (char*) malloc(_MAX_PATH * sizeof(char));

    int startIndex = 0;
    for(startIndex = filePathSize-1; filePath[startIndex] != '\\' && startIndex >= 0; startIndex--);
    if(startIndex < 0 || startIndex+1 >= filePathSize) {
        return NULL;
    }

    strncpy(fileName, &copyFilePath[startIndex+1], filePathSize - startIndex);
    fileName[filePathSize - startIndex+1] = '\000';
    return fileName;
}
