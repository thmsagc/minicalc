#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct tagBuffer {
    char *cont;
    long tam;
} Buffer;

Buffer* CriaBuffer(char *nome);
void DestroiBuffer(Buffer *b);

#endif
