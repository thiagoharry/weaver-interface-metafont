/*6:*/
#line 197 "weaver-interface-metafont_en.tex"

#include "metafont.h"
/*15:*/
#line 424 "weaver-interface-metafont_en.tex"

#include <stdio.h> 
/*:15*//*17:*/
#line 447 "weaver-interface-metafont_en.tex"

#include <ctype.h> 
/*:17*//*37:*/
#line 878 "weaver-interface-metafont_en.tex"

#include <string.h> 
/*:37*//*79:*/
#line 1782 "weaver-interface-metafont_en.tex"

#include <math.h> 
/*:79*//*224:*/
#line 5696 "weaver-interface-metafont_en.tex"

#include <complex.h> 
/*:224*/
#line 199 "weaver-interface-metafont_en.tex"

/*82:*/
#line 1840 "weaver-interface-metafont_en.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
/*:82*//*103:*/
#line 2326 "weaver-interface-metafont_en.tex"

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
#line 2371 "weaver-interface-metafont_en.tex"

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
          prev -> type != TYPE_OF &&                    \
          prev -> type != TYPE_POINT &&                 \
          prev -> type != TYPE_PRECONTROL &&            \
          prev -> type != TYPE_POSTCONTROL &&           \
          prev -> type != TYPE_UNIFORMDEVIATE))
/*:104*/
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
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
void*var;
char*value;
};
/*:11*//*12:*/
#line 335 "weaver-interface-metafont_en.tex"

#define TYPE_OPEN_PARENTHESIS  4 
#define TYPE_CLOSE_PARENTHESIS 5 
#define TYPE_COMMA             6 
#define TYPE_SEMICOLON         7 
/*39:*/
#line 948 "weaver-interface-metafont_en.tex"

#define TYPE_END             8 
#define TYPE_DUMP            9 
/*:39*//*50:*/
#line 1182 "weaver-interface-metafont_en.tex"

#define TYPE_BEGINGROUP            10 
#define TYPE_ENDGROUP              11 
/*:50*//*58:*/
#line 1350 "weaver-interface-metafont_en.tex"

#define TYPE_T_BOOLEAN               12 
#define TYPE_T_PATH                  13 
#define TYPE_T_PEN                   14 
#define TYPE_T_PICTURE               15 
#define TYPE_T_TRANSFORM             16 
#define TYPE_T_PAIR                  17 
#define TYPE_T_NUMERIC               18 
/*:58*//*93:*/
#line 2084 "weaver-interface-metafont_en.tex"

#define TYPE_ASSIGNMENT            19 
#define TYPE_ASSIGNMENT2           20 
/*:93*//*100:*/
#line 2285 "weaver-interface-metafont_en.tex"

#define TYPE_SUM                   21 
#define TYPE_SUBTRACT              22 
#define TYPE_PYTHAGOREAN_SUM       23 
#define TYPE_PYTHAGOREAN_SUBTRACT  24 
#define TYPE_OPEN_BRACKETS         25 
#define TYPE_CLOSE_BRACKETS        26 
#define TYPE_OPEN_BRACES           27 
#define TYPE_CLOSE_BRACES          28 
/*:100*//*107:*/
#line 2498 "weaver-interface-metafont_en.tex"

#define TYPE_MULTIPLICATION        29 
#define TYPE_DIVISION              30 
/*:107*//*111:*/
#line 2621 "weaver-interface-metafont_en.tex"

#define TYPE_LENGTH         31 
#define TYPE_SQRT           32 
#define TYPE_SIND           33 
#define TYPE_COSD           34 
#define TYPE_LOG            35 
#define TYPE_EXP            36 
#define TYPE_FLOOR          37 
#define TYPE_UNIFORMDEVIATE 38 
/*:111*//*129:*/
#line 3041 "weaver-interface-metafont_en.tex"

#define TYPE_NORMALDEVIATE  39 
/*:129*//*145:*/
#line 3411 "weaver-interface-metafont_en.tex"

#define TYPE_ROTATED  40 
#define TYPE_SCALED   41 
#define TYPE_SHIFTED  42 
#define TYPE_SLANTED  43 
#define TYPE_XSCALED  44 
#define TYPE_YSCALED  45 
#define TYPE_ZSCALED  46 
/*:145*//*165:*/
#line 4057 "weaver-interface-metafont_en.tex"

#define TYPE_XPART  47 
#define TYPE_YPART  48 
#define TYPE_ANGLE  49 
/*:165*//*176:*/
#line 4283 "weaver-interface-metafont_en.tex"

#define TYPE_CYCLE          50 
#define TYPE_AMPERSAND      51 
#define TYPE_JOIN           52 
#define TYPE_TENSION        53 
#define TYPE_AND            54 
#define TYPE_ATLEAST        55 
#define TYPE_CONTROLS       56 
#define TYPE_CURL           57 
#define TYPE_STRAIGHT_JOIN   58 
/*:176*//*255:*/
#line 6475 "weaver-interface-metafont_en.tex"

#define TYPE_REVERSE        59 
#define TYPE_SUBPATH        60 
#define TYPE_OF             61 
/*:255*//*270:*/
#line 6963 "weaver-interface-metafont_en.tex"

#define TYPE_POINT             62 
#define TYPE_PRECONTROL        63 
#define TYPE_POSTCONTROL       64 
/*:270*/
#line 340 "weaver-interface-metafont_en.tex"


struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:12*//*60:*/
#line 1389 "weaver-interface-metafont_en.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:60*//*61:*/
#line 1411 "weaver-interface-metafont_en.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:61*//*77:*/
#line 1755 "weaver-interface-metafont_en.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:77*//*85:*/
#line 1887 "weaver-interface-metafont_en.tex"

struct pair_variable{
int type;
int nesting_level;
void*next;
float x,y;
};
/*:85*//*87:*/
#line 1947 "weaver-interface-metafont_en.tex"

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
int length,total_length;
struct path_points*points;
};
/*:87*/
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
#line 831 "weaver-interface-metafont_en.tex"

static char*list_of_keywords[]= {
/*40:*/
#line 958 "weaver-interface-metafont_en.tex"

"end","dump",
/*:40*//*51:*/
#line 1191 "weaver-interface-metafont_en.tex"

"begingroup","endgroup",
/*:51*//*59:*/
#line 1364 "weaver-interface-metafont_en.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:59*//*94:*/
#line 2093 "weaver-interface-metafont_en.tex"

"=",":=",
/*:94*//*101:*/
#line 2300 "weaver-interface-metafont_en.tex"

"+","-","++","+-+","[","]","{","}",
/*:101*//*108:*/
#line 2505 "weaver-interface-metafont_en.tex"

"*","/",
/*:108*//*112:*/
#line 2634 "weaver-interface-metafont_en.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:112*//*130:*/
#line 3047 "weaver-interface-metafont_en.tex"

"normaldeviate",
/*:130*//*146:*/
#line 3423 "weaver-interface-metafont_en.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:146*//*166:*/
#line 4067 "weaver-interface-metafont_en.tex"

"xpart","ypart","angle",
/*:166*//*177:*/
#line 4299 "weaver-interface-metafont_en.tex"

"cycle","&","..","tension","and","atleast","controls","curl","--",
/*:177*//*256:*/
#line 6486 "weaver-interface-metafont_en.tex"

"reverse","subpath","of",
/*:256*//*271:*/
#line 6973 "weaver-interface-metafont_en.tex"

"point","precontrol","postcontrol",
/*:271*/
#line 833 "weaver-interface-metafont_en.tex"

NULL};
/*:35*/
#line 202 "weaver-interface-metafont_en.tex"

/*45:*/
#line 1037 "weaver-interface-metafont_en.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:45*//*48:*/
#line 1109 "weaver-interface-metafont_en.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:48*//*52:*/
#line 1200 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:52*//*71:*/
#line 1598 "weaver-interface-metafont_en.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:71*//*73:*/
#line 1655 "weaver-interface-metafont_en.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:73*//*75:*/
#line 1716 "weaver-interface-metafont_en.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:75*//*91:*/
#line 2027 "weaver-interface-metafont_en.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer);
/*:91*//*98:*/
#line 2224 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source);
/*:98*//*102:*/
#line 2309 "weaver-interface-metafont_en.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:102*//*109:*/
#line 2513 "weaver-interface-metafont_en.tex"

