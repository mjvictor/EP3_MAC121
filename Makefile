CC:=gcc
CFLAGS:=-Wall -ansi -pedantic -O2

ep3: tresReversao.o position.o
		$(CC) $(CFLAGS) -o $@ $^

%.o: %.c 
		$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -rf *.o