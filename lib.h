#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <wchar.h> // wchar needed for wprint too show different symbols.
#include <unistd.h> //used for clearing the screen
#include <windows.h> //used for placing cursor in console
#include <time.h>
#include <ctype.h> //Is used to make all letters lowercase, making the search function in drawProducts case insensitive
#include "terminal.h"
#include "UI.h"
#include "loadSave.h"
#include "product.h"

#include "states/editview.h"
#include "states/state.h"
#include "states/overview.h"
#include "states/menu.h"