/*7:*/
#line 229 "weaver-interface-metafont.tex"

#include "metafont.h"
/*18:*/
#line 484 "weaver-interface-metafont.tex"

#include <stdio.h> 
/*:18*//*20:*/
#line 506 "weaver-interface-metafont.tex"

#include <ctype.h> 
/*:20*//*40:*/
#line 940 "weaver-interface-metafont.tex"

#include <string.h> 
/*:40*//*88:*/
#line 2023 "weaver-interface-metafont.tex"

#include <math.h> 
/*:88*//*108:*/
#line 2417 "weaver-interface-metafont.tex"

struct pen_variable;
/*:108*//*286:*/
#line 7302 "weaver-interface-metafont.tex"

#include <complex.h> 
/*:286*/
#line 231 "weaver-interface-metafont.tex"

/*91:*/
#line 2080 "weaver-interface-metafont.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
/*:91*//*100:*/
#line 2240 "weaver-interface-metafont.tex"

#define INTERNAL_TRANSFORM_IDENTITY 0
/*:100*//*110:*/
#line 2463 "weaver-interface-metafont.tex"

#define FLAG_CONVEX   1
#define FLAG_STRAIGHT 2
#define FLAG_CIRCULAR 4
#define FLAG_SQUARE   8
#define FLAG_NULL    16
/*:110*//*116:*/
#line 2631 "weaver-interface-metafont.tex"

#define INTERNAL_PEN_CURRENTPEN 0
#define INTERNAL_PEN_PENSQUARE  1
/*:116*//*125:*/
#line 2760 "weaver-interface-metafont.tex"

#define INTERNAL_PICTURE_CURRENTPICTURE 0
/*:125*//*140:*/
#line 3103 "weaver-interface-metafont.tex"

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
#define RESET_NESTING_COUNT() nesting_parenthesis =  0; \
                              nesting_brackets =  0; \
                              nesting_braces =  0;
/*:140*//*141:*/
#line 3151 "weaver-interface-metafont.tex"

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
/*:141*//*454:*/
#line 12849 "weaver-interface-metafont.tex"

#define FLAG_ORIENTATION      32
#define FLAG_COUNTERCLOCKWISE 64
/*:454*/
#line 232 "weaver-interface-metafont.tex"

/*11:*/
#line 314 "weaver-interface-metafont.tex"

enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,


/*15:*/
#line 402 "weaver-interface-metafont.tex"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:15*//*42:*/
#line 1012 "weaver-interface-metafont.tex"

TYPE_END,
TYPE_DUMP,
/*:42*//*54:*/
#line 1295 "weaver-interface-metafont.tex"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:54*//*67:*/
#line 1578 "weaver-interface-metafont.tex"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:67*//*130:*/
#line 2848 "weaver-interface-metafont.tex"

TYPE_ASSIGNMENT,
TYPE_ASSIGNMENT2,
/*:130*//*137:*/
#line 3057 "weaver-interface-metafont.tex"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:137*//*143:*/
#line 3262 "weaver-interface-metafont.tex"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:143*//*147:*/
#line 3389 "weaver-interface-metafont.tex"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:147*//*163:*/
#line 3771 "weaver-interface-metafont.tex"

TYPE_NORMALDEVIATE,
/*:163*//*179:*/
#line 4143 "weaver-interface-metafont.tex"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:179*//*199:*/
#line 4799 "weaver-interface-metafont.tex"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:199*//*206:*/
#line 4970 "weaver-interface-metafont.tex"

TYPE_TRANSFORMED,
/*:206*//*225:*/
#line 5607 "weaver-interface-metafont.tex"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:225*//*238:*/
#line 5866 "weaver-interface-metafont.tex"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,

TYPE_STRAIGHT_JOIN,
/*:238*//*320:*/
#line 8156 "weaver-interface-metafont.tex"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:320*//*337:*/
#line 8723 "weaver-interface-metafont.tex"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:337*//*359:*/
#line 9464 "weaver-interface-metafont.tex"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_MAKEPEN,
/*:359*//*370:*/
#line 9767 "weaver-interface-metafont.tex"

TYPE_MAKEPATH,
/*:370*//*413:*/
#line 11102 "weaver-interface-metafont.tex"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:413*//*425:*/
#line 11513 "weaver-interface-metafont.tex"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:425*//*431:*/
#line 11708 "weaver-interface-metafont.tex"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:431*//*435:*/
#line 11969 "weaver-interface-metafont.tex"

TYPE_OR,
/*:435*//*441:*/
#line 12128 "weaver-interface-metafont.tex"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:441*//*449:*/
#line 12582 "weaver-interface-metafont.tex"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:449*/
#line 319 "weaver-interface-metafont.tex"


TYPE_INVALID_TOKEN
};
struct numeric_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
float value;
};
/*:11*//*12:*/
#line 337 "weaver-interface-metafont.tex"

struct string_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
char value[5];
};
/*:12*//*13:*/
#line 363 "weaver-interface-metafont.tex"

struct symbolic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
void*var;
char*value;
};
/*:13*//*14:*/
#line 387 "weaver-interface-metafont.tex"

struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:14*//*69:*/
#line 1617 "weaver-interface-metafont.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:69*//*70:*/
#line 1637 "weaver-interface-metafont.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:70*//*86:*/
#line 1995 "weaver-interface-metafont.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:86*//*94:*/
#line 2128 "weaver-interface-metafont.tex"

struct pair_variable{
int type;
int nesting_level;
void*next;
float x,y;
};
/*:94*//*96:*/
#line 2175 "weaver-interface-metafont.tex"

struct transform_variable{
int type;
int nesting_level;
void*next;
float value[6];
};
/*:96*//*102:*/
#line 2297 "weaver-interface-metafont.tex"

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
/*:102*//*109:*/
#line 2423 "weaver-interface-metafont.tex"

struct pen_variable{
int type;
int nesting_level;
void*next;
struct path_variable*format;
int flags;
struct pen_variable*referenced;
GLuint gl_vbo;
int number_of_vertices;
float gl_matrix[16];
};
/*:109*//*119:*/
#line 2676 "weaver-interface-metafont.tex"

struct picture_variable{
int type;
int nesting_level;
void*next;
int width,height;
GLuint texture;
};
/*:119*//*128:*/
#line 2796 "weaver-interface-metafont.tex"

struct boolean_variable{
int type;
int nesting_level;
void*next;
short value;
};
/*:128*/
#line 233 "weaver-interface-metafont.tex"

/*8:*/
#line 252 "weaver-interface-metafont.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:8*//*38:*/
#line 892 "weaver-interface-metafont.tex"

static char*list_of_keywords[]= {
/*43:*/
#line 1022 "weaver-interface-metafont.tex"

"end","dump",
/*:43*//*55:*/
#line 1308 "weaver-interface-metafont.tex"

"begingroup","endgroup","if","fi","beginchar","endchar",
/*:55*//*68:*/
#line 1592 "weaver-interface-metafont.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:68*//*131:*/
#line 2857 "weaver-interface-metafont.tex"

"=",":=",
/*:131*//*138:*/
#line 3072 "weaver-interface-metafont.tex"

"+","-","++","+-+","[","]","{","}",
/*:138*//*144:*/
#line 3269 "weaver-interface-metafont.tex"

"*","/",
/*:144*//*148:*/
#line 3402 "weaver-interface-metafont.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:148*//*164:*/
#line 3777 "weaver-interface-metafont.tex"

"normaldeviate",
/*:164*//*180:*/
#line 4155 "weaver-interface-metafont.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:180*//*200:*/
#line 4809 "weaver-interface-metafont.tex"

"xpart","ypart","angle",
/*:200*//*207:*/
#line 4978 "weaver-interface-metafont.tex"

"transformed",
/*:207*//*226:*/
#line 5618 "weaver-interface-metafont.tex"

"xxpart","xypart","yxpart","yypart",
/*:226*//*239:*/
#line 5884 "weaver-interface-metafont.tex"

"cycle","&","..","tension","and","atleast","controls","curl","--",
/*:239*//*321:*/
#line 8167 "weaver-interface-metafont.tex"

"reverse","subpath","of",
/*:321*//*338:*/
#line 8733 "weaver-interface-metafont.tex"

"point","precontrol","postcontrol",
/*:338*//*360:*/
#line 9475 "weaver-interface-metafont.tex"

"nullpen","pencircle","makepen",
/*:360*//*371:*/
#line 9775 "weaver-interface-metafont.tex"

"makepath",
/*:371*//*414:*/
#line 11111 "weaver-interface-metafont.tex"

"nullpicture","subpicture",
/*:414*//*426:*/
#line 11523 "weaver-interface-metafont.tex"

"totalweight","width","height",
/*:426*//*432:*/
#line 11720 "weaver-interface-metafont.tex"

"<","<=",">",">=","<>",
/*:432*//*436:*/
#line 11977 "weaver-interface-metafont.tex"

"or",
/*:436*//*442:*/
#line 12140 "weaver-interface-metafont.tex"

"true","false","odd","not",
/*:442*//*450:*/
#line 12592 "weaver-interface-metafont.tex"

"elseif","else",":",
/*:450*/
#line 894 "weaver-interface-metafont.tex"

NULL};
/*:38*//*379:*/
#line 10032 "weaver-interface-metafont.tex"

const static float square[20]= {
-1.0,-1.0,
0.0,0.0,
1.0,-1.0,
1.0,0.0,
1.0,1.0,
1.0,1.0,
-1.0,1.0,
0.0,1.0};
static GLuint vbo;
/*:379*//*382:*/
#line 10087 "weaver-interface-metafont.tex"

static const char vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat4 model_view_matrix;\n"
"varying highp vec2 texture_coordinate;\n"
"void main(){\n"
"  gl_Position = vec4(vertex_data.xy, 0.0, 1.0) * model_view_matrix;\n"
"  texture_coordinate = vertex_data.zw;\n"
"}\n";
/*:382*//*383:*/
#line 10104 "weaver-interface-metafont.tex"

static const char fragment_shader[]= 
"#version 100\n"
"precision mediump float;\n"
"varying mediump vec2 texture_coordinate;\n"
"uniform sampler2D texture1;\n"
"void main(){\n"
"  gl_FragColor = texture2D(texture1, texture_coordinate);"
"}\n";
static GLuint program;
GLint uniform_matrix;
GLint uniform_texture;
/*:383*//*396:*/
#line 10472 "weaver-interface-metafont.tex"

static const char fragment_shader_inverse[]= 
"#version 100\n"
"precision mediump float;\n"
"varying mediump vec2 texture_coordinate;\n"
"uniform sampler2D texture1;\n"
"void main(){\n"
"  vec4 texture = texture2D(texture1, texture_coordinate);\n"
"  gl_FragColor = vec4(1.0 - texture.r, 1.0 - texture.g, 1.0 - texture.b, \n"
"                      texture.a);\n"
"}\n";
static GLuint inv_program;
static GLint uniform_inv_texture;
static GLint uniform_inv_matrix;
/*:396*/
#line 234 "weaver-interface-metafont.tex"

/*48:*/
#line 1097 "weaver-interface-metafont.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:48*//*52:*/
#line 1204 "weaver-interface-metafont.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:52*//*56:*/
#line 1317 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:56*//*61:*/
#line 1401 "weaver-interface-metafont.tex"

bool begin_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
/*:61*//*80:*/
#line 1824 "weaver-interface-metafont.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:80*//*82:*/
#line 1893 "weaver-interface-metafont.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:82*//*84:*/
#line 1954 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:84*//*106:*/
#line 2380 "weaver-interface-metafont.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer);
/*:106*//*135:*/
#line 2993 "weaver-interface-metafont.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source);

/*:135*//*139:*/
#line 3082 "weaver-interface-metafont.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:139*//*145:*/
#line 3280 "weaver-interface-metafont.tex"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:145*//*149:*/
#line 3410 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:149*//*165:*/
#line 3788 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:165*//*175:*/
#line 4026 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source);
/*:175*//*177:*/
#line 4063 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result);
/*:177*//*181:*/
#line 4164 "weaver-interface-metafont.tex"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:181*//*192:*/
#line 4496 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:192*//*208:*/
#line 4995 "weaver-interface-metafont.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:208*//*210:*/
#line 5020 "weaver-interface-metafont.tex"

bool eval_transform_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:210*//*220:*/
#line 5449 "weaver-interface-metafont.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:220*//*232:*/
#line 5736 "weaver-interface-metafont.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source);
/*:232*//*234:*/
#line 5773 "weaver-interface-metafont.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target);
/*:234*//*236:*/
#line 5809 "weaver-interface-metafont.tex"

void recursive_aux_copy(struct path_points**dst,struct path_variable*origin);
/*:236*//*240:*/
#line 5899 "weaver-interface-metafont.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:240*//*242:*/
#line 5942 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:242*//*257:*/
#line 6388 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y);
/*:257*//*284:*/
#line 7280 "weaver-interface-metafont.tex"

double compute_f(double theta,double phi);
/*:284*//*288:*/
#line 7342 "weaver-interface-metafont.tex"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y);
/*:288*//*290:*/
#line 7380 "weaver-interface-metafont.tex"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y);
/*:290*//*296:*/
#line 7583 "weaver-interface-metafont.tex"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:296*//*298:*/
#line 7675 "weaver-interface-metafont.tex"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:298*//*301:*/
#line 7813 "weaver-interface-metafont.tex"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta);
/*:301*//*304:*/
#line 7865 "weaver-interface-metafont.tex"

void path_xyscale(struct path_variable*p,float x,float y);
/*:304*//*307:*/
#line 7916 "weaver-interface-metafont.tex"

void path_shift(struct path_variable*p,float x,float y);
/*:307*//*310:*/
#line 7961 "weaver-interface-metafont.tex"

void path_slant(struct path_variable*p,float s);
/*:310*//*315:*/
#line 8044 "weaver-interface-metafont.tex"

void path_zscale(struct path_variable*p,float x,float y);
/*:315*//*318:*/
#line 8103 "weaver-interface-metafont.tex"

void path_transform(struct path_variable*p,float x,float y,float xx,
float xy,float yx,float yy);
/*:318*//*322:*/
#line 8183 "weaver-interface-metafont.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:322*//*326:*/
#line 8322 "weaver-interface-metafont.tex"

void reverse_path(struct path_variable*src,struct path_variable*dst);
/*:326*//*329:*/
#line 8493 "weaver-interface-metafont.tex"

void copy_subpath(struct path_points*dst,struct path_variable*src,int offset,int size);
/*:329*//*331:*/
#line 8523 "weaver-interface-metafont.tex"

int recursive_copy_subpath(struct path_points**dst,
struct path_variable*pointer,
int*index,int*offset,int*size);
/*:331*//*339:*/
#line 8749 "weaver-interface-metafont.tex"

struct path_points*get_point(struct path_variable*v,int n);
/*:339*//*341:*/
#line 8779 "weaver-interface-metafont.tex"

struct path_points*_get_point(struct path_variable*v,int n,int*count);
/*:341*//*345:*/
#line 8935 "weaver-interface-metafont.tex"

void assign_pen_variable(struct metafont*mf,
struct pen_variable*target,
struct pen_variable*source);
/*:345*//*347:*/
#line 8989 "weaver-interface-metafont.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:347*//*349:*/
#line 9035 "weaver-interface-metafont.tex"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:349*//*361:*/
#line 9483 "weaver-interface-metafont.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result);
/*:361*//*368:*/
#line 9674 "weaver-interface-metafont.tex"

int read_flags(struct path_variable*path);
/*:368*//*384:*/
#line 10123 "weaver-interface-metafont.tex"

GLuint compile_shader_program(const char*vertex_shader_source,
const char*fragment_shader_source);
/*:384*//*388:*/
#line 10208 "weaver-interface-metafont.tex"

bool get_new_framebuffer(GLuint*new_framebuffer,GLuint*new_texture,
int width,int height);
/*:388*//*390:*/
#line 10248 "weaver-interface-metafont.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height,bool clear_background);

void print_picture(struct picture_variable*pic);
/*:390*//*392:*/
#line 10310 "weaver-interface-metafont.tex"

void assign_picture_variable(struct metafont*mf,
struct picture_variable*target,
struct picture_variable*source);
/*:392*//*394:*/
#line 10364 "weaver-interface-metafont.tex"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result);
/*:394*//*401:*/
#line 10645 "weaver-interface-metafont.tex"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result,
float*matrix,bool*modified);
/*:401*//*411:*/
#line 10981 "weaver-interface-metafont.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*origin,
float*matrix);
/*:411*//*415:*/
#line 11119 "weaver-interface-metafont.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result);
/*:415*//*433:*/
#line 11728 "weaver-interface-metafont.tex"

bool eval_boolean_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct boolean_variable*result);
/*:433*//*437:*/
#line 11985 "weaver-interface-metafont.tex"

bool eval_boolean_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result);
/*:437*//*439:*/
#line 12054 "weaver-interface-metafont.tex"

bool eval_boolean_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result);
/*:439*//*443:*/
#line 12148 "weaver-interface-metafont.tex"

bool eval_boolean_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result);
/*:443*//*445:*/
#line 12285 "weaver-interface-metafont.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_secondary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_tertiary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:445*//*455:*/
#line 12864 "weaver-interface-metafont.tex"

bool is_pen_counterclockwise(struct pen_variable*pen);
/*:455*//*457:*/
#line 12921 "weaver-interface-metafont.tex"

bool triangulate_pen(struct pen_variable*pen);
/*:457*/
#line 235 "weaver-interface-metafont.tex"

/*16:*/
#line 421 "weaver-interface-metafont.tex"

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
/*:16*//*17:*/
#line 444 "weaver-interface-metafont.tex"

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
/*19:*/
#line 496 "weaver-interface-metafont.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:19*/
#line 461 "weaver-interface-metafont.tex"

/*21:*/
#line 517 "weaver-interface-metafont.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:21*/
#line 462 "weaver-interface-metafont.tex"

/*22:*/
#line 534 "weaver-interface-metafont.tex"

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
/*:22*/
#line 463 "weaver-interface-metafont.tex"

