/*7:*/
#line 208 "weaver-interface-metafont_en.tex"

#include "metafont.h"
/*17:*/
#line 449 "weaver-interface-metafont_en.tex"

#include <stdio.h> 
/*:17*//*19:*/
#line 472 "weaver-interface-metafont_en.tex"

#include <ctype.h> 
/*:19*//*39:*/
#line 903 "weaver-interface-metafont_en.tex"

#include <string.h> 
/*:39*//*82:*/
#line 1844 "weaver-interface-metafont_en.tex"

#include <math.h> 
/*:82*//*248:*/
#line 6157 "weaver-interface-metafont_en.tex"

#include <complex.h> 
/*:248*/
#line 210 "weaver-interface-metafont_en.tex"

/*85:*/
#line 1902 "weaver-interface-metafont_en.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
/*:85*//*97:*/
#line 2165 "weaver-interface-metafont_en.tex"

#define FLAG_CONVEX   1
#define FLAG_STRAIGHT 2
#define FLAG_CIRCULAR 4
#define FLAG_SQUARE   8
#define FLAG_NULL    16
/*:97*//*103:*/
#line 2324 "weaver-interface-metafont_en.tex"

#define INTERNAL_PEN_CURRENTPEN 0
#define INTERNAL_PEN_PENSQUARE  1
/*:103*//*112:*/
#line 2452 "weaver-interface-metafont_en.tex"

#define INTERNAL_PICTURE_CURRENTPICTURE 0
/*:112*//*125:*/
#line 2756 "weaver-interface-metafont_en.tex"

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
/*:125*//*126:*/
#line 2801 "weaver-interface-metafont_en.tex"

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
/*:126*/
#line 211 "weaver-interface-metafont_en.tex"

/*11:*/
#line 294 "weaver-interface-metafont_en.tex"

#define TYPE_NUMERIC 1
struct numeric_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
float value;
};
/*:11*//*12:*/
#line 310 "weaver-interface-metafont_en.tex"

#define TYPE_STRING 2
struct string_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
char value[5];
};
/*:12*//*13:*/
#line 336 "weaver-interface-metafont_en.tex"

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
/*:13*//*14:*/
#line 360 "weaver-interface-metafont_en.tex"

#define TYPE_OPEN_PARENTHESIS  4 
#define TYPE_CLOSE_PARENTHESIS 5 
#define TYPE_COMMA             6 
#define TYPE_SEMICOLON         7 
/*41:*/
#line 973 "weaver-interface-metafont_en.tex"

#define TYPE_END             8 
#define TYPE_DUMP            9 
/*:41*//*53:*/
#line 1238 "weaver-interface-metafont_en.tex"

#define TYPE_BEGINGROUP            10 
#define TYPE_ENDGROUP              11 
/*:53*//*61:*/
#line 1406 "weaver-interface-metafont_en.tex"

#define TYPE_T_BOOLEAN               12 
#define TYPE_T_PATH                  13 
#define TYPE_T_PEN                   14 
#define TYPE_T_PICTURE               15 
#define TYPE_T_TRANSFORM             16 
#define TYPE_T_PAIR                  17 
#define TYPE_T_NUMERIC               18 
/*:61*//*115:*/
#line 2512 "weaver-interface-metafont_en.tex"

#define TYPE_ASSIGNMENT            19 
#define TYPE_ASSIGNMENT2           20 
/*:115*//*122:*/
#line 2715 "weaver-interface-metafont_en.tex"

#define TYPE_SUM                   21 
#define TYPE_SUBTRACT              22 
#define TYPE_PYTHAGOREAN_SUM       23 
#define TYPE_PYTHAGOREAN_SUBTRACT  24 
#define TYPE_OPEN_BRACKETS         25 
#define TYPE_CLOSE_BRACKETS        26 
#define TYPE_OPEN_BRACES           27 
#define TYPE_CLOSE_BRACES          28 
/*:122*//*129:*/
#line 2928 "weaver-interface-metafont_en.tex"

#define TYPE_MULTIPLICATION        29 
#define TYPE_DIVISION              30 
/*:129*//*133:*/
#line 3051 "weaver-interface-metafont_en.tex"

#define TYPE_LENGTH         31 
#define TYPE_SQRT           32 
#define TYPE_SIND           33 
#define TYPE_COSD           34 
#define TYPE_LOG            35 
#define TYPE_EXP            36 
#define TYPE_FLOOR          37 
#define TYPE_UNIFORMDEVIATE 38 
/*:133*//*151:*/
#line 3471 "weaver-interface-metafont_en.tex"

#define TYPE_NORMALDEVIATE  39 
/*:151*//*167:*/
#line 3841 "weaver-interface-metafont_en.tex"

#define TYPE_ROTATED  40 
#define TYPE_SCALED   41 
#define TYPE_SHIFTED  42 
#define TYPE_SLANTED  43 
#define TYPE_XSCALED  44 
#define TYPE_YSCALED  45 
#define TYPE_ZSCALED  46 
/*:167*//*187:*/
#line 4487 "weaver-interface-metafont_en.tex"

#define TYPE_XPART  47 
#define TYPE_YPART  48 
#define TYPE_ANGLE  49 
/*:187*//*200:*/
#line 4744 "weaver-interface-metafont_en.tex"

#define TYPE_CYCLE          50 
#define TYPE_AMPERSAND      51 
#define TYPE_JOIN           52 
#define TYPE_TENSION        53 
#define TYPE_AND            54 
#define TYPE_ATLEAST        55 
#define TYPE_CONTROLS       56 
#define TYPE_CURL           57 
#define TYPE_STRAIGHT_JOIN   58 
/*:200*//*279:*/
#line 6937 "weaver-interface-metafont_en.tex"

#define TYPE_REVERSE        59 
#define TYPE_SUBPATH        60 
#define TYPE_OF             61 
/*:279*//*296:*/
#line 7501 "weaver-interface-metafont_en.tex"

#define TYPE_POINT             62 
#define TYPE_PRECONTROL        63 
#define TYPE_POSTCONTROL       64 
/*:296*//*317:*/
#line 8182 "weaver-interface-metafont_en.tex"

#define TYPE_NULLPEN        65 
#define TYPE_PENCIRCLE      66 
#define TYPE_MAKEPEN        67 
/*:317*//*328:*/
#line 8482 "weaver-interface-metafont_en.tex"

#define TYPE_MAKEPATH       68 
/*:328*//*365:*/
#line 9551 "weaver-interface-metafont_en.tex"

#define TYPE_NULLPICTURE        69 
/*:365*//*379:*/
#line 9909 "weaver-interface-metafont_en.tex"

#define TYPE_TOTALWEIGHT        70 
/*:379*/
#line 365 "weaver-interface-metafont_en.tex"


struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:14*//*63:*/
#line 1445 "weaver-interface-metafont_en.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:63*//*64:*/
#line 1467 "weaver-interface-metafont_en.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:64*//*80:*/
#line 1817 "weaver-interface-metafont_en.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:80*//*88:*/
#line 1950 "weaver-interface-metafont_en.tex"

struct pair_variable{
int type;
int nesting_level;
void*next;
float x,y;
};
/*:88*//*90:*/
#line 2010 "weaver-interface-metafont_en.tex"

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
/*:90*//*96:*/
#line 2126 "weaver-interface-metafont_en.tex"

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
/*:96*//*106:*/
#line 2369 "weaver-interface-metafont_en.tex"

struct picture_variable{
int type;
int nesting_level;
void*next;
int width,height;
GLuint texture;
};
/*:106*/
#line 212 "weaver-interface-metafont_en.tex"

/*8:*/
#line 231 "weaver-interface-metafont_en.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:8*//*37:*/
#line 856 "weaver-interface-metafont_en.tex"

