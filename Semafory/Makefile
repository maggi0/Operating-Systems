#Rozszerzenia z ktorych korzystam
.SUFFIXES: .c .o .x .h
#nazwa katalogu - do archiwizacji i kompresji
DIR = `basename $(CURDIR)`
# Katalog dla bibliotek - do sprzataczki
LIB_DIR = ./lib
#nazwy plikow z ktorych korzystam
NAME1 = powielacz
NAME2 = bib
NAME3 = wykl
#argumenty
PROC = 
SEK = 
#programy wykonawcze; dodaje rozszerzenie .x
EXEC1 = $(NAME1).x
EXEC3 = $(NAME3).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS1  = $(NAME1).o
OBJS3  = $(NAME3).o
#biblioteki
LIB1 = $(NAME2).c
HEADS1 = $(NAME2).h
# Opcje kompilatora i linkera
CFLAGS = -pthread -Wall -std=c99 -pedantic
LFLAGS = -pthread -Wall -std=c99 -pedantic
# Kompilator i linker
CO = gcc
LD = $(CO)
# Regula wzorcowa; mowi jak otrzymac pliki z roszerzeniem .o z tych z .c.
# Po lewej - "cel", po prawej - "prerekwizyt".
# Make wykonuje kompilacje jesli plik celowy nie jest aktualny.
# % - dowolny ciag znakow
# $< - pierwszy prerekwizyt
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<
# Jawna regula zaleznosci - uaktualnia pliki po prawej stronie, potem wykonuje linkowanie
# $@ - cel
# $^ - wszystkie prerekwizyty
$(EXEC1): $(OBJS1) $(LIB1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3) $(LIB1)
	$(LD) -o $@ $(LFLAGS) $^
#uruchamianie programu
run: $(EXEC1) $(EXEC3)
	./$(EXEC1) $(EXEC3) $(PROC) $(SEK)
# Sprzataczka
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )