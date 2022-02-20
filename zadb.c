#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    if(argc!=4) // do nazwy programu dopisujemy nazwe sygnalu, polecenie i program zada (w make)
    {
        printf("Nieodpowiednia ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    int sygnal=atoi(argv[2]); // zmiana sygnalu z char na int
    int pid; // pid dziecka

    switch(pid=fork()) // fork zwraca pid dziecka
    {
        case -1: // obsluga bledu dla forka
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            if(execl(argv[3],argv[3],argv[1],argv[2],NULL)==-1) // zainicjowanie procesu na podstawie "zada.x"
            {
                perror("execl error"); // obsluga bledu dla execl
                _exit(EXIT_FAILURE);
            }
        }
        break;
        default:
        {
            sleep(1);
            if(kill(pid,0)==-1) // sprawdzenie czy dany proces istnieje
            {
                perror("Dany proces nie istnieje");
                exit(EXIT_FAILURE);
            }
            if(kill(pid,sygnal)==-1) // wysylanie sygnalow poprzez kill
            {
                perror("kill error"); // obsluga bledu dla kill
                exit(EXIT_FAILURE);
            }
            if(wait(0)==-1) // oczekiwanie procesu macierzystego na zakonczenie potomnego
            {
                perror("wait error"); // obsluga bledu dla waita
                exit(EXIT_FAILURE);
            }
        }
        break;
    }
}