static char*list_of_keywords[]= {
/*42:*/
#line 983 "weaver-interface-metafont_en.tex"

"end","dump",
/*:42*//*54:*/
#line 1247 "weaver-interface-metafont_en.tex"

"begingroup","endgroup",
/*:54*//*62:*/
#line 1420 "weaver-interface-metafont_en.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:62*//*116:*/
#line 2521 "weaver-interface-metafont_en.tex"

"=",":=",
/*:116*//*123:*/
#line 2730 "weaver-interface-metafont_en.tex"

"+","-","++","+-+","[","]","{","}",
/*:123*//*130:*/
#line 2935 "weaver-interface-metafont_en.tex"

"*","/",
/*:130*//*134:*/
#line 3064 "weaver-interface-metafont_en.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:134*//*152:*/
#line 3477 "weaver-interface-metafont_en.tex"

"normaldeviate",
/*:152*//*168:*/
#line 3853 "weaver-interface-metafont_en.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:168*//*188:*/
#line 4497 "weaver-interface-metafont_en.tex"

"xpart","ypart","angle",
/*:188*//*201:*/
#line 4760 "weaver-interface-metafont_en.tex"

"cycle","&","..","tension","and","atleast","controls","curl","--",
/*:201*//*280:*/
#line 6948 "weaver-interface-metafont_en.tex"

"reverse","subpath","of",
/*:280*//*297:*/
#line 7511 "weaver-interface-metafont_en.tex"

"point","precontrol","postcontrol",
/*:297*//*318:*/
#line 8192 "weaver-interface-metafont_en.tex"

"nullpen","pencircle","makepen",
/*:318*//*329:*/
#line 8491 "weaver-interface-metafont_en.tex"

"makepath",
/*:329*//*366:*/
#line 9560 "weaver-interface-metafont_en.tex"

"nullpicture",
/*:366*//*380:*/
#line 9917 "weaver-interface-metafont_en.tex"

"totalweight",
/*:380*/
#line 858 "weaver-interface-metafont_en.tex"

NULL};
/*:37*//*337:*/
#line 8743 "weaver-interface-metafont_en.tex"

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
/*:337*//*340:*/
#line 8797 "weaver-interface-metafont_en.tex"

static const char vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat4 model_view_matrix;\n"
"varying mediump vec2 texture_coordinate;\n"
"void main(){\n"
"  gl_Position = vec4(vertex_data.xy, 0.0, 1.0) * model_view_matrix;\n"
"  texture_coordinate = vertex_data.zw;\n"
"}\n";
/*:340*//*341:*/
#line 8814 "weaver-interface-metafont_en.tex"

static const char fragment_shader[]= 
"#version 100\n"
"precision mediump float;\n"
"varying mediump vec2 texture_coordinate;\n"
"uniform sampler2D texture1;\n"
"void main(){\n"
"  vec4 texture = texture2D(texture1, texture_coordinate);\n"
"  gl_FragColor = texture;"
"}\n";
static GLuint program;
GLint uniform_matrix;
GLint uniform_texture;
/*:341*//*373:*/
#line 9750 "weaver-interface-metafont_en.tex"

static const char fragment_shader_inv[]= 
"#version 100\n"
"precision highp float;\n"
"varying mediump vec2 texture_coordinate;\n"
"uniform sampler2D texture1;\n"
"void main(){\n"
"  vec4 texture = texture2D(texture1, texture_coordinate);\n"
"  gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0) - texture;"
"}\n";
static GLuint inverse_program;
GLint uniform_inverse_matrix;
GLint uniform_inverse_texture;
/*:373*/
#line 213 "weaver-interface-metafont_en.tex"

/*47:*/
#line 1062 "weaver-interface-metafont_en.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:47*//*51:*/
#line 1165 "weaver-interface-metafont_en.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:51*//*55:*/
#line 1256 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:55*//*74:*/
#line 1654 "weaver-interface-metafont_en.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:74*//*76:*/
#line 1717 "weaver-interface-metafont_en.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:76*//*78:*/
#line 1778 "weaver-interface-metafont_en.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:78*//*94:*/
#line 2090 "weaver-interface-metafont_en.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer);
/*:94*//*120:*/
#line 2654 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source);
/*:120*//*124:*/
#line 2739 "weaver-interface-metafont_en.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:124*//*131:*/
#line 2943 "weaver-interface-metafont_en.tex"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:131*//*135:*/
#line 3072 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:135*//*139:*/
#line 3171 "weaver-interface-metafont_en.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:139*//*153:*/
#line 3488 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:153*//*163:*/
#line 3725 "weaver-interface-metafont_en.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source);
/*:163*//*165:*/
#line 3763 "weaver-interface-metafont_en.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result);
/*:165*//*169:*/
#line 3864 "weaver-interface-metafont_en.tex"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:169*//*180:*/
#line 4187 "weaver-interface-metafont_en.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:180*//*194:*/
#line 4614 "weaver-interface-metafont_en.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source);
/*:194*//*196:*/
#line 4651 "weaver-interface-metafont_en.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target);
/*:196*//*198:*/
#line 4689 "weaver-interface-metafont_en.tex"

void recursive_aux_copy(struct path_points**dst,struct path_variable*origin);
/*:198*//*202:*/
#line 4770 "weaver-interface-metafont_en.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:202*//*204:*/
#line 4812 "weaver-interface-metafont_en.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:204*//*219:*/
#line 5255 "weaver-interface-metafont_en.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y);
/*:219*//*246:*/
#line 6135 "weaver-interface-metafont_en.tex"

double compute_f(double theta,double phi);
/*:246*//*250:*/
#line 6191 "weaver-interface-metafont_en.tex"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y);
/*:250*//*252:*/
#line 6225 "weaver-interface-metafont_en.tex"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y);
/*:252*//*258:*/
#line 6423 "weaver-interface-metafont_en.tex"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:258*//*260:*/
#line 6514 "weaver-interface-metafont_en.tex"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:260*//*263:*/
#line 6646 "weaver-interface-metafont_en.tex"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta);
/*:263*//*266:*/
#line 6699 "weaver-interface-metafont_en.tex"

void path_xyscale(struct path_variable*p,float x,float y);
/*:266*//*269:*/
#line 6751 "weaver-interface-metafont_en.tex"

void path_shift(struct path_variable*p,float x,float y);
/*:269*//*272:*/
#line 6797 "weaver-interface-metafont_en.tex"

void path_slant(struct path_variable*p,float s);
/*:272*//*277:*/
#line 6888 "weaver-interface-metafont_en.tex"

void path_zscale(struct path_variable*p,float x,float y);
/*:277*//*281:*/
#line 6962 "weaver-interface-metafont_en.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:281*//*285:*/
#line 7100 "weaver-interface-metafont_en.tex"

void reverse_path(struct path_variable*src,struct path_variable*dst);
/*:285*//*288:*/
#line 7271 "weaver-interface-metafont_en.tex"

void copy_subpath(struct path_points*dst,struct path_variable*src,int offset,int size);
/*:288*//*290:*/
#line 7301 "weaver-interface-metafont_en.tex"

int recursive_copy_subpath(struct path_points**dst,
struct path_variable*pointer,
int*index,int*offset,int*size);
/*:290*//*298:*/
#line 7527 "weaver-interface-metafont_en.tex"

struct path_points*get_point(struct path_variable*v,int n);
/*:298*//*300:*/
#line 7556 "weaver-interface-metafont_en.tex"

struct path_points*_get_point(struct path_variable*v,int n,int*count);
/*:300*//*304:*/
#line 7713 "weaver-interface-metafont_en.tex"

void assign_pen_variable(struct metafont*mf,
struct pen_variable*target,
struct pen_variable*source);
/*:304*//*306:*/
#line 7767 "weaver-interface-metafont_en.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:306*//*308:*/
#line 7810 "weaver-interface-metafont_en.tex"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:308*//*319:*/
#line 8200 "weaver-interface-metafont_en.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result);
/*:319*//*326:*/
#line 8390 "weaver-interface-metafont_en.tex"