bool eval_numeric_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:109*//*113:*/
#line 2642 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:113*//*117:*/
#line 2741 "weaver-interface-metafont_en.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:117*//*131:*/
#line 3058 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:131*//*141:*/
#line 3295 "weaver-interface-metafont_en.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source);
/*:141*//*143:*/
#line 3333 "weaver-interface-metafont_en.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result);
/*:143*//*147:*/
#line 3434 "weaver-interface-metafont_en.tex"

bool eval_pair_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:147*//*158:*/
#line 3757 "weaver-interface-metafont_en.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:158*//*172:*/
#line 4184 "weaver-interface-metafont_en.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source);
/*:172*//*174:*/
#line 4221 "weaver-interface-metafont_en.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target);
/*:174*//*178:*/
#line 4309 "weaver-interface-metafont_en.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:178*//*180:*/
#line 4351 "weaver-interface-metafont_en.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:180*//*195:*/
#line 4794 "weaver-interface-metafont_en.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y);
/*:195*//*222:*/
#line 5674 "weaver-interface-metafont_en.tex"

double compute_f(double theta,double phi);
/*:222*//*226:*/
#line 5730 "weaver-interface-metafont_en.tex"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y);
/*:226*//*228:*/
#line 5764 "weaver-interface-metafont_en.tex"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y);
/*:228*//*234:*/
#line 5962 "weaver-interface-metafont_en.tex"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:234*//*236:*/
#line 6053 "weaver-interface-metafont_en.tex"

bool eval_path_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:236*//*239:*/
#line 6185 "weaver-interface-metafont_en.tex"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta);
/*:239*//*242:*/
#line 6238 "weaver-interface-metafont_en.tex"

void path_xyscale(struct path_variable*p,float x,float y);
/*:242*//*245:*/
#line 6290 "weaver-interface-metafont_en.tex"

void path_shift(struct path_variable*p,float x,float y);
/*:245*//*248:*/
#line 6336 "weaver-interface-metafont_en.tex"

void path_slant(struct path_variable*p,float s);
/*:248*//*253:*/
#line 6427 "weaver-interface-metafont_en.tex"

void path_zscale(struct path_variable*p,float x,float y);
/*:253*//*257:*/
#line 6500 "weaver-interface-metafont_en.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:257*//*261:*/
#line 6638 "weaver-interface-metafont_en.tex"

void reverse_path(struct path_variable*src,struct path_variable*dst);
/*:261*//*264:*/
#line 6764 "weaver-interface-metafont_en.tex"

int recursive_copy_subpath(struct path_points*dst,struct path_variable*src,
int offset,int size);
/*:264*/
#line 203 "weaver-interface-metafont_en.tex"

/*13:*/
#line 362 "weaver-interface-metafont_en.tex"

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
#line 384 "weaver-interface-metafont_en.tex"

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
#line 437 "weaver-interface-metafont_en.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:16*/
#line 401 "weaver-interface-metafont_en.tex"

/*18:*/
#line 458 "weaver-interface-metafont_en.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:18*/
#line 402 "weaver-interface-metafont_en.tex"

/*19:*/
#line 475 "weaver-interface-metafont_en.tex"

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
#line 403 "weaver-interface-metafont_en.tex"

/*20:*/
#line 522 "weaver-interface-metafont_en.tex"

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
#line 404 "weaver-interface-metafont_en.tex"

/*21:*/
#line 567 "weaver-interface-metafont_en.tex"

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
#line 405 "weaver-interface-metafont_en.tex"

/*22:*/
#line 602 "weaver-interface-metafont_en.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*23:*/
#line 633 "weaver-interface-metafont_en.tex"

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
#line 608 "weaver-interface-metafont_en.tex"

/*24:*/
#line 650 "weaver-interface-metafont_en.tex"

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
#line 609 "weaver-interface-metafont_en.tex"

/*25:*/
#line 666 "weaver-interface-metafont_en.tex"

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
#line 610 "weaver-interface-metafont_en.tex"

/*26:*/
#line 682 "weaver-interface-metafont_en.tex"

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
#line 611 "weaver-interface-metafont_en.tex"

/*27:*/
#line 698 "weaver-interface-metafont_en.tex"

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
#line 612 "weaver-interface-metafont_en.tex"

/*28:*/
#line 714 "weaver-interface-metafont_en.tex"

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
#line 613 "weaver-interface-metafont_en.tex"

/*29:*/
#line 730 "weaver-interface-metafont_en.tex"

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
#line 614 "weaver-interface-metafont_en.tex"

/*30:*/
#line 746 "weaver-interface-metafont_en.tex"

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
#line 615 "weaver-interface-metafont_en.tex"

/*31:*/
#line 762 "weaver-interface-metafont_en.tex"

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
#line 616 "weaver-interface-metafont_en.tex"

/*32:*/
#line 778 "weaver-interface-metafont_en.tex"

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
#line 617 "weaver-interface-metafont_en.tex"

/*33:*/
#line 794 "weaver-interface-metafont_en.tex"

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
#line 618 "weaver-interface-metafont_en.tex"

/*34:*/
#line 810 "weaver-interface-metafont_en.tex"

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
#line 619 "weaver-interface-metafont_en.tex"


/*36:*/
#line 844 "weaver-interface-metafont_en.tex"

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
#line 967 "weaver-interface-metafont_en.tex"

if(token_type==TYPE_DUMP)
token_type= TYPE_END;
/*:41*//*95:*/
#line 2102 "weaver-interface-metafont_en.tex"

else if(token_type==TYPE_ASSIGNMENT2)
token_type= TYPE_ASSIGNMENT;
/*:95*/
#line 857 "weaver-interface-metafont_en.tex"

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
#line 621 "weaver-interface-metafont_en.tex"

/*38:*/
#line 888 "weaver-interface-metafont_en.tex"

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
#line 1862 "weaver-interface-metafont_en.tex"

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
#line 901 "weaver-interface-metafont_en.tex"

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
#line 622 "weaver-interface-metafont_en.tex"

}
/*:22*/
#line 406 "weaver-interface-metafont_en.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
fclose(fp);
return first_token;
}
/*:14*//*42:*/
#line 981 "weaver-interface-metafont_en.tex"

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
#line 1053 "weaver-interface-metafont_en.tex"

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
#line 1433 "weaver-interface-metafont_en.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:63*//*81:*/
#line 1812 "weaver-interface-metafont_en.tex"

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
/*:81*//*136:*/
#line 3183 "weaver-interface-metafont_en.tex"

mf->have_stored_normaldeviate= false;
/*:136*/
#line 1064 "weaver-interface-metafont_en.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*56:*/
#line 1257 "weaver-interface-metafont_en.tex"

cx->nesting_level= 0;
/*:56*//*67:*/
#line 1494 "weaver-interface-metafont_en.tex"

cx->variables= NULL;
/*:67*/
#line 1070 "weaver-interface-metafont_en.tex"

return cx;
}
/*:46*//*47:*/
#line 1080 "weaver-interface-metafont_en.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*64:*/
#line 1445 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*89:*/
#line 1998 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:89*/
#line 1451 "weaver-interface-metafont_en.tex"

mf->free(v);
v= next;
}
}
/*:64*//*65:*/
#line 1463 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)named->var;
next= (struct named_variable*)(named->next);
mf->free(named->name);
/*89:*/
#line 1998 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:89*/
#line 1472 "weaver-interface-metafont_en.tex"

mf->free(v);
mf->free(named);
named= next;
}
}
/*:65*//*83:*/
#line 1851 "weaver-interface-metafont_en.tex"

mf->free(mf->internal_numeric_variables);
/*:83*/
#line 1084 "weaver-interface-metafont_en.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*68:*/
#line 1502 "weaver-interface-metafont_en.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*90:*/
#line 2011 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL)
path_recursive_free(temporary_free,path,false);
}
/*:90*/
#line 1508 "weaver-interface-metafont_en.tex"

temporary_free(v);
v= next;
}
}
/*:68*/
#line 1090 "weaver-interface-metafont_en.tex"

temporary_free(cx);
}
}
/*:47*//*49:*/
#line 1121 "weaver-interface-metafont_en.tex"

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
#line 1207 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*54:*/
#line 1234 "weaver-interface-metafont_en.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:54*/
#line 1210 "weaver-interface-metafont_en.tex"

/*57:*/
#line 1290 "weaver-interface-metafont_en.tex"

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
#line 1211 "weaver-interface-metafont_en.tex"

