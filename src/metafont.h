/*7:*/
#line 386 "weaver-interface-metafont.tex"

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
#line 291 "weaver-interface-metafont.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*20:*/
#line 724 "weaver-interface-metafont.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:20*/
#line 400 "weaver-interface-metafont.tex"

/*548:*/
#line 15168 "weaver-interface-metafont.tex"

struct _glyph;
/*:548*/
#line 401 "weaver-interface-metafont.tex"

/*61:*/
#line 1655 "weaver-interface-metafont.tex"

struct context{
char current_character[5];
/*89:*/
#line 2282 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:89*//*114:*/
#line 2749 "weaver-interface-metafont.tex"

struct variable*variables;
/*:114*//*558:*/
#line 15548 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:558*/
#line 1658 "weaver-interface-metafont.tex"

};
/*:61*//*62:*/
#line 1675 "weaver-interface-metafont.tex"

struct metafont{
/*19:*/
#line 710 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:19*/
#line 1677 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*68:*/
#line 1789 "weaver-interface-metafont.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:68*//*110:*/
#line 2684 "weaver-interface-metafont.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:110*//*128:*/
#line 3056 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:128*//*137:*/
#line 3230 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:137*//*154:*/
#line 3618 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:154*//*164:*/
#line 3785 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:164*//*209:*/
#line 4926 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:209*//*496:*/
#line 13384 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:496*//*545:*/
#line 15037 "weaver-interface-metafont.tex"

int current_depth;
/*:545*//*551:*/
#line 15214 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:551*/
#line 1680 "weaver-interface-metafont.tex"

};
/*:62*/
#line 402 "weaver-interface-metafont.tex"

/*1:*/
#line 269 "weaver-interface-metafont.tex"

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
#line 309 "weaver-interface-metafont.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 323 "weaver-interface-metafont.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 345 "weaver-interface-metafont.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 356 "weaver-interface-metafont.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*561:*/
#line 15726 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:561*//*565:*/
#line 15819 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:565*/
#line 403 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
