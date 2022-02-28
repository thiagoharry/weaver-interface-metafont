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
#line 2358 "weaver-interface-metafont.tex"

#define DECLARE_NESTING_CONTROL() int nesting_parenthesis =  0, \
                                      nesting_brackets =  0, \
                                      nesting_braces =  0;
#define COUNT_NESTING(p) if(p -> type == TYPE_OPEN_PARENTHESIS)           \
                               nesting_parenthesis ++;                    \
                             else if(p -> type == TYPE_CLOSE_PARENTHESIS) \
                               nesting_parenthesis --;                    \
                             else if(p -> type == TYPE_OPEN_BRACKETS)     \
                               nesting_brackets ++;                       \
                             else if(p -> type == TYPE_CLOSE_BRACKETS)    \
                               nesting_brackets --;                       \
                             else if(p -> type == TYPE_OPEN_BRACES)       \
                               nesting_braces ++;                         \
                             else if(p -> type == TYPE_CLOSE_BRACES)      \
                               nesting_braces --;
#define IS_NOT_NESTED() (nesting_parenthesis == 0 && nesting_brackets == 0 && \
                         nesting_braces == 0)
/*:103*//*104:*/
#line 2403 "weaver-interface-metafont.tex"

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
/*:104*/
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
/*:100*//*106:*/
#line 2510 "weaver-interface-metafont.tex"

#define TYPE_MULTIPLICATION        29 
#define TYPE_DIVISION              30 
/*:106*//*110:*/
#line 2637 "weaver-interface-metafont.tex"

#define TYPE_LENGTH         31 
#define TYPE_SQRT           32 
#define TYPE_SIND           33 
#define TYPE_COSD           34 
#define TYPE_LOG            35 
#define TYPE_EXP            36 
#define TYPE_FLOOR          37 
#define TYPE_UNIFORMDEVIATE 38 
/*:110*//*128:*/
#line 3057 "weaver-interface-metafont.tex"

#define TYPE_NORMALDEVIATE  39 
/*:128*//*144:*/
#line 3429 "weaver-interface-metafont.tex"

#define TYPE_ROTATED  40 
#define TYPE_SCALED   41 
#define TYPE_SHIFTED  42 
#define TYPE_SLANTED  43 
#define TYPE_XSCALED  44 
#define TYPE_YSCALED  45 
#define TYPE_ZSCALED  46 
/*:144*//*164:*/
#line 4072 "weaver-interface-metafont.tex"

#define TYPE_XPART  47 
#define TYPE_YPART  48 
#define TYPE_ANGLE  49 
/*:164*//*175:*/
#line 4316 "weaver-interface-metafont.tex"

#define TYPE_CYCLE          50 
#define TYPE_AMPERSAND      51 
#define TYPE_JOIN           52 
#define TYPE_TENSION        53 
#define TYPE_AND            54 
#define TYPE_ATLEAST        55 
#define TYPE_CONTROLS       56 
#define TYPE_CURL           57 
/*:175*/
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
/*:101*//*107:*/
#line 2517 "weaver-interface-metafont.tex"

"*","/",
/*:107*//*111:*/
#line 2650 "weaver-interface-metafont.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:111*//*129:*/
#line 3063 "weaver-interface-metafont.tex"

"normaldeviate",
/*:129*//*145:*/
#line 3441 "weaver-interface-metafont.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:145*//*165:*/
#line 4082 "weaver-interface-metafont.tex"

"xpart","ypart","angle",
/*:165*//*176:*/
#line 4332 "weaver-interface-metafont.tex"

"cycle","&","..","tension","and","atleast","controls","curl",
/*:176*/
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
/*:102*//*108:*/
#line 2528 "weaver-interface-metafont.tex"

bool eval_numeric_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:108*//*112:*/
#line 2658 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:112*//*116:*/
#line 2761 "weaver-interface-metafont.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:116*//*130:*/
#line 3074 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:130*//*140:*/
#line 3312 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source);
/*:140*//*142:*/
#line 3349 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result);
/*:142*//*146:*/
#line 3450 "weaver-interface-metafont.tex"

