#define _POSIX_C_SOURCE 200112L
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{
    if(argc!=5) // do nazwy programu dopisujemy nazwe sygnalu, polecenie i 2 nazwy dolaczonych programow (w make)
    {
        printf("Nieodpowiednia ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    int sygnal=atoi(argv[2]); // zmiana sygnalu z char na int

    int pid; // pid dziecka

    printf("PID - %d\n",getpid());

    switch(pid=fork()) // fork zwraca pid dziecka
    {
        case -1: // obsluga bledu dla forka
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            if(setpgid(0,0)==-1) // ustawienie lidera procesow
            {
                perror("Setpgid error"); // obsluga bledu dla setpgid
                exit(EXIT_FAILURE);        
            }

            printf("PGID - %d\n", getpgid(getpid()));

            if(execl(argv[3],argv[3],argv[1],argv[2],argv[4],NULL)==-1) // zainicjowanie procesu na podstawie "zadc2.x"
            {
                perror("execl error"); // obsluga bledu dla execl
                _exit(EXIT_FAILURE);
            }
        }
        break;
        default:
        {
            sleep(5);

            if(kill(-pid,0)==-1) // sprawdzanie czy dany proces istnieje
            {
                perror("Dany proces nie istnieje");
                exit(EXIT_FAILURE);
            }

            if(kill(-pid,sygnal)==-1) // wysylanie sygnalu do grupy procesow
            {
                perror("Kill error"); // obsluga bledu dla kill
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