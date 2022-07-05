//Dabelea Ioana-Viviana - 313CB
#include "functions.h"

int main(int argc, char *input[])
{
    FILE *in, *out;
    char *line = NULL, *sep = " ", *com;
    int nr, time, prt, Stotal = 0;
    size_t len = 0;
    in = fopen(input[1], "rt");
    out = fopen(input[2], "wt");
    char *id = InitID(sizeof(int));
    if(!id){
        fprintf(out, "Error");
        return 0;
    }
    void *waiting = InitQ(sizeof(Task));
    if(!waiting){
        fprintf(out, "Error");
        free(id);
        return 0;
    }
    void *finished = InitQ(sizeof(Task));
    if(!finished){
        fprintf(out, "Error");
        DistrugereQ(&waiting);
        free(id);
        return 0;
    }
    void *running = InitQ(sizeof(Task));
    if(!running){
        fprintf(out, "Error");
        free(id);
        DistrugereQ(&waiting);
        DistrugereQ(&finished);
        return 0;
    }
    int Q, C;
    int ok = fscanf(in, "%d%d\n", &Q, &C);
    void *thred = InitThr(sizeof(int), (2 * C));
    if(!thred){
        fprintf(out, "Error");
        free(id);
        DistrugereQ(&waiting);
        DistrugereQ(&finished);
        DistrugereQ(&running);
        return 0;
    }
    int *id_pertime = malloc(sizeof(int) * (1<<15));
    while(getline(&line, &len, in) != -1){
        com = strtok(line, sep);
        if(strstr(com, "add") != NULL){
            nr = atoi(strtok(NULL, sep));
            time = atoi(strtok(NULL, sep));
            prt = atoi(strtok(NULL, sep));
            NewTask(waiting, id, nr, time, prt, out, id_pertime);
        }
        else if(strcmp(com, "print") == 0){
            com = strtok(NULL, sep);
            if(strstr(com, "waiting")){
                fprintf(out, "====== Waiting queue =======\n");
                PrintQ(waiting, out, AfisW);
            }
            if(strstr(com, "finished")){
                fprintf(out, "====== Finished queue =======\n");
                PrintQ(finished, out, AfisF);
            }
            if(strstr(com, "running")){
                fprintf(out, "====== Running in parallel =======\n");
                PrintQ(running, out, AfisR);
            }
        }
        else if(strcmp(com, "get_task") == 0){
            Task aux;
            aux.id = atoi(strtok(NULL, sep));
            void *el = CautaQ(running, &aux, my_idcmp);
            if(el != NULL)
                AfisFoundR(el, out);
            else{
                free(el);
                el = CautaQ(waiting, &aux, my_idcmp);
                if(el != NULL)
                    AfisFoundW(el, out);
                else{
                    free(el);
                    el = CautaQ(finished, &aux, my_idcmp);
                    if(el != NULL)
                        AfisFoundF(el, out);
                    else
                        fprintf(out, "Task %d not found.\n", aux.id);
                }
            }
            free(el);
        }
        else if(strcmp(com, "run") == 0){
            int T = atoi(strtok(NULL, sep));
            fprintf(out, "Running tasks for %d ms...\n", T);
            if(!IsVidSt(thred) && !IsVidQ(waiting))
                AddRunning(waiting, running, thred);
            int i = Q, pas = Q, ok = 0, apar = 0, Q1 = Q;
            if(i > T){
                Q = T - i + Q;
                i = T;
                ok = 1;
            }
            while(i <= T && IsVidQ(running) == 0){
                pas = GetPas(running, Q);
                DecreaseR(running, Q);
                Stotal += pas;
                void *auxq = InitQ(DIMEQ(running));
                if(auxq == NULL)
                    return 0;
                while(IsVidQ(running) == 0){
                    void *el = malloc(sizeof(Task));
                    ExtrQ(running, &el);
                    Task *x = (Task *)el;
                    if(x->time <= 0){
                        x->time = id_pertime[x->id];
                        id[x->id] = 0;
                        Push(thred, &(x->thrd));
                        AddQ(finished, el);
                    } else
                        AddQ(auxq, el);
                    free(el);
                }
                RastoarnaQ(running, auxq);
                DistrugereQ(&auxq);
                if(!IsVidSt(thred) && !IsVidQ(waiting))
                    AddRunning(waiting, running, thred);
                i += Q;
                if(i > T && T % Q != 0 && ok == 0){ // in cazul in care Q nu este divizibil cu T sa repet algoritmul de mai sus inca o data pentru rest
                    Q = T - i + Q;
                    i = T;
                    ok = 1;
                }
            }
            Q = Q1;
        }
        else if(strcmp(com, "get_thread") == 0){
            Task aux;
            aux.thrd = atoi(strtok(NULL, sep));
            void *el = CautaQ(running, &aux, my_thcmp);
            if(el != NULL)
                fprintf(out, "Thread %d is running task %d (remaining_time = %d).\n", aux.thrd, ((Task *)el)->id, ((Task *)el)->time);
            else if(aux.thrd < 2 * C)
                fprintf(out, "Thread %d is idle.\n", aux.thrd);
            free(el);
        }
        else if(strstr(com, "finish") != NULL){
            int pas;
            TCoada *q = (TCoada *)running;
            if(!IsVidSt(thred) && !IsVidQ(waiting))
                AddRunning(waiting, running, thred);
            while(IsVidQ(running) == 0){
                pas = GetPas(running, Q);
                Stotal += pas;
                DecreaseR(running, pas);
                void *auxq = InitQ(DIMEQ(running));
                if(auxq == NULL)
                    return 0;
                while(IsVidQ(running) == 0){
                    void *el = malloc(sizeof(Task));
                    ExtrQ(running, &el);
                    Task *x = (Task *)el;
                    if(x->time <= 0){
                        x->time = id_pertime[x->id];
                        id[x->id] = 0;
                        Push(thred, &(x->thrd));
                        AddQ(finished, el);
                    } else
                        AddQ(auxq, el);
                    free(el);
                }
                RastoarnaQ(running, auxq);
                DistrugereQ(&auxq);
                if(!IsVidSt(thred) && !IsVidQ(waiting))
                    AddRunning(waiting, running, thred);
            }
            fprintf(out, "Total time: %d", Stotal);
        }
    }
    fclose(in);
    fclose(out);
    free(line);
    DistrugereQ(&running);
    DistrugereQ(&waiting);
    DistrugereQ(&finished);
    free(id);
    DistrugereS(&thred);
    free(id_pertime);
    return 0;
}