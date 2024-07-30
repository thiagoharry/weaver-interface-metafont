/*8:*/
#line 442 "weaver-interface-metafont.tex"

#include "metafont.h"
/*40:*/
#line 1262 "weaver-interface-metafont.tex"

#include <stdio.h> 
/*:40*//*42:*/
#line 1286 "weaver-interface-metafont.tex"

#include <ctype.h> 
/*:42*//*62:*/
#line 1734 "weaver-interface-metafont.tex"

#include <string.h> 
/*:62*//*134:*/
#line 3258 "weaver-interface-metafont.tex"

#include <math.h> 
/*:134*//*160:*/
#line 3904 "weaver-interface-metafont.tex"

#include <complex.h> 
/*:160*//*190:*/
#line 5003 "weaver-interface-metafont.tex"

struct pen_variable;
/*:190*/
#line 444 "weaver-interface-metafont.tex"

/*9:*/
#line 481 "weaver-interface-metafont.tex"

#define INITIALIZE_IDENTITY_MATRIX(I) {\
  int _i;\
  for(_i =  0; _i < 9; _i++)\
    I[_i] =  ((_i%4)?(0.0):(1.0));\
}
/*:9*//*10:*/
#line 511 "weaver-interface-metafont.tex"

#define LINEAR_TRANSFORM_X(x, y, M) (x * M[0] + y * M[3] + M[6])
#define LINEAR_TRANSFORM_Y(x, y, M) (x * M[1] + y * M[4] + M[7])
/*:10*//*11:*/
#line 532 "weaver-interface-metafont.tex"

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
#line 562 "weaver-interface-metafont.tex"

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
#line 591 "weaver-interface-metafont.tex"

#define TRANSFORM_SCALE_X(M, s) {\
  M[0] =  M[0] * s;\
  M[3] =  M[3] * s;\
  M[6] =  M[6] * s;\
}
/*:13*//*14:*/
#line 610 "weaver-interface-metafont.tex"

#define TRANSFORM_SCALE_Y(M, s) {\
  M[1] =  M[1] * s;\
  M[4] =  M[4] * s;\
  M[7] =  M[7] * s;\
}
/*:14*//*15:*/
#line 623 "weaver-interface-metafont.tex"

#define TRANSFORM_SCALE(M, s) {\
  TRANSFORM_SCALE_X(M, s);\
  TRANSFORM_SCALE_Y(M, s);\
}
/*:15*//*16:*/
#line 644 "weaver-interface-metafont.tex"

#define TRANSFORM_SHIFT(M, a, b) {\
  M[6] =  M[6] + a;\
  M[7] =  M[7] + b;\
}
/*:16*//*17:*/
#line 662 "weaver-interface-metafont.tex"

#define TRANSFORM_SLANT(M, s) {\
  M[0] =  M[0] + s * M[1];\
  M[3] =  M[3] + s * M[4];\
  M[6] =  M[6] + s * M[7];\
}
/*:17*//*18:*/
#line 685 "weaver-interface-metafont.tex"

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
#line 752 "weaver-interface-metafont.tex"

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
#line 788 "weaver-interface-metafont.tex"

#define SUB_MUL_LINES(n, m, b, i, j, q) {\
  int _k;\
  b[i] -=  (q * b[j]);\
  for(_k =  0; _k < n; _k++){\
      m[i*n+_k] -=  (q * m[j*n+_k]);}}
/*:21*//*25:*/
#line 924 "weaver-interface-metafont.tex"

#if defined(_WIN32)
#define MUTEX_INIT(mutex) InitializeCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#define MUTEX_INIT(mutex) pthread_mutex_init(&mutex, NULL);
#elif defined(__EMSCRIPTEN__)
#define MUTEX_INIT(mutex)
#endif
/*:25*//*26:*/
#line 939 "weaver-interface-metafont.tex"

#if defined(_WIN32)
#define MUTEX_DESTROY(mutex) DeleteCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#define MUTEX_DESTROY(mutex) pthread_mutex_destroy(&mutex);
#elif defined(__EMSCRIPTEN__)
#define MUTEX_DESTROY(mutex)
#endif
/*:26*//*27:*/
#line 956 "weaver-interface-metafont.tex"

#if defined(_WIN32)
#define MUTEX_WAIT(mutex) EnterCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#define MUTEX_WAIT(mutex) pthread_mutex_lock(&mutex);
#elif defined(__EMSCRIPTEN__)
#define MUTEX_WAIT(mutex)
#endif
/*:27*//*28:*/
#line 971 "weaver-interface-metafont.tex"

#if defined(_WIN32)
#define MUTEX_SIGNAL(mutex) LeaveCriticalSection(mutex);
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#define MUTEX_SIGNAL(mutex) pthread_mutex_unlock(&mutex);
#elif defined(__EMSCRIPTEN__)
#define MUTEX_SIGNAL(mutex)
#endif
/*:28*//*77:*/
#line 2101 "weaver-interface-metafont.tex"

#define RAISE_GENERIC_ERROR(mf, cx, line, error_code) {\
  struct context *_cx =  cx;\
  if(!mf -> errno){\
    mf -> errno =  error_code;\
    mf -> errno_line =  line;\
    if(cx != NULL && _cx -> current_character[0] != '\0')\
      memcpy(mf -> errno_character, _cx -> current_character, 5);}}
/*:77*//*78:*/
#line 2121 "weaver-interface-metafont.tex"

#define RAISE_ERROR_NO_MEMORY(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NO_MEMORY);}
/*:78*//*79:*/
#line 2131 "weaver-interface-metafont.tex"

#define RAISE_ERROR_INVALID_CHAR(mf, cx, line, char) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_CHAR);\
    mf -> errno_int =  char;}}
/*:79*//*80:*/
#line 2143 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNCLOSED_STRING(mf, cx, line, str) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNCLOSED_STRING);\
    mf -> errno_str =  (char *) permanent_alloc(strlen(str)+1);\
    memcpy(mf -> errno_str, str, sizeof(str)+1);}}
/*:80*//*83:*/
#line 2203 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
#define OPTIONAL(x) x
#else
#define OPTIONAL(x) 0
#endif
/*:83*//*91:*/
#line 2433 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNKNOWN_STATEMENT(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNKNOWN_STATEMENT);}
/*:91*//*99:*/
#line 2583 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNEXPECTED_TOKEN(mf, cx, line, tok) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNEXPECTED_TOKEN);\
    mf -> errno_int =  tok;}}
/*:99*//*100:*/
#line 2599 "weaver-interface-metafont.tex"

#define RAISE_ERROR_EXPECTED_FOUND(mf, cx, line, expected, found) {\
  if(!mf -> errno){\
    mf -> errno_int =  found;\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_EXPECTED_FOUND);\
    if(expected >= 8){\
      size_t _s =  strlen(list_of_keywords[expected - 8]);\
      mf -> errno_str =  (char *) permanent_alloc(_s+1);\
      memcpy(mf -> errno_str, list_of_keywords[expected - 8], _s+1);\
    } else{\
      size_t _s =  strlen(token_names_not_in_list_of_keywords[expected]);\
      mf -> errno_str =  (char *) permanent_alloc(_s+1);\
      memcpy(mf -> errno_str, \
             token_names_not_in_list_of_keywords[expected], _s+1);}}}
/*:100*//*107:*/
#line 2746 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNFINISHED_STATEMENT(mf, cx, line, statement) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNFINISHED_STATEMENT);\
    mf -> errno_int =  statement;}}
/*:107*//*123:*/
#line 3021 "weaver-interface-metafont.tex"

#define RAISE_ERROR_INVALID_NAME(mf, cx, line, token_type) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_NAME);\
    mf -> errno_int =  token_type;}}
/*:123*//*137:*/
#line 3314 "weaver-interface-metafont.tex"

#define INTERNAL_NUMERIC_PT 0
#define INTERNAL_NUMERIC_CM 1
#define INTERNAL_NUMERIC_MM 2
#define INTERNAL_NUMERIC_W  3
#define INTERNAL_NUMERIC_H  4
#define INTERNAL_NUMERIC_D  5
/*:137*//*147:*/
#line 3492 "weaver-interface-metafont.tex"

#define INTERNAL_TRANSFORM_IDENTITY 0
/*:147*//*150:*/
#line 3547 "weaver-interface-metafont.tex"

#define UNINITIALIZED_FORMAT 0 
#define PROVISIONAL_FORMAT   1 
#define SUBPATH_FORMAT       2 
#define FINAL_FORMAT         3 
/*:150*//*192:*/
#line 5053 "weaver-interface-metafont.tex"

#define FLAG_CONVEX        1
#define FLAG_STRAIGHT      2
#define FLAG_CIRCULAR      4
#define FLAG_SEMICIRCULAR  8
#define FLAG_SQUARE       16
#define FLAG_NULL         32

/*:192*//*198:*/
#line 5226 "weaver-interface-metafont.tex"

#define INTERNAL_PEN_CURRENTPEN 0
#define INTERNAL_PEN_PENSQUARE  1
/*:198*//*208:*/
#line 5376 "weaver-interface-metafont.tex"

#define INTERNAL_PICTURE_CURRENTPICTURE 0
/*:208*//*217:*/
#line 5589 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNDECLARED_VARIABLE(mf, cx, line, name) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNDECLARED_VARIABLE);\
    mf -> errno_str =  (char *) permanent_alloc(strlen(name)+1);\
    memcpy(mf -> errno_str, name, strlen(name)+1);}}
/*:217*//*219:*/
#line 5630 "weaver-interface-metafont.tex"

#define VARIABLE_TO_STRING(name, type, str) {\
  size_t _s =  strlen(name) + 13;\
  str =  (char *) permanent_alloc(_s);\
  str[0] =  '\0';\
  strcat(str, "<");\
  strcat(str, name);\
  strcat(str, ":");\
  strcat(str, list_of_keywords[type - 8]);\
  strcat(str, ">");}
/*:219*//*220:*/
#line 5649 "weaver-interface-metafont.tex"

#define RAISE_ERROR_WRONG_VARIABLE_TYPE(mf, cx, line, name, type, expected) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_WRONG_VARIABLE_TYPE);\
    VARIABLE_TO_STRING(name, type, mf -> errno_str);\
    mf -> errno_int =  expected;}}
/*:220*//*222:*/
#line 5692 "weaver-interface-metafont.tex"

#define RAISE_ERROR_MISSING_EXPRESSION(mf, cx, line, type) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_MISSING_EXPRESSION);\
    mf -> errno_int =  type;}}
/*:222*//*229:*/
#line 5834 "weaver-interface-metafont.tex"

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
/*:229*//*230:*/
#line 5866 "weaver-interface-metafont.tex"

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
/*:230*//*232:*/
#line 5901 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNCLOSED_DELIMITER(mf, cx, line, delimiter) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNCLOSED_DELIMITER);\
    mf -> errno_int =  delimiter;}}
#define RAISE_ERROR_UNOPENED_DELIMITER(mf, cx, line, delimiter) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNOPENED_DELIMITER);\
    mf -> errno_int =  delimiter;}}
/*:232*//*234:*/
#line 5974 "weaver-interface-metafont.tex"

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
/*:234*//*237:*/
#line 6081 "weaver-interface-metafont.tex"

#define RAISE_ERROR_NEGATIVE_SQUARE_ROOT(mf, cx, line, number) {\
  if(!mf -> errno){\
    mf -> errno_str =  (char *) permanent_alloc(64);\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NEGATIVE_SQUARE_ROOT);\
    snprintf(mf -> errno_str, 63, "%g", number);\
    mf -> errno_str[63] =  '\0';}}
/*:237*//*244:*/
#line 6242 "weaver-interface-metafont.tex"

#define RAISE_ERROR_DIVISION_BY_ZERO(mf, cx, line) {\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_DIVISION_BY_ZERO);}
/*:244*//*251:*/
#line 6345 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNKNOWN_EXPRESSION(mf, cx, line, type) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNKNOWN_EXPRESSION);\
    mf -> errno_int =  type;}}
/*:251*//*256:*/
#line 6433 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNKNOWN_EXPRESSION_TYPE(mf, cx, line, type) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNKNOWN_EXPRESSION_TYPE);\
    mf -> errno_int =  type;}}
/*:256*//*263:*/
#line 6544 "weaver-interface-metafont.tex"

#define RAISE_ERROR_NEGATIVE_LOGARITHM(mf, cx, line, number) {\
  if(!mf -> errno){\
    mf -> errno_str =  (char *) permanent_alloc(64);\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NEGATIVE_LOGARITHM);\
    snprintf(mf -> errno_str, 63, "%g", number);\
    mf -> errno_str[63] =  '\0';}}
/*:263*//*278:*/
#line 6814 "weaver-interface-metafont.tex"

#define RAISE_ERROR_UNINITIALIZED_VARIABLE(mf, cx, line, name) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_UNINITIALIZED_VARIABLE);\
    mf -> errno_str =  (char *) permanent_alloc(strlen(name)+1);\
    memcpy(mf -> errno_str, name, strlen(name)+1);}}
/*:278*//*285:*/
#line 6951 "weaver-interface-metafont.tex"

#define RAISE_ERROR_EMPTY_DELIMITER(mf, cx, line, delimiter) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_EMPTY_DELIMITER);\
    mf -> errno_int =  delimiter;}}
/*:285*//*318:*/
#line 7827 "weaver-interface-metafont.tex"

#define RAISE_ERROR_ANGLE_OF_ORIGIN(mf, cx, line) {\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_ANGLE_OF_ORIGIN);}
/*:318*//*376:*/
#line 9405 "weaver-interface-metafont.tex"

#define RAISE_ERROR_DISCONTINUOUS_PATH(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_DISCONTINUOUS_PATH);}
/*:376*//*383:*/
#line 9632 "weaver-interface-metafont.tex"

#define RAISE_ERROR_INVALID_TENSION(mf, cx, line, value, position) {\
  if(!mf -> errno){\
    mf -> errno_str =  (char *) permanent_alloc(64);\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_TENSION);\
    snprintf(mf -> errno_str, 63, "%g", value);\
    mf -> errno_str[63] =  '\0';\
    mf -> errno_int =  position;}}
/*:383*//*459:*/
#line 11547 "weaver-interface-metafont.tex"

#define RAISE_ERROR_NONCYCLICAL_PEN(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NO_MEMORY);}
/*:459*//*489:*/
#line 12295 "weaver-interface-metafont.tex"

#define RAISE_ERROR_OPENGL_FRAMEBUFFER(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_OPENGL_FRAMEBUFFER);}
/*:489*//*533:*/
#line 13745 "weaver-interface-metafont.tex"

#define RAISE_ERROR_INVALID_COMPARISON(mf, cx, line) {\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_COMPARISON);}
/*:533*//*553:*/
#line 14553 "weaver-interface-metafont.tex"

#define RAISE_ERROR_MISSING_TOKEN(mf, cx, line, tok) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_MISSING_TOKEN);\
    mf -> errno_int =  tok;}}
/*:553*//*561:*/
#line 14719 "weaver-interface-metafont.tex"

#define DECLARE_PEN_EXTREMITIES() float _max_x =  -INFINITY, _min_x =  INFINITY,\
                                  _max_y =  -INFINITY, _min_y =  INFINITY;
/*:561*//*562:*/
#line 14731 "weaver-interface-metafont.tex"

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
/*:562*//*563:*/
#line 14755 "weaver-interface-metafont.tex"

#define UPDATE_PEN_EXTREMITIES() {\
  mf -> pen_lft =  _min_x;\
  mf -> pen_rt =  _max_x;\
  mf -> pen_top =  _max_y;\
  mf -> pen_bot =  _min_y;\
}
/*:563*//*568:*/
#line 15103 "weaver-interface-metafont.tex"

#define FLAG_ORIENTATION      64
#define FLAG_COUNTERCLOCKWISE 128
/*:568*//*593:*/
#line 16173 "weaver-interface-metafont.tex"

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
/*:593*//*594:*/
#line 16202 "weaver-interface-metafont.tex"

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
/*:594*//*595:*/
#line 16226 "weaver-interface-metafont.tex"

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
/*:595*//*620:*/
#line 17186 "weaver-interface-metafont.tex"

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
/*:620*//*670:*/
#line 18761 "weaver-interface-metafont.tex"

#define RAISE_ERROR_DUPLICATE_GLYPH(mf, cx, line, glyph) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_DUPLICATE_GLYPH);\
    mf -> errno_str =  (char *) permanent_alloc(strlen(glyph)+1);\
    memcpy(mf -> errno_str, glyph, strlen(glyph)+1);}}
#define RAISE_ERROR_MALFORMED_STATEMENT(mf, cx, line, stat) {\
  if(!mf -> errno){\
    RAISE_GENERIC_ERROR(mf, cx, line, ERROR_MALFORMED_STATEMENT);\
    mf -> errno_int =  stat;}}
#define RAISE_ERROR_NESTED_BEGINCHAR(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_NESTED_BEGINCHAR);}
/*:670*//*676:*/
#line 18974 "weaver-interface-metafont.tex"

#define RAISE_ERROR_INVALID_DIMENSION_GLYPH(mf, cx, line) {\
  RAISE_GENERIC_ERROR(mf, cx, line, ERROR_INVALID_DIMENSION_GLYPH);}
/*:676*/
#line 445 "weaver-interface-metafont.tex"

/*32:*/
#line 1065 "weaver-interface-metafont.tex"

enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,


/*37:*/
#line 1163 "weaver-interface-metafont.tex"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:37*//*86:*/
#line 2369 "weaver-interface-metafont.tex"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:86*//*110:*/
#line 2800 "weaver-interface-metafont.tex"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:110*//*213:*/
#line 5463 "weaver-interface-metafont.tex"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:213*//*225:*/
#line 5779 "weaver-interface-metafont.tex"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:225*//*226:*/
#line 5794 "weaver-interface-metafont.tex"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:226*//*239:*/
#line 6119 "weaver-interface-metafont.tex"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:239*//*246:*/
#line 6284 "weaver-interface-metafont.tex"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:246*//*271:*/
#line 6706 "weaver-interface-metafont.tex"

TYPE_NORMALDEVIATE,
/*:271*//*291:*/
#line 7120 "weaver-interface-metafont.tex"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:291*//*311:*/
#line 7716 "weaver-interface-metafont.tex"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:311*//*321:*/
#line 7897 "weaver-interface-metafont.tex"

TYPE_TRANSFORMED,
/*:321*//*340:*/
#line 8342 "weaver-interface-metafont.tex"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:340*//*347:*/
#line 8512 "weaver-interface-metafont.tex"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,
TYPE_STRAIGHT_JOIN,
/*:347*//*414:*/
#line 10361 "weaver-interface-metafont.tex"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:414*//*426:*/
#line 10766 "weaver-interface-metafont.tex"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:426*//*448:*/
#line 11335 "weaver-interface-metafont.tex"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:448*//*463:*/
#line 11663 "weaver-interface-metafont.tex"

TYPE_MAKEPATH,
/*:463*//*510:*/
#line 12931 "weaver-interface-metafont.tex"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:510*//*522:*/
#line 13321 "weaver-interface-metafont.tex"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:522*//*528:*/
#line 13501 "weaver-interface-metafont.tex"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:528*//*535:*/
#line 13778 "weaver-interface-metafont.tex"

TYPE_OR,
/*:535*//*541:*/
#line 13941 "weaver-interface-metafont.tex"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:541*//*549:*/
#line 14391 "weaver-interface-metafont.tex"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:549*//*557:*/
#line 14660 "weaver-interface-metafont.tex"

TYPE_PICKUP,
/*:557*//*634:*/
#line 17786 "weaver-interface-metafont.tex"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:634*//*640:*/
#line 17895 "weaver-interface-metafont.tex"

