/*8:*/
#line 517 "weaver-interface-metafont.cweb"

#include "metafont.h"
/*42:*/
#line 1359 "weaver-interface-metafont.cweb"

#include <stdio.h> 
/*:42*//*44:*/
#line 1379 "weaver-interface-metafont.cweb"

#include <ctype.h> 
/*:44*//*64:*/
#line 1789 "weaver-interface-metafont.cweb"

#include <string.h> 
/*:64*//*118:*/
#line 3170 "weaver-interface-metafont.cweb"

#include <math.h> 
/*:118*//*147:*/
#line 3828 "weaver-interface-metafont.cweb"

#include <complex.h> 
/*:147*//*177:*/
#line 4864 "weaver-interface-metafont.cweb"

struct pen_variable;
/*:177*//*660:*/
#line 18628 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 18632 "weaver-interface-metafont.cweb"
/*:660*//*694:*/
#line 19287 "weaver-interface-metafont.cweb"

#include <errno.h> 
/*:694*/
#line 519 "weaver-interface-metafont.cweb"

/*9:*/
#line 554 "weaver-interface-metafont.cweb"

#define INITIALIZE_IDENTITY_MATRIX(I) {\
  int _i;\
  for(_i =  0; _i < 9; _i++)\
    I[_i] =  ((_i%4)?(0.0):(1.0));\
}
/*:9*//*10:*/
#line 582 "weaver-interface-metafont.cweb"

#define LINEAR_TRANSFORM_X(x, y, M) (x * M[0] + y * M[3] + M[6])
#define LINEAR_TRANSFORM_Y(x, y, M) (x * M[1] + y * M[4] + M[7])
/*:10*//*11:*/
#line 601 "weaver-interface-metafont.cweb"

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
/*:11*//*12:*/
#line 629 "weaver-interface-metafont.cweb"

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
/*:12*//*13:*/
#line 656 "weaver-interface-metafont.cweb"

#define TRANSFORM_SCALE_X(M, s) {\
  M[0] =  M[0] * s;\
  M[3] =  M[3] * s;\
  M[6] =  M[6] * s;\
}
/*:13*//*14:*/
#line 673 "weaver-interface-metafont.cweb"

#define TRANSFORM_SCALE_Y(M, s) {\
  M[1] =  M[1] * s;\
  M[4] =  M[4] * s;\
  M[7] =  M[7] * s;\
}
/*:14*//*15:*/
#line 684 "weaver-interface-metafont.cweb"

#define TRANSFORM_SCALE(M, s) {\
  TRANSFORM_SCALE_X(M, s);\
  TRANSFORM_SCALE_Y(M, s);\
}
/*:15*//*16:*/
#line 703 "weaver-interface-metafont.cweb"

#define TRANSFORM_SHIFT(M, a, b) {\
  M[6] =  M[6] + a;\
  M[7] =  M[7] + b;\
}
/*:16*//*17:*/
#line 719 "weaver-interface-metafont.cweb"

#define TRANSFORM_SLANT(M, s) {\
  M[0] =  M[0] + s * M[1];\
  M[3] =  M[3] + s * M[4];\
  M[6] =  M[6] + s * M[7];\
}
/*:17*//*18:*/
#line 740 "weaver-interface-metafont.cweb"

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
/*:18*//*20:*/
#line 803 "weaver-interface-metafont.cweb"

#define EXCHANGE_ROWS(n, M, b, i, j) {\
  if(i != j){\
   int _k;\
   double _tmp;\
   _tmp =  b[i];\
   b[i] =  b[j];\
   b[j] =  _tmp;\
   for(_k =  0; _k < n; _k++){\
       _tmp =  m[i*n+_k];\
       m[i*n+_k] =  m[j*n+_k];\
       m[j*n+_k] =  _tmp;}}}
/*:20*//*21:*/
#line 835 "weaver-interface-metafont.cweb"

#define SUB_MUL_LINES(n, m, b, i, j, q) {\
  int _k;\
  b[i] -=  (q * b[j]);\
  for(_k =  0; _k < n; _k++){\
      m[i*n+_k] -=  (q * m[j*n+_k]);}}
/*:21*//*25:*/
#line 963 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
#define MUTEX_INIT(mutex) InitializeCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 967 "weaver-interface-metafont.cweb"
#define MUTEX_INIT(mutex) pthread_mutex_init(&mutex, NULL);
#elif defined(__EMSCRIPTEN__)
#line 969 "weaver-interface-metafont.cweb"
#define MUTEX_INIT(mutex)
#endif
#line 971 "weaver-interface-metafont.cweb"
/*:25*//*26:*/
#line 976 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
#define MUTEX_DESTROY(mutex) DeleteCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 980 "weaver-interface-metafont.cweb"
#define MUTEX_DESTROY(mutex) pthread_mutex_destroy(&mutex);
#elif defined(__EMSCRIPTEN__)
#line 982 "weaver-interface-metafont.cweb"
#define MUTEX_DESTROY(mutex)
#endif
#line 984 "weaver-interface-metafont.cweb"
/*:26*//*27:*/
#line 991 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
#define MUTEX_WAIT(mutex) EnterCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 995 "weaver-interface-metafont.cweb"
#define MUTEX_WAIT(mutex) pthread_mutex_lock(&mutex);
#elif defined(__EMSCRIPTEN__)
#line 997 "weaver-interface-metafont.cweb"
#define MUTEX_WAIT(mutex)
#endif
#line 999 "weaver-interface-metafont.cweb"
/*:27*//*28:*/
#line 1004 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
#define MUTEX_SIGNAL(mutex) LeaveCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 1008 "weaver-interface-metafont.cweb"
#define MUTEX_SIGNAL(mutex) pthread_mutex_unlock(&mutex);
#elif defined(__EMSCRIPTEN__)
#line 1010 "weaver-interface-metafont.cweb"
#define MUTEX_SIGNAL(mutex)
#endif
#line 1012 "weaver-interface-metafont.cweb"
/*:28*//*123:*/
#line 3263 "weaver-interface-metafont.cweb"

#define INTERNAL_NUMERIC_PT   0
#define INTERNAL_NUMERIC_CM   1
#define INTERNAL_NUMERIC_MM   2
#define INTERNAL_NUMERIC_R    3
#define INTERNAL_NUMERIC_G    4
#define INTERNAL_NUMERIC_B    5
#define INTERNAL_NUMERIC_A    6
#define INTERNAL_NUMERIC_MONO 7
#define INTERNAL_NUMERIC_W    0
#define INTERNAL_NUMERIC_H    1
#define INTERNAL_NUMERIC_D    2
/*:123*//*134:*/
#line 3443 "weaver-interface-metafont.cweb"

#define INTERNAL_TRANSFORM_IDENTITY 0
/*:134*//*137:*/
#line 3492 "weaver-interface-metafont.cweb"

#define UNINITIALIZED_FORMAT 0 
#define PROVISIONAL_FORMAT   1 
#define SUBPATH_FORMAT       2 
#define FINAL_FORMAT         3 
/*:137*//*179:*/
#line 4910 "weaver-interface-metafont.cweb"

#define FLAG_CONVEX        1
#define FLAG_STRAIGHT      2
#define FLAG_CIRCULAR      4
#define FLAG_SEMICIRCULAR  8
#define FLAG_SQUARE       16
#define FLAG_NULL         32

/*:179*//*187:*/
#line 5093 "weaver-interface-metafont.cweb"

#define INTERNAL_PEN_PENSQUARE  0
/*:187*//*209:*/
#line 5508 "weaver-interface-metafont.cweb"

#define DECLARE_NESTING_CONTROL() int nesting_parenthesis =  0, \
                                      nesting_brackets =  0, \
                                      nesting_braces =  0;
#define COUNT_NESTING(p) \
  {if(p -> type == TYPE_OPEN_PARENTHESIS){         \
    nesting_parenthesis ++;                       \
  } else if(p -> type == TYPE_CLOSE_PARENTHESIS){ \
    nesting_parenthesis --;                       \
  } else if(p -> type == TYPE_OPEN_BRACKETS){     \
    nesting_brackets ++;                          \
  } else if(p -> type == TYPE_CLOSE_BRACKETS){    \
    nesting_brackets --;                          \
  } else if(p -> type == TYPE_OPEN_BRACES){       \
    nesting_braces ++;                            \
  } else if(p -> type == TYPE_CLOSE_BRACES){      \
    nesting_braces --;\
  }}
#define IS_NOT_NESTED() (nesting_parenthesis == 0 && nesting_brackets == 0 && \
                         nesting_braces == 0)
#define RESET_NESTING_COUNT() nesting_parenthesis =  0; \
                              nesting_brackets =  0; \
                              nesting_braces =  0;
/*:209*//*210:*/
#line 5538 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf, cx, line) {\
  if(nesting_parenthesis >  0){\
    RAISE_ERROR_UNCLOSED_DELIMITER(mf, cx, line, '(');\
    return false;\
  } else if(nesting_parenthesis < 0){\
    RAISE_ERROR_UNOPENED_DELIMITER(mf, cx, line, ')');\
    return false;\
  } else if(nesting_brackets >  0){\
    RAISE_ERROR_UNCLOSED_DELIMITER(mf, cx, line, '[');\
    return false;\
  } else if(nesting_brackets < 0){\
    RAISE_ERROR_UNOPENED_DELIMITER(mf, cx, line, ']');\
    return false;\
  } else if(nesting_braces >  0){\
    RAISE_ERROR_UNCLOSED_DELIMITER(mf, cx, line, '{');\
    return false;\
  } else if(nesting_braces < 0){\
    RAISE_ERROR_UNOPENED_DELIMITER(mf, cx, line, '}');\
    return false;}}
/*:210*//*211:*/
#line 5605 "weaver-interface-metafont.cweb"

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
/*:211*//*505:*/
#line 13606 "weaver-interface-metafont.cweb"

#define DECLARE_PEN_EXTREMITIES() float _max_x =  -INFINITY, _min_x =  INFINITY,\
                                  _max_y =  -INFINITY, _min_y =  INFINITY;
/*:505*//*506:*/
#line 13616 "weaver-interface-metafont.cweb"

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
/*:506*//*507:*/
#line 13638 "weaver-interface-metafont.cweb"

#define UPDATE_PEN_EXTREMITIES() {\
  cx -> pen_lft =  _min_x;\
  cx -> pen_rt =  _max_x;\
  cx -> pen_top =  _max_y;\
  cx -> pen_bot =  _min_y;\
}
/*:507*//*512:*/
#line 13973 "weaver-interface-metafont.cweb"

#define FLAG_ORIENTATION      64
#define FLAG_COUNTERCLOCKWISE 128
/*:512*//*537:*/
#line 14994 "weaver-interface-metafont.cweb"

#define ADD_DIAGONAL(data, v1, v2) \
        if(v1 -> prev == v2 -> next){\
          ADD_TRIANGLE(data, v1 -> x, v1 -> y, v2 -> x, v2 -> y,\
                       v1 -> prev -> x, v1 -> prev -> y);\
          v1 -> prev =  v2;\
          if(v1 -> succ == v2 -> next) v1 -> succ =  v1 -> succ -> succ;\
          DESTROY_POLYGON_VERTEX(v2 -> next);\
          v2 -> next =  v1;\
        }\
        else if(v1 -> next == v2 -> prev){\
          ADD_TRIANGLE(data, v1 -> x, v1 -> y, v2 -> x, v2 -> y,\
                       v1 -> next -> x, v1 -> next -> y);\
          v1 -> next =  v2;\
          if(v1 -> succ == v2 -> prev) v1 -> succ =  v1 -> succ -> succ;\
          DESTROY_POLYGON_VERTEX(v2 -> prev);\
          v2 -> prev =  v1;\
        }\
        else printf("WARNING (%d): This should not happen (%p<-v1->%p)(%p<-v2->%p)!\n", __LINE__, v1->prev, v1->next,v2->prev,v2->next);
/*:537*//*538:*/
#line 15021 "weaver-interface-metafont.cweb"

#define ADD_TRIANGLE(data, x1, y1, x2, y2, x3, y3) \
  if(x1*y2+y1*x3+x2*y3-x3*y2-x2*y1-x1*y3 >  0){\
    data[0] =  x1; data[1] =  y1;\
    data[2] =  x2; data[3] =  y2;\
    data[4] =  x3; data[5] =  y3;\
  } else{\
    data[0] =  x1; data[1] =  y1;\
    data[2] =  x3; data[3] =  y3;\
    data[4] =  x2; data[5] =  y2;\
  }\
  (*number_of_triangles) ++;\
  data +=  6;
/*:538*//*539:*/
#line 15043 "weaver-interface-metafont.cweb"

#define COMMON_VERTEX(v1, v2) ((v1 -> next == v2 -> prev)?\
                               (v1 -> next):(v1 -> prev))
#define IS_DIAGONAL_INSIDE(v1, v2)\
  ((v1 -> y != v2 -> y) && \
   (((v1 -> flag & FLAG_UPPER) && \
     (COMMON_VERTEX(v1, v2)->x)*(v2->x-v1->x)/(v2->y-v1->y)+v1->y < \
      COMMON_VERTEX(v1,v2)->y)\
    ||\
   ((v1 -> flag & FLAG_LOWER) && \
    (COMMON_VERTEX(v1, v2)->x)*(v2->x-v1->x)/(v2->y-v1->y)+v1->y >  \
     COMMON_VERTEX(v1,v2)->y)))
/*:539*//*562:*/
#line 15803 "weaver-interface-metafont.cweb"

#define ADD_CUT(v1, v2) {                                    \
  if(last_diagonal == NULL){                                 \
    last_diagonal =  list_of_diagonals =  NEW_POLYGON_VERTEX();\
  } else{                                                    \
    last_diagonal -> succ =  NEW_POLYGON_VERTEX();            \
    last_diagonal =  last_diagonal -> succ;                   \
  }                                                          \
  if(last_diagonal == NULL){                                 \
    RAISE_ERROR_NO_MEMORY(mf, NULL, 0);                      \
    return false;                                            \
  }                                                          \
  last_diagonal -> prev =  v1;                                \
  last_diagonal -> next =  v2;                                \
  last_diagonal -> succ =  NULL;}
/*:562*//*668:*/
#line 18886 "weaver-interface-metafont.cweb"

#define RAISE_GENERIC_ERROR(mf, cx, line, error_code) {\
  struct context *_cx =  cx;\
  if(!mf -> err){\
    mf -> err =  error_code;\
    mf -> errno_line =  line;\
    if(cx != NULL && _cx -> current_character[0] != '\0')\
      memcpy(mf -> errno_character, _cx -> current_character, 5);}}
/*:668*//*669:*/
#line 18900 "weaver-interface-metafont.cweb"

#if defined(W_DEBUG_METAFONT)
#define OPTIONAL(x) x
#else
#line 18904 "weaver-interface-metafont.cweb"
#define OPTIONAL(x) 0
#endif
#line 18906 "weaver-interface-metafont.cweb"
/*:669*//*677:*/
#line 19095 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_DISCONTINUOUS_PATH(mf, cx, line, x1, y1, x2, y2) {\
  if(!mf -> err){\
    float *buffer =  (float *) (mf -> errno_str);\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_DISCONTINUOUS_PATH);\
    buffer[0] =  (float) (x1);\
    buffer[1] =  (float) (y1);\
    buffer[2] =  (float) (x2);\
    buffer[3] =  (float) (y2);}}
/*:677*//*680:*/
#line 19128 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_DIVISION_BY_ZERO(mf, cx, line) {\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_DIVISION_BY_ZERO);}
/*:680*//*683:*/
#line 19152 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_DUPLICATE_GLYPH(mf, cx, line, glyph) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_DUPLICATE_GLYPH);\
    memcpy(mf -> errno_str, glyph, 4);\
    mf -> errno_str[4] =  '\0';}}
/*:683*//*686:*/
#line 19196 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_EMPTY_DELIMITER(mf, cx, line, delimiter) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_EMPTY_DELIMITER);\
    mf -> errno_int =  delimiter;}}
/*:686*//*689:*/
#line 19229 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_EXPECTED_FOUND(mf, cx, line, expected, found) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_EXPECTED_FOUND);\
    mf -> errno_int =  expected;\
    token_to_string(found, mf -> errno_str);}}
/*:689*//*692:*/
#line 19262 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_FAILED_OPENING_FILE(mf, cx, line, str) {\
  if(!mf -> err){\
    size_t _len =  strlen(str) + 1;\
    if(_len >  32) _len =  32;\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_FAILED_OPENING_FILE);\
    mf -> errno_int =  errno;\
    memcpy(mf -> errno_str, str, _len);\
    mf -> errno_str[31] =  '\0';}}
/*:692*//*696:*/
#line 19305 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_INCOMPLETE_SOURCE(mf, cx, line) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INCOMPLETE_SOURCE);}}
/*:696*//*699:*/
#line 19335 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_INCOMPLETE_STATEMENT(mf, cx, line) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INCOMPLETE_STATEMENT);}}
/*:699*//*702:*/
#line 19392 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_INVALID_CHAR(mf, cx, line, str) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_CHAR);\
    memcpy(mf -> errno_str, str, 4);\
    mf -> errno_str[4] =  '\0';}}
/*:702*//*705:*/
#line 19470 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_INVALID_COMPARISON(mf, cx, line, operator, type) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_COMPARISON);\
    token_to_string(operator, mf -> errno_str);\
    mf -> errno_int =  type;}}
/*:705*//*708:*/
#line 19504 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_INVALID_DIMENSION_GLYPH(mf, cx, line, width, height) {\
  if(!mf -> err){\
    int *buffer =  (int *) (mf -> errno_str);\
    buffer[0] =  (int) width;\
    buffer[1] =  (int) height;\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_DIMENSION_GLYPH);}}
/*:708*//*711:*/
#line 19545 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_INVALID_NAME(mf, cx, line, tok, type) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_NAME);\
    token_to_string(tok, mf -> errno_str);\
    mf -> errno_int =  type;}}
/*:711*//*714:*/
#line 19601 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_INVALID_TENSION(mf, cx, line, value, position, x1, y1, x2, y2) {\
  if(!mf -> err){\
    float *buffer =  (float *) (mf -> errno_str);\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_TENSION);\
    buffer[0] =  (float) (x1);\
    buffer[1] =  (float) (y1);\
    buffer[2] =  (float) (x2);\
    buffer[3] =  (float) (y2);\
    buffer[4] =  (float) (value);\
    mf -> errno_int =  position;}}
/*:714*//*717:*/
#line 19640 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_MISSING_EXPRESSION(mf, cx, line, type) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_MISSING_EXPRESSION);\
    tokenid_to_string(type, mf -> errno_str);}}
/*:717*//*720:*/
#line 19669 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_MISSING_TOKEN(mf, cx, line, tok) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_MISSING_TOKEN);\
    tokenid_to_string(tok, mf -> errno_str);}}
/*:720*//*723:*/
#line 19696 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_NEGATIVE_LOGARITHM(mf, cx, line, number) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NEGATIVE_LOGARITHM);\
    snprintf(mf -> errno_str, 31, "%g", number);\
    mf -> errno_str[31] =  '\0';}}
/*:723*//*726:*/
#line 19724 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_NEGATIVE_SQUARE_ROOT(mf, cx, line, number) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NEGATIVE_SQUARE_ROOT);\
    snprintf(mf -> errno_str, 31, "%g", number);\
    mf -> errno_str[31] =  '\0';}}
/*:726*//*729:*/
#line 19754 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_NESTED_BEGINCHAR(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NESTED_BEGINCHAR);}
/*:729*//*732:*/
#line 19805 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_NO_MEMORY(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NO_MEMORY);}
/*:732*//*735:*/
#line 19836 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_NO_PICKUP_PEN(mf, cx, line) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NO_PICKUP_PEN);}}
/*:735*//*738:*/
#line 19864 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_NONCYCLICAL_PEN(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NONCYCLICAL_PEN);}
/*:738*//*741:*/
#line 19892 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_NULL_VECTOR_ANGLE(mf, cx, line) {\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NULL_VECTOR_ANGLE);}
/*:741*//*744:*/
#line 19921 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_OPENGL_FRAMEBUFFER(mf, cx, line) {\
  if(!mf -> err){\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_OPENGL_FRAMEBUFFER);\
  mf -> errno_int =  glCheckFramebufferStatus(GL_FRAMEBUFFER);}}
/*:744*//*747:*/
#line 19977 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_RECURSIVE_RENDERCHAR(mf, cx, line, glyph) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_RECURSIVE_RENDERCHAR);\
    memcpy(mf -> errno_str, glyph, 4);\
    mf -> errno_str[4] =  '\0';}}
/*:747*//*750:*/
#line 20011 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNBALANCED_ENDING_TOKEN(mf, cx, line, tok) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNCLOSED_STRING);\
    mf -> errno_int =  tok;}}
/*:750*//*753:*/
#line 20043 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNCLOSED_DELIMITER(mf, cx, line, delimiter) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNCLOSED_DELIMITER);\
    mf -> errno_int =  delimiter;}}
/*:753*//*756:*/
#line 20075 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNCLOSED_STRING(mf, cx, line, str) {\
  if(!mf -> err){\
    size_t _len =  strlen(str);\
    if(_len >  32) _len =  32;\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNCLOSED_STRING);\
    memcpy(mf -> errno_str, str, _len);\
    mf -> errno_str[31] =  '\0';}}
/*:756*//*759:*/
#line 20107 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNDECLARED_VARIABLE(mf, cx, line, tok) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNDECLARED_VARIABLE);\
    token_to_string((struct generic_token *) tok, mf -> errno_str);}}
/*:759*//*762:*/
#line 20141 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNEXPECTED_TOKEN(mf, cx, line, tok) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNEXPECTED_TOKEN);\
    token_to_string(tok, mf -> errno_str);}}
/*:762*//*765:*/
#line 20169 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNINITIALIZED_VARIABLE(mf, cx, line, var_token, var_type) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNINITIALIZED_VARIABLE);\
    token_to_string((struct generic_token *) (var_token), mf -> errno_str);\
    mf -> errno_int =  var_type;}}
/*:765*//*768:*/
#line 20200 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNKNOWN_GLYPH_DEPENDENCY(mf, cx, line, glyph) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNKNOWN_GLYPH_DEPENDENCY);\
    memcpy(mf -> errno_str, glyph, 4);\
    mf -> errno_str[4] =  '\0';}}
/*:768*//*771:*/
#line 20233 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNKNOWN_EXPRESSION(mf, cx, line, type) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNKNOWN_EXPRESSION);\
    mf -> errno_int =  type;}}
/*:771*//*774:*/
#line 20265 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNKNOWN_STATEMENT(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNKNOWN_STATEMENT);}
/*:774*//*777:*/
#line 20294 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNOPENED_DELIMITER(mf, cx, line, delimiter) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNOPENED_DELIMITER);\
    mf -> errno_int =  delimiter;}}
/*:777*//*780:*/
#line 20329 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_UNSUPORTED_LENGTH_OPERAND(mf, cx, line, type) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNSUPORTED_LENGTH_OPERAND);\
    mf -> errno_int =  type;}}
/*:780*//*783:*/
#line 20371 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_WRONG_NUMBER_OF_PARAMETERS(mf, cx, line, s, e, f) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_WRONG_NUMBER_OF_PARAMETERS);\
    tokenid_to_string(s, mf -> errno_str);\
    mf -> errno_int =  (e << 8) + f;}}
/*:783*//*786:*/
#line 20408 "weaver-interface-metafont.cweb"

#define RAISE_ERROR_WRONG_VARIABLE_TYPE(mf, cx, line, tok, type, expected) {\
  if(!mf -> err){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_WRONG_VARIABLE_TYPE);\
    token_to_string((struct generic_token *) tok, mf -> errno_str);\
    mf -> errno_int =  (type << 8) + expected;}}
/*:786*/
#line 520 "weaver-interface-metafont.cweb"

/*32:*/
#line 1121 "weaver-interface-metafont.cweb"

enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1250 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2516 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2782 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5293 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5461 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5474 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5711 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5837 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6125 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6456 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7012 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7152 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7559 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7715 "weaver-interface-metafont.cweb"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,
TYPE_STRAIGHT_JOIN,
/*:300*//*361:*/
#line 9382 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9761 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10282 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10563 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11715 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12083 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12250 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12489 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12640 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13127 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13331 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13555 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*576:*/
#line 16404 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16524 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16606 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16660 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*631:*/
#line 17859 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17964 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*//*644:*/
#line 18236 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:644*//*650:*/
#line 18389 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:650*/
#line 1126 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
/*:32*//*33:*/
#line 1138 "weaver-interface-metafont.cweb"

struct numeric_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
#line 1145 "weaver-interface-metafont.cweb"
 float value;
};
/*:33*//*34:*/
#line 1151 "weaver-interface-metafont.cweb"

struct string_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
#line 1158 "weaver-interface-metafont.cweb"
 char value[4];

struct _glyph*glyph;
};
/*:34*//*35:*/
#line 1173 "weaver-interface-metafont.cweb"

struct symbolic_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
#line 1180 "weaver-interface-metafont.cweb"
 void*var;
char*value;
};
/*:35*//*36:*/
#line 1195 "weaver-interface-metafont.cweb"

struct begin_loop_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
#line 1202 "weaver-interface-metafont.cweb"
 bool running;
float*control_var;
struct linked_token*end;
};
/*:36*//*37:*/
#line 1219 "weaver-interface-metafont.cweb"

struct linked_token{

int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
#line 1227 "weaver-interface-metafont.cweb"
 struct generic_token*link;
};
/*:37*//*38:*/
#line 1237 "weaver-interface-metafont.cweb"

struct generic_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
#line 1244 "weaver-interface-metafont.cweb"
};
/*:38*//*99:*/
#line 2818 "weaver-interface-metafont.cweb"


struct variable{
int type;
struct variable*next;
};
/*:99*//*100:*/
#line 2835 "weaver-interface-metafont.cweb"

struct named_variable{
char*name;
struct named_variable*next;
struct variable*var;
};
/*:100*//*116:*/
#line 3147 "weaver-interface-metafont.cweb"

struct numeric_variable{
int type;
void*next;
float value;
};
/*:116*//*127:*/
#line 3345 "weaver-interface-metafont.cweb"

struct pair_variable{
int type;
void*next;
float x,y;
};
/*:127*//*129:*/
#line 3385 "weaver-interface-metafont.cweb"

struct transform_variable{
int type;
void*next;
float value[9];
};
/*:129*//*136:*/
#line 3473 "weaver-interface-metafont.cweb"

struct path_variable{
int type;
void*next;
bool permanent;
bool cyclic;
int length,number_of_points,number_of_missing_directions;
struct path_points*points;
};
/*:136*//*138:*/
#line 3535 "weaver-interface-metafont.cweb"

struct path_points{
int format;
union{

struct{
float x,y;
float u_x,u_y,v_x,v_y;
}point;

struct path_variable*subpath;

struct{
float x,y;
float dir1_x,dir1_y,dir2_x,dir2_y;
float tension1,tension2;
bool atleast1,atleast2;
}prov;
};
};
/*:138*//*178:*/
#line 4868 "weaver-interface-metafont.cweb"

struct pen_variable{
int type;
void*next;
bool permanent;
struct path_variable*format;
int flags;
struct pen_variable*referenced;
float gl_matrix[9];

GLuint gl_vbo;
GLsizei indices;


float triang_resolution;
};
/*:178*//*192:*/
#line 5162 "weaver-interface-metafont.cweb"

struct picture_variable{
int type;
void*next;
int width,height;
GLuint texture;
};
/*:192*//*199:*/
#line 5247 "weaver-interface-metafont.cweb"

struct boolean_variable{
int type;
void*next;
short value;
};
/*:199*//*525:*/
#line 14548 "weaver-interface-metafont.cweb"

#define FLAG_UPPER 1
#define FLAG_LOWER 2
#define NEW_POLYGON_VERTEX() \
  (struct polygon_vertex *) temporary_alloc(sizeof(struct polygon_vertex))
#define DESTROY_POLYGON_VERTEX(v) \
  ((temporary_free != NULL)?(temporary_free(v)):(true))
struct polygon_vertex{
int flag;
float x,y;
struct polygon_vertex*prev,*next;
/*533:*/
#line 14870 "weaver-interface-metafont.cweb"

struct polygon_vertex*succ;
/*:533*//*542:*/
#line 15213 "weaver-interface-metafont.cweb"

struct polygon_vertex*pred;
/*:542*/
#line 14559 "weaver-interface-metafont.cweb"

};
/*:525*//*526:*/
#line 14567 "weaver-interface-metafont.cweb"

#define XMONOTONE_LEQ(v1, v2) ((v1->x==v2->x)?(v1->y<=v2->y):(v1->x<=v2->x))
/*:526*//*541:*/
#line 15194 "weaver-interface-metafont.cweb"

#define TYPE_UNKNOWN_VERTEX  0
#define TYPE_REGULAR_VERTEX  4
#define TYPE_BEGIN_VERTEX    8
#define TYPE_END_VERTEX     12
#define TYPE_SPLIT_VERTEX   16
#define TYPE_MERGE_VERTEX   20
#define GET_VERTEX_TYPE(v) (((v -> flag) >> 2) << 2)
/*:541*//*549:*/
#line 15417 "weaver-interface-metafont.cweb"

struct polygon_edge{
float x1,y1,x2,y2;
struct polygon_vertex*helper;
struct polygon_edge*parent,*left,*right;
};
#define NEW_POLYGON_EDGE() \
  (struct polygon_edge *) temporary_alloc(sizeof(struct polygon_edge));
#define INITIALIZE_POLYGON_EDGE(p, x1, y1, x2, y2, helper) {\
 p -> x1 =  x1; p -> x2 =  x2; p -> y1 =  y1; p -> y2 =  y2;\
 p -> helper =  helper;\
 p -> parent =  p -> left =  p -> right =  NULL;}
#define DESTROY_POLYGON_EDGE(p) \
  ((temporary_free != NULL)?(temporary_free(p)):(true))
/*:549*//*613:*/
#line 17129 "weaver-interface-metafont.cweb"

struct _glyph{
struct generic_token*begin,*end;
int width,height,depth;
int italic_correction;
struct kerning*kern;
GLuint texture;
bool need_rendering,is_being_rendered;
};
#define INITIALIZE_GLYPH(a) {a.begin =  NULL; \
                            a.end =  NULL; \
                            a.width =  0; \
                            a.height =  0;\
                            a.depth =  0; \
                            a.italic_correction =  0; \
                            a.kern =  NULL; \
                            a.texture =  0; \
                            a.need_rendering =  true; \
                            a.is_being_rendered =  false; \
                            }
/*:613*//*614:*/
#line 17155 "weaver-interface-metafont.cweb"

struct kerning{
char next_char[5];
float kern;
struct kerning*next;
};
/*:614*//*666:*/
#line 18830 "weaver-interface-metafont.cweb"

enum{
ERROR_NO_ERROR= 0,

/*676:*/
#line 19075 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:676*//*679:*/
#line 19121 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:679*//*682:*/
#line 19143 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:682*//*685:*/
#line 19173 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:685*//*688:*/
#line 19218 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:688*//*691:*/
#line 19252 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:691*//*695:*/
#line 19293 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:695*//*698:*/
#line 19323 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:698*//*701:*/
#line 19355 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:701*//*704:*/
#line 19460 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:704*//*707:*/
#line 19493 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:707*//*710:*/
#line 19533 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:710*//*713:*/
#line 19579 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:713*//*716:*/
#line 19628 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:716*//*719:*/
#line 19658 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:719*//*722:*/
#line 19688 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:722*//*725:*/
#line 19716 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:725*//*728:*/
#line 19743 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:728*//*731:*/
#line 19770 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:731*//*734:*/
#line 19822 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:734*//*737:*/
#line 19855 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:737*//*740:*/
#line 19881 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:740*//*743:*/
#line 19909 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:743*//*746:*/
#line 19963 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:746*//*749:*/
#line 19997 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:749*//*752:*/
#line 20033 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:752*//*755:*/
#line 20061 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:755*//*758:*/
#line 20098 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:758*//*761:*/
#line 20126 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:761*//*764:*/
#line 20159 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:764*//*767:*/
#line 20190 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:767*//*770:*/
#line 20221 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:770*//*773:*/
#line 20252 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:773*//*776:*/
#line 20283 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:776*//*779:*/
#line 20312 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:779*//*782:*/
#line 20355 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:782*//*785:*/
#line 20393 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:785*/
#line 18834 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
/*:666*/
#line 521 "weaver-interface-metafont.cweb"

/*29:*/
#line 1052 "weaver-interface-metafont.cweb"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int dpi;
/*:29*//*62:*/
#line 1744 "weaver-interface-metafont.cweb"

static char*list_of_keywords[]= {
/*85:*/
#line 2527 "weaver-interface-metafont.cweb"

"begingroup","endgroup","if","fi","beginchar","endchar",
/*:85*//*98:*/
#line 2794 "weaver-interface-metafont.cweb"

"boolean","path","pen","picture","transform","pair","numeric",
/*:98*//*202:*/
#line 5300 "weaver-interface-metafont.cweb"

"=",":=",
/*:202*//*207:*/
#line 5483 "weaver-interface-metafont.cweb"

"+","-","++","+-+","[","]","{","}",
/*:207*//*214:*/
#line 5716 "weaver-interface-metafont.cweb"

"*","/",
/*:214*//*218:*/
#line 5848 "weaver-interface-metafont.cweb"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:218*//*234:*/
#line 6129 "weaver-interface-metafont.cweb"

"normaldeviate",
/*:234*//*248:*/
#line 6466 "weaver-interface-metafont.cweb"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:248*//*268:*/
#line 7021 "weaver-interface-metafont.cweb"

"xpart","ypart","angle",
/*:268*//*275:*/
#line 7158 "weaver-interface-metafont.cweb"

"transformed",
/*:275*//*294:*/
#line 7568 "weaver-interface-metafont.cweb"

"xxpart","xypart","yxpart","yypart",
/*:294*//*301:*/
#line 7730 "weaver-interface-metafont.cweb"

"cycle","&","..","tension","and","atleast","controls","curl","--",
/*:301*//*362:*/
#line 9391 "weaver-interface-metafont.cweb"

"reverse","subpath","of",
/*:362*//*374:*/
#line 9769 "weaver-interface-metafont.cweb"

"point","precontrol","postcontrol",
/*:374*//*396:*/
#line 10292 "weaver-interface-metafont.cweb"

"nullpen","pencircle","pensemicircle","makepen",
/*:396*//*408:*/
#line 10569 "weaver-interface-metafont.cweb"

"makepath",
/*:408*//*452:*/
#line 11722 "weaver-interface-metafont.cweb"

"nullpicture","subpicture",
/*:452*//*464:*/
#line 12091 "weaver-interface-metafont.cweb"

"totalweight","width","height",
/*:464*//*470:*/
#line 12260 "weaver-interface-metafont.cweb"

"<","<=",">",">=","<>",
/*:470*//*474:*/
#line 12495 "weaver-interface-metafont.cweb"

"or",
/*:474*//*480:*/
#line 12650 "weaver-interface-metafont.cweb"

"true","false","odd","not",
/*:480*//*488:*/
#line 13135 "weaver-interface-metafont.cweb"

"elseif","else",":",
/*:488*//*493:*/
#line 13338 "weaver-interface-metafont.cweb"

"step","until",
/*:493*//*502:*/
#line 13559 "weaver-interface-metafont.cweb"

"pickup",
/*:502*//*577:*/
#line 16413 "weaver-interface-metafont.cweb"

"bot","top","lft","rt",
/*:577*//*585:*/
#line 16528 "weaver-interface-metafont.cweb"

"pickcolor",
/*:585*//*588:*/
#line 16610 "weaver-interface-metafont.cweb"

"monowidth",
/*:588*//*593:*/
#line 16665 "weaver-interface-metafont.cweb"

"draw","erase",
/*:593*//*632:*/
#line 17863 "weaver-interface-metafont.cweb"

"shipit",
/*:632*//*636:*/
#line 17969 "weaver-interface-metafont.cweb"

"renderchar","between",
/*:636*//*645:*/
#line 18240 "weaver-interface-metafont.cweb"

"kerning",
/*:645*//*651:*/
#line 18393 "weaver-interface-metafont.cweb"

"debug",
/*:651*/
#line 1746 "weaver-interface-metafont.cweb"

NULL};
/*:62*//*417:*/
#line 10840 "weaver-interface-metafont.cweb"

static const float square[20]= {
-1.0,-1.0,
0.0,0.0,
1.0,-1.0,
1.0,0.0,
1.0,1.0,
1.0,1.0,
-1.0,1.0,
0.0,1.0};
static GLuint vbo;
/*:417*//*420:*/
#line 10889 "weaver-interface-metafont.cweb"

static const char vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat3 model_view_matrix;\n"
"varying highp vec2 texture_coordinate;\n"
"void main(){\n"
"  highp vec3 coord;\n"
"  coord = vec3(vertex_data.xy, 1.0) * model_view_matrix;\n"
"  gl_Position = vec4(coord.x, coord.y, 0.0, 1.0);\n"
"  texture_coordinate = vertex_data.zw;\n"
"}\n";
/*:420*//*421:*/
#line 10906 "weaver-interface-metafont.cweb"

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
/*:421*//*434:*/
#line 11256 "weaver-interface-metafont.cweb"

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
/*:434*//*518:*/
#line 14090 "weaver-interface-metafont.cweb"

static GLuint pensquare_vbo;
/*:518*//*598:*/
#line 16751 "weaver-interface-metafont.cweb"

static GLint previous_fb;
/*:598*//*601:*/
#line 16787 "weaver-interface-metafont.cweb"

static const char pen_vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat3 model_view_matrix;\n"
"void main(){\n"
"  highp vec3 coord;\n"
"  coord = vec3(vertex_data.xy, 1.0) * model_view_matrix;\n"
"  gl_Position = vec4(coord.x, coord.y, 0.0, 1.0);\n"
"}\n";
/*:601*//*602:*/
#line 16802 "weaver-interface-metafont.cweb"

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
/*:602*/
#line 522 "weaver-interface-metafont.cweb"

/*19:*/
#line 787 "weaver-interface-metafont.cweb"

void solve_linear_system(int n,double*m,double*b,double*x);
/*:19*//*77:*/
#line 2281 "weaver-interface-metafont.cweb"

struct metafont*init_metafont(char*filename);
struct context*init_context(struct metafont*mf);
void destroy_context(struct context*cx);
/*:77*//*82:*/
#line 2391 "weaver-interface-metafont.cweb"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
struct generic_token*begin_list,
struct generic_token*end_list);
/*:82*//*86:*/
#line 2540 "weaver-interface-metafont.cweb"

bool eval_statement(struct metafont*,struct context*,
struct generic_token*begin,struct generic_token**end);
/*:86*//*90:*/
#line 2610 "weaver-interface-metafont.cweb"

bool begin_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
/*:90*//*110:*/
#line 3004 "weaver-interface-metafont.cweb"

struct variable*insert_variable(struct metafont*mf,
int type,
struct variable**target);
/*:110*//*112:*/
#line 3053 "weaver-interface-metafont.cweb"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:112*//*114:*/
#line 3110 "weaver-interface-metafont.cweb"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:114*//*142:*/
#line 3616 "weaver-interface-metafont.cweb"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer);
/*:142*//*144:*/
#line 3671 "weaver-interface-metafont.cweb"

bool recursive_copy_points(struct metafont*mf,struct context*cx,
void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target);
void recursive_aux_copy(struct path_points**dst,
struct path_variable*origin,int*missing_directions,
struct path_points**previous_point);
/*:144*//*148:*/
#line 3851 "weaver-interface-metafont.cweb"

void convert_to_final(struct path_variable*p);
double compute_f(double theta,double phi);
/*:148*//*152:*/
#line 3928 "weaver-interface-metafont.cweb"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y);
/*:152*//*154:*/
#line 3969 "weaver-interface-metafont.cweb"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y);
/*:154*//*158:*/
#line 4120 "weaver-interface-metafont.cweb"

bool find_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p);
/*:158*//*164:*/
#line 4275 "weaver-interface-metafont.cweb"

bool fill_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p,int begin,int end);
/*:164*//*166:*/
#line 4346 "weaver-interface-metafont.cweb"

bool fill_cyclic_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p,int begin,
int end);
/*:166*//*175:*/
#line 4808 "weaver-interface-metafont.cweb"

bool normalize_path(struct metafont*mf,struct context*cx,
struct path_variable*path);
/*:175*//*208:*/
#line 5490 "weaver-interface-metafont.cweb"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:208*//*215:*/
#line 5725 "weaver-interface-metafont.cweb"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result);
/*:215*//*219:*/
#line 5854 "weaver-interface-metafont.cweb"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result);
/*:219*//*235:*/
#line 6138 "weaver-interface-metafont.cweb"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result);
/*:235*//*245:*/
#line 6375 "weaver-interface-metafont.cweb"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result);
/*:245*//*249:*/
#line 6473 "weaver-interface-metafont.cweb"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result);
/*:249*//*260:*/
#line 6752 "weaver-interface-metafont.cweb"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result);
/*:260*//*276:*/
#line 7173 "weaver-interface-metafont.cweb"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result);
/*:276*//*278:*/
#line 7193 "weaver-interface-metafont.cweb"

bool eval_transform_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result);
/*:278*//*288:*/
#line 7387 "weaver-interface-metafont.cweb"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result);
/*:288*//*302:*/
#line 7743 "weaver-interface-metafont.cweb"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:302*//*304:*/
#line 7787 "weaver-interface-metafont.cweb"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:304*//*318:*/
#line 8254 "weaver-interface-metafont.cweb"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y);
/*:318*//*337:*/
#line 8897 "weaver-interface-metafont.cweb"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:337*//*339:*/
#line 8980 "weaver-interface-metafont.cweb"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:339*//*342:*/
#line 9112 "weaver-interface-metafont.cweb"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta);
/*:342*//*345:*/
#line 9154 "weaver-interface-metafont.cweb"

void path_xyscale(struct path_variable*p,float x,float y);
/*:345*//*348:*/
#line 9193 "weaver-interface-metafont.cweb"

void path_shift(struct path_variable*p,float x,float y);
/*:348*//*351:*/
#line 9227 "weaver-interface-metafont.cweb"

void path_slant(struct path_variable*p,float s);
/*:351*//*356:*/
#line 9293 "weaver-interface-metafont.cweb"

void path_zscale(struct path_variable*p,float x,float y);
/*:356*//*359:*/
#line 9337 "weaver-interface-metafont.cweb"

void path_transform(struct path_variable*p,float*M);
/*:359*//*363:*/
#line 9404 "weaver-interface-metafont.cweb"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:363*//*366:*/
#line 9464 "weaver-interface-metafont.cweb"

bool reverse_path(struct metafont*mf,struct context*cx,
struct path_variable*dst,
struct path_variable*origin);
/*:366*//*375:*/
#line 9783 "weaver-interface-metafont.cweb"

struct path_points*get_point(struct path_variable*v,int n);
/*:375*//*377:*/
#line 9809 "weaver-interface-metafont.cweb"

struct path_points*_get_point(struct path_variable*v,int n,int*count);
/*:377*//*381:*/
#line 9948 "weaver-interface-metafont.cweb"

bool assign_pen_variable(struct metafont*mf,struct context*cx,
struct pen_variable*target,
struct pen_variable*source);
/*:381*//*383:*/
#line 10008 "weaver-interface-metafont.cweb"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result);
/*:383*//*385:*/
#line 10058 "weaver-interface-metafont.cweb"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result);
/*:385*//*397:*/
#line 10298 "weaver-interface-metafont.cweb"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result);
/*:397*//*405:*/
#line 10474 "weaver-interface-metafont.cweb"

int read_flags(struct path_variable*path);
/*:405*//*422:*/
#line 10923 "weaver-interface-metafont.cweb"

GLuint compile_shader_program(const char*vertex_shader_source,
const char*fragment_shader_source);
/*:422*//*426:*/
#line 11002 "weaver-interface-metafont.cweb"

bool get_new_framebuffer(GLuint*new_framebuffer,GLuint*new_texture,
int width,int height);
/*:426*//*428:*/
#line 11035 "weaver-interface-metafont.cweb"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height,bool clear_background);

void print_picture(struct picture_variable*pic);
/*:428*//*430:*/
#line 11092 "weaver-interface-metafont.cweb"

bool assign_picture_variable(struct metafont*mf,struct context*cx,
struct picture_variable*target,
struct picture_variable*source);
/*:430*//*432:*/
#line 11155 "weaver-interface-metafont.cweb"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result);
/*:432*//*439:*/
#line 11416 "weaver-interface-metafont.cweb"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result,
float*matrix,bool*modified);
/*:439*//*449:*/
#line 11599 "weaver-interface-metafont.cweb"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*origin,
float*matrix);
/*:449*//*453:*/
#line 11728 "weaver-interface-metafont.cweb"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result);
/*:453*//*471:*/
#line 12266 "weaver-interface-metafont.cweb"

bool eval_boolean_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:471*//*475:*/
#line 12501 "weaver-interface-metafont.cweb"

bool eval_boolean_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:475*//*477:*/
#line 12568 "weaver-interface-metafont.cweb"

bool eval_boolean_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:477*//*481:*/
#line 12656 "weaver-interface-metafont.cweb"

bool eval_boolean_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:481*//*483:*/
#line 12783 "weaver-interface-metafont.cweb"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_secondary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_tertiary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:483*//*508:*/
#line 13658 "weaver-interface-metafont.cweb"

void pencircular_extremity_points(struct context*cx,
float*matrix,bool fullcircle);
/*:508*//*510:*/
#line 13850 "weaver-interface-metafont.cweb"

void path_extremity_points(struct context*cx,
struct path_variable*p,float*matrix);
/*:510*//*513:*/
#line 13986 "weaver-interface-metafont.cweb"

bool is_pen_counterclockwise(struct pen_variable*pen);
/*:513*//*515:*/
#line 14049 "weaver-interface-metafont.cweb"

bool triangulate_pen(struct metafont*mf,struct context*cx,
struct pen_variable*pen,float*transform_matrix);
/*:515*//*527:*/
#line 14574 "weaver-interface-metafont.cweb"

void destroy_vertex_linked_list(struct polygon_vertex*poly);
/*:527*//*529:*/
#line 14596 "weaver-interface-metafont.cweb"

struct polygon_vertex*polygon_from_pen(struct metafont*mf,
struct pen_variable*,
float*transform_matrix,
int*number_of_vertices);
/*:529*//*531:*/
#line 14751 "weaver-interface-metafont.cweb"

bool is_xmonotone(struct polygon_vertex*poly);
/*:531*//*535:*/
#line 14899 "weaver-interface-metafont.cweb"

static bool triangulate_xmonotone_polygon(struct polygon_vertex*p,
float**triangles,
int*number_of_triangles,
struct polygon_vertex**stack);
/*:535*//*545:*/
#line 15318 "weaver-interface-metafont.cweb"

void prepare_non_monotonous(struct polygon_vertex*p,int number_of_vertices);
/*:545*//*547:*/
#line 15366 "weaver-interface-metafont.cweb"

static bool is_turning_left(struct polygon_vertex*p1,
struct polygon_vertex*p2,
struct polygon_vertex*p3);
/*:547*//*550:*/
#line 15444 "weaver-interface-metafont.cweb"

static struct polygon_edge*insert_polygon_edge(struct polygon_edge**,
float,float,float,float,
struct polygon_vertex*,
bool(*)(struct polygon_edge*,
struct polygon_edge*),
bool(*)(struct polygon_edge*,
struct polygon_edge*));
/*:550*//*552:*/
#line 15505 "weaver-interface-metafont.cweb"

static bool leq_by_vertex(struct polygon_edge*,struct polygon_edge*);
/*:552*//*554:*/
#line 15570 "weaver-interface-metafont.cweb"

static bool eq_by_vertex(struct polygon_edge*,struct polygon_edge*);
/*:554*//*556:*/
#line 15585 "weaver-interface-metafont.cweb"

static struct polygon_edge*remove_polygon_edge(struct polygon_edge**,
float,float,float,float,
bool(*)(struct polygon_edge*,
struct polygon_edge*),
bool(*)(struct polygon_edge*,
struct polygon_edge*));
/*:556*//*558:*/
#line 15658 "weaver-interface-metafont.cweb"

static struct polygon_edge*find_edge_below(struct polygon_edge*,
float,float);
/*:558*//*560:*/
#line 15692 "weaver-interface-metafont.cweb"

static bool cut_polygon(struct polygon_vertex*v1,struct polygon_vertex*v2,
struct polygon_vertex**new1,
struct polygon_vertex**new2);
/*:560*//*563:*/
#line 15829 "weaver-interface-metafont.cweb"

static bool leq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2);
static bool eq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2);
/*:563*//*566:*/
#line 15903 "weaver-interface-metafont.cweb"

static void triangulate_polygon_tree(struct polygon_edge*tree,
float**triangles,
int*number_of_triangles,
struct polygon_vertex**buffer);
void print_tree(struct polygon_edge*tree){
printf(" (%f %f)--(%f %f)\n",tree->x1,tree->y1,tree->x2,tree->y2);
if(tree->left!=NULL)
print_tree(tree->left);
else printf("left nil\n");
if(tree->right!=NULL)
print_tree(tree->right);
else printf("right nil\n");
}
/*:566*//*606:*/
#line 16879 "weaver-interface-metafont.cweb"

bool drawing_commands(struct metafont*mf,struct context*cx,
struct path_variable*path,unsigned int flags);
/*:606*//*608:*/
#line 16964 "weaver-interface-metafont.cweb"

void drawpoint(struct context*cx,
struct pen_variable*pen,struct picture_variable*pic,
float x,float y,float*matrix,bool erasing);
/*:608*//*617:*/
#line 17193 "weaver-interface-metafont.cweb"

static struct _glyph*get_glyph(struct metafont*mf,unsigned char*utf8,
bool create_if_not_exist);
/*:617*//*670:*/
#line 18936 "weaver-interface-metafont.cweb"

void token_to_string(struct generic_token*tok,char*dst);
void tokenid_to_string(int token_id,char*dst);
/*:670*/
#line 523 "weaver-interface-metafont.cweb"

/*22:*/
#line 880 "weaver-interface-metafont.cweb"

void solve_linear_system(int n,double*m,double*b,double*x){
int i,j;
for(i= 0;i<n;i++){

int max_line= i;
double max= fabs(m[i*n+i]);
for(j= i+1;j<n;j++){
if(fabs(m[j*n+i])> max){
max= fabs(m[j*n+i]);
max_line= j;
}
}
EXCHANGE_ROWS(n,m,b,i,max_line);

for(j= i+1;j<n;j++){
double multiplier= m[j*n+i]/m[i*n+i];
SUB_MUL_LINES(n,m,b,j,i,multiplier);
}
}

for(i= n-1;i>=0;i--){
x[i]= 0;
for(j= n-1;j> i;j--)
x[i]+= x[j]*m[i*n+j];
x[i]= (b[i]-x[i])/m[i*n+i];
}
}
/*:22*//*40:*/
#line 1281 "weaver-interface-metafont.cweb"

void free_token_list(void*token_list){
if(permanent_free!=NULL&&token_list!=NULL){
struct generic_token*p,*p_next;
p= token_list;
while(p!=NULL){
p_next= p->next;
if(p->type==TYPE_SYMBOLIC)
permanent_free(((struct symbolic_token*)p)->value);
permanent_free(p);
p= p_next;
}
}
}
/*:40*//*41:*/
#line 1307 "weaver-interface-metafont.cweb"

bool lexer(struct metafont*mf,char*path,struct generic_token**first_token,
struct generic_token**last_token){
struct linked_token*aux_stack= NULL;
FILE*fp;
char c;
int line= 1;
*first_token= NULL;
*last_token= NULL;
fp= fopen(path,"r");
if(fp==NULL){
RAISE_ERROR_FAILED_OPENING_FILE(mf,NULL,0,path);
return false;
}
while((c= fgetc(fp))!=EOF){
char next_char= fgetc(fp);
ungetc(next_char,fp);
if(c=='\n'){
line++;
continue;
}
/*43:*/
#line 1370 "weaver-interface-metafont.cweb"

if(c==' '||c=='\t'||
(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:43*/
#line 1328 "weaver-interface-metafont.cweb"

/*45:*/
#line 1387 "weaver-interface-metafont.cweb"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:45*/
#line 1329 "weaver-interface-metafont.cweb"

/*46:*/
#line 1402 "weaver-interface-metafont.cweb"

if((c=='.'&&isdigit(next_char))||isdigit(c)){
char buffer[256];
struct numeric_token*new_token= 
(struct numeric_token*)permanent_alloc(sizeof(struct numeric_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
new_token->type= TYPE_NUMERIC;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 1418 "weaver-interface-metafont.cweb"
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
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
/*:46*/
#line 1330 "weaver-interface-metafont.cweb"

/*47:*/
#line 1454 "weaver-interface-metafont.cweb"

if(c==34){
struct string_token*new_token= 
(struct string_token*)permanent_alloc(sizeof(struct string_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
new_token->type= TYPE_STRING;
new_token->glyph= NULL;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 1470 "weaver-interface-metafont.cweb"
 int i= 0,prev= 0,prev_prev;
do{
prev_prev= prev;
prev= c;
c= fgetc(fp);
if(i<5&&(c!='\\'||prev=='\\')){
new_token->value[i]= c;
i++;
}
}while((c!=34||(prev=='\\'&&prev_prev!='\\'))&&
c!='\n'&&c!=EOF);
i--;
new_token->value[i]= '\0';
if(c=='\n'||c==EOF){
RAISE_ERROR_UNCLOSED_STRING(mf,NULL,line,new_token->value);
if(permanent_free!=NULL)
permanent_free(new_token);
free_token_list(*first_token);
*first_token= *last_token= NULL;
return false;
}
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
/*:47*/
#line 1331 "weaver-interface-metafont.cweb"

/*48:*/
#line 1505 "weaver-interface-metafont.cweb"

if(c=='('||c==')'||c==','||c==';'){
struct generic_token*new_token= 
(struct generic_token*)permanent_alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
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
#line 1527 "weaver-interface-metafont.cweb"
 if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
/*:48*/
#line 1332 "weaver-interface-metafont.cweb"

/*49:*/
#line 1541 "weaver-interface-metafont.cweb"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*50:*/
#line 1571 "weaver-interface-metafont.cweb"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_'||isdigit(c));
ungetc(c,fp);
buffer[i]= '\0';
}
/*:50*/
#line 1547 "weaver-interface-metafont.cweb"

/*51:*/
#line 1586 "weaver-interface-metafont.cweb"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:51*/
#line 1548 "weaver-interface-metafont.cweb"

/*52:*/
#line 1600 "weaver-interface-metafont.cweb"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:52*/
#line 1549 "weaver-interface-metafont.cweb"

/*53:*/
#line 1614 "weaver-interface-metafont.cweb"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:53*/
#line 1550 "weaver-interface-metafont.cweb"

/*54:*/
#line 1628 "weaver-interface-metafont.cweb"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:54*/
#line 1551 "weaver-interface-metafont.cweb"

/*55:*/
#line 1642 "weaver-interface-metafont.cweb"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:55*/
#line 1552 "weaver-interface-metafont.cweb"

/*56:*/
#line 1656 "weaver-interface-metafont.cweb"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:56*/
#line 1553 "weaver-interface-metafont.cweb"

/*57:*/
#line 1670 "weaver-interface-metafont.cweb"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:57*/
#line 1554 "weaver-interface-metafont.cweb"

/*58:*/
#line 1684 "weaver-interface-metafont.cweb"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:58*/
#line 1555 "weaver-interface-metafont.cweb"

/*59:*/
#line 1698 "weaver-interface-metafont.cweb"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:59*/
#line 1556 "weaver-interface-metafont.cweb"

/*60:*/
#line 1712 "weaver-interface-metafont.cweb"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:60*/
#line 1557 "weaver-interface-metafont.cweb"

/*61:*/
#line 1726 "weaver-interface-metafont.cweb"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:61*/
#line 1558 "weaver-interface-metafont.cweb"


/*65:*/
#line 1811 "weaver-interface-metafont.cweb"

if(!strcmp(buffer,"for")){
struct generic_token*previous_token= *last_token;
struct linked_token*endfor_token;
struct begin_loop_token*new_token= (struct begin_loop_token*)
permanent_alloc(sizeof(struct begin_loop_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
new_token->type= TYPE_FOR;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 1828 "weaver-interface-metafont.cweb"
 new_token->running= false;
new_token->control_var= NULL;
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
endfor_token= (struct linked_token*)
permanent_alloc(sizeof(struct linked_token));
if(endfor_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
endfor_token->link= (struct generic_token*)previous_token;
new_token->end= endfor_token;
endfor_token->type= TYPE_ENDFOR;
if(aux_stack==NULL){
aux_stack= endfor_token;
endfor_token->next= NULL;
}
else{
endfor_token->next= (struct generic_token*)aux_stack;
aux_stack= endfor_token;
}
continue;
}
/*:65*//*66:*/
#line 1864 "weaver-interface-metafont.cweb"

if(!strcmp(buffer,"endfor")){
if(aux_stack==NULL||aux_stack->type!=TYPE_ENDFOR){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_UNBALANCED_ENDING_TOKEN(mf,NULL,OPTIONAL(line),TYPE_ENDFOR);
return false;
}
struct linked_token*new_token= aux_stack;
aux_stack= (struct linked_token*)aux_stack->next;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 1878 "weaver-interface-metafont.cweb"
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
continue;
}
/*:66*//*67:*/
#line 1898 "weaver-interface-metafont.cweb"

if(!strcmp(buffer,"if")){
struct linked_token*if_token,*fi_token;
if_token= (struct linked_token*)
permanent_alloc(sizeof(struct linked_token));
if(if_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
if_token->type= TYPE_IF;
if_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
if_token->line= line;
#endif
#line 1914 "weaver-interface-metafont.cweb"
 if_token->link= NULL;
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)if_token;
else{
(*last_token)->next= (struct generic_token*)if_token;
*last_token= (struct generic_token*)if_token;
}
fi_token= (struct linked_token*)
temporary_alloc(sizeof(struct linked_token));
if(fi_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
fi_token->link= (struct generic_token*)if_token;
fi_token->type= TYPE_FI;
if(aux_stack==NULL){
aux_stack= fi_token;
fi_token->next= NULL;
}
else{
fi_token->next= (struct generic_token*)aux_stack;
aux_stack= fi_token;
}
continue;
}
/*:67*//*68:*/
#line 1952 "weaver-interface-metafont.cweb"

if(!strcmp(buffer,"elseif")||!strcmp(buffer,"else")){
struct linked_token*new_token;
if(aux_stack==NULL||aux_stack->type!=TYPE_FI||
aux_stack->link->type==TYPE_ELSE){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_UNBALANCED_ENDING_TOKEN(mf,NULL,OPTIONAL(line),
(buffer[4]=='i')?TYPE_ELSEIF:TYPE_ELSE);
return false;
}
new_token= (struct linked_token*)
permanent_alloc(sizeof(struct linked_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
((struct linked_token*)(aux_stack->link))->link= 
(struct generic_token*)new_token;
if(buffer[4]=='i')
new_token->type= TYPE_ELSEIF;
else
new_token->type= TYPE_ELSE;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 1981 "weaver-interface-metafont.cweb"
 new_token->link= NULL;
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
aux_stack->link= (struct generic_token*)new_token;
continue;
}
/*:68*//*69:*/
#line 1999 "weaver-interface-metafont.cweb"

if(!strcmp(buffer,"fi")){
struct generic_token*new_token;
if(aux_stack==NULL||aux_stack->type!=TYPE_FI){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_UNBALANCED_ENDING_TOKEN(mf,NULL,OPTIONAL(line),TYPE_FI);
return false;
}
new_token= (struct generic_token*)
permanent_alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
((struct linked_token*)aux_stack->link)->link= new_token;
new_token->type= TYPE_FI;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 2022 "weaver-interface-metafont.cweb"
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
struct linked_token*tmp= aux_stack;
aux_stack= (struct linked_token*)aux_stack->next;
if(temporary_free!=NULL)
temporary_free(tmp);
continue;
}
/*:69*//*70:*/
#line 2042 "weaver-interface-metafont.cweb"

if(!strcmp(buffer,"beginchar")){
struct linked_token*beginchar_token,*endchar_token= aux_stack;
beginchar_token= (struct linked_token*)
permanent_alloc(sizeof(struct linked_token));
if(beginchar_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
while(endchar_token!=NULL){
if(endchar_token->type==TYPE_ENDCHAR){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NESTED_BEGINCHAR(mf,NULL,line);
return false;
}
endchar_token= (struct linked_token*)(endchar_token->next);
}
beginchar_token->type= TYPE_BEGINCHAR;
beginchar_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
beginchar_token->line= line;
#endif
#line 2067 "weaver-interface-metafont.cweb"
 beginchar_token->link= NULL;
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)beginchar_token;
else{
(*last_token)->next= (struct generic_token*)beginchar_token;
*last_token= (struct generic_token*)beginchar_token;
}
endchar_token= (struct linked_token*)
temporary_alloc(sizeof(struct linked_token));
if(endchar_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
endchar_token->link= (struct generic_token*)beginchar_token;
endchar_token->type= TYPE_ENDCHAR;
if(aux_stack==NULL){
aux_stack= endchar_token;
endchar_token->next= NULL;
}
else{
endchar_token->next= (struct generic_token*)aux_stack;
aux_stack= endchar_token;
}
continue;
}
/*:70*//*71:*/
#line 2100 "weaver-interface-metafont.cweb"

if(!strcmp(buffer,"endchar")){
struct generic_token*new_token;
if(aux_stack==NULL||aux_stack->type!=TYPE_ENDCHAR){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_UNBALANCED_ENDING_TOKEN(mf,NULL,OPTIONAL(line),TYPE_ENDCHAR);
return false;
}
new_token= (struct generic_token*)
permanent_alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
((struct linked_token*)aux_stack->link)->link= new_token;
new_token->type= TYPE_ENDCHAR;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 2123 "weaver-interface-metafont.cweb"
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
struct linked_token*tmp= aux_stack;
aux_stack= (struct linked_token*)aux_stack->next;
if(temporary_free!=NULL)
temporary_free(tmp);
continue;
}
/*:71*/
#line 1560 "weaver-interface-metafont.cweb"

/*63:*/
#line 1755 "weaver-interface-metafont.cweb"

{
int token_type= 0;
for(i= 0;list_of_keywords[i]!=NULL;i++)
if(!strcmp(buffer,list_of_keywords[i]))
token_type= i+TYPE_SEMICOLON+1;
if(token_type!=0){
struct generic_token*new_token= 
(struct generic_token*)permanent_alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
new_token->type= token_type;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 1775 "weaver-interface-metafont.cweb"
 if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
}
/*:63*/
#line 1561 "weaver-interface-metafont.cweb"

/*73:*/
#line 2152 "weaver-interface-metafont.cweb"

if(buffer[0]!='\0'){
buffer[255]= '\0';
size_t buffer_size= strlen(buffer)+1;
struct symbolic_token*new_token= 
(struct symbolic_token*)permanent_alloc(sizeof(struct symbolic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return false;
}
new_token->type= TYPE_SYMBOLIC;
new_token->next= NULL;
new_token->var= NULL;


/*126:*/
#line 3297 "weaver-interface-metafont.cweb"

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
else if(!strcmp(buffer,"color_r")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_R]);
}
else if(!strcmp(buffer,"color_g")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_G]);
}
else if(!strcmp(buffer,"color_b")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_B]);
}
else if(!strcmp(buffer,"color_a")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_A]);
}
else if(!strcmp(buffer,"monospace")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_MONO]);
}
/*:126*//*135:*/
#line 3451 "weaver-interface-metafont.cweb"

else if(!strcmp(buffer,"identity"))
new_token->var= 
&(mf->internal_transform_variables[INTERNAL_TRANSFORM_IDENTITY]);
/*:135*//*190:*/
#line 5128 "weaver-interface-metafont.cweb"

else if(!strcmp(buffer,"pensquare"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_PENSQUARE]);
/*:190*/
#line 2169 "weaver-interface-metafont.cweb"

#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
#line 2173 "weaver-interface-metafont.cweb"
 new_token->value= (char*)permanent_alloc(buffer_size);
memcpy(new_token->value,buffer,buffer_size);
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
/*:73*/
#line 1562 "weaver-interface-metafont.cweb"

}
/*:49*/
#line 1333 "weaver-interface-metafont.cweb"

{

char unknown_char[5];
memset(unknown_char,0,5);
unknown_char[0]= c;
fgets(&(unknown_char[1]),4,fp);
RAISE_ERROR_INVALID_CHAR(mf,NULL,line,unknown_char);
return false;
}
free_token_list(first_token);
*first_token= NULL;
*last_token= NULL;
return false;
}
/*72:*/
#line 2138 "weaver-interface-metafont.cweb"

if(aux_stack!=NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_MISSING_TOKEN(mf,NULL,OPTIONAL(aux_stack->link->line),
aux_stack->type);
return false;
}
/*:72*/
#line 1348 "weaver-interface-metafont.cweb"

fclose(fp);
return true;
}
/*:41*//*74:*/
#line 2228 "weaver-interface-metafont.cweb"

bool eval_program(struct metafont*mf,struct context*cx,
struct generic_token*first_token,
struct generic_token*last_token){
if(first_token==NULL)
return true;
if(!eval_list_of_statements(mf,cx,first_token,last_token))
return false;

/*81:*/
#line 2355 "weaver-interface-metafont.cweb"

mf->loading= false;
/*:81*//*96:*/
#line 2754 "weaver-interface-metafont.cweb"

if(cx->nesting_level> 0){
RAISE_ERROR_MISSING_TOKEN(mf,cx,OPTIONAL(cx->end_token_stack->line),
TYPE_ENDGROUP);
;return false;
}
/*:96*/
#line 2237 "weaver-interface-metafont.cweb"

return true;
}
/*:74*//*78:*/
#line 2292 "weaver-interface-metafont.cweb"

struct metafont*init_metafont(char*filename){
struct metafont*mf;
mf= (struct metafont*)permanent_alloc(sizeof(struct metafont));
if(mf==NULL)
return NULL;
MUTEX_INIT(mf->mutex);

size_t filename_size= strlen(filename)+1;
mf->file= (char*)permanent_alloc(filename_size);
memcpy(mf->file,filename,filename_size);

mf->loading= true;

/*102:*/
#line 2854 "weaver-interface-metafont.cweb"

mf->named_variables= NULL;
mf->variables= NULL;
/*:102*//*121:*/
#line 3213 "weaver-interface-metafont.cweb"

mf->internal_numeric_variables= 
permanent_alloc(8*sizeof(struct numeric_variable));
((struct numeric_variable*)mf->internal_numeric_variables)[0].value= 
((double)dpi)/72.0;
((struct numeric_variable*)mf->internal_numeric_variables)[1].value= 
((double)dpi)/2.54;
((struct numeric_variable*)mf->internal_numeric_variables)[2].value= 
((double)dpi)/25.4;

((struct numeric_variable*)mf->internal_numeric_variables)[3].value= 0.0;
((struct numeric_variable*)mf->internal_numeric_variables)[4].value= 0.0;
((struct numeric_variable*)mf->internal_numeric_variables)[5].value= 0.0;
((struct numeric_variable*)mf->internal_numeric_variables)[6].value= 1.0;

((struct numeric_variable*)mf->internal_numeric_variables)[7].value= 0.0;
{
int i;
for(i= 0;i<8;i++){
((struct numeric_variable*)
mf->internal_numeric_variables)[i].type= TYPE_T_NUMERIC;
((struct numeric_variable*)
mf->internal_numeric_variables)[i].next= NULL;
}
}
/*:121*//*132:*/
#line 3419 "weaver-interface-metafont.cweb"

mf->internal_transform_variables= 
(struct transform_variable*)
permanent_alloc(sizeof(struct transform_variable));
if(mf->internal_transform_variables==NULL){
if(permanent_free!=NULL)
permanent_free(mf);
return NULL;
}

mf->internal_transform_variables[0].type= TYPE_T_TRANSFORM;
INITIALIZE_IDENTITY_MATRIX(mf->internal_transform_variables[0].value);
/*:132*//*186:*/
#line 5072 "weaver-interface-metafont.cweb"

mf->internal_pen_variables= (struct pen_variable*)
permanent_alloc(1*sizeof(struct pen_variable));
if(mf->internal_pen_variables==NULL){
if(permanent_free!=NULL)
permanent_free(mf);
return NULL;
}
mf->internal_pen_variables[0].format= NULL;
mf->internal_pen_variables[0].type= TYPE_T_PEN;
mf->internal_pen_variables[0].flags= FLAG_CONVEX|FLAG_STRAIGHT|
FLAG_SQUARE;
mf->internal_pen_variables[0].referenced= NULL;
mf->internal_pen_variables[0].gl_vbo= 0;
mf->internal_pen_variables[0].indices= 4;
mf->internal_pen_variables[0].permanent= true;
INITIALIZE_IDENTITY_MATRIX(mf->internal_pen_variables[0].gl_matrix);
/*:186*//*240:*/
#line 6256 "weaver-interface-metafont.cweb"

mf->have_stored_normaldeviate= false;
/*:240*//*590:*/
#line 16625 "weaver-interface-metafont.cweb"

mf->mono_expr_begin= mf->mono_expr_end= NULL;
/*:590*//*616:*/
#line 17183 "weaver-interface-metafont.cweb"

memset(mf->glyphs,0,sizeof(struct _glyph*)*332);
mf->first_glyph= NULL;
memset(mf->first_glyph_symbol,0,5);
mf->number_of_glyphs= 0;
/*:616*//*665:*/
#line 18804 "weaver-interface-metafont.cweb"

mf->err= mf->errno_line= 0;
mf->errno_character[0]= '\0';
memset(mf->errno_str,0,32);
mf->errno_int= 0;
/*:665*/
#line 2306 "weaver-interface-metafont.cweb"

return mf;
}
struct context*init_context(struct metafont*mf){
struct context*cx;
cx= (struct context*)temporary_alloc(sizeof(struct context));
if(cx==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return NULL;
}
cx->current_character[0]= '\0';

/*89:*/
#line 2595 "weaver-interface-metafont.cweb"

cx->nesting_level= 0;
cx->end_token_stack= NULL;
/*:89*//*106:*/
#line 2910 "weaver-interface-metafont.cweb"

cx->variables= NULL;
/*:106*//*122:*/
#line 3243 "weaver-interface-metafont.cweb"

cx->internal_numeric_variables= 
temporary_alloc(3*sizeof(struct numeric_variable));
((struct numeric_variable*)cx->internal_numeric_variables)[0].value= 0.0;
((struct numeric_variable*)cx->internal_numeric_variables)[1].value= 0.0;
((struct numeric_variable*)cx->internal_numeric_variables)[2].value= 0.0;
{
int i;
for(i= 0;i<3;i++){
((struct numeric_variable*)
cx->internal_numeric_variables)[i].type= TYPE_T_NUMERIC;
((struct numeric_variable*)
cx->internal_numeric_variables)[i].next= NULL;
}
}
/*:122*//*185:*/
#line 5052 "weaver-interface-metafont.cweb"

cx->currentpen= (struct pen_variable*)
permanent_alloc(sizeof(struct pen_variable));
if(cx->currentpen==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return NULL;
}
cx->currentpen->format= NULL;
cx->currentpen->type= TYPE_T_PEN;
cx->currentpen->flags= FLAG_NULL;
cx->currentpen->referenced= NULL;
cx->currentpen->gl_vbo= 0;
cx->currentpen->indices= 0;
cx->currentpen->permanent= true;
INITIALIZE_IDENTITY_MATRIX(cx->currentpen->gl_matrix);
/*:185*//*197:*/
#line 5218 "weaver-interface-metafont.cweb"

cx->currentpicture= (struct picture_variable*)
temporary_alloc(sizeof(struct picture_variable));
if(cx->currentpicture==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return NULL;
}
cx->currentpicture->type= TYPE_T_PICTURE;
cx->currentpicture->width= -1;
cx->currentpicture->height= -1;
cx->currentpicture->texture= 0;
/*:197*//*504:*/
#line 13591 "weaver-interface-metafont.cweb"

cx->pen_lft= cx->pen_rt= cx->pen_top= cx->pen_bot= 0.0;
/*:504*//*583:*/
#line 16503 "weaver-interface-metafont.cweb"

cx->color[0]= mf->internal_numeric_variables[INTERNAL_NUMERIC_R].value;
cx->color[1]= mf->internal_numeric_variables[INTERNAL_NUMERIC_G].value;
cx->color[2]= mf->internal_numeric_variables[INTERNAL_NUMERIC_B].value;
cx->color[3]= mf->internal_numeric_variables[INTERNAL_NUMERIC_A].value;
/*:583*//*595:*/
#line 16687 "weaver-interface-metafont.cweb"

cx->currentpicture_fb= 0;
/*:595*//*610:*/
#line 17002 "weaver-interface-metafont.cweb"

cx->current_depth= 0;
/*:610*/
#line 2318 "weaver-interface-metafont.cweb"

return cx;
}
/*:78*//*80:*/
#line 2337 "weaver-interface-metafont.cweb"

void destroy_context(struct context*cx){
if(temporary_free!=NULL){

/*93:*/
#line 2686 "weaver-interface-metafont.cweb"

if(temporary_free!=NULL){
while(cx->end_token_stack!=NULL){
struct linked_token*end_tok= cx->end_token_stack;
cx->end_token_stack= (struct linked_token*)(end_tok->next);
temporary_free(end_tok);
}
}
/*:93*//*107:*/
#line 2916 "weaver-interface-metafont.cweb"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*141:*/
#line 3602 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL)
path_recursive_free(temporary_free,path,false);
}
/*:141*//*182:*/
#line 5008 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&temporary_free!=NULL)
path_recursive_free(temporary_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
/*191:*/
#line 5142 "weaver-interface-metafont.cweb"

if(cx->currentpen->referenced==pen){
cx->currentpen->format= NULL;
cx->currentpen->type= TYPE_T_PEN;
cx->currentpen->flags= FLAG_NULL;
cx->currentpen->referenced= NULL;
cx->currentpen->gl_vbo= 0;
cx->currentpen->indices= 0;
}
/*:191*/
#line 5015 "weaver-interface-metafont.cweb"

}
/*:182*//*195:*/
#line 5196 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:195*/
#line 2922 "weaver-interface-metafont.cweb"

temporary_free(v);
v= next;
}
}
/*:107*//*125:*/
#line 3287 "weaver-interface-metafont.cweb"

if(temporary_free!=NULL)
temporary_free(cx->internal_numeric_variables);
/*:125*//*189:*/
#line 5113 "weaver-interface-metafont.cweb"

if(temporary_free!=NULL){
if(cx->currentpen->format!=NULL){
temporary_free(cx->currentpen->format->points);
temporary_free(cx->currentpen->format);
}
temporary_free(cx->currentpen);
}
/*:189*//*198:*/
#line 5235 "weaver-interface-metafont.cweb"

if(cx->currentpicture->texture!=0)
glDeleteTextures(1,&(cx->currentpicture->texture));
if(temporary_free!=NULL)
temporary_free(cx->currentpicture);
/*:198*/
#line 2341 "weaver-interface-metafont.cweb"

temporary_free(cx);
}
}
/*:80*//*83:*/
#line 2402 "weaver-interface-metafont.cweb"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
struct generic_token*begin_list,
struct generic_token*end_list){
struct generic_token*begin,*end= NULL;
begin= begin_list;
/*599:*/
#line 16761 "weaver-interface-metafont.cweb"

GLint _viewport[4];
glGetIntegerv(GL_VIEWPORT,_viewport);
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_fb);
/*:599*/
#line 2408 "weaver-interface-metafont.cweb"

while(begin!=NULL){


while(begin!=NULL&&begin->type==TYPE_SEMICOLON){
if(begin!=end_list)
begin= begin->next;
else
begin= NULL;
}
end= begin;

if(end!=NULL){
while(end!=end_list&&end->next->type!=TYPE_SEMICOLON)
end= end->next;
}

if(begin!=NULL){
if(!eval_statement(mf,cx,begin,&end))
return false;

if(end!=end_list)
begin= end->next;
else
begin= NULL;
}
}
/*600:*/
#line 16770 "weaver-interface-metafont.cweb"

glBindFramebuffer(GL_FRAMEBUFFER,previous_fb);
glViewport(_viewport[0],_viewport[1],_viewport[2],_viewport[3]);
/*:600*/
#line 2435 "weaver-interface-metafont.cweb"

return true;
}
/*:83*//*87:*/
#line 2553 "weaver-interface-metafont.cweb"

bool eval_statement(struct metafont*mf,struct context*cx,
struct generic_token*begin,struct generic_token**end){
/*94:*/
#line 2727 "weaver-interface-metafont.cweb"

if(begin->type==TYPE_BEGINGROUP){
begin_nesting_level(mf,cx,begin);

*end= begin;
return true;
}
/*:94*//*95:*/
#line 2740 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_ENDGROUP){
if(!end_nesting_level(mf,cx,begin))
return false;
*end= begin;
return true;
}
/*:95*//*489:*/
#line 13182 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_IF){
struct generic_token*begin_bool,*end_bool;
struct boolean_variable b;

begin_bool= begin->next;
end_bool= begin_bool;
while(end_bool!=NULL&&end_bool!=*end&&end_bool->next->type!=TYPE_COLON)
end_bool= end_bool->next;
if(end_bool==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(end_bool==*end){
RAISE_ERROR_INCOMPLETE_STATEMENT(mf,cx,OPTIONAL(begin->line));
return false;
}

if(!eval_boolean_expression(mf,cx,begin_bool,end_bool,&b))
return false;
if(b.value==1){
*end= end_bool->next;
return true;
}
else{
struct generic_token*t= ((struct linked_token*)begin)->link;
while(t!=NULL){
if(t->type==TYPE_FI){

*end= t;
return true;
}
else if(t->type==TYPE_ELSE){

*end= t->next;
if((*end)==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
else if((*end)->type!=TYPE_COLON){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL((*end)->line),
TYPE_COLON,(*end));
return false;
}
return true;
}
else if(t->type==TYPE_ELSEIF){

begin_bool= t->next;
end_bool= begin_bool;
while(end_bool!=NULL&&end_bool!=*end&&
end_bool->next->type!=TYPE_COLON)
end_bool= end_bool->next;
if(end_bool==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(!eval_boolean_expression(mf,cx,begin_bool,end_bool,&b))
return false;
if(b.value==1){
*end= end_bool->next;
return true;
}
}
t= ((struct linked_token*)t)->next;
}
}

RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
/*:489*//*490:*/
#line 13268 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_ELSEIF||begin->type==TYPE_ELSE){
struct generic_token*t;
t= ((struct linked_token*)begin)->link;
while(t!=NULL){
if(t->type==TYPE_FI){

*end= t;
return true;
}
t= ((struct linked_token*)t)->link;
}

RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
/*:490*//*491:*/
#line 13290 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_FI){
*end= begin;
return true;
}
/*:491*//*494:*/
#line 13347 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_FOR){
struct numeric_variable*control;
struct numeric_variable increment;
struct begin_loop_token*for_token= (struct begin_loop_token*)begin;
struct generic_token*current_token= begin,*begin_expr,*end_expr;
if(!(for_token->running)){
begin_nesting_level(mf,cx,begin);
/*495:*/
#line 13366 "weaver-interface-metafont.cweb"

{
struct symbolic_token*var_token= (struct symbolic_token*)for_token->next;
if(var_token==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(var_token->line));
return false;
}
if(var_token->type!=TYPE_SYMBOLIC){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(var_token->line),
TYPE_SYMBOLIC,(struct generic_token*)var_token);
return false;
}
if(var_token->var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(var_token->line),
var_token);
return false;
}
control= var_token->var;
if(control->type!=TYPE_T_NUMERIC){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(var_token->line),
var_token,control->type,
TYPE_T_NUMERIC);
return false;
}
for_token->control_var= &(control->value);
}
/*:495*//*496:*/
#line 13397 "weaver-interface-metafont.cweb"

{
current_token= for_token->next->next;
if(current_token==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(current_token->line));
return false;
}
if(current_token->type!=TYPE_ASSIGNMENT&&
current_token->type!=TYPE_EQUAL){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(current_token->line),
TYPE_EQUAL,current_token);
return false;
}
}
/*:496*//*497:*/
#line 13420 "weaver-interface-metafont.cweb"

{
begin_expr= current_token->next;
if(begin_expr==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(current_token->line));
return false;
}
end_expr= begin_expr;
while(end_expr->next!=NULL&&end_expr->next->type!=TYPE_STEP)
end_expr= end_expr->next;
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,control))
return false;
current_token= end_expr;
}
/*:497*/
#line 13355 "weaver-interface-metafont.cweb"

}
/*498:*/
#line 13444 "weaver-interface-metafont.cweb"

{
while(current_token!=NULL&&current_token->type!=TYPE_STEP)
current_token= current_token->next;
if(current_token==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(current_token->line));
return false;
}
begin_expr= current_token->next;
end_expr= begin_expr;
while(end_expr!=NULL&&end_expr->next!=NULL&&
end_expr->next->type!=TYPE_UNTIL)
end_expr= end_expr->next;
if(end_expr==NULL||end_expr->next==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(current_token->line));
return false;
}
if(end_expr->next->type==TYPE_SEMICOLON||
end_expr->next->type==TYPE_COLON){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(current_token->line),
TYPE_UNTIL,end_expr->next);
return false;
}
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&increment))
return false;
if(for_token->running)
*(for_token->control_var)+= increment.value;
else
for_token->running= true;
current_token= end_expr;
}
/*:498*//*499:*/
#line 13481 "weaver-interface-metafont.cweb"

{
struct numeric_variable limit;
current_token= current_token->next;
if(current_token->next==NULL){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(current_token->line),
TYPE_T_NUMERIC);
return false;
}
begin_expr= current_token->next;
end_expr= begin_expr;
while(end_expr->next!=NULL&&end_expr->next->type!=TYPE_COLON){
if(end_expr->next->type==TYPE_SEMICOLON){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(current_token->line),
TYPE_SEMICOLON,end_expr->next);
return false;
}
end_expr= end_expr->next;
}
if(end_expr->next==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(current_token->line));
return false;
}
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&limit))
return false;
if((increment.value> 0&&*(for_token->control_var)> limit.value)||
(increment.value<0&&*(for_token->control_var)<limit.value)){

for_token->running= false;
*end= (struct generic_token*)for_token->end;
if(!end_nesting_level(mf,cx,*end))
return false;
return true;
}
else{

*end= end_expr->next;
return true;
}
}
/*:499*/
#line 13357 "weaver-interface-metafont.cweb"

}
/*:494*//*500:*/
#line 13531 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_ENDFOR){
struct linked_token*endfor_token= (struct linked_token*)begin;
*end= endfor_token->link;
return true;
}
/*:500*//*620:*/
#line 17370 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_BEGINCHAR&&mf->loading){
DECLARE_NESTING_CONTROL();
struct _glyph*glyph;
struct generic_token*t= begin->next;
if(t==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(begin==*end){
RAISE_ERROR_INCOMPLETE_STATEMENT(mf,cx,OPTIONAL(begin->line));
return false;
}
if(t->type!=TYPE_OPEN_PARENTHESIS){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(t->line),
TYPE_OPEN_PARENTHESIS,t);
return false;
}
if(t!=*end)
t= t->next;
if(t==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(t->type!=TYPE_STRING){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(t->line),
TYPE_STRING,t);
return false;
}
{
struct string_token*str= (struct string_token*)t;
glyph= get_glyph(mf,(unsigned char*)str->value,true);
if(glyph==NULL)
return false;
if(mf->first_glyph==NULL){
mf->first_glyph= glyph;
memcpy(mf->first_glyph_symbol,(unsigned char*)str->value,4);
}
if(glyph->begin!=NULL){
RAISE_ERROR_DUPLICATE_GLYPH(mf,cx,OPTIONAL(begin->line),str->value);
return false;
}
glyph->begin= begin;
str->glyph= glyph;
}
{
int number_of_commas= 0;
struct generic_token*prev= t;
while(t!=NULL&&t!=*end){
COUNT_NESTING(t);
if(IS_NOT_NESTED()){
if(t->type==TYPE_COMMA&&prev->type!=TYPE_COMMA)
number_of_commas++;
}
prev= t;
t= t->next;
if(IS_NOT_NESTED()&&t->type==TYPE_CLOSE_PARENTHESIS)
break;
if(t->type==TYPE_SEMICOLON||t->type==TYPE_ENDCHAR)
break;
}
if(t==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(prev->line));
return false;
}
if(t->type!=TYPE_CLOSE_PARENTHESIS){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(t->line),
TYPE_CLOSE_PARENTHESIS,t);
return false;
}
if(number_of_commas!=3){
RAISE_ERROR_WRONG_NUMBER_OF_PARAMETERS(mf,cx,OPTIONAL(t->line),
TYPE_BEGINCHAR,4,
number_of_commas+1);
return false;
}
t= ((struct linked_token*)begin)->link;
glyph->end= t;
*end= t;
}
mf->number_of_glyphs++;
return true;
}
/*:620*//*621:*/
#line 17462 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_ENDCHAR&&mf->loading){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),begin);
return false;
}
/*:621*//*623:*/
#line 17496 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_BEGINCHAR){
DECLARE_NESTING_CONTROL();
struct generic_token*t,*begin_expr,*end_expr;
struct string_token*str;
struct numeric_variable width,height,depth;
begin_nesting_level(mf,cx,begin);

t= begin->next;
t= t->next;
str= (struct string_token*)t;
if(str->type!=TYPE_STRING){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(begin->line),TYPE_STRING,
(struct generic_token*)str);
return false;
}
cx->current_glyph= str->glyph;
/*649:*/
#line 18360 "weaver-interface-metafont.cweb"

{
struct kerning*existing_kerning= cx->current_glyph->kern;
while(existing_kerning!=NULL){
existing_kerning->kern= 0.0;
existing_kerning= existing_kerning->next;
}
}
/*:649*/
#line 17513 "weaver-interface-metafont.cweb"

memset(cx->current_character,0,5);
memcpy(cx->current_character,str->value,4);

t= t->next;
t= t->next;
begin_expr= t;
do{
COUNT_NESTING(t);
end_expr= t;
t= t->next;
}while(!IS_NOT_NESTED()||t->type!=TYPE_COMMA);

if(mf->internal_numeric_variables[INTERNAL_NUMERIC_MONO].value> 0.0&&
mf->mono_expr_begin!=NULL){
if(!eval_numeric_expression(mf,cx,mf->mono_expr_begin,
mf->mono_expr_end,&width))
return false;
}
else if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&width))
return false;
t= t->next;
begin_expr= t;
do{
COUNT_NESTING(t);
end_expr= t;
t= t->next;
}while(!IS_NOT_NESTED()||t->type!=TYPE_COMMA);
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&height))
return false;
t= t->next;
begin_expr= t;
do{
COUNT_NESTING(t);
end_expr= t;
t= t->next;
}while(!IS_NOT_NESTED()||t->type!=TYPE_CLOSE_PARENTHESIS);
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&depth))
return false;
if(height.value+depth.value<=0.0||width.value<=0){
RAISE_ERROR_INVALID_DIMENSION_GLYPH(mf,cx,OPTIONAL(begin->line),
width.value,
height.value+depth.value);
return false;
}
*end= t;
{
unsigned char*data;
struct numeric_variable*vars;
size_t size;
struct picture_variable*pic= cx->currentpicture;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
vars= ((struct numeric_variable*)cx->internal_numeric_variables);
#ifdef W_WeaveFont_DISABLE_MULTISAMPLE
cx->current_depth= round(depth.value);
pic->width= round(width.value);
pic->height= (round(height.value)+round(depth.value));
vars[INTERNAL_NUMERIC_W].value= round(width.value);
vars[INTERNAL_NUMERIC_H].value= round(height.value);
vars[INTERNAL_NUMERIC_D].value= round(depth.value);
#else
#line 17575 "weaver-interface-metafont.cweb"
 cx->current_depth= 2*round(depth.value);
pic->width= 2*round(width.value);
pic->height= 2*(round(height.value)+round(depth.value));
vars[INTERNAL_NUMERIC_W].value= 2*round(width.value);
vars[INTERNAL_NUMERIC_H].value= 2*round(height.value);
vars[INTERNAL_NUMERIC_D].value= 2*round(depth.value);
#endif
#line 17582 "weaver-interface-metafont.cweb"
 size= pic->width*pic->height*4;
data= temporary_alloc(size);
if(data==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}

memset(data,255,size);
{
size_t i;
for(i= 3;i<size;i+= 4)
data[i]= 0;
}
glGenTextures(1,&(pic->texture));
glBindTexture(GL_TEXTURE_2D,pic->texture);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pic->width,pic->height,0,
GL_RGBA,GL_UNSIGNED_BYTE,data);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glBindTexture(GL_TEXTURE_2D,0);
if(temporary_free!=NULL)
temporary_free(data);
/*597:*/
#line 16727 "weaver-interface-metafont.cweb"

{
if(cx->currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&(cx->currentpicture_fb));
}
cx->currentpicture_fb= 0;
}
/*:597*/
#line 17606 "weaver-interface-metafont.cweb"

}
return true;
}
/*:623*//*624:*/
#line 17621 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_ENDCHAR){
struct picture_variable*currentpicture= cx->currentpicture;
if(!end_nesting_level(mf,cx,begin))
return false;
cx->current_glyph->width= round(currentpicture->width);
cx->current_glyph->depth= round(cx->current_depth);
cx->current_glyph->height= round(currentpicture->height-
cx->current_depth);
cx->current_glyph->texture= currentpicture->texture;
#ifndef W_WeaveFont_DISABLE_MULTISAMPLE
cx->current_glyph->width/= 2;
cx->current_glyph->depth/= 2;
cx->current_glyph->height/= 2;
#endif
#line 17636 "weaver-interface-metafont.cweb"
 cx->current_glyph->need_rendering= false;
currentpicture->width= -1;
currentpicture->height= -1;
currentpicture->texture= 0;
*end= begin;
return true;
}
/*:624*/
#line 2556 "weaver-interface-metafont.cweb"

/*108:*/
#line 2936 "weaver-interface-metafont.cweb"

else if(begin->type>=TYPE_T_BOOLEAN&&begin->type<=TYPE_T_NUMERIC){
int type= begin->type;
struct symbolic_token*variable= (struct symbolic_token*)(begin->next);
if(variable==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(begin==*end){
RAISE_ERROR_INCOMPLETE_STATEMENT(mf,cx,OPTIONAL(begin->line));
return false;
}
do{
if(variable->type!=TYPE_SYMBOLIC||!strcmp(variable->value,"w")||
!strcmp(variable->value,"h")||!strcmp(variable->value,"d")||
!strcmp(variable->value,"currentpen")||
!strcmp(variable->value,"currentpicture")){
RAISE_ERROR_INVALID_NAME(mf,cx,OPTIONAL(variable->line),
(struct generic_token*)variable,
variable->type);
return false;
}
/*109:*/
#line 2982 "weaver-interface-metafont.cweb"

{
void*variable_pointer;
if(mf->loading){
if(cx->nesting_level!=0||variable->value[0]=='_')
variable_pointer= insert_variable(mf,type,&(mf->variables));
else
variable_pointer= insert_named_global_variable(mf,type,variable);
}
else{
variable_pointer= insert_variable(mf,type,&(cx->variables));
}
if(variable_pointer==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(variable->line));
return false;
}
update_token_pointer_for_variable(variable,variable_pointer);
}
/*:109*/
#line 2958 "weaver-interface-metafont.cweb"

if(variable!=(struct symbolic_token*)*end)
variable= (struct symbolic_token*)(variable->next);
else{
variable= NULL;
continue;
}
if(variable->type!=TYPE_COMMA){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(variable->line),
TYPE_COMMA,(struct generic_token*)variable);
return false;
}
if(variable==(struct symbolic_token*)*end){
RAISE_ERROR_INCOMPLETE_STATEMENT(mf,cx,OPTIONAL((*end)->line));
return false;
}
variable= (struct symbolic_token*)(variable->next);
}while(variable!=NULL);
return true;
}
/*:108*/
#line 2557 "weaver-interface-metafont.cweb"

/*203:*/
#line 5321 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_SYMBOLIC){
struct symbolic_token*var= (struct symbolic_token*)begin;
struct generic_token*begin_expression;
int type= 0;
int number_of_variables= 0;
do{
if(var->type!=TYPE_SYMBOLIC){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(var->line),TYPE_SYMBOLIC,
(struct generic_token*)var);
return false;
}


if(!strcmp(var->value,"h"))
var->var= 
(void*)&(cx->internal_numeric_variables[INTERNAL_NUMERIC_H]);
else if(!strcmp(var->value,"w"))
var->var= 
(void*)&(cx->internal_numeric_variables[INTERNAL_NUMERIC_W]);
else if(!strcmp(var->value,"d"))
var->var= 
(void*)&(cx->internal_numeric_variables[INTERNAL_NUMERIC_D]);
else if(!strcmp(var->value,"currentpen"))
var->var= (void*)cx->currentpen;
else if(!strcmp(var->value,"currentpicture"))
var->var= (void*)cx->currentpicture;
if(var->var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(var->line),var);
return false;
}
number_of_variables++;
if(type==0)
type= ((struct variable*)(var->var))->type;
else if(((struct variable*)(var->var))->type!=type){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(var->line),
var,
((struct variable*)(var->var))->type,
type);
return false;
}
if(var!=(struct symbolic_token*)end)
var= (struct symbolic_token*)(var->next);
else
var= NULL;
if(var->type!=TYPE_EQUAL&&var->type!=TYPE_ASSIGNMENT){
RAISE_ERROR_UNKNOWN_STATEMENT(mf,cx,OPTIONAL(begin->line));
return false;
}
if(var!=(struct symbolic_token*)*end)
var= (struct symbolic_token*)(var->next);
else
var= NULL;
}while(var!=NULL&&(var->next->type==TYPE_EQUAL||
var->next->type==TYPE_ASSIGNMENT));
if(var==NULL){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin->line),type);
return false;
}
begin_expression= (struct generic_token*)var;
/*204:*/
#line 5402 "weaver-interface-metafont.cweb"

if(type==TYPE_T_NUMERIC){
int i;
struct numeric_variable result;

if(!eval_numeric_expression(mf,cx,begin_expression,*end,&result))
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){

((struct numeric_variable*)(var->var))->value= result.value;

var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:204*/
#line 5381 "weaver-interface-metafont.cweb"

/*244:*/
#line 6340 "weaver-interface-metafont.cweb"

else if(type==TYPE_T_PAIR){
int i;
struct pair_variable result;
if(!eval_pair_expression(mf,cx,begin_expression,*end,&result))
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){
struct pair_variable*v= (struct pair_variable*)var->var;
v->x= result.x;
v->y= result.y;
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:244*/
#line 5382 "weaver-interface-metafont.cweb"

/*273:*/
#line 7110 "weaver-interface-metafont.cweb"

else if(type==TYPE_T_TRANSFORM){
int i;
struct transform_variable result;
if(!eval_transform_expression(mf,cx,begin_expression,*end,&result))
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){
memcpy(((struct transform_variable*)var->var)->value,result.value,
sizeof(float)*9);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:273*/
#line 5383 "weaver-interface-metafont.cweb"

/*299:*/
#line 7652 "weaver-interface-metafont.cweb"

else if(type==TYPE_T_PATH){
int i;
struct path_variable result;
void*(*alloc)(size_t);
void(*disalloc)(void*);
if(!eval_path_expression(mf,cx,begin_expression,*end,&result))
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){
struct path_variable*dst= (struct path_variable*)var->var;
if(dst->permanent){
alloc= permanent_alloc;
disalloc= permanent_free;
}
else{
alloc= temporary_alloc;
disalloc= temporary_free;
}

if(dst->length!=-1&&disalloc!=NULL)
path_recursive_free(disalloc,dst,false);

if(!recursive_copy_points(mf,NULL,alloc,&dst,&result,false))
return false;
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&result,false);
}
/*:299*/
#line 5384 "weaver-interface-metafont.cweb"

/*380:*/
#line 9925 "weaver-interface-metafont.cweb"

else if(type==TYPE_T_PEN){
int i;
struct pen_variable result;
if(!eval_pen_expression(mf,cx,begin_expression,*end,&result))
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){
if(!assign_pen_variable(mf,cx,(struct pen_variable*)var->var,
&result))
return false;
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
if(temporary_free!=NULL&&result.format!=NULL)
path_recursive_free(temporary_free,result.format,true);
if(result.gl_vbo!=0&&result.referenced==NULL)
glDeleteBuffers(1,&(result.gl_vbo));
}
/*:380*/
#line 5385 "weaver-interface-metafont.cweb"

/*416:*/
#line 10799 "weaver-interface-metafont.cweb"

else if(type==TYPE_T_PICTURE){
int i;
struct picture_variable result;
if(!eval_picture_expression(mf,cx,begin_expression,*end,&result))
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){
if(i==0){
struct picture_variable*pic= (struct picture_variable*)var->var;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
pic->width= result.width;
pic->height= result.height;
pic->texture= result.texture;
pic->type= TYPE_T_PICTURE;

if(pic==cx->currentpicture){

/*597:*/
#line 16727 "weaver-interface-metafont.cweb"

{
if(cx->currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&(cx->currentpicture_fb));
}
cx->currentpicture_fb= 0;
}
/*:597*/
#line 10818 "weaver-interface-metafont.cweb"

}
}
else
assign_picture_variable(mf,cx,(struct picture_variable*)var->var,
&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:416*/
#line 5386 "weaver-interface-metafont.cweb"

/*468:*/
#line 12203 "weaver-interface-metafont.cweb"

else if(type==TYPE_T_BOOLEAN){
int i;
bool ret;
struct boolean_variable result;
ret= eval_boolean_expression(mf,cx,begin_expression,*end,&result);
if(!ret)
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){
((struct boolean_variable*)var->var)->value= result.value;
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:468*/
#line 5387 "weaver-interface-metafont.cweb"

return true;
}
/*:203*/
#line 2558 "weaver-interface-metafont.cweb"

/*573:*/
#line 16149 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_PICKUP){
struct generic_token*end_expression= *end;
struct generic_token*next_token= begin->next;
if(begin==*end||(next_token->type!=TYPE_NULLPEN&&
next_token->type!=TYPE_SYMBOLIC&&
next_token->type!=TYPE_PENCIRCLE&&
next_token->type!=TYPE_PENSEMICIRCLE)){
RAISE_ERROR_NO_PICKUP_PEN(mf,cx,OPTIONAL(next_token->line));
return false;
}
if(cx->currentpen->gl_vbo!=0)
glDeleteBuffers(1,&(cx->currentpen->gl_vbo));
if(next_token->type==TYPE_NULLPEN){
cx->currentpen->flags= FLAG_NULL;
cx->currentpen->referenced= NULL;
cx->currentpen->gl_vbo= 0;
}
else if(next_token->type==TYPE_PENCIRCLE){
cx->currentpen->flags= FLAG_CONVEX|FLAG_CIRCULAR;
cx->currentpen->referenced= NULL;
cx->currentpen->gl_vbo= 0;
}
else if(next_token->type==TYPE_PENSEMICIRCLE){
cx->currentpen->flags= FLAG_CONVEX|FLAG_SEMICIRCULAR;
cx->currentpen->referenced= NULL;
cx->currentpen->gl_vbo= 0;
}
else{
struct symbolic_token*symbol= ((struct symbolic_token*)next_token);
struct pen_variable*var= (struct pen_variable*)(symbol->var);
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(next_token->line),
symbol);
return false;
}
if(var->type!=TYPE_T_PEN){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(next_token->line),
symbol,var->type,
TYPE_T_PEN);
return false;
}
if(var->format==NULL&&var->flags==false){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(next_token->line),
symbol,TYPE_T_PEN);
return false;
}
cx->currentpen->referenced= var;
}
INITIALIZE_IDENTITY_MATRIX(cx->currentpen->gl_matrix);
/*574:*/
#line 16214 "weaver-interface-metafont.cweb"

while(next_token!=end_expression){
struct generic_token*begin_subexpr,*end_subexpr;
DECLARE_NESTING_CONTROL();
next_token= next_token->next;
if(next_token==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(next_token==end_expression){
if(next_token->type==TYPE_ROTATED||
next_token->type==TYPE_SCALED||
next_token->type==TYPE_SLANTED||
next_token->type==TYPE_XSCALED||
next_token->type==TYPE_YSCALED){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_NUMERIC);
}
else if(next_token->type==TYPE_SHIFTED||
next_token->type==TYPE_ZSCALED){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PAIR);
}
else if(next_token->type==TYPE_TRANSFORMED){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_TRANSFORM);
}
else{
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),next_token);
}
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
TRANSFORM_ROTATE(cx->currentpen->gl_matrix,a.value*0.0174533);
break;
case TYPE_SCALED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_SCALE(cx->currentpen->gl_matrix,a.value);

if(cx->currentpen->referenced){
struct pen_variable*v= cx->currentpen->referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_SHIFTED:
if(!eval_pair_expression(mf,cx,begin_subexpr,end_subexpr,&p))
return false;
TRANSFORM_SHIFT(cx->currentpen->gl_matrix,p.x,p.y);
break;
case TYPE_SLANTED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_SLANT(cx->currentpen->gl_matrix,a.value);

if(cx->currentpen->referenced){
struct pen_variable*v= cx->currentpen->referenced;
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
TRANSFORM_SCALE_X(cx->currentpen->gl_matrix,a.value);

if(cx->currentpen->referenced){
struct pen_variable*v= cx->currentpen->referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_YSCALED:
if(!eval_numeric_expression(mf,cx,begin_subexpr,end_subexpr,&a))
return false;
TRANSFORM_SCALE_Y(cx->currentpen->gl_matrix,a.value);

if(cx->currentpen->referenced){
struct pen_variable*v= cx->currentpen->referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_ZSCALED:
if(!eval_pair_expression(mf,cx,begin_subexpr,end_subexpr,&p))
return false;
TRANSFORM_SCALE_Z(cx->currentpen->gl_matrix,p.x,p.y);

if(cx->currentpen->referenced){
struct pen_variable*v= cx->currentpen->referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
case TYPE_TRANSFORMED:
if(!eval_transform_expression(mf,cx,begin_subexpr,end_subexpr,&t))
return false;
MATRIX_MULTIPLICATION(cx->currentpen->gl_matrix,t.value);

if(cx->currentpen->referenced){
struct pen_variable*v= cx->currentpen->referenced;
if(v->gl_vbo!=0&&a.value> 1.0&&!(v->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(v->gl_vbo));
v->gl_vbo= 0;
}
}
break;
default:
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(next_token->line),
next_token);
return false;
}
next_token= end_subexpr;
}
/*:574*//*575:*/
#line 16369 "weaver-interface-metafont.cweb"

{
float final_transform_matrix[9];
if(cx->currentpen->referenced==NULL){
memcpy(final_transform_matrix,cx->currentpen->gl_matrix,
9*sizeof(float));
if(!triangulate_pen(mf,cx,cx->currentpen,final_transform_matrix))
return false;
}
else{
memcpy(final_transform_matrix,
cx->currentpen->referenced->gl_matrix,9*sizeof(float));
MATRIX_MULTIPLICATION(final_transform_matrix,
cx->currentpen->gl_matrix);
if(!triangulate_pen(mf,cx,cx->currentpen->referenced,
final_transform_matrix))
return false;
}
}
/*:575*/
#line 16199 "weaver-interface-metafont.cweb"

return true;
}
/*:573*//*586:*/
#line 16539 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_PICKCOLOR){
struct numeric_variable result;
int i;
DECLARE_NESTING_CONTROL();
struct generic_token*begin_expr,*end_expr;
begin_expr= begin->next;
if(begin_expr==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin_expr->line));
return false;
}
if(begin_expr->type!=TYPE_OPEN_PARENTHESIS){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(begin_expr->line),
TYPE_OPEN_PARENTHESIS,begin_expr);
return false;
}
begin_expr= begin_expr->next;
for(i= 0;i<4;i++){
end_expr= begin_expr;
if(end_expr==NULL||end_expr->type==TYPE_COMMA||
end_expr->type==TYPE_CLOSE_PARENTHESIS){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(end_expr->line),
TYPE_T_NUMERIC);
return false;
}
while(end_expr!=NULL){
COUNT_NESTING(end_expr);
if(IS_NOT_NESTED()&&end_expr->next!=NULL&&
((i<3&&end_expr->next->type==TYPE_COMMA)||
(i==3&&end_expr->next->type==TYPE_CLOSE_PARENTHESIS)))
break;
end_expr= end_expr->next;
}
if(end_expr==NULL){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_NUMERIC);
return false;
}
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&result))
return false;
cx->color[i]= result.value;
begin_expr= end_expr->next->next;
}
return true;
}
/*:586*//*591:*/
#line 16633 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_MONOWIDTH){
if(begin==*end){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_NUMERIC);
return false;
}
mf->mono_expr_begin= begin->next;
mf->mono_expr_end= *end;
return true;
}
/*:591*//*605:*/
#line 16851 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_DRAW){
struct path_variable path;

if(!eval_path_expression(mf,cx,begin->next,*end,&path))
return false;
if(!drawing_commands(mf,cx,&path,0))
return false;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&path,false);
return true;
}
else if(begin->type==TYPE_ERASE){
struct path_variable path;

if(!eval_path_expression(mf,cx,begin->next,*end,&path))
return false;
if(!drawing_commands(mf,cx,&path,1))
return false;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&path,false);
return true;
}
/*:605*//*633:*/
#line 17870 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_SHIPIT&&mf->loading){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),begin);
return false;
}
/*:633*//*634:*/
#line 17884 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_SHIPIT){
struct picture_variable*currentpicture;
if(begin->next==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(begin->next->type!=TYPE_SEMICOLON){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(begin->line),TYPE_SEMICOLON,
begin->next);
return false;
}
currentpicture= cx->currentpicture;
cx->current_glyph->texture= currentpicture->texture;
cx->current_glyph->width= round(currentpicture->width);
cx->current_glyph->depth= round(cx->current_depth);
cx->current_glyph->height= round(currentpicture->height-
cx->current_depth);
cx->current_glyph->texture= currentpicture->texture;
#ifndef W_WeaveFont_DISABLE_MULTISAMPLE
cx->current_glyph->width/= 2;
cx->current_glyph->depth/= 2;
cx->current_glyph->height/= 2;
#endif
#line 17908 "weaver-interface-metafont.cweb"
 currentpicture->width= -1;
currentpicture->height= -1;
currentpicture->texture= 0;
{
struct linked_token*aux= cx->end_token_stack;
while(aux!=NULL&&aux->type!=TYPE_ENDCHAR){
if(aux->type==TYPE_ENDFOR){
struct begin_loop_token*loop= (struct begin_loop_token*)aux->link;
loop->running= false;
}
end_nesting_level(mf,cx,(struct generic_token*)aux);
aux= cx->end_token_stack;
}
*end= ((struct linked_token*)(aux->link))->link;
end_nesting_level(mf,cx,(struct generic_token*)aux);
}
return true;
}
/*:634*//*637:*/
#line 17977 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_RENDERCHAR&&mf->loading){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),begin);
return false;
}
/*:637*//*638:*/
#line 17989 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_RENDERCHAR){
struct _glyph*glyph;
struct string_token*str;
struct pair_variable p1,p2;
/*639:*/
#line 18004 "weaver-interface-metafont.cweb"

{
str= (struct string_token*)(begin->next);
if(str==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(str->type!=TYPE_STRING){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(begin->line),TYPE_STRING,
(struct generic_token*)str);
return false;
}
if(str->glyph!=NULL)
glyph= str->glyph;
else{
glyph= get_glyph(mf,(unsigned char*)(str->value),false);
if(glyph==NULL){
RAISE_ERROR_UNKNOWN_GLYPH_DEPENDENCY(mf,cx,OPTIONAL(str->line),
str->value);
return false;
}
str->glyph= glyph;
}
}
/*:639*//*640:*/
#line 18037 "weaver-interface-metafont.cweb"

if(glyph->is_being_rendered){
RAISE_ERROR_RECURSIVE_RENDERCHAR(mf,cx,OPTIONAL(str->line),
str->value);
return false;
}
/*:640*//*641:*/
#line 18048 "weaver-interface-metafont.cweb"

if(glyph->need_rendering){
struct context*new_cx;
glyph->is_being_rendered= true;
new_cx= init_context(mf);
if(new_cx==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(str->line));
return false;
}
if(!eval_list_of_statements(mf,new_cx,glyph->begin,glyph->end)){
destroy_context(new_cx);
return false;
}
glyph->is_being_rendered= false;
destroy_context(new_cx);
}
/*:641*/
#line 17994 "weaver-interface-metafont.cweb"

/*642:*/
#line 18071 "weaver-interface-metafont.cweb"

{
DECLARE_NESTING_CONTROL();
struct generic_token*begin_expr,*end_expr;
begin_expr= str->next;
if(begin_expr==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(str->line));
return false;
}
if(begin_expr->type!=TYPE_BETWEEN){
RAISE_ERROR_EXPECTED_FOUND(mf,NULL,OPTIONAL(begin->line),
TYPE_BETWEEN,begin_expr);
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
return false;
}
begin_expr= begin_expr->next;
if(begin_expr->type==TYPE_AND||begin_expr->next==NULL){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin_expr->line),
TYPE_T_PAIR);
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
return false;
}
end_expr= begin_expr;
while(end_expr!=NULL&&end_expr->next!=NULL){
COUNT_NESTING(end_expr);
if(IS_NOT_NESTED()&&end_expr->next->type==TYPE_AND)
break;
end_expr= end_expr->next;
}
if(end_expr==NULL||end_expr->next==NULL){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_expr->line),
TYPE_T_PAIR);
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
return false;
}
if(!eval_pair_expression(mf,cx,begin_expr,end_expr,&p1)){
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
return false;
}
begin_expr= end_expr->next->next;
if(begin_expr->type==TYPE_SEMICOLON||begin_expr->next==NULL){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(begin_expr->line),
TYPE_T_PAIR);
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
return false;
}
end_expr= begin_expr;
while(end_expr!=NULL&&end_expr->next!=NULL){
COUNT_NESTING(end_expr);
if(IS_NOT_NESTED()&&end_expr->next->type==TYPE_SEMICOLON)
break;
end_expr= end_expr->next;
}
if(end_expr==NULL||end_expr->next==NULL){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_expr->line),
TYPE_T_PAIR);
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
return false;
}
if(!eval_pair_expression(mf,cx,begin_expr,end_expr,&p2)){
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
return false;
}
}
/*:642*//*643:*/
#line 18157 "weaver-interface-metafont.cweb"

{
float gl_matrix[9];
float width,height,depth;
float current_width,current_height,current_depth;
current_width= cx->internal_numeric_variables[INTERNAL_NUMERIC_W].value;
current_height= cx->internal_numeric_variables[INTERNAL_NUMERIC_H].value+
cx->internal_numeric_variables[INTERNAL_NUMERIC_D].value;
current_depth= cx->internal_numeric_variables[INTERNAL_NUMERIC_D].value;
INITIALIZE_IDENTITY_MATRIX(gl_matrix);
if(p1.x> p2.x){
width= p1.x-p2.x;
gl_matrix[0]= -(width/current_width);
gl_matrix[6]= ((p1.x+p2.x)/current_width)-1.0;
}
else{
width= p2.x-p1.x;
gl_matrix[0]= (width/current_width);
gl_matrix[6]= ((p1.x+p2.x)/current_width)-1.0;
}
if(p1.y> p2.y){
height= p1.y-p2.y;
depth= glyph->depth*(height/(glyph->height));
gl_matrix[4]= -(height+depth)/current_height;
gl_matrix[7]= ((p1.y+p2.y)/2)-
(glyph->depth/2)*(height/glyph->height)-(current_height)/2;
gl_matrix[7]= 2*(gl_matrix[7]/current_height);
gl_matrix[7]+= 2*(current_depth/current_height);
}
else{
height= p2.y-p1.y;
depth= glyph->depth*(height/(glyph->height));
gl_matrix[4]= (height+depth)/current_height;
gl_matrix[7]= ((p1.y+p2.y)/2)-
(glyph->depth/2)*(height/glyph->height)-(current_height)/2;
gl_matrix[7]= 2*(gl_matrix[7]/current_height);
gl_matrix[7]+= 2*(current_depth/current_height);
}
/*596:*/
#line 16695 "weaver-interface-metafont.cweb"

{
if(cx->currentpicture_fb==0){
int pic_width,pic_height;
GLuint texture;
pic_width= cx->currentpicture->width;
pic_height= cx->currentpicture->height;
texture= cx->currentpicture->texture;
glGenFramebuffers(1,&(cx->currentpicture_fb));
glBindTexture(GL_TEXTURE_2D,texture);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pic_width,pic_height,0,GL_RGBA,
GL_UNSIGNED_BYTE,NULL);
glBindFramebuffer(GL_FRAMEBUFFER,cx->currentpicture_fb);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,
texture,0);
if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,cx,0);
return false;
}
}
else
glBindFramebuffer(GL_FRAMEBUFFER,cx->currentpicture_fb);
}
/*:596*/
#line 18195 "weaver-interface-metafont.cweb"

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBlendEquation(GL_FUNC_ADD);
glColorMask(true,true,true,true);
glViewport(0,0,current_width,current_height);
glBindBuffer(GL_ARRAY_BUFFER,vbo);
glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,4*sizeof(float),(void*)0);
glEnableVertexAttribArray(0);
glUseProgram(program);
glUniformMatrix3fv(uniform_matrix,1,true,gl_matrix);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D,glyph->texture);
glUniform1i(uniform_texture,0);
glDrawArrays(GL_TRIANGLE_FAN,0,4);
glBindTexture(GL_TEXTURE_2D,0);
glDisable(GL_BLEND);
if(glyph->need_rendering)
glDeleteTextures(1,&(glyph->texture));
}
/*:643*/
#line 17995 "weaver-interface-metafont.cweb"

return true;
}
/*:638*//*646:*/
#line 18249 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_KERNING&&mf->loading){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),begin);
return false;
}
/*:646*//*647:*/
#line 18264 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_KERNING){
struct generic_token*str,*begin_expr,*end_expr;
struct numeric_variable numeric_result;
str= begin->next;
if(str==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
else if(str->type!=TYPE_OPEN_PARENTHESIS){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(str->line),
TYPE_OPEN_PARENTHESIS,str);
return false;
}
str= str->next;
if(str==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
else if(str->type!=TYPE_STRING){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(str->line),
TYPE_STRING,str);
return false;
}
begin_expr= str->next;
if(begin_expr==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(str->line));
return false;
}
else if(begin_expr->type!=TYPE_COMMA){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(begin_expr->line),
TYPE_COMMA,begin_expr);
return false;
}
begin_expr= begin_expr->next;
if(begin_expr==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(str->line));
return false;
}
end_expr= begin_expr;
while(end_expr->next!=NULL&&end_expr->next->next!=NULL&&
end_expr->next->type!=TYPE_SEMICOLON&&
end_expr->next->next->type!=TYPE_SEMICOLON)
end_expr= end_expr->next;
if(end_expr->next==NULL||end_expr->next->next==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin_expr->line));
return false;
}
if(end_expr->next->type==TYPE_SEMICOLON){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(begin_expr->line),
TYPE_CLOSE_PARENTHESIS,end_expr->next);
return false;
}
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&numeric_result))
return false;
/*648:*/
#line 18328 "weaver-interface-metafont.cweb"

{
struct kerning*new_kerning,*existing_kerning;
struct string_token*next_char= (struct string_token*)str;
existing_kerning= cx->current_glyph->kern;
while(existing_kerning!=NULL){
if(!strncmp(next_char->value,existing_kerning->next_char,4)){
existing_kerning->kern= numeric_result.value;
return true;
}
existing_kerning= existing_kerning->next;
}
new_kerning= (struct kerning*)permanent_alloc(sizeof(struct kerning));
if(new_kerning==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}
memcpy(new_kerning->next_char,next_char->value,4);
new_kerning->next_char[4]= '\0';
new_kerning->kern= numeric_result.value;
new_kerning->next= cx->current_glyph->kern;
cx->current_glyph->kern= new_kerning;
return true;
}
/*:648*/
#line 18319 "weaver-interface-metafont.cweb"

}
/*:647*//*652:*/
#line 18404 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_DEBUG){
#if defined(W_DEBUG_METAFONT)
struct generic_token*begin_expr,*end_expr;
int type;
if(begin==*end)
return true;
begin_expr= begin->next;
end_expr= *end;
type= get_tertiary_expression_type(mf,cx,begin_expr,end_expr);
switch(type){
case TYPE_T_NUMERIC:
/*653:*/
#line 18450 "weaver-interface-metafont.cweb"

{
struct numeric_variable result;
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&result))
return false;
printf("DEBUG: %s: %d: Numeric Expression: %f\n",mf->file,
begin_expr->line,result.value);
return true;
}
/*:653*/
#line 18416 "weaver-interface-metafont.cweb"

break;
case TYPE_T_PAIR:
/*654:*/
#line 18463 "weaver-interface-metafont.cweb"

{
struct pair_variable result;
if(!eval_pair_expression(mf,cx,begin_expr,end_expr,&result))
return false;
printf("DEBUG: %s: %d: Pair Expression: (%f, %f)\n",mf->file,
begin_expr->line,result.x,result.y);
return true;
}
/*:654*/
#line 18419 "weaver-interface-metafont.cweb"

break;
case TYPE_T_TRANSFORM:
/*655:*/
#line 18476 "weaver-interface-metafont.cweb"

{
struct transform_variable result;
if(!eval_transform_expression(mf,cx,begin_expr,end_expr,&result))
return false;
printf("DEBUG: %s: %d: Pair Expression: "
"(%f, %f, %f, %f, %f, %f, %f, %f, %f)\n",mf->file,
begin_expr->line,result.value[0],result.value[1],result.value[2],
result.value[3],result.value[4],result.value[5],result.value[6],
result.value[7],result.value[8]);
return true;
}
/*:655*/
#line 18422 "weaver-interface-metafont.cweb"

break;
case TYPE_T_PATH:
/*656:*/
#line 18492 "weaver-interface-metafont.cweb"

{
struct path_variable result;
int j;
if(!eval_path_expression(mf,cx,begin_expr,end_expr,&result))
return false;
printf("DEBUG: %s: %d: Path Expression: ",mf->file,begin_expr->line);
for(j= 0;j<result.length;j++){
if(j==result.length-1&&result.cyclic)
printf("cycle");
else
printf("(%f, %f)",result.points[j].point.x,result.points[j].point.y);
if(j<result.length-1){
printf(" .. controls (%f, %f) and (%f, %f) .. ",
result.points[j].point.u_x,result.points[j].point.u_y,
result.points[j].point.v_x,result.points[j].point.v_y);
}
}
printf("\n");
return true;
}
/*:656*/
#line 18425 "weaver-interface-metafont.cweb"

break;
case TYPE_T_PEN:
/*657:*/
#line 18517 "weaver-interface-metafont.cweb"

{
struct pen_variable result;
struct path_variable*format;
int j;
if(!eval_pen_expression(mf,cx,begin_expr,end_expr,&result))
return false;
printf("DEBUG: %s: %d: Pen Expression: ",mf->file,begin_expr->line);
switch(result.flags){
case FLAG_CIRCULAR:
printf("pencricle");
break;
case FLAG_SEMICIRCULAR:
printf("pensemicircle");
break;
case FLAG_SQUARE:
printf("pensquare");
break;
case FLAG_NULL:
printf("nullpen");
break;
default:
printf("makepen(");
format= result.format;
for(j= 0;j<format->length;j++){
if(j==format->length-1&&format->cyclic)
printf("cycle");
else
printf("(%f, %f)",format->points[j].point.x,
format->points[j].point.y);
if(j<format->length-1){
printf(" .. controls (%f, %f) and (%f, %f) .. ",
format->points[j].point.u_x,format->points[j].point.u_y,
format->points[j].point.v_x,format->points[j].point.v_y);
}
}
printf(")");
}
printf(" transformed (%f, %f, %f, %f, %f, %f)\n",
result.gl_matrix[6],result.gl_matrix[7],result.gl_matrix[0],
result.gl_matrix[3],result.gl_matrix[1],result.gl_matrix[4]);
return true;
}
/*:657*/
#line 18428 "weaver-interface-metafont.cweb"

break;
case TYPE_T_PICTURE:
/*658:*/
#line 18572 "weaver-interface-metafont.cweb"

{
struct picture_variable result;
if(!eval_picture_expression(mf,cx,begin_expr,end_expr,&result))
return false;
printf("DEBUG: %s: %d: Picture Expression: ",mf->file,begin_expr->line);
printf("nullpicture(%d, %d)\n",result.width,result.height);
return true;
}
/*:658*/
#line 18431 "weaver-interface-metafont.cweb"

break;
case TYPE_T_BOOLEAN:
/*659:*/
#line 18587 "weaver-interface-metafont.cweb"

{
struct boolean_variable result;
if(!eval_boolean_expression(mf,cx,begin_expr,end_expr,&result))
return false;
printf("DEBUG: %s: %d: Boolean Expression: ",mf->file,begin_expr->line);
if(result.value)
printf("true\n");
else
printf("false\n");
return true;
}
/*:659*/
#line 18434 "weaver-interface-metafont.cweb"

break;
default:
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
type);
return false;
}
#else
#line 18442 "weaver-interface-metafont.cweb"
 return true;
#endif
#line 18444 "weaver-interface-metafont.cweb"
}
/*:652*/
#line 2559 "weaver-interface-metafont.cweb"


RAISE_ERROR_UNKNOWN_STATEMENT(mf,cx,OPTIONAL(begin->line));
return false;
}
/*:87*//*91:*/
#line 2619 "weaver-interface-metafont.cweb"

bool begin_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok){
struct linked_token*end_token;
end_token= (struct linked_token*)
temporary_alloc(sizeof(struct linked_token));
if(end_token==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(tok->line));
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
case TYPE_FOR:
end_token->type= TYPE_ENDFOR;
break;
default:
return false;
}
end_token->link= tok;
#if defined(W_DEBUG_METAFONT)
end_token->line= tok->line;
#endif
#line 2650 "weaver-interface-metafont.cweb"
 cx->nesting_level++;
end_token->next= (struct generic_token*)(cx->end_token_stack);
cx->end_token_stack= end_token;
return true;
}
/*:91*//*92:*/
#line 2659 "weaver-interface-metafont.cweb"

bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok){
struct linked_token*end_tok= cx->end_token_stack;
if(end_tok==NULL){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(tok->line),tok);
return false;
}
else if(end_tok->type!=tok->type){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(tok->line),
end_tok->type,tok);
return false;
}
cx->nesting_level--;
cx->end_token_stack= (struct linked_token*)(end_tok->next);
if(temporary_free!=NULL)
temporary_free(end_tok);
return true;
}
/*:92*//*111:*/
#line 3017 "weaver-interface-metafont.cweb"

struct variable*insert_variable(struct metafont*mf,
int type,
struct variable**target){
struct variable*var;
size_t var_sizes[]= {
sizeof(struct boolean_variable),sizeof(struct path_variable),
sizeof(struct pen_variable),sizeof(struct picture_variable),
sizeof(struct transform_variable),sizeof(struct pair_variable),
sizeof(struct numeric_variable)
};
size_t var_size= var_sizes[type-TYPE_T_BOOLEAN];
if(mf->loading)
var= (struct variable*)permanent_alloc(var_size);
else
var= (struct variable*)temporary_alloc(var_size);
if(var!=NULL){
var->type= type;
var->next= NULL;
/*117:*/
#line 3161 "weaver-interface-metafont.cweb"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:117*//*128:*/
#line 3357 "weaver-interface-metafont.cweb"

if(type==TYPE_T_PAIR){
((struct pair_variable*)var)->x= NAN;
}
/*:128*//*130:*/
#line 3396 "weaver-interface-metafont.cweb"

if(type==TYPE_T_TRANSFORM)
((struct transform_variable*)var)->value[0]= NAN;
/*:130*//*139:*/
#line 3580 "weaver-interface-metafont.cweb"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
((struct path_variable*)var)->permanent= mf->loading;
}
/*:139*//*180:*/
#line 4980 "weaver-interface-metafont.cweb"

if(type==TYPE_T_PEN){
((struct pen_variable*)var)->format= NULL;
((struct pen_variable*)var)->gl_vbo= 0;
((struct pen_variable*)var)->indices= 0;
((struct pen_variable*)var)->flags= false;
((struct pen_variable*)var)->referenced= NULL;
((struct pen_variable*)var)->permanent= mf->loading;
}
/*:180*//*193:*/
#line 5174 "weaver-interface-metafont.cweb"

if(type==TYPE_T_PICTURE){
((struct picture_variable*)var)->width= -1;
((struct picture_variable*)var)->height= -1;
((struct picture_variable*)var)->texture= 0;
}
/*:193*//*200:*/
#line 5259 "weaver-interface-metafont.cweb"

if(type==TYPE_T_BOOLEAN)
((struct boolean_variable*)var)->value= -1;
/*:200*/
#line 3036 "weaver-interface-metafont.cweb"

}
if(*target==NULL)
*target= var;
else{
struct variable*p= (struct variable*)(*target);
while(p->next!=NULL){
p= (struct variable*)p->next;
}
p->next= var;
}
return var;
}
/*:111*//*113:*/
#line 3063 "weaver-interface-metafont.cweb"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var){
struct named_variable*named;
struct variable*new_var;
size_t name_size;
named= (struct named_variable*)
permanent_alloc(sizeof(struct named_variable));
if(named==NULL)
return NULL;
name_size= strlen(var->value)+1;
named->name= (char*)permanent_alloc(name_size);
if(named->name==NULL){
if(permanent_free!=NULL)
permanent_free(named);
return NULL;
}
memcpy(named->name,var->value,name_size);
named->next= NULL;
named->var= NULL;
new_var= insert_variable(mf,type,&(named->var));
if(new_var==NULL){
if(permanent_free!=NULL){
permanent_free(named->name);
permanent_free(named);
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
/*:113*//*115:*/
#line 3121 "weaver-interface-metafont.cweb"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer){
struct symbolic_token*p= (struct symbolic_token*)var_token->next;
int nesting_level= 0;
while(p!=NULL&&nesting_level>=0){
if(p->type==TYPE_BEGINGROUP||p->type==TYPE_IF||
p->type==TYPE_BEGINCHAR||p->type==TYPE_FOR)
nesting_level++;
else if(p->type==TYPE_ENDGROUP||p->type==TYPE_FI||
p->type==TYPE_ENDCHAR||p->type==TYPE_ENDFOR)
nesting_level--;
else if(p->type==TYPE_SYMBOLIC){
if(!strcmp(p->value,var_token->value)){
p->var= var_pointer;
}
}
p= (struct symbolic_token*)(p->next);
}
}
/*:115*//*143:*/
#line 3624 "weaver-interface-metafont.cweb"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer){
if(free_func!=NULL){
int i;
for(i= 0;i<path->length;i++){
if(path->points[i].format==SUBPATH_FORMAT)
path_recursive_free(free_func,(struct path_variable*)
path->points[i].subpath,true);
}
free_func(path->points);
if(free_first_pointer)
free_func(path);
}
}
/*:143*//*145:*/
#line 3689 "weaver-interface-metafont.cweb"

bool recursive_copy_points(struct metafont*mf,struct context*cx,
void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target){
struct path_points*p,*previous_point= NULL;
if(alloc_target){
*target= (struct path_variable*)alloc(sizeof(struct path_variable));
if(*target==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,0);
return false;
}
}
(*target)->cyclic= source->cyclic;
(*target)->permanent= (alloc==permanent_alloc);
(*target)->length= source->number_of_points;
(*target)->number_of_points= source->number_of_points;
(*target)->number_of_missing_directions= 0;
(*target)->points= (struct path_points*)
alloc(sizeof(struct path_points)*
(*target)->number_of_points);
if((*target)->points==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,0);
return false;
}
p= (*target)->points;
recursive_aux_copy(&p,source,&((*target)->number_of_missing_directions),
&previous_point);
return true;
}
/*:145*//*146:*/
#line 3724 "weaver-interface-metafont.cweb"

void recursive_aux_copy(struct path_points**dst,struct path_variable*origin,
int*missing_directions,
struct path_points**previous_point){
int index= 0;
while(index<=origin->length-1){
if(origin->points[index].format!=SUBPATH_FORMAT&&
!isnan(origin->points[index].point.x)){
memcpy(*dst,&(origin->points[index]),sizeof(struct path_points));


if(*previous_point!=NULL&&
(*previous_point)->format==PROVISIONAL_FORMAT&&
(*previous_point)->prov.x==(*dst)->prov.x&&
(*previous_point)->prov.y==(*dst)->prov.y){
if(isnan((*previous_point)->prov.dir1_x))
(*missing_directions)--;
if(isnan((*previous_point)->prov.dir2_x))
(*missing_directions)--;
(*previous_point)->format= FINAL_FORMAT;
(*previous_point)->point.u_x= (*previous_point)->point.x;
(*previous_point)->point.v_x= (*previous_point)->point.x;
(*previous_point)->point.u_y= (*previous_point)->point.y;
(*previous_point)->point.v_y= (*previous_point)->point.y;
}
if((*dst)->format==PROVISIONAL_FORMAT){

if((*dst)->prov.dir1_x==0.0&&
(*dst)->prov.dir1_y==0.0){
(*dst)->prov.dir1_x= NAN;
(*dst)->prov.dir1_y= NAN;
}
if((*dst)->prov.dir2_x==0.0&&
(*dst)->prov.dir2_y==0.0){
(*dst)->prov.dir2_x= NAN;
(*dst)->prov.dir2_y= NAN;
}
if(isnan((*dst)->prov.dir1_x))
(*missing_directions)++;
if(isnan((*dst)->prov.dir2_x))
(*missing_directions)++;
}
*previous_point= *dst;
(*dst)++;
}
else if(origin->points[index].format==SUBPATH_FORMAT){
recursive_aux_copy(dst,(struct path_variable*)
(origin->points[index].subpath),
missing_directions,previous_point);
path_recursive_free(temporary_free,(struct path_variable*)
(origin->points[index].subpath),true);
}
index++;
}
return;
}
/*:146*//*149:*/
#line 3858 "weaver-interface-metafont.cweb"

double compute_f(double theta,double phi){
double n= 2+sqrt(2)*(sin(theta)-0.0625*sin(phi))*
(sin(phi)-0.0625*sin(theta))*(cos(theta)-cos(phi));
double d= 3*(1+0.5*(sqrt(5)-1)*cos(theta)+0.5*(3-sqrt(5))*
cos(phi));
return n/d;
}
/*:149*//*150:*/
#line 3872 "weaver-interface-metafont.cweb"

void convert_to_final(struct path_variable*p){
int i;
for(i= 0;i<p->length-1;i++){
if(p->points[i].format==PROVISIONAL_FORMAT){
bool atleast0= p->points[i].prov.atleast1;
bool atleast1= p->points[i].prov.atleast2;
double complex u,v;
struct path_points*p0= &(p->points[i]),*p1= &(p->points[i+1]);
double w0_x= p0->prov.dir1_x,w0_y= p0->prov.dir1_y;
double w1_x= p0->prov.dir2_x,w1_y= p0->prov.dir2_y;
double complex z0= p0->prov.x+p0->prov.y*I;
double complex z1= p1->prov.x+p1->prov.y*I;
double theta= carg((w0_x+w0_y*I)/(z1-z0));
double phi= carg((z1-z0)/(w1_x+w1_y*I));
u= z0+(cexp(theta*I)*(z1-z0)*compute_f(theta,phi))/
p->points[i].prov.tension1;
v= z1-(cexp(-phi*I)*(z1-z0)*compute_f(phi,theta))/
p->points[i].prov.tension2;
p->points[i].format= FINAL_FORMAT;
p->points[i].point.u_x= creal(u);
p->points[i].point.u_y= cimag(u);
p->points[i].point.v_x= creal(v);
p->points[i].point.v_y= cimag(v);
/*151:*/
#line 3913 "weaver-interface-metafont.cweb"

if(atleast0)
correct_tension(p0->point.x,p0->point.y,
p1->point.x,p1->point.y,
w0_x,w0_y,w1_x,w1_y,
&(p->points[i].point.u_x),&(p->points[i].point.u_y));
if(atleast1)
correct_tension(p0->point.x,p0->point.y,
p1->point.x,p1->point.y,
w0_x,w0_y,w1_x,w1_y,
&(p->points[i].point.v_x),&(p->points[i].point.v_y));
/*:151*/
#line 3896 "weaver-interface-metafont.cweb"

}
}
if(p->cyclic)
memcpy(&(p->points[p->length-1]),&(p->points[0]),
sizeof(struct path_points));
}
/*:150*//*153:*/
#line 3936 "weaver-interface-metafont.cweb"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y){
double internal_angle0,internal_angle1,internal_angle2;
double triangle_angle;
double p2_x,p2_y;
internal_angle0= get_angle(p0_x,p0_y,p1_x,p1_y,p0_x+d0_x,p0_y+d0_y);
internal_angle1= get_angle(p1_x,p1_y,p0_x,p0_y,p1_x+d1_x,p1_y+d1_y);
internal_angle2= M_PI-internal_angle0-internal_angle1;
if(internal_angle0+internal_angle1>=M_PI-0.00002||
internal_angle0==0.0||internal_angle1==0.0||
internal_angle2==0.0)
return;
{

double known_side= hypot(p1_x-p0_x,p1_y-p0_y);
double triangle_side= known_side*sin(internal_angle0)/
sin(internal_angle2);

triangle_angle= get_angle(p0_x,p0_y,p1_x,p1_y,p0_x+1.0,p0_y);
p2_x= p1_x+triangle_side*cos(triangle_angle+internal_angle1);
p2_y= p1_y+triangle_side*sin(triangle_angle+internal_angle1);
}
{
/*156:*/
#line 4001 "weaver-interface-metafont.cweb"

bool s1,s2,s3;
s1= ((*control_x-p1_x)*(p0_y-p1_y)-
(p0_x-p1_x)*(*control_y-p1_y))<0;
s2= ((*control_x-p2_x)*(p1_y-p2_y)-
(p1_x-p2_x)*(*control_y-p2_y))<0;
s3= ((*control_x-p0_x)*(p2_y-p0_y)-
(p2_x-p0_x)*(*control_y-p0_y))<0;
if(s1==s2&&s2==s3)
return;
/*:156*/
#line 3961 "weaver-interface-metafont.cweb"

/*157:*/
#line 4022 "weaver-interface-metafont.cweb"

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
/*:157*/
#line 3962 "weaver-interface-metafont.cweb"

}
}
/*:153*//*155:*/
#line 3974 "weaver-interface-metafont.cweb"

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
(hypot(v0_x,v0_y)*hypot(v1_x,v1_y)));
}
/*:155*//*159:*/
#line 4125 "weaver-interface-metafont.cweb"

bool find_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p){
if(p->number_of_missing_directions==0||p->length<2)
return true;
if(p->cyclic&&p->number_of_missing_directions>=(2*p->length))
return fill_cyclic_missing_directions(mf,cx,p,0,p->length-1);
if(!(p->cyclic)&&
p->number_of_missing_directions>=(2*(p->length-1)-1))
return fill_missing_directions(mf,cx,p,0,p->length-2);
else{
int begin_segment= 0,end_segment= 0;
while(p->number_of_missing_directions> 0){
while(p->points[begin_segment].format!=PROVISIONAL_FORMAT||
isnan(p->points[begin_segment].prov.dir1_y)||
(!isnan(p->points[begin_segment].prov.dir1_x)&&
!isnan(p->points[begin_segment].prov.dir2_x)))
begin_segment= (begin_segment+1)%p->length;
end_segment= begin_segment;
while(isnan(p->points[end_segment].prov.dir2_y))
end_segment= (end_segment+1)%p->length;
if(!fill_missing_directions(mf,cx,p,begin_segment,end_segment))
return false;
}
return true;
}
}
/*:159*//*165:*/
#line 4280 "weaver-interface-metafont.cweb"

bool fill_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p,int begin,int end){
double*M,*x,*b;
struct path_points*p0= NULL,*p1= &(p->points[(begin)%p->length]),
*p2= &(p->points[(begin+1)%p->length]);
double complex z0= NAN,z1= p1->prov.x+p1->prov.y*I,
z2= p2->prov.x+p2->prov.y*I;
int i= 1,size,number_of_points;
/*160:*/
#line 4184 "weaver-interface-metafont.cweb"

int previous_theta,current_theta,current_psi,current_phi,next_phi,
number_of_equations;
previous_theta= -1;
current_theta= 0;
current_psi= current_phi= -1;
if(begin==end)
next_phi= 1;
else
next_phi= 3;
number_of_equations= 0;
/*:160*/
#line 4289 "weaver-interface-metafont.cweb"

/*171:*/
#line 4612 "weaver-interface-metafont.cweb"

if(begin==end&&isnan(p1->prov.dir1_x)&&isnan(p1->prov.dir2_x)){
p1->format= FINAL_FORMAT;
p1->point.u_x= p1->point.x+(1.0/3)*(p2->point.x-p1->point.x);
p1->point.v_x= p1->point.x+(2.0/3)*(p2->point.x-p1->point.x);
p1->point.u_y= p1->point.y+(1.0/3)*(p2->point.y-p1->point.y);
p1->point.v_y= p1->point.y+(2.0/3)*(p2->point.y-p1->point.y);
p->number_of_missing_directions-= 2;
return true;
}
/*:171*/
#line 4290 "weaver-interface-metafont.cweb"

if(end>=begin)
number_of_points= (end-begin+2);
else
number_of_points= p->length-(begin-end)+2;
size= 3*((number_of_points)-2)+2;

M= (double*)temporary_alloc(size*size*sizeof(double));
x= (double*)temporary_alloc(size*sizeof(double));
b= (double*)temporary_alloc(size*sizeof(double));
if(M==NULL||x==NULL||b==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,0);
if(M!=NULL&&temporary_free!=NULL)temporary_free(M);
if(x!=NULL&&temporary_free!=NULL)temporary_free(x);
if(b!=NULL&&temporary_free!=NULL)temporary_free(b);
return false;
}
memset(M,0,size*size*sizeof(double));

/*168:*/
#line 4437 "weaver-interface-metafont.cweb"

if(!isnan(p1->prov.dir1_x)){
double w1_x= p1->prov.dir1_x,w1_y= p1->prov.dir1_y;
M[0]= 1.0;
b[0]= carg((w1_x+w1_y*I)/(z2-z1));
}
else{
double gamma= p1->prov.dir1_y;
double t1= p1->prov.tension1;
double t2= p1->prov.tension2;
int phi1;
if(begin==end)
phi1= 1;
else
phi1= 3;
M[0]= t1*t1*(1/t2-3.0)-gamma*t2*t2*(1/t1);
M[phi1]= t1*t1*(1/t2)-gamma*t2*t2*(1/t1-3.0);
b[0]= 0.0;
}
{
previous_theta= size;
current_theta= size+1;
current_psi= size+2;
current_phi= size+3;
if(number_of_points> 3)
next_phi= size+6;
else
next_phi= size+4;
number_of_equations++;
}
/*:168*/
#line 4309 "weaver-interface-metafont.cweb"

if(begin!=end){
for(i= 1;(begin+i-1)%p->length!=end;i++){
p0= p1;p1= p2;
p2= &(p->points[(begin+i+1)%p->length]);
z0= z1;z1= z2;
z2= p2->prov.x+p2->prov.y*I;
/*170:*/
#line 4565 "weaver-interface-metafont.cweb"

M[current_psi]= 1.0;
b[number_of_equations]= carg((z2-z1)/(z1-z0));
if(b[number_of_equations]==-M_PI)
b[number_of_equations]*= -1.0;
/*162:*/
#line 4229 "weaver-interface-metafont.cweb"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:162*/
#line 4570 "weaver-interface-metafont.cweb"

M[current_theta]= M[current_psi]= M[current_phi]= 1.0;
b[number_of_equations]= 0.0;
/*162:*/
#line 4229 "weaver-interface-metafont.cweb"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:162*/
#line 4573 "weaver-interface-metafont.cweb"

{
double t0= p0->prov.tension1,t1= p0->prov.tension2,
t2= p1->prov.tension1,t3= p1->prov.tension2;
M[previous_theta]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0);
M[current_theta]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3-3.0);
M[current_phi]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0-3.0);
M[next_phi]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3);
b[number_of_equations]= 0.0;
/*163:*/
#line 4244 "weaver-interface-metafont.cweb"

{
previous_theta= current_theta+size;
current_phi= next_phi+size;
current_theta+= (size+3);
current_psi+= (size+3);
if(p->cyclic)
next_phi= number_of_equations*size+((next_phi+3)%size)+size;
else{
if(next_phi%size==size-2)
next_phi+= (size+1);
else
next_phi+= (size+3);
}
number_of_equations++;
}
/*:163*/
#line 4582 "weaver-interface-metafont.cweb"

}
/*:170*/
#line 4316 "weaver-interface-metafont.cweb"

}
}
/*169:*/
#line 4499 "weaver-interface-metafont.cweb"

p1= &(p->points[(end)%p->length]);
p2= &(p->points[(end+1)%p->length]);
z1= p1->prov.x+p1->prov.y*I;
z2= p2->prov.x+p2->prov.y*I;
if(!isnan(p1->prov.dir2_x)){
double w1_x= p1->prov.dir2_x,w1_y= p1->prov.dir2_y;
M[size*size-1]= 1.0;
b[size-1]= carg((z2-z1)/(w1_x+w1_y*I));
}
else{
double gamma= p1->prov.dir2_y;
double t1= p1->prov.tension1;
double t2= p1->prov.tension2;
int last_theta;
if(begin==end)
last_theta= 2;
else
last_theta= size*size-4;
M[last_theta]= t2*t2*(1/t1)-gamma*t1*t1*(1/t2-3.0);
M[size*size-1]= t2*t2*(1/t1-3.0)-gamma*t1*t1*(1/t2);
b[size-1]= 0.0;
}
/*:169*/
#line 4319 "weaver-interface-metafont.cweb"

solve_linear_system(size,M,b,x);
/*172:*/
#line 4638 "weaver-interface-metafont.cweb"

if(isnan(p->points[begin].prov.dir1_x)){
double complex dir;
z0= p->points[begin].prov.x+p->points[begin].prov.y*I;
z1= p->points[(begin+1)%p->length].prov.x+
p->points[(begin+1)%p->length].prov.y*I;
dir= cos(x[0])+sin(x[0])*I;
dir*= (z1-z0);
p->points[begin].prov.dir1_x= creal(dir);
p->points[begin].prov.dir1_y= cimag(dir);
p->number_of_missing_directions--;
}
/*:172*/
#line 4321 "weaver-interface-metafont.cweb"

{
int theta;
for(theta= 1,i= 1;i<number_of_points-1;i++,theta+= 3){

/*174:*/
#line 4697 "weaver-interface-metafont.cweb"

{
double complex dir;
z0= p->points[(begin+i)%p->length].prov.x+
p->points[(begin+i)%p->length].prov.y*I;
z1= p->points[(begin+i+1)%p->length].prov.x+
p->points[(begin+i+1)%p->length].prov.y*I;
dir= cos(x[theta])+sin(x[theta])*I;
dir*= (z1-z0);
p->points[(begin+i)%p->length].prov.dir1_x= creal(dir);
p->points[(begin+i)%p->length].prov.dir1_y= cimag(dir);
p->number_of_missing_directions--;
if(begin+i-1>=0){
p->points[(begin+i-1)%p->length].prov.dir2_x= creal(dir);
p->points[(begin+i-1)%p->length].prov.dir2_y= cimag(dir);
p->number_of_missing_directions--;
}
else if(p->cyclic){
p->points[end].prov.dir2_x= creal(dir);
p->points[end].prov.dir2_y= cimag(dir);
p->number_of_missing_directions--;
}
}
/*:174*/
#line 4326 "weaver-interface-metafont.cweb"

}
}
/*173:*/
#line 4663 "weaver-interface-metafont.cweb"

if(isnan(p->points[end].prov.dir2_x)){
double complex dir;
z1= p->points[end].prov.x+p->points[end].prov.y*I;
z2= p->points[(end+1)%p->length].prov.x+
p->points[(end+1)%p->length].prov.y*I;
dir= cos(x[size-1])+sin(x[size-1])*I;
dir/= (z2-z1);
dir= 1.0/dir;
p->points[end].prov.dir2_x= creal(dir);
p->points[end].prov.dir2_y= cimag(dir);
p->number_of_missing_directions--;
}
/*:173*/
#line 4329 "weaver-interface-metafont.cweb"

if(temporary_free!=NULL){
temporary_free(M);
temporary_free(x);
temporary_free(b);
}
return true;
}
/*:165*//*167:*/
#line 4352 "weaver-interface-metafont.cweb"

bool fill_cyclic_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p,int begin,
int end){
double*M,*x,*b;
struct path_points*p0= NULL,
*p1= &(p->points[end]),
*p2= &(p->points[begin]);
double complex z0,z1= p1->prov.x+p1->prov.y*I,
z2= p2->prov.x+p2->prov.y*I;
int i,size= 3*(p->length);
/*161:*/
#line 4210 "weaver-interface-metafont.cweb"

int previous_theta,current_theta,current_psi,current_phi,next_phi,
number_of_equations;
previous_theta= size-3;
current_theta= 0;
current_psi= 1;
current_phi= 2;
next_phi= 5;
number_of_equations= 0;
/*:161*/
#line 4363 "weaver-interface-metafont.cweb"


M= (double*)temporary_alloc(size*size*sizeof(double));
x= (double*)temporary_alloc(size*sizeof(double));
b= (double*)temporary_alloc(size*sizeof(double));
if(M==NULL||x==NULL||b==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,0);
if(M!=NULL&&temporary_free!=NULL)temporary_free(M);
if(x!=NULL&&temporary_free!=NULL)temporary_free(x);
if(b!=NULL&&temporary_free!=NULL)temporary_free(b);
return false;
}
memset(M,0,size*size*sizeof(double));

for(i= 0;i<p->length;i++){
p0= p1;p1= p2;
p2= &(p->points[(begin+i+1)%p->length]);
z0= z1;z1= z2;
z2= p2->prov.x+p2->prov.y*I;
/*170:*/
#line 4565 "weaver-interface-metafont.cweb"

M[current_psi]= 1.0;
b[number_of_equations]= carg((z2-z1)/(z1-z0));
if(b[number_of_equations]==-M_PI)
b[number_of_equations]*= -1.0;
/*162:*/
#line 4229 "weaver-interface-metafont.cweb"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:162*/
#line 4570 "weaver-interface-metafont.cweb"

M[current_theta]= M[current_psi]= M[current_phi]= 1.0;
b[number_of_equations]= 0.0;
/*162:*/
#line 4229 "weaver-interface-metafont.cweb"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:162*/
#line 4573 "weaver-interface-metafont.cweb"

{
double t0= p0->prov.tension1,t1= p0->prov.tension2,
t2= p1->prov.tension1,t3= p1->prov.tension2;
M[previous_theta]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0);
M[current_theta]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3-3.0);
M[current_phi]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0-3.0);
M[next_phi]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3);
b[number_of_equations]= 0.0;
/*163:*/
#line 4244 "weaver-interface-metafont.cweb"

{
previous_theta= current_theta+size;
current_phi= next_phi+size;
current_theta+= (size+3);
current_psi+= (size+3);
if(p->cyclic)
next_phi= number_of_equations*size+((next_phi+3)%size)+size;
else{
if(next_phi%size==size-2)
next_phi+= (size+1);
else
next_phi+= (size+3);
}
number_of_equations++;
}
/*:163*/
#line 4582 "weaver-interface-metafont.cweb"

}
/*:170*/
#line 4382 "weaver-interface-metafont.cweb"

}
solve_linear_system(size,M,b,x);
{
int theta;
for(theta= 0,i= 0;i<p->length;i++,theta+= 3){

/*174:*/
#line 4697 "weaver-interface-metafont.cweb"

{
double complex dir;
z0= p->points[(begin+i)%p->length].prov.x+
p->points[(begin+i)%p->length].prov.y*I;
z1= p->points[(begin+i+1)%p->length].prov.x+
p->points[(begin+i+1)%p->length].prov.y*I;
dir= cos(x[theta])+sin(x[theta])*I;
dir*= (z1-z0);
p->points[(begin+i)%p->length].prov.dir1_x= creal(dir);
p->points[(begin+i)%p->length].prov.dir1_y= cimag(dir);
p->number_of_missing_directions--;
if(begin+i-1>=0){
p->points[(begin+i-1)%p->length].prov.dir2_x= creal(dir);
p->points[(begin+i-1)%p->length].prov.dir2_y= cimag(dir);
p->number_of_missing_directions--;
}
else if(p->cyclic){
p->points[end].prov.dir2_x= creal(dir);
p->points[end].prov.dir2_y= cimag(dir);
p->number_of_missing_directions--;
}
}
/*:174*/
#line 4389 "weaver-interface-metafont.cweb"

}
}
if(temporary_free!=NULL){
temporary_free(M);
temporary_free(x);
temporary_free(b);
}
return true;
}
/*:167*//*176:*/
#line 4815 "weaver-interface-metafont.cweb"

bool normalize_path(struct metafont*mf,struct context*cx,
struct path_variable*path){
struct path_variable*new;
void*(*alloc)(size_t);
void(*disalloc)(void*);
if(path->permanent){
alloc= permanent_alloc;
disalloc= permanent_free;
}
else{
alloc= temporary_alloc;
disalloc= temporary_free;
}
if(!recursive_copy_points(mf,cx,alloc,&new,path,true))
return false;
if(disalloc!=NULL)
disalloc(path->points);

memcpy(path,new,sizeof(struct path_variable));
disalloc(new);
if(path->number_of_missing_directions> 0){
if(path->cyclic){
if(isnan(path->points[path->length-1].prov.dir1_x))
path->number_of_missing_directions--;
if(isnan(path->points[path->length-1].prov.dir2_x))
path->number_of_missing_directions--;
path->length--;
}
if(!find_missing_directions(mf,cx,path))
return false;
if(path->cyclic){
path->length++;
memcpy(&(path->points[path->length-1]),&(path->points[0]),
sizeof(struct path_points));
}
}
convert_to_final(path);
return true;
}
/*:176*//*212:*/
#line 5642 "weaver-interface-metafont.cweb"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secondary,
*last_sum= NULL,*p,*prev= NULL;
DECLARE_NESTING_CONTROL();
struct numeric_variable a,b;
p= begin;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_PYTHAGOREAN_SUM||
p->type==TYPE_PYTHAGOREAN_SUBTRACT||
IS_VALID_SUM_OR_SUB(prev,p))){
last_sum= p;
end_tertiary= prev;
}
prev= p;
if(p!=end)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
if(end_tertiary!=NULL){
begin_secondary= (struct generic_token*)(last_sum->next);
if(!eval_numeric_expression(mf,cx,begin,end_tertiary,&a))
return false;
if(!eval_numeric_secondary(mf,cx,begin_secondary,end,&b))
return false;
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
RAISE_ERROR_NEGATIVE_SQUARE_ROOT(mf,cx,OPTIONAL(last_sum->line),
a.value-b.value);
return false;
}
}
return true;
}
else
return eval_numeric_secondary(mf,cx,begin,end,result);
}
/*:212*//*216:*/
#line 5745 "weaver-interface-metafont.cweb"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result){
struct generic_token*end_secondary= NULL,*begin_primary,
*last_mul= NULL,*p,*prev= NULL,
*prev_prev= NULL,*last_fraction= NULL;
DECLARE_NESTING_CONTROL();
struct numeric_variable a,b;
b.value= 0.0;
p= begin;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_MULTIPLICATION||
p->type==TYPE_DIVISION)){
if(p->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
p!=end&&p->next->type!=TYPE_NUMERIC&&
last_fraction!=prev_prev)
last_fraction= p;
else{
last_mul= p;
end_secondary= prev;
}
}
prev_prev= prev;
prev= p;
if(p!=end)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
if(end_secondary!=NULL){
begin_primary= (struct generic_token*)(last_mul->next);
if(!eval_numeric_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
if(last_mul->type==TYPE_MULTIPLICATION)
result->value= a.value*b.value;
else if(last_mul->type==TYPE_DIVISION){
if(b.value==0.0){
RAISE_ERROR_DIVISION_BY_ZERO(mf,cx,OPTIONAL(last_mul->line));
return false;
}
result->value= a.value/b.value;
}
return true;
}
else
return eval_numeric_primary(mf,cx,begin,end,result);
}
/*:216*//*220:*/
#line 5864 "weaver-interface-metafont.cweb"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result){
/*221:*/
#line 5887 "weaver-interface-metafont.cweb"

if(begin==end||(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS)||
(begin->type==TYPE_NUMERIC&&begin->next!=end&&
begin->next->type==TYPE_DIVISION&&begin->next->next==end&&
end->type==TYPE_NUMERIC)){
return eval_numeric_atom(mf,cx,begin,end,result);
}
/*:221*/
#line 5869 "weaver-interface-metafont.cweb"

/*222:*/
#line 5903 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_LENGTH){
int expr_type= get_primary_expression_type(mf,cx,begin->next,end);
if(expr_type==TYPE_T_NUMERIC){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
result->value= ((num.value> 0)?(num.value):(-num.value));
return true;
}
/*269:*/
#line 7030 "weaver-interface-metafont.cweb"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,begin->next,end,&p))
return false;
result->value= (float)hypot(p.x,p.y);
return true;
}
/*:269*//*372:*/
#line 9735 "weaver-interface-metafont.cweb"

else if(expr_type==TYPE_T_PATH){
struct path_variable p;
if(!eval_path_primary(mf,cx,begin->next,end,&p))
return false;
result->value= (float)(p.number_of_points-1);
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&p,false);
return true;
}
/*:372*/
#line 5913 "weaver-interface-metafont.cweb"

else{
RAISE_ERROR_UNSUPORTED_LENGTH_OPERAND(mf,cx,OPTIONAL(begin->line),
expr_type);
return false;
}
}
/*:222*/
#line 5870 "weaver-interface-metafont.cweb"

/*223:*/
#line 5938 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_SQRT){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
if(num.value<0.0){
RAISE_ERROR_NEGATIVE_SQUARE_ROOT(mf,cx,OPTIONAL(begin->line),
num.value);
return false;
}
result->value= sqrtf(num.value);
return true;
}
/*:223*//*224:*/
#line 5957 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_SIND){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;

result->value= sinf(num.value*0.0174533);
return true;
}
/*:224*//*225:*/
#line 5970 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_COSD){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;

result->value= cosf(num.value*0.0174533);
return true;
}
/*:225*//*226:*/
#line 5983 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_LOG){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
if(num.value<=0.0){
RAISE_ERROR_NEGATIVE_LOGARITHM(mf,cx,OPTIONAL(begin->line),
num.value);
return false;
}
result->value= logf(num.value);
return true;
}
/*:226*//*227:*/
#line 6000 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_EXP){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
result->value= expf(num.value);
return true;
}
/*:227*//*228:*/
#line 6012 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_FLOOR){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
result->value= floorf(num.value);
return true;
}
/*:228*//*229:*/
#line 6037 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_UNIFORMDEVIATE){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
{
uint64_t random_bits= random_func();
float multiplicand= (float)ldexp((double)random_bits,-64);
result->value= multiplicand*num.value;
}
return true;
}
/*:229*//*230:*/
#line 6054 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_SUM){
if(!eval_numeric_primary(mf,cx,begin->next,end,result))
return false;
return true;
}
/*:230*//*231:*/
#line 6065 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_SUBTRACT){
if(!eval_numeric_primary(mf,cx,begin->next,end,result))
return false;
result->value*= -1;
return true;
}
/*:231*/
#line 5871 "weaver-interface-metafont.cweb"

/*270:*/
#line 7046 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_XPART){
struct pair_variable p;
int expr_type= get_primary_expression_type(mf,cx,begin->next,end);
if(expr_type==TYPE_T_PAIR){
if(!eval_pair_primary(mf,cx,begin->next,end,&p))
return false;
result->value= p.x;
return true;
}
else{
/*296:*/
#line 7598 "weaver-interface-metafont.cweb"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,begin->next,end,&t))
return false;
result->value= t.value[6];
return true;
/*:296*/
#line 7057 "weaver-interface-metafont.cweb"

}
}
/*:270*//*271:*/
#line 7066 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_YPART){
struct pair_variable p;
int expr_type= get_primary_expression_type(mf,cx,begin->next,end);
if(expr_type==TYPE_T_PAIR){
if(!eval_pair_primary(mf,cx,begin->next,end,&p))
return false;
result->value= p.y;
return true;
}
else{
/*297:*/
#line 7608 "weaver-interface-metafont.cweb"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,begin->next,end,&t))
return false;
result->value= t.value[7];
return true;
/*:297*/
#line 7077 "weaver-interface-metafont.cweb"

}
}
/*:271*//*272:*/
#line 7087 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_ANGLE){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,begin->next,end,&p))
return false;
if(p.x==0.0&&p.y==0.0){
RAISE_ERROR_NULL_VECTOR_ANGLE(mf,cx,OPTIONAL(begin->line));
return false;
}
result->value= (float)acos(p.x/(hypot(p.x,p.y)));
result->value*= 57.2958;
return true;
}
/*:272*//*295:*/
#line 7575 "weaver-interface-metafont.cweb"

else if(begin->type>=TYPE_XXPART&&begin->type<=TYPE_YYPART){
struct transform_variable t;
if(!eval_transform_primary(mf,cx,begin->next,end,&t))
return false;
if(begin->type==TYPE_XXPART)
result->value= t.value[0];
else if(begin->type==TYPE_XYPART)
result->value= t.value[3];
else if(begin->type==TYPE_YXPART)
result->value= t.value[1];
else if(begin->type==TYPE_YYPART)
result->value= t.value[4];
return true;
}
/*:295*//*465:*/
#line 12099 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_TOTALWEIGHT){
struct picture_variable p;
char*data;
GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
GLuint temporary_texture= 0;
float identity_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
if(begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
if(!eval_picture_primary(mf,cx,begin->next,end,&p))
return false;
data= temporary_alloc(p.width*p.height*4);
if(data==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_framebuffer);
if(!get_new_framebuffer(&temporary_framebuffer,&(temporary_texture),
p.width,p.height)){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,NULL,0);
return false;
}

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
glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:465*//*466:*/
#line 12165 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_WIDTH){
struct picture_variable p;
if(begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
if(!eval_picture_primary(mf,cx,begin->next,end,&p))
return false;
result->value= (float)p.width;
return true;
}
/*:466*//*467:*/
#line 12182 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_HEIGHT){
struct picture_variable p;
if(begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
if(!eval_picture_primary(mf,cx,begin->next,end,&p))
return false;
result->value= (float)p.height;
return true;
}
/*:467*/
#line 5872 "weaver-interface-metafont.cweb"

/*232:*/
#line 6084 "weaver-interface-metafont.cweb"

else{
float token_value;
struct generic_token*after_token;
if(begin->type!=TYPE_NUMERIC){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_NUMERIC);
return false;
}
token_value= ((struct numeric_token*)begin)->value;
after_token= begin->next;
if(after_token->type==TYPE_DIVISION){
if(after_token==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_NUMERIC);
return false;
}
after_token= after_token->next;
token_value/= ((struct numeric_token*)after_token)->value;
after_token= after_token->next;
}
if(!eval_numeric_primary(mf,cx,after_token,end,result))
return false;
result->value*= token_value;
return true;
}
/*:232*/
#line 5873 "weaver-interface-metafont.cweb"

RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_NUMERIC);
return false;
}
/*:220*//*236:*/
#line 6149 "weaver-interface-metafont.cweb"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result){
if(begin==end){
/*237:*/
#line 6172 "weaver-interface-metafont.cweb"

if(begin->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin)->value;
return true;
}
/*:237*/
#line 6155 "weaver-interface-metafont.cweb"

/*238:*/
#line 6184 "weaver-interface-metafont.cweb"

if(begin->type==TYPE_SYMBOLIC){
struct symbolic_token*var_token= ((struct symbolic_token*)begin);
struct numeric_variable*var;
if(!strcmp(var_token->value,"w"))
var= &(cx->internal_numeric_variables[INTERNAL_NUMERIC_W]);
else if(!strcmp(var_token->value,"h"))
var= &(cx->internal_numeric_variables[INTERNAL_NUMERIC_H]);
else if(!strcmp(var_token->value,"d"))
var= &(cx->internal_numeric_variables[INTERNAL_NUMERIC_D]);
else
var= var_token->var;
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(begin->line),
var_token);
return false;
}
if(var->type!=TYPE_T_NUMERIC){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(begin->line),
var_token,var->type,
TYPE_T_NUMERIC);
return false;
}
if(isnan(var->value)){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
var_token,TYPE_T_NUMERIC);
return false;
}
result->value= var->value;
return true;
}
/*:238*/
#line 6156 "weaver-interface-metafont.cweb"

/*241:*/
#line 6264 "weaver-interface-metafont.cweb"

if(begin->type==TYPE_NORMALDEVIATE){
if(mf->have_stored_normaldeviate){
mf->have_stored_normaldeviate= false;
result->value= mf->normaldeviate;
return true;
}
else{
uint64_t random_bits;
float u,v,s;
do{
random_bits= random_func();
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
/*:241*/
#line 6157 "weaver-interface-metafont.cweb"

}
else{
/*242:*/
#line 6297 "weaver-interface-metafont.cweb"

if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
struct generic_token*p= begin;
while(p->next!=end)
p= p->next;
if(p==begin){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'(');
return false;
}
if(!eval_numeric_expression(mf,cx,begin->next,p,result))
return false;
return true;
}
/*:242*/
#line 6160 "weaver-interface-metafont.cweb"

/*243:*/
#line 6321 "weaver-interface-metafont.cweb"

if(begin->type==TYPE_NUMERIC&&end->type==TYPE_NUMERIC&&
begin->next->type==TYPE_DIVISION){
if(((struct numeric_token*)end)->value==0.0){
RAISE_ERROR_DIVISION_BY_ZERO(mf,cx,OPTIONAL(begin->line));
return false;
}
result->value= ((struct numeric_token*)begin)->value/
((struct numeric_token*)end)->value;
return true;
}
/*:243*/
#line 6161 "weaver-interface-metafont.cweb"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_NUMERIC);
return false;
}
/*:236*//*246:*/
#line 6386 "weaver-interface-metafont.cweb"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result){
struct generic_token*end_tertiary= NULL,*begin_secondary,
*last_sum= NULL,*p,*prev= NULL;
DECLARE_NESTING_CONTROL();
struct pair_variable a,b;
p= begin;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&IS_VALID_SUM_OR_SUB(prev,p)){
last_sum= p;
end_tertiary= prev;
}
prev= p;
if(p!=end)
p= p->next;
else
p= NULL;
}while(p!=NULL);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
if(end_tertiary!=NULL){
begin_secondary= last_sum->next;
if(!eval_pair_expression(mf,cx,begin,end_tertiary,&a))
return false;
if(!eval_pair_secondary(mf,cx,begin_secondary,end,&b))
return false;
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
return eval_pair_secondary(mf,cx,begin,end,result);
}
/*:246*//*250:*/
#line 6490 "weaver-interface-metafont.cweb"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result){
struct generic_token*end_secondary= NULL,*begin_primary,
*last_mul= NULL,*p,*prev= NULL,
*prev_prev= NULL,*last_fraction= NULL;
DECLARE_NESTING_CONTROL();
p= begin;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_MULTIPLICATION||
p->type==TYPE_DIVISION||p->type==TYPE_ROTATED||
p->type==TYPE_SCALED||p->type==TYPE_SHIFTED||
p->type==TYPE_SLANTED||p->type==TYPE_XSCALED||
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED||

p->type==TYPE_TRANSFORMED)){
if(p->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
p!=end&&p->next->type!=TYPE_NUMERIC&&
last_fraction!=prev_prev)
last_fraction= p;
else{
last_mul= p;
end_secondary= prev;
}
}
prev_prev= prev;
prev= p;
if(p!=end)
p= p->next;
else
p= NULL;
}while(p!=NULL);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
if(end_secondary!=NULL){
begin_primary= last_mul->next;
/*251:*/
#line 6551 "weaver-interface-metafont.cweb"

if(last_mul->type==TYPE_MULTIPLICATION){
if(get_primary_expression_type(mf,cx,begin_primary,end)==TYPE_T_PAIR){
struct numeric_variable a;
struct pair_variable b;
if(!eval_numeric_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_pair_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= b.x*a.value;
result->y= b.y*a.value;
return true;
}
else{
struct pair_variable a;
struct numeric_variable b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= a.x*b.value;
result->y= a.y*b.value;
return true;
}
}
/*:251*/
#line 6528 "weaver-interface-metafont.cweb"

/*252:*/
#line 6581 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_DIVISION){
struct pair_variable a;
struct numeric_variable b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
if(b.value==0.0){
RAISE_ERROR_DIVISION_BY_ZERO(mf,cx,OPTIONAL(last_mul->line));
return false;
}
result->x= a.x/b.value;
result->y= a.y/b.value;
return true;
}
/*:252*/
#line 6529 "weaver-interface-metafont.cweb"

/*253:*/
#line 6602 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_ROTATED){
struct pair_variable a;
struct numeric_variable b;
double sin_theta,cos_theta,theta;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
theta= 0.0174533*b.value;
sin_theta= sin(theta);
cos_theta= cos(theta);
result->x= a.x*cos_theta-a.y*sin_theta;
result->y= a.x*sin_theta+a.y*cos_theta;
return true;
}
/*:253*/
#line 6530 "weaver-interface-metafont.cweb"

/*254:*/
#line 6622 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_SCALED){
struct pair_variable a;
struct numeric_variable b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= a.x*b.value;
result->y= a.y*b.value;
return true;
}
/*:254*/
#line 6531 "weaver-interface-metafont.cweb"

/*255:*/
#line 6639 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_SHIFTED){
struct pair_variable a,b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_pair_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= a.x+b.x;
result->y= a.y+b.y;
return true;
}
/*:255*/
#line 6532 "weaver-interface-metafont.cweb"

/*256:*/
#line 6656 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_SLANTED){
struct pair_variable a;
struct numeric_variable b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= a.x+b.value*a.y;
result->y= a.y;
return true;
}
/*:256*/
#line 6533 "weaver-interface-metafont.cweb"

/*257:*/
#line 6673 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_XSCALED){
struct pair_variable a;
struct numeric_variable b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= a.x*b.value;
result->y= a.y;
return true;
}
/*:257*/
#line 6534 "weaver-interface-metafont.cweb"

/*258:*/
#line 6690 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_YSCALED){
struct pair_variable a;
struct numeric_variable b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_numeric_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= a.x;
result->y= a.y*b.value;
return true;
}
/*:258*/
#line 6535 "weaver-interface-metafont.cweb"

/*259:*/
#line 6711 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_ZSCALED){
struct pair_variable a,b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_pair_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= a.x*b.x-a.y*b.y;
result->y= a.x*b.y+b.x*a.y;
return true;
}
/*:259*/
#line 6536 "weaver-interface-metafont.cweb"

/*298:*/
#line 7633 "weaver-interface-metafont.cweb"

else if(last_mul->type==TYPE_TRANSFORMED){
struct pair_variable a;
struct transform_variable b;
if(!eval_pair_secondary(mf,cx,begin,end_secondary,&a))
return false;
if(!eval_transform_primary(mf,cx,begin_primary,end,&b))
return false;
result->x= LINEAR_TRANSFORM_X(a.x,a.y,b.value);
result->y= LINEAR_TRANSFORM_Y(a.x,a.y,b.value);
return true;
}
/*:298*/
#line 6537 "weaver-interface-metafont.cweb"

}
else
return eval_pair_primary(mf,cx,begin,end,result);
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PAIR);
return false;
}
/*:250*//*261:*/
#line 6763 "weaver-interface-metafont.cweb"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result){
if(begin==end){
/*262:*/
#line 6788 "weaver-interface-metafont.cweb"

struct symbolic_token*tok= (struct symbolic_token*)begin;
struct pair_variable*var;
if(tok->type!=TYPE_SYMBOLIC){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PAIR);
return false;
}
var= (struct pair_variable*)tok->var;
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(begin->line),tok);
return false;
}
if(var->type!=TYPE_T_PAIR){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(begin->line),
tok,var->type,
TYPE_T_PAIR);
return false;
}
if(isnan(var->x)){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
tok,TYPE_T_PAIR);
return false;
}
result->x= var->x;
result->y= var->y;
return true;
/*:262*/
#line 6769 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*263:*/
#line 6823 "weaver-interface-metafont.cweb"

struct generic_token*begin_a,*end_a,*begin_b,*end_b,*comma;
if(begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'(');
return false;
}
begin_a= (struct generic_token*)begin->next;
end_a= begin_a;
DECLARE_NESTING_CONTROL();
bool literal= true;
while(end_a!=NULL){
COUNT_NESTING(end_a);
if(IS_NOT_NESTED()&&
((struct generic_token*)end_a->next)->type==TYPE_COMMA)
break;
if(end_a->next!=end)
end_a= (struct generic_token*)end_a->next;
else{
literal= false;
break;
}
}
if(literal){
struct numeric_variable a,b;
comma= (struct generic_token*)end_a->next;
begin_b= (struct generic_token*)comma->next;
if(begin_b==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(comma->line),
TYPE_T_PAIR);
return false;
}
end_b= begin_b;
while(end_b->next!=end)
end_b= (struct generic_token*)end_b->next;
if(!eval_numeric_expression(mf,cx,begin_a,end_a,&a))
return false;
if(!eval_numeric_expression(mf,cx,begin_b,end_b,&b))
return false;
result->x= a.value;
result->y= b.value;
return true;
}
/*:263*/
#line 6773 "weaver-interface-metafont.cweb"

/*264:*/
#line 6873 "weaver-interface-metafont.cweb"

else
return eval_pair_expression(mf,cx,begin_a,end_a,result);
/*:264*/
#line 6774 "weaver-interface-metafont.cweb"

}
/*379:*/
#line 9850 "weaver-interface-metafont.cweb"

if(begin->type==TYPE_POINT||
begin->type==TYPE_PRECONTROL||
begin->type==TYPE_POSTCONTROL){
DECLARE_NESTING_CONTROL();
struct generic_token*begin_num,*end_num,*of= NULL,*begin_path,*end_path;
struct numeric_variable a;
struct path_variable b;
begin_num= begin->next;
end_num= begin_num;
int index;
while(end_num!=NULL&&end_num->next!=end){
COUNT_NESTING(end_num);
if(IS_NOT_NESTED()&&
((struct generic_token*)end_num->next)->type==TYPE_OF){
of= end_num->next;
break;
}
end_num= end_num->next;
}
if(of==NULL||of->next==NULL){
RAISE_ERROR_INCOMPLETE_SOURCE(mf,cx,OPTIONAL(begin->line));
return false;
}
if(of==end){
RAISE_ERROR_INCOMPLETE_STATEMENT(mf,cx,OPTIONAL(begin->line));
return false;
}
begin_path= of->next;
end_path= end;
if(!eval_numeric_expression(mf,cx,begin_num,end_num,&a))
return false;
if(!eval_path_primary(mf,cx,begin_path,end_path,&b))
return false;
if(b.cyclic){
index= ((int)(a.value))%(b.number_of_points-1);
if(begin->type==TYPE_PRECONTROL)
index= (index-1)%(b.number_of_points-1);
}
else{
index= (int)(a.value);
if(index<0)index= 0;
if(index>=b.number_of_points)index= b.number_of_points-1;
if(begin->type==TYPE_PRECONTROL)
index--;
}
if(begin->type==TYPE_POINT){
result->x= get_point(&b,index)->point.x;
result->y= get_point(&b,index)->point.y;
}
else if(begin->type==TYPE_PRECONTROL){
if(index<0){
result->x= get_point(&b,0)->point.x;
result->y= get_point(&b,0)->point.y;
}
else{
result->x= get_point(&b,index)->point.v_x;
result->y= get_point(&b,index)->point.v_y;
}
}
else{
result->x= get_point(&b,index)->point.u_x;
result->y= get_point(&b,index)->point.u_y;
}
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&b,false);
return true;
}
/*:379*//*578:*/
#line 16426 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_BOT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->y+= cx->pen_bot;
return true;
}
/*:578*//*579:*/
#line 16441 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_TOP){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->y+= cx->pen_top;
return true;
}
/*:579*//*580:*/
#line 16459 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_LFT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->x+= cx->pen_lft;
return true;
}
/*:580*//*581:*/
#line 16475 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_RT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->x+= cx->pen_rt;
return true;
}
/*:581*/
#line 6776 "weaver-interface-metafont.cweb"

/*265:*/
#line 6883 "weaver-interface-metafont.cweb"

else if(end->type==TYPE_CLOSE_BRACKETS){
struct generic_token*begin_a,*end_a,*begin_b,*end_b,*begin_c,
*end_c;
struct numeric_variable a;
struct pair_variable b,c;
DECLARE_NESTING_CONTROL();
begin_a= begin;
end_a= begin_a;
while(end_a!=end){
COUNT_NESTING(end_a);
if(IS_NOT_NESTED()&&end_a->next->type==TYPE_OPEN_BRACKETS)
break;
end_a= end_a->next;
}
if(end_a==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PAIR);
return false;
}
begin_b= end_a->next;
begin_b= begin_b->next;
end_b= begin_b;
while(end_b!=end){
COUNT_NESTING(end_b);
if(IS_NOT_NESTED()&&end_b->next->type==TYPE_COMMA)
break;
end_b= end_b->next;
}
if(end_b==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PAIR);
return false;
}
begin_c= end_b->next;
begin_c= begin_c->next;
end_c= begin_c;
while(end_c!=end){
if(end_c->next==end)
break;
end_c= end_c->next;
}
if(end_c==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PAIR);
return false;
}
if(!eval_numeric_atom(mf,cx,begin_a,end_a,&a))
return false;
if(!eval_pair_expression(mf,cx,begin_b,end_b,&b))
return false;
if(!eval_pair_expression(mf,cx,begin_c,end_c,&c))
return false;
result->x= b.x+a.value*(c.x-b.x);
result->y= b.y+a.value*(c.y-b.y);
return true;
}
/*:265*/
#line 6777 "weaver-interface-metafont.cweb"

/*266:*/
#line 6957 "weaver-interface-metafont.cweb"

else{
if(begin->type==TYPE_SUM)
return eval_pair_primary(mf,cx,begin->next,end,result);
else if(begin->type==TYPE_SUBTRACT){
if(!eval_pair_primary(mf,cx,begin->next,end,result))
return false;
result->x= -(result->x);
result->y= -(result->y);
return true;
}
else if(begin->type==TYPE_NUMERIC){
struct generic_token*tok;
float value= ((struct numeric_token*)begin)->value;
tok= begin->next;
if(tok->type==TYPE_DIVISION){
tok= begin->next;
if(tok==end||tok->next==end||tok->type!=TYPE_NUMERIC){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PAIR);
return false;
}
if(((struct numeric_token*)tok)->value==0.0){
RAISE_ERROR_DIVISION_BY_ZERO(mf,cx,OPTIONAL(begin->line));
return false;
}
value/= ((struct numeric_token*)tok)->value;
tok= tok->next;
}
if(!eval_pair_primary(mf,cx,begin->next,end,result))
return false;
result->x*= value;
result->y*= value;
return true;
}
}
/*:266*/
#line 6778 "weaver-interface-metafont.cweb"

RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PAIR);
return false;
}
/*:261*//*277:*/
#line 7182 "weaver-interface-metafont.cweb"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result){
return eval_transform_secondary(mf,cx,begin,end,result);
}
/*:277*//*279:*/
#line 7209 "weaver-interface-metafont.cweb"

bool eval_transform_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result){
struct generic_token*p,*last_transform= NULL,*last_token= NULL,
*end_secondary= NULL;
DECLARE_NESTING_CONTROL();
p= begin;
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
if(p!=end)
p= p->next;
else
p= NULL;
}while(p!=NULL);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
if(last_transform!=NULL){
if(end_secondary==NULL){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_TRANSFORM);
return false;
}
if(!eval_transform_secondary(mf,cx,begin,end_secondary,result))
return false;
/*280:*/
#line 7258 "weaver-interface-metafont.cweb"

if(last_transform->type==TYPE_ROTATED){
struct numeric_variable theta;
double angle_radian;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&theta))
return false;

angle_radian= theta.value*0.0174533;
TRANSFORM_ROTATE(result->value,angle_radian);
return true;
}
/*:280*//*281:*/
#line 7274 "weaver-interface-metafont.cweb"

else if(last_transform->type==TYPE_SCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE(result->value,scale.value);
return true;
}
/*:281*//*282:*/
#line 7287 "weaver-interface-metafont.cweb"

else if(last_transform->type==TYPE_SHIFTED){
struct pair_variable shift;
if(!eval_pair_primary(mf,cx,last_transform->next,end,&shift))
return false;
TRANSFORM_SHIFT(result->value,shift.x,shift.y);
return true;
}
/*:282*//*283:*/
#line 7300 "weaver-interface-metafont.cweb"

else if(last_transform->type==TYPE_SLANTED){
struct numeric_variable slant;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&slant))
return false;
TRANSFORM_SLANT(result->value,slant.value);
return true;
}
/*:283*//*284:*/
#line 7313 "weaver-interface-metafont.cweb"

else if(last_transform->type==TYPE_XSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE_X(result->value,scale.value);
return true;
}
/*:284*//*285:*/
#line 7326 "weaver-interface-metafont.cweb"

else if(last_transform->type==TYPE_YSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE_Y(result->value,scale.value);
return true;
}
/*:285*//*286:*/
#line 7341 "weaver-interface-metafont.cweb"

else if(last_transform->type==TYPE_ZSCALED){
struct pair_variable scale;
if(!eval_pair_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE_Z(result->value,scale.x,scale.y);
return true;
}
/*:286*//*287:*/
#line 7356 "weaver-interface-metafont.cweb"

else if(last_transform->type==TYPE_TRANSFORMED){
struct transform_variable b;
if(!eval_transform_primary(mf,cx,last_transform->next,end,&b))
return false;
MATRIX_MULTIPLICATION(result->value,b.value);
return true;
}
/*:287*/
#line 7243 "weaver-interface-metafont.cweb"

}
else
return eval_transform_primary(mf,cx,begin,end,result);
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_TRANSFORM);
return false;
}
/*:279*//*289:*/
#line 7396 "weaver-interface-metafont.cweb"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result){
if(begin==end&&begin->type==TYPE_SYMBOLIC){
/*290:*/
#line 7448 "weaver-interface-metafont.cweb"

struct symbolic_token*v= (struct symbolic_token*)begin;
struct transform_variable*content= v->var;
if(content==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(v->line),v);
return false;
}
if(content->type!=TYPE_T_TRANSFORM){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),
v,content->type,
TYPE_T_TRANSFORM);
return false;
}
if(isnan(content->value[0])){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(v->line),v,
TYPE_T_TRANSFORM);
return false;
}
memcpy(result->value,content->value,sizeof(float)*9);
return true;
/*:290*/
#line 7402 "weaver-interface-metafont.cweb"

}
else if(begin!=end&&begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
if(begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'(');
return false;
}
struct generic_token*p= begin->next;
DECLARE_NESTING_CONTROL();
bool has_comma= false;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p->type==TYPE_COMMA){
RESET_NESTING_COUNT();
has_comma= true;
break;
}
if(p!=end)
p= p->next;
else
p= NULL;
}while(p!=NULL&&p!=end);
if(has_comma){
/*292:*/
#line 7484 "weaver-interface-metafont.cweb"

int i;
struct generic_token*begin_numeric_expr,*end_numeric_expr;
struct numeric_variable numeric_result;
end_numeric_expr= begin_numeric_expr= begin->next;
float values[6];
for(i= 0;i<6;i++){
p= begin_numeric_expr;
do{
if(p!=end){
COUNT_NESTING(p);
}
if(IS_NOT_NESTED()&&((i<5&&p->type==TYPE_COMMA)||
(i==5&&p->type==TYPE_CLOSE_PARENTHESIS))){
break;
}
end_numeric_expr= p;
if(p!=end)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(p==NULL){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_TRANSFORM);
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
/*:292*/
#line 7426 "weaver-interface-metafont.cweb"

}
else{
/*291:*/
#line 7474 "weaver-interface-metafont.cweb"

struct generic_token*end_expr;
for(end_expr= begin->next;end_expr->next!=end;
end_expr= end_expr->next);
return eval_transform_expression(mf,cx,begin->next,end_expr,result);
/*:291*/
#line 7429 "weaver-interface-metafont.cweb"

}
}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_TRANSFORM);
return false;
}
/*:289*//*303:*/
#line 7753 "weaver-interface-metafont.cweb"

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
/*:303*//*305:*/
#line 7797 "weaver-interface-metafont.cweb"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin,end);
expected_length= number_of_joins+1;
/*306:*/
#line 7844 "weaver-interface-metafont.cweb"

if(number_of_joins==0){
if(end->type==TYPE_CLOSE_BRACES){
float dir_x,dir_y;
struct generic_token*p= begin;
DECLARE_NESTING_CONTROL();
while(p!=end){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&
p->next->type==TYPE_OPEN_BRACES)
break;
p= p->next;
}
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));

if(!eval_direction_specifier(mf,cx,p->next,end,&dir_x,&dir_y))
return false;
end= p;
}
result->permanent= false;
if(!eval_path_tertiary(mf,cx,begin,end,result))
return false;
return normalize_path(mf,cx,result);
}
/*:306*/
#line 7805 "weaver-interface-metafont.cweb"

/*307:*/
#line 7875 "weaver-interface-metafont.cweb"

result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points)*
expected_length);
if(result->points==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}
result->length= 0;
result->permanent= false;
result->number_of_points= 0;
result->cyclic= false;
/*:307*/
#line 7806 "weaver-interface-metafont.cweb"

/*308:*/
#line 7901 "weaver-interface-metafont.cweb"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d= NULL,*end_d= NULL,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
struct path_points*z0_point= NULL,*z1_point= NULL,*z2_point= NULL;
struct path_variable*z1_parent;
begin_z1= begin;
end_z1= begin_z1;
/*309:*/
#line 7931 "weaver-interface-metafont.cweb"

{
DECLARE_NESTING_CONTROL();
int next_type;
while(end_z1!=end){
COUNT_NESTING(end_z1);
next_type= end_z1->next->type;
if(IS_NOT_NESTED()&&
(next_type==TYPE_OPEN_BRACES||next_type==TYPE_JOIN||
next_type==TYPE_AMPERSAND||next_type==TYPE_STRAIGHT_JOIN))
break;
end_z1= (struct generic_token*)end_z1->next;
}
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
}
/*:309*//*314:*/
#line 8088 "weaver-interface-metafont.cweb"

{
struct path_variable z1;
if(!eval_path_tertiary(mf,cx,begin_z1,end_z1,&z1))
return false;

if(z1.length==1&&z1.points[0].format!=SUBPATH_FORMAT){
result->points[0].format= PROVISIONAL_FORMAT;
result->points[0].prov.x= z1.points[0].prov.x;
result->points[0].prov.y= z1.points[0].prov.y;
result->points[0].prov.dir1_x= result->points[0].prov.dir1_y= NAN;
result->points[0].prov.dir2_x= result->points[0].prov.dir2_y= NAN;
result->points[0].prov.tension1= 1.0;
result->points[0].prov.tension2= 1.0;
result->points[0].prov.atleast1= false;
result->points[0].prov.atleast2= false;
result->number_of_points++;
}else{
result->points[0].format= SUBPATH_FORMAT;
if(!recursive_copy_points(mf,cx,temporary_alloc,
&(result->points[0].subpath),&z1,true))
return false;
result->number_of_points+= 
result->points[0].subpath->number_of_points;
}
result->cyclic= false;
result->length++;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&z1,false);
}
/*:314*/
#line 7910 "weaver-interface-metafont.cweb"

while(end_z1!=end||result->length<expected_length){
/*310:*/
#line 7953 "weaver-interface-metafont.cweb"

begin_d= end_z1->next;
if(begin_d->type!=TYPE_OPEN_BRACES){
begin_d= NULL;
end_d= NULL;
}
else{
DECLARE_NESTING_CONTROL();
if(begin_d==end){
RAISE_ERROR_UNCLOSED_DELIMITER(mf,cx,OPTIONAL(begin_d->line),'{');
return false;
}
end_d= begin_d->next;
while(end_d!=end){
if(IS_NOT_NESTED()&&end_d->type==TYPE_CLOSE_BRACES)
break;
COUNT_NESTING(end_d);
end_d= end_d->next;
}
if(end_d->type!=TYPE_CLOSE_BRACES){
RAISE_ERROR_UNCLOSED_DELIMITER(mf,cx,OPTIONAL(begin_d->line),'{');
return false;
}
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin_d->line));
}
/*:310*//*311:*/
#line 7987 "weaver-interface-metafont.cweb"

if(end_d==NULL)
begin_j= end_z1->next;
else
begin_j= end_d->next;
end_j= begin_j;
if(begin_j==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PATH);
return false;
}
if(begin_j->type==TYPE_JOIN&&
(begin_j->next->type==TYPE_CONTROLS||
begin_j->next->type==TYPE_TENSION)){
DECLARE_NESTING_CONTROL();
end_j= end_j->next;
while(end_j!=end){
COUNT_NESTING(end_j);
if(IS_NOT_NESTED()&&end_j->type==TYPE_JOIN)
break;
end_j= end_j->next;
}
if(end_j==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
}
else if(begin_j->type!=TYPE_JOIN&&begin_j->type!=TYPE_AMPERSAND&&
begin_j->type!=TYPE_STRAIGHT_JOIN){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
/*:311*//*312:*/
#line 8026 "weaver-interface-metafont.cweb"

begin_e= end_j->next;
if(begin_e->type!=TYPE_OPEN_BRACES){
begin_e= NULL;
end_e= NULL;
}else{
DECLARE_NESTING_CONTROL();
if(begin_e==end){
RAISE_ERROR_UNCLOSED_DELIMITER(mf,cx,OPTIONAL(begin_e->line),'{');
return false;
}
end_e= begin_e->next;
while(end_e!=end){
if(IS_NOT_NESTED()&&end_e->type==TYPE_CLOSE_BRACES)
break;
COUNT_NESTING(end_e);
end_e= end_e->next;
}
if(end_e->type!=TYPE_CLOSE_BRACES){
RAISE_ERROR_UNCLOSED_DELIMITER(mf,cx,OPTIONAL(begin_e->line),'{');
return false;
}
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin_e->line));
}
/*:312*//*313:*/
#line 8057 "weaver-interface-metafont.cweb"

{
DECLARE_NESTING_CONTROL();
if(end_e==NULL)
begin_z2= (struct generic_token*)end_j->next;
else
begin_z2= (struct generic_token*)end_e->next;
end_z2= begin_z2;
while(end_z2!=end){
COUNT_NESTING(end_z2);
if(IS_NOT_NESTED()&&
(end_z2->next->type==TYPE_OPEN_BRACES||
end_z2->next->type==TYPE_JOIN||
end_z2->next->type==TYPE_AMPERSAND||
end_z2->next->type==TYPE_STRAIGHT_JOIN))
break;
end_z2= end_z2->next;
}
if(end_z2==end)
COUNT_NESTING(end_z2);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin_z2->line));
}
/*:313*/
#line 7912 "weaver-interface-metafont.cweb"

/*315:*/
#line 8134 "weaver-interface-metafont.cweb"

if(begin_z2==end_z2&&begin_z2->type==TYPE_CYCLE){
struct path_points*p= result->points;

while(p[0].format==SUBPATH_FORMAT)
p= ((struct path_variable*)p[0].subpath)->points;
memcpy(&(result->points[result->length]),p,sizeof(struct path_points));
result->length++;
result->number_of_points++;
result->cyclic= true;
}
else{
struct path_variable z2;
if(!eval_path_tertiary(mf,cx,begin_z2,end_z2,&z2))
return false;
result->cyclic= false;
if(z2.length==1&&z2.points[0].format!=SUBPATH_FORMAT){
result->points[result->length].format= PROVISIONAL_FORMAT;
result->points[result->length].prov.x= z2.points[0].prov.x;
result->points[result->length].prov.y= z2.points[0].prov.y;
result->points[result->length].prov.dir1_x= NAN;
result->points[result->length].prov.dir1_y= NAN;
result->points[result->length].prov.dir2_x= NAN;
result->points[result->length].prov.dir2_y= NAN;
result->points[result->length].prov.tension1= 1.0;
result->points[result->length].prov.tension2= 1.0;
result->points[result->length].prov.atleast1= false;
result->points[result->length].prov.atleast2= false;
result->number_of_points++;
}
else{
result->points[result->length].format= SUBPATH_FORMAT;
if(!recursive_copy_points(mf,cx,temporary_alloc,
&(result->points[result->length].subpath),
&z2,true))
return false;
result->number_of_points+= 
result->points[result->length].subpath->number_of_points;
}
result->length++;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&z2,false);
}
/*:315*//*316:*/
#line 8207 "weaver-interface-metafont.cweb"


z1_point= &(result->points[result->length-2]);
z1_parent= result;
z0_point= NULL;
while(z1_point->format==SUBPATH_FORMAT){
struct path_variable*p= (struct path_variable*)z1_point->subpath;
z1_point= &(p->points[p->length-1]);
z1_parent= p;
if(p->length!=1&&z1_point->format!=SUBPATH_FORMAT)
z0_point= &(p->points[p->length-2]);
}
if(z0_point==NULL&&result->length> 2){
z0_point= &(result->points[result->length-3]);
while(z0_point->format==SUBPATH_FORMAT){
struct path_variable*p= (struct path_variable*)z0_point->subpath;
z0_point= &(p->points[p->length-1]);
}
}
z2_point= &(result->points[result->length-1]);
while(z2_point->format==SUBPATH_FORMAT){
struct path_variable*p= (struct path_variable*)z2_point->subpath;
z2_point= &(p->points[0]);
}
/*:316*/
#line 7913 "weaver-interface-metafont.cweb"

/*317:*/
#line 8241 "weaver-interface-metafont.cweb"

if(!eval_direction_specifier(mf,cx,begin_d,end_d,
&(z1_point->prov.dir1_x),
&(z1_point->prov.dir1_y)))
return false;
if(!eval_direction_specifier(mf,cx,begin_e,end_e,
&(z1_point->prov.dir2_x),
&(z1_point->prov.dir2_y)))
return false;
/*:317*//*324:*/
#line 8405 "weaver-interface-metafont.cweb"

if((begin_j==end_j&&(begin_j->type==TYPE_AMPERSAND||
begin_j->type==TYPE_STRAIGHT_JOIN))||
(z1_point->prov.x==z2_point->prov.x&&
z1_point->prov.y==z2_point->prov.y)){
if(z0_point!=NULL&&z0_point->format==PROVISIONAL_FORMAT&&
isnan(z0_point->prov.dir2_y)){
z0_point->prov.dir2_x= NAN;
z0_point->prov.dir2_y= 1.0;
}
if(z2_point->format==PROVISIONAL_FORMAT&&
isnan(z2_point->prov.dir1_y)){
z2_point->prov.dir1_x= NAN;
z2_point->prov.dir1_y= 1.0;
}

if(z1_point->prov.x==z2_point->prov.x&&
z1_point->prov.y==z2_point->prov.y&&
z1_point->format==PROVISIONAL_FORMAT){
z1_point->format= FINAL_FORMAT;
z1_point->point.u_x= z1_point->point.v_x= z1_point->point.x;
z1_point->point.u_y= z1_point->point.v_y= z1_point->point.y;
}
}
/*:324*//*326:*/
#line 8489 "weaver-interface-metafont.cweb"

if(!isnan(z1_point->prov.dir2_y)&&
z2_point->format==PROVISIONAL_FORMAT&&isnan(z2_point->prov.dir1_y)){
z2_point->prov.dir1_x= z1_point->prov.dir2_x;
z2_point->prov.dir1_y= z1_point->prov.dir2_y;
}
if(z0_point!=NULL&&isnan(z0_point->prov.dir2_y)&&
!isnan(z1_point->prov.dir1_y)){
z0_point->prov.dir2_x= z1_point->prov.dir1_x;
z0_point->prov.dir2_y= z1_point->prov.dir1_y;
}
/*:326*/
#line 7914 "weaver-interface-metafont.cweb"

/*327:*/
#line 8521 "weaver-interface-metafont.cweb"

if(begin_j==end_j&&begin_j->type==TYPE_AMPERSAND){
double dif_x= z1_point->prov.x-z2_point->prov.x;
double dif_y= z1_point->prov.y-z2_point->prov.y;
if(hypot(dif_x,dif_y)> 0.00002){
RAISE_ERROR_DISCONTINUOUS_PATH(mf,cx,OPTIONAL(begin_j->line),
z1_point->prov.x,z1_point->prov.y,
z2_point->prov.x,z2_point->prov.y);
return false;
}

result->number_of_points--;
if(z1_parent!=result){
z1_parent->length--;
z1_parent->number_of_points--;
}
z1_point->point.x= NAN;
z1_point->point.y= NAN;
}
/*:327*//*328:*/
#line 8548 "weaver-interface-metafont.cweb"

else if(begin_j==end_j&&begin_j->type==TYPE_STRAIGHT_JOIN){
z1_point->format= FINAL_FORMAT;
z1_point->point.u_x= z1_point->point.x+(1.0/3.0)*
(z2_point->prov.x-z1_point->point.x);
z1_point->point.u_y= z1_point->point.y+(1.0/3.0)*
(z2_point->prov.y-z1_point->point.y);
z1_point->point.v_x= z1_point->point.x+(2.0/3.0)*
(z2_point->prov.x-z1_point->point.x);
z1_point->point.v_y= z1_point->point.y+(2.0/3.0)*
(z2_point->prov.y-z1_point->point.y);
}
/*:328*//*329:*/
#line 8573 "weaver-interface-metafont.cweb"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
z1_point->prov.tension1= 1.0;
z1_point->prov.tension2= 1.0;
}
/*:329*//*330:*/
#line 8592 "weaver-interface-metafont.cweb"

else if(begin_j->type==TYPE_JOIN&&begin_j!=end_j&&
begin_j->next->type==TYPE_CONTROLS){
DECLARE_NESTING_CONTROL();
struct generic_token*begin_u,*end_u,*begin_v= NULL,*end_v= NULL;
struct pair_variable u,v;
if(begin_j->next==end_j||begin_j->next->next==end_j){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
begin_u= begin_j->next->next;
end_u= begin_u;
while(end_u->next!=end_j){
COUNT_NESTING(end_u);
if(IS_NOT_NESTED()&&end_u->next->type==TYPE_AND)
break;
end_u= end_u->next;
}
if(end_u->next!=end_j){
if(end_u->next->next==end_j){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
begin_v= end_u->next->next;
end_v= begin_v;
while(end_v->next!=end_j)
end_v= end_v->next;
}
if(!eval_pair_primary(mf,cx,begin_u,end_u,&u))
return false;
z1_point->format= FINAL_FORMAT;
z1_point->point.u_x= u.x;
z1_point->point.u_y= u.y;
if(begin_v!=NULL){
if(!eval_pair_primary(mf,cx,begin_v,end_v,&v))
return false;
z1_point->point.v_x= v.x;
z1_point->point.v_y= v.y;
}
else{
z1_point->point.v_x= u.x;
z1_point->point.v_y= u.y;
}
/*325:*/
#line 8451 "weaver-interface-metafont.cweb"

if(z0_point!=NULL&&z0_point->format==PROVISIONAL_FORMAT&&
isnan(z0_point->prov.dir2_y)){
z0_point->prov.dir2_x= z1_point->point.u_x-z1_point->point.x;
z0_point->prov.dir2_y= z1_point->point.u_y-z1_point->point.y;
if(z0_point->prov.dir2_x==0.0&&z0_point->prov.dir2_y==0.0){
z0_point->prov.dir2_x= NAN;
z0_point->prov.dir2_y= 1.0;
}
}
if(z2_point->format==PROVISIONAL_FORMAT&&isnan(z2_point->prov.dir1_y)){
z2_point->prov.dir1_x= z2_point->prov.x-z1_point->point.v_x;
z2_point->prov.dir1_y= z2_point->prov.y-z1_point->point.v_y;
if(z2_point->prov.dir1_x==0.0&&z2_point->prov.dir1_y==0.0){
z2_point->prov.dir1_x= NAN;
z2_point->prov.dir1_y= 1.0;
}
}
/*:325*/
#line 8637 "weaver-interface-metafont.cweb"

}
/*:330*//*331:*/
#line 8655 "weaver-interface-metafont.cweb"

else if(begin_j->type==TYPE_JOIN&&begin_j!=end_j&&
begin_j->next->type==TYPE_TENSION){
DECLARE_NESTING_CONTROL();
struct generic_token*begin_t0,*end_t0,*begin_t1= NULL,*end_t1= NULL;
struct numeric_variable t0,t1;
if(begin_j->next==end_j||begin_j->next->next==end_j){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
begin_t0= begin_j->next->next;
z1_point->prov.atleast1= (begin_t0->type==TYPE_ATLEAST);
if(begin_t0->type==TYPE_ATLEAST){
begin_t0= begin_t0->next;
if(begin_t0==end_j){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
}
end_t0= begin_t0;
while(end_t0->next!=end_j){
COUNT_NESTING(end_t0);
if(IS_NOT_NESTED()&&end_t0->next->type==TYPE_AND)
break;
end_t0= end_t0->next;
}
if(end_t0->next!=end_j){
if(begin_t0->next->next==end_j){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
begin_t1= end_t0->next->next;
z1_point->prov.atleast2= (begin_t1->type==TYPE_ATLEAST);
if(begin_t1->type==TYPE_ATLEAST){
begin_t1= (struct generic_token*)begin_t1->next;
if(begin_t1==end_j){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin_j->line),
TYPE_T_PATH);
return false;
}
}
end_t1= begin_t1;
while(end_t1->next!=end_j)
end_t1= end_t1->next;
}
if(!eval_numeric_primary(mf,cx,begin_t0,end_t0,&t0))
return false;
z1_point->prov.tension1= t0.value;
if(begin_t1!=NULL){
if(!eval_numeric_primary(mf,cx,begin_t1,end_t1,&t1))
return false;
z1_point->prov.tension2= t1.value;
}
else{
z1_point->prov.atleast2= z1_point->prov.atleast1;
z1_point->prov.tension2= z1_point->prov.tension1;
}
if(z1_point->prov.tension1<0.75){
RAISE_ERROR_INVALID_TENSION(mf,cx,OPTIONAL(begin_t0->line),
z1_point->prov.tension1,0,
z1_point->prov.x,z1_point->prov.y,
z2_point->prov.x,z2_point->prov.y);
return false;
}
if(z1_point->prov.tension2<0.75){
RAISE_ERROR_INVALID_TENSION(mf,cx,OPTIONAL(begin_t0->line),
z1_point->prov.tension2,1,
z1_point->prov.x,z1_point->prov.y,
z2_point->prov.x,z2_point->prov.y);
return false;
}
}
/*:331*/
#line 7915 "weaver-interface-metafont.cweb"

begin_z1= begin_z2;
end_z1= end_z2;
}

/*332:*/
#line 8744 "weaver-interface-metafont.cweb"

z0_point= &(result->points[0]);
while(z0_point->format==SUBPATH_FORMAT){
struct path_variable*p= (struct path_variable*)z0_point->subpath;
z0_point= &(p->points[0]);
}
/*:332*//*333:*/
#line 8761 "weaver-interface-metafont.cweb"

if(end_z1!=end){
float w_x= NAN,w_y= NAN;
if(!eval_direction_specifier(mf,cx,end_z1->next,end,&w_x,&w_y))
return false;
if(z1_point->format==PROVISIONAL_FORMAT&&
isnan(z1_point->prov.dir2_y)){
z1_point->prov.dir2_x= w_x;
z1_point->prov.dir2_y= w_y;
}
if(result->cyclic){
z1_point->prov.dir1_x= w_x;
z1_point->prov.dir1_y= w_y;
}
}
/*:333*//*334:*/
#line 8797 "weaver-interface-metafont.cweb"

if(!(result->cyclic)){
if(z0_point->format==PROVISIONAL_FORMAT&&
isnan(z0_point->prov.dir1_y)){
z0_point->prov.dir1_x= NAN;
z0_point->prov.dir1_y= 1.0;
}
if(z1_point->format==PROVISIONAL_FORMAT&&
isnan(z1_point->prov.dir2_y)){
z1_point->prov.dir2_x= NAN;
z1_point->prov.dir2_y= 1.0;
}
if(z2_point->format==PROVISIONAL_FORMAT){
z2_point->format= FINAL_FORMAT;
z2_point->point.u_x= z2_point->point.v_x= z2_point->point.x;
z2_point->point.u_y= z2_point->point.v_y= z2_point->point.y;
}
}
/*:334*//*335:*/
#line 8823 "weaver-interface-metafont.cweb"

if(result->cyclic&&z0_point->format==FINAL_FORMAT){
memcpy(z2_point,z0_point,sizeof(struct path_points));
if(z1_point->format==PROVISIONAL_FORMAT&&
isnan(z1_point->prov.dir2_y)){
z1_point->prov.dir2_x= z2_point->point.u_x-z2_point->point.x;
z1_point->prov.dir2_y= z2_point->point.u_y-z2_point->point.y;
if(z1_point->prov.dir2_x==0.0&&z1_point->prov.dir2_y==0.0){
z1_point->prov.dir2_x= NAN;
z1_point->prov.dir2_x= 1.0;
}
}
}
/*:335*//*336:*/
#line 8852 "weaver-interface-metafont.cweb"

else if(result->cyclic){
if(!isnan(z0_point->prov.dir1_y)){
z2_point->prov.dir1_x= z0_point->prov.dir1_x;
z2_point->prov.dir1_y= z0_point->prov.dir1_y;
if(z1_point->format==PROVISIONAL_FORMAT&&
isnan(z1_point->prov.dir2_y)){
z1_point->prov.dir2_x= z2_point->prov.dir1_x;
z1_point->prov.dir2_y= z2_point->prov.dir1_y;
}
}
else{
z0_point->prov.dir1_x= z2_point->prov.dir1_x;
z0_point->prov.dir1_y= z2_point->prov.dir1_y;
}
z2_point->prov.dir2_x= z0_point->prov.dir2_x;
z2_point->prov.dir2_y= z0_point->prov.dir2_y;
}
/*:336*/
#line 7920 "weaver-interface-metafont.cweb"

}
/*:308*/
#line 7807 "weaver-interface-metafont.cweb"


return normalize_path(mf,cx,result);
}
/*:305*//*319:*/
#line 8266 "weaver-interface-metafont.cweb"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y){

if(begin!=NULL&&begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'{');
return false;
}
/*320:*/
#line 8287 "weaver-interface-metafont.cweb"

if(begin==NULL||end==NULL)
return true;
/*:320*/
#line 8276 "weaver-interface-metafont.cweb"

/*321:*/
#line 8297 "weaver-interface-metafont.cweb"

if(begin->next->type==TYPE_CURL){
struct numeric_variable gamma;
struct generic_token*begin_n,*end_n;
begin_n= begin->next->next;
end_n= begin_n;
if(end_n==end){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(end_n->line),
TYPE_T_NUMERIC);
return false;
}
while(end_n->next!=end)
end_n= end_n->next;
if(!eval_numeric_expression(mf,cx,begin_n,end_n,&gamma))
return false;
*w_x= NAN;
*w_y= gamma.value;
return true;
}
/*:321*/
#line 8277 "weaver-interface-metafont.cweb"

/*322:*/
#line 8323 "weaver-interface-metafont.cweb"

DECLARE_NESTING_CONTROL();
struct generic_token*begin_a,*end_a,*begin_b= NULL,*end_b;
begin_a= (struct generic_token*)begin->next;
end_a= begin_a;
while(end_a->next!=end){
COUNT_NESTING(end_a);
if(IS_NOT_NESTED()&&end_a->next->type==TYPE_COMMA){
begin_b= (struct generic_token*)end_a->next->next;
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
*w_x= a.value;
*w_y= b.value;
return true;
}
/*:322*/
#line 8278 "weaver-interface-metafont.cweb"

/*323:*/
#line 8357 "weaver-interface-metafont.cweb"

else{
COUNT_NESTING(end_a);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin_a->line));
struct pair_variable a;
if(!eval_pair_expression(mf,cx,begin_a,end_a,&a))
return false;
*w_x= a.x;
*w_y= a.y;
return true;
}
/*:323*/
#line 8279 "weaver-interface-metafont.cweb"

return false;
}
/*:319*//*338:*/
#line 8906 "weaver-interface-metafont.cweb"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result){
struct generic_token*p,*prev= NULL;
bool this_expression_is_pair= false;
DECLARE_NESTING_CONTROL();
p= begin;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&IS_VALID_SUM_OR_SUB(prev,p)){
this_expression_is_pair= true;
break;
}
prev= p;
if(p!=end)
p= p->next;
else
p= NULL;
}while(p!=NULL);
if(this_expression_is_pair){
struct pair_variable pair;
if(!eval_pair_expression(mf,cx,begin,end,&pair))
return false;
result->cyclic= false;
result->length= 1;
result->number_of_points= 1;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
if(result->points==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}
result->points->format= FINAL_FORMAT;
result->points->point.x= pair.x;
result->points->point.y= pair.y;
result->points->point.u_x= pair.x;
result->points->point.u_y= pair.y;
result->points->point.v_x= pair.x;
result->points->point.v_y= pair.y;
return true;
}
else
return eval_path_secondary(mf,cx,begin,end,result);
}
/*:338*//*340:*/
#line 8989 "weaver-interface-metafont.cweb"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result){
bool have_transform= false,have_pair_operator= false;
struct generic_token*p,*last_fraction= NULL,*transform_op= NULL,
*before_transform= NULL,*prev= NULL,
*prev_prev= NULL;
DECLARE_NESTING_CONTROL();
p= begin;
do{
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&(p->type==TYPE_MULTIPLICATION||
p->type==TYPE_DIVISION||p->type==TYPE_ROTATED||
p->type==TYPE_SCALED||p->type==TYPE_SHIFTED||
p->type==TYPE_SLANTED||p->type==TYPE_XSCALED||
p->type==TYPE_YSCALED||p->type==TYPE_ZSCALED||
p->type==TYPE_TRANSFORMED)){
if(p->type==TYPE_DIVISION&&prev->type==TYPE_NUMERIC&&
p!=end&&p->next->type!=TYPE_NUMERIC&&
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
if(p!=end)
p= p->next;
else
p= NULL;
}while(p!=NULL);
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
if(have_transform){
if(transform_op->next==NULL){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PATH);
return false;
}
if(!eval_path_secondary(mf,cx,begin,before_transform,result))
return false;
/*341:*/
#line 9096 "weaver-interface-metafont.cweb"

if(transform_op->type==TYPE_ROTATED){
struct numeric_variable a;
double theta,sin_theta,cos_theta;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
theta= 0.0174533*a.value;
sin_theta= sin(theta);
cos_theta= cos(theta);
path_rotate(result,sin_theta,cos_theta);
return true;
}
/*:341*/
#line 9037 "weaver-interface-metafont.cweb"

/*344:*/
#line 9141 "weaver-interface-metafont.cweb"

else if(transform_op->type==TYPE_SCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_xyscale(result,a.value,a.value);
return true;
}
/*:344*/
#line 9038 "weaver-interface-metafont.cweb"

/*347:*/
#line 9181 "weaver-interface-metafont.cweb"

else if(transform_op->type==TYPE_SHIFTED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end,&a))
return false;
path_shift(result,a.x,a.y);
return true;
}
/*:347*/
#line 9039 "weaver-interface-metafont.cweb"

/*350:*/
#line 9215 "weaver-interface-metafont.cweb"

else if(transform_op->type==TYPE_SLANTED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_slant(result,a.value);
return true;
}
/*:350*/
#line 9040 "weaver-interface-metafont.cweb"

/*353:*/
#line 9246 "weaver-interface-metafont.cweb"

else if(transform_op->type==TYPE_XSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_xyscale(result,a.value,1.0);
return true;
}
/*:353*/
#line 9041 "weaver-interface-metafont.cweb"

/*354:*/
#line 9260 "weaver-interface-metafont.cweb"

else if(transform_op->type==TYPE_YSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_xyscale(result,1.0,a.value);
return true;
}
/*:354*/
#line 9042 "weaver-interface-metafont.cweb"

/*355:*/
#line 9281 "weaver-interface-metafont.cweb"

else if(transform_op->type==TYPE_ZSCALED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end,&a))
return false;
path_zscale(result,a.x,a.y);
return true;
}
/*:355*/
#line 9043 "weaver-interface-metafont.cweb"

/*358:*/
#line 9321 "weaver-interface-metafont.cweb"

else if(transform_op->type==TYPE_TRANSFORMED){
struct transform_variable a;
if(!eval_transform_primary(mf,cx,transform_op->next,end,&a))
return false;
path_transform(result,a.value);
return true;
}
else{
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PATH);
return false;
}
/*:358*/
#line 9044 "weaver-interface-metafont.cweb"

}
else if(have_pair_operator){
struct pair_variable pair;
if(!eval_pair_secondary(mf,cx,begin,end,&pair))
return false;
result->cyclic= false;
result->length= 1;
result->number_of_points= 1;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
if(result->points==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}
result->points->format= FINAL_FORMAT;
result->points[0].point.x= pair.x;
result->points[0].point.y= pair.y;
result->points[0].point.u_x= pair.x;
result->points[0].point.u_y= pair.y;
result->points[0].point.v_x= pair.x;
result->points[0].point.v_y= pair.y;
return true;
}
else
return eval_path_primary(mf,cx,begin,end,result);
}
/*:340*//*343:*/
#line 9117 "weaver-interface-metafont.cweb"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta){
int i;
for(i= 0;i<p->length;i++){
double x= p->points[i].prov.x,y= p->points[i].prov.y;
p->points[i].prov.x= x*cos_theta-y*sin_theta;
p->points[i].prov.y= x*sin_theta+y*cos_theta;
x= p->points[i].point.u_x;
y= p->points[i].point.u_y;
p->points[i].point.u_x= x*cos_theta-y*sin_theta;
p->points[i].point.u_y= x*sin_theta+y*cos_theta;
x= p->points[i].point.v_x;
y= p->points[i].point.v_y;
p->points[i].point.v_x= x*cos_theta-y*sin_theta;
p->points[i].point.v_y= x*sin_theta+y*cos_theta;
}
}
/*:343*//*346:*/
#line 9163 "weaver-interface-metafont.cweb"

void path_xyscale(struct path_variable*p,float x,float y){
int i;
for(i= 0;i<p->length;i++){
p->points[i].point.x*= x;
p->points[i].point.y*= y;
p->points[i].point.u_x*= x;
p->points[i].point.u_y*= y;
p->points[i].point.v_x*= x;
p->points[i].point.v_y*= y;
}
}
/*:346*//*349:*/
#line 9197 "weaver-interface-metafont.cweb"

void path_shift(struct path_variable*p,float x,float y){
int i;
for(i= 0;i<p->length;i++){
p->points[i].point.x+= x;
p->points[i].point.y+= y;
p->points[i].point.u_x+= x;
p->points[i].point.u_y+= y;
p->points[i].point.v_x+= x;
p->points[i].point.v_y+= y;
}
}
/*:349*//*352:*/
#line 9231 "weaver-interface-metafont.cweb"

void path_slant(struct path_variable*p,float s){
int i;
for(i= 0;i<p->length;i++){
p->points[i].point.x+= s*p->points[i].point.y;
p->points[i].point.u_x+= s*p->points[i].point.u_y;
p->points[i].point.v_x+= s*p->points[i].point.v_y;
}
}
/*:352*//*357:*/
#line 9297 "weaver-interface-metafont.cweb"

void path_zscale(struct path_variable*p,float x,float y){
int i;
for(i= 0;i<p->length;i++){
float x0= p->points[i].point.x;
float y0= p->points[i].point.y;
p->points[i].point.x= x0*x-y0*y;
p->points[i].point.y= x0*y+y0*x;
x0= p->points[i].point.u_x;
y0= p->points[i].point.u_y;
p->points[i].point.u_x= x0*x-y0*y;
p->points[i].point.u_y= x0*y+y0*x;
x0= p->points[i].point.v_x;
y0= p->points[i].point.v_y;
p->points[i].point.v_x= x0*x-y0*y;
p->points[i].point.v_x= x0*y+y0*x;
}
}
/*:357*//*360:*/
#line 9343 "weaver-interface-metafont.cweb"

void path_transform(struct path_variable*p,float*M){
int i;
for(i= 0;i<p->length;i++){
float x0= p->points[i].point.x;
float y0= p->points[i].point.y;
p->points[i].point.x= LINEAR_TRANSFORM_X(x0,y0,M);
p->points[i].point.y= LINEAR_TRANSFORM_Y(x0,y0,M);
x0= p->points[i].point.u_x;
y0= p->points[i].point.u_y;
p->points[i].point.u_x= LINEAR_TRANSFORM_X(x0,y0,M);
p->points[i].point.u_y= LINEAR_TRANSFORM_Y(x0,y0,M);
x0= p->points[i].point.v_x;
y0= p->points[i].point.v_y;
p->points[i].point.v_x= LINEAR_TRANSFORM_X(x0,y0,M);
p->points[i].point.v_x= LINEAR_TRANSFORM_Y(x0,y0,M);
}
}
/*:360*//*364:*/
#line 9413 "weaver-interface-metafont.cweb"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result){
if(begin->type==TYPE_REVERSE){
/*365:*/
#line 9447 "weaver-interface-metafont.cweb"

struct path_variable tmp;
if(begin->next==NULL||begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PATH);
return false;
}
if(!eval_path_primary(mf,cx,begin->next,end,&tmp))
return false;
if(!reverse_path(mf,cx,result,&tmp))
return false;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&tmp,false);
return true;
/*:365*/
#line 9419 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_SUBPATH){
/*368:*/
#line 9534 "weaver-interface-metafont.cweb"

DECLARE_NESTING_CONTROL();
struct pair_variable a;
struct path_variable b;
struct generic_token*of,*end_pair_expr= begin;
struct generic_token*begin_subexpr;
if(begin->next==NULL||end_pair_expr->type==TYPE_OF||begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PATH);
return false;
}
of= end_pair_expr->next;
while(of!=NULL&&of!=end){
COUNT_NESTING(of);
if(IS_NOT_NESTED()&&of->type==TYPE_OF)
break;
end_pair_expr= of;
of= of->next;
}
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
if(of==NULL||of==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PATH);
return false;
}
if(!eval_pair_expression(mf,cx,begin->next,end_pair_expr,&a))
return false;
begin_subexpr= of->next;
if(!eval_path_primary(mf,cx,begin_subexpr,end,&b))
return false;
{
int final_path_size,offset,i;
result->cyclic= false;

if(b.cyclic)
b.length= b.length-1;
if(a.x<0&&!b.cyclic)
a.x= 0;
if(a.y<0&&!b.cyclic)
a.y= 0;
if(a.x>=b.length&&!b.cyclic)
a.x= b.length-1;
if(a.y>=b.length&&!b.cyclic)
a.y= b.length-1;
final_path_size= a.y-a.x;
if(final_path_size<0)
final_path_size*= -1;
final_path_size++;
offset= ((int)((a.x<=a.y)?(a.x):(a.y)))%b.length;
if(offset<0)
offset*= -1;
result->length= final_path_size;
result->number_of_points= final_path_size;
result->points= (struct path_points*)
temporary_alloc(final_path_size*
sizeof(struct path_points));
if(result->points==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}
for(i= 0;i<result->length;i++)
memcpy(&(result->points[i]),&(b.points[(offset+i)%b.length]),
sizeof(struct path_points));

result->points[result->length-1].point.u_x= 
result->points[result->length-1].point.x;
result->points[result->length-1].point.u_y= 
result->points[result->length-1].point.y;
result->points[result->length-1].point.v_x= 
result->points[result->length-1].point.x;
result->points[result->length-1].point.v_y= 
result->points[result->length-1].point.y;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&b,false);
if(a.x> a.y){
struct path_variable c;
if(!reverse_path(mf,cx,&c,result))
return false;
if(temporary_free!=NULL)
temporary_free(result->points);
result->points= c.points;
}
return true;
}
/*:368*/
#line 9422 "weaver-interface-metafont.cweb"

}
else if(begin==end&&begin->type==TYPE_SYMBOLIC){
/*369:*/
#line 9623 "weaver-interface-metafont.cweb"

{
struct symbolic_token*v= (struct symbolic_token*)begin;
struct path_variable*var= v->var;
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(begin->line),v);
return false;
}
if(((struct pair_variable*)var)->type==TYPE_T_PAIR){
if(isnan(((struct pair_variable*)var)->x)){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
v,TYPE_T_PAIR);
return false;
}
result->length= 1;
result->number_of_points= 1;
result->cyclic= false;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
result->points[0].format= FINAL_FORMAT;
result->points[0].point.x= ((struct pair_variable*)var)->x;
result->points[0].point.y= ((struct pair_variable*)var)->y;
result->points[0].point.u_x= ((struct pair_variable*)var)->x;
result->points[0].point.u_y= ((struct pair_variable*)var)->y;
result->points[0].point.v_x= ((struct pair_variable*)var)->x;
result->points[0].point.v_y= ((struct pair_variable*)var)->y;
return true;
}
else if(var->type==TYPE_T_PATH){
if(var->length==-1){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
v,TYPE_T_PATH);
return false;
}
return recursive_copy_points(mf,cx,temporary_alloc,&result,var,false);
}
else{
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),v,
var->type,TYPE_T_PATH);
return false;
}
}
/*:369*/
#line 9425 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*370:*/
#line 9673 "weaver-interface-metafont.cweb"

struct generic_token*t= begin->next;
bool found_comma= false;
DECLARE_NESTING_CONTROL();
if(begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'(');
return false;
}
while(t!=NULL&&t->next!=end){
COUNT_NESTING(t);
if(IS_NOT_NESTED()&&t->type==TYPE_COMMA){
found_comma= true;
break;
}
t= t->next;
}
if(!found_comma){
return eval_path_expression(mf,cx,begin->next,t,result);
}
/*:370*/
#line 9429 "weaver-interface-metafont.cweb"

}
/*409:*/
#line 10581 "weaver-interface-metafont.cweb"

else if(begin->type==TYPE_MAKEPATH){
struct pen_variable tmp;
if(begin->next==NULL||begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PATH);
return false;
}
if(!eval_pen_primary(mf,cx,begin->next,end,&tmp))
return false;
if(tmp.flags&FLAG_NULL){
/*410:*/
#line 10614 "weaver-interface-metafont.cweb"

result->length= 1;
result->number_of_points= 1;
result->cyclic= false;
result->points= 
(struct path_points*)temporary_alloc(sizeof(struct path_points));
result->points[0].format= FINAL_FORMAT;
result->points[0].point.x= 0.0;
result->points[0].point.y= 0.0;
result->points[0].point.u_x= 0.0;
result->points[0].point.u_y= 0.0;
result->points[0].point.v_x= 0.0;
result->points[0].point.v_y= 0.0;
/*:410*/
#line 10592 "weaver-interface-metafont.cweb"

}
else if(tmp.flags&FLAG_CIRCULAR){
/*411:*/
#line 10634 "weaver-interface-metafont.cweb"

result->length= 9;
result->number_of_points= 9;
result->points= 
(struct path_points*)temporary_alloc(sizeof(struct path_points)*9);
result->points[0].format= FINAL_FORMAT;
result->points[0].point.x= 0.5;result->points[0].point.y= 0.0;
result->points[0].point.u_x= 0.5;result->points[0].point.u_y= 0.13261;
result->points[0].point.v_x= 0.44733;result->points[0].point.v_y= 0.2598;
result->points[1].format= FINAL_FORMAT;
result->points[1].point.x= 0.35356;result->points[1].point.y= 0.35356;
result->points[1].point.u_x= 0.2598;result->points[1].point.u_y= 0.44733;
result->points[1].point.v_x= 0.13261;result->points[1].point.v_y= 0.5;
result->points[2].format= FINAL_FORMAT;
result->points[2].point.x= 0.0;result->points[2].point.y= 0.5;
result->points[2].point.u_x= -0.13261;result->points[2].point.u_y= 0.5;
result->points[2].point.v_x= -0.2598;result->points[2].point.v_y= 0.44733;
result->points[3].format= FINAL_FORMAT;
result->points[3].point.x= -0.35356;result->points[3].point.y= 0.35356;
result->points[3].point.u_x= -0.44733;result->points[3].point.u_y= 0.2598;
result->points[3].point.v_x= -0.5;result->points[3].point.v_y= 0.13261;
result->points[4].format= FINAL_FORMAT;
result->points[4].point.x= -0.5;result->points[4].point.y= 0.0;
result->points[4].point.u_x= -0.5;result->points[4].point.u_y= -0.13261;
result->points[4].point.v_x= -0.44733;result->points[4].point.v_y= -0.2598;
result->points[5].format= FINAL_FORMAT;
result->points[5].point.x= -0.35356;result->points[5].point.y= -0.35356;
result->points[5].point.u_x= -0.2598;result->points[5].point.u_y= -0.44733;
result->points[5].point.v_x= -0.13261;result->points[5].point.v_y= -0.5;
result->points[6].format= FINAL_FORMAT;
result->points[6].point.x= 0.0;result->points[6].point.y= -0.5;
result->points[6].point.u_x= 0.13261;result->points[6].point.u_y= -0.5;
result->points[6].point.v_x= 0.2598;result->points[6].point.v_y= -0.44733;
result->points[7].format= FINAL_FORMAT;
result->points[7].point.x= 0.35356;result->points[7].point.y= -0.35356;
result->points[7].point.u_x= 0.44733;result->points[7].point.u_y= -0.2598;
result->points[7].point.v_x= 0.5;result->points[7].point.v_y= -0.13261;
result->points[7].format= FINAL_FORMAT;
result->points[8].point.x= 0.5;result->points[8].point.y= 0.0;
result->points[8].point.u_x= 0.5;result->points[8].point.u_y= 0.13261;
result->points[8].point.v_x= 0.44733;result->points[8].point.v_y= 0.2598;
result->points[8].format= FINAL_FORMAT;
result->cyclic= true;
/*:411*/
#line 10595 "weaver-interface-metafont.cweb"

}
else if(tmp.flags&FLAG_SEMICIRCULAR){
/*412:*/
#line 10681 "weaver-interface-metafont.cweb"

result->length= 5;
result->number_of_points= 5;
result->points= 
(struct path_points*)temporary_alloc(sizeof(struct path_points)*9);
result->points[0].format= FINAL_FORMAT;
result->points[0].point.x= 0.5;result->points[0].point.y= 0.0;
result->points[0].point.u_x= 0.5;result->points[0].point.u_y= 0.13261;
result->points[0].point.v_x= 0.44733;result->points[0].point.v_y= 0.2598;
result->points[1].format= FINAL_FORMAT;
result->points[1].point.x= 0.35356;result->points[1].point.y= 0.35356;
result->points[1].point.u_x= 0.2598;result->points[1].point.u_y= 0.44733;
result->points[1].point.v_x= 0.13261;result->points[1].point.v_y= 0.5;
result->points[2].format= FINAL_FORMAT;
result->points[2].point.x= 0.0;result->points[2].point.y= 0.5;
result->points[2].point.u_x= -0.13261;result->points[2].point.u_y= 0.5;
result->points[2].point.v_x= -0.2598;result->points[2].point.v_y= 0.44733;
result->points[3].format= FINAL_FORMAT;
result->points[3].point.x= -0.35356;result->points[3].point.y= 0.35356;
result->points[3].point.u_x= -0.44733;result->points[3].point.u_y= 0.2598;
result->points[3].point.v_x= -0.5;result->points[3].point.v_y= 0.13261;
result->points[4].format= FINAL_FORMAT;
result->points[4].point.x= -0.5;result->points[4].point.y= 0.0;
result->points[4].point.u_x= -0.33333;result->points[4].point.u_y= 0.0;
result->points[4].point.v_x= 0.33333;result->points[4].point.v_y= 0.0;
result->cyclic= true;
/*:412*/
#line 10598 "weaver-interface-metafont.cweb"

}
else if(tmp.flags&FLAG_SQUARE){
/*413:*/
#line 10712 "weaver-interface-metafont.cweb"

result->length= 5;
result->number_of_points= 5;
result->points= 
(struct path_points*)temporary_alloc(sizeof(struct path_points)*5);
result->points[0].format= FINAL_FORMAT;
result->points[0].point.x= -0.5;result->points[0].point.y= -0.5;
result->points[0].point.u_x= (-0.5+(1.0/3.0));
result->points[0].point.u_y= -0.5;
result->points[0].point.v_x= (-0.5+(2.0/3.0));
result->points[0].point.v_y= -0.5;
result->points[1].format= FINAL_FORMAT;
result->points[1].point.x= 0.5;result->points[1].point.y= -0.5;
result->points[1].point.u_x= 0.5;
result->points[1].point.u_y= (-0.5+(1.0/3.0));
result->points[1].point.v_x= 0.5;
result->points[1].point.v_y= (-0.5+(2.0/3.0));
result->points[2].format= FINAL_FORMAT;
result->points[2].point.x= 0.5;result->points[2].point.y= 0.5;
result->points[2].point.u_x= (0.5-(1.0/3.0));
result->points[2].point.u_y= 0.5;
result->points[2].point.v_x= (0.5-(2.0/3.0));
result->points[2].point.v_y= 0.5;
result->points[3].format= FINAL_FORMAT;
result->points[3].point.x= -0.5;result->points[3].point.y= 0.5;
result->points[3].point.u_x= -0.5;
result->points[3].point.u_y= (0.5-(1.0/3.0));
result->points[3].point.v_x= -0.5;
result->points[3].point.v_y= (0.5-(2.0/3.0));
result->points[4].format= FINAL_FORMAT;
result->points[4].point.x= -0.5;result->points[4].point.y= -0.5;
result->points[4].point.u_x= (-0.5+(1.0/3.0));
result->points[4].point.u_y= -0.5;
result->points[4].point.v_x= (-0.5+(2.0/3.0));
result->points[4].point.v_y= -0.5;
result->cyclic= true;
/*:413*/
#line 10601 "weaver-interface-metafont.cweb"

}
else{
/*414:*/
#line 10754 "weaver-interface-metafont.cweb"

if(!recursive_copy_points(mf,cx,temporary_alloc,&result,tmp.format,false))
return false;
if(temporary_free!=NULL){
temporary_free(tmp.format->points);
temporary_free(tmp.format);
}
/*:414*/
#line 10604 "weaver-interface-metafont.cweb"

}
/*415:*/
#line 10767 "weaver-interface-metafont.cweb"

{
int i;
for(i= 0;i<result->length;i++){
float x0= result->points[i].point.x,y0= result->points[i].point.y;
result->points[i].point.x= LINEAR_TRANSFORM_X(x0,y0,tmp.gl_matrix);
result->points[i].point.y= LINEAR_TRANSFORM_Y(x0,y0,tmp.gl_matrix);
x0= result->points[i].point.u_x;
y0= result->points[i].point.u_y;
result->points[i].point.u_x= LINEAR_TRANSFORM_X(x0,y0,tmp.gl_matrix);
result->points[i].point.u_y= LINEAR_TRANSFORM_Y(x0,y0,tmp.gl_matrix);
x0= result->points[i].point.v_x;
y0= result->points[i].point.v_y;
result->points[i].point.v_x= LINEAR_TRANSFORM_X(x0,y0,tmp.gl_matrix);
result->points[i].point.v_y= LINEAR_TRANSFORM_Y(x0,y0,tmp.gl_matrix);
}
}
/*:415*/
#line 10606 "weaver-interface-metafont.cweb"

return true;
}
/*:409*/
#line 9431 "weaver-interface-metafont.cweb"

{
/*371:*/
#line 9699 "weaver-interface-metafont.cweb"

struct pair_variable v;
if(!eval_pair_primary(mf,cx,begin,end,&v))
return false;
result->length= 1;
result->number_of_points= 1;
result->cyclic= false;
result->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points));
result->points[0].format= FINAL_FORMAT;
result->points[0].point.x= v.x;
result->points[0].point.y= v.y;
result->points[0].point.u_x= v.x;
result->points[0].point.u_y= v.y;
result->points[0].point.v_x= v.x;
result->points[0].point.v_y= v.y;
return true;
/*:371*/
#line 9433 "weaver-interface-metafont.cweb"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PATH);
return false;
}
/*:364*//*367:*/
#line 9470 "weaver-interface-metafont.cweb"

bool reverse_path(struct metafont*mf,struct context*cx,
struct path_variable*dst,
struct path_variable*origin){
int i;
dst->cyclic= origin->cyclic;
dst->length= origin->number_of_points;
dst->number_of_points= origin->number_of_points;
dst->points= (struct path_points*)
temporary_alloc(sizeof(struct path_points)*dst->length);
if(dst->points==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,0);
return false;
}
for(i= 0;i<origin->length-1;i++){
dst->points[i].format= FINAL_FORMAT;
dst->points[i].point.x= origin->points[origin->length-1-i].point.x;
dst->points[i].point.y= origin->points[origin->length-1-i].point.y;
dst->points[i].point.u_x= origin->points[origin->length-2-i].point.v_x;
dst->points[i].point.u_y= origin->points[origin->length-2-i].point.v_y;
dst->points[i].point.v_x= origin->points[origin->length-2-i].point.u_x;
dst->points[i].point.v_y= origin->points[origin->length-2-i].point.u_y;
}
dst->points[i].format= FINAL_FORMAT;
dst->points[i].point.x= origin->points[0].point.x;
dst->points[i].point.y= origin->points[0].point.y;
dst->points[i].point.u_x= origin->points[0].point.x;
dst->points[i].point.u_y= origin->points[0].point.y;
dst->points[i].point.v_x= origin->points[0].point.x;
dst->points[i].point.v_y= origin->points[0].point.y;
return true;
}
/*:367*//*376:*/
#line 9787 "weaver-interface-metafont.cweb"

struct path_points*get_point(struct path_variable*v,int n){
if(v->length==v->number_of_points){
struct path_points*ret= (struct path_points*)&(v->points[n]);
while(ret->format==SUBPATH_FORMAT)
ret= &(((struct path_variable*)(ret->subpath))->points[0]);
return ret;
}
else{
int count= 0;
return _get_point(v,n,&count);
}
}
/*:376*//*378:*/
#line 9815 "weaver-interface-metafont.cweb"

struct path_points*_get_point(struct path_variable*v,int n,int*count){
int i;
for(i= 0;i<v->length;i++){
if(v->points[i].format!=SUBPATH_FORMAT){
if(*count==n&&!isnan(v->points[i].point.x))
return((struct path_points*)&(v->points[i]));
else if(!isnan(v->points[i].point.x))
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
/*:378*//*382:*/
#line 9956 "weaver-interface-metafont.cweb"

bool assign_pen_variable(struct metafont*mf,struct context*cx,
struct pen_variable*target,
struct pen_variable*source){
void*(*alloc)(size_t);
void(*disalloc)(void*);
bool permanent= target->permanent;
struct variable*next= target->next;
if(permanent){
disalloc= permanent_free;
alloc= permanent_alloc;
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
target->next= next;
target->permanent= permanent;
if(!(source->flags&(FLAG_CIRCULAR|FLAG_SQUARE|FLAG_NULL)))
if(!recursive_copy_points(mf,NULL,alloc,&(target->format),
source->format,true))
return false;
target->gl_vbo= 0;
target->indices= 0;
target->referenced= NULL;


if(target==cx->currentpen)
triangulate_pen(mf,cx,target,target->gl_matrix);
return true;
}
/*:382*//*384:*/
#line 10015 "weaver-interface-metafont.cweb"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result){
if(begin->type!=TYPE_SYMBOLIC&&begin->type!=TYPE_NULLPEN&&
begin->type!=TYPE_OPEN_PARENTHESIS&&
begin->type!=TYPE_PENCIRCLE&&begin->type!=TYPE_PENSEMICIRCLE&&
begin->type!=TYPE_MAKEPEN){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PEN);
return false;
}
return eval_pen_secondary(mf,cx,begin,end,result);
}
/*:384*//*386:*/
#line 10071 "weaver-interface-metafont.cweb"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*pen){
DECLARE_NESTING_CONTROL();
struct generic_token*p,*prev= NULL,*last_transformer= NULL,
*before_last_transformer= begin;
p= begin;
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
if(p!=end)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(last_transformer==NULL)
return eval_pen_primary(mf,cx,begin,end,pen);
else{
if(!eval_pen_secondary(mf,cx,begin,before_last_transformer,pen))
return false;
if(last_transformer->type==TYPE_ROTATED){
/*387:*/
#line 10138 "weaver-interface-metafont.cweb"

struct numeric_variable r;
double rotation;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&r))
return false;
rotation= 0.017453292519943295*r.value;
TRANSFORM_ROTATE(pen->gl_matrix,rotation);
return true;
/*:387*/
#line 10102 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_SCALED){
/*388:*/
#line 10151 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&a.value> 1.0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:388*/
#line 10105 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*389:*/
#line 10168 "weaver-interface-metafont.cweb"

struct pair_variable pair;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&pair))
return false;
TRANSFORM_SHIFT(pen->gl_matrix,pair.x,pair.y);
return true;
/*:389*/
#line 10108 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_SLANTED){
/*390:*/
#line 10178 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SLANT(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&!(pen->flags&FLAG_STRAIGHT)&&
!(pen->flags&FLAG_CIRCULAR)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:390*/
#line 10111 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_XSCALED){
/*391:*/
#line 10197 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE_X(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&a.value> 1.0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:391*/
#line 10114 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_YSCALED){
/*392:*/
#line 10214 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE_Y(pen->gl_matrix,a.value);

if(pen->gl_vbo!=0&&a.value> 1.0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:392*/
#line 10117 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*393:*/
#line 10237 "weaver-interface-metafont.cweb"

struct pair_variable pair;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&pair))
return false;
TRANSFORM_SCALE_Z(pen->gl_matrix,pair.x,pair.y);

if(pen->gl_vbo!=0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:393*/
#line 10120 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*394:*/
#line 10254 "weaver-interface-metafont.cweb"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,last_transformer->next,end,&t))
return false;
MATRIX_MULTIPLICATION(pen->gl_matrix,t.value);

if(pen->gl_vbo!=0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:394*/
#line 10123 "weaver-interface-metafont.cweb"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PEN);
return false;
}
}
/*:386*//*398:*/
#line 10307 "weaver-interface-metafont.cweb"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result){
if(begin==end){
if(begin->type==TYPE_SYMBOLIC){
/*399:*/
#line 10348 "weaver-interface-metafont.cweb"

struct symbolic_token*v= (struct symbolic_token*)begin;
struct pen_variable*content= v->var,*to_copy= v->var;
if(content==NULL){
if(!strcmp(v->value,"currentpen"))
content= cx->currentpen;
else{
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(v->line),v);
return false;
}
}
if(content->type!=TYPE_T_PEN){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),v,
((struct variable*)(v->var))->type,
TYPE_T_PEN);
return false;
}
if(content->format==NULL&&content->flags==false){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(v->line),v,
TYPE_T_PEN);
return false;
}
if(content->referenced!=NULL)
to_copy= content->referenced;
memcpy(result,to_copy,sizeof(struct pen_variable));
if(to_copy->format!=NULL)
if(!recursive_copy_points(mf,cx,temporary_alloc,&(result->format),
to_copy->format,true))
return false;
if(to_copy!=content)
MATRIX_MULTIPLICATION(result->gl_matrix,content->gl_matrix);
return true;
/*:399*/
#line 10314 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_NULLPEN){
/*400:*/
#line 10386 "weaver-interface-metafont.cweb"

result->format= NULL;
result->flags= FLAG_NULL;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:400*/
#line 10317 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_PENCIRCLE){
/*401:*/
#line 10400 "weaver-interface-metafont.cweb"

result->format= NULL;
result->flags= FLAG_CONVEX|FLAG_CIRCULAR;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:401*/
#line 10320 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_PENSEMICIRCLE){
/*402:*/
#line 10412 "weaver-interface-metafont.cweb"

result->format= NULL;
result->flags= FLAG_CONVEX|FLAG_SEMICIRCULAR;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:402*/
#line 10323 "weaver-interface-metafont.cweb"

}

}
else{
if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*403:*/
#line 10426 "weaver-interface-metafont.cweb"

struct generic_token*t= begin->next;
DECLARE_NESTING_CONTROL();
if(begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'(');
return false;
}
while(t!=NULL&&t->next!=end){
COUNT_NESTING(t);
t= t->next;
}
RAISE_ERROR_AND_EXIT_IF_WRONG_NESTING(mf,cx,OPTIONAL(begin->line));
return eval_pen_expression(mf,cx,begin->next,t,result);
/*:403*/
#line 10330 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_MAKEPEN){
/*404:*/
#line 10446 "weaver-interface-metafont.cweb"

struct generic_token*p= begin->next;
result->format= 
(struct path_variable*)temporary_alloc(sizeof(struct path_variable));
if(result->format==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}
if(!eval_path_primary(mf,cx,p,end,result->format))
return false;
if(!(result->format->cyclic)){
RAISE_ERROR_NONCYCLICAL_PEN(mf,cx,OPTIONAL(begin->line));
return false;
}
result->flags= read_flags(result->format);
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:404*/
#line 10333 "weaver-interface-metafont.cweb"

}
}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PEN);
return false;
}
/*:398*//*406:*/
#line 10482 "weaver-interface-metafont.cweb"

int read_flags(struct path_variable*path){
int i,positive_cross_product= -1;
int flag= FLAG_CONVEX|FLAG_STRAIGHT;
for(i= 0;i<path->number_of_points-1;i++){
struct path_points*current,*next;
current= get_point(path,i);
next= get_point(path,i+1);
if(flag&FLAG_STRAIGHT){



double area= current->point.x*(current->point.u_y-next->point.y)+
current->point.u_x*(next->point.y-current->point.y)+
next->point.x*(current->point.y-current->point.u_y);
if(area> 0.01||area<-0.01)
flag-= FLAG_STRAIGHT;
area= current->point.x*(current->point.v_y-next->point.y)+
current->point.v_x*(next->point.y-current->point.y)+
next->point.x*(current->point.y-current->point.v_y);
if((flag&FLAG_STRAIGHT)&&(area> 0.01||area<-0.01))
flag-= FLAG_STRAIGHT;
}
if(flag&FLAG_CONVEX){



int j;
double d1_x,d1_y,d2_x,d2_y,z_cross_product;
double p1_x,p1_y,p2_x,p2_y,p3_x,p3_y;
for(j= 0;j<3;j++){
switch(j){
case 0:
p1_x= current->point.x;p1_y= current->point.y;
p2_x= current->point.u_x;p2_y= current->point.u_y;
p3_x= current->point.v_x;p3_y= current->point.v_y;
break;
case 1:
p1_x= p2_x;p1_y= p2_y;
p2_x= p3_x;p2_y= p3_y;
p3_x= next->point.x;p3_y= next->point.y;
break;
default:
p1_x= p2_x;p1_y= p2_y;
p2_x= p3_x;p2_y= p3_y;
p3_x= next->point.u_x;p3_y= next->point.u_y;
break;
}
d1_x= p2_x-p1_x;
d1_y= p2_y-p1_y;
d2_x= p3_x-p2_x;
d2_y= p3_y-p2_y;
z_cross_product= d1_x*d2_y-d1_y*d2_x;
if(z_cross_product> 0.01||z_cross_product<-0.01){
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
/*:406*//*423:*/
#line 10932 "weaver-interface-metafont.cweb"

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
/*:423*//*427:*/
#line 11007 "weaver-interface-metafont.cweb"

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
glBindTexture(GL_TEXTURE_2D,0);
return false;
}
glBindTexture(GL_TEXTURE_2D,0);
return true;
}
/*:427*//*429:*/
#line 11042 "weaver-interface-metafont.cweb"

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
/*:429*//*431:*/
#line 11100 "weaver-interface-metafont.cweb"

bool assign_picture_variable(struct metafont*mf,struct context*cx,
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
if(!get_new_framebuffer(&temporary_framebuffer,&(target->texture),
source->width,source->height)){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,NULL,0);
return false;
}
render_picture(source,model_view_matrix,source->width,source->height,true);

glBindTexture(GL_TEXTURE_2D,0);
glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
if(target==cx->currentpicture){

/*597:*/
#line 16727 "weaver-interface-metafont.cweb"

{
if(cx->currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&(cx->currentpicture_fb));
}
cx->currentpicture_fb= 0;
}
/*:597*/
#line 11124 "weaver-interface-metafont.cweb"

}
return true;
}
/*:431*//*433:*/
#line 11169 "weaver-interface-metafont.cweb"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin&&
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
/*438:*/
#line 11386 "weaver-interface-metafont.cweb"

{
float matrix[9];
bool modified= false;
INITIALIZE_IDENTITY_MATRIX(matrix);
if(last_operator==NULL){
if(!eval_picture_secondary(mf,cx,begin,end,sec,matrix,&modified))
return false;
}
else if(!eval_picture_secondary(mf,cx,last_operator->next,
end,sec,matrix,&modified))
return false;
if(modified){
if(!apply_image_transformation(mf,result,sec,matrix)){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,cx,OPTIONAL(begin->line));
return false;
}
if(sec->texture!=0)
glDeleteTextures(1,&(sec->texture));
}
else{
result->width= sec->width;
result->height= sec->height;
result->texture= sec->texture;
}
}
/*:438*/
#line 11191 "weaver-interface-metafont.cweb"

return true;
}
else{
struct picture_variable a,b;
struct picture_variable*sec= &b;
if(last_operator==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
if(!eval_picture_expression(mf,cx,begin,before_last_operator,&a))
return false;
/*438:*/
#line 11386 "weaver-interface-metafont.cweb"

{
float matrix[9];
bool modified= false;
INITIALIZE_IDENTITY_MATRIX(matrix);
if(last_operator==NULL){
if(!eval_picture_secondary(mf,cx,begin,end,sec,matrix,&modified))
return false;
}
else if(!eval_picture_secondary(mf,cx,last_operator->next,
end,sec,matrix,&modified))
return false;
if(modified){
if(!apply_image_transformation(mf,result,sec,matrix)){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,cx,OPTIONAL(begin->line));
return false;
}
if(sec->texture!=0)
glDeleteTextures(1,&(sec->texture));
}
else{
result->width= sec->width;
result->height= sec->height;
result->texture= sec->texture;
}
}
/*:438*/
#line 11204 "weaver-interface-metafont.cweb"

/*437:*/
#line 11293 "weaver-interface-metafont.cweb"


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
/*:437*/
#line 11205 "weaver-interface-metafont.cweb"

if(a.texture!=0)
glDeleteTextures(1,&(a.texture));
if(b.texture!=0)
glDeleteTextures(1,&(b.texture));
return true;
}
}
/*:433*//*440:*/
#line 11430 "weaver-interface-metafont.cweb"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result,
float*matrix,bool*modified){
DECLARE_NESTING_CONTROL();
struct generic_token*p,*prev= NULL,*last_transformer= NULL,
*before_last_transformer= begin;
p= begin;
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
if(p!=end)
p= (struct generic_token*)p->next;
else
p= NULL;
}while(p!=NULL);
if(last_transformer==NULL)
return eval_picture_primary(mf,cx,begin,end,result);
else{
if(!eval_picture_secondary(mf,cx,begin,before_last_transformer,result,
matrix,modified))
return false;
if(last_transformer->type==TYPE_ROTATED){
/*442:*/
#line 11510 "weaver-interface-metafont.cweb"

struct numeric_variable r;
double rotation;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&r))
return false;
rotation= 0.017453292519943295*r.value;
TRANSFORM_ROTATE(matrix,rotation);
*modified= true;
return true;
/*:442*/
#line 11463 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_SCALED){
/*441:*/
#line 11499 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE(matrix,a.value);
*modified= true;
return true;
/*:441*/
#line 11466 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*443:*/
#line 11526 "weaver-interface-metafont.cweb"

struct pair_variable pair;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&pair))
return false;
pair.x= 2.0*(pair.x/result->width);
pair.y= 2.0*(pair.y/result->height);
TRANSFORM_SHIFT(matrix,pair.x,pair.y);
*modified= true;
return true;
/*:443*/
#line 11469 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_SLANTED){
/*444:*/
#line 11539 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SLANT(matrix,a.value);
*modified= true;
return true;
/*:444*/
#line 11472 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_XSCALED){
/*445:*/
#line 11550 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE_X(matrix,a.value);
*modified= true;
return true;
/*:445*/
#line 11475 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_YSCALED){
/*446:*/
#line 11561 "weaver-interface-metafont.cweb"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE_Y(matrix,a.value);
*modified= true;
return true;
/*:446*/
#line 11478 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*447:*/
#line 11573 "weaver-interface-metafont.cweb"

struct pair_variable pair;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&pair))
return false;
TRANSFORM_SCALE_Z(matrix,pair.x,pair.y);
*modified= true;
return true;
/*:447*/
#line 11481 "weaver-interface-metafont.cweb"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*448:*/
#line 11585 "weaver-interface-metafont.cweb"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,last_transformer->next,end,&t))
return false;
MATRIX_MULTIPLICATION(matrix,t.value);
*modified= true;
return true;
/*:448*/
#line 11484 "weaver-interface-metafont.cweb"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
}
/*:440*//*450:*/
#line 11634 "weaver-interface-metafont.cweb"

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
if(!get_new_framebuffer(&temporary_framebuffer,&(dst->texture),dst->width,
dst->height)){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,NULL,0);
return false;
}

render_picture(origin,matrix,dst->width,dst->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:450*//*454:*/
#line 11737 "weaver-interface-metafont.cweb"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result){
if(begin==end){
if(begin->type==TYPE_SYMBOLIC){
/*455:*/
#line 11775 "weaver-interface-metafont.cweb"

GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
float identity_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
struct symbolic_token*v= (struct symbolic_token*)begin;
struct picture_variable*content= v->var;
if(!strcmp(v->value,"currentpicture"))
content= cx->currentpicture;
if(content==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(v->line),v);
return false;
}
if(content->type!=TYPE_T_PICTURE){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),v,
((struct variable*)(v->var))->type,
TYPE_T_PICTURE);
return false;
}
if(content->width==-1&&content->height==-1){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(v->line),v,
TYPE_T_PICTURE);
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
/*:455*/
#line 11744 "weaver-interface-metafont.cweb"

}
}
else{
if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*456:*/
#line 11819 "weaver-interface-metafont.cweb"

struct generic_token*t= begin->next;
if(begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'(');
return false;
}
while(t!=NULL&&t->next!=end)
t= t->next;
return eval_picture_expression(mf,cx,begin->next,t,result);
/*:456*/
#line 11750 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_NULLPICTURE){
/*457:*/
#line 11836 "weaver-interface-metafont.cweb"

struct generic_token*begin_pair_expression,*end_pair_expression;
struct pair_variable p;
unsigned char*data;
begin_pair_expression= begin->next;
end_pair_expression= end;
if(begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PAIR);
return false;
}
if(!eval_pair_primary(mf,cx,begin_pair_expression,end_pair_expression,&p))
return false;
result->width= p.x;
result->height= p.y;
data= temporary_alloc(p.x*p.y*4);
if(data==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
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
/*:457*/
#line 11753 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_SUM){
/*458:*/
#line 11881 "weaver-interface-metafont.cweb"

struct generic_token*p= begin->next;
if(begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
return eval_picture_primary(mf,cx,p,end,result);
/*:458*/
#line 11756 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_SUBTRACT){
/*459:*/
#line 11898 "weaver-interface-metafont.cweb"

struct picture_variable p;
GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
float identity_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
if(begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
if(!eval_picture_primary(mf,cx,begin->next,end,&p))
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
/*:459*/
#line 11759 "weaver-interface-metafont.cweb"

}
else if(begin->type==TYPE_SUBPICTURE){
/*460:*/
#line 11946 "weaver-interface-metafont.cweb"

struct pair_variable pair_offset,subpicture_size;
struct picture_variable original_picture;
/*461:*/
#line 11961 "weaver-interface-metafont.cweb"

{
DECLARE_NESTING_CONTROL();
struct generic_token*begin_pair1= NULL,*end_pair1= NULL,
*begin_pair2= NULL,*end_pair2= NULL,
*begin_pic= NULL,*end_pic= NULL,
*p= begin->next,
*last_token= begin;
int state= 0;
begin_pair1= p;
while(p!=end&&p!=NULL){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p->type==TYPE_AND){
if(state!=0||last_token->type==TYPE_SUBPICTURE){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(p->line),p);
return false;
}
end_pair1= last_token;
state++;
begin_pair2= p->next;
}
else if(IS_NOT_NESTED()&&p->type==TYPE_OF){
if(state!=1||last_token->type==TYPE_AND){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(p->line),p);
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
if(state<2){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PAIR);
}
else{
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
}
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
/*:461*/
#line 11949 "weaver-interface-metafont.cweb"

/*462:*/
#line 12020 "weaver-interface-metafont.cweb"

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
/*:462*/
#line 11950 "weaver-interface-metafont.cweb"

return false;
/*:460*/
#line 11762 "weaver-interface-metafont.cweb"

}
}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
/*:454*//*472:*/
#line 12286 "weaver-interface-metafont.cweb"

bool eval_boolean_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin&&
(p->type==TYPE_LT||p->type==TYPE_LEQ||
p->type==TYPE_GT||p->type==TYPE_GEQ||
p->type==TYPE_NEQ||p->type==TYPE_EQUAL)){
last_operator= p;
before_last_operator= prev;
}
prev= p;
p= p->next;
}
if(last_operator==NULL)
return eval_boolean_tertiary(mf,cx,begin,end,result);
else{
int type;
if(before_last_operator==NULL||last_operator==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_BOOLEAN);
return false;
}
type= get_tertiary_expression_type(mf,cx,last_operator->next,end);
switch(type){
case TYPE_T_NUMERIC:
{
struct numeric_variable a,b;
if(!eval_numeric_expression(mf,cx,begin,before_last_operator,&a))
return false;
if(!eval_numeric_expression(mf,cx,last_operator->next,end,&b))
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
case TYPE_EQUAL:
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
if(!eval_pair_expression(mf,cx,begin,before_last_operator,&a))
return false;
if(!eval_pair_expression(mf,cx,last_operator->next,end,&b))
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
case TYPE_EQUAL:
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
if(!eval_transform_expression(mf,cx,begin,before_last_operator,&a))
return false;
if(!eval_transform_expression(mf,cx,last_operator->next,end,&b))
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
case TYPE_EQUAL:
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
if(!eval_boolean_expression(mf,cx,begin,before_last_operator,&a))
return false;
if(!eval_boolean_tertiary(mf,cx,last_operator->next,end,&b))
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
case TYPE_EQUAL:
result->value= (a.value==b.value);
return true;
case TYPE_NEQ:
result->value= (a.value!=b.value);
return true;
}
break;
}
default:
RAISE_ERROR_INVALID_COMPARISON(mf,cx,OPTIONAL(begin->line),
last_operator,type);
return false;
}
return true;
}
}
/*:472*//*476:*/
#line 12515 "weaver-interface-metafont.cweb"

bool eval_boolean_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin&&p->type==TYPE_OR){
last_operator= p;
before_last_operator= prev;
}
prev= p;
p= p->next;
}
if(last_operator==NULL)
return eval_boolean_secondary(mf,cx,begin,end,result);
else{
if(last_operator==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_BOOLEAN);
return false;
}
struct boolean_variable a,b;
a.value= b.value= -1;
if(!eval_boolean_secondary(mf,cx,begin,before_last_operator,&a))
return false;
if(!eval_boolean_tertiary(mf,cx,last_operator->next,end,&b))
return false;
result->value= (a.value||b.value);
return true;
}
}
/*:476*//*478:*/
#line 12581 "weaver-interface-metafont.cweb"

bool eval_boolean_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result){
DECLARE_NESTING_CONTROL();
struct generic_token*p= begin,*prev= NULL;
struct generic_token*last_operator= NULL,*before_last_operator= NULL;
while(p!=end){
COUNT_NESTING(p);
if(IS_NOT_NESTED()&&p!=begin&&p->type==TYPE_AND){
last_operator= p;
before_last_operator= prev;
}
prev= p;
p= p->next;
}
if(last_operator==NULL)
return eval_boolean_primary(mf,cx,begin,end,result);
else{
if(last_operator==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_BOOLEAN);
return false;
}
struct boolean_variable a,b;
a.value= b.value= -1;
if(!eval_boolean_secondary(mf,cx,begin,before_last_operator,&a))
return false;
if(!eval_boolean_primary(mf,cx,last_operator->next,end,&b))
return false;
result->value= (a.value&&b.value);
return true;
}
}
/*:478*//*482:*/
#line 12668 "weaver-interface-metafont.cweb"

bool eval_boolean_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result){
struct symbolic_token*symbol;
struct path_variable path;
struct numeric_variable num;
struct boolean_variable b;
switch(begin->type){
case TYPE_SYMBOLIC:
symbol= ((struct symbolic_token*)begin);
struct boolean_variable*var= symbol->var;
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(begin->line),
symbol);
return false;
}
if(var->type!=TYPE_T_BOOLEAN){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(begin->line),
symbol,var->type,
TYPE_T_BOOLEAN);
return false;
}
if(var->value==-1){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
symbol,TYPE_T_BOOLEAN);
return false;
}
result->value= var->value;
return true;
break;
case TYPE_TRUE:
if(end!=begin){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_BOOLEAN);
return false;
}
result->value= 1;
return true;
break;
case TYPE_FALSE:
if(end!=begin){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_BOOLEAN);
return false;
}
result->value= 0;
return true;
break;
case TYPE_CYCLE:
if(!eval_path_primary(mf,cx,begin->next,end,&path))
return false;
result->value= path.cyclic;
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&path,false);
return true;
break;
case TYPE_ODD:
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
result->value= (((int)round(num.value))%2);
return true;
break;
case TYPE_NOT:
if(!eval_boolean_primary(mf,cx,begin->next,end,&b))
return false;
result->value= !(b.value);
return true;
break;
case TYPE_OPEN_PARENTHESIS:
if(end->type!=TYPE_CLOSE_PARENTHESIS){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_BOOLEAN);
return false;
}
struct generic_token*last_token= begin;
while(last_token->next!=end)
last_token= last_token->next;
return eval_boolean_expression(mf,cx,begin->next,last_token,
result);
break;
default:
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_BOOLEAN);
return false;
}
}
/*:482*//*484:*/
#line 12848 "weaver-interface-metafont.cweb"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr){
if(begin_expr==end_expr){
if(begin_expr->type==TYPE_SYMBOLIC){
struct variable*var= (struct variable*)
((struct symbolic_token*)begin_expr)->var;
if(var==NULL){
if(!strcmp(((struct symbolic_token*)begin_expr)->value,"w")||
!strcmp(((struct symbolic_token*)begin_expr)->value,"h")||
!strcmp(((struct symbolic_token*)begin_expr)->value,"d"))
return TYPE_T_NUMERIC;
if(!strcmp(((struct symbolic_token*)begin_expr)->value,
"currentpen"))
return TYPE_T_PEN;
if(!strcmp(((struct symbolic_token*)begin_expr)->value,
"currentpicture"))
return TYPE_T_PICTURE;
return-1;
}
else
return var->type;
}
if(begin_expr->type==TYPE_TRUE||begin_expr->type==TYPE_FALSE||
begin_expr->type==TYPE_NOT)
return TYPE_T_BOOLEAN;
if(begin_expr->type==TYPE_NUMERIC||
begin_expr->type==TYPE_NORMALDEVIATE)
return TYPE_T_NUMERIC;
if(begin_expr->type==TYPE_NULLPEN||
begin_expr->type==TYPE_PENCIRCLE||
begin_expr->type==TYPE_PENSEMICIRCLE)
return TYPE_T_PEN;
else
return-1;
}
else{
if(begin_expr->type==TYPE_CYCLE||begin_expr->type==TYPE_ODD||
begin_expr->type==TYPE_NOT)
return TYPE_T_BOOLEAN;

if(begin_expr->type==TYPE_POINT||
begin_expr->type==TYPE_PRECONTROL||
begin_expr->type==TYPE_POSTCONTROL||
begin_expr->type==TYPE_BOT||begin_expr->type==TYPE_TOP||
begin_expr->type==TYPE_LFT||begin_expr->type==TYPE_RT)
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

if(begin_expr->type==TYPE_SUBPATH||
begin_expr->type==TYPE_MAKEPATH||
begin_expr->type==TYPE_REVERSE)
return TYPE_T_PATH;
if(begin_expr->type==TYPE_MAKEPEN)
return TYPE_T_PEN;
if(begin_expr->type==TYPE_NULLPICTURE||
begin_expr->type==TYPE_SUBPICTURE)
return TYPE_T_PICTURE;


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
/*:484*//*485:*/
#line 12988 "weaver-interface-metafont.cweb"

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
/*:485*//*486:*/
#line 13069 "weaver-interface-metafont.cweb"

int get_tertiary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr){
DECLARE_NESTING_CONTROL();
struct generic_token*t= begin_expr,*prev= NULL,*last_op= NULL;
if(begin_expr==end_expr)
return get_primary_expression_type(mf,cx,begin_expr,end_expr);
while(t!=end_expr&&t!=NULL){
if(IS_NOT_NESTED()&&t->type==TYPE_OPEN_BRACES)
return TYPE_T_PATH;
COUNT_NESTING(t);
if(IS_NOT_NESTED()){
if(t->type==TYPE_OR||t->type==TYPE_LT||
t->type==TYPE_GT||t->type==TYPE_GEQ||
t->type==TYPE_LEQ||t->type==TYPE_EQUAL||
t->type==TYPE_NEQ)
return TYPE_T_BOOLEAN;
if(t->type==TYPE_AMPERSAND||t->type==TYPE_JOIN||
t->type==TYPE_STRAIGHT_JOIN)
return TYPE_T_PATH;
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
/*:486*//*509:*/
#line 13768 "weaver-interface-metafont.cweb"

void pencircular_extremity_points(struct context*cx,
float*matrix,bool fullcircle){
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
if(fullcircle)
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
y1= matrix[3-i*2]*sqrt(0.25-x1*x1)+
(matrix[index[3-i*2]]*x1/sqrt(0.25-x1*x1));
while(x0!=x1){
float x2= (x0+x1)/2;
float y2= matrix[index[3-i*2]]*sqrt(0.25-x2*x2)+
(matrix[index[3-i*2]]*x2/sqrt(0.25-x2*x2));
if(y2==0.0||x0==x2||x1==x2)
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
if(fullcircle)
CHECK_PEN_EXTREMITIES(x0,-sqrt(0.25-x0*x0),matrix);
CHECK_PEN_EXTREMITIES(-x0,sqrt(0.25-x0*x0),matrix);
if(fullcircle)
CHECK_PEN_EXTREMITIES(-x0,-sqrt(0.25-x0*x0),matrix);
}
else{
CHECK_PEN_EXTREMITIES(sqrt(0.25-x0*x0),x0,matrix);
CHECK_PEN_EXTREMITIES(-sqrt(0.25-x0*x0),x0,matrix);
if(fullcircle){
CHECK_PEN_EXTREMITIES(sqrt(0.25-x0*x0),-x0,matrix);
CHECK_PEN_EXTREMITIES(-sqrt(0.25-x0*x0),-x0,matrix);
}
}
}
}
UPDATE_PEN_EXTREMITIES();
}
/*:509*//*511:*/
#line 13881 "weaver-interface-metafont.cweb"

void path_extremity_points(struct context*cx,
struct path_variable*p,float*matrix){
int i,j,length= p->length;
DECLARE_PEN_EXTREMITIES();
for(i= 0;i<length;i++){
float x0,y0,u_x,u_y,v_x,v_y,x1,y1;
CHECK_PEN_EXTREMITIES(p->points[i].point.x,p->points[i].point.y,
matrix);
x0= LINEAR_TRANSFORM_X(p->points[i].point.x,p->points[i].point.y,
matrix);
y0= LINEAR_TRANSFORM_Y(p->points[i].point.x,p->points[i].point.y,
matrix);
u_x= LINEAR_TRANSFORM_X(p->points[i].point.u_x,p->points[i].point.u_y,
matrix);
u_y= LINEAR_TRANSFORM_Y(p->points[i].point.u_x,p->points[i].point.u_y,
matrix);
v_x= LINEAR_TRANSFORM_X(p->points[i].point.v_x,p->points[i].point.v_y,
matrix);
v_y= LINEAR_TRANSFORM_Y(p->points[i].point.v_x,p->points[i].point.v_y,
matrix);
x1= LINEAR_TRANSFORM_X(p->points[(i+1)%length].point.x,
p->points[i].point.y,matrix);
y1= LINEAR_TRANSFORM_Y(p->points[(i+1)%length].point.y,
p->points[i].point.y,matrix);

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
/*:511*//*514:*/
#line 13997 "weaver-interface-metafont.cweb"

bool is_pen_counterclockwise(struct pen_variable*pen){
int i,index= 0;
int size= pen->format->length;
float smallest_y= INFINITY,biggest_x= -INFINITY;
if(pen->flags&FLAG_ORIENTATION)
return(pen->flags&FLAG_COUNTERCLOCKWISE);
if(pen->format==NULL||size<=0)
return true;
for(i= 0;i<size;i++){
if(pen->format->points[i].point.y<smallest_y||
(pen->format->points[i].point.y==smallest_y&&
pen->format->points[i].point.y> biggest_x)){
smallest_y= pen->format->points[i].point.y;
biggest_x= pen->format->points[i].point.x;
index= i;
}
}
{
int n= (index-1)%size,p= (index+1)%size;
if(n<0)
n+= size;
if(p<0)
p+= size;
while(pen->format->points[index].point.x==
pen->format->points[n].point.x&&
pen->format->points[index].point.y==
pen->format->points[n].point.y)
n= (n+1)%size;
while(pen->format->points[index].point.x==
pen->format->points[p].point.x&&
pen->format->points[index].point.y==
pen->format->points[p].point.y)
p= (p-1)%size;
float ap_x= pen->format->points[p].point.x-
pen->format->points[index].point.x;
float ap_y= pen->format->points[p].point.y-
pen->format->points[index].point.y;
float an_x= pen->format->points[n].point.x-
pen->format->points[index].point.x;
float an_y= pen->format->points[n].point.y-
pen->format->points[index].point.y;
float prod= ap_x*an_x+ap_y*an_y;
pen->flags+= FLAG_ORIENTATION;
pen->flags+= FLAG_COUNTERCLOCKWISE*(prod> 0);
return(prod> 0);
}
}
/*:514*//*516:*/
#line 14056 "weaver-interface-metafont.cweb"

bool triangulate_pen(struct metafont*mf,struct context*cx,
struct pen_variable*pen,float*transform_matrix){
/*517:*/
#line 14075 "weaver-interface-metafont.cweb"

if((pen->flags&FLAG_NULL)){
pen->indices= 0;
DECLARE_PEN_EXTREMITIES();
CHECK_PEN_EXTREMITIES(0,0,transform_matrix);
UPDATE_PEN_EXTREMITIES();
return true;
}
/*:517*/
#line 14059 "weaver-interface-metafont.cweb"

/*521:*/
#line 14119 "weaver-interface-metafont.cweb"

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
/*:521*/
#line 14060 "weaver-interface-metafont.cweb"

/*522:*/
#line 14145 "weaver-interface-metafont.cweb"

if((pen->flags&FLAG_STRAIGHT)&&(pen->flags&FLAG_CONVEX)){
int i,index,increment;
DECLARE_PEN_EXTREMITIES();
GLsizei size= sizeof(float)*2*pen->format->length;
float*data= (float*)temporary_alloc(size);
if(data==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
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
data[2*i]= pen->format->points[index].point.x;
data[2*i+1]= pen->format->points[index].point.y;
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
/*:522*/
#line 14061 "weaver-interface-metafont.cweb"

/*523:*/
#line 14229 "weaver-interface-metafont.cweb"

if((pen->flags&FLAG_CIRCULAR)||(pen->flags&FLAG_SEMICIRCULAR)){
float radius;
GLsizei size;

pencircular_extremity_points(cx,transform_matrix,
(pen->flags&FLAG_CIRCULAR));

{
float side1,side2;
side1= fabs(cx->pen_rt-cx->pen_lft);
side2= fabs(cx->pen_top-cx->pen_bot);
radius= ((side1>=side2)?(side1):(side2))/2.0;
}

if(pen->gl_vbo!=0){
if(radius> pen->triang_resolution)
glDeleteBuffers(1,&(pen->gl_vbo));
else
return true;
}
pen->triang_resolution= radius;
if(pen->flags&FLAG_CIRCULAR)
size= sizeof(float)*2*(((int)(2*M_PI*radius))+4);
else
size= sizeof(float)*2*(((int)(M_PI*radius))+4);
float*data= (float*)temporary_alloc(size);
if(data==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return false;
}
{
size_t i;
float angle= 0.0;
data[0]= 0.0;
data[1]= 0.0;
for(i= 2;i<(size/sizeof(float));i++){
data[i]= 0.5*cos(angle);
i++;
data[i]= 0.5*sin(angle);
angle+= 1/radius;
if((pen->flags&FLAG_SEMICIRCULAR)&&angle> M_PI)
angle= M_PI;
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
/*:523*/
#line 14062 "weaver-interface-metafont.cweb"

/*524:*/
#line 14330 "weaver-interface-metafont.cweb"

if((pen->flags&FLAG_CONVEX)){
bool counterclockwise= is_pen_counterclockwise(pen);
int i,number_of_vertices= 1;

path_extremity_points(cx,pen->format,transform_matrix);
for(i= 0;i<pen->format->length-1;i++){
int distance= 0;
float x0,y0,u_x,u_y,v_x,v_y,x1,y1;
float dx,dy;
x0= LINEAR_TRANSFORM_X(pen->format->points[i].point.x,
pen->format->points[i].point.y,transform_matrix);
y0= LINEAR_TRANSFORM_Y(pen->format->points[i].point.x,
pen->format->points[i].point.y,transform_matrix);
u_x= LINEAR_TRANSFORM_X(pen->format->points[i].point.u_x,
pen->format->points[i].point.u_y,transform_matrix);
u_y= LINEAR_TRANSFORM_Y(pen->format->points[i].point.u_x,
pen->format->points[i].point.u_y,transform_matrix);
dx= u_x-x0;
dy= u_y-y0;
distance+= (int)round(sqrt(dx*dx+dy*dy));
v_x= LINEAR_TRANSFORM_X(pen->format->points[i].point.v_x,
pen->format->points[i].point.v_y,transform_matrix);
v_y= LINEAR_TRANSFORM_Y(pen->format->points[i].point.v_x,
pen->format->points[i].point.v_y,transform_matrix);
dx= v_x-u_x;
dy= v_y-u_y;
distance+= (int)round(sqrt(dx*dx+dy*dy));
x1= LINEAR_TRANSFORM_X(pen->format->points[i+1].point.x,
pen->format->points[i+1].point.y,
transform_matrix);
y1= LINEAR_TRANSFORM_Y(pen->format->points[i+1].point.x,
pen->format->points[i+1].point.y,
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
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return false;
}
{
struct path_points*p0,*p1;
int v;
if(counterclockwise)
p0= &(pen->format->points[0]);
else
p0= &(pen->format->points[pen->format->length-1]);
data[0]= p0->point.x;
data[1]= p0->point.y;
v= 2;
for(i= 0;i<pen->format->length-1;i++){
float b_x,b_y,c_x,c_y,dx,dy,x0,y0,x1,x2,y1,y2;
int distance= 0;
if(counterclockwise){
p1= &(pen->format->points[1+i]);
b_x= p0->point.u_x;
b_y= p0->point.u_y;
c_x= p0->point.v_x;
c_y= p0->point.v_y;
}
else{
p1= &(pen->format->points[pen->format->length-2-i]);
b_x= p1->point.v_x;
b_y= p1->point.v_y;
c_x= p1->point.u_x;
c_y= p1->point.u_y;
}
x0= LINEAR_TRANSFORM_X(p0->point.x,p0->point.y,transform_matrix);
y0= LINEAR_TRANSFORM_Y(p0->point.x,p0->point.y,transform_matrix);
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
x2= LINEAR_TRANSFORM_X(p1->point.x,p1->point.y,transform_matrix);
y2= LINEAR_TRANSFORM_Y(p1->point.x,p1->point.y,transform_matrix);
dx= x2-x1;
dy= y2-y1;
distance+= (int)round(sqrt(dx*dx+dy*dy));
dx= x2-x0;
dy= y2-y0;
if(distance==(int)round(sqrt(dx*dx+dy*dy))){
data[v++]= p1->point.x;
data[v++]= p1->point.y;
}
else{
int j;
float dt= 1.0/((float)distance);
for(j= 1;j<=distance;j++){
float t= dt*j;
data[v++]= (1-t)*(1-t)*(1-t)*p0->point.x+3*(1-t)*(1-t)*t*b_x+
3*(1-t)*t*t*c_x+t*t*t*p1->point.x;
data[v++]= (1-t)*(1-t)*(1-t)*p0->point.y+3*(1-t)*(1-t)*t*b_y+
3*(1-t)*t*t*c_y+t*t*t*p1->point.y;
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
/*:524*/
#line 14063 "weaver-interface-metafont.cweb"

/*540:*/
#line 15066 "weaver-interface-metafont.cweb"

if(!(pen->flags&FLAG_CONVEX)){
struct polygon_vertex*poly;
float*triang,*last_triang;
int number_of_vertices= 0,number_of_triangles= 0;
poly= polygon_from_pen(mf,pen,transform_matrix,&number_of_vertices);
if(poly==NULL)
return false;
if(pen->gl_vbo!=0){
if(number_of_vertices<=pen->triang_resolution){
destroy_vertex_linked_list(poly);
return true;
}
else
glDeleteBuffers(1,&(pen->gl_vbo));
}
pen->triang_resolution= number_of_vertices;
triang= temporary_alloc(3*number_of_vertices*2*sizeof(float));
if(triang==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return false;
}
last_triang= triang;
if(is_xmonotone(poly)){
struct polygon_vertex**stack;
stack= (struct polygon_vertex**)
temporary_alloc(sizeof(struct polygon_vertex*)*
number_of_vertices);
if(stack==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
if(temporary_free!=NULL)temporary_free(triang);
return false;
}
if(!triangulate_xmonotone_polygon(poly,&last_triang,&number_of_triangles,
stack)){
if(temporary_free!=NULL)temporary_free(triang);
return false;
}
if(temporary_free!=NULL)
temporary_free(stack);
glGenBuffers(1,&(pen->gl_vbo));
glBindBuffer(GL_ARRAY_BUFFER,pen->gl_vbo);
glBufferData(GL_ARRAY_BUFFER,number_of_triangles*3*2*
sizeof(float),triang,GL_STATIC_DRAW);
pen->indices= number_of_triangles*3;
if(temporary_free!=NULL)
temporary_free(triang);
return true;
}
else{
/*565:*/
#line 15846 "weaver-interface-metafont.cweb"

{
int i;
float*last_triangle= triang;
struct polygon_edge*list_of_subpolygons= NULL,*imaginary_line= NULL;
struct polygon_vertex*current_vertex= poly,*last_vertex;
struct polygon_vertex*list_of_diagonals= NULL,*last_diagonal= NULL;
struct polygon_vertex**buffer;
bool clockwise= is_turning_left(poly->next,poly,poly->prev);
buffer= (struct polygon_vertex**)
temporary_alloc(sizeof(struct polygon_vertex*)*
number_of_vertices);
if(buffer==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
if(temporary_free!=NULL)temporary_free(triang);
return false;
}
prepare_non_monotonous(poly,number_of_vertices);
for(i= 0;i<number_of_vertices;i++){

/*568:*/
#line 15950 "weaver-interface-metafont.cweb"

if(GET_VERTEX_TYPE(current_vertex)==TYPE_BEGIN_VERTEX){
if(current_vertex->prev->y<=current_vertex->next->y){
insert_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,current_vertex->prev->x,
current_vertex->prev->y,
current_vertex,leq_by_vertex,NULL);
}
else{
insert_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,current_vertex->next->x,
current_vertex->next->y,
current_vertex,leq_by_vertex,NULL);
}
}
/*:568*//*569:*/
#line 15974 "weaver-interface-metafont.cweb"

else if(GET_VERTEX_TYPE(current_vertex)==TYPE_END_VERTEX){
struct polygon_edge*removed;
if(current_vertex->prev->y<=current_vertex->next->y){
removed= remove_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,
current_vertex->prev->x,
current_vertex->prev->y,
leq_by_vertex,eq_by_vertex);
}
else{
removed= remove_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,
current_vertex->next->x,
current_vertex->next->y,
leq_by_vertex,eq_by_vertex);
}
if(GET_VERTEX_TYPE(removed->helper)==TYPE_MERGE_VERTEX){
ADD_CUT(current_vertex,removed->helper);
}
DESTROY_POLYGON_EDGE(removed);
}
/*:569*//*570:*/
#line 16007 "weaver-interface-metafont.cweb"

else if(GET_VERTEX_TYPE(current_vertex)==TYPE_SPLIT_VERTEX){
struct polygon_edge*below;
below= find_edge_below(imaginary_line,current_vertex->x,
current_vertex->y);
ADD_CUT(current_vertex,below->helper);
below->helper= current_vertex;
if(current_vertex->prev->y<=current_vertex->next->y){
insert_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,current_vertex->next->x,
current_vertex->next->y,
current_vertex,leq_by_vertex,NULL);
}
else{
insert_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,current_vertex->prev->x,
current_vertex->prev->y,
current_vertex,leq_by_vertex,NULL);
}
}
/*:570*//*571:*/
#line 16040 "weaver-interface-metafont.cweb"

else if(GET_VERTEX_TYPE(current_vertex)==TYPE_MERGE_VERTEX){
struct polygon_edge*removed,*below;
if(current_vertex->prev->y<=current_vertex->next->y){
removed= remove_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,
current_vertex->next->x,
current_vertex->next->y,
leq_by_vertex,eq_by_vertex);
}
else{
removed= remove_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,
current_vertex->prev->x,
current_vertex->prev->y,
leq_by_vertex,eq_by_vertex);
}
if(GET_VERTEX_TYPE(removed->helper)==TYPE_MERGE_VERTEX){
ADD_CUT(current_vertex,removed->helper);
}
DESTROY_POLYGON_EDGE(removed);
below= find_edge_below(imaginary_line,current_vertex->x,
current_vertex->y);
if(GET_VERTEX_TYPE(below->helper)==TYPE_MERGE_VERTEX){
ADD_CUT(current_vertex,below->helper);
}
below->helper= current_vertex;
}
/*:571*//*572:*/
#line 16088 "weaver-interface-metafont.cweb"

else{
struct polygon_edge*removed;
if((clockwise&&
XMONOTONE_LEQ(current_vertex->next,current_vertex->prev))||
(!clockwise&&
XMONOTONE_LEQ(current_vertex->prev,current_vertex->next))){
struct polygon_vertex*to_append;
if(current_vertex->prev->x<=current_vertex->next->x){
removed= remove_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,
current_vertex->prev->x,
current_vertex->prev->y,
leq_by_vertex,eq_by_vertex);
to_append= current_vertex->next;
}
else{
removed= remove_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,
current_vertex->next->x,
current_vertex->next->y,
leq_by_vertex,eq_by_vertex);
to_append= current_vertex->prev;
}
if(GET_VERTEX_TYPE(removed->helper)==TYPE_MERGE_VERTEX){
ADD_CUT(current_vertex,removed->helper);
}
DESTROY_POLYGON_EDGE(removed);
insert_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,to_append->x,
to_append->y,current_vertex,leq_by_vertex,NULL);
}
else{
struct polygon_edge*below;
below= find_edge_below(imaginary_line,current_vertex->x,
current_vertex->y);
if(below==NULL){
print_tree(imaginary_line);
}
if(GET_VERTEX_TYPE(below->helper)==TYPE_MERGE_VERTEX){
ADD_CUT(current_vertex,below->helper);
}
below->helper= current_vertex;
}
}
/*:572*/
#line 15866 "weaver-interface-metafont.cweb"

current_vertex= current_vertex->succ;
}
current_vertex= list_of_diagonals;

while(current_vertex!=NULL){
struct polygon_vertex*new1= NULL,*new2= NULL;
cut_polygon(current_vertex->next,current_vertex->prev,&new1,&new2);
insert_polygon_edge(&list_of_subpolygons,0,0,0,0,new1,leq_by_helper,
eq_by_helper);
insert_polygon_edge(&list_of_subpolygons,0,0,0,0,new2,leq_by_helper,
eq_by_helper);
last_vertex= current_vertex;
current_vertex= current_vertex->succ;
DESTROY_POLYGON_VERTEX(last_vertex);
}
triangulate_polygon_tree(list_of_subpolygons,&last_triangle,
&number_of_triangles,buffer);

glGenBuffers(1,&(pen->gl_vbo));
glBindBuffer(GL_ARRAY_BUFFER,pen->gl_vbo);
glBufferData(GL_ARRAY_BUFFER,number_of_triangles*3*2*
sizeof(float),triang,GL_STATIC_DRAW);
pen->indices= number_of_triangles*3;
if(temporary_free!=NULL){
temporary_free(buffer);
temporary_free(triang);
}
return true;
}
/*:565*/
#line 15116 "weaver-interface-metafont.cweb"

}
}
return false;
/*:540*/
#line 14064 "weaver-interface-metafont.cweb"

}
/*:516*//*528:*/
#line 14580 "weaver-interface-metafont.cweb"

void destroy_vertex_linked_list(struct polygon_vertex*poly){
if(temporary_alloc!=NULL&&poly!=NULL){
poly->prev->next= NULL;
while(poly->next!=NULL){
poly= poly->next;
temporary_free(poly->prev);
}
temporary_free(poly);
}
}
/*:528*//*530:*/
#line 14605 "weaver-interface-metafont.cweb"

struct polygon_vertex*polygon_from_pen(struct metafont*mf,
struct pen_variable*p,
float*transform_matrix,
int*number_of_vertices){
int i,j;
*number_of_vertices= 0;
struct polygon_vertex*first,*last,*leftmost;

struct path_variable*path= p->format;
if(path==NULL){
RAISE_GENERIC_ERROR(mf,NULL,0,ERROR_UNKNOWN);
return NULL;
}

first= NEW_POLYGON_VERTEX();
if(first==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return NULL;
}
first->next= NULL;
first->prev= NULL;
first->x= LINEAR_TRANSFORM_X(path->points[0].point.x,
path->points[0].point.y,transform_matrix);
first->y= LINEAR_TRANSFORM_Y(path->points[0].point.x,
path->points[0].point.y,transform_matrix);
leftmost= first;
last= first;
*number_of_vertices= 1;

for(i= 0;i<path->length-1;i++){
double x0,y0,u_x,u_y,v_x,v_y,x1,y1;
bool straight_line= (p->flags&FLAG_STRAIGHT);
x0= last->x;
y0= last->y;
u_x= LINEAR_TRANSFORM_X(path->points[i].point.u_x,
path->points[i].point.u_y,transform_matrix);
u_y= LINEAR_TRANSFORM_Y(path->points[i].point.u_x,
path->points[i].point.u_y,transform_matrix);
v_x= LINEAR_TRANSFORM_X(path->points[i].point.v_x,
path->points[i].point.v_y,transform_matrix);
v_y= LINEAR_TRANSFORM_Y(path->points[i].point.v_x,
path->points[i].point.v_y,transform_matrix);
x1= LINEAR_TRANSFORM_X(path->points[i+1].point.x,
path->points[i+1].point.y,transform_matrix);
y1= LINEAR_TRANSFORM_Y(path->points[i+1].point.x,
path->points[i+1].point.y,transform_matrix);
if(!straight_line){
double slope1,slope2,slope3;
slope1= (u_x-x0)/(u_y-y0);
slope2= (v_x-u_x)/(v_y-u_y);
slope3= (x1-v_x)/(y1-v_y);
if((y0==u_y&&u_y==v_y&&v_y==y1)||
(slope1==slope2&&slope2==slope3))
straight_line= true;
}
if(straight_line){
if(i<path->length-2){
last->next= NEW_POLYGON_VERTEX();
if(last->next==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return NULL;
}
last->next->prev= last;
last->next->next= NULL;
last= last->next;
last->x= x1;
last->y= y1;
(*number_of_vertices)++;
if(last->x<leftmost->x||
(last->x==leftmost->x&&last->y<leftmost->y))
leftmost= last;
}
}
else{
double dt;
int distance= (int)ceil(sqrt(pow(u_x-x0,2.0)+pow(u_y-y0,2.0)));
distance+= (int)ceil(sqrt(pow(v_x-u_x,2.0)+pow(v_y-u_y,2.0)));
distance+= (int)ceil(sqrt(pow(x1-v_x,2.0)+pow(y1-v_y,2.0)));
dt= 1.0/((double)distance);
for(j= 1;j<=distance;j++){
double t= dt*j;
float x= (1-t)*(1-t)*(1-t)*x0+3*(1-t)*(1-t)*t*u_x+
3*(1-t)*t*t*v_x+t*t*t*x1;
float y= (1-t)*(1-t)*(1-t)*y0+3*(1-t)*(1-t)*t*u_y+
3*(1-t)*t*t*v_y+t*t*t*y1;
if(*number_of_vertices> 0){
if(last->y==x&&last->y==y){
last->x= x;
last->y= y;
continue;
}
}
if(*number_of_vertices> 1){
double slope1,slope2;
slope1= (x-last->x)/(y-last->y);
slope2= (last->x-last->prev->x)/
(last->y-last->prev->y);
if((y==last->y&&y==last->prev->y)||slope1==slope2){

last->x= x;
last->y= y;
continue;
}
}

last->next= NEW_POLYGON_VERTEX();
if(last->next==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return NULL;
}
last->next->prev= last;
last->next->next= NULL;
last= last->next;
last->x= x;
last->y= y;
(*number_of_vertices)++;
if(last->x<leftmost->x||
(last->x==leftmost->x&&last->y<leftmost->y))
leftmost= last;
}
}
}
first->prev= last;
last->next= first;
return leftmost;
}
/*:530*//*532:*/
#line 14764 "weaver-interface-metafont.cweb"

bool is_xmonotone(struct polygon_vertex*poly){
bool clockwise;
struct polygon_vertex*upper,*lower;
upper= lower= poly;
upper->flag= (FLAG_UPPER|FLAG_LOWER);
while(upper->next->y==lower->prev->y){
if(upper->next->x>=upper->x)
upper= upper->next;
else if(lower->prev->x>=lower->x)
lower= lower->prev;
else break;
}
clockwise= (upper->next->y>=lower->prev->y);
upper= lower= poly;
do{
if(XMONOTONE_LEQ(upper,upper->next)){
upper= upper->next;
if(clockwise){
upper->flag= FLAG_UPPER;
}
else{
upper->flag= FLAG_LOWER;
}
}
else if(XMONOTONE_LEQ(lower,lower->prev)){
lower= lower->prev;
if(clockwise){
lower->flag= FLAG_LOWER;
}
else{
lower->flag= FLAG_UPPER;
}
}
else
return false;
}while(upper!=lower);
upper->flag= (FLAG_UPPER|FLAG_LOWER);
return true;
}
/*:532*//*534:*/
#line 14877 "weaver-interface-metafont.cweb"

static void order_vertices_on_xmonotone_polygon(struct polygon_vertex*p){
struct polygon_vertex*upper,*lower,*last;
last= upper= lower= p;
while(lower->prev!=upper&&upper->next!=lower){
if(XMONOTONE_LEQ(upper->next,lower->prev)){
last->succ= upper->next;
last= upper->next;
upper= upper->next;
}
else{
last->succ= lower->prev;
last= lower->prev;
lower= lower->prev;
}
}
last->succ= NULL;
}
/*:534*//*536:*/
#line 14915 "weaver-interface-metafont.cweb"

static bool triangulate_xmonotone_polygon(struct polygon_vertex*p,
float**triangles,
int*number_of_triangles,
struct polygon_vertex**stack){
float*data= *triangles;
int stack_size;
if(p->next->next==p->prev){
ADD_TRIANGLE(data,p->x,p->y,p->next->x,p->next->y,
p->prev->x,p->prev->y);
DESTROY_POLYGON_VERTEX(p->next);
DESTROY_POLYGON_VERTEX(p->prev);
DESTROY_POLYGON_VERTEX(p);
*triangles= data;
return true;
}

order_vertices_on_xmonotone_polygon(p);

stack[0]= p;
p= p->succ;
stack[1]= p;
stack_size= 2;

while(p!=NULL&&p->succ!=NULL&&p->succ->succ!=NULL){
p= p->succ;

if(((p->flag&FLAG_UPPER)&&(stack[stack_size-1]->flag&FLAG_LOWER))||
((p->flag&FLAG_LOWER)&&(stack[stack_size-1]->flag&FLAG_UPPER))){
int d;

for(d= 1;d<stack_size;d++){
ADD_DIAGONAL(data,p,stack[d]);
}

stack[0]= stack[stack_size-1];
stack[1]= p;
stack_size= 2;
}
else{

int d= stack_size-2,last_popped_vertex= stack_size-1;

while(d>=0&&IS_DIAGONAL_INSIDE(stack[d],p)){
ADD_DIAGONAL(data,p,stack[d]);
last_popped_vertex= d;
d--;
}

stack[last_popped_vertex+1]= p;
stack_size= last_popped_vertex+2;
}
}
{
int d;
if(p->succ!=NULL)
p= p->succ;

for(d= stack_size-2;d>=1;d--){
ADD_DIAGONAL(data,p,stack[d]);
}
ADD_DIAGONAL(data,p,p->next);
DESTROY_POLYGON_VERTEX(p->next);
DESTROY_POLYGON_VERTEX(p);
}
*triangles= data;
return true;
}
/*:536*//*543:*/
#line 15229 "weaver-interface-metafont.cweb"

struct polygon_vertex*merge(struct polygon_vertex*begin1,
struct polygon_vertex*begin2){
struct polygon_vertex*ret= NULL,*v= NULL;
if(XMONOTONE_LEQ(begin1,begin2)){
ret= v= begin1;
begin1= begin1->succ;
}
else{
ret= v= begin2;
begin2= begin2->succ;
}
while(begin1!=NULL||begin2!=NULL){
if(begin1==NULL){
v->succ= begin2;
begin2->pred= v;
v= v->succ;
begin2= begin2->succ;
}
else if(begin2==NULL){
v->succ= begin1;
begin1->pred= v;
v= v->succ;
begin1= begin1->succ;
}
else if(XMONOTONE_LEQ(begin1,begin2)){
v->succ= begin1;
begin1->pred= v;
v= v->succ;
begin1= begin1->succ;
}
else{
v->succ= begin2;
begin2->pred= v;
v= v->succ;
begin2= begin2->succ;
}
}
return ret;
}
/*:543*//*544:*/
#line 15273 "weaver-interface-metafont.cweb"

struct polygon_vertex*merge_sort(struct polygon_vertex*p,int size){
if(size==1)
return p;
else{
int i= 0;
struct polygon_vertex*p2= p;
while(i<size/2){
p2= p2->succ;
i++;
}
p2->pred->succ= NULL;
p2->pred= NULL;
p= merge_sort(p,i);
p2= merge_sort(p2,size-i);
p= merge(p,p2);
return p;
}
}
/*:544*//*546:*/
#line 15322 "weaver-interface-metafont.cweb"

void prepare_non_monotonous(struct polygon_vertex*p,int number_of_vertices){
bool turn_left= (p->next->y<p->y);
struct polygon_vertex*first_vertex= p;
do{
bool is_current_turn_left= is_turning_left(p->prev,p,p->next);
if((XMONOTONE_LEQ(p,p->next)&&XMONOTONE_LEQ(p->prev,p))||
(XMONOTONE_LEQ(p,p->prev)&&XMONOTONE_LEQ(p->next,p)))
p->flag= TYPE_REGULAR_VERTEX;

else if(XMONOTONE_LEQ(p,p->next)&&XMONOTONE_LEQ(p,p->prev)){
if(p==first_vertex)
p->flag= TYPE_BEGIN_VERTEX|FLAG_UPPER|FLAG_LOWER;
else if((turn_left&&is_current_turn_left)||
(!turn_left&&!is_current_turn_left))
p->flag= TYPE_BEGIN_VERTEX|FLAG_UPPER|FLAG_LOWER;
else
p->flag= TYPE_SPLIT_VERTEX;
}
else{
if((turn_left&&is_current_turn_left)||
(!turn_left&&!is_current_turn_left))
p->flag= TYPE_END_VERTEX|FLAG_UPPER|FLAG_LOWER;
else
p->flag= TYPE_MERGE_VERTEX;
}
p->succ= p->next;
p->next->pred= p;
p= p->next;
}while(p!=first_vertex);
p->pred->succ= NULL;
p->pred= NULL;
p= merge_sort(first_vertex,number_of_vertices);
}
/*:546*//*548:*/
#line 15372 "weaver-interface-metafont.cweb"

static bool is_turning_left(struct polygon_vertex*p1,
struct polygon_vertex*p2,
struct polygon_vertex*p3){
float v1_x,v1_y,v2_x,v2_y;
v1_x= p2->x-p1->x;
v1_y= p2->y-p1->y;
v2_x= p3->x-p2->x;
v2_y= p3->y-p2->y;
return((v1_x*v2_y-v1_y*v2_x)> 0);
}
/*:548*//*551:*/
#line 15454 "weaver-interface-metafont.cweb"

static void insert_polygon_edge_aux(struct polygon_edge*tree,
struct polygon_edge*new_edge,
bool(*leq)(struct polygon_edge*p1,
struct polygon_edge*p2),
bool(*eq)(struct polygon_edge*p1,
struct polygon_edge*p2)){
if(leq(new_edge,tree)){
if(eq!=NULL&&eq(new_edge,tree)){
DESTROY_POLYGON_EDGE(new_edge);
return;
}
if(tree->left==NULL)
tree->left= new_edge;
else
insert_polygon_edge_aux(tree->left,new_edge,leq,eq);
}
else{
if(tree->right==NULL)
tree->right= new_edge;
else
insert_polygon_edge_aux(tree->right,new_edge,leq,eq);
}
}
static struct polygon_edge*insert_polygon_edge(struct polygon_edge**tree,
float x1,float y1,
float x2,float y2,
struct polygon_vertex*helper,
bool(*leq)(struct polygon_edge*p1,
struct polygon_edge*p2),
bool(*eq)(struct polygon_edge*p1,
struct polygon_edge*p2)){
struct polygon_edge*new_edge;
new_edge= NEW_POLYGON_EDGE();
if(new_edge==NULL)
return NULL;
INITIALIZE_POLYGON_EDGE(new_edge,x1,y1,x2,y2,helper);
if(*tree==NULL)
*tree= new_edge;
else{
struct polygon_edge*current= *tree;
insert_polygon_edge_aux(current,new_edge,leq,eq);
}
return new_edge;
}
/*:551*//*553:*/
#line 15525 "weaver-interface-metafont.cweb"

static bool leq_by_vertex(struct polygon_edge*p1,struct polygon_edge*p2){
if(p1->x1==p1->x2&&p2->x1==p2->x2){
return(p1->y1<=p2->y1);
}
else if(p1->x1==p1->x2){
float slope= (p2->y2-p2->y1)/(p2->x2-p2->x1);
float b= p2->y1-slope*p2->x1;
if(p1->y1<=p1->y2)
return(p1->y2<=(slope*p1->x2+b));
else
return(p1->y1<=(slope*p1->x1+b));
}
else if(p2->x1==p2->x2){
float slope= (p1->y2-p1->y1)/(p1->x2-p1->x1);
float b= p1->y1-slope*p1->x1;
if(p2->y1<=p2->y2)
return(slope*p2->x1+b)<=p2->y1;
else
return(slope*p2->x2+b)<=p2->y2;
}
else if((p1->x1<=p2->x1&&p1->x1<=p2->x2)||
(p1->x2<=p2->x1&&p1->x2<=p2->x2)){
float slope= (p1->y2-p1->y1)/(p1->x2-p1->x1);
float b= p1->y1-slope*p1->x1;
if(p2->x1<=p2->x2)
return(slope*p2->x1+b<=p2->y1);
else
return(slope*p2->x2+b<=p2->y2);
}
else{
float slope= (p2->y2-p2->y1)/(p2->x2-p2->x1);
float b= p2->y1-slope*p2->x1;
if(p1->x1<=p1->x2)
return(p1->y1<=slope*p1->x1+b);
else
return(p1->y2<=slope*p1->x2+b);
}
}
/*:553*//*555:*/
#line 15574 "weaver-interface-metafont.cweb"

static bool eq_by_vertex(struct polygon_edge*p1,struct polygon_edge*p2){
return(p1->x1==p2->x1&&p1->y1==p2->y1&&
p1->x2==p2->x2&&p1->y2==p2->y2)||
(p1->x1==p2->x2&&p1->y1==p2->y2&&
p1->x2==p2->x1&&p1->y2==p2->y1);
}
/*:555*//*557:*/
#line 15594 "weaver-interface-metafont.cweb"

static struct polygon_edge*remove_polygon_edge(struct polygon_edge**tree,
float x1,float y1,float x2,
float y2,
bool(*leq)(struct polygon_edge*p1,
struct polygon_edge*p2),
bool(*eq)(struct polygon_edge*p1,
struct polygon_edge*p2)){
struct polygon_edge*current= *tree,searched;
searched.x1= x1;searched.x2= x2;
searched.y1= y1;searched.y2= y2;
if(current==NULL)
return NULL;
if(eq(current,&searched)){
if(current->left==NULL&&current->right==NULL){
*tree= NULL;
return current;
}
else if(current->right==NULL){
*tree= current->left;
current->left->parent= current->parent;
return current;
}
else if(current->left==NULL){
*tree= current->right;
current->right->parent= current->parent;
return current;
}
else{

struct polygon_edge*suc= current->right;
while(suc->left!=NULL)
suc= suc->left;
if(suc==current->right)
current->right= suc->right;
else
suc->parent->left= suc->right;
suc->right= current->right;
suc->left= current->left;
*tree= suc;
return current;
}
}
else{
if(leq(&searched,current)){
if(current->left!=NULL)
return remove_polygon_edge(&(current->left),x1,y1,x2,y2,leq,eq);
else
return NULL;
}
else{
if(current->right!=NULL)
return remove_polygon_edge(&(current->right),x1,y1,x2,y2,leq,eq);
else
return NULL;
}
}
}
/*:557*//*559:*/
#line 15663 "weaver-interface-metafont.cweb"

static struct polygon_edge*find_edge_below(struct polygon_edge*tree,
float x,float y){
float slope,b;
if(tree==NULL)
return NULL;
slope= (tree->y2-tree->y1)/(tree->x2-tree->x1);
b= tree->y1-slope*tree->x1;
if(slope*x+b<=y){
struct polygon_edge*candidate;
candidate= find_edge_below(tree->right,x,y);
if(candidate!=NULL)
return candidate;
else return tree;
}

else return find_edge_below(tree->left,x,y);
}
/*:559*//*561:*/
#line 15698 "weaver-interface-metafont.cweb"

static bool cut_polygon(struct polygon_vertex*v1,struct polygon_vertex*v2,
struct polygon_vertex**new1,
struct polygon_vertex**new2){
struct polygon_vertex*vv1,*vv2;
bool turn1= is_turning_left(v1->prev,v1,v1->next);
bool turn2= is_turning_left(v2->prev,v2,v2->next);
vv1= NEW_POLYGON_VERTEX();
if(vv1==NULL)
return false;
vv2= NEW_POLYGON_VERTEX();
if(vv2==NULL)
return false;

v1->flag&= (~0x3);
v2->flag&= (~0x3);

memcpy(vv1,v1,sizeof(struct polygon_vertex));
memcpy(vv2,v2,sizeof(struct polygon_vertex));


if((is_turning_left(v2,v1,v1->next)!=turn1&&
is_turning_left(vv1->prev,vv1,vv2)==turn1)||
(is_turning_left(v2->prev,v2,v1)!=turn2&&
is_turning_left(vv1,vv2,vv2->next)==turn2)){
v1->next->prev= vv1;
v1->next= v2;
v2->prev->next= vv2;
v2->prev= v1;
vv1->prev->next= v1;
vv1->prev= vv2;
vv2->next->prev= v2;
vv2->next= vv1;
}
else{
vv1->next->prev= v1;
vv1->next= vv2;
vv2->prev->next= v2;
vv2->prev= vv1;
v1->prev->next= vv1;
v1->prev= v2;
v2->next->prev= vv2;
v2->next= v1;
}

while(XMONOTONE_LEQ(vv1->prev,vv1))
vv1= vv1->prev;
while(XMONOTONE_LEQ(vv1->next,vv1))
vv1= vv1->next;
*new1= vv1;
while(XMONOTONE_LEQ(v1->prev,v1))
v1= v1->prev;
while(XMONOTONE_LEQ(v1->next,v1))
v1= v1->next;
*new2= v1;
return true;
}
/*:561*//*564:*/
#line 15834 "weaver-interface-metafont.cweb"

static bool leq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2){
return(p1->helper<=p2->helper);
}
static bool eq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2){
return(p1->helper==p2->helper);
}
/*:564*//*567:*/
#line 15919 "weaver-interface-metafont.cweb"

static void triangulate_polygon_tree(struct polygon_edge*tree,
float**triangles,
int*number_of_triangles,
struct polygon_vertex**buffer){
if(tree==NULL)
return;
if(tree->left!=NULL)
triangulate_polygon_tree(tree->left,triangles,number_of_triangles,
buffer);
if(tree->right!=NULL)
triangulate_polygon_tree(tree->right,triangles,number_of_triangles,
buffer);
if(!is_xmonotone(tree->helper))
fprintf(stderr,"WARNING: This should not happen: non-monotonous pen!\n");
triangulate_xmonotone_polygon(tree->helper,triangles,
number_of_triangles,buffer);
DESTROY_POLYGON_EDGE(tree);
return;
}
/*:567*//*607:*/
#line 16884 "weaver-interface-metafont.cweb"

#define ERASE_FLAG 1
bool drawing_commands(struct metafont*mf,struct context*cx,
struct path_variable*path,unsigned int flags){
int i,j;
float transform_matrix[9];
struct pen_variable*currentpen= cx->currentpen;
struct picture_variable*currentpicture= cx->currentpicture;

if(currentpen->referenced!=NULL){
memcpy(transform_matrix,currentpen->referenced->gl_matrix,
9*sizeof(float));
MATRIX_MULTIPLICATION(transform_matrix,currentpen->gl_matrix);
currentpen= currentpen->referenced;
}
else
memcpy(transform_matrix,currentpen->gl_matrix,9*sizeof(float));
/*596:*/
#line 16695 "weaver-interface-metafont.cweb"

{
if(cx->currentpicture_fb==0){
int pic_width,pic_height;
GLuint texture;
pic_width= cx->currentpicture->width;
pic_height= cx->currentpicture->height;
texture= cx->currentpicture->texture;
glGenFramebuffers(1,&(cx->currentpicture_fb));
glBindTexture(GL_TEXTURE_2D,texture);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,pic_width,pic_height,0,GL_RGBA,
GL_UNSIGNED_BYTE,NULL);
glBindFramebuffer(GL_FRAMEBUFFER,cx->currentpicture_fb);
glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,
texture,0);
if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,cx,0);
return false;
}
}
else
glBindFramebuffer(GL_FRAMEBUFFER,cx->currentpicture_fb);
}
/*:596*/
#line 16901 "weaver-interface-metafont.cweb"


for(i= 0;i<path->length-1;i++){
int distance= 0;
float dx,dy,dt;
dx= path->points[i].point.u_x-path->points[i].point.x;
dy= path->points[i].point.u_y-path->points[i].point.y;
distance+= (int)ceil(sqrt(dx*dx+dy*dy));
dx= path->points[i].point.v_x-path->points[i].point.u_x;
dy= path->points[i].point.v_y-path->points[i].point.u_y;
distance+= (int)ceil(sqrt(dx*dx+dy*dy));
dx= path->points[(i+1)%(path->length)].point.x-path->points[i].point.v_x;
dy= path->points[(i+1)%(path->length)].point.y-path->points[i].point.v_y;
distance+= (int)ceil(sqrt(dx*dx+dy*dy));
distance*= 1.4;
dt= 1/((float)distance);
for(j= 0;j<=distance;j++){
float t= dt*j;
float x= (1-t)*(1-t)*(1-t)*path->points[i].point.x+
3*(1-t)*(1-t)*t*path->points[i].point.u_x+
3*(1-t)*t*t*path->points[i].point.v_x+
t*t*t*path->points[(i+1)%(path->length)].point.x;
float y= (1-t)*(1-t)*(1-t)*path->points[i].point.y+
3*(1-t)*(1-t)*t*path->points[i].point.u_y+
3*(1-t)*t*t*path->points[i].point.v_y+
t*t*t*path->points[(i+1)%(path->length)].point.y;
drawpoint(cx,currentpen,currentpicture,x,y,transform_matrix,
flags&ERASE_FLAG);
}
}

if(path->length==1)
drawpoint(cx,currentpen,currentpicture,path->points[0].point.x,
path->points[0].point.y,transform_matrix,flags&ERASE_FLAG);
return true;
}
/*:607*//*611:*/
#line 17034 "weaver-interface-metafont.cweb"

void drawpoint(struct context*cx,
struct pen_variable*pen,struct picture_variable*pic,
float x,float y,float*matrix,bool erasing){
float gl_matrix[9];
gl_matrix[0]= (2*matrix[0])/pic->width;
gl_matrix[1]= (2*matrix[1])/pic->height;
gl_matrix[2]= 0.0;
gl_matrix[3]= (2*matrix[3])/pic->width;
gl_matrix[4]= (2*matrix[4])/pic->height;
gl_matrix[5]= 0.0;
gl_matrix[6]= 2*(matrix[6]+x)/pic->width-1.0;
gl_matrix[7]= 2*(matrix[7]+cx->current_depth+y)/pic->height-
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
glUniform4f(pen_uniform_color,cx->color[0],cx->color[1],
cx->color[2],cx->color[3]);
}
glEnableVertexAttribArray(0);
if(pen->flags&FLAG_CONVEX)
glDrawArrays(GL_TRIANGLE_FAN,0,pen->indices);
else
glDrawArrays(GL_TRIANGLES,0,pen->indices);
}
/*:611*//*618:*/
#line 17210 "weaver-interface-metafont.cweb"

static const uint32_t greatest_point[332]= {

0x7f,0xff,0x17f,0x24f,0x2af,0x2ff,0x36f,0x3ff,0x4ff,0x52f,
0x58f,0x5ff,0x6ff,0x74f,0x7ff,0x7bf,0x7ff,0x83f,0x85f,0x86f,
0x89f,0x8ff,0x97f,0x9ff,0xa7f,0xaff,0xb7f,0xbff,0xc7f,0xcff,
0xd7f,0xdff,0xe7f,0xeff,0xfff,0x109f,0x10ff,0x11ff,0x137f,0x139f,
0x13ff,0x167f,0x169f,0x16ff,0x171f,0x173f,0x175f,0x177f,0x17ff,0x18af,
0x18ff,0x194f,0x197f,0x19df,0x19ff,0x1a1f,0x1aaf,0x1aff,0x1b7f,0x1bbf,
0x1bff,0x1c4f,0x1c7f,0x1c8f,0x1cbf,0x1ccf,0x1cff,0x1d7f,0x1dbf,0x1dff,
0x1eff,0x1fff,0x206f,0x209f,0x20cf,0x20ff,0x214f,0x218f,0x21ff,0x22ff,
0x23ff,0x243f,0x245f,0x24ff,0x257f,0x259f,0x25ff,0x26ff,0x27bf,0x27ef,
0x27ff,0x28ff,0x297f,0x29ff,0x2aff,0x2bff,0x2c5f,0x2c7f,0x2cff,0x2d2f,
0x2d7f,0x2ddf,0x2dff,0x2eff,0x2fdf,0x2fff,0x303f,0x309f,0x30ff,0x312f,
0x318f,0x319f,0x31bf,0x31ef,0x31ff,0x32ff,0x33ff,0x4dbf,0x4dff,0x9fff,
0xa48f,0xa4cf,0xa4ff,0xa63f,0xa69f,0xa69f,0xa6ff,0xa71f,0xa7ff,0xa82f,
0xa83f,0xa87f,0xa8df,0xa8ff,0xa92f,0xa95f,0xa97f,0xa9df,0xa9ff,0xaa5f,
0xaa7f,0xaadf,0xaaff,0xab2f,0xab6f,0xabbf,0xabff,0xd7af,0xd7ff,0xdb7f,
0xdbff,0xdfff,0xf8ff,0xfaff,0xfb4f,0xfdff,0xfe0f,0xfe1f,0xfe2f,0xfe4f,
0xfe6f,0xfeff,0xffef,0xffff,

0x1007f,0x100ff,0x1013f,0x1018f,0x101cf,0x101ff,0x1029f,0x102df,
0x102ff,0x1032f,0x1034f,0x1037f,0x1039f,0x103df,0x1044f,0x1047f,
0x104af,0x104ff,0x1052f,0x1056f,0x105bf,0x1077f,0x107bf,0x1083f,
0x1085f,0x1087f,0x108af,0x108ff,0x1091f,0x1093f,0x1099f,0x109ff,
0x10a5f,0x10a7f,0x10a9f,0x10aff,0x10b3f,0x10b5f,0x10b7f,0x10baf,
0x10c4f,0x10cff,0x10d3f,0x10e7f,0x10ebf,0x10eff,0x10f2f,0x10f6f,
0x10faf,0x10fdf,0x10fff,0x1107f,0x110cf,0x110ff,0x1114f,0x1117f,
0x111df,0x111ff,0x1124f,0x112af,0x112ff,0x1137f,0x1147f,0x114df,
0x115ff,0x1166f,0x1167f,0x116cf,0x1174f,0x1184f,0x118ff,0x1195f,
0x119ff,0x11a4f,0x11aaf,0x11abf,0x11aff,0x11b5f,0x11c6f,0x11cbf,
0x11d5f,0x11daf,0x11eff,0x11f5f,0x11fbf,0x11fff,0x123ff,0x1247f,
0x1254f,0x12fff,0x1342f,0x1345f,0x1467f,0x16a3f,0x16a6f,0x16acf,
0x16aff,0x16b8f,0x16e9f,0x16f9f,0x16fff,0x187ff,0x18aff,0x18cff,
0x18d7f,0x1afff,0x1b0ff,0x1b12f,0x1b16f,0x1b2ff,0x1bc9f,0x1bcaf,
0x1cfcf,0x1d0ff,0x1d1ff,0x1d24f,0x1d2df,0x1d2ff,0x1d35f,0x1d37f,
0x1d7ff,0x1daaf,0x1dfff,0x1e02f,0x1e08f,0x1e14f,0x1e2bf,0x1e2ff,
0x1e4ff,0x1e7ff,0x1e8df,0x1e95f,0x1ecbf,0x1ed4f,0x1eeff,0x1f02f,
0x1f09f,0x1f0ff,0x1f1ff,0x1f2ff,0x1f5ff,0x1f64f,0x1f67f,0x1f6ff,
0x1f77f,0x1f7ff,0x1f8ff,0x1f9ff,0x1fa6f,0x1faff,0x1fbff,

0x1ffff,

0x2a6df,0x2b73f,0x2b81f,0x2ceaf,0x2ebef,0x2fa1f,

0x2ffff,

0x3134f,0x323af,

0xdffff,

0xe007f,0xe00ff,0xe01ef,

0xeffff,

0xfffff,

0x10ffff
};
static struct _glyph*get_glyph(struct metafont*mf,unsigned char*c,
bool create_if_not_exist){
uint32_t code_point;
int block,block_size,index;

if(c[0]<128)
code_point= c[0];
else if(c[0]>=192&&c[0]<=223&&c[1]>=128&&c[1]<=191){
code_point= c[1]-128;
code_point+= (c[0]-192)*64;
}
else if(c[0]>=224&&c[0]<=239&&c[1]>=128&&c[1]<=191&&
c[2]>=128&&c[2]<=191){
code_point= c[2]-128;
code_point+= (c[1]-128)*64;
code_point+= (c[0]-224)*4096;
}
else if(c[0]>=240&&c[0]<=247&&c[1]>=128&&c[1]<=191&&
c[2]>=128&&c[2]<=191&&c[3]>=128&&c[3]<=191){
code_point= c[3]-128;
code_point+= (c[2]-128)*64;
code_point+= (c[1]-128)*4096;
code_point+= (c[0]-240)*262144;
}
else return NULL;
if(code_point> greatest_point[331])
return NULL;
for(block= 0;code_point> greatest_point[block];block++);
if(block==0){
block_size= greatest_point[block]+1;
index= code_point;
}
else{
block_size= greatest_point[block]-greatest_point[block-1];
index= code_point-greatest_point[block-1]-1;
}
if(mf->glyphs[block]==NULL){
int i;
if(!create_if_not_exist)
return NULL;
mf->glyphs[block]= permanent_alloc(sizeof(struct _glyph)*block_size);
if(mf->glyphs[block]==NULL){
RAISE_ERROR_NO_MEMORY(mf,NULL,0);
return NULL;
}
for(i= 0;i<block_size;i++)
INITIALIZE_GLYPH(mf->glyphs[block][i]);
}
if(mf->glyphs[block][index].begin==NULL&&!create_if_not_exist)
return NULL;
return&(mf->glyphs[block][index]);
}
/*:618*//*671:*/
#line 18941 "weaver-interface-metafont.cweb"

void token_to_string(struct generic_token*tok,char*dst){
/*672:*/
#line 18989 "weaver-interface-metafont.cweb"

if(tok->type==TYPE_NUMERIC){
snprintf(dst,32,"%g",((struct numeric_token*)tok)->value);
return;
}
/*:672*//*673:*/
#line 18999 "weaver-interface-metafont.cweb"

if(tok->type==TYPE_STRING){
dst[0]= '"';
memcpy(&dst[1],((struct string_token*)tok)->value,29);
strncat(dst,"\"",2);
return;
}
/*:673*//*674:*/
#line 19012 "weaver-interface-metafont.cweb"

if(tok->type==TYPE_SYMBOLIC){
struct symbolic_token*symb= (struct symbolic_token*)tok;
size_t size= strlen(symb->value);
if(size<=31)
memcpy(dst,((struct symbolic_token*)tok)->value,size);
else{
memcpy(dst,((struct symbolic_token*)tok)->value,28);
dst[28]= dst[29]= dst[30]= '.';
}
dst[31]= '\0';
return;
}
/*:674*/
#line 18943 "weaver-interface-metafont.cweb"

tokenid_to_string(tok->type,dst);
return;
}
void tokenid_to_string(int token_id,char*dst){
switch(token_id){
case TYPE_NUMERIC:
strcpy(dst,"<Numeric>");
break;
case TYPE_STRING:
strcpy(dst,"<String>");
break;
case TYPE_SYMBOLIC:
strcpy(dst,"<Variable>");
break;
case TYPE_FOR:
strcpy(dst,"for");
break;
case TYPE_ENDFOR:
strcpy(dst,"endfor");
break;
case TYPE_OPEN_PARENTHESIS:
dst[0]= '(';dst[1]= '\0';
break;
case TYPE_CLOSE_PARENTHESIS:
dst[0]= ')';dst[1]= '\0';
break;
case TYPE_COMMA:
dst[0]= ',';dst[1]= '\0';
break;
case TYPE_SEMICOLON:
dst[0]= ';';dst[1]= '\0';
break;
default:
if(token_id>=TYPE_BEGINGROUP){
size_t len= strlen(list_of_keywords[token_id-TYPE_BEGINGROUP]);
memcpy(dst,list_of_keywords[token_id-TYPE_BEGINGROUP],len+1);
return;
}
}
}
/*:671*/
#line 524 "weaver-interface-metafont.cweb"

/*30:*/
#line 1063 "weaver-interface-metafont.cweb"

bool _Winit_weavefont(void*(*t_alloc)(size_t),
void(*t_free)(void*),
void*(*p_alloc)(size_t),
void(*p_free)(void*),
uint64_t(*random)(void),int pixel_density){
temporary_alloc= t_alloc;
temporary_free= t_free;
permanent_alloc= p_alloc;
permanent_free= p_free;
random_func= random;
dpi= pixel_density;
/*418:*/
#line 10867 "weaver-interface-metafont.cweb"

glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);

glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
/*:418*//*424:*/
#line 10980 "weaver-interface-metafont.cweb"

{
program= compile_shader_program(vertex_shader,fragment_shader);
if(program==0)
return false;
uniform_matrix= glGetUniformLocation(program,"model_view_matrix");
uniform_texture= glGetUniformLocation(program,"texture1");
}
/*:424*//*435:*/
#line 11275 "weaver-interface-metafont.cweb"

{
inv_program= compile_shader_program(vertex_shader,fragment_shader_inverse);
uniform_inv_matrix= glGetUniformLocation(inv_program,"model_view_matrix");
uniform_inv_texture= glGetUniformLocation(inv_program,"texture1");
}
/*:435*//*519:*/
#line 14096 "weaver-interface-metafont.cweb"

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
/*:519*//*603:*/
#line 16826 "weaver-interface-metafont.cweb"

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
/*:603*/
#line 1075 "weaver-interface-metafont.cweb"

return true;
}
/*:30*//*31:*/
#line 1084 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void){
/*419:*/
#line 10876 "weaver-interface-metafont.cweb"

glDeleteBuffers(1,&vbo);
/*:419*//*425:*/
#line 10992 "weaver-interface-metafont.cweb"

glDeleteProgram(program);
/*:425*//*436:*/
#line 11285 "weaver-interface-metafont.cweb"

glDeleteProgram(inv_program);
/*:436*//*520:*/
#line 14111 "weaver-interface-metafont.cweb"

glDeleteBuffers(1,&pensquare_vbo);
/*:520*//*604:*/
#line 16841 "weaver-interface-metafont.cweb"

glDeleteProgram(pen_program);
glDeleteProgram(pen_erase_program);
/*:604*/
#line 1086 "weaver-interface-metafont.cweb"

}
/*:31*//*79:*/
#line 2325 "weaver-interface-metafont.cweb"

void _Wdestroy_metafont(struct metafont*mf){
if(permanent_free!=NULL){
permanent_free(mf->file);

/*103:*/
#line 2865 "weaver-interface-metafont.cweb"

if(permanent_free!=NULL){
struct variable*v= (struct variable*)(mf->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*140:*/
#line 3591 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&permanent_free!=NULL)
path_recursive_free(permanent_free,path,false);
}
/*:140*//*181:*/
#line 4995 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&permanent_free!=NULL)
path_recursive_free(permanent_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
/*:181*//*194:*/
#line 5186 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:194*/
#line 2871 "weaver-interface-metafont.cweb"

permanent_free(v);
v= next;
}
}
/*:103*//*104:*/
#line 2882 "weaver-interface-metafont.cweb"

if(permanent_free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)(named->var);
next= (struct named_variable*)(named->next);
permanent_free(named->name);
/*140:*/
#line 3591 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&permanent_free!=NULL)
path_recursive_free(permanent_free,path,false);
}
/*:140*//*181:*/
#line 4995 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&permanent_free!=NULL)
path_recursive_free(permanent_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
/*:181*//*194:*/
#line 5186 "weaver-interface-metafont.cweb"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:194*/
#line 2891 "weaver-interface-metafont.cweb"

permanent_free(v);
permanent_free(named);
named= next;
}
}
/*:104*//*124:*/
#line 3280 "weaver-interface-metafont.cweb"

if(permanent_free!=NULL)
permanent_free(mf->internal_numeric_variables);
/*:124*//*133:*/
#line 3435 "weaver-interface-metafont.cweb"

if(permanent_free!=NULL)
permanent_free(mf->internal_transform_variables);
/*:133*//*188:*/
#line 5100 "weaver-interface-metafont.cweb"

if(permanent_free!=NULL){
if(mf->internal_pen_variables[0].format!=NULL){
permanent_free(mf->internal_pen_variables[0].format->points);
permanent_free(mf->internal_pen_variables[0].format);
}
permanent_free(mf->internal_pen_variables);
}
/*:188*//*619:*/
#line 17327 "weaver-interface-metafont.cweb"

{
int block,block_size,index;

for(block= 0;block<332;block++){
if(mf->glyphs[block]!=NULL){

if(block==0)
block_size= greatest_point[block]+1;
else
block_size= greatest_point[block]-greatest_point[block-1];

for(index= 0;index<block_size;index++){
struct kerning*kern= mf->glyphs[block][index].kern;
if(mf->glyphs[block][index].texture!=0)
glDeleteTextures(1,&(mf->glyphs[block][index].texture));
while(kern!=NULL&&permanent_free!=NULL){
struct kerning*to_be_erased;
to_be_erased= kern;
kern= kern->next;
permanent_free(to_be_erased);
}
}
if(permanent_free!=NULL)
permanent_free(mf->glyphs[block]);
}
}
}
/*:619*/
#line 2330 "weaver-interface-metafont.cweb"

MUTEX_DESTROY(mf->mutex);
permanent_free(mf);
}
}
/*:79*//*626:*/
#line 17662 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value){
int i;
bool updated= false;
char*internal_vars[]= {"pt","cm","mm","color_r","color_g","color_b",
"color_a","monospace",NULL};
for(i= 0;internal_vars[i]!=NULL;i++)
if(!strcmp(name,internal_vars[i])){
mf->internal_numeric_variables[i].value= value;
updated= true;
}
if(!updated){
struct named_variable*var= (struct named_variable*)mf->named_variables;
while(var!=NULL){
if(!strcmp(name,var->name)){
struct numeric_variable*n= (struct numeric_variable*)var->var;
if(n->type!=TYPE_T_NUMERIC)
return false;
n->value= value;
updated= true;
}
var= var->next;
}
}
if(updated){
int j;
for(i= 0;i<332;i++){
struct _glyph*g= mf->glyphs[i];
int size= ((i==0)?(greatest_point[0]+1):
(greatest_point[i]-greatest_point[i-1]));
if(g!=NULL){
for(j= 0;j<size;j++)
g[j].need_rendering= true;
}
}
return true;
}
return false;
}
/*:626*//*627:*/
#line 17706 "weaver-interface-metafont.cweb"

float _Wread_numeric_variable(struct metafont*mf,char*name){
struct named_variable*var= (struct named_variable*)mf->named_variables;
while(var!=NULL){
if(!strcmp(name,var->name)){
struct numeric_variable*n= (struct numeric_variable*)var->var;
if(n->type!=TYPE_T_NUMERIC)
return NAN;
return n->value;
}
var= var->next;
}
return NAN;
}
/*:627*//*628:*/
#line 17725 "weaver-interface-metafont.cweb"

struct metafont*_Wnew_metafont(char*filename){
struct metafont*mf;
struct context*cx;
struct generic_token*first,*last;
bool ret;
mf= init_metafont(filename);
lexer(mf,filename,&first,&last);
cx= init_context(mf);
ret= eval_program(mf,cx,first,last);
destroy_context(cx);
if(!ret){
_Wdestroy_metafont(mf);
return NULL;
}
return mf;
}
/*:628*//*630:*/
#line 17757 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning){
struct _glyph*current;
struct kerning*k;
struct context*cx= NULL;
MUTEX_WAIT(mf->mutex);
current= get_glyph(mf,(unsigned char*)glyph,false);
if(current==NULL||current->begin==NULL||current->end==NULL){
MUTEX_SIGNAL(mf->mutex);
return false;
}
if(current->need_rendering){
current->is_being_rendered= true;
cx= init_context(mf);
if(cx==NULL){
MUTEX_SIGNAL(mf->mutex);
return false;
}
if(!eval_list_of_statements(mf,cx,current->begin,current->end)){
destroy_context(cx);
MUTEX_SIGNAL(mf->mutex);
return false;
}
current->is_being_rendered= false;
}
*texture= current->texture;
*width= current->width;
*height= current->height;
*depth= current->depth;
*italcorr= current->italic_correction;
k= current->kern;
*kerning= 0;
while(k!=NULL&&next_glyph!=NULL){
if(!strcmp(k->next_char,next_glyph)){
*kerning= k->kern;
break;
}
k= k->next;
}
if(cx!=NULL)
destroy_context(cx);
MUTEX_SIGNAL(mf->mutex);
return true;
}
/*:630*//*661:*/
#line 18657 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
/*662:*/
#line 18744 "weaver-interface-metafont.cweb"

void _interface_free_metafont(void*data){
_Wdestroy_metafont((struct metafont*)data);
}
/*:662*//*663:*/
#line 18755 "weaver-interface-metafont.cweb"

void _reload_texture(struct user_interface*target){
struct metafont*mf= (struct metafont*)(target->_internal_data);
int texture_width,texture_height,texture_depth,ignore_this;


float size= 72.0*(target->height)/dpi;
_Wwrite_numeric_variable(mf,"size",size);

size= 72.0*(target->width)/dpi;
_Wwrite_numeric_variable(mf,"hsize",size);
glDeleteTextures(1,target->_texture1);
_Wrender_glyph(mf,mf->first_glyph_symbol,NULL,target->_texture1,
&texture_width,&texture_height,
&texture_depth,&ignore_this,&ignore_this);
if(mf->err){
_Wprint_metafont_error(mf);
_Wdestroy_metafont(mf);
target->_internal_data= NULL;
return;
}
if(!(mf->first_glyph->need_rendering))
target->animate= false;
target->width= texture_width;
target->height= texture_height+texture_depth;
}
/*:663*/
#line 18659 "weaver-interface-metafont.cweb"

void _Wmetafont_loading(void*(*p_alloc)(size_t),
void(*p_free)(void*),
void*(*t_alloc)(size_t),
void(*t_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target){
struct metafont*mf;
float size;
int texture_width,texture_height,texture_depth,ignore_this;
if(p_alloc!=permanent_alloc||p_free!=permanent_free||
t_alloc!=temporary_alloc||t_free!=temporary_free){
fprintf(stderr,"Weaver Interface Metafont Submodule: ERROR: Inconsistent "
"usage of memory allocators.\n");
exit(1);
}
if(before_loading_interface!=NULL)
before_loading_interface();
mf= _Wnew_metafont(source_filename);
if(mf==NULL)
return;
if(mf->err){
_Wprint_metafont_error(mf);
return;
}


size= 72.0*(target->height)/dpi;
_Wwrite_numeric_variable(mf,"size",size);

size= 72.0*(target->width)/dpi;
_Wwrite_numeric_variable(mf,"hsize",size);

target->_texture1= (GLuint*)permanent_alloc(sizeof(GLuint));
if(target->_texture1==NULL)
return;
_Wrender_glyph(mf,mf->first_glyph_symbol,NULL,target->_texture1,
&texture_width,&texture_height,
&texture_depth,&ignore_this,&ignore_this);
if(mf->err){
_Wprint_metafont_error(mf);
_Wdestroy_metafont(mf);
return;
}
if(mf->first_glyph->need_rendering){
float frame_duration;
target->animate= true;
target->frame_duration= (unsigned*)permanent_alloc(sizeof(unsigned));
if(target->frame_duration==NULL){
_Wdestroy_metafont(mf);
return;
}
frame_duration= (unsigned)_Wread_numeric_variable(mf,"frame_duration");
if(isnan(frame_duration))
target->frame_duration[0]= 0;
else
target->frame_duration[0]= (unsigned)frame_duration;
target->max_repetition= -1;
}
target->width= texture_width;
target->height= texture_height+texture_depth;
target->_internal_data= (void*)mf;
target->_free_internal_data= _interface_free_metafont;
target->_reload_texture= _reload_texture;
target->_loaded_texture= true;
if(after_loading_interface!=NULL)
after_loading_interface();
}
#endif
#line 18730 "weaver-interface-metafont.cweb"
/*:661*//*667:*/
#line 18851 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*mf){
char line_number[8];


if(mf->errno_line==0)
line_number[0]= '\0';
else
sprintf(line_number,"%d:",mf->errno_line);
switch(mf->err){
case ERROR_NO_ERROR:
fprintf(stderr,"%s:%s No errors.",mf->file,line_number);
break;
/*678:*/
#line 19108 "weaver-interface-metafont.cweb"

case ERROR_DISCONTINUOUS_PATH:
float*buffer= (float*)(mf->errno_str);
fprintf(stderr,
"%s:%s Concatenating endpoint '(%g, %g)' with endpoint '(%g, %g)':"
" discontinuous path.",
mf->file,line_number,buffer[0],buffer[1],buffer[2],buffer[3]);
break;
/*:678*//*681:*/
#line 19135 "weaver-interface-metafont.cweb"

case ERROR_DIVISION_BY_ZERO:
fprintf(stderr,"%s:%s Division by zero.",mf->file,line_number);
break;
/*:681*//*684:*/
#line 19162 "weaver-interface-metafont.cweb"

case ERROR_DUPLICATE_GLYPH:
fprintf(stderr,
"%s:%s Glyph '%s' is being defined twice.",
mf->file,line_number,mf->errno_str);
break;
/*:684*//*687:*/
#line 19206 "weaver-interface-metafont.cweb"

case ERROR_EMPTY_DELIMITER:
fprintf(stderr,"%s:%s Unexpected empty delimiter '%c%c'.",
mf->file,line_number,mf->errno_int,
((mf->errno_int=='(')?(')'):
((mf->errno_int=='[')?(']'):('}'))));
break;
/*:687*//*690:*/
#line 19239 "weaver-interface-metafont.cweb"

case ERROR_EXPECTED_FOUND:
char expected_name[32];
memset(expected_name,0,32);
tokenid_to_string(mf->errno_int,expected_name);
fprintf(stderr,"%s:%s Expected '%s' token. Found '%s' instead.",
mf->file,line_number,expected_name,mf->errno_str);
break;
/*:690*//*693:*/
#line 19277 "weaver-interface-metafont.cweb"

case ERROR_FAILED_OPENING_FILE:
fprintf(stderr,"%s:%s Failed opening file \"%s\": %s.",mf->file,
line_number,mf->errno_str,strerror(mf->errno_int));
break;
/*:693*//*697:*/
#line 19313 "weaver-interface-metafont.cweb"

case ERROR_INCOMPLETE_SOURCE:
fprintf(stderr,
"%s:%s Incomplete code. WeaveFont source code ended in middle of statement.",
mf->file,line_number);
break;
/*:697*//*700:*/
#line 19343 "weaver-interface-metafont.cweb"

case ERROR_INCOMPLETE_STATEMENT:
fprintf(stderr,
"%s:%s Incomplete statement. You ended the statement with ';' before "
"fully defining it.",
mf->file,line_number);
break;
/*:700*//*703:*/
#line 19406 "weaver-interface-metafont.cweb"

case ERROR_INVALID_CHAR:
{
uint32_t code_point;
if((unsigned char)mf->errno_str[0]<128){
code_point= (unsigned char)mf->errno_str[0];
mf->errno_str[1]= '\0';
}
else if((unsigned char)mf->errno_str[0]>=192&&
(unsigned char)mf->errno_str[0]<=223&&
(unsigned char)mf->errno_str[1]>=128&&
(unsigned char)mf->errno_str[1]<=191){
code_point= (unsigned char)mf->errno_str[1]-128;
code_point+= ((unsigned char)mf->errno_str[0]-192)*64;
mf->errno_str[2]= '\0';
}
else if((unsigned char)mf->errno_str[0]>=224&&
(unsigned char)mf->errno_str[0]<=239&&
(unsigned char)mf->errno_str[1]>=128&&
(unsigned char)mf->errno_str[1]<=191&&
(unsigned char)mf->errno_str[2]>=128&&
(unsigned char)mf->errno_str[2]<=191){
code_point= (unsigned char)mf->errno_str[2]-128;
code_point+= ((unsigned char)mf->errno_str[1]-128)*64;
code_point+= ((unsigned char)mf->errno_str[0]-224)*4096;
mf->errno_str[3]= '\0';
}
else if((unsigned char)mf->errno_str[0]>=240&&
(unsigned char)mf->errno_str[0]<=247&&
(unsigned char)mf->errno_str[1]>=128&&
(unsigned char)mf->errno_str[1]<=191&&
(unsigned char)mf->errno_str[2]>=128&&
(unsigned char)mf->errno_str[2]<=191&&
(unsigned char)mf->errno_str[3]>=128&&
(unsigned char)mf->errno_str[3]<=191){
code_point= (unsigned char)mf->errno_str[3]-128;
code_point+= ((unsigned char)mf->errno_str[2]-128)*64;
code_point+= ((unsigned char)mf->errno_str[1]-128)*4096;
code_point+= ((unsigned char)mf->errno_str[0]-240)*262144;
mf->errno_str[4]= '\0';
}
else{
fprintf(stderr,"%s:%s Invalid UTF-8 character in source code: '%s'.",
mf->file,line_number,mf->errno_str);
break;
}
fprintf(stderr,"%s:%s Unsupported UTF-8 character in source code: '%s' (U+%06X).",
mf->file,line_number,mf->errno_str,code_point);
break;
}
/*:703*//*706:*/
#line 19480 "weaver-interface-metafont.cweb"

case ERROR_INVALID_COMPARISON:
char expr_type[32];
tokenid_to_string(mf->errno_int,expr_type);
fprintf(stderr,
"%s:%s Tried to use '%s' to compare an "
"expression of type '%s', but such type is not comparable.",
mf->file,line_number,mf->errno_str,expr_type);
break;
/*:706*//*709:*/
#line 19515 "weaver-interface-metafont.cweb"

case ERROR_INVALID_DIMENSION_GLYPH:
int*size_buffer= (int*)(mf->errno_str);
fprintf(stderr,
"%s:%s Glyph with size %dx%d. Expected positive values for ",
mf->file,line_number,size_buffer[0],size_buffer[1]);
if(size_buffer[0]<=0&&size_buffer[1]<=0)
fprintf(stderr,"both width and height+depth.");
else if(size_buffer[0]<=0)
fprintf(stderr,"width.");
else if(size_buffer[1]<=0)
fprintf(stderr,"height+depth.");
break;
/*:709*//*712:*/
#line 19558 "weaver-interface-metafont.cweb"

case ERROR_INVALID_NAME:
char reason[128];
if(mf->errno_int==TYPE_NUMERIC||mf->errno_int==TYPE_STRING){
char type[16];
tokenid_to_string(mf->errno_int,type);
sprintf(reason,"it is a %s",type);
}
else if(mf->errno_int==TYPE_SYMBOLIC){
sprintf(reason,
"it's a special variable which cannot be shadowed by other declarations");
}
else
sprintf(reason,"it is a reserved keyword");
fprintf(stderr,"%s:%s You can not use '%s' as a variable name: %s.",
mf->file,line_number,mf->errno_str,reason);
break;
/*:712*//*715:*/
#line 19616 "weaver-interface-metafont.cweb"

case ERROR_INVALID_TENSION:
float*buf= (float*)(mf->errno_str);
fprintf(stderr,
"%s:%s Between path points (%g, %g) and (%g, %g) we found %s tension value '%g' smaller than minimal allowed '0.75'.",
mf->file,line_number,buf[0],buf[1],buf[2],buf[3],
(mf->errno_int==0)?"first":"second",buf[4]);
break;
/*:715*//*718:*/
#line 19649 "weaver-interface-metafont.cweb"

case ERROR_MISSING_EXPRESSION:
fprintf(stderr,"%s:%s Missing '%s' expression.",
mf->file,line_number,mf->errno_str);
break;
/*:718*//*721:*/
#line 19678 "weaver-interface-metafont.cweb"

case ERROR_MISSING_TOKEN:
fprintf(stderr,"%s:%s Missing matching token '%s'.",mf->file,line_number,
mf->errno_str);
break;
/*:721*//*724:*/
#line 19706 "weaver-interface-metafont.cweb"

case ERROR_NEGATIVE_LOGARITHM:
fprintf(stderr,"%s:%s Tried to compute logarithm of negative value '%s'.",
mf->file,line_number,mf->errno_str);
break;
/*:724*//*727:*/
#line 19734 "weaver-interface-metafont.cweb"

case ERROR_NEGATIVE_SQUARE_ROOT:
fprintf(stderr,"%s:%s Tried to compute square root of negative value '%s'.",
mf->file,line_number,mf->errno_str);
break;
/*:727*//*730:*/
#line 19761 "weaver-interface-metafont.cweb"

case ERROR_NESTED_BEGINCHAR:
fprintf(stderr,
"%s:%s You cannot nest 'beginchar' statements.",mf->file,line_number);
break;
/*:730*//*733:*/
#line 19813 "weaver-interface-metafont.cweb"

case ERROR_NO_MEMORY:
fprintf(stderr,"%s:%s Not enough memory for allocation.",mf->file,
line_number);
break;
/*:733*//*736:*/
#line 19844 "weaver-interface-metafont.cweb"

case ERROR_NO_PICKUP_PEN:
tokenid_to_string(mf->errno_int,mf->errno_str);
fprintf(stderr,"%s:%s After a 'pickup' command, you should use either a "
"'nullpen', 'pencircle', 'pensemicircle' or a pen variable.",
mf->file,line_number);
break;
/*:736*//*739:*/
#line 19871 "weaver-interface-metafont.cweb"

case ERROR_NONCYCLICAL_PEN:
fprintf(stderr,"%s:%s Tried to create a pen from non-cyclical path.",
mf->file,line_number);
break;
/*:739*//*742:*/
#line 19899 "weaver-interface-metafont.cweb"

case ERROR_NULL_VECTOR_ANGLE:
fprintf(stderr,"%s:%s You cannot use 'angle' operator in a null vector '(0, 0)'.",
mf->file,line_number);
break;
/*:742*//*745:*/
#line 19930 "weaver-interface-metafont.cweb"

case ERROR_OPENGL_FRAMEBUFFER:
fprintf(stderr,"%s:%s OpenGL error. Couldn't create framebuffer for image.",
mf->file,line_number);
switch(mf->errno_int){
case GL_FRAMEBUFFER_UNDEFINED:
printf(" Default framebuffer not defined.");
break;
case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
printf(" The framebuffer had incomplete attachment.");
break;
case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
printf(" The framebuffer had no image attached to it.");
break;
case GL_FRAMEBUFFER_UNSUPPORTED:
printf(" Depth and stencil attachments are not the same renderbuffer, "
"or internal image format is not supported by this implementation.");
break;
case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
printf("  GL_RENDERBUFFER_SAMPLES is not the same for all attached "
" renderbuffers or attached images are a mix of renderbuffers "
"and textures while the value of GL_RENDERBUFFER_SAMPLES "
"is not zero. ");
break;
default:
printf(" Unknown error.");
break;
}
break;
/*:745*//*748:*/
#line 19987 "weaver-interface-metafont.cweb"

case ERROR_RECURSIVE_RENDERCHAR:
fprintf(stderr,"%s:%s Recursive 'renderchar' detected. Glyph '%s' depends on "
"current glyph, but current glyph depends on '%s'.",mf->file,
line_number,mf->errno_str,mf->errno_str);
break;
/*:748*//*751:*/
#line 20021 "weaver-interface-metafont.cweb"

case ERROR_UNBALANCED_ENDING_TOKEN:
tokenid_to_string(mf->errno_int,mf->errno_str);
fprintf(stderr,"%s:%s Unexpected token \"%s\" found. You are trying to "
"close a compund command that were never opened or you have "
"two or more unbalanced compound statements.",mf->file,
line_number,mf->errno_str);
break;
/*:751*//*754:*/
#line 20052 "weaver-interface-metafont.cweb"

case ERROR_UNCLOSED_DELIMITER:
fprintf(stderr,"%s:%s Delimiter '%c' was not closed.",
mf->file,line_number,mf->errno_int);
break;
/*:754*//*757:*/
#line 20089 "weaver-interface-metafont.cweb"

case ERROR_UNCLOSED_STRING:
fprintf(stderr,"%s:%s Unclosed string \"%s\".",mf->file,
line_number,mf->errno_str);
break;
/*:757*//*760:*/
#line 20116 "weaver-interface-metafont.cweb"

case ERROR_UNDECLARED_VARIABLE:
fprintf(stderr,"%s:%s Variable '%s' was not declared.",mf->file,
line_number,mf->errno_str);
break;
/*:760*//*763:*/
#line 20150 "weaver-interface-metafont.cweb"

case ERROR_UNEXPECTED_TOKEN:
fprintf(stderr,"%s:%s We found '%s' token in a context where such "
"token makes no sense.",mf->file,line_number,mf->errno_str);
break;
/*:763*//*766:*/
#line 20179 "weaver-interface-metafont.cweb"

case ERROR_UNINITIALIZED_VARIABLE:
char var_type[32];
tokenid_to_string(mf->errno_int,var_type);
fprintf(stderr,"%s:%s Uninitialized %s variable '%s'.",
mf->file,line_number,var_type,mf->errno_str);
break;
/*:766*//*769:*/
#line 20210 "weaver-interface-metafont.cweb"

case ERROR_UNKNOWN_GLYPH_DEPENDENCY:
fprintf(stderr,
"%s:%s Command 'renderchar' created dependency of undefined glyph '%s'.",
mf->file,line_number,mf->errno_str);
break;
/*:769*//*772:*/
#line 20242 "weaver-interface-metafont.cweb"

case ERROR_UNKNOWN_EXPRESSION:
fprintf(stderr,"%s:%s Unknown %s expression.",mf->file,
line_number,list_of_keywords[mf->errno_int-10]);
break;
/*:772*//*775:*/
#line 20273 "weaver-interface-metafont.cweb"

case ERROR_UNKNOWN_STATEMENT:
fprintf(stderr,"%s:%s Unknown statement. Perhaps you misspelled some "
"operator, forgot an assignment or placed a ';' in the wrong "
"place.",mf->file,line_number);
break;
/*:775*//*778:*/
#line 20303 "weaver-interface-metafont.cweb"

case ERROR_UNOPENED_DELIMITER:
fprintf(stderr,"%s:%s Delimiter '%c' was not previously opened.",
mf->file,line_number,mf->errno_int);
break;
/*:778*//*781:*/
#line 20338 "weaver-interface-metafont.cweb"

case ERROR_UNSUPORTED_LENGTH_OPERAND:
if(mf->errno_int==-1)
fprintf(stderr,"%s:%s Operator 'length' expects a numeric, pair or path "
"expression as operand. Instead, we found an unknown expression.",
mf->file,line_number);
else{
tokenid_to_string(mf->errno_int,mf->errno_str);
fprintf(stderr,"%s:%s Operator 'length' expects a numeric, pair or path "
"expression as operand. Instead, we found a %s expression.",
mf->file,line_number,mf->errno_str);
}
break;
/*:781*//*784:*/
#line 20381 "weaver-interface-metafont.cweb"

case ERROR_WRONG_NUMBER_OF_PARAMETERS:
fprintf(stderr,
"%s:%s Statement '%s' expected %d parameters, but %d were given.",
mf->file,line_number,mf->errno_str,mf->errno_int>>8,
mf->errno_int&255);
break;
/*:784*//*787:*/
#line 20419 "weaver-interface-metafont.cweb"

case ERROR_WRONG_VARIABLE_TYPE:
char expected[32],found[32];
tokenid_to_string(mf->errno_int&255,expected);
tokenid_to_string(mf->errno_int>>8,found);
fprintf(stderr,"%s:%s Variable '%s' is a '%s' variable, but we expected a "
"'%s' variable.",mf->file,line_number,mf->errno_str,
found,expected);
break;
/*:787*/
#line 18864 "weaver-interface-metafont.cweb"

default:
fprintf(stderr,"%s:%s Unknown error.",mf->file,line_number);
}
if(mf->errno_character[0]!='\0'){
fprintf(stderr," (while rendering '%s')\n",mf->errno_character);
}
else
fprintf(stderr,"\n");
}
/*:667*/
#line 525 "weaver-interface-metafont.cweb"

/*:8*/
