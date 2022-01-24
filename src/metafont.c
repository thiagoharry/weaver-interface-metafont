/*6:*/
#line 197 "weaver-interface-metafont_en.tex"

#include "metafont.h"
/*15:*/
#line 421 "weaver-interface-metafont_en.tex"

#include <stdio.h> 
/*:15*//*17:*/
#line 444 "weaver-interface-metafont_en.tex"

#include <ctype.h> 
/*:17*//*35:*/
#line 829 "weaver-interface-metafont_en.tex"

#include <string.h> 
/*:35*/
#line 199 "weaver-interface-metafont_en.tex"


/*9:*/
#line 269 "weaver-interface-metafont_en.tex"

#define TYPE_NUMERIC 1
struct numeric_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
float value;
};
/*:9*//*10:*/
#line 285 "weaver-interface-metafont_en.tex"

#define TYPE_STRING 2
struct string_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
char value[5];
};
/*:10*//*11:*/
#line 311 "weaver-interface-metafont_en.tex"

#define TYPE_SYMBOLIC 3
struct symbolic_token{
int type;
void*next,*var;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
char*value;
};
/*:11*//*12:*/
#line 334 "weaver-interface-metafont_en.tex"

#define TYPE_OPEN_PARENTHESIS  4 
#define TYPE_CLOSE_PARENTHESIS 5 
#define TYPE_COMMA             6 
#define TYPE_SEMICOLON         7 
/*37:*/
#line 897 "weaver-interface-metafont_en.tex"

#define TYPE_END             8 
/*:37*//*47:*/
#line 1139 "weaver-interface-metafont_en.tex"

#define TYPE_BEGINGROUP             9 
#define TYPE_ENDGROUP              10 
/*:47*//*54:*/
#line 1321 "weaver-interface-metafont_en.tex"

#define TYPE_T_BOOLEAN               11 
#define TYPE_T_PATH                  12 
#define TYPE_T_PEN                   13 
#define TYPE_T_PICTURE               14 
#define TYPE_T_TRANSFORM             15 
#define TYPE_T_PAIR                  16 
#define TYPE_T_NUMERIC               17 
/*:54*/
#line 339 "weaver-interface-metafont_en.tex"


struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:12*//*56:*/
#line 1399 "weaver-interface-metafont_en.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:56*//*57:*/
#line 1421 "weaver-interface-metafont_en.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:57*/
#line 201 "weaver-interface-metafont_en.tex"

/*7:*/
#line 220 "weaver-interface-metafont_en.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:7*/
#line 202 "weaver-interface-metafont_en.tex"

/*42:*/
#line 994 "weaver-interface-metafont_en.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:42*//*45:*/
#line 1066 "weaver-interface-metafont_en.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:45*//*49:*/
#line 1180 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:49*/
#line 203 "weaver-interface-metafont_en.tex"

/*13:*/
#line 361 "weaver-interface-metafont_en.tex"

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
/*:13*//*14:*/
#line 383 "weaver-interface-metafont_en.tex"

void*lexer(void*(*alloc)(size_t),void(*dealloc)(void*),char*path){
FILE*fp;
char c;
int line= 1;
void*first_token= NULL,*last_token= NULL;
fp= fopen(path,"r");
if(fp==NULL)
return NULL;
while((c= fgetc(fp))!=EOF){
char next_char= fgetc(fp);
ungetc(next_char,fp);
if(c=='\n'){
line++;
continue;
}
/*16:*/
#line 434 "weaver-interface-metafont_en.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:16*/
#line 399 "weaver-interface-metafont_en.tex"

/*18:*/
#line 455 "weaver-interface-metafont_en.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:18*/
#line 400 "weaver-interface-metafont_en.tex"

/*19:*/
#line 472 "weaver-interface-metafont_en.tex"

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
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
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
/*:19*/
#line 401 "weaver-interface-metafont_en.tex"

/*20:*/
#line 519 "weaver-interface-metafont_en.tex"

if(c=='"'){
struct string_token*new_token= (struct string_token*)
alloc(sizeof(struct string_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
new_token->type= TYPE_STRING;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
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
fprintf(stderr,"ERROR: %s:%d: Incomplete String.\n",path,line);
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
/*:20*/
#line 402 "weaver-interface-metafont_en.tex"

/*21:*/
#line 564 "weaver-interface-metafont_en.tex"

if(c=='('||c==')'||c==','||c==';'){
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
else if(c==';')
new_token->type= TYPE_SEMICOLON;
else
new_token->type= TYPE_COMMA;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:21*/
#line 403 "weaver-interface-metafont_en.tex"

/*22:*/
#line 599 "weaver-interface-metafont_en.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*23:*/
#line 630 "weaver-interface-metafont_en.tex"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_'||isdigit(c));
ungetc(c,fp);
buffer[i]= '\0';
}
/*:23*/
#line 605 "weaver-interface-metafont_en.tex"

/*24:*/
#line 647 "weaver-interface-metafont_en.tex"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:24*/
#line 606 "weaver-interface-metafont_en.tex"

/*25:*/
#line 663 "weaver-interface-metafont_en.tex"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:25*/
#line 607 "weaver-interface-metafont_en.tex"

/*26:*/
#line 679 "weaver-interface-metafont_en.tex"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:26*/
#line 608 "weaver-interface-metafont_en.tex"

/*27:*/
#line 695 "weaver-interface-metafont_en.tex"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:27*/
#line 609 "weaver-interface-metafont_en.tex"

/*28:*/
#line 711 "weaver-interface-metafont_en.tex"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:28*/
#line 610 "weaver-interface-metafont_en.tex"

/*29:*/
#line 727 "weaver-interface-metafont_en.tex"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:29*/
#line 611 "weaver-interface-metafont_en.tex"

/*30:*/
#line 743 "weaver-interface-metafont_en.tex"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:30*/
#line 612 "weaver-interface-metafont_en.tex"

/*31:*/
#line 759 "weaver-interface-metafont_en.tex"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:31*/
#line 613 "weaver-interface-metafont_en.tex"

/*32:*/
#line 775 "weaver-interface-metafont_en.tex"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:32*/
#line 614 "weaver-interface-metafont_en.tex"

/*33:*/
#line 791 "weaver-interface-metafont_en.tex"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:33*/
#line 615 "weaver-interface-metafont_en.tex"

/*34:*/
#line 807 "weaver-interface-metafont_en.tex"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:34*/
#line 616 "weaver-interface-metafont_en.tex"


/*38:*/
#line 907 "weaver-interface-metafont_en.tex"

if(!strcmp(buffer,"end")||!strcmp(buffer,"dump")){
struct generic_token*new_token= 
(struct generic_token*)alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
new_token->type= TYPE_END;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:38*//*48:*/
#line 1149 "weaver-interface-metafont_en.tex"

else if(!strcmp(buffer,"begingroup")||!strcmp(buffer,"endgroup")){
struct generic_token*new_token= 
(struct generic_token*)alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
if(buffer[0]=='b')
new_token->type= TYPE_BEGINGROUP;
else
new_token->type= TYPE_ENDGROUP;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:48*//*55:*/
#line 1335 "weaver-interface-metafont_en.tex"

else if(!strcmp(buffer,"boolean")||!strcmp(buffer,"path")||
!strcmp(buffer,"pen")||!strcmp(buffer,"picture")||
!strcmp(buffer,"transform")||!strcmp(buffer,"pair")||
!strcmp(buffer,"numeric")){
struct generic_token*new_token= 
(struct generic_token*)alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
switch(buffer[0]){
case'b':
new_token->type= TYPE_T_BOOLEAN;break;
case'n':
new_token->type= TYPE_T_NUMERIC;break;
case't':
new_token->type= TYPE_T_TRANSFORM;break;
default:
switch(buffer[2]){
case't':
new_token->type= TYPE_T_PATH;break;
case'n':
new_token->type= TYPE_T_PEN;break;
case'c':
new_token->type= TYPE_T_PICTURE;break;
default:
new_token->type= TYPE_T_PAIR;break;
}
}
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
if(first_token==NULL)
first_token= last_token= new_token;
else{
((struct generic_token*)last_token)->next= new_token;
last_token= new_token;
}
continue;
}
/*:55*/
#line 618 "weaver-interface-metafont_en.tex"

/*36:*/
#line 839 "weaver-interface-metafont_en.tex"

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
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
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
/*:36*/
#line 619 "weaver-interface-metafont_en.tex"

}
/*:22*/
#line 404 "weaver-interface-metafont_en.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
return first_token;
}
/*:14*//*39:*/
#line 938 "weaver-interface-metafont_en.tex"

bool eval_program(struct metafont*mf,struct context*cx,
void*token_list){
struct generic_token*end= (struct generic_token*)token_list;
struct generic_token*previous= NULL;
while(end!=NULL&&end->type!=TYPE_END){
previous= end;
end= (struct generic_token*)(end->next);
}
if(end==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Program not finished with "
"'end' or 'dump'.\n",mf->file,
(previous==NULL)?(1):(previous->line));
#endif
return false;
}
if(end==token_list)
return true;
return eval_list_of_statements(mf,cx,token_list,previous);
}
/*:39*//*43:*/
#line 1010 "weaver-interface-metafont_en.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename){
struct metafont*mf;
size_t filename_size= strlen(filename)+1;
mf= (struct metafont*)alloc(sizeof(struct metafont));
mf->file= (char*)alloc(filename_size);
memcpy(mf->file,filename,filename_size);
mf->alloc= alloc;
mf->free= disalloc;
/*59:*/
#line 1443 "weaver-interface-metafont_en.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:59*/
#line 1021 "weaver-interface-metafont_en.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*63:*/
#line 1501 "weaver-interface-metafont_en.tex"

cx->variables= NULL;
/*:63*/
#line 1027 "weaver-interface-metafont_en.tex"

return cx;
}
/*:43*//*44:*/
#line 1037 "weaver-interface-metafont_en.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*60:*/
#line 1455 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
mf->free(v);
v= next;
}
}
/*:60*//*61:*/
#line 1472 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct named_variable*v= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(v!=NULL){
next= (struct named_variable*)(v->next);
mf->free(v->name);
mf->free(v->var);
mf->free(v);
v= next;
}
}
/*:61*/
#line 1041 "weaver-interface-metafont_en.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*64:*/
#line 1509 "weaver-interface-metafont_en.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
temporary_free(v);
v= next;
}
}
/*:64*/
#line 1047 "weaver-interface-metafont_en.tex"

