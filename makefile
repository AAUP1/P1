#Compilation of program with all files included

program.exe: states/addview.c states/editview.c states/menu.c states/overview.c box.c terminal.c main.c
	gcc states/addview.c states/editview.c states/menu.c states/overview.c box.c terminal.c main.c \
		-o program.exe

clean:
	rm program.exe