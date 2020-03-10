CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic

main.out : main.o io.o mem.o func.o 
	$(CC) -o main.out $^

main.exe : main.o io.o mem.o func.o 
	$(CC) -o main.exe $^

main.o : main.c *.h
	$(CC) $(CFLAGS) -c $<

io.o : io.c *.h
	$(CC) $(CFLAGS) -c $<

mem.o : mem.c mem.h structs.h
	$(CC) $(CFLAGS) -c $<

func.o : func.c func.h structs.h
	$(CC) $(CFLAGS) -c $<

clean :
	rm *.o *.out *.exe