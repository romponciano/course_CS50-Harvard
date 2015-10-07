/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H
 
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
 
/* maximum length for a word (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
do NOT change this */
#define LENGTH 45

#define ITEMSPERINDEX 8
 
/* type definitions. */
typedef uint8_t length_t;
 
typedef struct STORAGE
{
    unsigned int wordcount;
    unsigned int size; 
    char *s;
} store_t;
 
typedef struct DICT_NODE
{
    char *w; 
    length_t l;
    struct DICT_NODE *next;
} dict_node_t;
 
bool check(const char *word);
bool load(const char *dict);
unsigned int size(void);
bool unload(void);

bool load_storage(FILE *dfp);
uint32_t djb2_ci(const char *str);
void d_unshift(uint32_t index, length_t len, char *str);
dict_node_t *d_shift(uint32_t index);
bool q_streq(const char *str1, const char *str2, length_t l1, length_t l2);
char *strtolower(const char *word, length_t len);
 
#endif // DICTIONARY_H
