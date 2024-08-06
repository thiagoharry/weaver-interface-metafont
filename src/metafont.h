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

/*672:*/
#line 18710 "weaver-interface-metafont.tex"

struct _glyph;
/*:672*/
#line 411 "weaver-interface-metafont.tex"

/*70:*/
#line 1998 "weaver-interface-metafont.tex"

struct context{
char current_character[5];
/*98:*/
#line 2637 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:98*//*123:*/
#line 3108 "weaver-interface-metafont.tex"

struct variable*variables;
/*:123*//*685:*/
#line 19119 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:685*/
#line 2001 "weaver-interface-metafont.tex"

};
/*:70*//*71:*/
#line 2018 "weaver-interface-metafont.tex"

struct metafont{
/*23:*/
#line 899 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 2020 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*77:*/
#line 2132 "weaver-interface-metafont.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:77*//*119:*/
#line 3043 "weaver-interface-metafont.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:119*//*140:*/
#line 3453 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:140*//*149:*/
#line 3627 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:149*//*201:*/
#line 5352 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:201*//*211:*/
#line 5519 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:211*//*285:*/
#line 7037 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:285*//*573:*/
#line 15122 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:573*//*669:*/
#line 18575 "weaver-interface-metafont.tex"

int current_depth;
/*:669*//*675:*/
#line 18756 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:675*/
#line 2023 "weaver-interface-metafont.tex"

};
/*:71*/
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
/*:6*//*691:*/
#line 19336 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:691*//*695:*/
#line 19429 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:695*/
#line 413 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