bool eval_pair_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:146*//*157:*/
#line 3778 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:157*//*171:*/
#line 4202 "weaver-interface-metafont.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source);
/*:171*//*173:*/
#line 4256 "weaver-interface-metafont.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source);
/*:173*//*177:*/
#line 4347 "weaver-interface-metafont.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:177*//*179:*/
#line 4388 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:179*//*194:*/
#line 4814 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y,float*curl);
/*:194*/
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
/*:81*//*135:*/
#line 3198 "weaver-interface-metafont.tex"

mf->have_stored_normaldeviate= false;
/*:135*/
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

/*139:*/
#line 3291 "weaver-interface-metafont.tex"

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
/*:139*/
#line 2211 "weaver-interface-metafont.tex"

/*170:*/
#line 4174 "weaver-interface-metafont.tex"

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
if(temporary_free!=NULL){
for(i= 0;i<result.length;i++)
if(result.points[i].subpath!=NULL)
path_recursive_free(temporary_free,result.points[i].subpath);
temporary_free(result.points);
}
}
/*:170*/
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
/*:99*//*105:*/
#line 2438 "weaver-interface-metafont.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secundary,
*last_sum= NULL,*p,*prev= NULL;
DECLARE_NESTING_CONTROL();
struct numeric_variable a,b;
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_PYTHAGOREAN_SUM||
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
/*:105*//*109:*/
#line 2551 "weaver-interface-metafont.tex"

bool eval_numeric_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_secundary= NULL,*begin_primary,
*last_mul= NULL,*p,*prev= NULL,
*prev_prev= NULL,*last_fraction= NULL;
DECLARE_NESTING_CONTROL();
struct numeric_variable a,b;
b.value= 0.0;
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_MULTIPLICATION||
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
/*:109*//*113:*/
#line 2670 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*114:*/
#line 2696 "weaver-interface-metafont.tex"

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
/*:114*/
#line 2675 "weaver-interface-metafont.tex"

/*115:*/
#line 2720 "weaver-interface-metafont.tex"

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
/*166:*/
#line 4093 "weaver-interface-metafont.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)hypot(p.x*p.x,p.y*p.y);
return true;
}
/*:166*/
#line 2737 "weaver-interface-metafont.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:115*/
#line 2676 "weaver-interface-metafont.tex"

/*118:*/
#line 2801 "weaver-interface-metafont.tex"

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
/*:118*//*119:*/
#line 2829 "weaver-interface-metafont.tex"

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
/*:119*//*120:*/
#line 2848 "weaver-interface-metafont.tex"

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
/*:120*//*121:*/
#line 2867 "weaver-interface-metafont.tex"

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
/*:121*//*122:*/
#line 2893 "weaver-interface-metafont.tex"

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
/*:122*//*123:*/
#line 2911 "weaver-interface-metafont.tex"

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
/*:123*//*124:*/
#line 2942 "weaver-interface-metafont.tex"

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
/*:124*//*125:*/
#line 2965 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:125*//*126:*/
#line 2982 "weaver-interface-metafont.tex"

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
/*:126*/
#line 2677 "weaver-interface-metafont.tex"

/*167:*/
#line 4110 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_XPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.x;
return true;
}
/*:167*//*168:*/
#line 4127 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_YPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.y;
return true;
}
/*:168*//*169:*/
#line 4146 "weaver-interface-metafont.tex"

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
/*:169*/
#line 2678 "weaver-interface-metafont.tex"

/*127:*/
#line 3008 "weaver-interface-metafont.tex"

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
/*:127*/
#line 2679 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:113*//*117:*/
#line 2769 "weaver-interface-metafont.tex"

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
/*:117*//*131:*/
#line 3087 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*132:*/
#line 3109 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:132*/
#line 3093 "weaver-interface-metafont.tex"

/*133:*/
#line 3122 "weaver-interface-metafont.tex"

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
/*:133*/
#line 3094 "weaver-interface-metafont.tex"

