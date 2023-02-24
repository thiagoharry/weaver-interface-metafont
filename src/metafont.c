/*7:*/
#line 227 "weaver-interface-metafont.tex"

#include "metafont.h"
/*17:*/
#line 471 "weaver-interface-metafont.tex"

#include <stdio.h> 
/*:17*//*19:*/
#line 493 "weaver-interface-metafont.tex"

#include <ctype.h> 
/*:19*//*39:*/
#line 927 "weaver-interface-metafont.tex"

#include <string.h> 
/*:39*//*82:*/
#line 1879 "weaver-interface-metafont.tex"

#include <math.h> 
/*:82*//*102:*/
#line 2273 "weaver-interface-metafont.tex"

struct pen_variable;
/*:102*//*279:*/
#line 7121 "weaver-interface-metafont.tex"

#include <complex.h> 
/*:279*/
#line 229 "weaver-interface-metafont.tex"

/*85:*/
#line 1936 "weaver-interface-metafont.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
/*:85*//*94:*/
#line 2096 "weaver-interface-metafont.tex"

#define INTERNAL_TRANSFORM_IDENTITY 0
/*:94*//*104:*/
#line 2319 "weaver-interface-metafont.tex"

#define FLAG_CONVEX   1
#define FLAG_STRAIGHT 2
#define FLAG_CIRCULAR 4
#define FLAG_SQUARE   8
#define FLAG_NULL    16
/*:104*//*110:*/
#line 2487 "weaver-interface-metafont.tex"

#define INTERNAL_PEN_CURRENTPEN 0
#define INTERNAL_PEN_PENSQUARE  1
/*:110*//*119:*/
#line 2616 "weaver-interface-metafont.tex"

#define INTERNAL_PICTURE_CURRENTPICTURE 0
/*:119*//*134:*/
#line 2958 "weaver-interface-metafont.tex"

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
/*:134*//*135:*/
#line 3006 "weaver-interface-metafont.tex"

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
/*:135*/
#line 230 "weaver-interface-metafont.tex"

/*11:*/
#line 312 "weaver-interface-metafont.tex"

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
#line 328 "weaver-interface-metafont.tex"

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
#line 355 "weaver-interface-metafont.tex"

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
#line 380 "weaver-interface-metafont.tex"

#define TYPE_OPEN_PARENTHESIS  4 
#define TYPE_CLOSE_PARENTHESIS 5 
#define TYPE_COMMA             6 
#define TYPE_SEMICOLON         7 
/*41:*/
#line 999 "weaver-interface-metafont.tex"

#define TYPE_END             8 
#define TYPE_DUMP            9 
/*:41*//*53:*/
#line 1270 "weaver-interface-metafont.tex"

#define TYPE_BEGINGROUP            10 
#define TYPE_ENDGROUP              11 
/*:53*//*61:*/
#line 1436 "weaver-interface-metafont.tex"

#define TYPE_T_BOOLEAN               12 
#define TYPE_T_PATH                  13 
#define TYPE_T_PEN                   14 
#define TYPE_T_PICTURE               15 
#define TYPE_T_TRANSFORM             16 
#define TYPE_T_PAIR                  17 
#define TYPE_T_NUMERIC               18 
/*:61*//*124:*/
#line 2704 "weaver-interface-metafont.tex"

#define TYPE_ASSIGNMENT            19 
#define TYPE_ASSIGNMENT2           20 
/*:124*//*131:*/
#line 2912 "weaver-interface-metafont.tex"

#define TYPE_SUM                   21 
#define TYPE_SUBTRACT              22 
#define TYPE_PYTHAGOREAN_SUM       23 
#define TYPE_PYTHAGOREAN_SUBTRACT  24 
#define TYPE_OPEN_BRACKETS         25 
#define TYPE_CLOSE_BRACKETS        26 
#define TYPE_OPEN_BRACES           27 
#define TYPE_CLOSE_BRACES          28 
/*:131*//*137:*/
#line 3117 "weaver-interface-metafont.tex"

#define TYPE_MULTIPLICATION        29 
#define TYPE_DIVISION              30 
/*:137*//*141:*/
#line 3244 "weaver-interface-metafont.tex"

#define TYPE_LENGTH         31 
#define TYPE_SQRT           32 
#define TYPE_SIND           33 
#define TYPE_COSD           34 
#define TYPE_LOG            35 
#define TYPE_EXP            36 
#define TYPE_FLOOR          37 
#define TYPE_UNIFORMDEVIATE 38 
/*:141*//*159:*/
#line 3671 "weaver-interface-metafont.tex"

#define TYPE_NORMALDEVIATE  39 
/*:159*//*175:*/
#line 4043 "weaver-interface-metafont.tex"

#define TYPE_ROTATED  40 
#define TYPE_SCALED   41 
#define TYPE_SHIFTED  42 
#define TYPE_SLANTED  43 
#define TYPE_XSCALED  44 
#define TYPE_YSCALED  45 
#define TYPE_ZSCALED  46 
/*:175*//*195:*/
#line 4695 "weaver-interface-metafont.tex"

#define TYPE_XPART  47 
#define TYPE_YPART  48 
#define TYPE_ANGLE  49 
/*:195*//*202:*/
#line 4846 "weaver-interface-metafont.tex"

#define TYPE_TRANSFORMED  50 
/*:202*//*221:*/
#line 5482 "weaver-interface-metafont.tex"

#define TYPE_XXPART  51 
#define TYPE_XYPART  52 
#define TYPE_YXPART  53 
#define TYPE_YYPART  54 
/*:221*//*231:*/
#line 5685 "weaver-interface-metafont.tex"

#define TYPE_CYCLE          55 
#define TYPE_AMPERSAND      56 
#define TYPE_JOIN           57 
#define TYPE_TENSION        58 
#define TYPE_AND            59 
#define TYPE_ATLEAST        60 
#define TYPE_CONTROLS       61 
#define TYPE_CURL           52 

#define TYPE_STRAIGHT_JOIN  63 
/*:231*//*310:*/
#line 7915 "weaver-interface-metafont.tex"

#define TYPE_REVERSE        64 
#define TYPE_SUBPATH        65 
#define TYPE_OF             66 
/*:310*//*327:*/
#line 8482 "weaver-interface-metafont.tex"

#define TYPE_POINT             67 
#define TYPE_PRECONTROL        68 
#define TYPE_POSTCONTROL       69 
/*:327*//*348:*/
#line 9171 "weaver-interface-metafont.tex"

#define TYPE_NULLPEN        70 
#define TYPE_PENCIRCLE      71 
#define TYPE_MAKEPEN        72 
/*:348*//*359:*/
#line 9474 "weaver-interface-metafont.tex"

#define TYPE_MAKEPATH       73 
/*:359*//*401:*/
#line 10766 "weaver-interface-metafont.tex"

#define TYPE_NULLPICTURE        74 
/*:401*//*410:*/
#line 11037 "weaver-interface-metafont.tex"