TYPE_DRAW,
TYPE_ERASE,
/*:640*/
#line 1070 "weaver-interface-metafont.tex"


TYPE_INVALID_TOKEN
};
/*:32*//*33:*/
#line 1084 "weaver-interface-metafont.tex"

struct numeric_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
float value;
};
/*:33*//*34:*/
#line 1099 "weaver-interface-metafont.tex"

struct string_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
char value[4];

struct _glyph*glyph;
};
/*:34*//*35:*/
#line 1124 "weaver-interface-metafont.tex"

struct symbolic_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
void*var;
char*value;
};
/*:35*//*36:*/
#line 1148 "weaver-interface-metafont.tex"

struct generic_token{
int type;
struct generic_token*next;
#if defined(W_DEBUG_METAFONT)
int line;
#endif
};
/*:36*//*74:*/
#line 2020 "weaver-interface-metafont.tex"

enum{
ERROR_NO_ERROR= 0,

/*76:*/
#line 2088 "weaver-interface-metafont.tex"

ERROR_NO_MEMORY,ERROR_INVALID_CHAR,ERROR_UNCLOSED_STRING,
/*:76*//*90:*/
#line 2425 "weaver-interface-metafont.tex"

ERROR_UNKNOWN_STATEMENT,
/*:90*//*98:*/
#line 2574 "weaver-interface-metafont.tex"

ERROR_UNEXPECTED_TOKEN,ERROR_EXPECTED_FOUND,
/*:98*//*106:*/
#line 2737 "weaver-interface-metafont.tex"

ERROR_UNFINISHED_STATEMENT,
/*:106*//*122:*/
#line 3012 "weaver-interface-metafont.tex"

ERROR_INVALID_NAME,
/*:122*//*216:*/
#line 5566 "weaver-interface-metafont.tex"

ERROR_UNDECLARED_VARIABLE,ERROR_WRONG_VARIABLE_TYPE,ERROR_MISSING_EXPRESSION,
/*:216*//*231:*/
#line 5892 "weaver-interface-metafont.tex"

ERROR_UNCLOSED_DELIMITER,ERROR_UNOPENED_DELIMITER,
/*:231*//*236:*/
#line 6072 "weaver-interface-metafont.tex"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:236*//*243:*/
#line 6233 "weaver-interface-metafont.tex"

ERROR_DIVISION_BY_ZERO,
/*:243*//*250:*/
#line 6336 "weaver-interface-metafont.tex"

ERROR_UNKNOWN_EXPRESSION,
/*:250*//*255:*/
#line 6423 "weaver-interface-metafont.tex"

ERROR_UNKNOWN_EXPRESSION_TYPE,
/*:255*//*262:*/
#line 6535 "weaver-interface-metafont.tex"

ERROR_NEGATIVE_LOGARITHM,
/*:262*//*277:*/
#line 6805 "weaver-interface-metafont.tex"

ERROR_UNINITIALIZED_VARIABLE,
/*:277*//*284:*/
#line 6942 "weaver-interface-metafont.tex"

ERROR_EMPTY_DELIMITER,
/*:284*//*317:*/
#line 7819 "weaver-interface-metafont.tex"

ERROR_ANGLE_OF_ORIGIN,
/*:317*//*375:*/
#line 9397 "weaver-interface-metafont.tex"

ERROR_DISCONTINUOUS_PATH,
/*:375*//*382:*/
#line 9622 "weaver-interface-metafont.tex"

ERROR_INVALID_TENSION,
/*:382*//*458:*/
#line 11538 "weaver-interface-metafont.tex"

ERROR_NONCYCLICAL_PEN,
/*:458*//*488:*/
#line 12287 "weaver-interface-metafont.tex"

ERROR_OPENGL_FRAMEBUFFER,
/*:488*//*532:*/
#line 13737 "weaver-interface-metafont.tex"

ERROR_INVALID_COMPARISON,
/*:532*//*552:*/
#line 14543 "weaver-interface-metafont.tex"

ERROR_MISSING_TOKEN,
/*:552*//*669:*/
#line 18749 "weaver-interface-metafont.tex"

ERROR_DUPLICATE_GLYPH,ERROR_MALFORMED_STATEMENT,ERROR_NESTED_BEGINCHAR,
/*:669*//*675:*/
#line 18966 "weaver-interface-metafont.tex"

ERROR_INVALID_DIMENSION_GLYPH,
/*:675*/
#line 2024 "weaver-interface-metafont.tex"


ERROR_UNKNOWN
};
/*:74*//*112:*/
#line 2838 "weaver-interface-metafont.tex"


struct variable{
int type;
struct variable*next;
};
/*:112*//*113:*/
#line 2857 "weaver-interface-metafont.tex"

struct named_variable{
char*name;
struct named_variable*next;
struct variable*var;
};
/*:113*//*132:*/
#line 3231 "weaver-interface-metafont.tex"

struct numeric_variable{
int type;
void*next;
float value;
};
/*:132*//*140:*/
#line 3380 "weaver-interface-metafont.tex"

struct pair_variable{
int type;
void*next;
float x,y;
};
/*:140*//*142:*/
#line 3424 "weaver-interface-metafont.tex"

struct transform_variable{
int type;
void*next;
float value[9];
};
/*:142*//*149:*/
#line 3526 "weaver-interface-metafont.tex"

struct path_variable{
int type;
void*next;
bool permanent;
bool cyclic;
int length,number_of_points,number_of_missing_directions;
struct path_points*points;
};
/*:149*//*151:*/
#line 3592 "weaver-interface-metafont.tex"

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
/*:151*//*191:*/
#line 5009 "weaver-interface-metafont.tex"

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
/*:191*//*202:*/
#line 5292 "weaver-interface-metafont.tex"

struct picture_variable{
int type;
void*next;
int width,height;
GLuint texture;
};
/*:202*//*211:*/
#line 5412 "weaver-interface-metafont.tex"

struct boolean_variable{
int type;
void*next;
short value;
};
/*:211*//*581:*/
#line 15704 "weaver-interface-metafont.tex"

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
/*589:*/
#line 16041 "weaver-interface-metafont.tex"

struct polygon_vertex*succ;
/*:589*//*598:*/
#line 16403 "weaver-interface-metafont.tex"

struct polygon_vertex*pred;
/*:598*/
#line 15715 "weaver-interface-metafont.tex"

};
/*:581*//*582:*/
#line 15725 "weaver-interface-metafont.tex"

#define XMONOTONE_LEQ(v1, v2) ((v1->x==v2->x)?(v1->y<=v2->y):(v1->x<=v2->x))
/*:582*//*597:*/
#line 16382 "weaver-interface-metafont.tex"

#define TYPE_UNKNOWN_VERTEX  0
#define TYPE_REGULAR_VERTEX  4
#define TYPE_BEGIN_VERTEX    8
#define TYPE_END_VERTEX     12
#define TYPE_SPLIT_VERTEX   16
#define TYPE_MERGE_VERTEX   20
#define GET_VERTEX_TYPE(v) (((v -> flag) >> 2) << 2)
/*:597*//*605:*/
#line 16640 "weaver-interface-metafont.tex"

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
/*:605*//*661:*/
#line 18418 "weaver-interface-metafont.tex"

struct _glyph{
struct generic_token*begin,*end;
int width,height,depth;
int italic_correction;
struct kerning*kern;
GLuint texture;
bool need_rendering;
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
                            }
/*:661*//*662:*/
#line 18445 "weaver-interface-metafont.tex"

struct kerning{
char next_char[5];
int kern;
struct kerning*next;
};
/*:662*/
#line 446 "weaver-interface-metafont.tex"

/*29:*/
#line 991 "weaver-interface-metafont.tex"

static void*(*temporary_alloc)(size_t);
static void(*temporary_free)(void*);
static void*(*permanent_alloc)(size_t);
static void(*permanent_free)(void*);
static uint64_t(*random_func)(void);
static int dpi;
/*:29*//*60:*/
#line 1685 "weaver-interface-metafont.tex"

static char*list_of_keywords[]= {
/*87:*/
#line 2382 "weaver-interface-metafont.tex"

"begingroup","endgroup","if","fi","beginchar","endchar",
/*:87*//*111:*/
#line 2814 "weaver-interface-metafont.tex"

"boolean","path","pen","picture","transform","pair","numeric",
/*:111*//*214:*/
#line 5472 "weaver-interface-metafont.tex"

"=",":=",
/*:214*//*227:*/
#line 5805 "weaver-interface-metafont.tex"

"+","-","++","+-+","[","]","{","}",
/*:227*//*240:*/
#line 6126 "weaver-interface-metafont.tex"

"*","/",
/*:240*//*247:*/
#line 6297 "weaver-interface-metafont.tex"

"length","sqrt","sind","cosd","log","exp","floor","uniformdeviate",
/*:247*//*272:*/
#line 6712 "weaver-interface-metafont.tex"

"normaldeviate",
/*:272*//*292:*/
#line 7132 "weaver-interface-metafont.tex"

"rotated","scaled","shifted","slanted","xscaled","yscaled",
"zscaled",
/*:292*//*312:*/
#line 7726 "weaver-interface-metafont.tex"

"xpart","ypart","angle",
/*:312*//*322:*/
#line 7905 "weaver-interface-metafont.tex"

"transformed",
/*:322*//*341:*/
#line 8353 "weaver-interface-metafont.tex"

"xxpart","xypart","yxpart","yypart",
/*:341*//*348:*/
#line 8529 "weaver-interface-metafont.tex"

"cycle","&","..","tension","and","atleast","controls","curl","--",
/*:348*//*415:*/
#line 10372 "weaver-interface-metafont.tex"

"reverse","subpath","of",
/*:415*//*427:*/
#line 10776 "weaver-interface-metafont.tex"

"point","precontrol","postcontrol",
/*:427*//*449:*/
#line 11347 "weaver-interface-metafont.tex"

"nullpen","pencircle","pensemicircle","makepen",
/*:449*//*464:*/
#line 11671 "weaver-interface-metafont.tex"

"makepath",
/*:464*//*511:*/
#line 12940 "weaver-interface-metafont.tex"

"nullpicture","subpicture",
/*:511*//*523:*/
#line 13331 "weaver-interface-metafont.tex"

"totalweight","width","height",
/*:523*//*529:*/
#line 13513 "weaver-interface-metafont.tex"

"<","<=",">",">=","<>",
/*:529*//*536:*/
#line 13786 "weaver-interface-metafont.tex"

"or",
/*:536*//*542:*/
#line 13953 "weaver-interface-metafont.tex"

"true","false","odd","not",
/*:542*//*550:*/
#line 14401 "weaver-interface-metafont.tex"

"elseif","else",":",
/*:550*//*558:*/
#line 14666 "weaver-interface-metafont.tex"

"pickup",
/*:558*//*635:*/
#line 17797 "weaver-interface-metafont.tex"

"bot","top","lft","rt",
/*:635*//*641:*/
#line 17902 "weaver-interface-metafont.tex"

"draw","erase",
/*:641*/
#line 1687 "weaver-interface-metafont.tex"

NULL};
/*:60*//*101:*/
#line 2629 "weaver-interface-metafont.tex"

static char*token_names_not_in_list_of_keywords[]= {
"nil","<Numeric>","<String>","<Variable Name>","(",")",",",";"};
/*:101*//*473:*/
#line 11962 "weaver-interface-metafont.tex"

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
/*:473*//*476:*/
#line 12017 "weaver-interface-metafont.tex"

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
/*:476*//*477:*/
#line 12036 "weaver-interface-metafont.tex"

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
/*:477*//*493:*/
#line 12439 "weaver-interface-metafont.tex"

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
/*:493*//*574:*/
#line 15232 "weaver-interface-metafont.tex"

static GLuint pensquare_vbo;
/*:574*//*642:*/
#line 17919 "weaver-interface-metafont.tex"

static GLuint currentpicture_fb;
/*:642*//*646:*/
#line 17999 "weaver-interface-metafont.tex"

static GLint previous_fb;
/*:646*//*649:*/
#line 18041 "weaver-interface-metafont.tex"

static const char pen_vertex_shader[]= 
"#version 100\n"
"attribute vec4 vertex_data;\n"
"uniform mat3 model_view_matrix;\n"
"void main(){\n"
"  highp vec3 coord;\n"
"  coord = vec3(vertex_data.xy, 1.0) * model_view_matrix;\n"
"  gl_Position = vec4(coord.x, coord.y, 0.0, 1.0);\n"
"}\n";
/*:649*//*650:*/
#line 18058 "weaver-interface-metafont.tex"

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
/*:650*/
#line 447 "weaver-interface-metafont.tex"

/*19:*/
#line 734 "weaver-interface-metafont.tex"

void solve_linear_system(int n,double*m,double*b,double*x);
/*:19*//*67:*/
#line 1881 "weaver-interface-metafont.tex"

struct metafont*init_metafont(char*filename);
struct context*init_context(struct metafont*mf);
void destroy_context(struct metafont*mf,struct context*cx);
/*:67*//*84:*/
#line 2246 "weaver-interface-metafont.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
struct generic_token*begin_list,
struct generic_token*end_list);
/*:84*//*88:*/
#line 2390 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*,struct context*,
struct generic_token*begin,struct generic_token**end);
/*:88*//*95:*/
#line 2496 "weaver-interface-metafont.tex"

bool begin_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok);
/*:95*//*126:*/
#line 3074 "weaver-interface-metafont.tex"

struct variable*insert_variable(struct metafont*mf,
int type,
struct symbolic_token*variable,
struct variable**target);
/*:126*//*128:*/
#line 3129 "weaver-interface-metafont.tex"

struct variable*insert_named_global_variable(struct metafont*mf,
int type,
struct symbolic_token*var);
/*:128*//*130:*/
#line 3190 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer);
/*:130*//*155:*/
#line 3682 "weaver-interface-metafont.tex"

void path_recursive_free(void(*free_func)(void*),
struct path_variable*path,
bool free_first_pointer);
/*:155*//*157:*/
#line 3741 "weaver-interface-metafont.tex"

bool recursive_copy_points(struct metafont*mf,struct context*cx,
void*(*alloc)(size_t),
struct path_variable**target,
struct path_variable*source,
bool alloc_target);
void recursive_aux_copy(struct path_points**dst,
struct path_variable*origin,int*missing_directions,
struct path_points**previous_point);
/*:157*//*161:*/
#line 3929 "weaver-interface-metafont.tex"

void convert_to_final(struct path_variable*p);
double compute_f(double theta,double phi);
/*:161*//*165:*/
#line 4014 "weaver-interface-metafont.tex"

void correct_tension(double p0_x,double p0_y,double p1_x,double p1_y,
double d0_x,double d0_y,double d1_x,double d1_y,
float*control_x,float*control_y);
/*:165*//*167:*/
#line 4059 "weaver-interface-metafont.tex"

double get_angle(double v_x,double v_y,double c0_x,double c0_y,
double c1_x,double c1_y);
/*:167*//*171:*/
#line 4219 "weaver-interface-metafont.tex"

bool find_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p);
/*:171*//*177:*/
#line 4387 "weaver-interface-metafont.tex"

bool fill_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p,int begin,int end);
/*:177*//*179:*/
#line 4462 "weaver-interface-metafont.tex"

bool fill_cyclic_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p,int begin,
int end);
/*:179*//*188:*/
#line 4942 "weaver-interface-metafont.tex"

bool normalize_path(struct metafont*mf,struct context*cx,
struct path_variable*path);
/*:188*//*228:*/
#line 5814 "weaver-interface-metafont.tex"

bool eval_numeric_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin_expression,
struct generic_token*end_token_list,
struct numeric_variable*result);
/*:228*//*241:*/
#line 6137 "weaver-interface-metafont.tex"

bool eval_numeric_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result);
/*:241*//*248:*/
#line 6305 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result);
/*:248*//*273:*/
#line 6723 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result);
/*:273*//*289:*/
#line 7035 "weaver-interface-metafont.tex"

bool eval_pair_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result);
/*:289*//*293:*/
#line 7141 "weaver-interface-metafont.tex"

bool eval_pair_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result);
/*:293*//*304:*/
#line 7442 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result);
/*:304*//*323:*/
#line 7922 "weaver-interface-metafont.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result);
/*:323*//*325:*/
#line 7946 "weaver-interface-metafont.tex"

bool eval_transform_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result);
/*:325*//*335:*/
#line 8161 "weaver-interface-metafont.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result);
/*:335*//*349:*/
#line 8544 "weaver-interface-metafont.tex"

int count_path_joins(struct generic_token*begin,struct generic_token*end);
/*:349*//*351:*/
#line 8592 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:351*//*365:*/
#line 9087 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y);
/*:365*//*390:*/
#line 9828 "weaver-interface-metafont.tex"

bool eval_path_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:390*//*392:*/
#line 9915 "weaver-interface-metafont.tex"

bool eval_path_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:392*//*395:*/
#line 10053 "weaver-interface-metafont.tex"

void path_rotate(struct path_variable*p,double sin_theta,
double cos_theta);
/*:395*//*398:*/
#line 10100 "weaver-interface-metafont.tex"

void path_xyscale(struct path_variable*p,float x,float y);
/*:398*//*401:*/
#line 10145 "weaver-interface-metafont.tex"

void path_shift(struct path_variable*p,float x,float y);
/*:401*//*404:*/
#line 10185 "weaver-interface-metafont.tex"

void path_slant(struct path_variable*p,float s);
/*:404*//*409:*/
#line 10262 "weaver-interface-metafont.tex"

void path_zscale(struct path_variable*p,float x,float y);
/*:409*//*412:*/
#line 10312 "weaver-interface-metafont.tex"

void path_transform(struct path_variable*p,float*M);
/*:412*//*416:*/
#line 10387 "weaver-interface-metafont.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result);
/*:416*//*419:*/
#line 10453 "weaver-interface-metafont.tex"

bool reverse_path(struct metafont*mf,struct context*cx,
struct path_variable*dst,
struct path_variable*origin);
/*:419*//*428:*/
#line 10792 "weaver-interface-metafont.tex"

struct path_points*get_point(struct path_variable*v,int n);
/*:428*//*430:*/
#line 10822 "weaver-interface-metafont.tex"

struct path_points*_get_point(struct path_variable*v,int n,int*count);
/*:430*//*434:*/
#line 10972 "weaver-interface-metafont.tex"

bool assign_pen_variable(struct metafont*mf,
struct pen_variable*target,
struct pen_variable*source);
/*:434*//*436:*/
#line 11036 "weaver-interface-metafont.tex"

bool eval_pen_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result);
/*:436*//*438:*/
#line 11090 "weaver-interface-metafont.tex"

bool eval_pen_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result);
/*:438*//*450:*/
#line 11355 "weaver-interface-metafont.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result);
/*:450*//*461:*/
#line 11570 "weaver-interface-metafont.tex"

int read_flags(struct path_variable*path);
/*:461*//*478:*/
#line 12055 "weaver-interface-metafont.tex"

GLuint compile_shader_program(const char*vertex_shader_source,
const char*fragment_shader_source);
/*:478*//*482:*/
#line 12142 "weaver-interface-metafont.tex"

bool get_new_framebuffer(GLuint*new_framebuffer,GLuint*new_texture,
int width,int height);
/*:482*//*484:*/
#line 12179 "weaver-interface-metafont.tex"

void render_picture(struct picture_variable*pic,float*matrix,int dst_width,
int dst_height,bool clear_background);

void print_picture(struct picture_variable*pic);
/*:484*//*486:*/
#line 12240 "weaver-interface-metafont.tex"

bool assign_picture_variable(struct metafont*mf,
struct picture_variable*target,
struct picture_variable*source);
/*:486*//*491:*/
#line 12334 "weaver-interface-metafont.tex"

bool eval_picture_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result);
/*:491*//*498:*/
#line 12609 "weaver-interface-metafont.tex"

