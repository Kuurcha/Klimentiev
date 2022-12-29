%{
#include <stdio.h>
#include "y.tab.h"
%}

%%
[\+-][0-9]        { 
                  yylval.iValue=atoi(yytext);
                return SIGNEDNUMBER; 
              }
[0-9]         { 
                yylval.iValue=atoi(yytext); 
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
[^Ee]         {
                return INVALIDEXPONENT;
              }

%%



