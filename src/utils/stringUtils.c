#include <ctype.h>
#include <string.h>

#include "./stringUtils.h"

void toLower(char phrase[]) {
    // Percorre a string até ao final
    for(int i = 0; phrase[i] != '\000'; i++){
        phrase[i] = tolower(phrase[i]); // Converte cada caracter em minúsculo
    }

    return;
}

void removeSubstring(char phrase[], const char subString[]) {
    // Encontra um ponteiro para a primeira ocorrencia da substring
    char* subStringPointer = strstr(phrase, subString);
    if(subStringPointer == NULL) { // Se não encontrar
        return; // Não há nada a retirar
    }

    // Define o tamanho da substring
    size_t subStringSize = strlen(subString);
    // Encontra o index da posição inicial da substring
    size_t subStringStartIndex = strlen(phrase) - strlen(subStringPointer);

    // Encontra um ponteiro para o caracter posterior a substring que será removida
    char* afterSubStringPointer = &subStringPointer[subStringSize];
    trimStart(afterSubStringPointer); // Tira espaço no começo para evitar espaço duplo
    size_t afterSubStringSize = strlen(afterSubStringPointer); // Define o tamanho do resto da string apos a parte que será removida

    // Re-aloca as posições da string para sobrepor a parte que será removida
    memmove(&phrase[subStringStartIndex], afterSubStringPointer, afterSubStringSize);
    
    // Atualiza o fim da string
    size_t updatedLastPhraseInxed = strlen(phrase) - strlen(subString);
    phrase[updatedLastPhraseInxed] = '\000';
    return;
}

void trim(char phrase[]) {
    trimEnd(phrase); // Remove o espaço do começo
    trimStart(phrase); // Remove o espaço do fim

    return;
}

void trimEnd(char phrase[]) {
    // Verifica se a string está vazia
    size_t phraseSize = strlen(phrase);
    if(phraseSize == 0) {
        return; // Se estiver vazia apenas retorna
    }

    // Percorre do fim da string até a primeira posição que não é um espaço
    unsigned int finalIndex = 0;
    for(finalIndex = phraseSize-1; finalIndex > 0 && phrase[finalIndex] == ' '; finalIndex--);

    // Atualiza o fim da string para o index encontrado anteriormente
    phrase[finalIndex+1] = '\000';
    return;
}

void trimStart(char phrase[]) {
    // Verifica se a string está vazia
    size_t phraseSize = strlen(phrase);
    if(phraseSize == 0) {
        return; // Se estiver vazia apenas retorna
    }

    // Percorre do começo da string até a primeira posição que não é um espaço
    unsigned int startIndex = 0;
    for(startIndex = 0; phrase[startIndex] == ' ' && startIndex < phraseSize; startIndex++);
    if(startIndex == phraseSize-1) {
        phrase[0] = '\000';
    }

    // Move os caracteres que não são espaço para o começo da string
    phraseSize = strlen(&phrase[startIndex]);
    memmove(&phrase[0], &phrase[startIndex], phraseSize);

    // Atualiza o fim da string para o index encontrado anteriormente
    phrase[phraseSize] = '\000';
    return;
}
