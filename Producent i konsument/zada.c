#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

char *fifo; // zmienna globalna pod ktora wstawiamy pozniej nazwe potoku

void koniec(void) // funkcja sluzaca do usuwania potoku nazwanego
{
    if (unlink(fifo) == -1)
    {
        perror("Unlink error");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Usunieto\n");
    }
}

void my_sighandler() // funkcja obslugujaca sygnal
{
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    if (argc != 6) // sprawdzenie czy podano odpowiednia ilosc argumentow
    {
        printf("Nieprawidlowa ilosc argumentow!\n");
        exit(EXIT_FAILURE);
    }

    if (atexit(koniec) != 0) // usuwanie potoku nazwanego
    {
        perror("Atexit error");
        exit(EXIT_FAILURE);
    }
    
    if (mkfifo(argv[1], 0777) == -1) // utworzenie potoku nazwanego
    {
        perror("Mkfifo error");
        _exit(EXIT_FAILURE);
    }

    fifo = argv[1];
    int i;

    for (i = 0; i < 2; i++)
    {
        switch (fork())
        {
        case -1: // obsluga bledu dla forka
        {
            perror("fork error");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            if (i == 0) // producent
            {
                if (execl(argv[4], argv[4], argv[1], argv[2], NULL) == -1)
                {
                    perror("Execl error");
                    exit(EXIT_FAILURE);
                }
            }
            if (i == 1) // konsument
            {
                if (execl(argv[5], argv[5], argv[1], argv[3], NULL) == -1)
                {
                    perror("Execl error");
                    exit(EXIT_FAILURE);
                }
            }
            break;
        }
        default:
        {
        }
        }
    }
    if (signal(2, my_sighandler) == SIG_ERR) // wlasna obsluga sygnalu
    {
        perror("Signal error");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < 2; i++)
    {
        if (wait(NULL) == -1)
        {
            perror("Wait error");
            _exit(EXIT_FAILURE);
        }
    }
    return 0;
}