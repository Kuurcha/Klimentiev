%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h> 

int yylex();
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
%start startLabel

%union {
 int iValue; /* integer value */
 char sIndex; /* symbol table index */
}; 

%token <sIndex> SEPARATOR EXP ENTER INVALIDEXPONENT
%token <iValue> NUMBER SIGNEDNUMBER
%%

        startLabel:
                expr ENTER{
                      printf("Number is correct!");
                      printf("\n");
                      return 1;
                } 
                ; 
        expr: 
                mantisa EXP exponent
                ;
        mantisa: 
                SIGNEDNUMBER SEPARATOR repeatingNumber
                | NUMBER SEPARATOR repeatingNumber
                
        repeatingNumber: 
                repeatingNumber NUMBER
                |NUMBER 
                ;
        exponent:
                | SIGNEDNUMBER repeatingNumber
                | repeatingNumber
                | SIGNEDNUMBER 
                ;

       
 
%%