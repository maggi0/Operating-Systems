#ifndef BIB_H
#define BIB_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>


// tworzenie semafora
sem_t* stworz(const char *name, int wartosc);

// otwieranie semafora
sem_t* otworz(const char *name);

// uzyskiwanie wartosci semafora
void wartosc(sem_t *sem, int *val);

// operowanie na semaforze
void opusc(sem_t *sem);

void podnies(sem_t *sem);

// zamykanie semafora
void zamknij(sem_t *sem);

// usuwanie semafora
void usun(const char* name);

#endif