int read_flags(struct path_variable*path);
/*:326*//*344:*/
#line 8893 "weaver-interface-metafont_en.tex"

bool get_new_framebuffer(GLuint*new_framebuffer,GLuint*new_texture,
int width,int height);
/*:344*//*346:*/
#line 8931 "weaver-interface-metafont_en.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height);
/*:346*//*348:*/
#line 8963 "weaver-interface-metafont_en.tex"

void assign_picture_variable(struct metafont*mf,
struct picture_variable*target,
struct picture_variable*source);
/*:348*//*350:*/
#line 9016 "weaver-interface-metafont_en.tex"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result);
/*:350*//*354:*/
#line 9203 "weaver-interface-metafont_en.tex"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result,
float*matrix,bool*modified);
/*:354*//*363:*/
#line 9494 "weaver-interface-metafont_en.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*org,
float*matrix);
/*:363*//*367:*/
#line 9568 "weaver-interface-metafont_en.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result);
/*:367*//*376:*/
#line 9826 "weaver-interface-metafont_en.tex"

void render_inverse_picture(struct picture_variable*pic,float*matrix,
int dst_width,int dst_height);
/*:376*/
#line 214 "weaver-interface-metafont_en.tex"

/*15:*/
#line 387 "weaver-interface-metafont_en.tex"

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
/*:15*//*16:*/
#line 409 "weaver-interface-metafont_en.tex"

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
/*18:*/
#line 462 "weaver-interface-metafont_en.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:18*/
#line 426 "weaver-interface-metafont_en.tex"

/*20:*/
#line 483 "weaver-interface-metafont_en.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:20*/
#line 427 "weaver-interface-metafont_en.tex"

/*21:*/
#line 500 "weaver-interface-metafont_en.tex"

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
/*:21*/
#line 428 "weaver-interface-metafont_en.tex"

/*22:*/
#line 547 "weaver-interface-metafont_en.tex"

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
/*:22*/
#line 429 "weaver-interface-metafont_en.tex"

/*23:*/
#line 592 "weaver-interface-metafont_en.tex"

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
/*:23*/
#line 430 "weaver-interface-metafont_en.tex"

/*24:*/
#line 627 "weaver-interface-metafont_en.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*25:*/
#line 658 "weaver-interface-metafont_en.tex"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_'||isdigit(c));
ungetc(c,fp);
buffer[i]= '\0';
}
/*:25*/
#line 633 "weaver-interface-metafont_en.tex"

/*26:*/
#line 675 "weaver-interface-metafont_en.tex"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:26*/
#line 634 "weaver-interface-metafont_en.tex"

/*27:*/
#line 691 "weaver-interface-metafont_en.tex"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:27*/
#line 635 "weaver-interface-metafont_en.tex"

/*28:*/
#line 707 "weaver-interface-metafont_en.tex"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:28*/
#line 636 "weaver-interface-metafont_en.tex"

/*29:*/
#line 723 "weaver-interface-metafont_en.tex"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:29*/
#line 637 "weaver-interface-metafont_en.tex"

/*30:*/
#line 739 "weaver-interface-metafont_en.tex"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:30*/
#line 638 "weaver-interface-metafont_en.tex"

/*31:*/
#line 755 "weaver-interface-metafont_en.tex"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:31*/
#line 639 "weaver-interface-metafont_en.tex"

/*32:*/
#line 771 "weaver-interface-metafont_en.tex"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:32*/
#line 640 "weaver-interface-metafont_en.tex"

/*33:*/
#line 787 "weaver-interface-metafont_en.tex"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:33*/
#line 641 "weaver-interface-metafont_en.tex"

/*34:*/
#line 803 "weaver-interface-metafont_en.tex"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:34*/
#line 642 "weaver-interface-metafont_en.tex"

/*35:*/
#line 819 "weaver-interface-metafont_en.tex"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:35*/
#line 643 "weaver-interface-metafont_en.tex"

/*36:*/
#line 835 "weaver-interface-metafont_en.tex"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:36*/
#line 644 "weaver-interface-metafont_en.tex"


/*38:*/
#line 869 "weaver-interface-metafont_en.tex"

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
/*43:*/
#line 992 "weaver-interface-metafont_en.tex"

if(token_type==TYPE_DUMP)
token_type= TYPE_END;
/*:43*//*117:*/
#line 2530 "weaver-interface-metafont_en.tex"

else if(token_type==TYPE_ASSIGNMENT2)
token_type= TYPE_ASSIGNMENT;
/*:117*/
#line 882 "weaver-interface-metafont_en.tex"

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
/*:38*/
#line 646 "weaver-interface-metafont_en.tex"

/*40:*/
#line 913 "weaver-interface-metafont_en.tex"

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
/*87:*/
#line 1925 "weaver-interface-metafont_en.tex"

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
/*:87*//*105:*/
#line 2350 "weaver-interface-metafont_en.tex"

else if(!strcmp(buffer,"currentpen"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN]);
else if(!strcmp(buffer,"pensquare"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_PENSQUARE]);
/*:105*//*114:*/
#line 2474 "weaver-interface-metafont_en.tex"

else if(!strcmp(buffer,"currentpicture"))
new_token->var= 
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE]);
/*:114*/
#line 926 "weaver-interface-metafont_en.tex"

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
/*:40*/
#line 647 "weaver-interface-metafont_en.tex"

}
/*:24*/
#line 431 "weaver-interface-metafont_en.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
fclose(fp);
return first_token;
}
/*:16*//*44:*/
#line 1006 "weaver-interface-metafont_en.tex"

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
/*:44*//*48:*/
#line 1078 "weaver-interface-metafont_en.tex"

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
/*66:*/
#line 1489 "weaver-interface-metafont_en.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:66*//*84:*/
#line 1874 "weaver-interface-metafont_en.tex"

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
/*:84*//*102:*/
#line 2288 "weaver-interface-metafont_en.tex"

mf->internal_pen_variables= (struct pen_variable*)
mf->alloc(2*sizeof(struct pen_variable));
if(mf->internal_pen_variables==NULL){
if(disalloc!=NULL)
disalloc(mf);
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
/*:102*//*111:*/
#line 2433 "weaver-interface-metafont_en.tex"

mf->internal_picture_variables= (struct picture_variable*)
mf->alloc(sizeof(struct picture_variable));
if(mf->internal_picture_variables==NULL){
if(disalloc!=NULL)
disalloc(mf);
}

mf->internal_picture_variables[0].type= TYPE_T_PICTURE;
mf->internal_picture_variables[0].width= -1;
mf->internal_picture_variables[0].height= -1;
mf->internal_picture_variables[0].texture= 0;
/*:111*//*158:*/
#line 3613 "weaver-interface-metafont_en.tex"

mf->have_stored_normaldeviate= false;
/*:158*/
#line 1089 "weaver-interface-metafont_en.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*59:*/
#line 1313 "weaver-interface-metafont_en.tex"

cx->nesting_level= 0;
/*:59*//*70:*/
#line 1550 "weaver-interface-metafont_en.tex"

cx->variables= NULL;
/*:70*/
#line 1095 "weaver-interface-metafont_en.tex"

return cx;
}
/*:48*//*49:*/
#line 1105 "weaver-interface-metafont_en.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*67:*/
#line 1501 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*92:*/
#line 2061 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:92*//*99:*/
#line 2236 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:99*//*108:*/
#line 2397 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:108*/
#line 1507 "weaver-interface-metafont_en.tex"

mf->free(v);
v= next;
}
}
/*:67*//*68:*/
#line 1519 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)named->var;
next= (struct named_variable*)(named->next);
mf->free(named->name);
/*92:*/
#line 2061 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:92*//*99:*/
#line 2236 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:99*//*108:*/
#line 2397 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:108*/
#line 1528 "weaver-interface-metafont_en.tex"

