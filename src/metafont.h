/*7:*/
#line 387 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 393 "weaver-interface-metafont.cweb"
#include <stdbool.h>  
#include <stdlib.h>   
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 398 "weaver-interface-metafont.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 401 "weaver-interface-metafont.cweb"
/*2:*/
#line 303 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 307 "weaver-interface-metafont.cweb"
/*:2*//*24:*/
#line 869 "weaver-interface-metafont.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 873 "weaver-interface-metafont.cweb"
/*:24*/
#line 401 "weaver-interface-metafont.cweb"

/*616:*/
#line 17068 "weaver-interface-metafont.cweb"

struct _glyph;
/*:616*/
#line 402 "weaver-interface-metafont.cweb"

/*75:*/
#line 2162 "weaver-interface-metafont.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2501 "weaver-interface-metafont.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*106:*/
#line 2843 "weaver-interface-metafont.cweb"

struct variable*variables;
/*:106*//*121:*/
#line 3148 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:121*//*184:*/
#line 4979 "weaver-interface-metafont.cweb"

struct pen_variable*currentpen;
/*:184*//*197:*/
#line 5152 "weaver-interface-metafont.cweb"

struct picture_variable*currentpicture;
/*:197*//*507:*/
#line 13536 "weaver-interface-metafont.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:507*//*586:*/
#line 16444 "weaver-interface-metafont.cweb"

float color[4];
/*:586*//*598:*/
#line 16624 "weaver-interface-metafont.cweb"

GLuint currentpicture_fb;
/*:598*//*613:*/
#line 16939 "weaver-interface-metafont.cweb"

int current_depth;
/*:613*//*629:*/
#line 17430 "weaver-interface-metafont.cweb"

struct _glyph*current_glyph;
/*:629*/
#line 2165 "weaver-interface-metafont.cweb"

};
/*:75*//*76:*/
#line 2180 "weaver-interface-metafont.cweb"

struct metafont{
/*23:*/
#line 857 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 861 "weaver-interface-metafont.cweb"
pthread_mutex_t mutex;
#endif
#line 863 "weaver-interface-metafont.cweb"
/*:23*/
#line 2182 "weaver-interface-metafont.cweb"

char*file;
bool loading;
/*102:*/
#line 2786 "weaver-interface-metafont.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:102*//*120:*/
#line 3140 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*132:*/
#line 3354 "weaver-interface-metafont.cweb"

struct transform_variable*internal_transform_variables;
/*:132*//*185:*/
#line 4987 "weaver-interface-metafont.cweb"

struct pen_variable*internal_pen_variables;
/*:185*//*240:*/
#line 6191 "weaver-interface-metafont.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:240*//*593:*/
#line 16562 "weaver-interface-metafont.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:593*//*619:*/
#line 17109 "weaver-interface-metafont.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:619*//*657:*/
#line 18247 "weaver-interface-metafont.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:657*/
#line 2185 "weaver-interface-metafont.cweb"

};
/*:76*/
#line 403 "weaver-interface-metafont.cweb"

/*1:*/
#line 283 "weaver-interface-metafont.cweb"

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
#line 294 "weaver-interface-metafont.cweb"
/*:1*//*3:*/
#line 319 "weaver-interface-metafont.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 331 "weaver-interface-metafont.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 351 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 360 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*635:*/
#line 17632 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:635*//*639:*/
#line 17728 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:639*/
#line 404 "weaver-interface-metafont.cweb"

#ifdef __cplusplus
}
#endif
#line 408 "weaver-interface-metafont.cweb"
#endif
#line 409 "weaver-interface-metafont.cweb"
/*:7*/
