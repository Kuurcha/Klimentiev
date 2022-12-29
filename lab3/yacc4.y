%{
#include <stdio.h>
#include <math.h>
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


float calculateExponentValue(int signedValue, int unsignedValue){
        int countDigits = 1;
        int unsignedValueBackup = unsignedValue;
        while (unsignedValueBackup > 10){
                countDigits++;
                unsignedValueBackup = unsignedValueBackup/10;
                printf("digits %i\n", countDigits);
        }
        signedValue=signedValue* pow(10,countDigits);
        return signedValue > 0? signedValue + unsignedValue: signedValue - unsignedValue;
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
 const char * sIndex; /* symbol table index */
 float fValue;
}; 

%token SEPARATOR EXP ENTER INVALIDEXPONENT
%token <iValue> NUMBER SIGNEDNUMBER
%type <fValue> mantisa
%type <iValue> repeatingNumber exponentNumber exponent
%%

        startLabel:
                mantisa exponent ENTER{
                      printf("Number is correct!");
                      float mantisaValue = $1;
                      float exponentValue = $2;
                      printf("\nMantisa value: %f\n",  mantisaValue);
                      printf("\nExponent value: %f\n", exponentValue);
                      printf("\n");
                      return 1;   
                } 
                ; 
        exponent:
                EXP exponentNumber{
                        $$ = $2;
                }
                ;
        mantisa: 
                SIGNEDNUMBER SEPARATOR repeatingNumber{
                        float firstNum = atoi($<sIndex>1);
                        double secondNum = calculateMantisaValue($3);
                        $$ = firstNum > 0? firstNum + secondNum: firstNum - secondNum;
                }
                | NUMBER SEPARATOR repeatingNumber{
                        float firstNum = atoi($<sIndex>1);
                        double secondNum = calculateMantisaValue($3);
                        $$ = firstNum +  secondNum;
                }
                
        repeatingNumber: 
                repeatingNumber NUMBER
                {
                        
                        int repeatingNumberValue = $1*10 + atoi($<sIndex>2);
                        $$ = repeatingNumberValue;
                }
                |NUMBER{
                        $$ = atoi($<sIndex>1);
                }
                ;
        exponentNumber:
                SIGNEDNUMBER repeatingNumber{
                        $$ = atoi($<sIndex>1);
                }
                | repeatingNumber
                {
                        $$ = $1;
                }
                | SIGNEDNUMBER {
                        int num = atoi($<sIndex>1);
                        $$ = num;
                }
                ;

       
 
%%