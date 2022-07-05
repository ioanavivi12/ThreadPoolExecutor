#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Stiva.h"
#include "Coada.h"

typedef struct{
    int time;
    int id, thrd;
    char pry;
}Task;
void AfisW(void *el, FILE *out);
int CompQ(void *a, void *b);
int get_ID(char *s);
char *InitID(size_t d);
int Insert_Ord(void *qe, void *el, int (*CompQ)(void*,void*), int (*AddQ_Q)(void *, void*));
int CompNum(void *a, void *b);
int NewTask(void *q, char *id, int nr, int time, int prt, FILE *out, int *idt);
void AfisF(void *el, FILE *out);
void AfisR(void *el, FILE *out);
int my_idcmp(void *el1, void *el2);
void AfisFoundW(void *el, FILE *out);
void AfisFoundR(void *el, FILE *out);
void *InitThr(size_t d, int N);
int my_thcmp(void *el1, void *el2);
int AddRunning(void *wq, void *rq, void *th);
void DecreaseR(void *rq, int Q);
int GetPas(void *rq, int Q);
void AfisFoundF(void *el, FILE *out);
int CompQ_Q(void *el, void *qe);