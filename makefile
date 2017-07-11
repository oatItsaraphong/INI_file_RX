#use -D USEDEBUG to see debug message

COMPLIEONLY = g++ -std=gnu++11 -Wall -c
LINKOBJ = g++ -std=gnu++11 -Wall

program: main.o IniFile.o
		$(LINKOBJ) main.o IniFile.o -o program

main.o:	main.cpp header/IniFile.h
		$(COMPLIEONLY) main.cpp -o main.o

IniFile.o: header/IniFile.h IniFile.cpp 
		$(COMPLIEONLY) IniFile.cpp -o IniFile.o

clean:
		rm *.o