/*23:*/
#line 582 "weaver-interface-metafont.tex"

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
/*:23*/
#line 464 "weaver-interface-metafont.tex"

/*24:*/
#line 627 "weaver-interface-metafont.tex"

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
/*:24*/
#line 465 "weaver-interface-metafont.tex"

/*25:*/
#line 662 "weaver-interface-metafont.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*26:*/
#line 695 "weaver-interface-metafont.tex"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_'||isdigit(c));
ungetc(c,fp);
buffer[i]= '\0';
}
/*:26*/
#line 668 "weaver-interface-metafont.tex"

/*27:*/
#line 712 "weaver-interface-metafont.tex"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:27*/
#line 669 "weaver-interface-metafont.tex"

/*28:*/
#line 728 "weaver-interface-metafont.tex"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:28*/
#line 670 "weaver-interface-metafont.tex"

/*29:*/
#line 744 "weaver-interface-metafont.tex"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:29*/
#line 671 "weaver-interface-metafont.tex"

/*30:*/
#line 760 "weaver-interface-metafont.tex"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:30*/
#line 672 "weaver-interface-metafont.tex"

/*31:*/
#line 776 "weaver-interface-metafont.tex"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:31*/
#line 673 "weaver-interface-metafont.tex"

/*32:*/
#line 792 "weaver-interface-metafont.tex"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:32*/
#line 674 "weaver-interface-metafont.tex"

/*33:*/
#line 808 "weaver-interface-metafont.tex"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:33*/
#line 675 "weaver-interface-metafont.tex"

/*34:*/
#line 824 "weaver-interface-metafont.tex"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:34*/
#line 676 "weaver-interface-metafont.tex"

/*35:*/
#line 840 "weaver-interface-metafont.tex"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:35*/
#line 677 "weaver-interface-metafont.tex"

/*36:*/
#line 856 "weaver-interface-metafont.tex"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:36*/
#line 678 "weaver-interface-metafont.tex"

/*37:*/
#line 872 "weaver-interface-metafont.tex"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:37*/
#line 679 "weaver-interface-metafont.tex"


/*39:*/
#line 905 "weaver-interface-metafont.tex"

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
/*44:*/
#line 1032 "weaver-interface-metafont.tex"

if(token_type==TYPE_DUMP)
token_type= TYPE_END;
/*:44*//*132:*/
#line 2866 "weaver-interface-metafont.tex"

else if(token_type==TYPE_ASSIGNMENT2)
token_type= TYPE_ASSIGNMENT;
/*:132*/
#line 918 "weaver-interface-metafont.tex"

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
/*:39*/
#line 681 "weaver-interface-metafont.tex"

/*41:*/
#line 949 "weaver-interface-metafont.tex"

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
/*93:*/
#line 2103 "weaver-interface-metafont.tex"

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
/*:93*//*101:*/
#line 2250 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"identity"))
new_token->var= 
&(mf->internal_transform_variables[INTERNAL_TRANSFORM_IDENTITY]);
/*:101*//*118:*/
#line 2656 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"currentpen"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN]);
else if(!strcmp(buffer,"pensquare"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_PENSQUARE]);
/*:118*//*127:*/
#line 2783 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"currentpicture"))
new_token->var= 
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE]);
/*:127*/
#line 962 "weaver-interface-metafont.tex"

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
/*:41*/
#line 682 "weaver-interface-metafont.tex"

}
/*:25*/
#line 466 "weaver-interface-metafont.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
fclose(fp);
return first_token;
}
/*:17*//*45:*/
#line 1046 "weaver-interface-metafont.tex"

bool eval_program(struct metafont*mf,struct context*cx,
void*token_list){
struct generic_token*end= (struct generic_token*)token_list;
while(end!=NULL&&end->type!=TYPE_END)
end= (struct generic_token*)(end->next);
if(end==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s: Program not finished with "
"'end' or 'dump'.\n",mf->file);
#endif
return false;
}
if(end==token_list)
return true;
return eval_list_of_statements(mf,cx,token_list,end);
}
/*:45*//*49:*/
#line 1113 "weaver-interface-metafont.tex"

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
/*72:*/
#line 1659 "weaver-interface-metafont.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:72*//*90:*/
#line 2052 "weaver-interface-metafont.tex"

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
/*:90*//*99:*/
#line 2216 "weaver-interface-metafont.tex"

mf->internal_transform_variables= 
(struct transform_variable*)
mf->alloc(sizeof(struct transform_variable));
if(mf->internal_transform_variables==NULL){
if(disalloc!=NULL)
disalloc(mf);
return NULL;
}

mf->internal_transform_variables[0].type= TYPE_T_TRANSFORM;
mf->internal_transform_variables[0].value[0]= 0.0;
mf->internal_transform_variables[0].value[1]= 0.0;
mf->internal_transform_variables[0].value[2]= 1.0;
mf->internal_transform_variables[0].value[3]= 0.0;
mf->internal_transform_variables[0].value[4]= 0.0;
mf->internal_transform_variables[0].value[5]= 1.0;
/*:99*//*115:*/
#line 2594 "weaver-interface-metafont.tex"

mf->internal_pen_variables= (struct pen_variable*)
mf->alloc(2*sizeof(struct pen_variable));
if(mf->internal_pen_variables==NULL){
if(disalloc!=NULL)
disalloc(mf);
return NULL;
}
mf->internal_pen_variables[0].format= NULL;
mf->internal_pen_variables[0].type= TYPE_T_PEN;
mf->internal_pen_variables[0].flags= FLAG_CONVEX|FLAG_CIRCULAR;
mf->internal_pen_variables[0].referenced= NULL;
mf->internal_pen_variables[0].gl_vbo= 0;
mf->internal_pen_variables[0].number_of_vertices= 0;
mf->internal_pen_variables[1].format= NULL;
mf->internal_pen_variables[1].type= TYPE_T_PEN;
mf->internal_pen_variables[1].flags= FLAG_CONVEX|FLAG_STRAIGHT|
FLAG_SQUARE;
mf->internal_pen_variables[1].referenced= NULL;
mf->internal_pen_variables[1].gl_vbo= 0;
mf->internal_pen_variables[1].number_of_vertices= 0;
{
int i,j;
for(j= 0;j<2;j++)
for(i= 0;i<16;i++)
if(i%5==0)
mf->internal_pen_variables[j].gl_matrix[i]= 1.0;
else
mf->internal_pen_variables[j].gl_matrix[i]= 0.0;
}
/*:115*//*124:*/
#line 2740 "weaver-interface-metafont.tex"

mf->internal_picture_variables= (struct picture_variable*)
mf->alloc(sizeof(struct picture_variable));
if(mf->internal_picture_variables==NULL){
if(disalloc!=NULL)
disalloc(mf);
return NULL;
}

mf->internal_picture_variables[0].type= TYPE_T_PICTURE;
mf->internal_picture_variables[0].width= -1;
mf->internal_picture_variables[0].height= -1;
mf->internal_picture_variables[0].texture= 0;
/*:124*//*170:*/
#line 3912 "weaver-interface-metafont.tex"

mf->have_stored_normaldeviate= false;
/*:170*/
#line 1124 "weaver-interface-metafont.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*60:*/
#line 1384 "weaver-interface-metafont.tex"

cx->nesting_level= 0;
cx->end_token_stack= NULL;
/*:60*//*76:*/
#line 1720 "weaver-interface-metafont.tex"

cx->variables= NULL;
/*:76*/
#line 1130 "weaver-interface-metafont.tex"

return cx;
}
/*:49*//*50:*/
#line 1139 "weaver-interface-metafont.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*73:*/
#line 1671 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*104:*/
#line 2350 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:104*//*112:*/
#line 2543 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:112*//*121:*/
#line 2704 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:121*/
#line 1677 "weaver-interface-metafont.tex"

mf->free(v);
v= next;
}
}
/*:73*//*74:*/
#line 1689 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)(named->var);
next= (struct named_variable*)(named->next);
mf->free(named->name);
/*104:*/
#line 2350 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:104*//*112:*/
#line 2543 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:112*//*121:*/
#line 2704 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:121*/
#line 1698 "weaver-interface-metafont.tex"

mf->free(v);
mf->free(named);
named= next;
}
}
/*:74*//*92:*/
#line 2091 "weaver-interface-metafont.tex"

if(mf->free!=NULL)
mf->free(mf->internal_numeric_variables);
/*:92*//*117:*/
#line 2641 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
if(mf->internal_pen_variables[1].format!=NULL){
mf->free(mf->internal_pen_variables[1].format->points);
mf->free(mf->internal_pen_variables[1].format);
}
mf->free(mf->internal_pen_variables);
}
/*:117*//*126:*/
#line 2770 "weaver-interface-metafont.tex"

if(mf->internal_picture_variables[0].texture!=0)
glDeleteTextures(1,&(mf->internal_picture_variables[0].texture));
if(mf->free!=NULL)
mf->free(mf->internal_picture_variables);
/*:126*/
#line 1143 "weaver-interface-metafont.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*77:*/
#line 1728 "weaver-interface-metafont.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*105:*/
#line 2364 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL)
path_recursive_free(temporary_free,path,false);
}
/*:105*//*113:*/
#line 2560 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&temporary_free!=NULL)
path_recursive_free(temporary_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:113*//*122:*/
#line 2716 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:122*/
#line 1734 "weaver-interface-metafont.tex"

temporary_free(v);
v= next;
}
}
/*:77*/
#line 1149 "weaver-interface-metafont.tex"

temporary_free(cx);
}
}
/*:50*//*53:*/
#line 1217 "weaver-interface-metafont.tex"

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
/*:53*//*57:*/
#line 1323 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*58:*/
#line 1351 "weaver-interface-metafont.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:58*/
#line 1326 "weaver-interface-metafont.tex"

/*64:*/
#line 1511 "weaver-interface-metafont.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_BEGINGROUP){
begin_nesting_level(mf,cx,begin_token_list);
*end_token_list= begin_token_list;
return true;
}
/*:64*//*65:*/
#line 1526 "weaver-interface-metafont.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_ENDGROUP){
if(!end_nesting_level(mf,cx,begin_token_list))
return false;
*end_token_list= begin_token_list;
return true;
}
/*:65*//*66:*/
#line 1543 "weaver-interface-metafont.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_END){
if(cx->nesting_level> 0){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s: Program ending with unclosed "
"compound statement.\n",mf->file);
#endif
return false;
}
return true;
}
/*:66*//*451:*/
#line 12652 "weaver-interface-metafont.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_IF){
struct generic_token*begin_bool,*end_bool;
struct boolean_variable b;
int current_nesting_level;

begin_nesting_level(mf,cx,begin_token_list);
current_nesting_level= cx->nesting_level;

begin_bool= ((struct generic_token*)begin_token_list)->next;
end_bool= begin_bool;
while(end_bool!=*end_token_list&&
((struct generic_token*)(end_bool->next))->type!=TYPE_COLON)
end_bool= end_bool->next;
if(end_bool==*end_token_list){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Error delimiting boolean "
"condition.\n",mf->file,end_bool->line);
#endif
return false;
}

if(!eval_boolean_expression(mf,cx,begin_bool,end_bool,&b))
return false;
if(b.value==1){
*end_token_list= end_bool->next;
return true;
}
else{
struct generic_token*t= end_bool->next;
while(t->next!=NULL){
if(t->type==TYPE_FI&&cx->nesting_level==current_nesting_level){

if(!end_nesting_level(mf,cx,t))
return false;
*end_token_list= t;
return true;
}
else if(t->type==TYPE_ELSE&&
cx->nesting_level==current_nesting_level){

*end_token_list= t->next;
if(((struct generic_token*)*end_token_list)->type!=TYPE_COLON){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Expected ':' after "
"'else'.\n",mf->file,
((struct generic_token*)*end_token_list)->line);
#endif
return false;
}
return true;
}
else if(t->type==TYPE_ELSEIF&&
cx->nesting_level==current_nesting_level){

begin_bool= t->next;
end_bool= begin_bool;
while(end_bool!=*end_token_list&&
((struct generic_token*)
(end_bool->next))->type!=TYPE_COLON)
end_bool= end_bool->next;
if(!eval_boolean_expression(mf,cx,begin_bool,end_bool,&b))
return false;
if(b.value==1){
*end_token_list= end_bool->next;
return true;
}
}

else if(t->type==TYPE_IF||t->type==TYPE_BEGINGROUP||
t->type==TYPE_BEGINCHAR)
begin_nesting_level(mf,cx,t);
else if(t->type==TYPE_FI||t->type==TYPE_ENDGROUP||
t->type==TYPE_ENDCHAR)
if(!end_nesting_level(mf,cx,t))
return false;
t= t->next;
}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Not found corresponding 'fi' "
"for 'if' statement.\n",mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:451*//*452:*/
#line 12756 "weaver-interface-metafont.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_ELSEIF||
((struct generic_token*)begin_token_list)->type==
TYPE_ELSE){
int current_nesting_level;
struct generic_token*t;
if(cx->end_token_stack==NULL||
cx->end_token_stack->type!=TYPE_FI){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Token 'elseif' or 'else' should "
"have a corresponding 'if'.\n",mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
current_nesting_level= cx->nesting_level;
t= begin_token_list;
while(t!=NULL){
if(t->type==TYPE_FI&&cx->nesting_level==current_nesting_level){

if(!end_nesting_level(mf,cx,t))
return false;
*end_token_list= t;
return true;
}
else if(t->type==TYPE_IF||t->type==TYPE_BEGINGROUP||
t->type==TYPE_BEGINCHAR)
begin_nesting_level(mf,cx,t);
else if(t->type==TYPE_FI||t->type==TYPE_ENDGROUP||
t->type==TYPE_ENDCHAR)
if(!end_nesting_level(mf,cx,t))
return false;
t= t->next;
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Not found corresponding 'fi' "
"for 'else' or 'elseif' statement.\n",mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:452*//*453:*/
#line 12807 "weaver-interface-metafont.tex"

else if(((struct generic_token*)begin_token_list)->type==TYPE_FI){
if(!end_nesting_level(mf,cx,begin_token_list))
return false;
*end_token_list= begin_token_list;
return true;
}
/*:453*/
#line 1327 "weaver-interface-metafont.tex"

/*78:*/
#line 1745 "weaver-interface-metafont.tex"

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
/*79:*/
#line 1795 "weaver-interface-metafont.tex"

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
/*:79*/
#line 1762 "weaver-interface-metafont.tex"

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
/*:78*/
#line 1328 "weaver-interface-metafont.tex"

/*133:*/
#line 2890 "weaver-interface-metafont.tex"

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
"token in left side of assignment (type: %d).\n",
mf->file,
var->line,var->type);
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
/*134:*/
#line 2969 "weaver-interface-metafont.tex"

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
/*:134*/
#line 2951 "weaver-interface-metafont.tex"

/*174:*/
#line 4005 "weaver-interface-metafont.tex"

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
/*:174*/
#line 2952 "weaver-interface-metafont.tex"

/*205:*/
#line 4924 "weaver-interface-metafont.tex"

else if(type==TYPE_T_TRANSFORM){
int i;
struct transform_variable result;
if(!eval_transform_expression(mf,cx,begin_expression,
(struct generic_token*)*end_token_list,
&result))
return false;
var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
memcpy(((struct transform_variable*)var->var)->value,result.value,
sizeof(float)*6);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:205*/
#line 2953 "weaver-interface-metafont.tex"

/*231:*/
#line 5712 "weaver-interface-metafont.tex"

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
/*:231*/
#line 2954 "weaver-interface-metafont.tex"

/*344:*/
#line 8908 "weaver-interface-metafont.tex"

else if(type==TYPE_T_PEN){
int i;
struct pen_variable result;
if(!eval_pen_expression(mf,cx,begin_expression,
(struct generic_token*)*end_token_list,
&result))
return false;
var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
assign_pen_variable(mf,(struct pen_variable*)var->var,
&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
if(temporary_free!=NULL&&result.format!=NULL&&
result.referenced==NULL)
path_recursive_free(temporary_free,result.format,true);
if(result.gl_vbo!=0&&result.referenced==NULL)
glDeleteBuffers(1,&(result.gl_vbo));
}
/*:344*/
#line 2955 "weaver-interface-metafont.tex"

/*378:*/
#line 9991 "weaver-interface-metafont.tex"

else if(type==TYPE_T_PICTURE){
int i;
struct picture_variable result;
if(!eval_picture_expression(mf,cx,begin_expression,
(struct generic_token*)*end_token_list,
&result))
return false;
var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
if(i==0){
struct picture_variable*pic= (struct picture_variable*)var->var;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
memcpy(pic,&result,sizeof(struct picture_variable));
pic->type= TYPE_T_PICTURE;
}
else
assign_picture_variable(mf,(struct picture_variable*)var->var,
&result);


var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}

}
/*:378*/
#line 2956 "weaver-interface-metafont.tex"

/*430:*/
#line 11657 "weaver-interface-metafont.tex"

else if(type==TYPE_T_BOOLEAN){
int i;
bool ret;
struct boolean_variable result;
ret= eval_boolean_expression(mf,cx,begin_expression,
(struct generic_token*)*end_token_list,
&result);
if(!ret)
return false;
var= (struct symbolic_token*)begin_token_list;
for(i= 0;i<number_of_variables;i++){
((struct boolean_variable*)var->var)->value= result.value;
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:430*/
#line 2957 "weaver-interface-metafont.tex"

return true;
}
/*:133*/
#line 1329 "weaver-interface-metafont.tex"




#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement (%s).\n",
mf->file,
((struct generic_token*)begin_token_list)->line,
list_of_keywords[((struct generic_token*)begin_token_list)->type-8]);
#endif
return false;
}
/*:57*//*62:*/
#line 1412 "weaver-interface-metafont.tex"

bool begin_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok){
struct generic_token*end_token;
end_token= (struct generic_token*)
temporary_alloc(sizeof(struct generic_token));
if(end_token==NULL){
fprintf(stderr,"ERROR: No memory.");
return false;
}
switch(tok->type){
case TYPE_BEGINGROUP:
end_token->type= TYPE_ENDGROUP;
break;
case TYPE_IF:
end_token->type= TYPE_FI;
break;
case TYPE_BEGINCHAR:
end_token->type= TYPE_ENDCHAR;
break;
default:
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Invalid token beginning"
" compound statement.\n",mf->file,
((struct generic_token*)tok)->line);
#endif
return false;
}
cx->nesting_level++;
end_token->next= cx->end_token_stack;
cx->end_token_stack= end_token;
return true;
}
/*:62*//*63:*/
#line 1452 "weaver-interface-metafont.tex"

bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok){
struct generic_token*end_tok= cx->end_token_stack;
if(end_tok==NULL||end_tok->type!=tok->type){
#if defined(W_DEBUG_METAFONT)
printf("DEBUG: end_tok: %p\n",end_tok);
fprintf(stderr,
"METAFONT: Error: %s:%d: Invalid token ending"
" compound statement.\n",mf->file,
((struct generic_token*)tok)->line);
#endif
return false;
}
cx->nesting_level--;
cx->end_token_stack= end_tok->next;
if(temporary_free!=NULL)
temporary_free(end_tok);
return true;
}
/*:63*//*81:*/
#line 1837 "weaver-interface-metafont.tex"

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
case TYPE_T_PEN:
var_size= sizeof(struct pen_variable);
break;
case TYPE_T_PICTURE:
var_size= sizeof(struct picture_variable);
break;
case TYPE_T_TRANSFORM:
var_size= sizeof(struct transform_variable);
break;
case TYPE_T_BOOLEAN:
var_size= sizeof(struct boolean_variable);
break;
default:
var_size= sizeof(struct variable);
}
var= (struct variable*)alloc(var_size);
if(var!=NULL){
var->type= type;
var->next= NULL;
var->nesting_level= nesting_level;
/*87:*/
#line 2012 "weaver-interface-metafont.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:87*//*95:*/
#line 2143 "weaver-interface-metafont.tex"

if(type==TYPE_T_PAIR){
((struct pair_variable*)var)->x= NAN;
}
/*:95*//*97:*/
#line 2189 "weaver-interface-metafont.tex"

if(type==TYPE_T_TRANSFORM)
((struct transform_variable*)var)->value[0]= NAN;
/*:97*//*103:*/
#line 2338 "weaver-interface-metafont.tex"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
((struct path_variable*)var)->points= NULL;
}
/*:103*//*111:*/
#line 2528 "weaver-interface-metafont.tex"

if(type==TYPE_T_PEN){
((struct pen_variable*)var)->format= NULL;
((struct pen_variable*)var)->gl_vbo= 0;
((struct pen_variable*)var)->flags= false;
((struct pen_variable*)var)->referenced= NULL;
}
/*:111*//*120:*/
#line 2691 "weaver-interface-metafont.tex"

if(type==TYPE_T_PICTURE){
((struct picture_variable*)var)->width= -1;
((struct picture_variable*)var)->height= -1;
((struct picture_variable*)var)->texture= 0;
}
/*:120*//*129:*/
#line 2811 "weaver-interface-metafont.tex"

if(type==TYPE_T_BOOLEAN)
((struct boolean_variable*)var)->value= -1;
/*:129*/
#line 1875 "weaver-interface-metafont.tex"

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
/*:81*//*83:*/
#line 1904 "weaver-interface-metafont.tex"

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
if(mf->named_variables==NULL){
mf->named_variables= named;
}
else{
struct named_variable*p= (struct named_variable*)
mf->named_variables;
while(p->next!=NULL)
p= (struct named_variable*)p->next;
p->next= named;
}
return new_var;
}
/*:83*//*85:*/
#line 1967 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer){
struct symbolic_token*p= var_token->next;
int nesting_level= 0;
while(p!=NULL&&nesting_level>=0){
if(p->type==TYPE_BEGINGROUP||p->type==TYPE_IF||
p->type==TYPE_BEGINCHAR)
nesting_level++;
else if(p->type==TYPE_ENDGROUP||p->type==TYPE_FI||
p->type==TYPE_ENDCHAR)
nesting_level--;
else if(p->type==TYPE_SYMBOLIC){
if(!strcmp(p->value,var_token->value)){
p->var= var_pointer;
}
}
p= (struct symbolic_token*)(p->next);
}
}
/*:85*//*107:*/
#line 2390 "weaver-interface-metafont.tex"

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
/*:107*//*136:*/
#line 3003 "weaver-interface-metafont.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source){
target->value= source->value;
}
/*:136*//*142:*/
#line 3190 "weaver-interface-metafont.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secondary,
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
begin_secondary= (struct generic_token*)(last_sum->next);
eval_numeric_expression(mf,cx,begin_expression,end_tertiary,&a);
eval_numeric_secondary(mf,cx,begin_secondary,end_token_list,&b);
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
return eval_numeric_secondary(mf,cx,begin_expression,
end_token_list,result);
}
/*:142*//*146:*/
#line 3303 "weaver-interface-metafont.tex"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result){
struct generic_token*end_secondary= NULL,*begin_primary,
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
end_secondary= prev;
}
}
prev_prev= prev;
prev= p;
if(p!=end_token_list)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(end_secondary!=NULL){
begin_primary= (struct generic_token*)(last_mul->next);
eval_numeric_secondary(mf,cx,begin_expression,end_secondary,&a);
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
/*:146*//*150:*/
#line 3422 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*151:*/
#line 3448 "weaver-interface-metafont.tex"

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
/*:151*/
#line 3427 "weaver-interface-metafont.tex"

/*152:*/
#line 3472 "weaver-interface-metafont.tex"

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
/*201:*/
#line 4820 "weaver-interface-metafont.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)hypot(p.x*p.x,p.y*p.y);
return true;
}
/*:201*//*336:*/
#line 8693 "weaver-interface-metafont.tex"

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
/*:336*/
#line 3489 "weaver-interface-metafont.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:152*/
#line 3428 "weaver-interface-metafont.tex"

/*153:*/
#line 3515 "weaver-interface-metafont.tex"

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
/*:153*//*154:*/
#line 3543 "weaver-interface-metafont.tex"

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
/*:154*//*155:*/
#line 3562 "weaver-interface-metafont.tex"

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
/*:155*//*156:*/
#line 3581 "weaver-interface-metafont.tex"

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
/*:156*//*157:*/
#line 3607 "weaver-interface-metafont.tex"

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
/*:157*//*158:*/
#line 3625 "weaver-interface-metafont.tex"

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
/*:158*//*159:*/
#line 3656 "weaver-interface-metafont.tex"

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
/*:159*//*160:*/
#line 3679 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:160*//*161:*/
#line 3696 "weaver-interface-metafont.tex"

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
/*:161*/
#line 3429 "weaver-interface-metafont.tex"

/*202:*/
#line 4840 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_XPART){
struct pair_variable p;
int expr_type= get_primary_expression_type(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression);
if(expr_type==TYPE_T_PAIR){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.x;
return true;
}
else{
/*228:*/
#line 5648 "weaver-interface-metafont.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&t))
return false;
result->value= t.value[0];
return true;
/*:228*/
#line 4855 "weaver-interface-metafont.tex"

}
}
/*:202*//*203:*/
#line 4866 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_YPART){
struct pair_variable p;
int expr_type= get_primary_expression_type(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression);
if(expr_type==TYPE_T_PAIR){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.y;
return true;
}
else{
/*229:*/
#line 5662 "weaver-interface-metafont.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&t))
return false;
result->value= t.value[1];
return true;
/*:229*/
#line 4881 "weaver-interface-metafont.tex"

}
}
/*:203*//*204:*/
#line 4893 "weaver-interface-metafont.tex"

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
/*:204*//*227:*/
#line 5627 "weaver-interface-metafont.tex"

else if(begin_expression->type>=TYPE_XXPART&&
begin_expression->type<=TYPE_YYPART){
struct transform_variable t;
if(!eval_transform_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&t))
return false;
result->value= t.value[2+begin_expression->type-TYPE_XXPART];
return true;
}
/*:227*//*427:*/
#line 11533 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_TOTALWEIGHT){
struct picture_variable p;
char*data;
GLuint temporary_framebuffer= 0;
GLuint temporary_texture= 0;
float identity_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing picture expression after "
"'totalweight'.\n",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_picture_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
data= temporary_alloc(p.width*p.height*4);
if(data==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s: Not enough memory!\n",mf->file);
#endif
return false;
}
get_new_framebuffer(&temporary_framebuffer,&(temporary_texture),
p.width,p.height);

render_picture(&p,identity_matrix,p.width,p.height,true);

glReadPixels(0,0,p.width,p.height,GL_RGBA,GL_UNSIGNED_BYTE,data);
{

int i,size= p.width*p.height*4;
double sum= 0.0;
for(i= 0;i<size;i+= 4){



if(data[i]==data[i+1]&&data[i+1]==data[i+2]){
sum+= ((255-(unsigned char)data[i])/255.0)*
(((unsigned char)data[i+3])/255.0);
}
else{
double r= ((255-(unsigned char)data[i])/255.0)*0.2989,
g= ((255-(unsigned char)data[i+1])/255.0)*0.5870,
b= ((255-(unsigned char)data[i+2])/255.0)*0.1140,
a= ((unsigned char)data[i+3])/255.0;
sum+= ((r+g+b)*a);
}
}
result->value= sum;
}

if(temporary_free!=NULL)
temporary_free(data);
glDeleteTextures(1,&temporary_texture);
glDeleteTextures(1,&(p.texture));
glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:427*//*428:*/
#line 11606 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_WIDTH){
struct picture_variable p;
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing picture expression after "
"'width'.\n",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_picture_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)p.width;
return true;
}
/*:428*//*429:*/
#line 11629 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_HEIGHT){
struct picture_variable p;
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing picture expression after "
"'height'.\n",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_picture_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)p.height;
return true;
}
/*:429*/
#line 3430 "weaver-interface-metafont.tex"

/*162:*/
#line 3722 "weaver-interface-metafont.tex"

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
/*:162*/
#line 3431 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:150*//*166:*/
#line 3801 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*167:*/
#line 3823 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:167*/
#line 3807 "weaver-interface-metafont.tex"

/*168:*/
#line 3836 "weaver-interface-metafont.tex"

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
/*:168*/
#line 3808 "weaver-interface-metafont.tex"

/*171:*/
#line 3922 "weaver-interface-metafont.tex"

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
/*:171*/
#line 3809 "weaver-interface-metafont.tex"

}
else{
/*172:*/
#line 3957 "weaver-interface-metafont.tex"

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
/*:172*/
#line 3812 "weaver-interface-metafont.tex"

/*173:*/
#line 3986 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC&&
end_expression->type==TYPE_NUMERIC&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION){
result->value= ((struct numeric_token*)begin_expression)->value/
((struct numeric_token*)end_expression)->value;
return true;
}
/*:173*/
#line 3813 "weaver-interface-metafont.tex"

}
return false;
}
/*:166*//*176:*/
#line 4035 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source){
target->x= source->x;
target->y= source->y;
}
/*:176*//*178:*/
#line 4076 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secondary,
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
begin_secondary= (struct generic_token*)(last_sum->next);
eval_pair_expression(mf,cx,begin_expression,end_tertiary,&a);
eval_pair_secondary(mf,cx,begin_secondary,end_token_list,&b);
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
return eval_pair_secondary(mf,cx,begin_expression,
end_token_list,result);
}
/*:178*//*182:*/
#line 4184 "weaver-interface-metafont.tex"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
struct generic_token*end_secondary= NULL,*begin_primary,
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
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED||


p->type==TYPE_TRANSFORMED)){
if(p->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
p!=end_expression&&
((struct generic_token*)p->next)->type!=TYPE_NUMERIC&&
last_fraction!=prev_prev)
last_fraction= p;
else{
last_mul= p;
end_secondary= prev;
}
}
prev_prev= prev;
prev= p;
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(end_secondary!=NULL){
bool ret;
begin_primary= (struct generic_token*)(last_mul->next);
/*183:*/
#line 4255 "weaver-interface-metafont.tex"

if(last_mul->type==TYPE_MULTIPLICATION){
if(get_primary_expression_type(mf,cx,begin_primary,end_expression)==
TYPE_T_PAIR){
struct numeric_variable a;
struct pair_variable b;
ret= eval_numeric_secondary(mf,cx,begin_expression,end_secondary,
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
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,
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
/*:183*/
#line 4224 "weaver-interface-metafont.tex"

/*184:*/
#line 4294 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_DIVISION){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
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
/*:184*/
#line 4225 "weaver-interface-metafont.tex"

/*185:*/
#line 4322 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_ROTATED){
struct pair_variable a;
struct numeric_variable b;
double sin_theta,cos_theta,theta;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
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
/*:185*/
#line 4226 "weaver-interface-metafont.tex"

/*186:*/
#line 4346 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_SCALED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x*b.value;
result->y= a.y*b.value;
return true;
}
/*:186*/
#line 4227 "weaver-interface-metafont.tex"

/*187:*/
#line 4367 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_SHIFTED){
struct pair_variable a,b;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
if(!ret)
return false;
ret= eval_pair_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x+b.x;
result->y= a.y+b.y;
return true;
}
/*:187*/
#line 4228 "weaver-interface-metafont.tex"

/*188:*/
#line 4388 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_SLANTED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x+b.value*a.y;
result->y= a.y;
return true;
}
/*:188*/
#line 4229 "weaver-interface-metafont.tex"

/*189:*/
#line 4409 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_XSCALED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x*b.value;
result->y= a.y;
return true;
}
/*:189*/
#line 4230 "weaver-interface-metafont.tex"

/*190:*/
#line 4430 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_YSCALED){
struct pair_variable a;
struct numeric_variable b;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
if(!ret)
return false;
ret= eval_numeric_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x;
result->y= a.y*b.value;
return true;
}
/*:190*/
#line 4231 "weaver-interface-metafont.tex"

/*191:*/
#line 4455 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_ZSCALED){
struct pair_variable a,b;
ret= eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a);
if(!ret)
return false;
ret= eval_pair_primary(mf,cx,begin_primary,end_expression,&b);
if(!ret)
return false;
result->x= a.x*b.x-a.y*b.y;
result->y= a.x*b.y+b.x*a.y;
return true;
}
/*:191*/
#line 4232 "weaver-interface-metafont.tex"

/*230:*/
#line 5691 "weaver-interface-metafont.tex"

else if(last_mul->type==TYPE_TRANSFORMED){
struct pair_variable a;
struct transform_variable b;
if(!eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a))
return false;
if(!eval_transform_primary(mf,cx,begin_primary,end_expression,&b))
return false;
result->x= b.value[0]+a.x*b.value[2]+a.y*b.value[3];
result->y= b.value[1]+a.x*b.value[4]+a.y*b.value[5];
return true;
}
/*:230*/
#line 4233 "weaver-interface-metafont.tex"

}
else
return eval_pair_primary(mf,cx,begin_expression,
end_expression,result);
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:182*//*193:*/
#line 4509 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
if(begin_expression==end_expression){
/*194:*/
#line 4538 "weaver-interface-metafont.tex"

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
/*:194*/
#line 4515 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*195:*/
#line 4578 "weaver-interface-metafont.tex"

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
/*:195*/
#line 4519 "weaver-interface-metafont.tex"

/*196:*/
#line 4639 "weaver-interface-metafont.tex"

else{
return eval_pair_expression(mf,cx,begin_a,end_a,result);
}
/*:196*/
#line 4520 "weaver-interface-metafont.tex"

}
/*343:*/
#line 8825 "weaver-interface-metafont.tex"

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
index= ((int)(a.value))%(b.total_length-1);
if(begin_expression->type==TYPE_PRECONTROL)
index= (index-1)%(b.total_length-1);
}
else{
index= (int)(a.value);
if(index<0)index= 0;
if(index>=b.total_length)index= b.total_length-1;
if(begin_expression->type==TYPE_PRECONTROL)
index--;
}
if(begin_expression->type==TYPE_POINT){
result->x= get_point(&b,index)->x;
result->y= get_point(&b,index)->y;
}
else if(begin_expression->type==TYPE_PRECONTROL){
if(index<0){
result->x= get_point(&b,0)->x;
result->y= get_point(&b,0)->y;
}
else{
result->x= get_point(&b,index)->v_x;
result->y= get_point(&b,index)->v_y;
}
}
else{
result->x= get_point(&b,index)->u_x;
result->y= get_point(&b,index)->u_y;
}
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&b,false);
return true;
}
/*:343*/
#line 4522 "weaver-interface-metafont.tex"

/*197:*/
#line 4651 "weaver-interface-metafont.tex"

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
/*:197*/
#line 4523 "weaver-interface-metafont.tex"

/*198:*/
#line 4734 "weaver-interface-metafont.tex"

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
/*:198*/
#line 4524 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:193*//*209:*/
#line 5006 "weaver-interface-metafont.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result){
return eval_transform_secondary(mf,cx,begin_expression,end_expression,
result);
}
/*:209*//*211:*/
#line 5038 "weaver-interface-metafont.tex"

bool eval_transform_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result){
struct generic_token*p,*last_transform= NULL,*last_token= NULL,
*end_secondary= NULL;
DECLARE_NESTING_CONTROL();
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&
(p->type==TYPE_ROTATED||p->type==TYPE_SCALED||
p->type==TYPE_SHIFTED||p->type==TYPE_SLANTED||
p->type==TYPE_XSCALED||p->type==TYPE_YSCALED||
p->type==TYPE_ZSCALED||p->type==TYPE_TRANSFORMED)){
last_transform= p;
end_secondary= last_token;
}
last_token= p;
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(last_transform==NULL)
return eval_transform_primary(mf,cx,begin_expression,end_expression,
result);
else{
struct transform_variable a;
if(end_secondary==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Transform expression began "
"with transformer.",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_transform_secondary(mf,cx,begin_expression,end_secondary,&a))
return false;
/*212:*/
#line 5115 "weaver-interface-metafont.tex"

if(last_transform->type==TYPE_ROTATED){
double cos_theta,sin_theta;
struct numeric_variable theta;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&theta))
return false;

