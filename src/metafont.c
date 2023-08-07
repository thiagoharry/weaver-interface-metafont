/*7:*/
#line 213 "weaver-interface-metafont_en.tex"

#include "metafont.h"
/*28:*/
#line 705 "weaver-interface-metafont_en.tex"

#include <stdio.h> 
/*:28*//*30:*/
#line 728 "weaver-interface-metafont_en.tex"

#include <ctype.h> 
/*:30*//*50:*/
#line 1159 "weaver-interface-metafont_en.tex"

#include <string.h> 
/*:50*//*98:*/
#line 2230 "weaver-interface-metafont_en.tex"

#include <math.h> 
/*:98*//*297:*/
#line 7291 "weaver-interface-metafont_en.tex"

#include <complex.h> 
/*:297*/
#line 215 "weaver-interface-metafont_en.tex"

/*8:*/
#line 253 "weaver-interface-metafont_en.tex"

#define INITIALIZE_IDENTITY_MATRIX(I) {\
  int _i;\
  for(_i =  0; _i < 9; _i++)\
    I[_i] =  ((_i%4)?(0.0):(1.0));\
}
/*:8*//*9:*/
#line 281 "weaver-interface-metafont_en.tex"

#define LINEAR_TRANSFORM_X(x, y, M) (x * M[0] + y * M[3] + M[6])
#define LINEAR_TRANSFORM_Y(x, y, M) (x * M[1] + y * M[4] + M[7])
/*:9*//*10:*/
#line 301 "weaver-interface-metafont_en.tex"

#define MATRIX_MULTIPLICATION(A, B) {\
  float _a0 =  A[0], _a1 =  A[1], _a3 =  A[3], _a4 =  A[4], _a6 =  A[6],\
        _a7 =  A[7];\
  A[0] =  _a0 * B[0] + _a1 * B[3];\
  A[1] =  _a0 * B[1] + _a1 * B[4];\
  A[3] =  _a3 * B[0] + _a4 * B[3];\
  A[4] =  _a3 * B[1] + _a4 * B[4];\
  A[6] =  _a6 * B[0] + _a7 * B[3] + B[6];\
  A[7] =  _a6 * B[1] + _a7 * B[4] + B[7];\
}
/*:10*//*11:*/
#line 330 "weaver-interface-metafont_en.tex"

#define TRANSFORM_ROTATE(M, theta) {\
  float _m0 =  M[0], _m1 =  M[1], _m3 =  M[3], _m4 =  M[4], _m6 =  M[6],\
        _m7 =  M[7];\
  double _cos_theta, _sin_theta;\
  _sin_theta =  sin(theta);\
  _cos_theta =  cos(theta);\
  M[0] =  _m0 * _cos_theta - _m1 * _sin_theta;\
  M[1] =  _m0 * _sin_theta + _m1 * _cos_theta;\
  M[3] =  _m3 * _cos_theta - _m4 * _sin_theta;\
  M[4] =  _m3 * _sin_theta + _m4 * _cos_theta;\
  M[6] =  _m6 * _cos_theta - _m7 * _sin_theta;\
  M[7] =  _m6 * _sin_theta + _m7 * _cos_theta;\
}
/*:11*//*12:*/
#line 359 "weaver-interface-metafont_en.tex"

#define TRANSFORM_SCALE_X(M, s) {\
  M[0] =  M[0] * s;\
  M[3] =  M[3] * s;\
  M[6] =  M[6] * s;\
}
/*:12*//*13:*/
#line 378 "weaver-interface-metafont_en.tex"

#define TRANSFORM_SCALE_Y(M, s) {\
  M[1] =  M[1] * s;\
  M[4] =  M[4] * s;\
  M[7] =  M[7] * s;\
}
/*:13*//*14:*/
#line 391 "weaver-interface-metafont_en.tex"

#define TRANSFORM_SCALE(M, s) {\
  TRANSFORM_SCALE_X(M, s);\
  TRANSFORM_SCALE_Y(M, s);\
}
/*:14*//*15:*/
#line 412 "weaver-interface-metafont_en.tex"

#define TRANSFORM_SHIFT(M, a, b) {\
  M[6] =  M[6] + a;\
  M[7] =  M[7] + b;\
}
/*:15*//*16:*/
#line 430 "weaver-interface-metafont_en.tex"

#define TRANSFORM_SLANT(M, s) {\
  M[0] =  M[0] + s * M[1];\
  M[3] =  M[3] + s * M[4];\
  M[6] =  M[6] + s * M[7];\
}
/*:16*//*17:*/
#line 453 "weaver-interface-metafont_en.tex"

#define TRANSFORM_SCALE_Z(M, s, t) {\
  float _m0 =  M[0], _m1 =  M[1], _m3 =  M[3], _m4 =  M[4], _m6 =  M[6],\
        _m7 =  M[7];\
  M[0] =  _m0 * s - _m1 * t;\
  M[1] =  _m0 * t + _m1 * s;\
  M[3] =  _m3 * s - _m4 * t;\
  M[4] =  _m3 * t + _m4 * s;\
  M[6] =  _m6 * s - _m7 * t;\
  M[7] =  _m6 * t + _m7 * s;\
}
/*:17*//*101:*/
#line 2288 "weaver-interface-metafont_en.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
/*:101*//*110:*/
#line 2438 "weaver-interface-metafont_en.tex"

#define INTERNAL_TRANSFORM_IDENTITY 0
/*:110*//*119:*/
#line 2652 "weaver-interface-metafont_en.tex"

#define FLAG_CONVEX   1
#define FLAG_STRAIGHT 2
#define FLAG_CIRCULAR 4
#define FLAG_SQUARE   8
#define FLAG_NULL    16
/*:119*//*125:*/
#line 2817 "weaver-interface-metafont_en.tex"

#define INTERNAL_PEN_CURRENTPEN 0
#define INTERNAL_PEN_PENSQUARE  1
/*:125*//*135:*/
#line 2966 "weaver-interface-metafont_en.tex"

#define INTERNAL_PICTURE_CURRENTPICTURE 0
/*:135*//*150:*/
#line 3296 "weaver-interface-metafont_en.tex"

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
/*:150*//*151:*/
#line 3344 "weaver-interface-metafont_en.tex"

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
/*:151*//*469:*/
#line 12484 "weaver-interface-metafont_en.tex"

#define DECLARE_PEN_EXTREMITIES() float _max_x =  -INFINITY, _min_x =  INFINITY,\
                                  _max_y =  -INFINITY, _min_y =  INFINITY;
/*:469*//*470:*/
#line 12495 "weaver-interface-metafont_en.tex"

#define CHECK_PEN_EXTREMITIES(x, y, matrix) {\
   float _x, _y;\
   _x =  LINEAR_TRANSFORM_X(x, y, matrix);\
   _y =  LINEAR_TRANSFORM_Y(x, y, matrix);\
   if(_x < _min_x) _min_x =  _x;\
   if(_x >  _max_x) _max_x =  _x;\
   if(_y < _min_y) _min_y =  _y;\
   if(_y >  _max_y) _max_y =  _y;\
  }

#define CHECK_PEN_EXTREMITIES_I(x, y) {\
   if(x < _min_x) _min_x =  x;\
   if(x >  _max_x) _max_x =  x;\
   if(y < _min_y) _min_y =  y;\
   if(y >  _max_y) _max_y =  y;\
  }

/*:470*//*471:*/
#line 12520 "weaver-interface-metafont_en.tex"

#define UPDATE_PEN_EXTREMITIES() {\
  mf -> pen_lft =  _min_x;\
  mf -> pen_rt =  _max_x;\
  mf -> pen_top =  _max_y;\
  mf -> pen_bot =  _min_y;\
}
/*:471*//*476:*/
#line 12830 "weaver-interface-metafont_en.tex"

#define FLAG_ORIENTATION      32
#define FLAG_COUNTERCLOCKWISE 64
/*:476*/
#line 216 "weaver-interface-metafont_en.tex"

/*21:*/
#line 539 "weaver-interface-metafont_en.tex"

enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,


/*25:*/
#line 624 "weaver-interface-metafont_en.tex"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:25*//*52:*/
#line 1229 "weaver-interface-metafont_en.tex"

TYPE_END,
TYPE_DUMP,
/*:52*//*64:*/
#line 1508 "weaver-interface-metafont_en.tex"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:64*//*77:*/
#line 1784 "weaver-interface-metafont_en.tex"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:77*//*140:*/
#line 3050 "weaver-interface-metafont_en.tex"

TYPE_ASSIGNMENT,
TYPE_ASSIGNMENT2,
/*:140*//*147:*/
#line 3255 "weaver-interface-metafont_en.tex"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:147*//*154:*/
#line 3471 "weaver-interface-metafont_en.tex"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:154*//*158:*/
#line 3594 "weaver-interface-metafont_en.tex"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:158*//*174:*/
#line 3970 "weaver-interface-metafont_en.tex"

TYPE_NORMALDEVIATE,
/*:174*//*190:*/
#line 4340 "weaver-interface-metafont_en.tex"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:190*//*210:*/
#line 4990 "weaver-interface-metafont_en.tex"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:210*//*217:*/
#line 5162 "weaver-interface-metafont_en.tex"

TYPE_TRANSFORMED,
/*:217*//*236:*/
#line 5611 "weaver-interface-metafont_en.tex"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:236*//*249:*/
#line 5878 "weaver-interface-metafont_en.tex"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,
TYPE_STRAIGHT_JOIN,
/*:249*//*331:*/
#line 8128 "weaver-interface-metafont_en.tex"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:331*//*348:*/
#line 8692 "weaver-interface-metafont_en.tex"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:348*//*370:*/
#line 9246 "weaver-interface-metafont_en.tex"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_MAKEPEN,
/*:370*//*381:*/
#line 9532 "weaver-interface-metafont_en.tex"

TYPE_MAKEPATH,
/*:381*//*424:*/
#line 10719 "weaver-interface-metafont_en.tex"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:424*//*436:*/
#line 11128 "weaver-interface-metafont_en.tex"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:436*//*442:*/
#line 11319 "weaver-interface-metafont_en.tex"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:442*//*446:*/
#line 11575 "weaver-interface-metafont_en.tex"

TYPE_OR,
/*:446*//*452:*/
#line 11734 "weaver-interface-metafont_en.tex"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:452*//*460:*/
#line 12179 "weaver-interface-metafont_en.tex"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:460*//*465:*/
#line 12426 "weaver-interface-metafont_en.tex"

TYPE_PICKUP,
/*:465*//*493:*/
#line 13601 "weaver-interface-metafont_en.tex"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:493*//*499:*/
#line 13715 "weaver-interface-metafont_en.tex"

TYPE_DRAW,
TYPE_ERASE,
/*:499*/
#line 544 "weaver-interface-metafont_en.tex"


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
/*:21*//*22:*/
#line 562 "weaver-interface-metafont_en.tex"

struct string_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
char value[5];
};
/*:22*//*23:*/
#line 587 "weaver-interface-metafont_en.tex"

struct symbolic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
void*var;
char*value;
};
/*:23*//*24:*/
#line 610 "weaver-interface-metafont_en.tex"

