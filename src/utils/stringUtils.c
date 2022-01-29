#include <ctype.h>
#include <string.h>

#include "./stringUtils.h"

void toLower(char phrase[]) {
    for(int i = 0; phrase[i] != '\000'; i++){
        phrase[i] = tolower(phrase[i]);
    }

    return;
}

void removeSubstring(char phrase[], const char subString[]) {
    char* subStringPointer = strstr(phrase, subString);
    if(subStringPointer == NULL) {
        return;
    }

    size_t subStringSize = strlen(subString);
    size_t subStringStartIndex = strlen(phrase) - strlen(subStringPointer);

    char* afterSubStringPointer = &subStringPointer[subStringSize];
    trimStart(afterSubStringPointer);
    size_t afterSubStringSize = strlen(afterSubStringPointer);

    memmove(&phrase[subStringStartIndex], afterSubStringPointer, afterSubStringSize);
    
    size_t updatedLastPhraseInxed = strlen(phrase) - strlen(subString);
    phrase[updatedLastPhraseInxed] = '\000';
    return;
}

void trim(char phrase[]) {
    trimEnd(phrase);
    trimStart(phrase);

    return;
}

void trimEnd(char phrase[]) {
    size_t phraseSize = strlen(phrase);
    if(phraseSize == 0) {
        return;
    }

    unsigned int finalIndex = 0;
    for(finalIndex = phraseSize-1; finalIndex > 0 && phrase[finalIndex] == ' '; finalIndex--);

    phrase[finalIndex+1] = '\000';
    return;
}

void trimStart(char phrase[]) {
    size_t phraseSize = strlen(phrase);
    if(phraseSize == 0) {
        return;
    }

    unsigned int startIndex = 0;
    for(startIndex = 0; phrase[startIndex] == ' ' && startIndex < phraseSize; startIndex++);
    if(startIndex == phraseSize-1) {
        phrase[0] = '\000';
    }

    phraseSize = strlen(&phrase[startIndex]);
    memmove(&phrase[0], &phrase[startIndex], phraseSize);
    phrase[phraseSize] = '\000';
    return;
}
