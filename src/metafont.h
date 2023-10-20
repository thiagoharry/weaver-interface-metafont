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


/*605:*/
#line 16521 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:605*/
#line 385 "weaver-interface-metafont_en.tex"

/*65:*/
#line 1796 "weaver-interface-metafont_en.tex"

struct context{
char current_character[5];
/*93:*/
#line 2401 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:93*//*118:*/
#line 2871 "weaver-interface-metafont_en.tex"

struct variable*variables;
/*:118*//*615:*/
#line 16903 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:615*/
#line 1799 "weaver-interface-metafont_en.tex"

};
/*:65*//*66:*/
#line 1815 "weaver-interface-metafont_en.tex"

struct metafont{
/*23:*/
#line 858 "weaver-interface-metafont_en.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 1817 "weaver-interface-metafont_en.tex"

char*file;
bool loading;
/*72:*/
#line 1929 "weaver-interface-metafont_en.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:72*//*114:*/
#line 2806 "weaver-interface-metafont_en.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:114*//*132:*/
#line 3173 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:132*//*141:*/
#line 3345 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:141*//*190:*/
#line 4911 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:190*//*200:*/
#line 5077 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:200*//*274:*/
#line 6562 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:274*//*553:*/
#line 14747 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:553*//*602:*/
#line 16390 "weaver-interface-metafont_en.tex"

int current_depth;
/*:602*//*608:*/
#line 16569 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:608*/
#line 1820 "weaver-interface-metafont_en.tex"

};
/*:66*/
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
/*:6*//*618:*/
#line 17083 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:618*//*622:*/
#line 17175 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:622*/
#line 387 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