#define TYPE_TOTALWEIGHT        75 
/*:410*/
#line 385 "weaver-interface-metafont.tex"


struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:14*//*63:*/
#line 1475 "weaver-interface-metafont.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:63*//*64:*/
#line 1495 "weaver-interface-metafont.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:64*//*80:*/
#line 1851 "weaver-interface-metafont.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:80*//*88:*/
#line 1984 "weaver-interface-metafont.tex"

struct pair_variable{
int type;
int nesting_level;
void*next;
float x,y;
};
/*:88*//*90:*/
#line 2031 "weaver-interface-metafont.tex"

struct transform_variable{
int type;
int nesting_level;
void*next;
float value[6];
};
/*:90*//*96:*/
#line 2153 "weaver-interface-metafont.tex"

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
/*:96*//*103:*/
#line 2279 "weaver-interface-metafont.tex"

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
/*:103*//*113:*/
#line 2532 "weaver-interface-metafont.tex"

struct picture_variable{
int type;
int nesting_level;
void*next;
int width,height;
GLuint texture;
};
/*:113*//*122:*/
#line 2652 "weaver-interface-metafont.tex"

struct boolean_variable{
int type;
int nesting_level;
void*next;
short value;
};
/*:122*/
#line 231 "weaver-interface-metafont.tex"

/*8:*/
#line 250 "weaver-interface-metafont.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:8*//*37:*/
#line 879 "weaver-interface-metafont.tex"

static char*list_of_keywords[]= {
/*42:*/
#line 1009 "weaver-interface-metafont.tex"

"end","dump",
/*:42*//*54:*/
#line 1279 "weaver-interface-metafont.tex"

"begingroup","endgroup",
/*:54*//*62:*/
#line 1450 "weaver-interface-metafont.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:62*//*125:*/
#line 2713 "weaver-interface-metafont.tex"

"=",":=",
/*:125*//*132:*/
#line 2927 "weaver-interface-metafont.tex"

"+","-","++","+-+","[","]","{","}",
/*:132*//*138:*/
#line 3124 "weaver-interface-metafont.tex"

"*","/",
/*:138*//*142:*/
#line 3257 "weaver-interface-metafont.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:142*//*160:*/
#line 3677 "weaver-interface-metafont.tex"

"normaldeviate",
/*:160*//*176:*/
#line 4055 "weaver-interface-metafont.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:176*//*196:*/
#line 4705 "weaver-interface-metafont.tex"

"xpart","ypart","angle",
/*:196*//*203:*/
#line 4854 "weaver-interface-metafont.tex"

"transformed",
/*:203*//*222:*/
#line 5493 "weaver-interface-metafont.tex"

"xxpart","xypart","yxpart","yypart",
/*:222*//*232:*/
#line 5703 "weaver-interface-metafont.tex"

"cycle","&","..","tension","and","atleast","controls","curl","--",
/*:232*//*311:*/
#line 7926 "weaver-interface-metafont.tex"

"reverse","subpath","of",
/*:311*//*328:*/
#line 8492 "weaver-interface-metafont.tex"

"point","precontrol","postcontrol",
/*:328*//*349:*/
#line 9182 "weaver-interface-metafont.tex"

"nullpen","pencircle","makepen",
/*:349*//*360:*/
#line 9482 "weaver-interface-metafont.tex"

"makepath",
/*:360*//*402:*/
#line 10774 "weaver-interface-metafont.tex"

"nullpicture",
/*:402*//*411:*/
#line 11045 "weaver-interface-metafont.tex"

"totalweight",
/*:411*/
#line 881 "weaver-interface-metafont.tex"

NULL};
/*:37*//*368:*/
#line 9739 "weaver-interface-metafont.tex"

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
/*:368*//*371:*/
#line 9794 "weaver-interface-metafont.tex"

static const char vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat4 model_view_matrix;\n"
"varying highp vec2 texture_coordinate;\n"
"void main(){\n"
"  gl_Position = vec4(vertex_data.xy, 0.0, 1.0) * model_view_matrix;\n"
"  texture_coordinate = vertex_data.zw;\n"
"}\n";
/*:371*//*372:*/
#line 9811 "weaver-interface-metafont.tex"

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
/*:372*//*385:*/
#line 10179 "weaver-interface-metafont.tex"

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
/*:385*/
#line 232 "weaver-interface-metafont.tex"

/*47:*/
#line 1088 "weaver-interface-metafont.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct context*cx);
/*:47*//*51:*/
#line 1195 "weaver-interface-metafont.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:51*//*55:*/
#line 1288 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:55*//*74:*/
#line 1682 "weaver-interface-metafont.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:74*//*76:*/
#line 1751 "weaver-interface-metafont.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:76*//*78:*/
#line 1812 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:78*//*100:*/
#line 2236 "weaver-interface-metafont.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer);
/*:100*//*129:*/
#line 2848 "weaver-interface-metafont.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source);

/*:129*//*133:*/
#line 2937 "weaver-interface-metafont.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:133*//*139:*/
#line 3135 "weaver-interface-metafont.tex"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:139*//*143:*/
#line 3265 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:143*//*147:*/
#line 3368 "weaver-interface-metafont.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:147*//*161:*/
#line 3688 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:161*//*171:*/
#line 3926 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source);
/*:171*//*173:*/
#line 3963 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result);
/*:173*//*177:*/
#line 4064 "weaver-interface-metafont.tex"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:177*//*188:*/
#line 4392 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:188*//*204:*/
#line 4871 "weaver-interface-metafont.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:204*//*206:*/
#line 4896 "weaver-interface-metafont.tex"

bool eval_transform_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:206*//*216:*/
#line 5325 "weaver-interface-metafont.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:216*//*225:*/
#line 5555 "weaver-interface-metafont.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source);
/*:225*//*227:*/
#line 5592 "weaver-interface-metafont.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target);
/*:227*//*229:*/
#line 5628 "weaver-interface-metafont.tex"

void recursive_aux_copy(struct path_points**dst,struct path_variable*origin);
/*:229*//*233:*/
#line 5718 "weaver-interface-metafont.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:233*//*235:*/
#line 5761 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:235*//*250:*/
#line 6207 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y);
/*:250*//*277:*/
#line 7099 "weaver-interface-metafont.tex"

double compute_f(double theta,double phi);
/*:277*//*281:*/
#line 7161 "weaver-interface-metafont.tex"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y);
/*:281*//*283:*/
#line 7199 "weaver-interface-metafont.tex"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y);
/*:283*//*289:*/
#line 7402 "weaver-interface-metafont.tex"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:289*//*291:*/
#line 7492 "weaver-interface-metafont.tex"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:291*//*294:*/
#line 7628 "weaver-interface-metafont.tex"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta);
/*:294*//*297:*/
#line 7680 "weaver-interface-metafont.tex"

void path_xyscale(struct path_variable*p,float x,float y);
/*:297*//*300:*/
#line 7731 "weaver-interface-metafont.tex"

