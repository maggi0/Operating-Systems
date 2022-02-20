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
#include <signal.h>

const char *SemName; // wskaznik do nazwy semafora

sem_t *sem; // wskaznik typu sem_t

int main(int argc, char *argv[])
{
    if (argc != 4) // sprawdzanie ilosci argumentow
    {
        printf("Nieprawidlowa ilosc argumentow!");
        exit(EXIT_FAILURE);
    }
    int val = 1;                    // zmienna wartosci semafora
    int liczbaProc = atoi(argv[2]); // zmiana liczby procesow na typ int
    const char *SemName = "/Sem";   // nazwa semafora
    sem = stworz(SemName, val);     // tworzenie semafora
    printf("PID = %d\n", getpid());
    printf("Nazwa semafora: %s\n", SemName);
    printf("Adres semafora: %p\n", (void *)sem);
    wartosc(sem, &val);
    printf("Wartosc poczatkowa: %d\n", val);
    zamknij(sem); // zamkniecie semafora

    FILE *f1 = fopen("numer.txt", "w"); // tworzenie pliku numer.txt
    if(f1==NULL)
    {
        perror("Fopen error");
        exit(EXIT_FAILURE);
    }
    fprintf(f1, "%d", 0);               // zapisanie "0" do pliku
    fclose(f1);                         // zamkniecie pliku

    int i;
    for (i = 0; i < liczbaProc; i++)
    {
        switch (fork())
        {
        case -1: // obsluga bledu dla fork
        {
            perror("Fork error\n");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            if (execl(argv[1], argv[1], argv[2], argv[3], NULL) == -1) // wykonywanie programu "wykl.c"
            {
                perror("Execl error");
                exit(EXIT_FAILURE);
            }
        }
        break;
        case 1:
        {
        }
        break;
        }
    }

    for (i = 0; i < liczbaProc; i++) // czekanie na zakonczenie procesow potomnych
    {
        if (wait(NULL) == -1)
        {
            perror("Wait error");
            exit(EXIT_FAILURE);
        }
    }

    usun(SemName);

    return 0;
}