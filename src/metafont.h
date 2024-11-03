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


/*665:*/
#line 17205 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:665*/
#line 377 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2101 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*88:*/
#line 2428 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:88*//*106:*/
#line 2756 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:106*//*121:*/
#line 3053 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:121*//*183:*/
#line 4849 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:183*//*196:*/
#line 5020 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:196*//*556:*/
#line 13754 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:556*//*635:*/
#line 16588 "weaver-interface-metafont_en.cweb"

float color[4];
/*:635*//*647:*/
#line 16764 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:647*//*662:*/
#line 17077 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:662*//*678:*/
#line 17565 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:678*/
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
/*102:*/
#line 2699 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:102*//*120:*/
#line 3046 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:120*//*132:*/
#line 3257 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:132*//*184:*/
#line 4857 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:184*//*268:*/
#line 6355 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:268*//*642:*/
#line 16702 "weaver-interface-metafont_en.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:642*//*668:*/
#line 17247 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:668*//*706:*/
#line 18379 "weaver-interface-metafont_en.cweb"

int err,errno_line;
char errno_character[5];
char errno_str[32];
int errno_int;
/*:706*/
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
/*:6*//*684:*/
#line 17770 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:684*//*688:*/
#line 17867 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:688*/
#line 379 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 383 "weaver-interface-metafont_en.cweb"
#endif
#line 384 "weaver-interface-metafont_en.cweb"
/*:7*/
