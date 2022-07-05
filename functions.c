//Dabelea Ioana-Viviana - 313CB
#include "functions.h"

void *InitThr(size_t d, int N){
    void *s = InitS(d);
    if(!s)
        return NULL;
    int i;
    for(i = N - 1; i >= 0; i--)
        Push(s, &i);
    return s;
}
int my_thcmp(void *el1, void *el2){
    Task a = *(Task *)el1;
    Task b = *(Task *)el2;
    if(a.thrd != b.thrd)
        return 0;
    return 1;
}
int AddRunning(void *wq, void *rq, void *th){
    while(!IsVidSt(th) && IsVidQ(wq) == 0){
        void *el = malloc(sizeof(Task));
        if(!el)
            return 0;
        ExtrQ(wq, &el);
        Task *x = (Task *)el;
        void *aux = malloc(DIMEQ(th));
        if(!aux){
            free(el);
            return 0;
        }
        Pop(th, &aux);
        x->thrd = (*(short int *)aux);
        AddQ(rq, el);
        free(el);
        free(aux);
    }
    return 1;
}
void AfisFoundF(void *el, FILE *out){
    Task a = *((Task *)el);
    fprintf(out, "Task %d is finished (executed_time = %d).\n", a.id, a.time);
}
void DecreaseR(void *rq, int Q){
    void *auxq = InitQ(DIMEQ(rq));
    void *el = malloc(sizeof(Task));;
    while(!IsVidQ(rq)){
        ExtrQ(rq, &el);
        Task *x = (Task *)el;
        x->time -= Q;
        AddQ(auxq, el);

    }
    free(el);
    RastoarnaQ(rq, auxq);
    DistrugereQ(&auxq);
}
int GetPas(void *rq, int Q){
    int max = 0;
    void *auxq = InitQ(DIMEQ(rq));
    void *el;
    while(!IsVidQ(rq)){
        el = malloc(sizeof(Task));
        ExtrQ(rq, &el);
        Task *vr = (Task *)el;
        if(max < vr->time)
            max = vr->time;
        AddQ(auxq, el);
        free(el);
    }
    RastoarnaQ(rq, auxq);
    DistrugereQ(&auxq);
    if(max > Q)
        return Q;
    return max;
}
void AfisFoundW(void *el, FILE *out){
    Task a = *((Task *)el);
    fprintf(out, "Task %d is waiting (remaining_time = %d).\n", a.id, a.time);
}
void AfisFoundR(void *el, FILE *out){
    Task a = *((Task *)el);
    fprintf(out, "Task %d is running (remaining_time = %d).\n", a.id, a.time);
}
int my_idcmp(void *el1, void *el2){
    Task a = *(Task *)el1;
    Task b = *(Task *)el2;
    if(a.id != b.id)
        return 0;
    return 1;
}
void AfisF(void *el, FILE *out){
    Task a = *((Task *)el);
    fprintf(out, "(%d: priority = %d, executed_time = %d)", a.id, a.pry, a.time);
}
void AfisR(void *el, FILE *out){
    Task a = *(Task *)el;
    fprintf(out, "(%d: priority = %d, remaining_time = %d, running_thread = %d)", a.id, a.pry, a.time, a.thrd);
}
void AfisW(void *el, FILE *out){
    Task a = *(Task *)el;
    fprintf(out, "(%d: priority = %d, remaining_time = %d)", a.id, a.pry, a.time);
}
int CompNum(void *a, void *b){
    int e1 = *(int *)a;
    int e2 = *(int *)b;
    if(e1 > e2)
        return 0;
    return 1;
}
int CompQ(void *a, void *b){
    Task *e1 = (Task *)a;
    Task *e2 = (Task *)b;
    if(e1->pry > e2->pry)
        return 1;
    if(e1->pry < e2->pry)
        return 0;
    if(e1->time < e2->time)
        return 1;
    if(e1->time > e2->time)
        return 0;
    if(e1->id < e2->id)
        return 1;
    return 0;
}
int get_ID(char *s){
    int x = 1;
    while(s[x] == 1)
        x++;
    s[x] = 1;
    return x;
}
char *InitID(size_t d){
    int i, MAX = (1 << 16);
    char *s = calloc(MAX, sizeof(char));
    if(s == NULL)
        return NULL;
    return s;
}
int Insert_Ord(void *qe, void *el, int (*CompQ)(void*,void*), int (*AddQ_Q)(void *, void*)){
    if(IsVidQ(qe) == 1)
        return AddQ_Q(qe, el);
    void *auxq = InitQ(DIMEQ(qe));
    if(auxq == NULL)
        return 0;
    void *q = malloc(sizeof(Task));
    if(q == NULL)
        return 0;
    ExtrQ(qe, &q);
    while(!IsVidQ(qe) && CompQ(q, el) == 1){
        AddQ(auxq, q);
        ExtrQ(qe, &q);
    }
    if(CompQ(q, el) == 0){
        AddQ_Q(auxq, el);
        AddQ(auxq, q);
    } 
    else {
        AddQ(auxq, q);
        AddQ_Q(auxq, el);
    }
    while(!IsVidQ(qe)){
        ExtrQ(qe, &q);
        AddQ(auxq, q);
    }
    free(q);
    RastoarnaQ(qe, auxq);
    DistrugereQ(&auxq);
    return 1;
}
int CompQ_Q(void *el, void *qe){
    TCoada *q = (TCoada *)qe;
    return CompQ(el, ((CelQ *)(q->ic))->info);
}
int NewTask(void *q, char *id, int nr, int time, int prt, FILE *out, int *idt){
    Task x;
    int i;
    void *auxq = InitQ(DIMEQ(q));
    if(auxq == NULL)
        return 0;
    for(i = 0; i < nr; i++){
        x.pry = prt;
        x.time = time;
        x.id = get_ID(id);
        x.thrd = -1;
        idt[x.id] = x.time;
        Insert_Ord(auxq, &x, CompQ, AddQ);
        fprintf(out, "Task created successfully : ID %d.\n", x.id);
    }
    if(nr != 0)
        Insert_Ord(q, auxq, CompQ_Q, CopiazaQ);
    DistrugereQ(&auxq);
    return 1;
}