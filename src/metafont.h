/*7:*/
#line 512 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 518 "weaver-interface-metafont.cweb"
#include <stdbool.h>  
#include <stdlib.h>   
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 523 "weaver-interface-metafont.cweb"
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <EGL/egl.h> 
#include <GLES3/gl3.h>  
#endif
#line 527 "weaver-interface-metafont.cweb"
/*2:*/
#line 428 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 432 "weaver-interface-metafont.cweb"
/*:2*//*24:*/
#line 994 "weaver-interface-metafont.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 998 "weaver-interface-metafont.cweb"
/*:24*/
#line 527 "weaver-interface-metafont.cweb"

/*612:*/
#line 17237 "weaver-interface-metafont.cweb"

struct _glyph;
/*:612*/
#line 528 "weaver-interface-metafont.cweb"

/*75:*/
#line 2289 "weaver-interface-metafont.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2628 "weaver-interface-metafont.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*105:*/
#line 2945 "weaver-interface-metafont.cweb"

struct variable*variables;
/*:105*//*120:*/
#line 3247 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*183:*/
#line 5081 "weaver-interface-metafont.cweb"

struct pen_variable*currentpen;
/*:183*//*196:*/
#line 5254 "weaver-interface-metafont.cweb"

struct picture_variable*currentpicture;
/*:196*//*503:*/
#line 13629 "weaver-interface-metafont.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:503*//*583:*/
#line 16613 "weaver-interface-metafont.cweb"

float color[4];
/*:583*//*595:*/
#line 16798 "weaver-interface-metafont.cweb"

GLuint currentpicture_fb;
/*:595*//*609:*/
#line 17108 "weaver-interface-metafont.cweb"

int current_depth;
/*:609*//*622:*/
#line 17587 "weaver-interface-metafont.cweb"

struct _glyph*current_glyph;
/*:622*//*624:*/
#line 17728 "weaver-interface-metafont.cweb"

GLuint candidate_texture;
int candidate_texture_width,candidate_texture_height;
/*:624*/
#line 2292 "weaver-interface-metafont.cweb"

};
/*:75*//*76:*/
#line 2307 "weaver-interface-metafont.cweb"

struct metafont{
/*23:*/
#line 982 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 986 "weaver-interface-metafont.cweb"
pthread_mutex_t mutex;
#endif
#line 988 "weaver-interface-metafont.cweb"
/*:23*/
#line 2309 "weaver-interface-metafont.cweb"

char*file;
bool loading;
/*101:*/
#line 2888 "weaver-interface-metafont.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:101*//*119:*/
#line 3239 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:119*//*131:*/
#line 3455 "weaver-interface-metafont.cweb"

struct transform_variable*internal_transform_variables;
/*:131*//*184:*/
#line 5089 "weaver-interface-metafont.cweb"

struct pen_variable*internal_pen_variables;
/*:184*//*239:*/
#line 6292 "weaver-interface-metafont.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:239*//*590:*/
#line 16736 "weaver-interface-metafont.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:590*//*615:*/
#line 17279 "weaver-interface-metafont.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
char first_glyph_symbol[5];
int number_of_glyphs;
/*:615*//*666:*/
#line 18930 "weaver-interface-metafont.cweb"

bool reloading_texture;
/*:666*//*701:*/
#line 19672 "weaver-interface-metafont.cweb"

bool frenchspacing;
/*:701*//*712:*/
#line 19901 "weaver-interface-metafont.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:712*/
#line 2312 "weaver-interface-metafont.cweb"

};
/*:76*/
#line 529 "weaver-interface-metafont.cweb"

/*1:*/
#line 408 "weaver-interface-metafont.cweb"

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
#line 419 "weaver-interface-metafont.cweb"
/*:1*//*3:*/
#line 444 "weaver-interface-metafont.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 456 "weaver-interface-metafont.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 476 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 485 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*627:*/
#line 17782 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:627*//*631:*/
#line 17878 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:631*/
#line 530 "weaver-interface-metafont.cweb"

#ifdef __cplusplus
}
#endif
#line 534 "weaver-interface-metafont.cweb"
#endif
#line 535 "weaver-interface-metafont.cweb"
/*:7*/
