%{
#include <stdio.h>
#include <string.h>

int yywrap(){ return 1; }
#define input_str argv[1]

void yyerror(const char *str)
{
        printf("Error. Incorrect number format\n");
        return 0;
        
}

int calculateExponentValue(int i){
        int res = 0;
        while(i>0)
        {
                res = res*10+i%10;
                i /= 10;
        }
        return res;
} 

int main(int argn, char **argv)
{
        strcat(input_str, "\n");
	yy_scan_string(input_str);
        yyparse();
}

%}
%start start
%token SIGN NUMBER SEPARATOR EXP ENTER
%%
        start: 
                | SIGN beforeMantisa
                | NUMBER {
                        printf("ok!");
                }
        beforeMantisa:
                | NUMBER {
                        printf("ok!");
                }
%%
