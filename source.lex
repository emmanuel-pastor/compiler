D [0-9]
E [Ee][-+]?{D}+
L [a-zA-Z]
%%
[ \t\n]+ ;
"main" printf("tMain");
"{" printf("tOCB");
"}" printf("tCCB");
"const" printf("tConst");
"int" printf("tInt");
"+" printf("tAdd");
"-" printf("tSub");
"*" printf("tMul");
"/" printf("tDiv");
"=" printf("tEQ");
"(" printf("tOP");
")" printf("tCP");
"," printf("tCom");
";" printf("tSC");
"printf" printf("tPrintf");
{D}+(e{D}+)? { int n = strtold(yytext, NULL); printf("tValInt %s %d\n", yytext, n); }	
{L}({L}|{D}|\_)* printf("tId");
. printf("tError\n");
%%
int yywrap()
{
return 1 ;
}
int main ()
{
yylex() ;
return 1 ;
}
