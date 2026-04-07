/*7:*/
#line 446 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 452 "weaver-interface-metafont_en.cweb"
#include <stdbool.h>  
#include <stdlib.h>  
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 457 "weaver-interface-metafont_en.cweb"
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <EGL/egl.h> 
#include <GLES3/gl3.h>  
#endif
#line 461 "weaver-interface-metafont_en.cweb"
/*2:*/
#line 371 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 375 "weaver-interface-metafont_en.cweb"
/*:2*//*24:*/
#line 912 "weaver-interface-metafont_en.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 916 "weaver-interface-metafont_en.cweb"
/*:24*/
#line 461 "weaver-interface-metafont_en.cweb"

/*610:*/
#line 16886 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:610*/
#line 462 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2189 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2516 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*105:*/
#line 2835 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:105*//*120:*/
#line 3129 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*182:*/
#line 4926 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:182*//*195:*/
#line 5097 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:195*//*502:*/
#line 13366 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:502*//*581:*/
#line 16269 "weaver-interface-metafont_en.cweb"

float color[4];
/*:581*//*593:*/
#line 16450 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:593*//*607:*/
#line 16758 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:607*//*620:*/
#line 17234 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:620*//*622:*/
#line 17375 "weaver-interface-metafont_en.cweb"

GLuint candidate_texture;
int candidate_texture_width,candidate_texture_height;
/*:622*/
#line 2192 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2206 "weaver-interface-metafont_en.cweb"

struct metafont{
/*23:*/
#line 900 "weaver-interface-metafont_en.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 904 "weaver-interface-metafont_en.cweb"
pthread_mutex_t mutex;
#endif
#line 906 "weaver-interface-metafont_en.cweb"
/*:23*/
#line 2208 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*101:*/
#line 2778 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:101*//*119:*/
#line 3122 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:119*//*131:*/
#line 3333 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:131*//*183:*/
#line 4934 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:183*//*238:*/
#line 6108 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:238*//*588:*/
#line 16388 "weaver-interface-metafont_en.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:588*//*613:*/
#line 16928 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
char first_glyph_symbol[5];
int number_of_glyphs;
/*:613*//*663:*/
#line 18562 "weaver-interface-metafont_en.cweb"

bool reloading_texture;
/*:663*//*666:*/
#line 18597 "weaver-interface-metafont_en.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:666*/
#line 2211 "weaver-interface-metafont_en.cweb"

};
/*:76*/
#line 463 "weaver-interface-metafont_en.cweb"

/*1:*/
#line 352 "weaver-interface-metafont_en.cweb"

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
#line 363 "weaver-interface-metafont_en.cweb"
/*:1*//*3:*/
#line 385 "weaver-interface-metafont_en.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 396 "weaver-interface-metafont_en.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 414 "weaver-interface-metafont_en.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 422 "weaver-interface-metafont_en.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*625:*/
#line 17430 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:625*//*629:*/
#line 17527 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:629*/
#line 464 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 468 "weaver-interface-metafont_en.cweb"
#endif
#line 469 "weaver-interface-metafont_en.cweb"
/*:7*/