bool eval_picture_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result,
float*matrix,bool*modified);
/*:498*//*508:*/
#line 12813 "weaver-interface-metafont.tex"

bool apply_image_transformation(struct metafont*mf,
struct picture_variable*dst,
struct picture_variable*origin,
float*matrix);
/*:508*//*512:*/
#line 12948 "weaver-interface-metafont.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result);
/*:512*//*530:*/
#line 13521 "weaver-interface-metafont.tex"

bool eval_boolean_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:530*//*537:*/
#line 13794 "weaver-interface-metafont.tex"

bool eval_boolean_tertiary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:537*//*539:*/
#line 13865 "weaver-interface-metafont.tex"

bool eval_boolean_secondary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:539*//*543:*/
#line 13961 "weaver-interface-metafont.tex"

bool eval_boolean_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct boolean_variable*result);
/*:543*//*545:*/
#line 14089 "weaver-interface-metafont.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_secondary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
int get_tertiary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr);
/*:545*//*564:*/
#line 14777 "weaver-interface-metafont.tex"

void pencircular_extremity_points(struct metafont*mf,float*matrix,
bool fullcircle);
/*:564*//*566:*/
#line 14976 "weaver-interface-metafont.tex"

void path_extremity_points(struct metafont*mf,struct path_variable*p,
float*matrix);
/*:566*//*569:*/
#line 15118 "weaver-interface-metafont.tex"

bool is_pen_counterclockwise(struct pen_variable*pen);
/*:569*//*571:*/
#line 15185 "weaver-interface-metafont.tex"

bool triangulate_pen(struct metafont*mf,struct pen_variable*pen,
float*transform_matrix);
/*:571*//*583:*/
#line 15734 "weaver-interface-metafont.tex"

void destroy_vertex_linked_list(struct polygon_vertex*poly);
/*:583*//*585:*/
#line 15760 "weaver-interface-metafont.tex"

struct polygon_vertex*polygon_from_pen(struct metafont*mf,
struct pen_variable*,
float*transform_matrix,
int*number_of_vertices);
/*:585*//*587:*/
#line 15919 "weaver-interface-metafont.tex"

bool is_xmonotone(struct polygon_vertex*poly);
/*:587*//*591:*/
#line 16074 "weaver-interface-metafont.tex"

static bool triangulate_xmonotone_polygon(struct polygon_vertex*p,
float**triangles,
int*number_of_triangles,
struct polygon_vertex**stack);
/*:591*//*601:*/
#line 16517 "weaver-interface-metafont.tex"

void prepare_non_monotonous(struct polygon_vertex*p,int number_of_vertices);
/*:601*//*603:*/
#line 16585 "weaver-interface-metafont.tex"

static bool is_turning_left(struct polygon_vertex*p1,
struct polygon_vertex*p2,
struct polygon_vertex*p3);
/*:603*//*606:*/
#line 16669 "weaver-interface-metafont.tex"

static struct polygon_edge*insert_polygon_edge(struct polygon_edge**,
float,float,float,float,
struct polygon_vertex*,
bool(*)(struct polygon_edge*,
struct polygon_edge*),
bool(*)(struct polygon_edge*,
struct polygon_edge*));
/*:606*//*608:*/
#line 16735 "weaver-interface-metafont.tex"

static bool leq_by_vertex(struct polygon_edge*,struct polygon_edge*);
/*:608*//*610:*/
#line 16805 "weaver-interface-metafont.tex"

static bool eq_by_vertex(struct polygon_edge*,struct polygon_edge*);
/*:610*//*612:*/
#line 16824 "weaver-interface-metafont.tex"

static struct polygon_edge*remove_polygon_edge(struct polygon_edge**,
float,float,float,float,
bool(*)(struct polygon_edge*,
struct polygon_edge*),
bool(*)(struct polygon_edge*,
struct polygon_edge*));
/*:612*//*614:*/
#line 16898 "weaver-interface-metafont.tex"

static struct polygon_edge*find_edge_below(struct polygon_edge*,
float,float);
/*:614*//*616:*/
#line 16936 "weaver-interface-metafont.tex"

static bool cut_polygon(struct polygon_vertex*v1,struct polygon_vertex*v2,
struct polygon_vertex**new1,
struct polygon_vertex**new2);
/*:616*//*618:*/
#line 17083 "weaver-interface-metafont.tex"

static void aux_update_flags(struct polygon_vertex*v);
/*:618*//*621:*/
#line 17214 "weaver-interface-metafont.tex"

static bool leq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2);
static bool eq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2);
/*:621*//*624:*/
#line 17294 "weaver-interface-metafont.tex"

static void triangulate_polygon_tree(struct polygon_edge*tree,
float**triangles,
int*number_of_triangles,
struct polygon_vertex**buffer);
/*:624*//*654:*/
#line 18143 "weaver-interface-metafont.tex"

bool drawing_commands(struct metafont*mf,struct context*cx,
struct path_variable*path,unsigned int flags);
/*:654*//*656:*/
#line 18243 "weaver-interface-metafont.tex"

void drawpoint(struct metafont*mf,struct pen_variable*pen,
struct picture_variable*pic,float x,float y,float*matrix,
bool erasing);
/*:656*//*665:*/
#line 18486 "weaver-interface-metafont.tex"

static struct _glyph*get_glyph(struct metafont*mf,unsigned char*utf8,
bool create_if_not_exist);
/*:665*/
#line 448 "weaver-interface-metafont.tex"

/*22:*/
#line 835 "weaver-interface-metafont.tex"

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
/*:22*//*38:*/
#line 1195 "weaver-interface-metafont.tex"

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
/*:38*//*39:*/
#line 1221 "weaver-interface-metafont.tex"

void lexer(struct metafont*mf,char*path,struct generic_token**first_token,
struct generic_token**last_token){
FILE*fp;
char c;
int line= 1;
*first_token= NULL;
*last_token= NULL;
fp= fopen(path,"r");
if(fp==NULL)
return;
while((c= fgetc(fp))!=EOF){
char next_char= fgetc(fp);
ungetc(next_char,fp);
if(c=='\n'){
line++;
continue;
}
/*41:*/
#line 1275 "weaver-interface-metafont.tex"

if(c==' '||c=='\t'||
(c=='.'&&next_char!='.'&&!isdigit(next_char)))
continue;
/*:41*/
#line 1239 "weaver-interface-metafont.tex"

/*43:*/
#line 1296 "weaver-interface-metafont.tex"

if(c=='%'){
do{
c= fgetc(fp);
}while(c!='\n'&&c!=EOF);
ungetc(c,fp);
continue;
}
/*:43*/
#line 1240 "weaver-interface-metafont.tex"

/*44:*/
#line 1313 "weaver-interface-metafont.tex"

if((c=='.'&&isdigit(next_char))||isdigit(c)){
char buffer[256];
struct numeric_token*new_token= 
(struct numeric_token*)permanent_alloc(sizeof(struct numeric_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return;
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
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
/*:44*/
#line 1241 "weaver-interface-metafont.tex"

/*45:*/
#line 1368 "weaver-interface-metafont.tex"

if(c==34){
struct string_token*new_token= 
(struct string_token*)permanent_alloc(sizeof(struct string_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return;
}
new_token->type= TYPE_STRING;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
int i= 0,prev;
do{
prev= c;
c= fgetc(fp);
if(i<5&&(c!='\\'||prev=='\\')){
new_token->value[i]= c;
i++;
}
}while((c!=34||prev=='\\')&&c!='\n'&&c!=EOF);
i--;
new_token->value[i]= '\0';
if(c=='\n'||c==EOF){
RAISE_ERROR_UNCLOSED_STRING(mf,NULL,line,new_token->value);
if(permanent_free!=NULL)
permanent_free(new_token);
free_token_list(*first_token);
*first_token= *last_token= NULL;
return;
}
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
/*:45*/
#line 1242 "weaver-interface-metafont.tex"

/*46:*/
#line 1418 "weaver-interface-metafont.tex"

if(c=='('||c==')'||c==','||c==';'){
struct generic_token*new_token= 
(struct generic_token*)permanent_alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return;
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
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
/*:46*/
#line 1243 "weaver-interface-metafont.tex"

/*47:*/
#line 1456 "weaver-interface-metafont.tex"

{
char buffer[256];
int i= 0;
buffer[0]= '\0';

/*48:*/
#line 1488 "weaver-interface-metafont.tex"

if(isalpha(c)||c=='_'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(isalpha(c)||c=='_'||isdigit(c));
ungetc(c,fp);
buffer[i]= '\0';
}
/*:48*/
#line 1462 "weaver-interface-metafont.tex"

/*49:*/
#line 1505 "weaver-interface-metafont.tex"

else if(c=='>'||c=='<'||c=='='||c==':'||c=='|'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='>'||c=='<'||c=='='||c==':'||c=='|');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:49*/
#line 1463 "weaver-interface-metafont.tex"

/*50:*/
#line 1521 "weaver-interface-metafont.tex"

else if(c=='`'||c=='\''){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='`'||c=='\'');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:50*/
#line 1464 "weaver-interface-metafont.tex"

/*51:*/
#line 1537 "weaver-interface-metafont.tex"

else if(c=='+'||c=='-'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='+'||c=='-');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:51*/
#line 1465 "weaver-interface-metafont.tex"

/*52:*/
#line 1553 "weaver-interface-metafont.tex"

else if(c=='\\'||c=='/'||c=='*'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='\\'||c=='/'||c=='*');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:52*/
#line 1466 "weaver-interface-metafont.tex"

/*53:*/
#line 1569 "weaver-interface-metafont.tex"

else if(c=='?'||c=='!'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='?'||c=='!');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:53*/
#line 1467 "weaver-interface-metafont.tex"

/*54:*/
#line 1585 "weaver-interface-metafont.tex"

else if(c=='#'||c=='&'||c=='@'||c=='$'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='#'||c=='&'||c=='@'||c=='$');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:54*/
#line 1468 "weaver-interface-metafont.tex"

/*55:*/
#line 1601 "weaver-interface-metafont.tex"

else if(c=='^'||c=='~'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='^'||c=='~');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:55*/
#line 1469 "weaver-interface-metafont.tex"

/*56:*/
#line 1617 "weaver-interface-metafont.tex"

else if(c=='['){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='[');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:56*/
#line 1470 "weaver-interface-metafont.tex"

/*57:*/
#line 1633 "weaver-interface-metafont.tex"

else if(c==']'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c==']');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:57*/
#line 1471 "weaver-interface-metafont.tex"

/*58:*/
#line 1649 "weaver-interface-metafont.tex"

else if(c=='{'||c=='}'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='{'||c=='}');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:58*/
#line 1472 "weaver-interface-metafont.tex"

/*59:*/
#line 1665 "weaver-interface-metafont.tex"

else if(c=='.'){
do{
buffer[i]= c;
i++;
c= fgetc(fp);
}while(c=='.');
ungetc(c,fp);
buffer[i]= '\0';
}
/*:59*/
#line 1473 "weaver-interface-metafont.tex"


/*61:*/
#line 1698 "weaver-interface-metafont.tex"

{
int i,token_type= 0;
for(i= 0;list_of_keywords[i]!=NULL;i++)
if(!strcmp(buffer,list_of_keywords[i]))
token_type= i+8;
if(token_type!=0){
struct generic_token*new_token= 
(struct generic_token*)permanent_alloc(sizeof(struct generic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return;
}
new_token->type= token_type;
new_token->next= NULL;
#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
if(*first_token==NULL)
*first_token= *last_token= (struct generic_token*)new_token;
else{
(*last_token)->next= (struct generic_token*)new_token;
*last_token= (struct generic_token*)new_token;
}
continue;
}
}
/*:61*/
#line 1475 "weaver-interface-metafont.tex"

/*63:*/
#line 1744 "weaver-interface-metafont.tex"

if(buffer[0]!='\0'){
buffer[255]= '\0';
size_t buffer_size= strlen(buffer)+1;
struct symbolic_token*new_token= 
(struct symbolic_token*)permanent_alloc(sizeof(struct symbolic_token));
if(new_token==NULL){
free_token_list(*first_token);
*first_token= *last_token= NULL;
RAISE_ERROR_NO_MEMORY(mf,NULL,line);
return;
}
new_token->type= TYPE_SYMBOLIC;
new_token->next= NULL;
new_token->var= NULL;


/*139:*/
#line 3340 "weaver-interface-metafont.tex"

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
else if(!strcmp(buffer,"w")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_W]);
}
else if(!strcmp(buffer,"h")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_H]);
}
else if(!strcmp(buffer,"d")){
new_token->var= 
&(((struct numeric_variable*)
mf->internal_numeric_variables)[INTERNAL_NUMERIC_D]);
}
/*:139*//*148:*/
#line 3502 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"identity"))
new_token->var= 
&(mf->internal_transform_variables[INTERNAL_TRANSFORM_IDENTITY]);
/*:148*//*200:*/
#line 5251 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"currentpen"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN]);
else if(!strcmp(buffer,"pensquare"))
new_token->var= 
&(mf->internal_pen_variables[INTERNAL_PEN_PENSQUARE]);
/*:200*//*210:*/
#line 5399 "weaver-interface-metafont.tex"

else if(!strcmp(buffer,"currentpicture"))
new_token->var= 
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE]);
/*:210*/
#line 1761 "weaver-interface-metafont.tex"

#if defined(W_DEBUG_METAFONT)
new_token->line= line;
#endif
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
/*:63*/
#line 1476 "weaver-interface-metafont.tex"

}
/*:47*/
#line 1244 "weaver-interface-metafont.tex"


RAISE_ERROR_INVALID_CHAR(mf,NULL,line,c);
free_token_list(first_token);
*first_token= NULL;
*last_token= NULL;
return;
}
fclose(fp);
}
/*:39*//*64:*/
#line 1822 "weaver-interface-metafont.tex"

bool eval_program(struct metafont*mf,struct context*cx,
struct generic_token*first_token,
struct generic_token*last_token){
if(first_token==NULL)
return true;
if(!eval_list_of_statements(mf,cx,first_token,last_token))
return false;

/*71:*/
#line 1963 "weaver-interface-metafont.tex"

mf->loading= false;
/*:71*//*109:*/
#line 2769 "weaver-interface-metafont.tex"

if(cx->nesting_level> 0){
RAISE_ERROR_UNFINISHED_STATEMENT(mf,cx,
OPTIONAL(cx->end_token_stack->line),
cx->end_token_stack->type);
return false;
}
/*:109*/
#line 1831 "weaver-interface-metafont.tex"

return true;
}
/*:64*//*68:*/
#line 1894 "weaver-interface-metafont.tex"

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

/*73:*/
#line 1992 "weaver-interface-metafont.tex"

mf->errno= mf->errno_line= 0;
mf->errno_character[0]= '\0';
mf->errno_str= NULL;
mf->errno_int= 0;
/*:73*//*115:*/
#line 2880 "weaver-interface-metafont.tex"

mf->named_variables= NULL;
mf->variables= NULL;
/*:115*//*136:*/
#line 3289 "weaver-interface-metafont.tex"

mf->internal_numeric_variables= 
permanent_alloc(6*sizeof(struct numeric_variable));
((struct numeric_variable*)mf->internal_numeric_variables)[0].value= 
((double)dpi)/72.0;
((struct numeric_variable*)mf->internal_numeric_variables)[1].value= 
((double)dpi)/2.54;
((struct numeric_variable*)mf->internal_numeric_variables)[2].value= 
((double)dpi)/25.4;
{
int i;
for(i= 0;i<6;i++){
((struct numeric_variable*)
mf->internal_numeric_variables)[i].type= TYPE_T_NUMERIC;
((struct numeric_variable*)
mf->internal_numeric_variables)[i].next= NULL;
}
}
/*:136*//*145:*/
#line 3464 "weaver-interface-metafont.tex"

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
/*:145*//*197:*/
#line 5191 "weaver-interface-metafont.tex"

mf->internal_pen_variables= (struct pen_variable*)
permanent_alloc(2*sizeof(struct pen_variable));
if(mf->internal_pen_variables==NULL){
if(permanent_free!=NULL)
permanent_free(mf);
return NULL;
}
mf->internal_pen_variables[0].format= NULL;
mf->internal_pen_variables[0].type= TYPE_T_PEN;
mf->internal_pen_variables[0].flags= FLAG_NULL;
mf->internal_pen_variables[0].referenced= NULL;
mf->internal_pen_variables[0].gl_vbo= 0;
mf->internal_pen_variables[0].indices= 0;
mf->internal_pen_variables[0].permanent= true;
mf->internal_pen_variables[1].format= NULL;
mf->internal_pen_variables[1].type= TYPE_T_PEN;
mf->internal_pen_variables[1].flags= FLAG_CONVEX|FLAG_STRAIGHT|
FLAG_SQUARE;
mf->internal_pen_variables[1].referenced= NULL;
mf->internal_pen_variables[1].gl_vbo= 0;
mf->internal_pen_variables[1].indices= 4;
mf->internal_pen_variables[1].permanent= true;
{
int j;
for(j= 0;j<2;j++)
INITIALIZE_IDENTITY_MATRIX(mf->internal_pen_variables[j].gl_matrix);
}
/*:197*//*207:*/
#line 5356 "weaver-interface-metafont.tex"

mf->internal_picture_variables= (struct picture_variable*)
permanent_alloc(sizeof(struct picture_variable));
if(mf->internal_picture_variables==NULL){
if(permanent_free!=NULL)
permanent_free(mf);
return NULL;
}

mf->internal_picture_variables[0].type= TYPE_T_PICTURE;
mf->internal_picture_variables[0].width= -1;
mf->internal_picture_variables[0].height= -1;
mf->internal_picture_variables[0].texture= 0;
/*:207*//*281:*/
#line 6875 "weaver-interface-metafont.tex"

mf->have_stored_normaldeviate= false;
/*:281*//*560:*/
#line 14702 "weaver-interface-metafont.tex"

mf->pen_lft= mf->pen_rt= mf->pen_top= mf->pen_bot= 0.0;
/*:560*//*658:*/
#line 18285 "weaver-interface-metafont.tex"

mf->current_depth= 0;
/*:658*//*664:*/
#line 18475 "weaver-interface-metafont.tex"

memset(mf->glyphs,0,sizeof(struct _glyph*)*332);
mf->first_glyph= NULL;
mf->number_of_glyphs= 0;
/*:664*/
#line 1908 "weaver-interface-metafont.tex"

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

/*94:*/
#line 2479 "weaver-interface-metafont.tex"

cx->nesting_level= 0;
cx->end_token_stack= NULL;
/*:94*//*119:*/
#line 2944 "weaver-interface-metafont.tex"

cx->variables= NULL;
/*:119*/
#line 1920 "weaver-interface-metafont.tex"

return cx;
}
/*:68*//*70:*/
#line 1943 "weaver-interface-metafont.tex"

void destroy_context(struct metafont*mf,struct context*cx){
if(temporary_free!=NULL){

/*103:*/
#line 2665 "weaver-interface-metafont.tex"

if(temporary_free!=NULL){
while(cx->end_token_stack!=NULL){
struct generic_token*end_tok= cx->end_token_stack;
cx->end_token_stack= end_tok->next;
temporary_free(end_tok);
}
}
/*:103*//*120:*/
#line 2952 "weaver-interface-metafont.tex"

if(temporary_free!=NULL){
struct variable*v= (struct variable*)(cx->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*154:*/
#line 3666 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&temporary_free!=NULL)
path_recursive_free(temporary_free,path,false);
}
/*:154*//*195:*/
#line 5158 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&temporary_free!=NULL)
path_recursive_free(temporary_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
/*201:*/
#line 5270 "weaver-interface-metafont.tex"

if(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].referenced==pen){
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].format= NULL;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].type= TYPE_T_PEN;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].flags= FLAG_NULL;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].referenced= NULL;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].gl_vbo= 0;
mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN].indices= 0;
}
/*:201*/
#line 5165 "weaver-interface-metafont.tex"

}
/*:195*//*205:*/
#line 5332 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:205*/
#line 2958 "weaver-interface-metafont.tex"