void path_shift(struct path_variable*p,float x,float y);
/*:300*//*303:*/
#line 7776 "weaver-interface-metafont.tex"

void path_slant(struct path_variable*p,float s);
/*:303*//*308:*/
#line 7866 "weaver-interface-metafont.tex"

void path_zscale(struct path_variable*p,float x,float y);
/*:308*//*312:*/
#line 7942 "weaver-interface-metafont.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:312*//*316:*/
#line 8081 "weaver-interface-metafont.tex"

void reverse_path(struct path_variable*src,struct path_variable*dst);
/*:316*//*319:*/
#line 8252 "weaver-interface-metafont.tex"

void copy_subpath(struct path_points*dst,struct path_variable*src,int offset,int size);
/*:319*//*321:*/
#line 8282 "weaver-interface-metafont.tex"

int recursive_copy_subpath(struct path_points**dst,
struct path_variable*pointer,
int*index,int*offset,int*size);
/*:321*//*329:*/
#line 8508 "weaver-interface-metafont.tex"

struct path_points*get_point(struct path_variable*v,int n);
/*:329*//*331:*/
#line 8538 "weaver-interface-metafont.tex"

struct path_points*_get_point(struct path_variable*v,int n,int*count);
/*:331*//*335:*/
#line 8694 "weaver-interface-metafont.tex"

void assign_pen_variable(struct metafont*mf,
struct pen_variable*target,
struct pen_variable*source);
/*:335*//*337:*/
#line 8748 "weaver-interface-metafont.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:337*//*339:*/
#line 8792 "weaver-interface-metafont.tex"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:339*//*350:*/
#line 9190 "weaver-interface-metafont.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result);
/*:350*//*357:*/
#line 9381 "weaver-interface-metafont.tex"

int read_flags(struct path_variable*path);
/*:357*//*373:*/
#line 9830 "weaver-interface-metafont.tex"

GLuint compile_shader_program(const char*vertex_shader_source,
const char*fragment_shader_source);
/*:373*//*377:*/
#line 9915 "weaver-interface-metafont.tex"

bool get_new_framebuffer(GLuint*new_framebuffer,GLuint*new_texture,
int width,int height);
/*:377*//*379:*/
#line 9955 "weaver-interface-metafont.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height,bool clear_background);

void print_picture(struct picture_variable*pic);
/*:379*//*381:*/
#line 10017 "weaver-interface-metafont.tex"

void assign_picture_variable(struct metafont*mf,
struct picture_variable*target,
struct picture_variable*source);
/*:381*//*383:*/
#line 10071 "weaver-interface-metafont.tex"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result);
/*:383*//*390:*/
#line 10351 "weaver-interface-metafont.tex"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result,
float*matrix,bool*modified);
/*:390*//*399:*/
#line 10647 "weaver-interface-metafont.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*origin,
float*matrix);
/*:399*//*403:*/
#line 10782 "weaver-interface-metafont.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result);
/*:403*/
#line 233 "weaver-interface-metafont.tex"

/*15:*/
#line 408 "weaver-interface-metafont.tex"

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
#line 431 "weaver-interface-metafont.tex"

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
#line 483 "weaver-interface-metafont.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:18*/
#line 448 "weaver-interface-metafont.tex"

/*20:*/
#line 504 "weaver-interface-metafont.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:20*/
#line 449 "weaver-interface-metafont.tex"

/*21:*/
#line 521 "weaver-interface-metafont.tex"

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
#line 450 "weaver-interface-metafont.tex"

/*22:*/
#line 569 "weaver-interface-metafont.tex"

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
#line 451 "weaver-interface-metafont.tex"

/*23:*/
#line 614 "weaver-interface-metafont.tex"

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
#line 452 "weaver-interface-metafont.tex"

/*24:*/
#line 649 "weaver-interface-metafont.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*25:*/
#line 682 "weaver-interface-metafont.tex"

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
#line 655 "weaver-interface-metafont.tex"

/*26:*/
#line 699 "weaver-interface-metafont.tex"

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
#line 656 "weaver-interface-metafont.tex"

/*27:*/
#line 715 "weaver-interface-metafont.tex"

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
#line 657 "weaver-interface-metafont.tex"

/*28:*/
#line 731 "weaver-interface-metafont.tex"

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
#line 658 "weaver-interface-metafont.tex"

/*29:*/
#line 747 "weaver-interface-metafont.tex"

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
#line 659 "weaver-interface-metafont.tex"

/*30:*/
#line 763 "weaver-interface-metafont.tex"

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
#line 660 "weaver-interface-metafont.tex"

/*31:*/
#line 779 "weaver-interface-metafont.tex"

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
#line 661 "weaver-interface-metafont.tex"

/*32:*/
#line 795 "weaver-interface-metafont.tex"

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
#line 662 "weaver-interface-metafont.tex"

/*33:*/
#line 811 "weaver-interface-metafont.tex"

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
#line 663 "weaver-interface-metafont.tex"

/*34:*/
#line 827 "weaver-interface-metafont.tex"

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
#line 664 "weaver-interface-metafont.tex"

/*35:*/
#line 843 "weaver-interface-metafont.tex"

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
#line 665 "weaver-interface-metafont.tex"

/*36:*/
#line 859 "weaver-interface-metafont.tex"

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
#line 666 "weaver-interface-metafont.tex"


/*38:*/
#line 892 "weaver-interface-metafont.tex"

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
#line 1019 "weaver-interface-metafont.tex"

if(token_type==TYPE_DUMP)
token_type= TYPE_END;
/*:43*//*126:*/
#line 2722 "weaver-interface-metafont.tex"

else if(token_type==TYPE_ASSIGNMENT2)
token_type= TYPE_ASSIGNMENT;
/*:126*/
#line 905 "weaver-interface-metafont.tex"

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
#line 668 "weaver-interface-metafont.tex"

/*40:*/
#line 936 "weaver-interface-metafont.tex"

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
#line 1959 "weaver-interface-metafont.tex"

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
/*:87*//*95:*/
#line 2106 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"identity"))
new_token->var= 
&(mf->internal_transform_variables[INTERNAL_TRANSFORM_IDENTITY]);
/*:95*//*112:*/
#line 2512 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"currentpen"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN]);
else if(!strcmp(buffer,"pensquare"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_PENSQUARE]);
/*:112*//*121:*/
#line 2639 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"currentpicture"))
new_token->var= 
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE]);
/*:121*/
#line 949 "weaver-interface-metafont.tex"

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
#line 669 "weaver-interface-metafont.tex"

}
/*:24*/
#line 453 "weaver-interface-metafont.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
fclose(fp);
return first_token;
}
/*:16*//*44:*/
#line 1033 "weaver-interface-metafont.tex"

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
#line 1104 "weaver-interface-metafont.tex"

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
#line 1517 "weaver-interface-metafont.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:66*//*84:*/
#line 1908 "weaver-interface-metafont.tex"

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
/*:84*//*93:*/
#line 2072 "weaver-interface-metafont.tex"

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
/*:93*//*109:*/
#line 2450 "weaver-interface-metafont.tex"

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
/*:109*//*118:*/
#line 2596 "weaver-interface-metafont.tex"

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
/*:118*//*166:*/
#line 3812 "weaver-interface-metafont.tex"

