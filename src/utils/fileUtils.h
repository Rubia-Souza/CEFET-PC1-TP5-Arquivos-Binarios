#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdlib.h>

void createFolder(const char path[]);
void createFile(const char path[]);
char* getFolderPath(const char fileName[_MAX_PATH]);
char* getFileNameFromPath(const char filePath[_MAX_PATH]);

#endif