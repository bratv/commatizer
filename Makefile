objects = handlenum.o utf.o

prog : $(objects)
	gcc -Wall -o prog $(objects)

handlenum.o : utf.h
utf.o : utf.h
