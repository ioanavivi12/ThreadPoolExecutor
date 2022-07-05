Tema 2-SD
Fisierele Coada.c Coada.h Stiva.h şi Stiva.c conţin algoritmi de baza pentru lucrul cu stive si cozi, implementati cu ajutorul listelor simplu înlănţuite.
Fisierul main.c
 -> citesc argumentele din linia de comanda si deschid cele 2 fisiere
 -> initializez un vector de frecventa id care sa ma ajute sa gasesc cel mai mic id disponibil atunci cand adaug un task nou
 -> initializez o coada waiting, finished si running care o sa imi contina task urile la un moment dat
 -> initializez un vector id_pertime care sa imi pastreze pentru fiecare id timpul initial(ma ajuta atunci cand adaug in coada de finish taskurile)
 -> citez comenzile pe rand pana la finalul fisierului
Comanda add_tasks:
 -> apelez functia NewTask, careia ii dau ca parametrii coada unde trebuie adaugat taskurile, vectorul id, informatii despre taskuri si id_pertime
Functia NewTask(din fisierul functions.c)
 -> initializez o coada auxiliara
 -> creez un element x de tipul Task cu toate informatiile necesare (aflarea id-ul se face cu ajutorul functiei get_id care imi gaseste cea mai mica pozitie din vectorul id nula)
 -> inserez elementul x in coada auxiliara cu functia Insert_Ord
-------------------------------------------------------------------------------------------------------------------------------------------------
Functia Insert_Ord
 Deoarece la inceput compilatorul nu imi mergea pentru testul 12, am gasit urmatoarele metode de optimizare:
 -> functia primeste ca parametrii coada care va fi modificata(qe), un void *el care poate fi doar un element sau o alta coada, o functie de comparare si o functie de adaugare in coada
 -> extrag elemente din qe si le pun intr-o coada auxiliara pentru a gasi locul potrivit lui el in qe (compararile se fac cu ajut functiei date ca si parametru)
 -> il adaug pe el in coada auxiliara cu ajutorul celei de a 2a functii date ca parametru si continui sa extrag elemente din qe pana golesc coada
 -> la final rastorn in qe coada auxiliara
 Avand posibilitatea de a adauga o coada in alta coada in mod direct nu a mai fost nevoie sa tot reconstruiesc coada de waiting de un numar asa mare de ori
-------------------------------------------------------------------------------------------------------------------------------------------------
 -> dupa ce am terminat de inserat toate task urile adaug intreaga coada in coada de waiting
Comanda print:
 -> in functie de ce coada trebuia sa afisez aveam 3 functii AfisW, AfisF si AfisR care sa ma ajute
Comanda get_task:
 -> cu ajutorul functiei CautaQ(din fisierul Coada.c) caut intr-o coada data ca paramtru un element si criteriul de cautare se da cu o functie.
Comanda run:
 -> citesc timpul de rulare al task-urilor
 -> ma folosesc de functia AddRunning pentru a muta elemente din coada de waiting in cea de running si a le oferi un thred
-------------------------------------------------------------------------------------------------------------------------------------------------
Functia AddRunning (din fisierul functions.c)
 -> cat timp stiva de threduri si coada de waiting nu sunt vide extrage atat un element din coada cat si unul din stiva
 -> atribuie elementului din coada thredul dat
 -> adauga elementul actualizat in coada de running
-------------------------------------------------------------------------------------------------------------------------------------------------
 -> apelez functia GetPas pentru a vedea daca mai sunt elemente in coada de running care au nevoie de cele puitin Q secunde pentru a putea fi trecute in coada de finish(aceasta functie ma ajutan mai mult pentru a calcula numarul total de secunde necesar pentru comanda finish)
 -> apelez functia DecreaseR care imi ia fiecare element din coada si ii scade timpul de executie cu Q(atat coada cat si Q sunt dati ca parametru iar functia se gaseste in fisierul functions.c)
 -> parcurg coada de running pentru a vedea daca am task uri care si-au terminat executia
 -> in caz afirmativ le adaug in coada de finish modificand timpul de executie(aici ma folosesc de vectorul id_pertime)
 -> eliberez id ul si thredul alocat elementului
 -> repet ceea ce am facut pana se termina timpul
Comanda get_thread:
 -> caut cu ajutorul functiei CautaQ elementul care are campul thrd egal cu cel dat
Comanda finish:
 -> repet tot procesul de la comanda run pana cand coada de running este goala(singura diferenta este ca acum variabila pas obtinuta ca rezultat al functiei GetPas este cea data ca parametru pt functia DecreaseR)