struct generic_token{
int type;
void*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:24*//*79:*/
#line 1823 "weaver-interface-metafont_en.tex"


struct variable{
int type;
int nesting_level;
void*next;
};
/*:79*//*80:*/
#line 1845 "weaver-interface-metafont_en.tex"

struct named_variable{
char*name;
void*next;
struct variable*var;
};
/*:80*//*96:*/
#line 2203 "weaver-interface-metafont_en.tex"

struct numeric_variable{
int type;
int nesting_level;
void*next;
float value;
};
/*:96*//*104:*/
#line 2336 "weaver-interface-metafont_en.tex"

struct pair_variable{
int type;
int nesting_level;
void*next;
float x,y;
};
/*:104*//*106:*/
#line 2381 "weaver-interface-metafont_en.tex"

struct transform_variable{
int type;
int nesting_level;
void*next;
float value[9];
};
/*:106*//*112:*/
#line 2493 "weaver-interface-metafont_en.tex"

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
/*:112*//*118:*/
#line 2609 "weaver-interface-metafont_en.tex"

struct pen_variable{
int type;
int nesting_level;
void*next;
struct path_variable*format;
int flags;
struct pen_variable*referenced;
float gl_matrix[9];

GLuint gl_vbo;
GLsizei indices;


float triang_resolution;
};
/*:118*//*129:*/
#line 2882 "weaver-interface-metafont_en.tex"

struct picture_variable{
int type;
int nesting_level;
void*next;
int width,height;
GLuint texture;
};
/*:129*//*138:*/
#line 3001 "weaver-interface-metafont_en.tex"

struct boolean_variable{
int type;
int nesting_level;
void*next;
short value;
};
/*:138*/
#line 217 "weaver-interface-metafont_en.tex"

/*18:*/
#line 476 "weaver-interface-metafont_en.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int pt;
/*:18*//*48:*/
#line 1112 "weaver-interface-metafont_en.tex"

static char*list_of_keywords[]= {
/*53:*/
#line 1239 "weaver-interface-metafont_en.tex"

"end","dump",
/*:53*//*65:*/
#line 1521 "weaver-interface-metafont_en.tex"

"begingroup","endgroup","if","fi","beginchar","endchar",
/*:65*//*78:*/
#line 1798 "weaver-interface-metafont_en.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:78*//*141:*/
#line 3059 "weaver-interface-metafont_en.tex"

"=",":=",
/*:141*//*148:*/
#line 3270 "weaver-interface-metafont_en.tex"

"+","-","++","+-+","[","]","{","}",
/*:148*//*155:*/
#line 3478 "weaver-interface-metafont_en.tex"

"*","/",
/*:155*//*159:*/
#line 3607 "weaver-interface-metafont_en.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:159*//*175:*/
#line 3976 "weaver-interface-metafont_en.tex"

"normaldeviate",
/*:175*//*191:*/
#line 4352 "weaver-interface-metafont_en.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:191*//*211:*/
#line 5000 "weaver-interface-metafont_en.tex"

"xpart","ypart","angle",
/*:211*//*218:*/
#line 5170 "weaver-interface-metafont_en.tex"

"transformed",
/*:218*//*237:*/
#line 5622 "weaver-interface-metafont_en.tex"

"xxpart","xypart","yxpart","yypart",
/*:237*//*250:*/
#line 5894 "weaver-interface-metafont_en.tex"

"cycle","&","..","tension","and","atleast","controls","curl","--",
/*:250*//*332:*/
#line 8139 "weaver-interface-metafont_en.tex"

"reverse","subpath","of",
/*:332*//*349:*/
#line 8702 "weaver-interface-metafont_en.tex"

"point","precontrol","postcontrol",
/*:349*//*371:*/
#line 9256 "weaver-interface-metafont_en.tex"

"nullpen","pencircle","makepen",
/*:371*//*382:*/
#line 9541 "weaver-interface-metafont_en.tex"

"makepath",
/*:382*//*425:*/
#line 10729 "weaver-interface-metafont_en.tex"

"nullpicture","subpicture",
/*:425*//*437:*/
#line 11138 "weaver-interface-metafont_en.tex"

"totalweight","width","height",
/*:437*//*443:*/
#line 11331 "weaver-interface-metafont_en.tex"

"<","<=",">",">=","<>",
/*:443*//*447:*/
#line 11583 "weaver-interface-metafont_en.tex"

"or",
/*:447*//*453:*/
#line 11745 "weaver-interface-metafont_en.tex"

"true","false","odd","not",
/*:453*//*461:*/
#line 12189 "weaver-interface-metafont_en.tex"

"elseif","else",":",
/*:461*//*466:*/
#line 12432 "weaver-interface-metafont_en.tex"

"pickup",
/*:466*//*494:*/
#line 13613 "weaver-interface-metafont_en.tex"

"bot","top","lft","rt",
/*:494*//*500:*/
#line 13722 "weaver-interface-metafont_en.tex"

"draw","erase",
/*:500*/
#line 1114 "weaver-interface-metafont_en.tex"

NULL};
/*:48*//*390:*/
#line 9785 "weaver-interface-metafont_en.tex"

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
/*:390*//*393:*/
#line 9839 "weaver-interface-metafont_en.tex"

static const char vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat3 model_view_matrix;\n"
"varying mediump vec2 texture_coordinate;\n"
"void main(){\n"
"  highp vec3 coord;\n"
"  coord = vec3(vertex_data.xy, 1.0) * model_view_matrix;\n"
"  gl_Position = vec4(coord.x, coord.y, 0.0, 1.0);\n"
"  texture_coordinate = vertex_data.zw;\n"
"}\n";
/*:393*//*394:*/
#line 9858 "weaver-interface-metafont_en.tex"

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
/*:394*//*407:*/
#line 10232 "weaver-interface-metafont_en.tex"

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
/*:407*//*482:*/
#line 12947 "weaver-interface-metafont_en.tex"

static GLuint pensquare_vbo;
/*:482*//*501:*/
#line 13740 "weaver-interface-metafont_en.tex"

static GLuint currentpicture_fb;
/*:501*//*505:*/
#line 13816 "weaver-interface-metafont_en.tex"

static GLint previous_fb;
/*:505*//*508:*/
#line 13850 "weaver-interface-metafont_en.tex"

static const char pen_vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat3 model_view_matrix;\n"
"void main(){\n"
"  highp vec3 coord;\n"
"  coord = vec3(vertex_data.xy, 1.0) * model_view_matrix;\n"
"  gl_Position = vec4(coord.x, coord.y, 0.0, 1.0);\n"
"}\n";
/*:508*//*509:*/
#line 13868 "weaver-interface-metafont_en.tex"

static const char pen_erase_fragment_shader[]= 
"#version 100\n"
"precision mediump float;\n"
"uniform vec4 color;\n"
"void main(){\n"
"  gl_FragColor = vec4(1.0 - color.r, 1.0 - color.g, 1.0 - color.b, \n"
"                      color.a);\n"
"}\n";
static const char pen_fragment_shader[]= 
"#version 100\n"
"precision mediump float;\n"
"uniform vec4 color;\n"
"void main(){\n"
"  gl_FragColor = color;"
"}\n";
static GLuint pen_program,pen_erase_program;
static GLint pen_uniform_matrix,pen_erase_uniform_matrix;
static GLint pen_uniform_color,pen_erase_uniform_color;
/*:509*/
#line 218 "weaver-interface-metafont_en.tex"

/*58:*/
#line 1314 "weaver-interface-metafont_en.tex"

struct metafont*init_metafont(void*(*alloc)(size_t),
void(*disalloc)(void*),
char*filename);
struct context*init_context(void);
void destroy_metafont(struct metafont*mf);
void destroy_context(struct metafont*mf,struct context*cx);
/*:58*//*62:*/
#line 1417 "weaver-interface-metafont_en.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list);
/*:62*//*66:*/
#line 1530 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*,struct context*,void*,void**);
/*:66*//*71:*/
#line 1609 "weaver-interface-metafont_en.tex"

bool begin_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
/*:71*//*90:*/
#line 2032 "weaver-interface-metafont_en.tex"

struct variable*insert_variable(int nesting_level,
void*(*alloc)(size_t),
int type,
struct symbolic_token*variable,
void**target);
/*:90*//*92:*/
#line 2101 "weaver-interface-metafont_en.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:92*//*94:*/
#line 2162 "weaver-interface-metafont_en.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:94*//*116:*/
#line 2573 "weaver-interface-metafont_en.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer);
/*:116*//*145:*/
#line 3194 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source);
/*:145*//*149:*/
#line 3279 "weaver-interface-metafont_en.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:149*//*156:*/
#line 3486 "weaver-interface-metafont_en.tex"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:156*//*160:*/
#line 3615 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:160*//*176:*/
#line 3987 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result);
/*:176*//*186:*/
#line 4224 "weaver-interface-metafont_en.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source);
/*:186*//*188:*/
#line 4262 "weaver-interface-metafont_en.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pair_variable*result);
/*:188*//*192:*/
#line 4363 "weaver-interface-metafont_en.tex"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:192*//*203:*/
#line 4690 "weaver-interface-metafont_en.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result);
/*:203*//*219:*/
#line 5184 "weaver-interface-metafont_en.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:219*//*221:*/
#line 5209 "weaver-interface-metafont_en.tex"

bool eval_transform_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:221*//*231:*/
#line 5450 "weaver-interface-metafont_en.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result);
/*:231*//*243:*/
#line 5748 "weaver-interface-metafont_en.tex"

void assign_path_variable(struct metafont*mf,
struct path_variable*target,
struct path_variable*source);
/*:243*//*245:*/
#line 5785 "weaver-interface-metafont_en.tex"

void recursive_copy_points(void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target);
/*:245*//*247:*/
#line 5823 "weaver-interface-metafont_en.tex"

void recursive_aux_copy(struct path_points**dst,struct path_variable*origin);
/*:247*//*251:*/
#line 5904 "weaver-interface-metafont_en.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:251*//*253:*/
#line 5946 "weaver-interface-metafont_en.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:253*//*268:*/
#line 6389 "weaver-interface-metafont_en.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y);
/*:268*//*295:*/
#line 7269 "weaver-interface-metafont_en.tex"

double compute_f(double theta,double phi);
/*:295*//*299:*/
#line 7325 "weaver-interface-metafont_en.tex"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y);
/*:299*//*301:*/
#line 7359 "weaver-interface-metafont_en.tex"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y);
/*:301*//*307:*/
#line 7557 "weaver-interface-metafont_en.tex"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:307*//*309:*/
#line 7650 "weaver-interface-metafont_en.tex"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:309*//*312:*/
#line 7784 "weaver-interface-metafont_en.tex"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta);
/*:312*//*315:*/
#line 7837 "weaver-interface-metafont_en.tex"

void path_xyscale(struct path_variable*p,float x,float y);
/*:315*//*318:*/
#line 7889 "weaver-interface-metafont_en.tex"

void path_shift(struct path_variable*p,float x,float y);
/*:318*//*321:*/
#line 7935 "weaver-interface-metafont_en.tex"

void path_slant(struct path_variable*p,float s);
/*:321*//*326:*/
#line 8019 "weaver-interface-metafont_en.tex"

void path_zscale(struct path_variable*p,float x,float y);
/*:326*//*329:*/
#line 8077 "weaver-interface-metafont_en.tex"

void path_transform(struct path_variable*p,float*M);
/*:329*//*333:*/
#line 8153 "weaver-interface-metafont_en.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result);
/*:333*//*337:*/
#line 8291 "weaver-interface-metafont_en.tex"

void reverse_path(struct path_variable*src,struct path_variable*dst);
/*:337*//*340:*/
#line 8462 "weaver-interface-metafont_en.tex"

void copy_subpath(struct path_points*dst,struct path_variable*src,int offset,int size);
/*:340*//*342:*/
#line 8492 "weaver-interface-metafont_en.tex"

int recursive_copy_subpath(struct path_points**dst,
struct path_variable*pointer,
int*index,int*offset,int*size);
/*:342*//*350:*/
#line 8718 "weaver-interface-metafont_en.tex"

struct path_points*get_point(struct path_variable*v,int n);
/*:350*//*352:*/
#line 8747 "weaver-interface-metafont_en.tex"

struct path_points*_get_point(struct path_variable*v,int n,int*count);
/*:352*//*356:*/
#line 8903 "weaver-interface-metafont_en.tex"

void assign_pen_variable(struct metafont*mf,
struct pen_variable*target,
struct pen_variable*source);
/*:356*//*358:*/
#line 8959 "weaver-interface-metafont_en.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:358*//*360:*/
#line 9003 "weaver-interface-metafont_en.tex"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result);
/*:360*//*372:*/
#line 9264 "weaver-interface-metafont_en.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result);
/*:372*//*379:*/
#line 9440 "weaver-interface-metafont_en.tex"

int read_flags(struct path_variable*path);
/*:379*//*395:*/
#line 9878 "weaver-interface-metafont_en.tex"

GLuint compile_shader_program(const char*vertex_shader_source,
const char*fragment_shader_source);
/*:395*//*399:*/
#line 9966 "weaver-interface-metafont_en.tex"

bool get_new_framebuffer(GLuint*new_framebuffer,GLuint*new_texture,
int width,int height);
/*:399*//*401:*/
#line 10006 "weaver-interface-metafont_en.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height,bool clear_background);

void print_picture(struct picture_variable*pic);
/*:401*//*403:*/
#line 10067 "weaver-interface-metafont_en.tex"

void assign_picture_variable(struct metafont*mf,
struct picture_variable*target,
struct picture_variable*source);
/*:403*//*405:*/
#line 10126 "weaver-interface-metafont_en.tex"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result);
/*:405*//*412:*/
#line 10394 "weaver-interface-metafont_en.tex"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct picture_variable*result,
float*matrix,bool*modified);
/*:412*//*422:*/
#line 10601 "weaver-interface-metafont_en.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*org,
float*matrix);
/*:422*//*426:*/
#line 10737 "weaver-interface-metafont_en.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result);
/*:426*//*444:*/
#line 11340 "weaver-interface-metafont_en.tex"

bool eval_boolean_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct boolean_variable*result);
/*:444*//*448:*/
#line 11592 "weaver-interface-metafont_en.tex"

bool eval_boolean_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result);
/*:448*//*450:*/
#line 11660 "weaver-interface-metafont_en.tex"

bool eval_boolean_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result);
/*:450*//*454:*/
#line 11753 "weaver-interface-metafont_en.tex"

bool eval_boolean_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct boolean_variable*result);
/*:454*//*456:*/
#line 11882 "weaver-interface-metafont_en.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_secondary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_tertiary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:456*//*472:*/
#line 12541 "weaver-interface-metafont_en.tex"

void pencircle_extremity_points(struct metafont*mf,float*matrix);
/*:472*//*474:*/
#line 12711 "weaver-interface-metafont_en.tex"

void path_extremity_points(struct metafont*mf,struct path_variable*p,
float*matrix);
/*:474*//*477:*/
#line 12844 "weaver-interface-metafont_en.tex"

bool is_pen_counterclockwise(struct pen_variable*pen);
/*:477*//*479:*/
#line 12901 "weaver-interface-metafont_en.tex"

bool triangulate_pen(struct metafont*mf,struct pen_variable*pen,
float*transform_matrix);
/*:479*//*513:*/
#line 14025 "weaver-interface-metafont_en.tex"

void drawpoint(struct metafont*mf,struct pen_variable*pen,
struct picture_variable*pic,float x,float y,float*matrix,
bool erasing);
/*:513*/
#line 219 "weaver-interface-metafont_en.tex"

/*26:*/
#line 643 "weaver-interface-metafont_en.tex"

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
/*:26*//*27:*/
#line 665 "weaver-interface-metafont_en.tex"

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
/*29:*/
#line 718 "weaver-interface-metafont_en.tex"

if(c==' '||(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:29*/
#line 682 "weaver-interface-metafont_en.tex"

/*31:*/
#line 739 "weaver-interface-metafont_en.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:31*/
#line 683 "weaver-interface-metafont_en.tex"

/*32:*/
#line 756 "weaver-interface-metafont_en.tex"

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
/*:32*/
#line 684 "weaver-interface-metafont_en.tex"

/*33:*/
#line 803 "weaver-interface-metafont_en.tex"

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
/*:33*/
#line 685 "weaver-interface-metafont_en.tex"

/*34:*/
#line 848 "weaver-interface-metafont_en.tex"

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
/*:34*/
#line 686 "weaver-interface-metafont_en.tex"

/*35:*/
#line 883 "weaver-interface-metafont_en.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*36:*/
#line 914 "weaver-interface-metafont_en.tex"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_'||isdigit(c));
ungetc(c,fp);
buffer[i]= '\0';
}
/*:36*/
#line 889 "weaver-interface-metafont_en.tex"

/*37:*/
#line 931 "weaver-interface-metafont_en.tex"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:37*/
#line 890 "weaver-interface-metafont_en.tex"

/*38:*/
#line 947 "weaver-interface-metafont_en.tex"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:38*/
#line 891 "weaver-interface-metafont_en.tex"

/*39:*/
#line 963 "weaver-interface-metafont_en.tex"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:39*/
#line 892 "weaver-interface-metafont_en.tex"

/*40:*/
#line 979 "weaver-interface-metafont_en.tex"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:40*/
#line 893 "weaver-interface-metafont_en.tex"

/*41:*/
#line 995 "weaver-interface-metafont_en.tex"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:41*/
#line 894 "weaver-interface-metafont_en.tex"

/*42:*/
#line 1011 "weaver-interface-metafont_en.tex"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:42*/
#line 895 "weaver-interface-metafont_en.tex"

/*43:*/
#line 1027 "weaver-interface-metafont_en.tex"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:43*/
#line 896 "weaver-interface-metafont_en.tex"

/*44:*/
#line 1043 "weaver-interface-metafont_en.tex"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:44*/
#line 897 "weaver-interface-metafont_en.tex"

/*45:*/
#line 1059 "weaver-interface-metafont_en.tex"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:45*/
#line 898 "weaver-interface-metafont_en.tex"

/*46:*/
#line 1075 "weaver-interface-metafont_en.tex"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:46*/
#line 899 "weaver-interface-metafont_en.tex"

/*47:*/
#line 1091 "weaver-interface-metafont_en.tex"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:47*/
#line 900 "weaver-interface-metafont_en.tex"


/*49:*/
#line 1125 "weaver-interface-metafont_en.tex"

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
/*54:*/
#line 1248 "weaver-interface-metafont_en.tex"

if(token_type==TYPE_DUMP)
token_type= TYPE_END;
/*:54*//*142:*/
#line 3068 "weaver-interface-metafont_en.tex"

else if(token_type==TYPE_ASSIGNMENT2)
token_type= TYPE_ASSIGNMENT;
/*:142*/
#line 1138 "weaver-interface-metafont_en.tex"

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
/*:49*/
#line 902 "weaver-interface-metafont_en.tex"

/*51:*/
#line 1169 "weaver-interface-metafont_en.tex"

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
/*103:*/
#line 2311 "weaver-interface-metafont_en.tex"

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
/*:103*//*111:*/
#line 2447 "weaver-interface-metafont_en.tex"

else if(!strcmp(buffer,"identity"))
new_token->var= 
&(mf->internal_transform_variables[INTERNAL_TRANSFORM_IDENTITY]);
/*:111*//*127:*/
#line 2843 "weaver-interface-metafont_en.tex"

else if(!strcmp(buffer,"currentpen"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN]);
else if(!strcmp(buffer,"pensquare"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_PENSQUARE]);
/*:127*//*137:*/
#line 2988 "weaver-interface-metafont_en.tex"

else if(!strcmp(buffer,"currentpicture"))
new_token->var= 
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE]);
/*:137*/
#line 1182 "weaver-interface-metafont_en.tex"

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
/*:51*/
#line 903 "weaver-interface-metafont_en.tex"

}
/*:35*/
#line 687 "weaver-interface-metafont_en.tex"