mf->have_stored_normaldeviate= false;
/*:166*/
#line 1115 "weaver-interface-metafont.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*59:*/
#line 1344 "weaver-interface-metafont.tex"

cx->nesting_level= 0;
/*:59*//*70:*/
#line 1578 "weaver-interface-metafont.tex"

cx->variables= NULL;
/*:70*/
#line 1121 "weaver-interface-metafont.tex"

return cx;
}
/*:48*//*49:*/
#line 1130 "weaver-interface-metafont.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*67:*/
#line 1529 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*98:*/
#line 2206 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:98*//*106:*/
#line 2399 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:106*//*115:*/
#line 2560 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:115*/
#line 1535 "weaver-interface-metafont.tex"

mf->free(v);
v= next;
}
}
/*:67*//*68:*/
#line 1547 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)(named->var);
next= (struct named_variable*)(named->next);
mf->free(named->name);
/*98:*/
#line 2206 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:98*//*106:*/
#line 2399 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:106*//*115:*/
#line 2560 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:115*/
#line 1556 "weaver-interface-metafont.tex"

mf->free(v);
mf->free(named);
named= next;
}
}
/*:68*//*86:*/
#line 1947 "weaver-interface-metafont.tex"

if(mf->free!=NULL)
mf->free(mf->internal_numeric_variables);
/*:86*//*111:*/
#line 2497 "weaver-interface-metafont.tex"

if(mf->free!=NULL){
if(mf->internal_pen_variables[1].format!=NULL){
mf->free(mf->internal_pen_variables[1].format->points);
mf->free(mf->internal_pen_variables[1].format);
}
mf->free(mf->internal_pen_variables);
}
/*:111*//*120:*/
#line 2626 "weaver-interface-metafont.tex"

if(mf->internal_picture_variables[0].texture!=0)
glDeleteTextures(1,&(mf->internal_picture_variables[0].texture));
if(mf->free!=NULL)
mf->free(mf->internal_picture_variables);
/*:120*/
#line 1134 "weaver-interface-metafont.tex"

mf->free(mf);
}
}
void destroy_context(struct context*cx){
if(temporary_free!=NULL){
/*71:*/
#line 1586 "weaver-interface-metafont.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*99:*/
#line 2220 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL)
path_recursive_free(temporary_free,path,false);
}
/*:99*//*107:*/
#line 2416 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->referenced==NULL){
if(pen->format!=NULL&&temporary_free!=NULL)
path_recursive_free(temporary_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
}
/*:107*//*116:*/
#line 2572 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:116*/
#line 1592 "weaver-interface-metafont.tex"

temporary_free(v);
v= next;
}
}
/*:71*/
#line 1140 "weaver-interface-metafont.tex"

temporary_free(cx);
}
}
/*:49*//*52:*/
#line 1208 "weaver-interface-metafont.tex"

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
#line 1294 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*57:*/
#line 1321 "weaver-interface-metafont.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:57*/
#line 1297 "weaver-interface-metafont.tex"

/*60:*/
#line 1377 "weaver-interface-metafont.tex"

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
#line 1298 "weaver-interface-metafont.tex"

/*72:*/
#line 1603 "weaver-interface-metafont.tex"

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
#line 1653 "weaver-interface-metafont.tex"

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
#line 1620 "weaver-interface-metafont.tex"

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
#line 1299 "weaver-interface-metafont.tex"

/*127:*/
#line 2746 "weaver-interface-metafont.tex"

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
/*128:*/
#line 2824 "weaver-interface-metafont.tex"

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
/*:128*/
#line 2807 "weaver-interface-metafont.tex"

/*170:*/
#line 3905 "weaver-interface-metafont.tex"

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
/*:170*/
#line 2808 "weaver-interface-metafont.tex"

/*201:*/
#line 4800 "weaver-interface-metafont.tex"

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
/*:201*/
#line 2809 "weaver-interface-metafont.tex"

/*224:*/
#line 5531 "weaver-interface-metafont.tex"

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
/*:224*/
#line 2810 "weaver-interface-metafont.tex"

/*334:*/
#line 8667 "weaver-interface-metafont.tex"

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
/*:334*/
#line 2811 "weaver-interface-metafont.tex"

/*367:*/
#line 9698 "weaver-interface-metafont.tex"

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
/*:367*/
#line 2812 "weaver-interface-metafont.tex"

return true;
}
/*:127*/
#line 1300 "weaver-interface-metafont.tex"




#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:56*//*75:*/
#line 1695 "weaver-interface-metafont.tex"

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
/*81:*/
#line 1868 "weaver-interface-metafont.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:81*//*89:*/
#line 1999 "weaver-interface-metafont.tex"

if(type==TYPE_T_PAIR){
((struct pair_variable*)var)->x= NAN;
}
/*:89*//*91:*/
#line 2045 "weaver-interface-metafont.tex"

if(type==TYPE_T_TRANSFORM)
((struct transform_variable*)var)->value[0]= NAN;
/*:91*//*97:*/
#line 2194 "weaver-interface-metafont.tex"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
((struct path_variable*)var)->points= NULL;
}
/*:97*//*105:*/
#line 2384 "weaver-interface-metafont.tex"

if(type==TYPE_T_PEN){
((struct pen_variable*)var)->format= NULL;
((struct pen_variable*)var)->gl_vbo= 0;
((struct pen_variable*)var)->flags= false;
((struct pen_variable*)var)->referenced= NULL;
}
/*:105*//*114:*/
#line 2547 "weaver-interface-metafont.tex"

if(type==TYPE_T_PICTURE){
((struct picture_variable*)var)->width= -1;
((struct picture_variable*)var)->height= -1;
((struct picture_variable*)var)->texture= 0;
}
/*:114*//*123:*/
#line 2667 "weaver-interface-metafont.tex"

if(type==TYPE_T_BOOLEAN)
((struct boolean_variable*)var)->value= -1;
/*:123*/
#line 1733 "weaver-interface-metafont.tex"

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
#line 1762 "weaver-interface-metafont.tex"

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
/*:77*//*79:*/
#line 1825 "weaver-interface-metafont.tex"

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
/*:79*//*101:*/
#line 2246 "weaver-interface-metafont.tex"

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
/*:101*//*130:*/
#line 2858 "weaver-interface-metafont.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source){
target->value= source->value;
}
/*:130*//*136:*/
#line 3045 "weaver-interface-metafont.tex"

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
/*:136*//*140:*/
#line 3158 "weaver-interface-metafont.tex"

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
/*:140*//*144:*/
#line 3277 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*145:*/
#line 3303 "weaver-interface-metafont.tex"

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
/*:145*/
#line 3282 "weaver-interface-metafont.tex"

