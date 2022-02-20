#include "bib.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>

sem_t *sem; // wskaznik typu sem_t


// tworzenie semafora
sem_t *stworz(const char *name, int wartosc)
{
    sem = sem_open(name, O_CREAT | O_EXCL, 0777, wartosc);
    if (sem == SEM_FAILED)
    {
        perror("Sem_open error");
        exit(EXIT_FAILURE);
    }
    else
    {
        return sem;
    }
}

// otwarcie semafora
sem_t *otworz(const char *name)
{
    sem = sem_open(name, O_RDWR);
    if (sem == SEM_FAILED)
    {
        perror("Sem_open error");
        exit(EXIT_FAILURE);
    }
    else
    {
        return sem;
    }
}

// uzyskiwanie wartosci semafora
void wartosc(sem_t *sem, int *val)
{
    if (sem_getvalue(sem, val) == -1)
    {
        perror("Sem_getvalue error");
        exit(EXIT_FAILURE);
    }
}

//operowanie na semaforze
void opusc(sem_t *sem)
{
    if (sem_wait(sem) == -1)
    {
        perror("Sem_wait error");
        exit(EXIT_FAILURE);
    }
}

void podnies(sem_t *sem)
{
    if (sem_post(sem) == -1)
    {
        perror("Sem_post error");
        exit(EXIT_FAILURE);
    }
}

// zamykanie semafora
void zamknij(sem_t *sem)
{
    if (sem_close(sem) == -1)
    {
        perror("Sem_close error");
        exit(EXIT_FAILURE);
    }
}

// usuwanie semafora
void usun(const char *name)
{
    if (sem_unlink(name) == -1)
    {
        perror("Sem_unlink error");
        exit(EXIT_FAILURE);
    }
}