sin_theta= sin(theta.value*0.0174533);
cos_theta= cos(theta.value*0.0174533);

result->value[0]= a.value[0]*cos_theta-a.value[1]*sin_theta;

result->value[1]= a.value[0]*sin_theta+a.value[1]*cos_theta;

result->value[2]= a.value[2]*cos_theta-a.value[4]*sin_theta;

result->value[3]= a.value[3]*cos_theta-a.value[5]*sin_theta;

result->value[4]= a.value[2]*sin_theta+a.value[4]*cos_theta;

result->value[5]= a.value[3]*sin_theta+a.value[5]*cos_theta;
return true;
}
/*:212*//*213:*/
#line 5162 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_SCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;
result->value[0]= a.value[0]*scale.value;
result->value[1]= a.value[1]*scale.value;
result->value[2]= a.value[2]*scale.value;
result->value[3]= a.value[3]*scale.value;
result->value[4]= a.value[4]*scale.value;
result->value[5]= a.value[5]*scale.value;
return true;
}
/*:213*//*214:*/
#line 5202 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_SHIFTED){
struct pair_variable shift;
if(!eval_pair_primary(mf,cx,last_transform->next,end_expression,
&shift))
return false;
result->value[0]= a.value[0]+shift.x;
result->value[1]= a.value[1]+shift.y;
result->value[2]= a.value[2];
result->value[3]= a.value[3];
result->value[4]= a.value[4];
result->value[5]= a.value[5];
return true;
}
/*:214*//*215:*/
#line 5239 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_SLANTED){
struct numeric_variable slant;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&slant))
return false;

result->value[0]= a.value[0]+a.value[1]*slant.value;
result->value[1]= a.value[1];

result->value[2]= a.value[2]+a.value[4]*slant.value;

result->value[3]= a.value[3]+a.value[5]*slant.value;
result->value[4]= a.value[4];
result->value[5]= a.value[5];
return true;
}
/*:215*//*216:*/
#line 5278 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_XSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;

result->value[0]= a.value[0]*scale.value;
result->value[1]= a.value[1];

result->value[2]= a.value[2]*scale.value;

result->value[3]= a.value[3]*scale.value;
result->value[4]= a.value[4];
result->value[5]= a.value[5];
return true;
}
/*:216*//*217:*/
#line 5317 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_YSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;
result->value[0]= a.value[0];

result->value[1]= a.value[1]*scale.value;
result->value[2]= a.value[2];
result->value[3]= a.value[3]*scale.value;

result->value[4]= a.value[4]*scale.value;

result->value[5]= a.value[5]*scale.value;
return true;
}
/*:217*//*218:*/
#line 5358 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_ZSCALED){
struct pair_variable scale;
if(!eval_pair_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;

result->value[0]= a.value[0]*scale.x-a.value[0]*scale.y;

result->value[1]= a.value[0]*scale.y+a.value[0]*scale.y;

result->value[2]= a.value[2]*scale.x-a.value[3]*scale.y;

result->value[3]= a.value[3]*scale.x-a.value[5]*scale.y;

result->value[4]= a.value[2]*scale.y+a.value[4]*scale.x;

result->value[5]= a.value[3]*scale.y+a.value[5]*scale.x;
return true;
}
/*:218*//*219:*/
#line 5402 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_TRANSFORMED){
struct transform_variable b;
if(!eval_transform_primary(mf,cx,last_transform->next,end_expression,
&b))
return false;

result->value[0]= a.value[0]*b.value[2]+a.value[1]*b.value[3]+
b.value[0];

result->value[1]= a.value[0]*b.value[4]+a.value[1]*b.value[5]+
b.value[1];

result->value[2]= a.value[2]*b.value[2]+a.value[4]*b.value[3];

result->value[3]= a.value[3]*b.value[2]+a.value[5]*b.value[3];

result->value[4]= a.value[2]*b.value[4]+a.value[4]*b.value[5];

result->value[5]= a.value[3]*b.value[4]+a.value[5]*b.value[5];
return true;
}
/*:219*/
#line 5077 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transformer "
"in transform expression.",mf->file,begin_expression->line);
#endif
return false;
}
}
/*:211*//*221:*/
#line 5460 "weaver-interface-metafont.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result){
if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*222:*/
#line 5507 "weaver-interface-metafont.tex"

struct symbolic_token*v= (struct symbolic_token*)begin_expression;
struct transform_variable*content= v->var;
if(content==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Not allocated variable: "
"%s.\n",mf->file,v->line,v->value);
#endif
return false;
}
memcpy(result->value,content->value,sizeof(float)*6);
return true;
/*:222*/
#line 5467 "weaver-interface-metafont.tex"

}
else if(begin_expression!=end_expression&&
begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS&&
begin_expression->next!=end_expression){
struct generic_token*p= begin_expression->next;
DECLARE_NESTING_CONTROL();
bool has_comma= false;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p->type==TYPE_COMMA){
RESET_NESTING_COUNT();
has_comma= true;
break;
}
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL&&p!=end_expression);
if(has_comma){
/*224:*/
#line 5547 "weaver-interface-metafont.tex"

int i;
struct generic_token*begin_numeric_expr,*end_numeric_expr;
struct numeric_variable numeric_result;
begin_numeric_expr= begin_expression->next;
end_numeric_expr= begin_numeric_expr;
for(i= 0;i<6;i++){
p= begin_numeric_expr;
do{
if(p!=end_expression){
COUNT_NESTING(p);
}
if(IS_NOT_NESTED()&&((i<5&&p->type==TYPE_COMMA)||
(i==5&&p->type==TYPE_CLOSE_PARENTHESIS))){
break;
}
end_numeric_expr= p;
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(p==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Invalid transform literal in "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_numeric_expression(mf,cx,begin_numeric_expr,end_numeric_expr,
&numeric_result))
return false;
result->value[i]= numeric_result.value;
begin_numeric_expr= p->next;
end_numeric_expr= begin_numeric_expr;
}
return true;
/*:224*/
#line 5489 "weaver-interface-metafont.tex"

}
else{
/*223:*/
#line 5527 "weaver-interface-metafont.tex"

struct generic_token*end_expr;
if(begin_expression->next==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Empty parenthesis in transform "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
for(end_expr= begin_expression->next;end_expr->next!=end_expression;
end_expr= end_expr->next);
return eval_transform_expression(mf,cx,begin_expression->next,end_expr,
result);
/*:223*/
#line 5492 "weaver-interface-metafont.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transform primary "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:221*//*233:*/
#line 5746 "weaver-interface-metafont.tex"

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
/*:233*//*235:*/
#line 5786 "weaver-interface-metafont.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target){
struct path_points*p;
if(alloc_target)
*target= (struct path_variable*)alloc(sizeof(struct path_variable));
(*target)->cyclic= source->cyclic;
(*target)->length= source->total_length;
(*target)->total_length= source->total_length;
(*target)->points= (struct path_points*)
alloc(sizeof(struct path_points)*
(*target)->total_length);
p= (*target)->points;
recursive_aux_copy(&p,source);
}
/*:235*//*237:*/
#line 5815 "weaver-interface-metafont.tex"

void recursive_aux_copy(struct path_points**dst,struct path_variable*origin){
int index= 0;
while(index<=origin->length-1){
if(origin->points[index].subpath==NULL&&
!isnan(origin->points[index].x)){

memcpy(*dst,&(origin->points[index]),sizeof(struct path_points));
(*dst)->subpath= NULL;
(*dst)++;
}
else if(origin->points[index].subpath!=NULL)
recursive_aux_copy(dst,(struct path_variable*)
(origin->points[index].subpath));
index++;
}
return;
}
/*:237*//*241:*/
#line 5910 "weaver-interface-metafont.tex"

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
/*:241*//*243:*/
#line 5957 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin_expression,end_expression);
expected_length= number_of_joins+1;
/*244:*/
#line 5982 "weaver-interface-metafont.tex"

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
/*:244*/
#line 5965 "weaver-interface-metafont.tex"

/*245:*/
#line 6008 "weaver-interface-metafont.tex"

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
/*:245*/
#line 5966 "weaver-interface-metafont.tex"

/*246:*/
#line 6038 "weaver-interface-metafont.tex"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d= NULL,*end_d= NULL,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
struct path_points*z1_point= NULL,*z2_point= NULL;
/*255:*/
#line 6354 "weaver-interface-metafont.tex"

float w0_x= NAN,w0_y= NAN,w1_x= NAN,w1_y= NAN;
float prev_w_x= NAN,prev_w_y= NAN;
float next_w_x= NAN,next_w_y= NAN;
/*:255*//*271:*/
#line 6922 "weaver-interface-metafont.tex"

float first_w_x= NAN,first_w_y= NAN;
/*:271*//*275:*/
#line 7025 "weaver-interface-metafont.tex"

float previous_point_x= NAN,previous_point_y= NAN;
/*:275*//*279:*/
#line 7133 "weaver-interface-metafont.tex"

float first_point_x= NAN,first_point_y= NAN;
/*:279*/
#line 6044 "weaver-interface-metafont.tex"

begin_z1= begin_expression;
end_z1= begin_z1;
while(begin_z1!=end_expression||result->length<expected_length){
/*247:*/
#line 6069 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression){
DECLARE_NESTING_CONTROL();
int next_type;
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
/*:247*//*248:*/
#line 6095 "weaver-interface-metafont.tex"

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
/*:248*//*249:*/
#line 6132 "weaver-interface-metafont.tex"

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
/*:249*//*250:*/
#line 6170 "weaver-interface-metafont.tex"

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
/*:250*//*251:*/
#line 6210 "weaver-interface-metafont.tex"

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
/*:251*/
#line 6048 "weaver-interface-metafont.tex"

/*252:*/
#line 6243 "weaver-interface-metafont.tex"

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
/*:252*//*253:*/
#line 6277 "weaver-interface-metafont.tex"

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
&(result->points[result->length].subpath),&z2,true);
result->total_length+= 
((struct path_variable*)
result->points[result->length].subpath)->total_length;
}
result->length++;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&z2,false);
}
/*:253*//*254:*/
#line 6329 "weaver-interface-metafont.tex"

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
/*:254*/
#line 6049 "weaver-interface-metafont.tex"

/*256:*/
#line 6371 "weaver-interface-metafont.tex"

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
/*:256*/
#line 6050 "weaver-interface-metafont.tex"

/*262:*/
#line 6493 "weaver-interface-metafont.tex"

float tension0= NAN,tension1= NAN,u_x= NAN,u_y= NAN,v_x= NAN,
v_y= NAN;
bool atleast0= false,atleast1= false;
/*:262*//*263:*/
#line 6510 "weaver-interface-metafont.tex"

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
/*:263*//*264:*/
#line 6538 "weaver-interface-metafont.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_STRAIGHT_JOIN){
u_x= z1_point->x+(1.0/3.0)*(z2_point->x-z1_point->x);
u_y= z1_point->y+(1.0/3.0)*(z2_point->y-z1_point->y);
v_x= z1_point->x+(2.0/3.0)*(z2_point->x-z1_point->x);
v_y= z1_point->y+(2.0/3.0)*(z2_point->y-z1_point->y);
}
/*:264*//*265:*/
#line 6553 "weaver-interface-metafont.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
tension0= 1.0;
tension1= 1.0;
atleast0= false;
atleast1= false;
}
/*:265*//*266:*/
#line 6571 "weaver-interface-metafont.tex"

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
/*:266*//*267:*/
#line 6637 "weaver-interface-metafont.tex"

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
/*:267*/
#line 6051 "weaver-interface-metafont.tex"

/*269:*/
#line 6859 "weaver-interface-metafont.tex"

if(isnan(w0_x)&&isnan(w0_y)){
w0_x= prev_w_x;
w0_y= prev_w_y;
}
/*:269*//*270:*/
#line 6872 "weaver-interface-metafont.tex"

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
/*:270*//*272:*/
#line 6932 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d!=NULL&&end_d!=NULL){
first_w_x= w0_x;
first_w_y= w0_y;
}
/*:272*//*273:*/
#line 6945 "weaver-interface-metafont.tex"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE){
if(!isnan(first_w_x)&&isnan(w1_x)){
w1_x= first_w_x;
w1_y= first_w_y;
}
}
/*:273*//*274:*/
#line 6964 "weaver-interface-metafont.tex"

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
/*282:*/
#line 7179 "weaver-interface-metafont.tex"

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
/*:282*/
#line 6998 "weaver-interface-metafont.tex"

}
/*:274*//*276:*/
#line 7038 "weaver-interface-metafont.tex"

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
/*:276*//*277:*/
#line 7058 "weaver-interface-metafont.tex"

if(begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
previous_point_x= v_x;
previous_point_y= v_y;
}
else{
previous_point_x= NAN;
previous_point_y= NAN;
}
/*:277*//*278:*/
#line 7077 "weaver-interface-metafont.tex"

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
/*:278*//*280:*/
#line 7141 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
first_point_x= u_x;
first_point_y= u_y;
}
/*:280*//*281:*/
#line 7155 "weaver-interface-metafont.tex"

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
/*:281*//*283:*/
#line 7222 "weaver-interface-metafont.tex"

if(isnan(u_x)||isnan(u_y)||isnan(v_x)||isnan(v_y)){
if(isnan(w0_x)||isnan(w0_y)||isnan(w1_x)||isnan(w1_y)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
/*:283*//*287:*/
#line 7311 "weaver-interface-metafont.tex"

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
/*294:*/
#line 7519 "weaver-interface-metafont.tex"

if(atleast0)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&u_x,&u_y);
if(atleast1)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&v_x,&v_y);
/*:294*/
#line 7324 "weaver-interface-metafont.tex"

}
/*:287*//*295:*/
#line 7536 "weaver-interface-metafont.tex"

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
/*:295*/
#line 6052 "weaver-interface-metafont.tex"

/*268:*/
#line 6840 "weaver-interface-metafont.tex"

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
/*:268*/
#line 6053 "weaver-interface-metafont.tex"

begin_z1= begin_z2;
end_z1= end_z2;
}

}
/*:246*/
#line 5967 "weaver-interface-metafont.tex"

return true;
}
/*:243*//*258:*/
#line 6402 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y){
/*259:*/
#line 6419 "weaver-interface-metafont.tex"

if(begin==NULL||end==NULL){
return true;
}
/*:259*/
#line 6407 "weaver-interface-metafont.tex"

/*260:*/
#line 6432 "weaver-interface-metafont.tex"

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
/*:260*/
#line 6408 "weaver-interface-metafont.tex"

/*261:*/
#line 6470 "weaver-interface-metafont.tex"

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
/*:261*/
#line 6409 "weaver-interface-metafont.tex"

return false;
}
/*:258*//*285:*/
#line 7286 "weaver-interface-metafont.tex"

double compute_f(double theta,double phi){
double n= 2+sqrt(2)*(sin(theta)-0.0625*sin(phi))*
(sin(phi)-0.0625*sin(theta))*(cos(theta)-cos(phi));
double d= 3*(1+0.5*(sqrt(5.0)-1)*cos(theta)+0.5*(3-sqrt(5))*
cos(phi));
return n/d;
}
/*:285*//*289:*/
#line 7349 "weaver-interface-metafont.tex"

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
/*:289*//*291:*/
#line 7388 "weaver-interface-metafont.tex"

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
/*292:*/
#line 7431 "weaver-interface-metafont.tex"

bool s1,s2,s3;
s1= ((*control_x-p1_x)*(p0_y-p1_y)-
(p0_x-p1_x)*(*control_y-p1_y))<0;
s2= ((*control_x-p2_x)*(p1_y-p2_y)-
(p1_x-p2_x)*(*control_y-p2_y))<0;
s3= ((*control_x-p0_x)*(p2_y-p0_y)-
(p2_x-p0_x)*(*control_y-p0_y))<0;
if(s1==s2&&s2==s3)
return;
/*:292*/
#line 7414 "weaver-interface-metafont.tex"

/*293:*/
#line 7454 "weaver-interface-metafont.tex"

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
/*:293*/
#line 7415 "weaver-interface-metafont.tex"

}
}
/*:291*//*297:*/
#line 7594 "weaver-interface-metafont.tex"

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
return eval_path_secondary(mf,cx,begin_expression,end_expression,
result);
}
/*:297*//*299:*/
#line 7686 "weaver-interface-metafont.tex"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
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
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED||
p->type==TYPE_TRANSFORMED)){
if(p->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
p!=end_expression&&
((struct generic_token*)p->next)->type!=TYPE_NUMERIC&&
last_fraction!=prev_prev)
last_fraction= p;
else if(p->type==TYPE_DIVISION||
p->type==TYPE_MULTIPLICATION)
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
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_path_secondary(mf,cx,begin_expression,before_transform,
result))
return false;
/*300:*/
#line 7791 "weaver-interface-metafont.tex"

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
/*:300*/
#line 7737 "weaver-interface-metafont.tex"

/*303:*/
#line 7850 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,a.value);
return true;
}
/*:303*/
#line 7738 "weaver-interface-metafont.tex"

/*306:*/
#line 7901 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SHIFTED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_shift(result,a.x,a.y);
return true;
}
/*:306*/
#line 7739 "weaver-interface-metafont.tex"

/*309:*/
#line 7946 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SLANTED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_slant(result,a.value);
return true;
}
/*:309*/
#line 7740 "weaver-interface-metafont.tex"

/*312:*/
#line 7989 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_XSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,1.0);
return true;
}
/*:312*/
#line 7741 "weaver-interface-metafont.tex"

/*313:*/
#line 8006 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_YSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,1.0,a.value);
return true;
}
/*:313*/
#line 7742 "weaver-interface-metafont.tex"

/*314:*/
#line 8030 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_ZSCALED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,&a))
return false;
path_zscale(result,a.x,a.y);
return true;
}
/*:314*/
#line 7743 "weaver-interface-metafont.tex"

