# Kolejka-FIFO-oparta-na-liście
Kolejka FIFO oparta na liście dwukierunkowej, zrobiona na laby z algorytmów i struktur danych.

LISTA:
* wartosc;
* *first;
* *last;

KOLEJKA:
* *front;
* *end;

###    Dostępne komendy: 
###### ADD_BEG -> dodaje element na początek listy;
###### ADD_END -> dodaje element na koniec listy;
###### PRINT_FORWARD -> wypisuje liste od początku do końca 
###### PRINT_BACKWARD -> wypisuje liste od końca do początku
###### DEL_BEG -> usuwa element z początku listy
###### DEL_END -> usuwa element z końca listy
###### SIZE -> zwraca długość listy

#####  Komendy dla kolejki:
###### PUSH -> dodaje element na koniec kolejki
###### POP -> usuwa pierwszy element z kolejki
###### PRINT_QUEUE -> wypisuje kolejke od FRONT do END
###### COUNT -> zwraca długość kolejki
###### GARBAGE_SOFT -> ustawiwa zera elementom poza kolejką
###### GARBAGE_HARD -> usuwa elementy poza kolejką
        
        
#### PRZYKŁADOWE DZIAŁANIE:
##### F->front kolejki
##### E->end kolejki
```
       E       F
LISTA: 5 4 3 2 1
QUEUE: 1 2 3 4 5

ADD_BEG 6
ADD_END 7

         E       F
LISTA: 6 5 4 3 2 1 7
QUEUE:   1 2 3 4 5

PSUH 8

       E         F
LISTA: 8 5 4 3 2 1 7
QUEUE: 1 2 3 4 5 8

POP
POP

       E     F
LISTA: 8 5 4 3 2 1 7
QUEUE: 3 4 5 8

GARBAGE_SOFT

       E     F
LISTA: 8 5 4 3 0 0 0
QUEUE: 3 4 5 8

GARBAGE_HARD

       E     F
LISTA: 8 5 4 3
QUEUE: 3 4 5 8
```

