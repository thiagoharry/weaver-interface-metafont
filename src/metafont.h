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


/*671:*/
#line 17265 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:671*/
#line 377 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2101 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2428 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*109:*/
#line 2780 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:109*//*127:*/
#line 3124 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:127*//*189:*/
#line 4920 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:189*//*202:*/
#line 5091 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:202*//*562:*/
#line 13825 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:562*//*641:*/
#line 16648 "weaver-interface-metafont_en.cweb"

float color[4];
/*:641*//*653:*/
#line 16824 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:653*//*668:*/
#line 17137 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:668*//*684:*/
#line 17625 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:684*/
#line 2104 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2118 "weaver-interface-metafont_en.cweb"

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
#line 2120 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*105:*/
#line 2723 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:105*//*126:*/
#line 3117 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:126*//*138:*/
#line 3328 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:138*//*190:*/
#line 4928 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:190*//*274:*/
#line 6426 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:274*//*648:*/
#line 16762 "weaver-interface-metafont_en.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:648*//*674:*/
#line 17307 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:674*//*712:*/
#line 18438 "weaver-interface-metafont_en.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:712*/
#line 2123 "weaver-interface-metafont_en.cweb"

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
/*:6*//*690:*/
#line 17830 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:690*//*694:*/
#line 17927 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:694*/
#line 379 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 383 "weaver-interface-metafont_en.cweb"
#endif
#line 384 "weaver-interface-metafont_en.cweb"
/*:7*/