/*136:*/
#line 3208 "weaver-interface-metafont.tex"

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
/*:136*/
#line 3095 "weaver-interface-metafont.tex"

}
else{
/*137:*/
#line 3243 "weaver-interface-metafont.tex"

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
/*:137*/
#line 3098 "weaver-interface-metafont.tex"

/*138:*/
#line 3272 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC&&
end_expression->type==TYPE_NUMERIC&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION){
result->value= ((struct numeric_token*)begin_expression)->value/
((struct numeric_token*)end_expression)->value;
return true;
}
/*:138*/
#line 3099 "weaver-interface-metafont.tex"

}
return false;
}
/*:131*//*141:*/
#line 3321 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source){
target->x= source->x;
target->y= source->y;
}
/*:141*//*143:*/
#line 3362 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secundary,
*last_sum= NULL,*p,*prev= NULL;
DECLARE_NESTING_CONTROL();
struct pair_variable a,b;
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&IS_VALID_SUM_OR_SUB(prev,p)){
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
/*:143*//*147:*/
#line 3470 "weaver-interface-metafont.tex"

bool eval_pair_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
struct generic_token*end_secundary= NULL,*begin_primary,
*last_mul= NULL,*p,*prev= NULL,
*prev_prev= NULL,*last_fraction= NULL;
DECLARE_NESTING_CONTROL();
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_MULTIPLICATION||
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
/*148:*/
#line 3537 "weaver-interface-metafont.tex"

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
/*:148*/
#line 3507 "weaver-interface-metafont.tex"

/*149:*/
#line 3576 "weaver-interface-metafont.tex"

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
/*:149*/
#line 3508 "weaver-interface-metafont.tex"

/*150:*/
#line 3604 "weaver-interface-metafont.tex"

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
/*:150*/
#line 3509 "weaver-interface-metafont.tex"

/*151:*/
#line 3628 "weaver-interface-metafont.tex"

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
/*:151*/
#line 3510 "weaver-interface-metafont.tex"

/*152:*/
#line 3649 "weaver-interface-metafont.tex"

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
/*:152*/
#line 3511 "weaver-interface-metafont.tex"

/*153:*/
#line 3670 "weaver-interface-metafont.tex"

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
/*:153*/
#line 3512 "weaver-interface-metafont.tex"

/*154:*/
#line 3691 "weaver-interface-metafont.tex"

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
/*:154*/
#line 3513 "weaver-interface-metafont.tex"

/*155:*/
#line 3712 "weaver-interface-metafont.tex"

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
/*:155*/
#line 3514 "weaver-interface-metafont.tex"

/*156:*/
#line 3737 "weaver-interface-metafont.tex"

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
/*:156*/
#line 3515 "weaver-interface-metafont.tex"

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
/*:147*//*158:*/
#line 3791 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
if(begin_expression==end_expression){
/*159:*/
#line 3819 "weaver-interface-metafont.tex"

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
/*:159*/
#line 3797 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*160:*/
#line 3859 "weaver-interface-metafont.tex"

struct generic_token*begin_a,*end_a,*begin_b,*end_b,*comma;
begin_a= (struct generic_token*)begin_expression->next;
end_a= begin_a;
DECLARE_NESTING_CONTROL();
bool literal= true;
while(end_a!=NULL){
COUNT_NESTING(end_a);
if(IS_NOT_NESTED()&&
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
/*:160*/
#line 3801 "weaver-interface-metafont.tex"

/*161:*/
#line 3912 "weaver-interface-metafont.tex"

else{
return eval_pair_expression(mf,cx,begin_a,end_a,result);
}
/*:161*/
#line 3802 "weaver-interface-metafont.tex"

}
/*162:*/
#line 3924 "weaver-interface-metafont.tex"

if(end_expression->type==TYPE_CLOSE_BRACKETS){
struct generic_token*begin_a,*end_a,*begin_b,*end_b,*begin_c,
*end_c;
struct numeric_variable a;
struct pair_variable b,c;
DECLARE_NESTING_CONTROL();
begin_a= begin_expression;
end_a= begin_a;
while(end_a!=NULL){
COUNT_NESTING(end_a);
if(IS_NOT_NESTED()&&
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
COUNT_NESTING(end_b);
if(IS_NOT_NESTED()&&
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
/*:162*/
#line 3804 "weaver-interface-metafont.tex"

/*163:*/
#line 4007 "weaver-interface-metafont.tex"

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
/*:163*/
#line 3805 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:158*//*172:*/
#line 4212 "weaver-interface-metafont.tex"

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
/*:172*//*174:*/
#line 4264 "weaver-interface-metafont.tex"

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
/*:174*//*178:*/
#line 4358 "weaver-interface-metafont.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end){
int count= 0;
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin;
while(p!=NULL){
COUNT_NESTING(p);
if(IS_NOT_NESTED()){
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
/*:178*//*180:*/
#line 4405 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin_expression,end_expression);
if(end_expression->type==TYPE_CYCLE)
expected_length= number_of_joins;
else
expected_length= number_of_joins+1;
/*181:*/
#line 4433 "weaver-interface-metafont.tex"

if(number_of_joins==0){
if(end_expression->type==TYPE_CLOSE_BRACES){
struct generic_token*p= begin_expression;
DECLARE_NESTING_CONTROL();
while(p!=end_expression){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&
((struct generic_token*)p->next)->type==TYPE_OPEN_BRACES)
break;
p= (struct generic_token*)p->next;
}
end_expression= p;
}

return false;
}
/*:181*/
#line 4416 "weaver-interface-metafont.tex"

/*182:*/
#line 4459 "weaver-interface-metafont.tex"

result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points)*
expected_length);
if(result->points==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: No enough memory!\n",mf->file,
begin_expression->line);
#endif
return false;
}
result->length= 0;
result->points[0].x= NAN;
/*:182*/
#line 4417 "weaver-interface-metafont.tex"

/*183:*/
#line 4487 "weaver-interface-metafont.tex"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d,*end_d,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
/*192:*/
#line 4777 "weaver-interface-metafont.tex"

float w0_x= NAN,w0_y= NAN,w1_x= NAN,w1_y= NAN,curl0= NAN,curl1= NAN;
float prev_w_x= NAN,prev_w_y= NAN,prev_curl= NAN;
float next_w_x= NAN,next_w_y= NAN,next_curl= NAN;
/*:192*//*212:*/
#line 5375 "weaver-interface-metafont.tex"

float first_w_x= NAN,first_w_y= NAN,first_curl= NAN;
/*:212*/
#line 4492 "weaver-interface-metafont.tex"

begin_z1= begin_expression;
while(begin_z1!=end_expression||result->length<expected_length){
struct path_points*z1_point,*z2_point;
/*184:*/
#line 4519 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression){
DECLARE_NESTING_CONTROL();
int next_type;
while(end_z1!=end_expression){
COUNT_NESTING(end_z1);
next_type= ((struct generic_token*)end_z1->next)->type;
if(IS_NOT_NESTED()&&
(next_type==TYPE_OPEN_BRACES||next_type==TYPE_JOIN||
next_type==TYPE_AMPERSAND))
break;
end_z1= (struct generic_token*)end_z1->next;
}
}
/*:184*//*185:*/
#line 4545 "weaver-interface-metafont.tex"

if(end_z1==end_expression)
return true;
begin_d= (struct generic_token*)end_z1->next;
if(begin_d->type!=TYPE_OPEN_BRACES){
begin_d= NULL;
end_d= NULL;
}
else{
DECLARE_NESTING_CONTROL();
end_d= begin_d;
while(end_d!=end_expression){
COUNT_NESTING(end_d);
if(IS_NOT_NESTED()&&
((struct generic_token*)(end_d->next))->type==TYPE_CLOSE_BRACES)
break;
end_d= (struct generic_token*)end_d->next;
}
if(end_d!=end_expression)
end_d= (struct generic_token*)end_d->next;
if(begin_d==end_d){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unclosed brace '{'.\n",
mf->file,begin_d->line);
#endif
return false;
}
}
/*:185*//*186:*/
#line 4584 "weaver-interface-metafont.tex"

if(end_d==NULL)
begin_j= (struct generic_token*)end_z1->next;
else{
if(end_d==end_expression)
return true;
begin_j= (struct generic_token*)end_d->next;
}
end_j= begin_j;
if(begin_j->type==TYPE_JOIN){
struct generic_token*next_token;
next_token= (struct generic_token*)begin_j->next;
if(next_token->type==TYPE_CONTROLS||next_token->type==TYPE_TENSION){
DECLARE_NESTING_CONTROL();
end_j= next_token;
while(end_j!=end_expression){
COUNT_NESTING(end_j);
if(IS_NOT_NESTED()&&end_j->type!=TYPE_JOIN)
break;
end_j= (struct generic_token*)end_j->next;
}
}
}
else if(begin_j->type!=TYPE_AMPERSAND){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized path expression.\n",
mf->file,begin_f->line);
#endif
return false;
}
/*:186*//*187:*/
#line 4621 "weaver-interface-metafont.tex"

if(end_j==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized path expression.\n",
mf->file,end_f->line);
#endif
return false;
}
begin_e= (struct generic_token*)end_j->next;
if(begin_e->type!=TYPE_OPEN_BRACES){
begin_e= NULL;
end_e= NULL;
}
else{
DECLARE_NESTING_CONTROL();
end_e= begin_e;
while(end_e!=end_expression){
COUNT_NESTING(end_e);
if(IS_NOT_NESTED()&&
((struct generic_token*)(end_e->next))->type==TYPE_CLOSE_BRACES)
break;
end_e= (struct generic_token*)end_e->next;
}
if(end_e!=end_expression)
end_e= (struct generic_token*)end_e->next;
if(begin_e==end_e){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unclosed brace '{'.\n",
mf->file,begin_e->line);
#endif
return false;
}
}
/*:187*//*188:*/
#line 4663 "weaver-interface-metafont.tex"

{
DECLARE_NESTING_CONTROL();
int next_type;
if(end_e==NULL)
begin_z2= (struct generic_token*)end_j->next;
else{
if(end_e==end_expression)
return true;
begin_z2= (struct generic_token*)end_e->next;
}
end_z2= begin_z2;
while(end_z2!=end_expression){
COUNT_NESTING(end_z2);
next_type= ((struct generic_token*)end_z2->next)->type;
if(IS_NOT_NESTED()&&
(next_type==TYPE_OPEN_BRACES||next_type==TYPE_JOIN||
next_type==TYPE_AMPERSAND))
break;
end_z2= (struct generic_token*)end_z2->next;
}
}
/*:188*/
#line 4496 "weaver-interface-metafont.tex"

/*189:*/
#line 4696 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression){

struct path_variable z1;



if(z1.length==1&&z1.points[0].subpath==0){
result->points[0].subpath= NULL;
result->points[0].x= z1.points[0].x;
result->points[0].y= z1.points[0].y;
}
else
recursive_copy_points(temporary_alloc,(struct path_variable**)
&(result->points[0].subpath),&z1);
result->length++;
}
/*:189*//*190:*/
#line 4719 "weaver-interface-metafont.tex"

