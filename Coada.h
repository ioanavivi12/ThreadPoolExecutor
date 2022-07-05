#define SF(a) (((AQ)(a))->sc)
#define DIMEQ(a) (((AQ)(a))->dime)

typedef struct cel{
    struct cel *urm;
    void *info;
}CelQ, *ACelQ;

typedef struct coada{
    size_t dime;
    ACelQ ic, sc;
}TCoada, *AQ;
int IsVidQ(void *qe);
void* InitQ(size_t d);
int AddQ(void *qe, void *el);
void ExtrQ(void *qe, void **el);
void PrintQ(void *qe, FILE *out, void(*AfisEl)(void *, FILE *));
void DistrugereQ(void **qe);
CelQ* AlocCelQ(void *el, size_t d);
void *CautaQ(void *qe, void *el, int(*Comp)(void *, void*));
int RastoarnaQ(void *dest, void *source);
int CopiazaQ(void *dest, void *source);