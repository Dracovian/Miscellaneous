%{

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
    exit(-1);
}

void quit(void) {
    exit(0);
}

double dbldiv(double a, double b) {
    if (b == 0.0)
        yyerror("Division by Zero");
    
    return a / b;
}

long dblmod(double a, double b) {
    long _a = (long) a;
    long _b = (long) b;
    return _a % _b;
}

double dbllog(double a, double b) {
    double _a = log10(a);
    double _b = log10(b);
    return _a / _b;
}

long dblfact(double a) {
    long _a = (long) a;
    long _b = 1l;

    for (long _c = 2l; _c <= _a; _b *= _c, ++_c);
    return _b;
}


%}

%union { double dbl; }
%type <dbl> num;
%token <dbl> NUMBER

%token LPAREN RPAREN COMMA
%token ADD SUB MUL DIV MOD
%token POW ROOT LOG FACT
%token PI E

%%

start: num '\n' { fprintf(stdout, "%.3f\n\n", $1); } start
     | /* NULL */
     ;

num: NUMBER
   | '-' NUMBER { $$ = -$2; }
   | PI { $$ = yylval.dbl; }
   | E  { $$ = yylval.dbl; }
   | ADD  LPAREN NUMBER COMMA NUMBER RPAREN { $$ = $3 + $5; }
   | SUB  LPAREN NUMBER COMMA NUMBER RPAREN { $$ = $3 - $5; }
   | MUL  LPAREN NUMBER COMMA NUMBER RPAREN { $$ = $3 * $5; }
   | DIV  LPAREN NUMBER COMMA NUMBER RPAREN { $$ = dbldiv($3, $5); }
   | MOD  LPAREN NUMBER COMMA NUMBER RPAREN { $$ = dblmod($3, $5); }
   | POW  LPAREN NUMBER COMMA NUMBER RPAREN { $$ = pow($3, $5); }
   | ROOT LPAREN NUMBER COMMA NUMBER RPAREN { $$ = pow($3, 1.0 / $5); }
   | LOG  LPAREN NUMBER COMMA NUMBER RPAREN { $$ = dbllog($3, $5); }
   | FACT LPAREN NUMBER RPAREN              { $$ = dblfact($3); }
   ;

%%
