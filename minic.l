%option noyywrap
%option main
%{
#include "stdio.h"
%}

PALAVRACHAVE	return|int|printf|printint
LETRA 		[a-z]|[A-Z]|_
DIGITO 	[0-9]+
IDENTIFICADOR	{LETRA}({LETRA}|{DIGITO})*
COMENTARIO 	"//".*
OPBINARIO 	\<|\&\&|\+|\-|\*|\/|\^|\%
OPUNARIO 	!
STRING		\"(\\.|[^"\\])*\"
%%
{DIGITO} { 
printf("LITERAL INTEIRO: %d", atoi(yytext));
}
{STRING} { 
printf("LITERAL STRING: %s", yytext);
}
{PALAVRACHAVE} { 
printf("PALAVRA CHAVE: %s", yytext);
}
{IDENTIFICADOR} { 
printf("IDENTIFICADOR: %s", yytext);
}
{COMENTARIO} { 
printf("COMENTARIO: %s", yytext);
}
{OPBINARIO} { 
printf("OPERADOR BINÁRIO: %s", yytext);
}
{OPUNARIO} { 
printf("OPERADOR UNÁRIO: %s", yytext);
}
%%