/*317:*/
#line 8081 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_TRANSFORMED){
struct transform_variable a;
if(!eval_transform_primary(mf,cx,transform_op->next,end_expression,&a))
return false;
path_transform(result,a.value[0],a.value[1],a.value[2],a.value[3],
a.value[4],a.value[5]);
return true;
}
else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transformer\n",
mf->file,transform_op->line);
#endif
return false;
}
/*:317*/
#line 7744 "weaver-interface-metafont.tex"

}
else if(have_pair_operator){
struct pair_variable pair;
if(!eval_pair_secondary(mf,cx,begin_expression,end_expression,
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
/*:299*//*302:*/
#line 7820 "weaver-interface-metafont.tex"

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
/*:302*//*305:*/
#line 7876 "weaver-interface-metafont.tex"

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
/*:305*//*308:*/
#line 7922 "weaver-interface-metafont.tex"

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
/*:308*//*311:*/
#line 7967 "weaver-interface-metafont.tex"

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
/*:311*//*316:*/
#line 8050 "weaver-interface-metafont.tex"

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
/*:316*//*319:*/
#line 8112 "weaver-interface-metafont.tex"

void path_transform(struct path_variable*p,float x,float y,float xx,
float xy,float yx,float yy){
int i;
for(i= 0;i<p->length;i++){
if(p->points[i].subpath!=NULL)
path_transform((struct path_variable*)(p->points[i].subpath),
x,y,xx,xy,yx,yy);
else{
float x0= p->points[i].x;
float y0= p->points[i].y;
p->points[i].x= x+x0*xx+y0*xy;
p->points[i].y= y+x0*yx+y0*yy;
x0= p->points[i].u_x;
y0= p->points[i].u_y;
p->points[i].u_x= x+x0*xx+y0*xy;
p->points[i].u_y= y+x0*yx+y0*yy;
x0= p->points[i].v_x;
y0= p->points[i].v_y;
p->points[i].v_x= x+x0*xx+y0*xy;
p->points[i].v_x= y+x0*yx+y0*yy;
}
}
}
/*:319*//*323:*/
#line 8194 "weaver-interface-metafont.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
if(begin_expression->type==TYPE_REVERSE){
/*325:*/
#line 8293 "weaver-interface-metafont.tex"

struct path_variable tmp;
if(begin_expression->next==NULL||
begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
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
/*:325*/
#line 8200 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_SUBPATH){
/*328:*/
#line 8382 "weaver-interface-metafont.tex"

DECLARE_NESTING_CONTROL();
struct pair_variable a;
struct path_variable b;
struct generic_token*of,*end_pair_expr= begin_expression;
struct generic_token*begin_subexpr;
if(begin_expression->next==NULL||end_pair_expr->type==TYPE_OF||
begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
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
"expression.\n",mf->file,begin_expression->line);
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
int final_path_size,offset;
result->cyclic= false;
if(a.x<0&&!b.cyclic)
a.x= 0;
if(a.y<0&&!b.cyclic)
a.y= 0;
if(a.x>=b.total_length&&!b.cyclic)
a.x= b.total_length-1;
if(a.y>=b.total_length&&!b.cyclic)
a.y= b.total_length-1;
final_path_size= a.y-a.x;
if(final_path_size<0)
final_path_size*= -1;
final_path_size++;
offset= (a.x<=a.y)?(a.x):(a.y);
if(b.cyclic)
offset= offset%(b.total_length-1);
else
offset= offset%b.total_length;
if(offset<0)
offset*= -1;
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
copy_subpath(result->points,&b,offset,final_path_size);

result->points[result->length-1].u_x= 
result->points[result->length-1].x;
result->points[result->length-1].u_y= 
result->points[result->length-1].y;
result->points[result->length-1].v_x= 
result->points[result->length-1].x;
result->points[result->length-1].v_y= 
result->points[result->length-1].y;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&b,false);
if(a.x> a.y){
struct path_variable c;
c.length= result->total_length;
c.total_length= result->total_length;
c.points= (struct path_points*)temporary_alloc(sizeof(struct path_points)*
c.total_length);
if(c.points==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: No enough memory!\n",mf->file,
begin_expression->line);
#endif
return false;
}
reverse_path(result,&c);
temporary_free(result->points);
result->points= c.points;
}
return true;
}
/*:328*/
#line 8203 "weaver-interface-metafont.tex"

}
else if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*333:*/
#line 8582 "weaver-interface-metafont.tex"

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
/*:333*/
#line 8207 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*334:*/
#line 8624 "weaver-interface-metafont.tex"

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
/*:334*/
#line 8211 "weaver-interface-metafont.tex"

}
/*372:*/
#line 9789 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_MAKEPATH){
struct pen_variable tmp;
if(begin_expression->next==NULL||
begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_pen_primary(mf,cx,begin_expression->next,end_expression,
&tmp))
return false;
if(tmp.flags&FLAG_NULL){
/*373:*/
#line 9825 "weaver-interface-metafont.tex"

result->length= 1;
result->total_length= 1;
result->cyclic= false;
result->points= 
(struct path_points*)temporary_alloc(sizeof(struct path_points));
result->points[0].x= 0.0;
result->points[0].y= 0.0;
result->points[0].u_x= 0.0;
result->points[0].u_y= 0.0;
result->points[0].v_x= 0.0;
result->points[0].v_y= 0.0;
result->points[0].subpath= NULL;
/*:373*/
#line 9804 "weaver-interface-metafont.tex"

}
else if(tmp.flags&FLAG_CIRCULAR){
/*374:*/
#line 9847 "weaver-interface-metafont.tex"

result->length= 9;
result->total_length= 9;
result->points= 
(struct path_points*)temporary_alloc(sizeof(struct path_points)*9);
result->points[0].subpath= NULL;
result->points[0].x= 0.5;result->points[0].y= 0.0;
result->points[0].u_x= 0.5;result->points[0].u_y= 0.13261;
result->points[0].v_x= 0.44733;result->points[0].v_y= 0.2598;
result->points[1].subpath= NULL;
result->points[1].x= 0.35356;result->points[1].y= 0.35356;
result->points[1].u_x= 0.2598;result->points[1].u_y= 0.44733;
result->points[1].v_x= 0.13261;result->points[1].v_y= 0.5;
result->points[2].subpath= NULL;
result->points[2].x= 0.0;result->points[2].y= 0.5;
result->points[2].u_x= -0.13261;result->points[2].u_y= 0.5;
result->points[2].v_x= -0.2598;result->points[2].v_y= 0.44733;
result->points[3].subpath= NULL;
result->points[3].x= -0.35356;result->points[3].y= 0.35356;
result->points[3].u_x= -0.44733;result->points[3].u_y= 0.2598;
result->points[3].v_x= -0.5;result->points[3].v_y= 0.13261;
result->points[4].subpath= NULL;
result->points[4].x= -0.5;result->points[4].y= 0.0;
result->points[4].u_x= -0.5;result->points[4].u_y= -0.13261;
result->points[4].v_x= -0.44733;result->points[4].v_y= -0.2598;
result->points[5].subpath= NULL;
result->points[5].x= -0.35356;result->points[5].y= -0.35356;
result->points[5].u_x= -0.2598;result->points[5].u_y= -0.44733;
result->points[5].v_x= -0.13261;result->points[5].v_y= -0.5;
result->points[6].subpath= NULL;
result->points[6].x= 0.0;result->points[6].y= -0.5;
result->points[6].u_x= 0.13261;result->points[6].u_y= -0.5;
result->points[6].v_x= 0.2598;result->points[6].v_y= -0.44733;
result->points[7].subpath= NULL;
result->points[7].x= 0.35356;result->points[7].y= -0.35356;
result->points[7].u_x= 0.44733;result->points[7].u_y= -0.2598;
result->points[7].v_x= 0.5;result->points[7].v_y= -0.13261;
result->points[8].subpath= NULL;
result->points[8].x= 0.5;result->points[8].y= 0.0;
result->points[8].u_x= 0.5;result->points[8].u_y= 0.13261;
result->points[8].v_x= 0.44733;result->points[8].v_y= 0.2598;
result->cyclic= true;
/*:374*/
#line 9807 "weaver-interface-metafont.tex"

}
else if(tmp.flags&FLAG_SQUARE){
/*375:*/
#line 9896 "weaver-interface-metafont.tex"

result->length= 5;
result->total_length= 5;
result->points= 
(struct path_points*)temporary_alloc(sizeof(struct path_points)*5);
result->points[0].subpath= NULL;
result->points[0].x= -0.5;result->points[0].y= -0.5;
result->points[0].u_x= (-0.5+(1.0/3.0));result->points[0].u_y= -0.5;
result->points[0].v_x= (-0.5+(2.0/3.0));result->points[0].v_y= -0.5;
result->points[1].subpath= NULL;
result->points[1].x= 0.5;result->points[1].y= -0.5;
result->points[1].u_x= 0.5;result->points[1].u_y= (-0.5+(1.0/3.0));
result->points[1].v_x= 0.5;result->points[1].v_y= (-0.5+(2.0/3.0));
result->points[2].subpath= NULL;
result->points[2].x= 0.5;result->points[2].y= 0.5;
result->points[2].u_x= (0.5-(1.0/3.0));result->points[2].u_y= 0.5;
result->points[2].v_x= (0.5-(2.0/3.0));result->points[2].v_y= 0.5;
result->points[3].subpath= NULL;
result->points[3].x= -0.5;result->points[3].y= 0.5;
result->points[3].u_x= -0.5;result->points[3].u_y= (0.5-(1.0/3.0));
result->points[3].v_x= -0.5;result->points[3].v_y= (0.5-(2.0/3.0));
result->points[4].subpath= NULL;
result->points[4].x= -0.5;result->points[4].y= -0.5;
result->points[4].u_x= (-0.5+(1.0/3.0));result->points[4].u_y= -0.5;
result->points[4].v_x= (-0.5+(2.0/3.0));result->points[4].v_y= -0.5;
result->cyclic= true;
/*:375*/
#line 9810 "weaver-interface-metafont.tex"

}
else{
/*376:*/
#line 9931 "weaver-interface-metafont.tex"

if(tmp.referenced==NULL)
recursive_copy_points(temporary_alloc,&result,tmp.format,false);
else
recursive_copy_points(temporary_alloc,&result,tmp.referenced->format,
false);
if(temporary_free!=NULL&&tmp.referenced==NULL)
temporary_free(tmp.format);
/*:376*/
#line 9813 "weaver-interface-metafont.tex"

}
/*377:*/
#line 9947 "weaver-interface-metafont.tex"

{
int i;
for(i= 0;i<result->length;i++){
float old_x= result->points[i].x;
result->points[i].x= result->points[i].x*tmp.gl_matrix[0]+
result->points[i].y*tmp.gl_matrix[4]+
tmp.gl_matrix[12];
result->points[i].y= old_x*tmp.gl_matrix[1]+
result->points[i].y*tmp.gl_matrix[5]+
tmp.gl_matrix[13];
old_x= result->points[i].u_x;
result->points[i].u_x= result->points[i].u_x*tmp.gl_matrix[0]+
result->points[i].u_y*tmp.gl_matrix[4]+
tmp.gl_matrix[12];
result->points[i].u_y= old_x*tmp.gl_matrix[1]+
result->points[i].u_y*tmp.gl_matrix[5]+
tmp.gl_matrix[13];
old_x= result->points[i].v_x;
result->points[i].v_x= result->points[i].v_x*tmp.gl_matrix[0]+
result->points[i].v_y*tmp.gl_matrix[4]+
tmp.gl_matrix[12];
result->points[i].v_y= old_x*tmp.gl_matrix[1]+
result->points[i].v_y*tmp.gl_matrix[5]+
tmp.gl_matrix[13];
}
}
/*:377*/
#line 9815 "weaver-interface-metafont.tex"

return true;
}
/*:372*/
#line 8213 "weaver-interface-metafont.tex"

{
/*335:*/
#line 8655 "weaver-interface-metafont.tex"

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
/*:335*/
#line 8215 "weaver-interface-metafont.tex"

}
return false;
}
/*:323*//*324:*/
#line 8248 "weaver-interface-metafont.tex"

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
/*:324*//*327:*/
#line 8330 "weaver-interface-metafont.tex"

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
/*:327*//*330:*/
#line 8501 "weaver-interface-metafont.tex"

void copy_subpath(struct path_points*dst,struct path_variable*src,int offset,int size){
struct path_points*dst_pointer= dst;
while(size> 0){
int index= 0;
int initial_offset= offset,initial_size= size;
recursive_copy_subpath(&dst_pointer,src,&index,&offset,&size);

if(offset<=0&&src->cyclic&&
initial_offset+initial_size>=src->total_length){
dst_pointer--;
size++;
}
}
}
/*:330*//*332:*/
#line 8532 "weaver-interface-metafont.tex"

int recursive_copy_subpath(struct path_points**dst,
struct path_variable*pointer,
int*index,int*offset,int*size){
while(*size> 0){
if(pointer->points[*index].subpath==NULL&&
!isnan(pointer->points[*index].x)){
if(*offset> 0)
(*offset)--;
else{

memcpy(*dst,&(pointer->points[*index]),
sizeof(struct path_points));
(*dst)->subpath= NULL;
(*dst)++;
(*size)--;
}
if(*index<pointer->length-1)
(*index)++;
else
return false;
}
else if(pointer->points[*index].subpath!=NULL){
int new_index= 0;
recursive_copy_subpath(dst,(struct path_variable*)
(pointer->points[*index].subpath),
&new_index,offset,size);
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
/*:332*//*340:*/
#line 8755 "weaver-interface-metafont.tex"

struct path_points*get_point(struct path_variable*v,int n){
if(v->length==v->total_length){
struct path_points*ret= (struct path_points*)&(v->points[n]);
while(ret->subpath!=NULL)
ret= &(((struct path_variable*)(ret->subpath))->points[0]);
return ret;
}
else{
int count= 0;
return _get_point(v,n,&count);
}
}
/*:340*//*342:*/
#line 8787 "weaver-interface-metafont.tex"

struct path_points*_get_point(struct path_variable*v,int n,int*count){
int i;
for(i= 0;i<v->length;i++){
if(v->points[i].subpath==NULL){
if(*count==n&&!isnan(v->points[i].x))
return((struct path_points*)&(v->points[i]));
else if(!isnan(v->points[i].x))
(*count)++;
}
else{
struct path_points*r= 
_get_point((struct path_variable*)(v->points[i].subpath),
n,count);
if(r!=NULL)
return r;
}
}
return NULL;
}
/*:342*//*346:*/
#line 8945 "weaver-interface-metafont.tex"

void assign_pen_variable(struct metafont*mf,
struct pen_variable*target,
struct pen_variable*source){
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
if(target->referenced==NULL){
if(target->format!=NULL&&disalloc!=NULL)
path_recursive_free(disalloc,target->format,true);
if(target->gl_vbo!=0)
glDeleteBuffers(1,&(target->gl_vbo));
}
memcpy(target,source,sizeof(struct pen_variable));
target->type= TYPE_T_PEN;
if(!(source->flags&(FLAG_CIRCULAR|FLAG_SQUARE|FLAG_NULL)))
recursive_copy_points(alloc,&(target->format),source->format,true);
target->number_of_vertices= 0;
target->gl_vbo= 0;
target->referenced= NULL;
}
/*:346*//*348:*/
#line 8998 "weaver-interface-metafont.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result){
return eval_pen_secondary(mf,cx,begin_expression,end_token_list,result);
}
/*:348*//*350:*/
#line 9050 "weaver-interface-metafont.tex"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*pen){
DECLARE_NESTING_CONTROL();
struct generic_token*p,*prev= NULL,*last_transformer= NULL,
*before_last_transformer= begin_expression;
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_ROTATED||
p->type==TYPE_SCALED||p->type==TYPE_SHIFTED||
p->type==TYPE_SLANTED||p->type==TYPE_XSCALED||
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED||
p->type==TYPE_TRANSFORMED)){
last_transformer= p;
before_last_transformer= prev;
}
prev= p;
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(last_transformer==NULL)
return eval_pen_primary(mf,cx,begin_expression,end_expression,pen);
else{
if(!eval_pen_secondary(mf,cx,begin_expression,before_last_transformer,pen))
return false;
if(last_transformer->type==TYPE_ROTATED){
/*351:*/
#line 9137 "weaver-interface-metafont.tex"

struct numeric_variable r;
float temp_matrix[16];
double rotation,cos_theta,sin_theta;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&r))
return false;
rotation= 0.017453292519943295*r.value;
sin_theta= sin(rotation);
cos_theta= cos(rotation);
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[0]= temp_matrix[0]*cos_theta-temp_matrix[1]*sin_theta;
pen->gl_matrix[1]= temp_matrix[0]*sin_theta+temp_matrix[1]*cos_theta;
pen->gl_matrix[4]= temp_matrix[4]*cos_theta-temp_matrix[5]*sin_theta;
pen->gl_matrix[5]= temp_matrix[4]*sin_theta+temp_matrix[5]*cos_theta;
pen->gl_matrix[8]= temp_matrix[8]*cos_theta-temp_matrix[9]*sin_theta;
pen->gl_matrix[9]= temp_matrix[8]*sin_theta+temp_matrix[9]*cos_theta;
pen->gl_matrix[12]= temp_matrix[12]*cos_theta-temp_matrix[13]*sin_theta;
pen->gl_matrix[13]= temp_matrix[12]*sin_theta+temp_matrix[13]*cos_theta;
return true;
/*:351*/
#line 9081 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*352:*/
#line 9177 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[0]= temp_matrix[0]*a.value;
pen->gl_matrix[1]= temp_matrix[1]*a.value;
pen->gl_matrix[4]= temp_matrix[4]*a.value;
pen->gl_matrix[5]= temp_matrix[5]*a.value;
pen->gl_matrix[8]= temp_matrix[8]*a.value;
pen->gl_matrix[9]= temp_matrix[9]*a.value;
pen->gl_matrix[12]= temp_matrix[12]*a.value;
pen->gl_matrix[13]= temp_matrix[13]*a.value;

if(!(pen->flags&(FLAG_STRAIGHT|FLAG_NULL))&&a.value!=1.0){
if(pen->referenced!=NULL){
recursive_copy_points(temporary_alloc,&(pen->format),
pen->referenced->format,true);
pen->referenced= NULL;
}
else if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
}
return true;
/*:352*/
#line 9084 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*353:*/
#line 9221 "weaver-interface-metafont.tex"

