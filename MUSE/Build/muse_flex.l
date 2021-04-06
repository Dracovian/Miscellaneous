%{
#include "muse_bison.h"
%}

%option noyywrap
%option always-interactive

white [ \t]+
digit [0-9]
integer [-]?{digit}+
exponent [eE][+-]?{integer}
real {integer}("."{integer})?{exponent}?

%%

"ADD"|"add"   { return ADD; }
"SUB"|"sub"   { return SUB; }
"MUL"|"mul"   { return MUL; }
"DIV"|"div"   { return DIV; }
"MOD"|"mod"   { return MOD; }
"POW"|"pow"   { return POW; }
"ROOT"|"root" { return ROOT;}
"LOG"|"log"   { return LOG; }
"FACT"|"fact" { return FACT;}
"PI"|"pi"     { yylval.dbl = 3.1415926535897932384626433832795; return NUMBER; }
"E"|"e"       { yylval.dbl = 2.7182818284590452353602874713527; return NUMBER; }

"(" { return LPAREN; }
")" { return RPAREN; }
"," { return COMMA;  }

{real}  { yylval.dbl = atof(yytext); return NUMBER; }
[\n]    { return *yytext; }
{white} ;
\\q     { quit(); }
.       { yyerror("Unknown character"); }

%%