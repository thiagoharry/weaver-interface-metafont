/*7:*/
#line 458 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 464 "weaver-interface-metafont_en.cweb"
#include <stdbool.h>  
#include <stdlib.h>  
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 469 "weaver-interface-metafont_en.cweb"
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <EGL/egl.h> 
#include <GLES3/gl3.h>  
#endif
#line 473 "weaver-interface-metafont_en.cweb"
/*2:*/
#line 383 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 387 "weaver-interface-metafont_en.cweb"
/*:2*//*24:*/
#line 924 "weaver-interface-metafont_en.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 928 "weaver-interface-metafont_en.cweb"
/*:24*/
#line 473 "weaver-interface-metafont_en.cweb"

/*611:*/
#line 16918 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:611*/
#line 474 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2201 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2528 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*105:*/
#line 2847 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:105*//*120:*/
#line 3141 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*182:*/
#line 4938 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:182*//*195:*/
#line 5109 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:195*//*502:*/
#line 13382 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:502*//*582:*/
#line 16301 "weaver-interface-metafont_en.cweb"

float color[4];
/*:582*//*594:*/
#line 16482 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:594*//*608:*/
#line 16790 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:608*//*621:*/
#line 17266 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:621*//*623:*/
#line 17407 "weaver-interface-metafont_en.cweb"

GLuint candidate_texture;
int candidate_texture_width,candidate_texture_height;
/*:623*/
#line 2204 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2218 "weaver-interface-metafont_en.cweb"

struct metafont{
/*23:*/
#line 912 "weaver-interface-metafont_en.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 916 "weaver-interface-metafont_en.cweb"
pthread_mutex_t mutex;
#endif
#line 918 "weaver-interface-metafont_en.cweb"
/*:23*/
#line 2220 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*101:*/
#line 2790 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:101*//*119:*/
#line 3134 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:119*//*131:*/
#line 3345 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:131*//*183:*/
#line 4946 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:183*//*238:*/
#line 6120 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:238*//*589:*/
#line 16420 "weaver-interface-metafont_en.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:589*//*614:*/
#line 16960 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
char first_glyph_symbol[5];
int number_of_glyphs;
/*:614*//*664:*/
#line 18594 "weaver-interface-metafont_en.cweb"

bool reloading_texture;
/*:664*//*674:*/
#line 18752 "weaver-interface-metafont_en.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:674*/
#line 2223 "weaver-interface-metafont_en.cweb"

};
/*:76*/
#line 475 "weaver-interface-metafont_en.cweb"

/*1:*/
#line 364 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
void*target);
#endif
#line 375 "weaver-interface-metafont_en.cweb"
/*:1*//*3:*/
#line 397 "weaver-interface-metafont_en.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 408 "weaver-interface-metafont_en.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 426 "weaver-interface-metafont_en.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 434 "weaver-interface-metafont_en.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*626:*/
#line 17462 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:626*//*630:*/
#line 17559 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:630*/
#line 476 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 480 "weaver-interface-metafont_en.cweb"
#endif
#line 481 "weaver-interface-metafont_en.cweb"
/*:7*/
