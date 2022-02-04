/*6:*/
#line 197 "weaver-interface-metafont_en.tex"

#include "metafont.h"
/*15:*/
#line 423 "weaver-interface-metafont_en.tex"

#include <stdio.h> 
/*:15*//*17:*/
#line 446 "weaver-interface-metafont_en.tex"

#include <ctype.h> 
/*:17*//*37:*/
#line 877 "weaver-interface-metafont_en.tex"

#include <string.h> 
/*:37*//*79:*/
#line 1773 "weaver-interface-metafont_en.tex"

#include <math.h> 
/*:79*/
#line 199 "weaver-interface-metafont_en.tex"

/*82:*/
#line 1831 "weaver-interface-metafont_en.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
/*:82*//*95:*/
#line 2155 "weaver-interface-metafont_en.tex"

#define IS_VALID_SUM_OR_SUB(prev, cur)                   \
        ((cur -> type == TYPE_SUM ||                    \
         cur -> type == TYPE_SUBTRACT) &&               \
         (prev != NULL && prev -> type != TYPE_COMMA && \
          prev -> type != TYPE_OPEN_BRACKET &&          \
          prev -> type != TYPE_MULTIPLICATION &&        \
          prev -> type != TYPE_DIVISION &&              \
          prev -> type != TYPE_SUM &&                   \
          prev -> type != TYPE_SUBTRACT &&              \
          prev -> type != TYPE_PYTHAGOREAN_SUM &&       \
          prev -> type != TYPE_PYTHAGOREAN_SUBTRACT &&  \
          prev -> type != TYPE_LENGTH &&                \
          prev -> type != TYPE_SQRT &&                  \
          prev -> type != TYPE_SIND &&                  \
          prev -> type != TYPE_COSD &&                  \
          prev -> type != TYPE_LOG &&                   \
          prev -> type != TYPE_EXP &&                   \
          prev -> type != TYPE_FLOOR &&                 \
          prev -> type != TYPE_UNIFORMDEVIATE))
/*:95*/
#line 200 "weaver-interface-metafont_en.tex"

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
/*39:*/
#line 947 "weaver-interface-metafont_en.tex"

#define TYPE_END             8 
#define TYPE_DUMP            9 
/*:39*//*50:*/
#line 1181 "weaver-interface-metafont_en.tex"

#define TYPE_BEGINGROUP            10 
#define TYPE_ENDGROUP              11 
/*:50*//*58:*/
#line 1349 "weaver-interface-metafont_en.tex"

#define TYPE_T_BOOLEAN               12 
#define TYPE_T_PATH                  13 
#define TYPE_T_PEN                   14 
#define TYPE_T_PICTURE               15 
#define TYPE_T_TRANSFORM             16 
#define TYPE_T_PAIR                  17 
#define TYPE_T_NUMERIC               18 
/*:58*//*85:*/
#line 1900 "weaver-interface-metafont_en.tex"

#define TYPE_ASSIGNMENT            19 
#define TYPE_ASSIGNMENT2           20 
/*:85*//*92:*/
#line 2099 "weaver-interface-metafont_en.tex"

#define TYPE_SUM                   21 
#define TYPE_SUBTRACT              22 
#define TYPE_PYTHAGOREAN_SUM       23 
#define TYPE_PYTHAGOREAN_SUBTRACT  24 
#define TYPE_OPEN_BRACKET          25 
#define TYPE_CLOSE_BRACKET         26 
/*:92*//*97:*/
#line 2262 "weaver-interface-metafont_en.tex"

#define TYPE_MULTIPLICATION        27 
#define TYPE_DIVISION              28 
/*:97*//*101:*/
#line 2403 "weaver-interface-metafont_en.tex"