fprintf(stderr,"ERROR: %s:%d: Unknown character: '%c'\n",
path,line,c);
free_token_list(dealloc,first_token);
return NULL;
}
fclose(fp);
return first_token;
}
/*:27*//*55:*/
#line 1262 "weaver-interface-metafont_en.tex"

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
/*:55*//*59:*/
#line 1330 "weaver-interface-metafont_en.tex"

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
/*82:*/
#line 1867 "weaver-interface-metafont_en.tex"

mf->named_variables= NULL;
mf->global_variables= NULL;
/*:82*//*100:*/
#line 2260 "weaver-interface-metafont_en.tex"

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
/*:100*//*109:*/
#line 2419 "weaver-interface-metafont_en.tex"

mf->internal_transform_variables= 
(struct transform_variable*)
mf->alloc(sizeof(struct transform_variable));
if(mf->internal_transform_variables==NULL){
if(disalloc!=NULL)
disalloc(mf);
return NULL;
}

mf->internal_transform_variables[0].type= TYPE_T_TRANSFORM;
INITIALIZE_IDENTITY_MATRIX(mf->internal_transform_variables[0].value);
/*:109*//*124:*/
#line 2784 "weaver-interface-metafont_en.tex"

mf->internal_pen_variables= (struct pen_variable*)
mf->alloc(2*sizeof(struct pen_variable));
if(mf->internal_pen_variables==NULL){
if(disalloc!=NULL)
disalloc(mf);
return NULL;
}
mf->internal_pen_variables[0].format= NULL;
mf->internal_pen_variables[0].type= TYPE_T_PEN;
mf->internal_pen_variables[0].flags= FLAG_NULL;
mf->internal_pen_variables[0].referenced= NULL;
mf->internal_pen_variables[0].gl_vbo= 0;
mf->internal_pen_variables[0].indices= 0;
mf->internal_pen_variables[1].format= NULL;
mf->internal_pen_variables[1].type= TYPE_T_PEN;
mf->internal_pen_variables[1].flags= FLAG_CONVEX|FLAG_STRAIGHT|
FLAG_SQUARE;
mf->internal_pen_variables[1].referenced= NULL;
mf->internal_pen_variables[1].gl_vbo= 0;
mf->internal_pen_variables[1].indices= 4;
{
int j;
for(j= 0;j<2;j++)
INITIALIZE_IDENTITY_MATRIX(mf->internal_pen_variables[j].gl_matrix);
}
/*:124*//*134:*/
#line 2946 "weaver-interface-metafont_en.tex"

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
/*:134*//*181:*/
#line 4112 "weaver-interface-metafont_en.tex"

mf->have_stored_normaldeviate= false;
/*:181*//*468:*/
#line 12466 "weaver-interface-metafont_en.tex"

mf->pen_lft= mf->pen_rt= mf->pen_top= mf->pen_bot= 0.0;
/*:468*//*515:*/
#line 14068 "weaver-interface-metafont_en.tex"

mf->current_depth= 0;
/*:515*/
#line 1341 "weaver-interface-metafont_en.tex"

return mf;
}
struct context*init_context(void){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
/*70:*/
#line 1595 "weaver-interface-metafont_en.tex"

cx->nesting_level= 0;
cx->end_token_stack= NULL;
/*:70*//*86:*/
#line 1928 "weaver-interface-metafont_en.tex"

cx->variables= NULL;
/*:86*/
#line 1347 "weaver-interface-metafont_en.tex"

return cx;
}
/*:59*//*60:*/
#line 1357 "weaver-interface-metafont_en.tex"

void destroy_metafont(struct metafont*mf){
if(mf->free!=NULL){
mf->free(mf->file);
/*83:*/
#line 1879 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct variable*v= (struct variable*)(mf->global_variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*114:*/
#line 2544 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:114*//*121:*/
#line 2735 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
/*:121*//*131:*/
#line 2910 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:131*/
#line 1885 "weaver-interface-metafont_en.tex"

mf->free(v);
v= next;
}
}
/*:83*//*84:*/
#line 1897 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)named->var;
next= (struct named_variable*)(named->next);
mf->free(named->name);
/*114:*/
#line 2544 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&mf->free!=NULL)
path_recursive_free(mf->free,path,false);
}
/*:114*//*121:*/
#line 2735 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&mf->free!=NULL)
path_recursive_free(mf->free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
/*:121*//*131:*/
#line 2910 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:131*/
#line 1906 "weaver-interface-metafont_en.tex"

mf->free(v);
mf->free(named);
named= next;
}
}
/*:84*//*102:*/
#line 2299 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL)
mf->free(mf->internal_numeric_variables);
/*:102*//*126:*/
#line 2827 "weaver-interface-metafont_en.tex"

if(mf->free!=NULL){
if(mf->internal_pen_variables[1].format!=NULL){
mf->free(mf->internal_pen_variables[1].format->points);
mf->free(mf->internal_pen_variables[1].format);
}
mf->free(mf->internal_pen_variables);
}
/*:126*//*136:*/
#line 2975 "weaver-interface-metafont_en.tex"

if(mf->internal_picture_variables[0].texture!=0)
glDeleteTextures(1,&(mf->internal_picture_variables[0].texture));
if(mf->free!=NULL)
mf->free(mf->internal_picture_variables);
/*:136*/
#line 1361 "weaver-interface-metafont_en.tex"

mf->free(mf);
}
}
void destroy_context(struct metafont*mf,struct context*cx){
if(temporary_free!=NULL){
/*87:*/
#line 1936 "weaver-interface-metafont_en.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*115:*/
#line 2557 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL)
path_recursive_free(temporary_free,path,false);
}
/*:115*//*122:*/
#line 2750 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&temporary_free!=NULL)
path_recursive_free(temporary_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
/*128:*/
#line 2861 "weaver-interface-metafont_en.tex"

if(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].referenced==pen){
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].format= NULL;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].type= TYPE_T_PEN;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].flags= FLAG_NULL;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].referenced= NULL;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].gl_vbo= 0;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].indices= 0;
}
/*:128*/
#line 2757 "weaver-interface-metafont_en.tex"

}
/*:122*//*132:*/
#line 2922 "weaver-interface-metafont_en.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:132*/
#line 1942 "weaver-interface-metafont_en.tex"

temporary_free(v);
v= next;
}
}
/*:87*/
#line 1367 "weaver-interface-metafont_en.tex"

temporary_free(cx);
}
}
/*:60*//*63:*/
#line 1429 "weaver-interface-metafont_en.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
void*begin_token_list,void*end_token_list){
bool ret= true;
struct generic_token*begin,*end= NULL;
begin= (struct generic_token*)begin_token_list;
/*506:*/
#line 13825 "weaver-interface-metafont_en.tex"

glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_fb);
/*:506*/
#line 1435 "weaver-interface-metafont_en.tex"

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
/*507:*/
#line 13833 "weaver-interface-metafont_en.tex"

glBindFramebuffer(GL_FRAMEBUFFER,previous_fb);
/*:507*/
#line 1457 "weaver-interface-metafont_en.tex"

return ret;
}
/*:63*//*67:*/
#line 1537 "weaver-interface-metafont_en.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
void*begin_token_list,void**end_token_list){
/*68:*/
#line 1563 "weaver-interface-metafont_en.tex"

if(begin_token_list==end_token_list&&begin_token_list==NULL)
return true;
/*:68*/
#line 1540 "weaver-interface-metafont_en.tex"

/*74:*/
#line 1717 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_BEGINGROUP){
begin_nesting_level(mf,cx,begin_token_list);
*end_token_list= begin_token_list;
return true;
}
/*:74*//*75:*/
#line 1732 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_ENDGROUP){
if(!end_nesting_level(mf,cx,begin_token_list))
return false;
*end_token_list= begin_token_list;
return true;
}
/*:75*//*76:*/
#line 1749 "weaver-interface-metafont_en.tex"

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
/*:76*//*462:*/
#line 12246 "weaver-interface-metafont_en.tex"

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
/*:462*//*463:*/
#line 12348 "weaver-interface-metafont_en.tex"

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
/*:463*//*464:*/
#line 12399 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type==TYPE_FI){
if(!end_nesting_level(mf,cx,begin_token_list))
return false;
*end_token_list= begin_token_list;
return true;
}
/*:464*/
#line 1541 "weaver-interface-metafont_en.tex"

/*88:*/
#line 1953 "weaver-interface-metafont_en.tex"

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
/*89:*/
#line 2003 "weaver-interface-metafont_en.tex"

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
/*:89*/
#line 1970 "weaver-interface-metafont_en.tex"

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
/*:88*/
#line 1542 "weaver-interface-metafont_en.tex"

/*143:*/
#line 3092 "weaver-interface-metafont_en.tex"

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
/*144:*/
#line 3170 "weaver-interface-metafont_en.tex"

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
/*:144*/
#line 3152 "weaver-interface-metafont_en.tex"

/*185:*/
#line 4203 "weaver-interface-metafont_en.tex"

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
/*:185*/
#line 3153 "weaver-interface-metafont_en.tex"

/*216:*/
#line 5117 "weaver-interface-metafont_en.tex"

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
sizeof(float)*9);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:216*/
#line 3154 "weaver-interface-metafont_en.tex"

/*242:*/
#line 5724 "weaver-interface-metafont_en.tex"

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
/*:242*/
#line 3155 "weaver-interface-metafont_en.tex"

/*355:*/
#line 8877 "weaver-interface-metafont_en.tex"

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
if(temporary_free!=NULL&&result.format!=NULL)
path_recursive_free(temporary_free,result.format,true);
if(result.gl_vbo!=0&&result.referenced==NULL)
glDeleteBuffers(1,&(result.gl_vbo));
}
/*:355*/
#line 3156 "weaver-interface-metafont_en.tex"

/*389:*/
#line 9741 "weaver-interface-metafont_en.tex"

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

if(pic==
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE])){

/*504:*/
#line 13790 "weaver-interface-metafont_en.tex"

{
if(currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&currentpicture_fb);
}
currentpicture_fb= 0;
}
/*:504*/
#line 9761 "weaver-interface-metafont_en.tex"

}
}
else
assign_picture_variable(mf,(struct picture_variable*)var->var,
&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:389*/
#line 3157 "weaver-interface-metafont_en.tex"

/*441:*/
#line 11271 "weaver-interface-metafont_en.tex"

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
/*:441*/
#line 3158 "weaver-interface-metafont_en.tex"

return true;
}
/*:143*/
#line 1543 "weaver-interface-metafont_en.tex"

/*490:*/
#line 13349 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type==TYPE_PICKUP){
struct generic_token*end_expression= *end_token_list;
struct generic_token*next_token= 
((struct generic_token*)begin_token_list)->next;
if(begin_token_list==end_token_list||
(next_token->type!=TYPE_NULLPEN&&
next_token->type!=TYPE_SYMBOLIC&&
next_token->type!=TYPE_PENCIRCLE)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Expected 'nullpen' or pen "
"variable after 'pickup'. Not an arbitrary "
"expression.\n",
mf->file,next_token->line);
#endif
return false;
}
if(mf->internal_pen_variables[0].gl_vbo!=0)
glDeleteBuffers(1,&(mf->internal_pen_variables[0].gl_vbo));
if(next_token->type==TYPE_NULLPEN){
mf->internal_pen_variables[0].flags= FLAG_NULL;
mf->internal_pen_variables[0].referenced= NULL;
mf->internal_pen_variables[0].gl_vbo= 0;
}
else if(next_token->type==TYPE_PENCIRCLE){
mf->internal_pen_variables[0].flags= FLAG_CONVEX|FLAG_CIRCULAR;
mf->internal_pen_variables[0].referenced= NULL;
mf->internal_pen_variables[0].gl_vbo= 0;
}
else{
struct pen_variable*var= ((struct symbolic_token*)next_token)->var;
if(var==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Non-initialized variable after "
"after 'pickup' command.\n",
mf->file,next_token->line);
#endif
return false;
}
if(var->type!=TYPE_T_PEN){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Variable '%s' is not a "
"pen variable.\n",
mf->file,next_token->line,
((struct symbolic_token*)next_token)->value);
#endif
return false;
}
mf->internal_pen_variables[0].referenced= var;
}
INITIALIZE_IDENTITY_MATRIX(mf->internal_pen_variables[0].gl_matrix);
/*491:*/
#line 13417 "weaver-interface-metafont_en.tex"

