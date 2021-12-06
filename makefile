#Compilation of program with all files included

program.exe: loadSave.c states/addview.c states/editview.c states/menu.c states/overview.c UI.c terminal.c main.c
	gcc loadSave.c states/addview.c states/editview.c states/menu.c states/overview.c UI.c terminal.c main.c \
		-o program.exe

clean:
	rm program.exe