#define TYPE_LENGTH         29 
#define TYPE_SQRT           30 
#define TYPE_SIND           31 
#define TYPE_COSD           32 
#define TYPE_LOG            33 
#define TYPE_EXP            34 
#define TYPE_FLOOR          35 
#define TYPE_UNIFORMDEVIATE 36 
/*:101*//*120:*/
#line 2914 "weaver-interface-metafont_en.tex"

#define TYPE_NORMALDEVIATE  37 
/*:120*/
#line 339 "weaver-interface-metafont_en.tex"


struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:12*//*60:*/
#line 1388 "weaver-interface-metafont_en.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:60*//*61:*/
#line 1410 "weaver-interface-metafont_en.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:61*//*77:*/
#line 1746 "weaver-interface-metafont_en.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:77*/
#line 201 "weaver-interface-metafont_en.tex"

/*7:*/
#line 220 "weaver-interface-metafont_en.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:7*//*35:*/
#line 830 "weaver-interface-metafont_en.tex"

static char*list_of_keywords[]= {
/*40:*/
#line 957 "weaver-interface-metafont_en.tex"

"end","dump",
/*:40*//*51:*/
#line 1190 "weaver-interface-metafont_en.tex"

"begingroup","endgroup",
/*:51*//*59:*/
#line 1363 "weaver-interface-metafont_en.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:59*//*86:*/
#line 1909 "weaver-interface-metafont_en.tex"

"=",":=",
/*:86*//*93:*/
#line 2112 "weaver-interface-metafont_en.tex"

"+","-","++","+-+","[","]",
/*:93*//*98:*/
#line 2269 "weaver-interface-metafont_en.tex"

"*","/",
/*:98*//*102:*/
#line 2416 "weaver-interface-metafont_en.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate"
/*:102*//*121:*/
#line 2920 "weaver-interface-metafont_en.tex"

"normaldeviate",
/*:121*/
#line 832 "weaver-interface-metafont_en.tex"

NULL};
/*:35*/
#line 202 "weaver-interface-metafont_en.tex"

/*45:*/
#line 1036 "weaver-interface-metafont_en.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:45*//*48:*/
#line 1108 "weaver-interface-metafont_en.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:48*//*52:*/
#line 1199 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:52*//*71:*/
#line 1593 "weaver-interface-metafont_en.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:71*//*73:*/
#line 1644 "weaver-interface-metafont_en.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:73*//*75:*/
#line 1705 "weaver-interface-metafont_en.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:75*//*90:*/
#line 2038 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source);
/*:90*//*94:*/
#line 2121 "weaver-interface-metafont_en.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:94*//*99:*/
#line 2277 "weaver-interface-metafont_en.tex"

bool eval_numeric_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:99*//*103:*/
#line 2424 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:103*//*108:*/
#line 2621 "weaver-interface-metafont_en.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:108*//*122:*/
#line 2931 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:122*/
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

