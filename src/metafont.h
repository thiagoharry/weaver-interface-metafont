/*7:*/
#line 476 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 482 "weaver-interface-metafont.cweb"
#include <stdbool.h>  
#include <stdlib.h>   
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 487 "weaver-interface-metafont.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 490 "weaver-interface-metafont.cweb"
/*2:*/
#line 392 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 396 "weaver-interface-metafont.cweb"
/*:2*//*24:*/
#line 957 "weaver-interface-metafont.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 961 "weaver-interface-metafont.cweb"
/*:24*/
#line 490 "weaver-interface-metafont.cweb"

/*611:*/
#line 17125 "weaver-interface-metafont.cweb"

struct _glyph;
/*:611*/
#line 491 "weaver-interface-metafont.cweb"

/*75:*/
#line 2252 "weaver-interface-metafont.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2591 "weaver-interface-metafont.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*105:*/
#line 2908 "weaver-interface-metafont.cweb"

struct variable*variables;
/*:105*//*120:*/
#line 3210 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*183:*/
#line 5044 "weaver-interface-metafont.cweb"

struct pen_variable*currentpen;
/*:183*//*196:*/
#line 5217 "weaver-interface-metafont.cweb"

struct picture_variable*currentpicture;
/*:196*//*503:*/
#line 13588 "weaver-interface-metafont.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:503*//*582:*/
#line 16501 "weaver-interface-metafont.cweb"

float color[4];
/*:582*//*594:*/
#line 16686 "weaver-interface-metafont.cweb"

GLuint currentpicture_fb;
/*:594*//*608:*/
#line 16996 "weaver-interface-metafont.cweb"

int current_depth;
/*:608*//*621:*/
#line 17475 "weaver-interface-metafont.cweb"

struct _glyph*current_glyph;
/*:621*//*623:*/
#line 17616 "weaver-interface-metafont.cweb"

GLuint candidate_texture;
int candidate_texture_width,candidate_texture_height;
/*:623*/
#line 2255 "weaver-interface-metafont.cweb"

};
/*:75*//*76:*/
#line 2270 "weaver-interface-metafont.cweb"

struct metafont{
/*23:*/
#line 945 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 949 "weaver-interface-metafont.cweb"
pthread_mutex_t mutex;
#endif
#line 951 "weaver-interface-metafont.cweb"
/*:23*/
#line 2272 "weaver-interface-metafont.cweb"

char*file;
bool loading;
/*101:*/
#line 2851 "weaver-interface-metafont.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:101*//*119:*/
#line 3202 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:119*//*131:*/
#line 3418 "weaver-interface-metafont.cweb"

struct transform_variable*internal_transform_variables;
/*:131*//*184:*/
#line 5052 "weaver-interface-metafont.cweb"

struct pen_variable*internal_pen_variables;
/*:184*//*239:*/
#line 6255 "weaver-interface-metafont.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:239*//*589:*/
#line 16624 "weaver-interface-metafont.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:589*//*614:*/
#line 17167 "weaver-interface-metafont.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
char first_glyph_symbol[5];
int number_of_glyphs;
/*:614*//*665:*/
#line 18818 "weaver-interface-metafont.cweb"

bool reloading_texture;
/*:665*//*668:*/
#line 18853 "weaver-interface-metafont.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:668*/
#line 2275 "weaver-interface-metafont.cweb"

};
/*:76*/
#line 492 "weaver-interface-metafont.cweb"

/*1:*/
#line 372 "weaver-interface-metafont.cweb"

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
#line 383 "weaver-interface-metafont.cweb"
/*:1*//*3:*/
#line 408 "weaver-interface-metafont.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 420 "weaver-interface-metafont.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 440 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 449 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*626:*/
#line 17670 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:626*//*630:*/
#line 17766 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:630*/
#line 493 "weaver-interface-metafont.cweb"

#ifdef __cplusplus
}
#endif
#line 497 "weaver-interface-metafont.cweb"
#endif
#line 498 "weaver-interface-metafont.cweb"
/*:7*/
