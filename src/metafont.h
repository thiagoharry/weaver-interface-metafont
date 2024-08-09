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

/*677:*/
#line 18932 "weaver-interface-metafont.tex"

struct _glyph;
/*:677*/
#line 411 "weaver-interface-metafont.tex"

/*75:*/
#line 2267 "weaver-interface-metafont.tex"

struct context{
char current_character[5];
/*103:*/
#line 2906 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:103*//*128:*/
#line 3377 "weaver-interface-metafont.tex"

struct variable*variables;
/*:128*//*690:*/
#line 19329 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:690*/
#line 2270 "weaver-interface-metafont.tex"

};
/*:75*//*76:*/
#line 2287 "weaver-interface-metafont.tex"

struct metafont{
/*23:*/
#line 899 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 2289 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*82:*/
#line 2401 "weaver-interface-metafont.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:82*//*124:*/
#line 3312 "weaver-interface-metafont.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:124*//*145:*/
#line 3722 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:145*//*154:*/
#line 3896 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:154*//*206:*/
#line 5621 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:206*//*216:*/
#line 5788 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:216*//*290:*/
#line 7306 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:290*//*578:*/
#line 15344 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:578*//*674:*/
#line 18797 "weaver-interface-metafont.tex"

int current_depth;
/*:674*//*680:*/
#line 18978 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:680*/
#line 2292 "weaver-interface-metafont.tex"

};
/*:76*/
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
/*:6*//*696:*/
#line 19546 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:696*//*700:*/
#line 19639 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:700*/
#line 413 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