void*lexer(struct metafont*mf,void*(*alloc)(size_t),
void(*dealloc)(void*),char*path){
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
#line 436 "weaver-interface-metafont_en.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:16*/
#line 400 "weaver-interface-metafont_en.tex"

/*18:*/
#line 457 "weaver-interface-metafont_en.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:18*/
#line 401 "weaver-interface-metafont_en.tex"

/*19:*/
#line 474 "weaver-interface-metafont_en.tex"

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
#line 402 "weaver-interface-metafont_en.tex"

/*20:*/
#line 521 "weaver-interface-metafont_en.tex"

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
#line 403 "weaver-interface-metafont_en.tex"

/*21:*/
#line 566 "weaver-interface-metafont_en.tex"

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
#line 404 "weaver-interface-metafont_en.tex"

/*22:*/
#line 601 "weaver-interface-metafont_en.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*23:*/
#line 632 "weaver-interface-metafont_en.tex"

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
#line 607 "weaver-interface-metafont_en.tex"

/*24:*/
#line 649 "weaver-interface-metafont_en.tex"

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
#line 608 "weaver-interface-metafont_en.tex"

/*25:*/
#line 665 "weaver-interface-metafont_en.tex"

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
#line 609 "weaver-interface-metafont_en.tex"

/*26:*/
#line 681 "weaver-interface-metafont_en.tex"

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
#line 610 "weaver-interface-metafont_en.tex"

/*27:*/
#line 697 "weaver-interface-metafont_en.tex"

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
#line 611 "weaver-interface-metafont_en.tex"

/*28:*/
#line 713 "weaver-interface-metafont_en.tex"

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
#line 612 "weaver-interface-metafont_en.tex"

/*29:*/
#line 729 "weaver-interface-metafont_en.tex"

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
#line 613 "weaver-interface-metafont_en.tex"

/*30:*/
#line 745 "weaver-interface-metafont_en.tex"

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
#line 614 "weaver-interface-metafont_en.tex"

/*31:*/
#line 761 "weaver-interface-metafont_en.tex"

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
#line 615 "weaver-interface-metafont_en.tex"

/*32:*/
#line 777 "weaver-interface-metafont_en.tex"

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
#line 616 "weaver-interface-metafont_en.tex"

/*33:*/
#line 793 "weaver-interface-metafont_en.tex"

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
#line 617 "weaver-interface-metafont_en.tex"

/*34:*/
#line 809 "weaver-interface-metafont_en.tex"

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
#line 618 "weaver-interface-metafont_en.tex"


/*36:*/
#line 843 "weaver-interface-metafont_en.tex"

{
int i,token_type= 0;
for(i= 0;list_of_keywords[i]!=NULL;i++)
if(!strcmp(buffer,list_of_keywords[i]))
token_type= i+8;
if(token_type!=0){
struct generic_token*new_token= 
(struct generic_token*)alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(dealloc,first_token);
return NULL;
}
/*41:*/
#line 966 "weaver-interface-metafont_en.tex"

if(token_type==TYPE_DUMP)
token_type= TYPE_END;
/*:41*//*87:*/
#line 1918 "weaver-interface-metafont_en.tex"

else if(token_type==TYPE_ASSIGNMENT2)
token_type= TYPE_ASSIGNMENT;
/*:87*/
#line 856 "weaver-interface-metafont_en.tex"

new_token->type= token_type;
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
}
/*:36*/
#line 620 "weaver-interface-metafont_en.tex"

/*38:*/
#line 887 "weaver-interface-metafont_en.tex"

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
new_token->var= NULL;
/*84:*/
#line 1853 "weaver-interface-metafont_en.tex"

if(!strcmp(buffer,"pt")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_PT]);
}
else if(!strcmp(buffer,"cm")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_CM]);
}
else if(!strcmp(buffer,"mm")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_MM]);
}
/*:84*/
#line 900 "weaver-interface-metafont_en.tex"

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
/*:38*/
#line 621 "weaver-interface-metafont_en.tex"

}
/*:22*/
#line 405 "weaver-interface-metafont_en.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
fclose(fp);
return first_token;
}
/*:14*//*42:*/
#line 980 "weaver-interface-metafont_en.tex"

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
/*:42*//*46:*/
#line 1052 "weaver-interface-metafont_en.tex"

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
/*63:*/
#line 1432 "weaver-interface-metafont_en.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:63*//*81:*/
#line 1803 "weaver-interface-metafont_en.tex"

mf->internal_numeric_variables= 
mf->alloc(3*sizeof(struct numeric_variable));
((struct numeric_variable*)mf->internal_numeric_variables)[0].value= 
pt;
((struct numeric_variable*)mf->internal_numeric_variables)[1].value= 
28.3465*pt;
((struct numeric_variable*)mf->internal_numeric_variables)[2].value= 
2.83465*pt;
{
int i;
for(i= 0;i<3;i++){
((struct numeric_variable*)
mf->internal_numeric_variables)[i].type= TYPE_T_NUMERIC;
((struct numeric_variable*)
mf->internal_numeric_variables)[i].nesting_level= 0;
((struct numeric_variable*)
mf->internal_numeric_variables)[i].next= NULL;

}
}
/*:81*/
#line 1063 "weaver-interface-metafont_en.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*56:*/
#line 1256 "weaver-interface-metafont_en.tex"

