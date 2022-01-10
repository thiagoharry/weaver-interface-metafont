/*5:*/
#line 173 "weaver-interface-metafont_en.tex"

#include "metafont.h"
/*12:*/
#line 337 "weaver-interface-metafont_en.tex"

#include <stdio.h> 
/*:12*//*14:*/
#line 360 "weaver-interface-metafont_en.tex"

#include <ctype.h> 
/*:14*//*32:*/
#line 731 "weaver-interface-metafont_en.tex"

#include <string.h> 
/*:32*/
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
/*34:*/
#line 796 "weaver-interface-metafont_en.tex"

#define TYPE_END             7 
/*:34*/
#line 262 "weaver-interface-metafont_en.tex"


struct generic_token{
int type;
void*next;
};
/*:9*/
#line 177 "weaver-interface-metafont_en.tex"


/*10:*/
#line 281 "weaver-interface-metafont_en.tex"

void free_token_list(void(*dealloc)(void*),void*token_list){
struct generic_token*p,*p_next;
if(dealloc==NULL||token_list==NULL)
return;
p= token_list;
while(p!=NULL){
p_next= p->next;
if(p->type==TYPE_SYMBOLIC)
dealloc(((struct symbolic_token*)p)->value);
dealloc(p);
p= p_next;
}
}
/*:10*//*11:*/
#line 303 "weaver-interface-metafont_en.tex"

void*lexer(void*(*alloc)(size_t),void(*dealloc)(void*),char*path){
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
/*13:*/
#line 350 "weaver-interface-metafont_en.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:13*/
#line 316 "weaver-interface-metafont_en.tex"

/*15:*/
#line 371 "weaver-interface-metafont_en.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
continue;
}
/*:15*/
#line 317 "weaver-interface-metafont_en.tex"

/*16:*/
#line 387 "weaver-interface-metafont_en.tex"

if((c=='.'&&isdigit(next_char))||isdigit(c)){
char buffer[256];
struct numeric_token*new_token= (struct numeric_token*)
alloc(sizeof(struct numeric_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
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
/*:16*/
#line 318 "weaver-interface-metafont_en.tex"

/*17:*/
#line 431 "weaver-interface-metafont_en.tex"

if(c=='"'){
struct string_token*new_token= (struct string_token*)
alloc(sizeof(struct string_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
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
dealloc(new_token);
free_token_list(dealloc,first_token);
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
/*:17*/
#line 319 "weaver-interface-metafont_en.tex"

/*18:*/
#line 473 "weaver-interface-metafont_en.tex"

if(c=='('||c==')'||c==','){
struct generic_token*new_token= 
(struct generic_token*)alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
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
/*:18*/
#line 320 "weaver-interface-metafont_en.tex"

/*19:*/
#line 503 "weaver-interface-metafont_en.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*20:*/
#line 532 "weaver-interface-metafont_en.tex"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:20*/
#line 509 "weaver-interface-metafont_en.tex"

/*21:*/
#line 549 "weaver-interface-metafont_en.tex"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:21*/
#line 510 "weaver-interface-metafont_en.tex"

/*22:*/
#line 565 "weaver-interface-metafont_en.tex"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:22*/
#line 511 "weaver-interface-metafont_en.tex"

/*23:*/
#line 581 "weaver-interface-metafont_en.tex"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:23*/
#line 512 "weaver-interface-metafont_en.tex"

/*24:*/
#line 597 "weaver-interface-metafont_en.tex"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:24*/
#line 513 "weaver-interface-metafont_en.tex"

/*25:*/
#line 613 "weaver-interface-metafont_en.tex"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:25*/
#line 514 "weaver-interface-metafont_en.tex"

/*26:*/
#line 629 "weaver-interface-metafont_en.tex"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:26*/
#line 515 "weaver-interface-metafont_en.tex"

/*27:*/
#line 645 "weaver-interface-metafont_en.tex"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:27*/
#line 516 "weaver-interface-metafont_en.tex"

/*28:*/
#line 661 "weaver-interface-metafont_en.tex"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:28*/
#line 517 "weaver-interface-metafont_en.tex"

/*29:*/
#line 677 "weaver-interface-metafont_en.tex"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:29*/
#line 518 "weaver-interface-metafont_en.tex"

/*30:*/
#line 693 "weaver-interface-metafont_en.tex"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:30*/
#line 519 "weaver-interface-metafont_en.tex"

/*31:*/
#line 709 "weaver-interface-metafont_en.tex"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:31*/
#line 520 "weaver-interface-metafont_en.tex"


/*35:*/
#line 806 "weaver-interface-metafont_en.tex"

if(!strcmp(buffer,"end")||!strcmp(buffer,"dump")){
struct generic_token*new_token= 
(struct generic_token*)alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
new_token->type= TYPE_END;
new_token->next= NULL;
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:35*/
#line 522 "weaver-interface-metafont_en.tex"

/*33:*/
#line 741 "weaver-interface-metafont_en.tex"

if(buffer[0]!='\0'){
buffer[255]= '\0';
size_t buffer_size= strlen(buffer)+1;
struct symbolic_token*new_token= 
(struct symbolic_token*)alloc(sizeof(struct symbolic_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
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
/*:33*/
#line 523 "weaver-interface-metafont_en.tex"

}
/*:19*/
#line 321 "weaver-interface-metafont_en.tex"


fprintf(stderr,"ERROR: Unknown character: '%c'\n",c);
free_token_list(dealloc,first_token);
return NULL;
}
return first_token;
}
/*:11*/
#line 179 "weaver-interface-metafont_en.tex"


/*:5*/
