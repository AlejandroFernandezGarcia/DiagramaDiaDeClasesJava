%{
	#include <stdlib.h>
	#include "Practica3.tab.h"
	char *p;
	//me falta escapar lo de package
	//escapar comentarios
	//escapar contenido de metodos
	//escapar imports
%}
string [^\x2C\t\n\x3B\x20\x28\x29\x7B\x7D]+
comas [\x2C]
%%
package {return PACKAGE;}
import {return IMPORT;}

public {return PUBLIC;}
private {return PRIVATE;}
protected {return PROTECTED;}



class {return CLASS;}
\{ {return '{';}
\} {return '}';}
\; {return ';';}
\( {return '(';}
\) {return ')';}

{string}	{
	p=(char*) malloc(sizeof(char)*strlen(yytext));
	strcpy(p,yytext);
	yylval.valChar = p;
	return STRING;
}
\n
\x20
%%