struct pair_variable p;
float temp_matrix[16];
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[0]= temp_matrix[0]+temp_matrix[3]*p.x;
pen->gl_matrix[1]= temp_matrix[1]+temp_matrix[3]*p.y;
pen->gl_matrix[4]= temp_matrix[4]+temp_matrix[7]*p.x;
pen->gl_matrix[5]= temp_matrix[5]+temp_matrix[7]*p.y;
pen->gl_matrix[8]= temp_matrix[8]+temp_matrix[11]*p.x;
pen->gl_matrix[9]= temp_matrix[8]+temp_matrix[11]*p.y;
pen->gl_matrix[12]= temp_matrix[12]+temp_matrix[15]*p.x;
pen->gl_matrix[13]= temp_matrix[12]+temp_matrix[15]*p.y;
return true;
/*:353*/
#line 9087 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*354:*/
#line 9254 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[0]= temp_matrix[0]+a.value*temp_matrix[1];
pen->gl_matrix[4]= temp_matrix[4]+a.value*temp_matrix[5];
pen->gl_matrix[8]= temp_matrix[8]+a.value*temp_matrix[9];
pen->gl_matrix[12]= temp_matrix[12]+a.value*temp_matrix[13];

if(!(pen->flags&(FLAG_STRAIGHT|FLAG_NULL))&&a.value!=0.0){
if(pen->referenced!=NULL){
recursive_copy_points(temporary_alloc,&(pen->format),
pen->referenced->format,true);
pen->referenced= NULL;
}
else if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
}
return true;
/*:354*/
#line 9090 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*355:*/
#line 9294 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[0]= temp_matrix[0]*a.value;
pen->gl_matrix[4]= temp_matrix[4]*a.value;
pen->gl_matrix[8]= temp_matrix[8]*a.value;
pen->gl_matrix[12]= temp_matrix[12]*a.value;

if(!(pen->flags&(FLAG_STRAIGHT|FLAG_NULL))&&a.value!=1.0){
if(pen->referenced!=NULL){
recursive_copy_points(temporary_alloc,&(pen->format),
pen->referenced->format,true);
pen->referenced= NULL;
}
else if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
}
return true;
/*:355*/
#line 9093 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*356:*/
#line 9331 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[1]= temp_matrix[1]*a.value;
pen->gl_matrix[5]= temp_matrix[5]*a.value;
pen->gl_matrix[9]= temp_matrix[9]*a.value;
pen->gl_matrix[13]= temp_matrix[13]*a.value;

if(!(pen->flags&(FLAG_STRAIGHT|FLAG_NULL))&&a.value!=1.0){
if(pen->referenced!=NULL){
recursive_copy_points(temporary_alloc,&(pen->format),
pen->referenced->format,true);
pen->referenced= NULL;
}
else if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
}
return true;
/*:356*/
#line 9096 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*357:*/
#line 9376 "weaver-interface-metafont.tex"

struct pair_variable p;
float temp_matrix[16];
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[0]= temp_matrix[0]*p.x-temp_matrix[1]*p.y;
pen->gl_matrix[1]= temp_matrix[0]*p.y+temp_matrix[1]*p.x;
pen->gl_matrix[4]= temp_matrix[4]*p.x-temp_matrix[5]*p.y;
pen->gl_matrix[5]= temp_matrix[4]*p.y+temp_matrix[5]*p.x;
pen->gl_matrix[8]= temp_matrix[8]*p.x-temp_matrix[9]*p.y;
pen->gl_matrix[9]= temp_matrix[8]*p.y+temp_matrix[9]*p.x;
pen->gl_matrix[12]= temp_matrix[12]*p.x-temp_matrix[13]*p.y;
pen->gl_matrix[13]= temp_matrix[12]*p.y+temp_matrix[13]*p.x;
if(!(pen->flags&(FLAG_STRAIGHT|FLAG_NULL))){
if(pen->referenced!=NULL){
recursive_copy_points(temporary_alloc,&(pen->format),
pen->referenced->format,true);
pen->referenced= NULL;
}
else if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
}
return true;
/*:357*/
#line 9099 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*358:*/
#line 9417 "weaver-interface-metafont.tex"

struct transform_variable t;
float temp_matrix[16];
if(!eval_transform_primary(mf,cx,last_transformer->next,end_expression,&t))
return false;
memcpy(temp_matrix,pen->gl_matrix,16*sizeof(float));
pen->gl_matrix[0]= temp_matrix[0]*t.value[2]+temp_matrix[1]*t.value[3]+
temp_matrix[3]*t.value[0];
pen->gl_matrix[1]= temp_matrix[0]*t.value[4]+temp_matrix[1]*t.value[5]+
temp_matrix[3]*t.value[1];
pen->gl_matrix[4]= temp_matrix[4]*t.value[2]+temp_matrix[5]*t.value[3]+
temp_matrix[7]*t.value[0];
pen->gl_matrix[5]= temp_matrix[4]*t.value[4]+temp_matrix[5]*t.value[5]+
temp_matrix[7]*t.value[1];
pen->gl_matrix[12]= temp_matrix[12]*t.value[2]+temp_matrix[13]*t.value[3]+
temp_matrix[15]*t.value[0];
pen->gl_matrix[13]= temp_matrix[12]*t.value[4]+temp_matrix[13]*t.value[5]+
temp_matrix[15]*t.value[1];
if(!(pen->flags&(FLAG_STRAIGHT|FLAG_NULL))){
if(pen->referenced!=NULL){
recursive_copy_points(temporary_alloc,&(pen->format),
pen->referenced->format,true);
pen->referenced= NULL;
}
else if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
}
return true;
/*:358*/
#line 9102 "weaver-interface-metafont.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:350*//*362:*/
#line 9494 "weaver-interface-metafont.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*363:*/
#line 9535 "weaver-interface-metafont.tex"

struct symbolic_token*v= (struct symbolic_token*)begin_expression;
struct pen_variable*content= v->var;
if(content==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Using unknown variable '%s'.\n",
mf->file,begin_expression->line,v->value);
#endif
return false;
}
if(content->type!=TYPE_T_PEN){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Got non-pen variable (%d) in pen expression.\n",
mf->file,begin_expression->line,content->type);
#endif
return false;
}
memcpy(result,content,sizeof(struct pen_variable));
result->referenced= content;
return true;
/*:363*/
#line 9501 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_NULLPEN){
/*364:*/
#line 9563 "weaver-interface-metafont.tex"

result->format= NULL;
result->flags= FLAG_NULL;
result->referenced= false;
result->gl_vbo= 0;
result->gl_matrix[0]= result->gl_matrix[5]= result->gl_matrix[10]= 
result->gl_matrix[15]= 1.0;
result->gl_matrix[1]= result->gl_matrix[2]= result->gl_matrix[3]= 
result->gl_matrix[4]= result->gl_matrix[6]= 
result->gl_matrix[7]= result->gl_matrix[8]= 
result->gl_matrix[9]= result->gl_matrix[11]= 
result->gl_matrix[12]= result->gl_matrix[13]= 
result->gl_matrix[14]= 0.0;
return true;
/*:364*/
#line 9504 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_PENCIRCLE){
/*365:*/
#line 9585 "weaver-interface-metafont.tex"

result->format= NULL;
result->flags= FLAG_CONVEX|FLAG_CIRCULAR;
result->referenced= false;
result->gl_vbo= 0;
result->number_of_vertices= 0;
result->gl_matrix[0]= result->gl_matrix[5]= result->gl_matrix[10]= 
result->gl_matrix[15]= 1.0;
result->gl_matrix[1]= result->gl_matrix[2]= result->gl_matrix[3]= 
result->gl_matrix[4]= result->gl_matrix[6]= 
result->gl_matrix[7]= result->gl_matrix[8]= 
result->gl_matrix[9]= result->gl_matrix[11]= 
result->gl_matrix[12]= result->gl_matrix[13]= 
result->gl_matrix[14]= 0.0;
return true;
/*:365*/
#line 9507 "weaver-interface-metafont.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*366:*/
#line 9608 "weaver-interface-metafont.tex"

struct generic_token*t= begin_expression->next;
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
t= t->next;
}
return eval_pen_expression(mf,cx,begin_expression->next,t,result);
/*:366*/
#line 9513 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_MAKEPEN){
/*367:*/
#line 9632 "weaver-interface-metafont.tex"

struct generic_token*p= begin_expression->next;
result->format= 
(struct path_variable*)temporary_alloc(sizeof(struct path_variable));
if(result->format==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Not enough memory.\n",
mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_path_primary(mf,cx,p,end_expression,result->format))
return false;
if(!(result->format->cyclic)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Using 'makepen' with non-cyclic path.\n",
mf->file,begin_expression->line);
#endif
return false;
}
result->flags= read_flags(result->format);
result->referenced= NULL;
result->gl_vbo= 0;
result->number_of_vertices= 0;
result->gl_matrix[0]= result->gl_matrix[5]= result->gl_matrix[10]= 
result->gl_matrix[15]= 1.0;
result->gl_matrix[1]= result->gl_matrix[2]= result->gl_matrix[3]= 
result->gl_matrix[4]= result->gl_matrix[6]= 
result->gl_matrix[7]= result->gl_matrix[8]= 
result->gl_matrix[9]= result->gl_matrix[11]= 
result->gl_matrix[12]= result->gl_matrix[13]= 
result->gl_matrix[14]= 0.0;
return true;
/*:367*/
#line 9516 "weaver-interface-metafont.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:362*//*369:*/
#line 9684 "weaver-interface-metafont.tex"

int read_flags(struct path_variable*path){
int i,positive_cross_product= -1;
int flag= FLAG_CONVEX|FLAG_STRAIGHT;
for(i= 0;i<path->total_length-1;i++){
struct path_points*current,*next;
current= get_point(path,i);
next= get_point(path,i+1);
if(flag&FLAG_STRAIGHT){



double area= current->x*(current->u_y-next->y)+
current->u_x*(next->y-current->y)+
next->x*(current->y-current->u_y);
if(area> 0.00002)
flag-= FLAG_STRAIGHT;
area= current->x*(current->v_y-next->y)+
current->v_x*(next->y-current->y)+
next->x*(current->y-current->v_y);
if((flag&FLAG_STRAIGHT)&&area> 0.00002)
flag-= FLAG_STRAIGHT;
}
if(flag&FLAG_CONVEX){



int j;
double d1_x,d1_y,d2_x,d2_y,z_cross_product;
double p1_x,p1_y,p2_x,p2_y,p3_x,p3_y;
for(j= 0;j<3;j++){
switch(j){
case 0:
p1_x= current->x;p1_y= current->y;
p2_x= current->u_x;p2_y= current->u_y;
p3_x= current->v_x;p3_y= current->v_y;
break;
case 1:
p1_x= p2_x;p1_y= p2_y;
p2_x= p3_x;p2_y= p3_y;
p3_x= next->x;p3_y= next->y;
break;
default:
p1_x= p2_x;p1_y= p2_y;
p2_x= p3_x;p2_y= p3_y;
p3_x= next->u_x;p3_y= next->u_y;
break;
}
d1_x= p2_x-p1_x;
d1_y= p2_y-p1_y;
d2_x= p3_x-p2_x;
d2_y= p3_y-p2_y;
z_cross_product= d1_x*d2_y-d1_y*d2_x;
if(z_cross_product> 0.00002||z_cross_product<-0.00002){
if(positive_cross_product==-1)
positive_cross_product= (z_cross_product> 0);
else if((z_cross_product> 0)!=positive_cross_product){
flag-= FLAG_CONVEX;
break;
}
}
}
}
}
return flag;
}
/*:369*//*385:*/
#line 10134 "weaver-interface-metafont.tex"

GLuint compile_shader_program(const char*vertex_shader_source,
const char*fragment_shader_source){
GLuint vertex,fragment,prog;
GLint status= GL_TRUE;

vertex= glCreateShader(GL_VERTEX_SHADER);
fragment= glCreateShader(GL_FRAGMENT_SHADER);

glShaderSource(vertex,1,&vertex_shader_source,NULL);
glShaderSource(fragment,1,&fragment_shader_source,NULL);

glCompileShader(vertex);
glGetShaderiv(vertex,GL_COMPILE_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,
"ERROR: Weaver Metafont vertex shader compilation failed!\n");
return 0;
}

glCompileShader(fragment);
glGetShaderiv(fragment,GL_COMPILE_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,
"ERROR: Weaver Metafont fragment shader compilation failed!\n");
return 0;
}

prog= glCreateProgram();

glAttachShader(prog,vertex);
glAttachShader(prog,fragment);
glBindAttribLocation(prog,0,"vertex_data");
glLinkProgram(prog);
glGetProgramiv(prog,GL_LINK_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,"ERROR: Weaver Metafont shader linking failed!\n");
return 0;
}

glDeleteShader(vertex);
glDeleteShader(fragment);
return prog;
}
/*:385*//*389:*/
#line 10215 "weaver-interface-metafont.tex"

bool get_new_framebuffer(GLuint*new_framebuffer,GLuint*new_texture,
int width,int height){
glGenFramebuffers(1,new_framebuffer);
glGenTextures(1,new_texture);
glBindTexture(GL_TEXTURE_2D,*new_texture);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,
GL_UNSIGNED_BYTE,NULL);
glBindFramebuffer(GL_FRAMEBUFFER,*new_framebuffer);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,
*new_texture,0);
if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: OpenGL cannot create framebuffer!\n");
#endif
glBindTexture(GL_TEXTURE_2D,0);
return false;
}
glBindTexture(GL_TEXTURE_2D,0);
return true;
}
/*:389*//*391:*/
#line 10257 "weaver-interface-metafont.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height,bool clear_background){
glColorMask(true,true,true,true);
glViewport(0,0,dst_width,dst_height);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glUseProgram(program);
glUniformMatrix4fv(uniform_matrix,1,true,matrix);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,pic->texture);
glUniform1i(uniform_texture,0);
if(clear_background){

glClearColor(1.0,1.0,1.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
}
glDrawArrays(GL_TRIANGLE_FAN,0,4);
glBindTexture(GL_TEXTURE_2D,0);
}

void print_picture(struct picture_variable*pic){
float model_view_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
GLuint framebuffer;
GLuint texture;
unsigned char data[100000];
get_new_framebuffer(&framebuffer,&texture,pic->width,pic->height);
render_picture(pic,model_view_matrix,pic->width,pic->height,true);

glFinish();
glReadPixels(0,0,pic->width,pic->height,GL_RGBA,GL_UNSIGNED_BYTE,data);
{
int i,j;
for(i= pic->width*(pic->height-1)*4;
i>=0;i-= (pic->width*4)){
for(j= 0;j<(pic->width*4);j+= 4)
printf("(%hu %hu %hu %hu)",(unsigned char)data[i+j],(unsigned char)data[i+j+1],(unsigned char)data[i+j+2],(unsigned char)data[i+j+3]);
printf("\n");
}
}
}
/*:391*//*393:*/
#line 10320 "weaver-interface-metafont.tex"