/*69:*/
#line 1519 "weaver-interface-metafont_en.tex"

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
#line 1569 "weaver-interface-metafont_en.tex"

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
#line 1536 "weaver-interface-metafont_en.tex"

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
#line 1212 "weaver-interface-metafont_en.tex"

/*96:*/
#line 2126 "weaver-interface-metafont_en.tex"

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
#line 2200 "weaver-interface-metafont_en.tex"

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
#line 2186 "weaver-interface-metafont_en.tex"

/*140:*/
#line 3274 "weaver-interface-metafont_en.tex"

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
/*:140*/
#line 2187 "weaver-interface-metafont_en.tex"

/*171:*/
#line 4160 "weaver-interface-metafont_en.tex"

else if(type==TYPE_T_PATH){
int i;
struct path_variable result;
if(!eval_path_expression(mf,cx,begin_expression,
(struct generic_token*)*end_token_list,
&result))
return false;
var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
assign_path_variable(mf,(struct path_variable*)var->var,
&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&result,false);
}
/*:171*/
#line 2188 "weaver-interface-metafont_en.tex"

return true;
}
/*:96*/
#line 1213 "weaver-interface-metafont_en.tex"




#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:53*//*72:*/
#line 1611 "weaver-interface-metafont_en.tex"

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
case TYPE_T_PAIR:
var_size= sizeof(struct pair_variable);
break;
case TYPE_T_PATH:
var_size= sizeof(struct path_variable);
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
#line 1772 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:78*//*86:*/
#line 1902 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PAIR){
((struct pair_variable*)var)->x= NAN;
}
/*:86*//*88:*/
#line 1986 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
}
/*:88*/
#line 1637 "weaver-interface-metafont_en.tex"

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
#line 1666 "weaver-interface-metafont_en.tex"

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
#line 1729 "weaver-interface-metafont_en.tex"

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
#line 2037 "weaver-interface-metafont_en.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer){
if(free_func!=NULL){
int i;
for(i= 0;i<path->length;i++){
if(path->points[i].subpath!=NULL)
path_recursive_free(free_func,(struct path_variable*)
path->points[i].subpath,true);
}
free_func(path->points);
if(free_first_pointer)
free_func(path);
}
}
/*:92*//*99:*/
#line 2233 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source){
target->value= source->value;
}
/*:99*//*106:*/
#line 2427 "weaver-interface-metafont_en.tex"

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
/*:106*//*110:*/
#line 2535 "weaver-interface-metafont_en.tex"

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
/*:110*//*114:*/
#line 2655 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*115:*/
#line 2677 "weaver-interface-metafont_en.tex"

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
/*:115*/
#line 2660 "weaver-interface-metafont_en.tex"

/*116:*/
#line 2701 "weaver-interface-metafont_en.tex"

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
/*167:*/
#line 4079 "weaver-interface-metafont_en.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)hypot(p.x*p.x,p.y*p.y);
return true;
}
/*:167*//*269:*/
#line 6934 "weaver-interface-metafont_en.tex"

else if(expr_type==TYPE_T_PATH){
struct path_variable p;
if(!eval_path_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)(p.total_length-1);
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&p,false);
return true;
}
/*:269*/
#line 2718 "weaver-interface-metafont_en.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:116*/
#line 2661 "weaver-interface-metafont_en.tex"

/*119:*/
#line 2788 "weaver-interface-metafont_en.tex"

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
/*:119*//*120:*/
#line 2816 "weaver-interface-metafont_en.tex"

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
/*:120*//*121:*/
#line 2835 "weaver-interface-metafont_en.tex"

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
/*:121*//*122:*/
#line 2854 "weaver-interface-metafont_en.tex"

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
/*:122*//*123:*/
#line 2880 "weaver-interface-metafont_en.tex"

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
/*:123*//*124:*/
#line 2898 "weaver-interface-metafont_en.tex"

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
/*:124*//*125:*/
#line 2928 "weaver-interface-metafont_en.tex"

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
/*:125*//*126:*/
#line 2951 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:126*//*127:*/
#line 2968 "weaver-interface-metafont_en.tex"

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
/*:127*/
#line 2662 "weaver-interface-metafont_en.tex"

/*168:*/
#line 4095 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_XPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.x;
return true;
}
/*:168*//*169:*/
#line 4112 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_YPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.y;
return true;
}
/*:169*//*170:*/
#line 4132 "weaver-interface-metafont_en.tex"

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
/*:170*/
#line 2663 "weaver-interface-metafont_en.tex"

/*128:*/
#line 2992 "weaver-interface-metafont_en.tex"

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
/*:128*/
#line 2664 "weaver-interface-metafont_en.tex"

return true;
}
/*:114*//*118:*/
#line 2749 "weaver-interface-metafont_en.tex"

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
struct generic_token*aux;
aux= (struct generic_token*)begin_expr->next;
aux= (struct generic_token*)aux->next;
if(begin_expr->type==TYPE_OPEN_PARENTHESIS&&
end_expr->type==TYPE_CLOSE_PARENTHESIS&&
aux!=NULL&&aux->type==TYPE_COMMA)
return TYPE_T_PAIR;

}
return TYPE_T_NUMERIC;

}
/*:118*//*132:*/
#line 3071 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*133:*/
#line 3093 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:133*/
#line 3077 "weaver-interface-metafont_en.tex"

/*134:*/
#line 3106 "weaver-interface-metafont_en.tex"

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
/*:134*/
#line 3078 "weaver-interface-metafont_en.tex"

/*137:*/
#line 3193 "weaver-interface-metafont_en.tex"

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
/*:137*/
#line 3079 "weaver-interface-metafont_en.tex"

}
else{
/*138:*/
#line 3228 "weaver-interface-metafont_en.tex"

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
/*:138*/
#line 3082 "weaver-interface-metafont_en.tex"

/*139:*/
#line 3257 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_NUMERIC&&
end_expression->type==TYPE_NUMERIC&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION){
result->value= ((struct numeric_token*)begin_expression)->value/
((struct numeric_token*)end_expression)->value;
return true;
}
/*:139*/
#line 3083 "weaver-interface-metafont_en.tex"

}
return true;
}
/*:132*//*142:*/
#line 3304 "weaver-interface-metafont_en.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source){
target->x= source->x;
target->y= source->y;
}
/*:142*//*144:*/
#line 3346 "weaver-interface-metafont_en.tex"

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
/*:144*//*148:*/
#line 3453 "weaver-interface-metafont_en.tex"

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
/*149:*/
#line 3520 "weaver-interface-metafont_en.tex"