/*146:*/
#line 3327 "weaver-interface-metafont.tex"

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
/*197:*/
#line 4716 "weaver-interface-metafont.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)hypot(p.x*p.x,p.y*p.y);
return true;
}
/*:197*//*326:*/
#line 8452 "weaver-interface-metafont.tex"

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
/*:326*/
#line 3344 "weaver-interface-metafont.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:146*/
#line 3283 "weaver-interface-metafont.tex"

/*149:*/
#line 3415 "weaver-interface-metafont.tex"

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
/*:149*//*150:*/
#line 3443 "weaver-interface-metafont.tex"

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
/*:150*//*151:*/
#line 3462 "weaver-interface-metafont.tex"

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
/*:151*//*152:*/
#line 3481 "weaver-interface-metafont.tex"

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
/*:152*//*153:*/
#line 3507 "weaver-interface-metafont.tex"

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
/*:153*//*154:*/
#line 3525 "weaver-interface-metafont.tex"

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
/*:154*//*155:*/
#line 3556 "weaver-interface-metafont.tex"

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
/*:155*//*156:*/
#line 3579 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:156*//*157:*/
#line 3596 "weaver-interface-metafont.tex"

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
/*:157*/
#line 3284 "weaver-interface-metafont.tex"

/*198:*/
#line 4733 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_XPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.x;
return true;
}
/*:198*//*199:*/
#line 4750 "weaver-interface-metafont.tex"

else if(begin_expression->type==TYPE_YPART){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= p.y;
return true;
}
/*:199*//*200:*/
#line 4769 "weaver-interface-metafont.tex"

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
/*:200*//*223:*/
#line 5502 "weaver-interface-metafont.tex"

else if(begin_expression->type>=TYPE_XXPART&&
begin_expression->type<=TYPE_YYPART){
struct transform_variable t;
if(!eval_transform_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&t))
return false;
switch(begin_expression->type){
case TYPE_XPART:
result->value= t.value[0];
return true;
case TYPE_YPART:
result->value= t.value[1];
return true;
default:
result->value= t.value[2+begin_expression->type-TYPE_XXPART];
return true;
}
}
/*:223*//*412:*/
#line 11055 "weaver-interface-metafont.tex"

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
/*:412*/
#line 3285 "weaver-interface-metafont.tex"

/*158:*/
#line 3622 "weaver-interface-metafont.tex"

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
/*:158*/
#line 3286 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:144*//*148:*/
#line 3376 "weaver-interface-metafont.tex"

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
/*:148*//*162:*/
#line 3701 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*163:*/
#line 3723 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:163*/
#line 3707 "weaver-interface-metafont.tex"

/*164:*/
#line 3736 "weaver-interface-metafont.tex"

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
/*:164*/
#line 3708 "weaver-interface-metafont.tex"

/*167:*/
#line 3822 "weaver-interface-metafont.tex"

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
/*:167*/
#line 3709 "weaver-interface-metafont.tex"

}
else{
/*168:*/
#line 3857 "weaver-interface-metafont.tex"

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
/*:168*/
#line 3712 "weaver-interface-metafont.tex"

/*169:*/
#line 3886 "weaver-interface-metafont.tex"

if(begin_expression->type==TYPE_NUMERIC&&
end_expression->type==TYPE_NUMERIC&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION){
result->value= ((struct numeric_token*)begin_expression)->value/
((struct numeric_token*)end_expression)->value;
return true;
}
/*:169*/
#line 3713 "weaver-interface-metafont.tex"

}
return false;
}
/*:162*//*172:*/
#line 3935 "weaver-interface-metafont.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source){
target->x= source->x;
target->y= source->y;
}
/*:172*//*174:*/
#line 3976 "weaver-interface-metafont.tex"

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
/*:174*//*178:*/
#line 4084 "weaver-interface-metafont.tex"

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
/*179:*/
#line 4151 "weaver-interface-metafont.tex"

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
/*:179*/
#line 4121 "weaver-interface-metafont.tex"

/*180:*/
#line 4190 "weaver-interface-metafont.tex"

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
/*:180*/
#line 4122 "weaver-interface-metafont.tex"

/*181:*/
#line 4218 "weaver-interface-metafont.tex"

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
/*:181*/
#line 4123 "weaver-interface-metafont.tex"

/*182:*/
#line 4242 "weaver-interface-metafont.tex"

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
/*:182*/
#line 4124 "weaver-interface-metafont.tex"

/*183:*/
#line 4263 "weaver-interface-metafont.tex"

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
/*:183*/
#line 4125 "weaver-interface-metafont.tex"

/*184:*/
#line 4284 "weaver-interface-metafont.tex"

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
/*:184*/
#line 4126 "weaver-interface-metafont.tex"

/*185:*/
#line 4305 "weaver-interface-metafont.tex"

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
/*:185*/
#line 4127 "weaver-interface-metafont.tex"

/*186:*/
#line 4326 "weaver-interface-metafont.tex"

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
/*:186*/
#line 4128 "weaver-interface-metafont.tex"

/*187:*/
#line 4351 "weaver-interface-metafont.tex"

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
/*:187*/
#line 4129 "weaver-interface-metafont.tex"

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
/*:178*//*189:*/
#line 4405 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
if(begin_expression==end_expression){
/*190:*/
#line 4434 "weaver-interface-metafont.tex"

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
/*:190*/
#line 4411 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*191:*/
#line 4474 "weaver-interface-metafont.tex"

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
/*:191*/
#line 4415 "weaver-interface-metafont.tex"

/*192:*/
#line 4535 "weaver-interface-metafont.tex"

else{
return eval_pair_expression(mf,cx,begin_a,end_a,result);
}
/*:192*/
#line 4416 "weaver-interface-metafont.tex"

}
/*333:*/
#line 8584 "weaver-interface-metafont.tex"

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
/*:333*/
#line 4418 "weaver-interface-metafont.tex"

/*193:*/
#line 4547 "weaver-interface-metafont.tex"

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
/*:193*/
#line 4419 "weaver-interface-metafont.tex"

