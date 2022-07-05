#define VF(a) (((ASt)(a))->vf)
#define DIMEST(a) (((ASt)(a))->dime)

typedef struct celst{
    void *info;
    struct celst *urm;
}CelST, *ACelst;
typedef struct stiva
{
    size_t dime;
    CelST *vf;
}TStiva, *ASt;
void* InitS(size_t d);
int Push(void *st, void *el);
void Pop(void *st, void **el);
void PrintSt(void *st, void(*AfisEl)(void *));
void DistrugereS(void **st);
int IsVidSt(void *st);