if(last_mul->type==TYPE_MULTIPLICATION){
if(get_primary_expression_type(mf,cx,begin_primary,end_expression)==
TYPE_T_PAIR){
struct numeric_variable a;
struct pair_variable b;
if(!eval_numeric_secundary(mf,cx,begin_expression,end_secundary,
&a))
return false;
if(!eval_pair_primary(mf,cx,begin_primary,end_expression,&b))
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
/*:149*/
#line 3490 "weaver-interface-metafont_en.tex"

/*150:*/
#line 3557 "weaver-interface-metafont_en.tex"

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
/*:150*/
#line 3491 "weaver-interface-metafont_en.tex"

/*151:*/
#line 3585 "weaver-interface-metafont_en.tex"

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
/*:151*/
#line 3492 "weaver-interface-metafont_en.tex"

/*152:*/
#line 3609 "weaver-interface-metafont_en.tex"

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
/*:152*/
#line 3493 "weaver-interface-metafont_en.tex"

/*153:*/
#line 3629 "weaver-interface-metafont_en.tex"

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
/*:153*/
#line 3494 "weaver-interface-metafont_en.tex"

/*154:*/
#line 3650 "weaver-interface-metafont_en.tex"

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
/*:154*/
#line 3495 "weaver-interface-metafont_en.tex"

/*155:*/
#line 3671 "weaver-interface-metafont_en.tex"

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
/*:155*/
#line 3496 "weaver-interface-metafont_en.tex"

/*156:*/
#line 3692 "weaver-interface-metafont_en.tex"

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
/*:156*/
#line 3497 "weaver-interface-metafont_en.tex"

/*157:*/
#line 3717 "weaver-interface-metafont_en.tex"

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
/*:157*/
#line 3498 "weaver-interface-metafont_en.tex"

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
/*:148*//*159:*/
#line 3769 "weaver-interface-metafont_en.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
if(begin_expression==end_expression){
/*160:*/
#line 3798 "weaver-interface-metafont_en.tex"

if(begin_expression==end_expression){
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
"'%s'.\n",mf->file,begin_expression->line,
tok->value);
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
}
/*:160*/
#line 3775 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*161:*/
#line 3841 "weaver-interface-metafont_en.tex"

struct generic_token*begin_a,*end_a,*begin_b,*end_b,*comma;
if(begin_expression->next==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression (empty parenthesis).\n ",mf->file,
begin_expression->line);
#endif
return false;
}
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
/*:161*/
#line 3779 "weaver-interface-metafont_en.tex"

/*162:*/
#line 3902 "weaver-interface-metafont_en.tex"

else{
return eval_pair_expression(mf,cx,begin_a,end_a,result);
}
/*:162*/
#line 3780 "weaver-interface-metafont_en.tex"

}
/*272:*/
#line 6993 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_POINT||
begin_expression->type==TYPE_PRECONTROL||
begin_expression->type==TYPE_POSTCONTROL){
DECLARE_NESTING_CONTROL();
struct generic_token*begin_num,*end_num,*of= NULL,*begin_path,*end_path;
struct numeric_variable a;
struct path_variable b;
begin_num= begin_expression->next;
end_num= begin_num;
int index;
while(end_num!=NULL&&end_num->next!=end_expression){
COUNT_NESTING(end_num);
if(IS_NOT_NESTED()&&
((struct generic_token*)end_num->next)->type==TYPE_OF){
of= end_num->next;
break;
}
end_num= end_num->next;
}
if(of==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing 'of' in 'point' expression\n",
mf->file,begin_expression->line);
#endif
return false;
}
if(of->next==NULL||of==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing path expression in "
"'point' expression\n",mf->file,begin_expression->line);
#endif
return false;
}
begin_path= of->next;
end_path= end_expression;
if(!eval_numeric_expression(mf,cx,begin_num,end_num,&a))
return false;
if(!eval_path_primary(mf,cx,begin_path,end_path,&b))
return false;
if(b.cyclic){
index= ((int)(a.value))%b.length;
if(begin_expression->type==TYPE_PRECONTROL)
index= (index-1)%b.length;
}
else{
index= (int)(a.value);
if(index<0)index= 0;
if(index>=b.length)index= b.length-1;
if(begin_expression->type==TYPE_PRECONTROL)
index= (index-1)%b.length;
}
if(begin_expression->type==TYPE_POINT){
result->x= b.points[index].x;
result->y= b.points[index].y;
}
else if(begin_expression->type==TYPE_PRECONTROL){
if(index<0){
result->x= b.points[0].x;
result->y= b.points[0].y;
}
else{
result->x= b.points[index].v_x;
result->y= b.points[index].v_y;
}
}
else{
result->x= b.points[index].u_x;
result->y= b.points[index].u_y;
}
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&b,false);
return true;
}
/*:272*/
#line 3782 "weaver-interface-metafont_en.tex"

/*163:*/
#line 3913 "weaver-interface-metafont_en.tex"

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
/*:163*/
#line 3783 "weaver-interface-metafont_en.tex"

/*164:*/
#line 3993 "weaver-interface-metafont_en.tex"

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
/*:164*/
#line 3784 "weaver-interface-metafont_en.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:159*//*173:*/
#line 4194 "weaver-interface-metafont_en.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source){
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
if(target->length!=-1&&disalloc!=NULL)
path_recursive_free(disalloc,target,false);
recursive_copy_points(alloc,&target,source,false);
}
/*:173*//*175:*/
#line 4230 "weaver-interface-metafont_en.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target){
int i;
if(alloc_target)
*target= (struct path_variable*)alloc(sizeof(struct path_variable));
(*target)->cyclic= source->cyclic;
(*target)->length= source->length;
(*target)->total_length= source->total_length;
(*target)->points= (struct path_points*)
alloc(sizeof(struct path_points)*
(*target)->length);
for(i= 0;i<(*target)->length;i++){
memcpy(&((*target)->points[i]),&(source->points[i]),
sizeof(struct path_points));
if(source->points[i].subpath!=NULL)
recursive_copy_points(alloc,(struct path_variable**)
&((*target)->points[i].subpath),
source->points[i].subpath,true);
}
}
/*:175*//*179:*/
#line 4319 "weaver-interface-metafont_en.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end){
int count= 0;
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin;
while(p!=NULL){
COUNT_NESTING(p);
if(IS_NOT_NESTED()){
if(p->type==TYPE_AMPERSAND)
count++;
else if(p->type==TYPE_STRAIGHT_JOIN)
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
/*:179*//*181:*/
#line 4364 "weaver-interface-metafont_en.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin_expression,end_expression);
expected_length= number_of_joins+1;
/*182:*/
#line 4389 "weaver-interface-metafont_en.tex"

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
return eval_path_tertiary(mf,cx,begin_expression,end_expression,
result);
}
/*:182*/
#line 4372 "weaver-interface-metafont_en.tex"

/*183:*/
#line 4414 "weaver-interface-metafont_en.tex"

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
result->total_length= 0;
result->points[0].x= NAN;
result->cyclic= false;
/*:183*/
#line 4373 "weaver-interface-metafont_en.tex"

/*184:*/
#line 4444 "weaver-interface-metafont_en.tex"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d= NULL,*end_d= NULL,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
struct path_points*z1_point= NULL,*z2_point= NULL;
/*193:*/
#line 4761 "weaver-interface-metafont_en.tex"

float w0_x= NAN,w0_y= NAN,w1_x= NAN,w1_y= NAN;
float prev_w_x= NAN,prev_w_y= NAN;
float next_w_x= NAN,next_w_y= NAN;
/*:193*//*209:*/
#line 5321 "weaver-interface-metafont_en.tex"

float first_w_x= NAN,first_w_y= NAN;
/*:209*//*213:*/
#line 5422 "weaver-interface-metafont_en.tex"

float previous_point_x= NAN,previous_point_y= NAN;
/*:213*//*217:*/
#line 5528 "weaver-interface-metafont_en.tex"

float first_point_x= NAN,first_point_y= NAN;
/*:217*/
#line 4450 "weaver-interface-metafont_en.tex"

begin_z1= begin_expression;
end_z1= begin_z1;
while(begin_z1!=end_expression||result->length<expected_length){
/*185:*/
#line 4476 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression){
DECLARE_NESTING_CONTROL();
int next_type;
end_z1= begin_z1;
while(end_z1!=end_expression){
COUNT_NESTING(end_z1);
next_type= ((struct generic_token*)end_z1->next)->type;
if(IS_NOT_NESTED()&&
(next_type==TYPE_OPEN_BRACES||next_type==TYPE_JOIN||
next_type==TYPE_AMPERSAND||next_type==TYPE_STRAIGHT_JOIN))
break;
end_z1= (struct generic_token*)end_z1->next;
}
}
/*:185*//*186:*/
#line 4502 "weaver-interface-metafont_en.tex"

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
((struct generic_token*)end_d)->type==TYPE_CLOSE_BRACES)
break;
end_d= (struct generic_token*)end_d->next;
}
if(begin_d==end_d){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unclosed brace '{'.\n",
mf->file,begin_d->line);
#endif
return false;
}
}
/*:186*//*187:*/
#line 4538 "weaver-interface-metafont_en.tex"

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
if(IS_NOT_NESTED()&&end_j->type==TYPE_JOIN)
break;
end_j= (struct generic_token*)end_j->next;
}
}
}
else if(begin_j->type!=TYPE_AMPERSAND&&
begin_j->type!=TYPE_STRAIGHT_JOIN){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized path expression.\n",
mf->file,begin_j->line);
#endif
return false;
}
/*:187*//*188:*/
#line 4576 "weaver-interface-metafont_en.tex"

if(end_j==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized path expression.\n",
mf->file,end_j->line);
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
((struct generic_token*)end_e)->type==TYPE_CLOSE_BRACES)
break;
end_e= (struct generic_token*)end_e->next;
}
if(begin_e==end_e){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unclosed brace '{'.\n",
mf->file,begin_e->line);
#endif
return false;
}
}
/*:188*//*189:*/
#line 4616 "weaver-interface-metafont_en.tex"

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
next_type==TYPE_AMPERSAND||next_type==TYPE_STRAIGHT_JOIN))
break;
end_z2= (struct generic_token*)end_z2->next;
}
}
/*:189*/
#line 4454 "weaver-interface-metafont_en.tex"