temporary_free(v);
v= next;
}
}
/*:120*/
#line 1947 "weaver-interface-metafont.tex"

temporary_free(cx);
}
}
/*:70*//*85:*/
#line 2259 "weaver-interface-metafont.tex"

bool eval_list_of_statements(struct metafont*mf,struct context*cx,
struct generic_token*begin_list,
struct generic_token*end_list){
struct generic_token*begin,*end= NULL;
begin= begin_list;
/*647:*/
#line 18011 "weaver-interface-metafont.tex"

GLint _viewport[4];
glGetIntegerv(GL_VIEWPORT,_viewport);
glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING,&previous_fb);
/*:647*/
#line 2265 "weaver-interface-metafont.tex"

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
/*648:*/
#line 18022 "weaver-interface-metafont.tex"

glBindFramebuffer(GL_FRAMEBUFFER,previous_fb);
glViewport(_viewport[0],_viewport[1],_viewport[2],_viewport[3]);
/*:648*/
#line 2292 "weaver-interface-metafont.tex"

return true;
}
/*:85*//*89:*/
#line 2405 "weaver-interface-metafont.tex"

bool eval_statement(struct metafont*mf,struct context*cx,
struct generic_token*begin,struct generic_token**end){
/*104:*/
#line 2708 "weaver-interface-metafont.tex"

if(begin->type==TYPE_BEGINGROUP){
begin_nesting_level(mf,cx,begin);

*end= begin;
return true;
}
/*:104*//*105:*/
#line 2723 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_ENDGROUP){
if(!end_nesting_level(mf,cx,begin))
return false;
*end= begin;
return true;
}
/*:105*//*551:*/
#line 14461 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_IF){
struct generic_token*begin_bool,*end_bool;
struct boolean_variable b;
int current_nesting_level;

begin_nesting_level(mf,cx,begin);
current_nesting_level= cx->nesting_level;

begin_bool= begin->next;
end_bool= begin_bool;
while(end_bool!=*end&&end_bool->next->type!=TYPE_COLON)
end_bool= end_bool->next;
if(end_bool==*end){
RAISE_ERROR_MISSING_TOKEN(mf,cx,OPTIONAL(begin->line),TYPE_COLON);
return false;
}

if(!eval_boolean_expression(mf,cx,begin_bool,end_bool,&b))
return false;
if(b.value==1){
*end= end_bool->next;
return true;
}
else{
struct generic_token*t= end_bool->next;
while(t->next!=NULL){
if(t->type==TYPE_FI&&cx->nesting_level==current_nesting_level){

if(!end_nesting_level(mf,cx,t))
return false;
*end= t;
return true;
}
else if(t->type==TYPE_ELSE&&
cx->nesting_level==current_nesting_level){

*end= t->next;
if((*end)->type!=TYPE_COLON){
RAISE_ERROR_MISSING_TOKEN(mf,cx,OPTIONAL(begin->line),
TYPE_COLON);
return false;
}
return true;
}
else if(t->type==TYPE_ELSEIF&&
cx->nesting_level==current_nesting_level){

begin_bool= t->next;
end_bool= begin_bool;
while(end_bool!=*end&&end_bool->next->type!=TYPE_COLON)
end_bool= end_bool->next;
if(!eval_boolean_expression(mf,cx,begin_bool,end_bool,&b))
return false;
if(b.value==1){
*end= end_bool->next;
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
RAISE_ERROR_UNFINISHED_STATEMENT(mf,cx,OPTIONAL(begin->line),
TYPE_IF);
return false;
}
/*:551*//*555:*/
#line 14591 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_ELSEIF||begin->type==TYPE_ELSE){
int current_nesting_level;
struct generic_token*t;
if(cx->end_token_stack==NULL||
cx->end_token_stack->type!=TYPE_FI){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),
begin->type);
return false;
}
current_nesting_level= cx->nesting_level;
t= begin;
while(t!=NULL){
if(t->type==TYPE_FI&&cx->nesting_level==current_nesting_level){

if(!end_nesting_level(mf,cx,t))
return false;
*end= t;
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
RAISE_ERROR_UNFINISHED_STATEMENT(mf,cx,OPTIONAL(begin->line),
TYPE_IF);
return false;
}
/*:555*//*556:*/
#line 14633 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_FI){
if(!end_nesting_level(mf,cx,begin))
return false;
*end= begin;
return true;
}
/*:556*//*668:*/
#line 18669 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_BEGINCHAR&&mf->loading){
DECLARE_NESTING_CONTROL();
struct _glyph*glyph;
struct generic_token*t= begin->next;
if(t->type!=TYPE_OPEN_PARENTHESIS||begin==*end){
RAISE_ERROR_MISSING_TOKEN(mf,cx,OPTIONAL(t->line),
TYPE_OPEN_PARENTHESIS);
return false;
}
if(t!=*end)
t= t->next;
if(t->type!=TYPE_STRING){
RAISE_ERROR_MISSING_TOKEN(mf,cx,OPTIONAL(t->line),
TYPE_STRING);
return false;
}
{
struct string_token*str= (struct string_token*)t;
glyph= get_glyph(mf,(unsigned char*)str->value,true);
if(glyph==NULL)
return false;
if(mf->first_glyph==NULL)
mf->first_glyph= glyph;
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
}
if(t==NULL||number_of_commas!=3||
t->type!=TYPE_CLOSE_PARENTHESIS){
RAISE_ERROR_MALFORMED_STATEMENT(mf,cx,OPTIONAL(begin->line),
TYPE_BEGINCHAR);
return false;
}
t= t->next;
while(t!=NULL&&t->type!=TYPE_ENDCHAR){
if(t->type==TYPE_BEGINCHAR){
RAISE_ERROR_NESTED_BEGINCHAR(mf,cx,OPTIONAL(begin->line));
return false;
}
t= t->next;
}
if(t==NULL){
RAISE_ERROR_UNFINISHED_STATEMENT(mf,cx,OPTIONAL(begin->line),
TYPE_BEGINCHAR);
return false;
}
glyph->end= t;
*end= t;
}
mf->number_of_glyphs++;
return true;
}
/*:668*//*672:*/
#line 18805 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_ENDCHAR&&mf->loading){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),
TYPE_ENDCHAR);
return false;
}
/*:672*//*674:*/
#line 18845 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_BEGINCHAR){
DECLARE_NESTING_CONTROL();
begin_nesting_level(mf,cx,begin);
struct generic_token*t,*begin_expr,*end_expr;
struct string_token*str;
struct numeric_variable width,height,depth;

t= begin->next;
t= t->next;
str= (struct string_token*)t;
cx->current_glyph= str->glyph;
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
if(!eval_numeric_expression(mf,cx,begin_expr,end_expr,&width))
return false;
if(width.value<=0.0){
RAISE_ERROR_INVALID_DIMENSION_GLYPH(mf,cx,OPTIONAL(begin->line));
return false;
}
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
if(height.value+depth.value<=0.0){
RAISE_ERROR_INVALID_DIMENSION_GLYPH(mf,cx,OPTIONAL(begin->line));
return false;
}
*end= t;
{
unsigned char*data;
struct numeric_variable*vars;
size_t size;
struct picture_variable*pic= &(mf->internal_picture_variables[0]);
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
vars= ((struct numeric_variable*)mf->internal_numeric_variables);
#ifdef W_WEAVEFONT_DISABLE_MULTISAMPLE
mf->current_depth= round(depth.value);
pic->width= round(width.value);
pic->height= (round(height.value)+round(depth.value));
vars[INTERNAL_NUMERIC_W].value= round(width.value);
vars[INTERNAL_NUMERIC_H].value= round(height.value);
vars[INTERNAL_NUMERIC_D].value= round(depth.value);
#else
mf->current_depth= 2*round(depth.value);
pic->width= 2*round(width.value);
pic->height= 2*(round(height.value)+round(depth.value));
vars[INTERNAL_NUMERIC_W].value= 2*round(width.value);
vars[INTERNAL_NUMERIC_H].value= 2*round(height.value);
vars[INTERNAL_NUMERIC_D].value= 2*round(depth.value);
#endif
size= pic->width*pic->height*4;
data= temporary_alloc(size);
if(data==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(begin->line));
return false;
}

memset(data,255,size);
{
int i;
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
/*645:*/
#line 17973 "weaver-interface-metafont.tex"

{
if(currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&currentpicture_fb);
}
currentpicture_fb= 0;
}
/*:645*/
#line 18944 "weaver-interface-metafont.tex"

}
{
mf->internal_pen_variables[0].format= NULL;
mf->internal_pen_variables[0].type= TYPE_T_PEN;
mf->internal_pen_variables[0].flags= FLAG_NULL;
mf->internal_pen_variables[0].referenced= NULL;
if(mf->internal_pen_variables[0].gl_vbo!=0)
glDeleteBuffers(1,&(mf->internal_pen_variables[0].gl_vbo));
mf->internal_pen_variables[0].gl_vbo= 0;
mf->internal_pen_variables[0].indices= 0;
mf->pen_lft= mf->pen_rt= mf->pen_top= mf->pen_bot= 0.0;
}
return true;
}
/*:674*//*678:*/
#line 19005 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_ENDCHAR){
struct picture_variable*currentpicture= 
&(mf->internal_picture_variables[0]);
end_nesting_level(mf,cx,begin);
cx->current_glyph->width= round(currentpicture->width);
cx->current_glyph->depth= round(mf->current_depth);
cx->current_glyph->height= round(currentpicture->height-
mf->current_depth);
cx->current_glyph->texture= currentpicture->texture;
#ifndef W_WEAVEFONT_DISABLE_MULTISAMPLE
cx->current_glyph->width/= 2;
cx->current_glyph->depth/= 2;
cx->current_glyph->height/= 2;
#endif
cx->current_glyph->need_rendering= false;
currentpicture->width= -1;
currentpicture->height= -1;
currentpicture->texture= 0;
*end= begin;
return true;
}
/*:678*/
#line 2408 "weaver-interface-metafont.tex"

/*121:*/
#line 2974 "weaver-interface-metafont.tex"

else if(begin->type>=TYPE_T_BOOLEAN&&begin->type<=TYPE_T_NUMERIC){
int type= begin->type;
struct symbolic_token*variable= (struct symbolic_token*)(begin->next);
do{
if(variable->type!=TYPE_SYMBOLIC){
RAISE_ERROR_INVALID_NAME(mf,cx,OPTIONAL(variable->line),
variable->type);
return false;
}
/*125:*/
#line 3049 "weaver-interface-metafont.tex"

{
void*variable_pointer;
if(mf->loading){
if(cx->nesting_level!=0||variable->value[0]=='_')
variable_pointer= insert_variable(mf,type,variable,
&(mf->variables));
else
variable_pointer= insert_named_global_variable(mf,type,variable);
}
else{
variable_pointer= insert_variable(mf,type,variable,&(cx->variables));
}
if(variable_pointer==NULL){
RAISE_ERROR_NO_MEMORY(mf,cx,OPTIONAL(variable->line));
return false;
}
update_token_pointer_for_variable(variable,variable_pointer);
}
/*:125*/
#line 2984 "weaver-interface-metafont.tex"

if(variable!=(struct symbolic_token*)*end)
variable= (struct symbolic_token*)(variable->next);
else{
variable= NULL;
continue;
}
if(variable->type!=TYPE_COMMA){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(variable->line),
TYPE_COMMA,variable->type);
return false;
}
if(variable==(struct symbolic_token*)*end){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL((*end)->line),
TYPE_SEMICOLON,TYPE_COMMA);
return false;
}
variable= (struct symbolic_token*)(variable->next);
}while(variable!=NULL);
return true;
}
/*:121*/
#line 2409 "weaver-interface-metafont.tex"

/*215:*/
#line 5495 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_SYMBOLIC){
struct symbolic_token*var= (struct symbolic_token*)begin;
struct generic_token*begin_expression;
int type= 0;
int number_of_variables= 0;
do{
if(var->type!=TYPE_SYMBOLIC){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(var->line),
TYPE_SYMBOLIC,var->type);
return false;
}
if(var->var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(var->line),
var->value);
return false;
}
number_of_variables++;
if(type==0)
type= ((struct variable*)(var->var))->type;
else if(((struct variable*)(var->var))->type!=type){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(var->line),
var->value,
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
if(var!=(struct symbolic_token*)end)
var= (struct symbolic_token*)(var->next);
else
var= NULL;
}while(var!=NULL&&(var->next->type==TYPE_EQUAL||
var->next->type==TYPE_ASSIGNMENT));
if(var==NULL){
RAISE_ERROR_MISSING_EXPRESSION(mf,cx,OPTIONAL(var->line),type);
return false;
}
begin_expression= (struct generic_token*)var;
/*224:*/
#line 5718 "weaver-interface-metafont.tex"

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
/*:224*/
#line 5541 "weaver-interface-metafont.tex"

/*288:*/
#line 6998 "weaver-interface-metafont.tex"

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
/*:288*/
#line 5542 "weaver-interface-metafont.tex"

/*320:*/
#line 7853 "weaver-interface-metafont.tex"

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
/*:320*/
#line 5543 "weaver-interface-metafont.tex"

/*346:*/
#line 8447 "weaver-interface-metafont.tex"

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
/*:346*/
#line 5544 "weaver-interface-metafont.tex"

/*433:*/
#line 10947 "weaver-interface-metafont.tex"

else if(type==TYPE_T_PEN){
int i;
struct pen_variable result;
if(!eval_pen_expression(mf,cx,begin_expression,*end,&result))
return false;
var= (struct symbolic_token*)begin;
for(i= 0;i<number_of_variables;i++){
if(!assign_pen_variable(mf,(struct pen_variable*)var->var,
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
/*:433*/
#line 5545 "weaver-interface-metafont.tex"

/*472:*/
#line 11918 "weaver-interface-metafont.tex"

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

if(pic==
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE])){

/*645:*/
#line 17973 "weaver-interface-metafont.tex"

{
if(currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&currentpicture_fb);
}
currentpicture_fb= 0;
}
/*:645*/
#line 11938 "weaver-interface-metafont.tex"

}
}
else
assign_picture_variable(mf,(struct picture_variable*)var->var,
&result);
var= (struct symbolic_token*)(var->next);
var= (struct symbolic_token*)(var->next);
}
}
/*:472*/
#line 5546 "weaver-interface-metafont.tex"

/*527:*/
#line 13452 "weaver-interface-metafont.tex"

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
/*:527*/
#line 5547 "weaver-interface-metafont.tex"

return true;
}
/*:215*/
#line 2410 "weaver-interface-metafont.tex"

/*631:*/
#line 17537 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_PICKUP){
struct generic_token*end_expression= *end;
struct generic_token*next_token= begin->next;
if(begin==*end){
RAISE_ERROR_UNFINISHED_STATEMENT(mf,cx,OPTIONAL(begin->line),
TYPE_PICKUP);
return false;
}
if(next_token->type!=TYPE_NULLPEN&&
next_token->type!=TYPE_SYMBOLIC&&
next_token->type!=TYPE_PENCIRCLE&&
next_token->type!=TYPE_PENSEMICIRCLE){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(next_token->line),
next_token->type);
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
else if(next_token->type==TYPE_PENSEMICIRCLE){
mf->internal_pen_variables[0].flags= FLAG_CONVEX|FLAG_SEMICIRCULAR;
mf->internal_pen_variables[0].referenced= NULL;
mf->internal_pen_variables[0].gl_vbo= 0;
}
else{
struct symbolic_token*symbol= ((struct symbolic_token*)next_token);
struct pen_variable*var= (struct pen_variable*)(symbol->var);
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(next_token->line),
symbol->value);
return false;
}
if(var->type!=TYPE_T_PEN){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(next_token->line),
symbol->value,var->type,
TYPE_T_PEN);
return false;
}
if(var->format==NULL&&var->flags==false){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(next_token->line),
symbol->value);
return false;
}
mf->internal_pen_variables[0].referenced= var;
}
INITIALIZE_IDENTITY_MATRIX(mf->internal_pen_variables[0].gl_matrix);
/*632:*/
#line 17610 "weaver-interface-metafont.tex"

while(next_token!=end_expression){
struct generic_token*begin_subexpr,*end_subexpr;
DECLARE_NESTING_CONTROL();
next_token= next_token->next;
if(next_token==NULL||next_token==end_expression){
RAISE_ERROR_UNFINISHED_STATEMENT(mf,cx,OPTIONAL(begin->line),
TYPE_PICKUP);
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
TRANSFORM_ROTATE(mf->internal_pen_variables[0].gl_matrix,
a.value*0.0174533);
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
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(next_token->line),
next_token->type);
return false;
}
next_token= end_subexpr;
}
/*:632*//*633:*/
#line 17747 "weaver-interface-metafont.tex"

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
/*:633*/
#line 17593 "weaver-interface-metafont.tex"

return true;
}
/*:631*//*653:*/
#line 18113 "weaver-interface-metafont.tex"

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
/*:653*/
#line 2411 "weaver-interface-metafont.tex"


RAISE_ERROR_UNKNOWN_STATEMENT(mf,cx,OPTIONAL(begin->line));
return false;
}
/*:89*//*96:*/
#line 2507 "weaver-interface-metafont.tex"

bool begin_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok){
struct generic_token*end_token;
end_token= (struct generic_token*)
temporary_alloc(sizeof(struct generic_token));
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
default:
return false;
}
#if defined(W_DEBUG_METAFONT)
end_token->line= tok->line;
#endif
cx->nesting_level++;
end_token->next= cx->end_token_stack;
cx->end_token_stack= end_token;
return true;
}
/*:96*//*97:*/
#line 2545 "weaver-interface-metafont.tex"

bool end_nesting_level(struct metafont*mf,struct context*cx,
struct generic_token*tok){
struct generic_token*end_tok= cx->end_token_stack;
if(end_tok==NULL){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(tok->line),tok->type);
return false;
}
else if(end_tok->type!=tok->type){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(tok->line),
end_tok->type,tok->type);
return false;
}
cx->nesting_level--;
cx->end_token_stack= end_tok->next;
if(temporary_free!=NULL)
temporary_free(end_tok);
return true;
}
/*:97*//*127:*/
#line 3090 "weaver-interface-metafont.tex"