/*194:*/
#line 4630 "weaver-interface-metafont.tex"

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
/*:194*/
#line 4420 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:189*//*205:*/
#line 4882 "weaver-interface-metafont.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result){
return eval_transform_secondary(mf,cx,begin_expression,end_expression,
result);
}
/*:205*//*207:*/
#line 4914 "weaver-interface-metafont.tex"

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
/*208:*/
#line 4991 "weaver-interface-metafont.tex"

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
/*:208*//*209:*/
#line 5038 "weaver-interface-metafont.tex"

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
/*:209*//*210:*/
#line 5078 "weaver-interface-metafont.tex"

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
/*:210*//*211:*/
#line 5115 "weaver-interface-metafont.tex"

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
/*:211*//*212:*/
#line 5154 "weaver-interface-metafont.tex"

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
/*:212*//*213:*/
#line 5193 "weaver-interface-metafont.tex"

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
/*:213*//*214:*/
#line 5234 "weaver-interface-metafont.tex"

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
/*:214*//*215:*/
#line 5278 "weaver-interface-metafont.tex"

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
/*:215*/
#line 4953 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transformer "
"in transform expression.",mf->file,begin_expression->line);
#endif
return false;
}
}
/*:207*//*217:*/
#line 5336 "weaver-interface-metafont.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result){
if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*218:*/
#line 5383 "weaver-interface-metafont.tex"

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
/*:218*/
#line 5343 "weaver-interface-metafont.tex"

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
/*220:*/
#line 5423 "weaver-interface-metafont.tex"

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
(i==5&&p->type==TYPE_CLOSE_PARENTHESIS)))
break;
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
/*:220*/
#line 5365 "weaver-interface-metafont.tex"

}
else{
/*219:*/
#line 5403 "weaver-interface-metafont.tex"

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
/*:219*/
#line 5368 "weaver-interface-metafont.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transform primary "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:217*//*226:*/
#line 5565 "weaver-interface-metafont.tex"

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
/*:226*//*228:*/
#line 5605 "weaver-interface-metafont.tex"

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
/*:228*//*230:*/
#line 5634 "weaver-interface-metafont.tex"

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
/*:230*//*234:*/
#line 5729 "weaver-interface-metafont.tex"

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
/*:234*//*236:*/
#line 5776 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin_expression,end_expression);
expected_length= number_of_joins+1;
/*237:*/
#line 5801 "weaver-interface-metafont.tex"

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
/*:237*/
#line 5784 "weaver-interface-metafont.tex"

/*238:*/
#line 5827 "weaver-interface-metafont.tex"

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
/*:238*/
#line 5785 "weaver-interface-metafont.tex"

/*239:*/
#line 5857 "weaver-interface-metafont.tex"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d= NULL,*end_d= NULL,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
struct path_points*z1_point= NULL,*z2_point= NULL;
/*248:*/
#line 6173 "weaver-interface-metafont.tex"

float w0_x= NAN,w0_y= NAN,w1_x= NAN,w1_y= NAN;
float prev_w_x= NAN,prev_w_y= NAN;
float next_w_x= NAN,next_w_y= NAN;
/*:248*//*264:*/
#line 6741 "weaver-interface-metafont.tex"

float first_w_x= NAN,first_w_y= NAN;
/*:264*//*268:*/
#line 6844 "weaver-interface-metafont.tex"

float previous_point_x= NAN,previous_point_y= NAN;
/*:268*//*272:*/
#line 6952 "weaver-interface-metafont.tex"

float first_point_x= NAN,first_point_y= NAN;
/*:272*/
#line 5863 "weaver-interface-metafont.tex"

begin_z1= begin_expression;
end_z1= begin_z1;
while(begin_z1!=end_expression||result->length<expected_length){
/*240:*/
#line 5888 "weaver-interface-metafont.tex"

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
/*:240*//*241:*/
#line 5914 "weaver-interface-metafont.tex"

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
/*:241*//*242:*/
#line 5951 "weaver-interface-metafont.tex"

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
/*:242*//*243:*/
#line 5989 "weaver-interface-metafont.tex"

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
/*:243*//*244:*/
#line 6029 "weaver-interface-metafont.tex"

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
/*:244*/
#line 5867 "weaver-interface-metafont.tex"

/*245:*/
#line 6062 "weaver-interface-metafont.tex"

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
/*:245*//*246:*/
#line 6096 "weaver-interface-metafont.tex"

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
/*:246*//*247:*/
#line 6148 "weaver-interface-metafont.tex"

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
/*:247*/
#line 5868 "weaver-interface-metafont.tex"

/*249:*/
#line 6190 "weaver-interface-metafont.tex"

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
/*:249*/
#line 5869 "weaver-interface-metafont.tex"

/*255:*/
#line 6312 "weaver-interface-metafont.tex"

float tension0= NAN,tension1= NAN,u_x= NAN,u_y= NAN,v_x= NAN,
v_y= NAN;
bool atleast0= false,atleast1= false;
/*:255*//*256:*/
#line 6329 "weaver-interface-metafont.tex"

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
/*:256*//*257:*/
#line 6357 "weaver-interface-metafont.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_STRAIGHT_JOIN){
u_x= z1_point->x+(1.0/3.0)*(z2_point->x-z1_point->x);
u_y= z1_point->y+(1.0/3.0)*(z2_point->y-z1_point->y);
v_x= z1_point->x+(2.0/3.0)*(z2_point->x-z1_point->x);
v_y= z1_point->y+(2.0/3.0)*(z2_point->y-z1_point->y);
}
/*:257*//*258:*/
#line 6372 "weaver-interface-metafont.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
tension0= 1.0;
tension1= 1.0;
atleast0= false;
atleast1= false;
}
/*:258*//*259:*/
#line 6390 "weaver-interface-metafont.tex"

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
/*:259*//*260:*/
#line 6456 "weaver-interface-metafont.tex"

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
/*:260*/
#line 5870 "weaver-interface-metafont.tex"

/*262:*/
#line 6678 "weaver-interface-metafont.tex"

if(isnan(w0_x)&&isnan(w0_y)){
w0_x= prev_w_x;
w0_y= prev_w_y;
}
/*:262*//*263:*/
#line 6691 "weaver-interface-metafont.tex"

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
/*:263*//*265:*/
#line 6751 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d!=NULL&&end_d!=NULL){
first_w_x= w0_x;
first_w_y= w0_y;
}
/*:265*//*266:*/
#line 6764 "weaver-interface-metafont.tex"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE){
if(!isnan(first_w_x)&&isnan(w1_x)){
w1_x= first_w_x;
w1_y= first_w_y;
}
}
/*:266*//*267:*/
#line 6783 "weaver-interface-metafont.tex"

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
/*275:*/
#line 6998 "weaver-interface-metafont.tex"

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
/*:275*/
#line 6817 "weaver-interface-metafont.tex"

}
/*:267*//*269:*/
#line 6857 "weaver-interface-metafont.tex"

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
/*:269*//*270:*/
#line 6877 "weaver-interface-metafont.tex"

if(begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
previous_point_x= v_x;
previous_point_y= v_y;
}
else{
previous_point_x= NAN;
previous_point_y= NAN;
}
/*:270*//*271:*/
#line 6896 "weaver-interface-metafont.tex"

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
/*:271*//*273:*/
#line 6960 "weaver-interface-metafont.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
first_point_x= u_x;
first_point_y= u_y;
}
/*:273*//*274:*/
#line 6974 "weaver-interface-metafont.tex"

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
/*:274*//*276:*/
#line 7041 "weaver-interface-metafont.tex"

