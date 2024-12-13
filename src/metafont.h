/*7:*/
#line 467 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 473 "weaver-interface-metafont.cweb"
#include <stdbool.h>  
#include <stdlib.h>   
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 478 "weaver-interface-metafont.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 481 "weaver-interface-metafont.cweb"
/*2:*/
#line 383 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 387 "weaver-interface-metafont.cweb"
/*:2*//*24:*/
#line 948 "weaver-interface-metafont.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 952 "weaver-interface-metafont.cweb"
/*:24*/
#line 481 "weaver-interface-metafont.cweb"

/*612:*/
#line 17100 "weaver-interface-metafont.cweb"

struct _glyph;
/*:612*/
#line 482 "weaver-interface-metafont.cweb"

/*75:*/
#line 2241 "weaver-interface-metafont.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2580 "weaver-interface-metafont.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*105:*/
#line 2897 "weaver-interface-metafont.cweb"

struct variable*variables;
/*:105*//*120:*/
#line 3202 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*183:*/
#line 5033 "weaver-interface-metafont.cweb"

struct pen_variable*currentpen;
/*:183*//*196:*/
#line 5206 "weaver-interface-metafont.cweb"

struct picture_variable*currentpicture;
/*:196*//*503:*/
#line 13563 "weaver-interface-metafont.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:503*//*582:*/
#line 16471 "weaver-interface-metafont.cweb"

float color[4];
/*:582*//*594:*/
#line 16656 "weaver-interface-metafont.cweb"

GLuint currentpicture_fb;
/*:594*//*609:*/
#line 16971 "weaver-interface-metafont.cweb"

int current_depth;
/*:609*//*622:*/
#line 17450 "weaver-interface-metafont.cweb"

struct _glyph*current_glyph;
/*:622*/
#line 2244 "weaver-interface-metafont.cweb"

};
/*:75*//*76:*/
#line 2259 "weaver-interface-metafont.cweb"

struct metafont{
/*23:*/
#line 936 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 940 "weaver-interface-metafont.cweb"
pthread_mutex_t mutex;
#endif
#line 942 "weaver-interface-metafont.cweb"
/*:23*/
#line 2261 "weaver-interface-metafont.cweb"

char*file;
bool loading;
/*101:*/
#line 2840 "weaver-interface-metafont.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:101*//*119:*/
#line 3194 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:119*//*131:*/
#line 3408 "weaver-interface-metafont.cweb"

struct transform_variable*internal_transform_variables;
/*:131*//*184:*/
#line 5041 "weaver-interface-metafont.cweb"

struct pen_variable*internal_pen_variables;
/*:184*//*239:*/
#line 6244 "weaver-interface-metafont.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:239*//*589:*/
#line 16594 "weaver-interface-metafont.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:589*//*615:*/
#line 17142 "weaver-interface-metafont.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
char first_glyph_symbol[5];
int number_of_glyphs;
/*:615*//*648:*/
#line 18370 "weaver-interface-metafont.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:648*/
#line 2264 "weaver-interface-metafont.cweb"

};
/*:76*/
#line 483 "weaver-interface-metafont.cweb"

/*1:*/
#line 363 "weaver-interface-metafont.cweb"

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
#line 374 "weaver-interface-metafont.cweb"
/*:1*//*3:*/
#line 399 "weaver-interface-metafont.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 411 "weaver-interface-metafont.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 431 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 440 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*625:*/
#line 17626 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:625*//*629:*/
#line 17722 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:629*/
#line 484 "weaver-interface-metafont.cweb"

#ifdef __cplusplus
}
#endif
#line 488 "weaver-interface-metafont.cweb"
#endif
#line 489 "weaver-interface-metafont.cweb"
/*:7*/
