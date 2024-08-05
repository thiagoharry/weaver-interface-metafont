/*7:*/
#line 369 "weaver-interface-metafont_en.tex"

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
#line 283 "weaver-interface-metafont_en.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*24:*/
#line 872 "weaver-interface-metafont_en.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:24*/
#line 383 "weaver-interface-metafont_en.tex"


/*671:*/
#line 18428 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:671*/
#line 385 "weaver-interface-metafont_en.tex"

/*70:*/
#line 1942 "weaver-interface-metafont_en.tex"

struct context{
char current_character[5];
/*98:*/
#line 2560 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:98*//*123:*/
#line 3034 "weaver-interface-metafont_en.tex"

struct variable*variables;
/*:123*//*684:*/
#line 18840 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:684*/
#line 1945 "weaver-interface-metafont_en.tex"

};
/*:70*//*71:*/
#line 1961 "weaver-interface-metafont_en.tex"

struct metafont{
/*23:*/
#line 858 "weaver-interface-metafont_en.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 1963 "weaver-interface-metafont_en.tex"

char*file;
bool loading;
/*77:*/
#line 2075 "weaver-interface-metafont_en.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:77*//*119:*/
#line 2969 "weaver-interface-metafont_en.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:119*//*140:*/
#line 3372 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:140*//*149:*/
#line 3544 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:149*//*200:*/
#line 5236 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:200*//*210:*/
#line 5402 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:210*//*284:*/
#line 6889 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:284*//*572:*/
#line 14906 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:572*//*668:*/
#line 18294 "weaver-interface-metafont_en.tex"

int current_depth;
/*:668*//*674:*/
#line 18476 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:674*/
#line 1966 "weaver-interface-metafont_en.tex"

};
/*:71*/
#line 386 "weaver-interface-metafont_en.tex"

/*1:*/
#line 262 "weaver-interface-metafont_en.tex"

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
#line 299 "weaver-interface-metafont_en.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 312 "weaver-interface-metafont_en.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 332 "weaver-interface-metafont_en.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 342 "weaver-interface-metafont_en.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*690:*/
#line 19058 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:690*//*694:*/
#line 19150 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:694*/
#line 387 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