{

struct path_variable z2;



if(z2.length==1&&z2.points[0].subpath==0){
result->points[result->length].subpath= NULL;
result->points[result->length].x= z2.points[0].x;
result->points[result->length].y= z2.points[0].y;
}
else
recursive_copy_points(temporary_alloc,
(struct path_variable**)
&(result->points[result->length].subpath),&z2);
result->length++;
}
/*:190*//*191:*/
#line 4749 "weaver-interface-metafont.tex"

z1_point= &(result->points[result->length-2]);
while(z1_point->subpath!=NULL){
struct path_variable*p= (struct path_variable*)z1_point->subpath;
z1_point= &(p->points[p->length-1]);
}
z2_point= &(result->points[result->length-1]);
while(z2_point->subpath!=NULL){
struct path_variable*p= (struct path_variable*)z2_point->subpath;
z2_point= &(p->points[0]);
}
/*:191*/
#line 4497 "weaver-interface-metafont.tex"

/*193:*/
#line 4794 "weaver-interface-metafont.tex"

w0_x= w0_y= w1_x= w1_y= curl0= curl1= NAN;
if(!isnan(next_w_x)){
w0_x= next_w_x;
w0_y= next_w_y;
}
else if(!isnan(next_curl)){
curl0= next_curl;
}
else if(!eval_direction_specifier(mf,cx,begin_d,end_d,&w0_x,&w0_y,&curl0))
return false;
next_w_x= next_w_y= next_curl= NAN;
if(!eval_direction_specifier(mf,cx,begin_e,end_e,&w1_x,&w1_y,&curl1))
return false;
/*:193*/
#line 4498 "weaver-interface-metafont.tex"

