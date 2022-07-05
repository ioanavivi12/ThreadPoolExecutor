//Dabelea Ioana-Viviana - 313CB
#include "functions.h"

CelQ* AlocCelQ(void *el, size_t d){
    CelQ *vr = malloc(sizeof(CelQ));
    if(!vr)
        return NULL;
    vr->info = malloc(d);
    if(vr->info == NULL){
        free(vr);
        return NULL;
    }
    memcpy(vr->info, el, d);
    return vr;
}
int RastoarnaQ(void *dest, void *source){
    void *el = malloc(sizeof(Task));
    if(el == NULL)
        return 0;
    while(!IsVidQ(source)){
        ExtrQ(source, &el);
        AddQ(dest, el);
    }
    free(el);
}
void *CautaQ(void *qe, void *el, int(*Comp)(void *, void*)){
    if(IsVidQ(qe) == 1)
        return NULL;
    void *vr = malloc(sizeof(Task));
    if(!vr)
        return 0;
    void *rasp = malloc(sizeof(Task));
    if(!rasp){
        free(vr);
        return 0;
    }
    void *auxq = InitQ(DIMEQ(qe));
    if(!auxq){
        free(vr);
        free(rasp);
        return 0;
    }
    int ok = 0;
    while(!IsVidQ(qe)){
        ExtrQ(qe, &vr);
        if(Comp(vr, el) == 1 && ok == 0){
            ok = 1;
            memcpy(rasp, vr, sizeof(Task));
        }
        AddQ(auxq, vr);
    }
    RastoarnaQ(qe, auxq);
    free(vr);
    DistrugereQ(&auxq);
    if(ok == 1)
        return rasp;
    free(rasp);
    return NULL;
}
int IsVidQ(void *qe){
    TCoada *q = (TCoada *)qe;
    if(q->ic == q->sc && q->ic == NULL)
        return 1;
    return 0;
}
void* InitQ(size_t d){
    AQ q = (AQ)malloc(sizeof(TCoada));
    if(!q)
        return NULL;
    q->dime = d;
    q->ic = q->sc = NULL;
    return (void *)q;
}
int AddQ(void *qe, void *el){
    TCoada *q = (TCoada *)qe;
    CelQ *aux = AlocCelQ(el, q->dime);
    if(!aux)
        return 0;
    aux->urm = NULL;
    if(q->sc)
        ((CelQ *)q->sc)->urm = aux;
    q->sc = aux;
    if(q->ic == NULL)
        q->ic = aux;
    return 1;
}
int CopiazaQ(void *dest, void *source){
    void *auxq = InitQ(DIMEQ(source));
    if(auxq == NULL)
        return 0;
    RastoarnaQ(auxq, source);
    RastoarnaQ(dest, auxq);
    DistrugereQ(&auxq);
    return 1;
}
void PrintQ(void *qe, FILE *out, void(*AfisEl)(void *, FILE *)){
    if(IsVidQ(qe) == 1){
        fprintf(out, "[]\n");
        return;
    }
    void *el = malloc(sizeof(Task));
    void *auxq = InitQ(DIMEQ(qe));

    fprintf(out, "[");
    ExtrQ(qe, &el);
    AddQ(auxq, el);
    AfisEl(el, out);
    while(!IsVidQ(qe)){
        fprintf(out,",\n");
        ExtrQ(qe, &el);
        AfisEl(el, out);
        AddQ(auxq, el);
    }
    RastoarnaQ(qe, auxq);
    free(el);
    DistrugereQ(&auxq);
    fprintf(out, "]\n");
}
void ExtrQ(void *qe, void **el){
    TCoada *q = (TCoada *)qe;
    CelQ *vr = (CelQ *)(q->ic);
    memcpy((*el), vr->info, q->dime);
    q->ic = vr->urm;
    free(vr->info);
    free(vr);
    if(q->ic == NULL)
        q->sc = NULL;
}
void DistrugereQ(void **qe){
    TCoada *q = (TCoada *)(*qe);
    while(q->ic != NULL){
        CelQ *vr = (CelQ*)q->ic;
        q->ic = vr->urm;
        free(vr->info);
        free(vr);
    }
    free(q);
}