D [0-9]
E [Ee][-+]?{D}+
%%
[ \t]+$ ;
"main" printf("tMain");
"{" printf("tOCB");
"}" printf("tCCB");
. {};
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
