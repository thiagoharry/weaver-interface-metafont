/*7:*/
#line 381 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 387 "weaver-interface-metafont.cweb"
#include <stdbool.h>  
#include <stdlib.h>   
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 392 "weaver-interface-metafont.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 395 "weaver-interface-metafont.cweb"
/*2:*/
#line 297 "weaver-interface-metafont.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 301 "weaver-interface-metafont.cweb"
/*:2*//*24:*/
#line 863 "weaver-interface-metafont.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 867 "weaver-interface-metafont.cweb"
/*:24*/
#line 395 "weaver-interface-metafont.cweb"

/*687:*/
#line 17777 "weaver-interface-metafont.cweb"

struct _glyph;
/*:687*/
#line 396 "weaver-interface-metafont.cweb"

/*75:*/
#line 2117 "weaver-interface-metafont.cweb"

struct context{
char current_character[5];
/*104:*/
#line 2716 "weaver-interface-metafont.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:104*//*129:*/
#line 3140 "weaver-interface-metafont.cweb"

struct variable*variables;
/*:129*//*147:*/
#line 3485 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:147*//*210:*/
#line 5308 "weaver-interface-metafont.cweb"

struct pen_variable*currentpen;
/*:210*//*223:*/
#line 5481 "weaver-interface-metafont.cweb"

struct picture_variable*currentpicture;
/*:223*//*583:*/
#line 14313 "weaver-interface-metafont.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:583*//*662:*/
#line 17211 "weaver-interface-metafont.cweb"

float color[4];
/*:662*//*669:*/
#line 17332 "weaver-interface-metafont.cweb"

GLuint currentpicture_fb;
/*:669*//*684:*/
#line 17648 "weaver-interface-metafont.cweb"

int current_depth;
/*:684*//*700:*/
#line 18147 "weaver-interface-metafont.cweb"

struct _glyph*current_glyph;
/*:700*/
#line 2120 "weaver-interface-metafont.cweb"

};
/*:75*//*76:*/
#line 2135 "weaver-interface-metafont.cweb"

struct metafont{
/*23:*/
#line 851 "weaver-interface-metafont.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 855 "weaver-interface-metafont.cweb"
pthread_mutex_t mutex;
#endif
#line 857 "weaver-interface-metafont.cweb"
/*:23*/
#line 2137 "weaver-interface-metafont.cweb"

char*file;
bool loading;
/*82:*/
#line 2237 "weaver-interface-metafont.cweb"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:82*//*125:*/
#line 3083 "weaver-interface-metafont.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:125*//*146:*/
#line 3477 "weaver-interface-metafont.cweb"

struct numeric_variable*internal_numeric_variables;
/*:146*//*158:*/
#line 3683 "weaver-interface-metafont.cweb"

struct transform_variable*internal_transform_variables;
/*:158*//*211:*/
#line 5316 "weaver-interface-metafont.cweb"

struct pen_variable*internal_pen_variables;
/*:211*//*295:*/
#line 6854 "weaver-interface-metafont.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:295*//*690:*/
#line 17818 "weaver-interface-metafont.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:690*/
#line 2140 "weaver-interface-metafont.cweb"

};
/*:76*/
#line 397 "weaver-interface-metafont.cweb"

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
#line 313 "weaver-interface-metafont.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 325 "weaver-interface-metafont.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 345 "weaver-interface-metafont.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 354 "weaver-interface-metafont.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*706:*/
#line 18342 "weaver-interface-metafont.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:706*//*710:*/
#line 18426 "weaver-interface-metafont.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:710*/
#line 398 "weaver-interface-metafont.cweb"

#ifdef __cplusplus
}
#endif
#line 402 "weaver-interface-metafont.cweb"
#endif
#line 403 "weaver-interface-metafont.cweb"
/*:7*/
