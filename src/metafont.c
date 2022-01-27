/*6:*/
#line 215 "weaver-interface-metafont.tex"

#include "metafont.h"
/*15:*/
#line 442 "weaver-interface-metafont.tex"

#include <stdio.h> 
/*:15*//*17:*/
#line 464 "weaver-interface-metafont.tex"

#include <ctype.h> 
/*:17*//*35:*/
#line 852 "weaver-interface-metafont.tex"

#include <string.h> 
/*:35*/
#line 217 "weaver-interface-metafont.tex"


/*9:*/
#line 286 "weaver-interface-metafont.tex"

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
#line 302 "weaver-interface-metafont.tex"

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
#line 329 "weaver-interface-metafont.tex"

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
#line 353 "weaver-interface-metafont.tex"

#define TYPE_OPEN_PARENTHESIS  4 
#define TYPE_CLOSE_PARENTHESIS 5 
#define TYPE_COMMA             6 
#define TYPE_SEMICOLON         7 
/*37:*/
#line 922 "weaver-interface-metafont.tex"

#define TYPE_END             8 
/*:37*//*47:*/
#line 1167 "weaver-interface-metafont.tex"

#define TYPE_BEGINGROUP             9 
#define TYPE_ENDGROUP              10 
/*:47*//*55:*/
#line 1357 "weaver-interface-metafont.tex"

#define TYPE_T_BOOLEAN               11 
#define TYPE_T_PATH                  12 
#define TYPE_T_PEN                   13 
#define TYPE_T_PICTURE               14 
#define TYPE_T_TRANSFORM             15 
#define TYPE_T_PAIR                  16 
#define TYPE_T_NUMERIC               17 
/*:55*/
#line 358 "weaver-interface-metafont.tex"


struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:12*//*57:*/
#line 1435 "weaver-interface-metafont.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:57*//*58:*/
#line 1455 "weaver-interface-metafont.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:58*//*74:*/
#line 1787 "weaver-interface-metafont.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:74*/
#line 219 "weaver-interface-metafont.tex"

/*7:*/
#line 238 "weaver-interface-metafont.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:7*/
#line 220 "weaver-interface-metafont.tex"

/*42:*/
#line 1019 "weaver-interface-metafont.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:42*//*45:*/
#line 1091 "weaver-interface-metafont.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:45*//*49:*/
#line 1207 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:49*//*68:*/
#line 1638 "weaver-interface-metafont.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:68*//*70:*/
#line 1688 "weaver-interface-metafont.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:70*//*72:*/
#line 1748 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:72*/
#line 221 "weaver-interface-metafont.tex"

/*13:*/
#line 381 "weaver-interface-metafont.tex"

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
#line 404 "weaver-interface-metafont.tex"

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
#line 454 "weaver-interface-metafont.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:16*/
#line 420 "weaver-interface-metafont.tex"

/*18:*/
#line 475 "weaver-interface-metafont.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:18*/
#line 421 "weaver-interface-metafont.tex"

/*19:*/
#line 492 "weaver-interface-metafont.tex"

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
#line 422 "weaver-interface-metafont.tex"

/*20:*/
#line 540 "weaver-interface-metafont.tex"

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
#line 423 "weaver-interface-metafont.tex"

/*21:*/
#line 585 "weaver-interface-metafont.tex"

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
#line 424 "weaver-interface-metafont.tex"

/*22:*/
#line 620 "weaver-interface-metafont.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*23:*/
#line 653 "weaver-interface-metafont.tex"

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
#line 626 "weaver-interface-metafont.tex"

/*24:*/
#line 670 "weaver-interface-metafont.tex"

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
#line 627 "weaver-interface-metafont.tex"

/*25:*/
#line 686 "weaver-interface-metafont.tex"

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
#line 628 "weaver-interface-metafont.tex"

/*26:*/
#line 702 "weaver-interface-metafont.tex"

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
#line 629 "weaver-interface-metafont.tex"

/*27:*/
#line 718 "weaver-interface-metafont.tex"

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
#line 630 "weaver-interface-metafont.tex"

/*28:*/
#line 734 "weaver-interface-metafont.tex"

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
#line 631 "weaver-interface-metafont.tex"

/*29:*/
#line 750 "weaver-interface-metafont.tex"

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
#line 632 "weaver-interface-metafont.tex"

/*30:*/
#line 766 "weaver-interface-metafont.tex"

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
#line 633 "weaver-interface-metafont.tex"

/*31:*/
#line 782 "weaver-interface-metafont.tex"

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
#line 634 "weaver-interface-metafont.tex"

/*32:*/
#line 798 "weaver-interface-metafont.tex"

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
#line 635 "weaver-interface-metafont.tex"

/*33:*/
#line 814 "weaver-interface-metafont.tex"

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
#line 636 "weaver-interface-metafont.tex"

/*34:*/
#line 830 "weaver-interface-metafont.tex"

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
#line 637 "weaver-interface-metafont.tex"


/*38:*/
#line 932 "weaver-interface-metafont.tex"

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
#line 1176 "weaver-interface-metafont.tex"

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
/*:48*//*56:*/
#line 1371 "weaver-interface-metafont.tex"

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
/*:56*/
#line 639 "weaver-interface-metafont.tex"

/*36:*/
#line 861 "weaver-interface-metafont.tex"

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
#line 640 "weaver-interface-metafont.tex"

}
/*:22*/
#line 425 "weaver-interface-metafont.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
return first_token;
}
/*:14*//*39:*/
#line 964 "weaver-interface-metafont.tex"

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
#line 1035 "weaver-interface-metafont.tex"

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
/*60:*/
#line 1477 "weaver-interface-metafont.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:60*/
#line 1046 "weaver-interface-metafont.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*53:*/
#line 1265 "weaver-interface-metafont.tex"