while(next_token!=end_expression){
struct generic_token*begin_subexpr,*end_subexpr;
DECLARE_NESTING_CONTROL();
next_token= next_token->next;
if(next_token==NULL||next_token==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable 'pickup' "
"command format.\n",
mf->file,next_token->line);
#endif
return false;
}
begin_subexpr= next_token->next;
end_subexpr= begin_subexpr;
while(end_subexpr!=end_expression){
struct generic_token*next= end_subexpr->next;
COUNT_NESTING(end_subexpr);
if(IS_NOT_NESTED()&&
(next->type==TYPE_ROTATED||next->type==TYPE_SCALED||
next->type==TYPE_SHIFTED||next->type==TYPE_SLANTED||
next->type==TYPE_XSCALED||next->type==TYPE_YSCALED||
next->type==TYPE_ZSCALED||next->type==TYPE_TRANSFORMED))
break;
end_subexpr= next;
}
switch(next_token->type){
struct numeric_variable a;
struct pair_variable p;
struct transform_variable t;
case TYPE_ROTATED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_ROTATE(mf->internal_pen_variables[0].gl_matrix,a.value);
break;
case TYPE_SCALED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_SCALE(mf->internal_pen_variables[0].gl_matrix,a.value);

if(mf->internal_pen_variables[0].referenced){
struct pen_variable*v= mf->internal_pen_variables[0].referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_SHIFTED:
if(!eval_pair_expression(mf,cx,begin_subexpr,end_subexpr,&p))
return false;
TRANSFORM_SHIFT(mf->internal_pen_variables[0].gl_matrix,p.x,p.y);
break;
case TYPE_SLANTED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_SLANT(mf->internal_pen_variables[0].gl_matrix,a.value);

if(mf->internal_pen_variables[0].referenced){
struct pen_variable*v= mf->internal_pen_variables[0].referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)&&
!(v->flags&FLAG_CIRCULAR)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_XSCALED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_SCALE_X(mf->internal_pen_variables[0].gl_matrix,a.value);

if(mf->internal_pen_variables[0].referenced){
struct pen_variable*v= mf->internal_pen_variables[0].referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_YSCALED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_SCALE_Y(mf->internal_pen_variables[0].gl_matrix,a.value);

if(mf->internal_pen_variables[0].referenced){
struct pen_variable*v= mf->internal_pen_variables[0].referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_ZSCALED:
if(!eval_pair_expression(mf,cx,begin_subexpr,end_subexpr,&p))
return false;
TRANSFORM_SCALE_Z(mf->internal_pen_variables[0].gl_matrix,p.x,p.y);

if(mf->internal_pen_variables[0].referenced){
struct pen_variable*v= mf->internal_pen_variables[0].referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_TRANSFORMED:
if(!eval_transform_expression(mf,cx,begin_subexpr,end_subexpr,&t))
return false;
MATRIX_MULTIPLICATION(mf->internal_pen_variables[0].gl_matrix,t.value);

if(mf->internal_pen_variables[0].referenced){
struct pen_variable*v= mf->internal_pen_variables[0].referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
default:
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable 'pickup' "
"command format.\n",
mf->file,next_token->line);
#endif
return false;
}
if(end_subexpr!=end_expression)
next_token= end_subexpr->next;
else
next_token= end_subexpr;
}
/*:491*//*492:*/
#line 13563 "weaver-interface-metafont_en.tex"

{
float final_transform_matrix[9];
if(mf->internal_pen_variables[0].referenced==NULL){
memcpy(final_transform_matrix,mf->internal_pen_variables[0].gl_matrix,
9*sizeof(float));
if(!triangulate_pen(mf,&(mf->internal_pen_variables[0]),
final_transform_matrix))
return false;
}
else{
memcpy(final_transform_matrix,
mf->internal_pen_variables[0].referenced->gl_matrix,
9*sizeof(float));
MATRIX_MULTIPLICATION(final_transform_matrix,
mf->internal_pen_variables[0].gl_matrix);
if(!triangulate_pen(mf,mf->internal_pen_variables[0].referenced,
final_transform_matrix))
return false;
}
}
/*:492*/
#line 13400 "weaver-interface-metafont_en.tex"

return true;
}
/*:490*//*512:*/
#line 13923 "weaver-interface-metafont_en.tex"

else if(((struct generic_token*)begin_token_list)->type==
TYPE_DRAW||((struct generic_token*)begin_token_list)->type==
TYPE_ERASE){
int i,j;
struct path_variable path;
float transform_matrix[9];

bool erasing= (((struct generic_token*)begin_token_list)->type==
TYPE_ERASE);
struct pen_variable*currentpen= &(mf->internal_pen_variables[0]);
struct picture_variable*currentpicture= 
&(mf->internal_picture_variables[0]);

if(!eval_path_expression(mf,cx,
((struct generic_token*)begin_token_list)->next,
(struct generic_token*)*end_token_list,
&path))
return false;

if(currentpen->referenced!=NULL){
memcpy(transform_matrix,currentpen->referenced->gl_matrix,
9*sizeof(float));
MATRIX_MULTIPLICATION(transform_matrix,currentpen->gl_matrix);
currentpen= currentpen->referenced;
}
else
memcpy(transform_matrix,currentpen->gl_matrix,9*sizeof(float));
/*503:*/
#line 13758 "weaver-interface-metafont_en.tex"

{
if(currentpicture_fb==0){
int width,height;
GLuint texture;
width= mf->
internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE].width;
height= mf->
internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE].height;
texture= mf->
internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE].texture;
glGenFramebuffers(1,&currentpicture_fb);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,
GL_UNSIGNED_BYTE,NULL);
glBindFramebuffer(GL_FRAMEBUFFER,currentpicture_fb);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,
texture,0);
}
else
glBindFramebuffer(GL_FRAMEBUFFER,currentpicture_fb);
}
/*:503*/
#line 13951 "weaver-interface-metafont_en.tex"

if(erasing){
glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
else{
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

for(i= 0;i<path.length-1;i++){
int distance= 0;
float dx,dy,dt;
dx= path.points[i].u_x-path.points[i].x;
dy= path.points[i].u_y-path.points[i].y;
distance+= (int)round(sqrt(dx*dx+dy*dy));
dx= path.points[i].v_x-path.points[i].u_x;
dy= path.points[i].v_y-path.points[i].u_y;
distance+= (int)round(sqrt(dx*dx+dy*dy));
dx= path.points[(i+1)%(path.length)].x-path.points[i].v_x;
dy= path.points[(i+1)%(path.length)].y-path.points[i].v_y;
distance+= (int)round(sqrt(dx*dx+dy*dy));
dt= 1/((float)distance);
for(j= 0;j<=distance;j++){
float t= dt*j;
float x= (1-t)*(1-t)*(1-t)*path.points[i].x+
3*(1-t)*(1-t)*t*path.points[i].u_x+
3*(1-t)*t*t*path.points[i].v_x+
t*t*t*path.points[(i+1)%(path.length)].x;
float y= (1-t)*(1-t)*(1-t)*path.points[i].y+
3*(1-t)*(1-t)*t*path.points[i].u_y+
3*(1-t)*t*t*path.points[i].v_y+
t*t*t*path.points[(i+1)%(path.length)].y;
drawpoint(mf,currentpen,currentpicture,x,y,transform_matrix,
erasing);
}
}

if(path.length==1)
drawpoint(mf,currentpen,currentpicture,path.points[0].x,
path.points[0].y,transform_matrix,erasing);

if(temporary_free!=NULL)
path_recursive_free(temporary_free,&path,false);
return true;
}
/*:512*/
#line 1544 "weaver-interface-metafont_en.tex"


#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unknown statement.\n",
mf->file,
((struct generic_token*)begin_token_list)->line);
#endif
return false;
}
/*:67*//*72:*/
#line 1620 "weaver-interface-metafont_en.tex"

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
/*:72*//*73:*/
#line 1660 "weaver-interface-metafont_en.tex"

bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok){
struct generic_token*end_tok= cx->end_token_stack;
if(end_tok==NULL||end_tok->type!=tok->type){
#if defined(W_DEBUG_METAFONT)
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
/*:73*//*91:*/
#line 2045 "weaver-interface-metafont_en.tex"

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
/*97:*/
#line 2220 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:97*//*105:*/
#line 2351 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PAIR){
((struct pair_variable*)var)->x= NAN;
}
/*:105*//*107:*/
#line 2395 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_TRANSFORM)
((struct transform_variable*)var)->value[0]= NAN;
/*:107*//*113:*/
#line 2532 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
}
/*:113*//*120:*/
#line 2719 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PEN){
((struct pen_variable*)var)->format= NULL;
((struct pen_variable*)var)->gl_vbo= 0;
((struct pen_variable*)var)->indices= 0;
((struct pen_variable*)var)->flags= false;
((struct pen_variable*)var)->referenced= NULL;
}
/*:120*//*130:*/
#line 2897 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_PICTURE){
((struct picture_variable*)var)->width= -1;
((struct picture_variable*)var)->height= -1;
((struct picture_variable*)var)->texture= 0;
}
/*:130*//*139:*/
#line 3015 "weaver-interface-metafont_en.tex"

if(type==TYPE_T_BOOLEAN)
((struct boolean_variable*)var)->value= -1;
/*:139*/
#line 2083 "weaver-interface-metafont_en.tex"

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
/*:91*//*93:*/
#line 2112 "weaver-interface-metafont_en.tex"

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
/*:93*//*95:*/
#line 2175 "weaver-interface-metafont_en.tex"

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
/*:95*//*117:*/
#line 2583 "weaver-interface-metafont_en.tex"

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
/*:117*//*146:*/
#line 3203 "weaver-interface-metafont_en.tex"

void assign_numeric_variable(struct numeric_variable*target,
struct numeric_variable*source){
target->value= source->value;
}
/*:146*//*153:*/
#line 3400 "weaver-interface-metafont_en.tex"

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
/*:153*//*157:*/
#line 3508 "weaver-interface-metafont_en.tex"

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
/*:157*//*161:*/
#line 3628 "weaver-interface-metafont_en.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
/*162:*/
#line 3650 "weaver-interface-metafont_en.tex"

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
/*:162*/
#line 3633 "weaver-interface-metafont_en.tex"

/*163:*/
#line 3674 "weaver-interface-metafont_en.tex"

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
/*212:*/
#line 5012 "weaver-interface-metafont_en.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&p))
return false;
result->value= (float)hypot(p.x*p.x,p.y*p.y);
return true;
}
/*:212*//*347:*/
#line 8663 "weaver-interface-metafont_en.tex"

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
/*:347*/
#line 3691 "weaver-interface-metafont_en.tex"

else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"primary expression after 'length'.\n",mf->file,
begin_expression->line);
#endif
return false;
}
}
/*:163*/
#line 3634 "weaver-interface-metafont_en.tex"

/*164:*/
#line 3717 "weaver-interface-metafont_en.tex"

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
/*:164*//*165:*/
#line 3745 "weaver-interface-metafont_en.tex"

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
/*:165*//*166:*/
#line 3764 "weaver-interface-metafont_en.tex"

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
/*:166*//*167:*/
#line 3783 "weaver-interface-metafont_en.tex"

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
/*:167*//*168:*/
#line 3809 "weaver-interface-metafont_en.tex"

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
/*:168*//*169:*/
#line 3827 "weaver-interface-metafont_en.tex"

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
/*:169*//*170:*/
#line 3857 "weaver-interface-metafont_en.tex"

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
/*:170*//*171:*/
#line 3880 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_SUM){
bool ret;
ret= eval_numeric_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result);
if(!ret)
return false;
return true;
}
/*:171*//*172:*/
#line 3897 "weaver-interface-metafont_en.tex"

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
/*:172*/
#line 3635 "weaver-interface-metafont_en.tex"

/*213:*/
#line 5032 "weaver-interface-metafont_en.tex"

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
/*239:*/
#line 5660 "weaver-interface-metafont_en.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&t))
return false;
result->value= t.value[6];
return true;
/*:239*/
#line 5047 "weaver-interface-metafont_en.tex"

}
}
/*:213*//*214:*/
#line 5058 "weaver-interface-metafont_en.tex"

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
/*240:*/
#line 5674 "weaver-interface-metafont_en.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&t))
return false;
result->value= t.value[7];
return true;
/*:240*/
#line 5073 "weaver-interface-metafont_en.tex"

}
}
/*:214*//*215:*/
#line 5086 "weaver-interface-metafont_en.tex"

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
/*:215*//*238:*/
#line 5631 "weaver-interface-metafont_en.tex"

else if(begin_expression->type>=TYPE_XXPART&&
begin_expression->type<=TYPE_YYPART){
struct transform_variable t;
if(!eval_transform_primary(mf,cx,(struct generic_token*)
begin_expression->next,end_expression,
&t))
return false;
if(begin_expression->type==TYPE_XXPART)
result->value= t.value[0];
else if(begin_expression->type==TYPE_XYPART)
result->value= t.value[3];
else if(begin_expression->type==TYPE_YXPART)
result->value= t.value[1];
else if(begin_expression->type==TYPE_YYPART)
result->value= t.value[4];
return true;
}
/*:238*//*438:*/
#line 11149 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_TOTALWEIGHT){
struct picture_variable p;
char*data;
GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
GLuint temporary_texture= 0;
float identity_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
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
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
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
double r= (255-(unsigned char)data[i])/255.0,
g= (255-(unsigned char)data[i+1])/255.0,
b= (255-(unsigned char)data[i+2])/255.0,
a= ((unsigned char)data[i+3])/255.0;
double v= sqrt(r*r+g*g+b*b)/sqrt(3.0);
sum+= (v*a);
}
}
result->value= sum;
}

if(temporary_free!=NULL)
temporary_free(data);
glDeleteTextures(1,&temporary_texture);
glDeleteTextures(1,&(p.texture));
glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:438*//*439:*/
#line 11221 "weaver-interface-metafont_en.tex"

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
/*:439*//*440:*/
#line 11244 "weaver-interface-metafont_en.tex"

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
/*:440*/
#line 3636 "weaver-interface-metafont_en.tex"

/*173:*/
#line 3921 "weaver-interface-metafont_en.tex"

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
/*:173*/
#line 3637 "weaver-interface-metafont_en.tex"

return true;
}
/*:161*//*177:*/
#line 4000 "weaver-interface-metafont_en.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct numeric_variable*result){
if(begin_expression==end_expression){
/*178:*/
#line 4022 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin_expression)->value;
return true;
}
/*:178*/
#line 4006 "weaver-interface-metafont_en.tex"

/*179:*/
#line 4035 "weaver-interface-metafont_en.tex"

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
/*:179*/
#line 4007 "weaver-interface-metafont_en.tex"

/*182:*/
#line 4122 "weaver-interface-metafont_en.tex"

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
/*:182*/
#line 4008 "weaver-interface-metafont_en.tex"

}
else{
/*183:*/
#line 4157 "weaver-interface-metafont_en.tex"

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
/*:183*/
#line 4011 "weaver-interface-metafont_en.tex"

/*184:*/
#line 4186 "weaver-interface-metafont_en.tex"

if(begin_expression->type==TYPE_NUMERIC&&
end_expression->type==TYPE_NUMERIC&&
((struct generic_token*)begin_expression->next)->type==
TYPE_DIVISION){
result->value= ((struct numeric_token*)begin_expression)->value/
((struct numeric_token*)end_expression)->value;
return true;
}
/*:184*/
#line 4012 "weaver-interface-metafont_en.tex"

}
return true;
}
/*:177*//*187:*/
#line 4233 "weaver-interface-metafont_en.tex"

void assign_pair_variable(struct pair_variable*target,
struct pair_variable*source){
target->x= source->x;
target->y= source->y;
}
/*:187*//*189:*/
#line 4275 "weaver-interface-metafont_en.tex"

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
/*:189*//*193:*/
#line 4382 "weaver-interface-metafont_en.tex"

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
/*194:*/
#line 4453 "weaver-interface-metafont_en.tex"

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
/*:194*/
#line 4422 "weaver-interface-metafont_en.tex"

/*195:*/
#line 4490 "weaver-interface-metafont_en.tex"

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
/*:195*/
#line 4423 "weaver-interface-metafont_en.tex"

/*196:*/
#line 4518 "weaver-interface-metafont_en.tex"

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
/*:196*/
#line 4424 "weaver-interface-metafont_en.tex"

/*197:*/
#line 4542 "weaver-interface-metafont_en.tex"

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
/*:197*/
#line 4425 "weaver-interface-metafont_en.tex"

/*198:*/
#line 4562 "weaver-interface-metafont_en.tex"

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
/*:198*/
#line 4426 "weaver-interface-metafont_en.tex"

/*199:*/
#line 4583 "weaver-interface-metafont_en.tex"

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
/*:199*/
#line 4427 "weaver-interface-metafont_en.tex"

/*200:*/
#line 4604 "weaver-interface-metafont_en.tex"

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
/*:200*/
#line 4428 "weaver-interface-metafont_en.tex"

/*201:*/
#line 4625 "weaver-interface-metafont_en.tex"

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
/*:201*/
#line 4429 "weaver-interface-metafont_en.tex"

/*202:*/
#line 4650 "weaver-interface-metafont_en.tex"

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
/*:202*/
#line 4430 "weaver-interface-metafont_en.tex"

