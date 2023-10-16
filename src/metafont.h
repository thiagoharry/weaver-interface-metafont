/*7:*/
#line 388 "weaver-interface-metafont.tex"

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
#line 293 "weaver-interface-metafont.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*24:*/
#line 905 "weaver-interface-metafont.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:24*/
#line 402 "weaver-interface-metafont.tex"

/*607:*/
#line 16633 "weaver-interface-metafont.tex"

struct _glyph;
/*:607*/
#line 403 "weaver-interface-metafont.tex"

/*65:*/
#line 1836 "weaver-interface-metafont.tex"

struct context{
char current_character[5];
/*93:*/
#line 2463 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:93*//*118:*/
#line 2930 "weaver-interface-metafont.tex"

struct variable*variables;
/*:118*//*617:*/
#line 17013 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:617*/
#line 1839 "weaver-interface-metafont.tex"

};
/*:65*//*66:*/
#line 1856 "weaver-interface-metafont.tex"

struct metafont{
/*23:*/
#line 891 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 1858 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*72:*/
#line 1970 "weaver-interface-metafont.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:72*//*114:*/
#line 2865 "weaver-interface-metafont.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:114*//*132:*/
#line 3237 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:132*//*141:*/
#line 3411 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:141*//*189:*/
#line 4872 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:189*//*199:*/
#line 5039 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:199*//*273:*/
#line 6553 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:273*//*555:*/
#line 14845 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:555*//*604:*/
#line 16502 "weaver-interface-metafont.tex"

int current_depth;
/*:604*//*610:*/
#line 16679 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:610*/
#line 1861 "weaver-interface-metafont.tex"

};
/*:66*/
#line 404 "weaver-interface-metafont.tex"

/*1:*/
#line 271 "weaver-interface-metafont.tex"

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
#line 311 "weaver-interface-metafont.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 325 "weaver-interface-metafont.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 347 "weaver-interface-metafont.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 358 "weaver-interface-metafont.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*620:*/
#line 17191 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:620*//*624:*/
#line 17284 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:624*/
#line 405 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
