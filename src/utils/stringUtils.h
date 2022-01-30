#ifndef STRING_UTILS_H
#define STRING_UTILS_H

/*
 * @description: transforma todos os caracteres da string em letras minúsculas
 * @param: phrase é a string que será transformada em minúsculas
 */
void toLower(char phrase[]);

/*
 * @description: remove uma substring de uma string
 * @param: phrase é a string que terá a substring removida
 * @param: subString é o padrão que será procurado e usado para remover da string phrase
 */
void removeSubstring(char phrase[], const char subString[]);

/*
 * @description: remove espaços vazios nos extremos da string
 * @param: phrase é a string que terá os espaços vazios nos extremos removidos
 */
void trim(char phrase[]);

/*
 * @description: remove espaços vazios no final da string
 * @param: phrase é a string que terá os espaços vazios no final removidos
 */
void trimEnd(char phrase[]);

/*
 * @description: remove espaços vazios no começo da string
 * @param: phrase é a string que terá os espaços vazios no começo removidos
 */
void trimStart(char phrase[]);

#endif
