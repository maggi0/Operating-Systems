#Rozszerzenia z ktorych korzystam
.SUFFIXES: .c .o .x
#nazwa katalogu - do archiwizacji i kompresji
DIR = `basename $(CURDIR)`
# Katalog dla bibliotek - do sprzataczki
LIB_DIR = ./lib
#nazwy plikow z ktorych korzystam
NAME1 = zada
NAME2 = producent
NAME3 = konsument
#argumenty
ARG1 = in.txt
ARG2 = out.txt
#potok
FIFO = mojfifo
#programy wykonawcze; dodaje rozszerzenie .x
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
#pliki powstale po kompilacji plikow zrodlowych
OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic
LFLAGS = -Wall -std=c99 -pedantic
# Kompilator i linker
CO = gcc
LD = $(CO)
# Regula wzorcowa; mowi jak otrzymac pliki z roszerzeniem .o z tych z .c.
# Po lewej - "cel", po prawej - "prerekwizyt".
# Make wykonuje kompilacje jesli plik celowy nie jest aktualny.
# % - dowolny ciag znakow
# $< - pierwszy prerekwizyt
%.o: %.c
	$(CO) $(CFLAGS) -c $<
# Jawna regula zaleznosci - uaktualnia pliki po prawej stronie, potem wykonuje linkowanie
# $@ - cel
# $^ - wszystkie prerekwizyty
$(EXEC1): $(OBJS1) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2) 
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3) 
	$(LD) -o $@ $(LFLAGS) $^
#uruchamianie programu
run1: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(FIFO) $(ARG1) $(ARG2) $(EXEC2) $(EXEC3)
	diff -s $(ARG1) $(ARG2)

run2: $(EXEC2) $(EXEC3)
	mkfifo $(FIFO)
	xterm -hold -title $(NAME2) -e ./$(NAME2).x $(FIFO) $(ARG1) &
	xterm -hold -title $(NAME3) -e ./$(NAME3).x $(FIFO) $(ARG2)
	rm $(FIFO)
# Sprzataczka
.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )