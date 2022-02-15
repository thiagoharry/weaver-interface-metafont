/*6:*/
#line 215 "weaver-interface-metafont.tex"

#include "metafont.h"
/*15:*/
#line 444 "weaver-interface-metafont.tex"

#include <stdio.h> 
/*:15*//*17:*/
#line 466 "weaver-interface-metafont.tex"

#include <ctype.h> 
/*:17*//*37:*/
#line 900 "weaver-interface-metafont.tex"

#include <string.h> 
/*:37*//*79:*/
#line 1798 "weaver-interface-metafont.tex"

#include <math.h> 
/*:79*/
#line 217 "weaver-interface-metafont.tex"

/*82:*/
#line 1855 "weaver-interface-metafont.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
/*:82*//*103:*/
#line 2374 "weaver-interface-metafont.tex"

#define IS_VALID_SUM_OR_SUB(prev, cur)                   \
        ((cur -> type == TYPE_SUM ||                    \
         cur -> type == TYPE_SUBTRACT) &&               \
         (prev != NULL && prev -> type != TYPE_COMMA && \
          prev -> type != TYPE_OPEN_BRACKETS &&          \
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
          prev -> type != TYPE_ROTATED &&               \
          prev -> type != TYPE_SCALED &&                \
          prev -> type != TYPE_SHIFTED &&               \
          prev -> type != TYPE_SLANTED &&               \
          prev -> type != TYPE_XSCALED &&               \
          prev -> type != TYPE_YSCALED &&               \
          prev -> type != TYPE_ZSCALED &&               \
          prev -> type != TYPE_UNIFORMDEVIATE))
/*:103*/
#line 218 "weaver-interface-metafont.tex"

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
/*39:*/
#line 972 "weaver-interface-metafont.tex"

#define TYPE_END             8 
#define TYPE_DUMP            9 
/*:39*//*50:*/
#line 1208 "weaver-interface-metafont.tex"

#define TYPE_BEGINGROUP            10 
#define TYPE_ENDGROUP              11 
/*:50*//*58:*/
#line 1374 "weaver-interface-metafont.tex"

#define TYPE_T_BOOLEAN               12 
#define TYPE_T_PATH                  13 
#define TYPE_T_PEN                   14 
#define TYPE_T_PICTURE               15 
#define TYPE_T_TRANSFORM             16 
#define TYPE_T_PAIR                  17 
#define TYPE_T_NUMERIC               18 
/*:58*//*93:*/
#line 2108 "weaver-interface-metafont.tex"

#define TYPE_ASSIGNMENT            19 
#define TYPE_ASSIGNMENT2           20 
/*:93*//*100:*/
#line 2312 "weaver-interface-metafont.tex"

#define TYPE_SUM                   21 
#define TYPE_SUBTRACT              22 
#define TYPE_PYTHAGOREAN_SUM       23 
#define TYPE_PYTHAGOREAN_SUBTRACT  24 
#define TYPE_OPEN_BRACKETS         25 
#define TYPE_CLOSE_BRACKETS        26 
#define TYPE_OPEN_BRACES           27 
#define TYPE_CLOSE_BRACES          28 
/*:100*//*105:*/
#line 2494 "weaver-interface-metafont.tex"

#define TYPE_MULTIPLICATION        29 
#define TYPE_DIVISION              30 
/*:105*//*109:*/
#line 2634 "weaver-interface-metafont.tex"

#define TYPE_LENGTH         31 
#define TYPE_SQRT           32 
#define TYPE_SIND           33 
#define TYPE_COSD           34 
#define TYPE_LOG            35 
#define TYPE_EXP            36 
#define TYPE_FLOOR          37 
#define TYPE_UNIFORMDEVIATE 38 
/*:109*//*127:*/
#line 3054 "weaver-interface-metafont.tex"

#define TYPE_NORMALDEVIATE  39 
/*:127*//*143:*/
#line 3438 "weaver-interface-metafont.tex"

#define TYPE_ROTATED  40 
#define TYPE_SCALED   41 
#define TYPE_SHIFTED  42 
#define TYPE_SLANTED  43 
#define TYPE_XSCALED  44 
#define TYPE_YSCALED  45 
#define TYPE_ZSCALED  46 
/*:143*//*163:*/
#line 4133 "weaver-interface-metafont.tex"

#define TYPE_XPART  47 
#define TYPE_YPART  48 
#define TYPE_ANGLE  49 
/*:163*//*174:*/
#line 4373 "weaver-interface-metafont.tex"

#define TYPE_CYCLE          50 
#define TYPE_AMPERSAND      51 
#define TYPE_JOIN           52 
#define TYPE_TENSION        53 
#define TYPE_AND            54 
#define TYPE_ATLEAST        55 
#define TYPE_CONTROLS       56 
#define TYPE_CURL           57 
/*:174*/
#line 358 "weaver-interface-metafont.tex"


struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:12*//*60:*/
#line 1413 "weaver-interface-metafont.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:60*//*61:*/
#line 1433 "weaver-interface-metafont.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:61*//*77:*/
#line 1770 "weaver-interface-metafont.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:77*//*85:*/
#line 1902 "weaver-interface-metafont.tex"

struct pair_variable{
int type;
int nesting_level;
void*next;
float x,y;
};
/*:85*//*87:*/
#line 1964 "weaver-interface-metafont.tex"

struct path_points{
float x,y;
float u_x,u_y,v_x,v_y;
void*subpath;
};
struct path_variable{
int type;
int nesting_level;
void*next;
bool cyclic;
int length;
struct path_points*points;
};
/*:87*/
#line 219 "weaver-interface-metafont.tex"

/*7:*/
#line 238 "weaver-interface-metafont.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:7*//*35:*/
#line 852 "weaver-interface-metafont.tex"

static char*list_of_keywords[]= {
/*40:*/
#line 982 "weaver-interface-metafont.tex"

"end","dump",
/*:40*//*51:*/
#line 1217 "weaver-interface-metafont.tex"

"begingroup","endgroup",
/*:51*//*59:*/
#line 1388 "weaver-interface-metafont.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:59*//*94:*/
#line 2117 "weaver-interface-metafont.tex"

"=",":=",
/*:94*//*101:*/
#line 2327 "weaver-interface-metafont.tex"

"+","-","++","+-+","[","]","{","}",
/*:101*//*106:*/
#line 2501 "weaver-interface-metafont.tex"

"*","/",
/*:106*//*110:*/
#line 2647 "weaver-interface-metafont.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:110*//*128:*/
#line 3060 "weaver-interface-metafont.tex"

"normaldeviate",
/*:128*//*144:*/
#line 3450 "weaver-interface-metafont.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:144*//*164:*/
#line 4143 "weaver-interface-metafont.tex"

"xpart","ypart","angle",
/*:164*//*175:*/
#line 4389 "weaver-interface-metafont.tex"

"cycle","&","..","tension","and","atleast","controls","curl",
/*:175*/
#line 854 "weaver-interface-metafont.tex"

NULL};
/*:35*/
#line 220 "weaver-interface-metafont.tex"

/*45:*/
#line 1061 "weaver-interface-metafont.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:45*//*48:*/
#line 1133 "weaver-interface-metafont.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:48*//*52:*/
#line 1226 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:52*//*71:*/
#line 1620 "weaver-interface-metafont.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:71*//*73:*/
#line 1671 "weaver-interface-metafont.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:73*//*75:*/
#line 1731 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:75*//*91:*/
#line 2051 "weaver-interface-metafont.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path);
/*:91*//*98:*/
#line 2248 "weaver-interface-metafont.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source);

/*:98*//*102:*/
#line 2337 "weaver-interface-metafont.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:102*//*107:*/
#line 2512 "weaver-interface-metafont.tex"

bool eval_numeric_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:107*//*111:*/
#line 2655 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:111*//*115:*/
#line 2758 "weaver-interface-metafont.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:115*//*129:*/
#line 3071 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:129*//*139:*/
#line 3309 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source);
/*:139*//*141:*/
#line 3346 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result);
/*:141*//*145:*/
#line 3459 "weaver-interface-metafont.tex"

bool eval_pair_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:145*//*156:*/
#line 3800 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:156*//*170:*/
#line 4259 "weaver-interface-metafont.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source);
/*:170*//*172:*/
#line 4313 "weaver-interface-metafont.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source);
/*:172*//*176:*/
#line 4404 "weaver-interface-metafont.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:176*//*178:*/
#line 4457 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:178*/
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
#line 456 "weaver-interface-metafont.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:16*/
#line 421 "weaver-interface-metafont.tex"

/*18:*/
#line 477 "weaver-interface-metafont.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:18*/
#line 422 "weaver-interface-metafont.tex"

/*19:*/
#line 494 "weaver-interface-metafont.tex"

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
#line 423 "weaver-interface-metafont.tex"

/*20:*/
#line 542 "weaver-interface-metafont.tex"

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
#line 424 "weaver-interface-metafont.tex"

/*21:*/
#line 587 "weaver-interface-metafont.tex"

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
#line 425 "weaver-interface-metafont.tex"

/*22:*/
#line 622 "weaver-interface-metafont.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*23:*/
#line 655 "weaver-interface-metafont.tex"

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
#line 628 "weaver-interface-metafont.tex"

/*24:*/
#line 672 "weaver-interface-metafont.tex"

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
#line 629 "weaver-interface-metafont.tex"

/*25:*/
#line 688 "weaver-interface-metafont.tex"

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
#line 630 "weaver-interface-metafont.tex"

/*26:*/
#line 704 "weaver-interface-metafont.tex"

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
#line 631 "weaver-interface-metafont.tex"

/*27:*/
#line 720 "weaver-interface-metafont.tex"

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
#line 632 "weaver-interface-metafont.tex"

/*28:*/
#line 736 "weaver-interface-metafont.tex"

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
#line 633 "weaver-interface-metafont.tex"

/*29:*/
#line 752 "weaver-interface-metafont.tex"

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
#line 634 "weaver-interface-metafont.tex"

/*30:*/
#line 768 "weaver-interface-metafont.tex"

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
#line 635 "weaver-interface-metafont.tex"

/*31:*/
#line 784 "weaver-interface-metafont.tex"

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
#line 636 "weaver-interface-metafont.tex"

/*32:*/
#line 800 "weaver-interface-metafont.tex"

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
#line 637 "weaver-interface-metafont.tex"

/*33:*/
#line 816 "weaver-interface-metafont.tex"

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
#line 638 "weaver-interface-metafont.tex"

/*34:*/
#line 832 "weaver-interface-metafont.tex"

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
#line 639 "weaver-interface-metafont.tex"


/*36:*/
#line 865 "weaver-interface-metafont.tex"

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
#line 992 "weaver-interface-metafont.tex"

if(token_type==TYPE_DUMP)
token_type= TYPE_END;
/*:41*//*95:*/
#line 2126 "weaver-interface-metafont.tex"

else if(token_type==TYPE_ASSIGNMENT2)
token_type= TYPE_ASSIGNMENT;
/*:95*/
#line 878 "weaver-interface-metafont.tex"

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
#line 641 "weaver-interface-metafont.tex"

/*38:*/
#line 909 "weaver-interface-metafont.tex"

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
#line 1877 "weaver-interface-metafont.tex"

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
#line 922 "weaver-interface-metafont.tex"

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
#line 642 "weaver-interface-metafont.tex"

}
/*:22*/
#line 426 "weaver-interface-metafont.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
fclose(fp);
return first_token;
}
/*:14*//*42:*/
#line 1006 "weaver-interface-metafont.tex"

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
#line 1077 "weaver-interface-metafont.tex"

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
#line 1455 "weaver-interface-metafont.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:63*//*81:*/
#line 1827 "weaver-interface-metafont.tex"

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
/*:81*//*134:*/
#line 3195 "weaver-interface-metafont.tex"

mf->have_stored_normaldeviate= false;
/*:134*/
#line 1088 "weaver-interface-metafont.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*56:*/
#line 1282 "weaver-interface-metafont.tex"

cx->nesting_level= 0;
/*:56*//*67:*/
#line 1516 "weaver-interface-metafont.tex"

cx->variables= NULL;
/*:67*/
#line 1094 "weaver-interface-metafont.tex"

return cx;
}
/*:46*//*47:*/
#line 1103 "weaver-interface-metafont.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*64:*/
#line 1467 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*89:*/
#line 2009 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL){
int i;
for(i= 0;i<path->length;i++)
if(path->points[i].subpath!=NULL)
path_recursive_free(mf->free,(struct path_variable*)
path->points[i].subpath);
mf->free(path->points);
}
}
/*:89*/
#line 1473 "weaver-interface-metafont.tex"

mf->free(v);
v= next;
}
}
/*:64*//*65:*/
#line 1485 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)(named->var);
next= (struct named_variable*)(named->next);
mf->free(named->name);
/*89:*/
#line 2009 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL){
int i;
for(i= 0;i<path->length;i++)
if(path->points[i].subpath!=NULL)
path_recursive_free(mf->free,(struct path_variable*)
path->points[i].subpath);
mf->free(path->points);
}
}
/*:89*/
#line 1494 "weaver-interface-metafont.tex"

mf->free(v);
mf->free(named);
named= next;
}
}
/*:65*//*83:*/
#line 1866 "weaver-interface-metafont.tex"

mf->free(mf->internal_numeric_variables);
/*:83*/
#line 1107 "weaver-interface-metafont.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*68:*/
#line 1524 "weaver-interface-metafont.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*90:*/
#line 2029 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL){
int i;
for(i= 0;i<path->length;i++)
if(path->points[i].subpath!=NULL)
path_recursive_free(temporary_free,(struct path_variable*)
path->points[i].subpath);
temporary_free(path->points);
}
}
/*:90*/
#line 1530 "weaver-interface-metafont.tex"

temporary_free(v);
v= next;
}
}
/*:68*/
#line 1113 "weaver-interface-metafont.tex"

temporary_free(cx);
}
}
/*:47*//*49:*/
#line 1146 "weaver-interface-metafont.tex"

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
#line 1232 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*54:*/
#line 1259 "weaver-interface-metafont.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:54*/
#line 1235 "weaver-interface-metafont.tex"

/*57:*/
#line 1315 "weaver-interface-metafont.tex"

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
#line 1236 "weaver-interface-metafont.tex"

/*69:*/
#line 1541 "weaver-interface-metafont.tex"

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
#line 1591 "weaver-interface-metafont.tex"

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
#line 1558 "weaver-interface-metafont.tex"

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
#line 1237 "weaver-interface-metafont.tex"

/*96:*/
#line 2150 "weaver-interface-metafont.tex"

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
/*97:*/
#line 2224 "weaver-interface-metafont.tex"

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
/*:97*/
#line 2210 "weaver-interface-metafont.tex"

/*138:*/
#line 3288 "weaver-interface-metafont.tex"

else if(type==TYPE_T_PAIR){
int i;
struct pair_variable result;
if(!eval_pair_expression(mf,cx,begin_expression,
(struct generic_token*)*end_token_list,
&result))
return false;
var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
assign_pair_variable((struct pair_variable*)var->var,&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:138*/
#line 2211 "weaver-interface-metafont.tex"

/*169:*/
#line 4235 "weaver-interface-metafont.tex"

else if(type==TYPE_T_PATH){
int i;
struct path_variable result;




var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
assign_path_variable(mf,(struct path_variable*)var->var,
&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
if(temporary_free!=NULL)
temporary_free(result.points);
}
/*:169*/
#line 2212 "weaver-interface-metafont.tex"

return true;
}
/*:96*/
#line 1238 "weaver-interface-metafont.tex"




#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:53*//*72:*/
#line 1633 "weaver-interface-metafont.tex"

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
#line 1787 "weaver-interface-metafont.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:78*//*88:*/
#line 1998 "weaver-interface-metafont.tex"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
}
/*:88*/
#line 1653 "weaver-interface-metafont.tex"

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
#line 1682 "weaver-interface-metafont.tex"

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
#line 1744 "weaver-interface-metafont.tex"

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
/*:76*//*92:*/
#line 2060 "weaver-interface-metafont.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path){
if(free_func!=NULL){
int i;
for(i= 0;i<path->length;i++){
if(path->points[i].subpath!=NULL)
path_recursive_free(free_func,(struct path_variable*)
path->points[i].subpath);
}
free_func(path->points);
free_func(path);
}
}
/*:92*//*99:*/
#line 2258 "weaver-interface-metafont.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source){
target->value= source->value;
}
/*:99*//*104:*/
#line 2409 "weaver-interface-metafont.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secundary,
*last_sum= NULL,*p,*prev= NULL;
int nesting_parenthesis= 0,nesting_brackets= 0,nesting_braces= 0;
struct numeric_variable a,b;
p= begin_expression;
do{
if(p->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
else if(p->type==TYPE_OPEN_BRACKETS)
nesting_brackets++;
else if(p->type==TYPE_CLOSE_BRACKETS)
nesting_brackets--;
else if(p->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(p->type==TYPE_CLOSE_BRACES)
nesting_braces--;
else if(nesting_parenthesis==0&&nesting_brackets==0&&
nesting_braces==0&&
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
last_sum->line);
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
/*:104*//*108:*/
#line 2535 "weaver-interface-metafont.tex"

bool eval_numeric_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_secundary= NULL,*begin_primary,
*last_mul= NULL,*p,*prev= NULL,
*prev_prev= NULL,*last_fraction= NULL;
int nesting_parenthesis= 0,nesting_brackets= 0,nesting_braces= 0;
struct numeric_variable a,b;
b.value= 0.0;
p= begin_expression;
do{
if(p->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
else if(p->type==TYPE_OPEN_BRACKETS)
nesting_brackets++;
else if(p->type==TYPE_CLOSE_BRACKETS)
nesting_brackets--;
else if(p->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(p->type==TYPE_CLOSE_BRACES)
nesting_braces--;
else if(nesting_parenthesis==0&&nesting_brackets==0&&
nesting_braces==0&&
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
/*:108*//*112:*/
#line 2667 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*113:*/
#line 2693 "weaver-interface-metafont.tex"

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
/*:113*/
#line 2672 "weaver-interface-metafont.tex"

/*114:*/
#line 2717 "weaver-interface-metafont.tex"

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
/*165:*/
#line 4154 "weaver-interface-metafont.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)hypot(p.x*p.x,p.y*p.y);
return true;
}
/*:165*/
#line 2734 "weaver-interface-metafont.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:114*/
#line 2673 "weaver-interface-metafont.tex"

/*117:*/
#line 2798 "weaver-interface-metafont.tex"

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
/*:117*//*118:*/
#line 2826 "weaver-interface-metafont.tex"

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
/*:118*//*119:*/
#line 2845 "weaver-interface-metafont.tex"

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
/*:119*//*120:*/
#line 2864 "weaver-interface-metafont.tex"

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
/*:120*//*121:*/
#line 2890 "weaver-interface-metafont.tex"

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
/*:121*//*122:*/
#line 2908 "weaver-interface-metafont.tex"

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
/*:122*//*123:*/
#line 2939 "weaver-interface-metafont.tex"

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
/*:123*//*124:*/
#line 2962 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:124*//*125:*/
#line 2979 "weaver-interface-metafont.tex"

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
/*:125*/
#line 2674 "weaver-interface-metafont.tex"

/*166:*/
#line 4171 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_XPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.x;
return true;
}
/*:166*//*167:*/
#line 4188 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_YPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.y;
return true;
}
/*:167*//*168:*/
#line 4207 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_ANGLE){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
if(p.x==0.0&&p.y==0.0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Measuring the angle "
"of (0,0).\n ",mf->file,
begin_expression->line);
#endif
return false;
}
result->value= (float)asin(p.y/(hypot(p.x*p.x,p.y*p.y)));
result->value*= 57.2958;
return true;
}
/*:168*/
#line 2675 "weaver-interface-metafont.tex"

/*126:*/
#line 3005 "weaver-interface-metafont.tex"

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
/*:126*/
#line 2676 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:112*//*116:*/
#line 2766 "weaver-interface-metafont.tex"

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
/*:116*//*130:*/
#line 3084 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*131:*/
#line 3106 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:131*/
#line 3090 "weaver-interface-metafont.tex"

/*132:*/
#line 3119 "weaver-interface-metafont.tex"

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
/*:132*/
#line 3091 "weaver-interface-metafont.tex"

/*135:*/
#line 3205 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NORMALDEVIATE){
if(mf->have_stored_normaldeviate){
mf->have_stored_normaldeviate= false;
result->value= mf->normaldeviate;
return true;
}
else{
uint64_t random_bits;
float u,v,s;
random_bits= random_func();
do{
u= (float)ldexp((double)(random_bits>>1),-63)*
((random_bits%2)?(-1.0):(+1.0));
v= (float)ldexp((double)(random_bits>>1),-63)*
((random_bits%2)?(-1.0):(+1.0));
s= u*u+v*v;
}while(s>=1.0||s==0.0);
u*= (float)sqrt((-2.0*log((double)s))/s);
v*= (float)sqrt((-2.0*log((double)s))/s);
mf->have_stored_normaldeviate= true;
mf->normaldeviate= u;
result->value= v;
return true;
}
}
/*:135*/
#line 3092 "weaver-interface-metafont.tex"

}
else{
/*136:*/
#line 3240 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
bool ret;
struct generic_token*p= begin_expression;
while(p->next!=end_expression)
p= (struct generic_token*)p->next;
if(p==begin_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Empty parenthesis.",
mf->file,begin_expression->line);
#endif
return false;
}
ret= eval_numeric_expression(mf,cx,(struct generic_token*)
begin_expression->next,p,
result);
if(!ret)
return false;
return true;
}
/*:136*/
#line 3095 "weaver-interface-metafont.tex"

/*137:*/
#line 3269 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC&&
end_expression->type==TYPE_NUMERIC&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION){
result->value= ((struct numeric_token*)begin_expression)->value/
((struct numeric_token*)end_expression)->value;
return true;
}
/*:137*/
#line 3096 "weaver-interface-metafont.tex"

}
return false;
}
/*:130*//*140:*/
#line 3318 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source){
target->x= source->x;
target->y= source->y;
}
/*:140*//*142:*/
#line 3359 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secundary,
*last_sum= NULL,*p,*prev= NULL;
int nesting_parenthesis= 0,nesting_brackets= 0,nesting_braces= 0;
struct pair_variable a,b;
p= begin_expression;
do{
if(p->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
else if(p->type==TYPE_OPEN_BRACKETS)
nesting_brackets++;
else if(p->type==TYPE_CLOSE_BRACKETS)
nesting_brackets--;
else if(p->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(p->type==TYPE_CLOSE_BRACES)
nesting_braces--;
else if(nesting_parenthesis==0&&nesting_brackets==0&&
nesting_braces==0&&IS_VALID_SUM_OR_SUB(prev,p)){
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
eval_pair_expression(mf,cx,begin_expression,end_tertiary,&a);
eval_pair_secundary(mf,cx,begin_secundary,end_token_list,&b);
if(last_sum->type==TYPE_SUM){
result->x= a.x+b.x;
result->y= a.y+b.y;
}
else if(last_sum->type==TYPE_SUBTRACT){
result->x= a.x-b.x;
result->y= a.y-b.y;
}
return true;
}
else
return eval_pair_secundary(mf,cx,begin_expression,
end_token_list,result);
}
/*:142*//*146:*/
#line 3479 "weaver-interface-metafont.tex"

bool eval_pair_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
struct generic_token*end_secundary= NULL,*begin_primary,
*last_mul= NULL,*p,*prev= NULL,
*prev_prev= NULL,*last_fraction= NULL;
int nesting_parenthesis= 0,nesting_brackets= 0,nesting_braces= 0;
p= begin_expression;
do{
if(p->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
else if(p->type==TYPE_OPEN_BRACKETS)
nesting_brackets++;
else if(p->type==TYPE_CLOSE_BRACKETS)
nesting_brackets--;
else if(p->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(p->type==TYPE_CLOSE_BRACES)
nesting_braces--;
else if(nesting_parenthesis==0&&nesting_brackets==0&&
nesting_braces==0&&
(p->type==TYPE_MULTIPLICATION||
p->type==TYPE_DIVISION||p->type==TYPE_ROTATED||
p->type==TYPE_SCALED||p->type==TYPE_SHIFTED||
p->type==TYPE_SLANTED||p->type==TYPE_XSCALED||
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED)){
if(p->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
p!=end_expression&&
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
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(end_secundary!=NULL){
bool ret;
begin_primary= (struct generic_token*)(last_mul->next);
/*147:*/
#line 3559 "weaver-interface-metafont.tex"

if(last_mul->type==TYPE_MULTIPLICATION){
if(get_primary_expression_type(mf,cx,begin_primary,end_expression)==
TYPE_T_PAIR){
struct numeric_variable a;
struct pair_variable b;
ret= eval_numeric_secundary(mf,cx,begin_expression,end_secundary,
&a);
if(!ret)
return false;
ret= eval_pair_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= b.x*a.value;
result->y= b.y*a.value;
return true;
}
else{
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,
&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x*b.value;
result->y= a.y*b.value;
return true;
}
}
/*:147*/
#line 3529 "weaver-interface-metafont.tex"

/*148:*/
#line 3598 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_DIVISION){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
if(b.value==0.0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Division by zero.",
mf->file,last_mul->line);
#endif
return false;
}
result->x= a.x/b.value;
result->y= a.y/b.value;
return true;
}
/*:148*/
#line 3530 "weaver-interface-metafont.tex"

/*149:*/
#line 3626 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_ROTATED){
struct pair_variable a;
struct numeric_variable b;
double sin_theta,cos_theta,theta;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
theta= 0.0174533*b.value;
sin_theta= sin(theta);
cos_theta= cos(theta);
result->x= a.x*cos_theta-a.y*sin_theta;
result->y= a.x*sin_theta+a.y*cos_theta;
return true;
}
/*:149*/
#line 3531 "weaver-interface-metafont.tex"

/*150:*/
#line 3650 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_SCALED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x*b.value;
result->y= a.y*b.value;
return true;
}
/*:150*/
#line 3532 "weaver-interface-metafont.tex"

/*151:*/
#line 3671 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_SHIFTED){
struct pair_variable a,b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_pair_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x+b.x;
result->y= a.y+b.y;
return true;
}
/*:151*/
#line 3533 "weaver-interface-metafont.tex"

/*152:*/
#line 3692 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_SLANTED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x+b.value*a.y;
result->y= a.y;
return true;
}
/*:152*/
#line 3534 "weaver-interface-metafont.tex"

/*153:*/
#line 3713 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_XSCALED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x*b.value;
result->y= a.y;
return true;
}
/*:153*/
#line 3535 "weaver-interface-metafont.tex"

/*154:*/
#line 3734 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_YSCALED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x;
result->y= a.y*b.value;
return true;
}
/*:154*/
#line 3536 "weaver-interface-metafont.tex"