void assign_picture_variable(struct metafont*mf,
struct picture_variable*target,
struct picture_variable*source){
GLuint temporary_framebuffer;
float model_view_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
if(target->texture!=0)
glDeleteTextures(1,&(target->texture));
get_new_framebuffer(&temporary_framebuffer,&(target->texture),
source->width,source->height);
render_picture(source,model_view_matrix,source->width,source->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
}
/*:393*//*395:*/
#line 10380 "weaver-interface-metafont.tex"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin_expression,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end_expression){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin_expression&&
(p->type==TYPE_SUM||p->type==TYPE_SUBTRACT)&&
prev->type!=TYPE_SUM&&prev->type!=TYPE_SUBTRACT){
last_operator= p;
before_last_operator= prev;
}
prev= p;
p= p->next;
}
if(last_operator==NULL||before_last_operator==NULL){
struct picture_variable a;
struct picture_variable*sec= &a;
/*400:*/
#line 10609 "weaver-interface-metafont.tex"

{
float matrix[16];
int i;
bool modified= false;
for(i= 0;i<16;i++)
if(i%5==0)
matrix[i]= 1.0;
else
matrix[i]= 0.0;
if(last_operator==NULL){
if(!eval_picture_secondary(mf,cx,begin_expression,end_expression,sec,
matrix,&modified))
return false;
}
else if(!eval_picture_secondary(mf,cx,last_operator->next,
end_expression,sec,matrix,&modified))
return false;
if(modified){
if(!apply_image_transformation(mf,result,sec,matrix))
return false;
if(sec->texture!=0)
glDeleteTextures(1,&(sec->texture));
}
else{
result->width= sec->width;
result->height= sec->height;
result->texture= sec->texture;
}
}
/*:400*/
#line 10402 "weaver-interface-metafont.tex"

return true;
}
else{
struct picture_variable a,b;
struct picture_variable*sec= &b;
if(last_operator==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Incomplete picture expression "
"ending with '+' or '-'.\n",
mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_picture_expression(mf,cx,begin_expression,before_last_operator,&a))
return false;
/*400:*/
#line 10609 "weaver-interface-metafont.tex"

{
float matrix[16];
int i;
bool modified= false;
for(i= 0;i<16;i++)
if(i%5==0)
matrix[i]= 1.0;
else
matrix[i]= 0.0;
if(last_operator==NULL){
if(!eval_picture_secondary(mf,cx,begin_expression,end_expression,sec,
matrix,&modified))
return false;
}
else if(!eval_picture_secondary(mf,cx,last_operator->next,
end_expression,sec,matrix,&modified))
return false;
if(modified){
if(!apply_image_transformation(mf,result,sec,matrix))
return false;
if(sec->texture!=0)
glDeleteTextures(1,&(sec->texture));
}
else{
result->width= sec->width;
result->height= sec->height;
result->texture= sec->texture;
}
}
/*:400*/
#line 10418 "weaver-interface-metafont.tex"

/*399:*/
#line 10515 "weaver-interface-metafont.tex"


GLuint temporary_framebuffer= 0;
float model_view_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
result->width= ((a.width>=b.width)?(a.width):(b.width));
result->height= ((a.height>=b.height)?(a.height):(b.height));
get_new_framebuffer(&temporary_framebuffer,&(result->texture),
result->width,result->height);

model_view_matrix[0]= (double)a.width/(double)result->width;
model_view_matrix[5]= (double)a.height/(double)result->height;
render_picture(&a,model_view_matrix,result->width,result->height,true);

model_view_matrix[0]= (double)b.width/(double)result->width;
model_view_matrix[5]= (double)b.height/(double)result->height;
if(last_operator->type==TYPE_SUBTRACT){
glEnable(GL_BLEND);

glBlendFunc(GL_ONE,GL_ONE);

glBlendEquationSeparate(GL_MAX,GL_FUNC_REVERSE_SUBTRACT);
glUseProgram(inv_program);
glUniformMatrix4fv(uniform_inv_matrix,1,true,model_view_matrix);
glUniform1i(uniform_inv_texture,0);
glBindTexture(GL_TEXTURE_2D,b.texture);
glDrawArrays(GL_TRIANGLE_FAN,0,4);
glBlendEquation(GL_FUNC_ADD);
glDisable(GL_BLEND);
}
else{
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBlendEquation(GL_FUNC_ADD);
render_picture(&b,model_view_matrix,result->width,result->height,false);
glDisable(GL_BLEND);
}

glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
/*:399*/
#line 10419 "weaver-interface-metafont.tex"

if(a.texture!=0)
glDeleteTextures(1,&(a.texture));
if(b.texture!=0)
glDeleteTextures(1,&(b.texture));
return true;
}
}
/*:395*//*402:*/
#line 10661 "weaver-interface-metafont.tex"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result,
float*matrix,bool*modified){
DECLARE_NESTING_CONTROL();
struct generic_token*p,*prev= NULL,*last_transformer= NULL,
*before_last_transformer= begin_expression;
p= begin_expression;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_ROTATED||
p->type==TYPE_SCALED||p->type==TYPE_SHIFTED||
p->type==TYPE_SLANTED||p->type==TYPE_XSCALED||
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED||
p->type==TYPE_TRANSFORMED)){
last_transformer= p;
before_last_transformer= prev;
}
prev= p;
if(p!=end_expression)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(last_transformer==NULL)
return eval_picture_primary(mf,cx,begin_expression,end_expression,result);
else{
if(!eval_picture_secondary(mf,cx,begin_expression,
before_last_transformer,result,matrix,modified))
return false;
if(last_transformer->type==TYPE_ROTATED){
/*404:*/
#line 10777 "weaver-interface-metafont.tex"

struct numeric_variable r;
float temp_matrix[16];
double rotation,cos_theta,sin_theta;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&r))
return false;
rotation= 0.017453292519943295*r.value;
sin_theta= sin(rotation);
cos_theta= cos(rotation);
memcpy(temp_matrix,matrix,16*sizeof(float));
matrix[0]= temp_matrix[0]*cos_theta-temp_matrix[1]*sin_theta;
matrix[1]= temp_matrix[0]*sin_theta+temp_matrix[1]*cos_theta;
matrix[4]= temp_matrix[4]*cos_theta-temp_matrix[5]*sin_theta;
matrix[5]= temp_matrix[4]*sin_theta+temp_matrix[5]*cos_theta;
matrix[8]= temp_matrix[8]*cos_theta-temp_matrix[9]*sin_theta;
matrix[9]= temp_matrix[8]*sin_theta+temp_matrix[9]*cos_theta;
matrix[12]= temp_matrix[12]*cos_theta-temp_matrix[13]*sin_theta;
matrix[13]= temp_matrix[12]*sin_theta+temp_matrix[13]*cos_theta;
*modified= true;
return true;
/*:404*/
#line 10694 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*403:*/
#line 10743 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
matrix[0]= temp_matrix[0]*a.value;
matrix[1]= temp_matrix[1]*a.value;
matrix[4]= temp_matrix[4]*a.value;
matrix[5]= temp_matrix[5]*a.value;
matrix[8]= temp_matrix[8]*a.value;
matrix[9]= temp_matrix[9]*a.value;
matrix[12]= temp_matrix[12]*a.value;
matrix[13]= temp_matrix[13]*a.value;
*modified= true;
return true;
/*:403*/
#line 10697 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*405:*/
#line 10812 "weaver-interface-metafont.tex"

struct pair_variable p;
float temp_matrix[16];
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
p.x= 2.0*(p.x/result->width);
p.y= 2.0*(p.y/result->height);
matrix[0]= temp_matrix[0]+temp_matrix[3]*p.x;
matrix[1]= temp_matrix[1]+temp_matrix[3]*p.y;
matrix[4]= temp_matrix[4]+temp_matrix[7]*p.x;
matrix[5]= temp_matrix[5]+temp_matrix[7]*p.y;
matrix[8]= temp_matrix[8]+temp_matrix[11]*p.x;
matrix[9]= temp_matrix[8]+temp_matrix[11]*p.y;
matrix[12]= temp_matrix[12]+temp_matrix[15]*p.x;
matrix[13]= temp_matrix[12]+temp_matrix[15]*p.y;
*modified= true;
return true;
/*:405*/
#line 10700 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*406:*/
#line 10844 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
matrix[0]= temp_matrix[0]+a.value*temp_matrix[1];
matrix[4]= temp_matrix[4]+a.value*temp_matrix[5];
matrix[8]= temp_matrix[8]+a.value*temp_matrix[9];
matrix[12]= temp_matrix[12]+a.value*temp_matrix[13];
*modified= true;
return true;
/*:406*/
#line 10703 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*407:*/
#line 10869 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
matrix[0]= temp_matrix[0]*a.value;
matrix[4]= temp_matrix[4]*a.value;
matrix[8]= temp_matrix[8]*a.value;
matrix[12]= temp_matrix[12]*a.value;
*modified= true;
return true;
/*:407*/
#line 10706 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*408:*/
#line 10894 "weaver-interface-metafont.tex"

struct numeric_variable a;
float temp_matrix[16];
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
matrix[1]= temp_matrix[1]*a.value;
matrix[5]= temp_matrix[5]*a.value;
matrix[9]= temp_matrix[9]*a.value;
matrix[13]= temp_matrix[13]*a.value;
*modified= true;
return true;
/*:408*/
#line 10709 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*409:*/
#line 10920 "weaver-interface-metafont.tex"

struct pair_variable p;
float temp_matrix[16];
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
matrix[0]= temp_matrix[0]*p.x-temp_matrix[1]*p.y;
matrix[1]= temp_matrix[0]*p.y+temp_matrix[1]*p.x;
matrix[4]= temp_matrix[4]*p.x-temp_matrix[5]*p.y;
matrix[5]= temp_matrix[4]*p.y+temp_matrix[5]*p.x;
matrix[8]= temp_matrix[8]*p.x-temp_matrix[9]*p.y;
matrix[9]= temp_matrix[8]*p.y+temp_matrix[9]*p.x;
matrix[12]= temp_matrix[12]*p.x-temp_matrix[13]*p.y;
matrix[13]= temp_matrix[12]*p.y+temp_matrix[13]*p.x;
*modified= true;
return true;
/*:409*/
#line 10712 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*410:*/
#line 10951 "weaver-interface-metafont.tex"

struct transform_variable t;
float temp_matrix[16];
if(!eval_transform_primary(mf,cx,last_transformer->next,end_expression,
&t))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
matrix[0]= temp_matrix[0]*t.value[2]+temp_matrix[1]*t.value[3]+
t.value[0];
matrix[1]= temp_matrix[0]*t.value[4]+temp_matrix[1]*t.value[5]+
t.value[1];
matrix[4]= temp_matrix[4]*t.value[2]+temp_matrix[5]*t.value[3]+
t.value[0];
matrix[5]= temp_matrix[4]*t.value[4]+temp_matrix[5]*t.value[5]+
t.value[1];
matrix[12]= temp_matrix[12]*t.value[2]+temp_matrix[13]*t.value[3]+
t.value[0];
matrix[13]= temp_matrix[12]*t.value[4]+temp_matrix[13]*t.value[5]+
t.value[1];
*modified= true;
return true;
/*:410*/
#line 10715 "weaver-interface-metafont.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:402*//*412:*/
#line 11018 "weaver-interface-metafont.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*origin,
float*matrix){
int i;
GLuint temporary_framebuffer= 0;



float min_x= INFINITY,min_y= INFINITY,max_x= -INFINITY,max_y= -INFINITY;
float origin_coordinates[8];
origin_coordinates[0]= -((float)origin->width)/2.0;
origin_coordinates[1]= -((float)origin->height)/2.0;
origin_coordinates[2]= ((float)origin->width)/2.0;
origin_coordinates[3]= -((float)origin->height)/2.0;
origin_coordinates[4]= ((float)origin->width)/2.0;
origin_coordinates[5]= ((float)origin->height)/2.0;
origin_coordinates[6]= -((float)origin->width)/2.0;
origin_coordinates[7]= ((float)origin->height)/2.0;
for(i= 0;i<8;i+= 2){
float x= origin_coordinates[i]*matrix[0]+
origin_coordinates[i+1]*matrix[4];
float y= origin_coordinates[i]*matrix[1]+
origin_coordinates[i+1]*matrix[5];
if(x> max_x)max_x= x;
if(x<min_x)min_x= x;
if(y> max_y)max_y= y;
if(y<min_y)min_y= y;
}

dst->width= (int)(max_x-min_x)+
(int)(origin->width*matrix[12]);
dst->height= (int)(max_y-min_y)+
(int)(origin->height*matrix[13]);


{
double x_correction= ((double)origin->width)/(double)dst->width;
double y_correction= ((double)origin->height)/(double)dst->height;
matrix[0]= matrix[0]*x_correction;
matrix[4]= matrix[4]*x_correction;
matrix[8]= matrix[8]*x_correction;
matrix[12]= matrix[12]*x_correction;
matrix[1]= matrix[1]*y_correction;
matrix[5]= matrix[5]*y_correction;
matrix[9]= matrix[9]*y_correction;
matrix[13]= matrix[13]*y_correction;
}






get_new_framebuffer(&temporary_framebuffer,&(dst->texture),dst->width,
dst->height);

render_picture(origin,matrix,dst->width,dst->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:412*//*416:*/
#line 11130 "weaver-interface-metafont.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*417:*/
#line 11172 "weaver-interface-metafont.tex"

GLuint temporary_framebuffer= 0;
float identity_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
struct symbolic_token*v= (struct symbolic_token*)begin_expression;
struct picture_variable*content= v->var;
if(content==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Using unknown variable '%s'.\n",
mf->file,begin_expression->line,v->value);
#endif
return false;
}
if(content->type!=TYPE_T_PICTURE){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Got non-picture variable (%d) in "
"picture expression.\n",
mf->file,begin_expression->line,content->type);
#endif
return false;
}

result->width= content->width;
result->height= content->height;
get_new_framebuffer(&temporary_framebuffer,&(result->texture),
result->width,result->height);

render_picture(content,identity_matrix,result->width,result->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
/*:417*/
#line 11137 "weaver-interface-metafont.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*418:*/
#line 11215 "weaver-interface-metafont.tex"

struct generic_token*t= begin_expression->next;
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
t= t->next;
}
return eval_picture_expression(mf,cx,begin_expression->next,t,result);
/*:418*/
#line 11143 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_NULLPICTURE){
/*419:*/
#line 11240 "weaver-interface-metafont.tex"

struct generic_token*begin_pair_expression,*end_pair_expression;
struct pair_variable p;
unsigned char*data;
begin_pair_expression= begin_expression->next;
end_pair_expression= end_expression;
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing pair expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_pair_primary(mf,cx,begin_pair_expression,end_pair_expression,&p))
return false;
result->width= p.x;
result->height= p.y;
data= temporary_alloc(p.x*p.y*4);
if(data==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: Not enough memory.\n");
#endif
return false;
}

memset(data,255,result->width*result->height*4);
{
int i,size= result->width*result->height*4;
for(i= 3;i<size;i+= 4)
data[i]= 0;
}
glGenTextures(1,&(result->texture));
glBindTexture(GL_TEXTURE_2D,result->texture);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,result->width,result->height,0,
GL_RGBA,GL_UNSIGNED_BYTE,data);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glBindTexture(GL_TEXTURE_2D,0);
if(temporary_free!=NULL)
temporary_free(data);
return true;
/*:419*/
#line 11146 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_SUM){
/*420:*/
#line 11292 "weaver-interface-metafont.tex"

struct generic_token*p= begin_expression->next;
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing image expression "
"after '+'.\n",mf->file,begin_expression->line);
#endif
return false;
}
return eval_picture_primary(mf,cx,p,end_expression,result);
/*:420*/
#line 11149 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_SUBTRACT){
/*421:*/
#line 11314 "weaver-interface-metafont.tex"

struct picture_variable p;
GLuint temporary_framebuffer= 0;
float identity_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing picture expression after "
"'-'.\n",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_picture_primary(mf,cx,begin_expression->next,end_expression,&p))
return false;

result->width= p.width;
result->height= p.height;
get_new_framebuffer(&temporary_framebuffer,&(result->texture),
result->width,result->height);

glClearColor(1.0,1.0,1.0,1.0);
glClear(GL_COLOR_BUFFER_BIT);

glEnable(GL_BLEND);
glBlendFuncSeparate(GL_ONE,GL_ONE,GL_ONE,GL_ONE);
glBlendEquationSeparate(GL_FUNC_REVERSE_SUBTRACT,GL_FUNC_REVERSE_SUBTRACT);

render_picture(&p,identity_matrix,result->width,result->height,false);

glDisable(GL_BLEND);
glDeleteTextures(1,&(p.texture));
glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
/*:421*/
#line 11152 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_SUBPICTURE){
/*422:*/
#line 11365 "weaver-interface-metafont.tex"

struct pair_variable pair_offset,subpicture_size;
struct picture_variable original_picture;
/*423:*/
#line 11382 "weaver-interface-metafont.tex"

{
DECLARE_NESTING_CONTROL();
struct generic_token*begin_pair1= NULL,*end_pair1= NULL,
*begin_pair2= NULL,*end_pair2= NULL,
*begin_pic= NULL,*end_pic= NULL,
*p= begin_expression->next,
*last_token= begin_expression;
int state= 0;
begin_pair1= p;
while(p!=end_expression&&p!=NULL){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p->type==TYPE_AND){
if(state!=0||last_token->type==TYPE_SUBPICTURE){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Malformed subpicture expression.\n",
mf->file,p->line);
#endif
return false;
}
end_pair1= last_token;
state++;
begin_pair2= p->next;
}
else if(IS_NOT_NESTED()&&p->type==TYPE_OF){
if(state!=1||last_token->type==TYPE_AND){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Malformed subpicture expression.\n",
mf->file,p->line);
#endif
return false;
}
end_pair2= last_token;
state++;
begin_pic= p->next;
}
last_token= p;
p= p->next;
}
if(p==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,
"METAFONT: Error: %s:%d: Malformed subpicture expression.\n",
mf->file,p->line);
#endif
return false;
}
end_pic= p;
if(!eval_pair_primary(mf,cx,begin_pair1,end_pair1,&pair_offset))
return false;
if(!eval_pair_primary(mf,cx,begin_pair2,end_pair2,&subpicture_size))
return false;
if(!eval_picture_primary(mf,cx,begin_pic,end_pic,&original_picture))
return false;
}
/*:423*/
#line 11368 "weaver-interface-metafont.tex"

/*424:*/
#line 11448 "weaver-interface-metafont.tex"

