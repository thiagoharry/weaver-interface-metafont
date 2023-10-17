/*7:*/
#line 361 "weaver-interface-metafont_en.tex"

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
#line 275 "weaver-interface-metafont_en.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*24:*/
#line 864 "weaver-interface-metafont_en.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:24*/
#line 375 "weaver-interface-metafont_en.tex"


/*607:*/
#line 16512 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:607*/
#line 377 "weaver-interface-metafont_en.tex"

/*65:*/
#line 1788 "weaver-interface-metafont_en.tex"

struct context{
char current_character[5];
/*93:*/
#line 2393 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:93*//*118:*/
#line 2863 "weaver-interface-metafont_en.tex"

struct variable*variables;
/*:118*//*617:*/
#line 16894 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:617*/
#line 1791 "weaver-interface-metafont_en.tex"

};
/*:65*//*66:*/
#line 1807 "weaver-interface-metafont_en.tex"

struct metafont{
/*23:*/
#line 850 "weaver-interface-metafont_en.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 1809 "weaver-interface-metafont_en.tex"

char*file;
bool loading;
/*72:*/
#line 1921 "weaver-interface-metafont_en.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:72*//*114:*/
#line 2798 "weaver-interface-metafont_en.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:114*//*132:*/
#line 3165 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:132*//*141:*/
#line 3337 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:141*//*190:*/
#line 4903 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:190*//*200:*/
#line 5069 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:200*//*274:*/
#line 6554 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:274*//*555:*/
#line 14738 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:555*//*604:*/
#line 16381 "weaver-interface-metafont_en.tex"

int current_depth;
/*:604*//*610:*/
#line 16560 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:610*/
#line 1812 "weaver-interface-metafont_en.tex"

};
/*:66*/
#line 378 "weaver-interface-metafont_en.tex"

/*1:*/
#line 254 "weaver-interface-metafont_en.tex"

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
#line 291 "weaver-interface-metafont_en.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 304 "weaver-interface-metafont_en.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 324 "weaver-interface-metafont_en.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 334 "weaver-interface-metafont_en.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*620:*/
#line 17074 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:620*//*624:*/
#line 17166 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:624*/
#line 379 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