/*155:*/
#line 3759 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_ZSCALED){
struct pair_variable a,b;
ret= eval_pair_secundary(mf,cx,begin_expression,end_secundary,&a);
if(!ret)
return false;
ret= eval_pair_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x*b.x-a.y*b.y;
result->y= a.x*b.y+b.x*a.y;
return true;
}
/*:155*/
#line 3537 "weaver-interface-metafont.tex"

}
else
return eval_pair_primary(mf,cx,begin_expression,
end_expression,result);
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:146*//*157:*/
#line 3813 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
if(begin_expression==end_expression){
/*158:*/
#line 3841 "weaver-interface-metafont.tex"

struct symbolic_token*tok= (struct symbolic_token*)begin_expression;
struct pair_variable*var;
if(tok->type!=TYPE_SYMBOLIC){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable token "
"in pair expression.",mf->file,begin_expression->line);
#endif
return false;
}
var= (struct pair_variable*)tok->var;
if(var==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Undeclared variable "
"'%s'.\n",mf->file,begin_expression->line,tok->value);
#endif
return false;
}
if(var->type!=TYPE_T_PAIR){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Non-pair variable "
"'%s' in pair expression.\n",mf->file,
begin_expression->line,tok->value);
#endif
return false;
}
result->x= var->x;
result->y= var->y;
return true;
/*:158*/
#line 3819 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*159:*/
#line 3881 "weaver-interface-metafont.tex"

