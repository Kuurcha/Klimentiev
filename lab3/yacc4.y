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

float calculateMantisaValue(int value){
       
        float mantisaValue = value;
        while(mantisaValue>1)
                mantisaValue=mantisaValue/10;
        return mantisaValue;
} 
float calculateExponentValue(int value){

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
 float fValue;
}; 

%token SEPARATOR EXP ENTER INVALIDEXPONENT
%token <iValue> NUMBER SIGNEDNUMBER
%type <fValue> mantisa
%type <iValue> repeatingNumber, exponentNumber, exponent
%%

        startLabel:
                mantisa exponent ENTER{
                      printf("Number is correct!");
                      printf("\nMantisa value: %f\n", $1);
                      printf("\n");
                      return 1;
                      
                      
                } 
                ; 
        exponent:
                EXP exponentNumber
                ;
        mantisa: 
                SIGNEDNUMBER SEPARATOR repeatingNumber{
                        float firstNum = $1;
                        double secondNum = calculateMantisaValue($3);
                        $$ = firstNum > 0? firstNum + secondNum: firstNum - secondNum;
                }
                | NUMBER SEPARATOR repeatingNumber{
                        float firstNum = $1;
                        double secondNum = calculateMantisaValue($3);
                        $$ = firstNum +  secondNum;
                }
                
        repeatingNumber: 
                repeatingNumber NUMBER
                {
                        int repeatingNumberValue = $1*10 + $2;
                        $$ = repeatingNumberValue;
                }
                |NUMBER{
                        $$ = $1;
                }
                ;
        exponentNumber:
                | SIGNEDNUMBER repeatingNumber{
                        $$ = $1;
                }
                | repeatingNumber
                | SIGNEDNUMBER {
                        $$ = $1;
                }
                ;

       
 
%%