cx->nesting_level= 0;
/*:56*//*67:*/
#line 1490 "weaver-interface-metafont_en.tex"

cx->variables= NULL;
/*:67*/
#line 1069 "weaver-interface-metafont_en.tex"

return cx;
}
/*:46*//*47:*/
#line 1079 "weaver-interface-metafont_en.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*64:*/
#line 1444 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
mf->free(v);
v= next;
}
}
/*:64*//*65:*/
#line 1461 "weaver-interface-metafont_en.tex"

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
/*:65*//*83:*/
#line 1842 "weaver-interface-metafont_en.tex"

mf->free(mf->internal_numeric_variables);
/*:83*/
#line 1083 "weaver-interface-metafont_en.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*68:*/
#line 1498 "weaver-interface-metafont_en.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
temporary_free(v);
v= next;
}
}
/*:68*/
#line 1089 "weaver-interface-metafont_en.tex"

temporary_free(cx);
}
}
/*:47*//*49:*/
#line 1120 "weaver-interface-metafont_en.tex"

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
/*:49*//*53:*/
#line 1206 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*54:*/
#line 1233 "weaver-interface-metafont_en.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:54*/
#line 1209 "weaver-interface-metafont_en.tex"

/*57:*/
#line 1289 "weaver-interface-metafont_en.tex"

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
/*:57*/
#line 1210 "weaver-interface-metafont_en.tex"

/*69:*/
#line 1514 "weaver-interface-metafont_en.tex"

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
/*70:*/
#line 1564 "weaver-interface-metafont_en.tex"

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
/*:70*/
#line 1531 "weaver-interface-metafont_en.tex"

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
/*:69*/
#line 1211 "weaver-interface-metafont_en.tex"

/*88:*/
#line 1942 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_SYMBOLIC){
struct symbolic_token*var= (struct symbolic_token*)begin_token_list;
struct generic_token*begin_expression;
int type= 0;
int number_of_variables= 0;
do{
if(var->type!=TYPE_SYMBOLIC){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Non-symbolic "
"token in left side of assignment.\n",mf->file,
var->line);
#endif
return false;
}
if(var->var==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Undeclared variable "
"'%s'.\n",mf->file,var->line,var->value);
#endif
return false;
}
number_of_variables++;
if(type==0)
type= ((struct variable*)(var->var))->type;
else if(((struct variable*)(var->var))->type!=type){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Assigning variables "
"with different types: '%s'.\n",mf->file,
var->line,var->value);
#endif
return false;
}
if((void*)var!=end_token_list)
var= (struct symbolic_token*)(var->next);
else
var= NULL;
if(var->type!=TYPE_ASSIGNMENT){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Variable in left-side "
"without assignment.\n",mf->file,var->line);
#endif
return false;
}
if((void*)var!=end_token_list)
var= (struct symbolic_token*)(var->next);
else
var= NULL;
}while(var!=NULL&&
((struct generic_token*)(var->next))->type==
TYPE_ASSIGNMENT);
if(var==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Empty expression in "
"assignment.\n",mf->file,var->line);
#endif
return false;
}
begin_expression= (struct generic_token*)var;
/*89:*/
#line 2014 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_NUMERIC){
int i;
bool ret;
struct numeric_variable result;
ret= eval_numeric_expression(mf,cx,begin_expression,
(struct generic_token*)*end_token_list,
&result);
if(!ret)
return false;
var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
assign_numeric_variable((struct numeric_variable*)var->var,
&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:89*/
#line 2002 "weaver-interface-metafont_en.tex"

return true;
}
/*:88*/
#line 1212 "weaver-interface-metafont_en.tex"