struct generic_token*begin_a,*end_a,*begin_b,*end_b,*comma;
begin_a= (struct generic_token*)begin_expression->next;
end_a= begin_a;
int nesting_parenthesis= 0,nesting_brackets= 0,nesting_braces= 0;
bool literal= true;
while(end_a!=NULL){
if(end_a->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(end_a->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
if(end_a->type==TYPE_OPEN_BRACKETS)
nesting_brackets++;
else if(end_a->type==TYPE_CLOSE_BRACKETS)
nesting_brackets--;
if(end_a->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(end_a->type==TYPE_CLOSE_BRACES)
nesting_braces--;
if(nesting_parenthesis<0||nesting_brackets<0||
nesting_braces<0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n ",mf->file,begin_expression->line);
#endif
return false;
}
if(nesting_parenthesis==0&&nesting_brackets==0&&
nesting_braces==0&&
((struct generic_token*)end_a->next)->type==TYPE_COMMA)
break;
if(end_a->next!=end_expression)
end_a= (struct generic_token*)end_a->next;
else{
literal= false;
break;
}
}
if(literal){
struct numeric_variable a,b;
bool ret;
comma= (struct generic_token*)end_a->next;
begin_b= (struct generic_token*)comma->next;
if(begin_b==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n ",mf->file,begin_expression->line);
#endif
return false;
}
end_b= begin_b;
while(end_b->next!=end_expression)
end_b= (struct generic_token*)end_b->next;
ret= eval_numeric_expression(mf,cx,begin_a,end_a,&a);
if(!ret)
return false;
ret= eval_numeric_expression(mf,cx,begin_b,end_b,&b);
if(!ret)
return false;
result->x= a.value;
result->y= b.value;
return true;
}
/*:159*/
#line 3823 "weaver-interface-metafont.tex"

/*160:*/
#line 3954 "weaver-interface-metafont.tex"

else{
return eval_pair_expression(mf,cx,begin_a,end_a,result);
}
/*:160*/
#line 3824 "weaver-interface-metafont.tex"

}
/*161:*/
#line 3966 "weaver-interface-metafont.tex"

if(end_expression->type==TYPE_CLOSE_BRACKETS){
struct generic_token*begin_a,*end_a,*begin_b,*end_b,*begin_c,
*end_c;
struct numeric_variable a;
struct pair_variable b,c;
int nesting_parenthesis= 0,nesting_brackets= 0,nesting_braces= 0;
begin_a= begin_expression;
end_a= begin_a;
while(end_a!=NULL){
if(end_a->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(end_a->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
else if(end_a->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(end_a->type==TYPE_CLOSE_BRACES)
nesting_braces--;
if(nesting_parenthesis==0&&nesting_braces==0&&
((struct generic_token*)end_a->next)->type==
TYPE_OPEN_BRACKETS)
break;
if(end_a->next!=end_expression)
end_a= (struct generic_token*)end_a->next;
else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n ",mf->file,begin_expression->line);
#endif
return false;
}
}
begin_b= (struct generic_token*)end_a->next;
begin_b= (struct generic_token*)begin_b->next;
if(begin_b==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n ",mf->file,begin_expression->line);
#endif
return false;
}
end_b= begin_b;
while(end_b!=end_expression){
if(end_b->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(end_b->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
else if(end_b->type==TYPE_OPEN_BRACKETS)
nesting_brackets++;
else if(end_b->type==TYPE_CLOSE_BRACKETS)
nesting_brackets--;
else if(end_b->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(end_b->type==TYPE_CLOSE_BRACES)
nesting_braces--;
if(nesting_parenthesis==0&&nesting_brackets==0&&
nesting_braces==0&&
((struct generic_token*)end_b->next)->type==TYPE_COMMA)
break;
if(end_b->next!=end_expression)
end_b= (struct generic_token*)end_b->next;
else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n ",mf->file,begin_expression->line);
#endif
return false;
}
}
begin_c= (struct generic_token*)end_b->next;
begin_c= (struct generic_token*)begin_c->next;
if(begin_c==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n ",mf->file,begin_expression->line);
#endif
return false;
}
end_c= begin_c;
while(end_c->next!=end_expression)
end_c= (struct generic_token*)end_c->next;
if(!eval_numeric_atom(mf,cx,begin_a,end_a,&a))
return false;
if(!eval_pair_expression(mf,cx,begin_b,end_b,&b))
return false;
if(!eval_pair_expression(mf,cx,begin_c,end_c,&c))
return false;
result->x= (b.x+c.x)*a.value;
result->y= (b.y+c.y)*a.value;
return true;
}
/*:161*/
#line 3826 "weaver-interface-metafont.tex"

/*162:*/
#line 4068 "weaver-interface-metafont.tex"

else{
bool ret;
if(begin_expression->type==TYPE_SUM)
return eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
else if(begin_expression->type==TYPE_SUBTRACT){
ret= eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
result->x= -(result->x);
result->y= -(result->y);
return true;
}
else if(begin_expression->type==TYPE_NUMERIC){
struct generic_token*tok;
float value= ((struct numeric_token*)begin_expression)->value;
tok= (struct generic_token*)begin_expression->next;
if(tok->type==TYPE_DIVISION){
tok= (struct generic_token*)begin_expression->next;
if(tok==end_expression||tok->next==end_expression||
tok->type!=TYPE_NUMERIC){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n ",mf->file,begin_expression->line);
#endif
return false;
}
value/= ((struct numeric_token*)tok)->value;
tok= (struct generic_token*)tok->next;
}
ret= eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
result->x*= value;
result->y*= value;
return true;
}
}
/*:162*/
#line 3827 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:157*//*171:*/
#line 4269 "weaver-interface-metafont.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source){
int i;
void*(*alloc)(size_t);
void(*disalloc)(void*);
if(target->nesting_level==0){
disalloc= mf->free;
alloc= mf->alloc;
}
else{
disalloc= temporary_free;
alloc= temporary_alloc;
}
if(target->length!=-1&&disalloc!=NULL){
for(i= 0;i<target->length;i++)
if(target->points[i].subpath!=NULL)
path_recursive_free(disalloc,(struct path_variable*)
target->points[i].subpath);
}
target->cyclic= source->cyclic;
target->length= source->length;
target->points= (struct path_points*)
alloc(sizeof(struct path_points)*
target->length);
for(i= 0;i<target->length;i++){
memcpy(&(target->points[i]),&(source->points[i]),
sizeof(struct path_points));
if(source->points[i].subpath!=NULL)
recursive_copy_points(alloc,(struct path_variable**)
&(target->points[i].subpath),
source->points[i].subpath);
}
}
/*:171*//*173:*/
#line 4321 "weaver-interface-metafont.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source){
int i;
*target= (struct path_variable*)alloc(sizeof(struct path_variable));
(*target)->cyclic= source->cyclic;
(*target)->length= source->length;
(*target)->points= (struct path_points*)
alloc(sizeof(struct path_points)*
(*target)->length);
for(i= 0;i<(*target)->length;i++){
memcpy(&((*target)->points[i]),&(source->points[i]),
sizeof(struct path_points));
if(source->points[i].subpath!=NULL)
recursive_copy_points(alloc,(struct path_variable**)
&((*target)->points[i].subpath),
source->points[i].subpath);
}
}
/*:173*//*177:*/
#line 4415 "weaver-interface-metafont.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end){
int count= 0;
int nesting_parenthesis= 0,nesting_brackets= 0,nesting_braces= 0;
struct generic_token*p= begin;
while(p!=NULL){
if(p->type==TYPE_OPEN_PARENTHESIS)
nesting_parenthesis++;
else if(p->type==TYPE_CLOSE_PARENTHESIS)
nesting_parenthesis--;
else if(p->type==TYPE_OPEN_BRACKETS)
nesting_brackets++;
else if(p->type==TYPE_CLOSE_BRACKETS)
nesting_brackets--;
else if(p->type==TYPE_OPEN_BRACES)
nesting_braces++;
else if(p->type==TYPE_CLOSE_BRACES)
nesting_braces--;
else if(nesting_parenthesis==0&&nesting_brackets==0&&
nesting_braces==0){
if(p->type==TYPE_AMPERSAND)
count++;
else if(p->type==TYPE_JOIN){
struct generic_token*next= (struct generic_token*)p->next;
if(p==end||(next->type!=TYPE_TENSION&&
next->type!=TYPE_CONTROLS))
count++;
}
}
if(p!=end)
p= (struct generic_token*)p->next;
else
p= NULL;
}
return count;
}
/*:177*/
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
