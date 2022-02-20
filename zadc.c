#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[])
{
    if(argc!=3) // do nazwy programu dopisujemy nazwe sygnalu i polecenie
    {
        printf("Nieodpowiednia ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    int sygnal=atoi(argv[2]); // zmiana sygnalu z char na int
    int pid; // pid dziecka
    int i;

    switch(pid=fork()) // fork zwraca pid dziecka
    {
        case -1: // obsluga bledu dla forka
        {
            perror("fork error\n");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            if(setpgid(0,0)==-1) // zmiana lidera procesu
            {
                perror("setpgid error"); // obsluga bledu dla setpgid
                exit(EXIT_FAILURE);
            }
        }
        break;
        default:
        {
        }
        break;
    }
}