/*190:*/
#line 4649 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression){
bool ret;
struct path_variable z1;
ret= eval_path_tertiary(mf,cx,begin_z1,end_z1,&z1);
if(!ret)
return false;
if(z1.length==1&&z1.points[0].subpath==0){
result->points[0].subpath= NULL;
result->points[0].x= z1.points[0].x;
result->points[0].y= z1.points[0].y;
result->total_length++;
}
else{
recursive_copy_points(temporary_alloc,(struct path_variable**)
&(result->points[0].subpath),&z1,
true);
result->total_length+= ((struct path_variable*)
result->points[0].subpath)->total_length;
}
result->length++;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&z1,false);
}
/*:190*//*191:*/
#line 4682 "weaver-interface-metafont_en.tex"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE){
struct path_points*p= result->points;
while(p[0].subpath!=NULL)
p= ((struct path_variable*)p[0].subpath)->points;
result->points[result->length].subpath= NULL;
result->points[result->length].x= p[0].x;
result->points[result->length].y= p[0].y;
result->points[result->length].u_x= p[0].u_x;
result->points[result->length].u_y= p[0].u_y;
result->points[result->length].v_x= p[0].v_x;
result->points[result->length].v_y= p[0].v_y;
result->length++;
result->total_length++;
result->cyclic= true;
}
else{
bool ret;
struct path_variable z2;
ret= eval_path_tertiary(mf,cx,begin_z2,end_z2,&z2);
if(!ret)
return false;
if(z2.length==1&&z2.points[0].subpath==0){
result->points[result->length].subpath= NULL;
result->points[result->length].x= z2.points[0].x;
result->points[result->length].y= z2.points[0].y;
result->total_length++;
}
else{
recursive_copy_points(temporary_alloc,
(struct path_variable**)
&(result->points[result->length].subpath),&z2,
true);
result->total_length+= 
((struct path_variable*)
result->points[result->length].subpath)->total_length;
}
result->length++;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&z2,false);
}
/*:191*//*192:*/
#line 4735 "weaver-interface-metafont_en.tex"

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
/*:192*/
#line 4455 "weaver-interface-metafont_en.tex"

/*194:*/
#line 4777 "weaver-interface-metafont_en.tex"

w0_x= w0_y= w1_x= w1_y= NAN;
if(!isnan(next_w_x)){
w0_x= next_w_x;
w0_y= next_w_y;
}
else if(!eval_direction_specifier(mf,cx,begin_d,end_d,&w0_x,&w0_y))
return false;
next_w_x= next_w_y= NAN;
if(!eval_direction_specifier(mf,cx,begin_e,end_e,&w1_x,&w1_y))
return false;
/*:194*/
#line 4456 "weaver-interface-metafont_en.tex"

/*200:*/
#line 4897 "weaver-interface-metafont_en.tex"

float tension0= NAN,tension1= NAN,u_x= NAN,u_y= NAN,v_x= NAN,
v_y= NAN;
bool atleast0= false,atleast1= false;
/*:200*//*201:*/
#line 4913 "weaver-interface-metafont_en.tex"

if(begin_j==end_j&&begin_j->type==TYPE_AMPERSAND){
double dif_x= z1_point->x-z2_point->x;
double dif_y= z1_point->y-z2_point->y;
if(hypot(dif_x*dif_x,dif_y*dif_y)> 0.00002){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Concatenating discontinuous paths.\n",
mf->file,begin_j->line);
#endif
return false;
}
v_x= u_x= z1_point->x;
v_y= u_y= z1_point->y;


result->total_length--;
z1_point->x= NAN;
z1_point->y= NAN;
}
/*:201*//*202:*/
#line 4941 "weaver-interface-metafont_en.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_STRAIGHT_JOIN){
u_x= z1_point->x+(1.0/3.0)*(z2_point->x-z1_point->x);
u_y= z1_point->y+(1.0/3.0)*(z2_point->y-z1_point->y);
v_x= z1_point->x+(2.0/3.0)*(z2_point->x-z1_point->x);
v_y= z1_point->y+(2.0/3.0)*(z2_point->y-z1_point->y);
}
/*:202*//*203:*/
#line 4956 "weaver-interface-metafont_en.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
tension0= 1.0;
tension1= 1.0;
atleast0= false;
atleast1= false;
}
/*:203*//*204:*/
#line 4974 "weaver-interface-metafont_en.tex"

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
/*:204*//*205:*/
#line 5041 "weaver-interface-metafont_en.tex"

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
if(tension0<0.75||tension1<0.75){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Improper tension. Should be >= 0.75\n",
mf->file,begin_j->line);
#endif
return false;
}
}
/*:205*/
#line 4457 "weaver-interface-metafont_en.tex"

/*207:*/
#line 5258 "weaver-interface-metafont_en.tex"

if(isnan(w0_x)&&isnan(w0_y)){
w0_x= prev_w_x;
w0_y= prev_w_y;
}
/*:207*//*208:*/
#line 5271 "weaver-interface-metafont_en.tex"

if(isnan(w1_x)&&isnan(w1_y)){
if(end_z2->next!=NULL&&end_z2!=end_expression&&
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
if(!eval_direction_specifier(mf,cx,next0,next1,&next_w_x,
&next_w_y))
return false;
w1_x= next_w_x;
w1_y= next_w_y;
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
/*:208*//*210:*/
#line 5330 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d!=NULL&&end_d!=NULL){
first_w_x= w0_x;
first_w_y= w0_y;
}
/*:210*//*211:*/
#line 5343 "weaver-interface-metafont_en.tex"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE){
if(!isnan(first_w_x)&&isnan(w1_x)){
w1_x= first_w_x;
w1_y= first_w_y;
}
}
/*:211*//*212:*/
#line 5361 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d==NULL&&isnan(w0_x)&&isnan(u_x)){
struct generic_token*begin_last_spec= NULL,*end_last_spec= NULL,
*last_join= NULL,*second_last_join= NULL,*p;
DECLARE_NESTING_CONTROL();
p= end_z1->next;
while(p!=end_expression){
if(IS_NOT_NESTED()){
if(p->type==TYPE_OPEN_BRACES){
begin_last_spec= p;
}
else if(p->type==TYPE_CLOSE_BRACES)
end_last_spec= p;
else if(p->type==TYPE_JOIN||p->type==TYPE_AMPERSAND||
p->type==TYPE_STRAIGHT_JOIN){
second_last_join= last_join;
last_join= p;
}
else if(p->type==TYPE_CYCLE)
break;
else
COUNT_NESTING(p);
}
else
COUNT_NESTING(p);
p= (struct generic_token*)p->next;
}
if(end_last_spec!=NULL&&end_last_spec->next==p&&
p->type==TYPE_CYCLE){
if(!eval_direction_specifier(mf,cx,begin_last_spec,end_last_spec,
&w0_x,&w0_y))
return false;
}
/*220:*/
#line 5575 "weaver-interface-metafont_en.tex"