mf->free(v);
mf->free(named);
named= next;
}
}
/*:68*//*86:*/
#line 1913 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL)
mf->free(mf->internal_numeric_variables);
/*:86*//*104:*/
#line 2334 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
if(mf->internal_pen_variables[1].format!=NULL){
mf->free(mf->internal_pen_variables[1].format->points);
mf->free(mf->internal_pen_variables[1].format);
}
mf->free(mf->internal_pen_variables);
}
/*:104*//*113:*/
#line 2461 "weaver-interface-metafont_en.tex"

if(mf->internal_picture_variables[0].texture!=0)
glDeleteTextures(1,&(mf->internal_picture_variables[0].texture));
if(mf->free!=NULL)
mf->free(mf->internal_picture_variables);
/*:113*/
#line 1109 "weaver-interface-metafont_en.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*71:*/
#line 1558 "weaver-interface-metafont_en.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*93:*/
#line 2074 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL)
path_recursive_free(temporary_free,path,false);
}
/*:93*//*100:*/
#line 2253 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&temporary_free!=NULL)
path_recursive_free(temporary_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:100*//*109:*/
#line 2409 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:109*/
#line 1564 "weaver-interface-metafont_en.tex"

temporary_free(v);
v= next;
}
}
/*:71*/
#line 1115 "weaver-interface-metafont_en.tex"

temporary_free(cx);
}
}
/*:49*//*52:*/
#line 1177 "weaver-interface-metafont_en.tex"

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
/*:52*//*56:*/
#line 1263 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*57:*/
#line 1290 "weaver-interface-metafont_en.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:57*/
#line 1266 "weaver-interface-metafont_en.tex"

/*60:*/
#line 1346 "weaver-interface-metafont_en.tex"

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
/*:60*/
#line 1267 "weaver-interface-metafont_en.tex"

/*72:*/
#line 1575 "weaver-interface-metafont_en.tex"

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
/*73:*/
#line 1625 "weaver-interface-metafont_en.tex"

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
/*:73*/
#line 1592 "weaver-interface-metafont_en.tex"

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
/*:72*/
#line 1268 "weaver-interface-metafont_en.tex"

/*118:*/
#line 2554 "weaver-interface-metafont_en.tex"

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
/*119:*/
#line 2630 "weaver-interface-metafont_en.tex"

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
/*:119*/
#line 2614 "weaver-interface-metafont_en.tex"

/*162:*/
#line 3704 "weaver-interface-metafont_en.tex"

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
/*:162*/
#line 2615 "weaver-interface-metafont_en.tex"

/*193:*/
#line 4590 "weaver-interface-metafont_en.tex"

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
/*:193*/
#line 2616 "weaver-interface-metafont_en.tex"

/*303:*/
#line 7686 "weaver-interface-metafont_en.tex"

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
/*:303*/
#line 2617 "weaver-interface-metafont_en.tex"

/*336:*/
#line 8705 "weaver-interface-metafont_en.tex"

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
/*:336*/
#line 2618 "weaver-interface-metafont_en.tex"

return true;
}
/*:118*/
#line 1269 "weaver-interface-metafont_en.tex"




#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:56*//*75:*/
#line 1667 "weaver-interface-metafont_en.tex"

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
default:
var_size= sizeof(struct variable);
}
var= (struct variable*)alloc(var_size);
if(var!=NULL){
var->type= type;
var->next= NULL;
var->nesting_level= nesting_level;
/*81:*/
#line 1834 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:81*//*89:*/
#line 1965 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PAIR){
((struct pair_variable*)var)->x= NAN;
}
/*:89*//*91:*/
#line 2049 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
}
/*:91*//*98:*/
#line 2221 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PEN){
((struct pen_variable*)var)->format= NULL;
((struct pen_variable*)var)->gl_vbo= 0;
((struct pen_variable*)var)->flags= false;
((struct pen_variable*)var)->referenced= NULL;
}
/*:98*//*107:*/
#line 2384 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PICTURE){
((struct picture_variable*)var)->width= -1;
((struct picture_variable*)var)->height= -1;
((struct picture_variable*)var)->texture= 0;
}
/*:107*/
#line 1699 "weaver-interface-metafont_en.tex"

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
/*:75*//*77:*/
#line 1728 "weaver-interface-metafont_en.tex"

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
/*:77*//*79:*/
#line 1791 "weaver-interface-metafont_en.tex"

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
/*:79*//*95:*/
#line 2100 "weaver-interface-metafont_en.tex"

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
/*:95*//*121:*/
#line 2663 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source){
target->value= source->value;
}
/*:121*//*128:*/
#line 2857 "weaver-interface-metafont_en.tex"

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
/*:128*//*132:*/
#line 2965 "weaver-interface-metafont_en.tex"

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
/*:132*//*136:*/
#line 3085 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*137:*/
#line 3107 "weaver-interface-metafont_en.tex"

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
/*:137*/
#line 3090 "weaver-interface-metafont_en.tex"

/*138:*/
#line 3131 "weaver-interface-metafont_en.tex"

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
/*189:*/
#line 4509 "weaver-interface-metafont_en.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)hypot(p.x*p.x,p.y*p.y);
return true;
}
/*:189*//*295:*/
#line 7472 "weaver-interface-metafont_en.tex"

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
/*:295*/
#line 3148 "weaver-interface-metafont_en.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:138*/
#line 3091 "weaver-interface-metafont_en.tex"

/*141:*/
#line 3218 "weaver-interface-metafont_en.tex"

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
/*:141*//*142:*/
#line 3246 "weaver-interface-metafont_en.tex"

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
/*:142*//*143:*/
#line 3265 "weaver-interface-metafont_en.tex"

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
/*:143*//*144:*/
#line 3284 "weaver-interface-metafont_en.tex"

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
/*:144*//*145:*/
#line 3310 "weaver-interface-metafont_en.tex"

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
/*:145*//*146:*/
#line 3328 "weaver-interface-metafont_en.tex"

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
/*:146*//*147:*/
#line 3358 "weaver-interface-metafont_en.tex"

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
/*:147*//*148:*/
#line 3381 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:148*//*149:*/
#line 3398 "weaver-interface-metafont_en.tex"

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
/*:149*/
#line 3092 "weaver-interface-metafont_en.tex"

/*190:*/
#line 4525 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_XPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.x;
return true;
}
/*:190*//*191:*/
#line 4542 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_YPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.y;
return true;
}
/*:191*//*192:*/
#line 4562 "weaver-interface-metafont_en.tex"

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
/*:192*//*381:*/
#line 9927 "weaver-interface-metafont_en.tex"

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

render_picture(&p,identity_matrix,p.width,p.height);

