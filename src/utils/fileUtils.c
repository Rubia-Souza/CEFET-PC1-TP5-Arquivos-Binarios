#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

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
