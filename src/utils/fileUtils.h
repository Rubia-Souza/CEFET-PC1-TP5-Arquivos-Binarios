#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdlib.h>

/*
 * @description: Cria uma pasta no caminho informado caso ainda não exista
 * @param: path é o caminho onde a pasta será criada 
 */
void createFolder(const char path[_MAX_PATH]);

/*
 * @description: Cria um arquivo do formato presente no caminho informado caso ainda não exita
 * @param: path é o caminho onde o arquivo deverá ser criado
 */
void createFile(const char path[_MAX_PATH]);

/*
 * @description: Extrai do caminho de um arquivo a pasta em que ele está localizado
 * @param: fileName é o caminho completo do arquivo
 * @return: retorna uma string com o caminho da pasta do arquivo informado
 */
char* getFolderPath(const char fileName[_MAX_PATH]);

/*
 * @description: Extrai o nome do arquivo do caminho completo informado
 * @param: filePath é o caminho comlpeto do arquivo
 * @return: retorna uma string contendo o nome e extensão do arquivo
 */
char* getFileNameFromPath(const char filePath[_MAX_PATH]);

#endif