glReadPixels(0,0,p.width,p.height,GL_RGBA,GL_UNSIGNED_BYTE,data);
{
int i,size= p.width*p.height*4;
double sum= 0.0;
for(i= 0;i<size;i+= 4){
double v= ((unsigned char)data[i]+(unsigned char)data[i+1]+
(unsigned char)data[i+2])/765.0;
sum+= v*((unsigned char)data[i+3]/255.0);
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
/*:381*/
#line 3093 "weaver-interface-metafont_en.tex"

/*150:*/
#line 3422 "weaver-interface-metafont_en.tex"

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
/*:150*/
#line 3094 "weaver-interface-metafont_en.tex"

return true;
}
/*:136*//*140:*/
#line 3179 "weaver-interface-metafont_en.tex"

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
/*:140*//*154:*/
#line 3501 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*155:*/
#line 3523 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:155*/
#line 3507 "weaver-interface-metafont_en.tex"

/*156:*/
#line 3536 "weaver-interface-metafont_en.tex"

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
/*:156*/
#line 3508 "weaver-interface-metafont_en.tex"

/*159:*/
#line 3623 "weaver-interface-metafont_en.tex"

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
/*:159*/
#line 3509 "weaver-interface-metafont_en.tex"

}
else{
/*160:*/
#line 3658 "weaver-interface-metafont_en.tex"

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
/*:160*/
#line 3512 "weaver-interface-metafont_en.tex"

/*161:*/
#line 3687 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_NUMERIC&&
end_expression->type==TYPE_NUMERIC&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION){
result->value= ((struct numeric_token*)begin_expression)->value/
((struct numeric_token*)end_expression)->value;
return true;
}
/*:161*/
#line 3513 "weaver-interface-metafont_en.tex"

}
return true;
}
/*:154*//*164:*/
#line 3734 "weaver-interface-metafont_en.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source){
target->x= source->x;
target->y= source->y;
}
/*:164*//*166:*/
#line 3776 "weaver-interface-metafont_en.tex"

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
/*:166*//*170:*/
#line 3883 "weaver-interface-metafont_en.tex"

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
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED)){
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
/*171:*/
#line 3950 "weaver-interface-metafont_en.tex"

if(last_mul->type==TYPE_MULTIPLICATION){
if(get_primary_expression_type(mf,cx,begin_primary,end_expression)==
TYPE_T_PAIR){
struct numeric_variable a;
struct pair_variable b;
if(!eval_numeric_secondary(mf,cx,begin_expression,end_secondary,
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
/*:171*/
#line 3920 "weaver-interface-metafont_en.tex"

/*172:*/
#line 3987 "weaver-interface-metafont_en.tex"

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
/*:172*/
#line 3921 "weaver-interface-metafont_en.tex"

/*173:*/
#line 4015 "weaver-interface-metafont_en.tex"

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
/*:173*/
#line 3922 "weaver-interface-metafont_en.tex"

/*174:*/
#line 4039 "weaver-interface-metafont_en.tex"

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
/*:174*/
#line 3923 "weaver-interface-metafont_en.tex"

/*175:*/
#line 4059 "weaver-interface-metafont_en.tex"

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
/*:175*/
#line 3924 "weaver-interface-metafont_en.tex"

/*176:*/
#line 4080 "weaver-interface-metafont_en.tex"

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
/*:176*/
#line 3925 "weaver-interface-metafont_en.tex"

/*177:*/
#line 4101 "weaver-interface-metafont_en.tex"

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
/*:177*/
#line 3926 "weaver-interface-metafont_en.tex"

/*178:*/
#line 4122 "weaver-interface-metafont_en.tex"

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
/*:178*/
#line 3927 "weaver-interface-metafont_en.tex"

/*179:*/
#line 4147 "weaver-interface-metafont_en.tex"

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
/*:179*/
#line 3928 "weaver-interface-metafont_en.tex"

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
/*:170*//*181:*/
#line 4199 "weaver-interface-metafont_en.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
if(begin_expression==end_expression){
/*182:*/
#line 4228 "weaver-interface-metafont_en.tex"

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
/*:182*/
#line 4205 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*183:*/
#line 4271 "weaver-interface-metafont_en.tex"

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
/*:183*/
#line 4209 "weaver-interface-metafont_en.tex"

/*184:*/
#line 4332 "weaver-interface-metafont_en.tex"

else{
return eval_pair_expression(mf,cx,begin_a,end_a,result);
}
/*:184*/
#line 4210 "weaver-interface-metafont_en.tex"

}
/*302:*/
#line 7603 "weaver-interface-metafont_en.tex"

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
/*:302*/
#line 4212 "weaver-interface-metafont_en.tex"

/*185:*/
#line 4343 "weaver-interface-metafont_en.tex"

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
/*:185*/
#line 4213 "weaver-interface-metafont_en.tex"

/*186:*/
#line 4423 "weaver-interface-metafont_en.tex"

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
/*:186*/
#line 4214 "weaver-interface-metafont_en.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:181*//*195:*/
#line 4624 "weaver-interface-metafont_en.tex"

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
/*:195*//*197:*/
#line 4665 "weaver-interface-metafont_en.tex"

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
/*:197*//*199:*/
#line 4695 "weaver-interface-metafont_en.tex"

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
/*:199*//*203:*/
#line 4780 "weaver-interface-metafont_en.tex"

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
/*:203*//*205:*/
#line 4825 "weaver-interface-metafont_en.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin_expression,end_expression);
expected_length= number_of_joins+1;
/*206:*/
#line 4850 "weaver-interface-metafont_en.tex"

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
/*:206*/
#line 4833 "weaver-interface-metafont_en.tex"

/*207:*/
#line 4875 "weaver-interface-metafont_en.tex"

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
/*:207*/
#line 4834 "weaver-interface-metafont_en.tex"

/*208:*/
#line 4905 "weaver-interface-metafont_en.tex"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d= NULL,*end_d= NULL,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
struct path_points*z1_point= NULL,*z2_point= NULL;
/*217:*/
#line 5222 "weaver-interface-metafont_en.tex"

float w0_x= NAN,w0_y= NAN,w1_x= NAN,w1_y= NAN;
float prev_w_x= NAN,prev_w_y= NAN;
float next_w_x= NAN,next_w_y= NAN;
/*:217*//*233:*/
#line 5782 "weaver-interface-metafont_en.tex"

float first_w_x= NAN,first_w_y= NAN;
/*:233*//*237:*/
#line 5883 "weaver-interface-metafont_en.tex"

float previous_point_x= NAN,previous_point_y= NAN;
/*:237*//*241:*/
#line 5989 "weaver-interface-metafont_en.tex"

float first_point_x= NAN,first_point_y= NAN;
/*:241*/
#line 4911 "weaver-interface-metafont_en.tex"

begin_z1= begin_expression;
end_z1= begin_z1;
while(begin_z1!=end_expression||result->length<expected_length){
/*209:*/
#line 4937 "weaver-interface-metafont_en.tex"

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
/*:209*//*210:*/
#line 4963 "weaver-interface-metafont_en.tex"

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
/*:210*//*211:*/
#line 4999 "weaver-interface-metafont_en.tex"

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
/*:211*//*212:*/
#line 5037 "weaver-interface-metafont_en.tex"

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
/*:212*//*213:*/
#line 5077 "weaver-interface-metafont_en.tex"

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
/*:213*/
#line 4915 "weaver-interface-metafont_en.tex"

/*214:*/
#line 5110 "weaver-interface-metafont_en.tex"

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
/*:214*//*215:*/
#line 5143 "weaver-interface-metafont_en.tex"

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
/*:215*//*216:*/
#line 5196 "weaver-interface-metafont_en.tex"

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
/*:216*/
#line 4916 "weaver-interface-metafont_en.tex"

/*218:*/
#line 5238 "weaver-interface-metafont_en.tex"

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
/*:218*/
#line 4917 "weaver-interface-metafont_en.tex"

/*224:*/
#line 5358 "weaver-interface-metafont_en.tex"

float tension0= NAN,tension1= NAN,u_x= NAN,u_y= NAN,v_x= NAN,
v_y= NAN;
bool atleast0= false,atleast1= false;
/*:224*//*225:*/
#line 5374 "weaver-interface-metafont_en.tex"

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
/*:225*//*226:*/
#line 5402 "weaver-interface-metafont_en.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_STRAIGHT_JOIN){
u_x= z1_point->x+(1.0/3.0)*(z2_point->x-z1_point->x);
u_y= z1_point->y+(1.0/3.0)*(z2_point->y-z1_point->y);
v_x= z1_point->x+(2.0/3.0)*(z2_point->x-z1_point->x);
v_y= z1_point->y+(2.0/3.0)*(z2_point->y-z1_point->y);
}
/*:226*//*227:*/
#line 5417 "weaver-interface-metafont_en.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
tension0= 1.0;
tension1= 1.0;
atleast0= false;
atleast1= false;
}
/*:227*//*228:*/
#line 5435 "weaver-interface-metafont_en.tex"

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
/*:228*//*229:*/
#line 5502 "weaver-interface-metafont_en.tex"

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
/*:229*/
#line 4918 "weaver-interface-metafont_en.tex"

/*231:*/
#line 5719 "weaver-interface-metafont_en.tex"

if(isnan(w0_x)&&isnan(w0_y)){
w0_x= prev_w_x;
w0_y= prev_w_y;
}
/*:231*//*232:*/
#line 5732 "weaver-interface-metafont_en.tex"

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
/*:232*//*234:*/
#line 5791 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d!=NULL&&end_d!=NULL){
first_w_x= w0_x;
first_w_y= w0_y;
}
/*:234*//*235:*/
#line 5804 "weaver-interface-metafont_en.tex"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE){
if(!isnan(first_w_x)&&isnan(w1_x)){
w1_x= first_w_x;
w1_y= first_w_y;
}
}
/*:235*//*236:*/
#line 5822 "weaver-interface-metafont_en.tex"

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
/*244:*/
#line 6036 "weaver-interface-metafont_en.tex"

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
/*:244*/
#line 5856 "weaver-interface-metafont_en.tex"

}
/*:236*//*238:*/
#line 5894 "weaver-interface-metafont_en.tex"

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
/*:238*//*239:*/
#line 5915 "weaver-interface-metafont_en.tex"

if(begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
previous_point_x= v_x;
previous_point_y= v_y;
}
else{
previous_point_x= NAN;
previous_point_y= NAN;
}
/*:239*//*240:*/
#line 5934 "weaver-interface-metafont_en.tex"

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
/*:240*//*242:*/
#line 5997 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
first_point_x= u_x;
first_point_y= u_y;
}
/*:242*//*243:*/
#line 6011 "weaver-interface-metafont_en.tex"

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
/*:243*//*245:*/
#line 6078 "weaver-interface-metafont_en.tex"

