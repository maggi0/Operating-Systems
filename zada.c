#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

extern const char * const sys_siglist[];

void my_sighandler(int sygnal) // funkcja do wlasnej obslugi sygnalu
{
    printf("\nZostal przechwycony sygnal %d - %s\n", sygnal, sys_siglist[sygnal]); 
}

int main(int argc, char *argv[])
{
    if(argc!=3) // do nazwy programu dopisujemy nazwe sygnalu i polecenie
    {
        printf("Nieodpowiednia ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    int opcja=atoi(argv[1]); // zmiana polecenia z char na int
    int sygnal=atoi(argv[2]); // zmiana sygnalu z char na int

    switch(opcja) // wybor polecenia
    {
        case 1: 
        {
            if(signal(sygnal, SIG_DFL)==SIG_ERR) // domyslna obsluga sygnalu
            {
                perror("Signal error");
                exit(EXIT_FAILURE);
            }
        }
        break;
        case 2:
        {
            if(signal(sygnal, SIG_IGN)==SIG_ERR) // ignorowanie sygnalu
            {
                perror("Signal error");
                exit(EXIT_FAILURE);
            }
        }
        break;
        case 3:
        {
            if(signal(sygnal, my_sighandler)==SIG_ERR) // wlasna obsluga sygnalu
            {
                perror("Signal error");
                exit(EXIT_FAILURE);
            }
        }
        break;
        default: // przypadek gdy poleceniem nie bylo 1, 2 lub 3
        {
            printf("Nieodpowiedni argument\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("PID - %d \n", getpid());
    pause(); // oczekiwanie na dostanie sygnalu
}