struct variable*insert_variable(struct metafont*mf,
int type,
struct symbolic_token*variable,
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
/*133:*/
#line 3247 "weaver-interface-metafont.tex"

if(type==TYPE_T_NUMERIC){
((struct numeric_variable*)var)->value= NAN;
}
/*:133*//*141:*/
#line 3394 "weaver-interface-metafont.tex"

if(type==TYPE_T_PAIR){
((struct pair_variable*)var)->x= NAN;
}
/*:141*//*143:*/
#line 3437 "weaver-interface-metafont.tex"

if(type==TYPE_T_TRANSFORM)
((struct transform_variable*)var)->value[0]= NAN;
/*:143*//*152:*/
#line 3639 "weaver-interface-metafont.tex"

if(type==TYPE_T_PATH){
((struct path_variable*)var)->length= -1;
((struct path_variable*)var)->permanent= mf->loading;
}
/*:152*//*193:*/
#line 5126 "weaver-interface-metafont.tex"

if(type==TYPE_T_PEN){
((struct pen_variable*)var)->format= NULL;
((struct pen_variable*)var)->gl_vbo= 0;
((struct pen_variable*)var)->indices= 0;
((struct pen_variable*)var)->flags= false;
((struct pen_variable*)var)->referenced= NULL;
((struct pen_variable*)var)->permanent= mf->loading;
}
/*:193*//*203:*/
#line 5306 "weaver-interface-metafont.tex"

if(type==TYPE_T_PICTURE){
((struct picture_variable*)var)->width= -1;
((struct picture_variable*)var)->height= -1;
((struct picture_variable*)var)->texture= 0;
}
/*:203*//*212:*/
#line 5426 "weaver-interface-metafont.tex"

if(type==TYPE_T_BOOLEAN)
((struct boolean_variable*)var)->value= -1;
/*:212*/
#line 3110 "weaver-interface-metafont.tex"

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
/*:127*//*129:*/
#line 3141 "weaver-interface-metafont.tex"

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
new_var= insert_variable(mf,type,var,&(named->var));
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
/*:129*//*131:*/
#line 3203 "weaver-interface-metafont.tex"

void update_token_pointer_for_variable(struct symbolic_token*var_token,
struct variable*var_pointer){
struct symbolic_token*p= (struct symbolic_token*)var_token->next;
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
/*:131*//*156:*/
#line 3692 "weaver-interface-metafont.tex"

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
/*:156*//*158:*/
#line 3761 "weaver-interface-metafont.tex"

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
/*:158*//*159:*/
#line 3798 "weaver-interface-metafont.tex"

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
/*:159*//*162:*/
#line 3938 "weaver-interface-metafont.tex"

double compute_f(double theta,double phi){
double n= 2+sqrt(2)*(sin(theta)-0.0625*sin(phi))*
(sin(phi)-0.0625*sin(theta))*(cos(theta)-cos(phi));
double d= 3*(1+0.5*(sqrt(5)-1)*cos(theta)+0.5*(3-sqrt(5))*
cos(phi));
return n/d;
}
/*:162*//*163:*/
#line 3954 "weaver-interface-metafont.tex"

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
/*164:*/
#line 3997 "weaver-interface-metafont.tex"

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
/*:164*/
#line 3978 "weaver-interface-metafont.tex"

}
}
if(p->cyclic)
memcpy(&(p->points[p->length-1]),&(p->points[0]),
sizeof(struct path_points));
}
/*:163*//*166:*/
#line 4024 "weaver-interface-metafont.tex"

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
/*169:*/
#line 4096 "weaver-interface-metafont.tex"

bool s1,s2,s3;
s1= ((*control_x-p1_x)*(p0_y-p1_y)-
(p0_x-p1_x)*(*control_y-p1_y))<0;
s2= ((*control_x-p2_x)*(p1_y-p2_y)-
(p1_x-p2_x)*(*control_y-p2_y))<0;
s3= ((*control_x-p0_x)*(p2_y-p0_y)-
(p2_x-p0_x)*(*control_y-p0_y))<0;
if(s1==s2&&s2==s3)
return;
/*:169*/
#line 4049 "weaver-interface-metafont.tex"

/*170:*/
#line 4119 "weaver-interface-metafont.tex"

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
/*:170*/
#line 4050 "weaver-interface-metafont.tex"

}
}
/*:166*//*168:*/
#line 4066 "weaver-interface-metafont.tex"

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
/*:168*//*172:*/
#line 4226 "weaver-interface-metafont.tex"

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
/*:172*//*178:*/
#line 4394 "weaver-interface-metafont.tex"

bool fill_missing_directions(struct metafont*mf,struct context*cx,
struct path_variable*p,int begin,int end){
double*M,*x,*b;
struct path_points*p0= NULL,*p1= &(p->points[(begin)%p->length]),
*p2= &(p->points[(begin+1)%p->length]);
double complex z0= NAN,z1= p1->prov.x+p1->prov.y*I,
z2= p2->prov.x+p2->prov.y*I;
int i= 1,size,number_of_points;
/*173:*/
#line 4287 "weaver-interface-metafont.tex"

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
/*:173*/
#line 4403 "weaver-interface-metafont.tex"

/*184:*/
#line 4738 "weaver-interface-metafont.tex"

if(begin==end&&isnan(p1->prov.dir1_x)&&isnan(p1->prov.dir2_x)){
p1->format= FINAL_FORMAT;
p1->point.u_x= p1->point.x+(1.0/3)*(p2->point.x-p1->point.x);
p1->point.v_x= p1->point.x+(2.0/3)*(p2->point.x-p1->point.x);
p1->point.u_y= p1->point.y+(1.0/3)*(p2->point.y-p1->point.y);
p1->point.v_y= p1->point.y+(2.0/3)*(p2->point.y-p1->point.y);
p->number_of_missing_directions-= 2;
return true;
}
/*:184*/
#line 4404 "weaver-interface-metafont.tex"

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

/*181:*/
#line 4557 "weaver-interface-metafont.tex"

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
/*:181*/
#line 4423 "weaver-interface-metafont.tex"

if(begin!=end){
for(i= 1;(begin+i-1)%p->length!=end;i++){
p0= p1;p1= p2;
p2= &(p->points[(begin+i+1)%p->length]);
z0= z1;z1= z2;
z2= p2->prov.x+p2->prov.y*I;
/*183:*/
#line 4689 "weaver-interface-metafont.tex"

M[current_psi]= 1.0;
b[number_of_equations]= carg((z2-z1)/(z1-z0));
if(b[number_of_equations]==-M_PI)
b[number_of_equations]*= -1.0;
/*175:*/
#line 4337 "weaver-interface-metafont.tex"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:175*/
#line 4694 "weaver-interface-metafont.tex"

M[current_theta]= M[current_psi]= M[current_phi]= 1.0;
b[number_of_equations]= 0.0;
/*175:*/
#line 4337 "weaver-interface-metafont.tex"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:175*/
#line 4697 "weaver-interface-metafont.tex"

{
double t0= p0->prov.tension1,t1= p0->prov.tension2,
t2= p1->prov.tension1,t3= p1->prov.tension2;
M[previous_theta]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0);
M[current_theta]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3-3.0);
M[current_phi]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0-3.0);
M[next_phi]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3);
b[number_of_equations]= 0.0;
/*176:*/
#line 4354 "weaver-interface-metafont.tex"

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
/*:176*/
#line 4706 "weaver-interface-metafont.tex"

}
/*:183*/
#line 4430 "weaver-interface-metafont.tex"

}
}
/*182:*/
#line 4621 "weaver-interface-metafont.tex"

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
/*:182*/
#line 4433 "weaver-interface-metafont.tex"

solve_linear_system(size,M,b,x);
/*185:*/
#line 4766 "weaver-interface-metafont.tex"

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
/*:185*/
#line 4435 "weaver-interface-metafont.tex"

{
int theta;
for(theta= 1,i= 1;i<number_of_points-1;i++,theta+= 3){

/*187:*/
#line 4829 "weaver-interface-metafont.tex"

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
/*:187*/
#line 4440 "weaver-interface-metafont.tex"

}
}
/*186:*/
#line 4793 "weaver-interface-metafont.tex"

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
/*:186*/
#line 4443 "weaver-interface-metafont.tex"

if(temporary_free!=NULL){
temporary_free(M);
temporary_free(x);
temporary_free(b);
}
return true;
}
/*:178*//*180:*/
#line 4470 "weaver-interface-metafont.tex"

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
/*174:*/
#line 4315 "weaver-interface-metafont.tex"

int previous_theta,current_theta,current_psi,current_phi,next_phi,
number_of_equations;
previous_theta= size-3;
current_theta= 0;
current_psi= 1;
current_phi= 2;
next_phi= 5;
number_of_equations= 0;
/*:174*/
#line 4481 "weaver-interface-metafont.tex"


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
/*183:*/
#line 4689 "weaver-interface-metafont.tex"

M[current_psi]= 1.0;
b[number_of_equations]= carg((z2-z1)/(z1-z0));
if(b[number_of_equations]==-M_PI)
b[number_of_equations]*= -1.0;
/*175:*/
#line 4337 "weaver-interface-metafont.tex"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:175*/
#line 4694 "weaver-interface-metafont.tex"

M[current_theta]= M[current_psi]= M[current_phi]= 1.0;
b[number_of_equations]= 0.0;
/*175:*/
#line 4337 "weaver-interface-metafont.tex"

{
previous_theta+= size;
current_theta+= size;
current_psi+= size;
current_phi+= size;
next_phi+= size;
number_of_equations++;
}
/*:175*/
#line 4697 "weaver-interface-metafont.tex"

{
double t0= p0->prov.tension1,t1= p0->prov.tension2,
t2= p1->prov.tension1,t3= p1->prov.tension2;
M[previous_theta]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0);
M[current_theta]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3-3.0);
M[current_phi]= t1*t1*(1.0/cabs(z1-z0))*(1.0/t0-3.0);
M[next_phi]= -t2*t2*(1.0/cabs(z2-z1))*(1.0/t3);
b[number_of_equations]= 0.0;
/*176:*/
#line 4354 "weaver-interface-metafont.tex"

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
/*:176*/
#line 4706 "weaver-interface-metafont.tex"

}
/*:183*/
#line 4500 "weaver-interface-metafont.tex"

}
solve_linear_system(size,M,b,x);
{
int theta;
for(theta= 0,i= 0;i<p->length;i++,theta+= 3){

/*187:*/
#line 4829 "weaver-interface-metafont.tex"

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
/*:187*/
#line 4507 "weaver-interface-metafont.tex"

}
}
if(temporary_free!=NULL){
temporary_free(M);
temporary_free(x);
temporary_free(b);
}
return true;
}
/*:180*//*189:*/
#line 4951 "weaver-interface-metafont.tex"

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
/*:189*//*235:*/
#line 6013 "weaver-interface-metafont.tex"

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
/*:235*//*242:*/
#line 6160 "weaver-interface-metafont.tex"

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
/*:242*//*249:*/
#line 6317 "weaver-interface-metafont.tex"

bool eval_numeric_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result){
/*253:*/
#line 6372 "weaver-interface-metafont.tex"

if(begin==end||(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS)||
(begin->type==TYPE_NUMERIC&&begin->next!=end&&
begin->next->type==TYPE_DIVISION&&begin->next->next==end&&
end->type==TYPE_NUMERIC)){
return eval_numeric_atom(mf,cx,begin,end,result);
}
/*:253*/
#line 6322 "weaver-interface-metafont.tex"

/*254:*/
#line 6390 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_LENGTH){
int expr_type= get_primary_expression_type(mf,cx,begin->next,end);
if(expr_type==TYPE_T_NUMERIC){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
result->value= ((num.value> 0)?(num.value):(-num.value));
return true;
}
/*313:*/
#line 7737 "weaver-interface-metafont.tex"

else if(expr_type==TYPE_T_PAIR){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,begin->next,end,&p))
return false;
result->value= (float)hypot(p.x,p.y);
return true;
}
/*:313*//*425:*/
#line 10738 "weaver-interface-metafont.tex"

else if(expr_type==TYPE_T_PATH){
struct path_variable p;
if(!eval_path_primary(mf,cx,begin->next,end,&p))
return false;
result->value= (float)(p.number_of_points-1);
if(temporary_free!=NULL)
path_recursive_free(temporary_free,&p,false);
return true;
}
/*:425*/
#line 6400 "weaver-interface-metafont.tex"

else{
RAISE_ERROR_UNKNOWN_EXPRESSION_TYPE(mf,cx,OPTIONAL(begin->line),
expr_type);
return false;
}
}
/*:254*/
#line 6323 "weaver-interface-metafont.tex"

/*258:*/
#line 6464 "weaver-interface-metafont.tex"

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
/*:258*//*259:*/
#line 6485 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_SIND){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;

result->value= sinf(num.value*0.0174533);
return true;
}
/*:259*//*260:*/
#line 6500 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_COSD){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;

result->value= cosf(num.value*0.0174533);
return true;
}
/*:260*//*261:*/
#line 6515 "weaver-interface-metafont.tex"

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
/*:261*//*265:*/
#line 6568 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_EXP){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
result->value= expf(num.value);
return true;
}
/*:265*//*266:*/
#line 6582 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_FLOOR){
struct numeric_variable num;
if(!eval_numeric_primary(mf,cx,begin->next,end,&num))
return false;
result->value= floorf(num.value);
return true;
}
/*:266*//*267:*/
#line 6609 "weaver-interface-metafont.tex"

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
/*:267*//*268:*/
#line 6628 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_SUM){
if(!eval_numeric_primary(mf,cx,begin->next,end,result))
return false;
return true;
}
/*:268*//*269:*/
#line 6641 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_SUBTRACT){
if(!eval_numeric_primary(mf,cx,begin->next,end,result))
return false;
result->value*= -1;
return true;
}
/*:269*/
#line 6324 "weaver-interface-metafont.tex"

/*314:*/
#line 7755 "weaver-interface-metafont.tex"

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
/*343:*/
#line 8387 "weaver-interface-metafont.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,begin->next,end,&t))
return false;
result->value= t.value[6];
return true;
/*:343*/
#line 7766 "weaver-interface-metafont.tex"

}
}
/*:314*//*315:*/
#line 7777 "weaver-interface-metafont.tex"

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
/*344:*/
#line 8399 "weaver-interface-metafont.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,begin->next,end,&t))
return false;
result->value= t.value[7];
return true;
/*:344*/
#line 7788 "weaver-interface-metafont.tex"

}
}
/*:315*//*316:*/
#line 7800 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_ANGLE){
struct pair_variable p;
if(!eval_pair_primary(mf,cx,begin->next,end,&p))
return false;
if(p.x==0.0&&p.y==0.0){
RAISE_ERROR_ANGLE_OF_ORIGIN(mf,cx,OPTIONAL(begin->line));
return false;
}
result->value= (float)acos(p.x/(hypot(p.x,p.y)));
result->value*= 57.2958;
return true;
}
/*:316*//*342:*/
#line 8362 "weaver-interface-metafont.tex"

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
/*:342*//*524:*/
#line 13341 "weaver-interface-metafont.tex"

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
/*:524*//*525:*/
#line 13409 "weaver-interface-metafont.tex"

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
/*:525*//*526:*/
#line 13428 "weaver-interface-metafont.tex"

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
/*:526*/
#line 6325 "weaver-interface-metafont.tex"

/*270:*/
#line 6663 "weaver-interface-metafont.tex"

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
/*:270*/
#line 6326 "weaver-interface-metafont.tex"

RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_NUMERIC);
return false;
}
/*:249*//*274:*/
#line 6736 "weaver-interface-metafont.tex"

bool eval_numeric_atom(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct numeric_variable*result){
if(begin==end){
/*275:*/
#line 6760 "weaver-interface-metafont.tex"

if(begin->type==TYPE_NUMERIC){
result->value= ((struct numeric_token*)begin)->value;
return true;
}
/*:275*/
#line 6742 "weaver-interface-metafont.tex"

/*276:*/
#line 6773 "weaver-interface-metafont.tex"

if(begin->type==TYPE_SYMBOLIC){
struct symbolic_token*var_token= ((struct symbolic_token*)begin);
struct numeric_variable*var;
var= var_token->var;
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(begin->line),
var_token->value);
return false;
}
if(var->type!=TYPE_T_NUMERIC){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(begin->line),
var_token->value,var->type,
TYPE_T_NUMERIC);
return false;
}
if(isnan(var->value)){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
var_token->value);
return false;
}
result->value= var->value;
return true;
}
/*:276*/
#line 6743 "weaver-interface-metafont.tex"

/*282:*/
#line 6885 "weaver-interface-metafont.tex"

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
/*:282*/
#line 6744 "weaver-interface-metafont.tex"

}
else{
/*283:*/
#line 6920 "weaver-interface-metafont.tex"

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
/*:283*/
#line 6747 "weaver-interface-metafont.tex"

/*287:*/
#line 6978 "weaver-interface-metafont.tex"

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
/*:287*/
#line 6748 "weaver-interface-metafont.tex"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_NUMERIC);
return false;
}
/*:274*//*290:*/
#line 7048 "weaver-interface-metafont.tex"

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
/*:290*//*294:*/
#line 7161 "weaver-interface-metafont.tex"

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
/*295:*/
#line 7224 "weaver-interface-metafont.tex"

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
/*:295*/
#line 7199 "weaver-interface-metafont.tex"

/*296:*/
#line 7256 "weaver-interface-metafont.tex"

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
/*:296*/
#line 7200 "weaver-interface-metafont.tex"

/*297:*/
#line 7279 "weaver-interface-metafont.tex"

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
/*:297*/
#line 7201 "weaver-interface-metafont.tex"

/*298:*/
#line 7301 "weaver-interface-metafont.tex"

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
/*:298*/
#line 7202 "weaver-interface-metafont.tex"

/*299:*/
#line 7320 "weaver-interface-metafont.tex"

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
/*:299*/
#line 7203 "weaver-interface-metafont.tex"

/*300:*/
#line 7339 "weaver-interface-metafont.tex"

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
/*:300*/
#line 7204 "weaver-interface-metafont.tex"

/*301:*/
#line 7358 "weaver-interface-metafont.tex"

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
/*:301*/
#line 7205 "weaver-interface-metafont.tex"

/*302:*/
#line 7377 "weaver-interface-metafont.tex"

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
/*:302*/
#line 7206 "weaver-interface-metafont.tex"

/*303:*/
#line 7400 "weaver-interface-metafont.tex"

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
/*:303*/
#line 7207 "weaver-interface-metafont.tex"

/*345:*/
#line 8426 "weaver-interface-metafont.tex"

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
/*:345*/
#line 7208 "weaver-interface-metafont.tex"

}
else
return eval_pair_primary(mf,cx,begin,end,result);
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PAIR);
return false;
}
/*:294*//*305:*/
#line 7455 "weaver-interface-metafont.tex"

bool eval_pair_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pair_variable*result){
if(begin==end){
/*306:*/
#line 7481 "weaver-interface-metafont.tex"

struct symbolic_token*tok= (struct symbolic_token*)begin;
struct pair_variable*var;
if(tok->type!=TYPE_SYMBOLIC){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PAIR);
return false;
}
var= (struct pair_variable*)tok->var;
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(begin->line),
tok->value);
return false;
}
if(var->type!=TYPE_T_PAIR){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(begin->line),
tok->value,var->type,
TYPE_T_PAIR);
return false;
}
if(isnan(var->x)){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
tok->value);
return false;
}
result->x= var->x;
result->y= var->y;
return true;
/*:306*/
#line 7461 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*307:*/
#line 7519 "weaver-interface-metafont.tex"

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
/*:307*/
#line 7465 "weaver-interface-metafont.tex"

/*308:*/
#line 7571 "weaver-interface-metafont.tex"

else
return eval_pair_expression(mf,cx,begin_a,end_a,result);
/*:308*/
#line 7466 "weaver-interface-metafont.tex"

}
/*432:*/
#line 10868 "weaver-interface-metafont.tex"

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
if(of==NULL){
RAISE_ERROR_EXPECTED_FOUND(mf,cx,OPTIONAL(begin->line),
TYPE_SEMICOLON,TYPE_OF);
return false;
}
if(of->next==NULL||of==end){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(begin->line),
TYPE_SEMICOLON);
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
/*:432*//*636:*/
#line 17812 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_BOT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->y+= mf->pen_bot;
return true;
}
/*:636*//*637:*/
#line 17829 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_TOP){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->y+= mf->pen_top;
return true;
}
/*:637*//*638:*/
#line 17849 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_LFT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->x+= mf->pen_lft;
return true;
}
/*:638*//*639:*/
#line 17867 "weaver-interface-metafont.tex"

else if(begin->type==TYPE_RT){
if(!eval_pair_primary(mf,cx,(struct generic_token*)
begin->next,
end,result))
return false;
result->x+= mf->pen_rt;
return true;
}
/*:639*/
#line 7468 "weaver-interface-metafont.tex"

