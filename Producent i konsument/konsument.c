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
    int out = open(argv[2], O_WRONLY | O_TRUNC); // otwarcie pliku out.txt
    int b1 = 16;
    char *BUFFER = malloc(b1);
    int fd = open(argv[1], O_RDONLY); // otwarcie potoku
    sleep(2);                         // krotkie uspienie procesu
    int s;
    int p;
    srand(43);                // ustawienie innego "seeda" dla pseudo-losowych licz
    p = read(fd, BUFFER, b1); // czytanie z potoku do bufora
    if (p == -1)              // obsluga bledu dla pierwszego czytania
    {
        perror("Read error");
        exit(EXIT_FAILURE);
    }
    while (p > 0) // wykonywanie do czasu, gdy jest co czytac z potoku
    {
        int b = write(out, BUFFER, p); // pisanie z buforu do pliku
        if (b == -1)
        {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        if (write(STDOUT_FILENO, "Konsument - ", 12) == -1) // wypisywanie na konsole komunikatu swiadczacego o tym,
        {                                                   // ze jest to konsument.
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        if (write(STDOUT_FILENO, BUFFER, b1) == -1) // wypisywanie na konsole zawartosci bufora
        {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        char *temp = malloc(2);                   // utworzenie tymczasowego bufora
        sprintf(temp, " - %d\n", b);              // zapisanie do bufora liczby zapisanych bitow do pliku wyjsciowego
        if (write(STDOUT_FILENO, temp, 16) == -1) // wypisanie na konsole tej liczby
        {
            perror("Write error");
            exit(EXIT_FAILURE);
        }
        memset(BUFFER, 0, 16);    // wyzerowanie zawartosci bufora
        s = rand() % 3 + 1;       // przypisanie zmiennej s liczby od 1 do 3
        sleep(s);                 // uspienie procesu na s sekund
        p = read(fd, BUFFER, b1); // czytanie z potoku do bufora w petli
        if (p == -1)
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
    if(close(out)==-1)
    {
        perror("Close error");
        exit(EXIT_FAILURE);
    }
}