if(isnan(u_x)||isnan(u_y)||isnan(v_x)||isnan(v_y)){
if(isnan(w0_x)||isnan(w0_y)||isnan(w1_x)||isnan(w1_y)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
/*:276*//*280:*/
#line 7130 "weaver-interface-metafont.tex"

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
/*287:*/
#line 7338 "weaver-interface-metafont.tex"

if(atleast0)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&u_x,&u_y);
if(atleast1)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&v_x,&v_y);
/*:287*/
#line 7143 "weaver-interface-metafont.tex"

}
/*:280*//*288:*/
#line 7355 "weaver-interface-metafont.tex"

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
/*:288*/
#line 5871 "weaver-interface-metafont.tex"

/*261:*/
#line 6659 "weaver-interface-metafont.tex"

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
/*:261*/
#line 5872 "weaver-interface-metafont.tex"

begin_z1= begin_z2;
end_z1= end_z2;
}

}
/*:239*/
#line 5786 "weaver-interface-metafont.tex"

return true;
}
/*:236*//*251:*/
#line 6221 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y){
/*252:*/
#line 6238 "weaver-interface-metafont.tex"

if(begin==NULL||end==NULL){
return true;
}
/*:252*/
#line 6226 "weaver-interface-metafont.tex"

/*253:*/
#line 6251 "weaver-interface-metafont.tex"

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
/*:253*/
#line 6227 "weaver-interface-metafont.tex"

/*254:*/
#line 6289 "weaver-interface-metafont.tex"

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
/*:254*/
#line 6228 "weaver-interface-metafont.tex"

return false;
}
/*:251*//*278:*/
#line 7105 "weaver-interface-metafont.tex"

double compute_f(double theta,double phi){
double n= 2+sqrt(2)*(sin(theta)-0.0625*sin(phi))*
(sin(phi)-0.0625*sin(theta))*(cos(theta)-cos(phi));
double d= 3*(1+0.5*(sqrt(5.0)-1)*cos(theta)+0.5*(3-sqrt(5))*
cos(phi));
return n/d;
}
/*:278*//*282:*/
#line 7168 "weaver-interface-metafont.tex"

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
/*:282*//*284:*/
#line 7207 "weaver-interface-metafont.tex"

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
/*285:*/
#line 7250 "weaver-interface-metafont.tex"

bool s1,s2,s3;
s1= ((*control_x-p1_x)*(p0_y-p1_y)-
(p0_x-p1_x)*(*control_y-p1_y))<0;
s2= ((*control_x-p2_x)*(p1_y-p2_y)-
(p1_x-p2_x)*(*control_y-p2_y))<0;
s3= ((*control_x-p0_x)*(p2_y-p0_y)-
(p2_x-p0_x)*(*control_y-p0_y))<0;
if(s1==s2&&s2==s3)
return;
/*:285*/
#line 7233 "weaver-interface-metafont.tex"

/*286:*/
#line 7273 "weaver-interface-metafont.tex"

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
/*:286*/
#line 7234 "weaver-interface-metafont.tex"

}
}
/*:284*//*290:*/
#line 7413 "weaver-interface-metafont.tex"

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
/*:290*//*292:*/
#line 7503 "weaver-interface-metafont.tex"

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
/*293:*/
#line 7606 "weaver-interface-metafont.tex"

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
/*:293*/
#line 7553 "weaver-interface-metafont.tex"

/*296:*/
#line 7665 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,a.value);
return true;
}
/*:296*/
#line 7554 "weaver-interface-metafont.tex"

/*299:*/
#line 7716 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SHIFTED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_shift(result,a.x,a.y);
return true;
}
/*:299*/
#line 7555 "weaver-interface-metafont.tex"

/*302:*/
#line 7761 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SLANTED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_slant(result,a.value);
return true;
}
/*:302*/
#line 7556 "weaver-interface-metafont.tex"

/*305:*/
#line 7804 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_XSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,1.0);
return true;
}
/*:305*/
#line 7557 "weaver-interface-metafont.tex"

/*306:*/
#line 7821 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_YSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,1.0,a.value);
return true;
}
/*:306*/
#line 7558 "weaver-interface-metafont.tex"

/*307:*/
#line 7845 "weaver-interface-metafont.tex"

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
/*:307*/
#line 7559 "weaver-interface-metafont.tex"

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
/*:292*//*295:*/
#line 7635 "weaver-interface-metafont.tex"

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
/*:295*//*298:*/
#line 7691 "weaver-interface-metafont.tex"

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
/*:298*//*301:*/
#line 7737 "weaver-interface-metafont.tex"

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
/*:301*//*304:*/
#line 7782 "weaver-interface-metafont.tex"

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
/*:304*//*309:*/
#line 7872 "weaver-interface-metafont.tex"

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
/*:309*//*313:*/
#line 7953 "weaver-interface-metafont.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
if(begin_expression->type==TYPE_REVERSE){
/*315:*/
#line 8052 "weaver-interface-metafont.tex"

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
/*:315*/
#line 7959 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_SUBPATH){
/*318:*/
#line 8141 "weaver-interface-metafont.tex"

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
/*:318*/
#line 7962 "weaver-interface-metafont.tex"

}
else if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*323:*/
#line 8341 "weaver-interface-metafont.tex"

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
/*:323*/
#line 7966 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*324:*/
#line 8383 "weaver-interface-metafont.tex"

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
/*:324*/
#line 7970 "weaver-interface-metafont.tex"

}
/*361:*/
#line 9496 "weaver-interface-metafont.tex"

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
/*362:*/
#line 9532 "weaver-interface-metafont.tex"

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
/*:362*/
#line 9511 "weaver-interface-metafont.tex"

}
else if(tmp.flags&FLAG_CIRCULAR){
/*363:*/
#line 9554 "weaver-interface-metafont.tex"

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
/*:363*/
#line 9514 "weaver-interface-metafont.tex"

}
else if(tmp.flags&FLAG_SQUARE){
/*364:*/
#line 9603 "weaver-interface-metafont.tex"

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
/*:364*/
#line 9517 "weaver-interface-metafont.tex"

}
else{
/*365:*/
#line 9638 "weaver-interface-metafont.tex"

if(tmp.referenced==NULL)
recursive_copy_points(temporary_alloc,&result,tmp.format,false);
else
recursive_copy_points(temporary_alloc,&result,tmp.referenced->format,
false);
if(temporary_free!=NULL&&tmp.referenced==NULL)
temporary_free(tmp.format);
/*:365*/
#line 9520 "weaver-interface-metafont.tex"

}
/*366:*/
#line 9654 "weaver-interface-metafont.tex"

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
/*:366*/
#line 9522 "weaver-interface-metafont.tex"

return true;
}
/*:361*/
#line 7972 "weaver-interface-metafont.tex"

