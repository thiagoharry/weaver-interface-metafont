/*7:*/
#line 478 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 484 "weaver-interface-metafont.cweb"
#include <stdbool.h>  
#include <stdlib.h>   
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 489 "weaver-interface-metafont.cweb"
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <EGL/egl.h> 
#include <GLES3/gl3.h>  
#endif
#line 493 "weaver-interface-metafont.cweb"
/*2:*/
#line 394 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 398 "weaver-interface-metafont.cweb"
/*:2*//*24:*/
#line 960 "weaver-interface-metafont.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 964 "weaver-interface-metafont.cweb"
/*:24*/
#line 493 "weaver-interface-metafont.cweb"

/*611:*/
#line 17187 "weaver-interface-metafont.cweb"

struct _glyph;
/*:611*/
#line 494 "weaver-interface-metafont.cweb"

/*75:*/
#line 2255 "weaver-interface-metafont.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2594 "weaver-interface-metafont.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*105:*/
#line 2911 "weaver-interface-metafont.cweb"

struct variable*variables;
/*:105*//*120:*/
#line 3213 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*183:*/
#line 5047 "weaver-interface-metafont.cweb"

struct pen_variable*currentpen;
/*:183*//*196:*/
#line 5220 "weaver-interface-metafont.cweb"

struct picture_variable*currentpicture;
/*:196*//*503:*/
#line 13595 "weaver-interface-metafont.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:503*//*582:*/
#line 16563 "weaver-interface-metafont.cweb"

float color[4];
/*:582*//*594:*/
#line 16748 "weaver-interface-metafont.cweb"

GLuint currentpicture_fb;
/*:594*//*608:*/
#line 17058 "weaver-interface-metafont.cweb"

int current_depth;
/*:608*//*621:*/
#line 17537 "weaver-interface-metafont.cweb"

struct _glyph*current_glyph;
/*:621*//*623:*/
#line 17678 "weaver-interface-metafont.cweb"

GLuint candidate_texture;
int candidate_texture_width,candidate_texture_height;
/*:623*/
#line 2258 "weaver-interface-metafont.cweb"

};
/*:75*//*76:*/
#line 2273 "weaver-interface-metafont.cweb"

struct metafont{
/*23:*/
#line 948 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 952 "weaver-interface-metafont.cweb"
pthread_mutex_t mutex;
#endif
#line 954 "weaver-interface-metafont.cweb"
/*:23*/
#line 2275 "weaver-interface-metafont.cweb"

char*file;
bool loading;
/*101:*/
#line 2854 "weaver-interface-metafont.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:101*//*119:*/
#line 3205 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:119*//*131:*/
#line 3421 "weaver-interface-metafont.cweb"

struct transform_variable*internal_transform_variables;
/*:131*//*184:*/
#line 5055 "weaver-interface-metafont.cweb"

struct pen_variable*internal_pen_variables;
/*:184*//*239:*/
#line 6258 "weaver-interface-metafont.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:239*//*589:*/
#line 16686 "weaver-interface-metafont.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:589*//*614:*/
#line 17229 "weaver-interface-metafont.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
char first_glyph_symbol[5];
int number_of_glyphs;
/*:614*//*665:*/
#line 18880 "weaver-interface-metafont.cweb"

bool reloading_texture;
/*:665*//*668:*/
#line 18915 "weaver-interface-metafont.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:668*/
#line 2278 "weaver-interface-metafont.cweb"

};
/*:76*/
#line 495 "weaver-interface-metafont.cweb"

/*1:*/
#line 374 "weaver-interface-metafont.cweb"

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
#line 385 "weaver-interface-metafont.cweb"
/*:1*//*3:*/
#line 410 "weaver-interface-metafont.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 422 "weaver-interface-metafont.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 442 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 451 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*626:*/
#line 17732 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:626*//*630:*/
#line 17828 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:630*/
#line 496 "weaver-interface-metafont.cweb"

#ifdef __cplusplus
}
#endif
#line 500 "weaver-interface-metafont.cweb"
#endif
#line 501 "weaver-interface-metafont.cweb"
/*:7*/
