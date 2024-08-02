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

/*662:*/
#line 18390 "weaver-interface-metafont.tex"

struct _glyph;
/*:662*/
#line 411 "weaver-interface-metafont.tex"

/*69:*/
#line 1952 "weaver-interface-metafont.tex"

struct context{
char current_character[5];
/*97:*/
#line 2577 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:97*//*122:*/
#line 3045 "weaver-interface-metafont.tex"

struct variable*variables;
/*:122*//*675:*/
#line 18799 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:675*/
#line 1955 "weaver-interface-metafont.tex"

};
/*:69*//*70:*/
#line 1972 "weaver-interface-metafont.tex"

struct metafont{
/*23:*/
#line 899 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 1974 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*76:*/
#line 2086 "weaver-interface-metafont.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:76*//*118:*/
#line 2980 "weaver-interface-metafont.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:118*//*139:*/
#line 3390 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:139*//*148:*/
#line 3564 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:148*//*200:*/
#line 5289 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:200*//*210:*/
#line 5456 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:210*//*284:*/
#line 6974 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:284*//*563:*/
#line 14802 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:563*//*659:*/
#line 18255 "weaver-interface-metafont.tex"

int current_depth;
/*:659*//*665:*/
#line 18436 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:665*/
#line 1977 "weaver-interface-metafont.tex"

};
/*:70*/
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
/*:6*//*681:*/
#line 19016 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:681*//*685:*/
#line 19109 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:685*/
#line 413 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