if(isnan(u_x)||isnan(u_y)||isnan(v_x)||isnan(v_y)){
if(isnan(w0_x)||isnan(w0_y)||isnan(w1_x)||isnan(w1_y)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
/*:245*//*249:*/
#line 6166 "weaver-interface-metafont_en.tex"

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
/*256:*/
#line 6361 "weaver-interface-metafont_en.tex"

if(atleast0)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&u_x,&u_y);
if(atleast1)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&v_x,&v_y);
/*:256*/
#line 6179 "weaver-interface-metafont_en.tex"

}
/*:249*//*257:*/
#line 6377 "weaver-interface-metafont_en.tex"

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
/*:257*/
#line 4919 "weaver-interface-metafont_en.tex"

/*230:*/
#line 5700 "weaver-interface-metafont_en.tex"

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
/*:230*/
#line 4920 "weaver-interface-metafont_en.tex"

begin_z1= begin_z2;
end_z1= end_z2;
}
}
/*:208*/
#line 4835 "weaver-interface-metafont_en.tex"

return true;
}
/*:205*//*220:*/
#line 5269 "weaver-interface-metafont_en.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y){
/*221:*/
#line 5286 "weaver-interface-metafont_en.tex"

if(begin==NULL||end==NULL){
return true;
}
/*:221*/
#line 5274 "weaver-interface-metafont_en.tex"

/*222:*/
#line 5299 "weaver-interface-metafont_en.tex"

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
/*:222*/
#line 5275 "weaver-interface-metafont_en.tex"

/*223:*/
#line 5337 "weaver-interface-metafont_en.tex"

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
/*:223*/
#line 5276 "weaver-interface-metafont_en.tex"

return false;
}
/*:220*//*247:*/
#line 6141 "weaver-interface-metafont_en.tex"

double compute_f(double theta,double phi){
double n= 2+sqrt(2)*(sin(theta)-0.0625*sin(phi))*
(sin(phi)-0.0625*sin(theta))*(cos(theta)-cos(phi));
double d= 3*(1+0.5*(sqrt(5)-1)*cos(theta)+0.5*(3-sqrt(5))*
cos(phi));
return n/d;
}
/*:247*//*251:*/
#line 6198 "weaver-interface-metafont_en.tex"

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
/*:251*//*253:*/
#line 6233 "weaver-interface-metafont_en.tex"

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
/*254:*/
#line 6275 "weaver-interface-metafont_en.tex"

bool s1,s2,s3;
s1= ((*control_x-p1_x)*(p0_y-p1_y)-
(p0_x-p1_x)*(*control_y-p1_y))<0;
s2= ((*control_x-p2_x)*(p1_y-p2_y)-
(p1_x-p2_x)*(*control_y-p2_y))<0;
s3= ((*control_x-p0_x)*(p2_y-p0_y)-
(p2_x-p0_x)*(*control_y-p0_y))<0;
if(s1==s2&&s2==s3)
return;
/*:254*/
#line 6257 "weaver-interface-metafont_en.tex"

/*255:*/
#line 6297 "weaver-interface-metafont_en.tex"

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
/*:255*/
#line 6258 "weaver-interface-metafont_en.tex"

}
}
/*:253*//*259:*/
#line 6434 "weaver-interface-metafont_en.tex"

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
/*:259*//*261:*/
#line 6525 "weaver-interface-metafont_en.tex"

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
if(!eval_path_secondary(mf,cx,begin_expression,before_transform,result))
return false;
/*262:*/
#line 6625 "weaver-interface-metafont_en.tex"

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
/*:262*/
#line 6573 "weaver-interface-metafont_en.tex"

/*265:*/
#line 6683 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,a.value);
return true;
}
/*:265*/
#line 6574 "weaver-interface-metafont_en.tex"

/*268:*/
#line 6736 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SHIFTED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_shift(result,a.x,a.y);
return true;
}
/*:268*/
#line 6575 "weaver-interface-metafont_en.tex"

/*271:*/
#line 6782 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SLANTED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_slant(result,a.value);
return true;
}
/*:271*/
#line 6576 "weaver-interface-metafont_en.tex"

/*274:*/
#line 6825 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_XSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,1.0);
return true;
}
/*:274*/
#line 6577 "weaver-interface-metafont_en.tex"

/*275:*/
#line 6841 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_YSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,1.0,a.value);
return true;
}
/*:275*/
#line 6578 "weaver-interface-metafont_en.tex"

/*276:*/
#line 6867 "weaver-interface-metafont_en.tex"

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
/*:276*/
#line 6579 "weaver-interface-metafont_en.tex"

}
else if(have_pair_operator){
struct pair_variable pair;
if(!eval_pair_secondary(mf,cx,begin_expression,end_expression,&pair))
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
/*:261*//*264:*/
#line 6653 "weaver-interface-metafont_en.tex"

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
/*:264*//*267:*/
#line 6711 "weaver-interface-metafont_en.tex"

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
/*:267*//*270:*/
#line 6757 "weaver-interface-metafont_en.tex"

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
/*:270*//*273:*/
#line 6803 "weaver-interface-metafont_en.tex"

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
/*:273*//*278:*/
#line 6894 "weaver-interface-metafont_en.tex"

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
/*:278*//*282:*/
#line 6973 "weaver-interface-metafont_en.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
if(begin_expression->type==TYPE_REVERSE){
/*284:*/
#line 7071 "weaver-interface-metafont_en.tex"

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
/*:284*/
#line 6979 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUBPATH){
/*287:*/
#line 7160 "weaver-interface-metafont_en.tex"

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
/*:287*/
#line 6982 "weaver-interface-metafont_en.tex"

}
else if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*292:*/
#line 7358 "weaver-interface-metafont_en.tex"

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
/*:292*/
#line 6986 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*293:*/
#line 7403 "weaver-interface-metafont_en.tex"

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
/*:293*/
#line 6990 "weaver-interface-metafont_en.tex"

}
/*330:*/
#line 8505 "weaver-interface-metafont_en.tex"

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
/*331:*/
#line 8542 "weaver-interface-metafont_en.tex"

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
/*:331*/
#line 8520 "weaver-interface-metafont_en.tex"

}
else if(tmp.flags&FLAG_CIRCULAR){
/*332:*/
#line 8564 "weaver-interface-metafont_en.tex"

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
/*:332*/
#line 8523 "weaver-interface-metafont_en.tex"

}
else if(tmp.flags&FLAG_SQUARE){
/*333:*/
#line 8613 "weaver-interface-metafont_en.tex"

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
/*:333*/
#line 8526 "weaver-interface-metafont_en.tex"

}
else{
/*334:*/
#line 8647 "weaver-interface-metafont_en.tex"

if(tmp.referenced==NULL)
recursive_copy_points(temporary_alloc,&result,tmp.format,false);
else
recursive_copy_points(temporary_alloc,&result,tmp.referenced->format,
false);
if(temporary_free!=NULL&&tmp.referenced==NULL)
temporary_free(tmp.format);
/*:334*/
#line 8529 "weaver-interface-metafont_en.tex"

}
/*335:*/
#line 8663 "weaver-interface-metafont_en.tex"

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
/*:335*/
#line 8531 "weaver-interface-metafont_en.tex"