/*309:*/
#line 7583 "weaver-interface-metafont.tex"

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
/*:309*/
#line 7469 "weaver-interface-metafont.tex"

/*310:*/
#line 7659 "weaver-interface-metafont.tex"

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
/*:310*/
#line 7470 "weaver-interface-metafont.tex"

RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PAIR);
return false;
}
/*:305*//*324:*/
#line 7933 "weaver-interface-metafont.tex"

bool eval_transform_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result){
return eval_transform_secondary(mf,cx,begin,end,result);
}
/*:324*//*326:*/
#line 7964 "weaver-interface-metafont.tex"

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
/*327:*/
#line 8015 "weaver-interface-metafont.tex"

if(last_transform->type==TYPE_ROTATED){
struct numeric_variable theta;
double angle_radian;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&theta))
return false;

angle_radian= theta.value*0.0174533;
TRANSFORM_ROTATE(result->value,angle_radian);
return true;
}
/*:327*//*328:*/
#line 8034 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_SCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE(result->value,scale.value);
return true;
}
/*:328*//*329:*/
#line 8049 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_SHIFTED){
struct pair_variable shift;
if(!eval_pair_primary(mf,cx,last_transform->next,end,&shift))
return false;
TRANSFORM_SHIFT(result->value,shift.x,shift.y);
return true;
}
/*:329*//*330:*/
#line 8064 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_SLANTED){
struct numeric_variable slant;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&slant))
return false;
TRANSFORM_SLANT(result->value,slant.value);
return true;
}
/*:330*//*331:*/
#line 8079 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_XSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE_X(result->value,scale.value);
return true;
}
/*:331*//*332:*/
#line 8094 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_YSCALED){
struct numeric_variable scale;
if(!eval_numeric_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE_Y(result->value,scale.value);
return true;
}
/*:332*//*333:*/
#line 8111 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_ZSCALED){
struct pair_variable scale;
if(!eval_pair_primary(mf,cx,last_transform->next,end,&scale))
return false;
TRANSFORM_SCALE_Z(result->value,scale.x,scale.y);
return true;
}
/*:333*//*334:*/
#line 8128 "weaver-interface-metafont.tex"

else if(last_transform->type==TYPE_TRANSFORMED){
struct transform_variable b;
if(!eval_transform_primary(mf,cx,last_transform->next,end,&b))
return false;
MATRIX_MULTIPLICATION(result->value,b.value);
return true;
}
/*:334*/
#line 7998 "weaver-interface-metafont.tex"

}
else
return eval_transform_primary(mf,cx,begin,end,result);
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_TRANSFORM);
return false;
}
/*:326*//*336:*/
#line 8172 "weaver-interface-metafont.tex"

bool eval_transform_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct transform_variable*result){
if(begin==end&&begin->type==TYPE_SYMBOLIC){
/*337:*/
#line 8226 "weaver-interface-metafont.tex"

struct symbolic_token*v= (struct symbolic_token*)begin;
struct transform_variable*content= v->var;
if(content==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(v->line),v->value);
return false;
}
if(content->type!=TYPE_T_TRANSFORM){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),
v->value,content->type,
TYPE_T_TRANSFORM);
return false;
}
if(isnan(content->value[0])){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(v->line),v->value);
return false;
}
memcpy(result->value,content->value,sizeof(float)*9);
return true;
/*:337*/
#line 8178 "weaver-interface-metafont.tex"

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
/*339:*/
#line 8265 "weaver-interface-metafont.tex"

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
/*:339*/
#line 8202 "weaver-interface-metafont.tex"

}
else{
/*338:*/
#line 8253 "weaver-interface-metafont.tex"

struct generic_token*end_expr;
for(end_expr= begin->next;end_expr->next!=end;
end_expr= end_expr->next);
return eval_transform_expression(mf,cx,begin->next,end_expr,result);
/*:338*/
#line 8205 "weaver-interface-metafont.tex"

}
}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_TRANSFORM);
return false;
}
/*:336*//*350:*/
#line 8556 "weaver-interface-metafont.tex"

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
/*:350*//*352:*/
#line 8604 "weaver-interface-metafont.tex"

bool eval_path_expression(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result){
int expected_length;
int number_of_joins= count_path_joins(begin,end);
expected_length= number_of_joins+1;
/*353:*/
#line 8653 "weaver-interface-metafont.tex"

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
/*:353*/
#line 8612 "weaver-interface-metafont.tex"

/*354:*/
#line 8686 "weaver-interface-metafont.tex"

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
/*:354*/
#line 8613 "weaver-interface-metafont.tex"

/*355:*/
#line 8714 "weaver-interface-metafont.tex"

{
struct generic_token*begin_z1,*end_z1= NULL,*begin_z2,*end_z2;
struct generic_token*begin_d= NULL,*end_d= NULL,*begin_e,*end_e;
struct generic_token*begin_j,*end_j;
struct path_points*z0_point= NULL,*z1_point= NULL,*z2_point= NULL;
struct path_variable*z1_parent;
begin_z1= begin;
end_z1= begin_z1;
/*356:*/
#line 8746 "weaver-interface-metafont.tex"

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
/*:356*//*361:*/
#line 8913 "weaver-interface-metafont.tex"

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
/*:361*/
#line 8723 "weaver-interface-metafont.tex"

while(end_z1!=end||result->length<expected_length){
/*357:*/
#line 8770 "weaver-interface-metafont.tex"

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
/*:357*//*358:*/
#line 8806 "weaver-interface-metafont.tex"

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
/*:358*//*359:*/
#line 8847 "weaver-interface-metafont.tex"

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
/*:359*//*360:*/
#line 8880 "weaver-interface-metafont.tex"

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
/*:360*/
#line 8725 "weaver-interface-metafont.tex"

/*362:*/
#line 8961 "weaver-interface-metafont.tex"

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
/*:362*//*363:*/
#line 9036 "weaver-interface-metafont.tex"


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
/*:363*/
#line 8726 "weaver-interface-metafont.tex"

/*364:*/
#line 9072 "weaver-interface-metafont.tex"

if(!eval_direction_specifier(mf,cx,begin_d,end_d,
&(z1_point->prov.dir1_x),
&(z1_point->prov.dir1_y)))
return false;
if(!eval_direction_specifier(mf,cx,begin_e,end_e,
&(z1_point->prov.dir2_x),
&(z1_point->prov.dir2_y)))
return false;
/*:364*//*371:*/
#line 9251 "weaver-interface-metafont.tex"

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
/*:371*//*373:*/
#line 9339 "weaver-interface-metafont.tex"

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
/*:373*/
#line 8727 "weaver-interface-metafont.tex"

/*374:*/
#line 9373 "weaver-interface-metafont.tex"

if(begin_j==end_j&&begin_j->type==TYPE_AMPERSAND){
double dif_x= z1_point->prov.x-z2_point->prov.x;
double dif_y= z1_point->prov.y-z2_point->prov.y;
if(hypot(dif_x,dif_y)> 0.00002){
RAISE_ERROR_DISCONTINUOUS_PATH(mf,cx,OPTIONAL(begin_j->line));
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
/*:374*//*378:*/
#line 9429 "weaver-interface-metafont.tex"

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
/*:378*//*379:*/
#line 9456 "weaver-interface-metafont.tex"

else if(begin_j==end_j&&begin_j->type==TYPE_JOIN){
z1_point->prov.tension1= 1.0;
z1_point->prov.tension2= 1.0;
}
/*:379*//*380:*/
#line 9477 "weaver-interface-metafont.tex"

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
/*372:*/
#line 9299 "weaver-interface-metafont.tex"

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
/*:372*/
#line 9522 "weaver-interface-metafont.tex"

}
/*:380*//*381:*/
#line 9542 "weaver-interface-metafont.tex"

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
z1_point->prov.tension1,0);
return false;
}
if(z1_point->prov.tension2<0.75){
RAISE_ERROR_INVALID_TENSION(mf,cx,OPTIONAL(begin_t0->line),
z1_point->prov.tension2,1);
return false;
}
}
/*:381*/
#line 8728 "weaver-interface-metafont.tex"

begin_z1= begin_z2;
end_z1= end_z2;
}

/*385:*/
#line 9665 "weaver-interface-metafont.tex"

z0_point= &(result->points[0]);
while(z0_point->format==SUBPATH_FORMAT){
struct path_variable*p= (struct path_variable*)z0_point->subpath;
z0_point= &(p->points[0]);
}
/*:385*//*386:*/
#line 9684 "weaver-interface-metafont.tex"

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
/*:386*//*387:*/
#line 9722 "weaver-interface-metafont.tex"

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
/*:387*//*388:*/
#line 9750 "weaver-interface-metafont.tex"

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
/*:388*//*389:*/
#line 9781 "weaver-interface-metafont.tex"

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
/*:389*/
#line 8733 "weaver-interface-metafont.tex"

}
/*:355*/
#line 8614 "weaver-interface-metafont.tex"


return normalize_path(mf,cx,result);
}
/*:352*//*366:*/
#line 9101 "weaver-interface-metafont.tex"

bool eval_direction_specifier(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,float*w_x,
float*w_y){

if(begin!=NULL&&begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'{');
return false;
}
/*367:*/
#line 9124 "weaver-interface-metafont.tex"

if(begin==NULL||end==NULL)
return true;
/*:367*/
#line 9111 "weaver-interface-metafont.tex"

/*368:*/
#line 9136 "weaver-interface-metafont.tex"

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
/*:368*/
#line 9112 "weaver-interface-metafont.tex"

/*369:*/
#line 9165 "weaver-interface-metafont.tex"

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
/*:369*/
#line 9113 "weaver-interface-metafont.tex"

/*370:*/
#line 9201 "weaver-interface-metafont.tex"

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
/*:370*/
#line 9114 "weaver-interface-metafont.tex"

return false;
}
/*:366*//*391:*/
#line 9839 "weaver-interface-metafont.tex"

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
/*:391*//*393:*/
#line 9926 "weaver-interface-metafont.tex"

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
/*394:*/
#line 10035 "weaver-interface-metafont.tex"

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
/*:394*/
#line 9974 "weaver-interface-metafont.tex"

/*397:*/
#line 10085 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_xyscale(result,a.value,a.value);
return true;
}
/*:397*/
#line 9975 "weaver-interface-metafont.tex"

/*400:*/
#line 10131 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SHIFTED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end,&a))
return false;
path_shift(result,a.x,a.y);
return true;
}
/*:400*/
#line 9976 "weaver-interface-metafont.tex"

/*403:*/
#line 10171 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_SLANTED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_slant(result,a.value);
return true;
}
/*:403*/
#line 9977 "weaver-interface-metafont.tex"

/*406:*/
#line 10209 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_XSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_xyscale(result,a.value,1.0);
return true;
}
/*:406*/
#line 9978 "weaver-interface-metafont.tex"

/*407:*/
#line 10225 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_YSCALED){
struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,transform_op->next,end,&a))
return false;
path_xyscale(result,1.0,a.value);
return true;
}
/*:407*/
#line 9979 "weaver-interface-metafont.tex"

/*408:*/
#line 10248 "weaver-interface-metafont.tex"

else if(transform_op->type==TYPE_ZSCALED){
struct pair_variable a;
if(!eval_pair_primary(mf,cx,transform_op->next,end,&a))
return false;
path_zscale(result,a.x,a.y);
return true;
}
/*:408*/
#line 9980 "weaver-interface-metafont.tex"

/*411:*/
#line 10294 "weaver-interface-metafont.tex"

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
/*:411*/
#line 9981 "weaver-interface-metafont.tex"

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
/*:393*//*396:*/
#line 10060 "weaver-interface-metafont.tex"

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
/*:396*//*399:*/
#line 10111 "weaver-interface-metafont.tex"

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
/*:399*//*402:*/
#line 10151 "weaver-interface-metafont.tex"

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
/*:402*//*405:*/
#line 10191 "weaver-interface-metafont.tex"

void path_slant(struct path_variable*p,float s){
int i;
for(i= 0;i<p->length;i++){
p->points[i].point.x+= s*p->points[i].point.y;
p->points[i].point.u_x+= s*p->points[i].point.u_y;
p->points[i].point.v_x+= s*p->points[i].point.v_y;
}
}
/*:405*//*410:*/
#line 10268 "weaver-interface-metafont.tex"

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
/*:410*//*413:*/
#line 10320 "weaver-interface-metafont.tex"

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
/*:413*//*417:*/
#line 10398 "weaver-interface-metafont.tex"

bool eval_path_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct path_variable*result){
if(begin->type==TYPE_REVERSE){
/*418:*/
#line 10434 "weaver-interface-metafont.tex"

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
/*:418*/
#line 10404 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_SUBPATH){
/*421:*/
#line 10528 "weaver-interface-metafont.tex"

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
/*:421*/
#line 10407 "weaver-interface-metafont.tex"

}
else if(begin==end&&begin->type==TYPE_SYMBOLIC){
/*422:*/
#line 10619 "weaver-interface-metafont.tex"

{
struct symbolic_token*v= (struct symbolic_token*)begin;
struct path_variable*var= v->var;
if(var==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(begin->line),
v->value);
return false;
}
if(((struct pair_variable*)var)->type==TYPE_T_PAIR){
if(isnan(((struct pair_variable*)var)->x)){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
v->value);
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
v->value);
return false;
}
return recursive_copy_points(mf,cx,temporary_alloc,&result,var,false);
}
else{
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),v->value,
var->type,TYPE_T_PATH);
return false;
}
}
/*:422*/
#line 10410 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*423:*/
#line 10672 "weaver-interface-metafont.tex"

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
/*:423*/
#line 10414 "weaver-interface-metafont.tex"

}
/*465:*/
#line 11685 "weaver-interface-metafont.tex"

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
/*466:*/
#line 11720 "weaver-interface-metafont.tex"

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
/*:466*/
#line 11696 "weaver-interface-metafont.tex"

}
else if(tmp.flags&FLAG_CIRCULAR){
/*467:*/
#line 11742 "weaver-interface-metafont.tex"

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
/*:467*/
#line 11699 "weaver-interface-metafont.tex"

}
else if(tmp.flags&FLAG_SEMICIRCULAR){
/*468:*/
#line 11791 "weaver-interface-metafont.tex"

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
/*:468*/
#line 11702 "weaver-interface-metafont.tex"

}
else if(tmp.flags&FLAG_SQUARE){
/*469:*/
#line 11825 "weaver-interface-metafont.tex"

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
/*:469*/
#line 11705 "weaver-interface-metafont.tex"

}
else{
/*470:*/
#line 11869 "weaver-interface-metafont.tex"

if(!recursive_copy_points(mf,cx,temporary_alloc,&result,tmp.format,false))
return false;
if(temporary_free!=NULL){
temporary_free(tmp.format->points);
temporary_free(tmp.format);
}
/*:470*/
#line 11708 "weaver-interface-metafont.tex"

}
/*471:*/
#line 11884 "weaver-interface-metafont.tex"

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
/*:471*/
#line 11710 "weaver-interface-metafont.tex"

return true;
}
/*:465*/
#line 10416 "weaver-interface-metafont.tex"

{
/*424:*/
#line 10700 "weaver-interface-metafont.tex"

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
/*:424*/
#line 10418 "weaver-interface-metafont.tex"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),TYPE_T_PATH);
return false;
}
/*:417*//*420:*/
#line 10461 "weaver-interface-metafont.tex"

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
/*:420*//*429:*/
#line 10798 "weaver-interface-metafont.tex"

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
/*:429*//*431:*/
#line 10830 "weaver-interface-metafont.tex"

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
/*:431*//*435:*/
#line 10982 "weaver-interface-metafont.tex"

bool assign_pen_variable(struct metafont*mf,
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


if(target==&(mf->internal_pen_variables[INTERNAL_PEN_CURRENTPEN]))
triangulate_pen(mf,target,target->gl_matrix);
return true;
}
/*:435*//*437:*/
#line 11045 "weaver-interface-metafont.tex"

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
/*:437*//*439:*/
#line 11105 "weaver-interface-metafont.tex"

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
/*440:*/
#line 11174 "weaver-interface-metafont.tex"

struct numeric_variable r;
double rotation;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&r))
return false;
rotation= 0.017453292519943295*r.value;
TRANSFORM_ROTATE(pen->gl_matrix,rotation);
return true;
/*:440*/
#line 11136 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*441:*/
#line 11189 "weaver-interface-metafont.tex"

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
/*:441*/
#line 11139 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*442:*/
#line 11208 "weaver-interface-metafont.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&p))
return false;
TRANSFORM_SHIFT(pen->gl_matrix,p.x,p.y);
return true;
/*:442*/
#line 11142 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*443:*/
#line 11220 "weaver-interface-metafont.tex"

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
/*:443*/
#line 11145 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*444:*/
#line 11241 "weaver-interface-metafont.tex"

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
/*:444*/
#line 11148 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*445:*/
#line 11260 "weaver-interface-metafont.tex"

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
/*:445*/
#line 11151 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*446:*/
#line 11285 "weaver-interface-metafont.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&p))
return false;
TRANSFORM_SCALE_Z(pen->gl_matrix,p.x,p.y);

if(pen->gl_vbo!=0&&!(pen->flags&FLAG_STRAIGHT)){
glDeleteBuffers(1,&(pen->gl_vbo));
pen->gl_vbo= 0;
pen->indices= 0;
}
return true;
/*:446*/
#line 11154 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*447:*/
#line 11304 "weaver-interface-metafont.tex"

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
/*:447*/
#line 11157 "weaver-interface-metafont.tex"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PEN);
return false;
}
}
/*:439*//*451:*/
#line 11366 "weaver-interface-metafont.tex"

bool eval_pen_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct pen_variable*result){
if(begin==end){
if(begin->type==TYPE_SYMBOLIC){
/*452:*/
#line 11409 "weaver-interface-metafont.tex"

struct symbolic_token*v= (struct symbolic_token*)begin;
struct pen_variable*content= v->var,*to_copy= v->var;
if(content==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(v->line),v->value);
return false;
}
if(content->type!=TYPE_T_PEN){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),v->value,
((struct variable*)(v->var))->type,
TYPE_T_PEN);
return false;
}
if(content->format==NULL&&content->flags==false){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(v->line),v->value);
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
/*:452*/
#line 11373 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_NULLPEN){
/*453:*/
#line 11444 "weaver-interface-metafont.tex"

result->format= NULL;
result->flags= FLAG_NULL;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:453*/
#line 11376 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_PENCIRCLE){
/*454:*/
#line 11460 "weaver-interface-metafont.tex"

result->format= NULL;
result->flags= FLAG_CONVEX|FLAG_CIRCULAR;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:454*/
#line 11379 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_PENSEMICIRCLE){
/*455:*/
#line 11474 "weaver-interface-metafont.tex"

result->format= NULL;
result->flags= FLAG_CONVEX|FLAG_SEMICIRCULAR;
result->referenced= NULL;
result->gl_vbo= 0;
result->indices= 0;
INITIALIZE_IDENTITY_MATRIX(result->gl_matrix);
return true;
/*:455*/
#line 11382 "weaver-interface-metafont.tex"

}

}
else{
if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*456:*/
#line 11490 "weaver-interface-metafont.tex"

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
/*:456*/
#line 11389 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_MAKEPEN){
/*457:*/
#line 11512 "weaver-interface-metafont.tex"

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
/*:457*/
#line 11392 "weaver-interface-metafont.tex"

}
}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PEN);
return false;
}
/*:451*//*462:*/
#line 11580 "weaver-interface-metafont.tex"

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
/*:462*//*479:*/
#line 12066 "weaver-interface-metafont.tex"

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
/*:479*//*483:*/
#line 12149 "weaver-interface-metafont.tex"

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
/*:483*//*485:*/
#line 12188 "weaver-interface-metafont.tex"

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
/*:485*//*487:*/
#line 12250 "weaver-interface-metafont.tex"

