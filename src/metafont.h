/*7:*/
#line 359 "weaver-interface-metafont_en.tex"

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
#line 273 "weaver-interface-metafont_en.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*20:*/
#line 693 "weaver-interface-metafont_en.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:20*/
#line 373 "weaver-interface-metafont_en.tex"


/*570:*/
#line 15216 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:570*/
#line 375 "weaver-interface-metafont_en.tex"

/*61:*/
#line 1617 "weaver-interface-metafont_en.tex"

struct context{
char current_character[5];
/*89:*/
#line 2222 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:89*//*114:*/
#line 2692 "weaver-interface-metafont_en.tex"

struct variable*variables;
/*:114*//*580:*/
#line 15598 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:580*/
#line 1620 "weaver-interface-metafont_en.tex"

};
/*:61*//*62:*/
#line 1636 "weaver-interface-metafont_en.tex"

struct metafont{
/*19:*/
#line 679 "weaver-interface-metafont_en.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:19*/
#line 1638 "weaver-interface-metafont_en.tex"

char*file;
bool loading;
/*68:*/
#line 1750 "weaver-interface-metafont_en.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:68*//*110:*/
#line 2627 "weaver-interface-metafont_en.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:110*//*128:*/
#line 2994 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:128*//*137:*/
#line 3166 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:137*//*153:*/
#line 3541 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:153*//*163:*/
#line 3707 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:163*//*231:*/
#line 5122 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:231*//*518:*/
#line 13446 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:518*//*567:*/
#line 15085 "weaver-interface-metafont_en.tex"

int current_depth;
/*:567*//*573:*/
#line 15264 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:573*/
#line 1641 "weaver-interface-metafont_en.tex"

};
/*:62*/
#line 376 "weaver-interface-metafont_en.tex"

/*1:*/
#line 252 "weaver-interface-metafont_en.tex"

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
#line 289 "weaver-interface-metafont_en.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 302 "weaver-interface-metafont_en.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 322 "weaver-interface-metafont_en.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 332 "weaver-interface-metafont_en.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*583:*/
#line 15778 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:583*//*587:*/
#line 15870 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:587*/
#line 377 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