{
GLuint temporary_framebuffer= 0;
float render_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
get_new_framebuffer(&temporary_framebuffer,&(result->texture),
subpicture_size.x,subpicture_size.y);
result->width= subpicture_size.x;
result->height= subpicture_size.y;

glClearColor(1.0,1.0,1.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);

render_matrix[0]= original_picture.width/subpicture_size.x;
render_matrix[5]= original_picture.height/subpicture_size.y;

render_matrix[12]= -2.0*(pair_offset.x+
0.5*(subpicture_size.x-original_picture.width))/
subpicture_size.x;
render_matrix[13]= -2.0*(pair_offset.y+
0.5*(subpicture_size.y-original_picture.height))/
subpicture_size.y;

render_picture(&original_picture,render_matrix,result->width,result->height,
false);


glDisable(GL_BLEND);
glDeleteTextures(1,&(original_picture.texture));
glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:424*/
#line 11369 "weaver-interface-metafont.tex"

return false;
/*:422*/
#line 11155 "weaver-interface-metafont.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:416*//*434:*/
#line 11750 "weaver-interface-metafont.tex"

bool eval_boolean_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin_expression,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end_expression){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin_expression&&
(p->type==TYPE_LT||p->type==TYPE_LEQ||
p->type==TYPE_GT||p->type==TYPE_GEQ||
p->type==TYPE_NEQ||p->type==TYPE_ASSIGNMENT)){
last_operator= p;
before_last_operator= prev;
}
prev= p;
p= p->next;
}
if(last_operator==NULL)
return eval_boolean_tertiary(mf,cx,begin_expression,end_expression,
result);
else{
int type;
if(before_last_operator==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Relational operator without "
"l-value.\n",mf->file,begin_expression->line);
#endif
return false;
}
type= get_tertiary_expression_type(mf,cx,last_operator->next,
end_expression);
switch(type){
case TYPE_T_NUMERIC:
{
struct numeric_variable a,b;
if(!eval_numeric_expression(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_numeric_expression(mf,cx,last_operator->next,
end_expression,&b))
return false;
switch(last_operator->type){
case TYPE_LT:
result->value= a.value<b.value;
return true;
case TYPE_LEQ:
result->value= a.value<=b.value;
return true;
case TYPE_GT:
result->value= a.value> b.value;
return true;
case TYPE_GEQ:
result->value= a.value>=b.value;
return true;
case TYPE_ASSIGNMENT:
result->value= a.value==b.value;
return true;
case TYPE_NEQ:
result->value= a.value!=b.value;
return true;
}
break;
}
case TYPE_T_PAIR:
{
struct pair_variable a,b;
if(!eval_pair_expression(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_pair_expression(mf,cx,last_operator->next,
end_expression,&b))
return false;
switch(last_operator->type){
case TYPE_LT:
result->value= (a.x<b.x)||(a.x==b.x&&a.y<b.y);
return true;
case TYPE_LEQ:
result->value= (a.x<b.x)||(a.x==b.x&&a.y<=b.y);
return true;
case TYPE_GT:
result->value= (a.x> b.x)||(a.x==b.x&&a.y> b.y);
return true;
case TYPE_GEQ:
result->value= (a.x> b.x)||(a.x==b.x&&a.y> b.y);
return true;
case TYPE_ASSIGNMENT:
result->value= (a.x==b.x&&a.y==b.y);
return true;
case TYPE_NEQ:
result->value= (a.x!=b.x||a.y!=b.y);
return true;
}
break;
}
case TYPE_T_TRANSFORM:
{
struct transform_variable a,b;
int i;
if(!eval_transform_expression(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_transform_expression(mf,cx,last_operator->next,
end_expression,&b))
return false;
switch(last_operator->type){
case TYPE_LT:
for(i= 0;i<5;i++)
if(a.value[i]!=b.value[i]){
result->value= (a.value[i]<b.value[i]);
return true;
}
result->value= (a.value[i]<b.value[i]);
return true;
case TYPE_LEQ:
for(i= 0;i<5;i++)
if(a.value[i]!=b.value[i]){
result->value= (a.value[i]<b.value[i]);
return true;
}
result->value= (a.value[i]<=b.value[i]);
return true;
case TYPE_GT:
for(i= 0;i<5;i++)
if(a.value[i]!=b.value[i]){
result->value= (a.value[i]> b.value[i]);
return true;
}
result->value= (a.value[i]> b.value[i]);
return true;
case TYPE_GEQ:
for(i= 0;i<5;i++)
if(a.value[i]!=b.value[i]){
result->value= (a.value[i]> b.value[i]);
return true;
}
result->value= (a.value[i]>=b.value[i]);
return true;
case TYPE_ASSIGNMENT:
for(i= 0;i<5;i++)
if(a.value[i]!=b.value[i]){
result->value= false;
return true;
}
result->value= (a.value[i]==b.value[i]);
return true;
case TYPE_NEQ:
for(i= 0;i<5;i++)
if(a.value[i]!=b.value[i]){
result->value= true;
return true;
}
result->value= (a.value[i]!=b.value[i]);
return true;
}
break;
}
case TYPE_T_BOOLEAN:
{
struct boolean_variable a,b;
a.value= b.value= -1;
if(!eval_boolean_expression(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_boolean_tertiary(mf,cx,last_operator->next,
end_expression,&b))
return false;
switch(last_operator->type){
case TYPE_LT:
result->value= a.value<b.value;
return true;
case TYPE_LEQ:
result->value= a.value<=b.value;
return true;
case TYPE_GT:
result->value= a.value> b.value;
return true;
case TYPE_GEQ:
result->value= a.value>=b.value;
return true;
case TYPE_ASSIGNMENT:
result->value= (a.value==b.value);
return true;
case TYPE_NEQ:
result->value= (a.value!=b.value);
return true;
}
break;
}
default:
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression after boolean operator.\n",mf->file,
begin_expression->line);
#endif
return false;
}
return true;
}
}
/*:434*//*438:*/
#line 12001 "weaver-interface-metafont.tex"

bool eval_boolean_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin_expression,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end_expression){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin_expression&&p->type==TYPE_OR){
last_operator= p;
before_last_operator= prev;
}
prev= p;
p= p->next;
}
if(last_operator==NULL)
return eval_boolean_secondary(mf,cx,begin_expression,end_expression,
result);
else{
struct boolean_variable a,b;
a.value= b.value= -1;
if(!eval_boolean_secondary(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_boolean_tertiary(mf,cx,last_operator->next,
end_expression,&b))
return false;
result->value= (a.value||b.value);
return true;
}
}
/*:438*//*440:*/
#line 12069 "weaver-interface-metafont.tex"

bool eval_boolean_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin_expression,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end_expression){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin_expression&&p->type==TYPE_AND){
last_operator= p;
before_last_operator= prev;
}
prev= p;
p= p->next;
}
if(last_operator==NULL)
return eval_boolean_primary(mf,cx,begin_expression,end_expression,
result);
else{
struct boolean_variable a,b;
a.value= b.value= -1;
if(!eval_boolean_secondary(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_boolean_primary(mf,cx,last_operator->next,
end_expression,&b))
return false;
result->value= (a.value&&b.value);
return true;
}
}
/*:440*//*444:*/
#line 12162 "weaver-interface-metafont.tex"

bool eval_boolean_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result){
switch(begin_expression->type){
case TYPE_SYMBOLIC:
struct boolean_variable*var;
var= ((struct symbolic_token*)begin_expression)->var;
if(var->value==-1){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unitialized variable "
"'%s'.\n",mf->file,begin_expression->line,
((struct symbolic_token*)begin_expression)->value);
#endif
return false;
}
result->value= var->value;
return true;
break;
case TYPE_TRUE:
if(end_expression!=begin_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"boolean expression. Did you miss a ';'?\n",
mf->file,begin_expression->line);
#endif
printf("DEBUG: %d %d\n",begin_expression->type,end_expression->type);
return false;
}
result->value= 1;
return true;
break;
case TYPE_FALSE:
if(end_expression!=begin_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"boolean expression. Did you miss a ';'?\n",
mf->file,begin_expression->line);
#endif
printf("DEBUG: %d %d %d\n",begin_expression->type,
((struct generic_token*)begin_expression->next)->type,
end_expression->type);
printf("DEBUG: %p %p\n",begin_expression,end_expression);
return false;
}
result->value= 0;
return true;
break;
case TYPE_CYCLE:
struct path_variable path;
if(!eval_path_primary(mf,cx,begin_expression->next,end_expression,
&path))
return false;
result->value= path.cyclic;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&path,false);
return true;
break;
case TYPE_ODD:
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin_expression->next,end_expression,
&num))
return false;
result->value= (((int)round(num.value))%2);
return true;
break;
case TYPE_NOT:
struct boolean_variable b;
if(!eval_boolean_primary(mf,cx,begin_expression->next,end_expression,
&b))
return false;
result->value= !(b.value);
return true;
break;
case TYPE_OPEN_PARENTHESIS:
if(end_expression->type!=TYPE_CLOSE_PARENTHESIS){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
struct generic_token*last_token= begin_expression;
while(last_token->next!=end_expression)
last_token= last_token->next;
return eval_boolean_expression(mf,cx,begin_expression->next,
last_token,result);
break;
default:
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
}
/*:444*//*446:*/
#line 12340 "weaver-interface-metafont.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr){
if(begin_expr==end_expr){
if(begin_expr->type==TYPE_SYMBOLIC){
struct variable*var= (struct variable*)
((struct symbolic_token*)begin_expr)->var;
return var->type;
}
if(begin_expr->type==TYPE_TRUE||begin_expr->type==TYPE_FALSE||
begin_expr->type==TYPE_NOT)
return TYPE_T_BOOLEAN;
if(begin_expr->type==TYPE_NUMERIC||
begin_expr->type==TYPE_NORMALDEVIATE)
return TYPE_T_NUMERIC;
else
return-1;
}
else{
if(begin_expr->type==TYPE_CYCLE||begin_expr->type==TYPE_ODD||
begin_expr->type==TYPE_NOT)
return TYPE_T_BOOLEAN;

if(begin_expr->type==TYPE_POINT||
begin_expr->type==TYPE_PRECONTROL||
begin_expr->type==TYPE_POSTCONTROL)
return TYPE_T_PAIR;

if(begin_expr->type==TYPE_LENGTH||begin_expr->type==TYPE_XPART||
begin_expr->type==TYPE_YPART||begin_expr->type==TYPE_ANGLE||
begin_expr->type==TYPE_XXPART||begin_expr->type==TYPE_FLOOR||
begin_expr->type==TYPE_XYPART||begin_expr->type==TYPE_SIND||
begin_expr->type==TYPE_YXPART||begin_expr->type==TYPE_SQRT||
begin_expr->type==TYPE_YYPART||begin_expr->type==TYPE_LOG||
begin_expr->type==TYPE_COSD||begin_expr->type==TYPE_EXP||
begin_expr->type==TYPE_UNIFORMDEVIATE)
return TYPE_T_NUMERIC;

if(begin_expr->type==TYPE_SUM||begin_expr->type==TYPE_SUBTRACT)
return get_primary_expression_type(mf,cx,begin_expr->next,end_expr);

if(begin_expr->type==TYPE_NUMERIC){
struct generic_token*t= begin_expr;
while(t!=NULL&&t!=end_expr){
if(t->type==TYPE_OPEN_BRACKETS||t->type==TYPE_PRECONTROL||
t->type==TYPE_OPEN_PARENTHESIS||t->type==TYPE_POINT||
t->type==TYPE_POSTCONTROL)
return TYPE_T_PAIR;
t= t->next;
}
return TYPE_T_NUMERIC;
}


if((begin_expr->type==TYPE_OPEN_PARENTHESIS&&
end_expr->type!=TYPE_CLOSE_PARENTHESIS)||
begin_expr->type==TYPE_NORMALDEVIATE)
return TYPE_T_PAIR;
if(begin_expr->type==TYPE_OPEN_PARENTHESIS&&
end_expr->type==TYPE_CLOSE_PARENTHESIS&&
begin_expr->next!=end_expr){
DECLARE_NESTING_CONTROL();
int number_of_commas= 0;
struct generic_token*t= begin_expr->next;
while(t!=NULL&&t->next!=end_expr){
COUNT_NESTING(t);
if(IS_NOT_NESTED()&&t->type==TYPE_COMMA)
number_of_commas++;
t= t->next;
}
if(number_of_commas==0)
return get_tertiary_expression_type(mf,cx,begin_expr->next,t);
else if(number_of_commas==1)
return TYPE_T_PAIR;
else if(number_of_commas==5)
return TYPE_T_TRANSFORM;
}
return-1;
}
}
/*:446*//*447:*/
#line 12451 "weaver-interface-metafont.tex"

int get_secondary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr){
DECLARE_NESTING_CONTROL();
struct generic_token*t= begin_expr,*prev= NULL,*last_op= NULL;
struct generic_token*last_fraction= NULL;
struct generic_token*before_last_op= NULL,*prev_prev= NULL;
if(begin_expr==end_expr)
return get_primary_expression_type(mf,cx,begin_expr,end_expr);
while(t!=end_expr&&t!=NULL){
COUNT_NESTING(t);
if(IS_NOT_NESTED()){
if(t->type==TYPE_AND)
return TYPE_T_BOOLEAN;
if(t->type==TYPE_TRANSFORMED||t->type==TYPE_ROTATED||
t->type==TYPE_SCALED||t->type==TYPE_SHIFTED||
t->type==TYPE_SLANTED||t->type==TYPE_XSCALED||
t->type==TYPE_YSCALED||t->type==TYPE_ZSCALED){
if(prev==NULL)
return-1;
return get_secondary_expression_type(mf,cx,begin_expr,prev);
}
if(t->type==TYPE_MULTIPLICATION||t->type==TYPE_DIVISION){
if(t->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
t!=end_expr&&
((struct generic_token*)t->next)->type!=TYPE_NUMERIC&&
last_fraction!=prev_prev)
last_fraction= t;
else{
last_op= t;
before_last_op= prev;
}
}
}
prev_prev= prev;
prev= t;
t= t->next;
}
if(last_op!=NULL){
int s= get_primary_expression_type(mf,cx,last_op->next,end_expr)+
get_secondary_expression_type(mf,cx,begin_expr,before_last_op);
if(s==2*TYPE_T_NUMERIC)
return TYPE_T_NUMERIC;
else if(s==TYPE_T_NUMERIC+TYPE_T_PAIR)
return TYPE_T_PAIR;
else return-1;
}
else return get_primary_expression_type(mf,cx,begin_expr,end_expr);
}
/*:447*//*448:*/
#line 12526 "weaver-interface-metafont.tex"

int get_tertiary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr){
DECLARE_NESTING_CONTROL();
struct generic_token*t= begin_expr,*prev= NULL,*last_op= NULL;
if(begin_expr==end_expr)
return get_primary_expression_type(mf,cx,begin_expr,end_expr);
while(t!=end_expr&&t!=NULL){
COUNT_NESTING(t);
if(IS_NOT_NESTED()){
if(t->type==TYPE_OR||t->type==TYPE_LT||
t->type==TYPE_GT||t->type==TYPE_GEQ||
t->type==TYPE_LEQ||t->type==TYPE_ASSIGNMENT||
t->type==TYPE_NEQ){
return TYPE_T_BOOLEAN;
}
if(t->type==TYPE_PYTHAGOREAN_SUM||
t->type==TYPE_PYTHAGOREAN_SUBTRACT){
return TYPE_T_NUMERIC;
}
if(IS_VALID_SUM_OR_SUB(prev,t)&&t!=end_expr)
last_op= t;
}
prev= t;
t= t->next;
}
if(last_op!=NULL)
return get_secondary_expression_type(mf,cx,last_op->next,end_expr);
else return get_secondary_expression_type(mf,cx,begin_expr,end_expr);
}
/*:448*//*456:*/
#line 12877 "weaver-interface-metafont.tex"

bool is_pen_counterclockwise(struct pen_variable*pen){
int i,index= 0;
int size= pen->format->length;
float smallest_y= INFINITY,biggest_x= -INFINITY;
if(pen->flags&FLAG_ORIENTATION)
return(pen->flags&FLAG_COUNTERCLOCKWISE);
for(i= 0;i<size;i++){
if(pen->format->points[i].y<smallest_y||
(pen->format->points[i].y==smallest_y&&
pen->format->points[i].y> biggest_x)){
smallest_y= pen->format->points[i].y;
biggest_x= pen->format->points[i].x;
index= i;
}
}
{
int n= (index-1)%size,p= (index+1)%size;
while(pen->format->points[index].x==pen->format->points[n].x&&
pen->format->points[index].y==pen->format->points[n].y)
n= (n+1)%size;
while(pen->format->points[index].x==pen->format->points[p].x&&
pen->format->points[index].y==pen->format->points[p].y)
p= (p-1)%size;
float ap_x= pen->format->points[p].x-
pen->format->points[index].x;
float ap_y= pen->format->points[p].y-
pen->format->points[index].y;
float an_x= pen->format->points[n].x-
pen->format->points[index].x;
float an_y= pen->format->points[n].y-
pen->format->points[index].y;
float prod= ap_x*an_x+ap_y*an_y;
pen->flags+= FLAG_ORIENTATION;
pen->flags+= FLAG_COUNTERCLOCKWISE*(prod> 0);
return(prod> 0);
}
}
/*:456*//*458:*/
#line 12929 "weaver-interface-metafont.tex"

bool triangulate_pen(struct pen_variable*pen){
if(pen->gl_vbo!=0)
return true;
/*459:*/
#line 12950 "weaver-interface-metafont.tex"

if((pen->flags|FLAG_NULL)||(pen->flags|FLAG_SQUARE))
return true;
/*:459*/
#line 12933 "weaver-interface-metafont.tex"

/*460:*/
#line 12969 "weaver-interface-metafont.tex"

if((pen->flags|FLAG_STRAIGHT)&&(pen->flags|FLAG_CONVEX)){
int i,index,increment;
GLsizei size= sizeof(float)*2*pen->format->length;
float*data= (float*)temporary_alloc(size);
if(data==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: Not enough memory.\n");
#endif
return false;
}
if(is_pen_counterclockwise(pen)){
index= 0;
increment= 1;
}
else{
index= pen->format->length-1;
increment= -1;
}
for(i= 0;i<pen->format->length;i++){
data[2*i]= pen->format->points[index].x;
data[2*i+1]= pen->format->points[index].y;
index+= increment;
}
glGenBuffers(1,&(pen->gl_vbo));
glBindBuffer(GL_ARRAY_BUFFER,pen->gl_vbo);
glBufferData(pen->gl_vbo,size,data,GL_STATIC_DRAW);
if(temporary_free!=NULL)
temporary_free(data);
return true;
}
/*:460*/
#line 12934 "weaver-interface-metafont.tex"

}
/*:458*/
#line 236 "weaver-interface-metafont.tex"

/*9:*/
#line 265 "weaver-interface-metafont.tex"

bool _Winit_metafont(void*(*t_alloc)(size_t),
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
/*380:*/
#line 10061 "weaver-interface-metafont.tex"

glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);

glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
/*:380*//*386:*/
#line 10184 "weaver-interface-metafont.tex"

{
program= compile_shader_program(vertex_shader,fragment_shader);
uniform_matrix= glGetUniformLocation(program,"model_view_matrix");
uniform_texture= glGetUniformLocation(program,"texture1");
}
/*:386*//*397:*/
#line 10493 "weaver-interface-metafont.tex"

{
inv_program= compile_shader_program(vertex_shader,fragment_shader_inverse);
uniform_inv_matrix= glGetUniformLocation(inv_program,"model_view_matrix");
uniform_inv_texture= glGetUniformLocation(inv_program,"texture1");
}
/*:397*/
#line 277 "weaver-interface-metafont.tex"

return true;
}
/*:9*//*10:*/
#line 288 "weaver-interface-metafont.tex"

void _Wfinish_metafont(void){
/*381:*/
#line 10072 "weaver-interface-metafont.tex"

glDeleteBuffers(1,&vbo);
/*:381*//*387:*/
#line 10196 "weaver-interface-metafont.tex"

glDeleteProgram(program);
/*:387*//*398:*/
#line 10505 "weaver-interface-metafont.tex"

glDeleteProgram(inv_program);
/*:398*/
#line 290 "weaver-interface-metafont.tex"

}
/*:10*/
#line 237 "weaver-interface-metafont.tex"

/*:7*/
