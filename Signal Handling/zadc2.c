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
    if(argc!=4) // do nazwy programu dopisujemy nazwe sygnalu i polecenie
    {
        printf("Nieodpowiednia ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    int sygnal=atoi(argv[2]); // zmiana sygnalu z char na int

    int i;
    int status;
    int stat_loc;

    for(i=0;i<3;i++)
    {
        switch(fork())
        {
            case -1: // obsluga bledu dla forka
            {
                perror("fork error");
                exit(EXIT_FAILURE);
            }
            break;
            case 0: // dla procesu potomnego
            {
                if(execl(argv[3],argv[3],argv[1],argv[2],NULL)==-1) // zainicjowanie procesu na podstawie "zada.x"
                {
                    perror("execl error"); // obsluga bledu dla execl
                    _exit(EXIT_FAILURE);
                }
            }
            break;
            default: // dla procesu macierzystego
            break;
        }
    }

    if(signal(sygnal, SIG_IGN)==SIG_ERR) // ustawienie ignorowania sygnalu dla lidera grupy
    {
        perror("Signal error"); 
        exit(EXIT_FAILURE);
    } 

    for(i=0;i<3;i++)
    {
        if((status=wait(&stat_loc))==-1) // obsluga bledu dla wait
        {
            perror ("Wait error");
            exit(EXIT_FAILURE);
        }
        printf("Status zakonczenia %d - %d\n", status, stat_loc); // wypisywanie statusu zakonczenia procesu za pomoca waita
    }
}
