reversi.exe: reversi.o reversi_ui.o
	gcc -o reversi.exe reversi.o reversi_ui.o

reversi.o: reversi.c
	gcc -c reversi.c

reversi_ui.o: reversi_ui.c
	gcc -c reversi_ui.c

clean:
	del *.exe *.o