#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:53*//*72:*/
#line 1606 "weaver-interface-metafont_en.tex"

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
/*78:*/
#line 1763 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:78*/
#line 1626 "weaver-interface-metafont_en.tex"

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
/*:72*//*74:*/
#line 1655 "weaver-interface-metafont_en.tex"

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
/*:74*//*76:*/
#line 1718 "weaver-interface-metafont_en.tex"

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
/*:76*//*91:*/
#line 2047 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source){
target->value= source->value;
}
/*:91*//*96:*/
#line 2183 "weaver-interface-metafont_en.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secundary,
*last_sum= NULL,*p,*prev= NULL;
int nesting_parenthesis= 0,nesting_brackets= 0;
struct numeric_variable a,b;
p= begin_expression;
do{
if(p->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_OPEN_BRACKET)
nesting_brackets++;
else if(p->type==TYPE_CLOSE_BRACKET)
nesting_brackets--;
else if(nesting_parenthesis==0&&nesting_brackets==0&&
(p->type==TYPE_PYTHAGOREAN_SUM||
p->type==TYPE_PYTHAGOREAN_SUBTRACT||
IS_VALID_SUM_OR_SUB(prev,p))){
last_sum= p;
end_tertiary= prev;
}
prev= p;
if(p!=end_token_list)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(end_tertiary!=NULL){
begin_secundary= (struct generic_token*)(last_sum->next);
eval_numeric_expression(mf,cx,begin_expression,end_tertiary,&a);
eval_numeric_secundary(mf,cx,begin_secundary,end_token_list,&b);
if(last_sum->type==TYPE_SUM)
result->value= a.value+b.value;
else if(last_sum->type==TYPE_SUBTRACT)
result->value= a.value-b.value;
else if(last_sum->type==TYPE_PYTHAGOREAN_SUM)
result->value= hypotf(a.value,b.value);
else if(last_sum->type==TYPE_PYTHAGOREAN_SUBTRACT){
result->value= sqrtf(a.value+b.value)*
sqrtf(a.value-b.value);
if(isnan(result->value)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Negative square root "
" in pythagorean subtraction.\n",mf->file,
var->line);
#endif
return false;
}
}
return true;
}
else
return eval_numeric_secundary(mf,cx,begin_expression,
end_token_list,result);
}
/*:96*//*100:*/
#line 2299 "weaver-interface-metafont_en.tex"

bool eval_numeric_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_secundary= NULL,*begin_primary,
*last_mul= NULL,*p,*prev= NULL,
*prev_prev= NULL,*last_fraction= NULL;
int nesting_parenthesis= 0,nesting_brackets= 0;
struct numeric_variable a,b;
b.value= 0.0;
p= begin_expression;
do{
if(p->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_OPEN_BRACKET)
nesting_brackets++;
else if(p->type==TYPE_CLOSE_BRACKET)
nesting_brackets--;
else if(nesting_parenthesis==0&&nesting_brackets==0&&
(p->type==TYPE_MULTIPLICATION||
p->type==TYPE_DIVISION)){
if(p->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
p!=end_token_list&&
((struct generic_token*)p->next)->type!=TYPE_NUMERIC&&
last_fraction!=prev_prev)
last_fraction= p;
else{
last_mul= p;
end_secundary= prev;
}
}
prev_prev= prev;
prev= p;
if(p!=end_token_list)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(end_secundary!=NULL){
begin_primary= (struct generic_token*)(last_mul->next);
eval_numeric_secundary(mf,cx,begin_expression,end_secundary,&a);
eval_numeric_primary(mf,cx,begin_primary,end_token_list,&b);
if(last_mul->type==TYPE_MULTIPLICATION)
result->value= a.value*b.value;
else if(last_mul->type==TYPE_DIVISION){
if(b.value==0.0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Division by zero.\n",
mf->file,last_mul->line);
#endif
return false;
}
result->value= a.value/b.value;
}
return true;
}
else
return eval_numeric_primary(mf,cx,begin_expression,
end_token_list,result);
}
/*:100*//*104:*/
#line 2437 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*105:*/
#line 2459 "weaver-interface-metafont_en.tex"

