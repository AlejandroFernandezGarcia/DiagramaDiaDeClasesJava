%{
	#include <stdlib.h>
	#include "Practica3.tab.h"
	char *p;
%}
numero [0-9]+
string [^\x2C\x2E\t\n\x3B\x20]+
comas [\x2C]
%%
\n
\x20
%%