if(last_join!=NULL&&last_join->type==TYPE_JOIN){
struct generic_token*p= (struct generic_token*)second_last_join->next;
if(p->type==TYPE_CONTROLS){
struct generic_token*p_end;
p= (struct generic_token*)p->next;
p_end= p;
while(p_end!=end_expression){
struct generic_token*next= (struct generic_token*)p_end->next;
COUNT_NESTING(p_end);
if(IS_NOT_NESTED()){
if(next->type==TYPE_AND)
p= (struct generic_token*)next->next;
else if(next->type==TYPE_JOIN)
break;
}
p_end= next;
}
if(p_end!=end_expression){
struct pair_variable var;
if(!eval_pair_primary(mf,cx,p,p_end,&var))
return false;
w0_x= z1_point->x-var.x;
w0_y= z1_point->y-var.y;
if(hypot(w0_x*w0_x,w0_y*w0_y)<=0.00002){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
}
}
/*:220*/
#line 5395 "weaver-interface-metafont_en.tex"

}
/*:212*//*214:*/
#line 5433 "weaver-interface-metafont_en.tex"

if(begin_d==NULL&&end_d==NULL&&!isnan(previous_point_x)&&
!isnan(previous_point_y)&&isnan(w0_x)){
w0_x= z1_point->x-previous_point_x;
w0_y= z1_point->y-previous_point_y;
if(hypot(w0_x*w0_x,w0_y*w0_y)<=0.00002){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
/*:214*//*215:*/
#line 5454 "weaver-interface-metafont_en.tex"

if(begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
previous_point_x= v_x;
previous_point_y= v_y;
}
else{
previous_point_x= NAN;
previous_point_y= NAN;
}
/*:215*//*216:*/
#line 5473 "weaver-interface-metafont_en.tex"

if(begin_e==NULL&&end_e==NULL&&isnan(w1_x)&&
end_z2!=end_expression){
DECLARE_NESTING_CONTROL();
struct generic_token*begin_point,*end_point;
begin_point= (struct generic_token*)end_z2->next;
while(begin_point!=end_expression){
COUNT_NESTING(begin_point);
if(IS_NOT_NESTED()&&(begin_point->type==TYPE_JOIN||
begin_point->type==TYPE_AMPERSAND||
begin_point->type==TYPE_STRAIGHT_JOIN))
break;
begin_point= (struct generic_token*)begin_point->next;
}
if(begin_point!=end_expression&&
begin_point->type!=TYPE_AMPERSAND&&
begin_point->type!=TYPE_STRAIGHT_JOIN){
begin_point= (struct generic_token*)begin_point->next;
if(begin_point!=end_expression&&begin_point->type==TYPE_CONTROLS){
begin_point= (struct generic_token*)begin_point->next;
end_point= begin_point;
while(end_point!=end_expression){
struct generic_token*next= (struct generic_token*)end_point->next;
COUNT_NESTING(end_point);
if(IS_NOT_NESTED()&&next!=NULL&&
(next->type==TYPE_AND||next->type==TYPE_JOIN))
break;
end_point= (struct generic_token*)end_point->next;
}
if(end_point!=end_expression){
struct pair_variable var;
if(!eval_pair_primary(mf,cx,begin_point,end_point,&var))
return false;
w1_x= var.x-z2_point->x;
w1_y= var.y-z2_point->y;
if(hypot(w1_x*w1_x,w1_y*w1_y)<=0.00002){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,
begin_j->line);
#endif
return false;
}
}
}
}
}
/*:216*//*218:*/
#line 5536 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
first_point_x= u_x;
first_point_y= u_y;
}
/*:218*//*219:*/
#line 5550 "weaver-interface-metafont_en.tex"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE&&begin_d==NULL&&
end_d==NULL&&isnan(w1_x)&&!isnan(first_point_x)&&isnan(w1_x)){
w1_x= first_point_x-z2_point->x;
w1_y= first_point_y-z2_point->y;
if(hypot(w1_x*w1_x,w1_y*w1_y)<=0.00002){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
/*:219*//*221:*/
#line 5617 "weaver-interface-metafont_en.tex"

if(isnan(u_x)||isnan(u_y)||isnan(v_x)||isnan(v_y)){
if(isnan(w0_x)||isnan(w0_y)||isnan(w1_x)||isnan(w1_y)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
/*:221*//*225:*/
#line 5705 "weaver-interface-metafont_en.tex"

if(isnan(u_x)||isnan(u_y)||isnan(v_x)||isnan(v_y)){
double complex u,v;
double complex z0= z1_point->x+z1_point->y*I;
double complex z1= z2_point->x+z2_point->y*I;
double theta= carg((w0_x+w0_y*I)/(z1-z0));
double phi= carg((z1-z0)/(w1_x+w1_y*I));
u= z0+(cexp(theta*I)*(z1-z0)*compute_f(theta,phi))/tension0;
v= z1-(cexp(-phi*I)*(z1-z0)*compute_f(phi,theta))/tension1;
u_x= creal(u);
u_y= cimag(u);
v_x= creal(v);
v_y= cimag(v);
/*232:*/
#line 5900 "weaver-interface-metafont_en.tex"

if(atleast0)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&u_x,&u_y);
if(atleast1)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&v_x,&v_y);
/*:232*/
#line 5718 "weaver-interface-metafont_en.tex"

}
/*:225*//*233:*/
#line 5916 "weaver-interface-metafont_en.tex"

z1_point->u_x= u_x;
z1_point->u_y= u_y;
z1_point->v_x= v_x;
z1_point->v_y= v_y;
if(result->length>=expected_length&&result->cyclic==false){
struct path_points*final_point= 
&(result->points[result->length-1]);
while(final_point->subpath!=NULL){
struct path_variable*p= (struct path_variable*)
(final_point->subpath);
final_point= &(p->points[p->length-1]);
}
final_point->u_x= final_point->x;
final_point->u_y= final_point->y;
final_point->v_x= final_point->x;
final_point->v_y= final_point->y;
}
/*:233*/
#line 4458 "weaver-interface-metafont_en.tex"

/*206:*/
#line 5239 "weaver-interface-metafont_en.tex"

if((begin_z1==begin_expression&&end_expression->type!=TYPE_CYCLE)||
(begin_j==end_j&&begin_j->type==TYPE_AMPERSAND)||
(begin_j==end_j&&begin_j->type==TYPE_STRAIGHT_JOIN)||
(begin_e!=NULL&&end_e!=NULL)){
prev_w_x= w1_x;
prev_w_y= w1_y;
}
else{
prev_w_x= NAN;
prev_w_y= NAN;
}
/*:206*/
#line 4459 "weaver-interface-metafont_en.tex"

begin_z1= begin_z2;
end_z1= end_z2;
}
}
/*:184*/
#line 4374 "weaver-interface-metafont_en.tex"

return true;
}
/*:181*//*196:*/
#line 4808 "weaver-interface-metafont_en.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y){
/*197:*/
#line 4825 "weaver-interface-metafont_en.tex"

if(begin==NULL||end==NULL){
return true;
}
/*:197*/
#line 4813 "weaver-interface-metafont_en.tex"

/*198:*/
#line 4838 "weaver-interface-metafont_en.tex"

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
#line 4814 "weaver-interface-metafont_en.tex"

/*199:*/
#line 4876 "weaver-interface-metafont_en.tex"

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
#line 4815 "weaver-interface-metafont_en.tex"

return false;
}
/*:196*//*223:*/
#line 5680 "weaver-interface-metafont_en.tex"