if(begin_expression==end_expression||
(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS)||
(begin_expression->type==TYPE_NUMERIC&&
begin_expression->next!=end_expression&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION&&
((struct generic_token*)begin_expression->next)->next==
end_expression&&
end_expression->type==TYPE_NUMERIC)){
return eval_numeric_atom(mf,cx,begin_expression,end_expression,
result);
}
/*:105*/
#line 2442 "weaver-interface-metafont_en.tex"

/*106:*/
#line 2482 "weaver-interface-metafont_en.tex"

if(end_expression->type==TYPE_CLOSE_BRACKET){
bool ret;
int nesting_parenthesis= 0,nesting_brackets= 0;
struct numeric_variable a,b,c;
struct generic_token*begin_a,*end_a,*begin_b,*end_b,*begin_c,
*end_c;
begin_a= begin_expression;
end_a= begin_a;
while(((struct generic_token*)end_a->next)->type!=
TYPE_OPEN_BRACKET||nesting_parenthesis!=0||
nesting_brackets!=0){
if(end_a->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(end_a->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
if(end_a->type==TYPE_OPEN_BRACKET)
nesting_brackets++;
else if(end_a->type==TYPE_CLOSE_BRACKET)
nesting_brackets--;
end_a= (struct generic_token*)end_a->next;
if(end_a==end_expression||nesting_parenthesis<0||
nesting_brackets<0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
}
begin_b= (struct generic_token*)end_a->next;
begin_b= (struct generic_token*)begin_b->next;
end_b= begin_b;
while(((struct generic_token*)end_b->next)->type!=TYPE_COMMA||
nesting_parenthesis!=0||nesting_brackets!=0){
if(end_b->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(end_b->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
if(end_b->type==TYPE_OPEN_BRACKET)
nesting_brackets++;
else if(end_b->type==TYPE_CLOSE_BRACKET)
nesting_brackets--;
end_b= (struct generic_token*)end_b->next;
if(end_b==end_expression||nesting_parenthesis<0||
nesting_brackets<0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
}
begin_c= (struct generic_token*)end_b->next;
begin_c= (struct generic_token*)begin_c->next;
end_c= begin_c;
while(((struct generic_token*)end_b->next)->type!=
TYPE_CLOSE_BRACKET||nesting_parenthesis!=0||
nesting_brackets!=0){
if(end_c->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(end_c->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
if(end_c->type==TYPE_OPEN_BRACKET)
nesting_brackets++;
else if(end_c->type==TYPE_CLOSE_BRACKET)
nesting_brackets--;
end_c= (struct generic_token*)end_c->next;
if(end_c==end_expression||nesting_parenthesis<0||
nesting_brackets<0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
}
ret= eval_numeric_atom(mf,cx,begin_a,end_a,&a);
if(!ret)
return false;
ret= eval_numeric_expression(mf,cx,begin_b,end_b,&b);
if(!ret)
return false;
ret= eval_numeric_expression(mf,cx,begin_b,end_b,&c);
if(!ret)
return false;
result->value= a.value*(b.value+c.value);
return true;
}
/*:106*/
#line 2443 "weaver-interface-metafont_en.tex"

/*107:*/
#line 2581 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_LENGTH){
int expr_type= get_primary_expression_type(mf,cx,
(struct generic_token*)
begin_expression->next,
end_expression);
if(expr_type==TYPE_T_NUMERIC){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;
result->value= ((num.value> 0)?(num.value):(-num.value));
return true;
}

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:107*/
#line 2444 "weaver-interface-metafont_en.tex"

/*110:*/
#line 2661 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_SQRT){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;
if(num.value<0.0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Square root "
"of negative number.\n",mf->file,
begin_expression->line);
#endif
return false;
}
result->value= sqrtf(num.value);
return true;
}
/*:110*//*111:*/
#line 2689 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_SIND){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;

result->value= sinf(num.value*0.0174533);
return true;
}
/*:111*//*112:*/
#line 2708 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_COSD){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;

result->value= cosf(num.value*0.0174533);
return true;
}
/*:112*//*113:*/
#line 2727 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_LOG){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;
if(num.value<=0.0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Computing logarithm of "
"non-positive number.\n",mf->file,
begin_expression->line);
#endif
return false;
}
result->value= logf(num.value);
return true;
}
/*:113*//*114:*/
#line 2753 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_EXP){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;
result->value= expf(num.value);
return true;
}
/*:114*//*115:*/
#line 2771 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_FLOOR){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;
result->value= floorf(num.value);
return true;
}
/*:115*//*116:*/
#line 2801 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_UNIFORMDEVIATE){
bool ret;
struct numeric_variable num;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,&num);
if(!ret)
return false;
{
uint64_t random_bits= random_func();
float multiplicand= (float)ldexp((double)random_bits,-64);
result->value= multiplicand*num.value;
}
return true;
}
/*:116*//*117:*/
#line 2824 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:117*//*118:*/
#line 2841 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_SUBTRACT){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
result->value*= -1;
return true;
}
/*:118*/
#line 2445 "weaver-interface-metafont_en.tex"