temporary_free(cx);
}
}
/*:44*//*46:*/
#line 1078 "weaver-interface-metafont_en.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list){
bool ret= true;
struct generic_token*begin,*end= NULL;
begin= (struct generic_token*)begin_token_list;
while(begin!=NULL){
while(begin!=NULL&&begin->type==TYPE_SEMICOLON){
if(begin!=end_token_list)
begin= (struct generic_token*)begin->next;
else
begin= NULL;
}
end= begin;
if(end!=NULL){
while(end!=end_token_list&&
((struct generic_token*)(end->next))->type!=
TYPE_SEMICOLON)
end= end->next;
}
if(begin!=NULL){
ret= eval_statement(mf,cx,begin,(void**)&end);
if(!ret)
return false;
begin= end->next;
}
}
return ret;
}
/*:46*//*50:*/
#line 1187 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*51:*/
#line 1215 "weaver-interface-metafont_en.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:51*/
#line 1190 "weaver-interface-metafont_en.tex"

/*53:*/
#line 1262 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_BEGINGROUP){
struct generic_token*t= begin_token_list,*previous= NULL;
int nesting_level= 0;
while(t!=NULL){
if(t->type==TYPE_BEGINGROUP)
nesting_level++;
else if(t->type==TYPE_ENDGROUP){
nesting_level--;
if(nesting_level==0)
break;
}
previous= t;
t= (struct generic_token*)(t->next);
}
*end_token_list= t;
if(*end_token_list==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unclosed 'begingroup'.\n",
mf->file,begin_token_list->line);
#endif
return false;
}
if(previous==begin_token_list)
return true;
else{
bool ret;
cx->nesting_level++;
ret= eval_list_of_statements(mf,cx,((struct generic_token*)
begin_token_list)->next,
previous);
cx->nesting_level--;
return ret;
}
}
/*:53*/
#line 1191 "weaver-interface-metafont_en.tex"

/*65:*/
#line 1525 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type>=
TYPE_T_BOOLEAN&&
((struct generic_token*)begin_token_list)->type<=
TYPE_T_NUMERIC){

struct generic_token*variable_token= (struct generic_token*)
(((struct generic_token*)begin_token_list)->next);
do{
if(variable_token->type!=TYPE_SYMBOLIC){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: A declared variable "
"should be a single symbolic token.\n",mf->file,
variable_token->line);
#endif
return false;
}

if(variable_token!=*end_token_list)
variable_token= (struct generic_token*)(variable_token->next);
else{
variable_token= NULL;
continue;
}
if(variable_token->type!=TYPE_COMMA){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Declared variables "
"should be separed by commas.\n",mf->file,
variable_token->line);
#endif
return false;
}
if(variable_token==*end_token_list){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Variable declaration "
"shouldn't end with comma.\n",mf->file,
variable_token->line);
#endif
return false;
}
variable_token= (struct generic_token*)(variable_token->next);
}while(variable_token!=NULL);
}
/*:65*/
#line 1192 "weaver-interface-metafont_en.tex"







#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,begin_token_list->line);
#endif
return false;
}
/*:50*/
#line 204 "weaver-interface-metafont_en.tex"

/*8:*/
#line 233 "weaver-interface-metafont_en.tex"

void Winit_metafont(void*(*t_alloc)(size_t),
void(*t_free)(void*),
void*(*p_alloc)(size_t),
void(*p_free)(void*),
uint64_t(*random)(void),int pt_in_pixels){
temporary_alloc= t_alloc;
temporary_free= t_free;
permanent_alloc= p_alloc;
permanent_free= p_free;
random_func= random;
pt= pt_in_pixels;
}
/*:8*/
#line 205 "weaver-interface-metafont_en.tex"

/*:6*/