/*200:*/
#line 4951 "weaver-interface-metafont.tex"

float tension0= NAN,tension1= NAN,u_x= NAN,u_y= NAN,v_x= NAN,
v_y= NAN;
bool atleast0,atleast1;
/*:200*//*201:*/
#line 4968 "weaver-interface-metafont.tex"

if(begin_j==end_j&&begin_j->type==TYPE_AMPERSAND){
double dif_x= z1_point->x-z2_point->x;
double dif_y= z1_point->y-z2_point->y;
if(hypot(dif_x*dif_x,dif_y*dif_y)> 0.00002){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Concatenating discontinuous paths.\n",
mf->file,begin_f->line);
#endif
return false;
}
v_x= u_x= (z1_point->x+z2_point->x)/2.0;
v_y= u_y= (z1_point->y+z2_point->y)/2.0;
}
/*:201*//*202:*/
#line 4990 "weaver-interface-metafont.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
tension0= 1.0;
tension1= 1.0;
atleast0= false;
atleast1= false;
}
/*:202*//*203:*/
#line 5008 "weaver-interface-metafont.tex"

else if(begin_j->type==TYPE_JOIN&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
DECLARE_NESTING_CONTROL();
struct generic_token*begin_c0,*end_c0,*begin_c1= NULL,*end_c1= NULL;
struct pair_variable c0,c1;
begin_c0= (struct generic_token*)begin_j->next;
begin_c0= (struct generic_token*)begin_c0->next;
if(begin_c0==end_j){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized join expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
end_c0= begin_c0;
while(end_c0->next!=end_j){
COUNT_NESTING(end_c0);
if(IS_NOT_NESTED()&&
((struct generic_token*)end_c0->next)->type==TYPE_AND)
break;
end_c0= (struct generic_token*)end_c0->next;
}
if(end_c0->next!=end_j){
begin_c1= end_c0->next;
begin_c1= (struct generic_token*)begin_c1->next;
if(begin_c1==end_j){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized join expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
end_c1= begin_c1;
while(end_c1->next!=end_j)
end_c1= (struct generic_token*)end_c1->next;
}
if(!eval_pair_primary(mf,cx,begin_c0,end_c0,&c0))
return false;
u_x= c0.x;
u_y= c0.y;
if(begin_c1!=NULL){
if(!eval_pair_primary(mf,cx,begin_c1,end_c1,&c1))
return false;
v_x= c1.x;
v_y= c1.y;
}
else{
v_x= c0.x;
v_y= c0.y;
}
}
/*:203*//*204:*/
#line 5074 "weaver-interface-metafont.tex"

else if(begin_j->type==TYPE_JOIN&&
((struct generic_token*)(begin_j->next))->type==TYPE_TENSION){
DECLARE_NESTING_CONTROL();
struct generic_token*begin_t0,*end_t0,*begin_t1= NULL,*end_t1= NULL;
struct numeric_variable t0,t1;
begin_t0= (struct generic_token*)begin_j->next;
begin_t0= (struct generic_token*)begin_t0->next;
if(begin_t0==end_j){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized join expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
if(begin_t0->type==TYPE_ATLEAST){
atleast0= true;
begin_t0= (struct generic_token*)begin_t0->next;
}
if(begin_t0==end_j||
(begin_t0->type==TYPE_ATLEAST&&begin_t0->next==end_j)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized join expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
if(begin_t0->type==TYPE_ATLEAST){
atleast0= true;
begin_t0= (struct generic_token*)begin_t0->next;
}
else
atleast0= false;
end_t0= begin_t0;
while(end_t0->next!=end_j){
COUNT_NESTING(end_t0);
if(IS_NOT_NESTED()&&
((struct generic_token*)end_t0->next)->type==TYPE_AND)
break;
end_t0= (struct generic_token*)end_t0->next;
}
if(end_t0->next!=end_j){
begin_t1= end_t0->next;
begin_t1= (struct generic_token*)begin_t1->next;
if(begin_t1==end_j||
(begin_t1->type==TYPE_ATLEAST&&begin_t1->next==end_j)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized join expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
if(begin_t1->type==TYPE_ATLEAST){
atleast1= true;
begin_t1= (struct generic_token*)begin_t1->next;
}
else
atleast1= false;
end_t1= begin_t1;
while(end_t1->next!=end_j)
end_t1= (struct generic_token*)end_t1->next;
}
if(!eval_numeric_primary(mf,cx,begin_t0,end_t0,&t0))
return false;
tension0= t0.value;
if(begin_t1!=NULL){
if(!eval_numeric_primary(mf,cx,begin_t1,end_t1,&t1))
return false;
tension1= t1.value;
}
else{
tension1= t0.value;
}
}
/*:204*//*205:*/
#line 5158 "weaver-interface-metafont.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized join expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
/*:205*/
#line 4499 "weaver-interface-metafont.tex"

/*206:*/
#line 5201 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression&&end_expression->type!=TYPE_CYCLE)
prev_curl= 1.0;
/*:206*//*207:*/
#line 5211 "weaver-interface-metafont.tex"

if(begin_j==end_j&&begin_j->type==TYPE_AMPERSAND){
if(isnan(curl0)&&isnan(w0_x))
curl0= 1.0;
if(isnan(curl1)&&isnan(w1_x))
curl1= 1.0;
}
/*:207*//*208:*/
#line 5229 "weaver-interface-metafont.tex"

if(end_z1==end_expression)
next_curl= 1.0;
else if(end_expression->type!=TYPE_CYCLE&&
((struct generic_token*)(end_z1->next))->type!=
TYPE_OPEN_BRACES){
bool last_join= true;
struct generic_token*p= (struct generic_token*)end_z1->next;
DECLARE_NESTING_CONTROL();
while(p!=end_expression){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&
(p->type==TYPE_AMPERSAND||p->type==TYPE_JOIN)){
last_join= false;
break;
}
p= (struct generic_token*)p->next;
}
if(last_join)
next_curl= 1.0;
}
/*:208*//*210:*/
#line 5308 "weaver-interface-metafont.tex"

if(isnan(w0_x)&&isnan(w0_y)&&isnan(curl0)){
w0_x= prev_w_x;
w0_y= prev_w_y;
curl0= prev_curl;
}
/*:210*//*211:*/
#line 5322 "weaver-interface-metafont.tex"

if(isnan(w1_x)&&isnan(w1_y)&&isnan(curl1)){
if(!isnan(next_curl))
curl1= next_curl;
else if(end_z2->next!=NULL&&end_z2!=end_expression&&
((struct generic_token*)(end_z2->next))->type==
TYPE_OPEN_BRACES){
struct generic_token*next0,*next1;
DECLARE_NESTING_CONTROL();
next0= (struct generic_token*)end_z2->next;
next1= next0;
while(next1!=end_expression){
COUNT_NESTING(next1);
if(IS_NOT_NESTED()&&next1->type==TYPE_CLOSE_BRACES)
break;
next1= (struct generic_token*)next1->next;
}
if(next0->type==TYPE_OPEN_BRACES&&next1->type==TYPE_CLOSE_BRACES){
if(!eval_direction_specifier(mf,cx,begin_e,end_e,&next_w_x,&next_w_y,
&next_curl))
return false;
w1_x= next_w_x;
w1_y= next_w_y;
curl1= next_curl;
}
else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized join expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
}
}
/*:211*//*213:*/
#line 5385 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d!=NULL&&end_d!=NULL){
first_w_x= w0_x;
first_w_y= w0_y;
first_curl= curl0;
}
/*:213*//*215:*/
#line 5421 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d==NULL&&isnan(curl0)&&isnan(w0_x)){
struct generic_token*begin_last_spec= NULL,*end_last_spec= NULL,
*last_join= NULL,*p;
DECLARE_NESTING_CONTROL();
p= end_z2;
while(p->type!=end_expression){
if(IS_NOT_NESTED()&&p->type==TYPE_OPEN_BRACES)
begin_last_spec= p;
COUNT_NESTING(p);
if(IS_NOT_NESTED()){
if(p->type==TYPE_CLOSE_BRACES)
end_last_spec= p;
else if(p->type==TYPE_JOIN||p->type==TYPE_AMPERSAND)
last_join= p;
else if(p->type==TYPE_CYCLE)
break;
}
p= (struct generic_token*)p->next;
}
if(end_last_spec!=NULL&&end_last_spec->next==p&&
p->type==TYPE_CYCLE){
if(!eval_direction_specifier(mf,cx,begin_last_spec,end_last_spec,
&w0_x,&w0_y,&curl0))
return false;
}
else if(last_join!=NULL&&last_join->type==TYPE_AMPERSAND)
curl0= 1.0;
}
/*:215*/
#line 4500 "weaver-interface-metafont.tex"

/*209:*/
#line 5288 "weaver-interface-metafont.tex"

if((begin_z1==begin_expression&&end_expression->type!=TYPE_CYCLE)||
(begin_j==end_j&&begin_j->type==TYPE_AMPERSAND)||
(begin_e!=NULL&&end_e!=NULL)){
prev_w_x= w1_x;
prev_w_y= w1_y;
prev_curl= curl1;
}
else{
prev_w_x= NAN;
prev_w_y= NAN;
prev_curl= NAN;
}
/*:209*/
#line 4501 "weaver-interface-metafont.tex"

begin_z1= begin_z2;
end_z1= end_z2;
}
if(end_expression->type==TYPE_CYCLE){
/*214:*/
#line 5399 "weaver-interface-metafont.tex"

if(begin_d==NULL&&end_d==NULL){
if(!isnan(first_w_x)||!isnan(first_curl)){
w1_x= first_w_x;
w1_y= first_w_y;
curl1= first_curl;
}
}
/*:214*/
#line 4506 "weaver-interface-metafont.tex"

}
}
/*:183*/
#line 4418 "weaver-interface-metafont.tex"