cx->nesting_level= 0;
/*:53*//*64:*/
#line 1535 "weaver-interface-metafont.tex"

cx->variables= NULL;
/*:64*/
#line 1052 "weaver-interface-metafont.tex"

return cx;
}
/*:43*//*44:*/
#line 1061 "weaver-interface-metafont.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*61:*/
#line 1489 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
mf->free(v);
v= next;
}
}
/*:61*//*62:*/
#line 1506 "weaver-interface-metafont.tex"

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
/*:62*/
#line 1065 "weaver-interface-metafont.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*65:*/
#line 1543 "weaver-interface-metafont.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
temporary_free(v);
v= next;
}
}
/*:65*/
#line 1071 "weaver-interface-metafont.tex"

temporary_free(cx);
}
}
/*:44*//*46:*/
#line 1104 "weaver-interface-metafont.tex"

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
#line 1213 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*51:*/
#line 1242 "weaver-interface-metafont.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:51*/
#line 1216 "weaver-interface-metafont.tex"

/*54:*/
#line 1298 "weaver-interface-metafont.tex"

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
mf->file,
((struct generic_token*)begin_token_list)->line);
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
/*:54*/
#line 1217 "weaver-interface-metafont.tex"

/*66:*/
#line 1559 "weaver-interface-metafont.tex"

else if(((struct generic_token*)begin_token_list)->type>=
TYPE_T_BOOLEAN&&
((struct generic_token*)begin_token_list)->type<=
TYPE_T_NUMERIC){
int type= ((struct generic_token*)begin_token_list)->type;
struct symbolic_token*variable= (struct symbolic_token*)
(((struct symbolic_token*)begin_token_list)->next);
do{
if(variable->type!=TYPE_SYMBOLIC){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: A declared variable "
"should be a single symbolic token.\n",mf->file,
variable->line);
#endif
return false;
}
/*67:*/
#line 1609 "weaver-interface-metafont.tex"

{
void*variable_pointer;
if(cx->nesting_level==0){
if(variable->value[0]=='_')
variable_pointer= insert_variable(0,mf->alloc,type,variable,
&(mf->global_variables));
else
variable_pointer= insert_named_global_variable(mf,type,variable);
}
else
variable_pointer= insert_variable(cx->nesting_level,
temporary_alloc,type,
variable,&(cx->variables));
if(variable_pointer==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: No memory to create "
"variable.\n",mf->file,variable->line);
#endif
return false;
}
update_token_pointer_for_variable(variable,variable_pointer);
}
/*:67*/
#line 1576 "weaver-interface-metafont.tex"

if(variable!=*end_token_list)
variable= (struct symbolic_token*)(variable->next);
else{
variable= NULL;
continue;
}
if(variable->type!=TYPE_COMMA){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Declared variables "
"should be separed by commas.\n",mf->file,
variable->line);
#endif
return false;
}
if(variable==*end_token_list){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Variable declaration "
"shouldn't end with comma.\n",mf->file,
variable->line);
#endif
return false;
}
variable= (struct symbolic_token*)(variable->next);
}while(variable!=NULL);
return true;
}
/*:66*/
#line 1218 "weaver-interface-metafont.tex"







#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:50*//*69:*/
#line 1651 "weaver-interface-metafont.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target){
struct variable*var;
size_t var_size;
switch(type){
case TYPE_T_NUMERIC:
var_size= sizeof(struct numeric_variable);
break;
default:
var_size= sizeof(struct variable);
}
var= (struct variable*)alloc(var_size);
if(var!=NULL){
var->type= type;
var->next= NULL;
var->nesting_level= nesting_level;
}
if(*target==NULL)
*target= var;
else{
struct variable*p= (struct variable*)(*target);
while(p->next!=NULL)
p= (struct variable*)p->next;
p->next= var;
}
return var;
}
/*:69*//*71:*/
#line 1699 "weaver-interface-metafont.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var){
struct named_variable*named;
struct variable*new_var;
size_t name_size;
named= (struct named_variable*)
mf->alloc(sizeof(struct named_variable));
if(named==NULL)
return NULL;
name_size= strlen(var->value)+1;
named->name= (char*)mf->alloc(name_size);
if(named->name==NULL){
if(mf->free!=NULL)
mf->free(named);
return NULL;
}
memcpy(named->name,var->value,name_size);
named->next= NULL;
named->var= NULL;
new_var= insert_variable(0,mf->alloc,type,var,
(void**)&(named->var));
if(new_var==NULL){
if(mf->free!=NULL){
mf->free(named->name);
mf->free(named);
return NULL;
}
}
if(mf->named_variables==NULL)
mf->named_variables= named;
else{
struct named_variable*p= (struct named_variable*)
mf->named_variables;
while(p->next!=NULL)
p= (struct named_variable*)p->next;
p->next= named;
}
return new_var;
}
/*:71*//*73:*/
#line 1761 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer){
struct symbolic_token*p= var_token->next;
int nesting_level= 0;
while(p!=NULL&&nesting_level>=0){
if(p->type==TYPE_BEGINGROUP)
nesting_level++;
else if(p->type==TYPE_ENDGROUP)
nesting_level--;
else if(p->type==TYPE_SYMBOLIC){
if(!strcmp(p->value,var_token->value)){
p->var= var_pointer;
}
}
p= (struct symbolic_token*)(p->next);
}
}
/*:73*/
#line 222 "weaver-interface-metafont.tex"

/*8:*/
#line 251 "weaver-interface-metafont.tex"

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
#line 223 "weaver-interface-metafont.tex"

/*:6*/