/*241:*/
#line 5702 "weaver-interface-metafont_en.tex"

else if(last_mul->type==TYPE_TRANSFORMED){
struct pair_variable a;
struct transform_variable b;
if(!eval_pair_secondary(mf,cx,begin_expression,end_secondary,&a))
return false;
if(!eval_transform_primary(mf,cx,begin_primary,end_expression,&b))
return false;
result->x= LINEAR_TRANSFORM_X(a.x,a.y,b.value);
result->y= LINEAR_TRANSFORM_Y(a.x,a.y,b.value);
return true;
}
/*:241*/
#line 4431 "weaver-interface-metafont_en.tex"

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
/*:193*//*204:*/
#line 4702 "weaver-interface-metafont_en.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pair_variable*result){
if(begin_expression==end_expression){
/*205:*/
#line 4731 "weaver-interface-metafont_en.tex"

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
/*:205*/
#line 4708 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*206:*/
#line 4774 "weaver-interface-metafont_en.tex"

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
/*:206*/
#line 4712 "weaver-interface-metafont_en.tex"

/*207:*/
#line 4835 "weaver-interface-metafont_en.tex"

else{
return eval_pair_expression(mf,cx,begin_a,end_a,result);
}
/*:207*/
#line 4713 "weaver-interface-metafont_en.tex"

}
/*354:*/
#line 8794 "weaver-interface-metafont_en.tex"

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
/*:354*//*495:*/
#line 13628 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_BOT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result))
return false;
result->y-= mf->pen_bot;
return true;
}
/*:495*//*496:*/
#line 13647 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_TOP){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result))
return false;
result->y-= mf->pen_top;
return true;
}
/*:496*//*497:*/
#line 13666 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_LFT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result))
return false;
result->x-= mf->pen_lft;
return true;
}
/*:497*//*498:*/
#line 13686 "weaver-interface-metafont_en.tex"

else if(begin_expression->type==TYPE_RT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin_expression->next,
end_expression,result))
return false;
result->x-= mf->pen_rt;
return true;
}
/*:498*/
#line 4715 "weaver-interface-metafont_en.tex"

/*208:*/
#line 4846 "weaver-interface-metafont_en.tex"

else if(end_expression->type==TYPE_CLOSE_BRACKETS){
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
/*:208*/
#line 4716 "weaver-interface-metafont_en.tex"

/*209:*/
#line 4926 "weaver-interface-metafont_en.tex"

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
/*:209*/
#line 4717 "weaver-interface-metafont_en.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable "
"expression.",mf->file,begin_expression->line);
#endif
return false;
}
/*:204*//*220:*/
#line 5195 "weaver-interface-metafont_en.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result){
return eval_transform_secondary(mf,cx,begin_expression,end_expression,
result);
}
/*:220*//*222:*/
#line 5227 "weaver-interface-metafont_en.tex"

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
if(end_secondary==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Transform expression began "
"with transformer.",mf->file,begin_expression->line);
#endif
return false;
}
if(!eval_transform_secondary(mf,cx,begin_expression,end_secondary,
result))
return false;
/*223:*/
#line 5282 "weaver-interface-metafont_en.tex"

if(last_transform->type==TYPE_ROTATED){
struct numeric_variable theta;
double angle_radian;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&theta))
return false;

angle_radian= theta.value*0.0174533;
TRANSFORM_ROTATE(result->value,angle_radian);
return true;
}
/*:223*//*224:*/
#line 5300 "weaver-interface-metafont_en.tex"

else if(last_transform->type==TYPE_SCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;
TRANSFORM_SCALE(result->value,scale.value);
return true;
}
/*:224*//*225:*/
#line 5316 "weaver-interface-metafont_en.tex"

else if(last_transform->type==TYPE_SHIFTED){
struct pair_variable shift;
if(!eval_pair_primary(mf,cx,last_transform->next,end_expression,
&shift))
return false;
TRANSFORM_SHIFT(result->value,shift.x,shift.y);
return true;
}
/*:225*//*226:*/
#line 5332 "weaver-interface-metafont_en.tex"

else if(last_transform->type==TYPE_SLANTED){
struct numeric_variable slant;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&slant))
return false;
TRANSFORM_SLANT(result->value,slant.value);
return true;
}
/*:226*//*227:*/
#line 5349 "weaver-interface-metafont_en.tex"

else if(last_transform->type==TYPE_XSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;
TRANSFORM_SCALE_X(result->value,scale.value);
return true;
}
/*:227*//*228:*/
#line 5364 "weaver-interface-metafont_en.tex"

else if(last_transform->type==TYPE_YSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;
TRANSFORM_SCALE_Y(result->value,scale.value);
return true;
}
/*:228*//*229:*/
#line 5382 "weaver-interface-metafont_en.tex"

else if(last_transform->type==TYPE_ZSCALED){
struct pair_variable scale;
if(!eval_pair_primary(mf,cx,last_transform->next,end_expression,
&scale))
return false;
TRANSFORM_SCALE_Z(result->value,scale.x,scale.y);
return true;
}
/*:229*//*230:*/
#line 5416 "weaver-interface-metafont_en.tex"

else if(last_transform->type==TYPE_TRANSFORMED){
struct transform_variable b;
if(!eval_transform_primary(mf,cx,last_transform->next,end_expression,
&b))
return false;
MATRIX_MULTIPLICATION(result->value,b.value);
return true;
}
/*:230*/
#line 5266 "weaver-interface-metafont_en.tex"

#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transformer "
"in transform expression.",mf->file,begin_expression->line);
#endif
return false;
}
}
/*:222*//*232:*/
#line 5461 "weaver-interface-metafont_en.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct transform_variable*result){
if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*233:*/
#line 5508 "weaver-interface-metafont_en.tex"

struct symbolic_token*v= (struct symbolic_token*)begin_expression;
struct transform_variable*content= v->var;
if(content==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Not allocated variable: "
"%s.\n",mf->file,v->line,v->value);
#endif
return false;
}
memcpy(result->value,content->value,sizeof(float)*9);
return true;
/*:233*/
#line 5468 "weaver-interface-metafont_en.tex"

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
}while(p!=NULL);
if(has_comma){
/*235:*/
#line 5546 "weaver-interface-metafont_en.tex"

int i;
struct generic_token*begin_numeric_expr,*end_numeric_expr;
struct numeric_variable numeric_result;
begin_numeric_expr= begin_expression->next;
end_numeric_expr= begin_numeric_expr;
float values[6];
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
values[i]= numeric_result.value;
begin_numeric_expr= p->next;
end_numeric_expr= begin_numeric_expr;
}

result->value[0]= values[2];result->value[1]= values[4];
result->value[2]= 0.0;
result->value[3]= values[3];result->value[4]= values[5];
result->value[5]= 0.0;
result->value[6]= values[0];result->value[7]= values[1];
result->value[8]= 1.0;
return true;
/*:235*/
#line 5490 "weaver-interface-metafont_en.tex"

}
else{
/*234:*/
#line 5526 "weaver-interface-metafont_en.tex"

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
/*:234*/
#line 5493 "weaver-interface-metafont_en.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transform primary "
"expression.\n",mf->file,begin_expression->line);
#endif
return false;
}
/*:232*//*244:*/
#line 5758 "weaver-interface-metafont_en.tex"

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
/*:244*//*246:*/
#line 5799 "weaver-interface-metafont_en.tex"

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
/*:246*//*248:*/
#line 5829 "weaver-interface-metafont_en.tex"

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
/*:248*//*252:*/
#line 5914 "weaver-interface-metafont_en.tex"

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
/*:252*//*254:*/
#line 5959 "weaver-interface-metafont_en.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin_expression,end_expression);
expected_length= number_of_joins+1;
/*255:*/
#line 5984 "weaver-interface-metafont_en.tex"

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
/*:255*/
#line 5967 "weaver-interface-metafont_en.tex"

/*256:*/
#line 6009 "weaver-interface-metafont_en.tex"

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
/*:256*/
#line 5968 "weaver-interface-metafont_en.tex"

/*257:*/
#line 6039 "weaver-interface-metafont_en.tex"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d= NULL,*end_d= NULL,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
struct path_points*z1_point= NULL,*z2_point= NULL;
/*266:*/
#line 6356 "weaver-interface-metafont_en.tex"

float w0_x= NAN,w0_y= NAN,w1_x= NAN,w1_y= NAN;
float prev_w_x= NAN,prev_w_y= NAN;
float next_w_x= NAN,next_w_y= NAN;
/*:266*//*282:*/
#line 6916 "weaver-interface-metafont_en.tex"

float first_w_x= NAN,first_w_y= NAN;
/*:282*//*286:*/
#line 7017 "weaver-interface-metafont_en.tex"

float previous_point_x= NAN,previous_point_y= NAN;
/*:286*//*290:*/
#line 7123 "weaver-interface-metafont_en.tex"

float first_point_x= NAN,first_point_y= NAN;
/*:290*/
#line 6045 "weaver-interface-metafont_en.tex"

begin_z1= begin_expression;
end_z1= begin_z1;
while(begin_z1!=end_expression||result->length<expected_length){
/*258:*/
#line 6071 "weaver-interface-metafont_en.tex"

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
/*:258*//*259:*/
#line 6097 "weaver-interface-metafont_en.tex"

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
/*:259*//*260:*/
#line 6133 "weaver-interface-metafont_en.tex"

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
/*:260*//*261:*/
#line 6171 "weaver-interface-metafont_en.tex"

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
/*:261*//*262:*/
#line 6211 "weaver-interface-metafont_en.tex"

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
/*:262*/
#line 6049 "weaver-interface-metafont_en.tex"

/*263:*/
#line 6244 "weaver-interface-metafont_en.tex"

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
/*:263*//*264:*/
#line 6277 "weaver-interface-metafont_en.tex"

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
/*:264*//*265:*/
#line 6330 "weaver-interface-metafont_en.tex"

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
/*:265*/
#line 6050 "weaver-interface-metafont_en.tex"

/*267:*/
#line 6372 "weaver-interface-metafont_en.tex"

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
/*:267*/
#line 6051 "weaver-interface-metafont_en.tex"

/*273:*/
#line 6492 "weaver-interface-metafont_en.tex"

float tension0= NAN,tension1= NAN,u_x= NAN,u_y= NAN,v_x= NAN,
v_y= NAN;
bool atleast0= false,atleast1= false;
/*:273*//*274:*/
#line 6508 "weaver-interface-metafont_en.tex"

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
/*:274*//*275:*/
#line 6536 "weaver-interface-metafont_en.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_STRAIGHT_JOIN){
u_x= z1_point->x+(1.0/3.0)*(z2_point->x-z1_point->x);
u_y= z1_point->y+(1.0/3.0)*(z2_point->y-z1_point->y);
v_x= z1_point->x+(2.0/3.0)*(z2_point->x-z1_point->x);
v_y= z1_point->y+(2.0/3.0)*(z2_point->y-z1_point->y);
}
/*:275*//*276:*/
#line 6551 "weaver-interface-metafont_en.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
tension0= 1.0;
tension1= 1.0;
atleast0= false;
atleast1= false;
}
/*:276*//*277:*/
#line 6569 "weaver-interface-metafont_en.tex"

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
/*:277*//*278:*/
#line 6636 "weaver-interface-metafont_en.tex"

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
/*:278*/
#line 6052 "weaver-interface-metafont_en.tex"

/*280:*/
#line 6853 "weaver-interface-metafont_en.tex"

if(isnan(w0_x)&&isnan(w0_y)){
w0_x= prev_w_x;
w0_y= prev_w_y;
}
/*:280*//*281:*/
#line 6866 "weaver-interface-metafont_en.tex"

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
/*:281*//*283:*/
#line 6925 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_d!=NULL&&end_d!=NULL){
first_w_x= w0_x;
first_w_y= w0_y;
}
/*:283*//*284:*/
#line 6938 "weaver-interface-metafont_en.tex"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE){
if(!isnan(first_w_x)&&isnan(w1_x)){
w1_x= first_w_x;
w1_y= first_w_y;
}
}
/*:284*//*285:*/
#line 6956 "weaver-interface-metafont_en.tex"

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
/*293:*/
#line 7170 "weaver-interface-metafont_en.tex"

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
/*:293*/
#line 6990 "weaver-interface-metafont_en.tex"

}
/*:285*//*287:*/
#line 7028 "weaver-interface-metafont_en.tex"

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
/*:287*//*288:*/
#line 7049 "weaver-interface-metafont_en.tex"

if(begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
previous_point_x= v_x;
previous_point_y= v_y;
}
else{
previous_point_x= NAN;
previous_point_y= NAN;
}
/*:288*//*289:*/
#line 7068 "weaver-interface-metafont_en.tex"

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
/*:289*//*291:*/
#line 7131 "weaver-interface-metafont_en.tex"

if(begin_z1==begin_expression&&end_expression->type==TYPE_CYCLE&&
begin_j!=end_j&&
((struct generic_token*)(begin_j->next))->type==TYPE_CONTROLS){
first_point_x= u_x;
first_point_y= u_y;
}
/*:291*//*292:*/
#line 7145 "weaver-interface-metafont_en.tex"

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
/*:292*//*294:*/
#line 7212 "weaver-interface-metafont_en.tex"

if(isnan(u_x)||isnan(u_y)||isnan(v_x)||isnan(v_y)){
if(isnan(w0_x)||isnan(w0_y)||isnan(w1_x)||isnan(w1_y)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Could not find a suitable "
"direction specifier.\n",mf->file,begin_j->line);
#endif
return false;
}
}
/*:294*//*298:*/
#line 7300 "weaver-interface-metafont_en.tex"

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
/*305:*/
#line 7495 "weaver-interface-metafont_en.tex"

if(atleast0)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&u_x,&u_y);
if(atleast1)
correct_tension(z1_point->x,z1_point->y,z2_point->x,z2_point->y,
w0_x,w0_y,w1_x,w1_y,&v_x,&v_y);
/*:305*/
#line 7313 "weaver-interface-metafont_en.tex"

}
/*:298*//*306:*/
#line 7511 "weaver-interface-metafont_en.tex"

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
/*:306*/
#line 6053 "weaver-interface-metafont_en.tex"

/*279:*/
#line 6834 "weaver-interface-metafont_en.tex"

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
/*:279*/
#line 6054 "weaver-interface-metafont_en.tex"

begin_z1= begin_z2;
end_z1= end_z2;
}
}
/*:257*/
#line 5969 "weaver-interface-metafont_en.tex"

return true;
}
/*:254*//*269:*/
#line 6403 "weaver-interface-metafont_en.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y){
/*270:*/
#line 6420 "weaver-interface-metafont_en.tex"

if(begin==NULL||end==NULL){
return true;
}
/*:270*/
#line 6408 "weaver-interface-metafont_en.tex"

/*271:*/
#line 6433 "weaver-interface-metafont_en.tex"

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
/*:271*/
#line 6409 "weaver-interface-metafont_en.tex"

/*272:*/
#line 6471 "weaver-interface-metafont_en.tex"

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
/*:272*/
#line 6410 "weaver-interface-metafont_en.tex"

