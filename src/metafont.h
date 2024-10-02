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


/*683:*/
#line 17457 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:683*/
#line 377 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2102 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*96:*/
#line 2551 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:96*//*121:*/
#line 2975 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:121*//*139:*/
#line 3313 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:139*//*201:*/
#line 5109 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:201*//*214:*/
#line 5280 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:214*//*574:*/
#line 14015 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:574*//*653:*/
#line 16840 "weaver-interface-metafont_en.cweb"

float color[4];
/*:653*//*665:*/
#line 17016 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:665*//*680:*/
#line 17329 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:680*//*696:*/
#line 17825 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:696*/
#line 2105 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2119 "weaver-interface-metafont_en.cweb"

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
#line 2121 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*117:*/
#line 2918 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:117*//*138:*/
#line 3306 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:138*//*150:*/
#line 3517 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:150*//*202:*/
#line 5117 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:202*//*286:*/
#line 6621 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:286*//*660:*/
#line 16954 "weaver-interface-metafont_en.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:660*//*686:*/
#line 17499 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:686*//*724:*/
#line 18640 "weaver-interface-metafont_en.cweb"

int errno,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:724*/
#line 2124 "weaver-interface-metafont_en.cweb"

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
/*:6*//*702:*/
#line 18030 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:702*//*706:*/
#line 18127 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:706*/
#line 379 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 383 "weaver-interface-metafont_en.cweb"
#endif
#line 384 "weaver-interface-metafont_en.cweb"
/*:7*/