/*119:*/
#line 2865 "weaver-interface-metafont_en.tex"

else{
bool ret;
float token_value;
struct generic_token*after_token;
if(begin_expression->type!=TYPE_NUMERIC){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
token_value= ((struct numeric_token*)begin_expression)->value;
after_token= (struct generic_token*)(begin_expression->next);
if(after_token->type==TYPE_DIVISION){
if(after_token==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
after_token= (struct generic_token*)(after_token->next);
token_value/= ((struct numeric_token*)after_token)->value;
after_token= (struct generic_token*)(after_token->next);
}
ret= eval_numeric_primary(mf,cx,after_token,end_expression,result);
if(!ret)
return false;
result->value*= token_value;
return true;
}
/*:119*/
#line 2446 "weaver-interface-metafont_en.tex"

return true;
}
/*:104*//*109:*/
#line 2629 "weaver-interface-metafont_en.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr){
if(begin_expr==end_expr){
if(begin_expr->type==TYPE_NUMERIC)
return TYPE_T_NUMERIC;
else if(begin_expr->type==TYPE_SYMBOLIC){
struct symbolic_token*p= (struct symbolic_token*)begin_expr;
if(p->var==NULL)
return 0;
else{
struct variable*v= (struct variable*)(p->var);
return v->type;
}
}
}
else{

}
return TYPE_T_NUMERIC;

}
/*:109*//*123:*/
#line 2944 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*124:*/
#line 2966 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:124*/
#line 2950 "weaver-interface-metafont_en.tex"

/*125:*/
#line 2979 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_SYMBOLIC){
struct numeric_variable*var;
var= ((struct symbolic_token*)begin_expression)->var;
if(var==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Undeclared variable "
"'%s'.\n",mf->file,begin_expression->line,
((struct symbolic_token*)begin_expression)->value);
#endif
return false;
}
if(var->type!=TYPE_T_NUMERIC){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Non-numeric variable "
"'%s' in numeric expression.\n",mf->file,
begin_expression->line,
((struct symbolic_token*)begin_expression)->value);
#endif
return false;
}
if(isnan(var->value)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unitialized variable "
"'%s'.\n",mf->file,begin_expression->line,
((struct symbolic_token*)begin_expression)->value);
#endif
return false;
}
result->value= var->value;
return true;
}
/*:125*/
#line 2951 "weaver-interface-metafont_en.tex"


}
else{


}
return true;
}
/*:123*/
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
