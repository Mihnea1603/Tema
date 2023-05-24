# Tema-LAN-Party
  Facultatea de Automatică și Calculatoare prin LSAC organizează în fiecare semestru un LAN Party la care participă toți studenții care vor sa își testeze abilitățile la un anumit joc. Se dorește realizarea unei soluții software(program executabil) ce poate automatiza acest proces.
## Cerința 1
  Pentru a stoca informațiile din fișier legate de echipe și jucătorii lor am folosit stivă în stivă. Mai întâi se citește numărul de echipe, iar după datele despre fiecare echipă sunt citite în niște variabile buffer în cadrul unei funcții, ca apoi să-i dau push în stiva de echipe, unde se alocă memorie dinamic pentru acestea. Pentru fiecare jucător din echipe, se citesc într-o funcție separată datele despre acesta, ca după să-i dau push în stiva de jucători din echipa respectivă. În plus, punctele acestuia sunt adunate la totalul echipei pentru a face media la final.
    Struct-ul pentru nodul stivei de echipe este următorul:
```c
typedef struct NodeTeam
{
    char *name;
    float points;
    NodePlayer *topPlayers;
    struct NodeTeam *next;
} NodeTeam;
```
## Cerința 2
  La cerința 2, pentru eliminarea echipelor cu punctajul minim pană când rămân un număr de echipe care să fie putere de 2 am parcurs pur și simplu stiva ca o listă și am eliminat echipele respective până la rămanerea numărului de echipe dorit. De fiecare dată când se găsește o echipă care are punctajul minim și este eliminată, căutarea o ia de la capăt, iar minimul este calculat din nou în caz că nu s-a mai găsit nicio echipă cu punctajul minim în căutarea precedentă.
  În acest moment am afișat echipele rămase, că s-a efectuat sau nu cerința 2.
## Cerința 3
  Pentru rezolvarea cerinței 3 am urmărit indicațiile. Mai întâi am umplut coada de meciuri cu echipele rămase de la 2 și le am eliminat în funcție de cine avea punctajul mai mare, câștigătorii punându-i într-o stivă, iar pierzătorii în alta pentru a-i putea șterge după afișarea rundei. De menționat că la crearea stivelor si meciurilor din coadă, doar am legat nodurile echipelor respective, nu am alocat din nou memorie pentru acestea. Pe urmă am reumplut coada cu câștigătorii pentru următoarea rundă și am repetat acești pași până când mai rămânea o singură echipă, câștigătoarea. 
  De asemenea, în momentul în care au mai rămas 8 echipe, le am dat push într-o stivă(în acest caz alocând din nou memorie pentru a reține punctajele din momentul respectiv, care se vor modifica până la aflarea câștigătorului) pentru a le utiliza la cerințele 4 și 5.
## Cerința 4
  Pentru realizarea cerinței 4 am creat un BST(arbore binar de căutare) cu ultimele 8 echipe în funcție de punctajele acestora și, în cazuri speciale, de numele acestora dacă aveau același punctaj, iar apoi l-am afișat în inordine inversă pentru a obține echipele în ordinea descrescătoare a punctajului.
## Cerința 5
  Cerința 5 presupune realizarea unui arbore AVL, inserând echipele în ordinea afisării de la 4, adică descrescător. Pentru asta am parcurs din nou în inordine descrescătoare BST-ul și am inserat nodurile în AVL folosind o funcție din curs, modificată pentru cerințele programului, care efectuează rotațiile necesare pentru echilibrarea arborelui. În final, am afișat echipele de pe nivelul 2, așa cum se cerea, și am eliberat memoria pentru ce mai era de eliberat(ultimele 8 echipe, arborii etc.).