return false;
}
/*:180*//*195:*/
#line 4828 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y,float*curl){
/*196:*/
#line 4846 "weaver-interface-metafont.tex"

if(begin==NULL||end==NULL){
return true;
}
/*:196*/
#line 4833 "weaver-interface-metafont.tex"

/*197:*/
#line 4857 "weaver-interface-metafont.tex"

if(begin!=NULL&&
((struct generic_token*)(begin->next))->type==TYPE_CURL){
struct numeric_variable result;
struct generic_token*begin_numeric_expr,*end_numeric_expr;
begin_numeric_expr= (struct generic_token*)begin->next;
begin_numeric_expr= (struct generic_token*)begin_numeric_expr->next;
end_numeric_expr= begin_numeric_expr;
while(end_numeric_expr!=NULL&&end_numeric_expr->next!=end)
end_numeric_expr= (struct generic_token*)end_numeric_expr->next;
if(end_numeric_expr==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Unrecognized direction delimiter.\n",
mf->file,begin->line);
#endif
return false;
}
if(!eval_numeric_expression(mf,cx,begin_numeric_expr,end_numeric_expr,
&result))
return false;
*curl= result.value;
return true;
}
/*:197*/
#line 4834 "weaver-interface-metafont.tex"

/*198:*/
#line 4890 "weaver-interface-metafont.tex"

