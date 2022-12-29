%{
#include <stdio.h>
#include "y.tab.h"
#include <stdarg.h> 
%}

%%


[\+-][0-9]        { 
                  yylval.sIndex=yytext; 
                return SIGNEDNUMBER; 
              }
[0-9]         {
                yylval.sIndex=yytext; 
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