return true;
}
/*:330*/
#line 6992 "weaver-interface-metafont_en.tex"

{
/*294:*/
#line 7434 "weaver-interface-metafont_en.tex"

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
/*:294*/
#line 6994 "weaver-interface-metafont_en.tex"

}
return false;
}
/*:282*//*283:*/
#line 7026 "weaver-interface-metafont_en.tex"

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
/*:283*//*286:*/
#line 7108 "weaver-interface-metafont_en.tex"

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
/*:286*//*289:*/
#line 7279 "weaver-interface-metafont_en.tex"

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
/*:289*//*291:*/
#line 7309 "weaver-interface-metafont_en.tex"

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
/*:291*//*299:*/
#line 7533 "weaver-interface-metafont_en.tex"

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
/*:299*//*301:*/
#line 7564 "weaver-interface-metafont_en.tex"

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
/*:301*//*305:*/
#line 7723 "weaver-interface-metafont_en.tex"

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
/*:305*//*307:*/
#line 7776 "weaver-interface-metafont_en.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result){
return eval_pen_secondary(mf,cx,begin_expression,end_token_list,result);
}
/*:307*//*309:*/
#line 7826 "weaver-interface-metafont_en.tex"

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
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED)){
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
/*310:*/
#line 7905 "weaver-interface-metafont_en.tex"

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
/*:310*/
#line 7856 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*311:*/
#line 7945 "weaver-interface-metafont_en.tex"

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
/*:311*/
#line 7859 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*312:*/
#line 7988 "weaver-interface-metafont_en.tex"

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
/*:312*/
#line 7862 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*313:*/
#line 8021 "weaver-interface-metafont_en.tex"

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
/*:313*/
#line 7865 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*314:*/
#line 8060 "weaver-interface-metafont_en.tex"

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
/*:314*/
#line 7868 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*315:*/
#line 8097 "weaver-interface-metafont_en.tex"

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
/*:315*/
#line 7871 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*316:*/
#line 8141 "weaver-interface-metafont_en.tex"

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
/*:316*/
#line 7874 "weaver-interface-metafont_en.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:309*//*320:*/
#line 8211 "weaver-interface-metafont_en.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*321:*/
#line 8252 "weaver-interface-metafont_en.tex"

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
fprintf(stderr,"METAFONT: Error: %s:%d: Got non-pen variable in pen expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
memcpy(result,content,sizeof(struct pen_variable));
result->referenced= content;
return true;
/*:321*/
#line 8218 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_NULLPEN){
/*322:*/
#line 8280 "weaver-interface-metafont_en.tex"

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
/*:322*/
#line 8221 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_PENCIRCLE){
/*323:*/
#line 8302 "weaver-interface-metafont_en.tex"

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
/*:323*/
#line 8224 "weaver-interface-metafont_en.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*324:*/
#line 8325 "weaver-interface-metafont_en.tex"

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
/*:324*/
#line 8230 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_MAKEPEN){
/*325:*/
#line 8348 "weaver-interface-metafont_en.tex"

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
/*:325*/
#line 8233 "weaver-interface-metafont_en.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:320*//*327:*/
#line 8400 "weaver-interface-metafont_en.tex"

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
/*:327*//*345:*/
#line 8900 "weaver-interface-metafont_en.tex"

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
return false;
}
return true;
}
/*:345*//*347:*/
#line 8938 "weaver-interface-metafont_en.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height){
glColorMask(true,true,true,true);
glViewport(0,0,dst_width,dst_height);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glUseProgram(program);
glUniformMatrix4fv(uniform_matrix,1,false,matrix);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,pic->texture);
glUniform1i(uniform_texture,0);
glClearColor(0.0,0.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
glDrawArrays(GL_TRIANGLE_FAN,0,4);
}
/*:347*//*349:*/
#line 8973 "weaver-interface-metafont_en.tex"

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
render_picture(source,model_view_matrix,source->width,source->height);

glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
}
/*:349*//*351:*/
#line 9032 "weaver-interface-metafont_en.tex"

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
/*353:*/
#line 9172 "weaver-interface-metafont_en.tex"

