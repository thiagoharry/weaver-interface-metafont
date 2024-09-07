/*7:*/
#line 367 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 373 "weaver-interface-metafont_en.cweb"
#include <stdbool.h>  
#include <stdlib.h>  
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 378 "weaver-interface-metafont_en.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 381 "weaver-interface-metafont_en.cweb"
/*2:*/
#line 281 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 285 "weaver-interface-metafont_en.cweb"
/*:2*//*24:*/
#line 870 "weaver-interface-metafont_en.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 874 "weaver-interface-metafont_en.cweb"
/*:24*/
#line 381 "weaver-interface-metafont_en.cweb"


/*678:*/
#line 18709 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:678*/
#line 383 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2215 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*104:*/
#line 2853 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:104*//*129:*/
#line 3328 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:129*//*206:*/
#line 5539 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:206*//*219:*/
#line 5737 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:219*//*579:*/
#line 15198 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:579*//*660:*/
#line 18227 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:660*//*675:*/
#line 18577 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:675*//*691:*/
#line 19108 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:691*/
#line 2218 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2234 "weaver-interface-metafont_en.cweb"

struct metafont{
/*23:*/
#line 856 "weaver-interface-metafont_en.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 860 "weaver-interface-metafont_en.cweb"
pthread_mutex_t mutex;
#endif
#line 862 "weaver-interface-metafont_en.cweb"
/*:23*/
#line 2236 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*82:*/
#line 2348 "weaver-interface-metafont_en.cweb"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:82*//*125:*/
#line 3263 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:125*//*146:*/
#line 3666 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:146*//*155:*/
#line 3838 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:155*//*207:*/
#line 5549 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:207*//*291:*/
#line 7209 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:291*//*681:*/
#line 18758 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:681*/
#line 2239 "weaver-interface-metafont_en.cweb"

};
/*:76*/
#line 384 "weaver-interface-metafont_en.cweb"

/*1:*/
#line 260 "weaver-interface-metafont_en.cweb"

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
#line 271 "weaver-interface-metafont_en.cweb"
/*:1*//*3:*/
#line 297 "weaver-interface-metafont_en.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 310 "weaver-interface-metafont_en.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 330 "weaver-interface-metafont_en.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 340 "weaver-interface-metafont_en.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*697:*/
#line 19318 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:697*//*701:*/
#line 19410 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:701*/
#line 385 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 389 "weaver-interface-metafont_en.cweb"
#endif
#line 390 "weaver-interface-metafont_en.cweb"
/*:7*/
