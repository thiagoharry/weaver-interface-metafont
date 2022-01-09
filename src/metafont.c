/*5:*/
#line 173 "weaver-interface-metafont_en.tex"

#include "metafont.h"
/*11:*/
#line 313 "weaver-interface-metafont_en.tex"

#include <stdio.h> 
/*:11*//*13:*/
#line 336 "weaver-interface-metafont_en.tex"

#include <ctype.h> 
/*:13*//*31:*/
#line 699 "weaver-interface-metafont_en.tex"

#include <string.h> 
/*:31*/
#line 175 "weaver-interface-metafont_en.tex"


/*6:*/
#line 206 "weaver-interface-metafont_en.tex"

#define TYPE_NUMERIC 1
struct numeric_token{
int type;
void*next;
float value;
};
/*:6*//*7:*/
#line 219 "weaver-interface-metafont_en.tex"

#define TYPE_STRING 2
struct string_token{
int type;
void*next;
char value[5];
};
/*:7*//*8:*/
#line 242 "weaver-interface-metafont_en.tex"

#define TYPE_SYMBOLIC 3
struct symbolic_token{
int type;
void*next;
char*value;
};
/*:8*//*9:*/
#line 258 "weaver-interface-metafont_en.tex"

#define TYPE_OPEN_PARENTHESIS  4 
#define TYPE_CLOSE_PARENTHESIS 5 
#define TYPE_COMMA             6 


struct generic_token{
int type;
void*next;
};
/*:9*/
#line 177 "weaver-interface-metafont_en.tex"


/*10:*/
#line 280 "weaver-interface-metafont_en.tex"

void*lexer(void*(*alloc)(size_t),char*path){
FILE*fp;
char c;
void*first_token= NULL,*last_token= NULL;
fp= fopen(path,"r");
if(fp==NULL)
return NULL;
while((c= fgetc(fp))!=EOF){
char next_char= fgetc(fp);
ungetc(next_char,fp);
if(c=='\n')
continue;
/*12:*/
#line 326 "weaver-interface-metafont_en.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:12*/
#line 293 "weaver-interface-metafont_en.tex"

/*14:*/
#line 347 "weaver-interface-metafont_en.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
continue;
}
/*:14*/
#line 294 "weaver-interface-metafont_en.tex"

/*15:*/
#line 363 "weaver-interface-metafont_en.tex"

if((c=='.'&&isdigit(next_char))||isdigit(c)){
char buffer[256];
struct numeric_token*new_token= (struct numeric_token*)
alloc(sizeof(struct numeric_token));
if(new_token==NULL)
return NULL;
new_token->type= TYPE_NUMERIC;
new_token->next= NULL;
int i= 0;
int number_of_dots= (c=='.');
buffer[i]= c;
i++;
do{
c= fgetc(fp);
if(c=='.')
number_of_dots++;
buffer[i]= c;
i++;
}while(isdigit(c)||(c=='.'&&number_of_dots==1));
ungetc(c,fp);
i--;
buffer[i]= '\0';
new_token->value= atof(buffer);
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:15*/
#line 295 "weaver-interface-metafont_en.tex"

/*16:*/
#line 405 "weaver-interface-metafont_en.tex"

if(c=='"'){
struct string_token*new_token= (struct string_token*)
alloc(sizeof(struct string_token));
if(new_token==NULL)
return NULL;
new_token->type= TYPE_STRING;
new_token->next= NULL;
int i= 0;
do{
c= fgetc(fp);
if(i<5){
new_token->value[i]= c;
i++;
}
}while(c!='"'&&c!='\n'&&c!=EOF);
i--;
new_token->value[i]= '\0';
if(c=='\n'||c==EOF){
fprintf(stderr,"ERROR: Incomplete String.\n");
return NULL;
}
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:16*/
#line 296 "weaver-interface-metafont_en.tex"

/*17:*/
#line 443 "weaver-interface-metafont_en.tex"

if(c=='('||c==')'||c==','){
struct generic_token*new_token= 
(struct generic_token*)alloc(sizeof(struct generic_token));
if(new_token==NULL)
return NULL;
if(c=='(')
new_token->type= TYPE_OPEN_PARENTHESIS;
else if(c==')')
new_token->type= TYPE_CLOSE_PARENTHESIS;
else
new_token->type= TYPE_COMMA;
new_token->next= NULL;
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:17*/
#line 297 "weaver-interface-metafont_en.tex"

/*18:*/
#line 471 "weaver-interface-metafont_en.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*19:*/
#line 500 "weaver-interface-metafont_en.tex"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:19*/
#line 477 "weaver-interface-metafont_en.tex"

/*20:*/
#line 517 "weaver-interface-metafont_en.tex"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:20*/
#line 478 "weaver-interface-metafont_en.tex"

/*21:*/
#line 533 "weaver-interface-metafont_en.tex"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:21*/
#line 479 "weaver-interface-metafont_en.tex"

/*22:*/
#line 549 "weaver-interface-metafont_en.tex"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:22*/
#line 480 "weaver-interface-metafont_en.tex"

/*23:*/
#line 565 "weaver-interface-metafont_en.tex"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:23*/
#line 481 "weaver-interface-metafont_en.tex"

/*24:*/
#line 581 "weaver-interface-metafont_en.tex"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:24*/
#line 482 "weaver-interface-metafont_en.tex"

/*25:*/
#line 597 "weaver-interface-metafont_en.tex"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:25*/
#line 483 "weaver-interface-metafont_en.tex"

/*26:*/
#line 613 "weaver-interface-metafont_en.tex"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:26*/
#line 484 "weaver-interface-metafont_en.tex"

/*27:*/
#line 629 "weaver-interface-metafont_en.tex"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:27*/
#line 485 "weaver-interface-metafont_en.tex"

/*28:*/
#line 645 "weaver-interface-metafont_en.tex"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:28*/
#line 486 "weaver-interface-metafont_en.tex"

/*29:*/
#line 661 "weaver-interface-metafont_en.tex"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:29*/
#line 487 "weaver-interface-metafont_en.tex"

/*30:*/
#line 677 "weaver-interface-metafont_en.tex"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:30*/
#line 488 "weaver-interface-metafont_en.tex"



/*32:*/
#line 709 "weaver-interface-metafont_en.tex"

if(buffer[0]!='\0'){
buffer[255]= '\0';
size_t buffer_size= strlen(buffer)+1;
struct symbolic_token*new_token= 
(struct symbolic_token*)alloc(sizeof(struct symbolic_token));
if(new_token==NULL)
return NULL;
new_token->type= TYPE_SYMBOLIC;
new_token->next= NULL;
new_token->value= (char*)alloc(buffer_size);
memcpy(new_token->value,buffer,buffer_size);
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:32*/
#line 491 "weaver-interface-metafont_en.tex"

}
/*:18*/
#line 298 "weaver-interface-metafont_en.tex"


fprintf(stderr,"ERROR: Unknown character: '%c'\n",c);
return NULL;
}
return first_token;
}
/*:10*/
#line 179 "weaver-interface-metafont_en.tex"


/*:5*/