{
float matrix[16];
int i;
bool modified= false;
for(i= 0;i<16;i++)
if(i%5==0)
matrix[i]= 1.0;
else
matrix[i]= 0.0;
if(!eval_picture_secondary(mf,cx,begin_expression,end_expression,sec,
matrix,&modified))
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
/*:353*/
#line 9054 "weaver-interface-metafont_en.tex"

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
/*353:*/
#line 9172 "weaver-interface-metafont_en.tex"

{
float matrix[16];
int i;
bool modified= false;
for(i= 0;i<16;i++)
if(i%5==0)
matrix[i]= 1.0;
else
matrix[i]= 0.0;
if(!eval_picture_secondary(mf,cx,begin_expression,end_expression,sec,
matrix,&modified))
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
/*:353*/
#line 9070 "weaver-interface-metafont_en.tex"

/*352:*/
#line 9094 "weaver-interface-metafont_en.tex"


GLuint temporary_framebuffer= 0;
float model_view_matrix[16]= {1.0,0.0,0.0,0.0,
0.0,1.0,0.0,0.0,
0.0,0.0,1.0,0.0,
0.0,0.0,0.0,1.0};
int final_width= ((a.width>=b.width)?(a.width):(b.width));
int final_height= ((a.height>=b.height)?(a.height):(b.height));
get_new_framebuffer(&temporary_framebuffer,&(result->texture),final_width,
final_height);

model_view_matrix[0]= a.width/final_width;
model_view_matrix[5]= a.height/final_height;
render_picture(&a,model_view_matrix,final_width,final_height);

model_view_matrix[0]= b.width/final_width;
model_view_matrix[5]= b.height/final_height;
glUniformMatrix4fv(uniform_matrix,1,false,model_view_matrix);
glBindTexture(GL_TEXTURE_2D,b.texture);
glUniform1i(uniform_texture,0);
if(last_operator->type==TYPE_SUBTRACT){
glBlendEquation(GL_FUNC_SUBTRACT);
glDrawArrays(GL_TRIANGLE_FAN,0,4);
glBlendEquation(GL_FUNC_ADD);
}
else
glDrawArrays(GL_TRIANGLE_FAN,0,4);

glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
/*:352*/
#line 9071 "weaver-interface-metafont_en.tex"

if(a.texture!=0)
glDeleteTextures(1,&(a.texture));
if(b.texture!=0)
glDeleteTextures(1,&(b.texture));
return true;
}
}
/*:351*//*355:*/
#line 9220 "weaver-interface-metafont_en.tex"

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
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED)){
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
/*357:*/
#line 9328 "weaver-interface-metafont_en.tex"

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
/*:357*/
#line 9252 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*356:*/
#line 9296 "weaver-interface-metafont_en.tex"

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
/*:356*/
#line 9255 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*358:*/
#line 9362 "weaver-interface-metafont_en.tex"

struct pair_variable p;
float temp_matrix[16];
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
memcpy(temp_matrix,matrix,16*sizeof(float));
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
/*:358*/
#line 9258 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*359:*/
#line 9393 "weaver-interface-metafont_en.tex"

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
/*:359*/
#line 9261 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*360:*/
#line 9418 "weaver-interface-metafont_en.tex"

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
/*:360*/
#line 9264 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*361:*/
#line 9443 "weaver-interface-metafont_en.tex"

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
/*:361*/
#line 9267 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*362:*/
#line 9469 "weaver-interface-metafont_en.tex"

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
/*:362*/
#line 9270 "weaver-interface-metafont_en.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:355*//*364:*/
#line 9508 "weaver-interface-metafont_en.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*org,
float*matrix){
GLuint temporary_framebuffer= 0;

float offset_x,offset_y,end_x,end_y;
offset_x= matrix[12];
offset_y= matrix[13];
end_x= ((float)dst->width)*matrix[0]+
((float)dst->height)*matrix[4]+matrix[12];
end_y= ((float)dst->width)*matrix[1]+
((float)dst->height)*matrix[5]+matrix[13];
dst->width= (int)(end_x-offset_x);
dst->height= (int)(end_y-offset_y);

get_new_framebuffer(&temporary_framebuffer,&(dst->texture),dst->width,
dst->height);

render_picture(org,matrix,dst->width,dst->height);

glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:364*//*368:*/
#line 9579 "weaver-interface-metafont_en.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*369:*/
#line 9618 "weaver-interface-metafont_en.tex"

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

render_picture(content,identity_matrix,result->width,result->height);

glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
/*:369*/
#line 9586 "weaver-interface-metafont_en.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*370:*/
#line 9661 "weaver-interface-metafont_en.tex"

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
/*:370*/
#line 9592 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_NULLPICTURE){
/*371:*/
#line 9686 "weaver-interface-metafont_en.tex"

struct generic_token*begin_pair_expression,*end_pair_expression;
struct pair_variable p;
void*data;
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
memset(data,0,result->width*result->height*4);
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
/*:371*/
#line 9595 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUM){
/*372:*/
#line 9732 "weaver-interface-metafont_en.tex"

struct generic_token*p= begin_expression->next;
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing image expression "
"after '+'.\n",mf->file,begin_expression->line);
#endif
return false;
}
return eval_picture_primary(mf,cx,p,end_expression,result);
/*:372*/
#line 9598 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUBTRACT){
/*378:*/
#line 9859 "weaver-interface-metafont_en.tex"

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

render_inverse_picture(&p,identity_matrix,result->width,result->height);

glDeleteTextures(1,&(p.texture));
glBindFramebuffer(GL_FRAMEBUFFER,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
/*:378*/
#line 9601 "weaver-interface-metafont_en.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:368*//*377:*/
#line 9833 "weaver-interface-metafont_en.tex"

void render_inverse_picture(struct picture_variable*pic,float*matrix,
int dst_width,int dst_height){
glColorMask(true,true,true,true);
glViewport(0,0,dst_width,dst_height);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glUseProgram(inverse_program);
glUniformMatrix4fv(uniform_inverse_matrix,1,false,matrix);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,pic->texture);
glUniform1i(uniform_inverse_texture,0);
glClearColor(0.0,0.0,0.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);
glDrawArrays(GL_TRIANGLE_FAN,0,4);
glBindTexture(GL_TEXTURE_2D,0);
}
/*:377*/
#line 215 "weaver-interface-metafont_en.tex"

/*9:*/
#line 244 "weaver-interface-metafont_en.tex"

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
/*338:*/
#line 8772 "weaver-interface-metafont_en.tex"

glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);

glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
/*:338*//*342:*/
#line 8833 "weaver-interface-metafont_en.tex"

{
GLuint vertex,fragment;
GLint status= GL_TRUE;
const char*source_code[1];
vertex= glCreateShader(GL_VERTEX_SHADER);
fragment= glCreateShader(GL_FRAGMENT_SHADER);
source_code[0]= vertex_shader;
glShaderSource(vertex,1,source_code,NULL);
source_code[0]= fragment_shader;
glShaderSource(fragment,1,source_code,NULL);
glCompileShader(vertex);
glGetShaderiv(vertex,GL_COMPILE_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,
"ERROR: Weaver Metafont vertex shader compilation failed!\n");
return false;
}
glCompileShader(fragment);
glGetShaderiv(fragment,GL_COMPILE_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,
"ERROR: Weaver Metafont fragment shader compilation failed!\n");
return false;
}
program= glCreateProgram();
glAttachShader(program,vertex);
glAttachShader(program,fragment);
glBindAttribLocation(program,0,"vertex_data");
glLinkProgram(program);
glGetProgramiv(program,GL_LINK_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,"ERROR: Weaver Metafont shader linking failed!\n");
return false;
}
glDeleteShader(vertex);
glDeleteShader(fragment);

uniform_matrix= glGetUniformLocation(program,"model_view_matrix");
uniform_texture= glGetUniformLocation(program,"texture1");
}
/*:342*//*374:*/
#line 9769 "weaver-interface-metafont_en.tex"

{
GLuint vertex,fragment;
GLint status= GL_TRUE;
const char*source_code[1];
vertex= glCreateShader(GL_VERTEX_SHADER);
fragment= glCreateShader(GL_FRAGMENT_SHADER);
source_code[0]= vertex_shader;
glShaderSource(vertex,1,source_code,NULL);
source_code[0]= fragment_shader_inv;
glShaderSource(fragment,1,source_code,NULL);
glCompileShader(vertex);
glGetShaderiv(vertex,GL_COMPILE_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,
"ERROR: Weaver Metafont vertex shader compilation failed!\n");
return false;
}
glCompileShader(fragment);
glGetShaderiv(fragment,GL_COMPILE_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,
"ERROR: Weaver Metafont inverse fragment shader compilation "
"failed!\n");
return false;
}
inverse_program= glCreateProgram();
glAttachShader(inverse_program,vertex);
glAttachShader(inverse_program,fragment);
glBindAttribLocation(program,0,"vertex_data");
glLinkProgram(inverse_program);
glGetProgramiv(inverse_program,GL_LINK_STATUS,&status);
if(status==GL_FALSE){
fprintf(stderr,"ERROR: Weaver Metafont shader linking failed!\n");
return false;
}
glDeleteShader(vertex);
glDeleteShader(fragment);

uniform_inverse_matrix= glGetUniformLocation(inverse_program,"model_view_matrix");
uniform_inverse_texture= glGetUniformLocation(inverse_program,"texture1");
}
/*:374*/
#line 256 "weaver-interface-metafont_en.tex"

return true;
}
/*:9*//*10:*/
#line 267 "weaver-interface-metafont_en.tex"

void _Wfinish_metafont(void){
/*339:*/
#line 8783 "weaver-interface-metafont_en.tex"

glDeleteBuffers(1,&vbo);
/*:339*//*343:*/
#line 8880 "weaver-interface-metafont_en.tex"

glDeleteProgram(program);
/*:343*//*375:*/
#line 9817 "weaver-interface-metafont_en.tex"

glDeleteProgram(inverse_program);
/*:375*/
#line 269 "weaver-interface-metafont_en.tex"

}
/*:10*/
#line 216 "weaver-interface-metafont_en.tex"

/*:7*/