double compute_f(double theta,double phi){
double n= 2+sqrt(2)*(sin(theta)-0.0625*sin(phi))*
(sin(phi)-0.0625*sin(theta))*(cos(theta)-cos(phi));
double d= 3*(1+0.5*(sqrt(5)-1)*cos(theta)+0.5*(3-sqrt(5))*
cos(phi));
return n/d;
}
/*:223*//*227:*/
#line 5737 "weaver-interface-metafont_en.tex"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y){
double v0_x,v0_y,v1_x,v1_y;
v0_x= c0_x-v_x;
v0_y= c0_y-v_y;
v1_x= c1_x-v_x;
v1_y= c1_y-v_y;
if(fabs(v0_x)<=0.00002&&fabs(v0_y)<=0.00002)
return INFINITY;
if(fabs(v1_x)<=0.00002&&fabs(v1_y)<=0.00002)
return INFINITY;
return acos((v0_x*v1_x+v0_y*v1_y)/
(hypot(v0_x*v0_x,v0_y*v0_y)*
hypot(v1_x*v1_x,v1_y*v1_y)));
}
/*:227*//*229:*/
#line 5772 "weaver-interface-metafont_en.tex"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y){
double internal_angle0,internal_angle1,internal_angle2;
double triangle_angle;
double p2_x,p2_y;
internal_angle0= get_angle(p0_x,p0_y,p1_x,p1_y,p0_x+d0_x,p0_y+d0_y);
internal_angle1= get_angle(p1_x,p1_y,p0_x,p0_y,p1_x+d1_x,p1_y+d1_y);
internal_angle2= M_PI-internal_angle0-internal_angle1;
if(internal_angle0+internal_angle1>=M_PI-0.00002)
return;
{

double known_side= hypot((p1_x-p0_x)*(p1_x-p0_x),
(p1_y-p0_y)*(p1_y-p0_y));
double triangle_side= known_side*sin(internal_angle0)/
sin(internal_angle2);

triangle_angle= get_angle(p0_x,p0_y,p1_x,p1_y,p0_x+1.0,p0_y);
p2_x= p0_x+triangle_side*cos(triangle_angle+internal_angle0);
p2_y= p0_y+triangle_side*sin(triangle_angle+internal_angle0);
}
{
/*230:*/
#line 5814 "weaver-interface-metafont_en.tex"

bool s1,s2,s3;
s1= ((*control_x-p1_x)*(p0_y-p1_y)-
(p0_x-p1_x)*(*control_y-p1_y))<0;
s2= ((*control_x-p2_x)*(p1_y-p2_y)-
(p1_x-p2_x)*(*control_y-p2_y))<0;
s3= ((*control_x-p0_x)*(p2_y-p0_y)-
(p2_x-p0_x)*(*control_y-p0_y))<0;
if(s1==s2&&s2==s3)
return;
/*:230*/
#line 5796 "weaver-interface-metafont_en.tex"

/*231:*/
#line 5836 "weaver-interface-metafont_en.tex"

{
double x0,y0,x1,y1;
if(s1!=s2&&s1!=s3){
x0= p0_x;y0= p0_y;
x1= p1_x;y1= p1_y;
}
else if(s2!=s1&&s2!=s3){
x0= p1_x;y0= p1_y;
x1= p2_x;y1= p2_y;
}
else{
x0= p2_x;y0= p2_y;
x1= p0_x;y1= p0_y;
}
if(x1<x0){
double tmp;
tmp= x1;x1= x0;x0= tmp;
tmp= y1;y1= y0;y0= tmp;
}
if(x0==x1){
*control_x= x0;
if(*control_y> y0&&*control_y> y1){
if(y0> y1)
*control_y= y0;
else
*control_y= y1;
}
else if(*control_y<y0&&*control_y<y1){
if(y0<y1)
*control_y= y0;
else
*control_y= y1;
}
}
else if(y0==y1)
*control_y= y0;
else{

double m0= (y1-y0)/(x1-x0);
double b0= y1-m0*x1;

double m1= -m0;
double b1= *control_y-m1**control_x;
*control_x= (b1-b0)/(m0-m1);
*control_y= m0**control_x+b0;
}
if(*control_x> x1){
*control_x= x1;
*control_y= y1;
}
else if(*control_x<x0){
*control_x= x0;
*control_y= y0;
}
}
/*:231*/
#line 5797 "weaver-interface-metafont_en.tex"

}
}
/*:229*//*235:*/
#line 5973 "weaver-interface-metafont_en.tex"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
struct generic_token*p,*prev= NULL;
bool this_expression_is_pair= false;
DECLARE_NESTING_CONTROL();
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&IS_VALID_SUM_OR_SUB(prev,p)){
this_expression_is_pair= true;
break;
}
prev= p;
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(this_expression_is_pair){
struct pair_variable pair;
if(!eval_pair_expression(mf,cx,begin_expression,end_expression,
&pair))
return false;
result->cyclic= false;
result->length= 1;
result->total_length= 1;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
if(result->points==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Not enough memory!\n",
mf->file,begin_expression->line);
#endif
return false;
}
result->points->x= pair.x;
result->points->y= pair.y;
result->points->u_x= pair.x;
result->points->u_y= pair.y;
result->points->v_x= pair.x;
result->points->v_y= pair.y;
result->points->subpath= NULL;
return true;
}
else
return eval_path_secundary(mf,cx,begin_expression,end_expression,
result);
}
/*:235*//*237:*/
#line 6064 "weaver-interface-metafont_en.tex"

bool eval_path_secundary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
bool have_transform= false,have_pair_operator= false;
struct generic_token*p,*last_fraction= NULL,*transform_op= NULL,
*before_transform= NULL,*prev= NULL,
*prev_prev= NULL;
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
else if(p->type==TYPE_DIVISION||p->type==TYPE_MULTIPLICATION)
have_pair_operator= true;
else{
have_transform= true;
transform_op= p;
before_transform= prev;
}
}
prev_prev= prev;
prev= p;
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(have_transform){
if(transform_op->next==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_path_secundary(mf,cx,begin_expression,before_transform,result))
return false;
/*238:*/
#line 6164 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_ROTATED){
struct numeric_variable a;
double theta,sin_theta,cos_theta;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
theta= 0.0174533*a.value;
sin_theta= sin(theta);
cos_theta= cos(theta);
path_rotate(result,sin_theta,cos_theta);
return true;
}
/*:238*/
#line 6112 "weaver-interface-metafont_en.tex"

/*241:*/
#line 6222 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,a.value);
return true;
}
/*:241*/
#line 6113 "weaver-interface-metafont_en.tex"

/*244:*/
#line 6275 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SHIFTED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_shift(result,a.x,a.y);
return true;
}
/*:244*/
#line 6114 "weaver-interface-metafont_en.tex"

/*247:*/
#line 6321 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SLANTED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_slant(result,a.value);
return true;
}
/*:247*/
#line 6115 "weaver-interface-metafont_en.tex"

/*250:*/
#line 6364 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_XSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,1.0);
return true;
}
/*:250*/
#line 6116 "weaver-interface-metafont_en.tex"

/*251:*/
#line 6380 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_YSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,1.0,a.value);
return true;
}
/*:251*/
#line 6117 "weaver-interface-metafont_en.tex"

/*252:*/
#line 6406 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_ZSCALED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,&a))
return false;
path_zscale(result,a.x,a.y);
return true;
}
else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transformer\n",
mf->file,transform_op->line);
#endif
return false;
}
/*:252*/
#line 6118 "weaver-interface-metafont_en.tex"

}
else if(have_pair_operator){
struct pair_variable pair;
if(!eval_pair_secundary(mf,cx,begin_expression,end_expression,&pair))
return false;
result->cyclic= false;
result->length= 1;
result->total_length= 1;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
if(result->points==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Not enough memory!\n",
mf->file,begin_expression->line);
#endif
return false;
}
result->points[0].x= pair.x;
result->points[0].y= pair.y;
result->points[0].u_x= pair.x;
result->points[0].u_y= pair.y;
result->points[0].v_x= pair.x;
result->points[0].v_y= pair.y;
result->points[0].subpath= NULL;
return true;
}
else
return eval_path_primary(mf,cx,begin_expression,end_expression,
result);
}
/*:237*//*240:*/
#line 6192 "weaver-interface-metafont_en.tex"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta){
int i;
for(i= 0;i<p->length;i++){
if(p->points[i].subpath!=NULL)
path_rotate((struct path_variable*)(p->points[i].subpath),
sin_theta,cos_theta);
else{
double x= p->points[i].x,y= p->points[i].y;
p->points[i].x= x*cos_theta-y*sin_theta;
p->points[i].y= x*sin_theta+y*cos_theta;
x= p->points[i].u_x;
y= p->points[i].u_y;
p->points[i].u_x= x*cos_theta-y*sin_theta;
p->points[i].u_y= x*sin_theta+y*cos_theta;
x= p->points[i].v_x;
y= p->points[i].v_y;
p->points[i].v_x= x*cos_theta-y*sin_theta;
p->points[i].v_y= x*sin_theta+y*cos_theta;
}
}
}
/*:240*//*243:*/
#line 6250 "weaver-interface-metafont_en.tex"

void path_xyscale(struct path_variable*p,float x,float y){
int i;
for(i= 0;i<p->length;i++){
if(p->points[i].subpath!=NULL)
path_xyscale((struct path_variable*)(p->points[i].subpath),x,
y);
else{
p->points[i].x*= x;
p->points[i].y*= y;
p->points[i].u_x*= x;
p->points[i].u_y*= y;
p->points[i].v_x*= x;
p->points[i].v_y*= y;
}
}
}
/*:243*//*246:*/
#line 6296 "weaver-interface-metafont_en.tex"

void path_shift(struct path_variable*p,float x,float y){
int i;
for(i= 0;i<p->length;i++){
if(p->points[i].subpath!=NULL)
path_shift((struct path_variable*)(p->points[i].subpath),x,y);
else{
p->points[i].x+= x;
p->points[i].y+= y;
p->points[i].u_x+= x;
p->points[i].u_y+= y;
p->points[i].v_x+= x;
p->points[i].v_y+= y;
}
}
}
/*:246*//*249:*/
#line 6342 "weaver-interface-metafont_en.tex"

void path_slant(struct path_variable*p,float s){
int i;
for(i= 0;i<p->length;i++){
if(p->points[i].subpath!=NULL)
path_slant((struct path_variable*)(p->points[i].subpath),s);
else{
p->points[i].x+= s*p->points[i].y;
p->points[i].u_x+= s*p->points[i].u_y;
p->points[i].v_x+= s*p->points[i].v_y;
}
}
}
/*:249*//*254:*/
#line 6433 "weaver-interface-metafont_en.tex"

