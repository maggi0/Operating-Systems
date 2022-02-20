#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int in = open(argv[2], O_RDONLY); // otwarcie pliku in.txt
    if(in==-1)
    {
        perror("Open error");
        exit(EXIT_FAILURE);
    }
    int b1 = 16;
    char *BUFFER = malloc(b1);
    int fd = open(argv[1], O_WRONLY); // otwarcie potoku
    if(fd==-1)
    {
        perror("Open error");
        exit(EXIT_FAILURE);
    }
    int cz;
    int s;
    srand(42);                 // ustawienie "seeda" dla pseudo-losowych licz
    cz = read(in, BUFFER, b1); // czytanie z pliku do bufora
    if (cz == -1)              // obsluga bledu dla pierwszego reada
    {
        perror("Read error");
        exit(EXIT_FAILURE);
    }
    while (cz > 0) // wykonuje do czasu, gdy liczba wczytanych bitow jest wieksza niz 0
    {
        int b = write(fd, BUFFER, cz); // pisanie z bufora do potoku
        if (b == -1)
        {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        if (write(STDOUT_FILENO, "Producent - ", 12) == -1) // wypisywanie na konsole komunikatu swiadczacego o tym,
        {                                                   // ze jest to producent.
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        if (write(STDOUT_FILENO, BUFFER, b1) == -1) // wypisywanie na konsole zawartosci bufora
        {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        char *temp = malloc(2);                   // utworzenie tymczasowego bufora
        sprintf(temp, " - %d\n", b);              // zapisanie do bufora liczby zapisanych bitow funkcja write do potoku
        if (write(STDOUT_FILENO, temp, 16) == -1) // wypisywanie na konsole ta liczbe
        {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        memset(BUFFER, 0, 16);     // wyzerowanie bufora
        s = rand() % 3 + 1;        // przypisanie zmiennej s liczby od 1 do 3
        sleep(s);                  // uspienie procesu na s sekund
        cz = read(in, BUFFER, b1); // czytanie z pliku do bufora w petli
        if (cz == -1)
        {
            perror("Read error");
            exit(EXIT_FAILURE);
        }
    }
    if(close(fd)==-1) // zamkniecie deskryptorow
    {
        perror("Close error");
        exit(EXIT_FAILURE);
    }
    if(close(in)==-1)
    {
        perror("Close error");
        exit(EXIT_FAILURE);
    } 
}