return false;
}
/*:269*//*296:*/
#line 7275 "weaver-interface-metafont_en.tex"

double compute_f(double theta,double phi){
double n= 2+sqrt(2)*(sin(theta)-0.0625*sin(phi))*
(sin(phi)-0.0625*sin(theta))*(cos(theta)-cos(phi));
double d= 3*(1+0.5*(sqrt(5)-1)*cos(theta)+0.5*(3-sqrt(5))*
cos(phi));
return n/d;
}
/*:296*//*300:*/
#line 7332 "weaver-interface-metafont_en.tex"

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
/*:300*//*302:*/
#line 7367 "weaver-interface-metafont_en.tex"

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
/*303:*/
#line 7409 "weaver-interface-metafont_en.tex"

bool s1,s2,s3;
s1= ((*control_x-p1_x)*(p0_y-p1_y)-
(p0_x-p1_x)*(*control_y-p1_y))<0;
s2= ((*control_x-p2_x)*(p1_y-p2_y)-
(p1_x-p2_x)*(*control_y-p2_y))<0;
s3= ((*control_x-p0_x)*(p2_y-p0_y)-
(p2_x-p0_x)*(*control_y-p0_y))<0;
if(s1==s2&&s2==s3)
return;
/*:303*/
#line 7391 "weaver-interface-metafont_en.tex"

/*304:*/
#line 7431 "weaver-interface-metafont_en.tex"

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
/*:304*/
#line 7392 "weaver-interface-metafont_en.tex"

}
}
/*:302*//*308:*/
#line 7568 "weaver-interface-metafont_en.tex"

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
/*:308*//*310:*/
#line 7661 "weaver-interface-metafont_en.tex"

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
/*311:*/
#line 7763 "weaver-interface-metafont_en.tex"

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
/*:311*/
#line 7710 "weaver-interface-metafont_en.tex"

/*314:*/
#line 7821 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,a.value);
return true;
}
/*:314*/
#line 7711 "weaver-interface-metafont_en.tex"

/*317:*/
#line 7874 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SHIFTED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_shift(result,a.x,a.y);
return true;
}
/*:317*/
#line 7712 "weaver-interface-metafont_en.tex"

/*320:*/
#line 7920 "weaver-interface-metafont_en.tex"

if(transform_op->type==TYPE_SLANTED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_slant(result,a.value);
return true;
}
/*:320*/
#line 7713 "weaver-interface-metafont_en.tex"

/*323:*/
#line 7963 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_XSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,a.value,1.0);
return true;
}
/*:323*/
#line 7714 "weaver-interface-metafont_en.tex"

/*324:*/
#line 7979 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_YSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end_expression,
&a))
return false;
path_xyscale(result,1.0,a.value);
return true;
}
/*:324*/
#line 7715 "weaver-interface-metafont_en.tex"

/*325:*/
#line 8005 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_ZSCALED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end_expression,&a))
return false;
path_zscale(result,a.x,a.y);
return true;
}
/*:325*/
#line 7716 "weaver-interface-metafont_en.tex"

/*328:*/
#line 8056 "weaver-interface-metafont_en.tex"

else if(transform_op->type==TYPE_TRANSFORMED){
struct transform_variable a;
if(!eval_transform_primary(mf,cx,transform_op->next,end_expression,&a))
return false;
path_transform(result,a.value);
return true;
}
else{
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognizable transformer\n",
mf->file,transform_op->line);
#endif
return false;
}
/*:328*/
#line 7717 "weaver-interface-metafont_en.tex"

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
/*:310*//*313:*/
#line 7791 "weaver-interface-metafont_en.tex"

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
/*:313*//*316:*/
#line 7849 "weaver-interface-metafont_en.tex"

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
/*:316*//*319:*/
#line 7895 "weaver-interface-metafont_en.tex"

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
/*:319*//*322:*/
#line 7941 "weaver-interface-metafont_en.tex"

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
/*:322*//*327:*/
#line 8025 "weaver-interface-metafont_en.tex"

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
/*:327*//*330:*/
#line 8085 "weaver-interface-metafont_en.tex"

void path_transform(struct path_variable*p,float*M){
int i;
for(i= 0;i<p->length;i++){
if(p->points[i].subpath!=NULL)
path_transform((struct path_variable*)(p->points[i].subpath),M);
else{
float x0= p->points[i].x;
float y0= p->points[i].y;
p->points[i].x= LINEAR_TRANSFORM_X(x0,y0,M);
p->points[i].y= LINEAR_TRANSFORM_Y(x0,y0,M);
x0= p->points[i].u_x;
y0= p->points[i].u_y;
p->points[i].u_x= LINEAR_TRANSFORM_X(x0,y0,M);
p->points[i].u_y= LINEAR_TRANSFORM_Y(x0,y0,M);
x0= p->points[i].v_x;
y0= p->points[i].v_y;
p->points[i].v_x= LINEAR_TRANSFORM_X(x0,y0,M);
p->points[i].v_x= LINEAR_TRANSFORM_Y(x0,y0,M);
}
}
}
/*:330*//*334:*/
#line 8164 "weaver-interface-metafont_en.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct path_variable*result){
if(begin_expression->type==TYPE_REVERSE){
/*336:*/
#line 8262 "weaver-interface-metafont_en.tex"

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
/*:336*/
#line 8170 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUBPATH){
/*339:*/
#line 8351 "weaver-interface-metafont_en.tex"

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
/*:339*/
#line 8173 "weaver-interface-metafont_en.tex"

}
else if(begin_expression==end_expression&&
begin_expression->type==TYPE_SYMBOLIC){
/*344:*/
#line 8549 "weaver-interface-metafont_en.tex"

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
/*:344*/
#line 8177 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*345:*/
#line 8594 "weaver-interface-metafont_en.tex"

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
/*:345*/
#line 8181 "weaver-interface-metafont_en.tex"

}
/*383:*/
#line 9555 "weaver-interface-metafont_en.tex"

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
/*384:*/
#line 9592 "weaver-interface-metafont_en.tex"

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
/*:384*/
#line 9570 "weaver-interface-metafont_en.tex"

}
else if(tmp.flags&FLAG_CIRCULAR){
/*385:*/
#line 9614 "weaver-interface-metafont_en.tex"

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
/*:385*/
#line 9573 "weaver-interface-metafont_en.tex"

}
else if(tmp.flags&FLAG_SQUARE){
/*386:*/
#line 9663 "weaver-interface-metafont_en.tex"

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
/*:386*/
#line 9576 "weaver-interface-metafont_en.tex"

}
else{
/*387:*/
#line 9697 "weaver-interface-metafont_en.tex"

recursive_copy_points(temporary_alloc,&result,tmp.format,false);
if(temporary_free!=NULL&&tmp.referenced==NULL)
temporary_free(tmp.format);
/*:387*/
#line 9579 "weaver-interface-metafont_en.tex"

}
/*388:*/
#line 9709 "weaver-interface-metafont_en.tex"

{
int i;
for(i= 0;i<result->length;i++){
float x0= result->points[i].x,y0= result->points[i].y;
result->points[i].x= LINEAR_TRANSFORM_X(x0,y0,tmp.gl_matrix);
result->points[i].y= LINEAR_TRANSFORM_Y(x0,y0,tmp.gl_matrix);
x0= result->points[i].u_x;
y0= result->points[i].u_y;
result->points[i].u_x= LINEAR_TRANSFORM_X(x0,y0,tmp.gl_matrix);
result->points[i].u_y= LINEAR_TRANSFORM_Y(x0,y0,tmp.gl_matrix);
x0= result->points[i].v_x;
y0= result->points[i].v_y;
result->points[i].v_x= LINEAR_TRANSFORM_X(x0,y0,tmp.gl_matrix);
result->points[i].v_y= LINEAR_TRANSFORM_Y(x0,y0,tmp.gl_matrix);
}
}
/*:388*/
#line 9581 "weaver-interface-metafont_en.tex"

return true;
}
/*:383*/
#line 8183 "weaver-interface-metafont_en.tex"

{
/*346:*/
#line 8625 "weaver-interface-metafont_en.tex"

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
/*:346*/
#line 8185 "weaver-interface-metafont_en.tex"

}
return false;
}
/*:334*//*335:*/
#line 8217 "weaver-interface-metafont_en.tex"

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
/*:335*//*338:*/
#line 8299 "weaver-interface-metafont_en.tex"

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
/*:338*//*341:*/
#line 8470 "weaver-interface-metafont_en.tex"

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
/*:341*//*343:*/
#line 8500 "weaver-interface-metafont_en.tex"

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
/*:343*//*351:*/
#line 8724 "weaver-interface-metafont_en.tex"

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
/*:351*//*353:*/
#line 8755 "weaver-interface-metafont_en.tex"

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
/*:353*//*357:*/
#line 8913 "weaver-interface-metafont_en.tex"

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
if(target->format!=NULL&&disalloc!=NULL)
path_recursive_free(disalloc,target->format,true);
if(target->gl_vbo!=0)
glDeleteBuffers(1,&(target->gl_vbo));
memcpy(target,source,sizeof(struct pen_variable));
target->type= TYPE_T_PEN;
if(!(source->flags&(FLAG_CIRCULAR|FLAG_SQUARE|FLAG_NULL)))
recursive_copy_points(alloc,&(target->format),source->format,true);
target->gl_vbo= 0;
target->indices= 0;
target->referenced= NULL;


if(target==&(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN]))
triangulate_pen(mf,target,target->gl_matrix);
}
/*:357*//*359:*/
#line 8968 "weaver-interface-metafont_en.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct pen_variable*result){
return eval_pen_secondary(mf,cx,begin_expression,end_token_list,result);
}
/*:359*//*361:*/
#line 9019 "weaver-interface-metafont_en.tex"

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
/*362:*/
#line 9089 "weaver-interface-metafont_en.tex"

struct numeric_variable r;
double rotation;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&r))
return false;
rotation= 0.017453292519943295*r.value;
TRANSFORM_ROTATE(pen->gl_matrix,rotation);
return true;
/*:362*/
#line 9050 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*363:*/
#line 9104 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SCALE(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&a.value> 1.0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:363*/
#line 9053 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*364:*/
#line 9123 "weaver-interface-metafont_en.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
TRANSFORM_SHIFT(pen->gl_matrix,p.x,p.y);
return true;
/*:364*/
#line 9056 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*365:*/
#line 9135 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SLANT(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&!(pen->flags&FLAG_STRAIGHT)&&
!(pen->flags&FLAG_CIRCULAR)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:365*/
#line 9059 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*366:*/
#line 9155 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SCALE_X(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&a.value> 1.0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:366*/
#line 9062 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*367:*/
#line 9174 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SCALE_Y(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&a.value> 1.0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:367*/
#line 9065 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*368:*/
#line 9199 "weaver-interface-metafont_en.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
TRANSFORM_SCALE_Z(pen->gl_matrix,p.x,p.y);

if(pen->gl_vbo!=0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:368*/
#line 9068 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*369:*/
#line 9218 "weaver-interface-metafont_en.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,last_transformer->next,end_expression,&t))
return false;
MATRIX_MULTIPLICATION(pen->gl_matrix,t.value);

if(pen->gl_vbo!=0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:369*/
#line 9071 "weaver-interface-metafont_en.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:361*//*373:*/
#line 9275 "weaver-interface-metafont_en.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct pen_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*374:*/
#line 9316 "weaver-interface-metafont_en.tex"

struct symbolic_token*v= (struct symbolic_token*)begin_expression;
struct pen_variable*content= v->var,*to_copy= v->var;
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
if(content->referenced!=NULL)
to_copy= content->referenced;
memcpy(result,to_copy,sizeof(struct pen_variable));
if(to_copy->format!=NULL)
recursive_copy_points(temporary_alloc,&(result->format),
to_copy->format,true);
if(to_copy!=content)
MATRIX_MULTIPLICATION(result->gl_matrix,content->gl_matrix);
return true;
/*:374*/
#line 9282 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_NULLPEN){
/*375:*/
#line 9350 "weaver-interface-metafont_en.tex"

result->format= NULL;
result->flags= FLAG_NULL;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:375*/
#line 9285 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_PENCIRCLE){
/*376:*/
#line 9366 "weaver-interface-metafont_en.tex"

result->format= NULL;
result->flags= FLAG_CONVEX|FLAG_CIRCULAR;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:376*/
#line 9288 "weaver-interface-metafont_en.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*377:*/
#line 9382 "weaver-interface-metafont_en.tex"

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
/*:377*/
#line 9294 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_MAKEPEN){
/*378:*/
#line 9405 "weaver-interface-metafont_en.tex"

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
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:378*/
#line 9297 "weaver-interface-metafont_en.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized pen expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:373*//*380:*/
#line 9450 "weaver-interface-metafont_en.tex"

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
/*:380*//*396:*/
#line 9889 "weaver-interface-metafont_en.tex"

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
return false;
}

glDeleteShader(vertex);
glDeleteShader(fragment);
return prog;
}
/*:396*//*400:*/
#line 9973 "weaver-interface-metafont_en.tex"

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
/*:400*//*402:*/
#line 10015 "weaver-interface-metafont_en.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height,bool clear_background){
glColorMask(true,true,true,true);
glViewport(0,0,dst_width,dst_height);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glUseProgram(program);
glUniformMatrix3fv(uniform_matrix,1,true,matrix);
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
float model_view_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
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
/*:402*//*404:*/
#line 10077 "weaver-interface-metafont_en.tex"

void assign_picture_variable(struct metafont*mf,
struct picture_variable*target,
struct picture_variable*source){
GLuint temporary_framebuffer;
GLint previous_framebuffer;
float model_view_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
if(target->texture!=0)
glDeleteTextures(1,&(target->texture));
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
get_new_framebuffer(&temporary_framebuffer,&(target->texture),
source->width,source->height);
render_picture(source,model_view_matrix,source->width,source->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
if(target==
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE])){

/*504:*/
#line 13790 "weaver-interface-metafont_en.tex"

{
if(currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&currentpicture_fb);
}
currentpicture_fb= 0;
}
/*:504*/
#line 10099 "weaver-interface-metafont_en.tex"

}
}
/*:404*//*406:*/
#line 10142 "weaver-interface-metafont_en.tex"

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
/*411:*/
#line 10363 "weaver-interface-metafont_en.tex"

