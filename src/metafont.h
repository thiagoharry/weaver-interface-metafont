/*7:*/
#line 353 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 359 "weaver-interface-metafont_en.cweb"
#include <stdbool.h>  
#include <stdlib.h>  
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 364 "weaver-interface-metafont_en.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 367 "weaver-interface-metafont_en.cweb"
/*2:*/
#line 278 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 282 "weaver-interface-metafont_en.cweb"
/*:2*//*24:*/
#line 819 "weaver-interface-metafont_en.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 823 "weaver-interface-metafont_en.cweb"
/*:24*/
#line 367 "weaver-interface-metafont_en.cweb"


/*686:*/
#line 17479 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:686*/
#line 369 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2056 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*104:*/
#line 2633 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:104*//*129:*/
#line 3057 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:129*//*147:*/
#line 3395 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:147*//*209:*/
#line 5191 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:209*//*222:*/
#line 5362 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:222*//*582:*/
#line 14096 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:582*//*661:*/
#line 16921 "weaver-interface-metafont_en.cweb"

float color[4];
/*:661*//*668:*/
#line 17038 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:668*//*683:*/
#line 17351 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:683*//*699:*/
#line 17847 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:699*/
#line 2059 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2073 "weaver-interface-metafont_en.cweb"

struct metafont{
/*23:*/
#line 807 "weaver-interface-metafont_en.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 811 "weaver-interface-metafont_en.cweb"
pthread_mutex_t mutex;
#endif
#line 813 "weaver-interface-metafont_en.cweb"
/*:23*/
#line 2075 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*82:*/
#line 2175 "weaver-interface-metafont_en.cweb"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:82*//*125:*/
#line 3000 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:125*//*146:*/
#line 3388 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:146*//*158:*/
#line 3599 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:158*//*210:*/
#line 5199 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:210*//*294:*/
#line 6703 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:294*//*689:*/
#line 17521 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:689*/
#line 2078 "weaver-interface-metafont_en.cweb"

};
/*:76*/
#line 370 "weaver-interface-metafont_en.cweb"

/*1:*/
#line 259 "weaver-interface-metafont_en.cweb"

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
#line 270 "weaver-interface-metafont_en.cweb"
/*:1*//*3:*/
#line 292 "weaver-interface-metafont_en.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 303 "weaver-interface-metafont_en.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 321 "weaver-interface-metafont_en.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 329 "weaver-interface-metafont_en.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*705:*/
#line 18045 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:705*//*709:*/
#line 18129 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:709*/
#line 371 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 375 "weaver-interface-metafont_en.cweb"
#endif
#line 376 "weaver-interface-metafont_en.cweb"
/*:7*/
