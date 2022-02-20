#include "bib.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>

const char *SemName; // wskaznik do nazwy semafora

int main(int argc, char *argv[])
{
    if (argc != 3) // sprawdzenie ilosci argumentow
    {
        printf("Nieprawidlowa ilosc argumentow!");
        exit(EXIT_FAILURE);
    }
    sem_t *sem;                 // wskaznik typu sem_t
    const char *SemName = "/Sem"; // nazwa semafora
    sem = otworz(SemName);      // otwarcie semafora
    int val;
    srand(43); // ustawienie seeda dla liczb pseudolosowych

    int liczbaSekcji = atoi(argv[2]); // zmiana liczby sekcji na typ int

    int s1; // zmienne odpowiadajace za sleep
    int s2;

    int i;

    for (i = 0; i < liczbaSekcji; i++)
    {
        FILE *f2 = fopen("numer.txt", "r");    // otwarcie pliku do czytania
        if(f2==NULL)
        {
            perror("Fopen error");
            exit(EXIT_FAILURE);
        }
        s1 = rand() % 3 + 1;     // przypisanie zmiennej s1 od 1 do 3
        sleep(s1);           // uspienie na s1 sekund
        wartosc(sem, &val);      // uzyskanie wartosci semafora
        printf("Przed %d sekcja krytyczna - PID: %d, wartosc: %d\n", i + 1, getpid(), val);
        opusc(sem);                    // opuszczenie semafora
        int numerek;
        fscanf(f2, "%d", &numerek);         // odczytanie wartosci z pliku
        printf("\tPID %d odczytal %d\n", getpid(), numerek);
        fclose(f2);
        s2 = rand() % 3 + 1;
        sleep(s2);
        wartosc(sem, &val);
        printf("\tWewnatrz %d sekcji krytycznej - PID: %d, wartosc: %d\n", i + 1, getpid(), val);
        numerek = numerek + 1;         // zwiekszenie wartosci zapisywanej do pliku o 1
        FILE *f3 = fopen("numer.txt", "w"); // otwarcie pliku do pisania
        if(f3==NULL)
        {
            perror("Fopen error");
            exit(EXIT_FAILURE);
        }
        fprintf(f3, "%d", numerek);
        printf("\tPID %d zapisal %d\n", getpid(), numerek);
        fclose(f3);
        podnies(sem);                 // podniesienie semafora
        wartosc(sem, &val);
        printf("Po %d sekcji krytycznej - PID: %d, wartosc: %d\n", i + 1, getpid(), val);
    }

    return 0;
}