{
float matrix[9];
bool modified= false;
INITIALIZE_IDENTITY_MATRIX(matrix);
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
/*:411*/
#line 10164 "weaver-interface-metafont_en.tex"

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
/*411:*/
#line 10363 "weaver-interface-metafont_en.tex"

{
float matrix[9];
bool modified= false;
INITIALIZE_IDENTITY_MATRIX(matrix);
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
/*:411*/
#line 10180 "weaver-interface-metafont_en.tex"

/*410:*/
#line 10272 "weaver-interface-metafont_en.tex"


GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
float model_view_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
result->width= ((a.width>=b.width)?(a.width):(b.width));
result->height= ((a.height>=b.height)?(a.height):(b.height));
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
get_new_framebuffer(&temporary_framebuffer,&(result->texture),
result->width,result->height);

model_view_matrix[0]= (double)a.width/(double)result->width;
model_view_matrix[4]= (double)a.height/(double)result->height;
render_picture(&a,model_view_matrix,result->width,result->height,true);

model_view_matrix[0]= (double)b.width/(double)result->width;
model_view_matrix[4]= (double)b.height/(double)result->height;
if(last_operator->type==TYPE_SUBTRACT){
glEnable(GL_BLEND);

glBlendFunc(GL_ONE,GL_ONE);

glBlendEquationSeparate(GL_MAX,GL_FUNC_REVERSE_SUBTRACT);
glUseProgram(inv_program);
glUniformMatrix3fv(uniform_inv_matrix,1,true,model_view_matrix);
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

glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&temporary_framebuffer);
/*:410*/
#line 10181 "weaver-interface-metafont_en.tex"

if(a.texture!=0)
glDeleteTextures(1,&(a.texture));
if(b.texture!=0)
glDeleteTextures(1,&(b.texture));
return true;
}
}
/*:406*//*413:*/
#line 10411 "weaver-interface-metafont_en.tex"

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
/*415:*/
#line 10498 "weaver-interface-metafont_en.tex"

struct numeric_variable r;
double rotation;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&r))
return false;
rotation= 0.017453292519943295*r.value;
TRANSFORM_ROTATE(matrix,rotation);
*modified= true;
return true;
/*:415*/
#line 10444 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*414:*/
#line 10485 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SCALE(matrix,a.value);
*modified= true;
return true;
/*:414*/
#line 10447 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*416:*/
#line 10516 "weaver-interface-metafont_en.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
p.x= 2.0*(p.x/result->width);
p.y= 2.0*(p.y/result->height);
TRANSFORM_SHIFT(matrix,p.x,p.y);
*modified= true;
return true;
/*:416*/
#line 10450 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*417:*/
#line 10531 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SLANT(matrix,a.value);
*modified= true;
return true;
/*:417*/
#line 10453 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*418:*/
#line 10544 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SCALE_X(matrix,a.value);
*modified= true;
return true;
/*:418*/
#line 10456 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*419:*/
#line 10557 "weaver-interface-metafont_en.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end_expression,&a))
return false;
TRANSFORM_SCALE_Y(matrix,a.value);
*modified= true;
return true;
/*:419*/
#line 10459 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*420:*/
#line 10570 "weaver-interface-metafont_en.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end_expression,&p))
return false;
TRANSFORM_SCALE_Z(matrix,p.x,p.y);
*modified= true;
return true;
/*:420*/
#line 10462 "weaver-interface-metafont_en.tex"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*421:*/
#line 10584 "weaver-interface-metafont_en.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,last_transformer->next,end_expression,
&t))
return false;
MATRIX_MULTIPLICATION(matrix,t.value);
*modified= true;
return true;
/*:421*/
#line 10465 "weaver-interface-metafont_en.tex"

}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture transformer\n",
mf->file,begin_expression->line);
#endif
return false;
}
}
/*:413*//*423:*/
#line 10640 "weaver-interface-metafont_en.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*origin,
float*matrix){
int i;
GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;



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
float x= LINEAR_TRANSFORM_X(origin_coordinates[i],
origin_coordinates[i+1],matrix);
float y= LINEAR_TRANSFORM_Y(origin_coordinates[i],
origin_coordinates[i+1],matrix);
if(x> max_x)max_x= x;
if(x<min_x)min_x= x;
if(y> max_y)max_y= y;
if(y<min_y)min_y= y;
}

dst->width= (int)(max_x-min_x)+
(int)(origin->width*matrix[6]);
dst->height= (int)(max_y-min_y)+
(int)(origin->height*matrix[7]);


{
double x_correction= ((double)origin->width)/(double)dst->width;
double y_correction= ((double)origin->height)/(double)dst->height;
matrix[0]= matrix[0]*x_correction;
matrix[3]= matrix[3]*x_correction;
matrix[6]= matrix[6]*x_correction;
matrix[1]= matrix[1]*y_correction;
matrix[4]= matrix[4]*y_correction;
matrix[7]= matrix[7]*y_correction;
}

glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
get_new_framebuffer(&temporary_framebuffer,&(dst->texture),dst->width,
dst->height);

render_picture(origin,matrix,dst->width,dst->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:423*//*427:*/
#line 10748 "weaver-interface-metafont_en.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_expression,
struct picture_variable*result){
if(begin_expression==end_expression){
if(begin_expression->type==TYPE_SYMBOLIC){
/*428:*/
#line 10790 "weaver-interface-metafont_en.tex"

GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
float identity_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
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
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
get_new_framebuffer(&temporary_framebuffer,&(result->texture),
result->width,result->height);

render_picture(content,identity_matrix,result->width,result->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
/*:428*/
#line 10755 "weaver-interface-metafont_en.tex"

}
}
else{
if(begin_expression->type==TYPE_OPEN_PARENTHESIS&&
end_expression->type==TYPE_CLOSE_PARENTHESIS){
/*429:*/
#line 10834 "weaver-interface-metafont_en.tex"

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
/*:429*/
#line 10761 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_NULLPICTURE){
/*430:*/
#line 10859 "weaver-interface-metafont_en.tex"

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
/*:430*/
#line 10764 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUM){
/*431:*/
#line 10911 "weaver-interface-metafont_en.tex"

struct generic_token*p= begin_expression->next;
if(begin_expression==end_expression){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Missing image expression "
"after '+'.\n",mf->file,begin_expression->line);
#endif
return false;
}
return eval_picture_primary(mf,cx,p,end_expression,result);
/*:431*/
#line 10767 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUBTRACT){
/*432:*/
#line 10932 "weaver-interface-metafont_en.tex"

struct picture_variable p;
GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
float identity_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
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
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
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
glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
/*:432*/
#line 10770 "weaver-interface-metafont_en.tex"

}
else if(begin_expression->type==TYPE_SUBPICTURE){
/*433:*/
#line 10983 "weaver-interface-metafont_en.tex"

struct pair_variable pair_offset,subpicture_size;
struct picture_variable original_picture;
/*434:*/
#line 11000 "weaver-interface-metafont_en.tex"

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
/*:434*/
#line 10986 "weaver-interface-metafont_en.tex"

/*435:*/
#line 11066 "weaver-interface-metafont_en.tex"

{
GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
float render_matrix[9];
INITIALIZE_IDENTITY_MATRIX(render_matrix);
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
get_new_framebuffer(&temporary_framebuffer,&(result->texture),
subpicture_size.x,subpicture_size.y);
result->width= subpicture_size.x;
result->height= subpicture_size.y;

glClearColor(1.0,1.0,1.0,0.0);
glClear(GL_COLOR_BUFFER_BIT);

render_matrix[0]= original_picture.width/subpicture_size.x;
render_matrix[4]= original_picture.height/subpicture_size.y;

render_matrix[6]= -2.0*(pair_offset.x+
0.5*(subpicture_size.x-original_picture.width))/
subpicture_size.x;
render_matrix[7]= -2.0*(pair_offset.y+
0.5*(subpicture_size.y-original_picture.height))/
subpicture_size.y;

render_picture(&original_picture,render_matrix,result->width,result->height,
false);


glDisable(GL_BLEND);
glDeleteTextures(1,&(original_picture.texture));
glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:435*/
#line 10987 "weaver-interface-metafont_en.tex"

return false;
/*:433*/
#line 10773 "weaver-interface-metafont_en.tex"

}
}
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: %s:%d: Unrecognized picture expression.\n",
mf->file,begin_expression->line);
#endif
return false;
}
/*:427*//*445:*/
#line 11362 "weaver-interface-metafont_en.tex"

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
int i,order[6]= {6,7,0,3,1,4};
if(!eval_transform_expression(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_transform_expression(mf,cx,last_operator->next,
end_expression,&b))
return false;
switch(last_operator->type){
case TYPE_LT:
for(i= 0;i<5;i++)
if(a.value[order[i]]!=b.value[order[i]]){
result->value= (a.value[order[i]]<b.value[order[i]]);
return true;
}
result->value= (a.value[order[i]]<b.value[order[i]]);
return true;
case TYPE_LEQ:
for(i= 0;i<5;i++)
if(a.value[order[i]]!=b.value[order[i]]){
result->value= (a.value[order[i]]<b.value[order[i]]);
return true;
}
result->value= (a.value[order[i]]<=b.value[order[i]]);
return true;
case TYPE_GT:
for(i= 0;i<5;i++)
if(a.value[order[i]]!=b.value[order[i]]){
result->value= (a.value[order[i]]> b.value[order[i]]);
return true;
}
result->value= (a.value[order[i]]> b.value[order[i]]);
return true;
case TYPE_GEQ:
for(i= 0;i<5;i++)
if(a.value[order[i]]!=b.value[order[i]]){
result->value= (a.value[order[i]]> b.value[order[i]]);
return true;
}
result->value= (a.value[order[i]]>=b.value[order[i]]);
return true;
case TYPE_ASSIGNMENT:
for(i= 0;i<5;i++)
if(a.value[order[i]]!=b.value[order[i]]){
result->value= false;
return true;
}
result->value= (a.value[order[i]]==b.value[order[i]]);
return true;
case TYPE_NEQ:
for(i= 0;i<5;i++)
if(a.value[order[i]]!=b.value[order[i]]){
result->value= true;
return true;
}
result->value= (a.value[order[i]]!=b.value[order[i]]);
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
}
return true;
}
}
/*:445*//*449:*/
#line 11608 "weaver-interface-metafont_en.tex"

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
if(!eval_boolean_tertiary(mf,cx,begin_expression,
before_last_operator,&a))
return false;
if(!eval_boolean_secondary(mf,cx,last_operator->next,
end_expression,&b))
return false;
result->value= (a.value||b.value);
return true;
}
}
/*:449*//*451:*/
#line 11675 "weaver-interface-metafont_en.tex"

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
/*:451*//*455:*/
#line 11766 "weaver-interface-metafont_en.tex"

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
/*:455*//*457:*/
#line 11937 "weaver-interface-metafont_en.tex"

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
/*:457*//*458:*/
#line 12051 "weaver-interface-metafont_en.tex"

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
/*:458*//*459:*/
#line 12126 "weaver-interface-metafont_en.tex"

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
t->type==TYPE_NEQ)
return TYPE_T_BOOLEAN;
if(t->type==TYPE_PYTHAGOREAN_SUM||
t->type==TYPE_PYTHAGOREAN_SUBTRACT)
return TYPE_T_NUMERIC;
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
/*:459*//*473:*/
#line 12635 "weaver-interface-metafont_en.tex"

void pencircle_extremity_points(struct metafont*mf,float*matrix){
DECLARE_PEN_EXTREMITIES();
int i,index[4]= {0,3,4,1};
for(i= 0;i<2;i++){

if((i==0&&matrix[3]==0.0)||
(i==1&&matrix[4]==0.0)){
CHECK_PEN_EXTREMITIES(-0.5,0.0,matrix);
CHECK_PEN_EXTREMITIES(0.5,0.0,matrix);
}
else if((i==0&&matrix[0]==0.0)||
(i==1&&matrix[1]==0.0)){
CHECK_PEN_EXTREMITIES(0.0,0.5,matrix);
CHECK_PEN_EXTREMITIES(0.0,-0.5,matrix);
}
else{

float x0= INFINITY,x1= 0.0;
do{
x0= x1;
x1= x0-((matrix[index[2*i]]+(matrix[index[2*i+1]]*
x0/sqrt(0.25-x0*x0)))/
(matrix[index[2*i+1]]*sqrt(0.25-x0*x0)+
((matrix[index[2*i+1]]*x0*x0)/
(sqrt(0.25-x0*x0)))));
if(x1<=-0.5||x1>=0.5){

float y1;
x0= -0.5;
x1= 0.5;
y1= matrix[2*i]+(matrix[index[2*i]]*x1/sqrt(0.25-x1*x1));
while(x0!=x1){
float x2= (x0+x1)/2;
float y2= matrix[index[2*i]]+
(matrix[index[2*i+1]]*x2/sqrt(0.25-x2*x2));
if(y2==0.0)
x0= x1= x2;
else if(y2> 0){
if(y1> 0)
x1= x2;
else
x0= x2;
}
else{
if(y1> 0)
x0= x2;
else
x1= x2;
}
}
}
}while(x0!=x1);
if(i==0){
CHECK_PEN_EXTREMITIES(x0,sqrt(0.25-x0*x0),matrix);
CHECK_PEN_EXTREMITIES(x0,-sqrt(0.25-x0*x0),matrix);
CHECK_PEN_EXTREMITIES(-x0,sqrt(0.25-x0*x0),matrix);
CHECK_PEN_EXTREMITIES(-x0,-sqrt(0.25-x0*x0),matrix);
}
else{
CHECK_PEN_EXTREMITIES(sqrt(0.25-x0*x0),x0,matrix);
CHECK_PEN_EXTREMITIES(-sqrt(0.25-x0*x0),x0,matrix);
CHECK_PEN_EXTREMITIES(sqrt(0.25-x0*x0),-x0,matrix);
CHECK_PEN_EXTREMITIES(-sqrt(0.25-x0*x0),-x0,matrix);
}
}
}
UPDATE_PEN_EXTREMITIES();
}
/*:473*//*475:*/
#line 12742 "weaver-interface-metafont_en.tex"

void path_extremity_points(struct metafont*mf,struct path_variable*p,
float*matrix){
int i,j,length= p->length;
DECLARE_PEN_EXTREMITIES();
for(i= 0;i<length;i++){
float x0,y0,u_x,u_y,v_x,v_y,x1,y1;
CHECK_PEN_EXTREMITIES(p->points[i].x,p->points[i].y,matrix);
x0= LINEAR_TRANSFORM_X(p->points[i].x,p->points[i].y,matrix);
y0= LINEAR_TRANSFORM_Y(p->points[i].x,p->points[i].y,matrix);
u_x= LINEAR_TRANSFORM_X(p->points[i].u_x,p->points[i].u_y,matrix);
u_y= LINEAR_TRANSFORM_Y(p->points[i].u_x,p->points[i].u_y,matrix);
v_x= LINEAR_TRANSFORM_X(p->points[i].v_x,p->points[i].v_y,matrix);
v_y= LINEAR_TRANSFORM_Y(p->points[i].v_x,p->points[i].v_y,matrix);
x1= LINEAR_TRANSFORM_X(p->points[(i+1)%length].x,p->points[i].y,
matrix);
y1= LINEAR_TRANSFORM_Y(p->points[(i+1)%length].y,p->points[i].y,
matrix);

float a,b,c,deltah,t;
a= (-3*x0+9*u_x-9*v_x+3*x1);
b= (6*x0-12*u_x+6*v_x);
c= (-3*x0+3*u_x);
deltah= b*b-4*a*c;
for(j= -1;j<2;j+= 2){
t= (-b+j*sqrt(deltah))/(2*a);
if(t> 0.0&&t<1.0){
float x,y;
x= (1-t)*(1-t)*(1-t)*x0+3*(1-t)*(1-t)*t*u_x+3*(1-t)*t*t*v_x+
t*t*t*x1;
y= (1-t)*(1-t)*(1-t)*y0+3*(1-t)*(1-t)*t*u_y+3*(1-t)*t*t*v_y+
t*t*t*y1;
CHECK_PEN_EXTREMITIES_I(x,y);
}
}

a= (-3*y0+9*u_y-9*v_y+3*y1);
b= (6*y0-12*u_y+6*v_y);
c= (-3*y0+3*u_y);
deltah= b*b-4*a*c;
for(j= -1;j<2;j+= 2){
t= (-b+j*sqrt(b*b-4*a*c))/(2*a);
if(t> 0.0&&t<1.0){
float x,y;
x= (1-t)*(1-t)*(1-t)*x0+3*(1-t)*(1-t)*t*u_x+3*(1-t)*t*t*v_x+
t*t*t*x1;
y= (1-t)*(1-t)*(1-t)*y0+3*(1-t)*(1-t)*t*u_y+3*(1-t)*t*t*v_y+
t*t*t*y1;
CHECK_PEN_EXTREMITIES_I(x,y);
}
}
}
UPDATE_PEN_EXTREMITIES();
}
/*:475*//*478:*/
#line 12857 "weaver-interface-metafont_en.tex"

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
/*:478*//*480:*/
#line 12910 "weaver-interface-metafont_en.tex"