{
/*325:*/
#line 8414 "weaver-interface-metafont.tex"

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
/*:325*/
#line 7974 "weaver-interface-metafont.tex"

}
return false;
}
/*:313*//*314:*/
#line 8007 "weaver-interface-metafont.tex"

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
/*:314*//*317:*/
#line 8089 "weaver-interface-metafont.tex"

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
/*:317*//*320:*/
#line 8260 "weaver-interface-metafont.tex"

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
/*:320*//*322:*/
#line 8291 "weaver-interface-metafont.tex"

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
/*:322*//*330:*/
#line 8514 "weaver-interface-metafont.tex"

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
/*:330*//*332:*/
#line 8546 "weaver-interface-metafont.tex"

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
/*:332*//*336:*/
#line 8704 "weaver-interface-metafont.tex"

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
/*:336*//*338:*/
#line 8757 "weaver-interface-metafont.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result){
return eval_pen_secondary(mf,cx,begin_expression,end_token_list,result);
}
/*:338*//*340:*/
#line 8807 "weaver-interface-metafont.tex"

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
/*341:*/
#line 8890 "weaver-interface-metafont.tex"

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
/*:341*/
#line 8837 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*342:*/
#line 8930 "weaver-interface-metafont.tex"

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
/*:342*/
#line 8840 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*343:*/
#line 8974 "weaver-interface-metafont.tex"

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
/*:343*/
#line 8843 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*344:*/
#line 9007 "weaver-interface-metafont.tex"

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
/*:344*/
#line 8846 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*345:*/
#line 9047 "weaver-interface-metafont.tex"

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
/*:345*/
#line 8849 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*346:*/
#line 9084 "weaver-interface-metafont.tex"

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
/*:346*/
#line 8852 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*347:*/
#line 9129 "weaver-interface-metafont.tex"

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
/*:347*/
#line 8855 "weaver-interface-metafont.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:340*//*351:*/
#line 9201 "weaver-interface-metafont.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*352:*/
#line 9242 "weaver-interface-metafont.tex"

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
/*:352*/
#line 9208 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_NULLPEN){
/*353:*/
#line 9270 "weaver-interface-metafont.tex"

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
/*:353*/
#line 9211 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_PENCIRCLE){
/*354:*/
#line 9292 "weaver-interface-metafont.tex"

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
/*:354*/
#line 9214 "weaver-interface-metafont.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*355:*/
#line 9315 "weaver-interface-metafont.tex"

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
/*:355*/
#line 9220 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_MAKEPEN){
/*356:*/
#line 9339 "weaver-interface-metafont.tex"

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
/*:356*/
#line 9223 "weaver-interface-metafont.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:351*//*358:*/
#line 9391 "weaver-interface-metafont.tex"

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
/*:358*//*374:*/
#line 9841 "weaver-interface-metafont.tex"

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
/*:374*//*378:*/
#line 9922 "weaver-interface-metafont.tex"

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
/*:378*//*380:*/
#line 9964 "weaver-interface-metafont.tex"

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
/*:380*//*382:*/
#line 10027 "weaver-interface-metafont.tex"

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
/*:382*//*384:*/
#line 10087 "weaver-interface-metafont.tex"

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
/*389:*/
#line 10315 "weaver-interface-metafont.tex"

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
/*:389*/
#line 10109 "weaver-interface-metafont.tex"

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
/*389:*/
#line 10315 "weaver-interface-metafont.tex"

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
/*:389*/
#line 10125 "weaver-interface-metafont.tex"

/*388:*/
#line 10222 "weaver-interface-metafont.tex"


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
/*:388*/
#line 10126 "weaver-interface-metafont.tex"

if(a.texture!=0)
glDeleteTextures(1,&(a.texture));
if(b.texture!=0)
glDeleteTextures(1,&(b.texture));
return true;
}
}
/*:384*//*391:*/
#line 10367 "weaver-interface-metafont.tex"

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
/*393:*/
#line 10479 "weaver-interface-metafont.tex"

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
/*:393*/
#line 10399 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*392:*/
#line 10445 "weaver-interface-metafont.tex"

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
/*:392*/
#line 10402 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*394:*/
#line 10514 "weaver-interface-metafont.tex"

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
/*:394*/
#line 10405 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*395:*/
#line 10546 "weaver-interface-metafont.tex"

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
/*:395*/
#line 10408 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*396:*/
#line 10571 "weaver-interface-metafont.tex"

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
/*:396*/
#line 10411 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*397:*/
#line 10596 "weaver-interface-metafont.tex"

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
/*:397*/
#line 10414 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*398:*/
#line 10622 "weaver-interface-metafont.tex"

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
/*:398*/
#line 10417 "weaver-interface-metafont.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:391*//*400:*/
#line 10684 "weaver-interface-metafont.tex"

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
/*:400*//*404:*/
#line 10793 "weaver-interface-metafont.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*405:*/
#line 10832 "weaver-interface-metafont.tex"

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
/*:405*/
#line 10800 "weaver-interface-metafont.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*406:*/
#line 10875 "weaver-interface-metafont.tex"

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
/*:406*/
#line 10806 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_NULLPICTURE){
/*407:*/
#line 10900 "weaver-interface-metafont.tex"

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
/*:407*/
#line 10809 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_SUM){
/*408:*/
#line 10952 "weaver-interface-metafont.tex"

struct generic_token*p= begin_expression->next;
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing image expression "
"after '+'.\n",mf->file,begin_expression->line);
#endif
return false;
}
return eval_picture_primary(mf,cx,p,end_expression,result);
/*:408*/
#line 10812 "weaver-interface-metafont.tex"

}
else if(begin_expression->type==TYPE_SUBTRACT){
/*409:*/
#line 10974 "weaver-interface-metafont.tex"

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
/*:409*/
#line 10815 "weaver-interface-metafont.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:404*/
#line 234 "weaver-interface-metafont.tex"

/*9:*/
#line 263 "weaver-interface-metafont.tex"

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
/*369:*/
#line 9768 "weaver-interface-metafont.tex"

glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);

glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
/*:369*//*375:*/
#line 9891 "weaver-interface-metafont.tex"

{
program= compile_shader_program(vertex_shader,fragment_shader);
uniform_matrix= glGetUniformLocation(program,"model_view_matrix");
uniform_texture= glGetUniformLocation(program,"texture1");
}
/*:375*//*386:*/
#line 10200 "weaver-interface-metafont.tex"

{
inv_program= compile_shader_program(vertex_shader,fragment_shader_inverse);
uniform_inv_matrix= glGetUniformLocation(inv_program,"model_view_matrix");
uniform_inv_texture= glGetUniformLocation(inv_program,"texture1");
}
/*:386*/
#line 275 "weaver-interface-metafont.tex"

return true;
}
/*:9*//*10:*/
#line 286 "weaver-interface-metafont.tex"

void _Wfinish_metafont(void){
/*370:*/
#line 9779 "weaver-interface-metafont.tex"

glDeleteBuffers(1,&vbo);
/*:370*//*376:*/
#line 9903 "weaver-interface-metafont.tex"

glDeleteProgram(program);
/*:376*//*387:*/
#line 10212 "weaver-interface-metafont.tex"

glDeleteProgram(inv_program);
/*:387*/
#line 288 "weaver-interface-metafont.tex"

}
/*:10*/
#line 235 "weaver-interface-metafont.tex"

/*:7*/
