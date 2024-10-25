/*7:*/
#line 361 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 367 "weaver-interface-metafont_en.cweb"
#include <stdbool.h>  
#include <stdlib.h>  
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 372 "weaver-interface-metafont_en.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 375 "weaver-interface-metafont_en.cweb"
/*2:*/
#line 286 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 290 "weaver-interface-metafont_en.cweb"
/*:2*//*24:*/
#line 827 "weaver-interface-metafont_en.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 831 "weaver-interface-metafont_en.cweb"
/*:24*/
#line 375 "weaver-interface-metafont_en.cweb"


/*675:*/
#line 17325 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:675*/
#line 377 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2102 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2429 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*113:*/
#line 2851 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:113*//*131:*/
#line 3188 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:131*//*193:*/
#line 4984 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:193*//*206:*/
#line 5155 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:206*//*566:*/
#line 13883 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:566*//*645:*/
#line 16708 "weaver-interface-metafont_en.cweb"

float color[4];
/*:645*//*657:*/
#line 16884 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:657*//*672:*/
#line 17197 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:672*//*688:*/
#line 17692 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:688*/
#line 2105 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2119 "weaver-interface-metafont_en.cweb"

struct metafont{
/*23:*/
#line 815 "weaver-interface-metafont_en.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 819 "weaver-interface-metafont_en.cweb"
pthread_mutex_t mutex;
#endif
#line 821 "weaver-interface-metafont_en.cweb"
/*:23*/
#line 2121 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*109:*/
#line 2794 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:109*//*130:*/
#line 3181 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:130*//*142:*/
#line 3392 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:142*//*194:*/
#line 4992 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:194*//*278:*/
#line 6490 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:278*//*652:*/
#line 16822 "weaver-interface-metafont_en.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:652*//*678:*/
#line 17367 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:678*//*716:*/
#line 18505 "weaver-interface-metafont_en.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:716*/
#line 2124 "weaver-interface-metafont_en.cweb"

};
/*:76*/
#line 378 "weaver-interface-metafont_en.cweb"

/*1:*/
#line 267 "weaver-interface-metafont_en.cweb"

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
#line 278 "weaver-interface-metafont_en.cweb"
/*:1*//*3:*/
#line 300 "weaver-interface-metafont_en.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 311 "weaver-interface-metafont_en.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 329 "weaver-interface-metafont_en.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 337 "weaver-interface-metafont_en.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*694:*/
#line 17897 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:694*//*698:*/
#line 17994 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:698*/
#line 379 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 383 "weaver-interface-metafont_en.cweb"
#endif
#line 384 "weaver-interface-metafont_en.cweb"
/*:7*/
