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

/*679:*/
#line 19005 "weaver-interface-metafont.tex"

struct _glyph;
/*:679*/
#line 411 "weaver-interface-metafont.tex"

/*76:*/
#line 2317 "weaver-interface-metafont.tex"

struct context{
char current_character[5];
/*105:*/
#line 2975 "weaver-interface-metafont.tex"

int nesting_level;
struct linked_token*end_token_stack;
/*:105*//*130:*/
#line 3447 "weaver-interface-metafont.tex"

struct variable*variables;
/*:130*//*692:*/
#line 19400 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:692*/
#line 2320 "weaver-interface-metafont.tex"

};
/*:76*//*77:*/
#line 2337 "weaver-interface-metafont.tex"

struct metafont{
/*23:*/
#line 899 "weaver-interface-metafont.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:23*/
#line 2339 "weaver-interface-metafont.tex"

char*file;
bool loading;
/*83:*/
#line 2451 "weaver-interface-metafont.tex"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:83*//*126:*/
#line 3382 "weaver-interface-metafont.tex"

struct named_variable*named_variables;
struct variable*variables;
/*:126*//*147:*/
#line 3792 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:147*//*156:*/
#line 3966 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:156*//*208:*/
#line 5691 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:208*//*218:*/
#line 5858 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:218*//*292:*/
#line 7376 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:292*//*580:*/
#line 15417 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:580*//*676:*/
#line 18870 "weaver-interface-metafont.tex"

int current_depth;
/*:676*//*682:*/
#line 19051 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:682*/
#line 2342 "weaver-interface-metafont.tex"

};
/*:77*/
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
/*:6*//*698:*/
#line 19618 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:698*//*702:*/
#line 19711 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:702*/
#line 413 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