void path_zscale(struct path_variable*p,float x,float y){
int i;
for(i= 0;i<p->length;i++){
if(p->points[i].subpath!=NULL)
path_zscale((struct path_variable*)(p->points[i].subpath),
x,y);
else{
float x0= p->points[i].x;
float y0= p->points[i].y;
p->points[i].x= x0*x-y0*y;
p->points[i].y= x0*y+y0*x;
x0= p->points[i].u_x;
y0= p->points[i].u_y;
p->points[i].u_x= x0*x-y0*y;
p->points[i].u_y= x0*y+y0*x;
x0= p->points[i].v_x;
y0= p->points[i].v_y;
p->points[i].v_x= x0*x-y0*y;
p->points[i].v_x= x0*y+y0*x;
}
}
}
/*:254*//*258:*/
#line 6511 "weaver-interface-metafont_en.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
if(begin_expression->type==TYPE_REVERSE){
/*260:*/
#line 6609 "weaver-interface-metafont_en.tex"

struct path_variable tmp;
if(begin_expression->next==NULL||
begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_path_primary(mf,cx,begin_expression->next,end_expression,
&tmp))
return false;
result->length= tmp.total_length;
result->total_length= tmp.total_length;
result->points= 
(struct path_points*)
temporary_alloc(sizeof(struct path_points)*tmp.total_length);
reverse_path(&tmp,result);
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&tmp,false);
return true;
/*:260*/
#line 6517 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUBPATH){
/*263:*/
#line 6677 "weaver-interface-metafont_en.tex"

DECLARE_NESTING_CONTROL();
struct pair_variable a;
struct path_variable b;
struct generic_token*of,*end_pair_expr= begin_expression;
struct generic_token*begin_subexpr;
if(begin_expression->next==NULL||end_pair_expr->type==TYPE_OF||
begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
of= (struct generic_token*)(end_pair_expr->next);
while(of!=NULL&&of!=end_expression){
COUNT_NESTING(of);
if(IS_NOT_NESTED()&&of->type==TYPE_OF)
break;
end_pair_expr= of;
of= (struct generic_token*)(of->next);
}
if(of==NULL||of==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_pair_expression(mf,cx,(struct generic_token*)begin_expression->next,
end_pair_expr,&a))
return false;
begin_subexpr= of->next;
if(!eval_path_primary(mf,cx,begin_subexpr,end_expression,&b))
return false;
{
int final_path_size;
result->cyclic= false;
if(b.cyclic&&((a.x-a.y)>=b.length||-(a.x-a.y)>=b.length))
result->cyclic= true;
if(a.x<0)
a.x= 0;
if(a.y<0)
a.y= 0;
if(a.x>=b.length)
a.x= b.length-1;
if(a.y>=b.length)
a.y= b.length-1;
final_path_size= a.y-a.x;
if(final_path_size<0)
final_path_size*= -1;
final_path_size++;
result->length= final_path_size;
result->total_length= final_path_size;
result->points= (struct path_points*)
temporary_alloc(final_path_size*
sizeof(struct path_points));
if(result->points==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: No enough memory!\n",mf->file,
begin_expression->line);
#endif
return false;
}
recursive_copy_subpath(result->points,&b,(a.x<=a.y)?(a.x):(a.y),
final_path_size);
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&b,false);


return true;
}
/*:263*/
#line 6520 "weaver-interface-metafont_en.tex"

}
else if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*266:*/
#line 6820 "weaver-interface-metafont_en.tex"

{
struct symbolic_token*v= (struct symbolic_token*)begin_expression;
void*content= v->var;
if(((struct pair_variable*)content)->type==TYPE_T_PAIR){
result->length= 1;
result->total_length= 1;
result->cyclic= false;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
result->points[0].x= ((struct pair_variable*)content)->x;
result->points[0].y= ((struct pair_variable*)content)->y;
result->points[0].u_x= ((struct pair_variable*)content)->x;
result->points[0].u_y= ((struct pair_variable*)content)->y;
result->points[0].v_x= ((struct pair_variable*)content)->x;
result->points[0].v_y= ((struct pair_variable*)content)->y;
result->points[0].subpath= NULL;
return true;
}
else if(((struct path_variable*)content)->type==TYPE_T_PATH){
recursive_copy_points(temporary_alloc,&result,
(struct path_variable*)content,false);
return true;
}
else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Variable is not pair nor path!\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:266*/
#line 6524 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*267:*/
#line 6865 "weaver-interface-metafont_en.tex"

struct generic_token*t= begin_expression->next;
bool found_comma= false;
DECLARE_NESTING_CONTROL();
if(begin_expression->next==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Empty parenthesis.\n",
mf->file,begin_expression->line);
#endif
return false;
}
while(t!=NULL&&t->next!=end_expression){
COUNT_NESTING(t);
if(IS_NOT_NESTED()&&t->type==TYPE_COMMA){
found_comma= true;
break;
}
t= t->next;
}
if(!found_comma){
return eval_path_expression(mf,cx,begin_expression->next,t,result);
}
/*:267*/
#line 6528 "weaver-interface-metafont_en.tex"

}
{
/*268:*/
#line 6896 "weaver-interface-metafont_en.tex"

struct pair_variable v;
if(!eval_pair_primary(mf,cx,begin_expression,end_expression,&v))
return false;
result->length= 1;
result->total_length= 1;
result->cyclic= false;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
result->points[0].subpath= NULL;
result->points[0].x= v.x;
result->points[0].y= v.y;
result->points[0].u_x= v.x;
result->points[0].u_y= v.y;
result->points[0].v_x= v.x;
result->points[0].v_y= v.y;
return true;
/*:268*/
#line 6531 "weaver-interface-metafont_en.tex"

}
return false;
}
/*:258*//*259:*/
#line 6564 "weaver-interface-metafont_en.tex"

bool aux_reverse(struct path_points**right_dst,
struct path_variable*pointer,int*index,
int*copied_points,int total_points){
while(*copied_points<total_points){
if(pointer->points[*index].subpath==NULL&&
!isnan(pointer->points[*index].x)){

memcpy(*right_dst,&(pointer->points[*index]),
sizeof(struct path_points));
(*right_dst)->subpath= NULL;
(*right_dst)--;
(*copied_points)++;
if(*index<pointer->length-1)
(*index)++;
else
return false;
}
else if(pointer->points[*index].subpath!=NULL){
int new_index= 0;
aux_reverse(right_dst,(struct path_variable*)
(pointer->points[*index].subpath),
&new_index,copied_points,total_points);
if(*index>=pointer->length-1)
return false;
else
(*index)++;
}
else{
if(*index>=pointer->length-1)
return false;
else
(*index)++;
}
}
return true;
}
/*:259*//*262:*/
#line 6646 "weaver-interface-metafont_en.tex"

void reverse_path(struct path_variable*src,struct path_variable*dst){
int index= 0,i,copied_points= 0;
struct path_points*right= &(dst->points[dst->length-1]);
struct path_variable*l= src;
aux_reverse(&right,l,&index,&copied_points,dst->length);
for(i= 0;i<dst->length-1;i++){
dst->points[i].u_x= dst->points[i+1].v_x;
dst->points[i].u_y= dst->points[i+1].v_y;
dst->points[i].v_x= dst->points[i+1].u_x;
dst->points[i].v_y= dst->points[i+1].u_y;
}
dst->points[i].u_x= dst->points[i].x;
dst->points[i].u_y= dst->points[i].y;
dst->points[i].v_x= dst->points[i].x;
dst->points[i].v_y= dst->points[i].y;
dst->cyclic= src->cyclic;
}
/*:262*//*265:*/
#line 6771 "weaver-interface-metafont_en.tex"

int recursive_copy_subpath(struct path_points*dst,struct path_variable*src,
int offset,int size){
int i,read_data= 0;
for(i= 0;i<src->length;i++){
if(size<=0)
break;
if(src->points[i].subpath==NULL){
if(offset<=0){
dst->subpath= NULL;
dst->x= src->points[i].x;
dst->y= src->points[i].y;
dst->u_x= src->points[i].u_x;
dst->u_y= src->points[i].u_y;
dst->v_x= src->points[i].v_x;
dst->v_y= src->points[i].v_y;
size--;
dst++;
}
else
offset--;
read_data++;
}
else{
int recursive_read= recursive_copy_subpath(dst,(struct path_variable*)
src->points[i].subpath,
offset,size);
if(offset> recursive_read){
offset-= recursive_read;
read_data+= recursive_read;
}
else{
read_data+= recursive_read;
dst+= (read_data-offset);
size-= (read_data-offset);
offset= 0;
}
}
}
return read_data;
}
/*:265*/
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