bool assign_picture_variable(struct metafont*mf,
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
if(target==
&(mf->internal_picture_variables[INTERNAL_PICTURE_CURRENTPICTURE])){

/*645:*/
#line 17973 "weaver-interface-metafont.tex"

{
if(currentpicture_fb!=0){
glBindFramebuffer(GL_FRAMEBUFFER,0);
glBindTexture(GL_TEXTURE_2D,0);
glDeleteFramebuffers(1,&currentpicture_fb);
}
currentpicture_fb= 0;
}
/*:645*/
#line 12275 "weaver-interface-metafont.tex"

}
return true;
}
/*:487*//*492:*/
#line 12350 "weaver-interface-metafont.tex"

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
/*497:*/
#line 12577 "weaver-interface-metafont.tex"

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
/*:497*/
#line 12372 "weaver-interface-metafont.tex"

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
/*497:*/
#line 12577 "weaver-interface-metafont.tex"

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
/*:497*/
#line 12385 "weaver-interface-metafont.tex"

/*496:*/
#line 12482 "weaver-interface-metafont.tex"


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
/*:496*/
#line 12386 "weaver-interface-metafont.tex"

if(a.texture!=0)
glDeleteTextures(1,&(a.texture));
if(b.texture!=0)
glDeleteTextures(1,&(b.texture));
return true;
}
}
/*:492*//*499:*/
#line 12625 "weaver-interface-metafont.tex"

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
/*501:*/
#line 12710 "weaver-interface-metafont.tex"

struct numeric_variable r;
double rotation;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&r))
return false;
rotation= 0.017453292519943295*r.value;
TRANSFORM_ROTATE(matrix,rotation);
*modified= true;
return true;
/*:501*/
#line 12658 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SCALED){
/*500:*/
#line 12697 "weaver-interface-metafont.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE(matrix,a.value);
*modified= true;
return true;
/*:500*/
#line 12661 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SHIFTED){
/*502:*/
#line 12728 "weaver-interface-metafont.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&p))
return false;
p.x= 2.0*(p.x/result->width);
p.y= 2.0*(p.y/result->height);
TRANSFORM_SHIFT(matrix,p.x,p.y);
*modified= true;
return true;
/*:502*/
#line 12664 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_SLANTED){
/*503:*/
#line 12743 "weaver-interface-metafont.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SLANT(matrix,a.value);
*modified= true;
return true;
/*:503*/
#line 12667 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_XSCALED){
/*504:*/
#line 12756 "weaver-interface-metafont.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE_X(matrix,a.value);
*modified= true;
return true;
/*:504*/
#line 12670 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_YSCALED){
/*505:*/
#line 12769 "weaver-interface-metafont.tex"

struct numeric_variable a;
if(!eval_numeric_primary(mf,cx,last_transformer->next,end,&a))
return false;
TRANSFORM_SCALE_Y(matrix,a.value);
*modified= true;
return true;
/*:505*/
#line 12673 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_ZSCALED){
/*506:*/
#line 12783 "weaver-interface-metafont.tex"

struct pair_variable p;
if(!eval_pair_primary(mf,cx,last_transformer->next,end,&p))
return false;
TRANSFORM_SCALE_Z(matrix,p.x,p.y);
*modified= true;
return true;
/*:506*/
#line 12676 "weaver-interface-metafont.tex"

}
else if(last_transformer->type==TYPE_TRANSFORMED){
/*507:*/
#line 12797 "weaver-interface-metafont.tex"

struct transform_variable t;
if(!eval_transform_primary(mf,cx,last_transformer->next,end,&t))
return false;
MATRIX_MULTIPLICATION(matrix,t.value);
*modified= true;
return true;
/*:507*/
#line 12679 "weaver-interface-metafont.tex"

}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
}
/*:499*//*509:*/
#line 12850 "weaver-interface-metafont.tex"

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
dst->height))
return false;

render_picture(origin,matrix,dst->width,dst->height,true);

glBindFramebuffer(GL_FRAMEBUFFER,previous_framebuffer);
glDeleteFramebuffers(1,&temporary_framebuffer);
return true;
}
/*:509*//*513:*/
#line 12959 "weaver-interface-metafont.tex"

bool eval_picture_primary(struct metafont*mf,struct context*cx,
struct generic_token*begin,
struct generic_token*end,
struct picture_variable*result){
if(begin==end){
if(begin->type==TYPE_SYMBOLIC){
/*514:*/
#line 12999 "weaver-interface-metafont.tex"

GLuint temporary_framebuffer= 0;
GLint previous_framebuffer;
float identity_matrix[9]= {1.0,0.0,0.0,
0.0,1.0,0.0,
0.0,0.0,1.0};
struct symbolic_token*v= (struct symbolic_token*)begin;
struct picture_variable*content= v->var;
if(content==NULL){
RAISE_ERROR_UNDECLARED_VARIABLE(mf,cx,OPTIONAL(v->line),v->value);
return false;
}
if(content->width==-1&&content->height==-1){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(v->line),v->value);
return false;
}
if(content->type!=TYPE_T_PICTURE){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(v->line),v->value,
((struct variable*)(v->var))->type,
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
/*:514*/
#line 12966 "weaver-interface-metafont.tex"

}
}
else{
if(begin->type==TYPE_OPEN_PARENTHESIS&&
end->type==TYPE_CLOSE_PARENTHESIS){
/*515:*/
#line 13042 "weaver-interface-metafont.tex"

struct generic_token*t= begin->next;
if(begin->next==end){
RAISE_ERROR_EMPTY_DELIMITER(mf,cx,OPTIONAL(begin->line),'(');
return false;
}
while(t!=NULL&&t->next!=end)
t= t->next;
return eval_picture_expression(mf,cx,begin->next,t,result);
/*:515*/
#line 12972 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_NULLPICTURE){
/*516:*/
#line 13061 "weaver-interface-metafont.tex"

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
/*:516*/
#line 12975 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_SUM){
/*517:*/
#line 13108 "weaver-interface-metafont.tex"

struct generic_token*p= begin->next;
if(begin==end){
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
return eval_picture_primary(mf,cx,p,end,result);
/*:517*/
#line 12978 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_SUBTRACT){
/*518:*/
#line 13128 "weaver-interface-metafont.tex"

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
/*:518*/
#line 12981 "weaver-interface-metafont.tex"

}
else if(begin->type==TYPE_SUBPICTURE){
/*519:*/
#line 13178 "weaver-interface-metafont.tex"

struct pair_variable pair_offset,subpicture_size;
struct picture_variable original_picture;
/*520:*/
#line 13195 "weaver-interface-metafont.tex"

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
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(p->line),TYPE_AND);
return false;
}
end_pair1= last_token;
state++;
begin_pair2= p->next;
}
else if(IS_NOT_NESTED()&&p->type==TYPE_OF){
if(state!=1||last_token->type==TYPE_AND){
RAISE_ERROR_UNEXPECTED_TOKEN(mf,cx,OPTIONAL(p->line),TYPE_OF);
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
/*:520*/
#line 13181 "weaver-interface-metafont.tex"

/*521:*/
#line 13256 "weaver-interface-metafont.tex"

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
/*:521*/
#line 13182 "weaver-interface-metafont.tex"

return false;
/*:519*/
#line 12984 "weaver-interface-metafont.tex"

}
}
RAISE_ERROR_UNKNOWN_EXPRESSION(mf,cx,OPTIONAL(begin->line),
TYPE_T_PICTURE);
return false;
}
/*:513*//*531:*/
#line 13543 "weaver-interface-metafont.tex"

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
RAISE_ERROR_INVALID_COMPARISON(mf,cx,OPTIONAL(begin->line));
return false;
}
return true;
}
}
/*:531*//*538:*/
#line 13810 "weaver-interface-metafont.tex"

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
/*:538*//*540:*/
#line 13880 "weaver-interface-metafont.tex"

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
/*:540*//*544:*/
#line 13975 "weaver-interface-metafont.tex"

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
symbol->value);
return false;
}
if(var->type!=TYPE_T_BOOLEAN){
RAISE_ERROR_WRONG_VARIABLE_TYPE(mf,cx,OPTIONAL(begin->line),
symbol->value,var->type,
TYPE_T_BOOLEAN);
return false;
}
if(var->value==-1){
RAISE_ERROR_UNINITIALIZED_VARIABLE(mf,cx,OPTIONAL(begin->line),
symbol->value);
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
/*:544*//*546:*/
#line 14144 "weaver-interface-metafont.tex"

int get_primary_expression_type(struct metafont*mf,struct context*cx,
struct generic_token*begin_expr,
struct generic_token*end_expr){
if(begin_expr==end_expr){
if(begin_expr->type==TYPE_SYMBOLIC){
struct variable*var= (struct variable*)
((struct symbolic_token*)begin_expr)->var;
if(var==NULL)
return-1;
else
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
/*:546*//*547:*/
#line 14260 "weaver-interface-metafont.tex"

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
/*:547*//*548:*/
#line 14335 "weaver-interface-metafont.tex"

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
t->type==TYPE_LEQ||t->type==TYPE_EQUAL||
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
/*:548*//*565:*/
#line 14892 "weaver-interface-metafont.tex"

void pencircular_extremity_points(struct metafont*mf,float*matrix,
bool fullcircle){
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
/*:565*//*567:*/
#line 15009 "weaver-interface-metafont.tex"

void path_extremity_points(struct metafont*mf,struct path_variable*p,
float*matrix){
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
/*:567*//*570:*/
#line 15131 "weaver-interface-metafont.tex"

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
/*:570*//*572:*/
#line 15194 "weaver-interface-metafont.tex"

bool triangulate_pen(struct metafont*mf,struct pen_variable*pen,
float*transform_matrix){
/*573:*/
#line 15215 "weaver-interface-metafont.tex"

if((pen->flags&FLAG_NULL)){
pen->indices= 0;
DECLARE_PEN_EXTREMITIES();
CHECK_PEN_EXTREMITIES(0,0,transform_matrix);
UPDATE_PEN_EXTREMITIES();
return true;
}
/*:573*/
#line 15197 "weaver-interface-metafont.tex"

/*577:*/
#line 15267 "weaver-interface-metafont.tex"

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
/*:577*/
#line 15198 "weaver-interface-metafont.tex"

/*578:*/
#line 15295 "weaver-interface-metafont.tex"

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
/*:578*/
#line 15199 "weaver-interface-metafont.tex"

/*579:*/
#line 15381 "weaver-interface-metafont.tex"

if((pen->flags&FLAG_CIRCULAR)||(pen->flags&FLAG_SEMICIRCULAR)){
float radius;
GLsizei size;

pencircular_extremity_points(mf,transform_matrix,
(pen->flags&FLAG_CIRCULAR));

{
float side1,side2;
side1= fabs(mf->pen_rt-mf->pen_lft);
side2= fabs(mf->pen_top-mf->pen_bot);
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
int i;
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
/*:579*/
#line 15200 "weaver-interface-metafont.tex"

/*580:*/
#line 15484 "weaver-interface-metafont.tex"

if((pen->flags&FLAG_CONVEX)){
bool counterclockwise= is_pen_counterclockwise(pen);
int i,number_of_vertices= 1;

path_extremity_points(mf,pen->format,transform_matrix);


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
/*:580*/
#line 15201 "weaver-interface-metafont.tex"

/*596:*/
#line 16251 "weaver-interface-metafont.tex"

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
/*623:*/
#line 17235 "weaver-interface-metafont.tex"

{
int i;
float*last_triang= triang;
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

/*626:*/
#line 17335 "weaver-interface-metafont.tex"

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
/*:626*//*627:*/
#line 17361 "weaver-interface-metafont.tex"

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
/*:627*//*628:*/
#line 17396 "weaver-interface-metafont.tex"

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
/*:628*//*629:*/
#line 17431 "weaver-interface-metafont.tex"

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
if(GET_VERTEX_TYPE(removed->helper)==TYPE_MERGE_VERTEX)
ADD_CUT(current_vertex,removed->helper);
DESTROY_POLYGON_EDGE(removed);
below= find_edge_below(imaginary_line,current_vertex->x,
current_vertex->y);
if(GET_VERTEX_TYPE(below->helper)==TYPE_MERGE_VERTEX)
ADD_CUT(current_vertex,below->helper);
below->helper= current_vertex;
}
/*:629*//*630:*/
#line 17479 "weaver-interface-metafont.tex"

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
if(GET_VERTEX_TYPE(removed->helper)==TYPE_MERGE_VERTEX)
ADD_CUT(current_vertex,removed->helper);
DESTROY_POLYGON_EDGE(removed);
insert_polygon_edge(&imaginary_line,current_vertex->x,
current_vertex->y,to_append->x,
to_append->y,current_vertex,leq_by_vertex,NULL);
}
else{
struct polygon_edge*below;
below= find_edge_below(imaginary_line,current_vertex->x,
current_vertex->y);
if(GET_VERTEX_TYPE(below->helper)==TYPE_MERGE_VERTEX)
ADD_CUT(current_vertex,below->helper);
below->helper= current_vertex;
}
}
/*:630*/
#line 17255 "weaver-interface-metafont.tex"

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
triangulate_polygon_tree(list_of_subpolygons,&last_triang,
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
/*:623*/
#line 16301 "weaver-interface-metafont.tex"

}
}
return false;
/*:596*/
#line 15202 "weaver-interface-metafont.tex"

}
/*:572*//*584:*/
#line 15742 "weaver-interface-metafont.tex"

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
/*:584*//*586:*/
#line 15771 "weaver-interface-metafont.tex"

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
/*:586*//*588:*/
#line 15934 "weaver-interface-metafont.tex"

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
/*:588*//*590:*/
#line 16050 "weaver-interface-metafont.tex"

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
/*:590*//*592:*/
#line 16091 "weaver-interface-metafont.tex"

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
ADD_DIAGONAL(data,stack[0],stack[stack_size-1]);
DESTROY_POLYGON_VERTEX(stack[0]);
DESTROY_POLYGON_VERTEX(stack[stack_size-1]);
}
*triangles= data;
return true;
}
/*:592*//*599:*/
#line 16421 "weaver-interface-metafont.tex"

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
/*:599*//*600:*/
#line 16467 "weaver-interface-metafont.tex"

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
/*:600*//*602:*/
#line 16523 "weaver-interface-metafont.tex"

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
{
struct polygon_vertex*tmp= p;
unsigned current_flag= (turn_left)?(FLAG_LOWER):(FLAG_UPPER);
while(tmp->succ!=NULL){
tmp->flag|= current_flag;
tmp= tmp->next;
}
tmp->flag|= current_flag;
tmp= p;
current_flag= (current_flag==FLAG_LOWER)?(FLAG_UPPER):(FLAG_LOWER);
while(tmp->succ!=NULL){
tmp->flag|= current_flag;
tmp= tmp->prev;
}
tmp->flag|= current_flag;
}
}
/*:602*//*604:*/
#line 16593 "weaver-interface-metafont.tex"

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
/*:604*//*607:*/
#line 16681 "weaver-interface-metafont.tex"

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
/*:607*//*609:*/
#line 16757 "weaver-interface-metafont.tex"

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
return(slope*p1->x1+b<=p1->y1);
else
return(slope*p1->x2+b<=p1->y2);
}
}
/*:609*//*611:*/
#line 16811 "weaver-interface-metafont.tex"

static bool eq_by_vertex(struct polygon_edge*p1,struct polygon_edge*p2){
return(p1->x1==p2->x1&&p1->y1==p2->y1&&
p1->x2==p2->x2&&p1->y2==p2->y2)||
(p1->x1==p2->x2&&p1->y1==p2->y2&&
p1->x2==p2->x1&&p1->y2==p2->y1);
}
/*:611*//*613:*/
#line 16835 "weaver-interface-metafont.tex"

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
struct polygon_edge*max= current;
while(max->right!=NULL)
max= max->right;
max->parent->right= max->left;
max->left= NULL;
max->right= current->right;
max->left= current->left;
*tree= max;
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
/*:613*//*615:*/
#line 16905 "weaver-interface-metafont.tex"

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
/*:615*//*617:*/
#line 16945 "weaver-interface-metafont.tex"

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

aux_update_flags(v1);
aux_update_flags(v2);
aux_update_flags(vv1);
aux_update_flags(vv2);

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
/*:617*//*619:*/
#line 17089 "weaver-interface-metafont.tex"

static void aux_update_flags(struct polygon_vertex*v){

if(XMONOTONE_LEQ(v,v->prev)&&XMONOTONE_LEQ(v,v->next))
v->flag+= FLAG_UPPER+FLAG_LOWER;

else if(XMONOTONE_LEQ(v->prev,v)&&XMONOTONE_LEQ(v->next,v))
v->flag+= FLAG_UPPER+FLAG_LOWER;

else if(v->next->next==v->prev||
v->next->next==v->prev->prev){
struct polygon_vertex*begin,*end;
float m,b;
begin= end= v;
if(begin->next->x<=begin->x){
while(begin->next->x<=begin->x)
begin= begin->next;
}
else{
while(begin->prev->x<=begin->x)
begin= begin->prev;
}
if(end->next->x>=end->x){
while(end->next->x>=end->x)
end= end->next;
}
else{
while(end->prev->x>=end->x)
end= end->prev;
}
m= (end->y-begin->y)/(end->x-begin->x);
b= begin->y-m*(begin->x);
if(v->y>=m*v->x+b)
v->flag+= FLAG_UPPER;
else
v->flag+= FLAG_LOWER;
}
else if((XMONOTONE_LEQ(v->next,v->next->next)&&
XMONOTONE_LEQ(v->next,v))||(XMONOTONE_LEQ(v,v->next)&&
XMONOTONE_LEQ(v->next->next,v->next))){

if((XMONOTONE_LEQ(v->prev,v->prev->prev)&&
XMONOTONE_LEQ(v->prev,v))||(XMONOTONE_LEQ(v,v->prev)&&
XMONOTONE_LEQ(v->prev->prev,v->prev))){
struct polygon_vertex*aux;
aux= v->next->next;
if((aux->flag%4)==0x0)
aux= aux->next;
v->flag+= (~(aux->flag%4));
}

else{
if(v->prev->flag%4!=0)
v->flag+= (v->prev->flag%4);
else if(v->prev->prev->flag%4!=3)
v->flag+= (v->prev->prev->flag%4);
else
v->flag+= ~(v->prev->prev->prev->flag%4);
}
}

else{
if(v->next->flag%4!=0)
v->flag+= (v->next->flag%4);
else if(v->next->next->flag%4!=3)
v->flag+= (v->next->next->flag%4);
else
v->flag+= ~(v->next->next->next->flag%4);
}
}
/*:619*//*622:*/
#line 17221 "weaver-interface-metafont.tex"

static bool leq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2){
return(p1->helper<=p2->helper);
}
static bool eq_by_helper(struct polygon_edge*p1,struct polygon_edge*p2){
return(p1->helper==p2->helper);
}
/*:622*//*625:*/
#line 17303 "weaver-interface-metafont.tex"

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
triangulate_xmonotone_polygon(tree->helper,triangles,
number_of_triangles,buffer);
DESTROY_POLYGON_EDGE(tree);
return;
}
/*:625*//*655:*/
#line 18150 "weaver-interface-metafont.tex"

