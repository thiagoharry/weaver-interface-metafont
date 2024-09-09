/*7:*/
#line 394 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 400 "weaver-interface-metafont.cweb"
#include <stdbool.h>  
#include <stdlib.h>   
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 405 "weaver-interface-metafont.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 408 "weaver-interface-metafont.cweb"
/*2:*/
#line 299 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 303 "weaver-interface-metafont.cweb"
/*:2*//*24:*/
#line 910 "weaver-interface-metafont.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 914 "weaver-interface-metafont.cweb"
/*:24*/
#line 408 "weaver-interface-metafont.cweb"

/*682:*/
#line 18999 "weaver-interface-metafont.cweb"

struct _glyph;
/*:682*/
#line 409 "weaver-interface-metafont.cweb"

/*75:*/
#line 2269 "weaver-interface-metafont.cweb"

struct context{
char current_character[5];
/*104:*/
#line 2927 "weaver-interface-metafont.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:104*//*129:*/
#line 3399 "weaver-interface-metafont.cweb"

struct variable*variables;
/*:129*//*147:*/
#line 3750 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:147*//*210:*/
#line 5660 "weaver-interface-metafont.cweb"

struct pen_variable*currentpen;
/*:210*//*223:*/
#line 5860 "weaver-interface-metafont.cweb"

struct picture_variable*currentpicture;
/*:223*//*583:*/
#line 15424 "weaver-interface-metafont.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:583*//*664:*/
#line 18517 "weaver-interface-metafont.cweb"

GLuint currentpicture_fb;
/*:664*//*679:*/
#line 18866 "weaver-interface-metafont.cweb"

int current_depth;
/*:679*//*695:*/
#line 19395 "weaver-interface-metafont.cweb"

struct _glyph*current_glyph;
/*:695*/
#line 2272 "weaver-interface-metafont.cweb"

};
/*:75*//*76:*/
#line 2289 "weaver-interface-metafont.cweb"

struct metafont{
/*23:*/
#line 896 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 900 "weaver-interface-metafont.cweb"
pthread_mutex_t mutex;
#endif
#line 902 "weaver-interface-metafont.cweb"
/*:23*/
#line 2291 "weaver-interface-metafont.cweb"

char*file;
bool loading;
/*82:*/
#line 2403 "weaver-interface-metafont.cweb"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:82*//*125:*/
#line 3334 "weaver-interface-metafont.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:125*//*146:*/
#line 3742 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:146*//*158:*/
#line 3928 "weaver-interface-metafont.cweb"

struct transform_variable*internal_transform_variables;
/*:158*//*211:*/
#line 5670 "weaver-interface-metafont.cweb"

struct pen_variable*internal_pen_variables;
/*:211*//*295:*/
#line 7380 "weaver-interface-metafont.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:295*//*685:*/
#line 19046 "weaver-interface-metafont.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:685*/
#line 2294 "weaver-interface-metafont.cweb"

};
/*:76*/
#line 410 "weaver-interface-metafont.cweb"

/*1:*/
#line 277 "weaver-interface-metafont.cweb"

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
#line 288 "weaver-interface-metafont.cweb"
/*:1*//*3:*/
#line 317 "weaver-interface-metafont.cweb"

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
#line 353 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 364 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*701:*/
#line 19606 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:701*//*705:*/
#line 19699 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:705*/
#line 411 "weaver-interface-metafont.cweb"

#ifdef __cplusplus
}
#endif
#line 415 "weaver-interface-metafont.cweb"
#endif
#line 416 "weaver-interface-metafont.cweb"
/*:7*/
