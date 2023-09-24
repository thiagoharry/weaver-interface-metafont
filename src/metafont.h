/*7:*/
#line 382 "weaver-interface-metafont.tex"

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
#line 287 "weaver-interface-metafont.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*20:*/
#line 720 "weaver-interface-metafont.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:20*/
#line 396 "weaver-interface-metafont.tex"

/*536:*/
#line 15004 "weaver-interface-metafont.tex"

struct _glyph;
/*:536*/
#line 397 "weaver-interface-metafont.tex"

/*61:*/
#line 1648 "weaver-interface-metafont.tex"

struct context{
/*85:*/
#line 2147 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:85*//*102:*/
#line 2499 "weaver-interface-metafont.tex"

void*variables;
/*:102*//*546:*/
#line 15386 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:546*/
#line 1650 "weaver-interface-metafont.tex"

};
/*:61*//*62:*/
#line 1667 "weaver-interface-metafont.tex"

struct metafont{
/*19:*/
#line 706 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:19*/
#line 1669 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*68:*/
#line 1780 "weaver-interface-metafont.tex"

int errno,errno_line;
char*errno_str;
int errno_int;
/*:68*//*98:*/
#line 2437 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:98*//*116:*/
#line 2837 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:116*//*125:*/
#line 3016 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:125*//*142:*/
#line 3405 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:142*//*152:*/
#line 3572 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:152*//*197:*/
#line 4734 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:197*//*484:*/
#line 13213 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:484*//*533:*/
#line 14873 "weaver-interface-metafont.tex"

int current_depth;
/*:533*//*539:*/
#line 15050 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:539*/
#line 1672 "weaver-interface-metafont.tex"

};
/*:62*/
#line 398 "weaver-interface-metafont.tex"

/*1:*/
#line 265 "weaver-interface-metafont.tex"

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
#line 305 "weaver-interface-metafont.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 319 "weaver-interface-metafont.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 341 "weaver-interface-metafont.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 352 "weaver-interface-metafont.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*549:*/
#line 15564 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:549*//*553:*/
#line 15657 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:553*/
#line 399 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
