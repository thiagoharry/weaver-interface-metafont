/*7:*/
#line 355 "weaver-interface-metafont_en.tex"

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
#line 269 "weaver-interface-metafont_en.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*20:*/
#line 689 "weaver-interface-metafont_en.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:20*/
#line 369 "weaver-interface-metafont_en.tex"


/*542:*/
#line 14909 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:542*/
#line 371 "weaver-interface-metafont_en.tex"

/*61:*/
#line 1610 "weaver-interface-metafont_en.tex"

struct context{
/*88:*/
#line 2187 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:88*//*108:*/
#line 2584 "weaver-interface-metafont_en.tex"

void*variables;
/*:108*//*552:*/
#line 15291 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:552*/
#line 1612 "weaver-interface-metafont_en.tex"

};
/*:61*//*62:*/
#line 1628 "weaver-interface-metafont_en.tex"

struct metafont{
/*19:*/
#line 675 "weaver-interface-metafont_en.tex"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
pthread_mutex_t mutex;
#endif
/*:19*/
#line 1630 "weaver-interface-metafont_en.tex"

char*file;
bool loading;
/*68:*/
#line 1741 "weaver-interface-metafont_en.tex"

int errno,errno_line;
char*errno_str;
int errno_int;
/*:68*//*104:*/
#line 2522 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:104*//*122:*/
#line 2914 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:122*//*131:*/
#line 3091 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:131*//*147:*/
#line 3463 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:147*//*157:*/
#line 3630 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:157*//*203:*/
#line 4781 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:203*//*490:*/
#line 13139 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:490*//*539:*/
#line 14778 "weaver-interface-metafont_en.tex"

int current_depth;
/*:539*//*545:*/
#line 14957 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:545*/
#line 1633 "weaver-interface-metafont_en.tex"

};
/*:62*/
#line 372 "weaver-interface-metafont_en.tex"

/*1:*/
#line 248 "weaver-interface-metafont_en.tex"

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
#line 285 "weaver-interface-metafont_en.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 298 "weaver-interface-metafont_en.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 318 "weaver-interface-metafont_en.tex"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 328 "weaver-interface-metafont_en.tex"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*555:*/
#line 15469 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:555*//*559:*/
#line 15561 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:559*/
#line 373 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:7*/