#define ERASE_FLAG 1
bool drawing_commands(struct metafont*mf,struct context*cx,
struct path_variable*path,unsigned int flags){
int i,j;
float transform_matrix[9];
struct pen_variable*currentpen= &(mf->internal_pen_variables[0]);
struct picture_variable*currentpicture= 
&(mf->internal_picture_variables[0]);

if(currentpen->referenced!=NULL){
memcpy(transform_matrix,currentpen->referenced->gl_matrix,
9*sizeof(float));
MATRIX_MULTIPLICATION(transform_matrix,currentpen->gl_matrix);
currentpen= currentpen->referenced;
}
else
memcpy(transform_matrix,currentpen->gl_matrix,9*sizeof(float));
/*644:*/
#line 17937 "weaver-interface-metafont.tex"

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
if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE){
RAISE_ERROR_OPENGL_FRAMEBUFFER(mf,cx,0);
return false;
}
}
else
glBindFramebuffer(GL_FRAMEBUFFER,currentpicture_fb);
}
/*:644*/
#line 18168 "weaver-interface-metafont.tex"

glEnable(GL_BLEND);
if(flags&ERASE_FLAG){
glBlendFunc(GL_ONE,GL_ONE);
glBlendEquationSeparate(GL_MAX,GL_FUNC_REVERSE_SUBTRACT);
}
else{
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBlendEquation(GL_FUNC_ADD);
}

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
drawpoint(mf,currentpen,currentpicture,x,y,transform_matrix,
flags&ERASE_FLAG);
}
}

if(path->length==1)
drawpoint(mf,currentpen,currentpicture,path->points[0].point.x,
path->points[0].point.y,transform_matrix,flags&ERASE_FLAG);

glDisable(GL_BLEND);
return true;
}
/*:655*//*659:*/
#line 18319 "weaver-interface-metafont.tex"

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
gl_matrix[7]= 2*(matrix[7]+mf->current_depth+y)/pic->height-
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
if(pen->flags&FLAG_CONVEX)
glDrawArrays(GL_TRIANGLE_FAN,0,pen->indices);
else
glDrawArrays(GL_TRIANGLES,0,pen->indices);

}
/*:659*//*666:*/
#line 18505 "weaver-interface-metafont.tex"

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
else if(c[0]>=192&&c[0]<=223&&c[1]>=128&&c[1]<=159){
code_point= c[1]-128;
code_point+= (c[0]-192)*64;
}
else if(c[0]>=224&&c[0]<=239&&c[1]>=128&&c[1]<=159&&
c[2]>=128&&c[2]<=159){
code_point= c[2]-128;
code_point+= (c[1]-128)*64;
code_point+= (c[0]-224)*4096;
}
else if(c[0]>=240&&c[0]<=247&&c[1]>=128&&c[1]<=159&&
c[2]>=128&&c[2]<=159&&c[3]>=128&&c[3]<=159){
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
return&(mf->glyphs[block][index]);
}
/*:666*/
#line 449 "weaver-interface-metafont.tex"

/*30:*/
#line 1004 "weaver-interface-metafont.tex"

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
/*474:*/
#line 11991 "weaver-interface-metafont.tex"

glGenBuffers(1,&vbo);
glBindBuffer(GL_ARRAY_BUFFER,vbo);

glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
/*:474*//*480:*/
#line 12116 "weaver-interface-metafont.tex"

{
program= compile_shader_program(vertex_shader,fragment_shader);
if(program==0)
return false;
uniform_matrix= glGetUniformLocation(program,"model_view_matrix");
uniform_texture= glGetUniformLocation(program,"texture1");
}
/*:480*//*494:*/
#line 12460 "weaver-interface-metafont.tex"

{
inv_program= compile_shader_program(vertex_shader,fragment_shader_inverse);
uniform_inv_matrix= glGetUniformLocation(inv_program,"model_view_matrix");
uniform_inv_texture= glGetUniformLocation(inv_program,"texture1");
}
/*:494*//*575:*/
#line 15240 "weaver-interface-metafont.tex"

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
/*:575*//*643:*/
#line 17927 "weaver-interface-metafont.tex"

currentpicture_fb= 0;
/*:643*//*651:*/
#line 18084 "weaver-interface-metafont.tex"

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
/*:651*/
#line 1016 "weaver-interface-metafont.tex"

return true;
}
/*:30*//*31:*/
#line 1027 "weaver-interface-metafont.tex"

void _Wfinish_weavefont(void){
/*475:*/
#line 12002 "weaver-interface-metafont.tex"

glDeleteBuffers(1,&vbo);
/*:475*//*481:*/
#line 12130 "weaver-interface-metafont.tex"

glDeleteProgram(program);
/*:481*//*495:*/
#line 12472 "weaver-interface-metafont.tex"

glDeleteProgram(inv_program);
/*:495*//*576:*/
#line 15257 "weaver-interface-metafont.tex"

glDeleteBuffers(1,&pensquare_vbo);
/*:576*//*652:*/
#line 18101 "weaver-interface-metafont.tex"

glDeleteProgram(pen_program);
glDeleteProgram(pen_erase_program);
/*:652*/
#line 1029 "weaver-interface-metafont.tex"

}
/*:31*//*69:*/
#line 1929 "weaver-interface-metafont.tex"

void _Wdestroy_metafont(struct metafont*mf){
if(permanent_free!=NULL){
permanent_free(mf->file);

/*82:*/
#line 2179 "weaver-interface-metafont.tex"

if(mf->errno_str!=NULL&&permanent_free!=NULL)
permanent_free(mf->errno_str);
/*:82*//*116:*/
#line 2893 "weaver-interface-metafont.tex"

if(permanent_free!=NULL){
struct variable*v= (struct variable*)(mf->variables);
struct variable*next;
while(v!=NULL){
next= (struct variable*)(v->next);
/*153:*/
#line 3652 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&permanent_free!=NULL)
path_recursive_free(permanent_free,path,false);
}
/*:153*//*194:*/
#line 5143 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&permanent_free!=NULL)
path_recursive_free(permanent_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
/*:194*//*204:*/
#line 5320 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:204*/
#line 2899 "weaver-interface-metafont.tex"

permanent_free(v);
v= next;
}
}
/*:116*//*117:*/
#line 2912 "weaver-interface-metafont.tex"

if(permanent_free!=NULL){
struct named_variable*named= (struct named_variable*)
(mf->named_variables);
struct named_variable*next;
while(named!=NULL){
struct variable*v= (struct variable*)(named->var);
next= (struct named_variable*)(named->next);
permanent_free(named->name);
/*153:*/
#line 3652 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PATH){
struct path_variable*path= (struct path_variable*)v;
if(path->length!=-1&&permanent_free!=NULL)
path_recursive_free(permanent_free,path,false);
}
/*:153*//*194:*/
#line 5143 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PEN){
struct pen_variable*pen= (struct pen_variable*)v;
if(pen->format!=NULL&&permanent_free!=NULL)
path_recursive_free(permanent_free,pen->format,true);
if(pen->gl_vbo!=0)
glDeleteBuffers(1,&(pen->gl_vbo));
}
/*:194*//*204:*/
#line 5320 "weaver-interface-metafont.tex"

if(v->type==TYPE_T_PICTURE){
struct picture_variable*pic= (struct picture_variable*)v;
if(pic->texture!=0)
glDeleteTextures(1,&(pic->texture));
}
/*:204*/
#line 2921 "weaver-interface-metafont.tex"

permanent_free(v);
permanent_free(named);
named= next;
}
}
/*:117*//*138:*/
#line 3328 "weaver-interface-metafont.tex"

if(permanent_free!=NULL)
permanent_free(mf->internal_numeric_variables);
/*:138*//*146:*/
#line 3482 "weaver-interface-metafont.tex"

if(permanent_free!=NULL)
permanent_free(mf->internal_transform_variables);
/*:146*//*199:*/
#line 5236 "weaver-interface-metafont.tex"

if(permanent_free!=NULL){
if(mf->internal_pen_variables[1].format!=NULL){
permanent_free(mf->internal_pen_variables[1].format->points);
permanent_free(mf->internal_pen_variables[1].format);
}
permanent_free(mf->internal_pen_variables);
}
/*:199*//*209:*/
#line 5386 "weaver-interface-metafont.tex"

if(mf->internal_picture_variables[0].texture!=0)
glDeleteTextures(1,&(mf->internal_picture_variables[0].texture));
if(permanent_free!=NULL)
permanent_free(mf->internal_picture_variables);
/*:209*//*667:*/
#line 18622 "weaver-interface-metafont.tex"

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
/*:667*/
#line 1934 "weaver-interface-metafont.tex"

MUTEX_DESTROY(mf->mutex);
permanent_free(mf);
}
}
/*:69*//*75:*/
#line 2050 "weaver-interface-metafont.tex"

void _Wprint_metafont_error(struct metafont*mf){
char*line_number;


int str_size= 128;
line_number= (char*)temporary_alloc(str_size);

if(mf->errno_line==0)
line_number[0]= '\0';
else
sprintf(line_number,"%d: ",mf->errno_line);
switch(mf->errno){
case ERROR_NO_ERROR:
fprintf(stderr,"%s:%s No errors.",mf->file,line_number);
break;
/*81:*/
#line 2156 "weaver-interface-metafont.tex"

case ERROR_NO_MEMORY:
fprintf(stderr,"%s:%s Not enough memory for allocation.",mf->file,
line_number);
break;
case ERROR_INVALID_CHAR:
fprintf(stderr,"%s:%s Unsupported character in source code: '%x'.",
mf->file,line_number,(unsigned)mf->errno_int);
break;
case ERROR_UNCLOSED_STRING:
fprintf(stderr,"%s:%s Unclosed string \"%s\".",mf->file,
line_number,mf->errno_str);
break;
/*:81*//*92:*/
#line 2443 "weaver-interface-metafont.tex"

case ERROR_UNKNOWN_STATEMENT:
fprintf(stderr,"%s:%s Unknown statement. Perhaps you misspelled some "
"operator, forgot an assignment or placed a ';' in the wrong "
"place.",mf->file,line_number);
break;
/*:92*//*102:*/
#line 2640 "weaver-interface-metafont.tex"

case ERROR_UNEXPECTED_TOKEN:
fprintf(stderr,"%s:%s We found '%s' token in a context where such "
"token makes no sense.",mf->file,line_number,
((mf->errno_int<8)?
(token_names_not_in_list_of_keywords[mf->errno_int]):
(list_of_keywords[mf->errno_int-8])));
break;
case ERROR_EXPECTED_FOUND:
fprintf(stderr,"%s:%s Expected '%s' token. Found '%s' token.",
mf->file,line_number,mf->errno_str,
((mf->errno_int<8)?
(token_names_not_in_list_of_keywords[mf->errno_int]):
(list_of_keywords[mf->errno_int-8])));
break;
/*:102*//*108:*/
#line 2757 "weaver-interface-metafont.tex"

case ERROR_UNFINISHED_STATEMENT:
fprintf(stderr,"%s:%s Unfinished statement '%s'.",
mf->file,line_number,list_of_keywords[mf->errno_int-8]);
break;
/*:108*//*124:*/
#line 3032 "weaver-interface-metafont.tex"

case ERROR_INVALID_NAME:
fprintf(stderr,"%s:%s You cannot name a variable with a reserved "
"word or with non-symbolic tokens. Found '%s' as variable "
"name.",mf->file,line_number,
((mf->errno_int<8)?
(token_names_not_in_list_of_keywords[mf->errno_int]):
(list_of_keywords[mf->errno_int-8])));
break;
/*:124*//*218:*/
#line 5603 "weaver-interface-metafont.tex"

case ERROR_UNDECLARED_VARIABLE:
fprintf(stderr,"%s:%s Variable '%s' was not declared.",mf->file,
line_number,mf->errno_str);
break;
/*:218*//*221:*/
#line 5661 "weaver-interface-metafont.tex"

case ERROR_WRONG_VARIABLE_TYPE:
fprintf(stderr,"%s:%s Found '%s', but a variable of type '%s' was expected.",
mf->file,line_number,mf->errno_str,
list_of_keywords[mf->errno_int-8]);
break;
/*:221*//*223:*/
#line 5703 "weaver-interface-metafont.tex"

case ERROR_MISSING_EXPRESSION:
fprintf(stderr,"%s:%s Missing %s expression.",
mf->file,line_number,list_of_keywords[mf->errno_int-8]);
break;
/*:223*//*233:*/
#line 5916 "weaver-interface-metafont.tex"

case ERROR_UNCLOSED_DELIMITER:
fprintf(stderr,"%s:%s Delimiter '%c' was not closed.",
mf->file,line_number,mf->errno_int);
break;
case ERROR_UNOPENED_DELIMITER:
fprintf(stderr,"%s:%s Delimiter '%c' was not previously opened.",
mf->file,line_number,mf->errno_int);
break;
/*:233*//*238:*/
#line 6094 "weaver-interface-metafont.tex"

case ERROR_NEGATIVE_SQUARE_ROOT:
fprintf(stderr,"%s:%s Tried to compute square root of negative value '%s'.",
mf->file,line_number,mf->errno_str);
break;
/*:238*//*245:*/
#line 6251 "weaver-interface-metafont.tex"

case ERROR_DIVISION_BY_ZERO:
fprintf(stderr,"%s:%s Division by zero.",mf->file,line_number);
break;
/*:245*//*252:*/
#line 6356 "weaver-interface-metafont.tex"

case ERROR_UNKNOWN_EXPRESSION:
fprintf(stderr,"%s:%s Unrecognizable %s expression.",mf->file,
line_number,list_of_keywords[mf->errno_int-8]);
break;
/*:252*//*257:*/
#line 6445 "weaver-interface-metafont.tex"

case ERROR_UNKNOWN_EXPRESSION_TYPE:
if(mf->errno_int==-1)
fprintf(stderr,"%s:%s We could not identity the expression type.",
mf->file,line_number);
else
fprintf(stderr,"%s:%s Found %s expression in a context where such"
"expression was not expected.",mf->file,line_number,
list_of_keywords[mf->errno_int-8]);
break;
/*:257*//*264:*/
#line 6557 "weaver-interface-metafont.tex"

case ERROR_NEGATIVE_LOGARITHM:
fprintf(stderr,"%s:%s Tried to compute logarithm of negative value '%s'.",
mf->file,line_number,mf->errno_str);
break;
/*:264*//*279:*/
#line 6826 "weaver-interface-metafont.tex"

case ERROR_UNINITIALIZED_VARIABLE:
fprintf(stderr,"%s:%s Uninitialized variable '%s'.",
mf->file,line_number,mf->errno_str);
break;
/*:279*//*286:*/
#line 6963 "weaver-interface-metafont.tex"

case ERROR_EMPTY_DELIMITER:
fprintf(stderr,"%s:%s Unexpected empty delimiter '%c%c'.",
mf->file,line_number,mf->errno_int,
((mf->errno_int=='(')?(')'):
((mf->errno_int=='[')?(']'):('}'))));
break;
/*:286*//*319:*/
#line 7836 "weaver-interface-metafont.tex"

case ERROR_ANGLE_OF_ORIGIN:
fprintf(stderr,"%s:%s Undefined operation 'angle (0, 0)'.",
mf->file,line_number);
break;
/*:319*//*377:*/
#line 9414 "weaver-interface-metafont.tex"

case ERROR_DISCONTINUOUS_PATH:
fprintf(stderr,
"%s:%s Trying to concatenate paths without a common extremity.",
mf->file,line_number);
break;
/*:377*//*384:*/
#line 9646 "weaver-interface-metafont.tex"

case ERROR_INVALID_TENSION:
fprintf(stderr,
"%s:%s %s tension value was smaller than 0.75 (Found value: %s).",
mf->file,line_number,(mf->errno_int==0)?"First":"Second",
mf->errno_str);
break;
/*:384*//*460:*/
#line 11556 "weaver-interface-metafont.tex"

case ERROR_NONCYCLICAL_PEN:
fprintf(stderr,"%s:%s Tried to create a pen with non-cyclical format.",
mf->file,line_number);
break;
/*:460*//*490:*/
#line 12304 "weaver-interface-metafont.tex"

case ERROR_OPENGL_FRAMEBUFFER:
fprintf(stderr,"%s:%s OpenGL error. Couldn't create framebuffer for image.",
mf->file,line_number);
break;
/*:490*//*534:*/
#line 13754 "weaver-interface-metafont.tex"

case ERROR_INVALID_COMPARISON:
fprintf(stderr,
"%s:%s Boolean comparison over non-camparable expression type."
" You cannot compare paths, pens or pictures.",
mf->file,line_number);
break;
/*:534*//*554:*/
#line 14564 "weaver-interface-metafont.tex"

case ERROR_MISSING_TOKEN:
fprintf(stderr,"%s:%s We expected to find a '%s' token in the present "
"context, but none was found.",mf->file,line_number,
((mf->errno_int<8)?
(token_names_not_in_list_of_keywords[mf->errno_int]):
(list_of_keywords[mf->errno_int-8])));
break;
/*:554*//*671:*/
#line 18779 "weaver-interface-metafont.tex"

case ERROR_DUPLICATE_GLYPH:
fprintf(stderr,
"%s:%s Glyph '%s' was defined twice by 'beginchar' statement.",
mf->file,line_number,mf->errno_str);
break;
case ERROR_MALFORMED_STATEMENT:
fprintf(stderr,
"%s:%s Malformed '%s' statement.",mf->file,line_number,
list_of_keywords[mf->errno_int-8]);
break;
case ERROR_NESTED_BEGINCHAR:
fprintf(stderr,
"%s:%s Nested 'beginchar' statement.",mf->file,line_number);
break;
/*:671*//*677:*/
#line 18983 "weaver-interface-metafont.tex"

case ERROR_INVALID_DIMENSION_GLYPH:
fprintf(stderr,
"%s:%s You tried to specify a glyph with nonpositive width or "
"non-positive height+depth.",mf->file,line_number);
break;
/*:677*/
#line 2066 "weaver-interface-metafont.tex"

default:
fprintf(stderr,"%s:%s Unknown error.",mf->file,line_number);
}
if(mf->errno_character[0]!='\0'){
fprintf(stderr," (while rendering '%s')\n",mf->errno_character);
}
else
fprintf(stderr,"\n");
if(temporary_free!=NULL)
temporary_free(line_number);
}
/*:75*//*680:*/
#line 19050 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value){
struct named_variable*var= (struct named_variable*)mf->named_variables;
while(var!=NULL){
if(!strcmp(name,var->name)){
struct numeric_variable*n= (struct numeric_variable*)var->var;
if(n->type!=TYPE_T_NUMERIC)
return false;
n->value= value;
{
int i,j;
for(i= 0;i<332;i++){
struct _glyph*g= mf->glyphs[i];
int size= ((i==0)?(greatest_point[0]+1):
(greatest_point[i]-greatest_point[i-1]));
if(g!=NULL){
for(j= 0;j<size;j++)
g[j].need_rendering= true;
}
}
}
return true;
}
var= var->next;
}
return false;
}
/*:680*//*681:*/
#line 19084 "weaver-interface-metafont.tex"

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
/*:681*//*682:*/
#line 19106 "weaver-interface-metafont.tex"

struct metafont*_Wnew_metafont(char*filename){
struct metafont*mf;
struct context*cx;
struct generic_token*first,*last;
bool ret;
mf= init_metafont(filename);
lexer(mf,filename,&first,&last);
cx= init_context(mf);
ret= eval_program(mf,cx,first,last);
destroy_context(mf,cx);
if(!ret){
_Wdestroy_metafont(mf);
return NULL;
}
return mf;
}
/*:682*//*684:*/
#line 19142 "weaver-interface-metafont.tex"

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
cx= init_context(mf);
if(cx==NULL){
MUTEX_SIGNAL(mf->mutex);
return false;
}
if(!eval_list_of_statements(mf,cx,current->begin,current->end)){
destroy_context(mf,cx);
MUTEX_SIGNAL(mf->mutex);
return false;
}
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
destroy_context(mf,cx);
MUTEX_SIGNAL(mf->mutex);
return true;
}
/*:684*/
#line 450 "weaver-interface-metafont.tex"

/*:8*/
