/*7:*/
#line 396 "weaver-interface-metafont.tex"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#include <stdbool.h>  
#include <stdlib.h>   
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
/*2:*/
#line 301 "weaver-interface-metafont.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*24:*/
#line 913 "weaver-interface-metafont.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:24*/
#line 410 "weaver-interface-metafont.tex"

/*611:*/
#line 16519 "weaver-interface-metafont.tex"

struct _glyph;
/*:611*/
#line 411 "weaver-interface-metafont.tex"

/*65:*/
#line 1844 "weaver-interface-metafont.tex"

struct context{
char current_character[5];
/*93:*/
#line 2469 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:93*//*118:*/
#line 2936 "weaver-interface-metafont.tex"

struct variable*variables;
/*:118*//*624:*/
#line 16928 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:624*/
#line 1847 "weaver-interface-metafont.tex"

};
/*:65*//*66:*/
#line 1864 "weaver-interface-metafont.tex"

struct metafont{
/*23:*/
#line 899 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 1866 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*72:*/
#line 1978 "weaver-interface-metafont.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:72*//*114:*/
#line 2871 "weaver-interface-metafont.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:114*//*135:*/
#line 3281 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:135*//*144:*/
#line 3455 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:144*//*196:*/
#line 5181 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:196*//*206:*/
#line 5348 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:206*//*280:*/
#line 6866 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:280*//*559:*/
#line 14690 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:559*//*608:*/
#line 16388 "weaver-interface-metafont.tex"

int current_depth;
/*:608*//*614:*/
#line 16565 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:614*/
#line 1869 "weaver-interface-metafont.tex"

};
/*:66*/
#line 412 "weaver-interface-metafont.tex"

/*1:*/
#line 279 "weaver-interface-metafont.tex"

#if defined(WEAVER_ENGINE)
void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
#endif
/*:1*//*3:*/
#line 319 "weaver-interface-metafont.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 333 "weaver-interface-metafont.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 355 "weaver-interface-metafont.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 366 "weaver-interface-metafont.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*630:*/
#line 17145 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:630*//*634:*/
#line 17238 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:634*/
#line 413 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
