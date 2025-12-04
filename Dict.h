#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_LENGTH 100

typedef struct dict_entry {
    char key[MAX_KEY_LENGTH];
    void* value;
    struct dict_entry* next;
} DictEntry;

typedef struct {
    DictEntry* head;
    int size;
} Dict;

void dict_init(Dict* dict);
void dict_insert(Dict* dict, const char* key, void* value);
void* dict_search(Dict* dict, const char* key);
void* dict_remove(Dict* dict, const char* key);
int dict_entries(Dict* dict);

#endif