DECLARE_NESTING_CONTROL();
struct generic_token*begin_a,*end_a,*begin_b= NULL,*end_b;
begin_a= (struct generic_token*)begin->next;
end_a= begin_a;
while(end_a->next!=end){
COUNT_NESTING(end_a);
if(IS_NOT_NESTED()&&end_a->type==TYPE_COMMA){
begin_b= (struct generic_token*)end_a->next;
break;
}
end_a= (struct generic_token*)end_a->next;
}
if(begin_b!=NULL){
struct numeric_variable a,b;
end_b= begin_b;
while(end_b->next!=end)
end_b= (struct generic_token*)end_b->next;
if(!eval_numeric_expression(mf,cx,begin_a,end_a,&a))
return false;
if(!eval_numeric_expression(mf,cx,begin_b,end_b,&b))
return false;
if(a.value!=0.0||b.value!=0.0){
*w_x= a.value;
*w_y= b.value;
}
return true;
}
/*:198*/
#line 4835 "weaver-interface-metafont.tex"

/*199:*/
#line 4928 "weaver-interface-metafont.tex"

else{
struct pair_variable a;
if(!eval_pair_expression(mf,cx,begin_a,end_a,&a))
return false;
if(a.x!=0.0||a.y!=0.0){
*w_x= a.x;
*w_y= a.y;
}
return true;
}
/*:199*/
#line 4836 "weaver-interface-metafont.tex"

return false;
}
/*:195*/
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