bool triangulate_pen(struct metafont*mf,struct pen_variable*pen,
float*transform_matrix){
/*481:*/
#line 12930 "weaver-interface-metafont_en.tex"

if((pen->flags&FLAG_NULL)){
pen->indices= 0;
DECLARE_PEN_EXTREMITIES();
CHECK_PEN_EXTREMITIES(0,0,transform_matrix);
UPDATE_PEN_EXTREMITIES();
return true;
}
/*:481*/
#line 12913 "weaver-interface-metafont_en.tex"

/*485:*/
#line 12982 "weaver-interface-metafont_en.tex"

if((pen->flags&FLAG_SQUARE)){
float square_vertices[8]= {-0.5,-0.5,0.5,-0.5,0.5,0.5,-0.5,0.5};
pen->indices= 4;
DECLARE_PEN_EXTREMITIES();
int i;
for(i= 0;i<4;i++)
CHECK_PEN_EXTREMITIES(square_vertices[2*i],square_vertices[2*i+1],
transform_matrix);
UPDATE_PEN_EXTREMITIES();
return true;
}
/*:485*/
#line 12914 "weaver-interface-metafont_en.tex"

/*486:*/
#line 13010 "weaver-interface-metafont_en.tex"

if((pen->flags&FLAG_STRAIGHT)&&(pen->flags&FLAG_CONVEX)){
int i,index,increment;
DECLARE_PEN_EXTREMITIES();
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
CHECK_PEN_EXTREMITIES(data[2*i],data[2*i+1],transform_matrix);
index+= increment;
}
if(pen->gl_vbo==0){
glGenBuffers(1,&(pen->gl_vbo));
glBindBuffer(GL_ARRAY_BUFFER,pen->gl_vbo);
glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
pen->indices= pen->format->length;
}
if(temporary_free!=NULL)
temporary_free(data);
UPDATE_PEN_EXTREMITIES();
return true;
}
/*:486*/
#line 12915 "weaver-interface-metafont_en.tex"

/*487:*/
#line 13086 "weaver-interface-metafont_en.tex"

if((pen->flags&FLAG_CIRCULAR)){
float radius;

pencircle_extremity_points(mf,transform_matrix);

{
float side1,side2;
side1= abs(mf->pen_rt-mf->pen_lft);
side2= abs(mf->pen_top-mf->pen_bot);
radius= ((side1>=side2)?(side1):(side2))/2.0;
}

if(pen->gl_vbo!=0){
if(radius> pen->triang_resolution)
glDeleteBuffers(1,&(pen->gl_vbo));
else
return true;
}
pen->triang_resolution= radius;
GLsizei size= sizeof(float)*2*(((int)(2*M_PI*radius))+4);
float*data= (float*)temporary_alloc(size);
if(data==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: Not enough memory.\n");
#endif
return false;
}
{
int i;
float angle= 0.0;
data[0]= 0.0;
data[1]= 0.0;
for(i= 2;i<(size/sizeof(float));i++){
data[i]= 0.5*sin(angle);
i++;
data[i]= 0.5*cos(angle);
angle+= 1/radius;
}
}
glGenBuffers(1,&(pen->gl_vbo));
glBindBuffer(GL_ARRAY_BUFFER,pen->gl_vbo);
glBufferData(GL_ARRAY_BUFFER,size,data,GL_STATIC_DRAW);
pen->indices= (size/(2*sizeof(float)));
if(temporary_free!=NULL)
temporary_free(data);
return true;
}
/*:487*/
#line 12916 "weaver-interface-metafont_en.tex"

/*488:*/
#line 13181 "weaver-interface-metafont_en.tex"

if((pen->flags&FLAG_CONVEX)){
bool counterclockwise= is_pen_counterclockwise(pen);
int i,number_of_vertices= 1;

path_extremity_points(mf,pen->format,transform_matrix);
for(i= 0;i<pen->format->length-1;i++){
int distance= 0;
float x0,y0,u_x,u_y,v_x,v_y,x1,y1;
float dx,dy;
x0= LINEAR_TRANSFORM_X(pen->format->points[i].x,
pen->format->points[i].y,transform_matrix);
y0= LINEAR_TRANSFORM_Y(pen->format->points[i].x,
pen->format->points[i].y,transform_matrix);
u_x= LINEAR_TRANSFORM_X(pen->format->points[i].u_x,
pen->format->points[i].u_y,transform_matrix);
u_y= LINEAR_TRANSFORM_Y(pen->format->points[i].u_x,
pen->format->points[i].u_y,transform_matrix);
dx= u_x-x0;
dy= u_y-y0;
distance+= (int)round(sqrt(dx*dx+dy*dy));
v_x= LINEAR_TRANSFORM_X(pen->format->points[i].v_x,
pen->format->points[i].v_y,transform_matrix);
v_y= LINEAR_TRANSFORM_Y(pen->format->points[i].v_x,
pen->format->points[i].v_y,transform_matrix);
dx= v_x-u_x;
dy= v_y-u_y;
distance+= (int)round(sqrt(dx*dx+dy*dy));
x1= LINEAR_TRANSFORM_X(pen->format->points[i+1].x,
pen->format->points[i+1].y,
transform_matrix);
y1= LINEAR_TRANSFORM_Y(pen->format->points[i+1].x,
pen->format->points[i+1].y,
transform_matrix);
dx= x1-v_x;
dy= y1-v_y;
distance+= (int)round(sqrt(dx*dx+dy*dy));
dx= x1-x0;
dy= y1-y0;
if(distance==(int)round(sqrt(dx*dx+dy*dy)))
number_of_vertices++;
else
number_of_vertices+= distance;
}
if(pen->gl_vbo!=0){
if(number_of_vertices<=pen->triang_resolution)
return true;
else
glDeleteBuffers(1,&(pen->gl_vbo));
}
pen->triang_resolution= number_of_vertices;
float*data= (float*)temporary_alloc(number_of_vertices*2*
sizeof(float));
if(data==NULL){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: Not enough memory.\n");
#endif
return false;
}
{
struct path_points*p0,*p1;
int v;
if(counterclockwise)
p0= &(pen->format->points[0]);
else
p0= &(pen->format->points[pen->format->length-1]);
data[0]= p0->x;
data[1]= p0->y;
v= 2;
for(i= 0;i<pen->format->length-1;i++){
float b_x,b_y,c_x,c_y,dx,dy,x0,y0,x1,x2,y1,y2;
int distance= 0;
if(counterclockwise){
p1= &(pen->format->points[1+i]);
b_x= p0->u_x;
b_y= p0->u_y;
c_x= p0->v_x;
c_y= p0->v_y;
}
else{
p1= &(pen->format->points[pen->format->length-2-i]);
b_x= p1->v_x;
b_y= p1->v_y;
c_x= p1->u_x;
c_y= p1->u_y;
}
x0= LINEAR_TRANSFORM_X(p0->x,p0->y,transform_matrix);
y0= LINEAR_TRANSFORM_Y(p0->x,p0->y,transform_matrix);
x2= LINEAR_TRANSFORM_X(b_x,b_y,transform_matrix);
y2= LINEAR_TRANSFORM_Y(b_x,b_y,transform_matrix);
dx= x2-x0;
dy= y2-y0;
distance+= (int)round(sqrt(dx*dx+dy*dy));
x1= x2;
y1= y2;
x2= LINEAR_TRANSFORM_X(c_x,c_y,transform_matrix);
y2= LINEAR_TRANSFORM_Y(c_x,c_y,transform_matrix);
dx= x2-x1;
dy= y2-y1;
distance+= (int)round(sqrt(dx*dx+dy*dy));
x1= x2;
y1= y2;
x2= LINEAR_TRANSFORM_X(p1->x,p1->y,transform_matrix);
y2= LINEAR_TRANSFORM_Y(p1->x,p1->y,transform_matrix);
dx= x2-x1;
dy= y2-y1;
distance+= (int)round(sqrt(dx*dx+dy*dy));
dx= x2-x0;
dy= y2-y0;
if(distance==(int)round(sqrt(dx*dx+dy*dy))){
data[v++]= p1->x;
data[v++]= p1->y;
}
else{
int j;
float dt= 1.0/((float)distance);
for(j= 1;j<=distance;j++){
float t= dt*j;
data[v++]= (1-t)*(1-t)*(1-t)*p0->x+3*(1-t)*(1-t)*t*b_x+
3*(1-t)*t*t*c_x+t*t*t*p1->x;
data[v++]= (1-t)*(1-t)*(1-t)*p0->y+3*(1-t)*(1-t)*t*b_y+
3*(1-t)*t*t*c_y+t*t*t*p1->y;
}
}
p0= p1;
}
}
glGenBuffers(1,&(pen->gl_vbo));
glBindBuffer(GL_ARRAY_BUFFER,pen->gl_vbo);
glBufferData(GL_ARRAY_BUFFER,number_of_vertices*2*
sizeof(float),data,GL_STATIC_DRAW);
pen->indices= number_of_vertices;
if(temporary_free!=NULL)
temporary_free(data);
return true;
}
/*:488*/
#line 12917 "weaver-interface-metafont_en.tex"

/*489:*/
#line 13324 "weaver-interface-metafont_en.tex"

if(!(pen->flags&FLAG_CONVEX)){
#if defined(W_DEBUG_METAFONT)
fprintf(stderr,"METAFONT: Error: Concave pens still not supported.\n");
#endif
return false;
}
return false;
/*:489*/
#line 12918 "weaver-interface-metafont_en.tex"

}
/*:480*//*516:*/
#line 14103 "weaver-interface-metafont_en.tex"

void drawpoint(struct metafont*mf,struct pen_variable*pen,
struct picture_variable*pic,float x,float y,float*matrix,
bool erasing){
float gl_matrix[9];
gl_matrix[0]= (2*matrix[0])/pic->width;
gl_matrix[1]= (2*matrix[1])/pic->height;
gl_matrix[2]= 0.0;
gl_matrix[3]= (2*matrix[3])/pic->width;
gl_matrix[4]= (2*matrix[4])/pic->height;
gl_matrix[5]= 0.0;
gl_matrix[6]= 2*(matrix[6]+x)/pic->width-1.0;
gl_matrix[7]= 2*(matrix[7]+mf->current_depth+y)/pic->width-
1.0;
gl_matrix[8]= 1.0;
glViewport(0,0,pic->width,pic->height);


if(pen->flags&FLAG_SQUARE)
glBindBuffer(GL_ARRAY_BUFFER,pensquare_vbo);
else
glBindBuffer(GL_ARRAY_BUFFER,pen->gl_vbo);
glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
if(erasing){
glUseProgram(pen_erase_program);
glUniformMatrix3fv(pen_erase_uniform_matrix,1,true,gl_matrix);
glUniform4f(pen_erase_uniform_color,0.0,0.0,0.0,1.0);
}
else{
glUseProgram(pen_program);
glUniformMatrix3fv(pen_uniform_matrix,1,true,gl_matrix);
glUniform4f(pen_uniform_color,0.0,0.0,0.0,1.0);
}
glEnableVertexAttribArray(0);
glDrawArrays(GL_TRIANGLE_FAN,0,pen->indices);
}
/*:516*/
#line 220 "weaver-interface-metafont_en.tex"

/*19:*/
#line 489 "weaver-interface-metafont_en.tex"

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
/*391:*/
#line 9814 "weaver-interface-metafont_en.tex"

glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);

glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
/*:391*//*397:*/
#line 9941 "weaver-interface-metafont_en.tex"

{
program= compile_shader_program(vertex_shader,fragment_shader);
uniform_matrix= glGetUniformLocation(program,"model_view_matrix");
uniform_texture= glGetUniformLocation(program,"texture1");
}
/*:397*//*408:*/
#line 10253 "weaver-interface-metafont_en.tex"

{
inv_program= compile_shader_program(vertex_shader,fragment_shader_inverse);
uniform_inv_matrix= glGetUniformLocation(program,"model_view_matrix");
uniform_inv_texture= glGetUniformLocation(program,"texture1");
}
/*:408*//*483:*/
#line 12955 "weaver-interface-metafont_en.tex"

{
float square_vertices[8]= {-0.5,-0.5,
+0.5,-0.5,
+0.5,+0.5,
-0.5,+0.5};
glGenBuffers(1,&pensquare_vbo);
glBindBuffer(GL_ARRAY_BUFFER,pensquare_vbo);
glBufferData(GL_ARRAY_BUFFER,8*sizeof(float),square_vertices,
GL_STATIC_DRAW);
}
/*:483*//*502:*/
#line 13748 "weaver-interface-metafont_en.tex"

currentpicture_fb= 0;
/*:502*//*510:*/
#line 13894 "weaver-interface-metafont_en.tex"

{
pen_program= compile_shader_program(pen_vertex_shader,pen_fragment_shader);
pen_uniform_matrix= glGetUniformLocation(pen_program,"model_view_matrix");
pen_uniform_color= glGetUniformLocation(pen_program,"color");
pen_erase_program= compile_shader_program(pen_vertex_shader,
pen_erase_fragment_shader);
pen_erase_uniform_matrix= glGetUniformLocation(pen_erase_program,
"model_view_matrix");
pen_erase_uniform_color= glGetUniformLocation(pen_erase_program,"color");
}
/*:510*/
#line 501 "weaver-interface-metafont_en.tex"

return true;
}
/*:19*//*20:*/
#line 512 "weaver-interface-metafont_en.tex"

void _Wfinish_metafont(void){
/*392:*/
#line 9825 "weaver-interface-metafont_en.tex"

glDeleteBuffers(1,&vbo);
/*:392*//*398:*/
#line 9953 "weaver-interface-metafont_en.tex"

glDeleteProgram(program);
/*:398*//*409:*/
#line 10265 "weaver-interface-metafont_en.tex"

glDeleteProgram(inv_program);
/*:409*//*511:*/
#line 13911 "weaver-interface-metafont_en.tex"

glDeleteProgram(pen_program);
glDeleteProgram(pen_erase_program);
/*:511*/
#line 514 "weaver-interface-metafont_en.tex"

}
/*:20*/
#line 221 "weaver-interface-metafont_en.tex"

/*:7*/
