%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
[\+|-]        { 
                yylval=atoi(yytext); 
                return SIGN; 
              }
[0-9]         { 
                yylval=atoi(yytext); 
                return NUMBER; 
              }
[.,]          {
                return SEPARATOR;
              }
[Ee]          { 
                return EXP;
              }
[\n]          {
                return ENTER;
              }
%%


