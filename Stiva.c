//Dabelea Ioana-Viviana - 313CB
#include "functions.h"

int IsVidSt(void *st){
    TStiva *s = (TStiva *)st;
    if(s->vf ==  NULL)
        return 1;
    return 0;
}
void* InitS(size_t d){
    ASt s;
    s = (ASt)malloc(sizeof(TStiva));
    if(!s)
        return NULL;
    s->dime = d;
    s->vf = NULL;
    return (void *)s;
}
int Push(void *st, void *el){
    TStiva *s = (TStiva *)st;
    ACelst vr = malloc(sizeof(CelST));
    if(!vr)
        return 0;
    vr->info = malloc(s->dime);
    if(!vr->info){
        free(vr);
        return 0;
    }
    memcpy(vr->info, el, s->dime);
    vr->urm = s->vf;
    s->vf = vr;
    return 1;
}
void Pop(void *st, void **el){
    TStiva *s = (TStiva *)st;
    ACelst vr = s->vf;
    memcpy((*el), vr->info,s->dime);
    s->vf = ((ACelst)(s->vf))->urm;
    free(vr->info);
    free(vr);
}
void PrintSt(void *st, void(*AfisEl)(void *)){
    TStiva *s = (TStiva *)st;
    ACelst vr = s->vf;
    while(vr != NULL){
        AfisEl(vr->info);
        vr = vr->urm;
    }
}
void DistrugereS(void **st){
    TStiva *s = (TStiva *)(*st);
    while(s->vf != NULL){
        ACelst vr = s->vf;
        s->vf = ((ACelst)(s->vf))->urm;
        free(vr->info);
        free(vr);
    }
    free(s);
}