/*6:*/
#line 366 "weaver-interface-metafont.tex"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#include <stdbool.h>  
#include <stdlib.h>   
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
/*2:*/
#line 283 "weaver-interface-metafont.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*19:*/
#line 704 "weaver-interface-metafont.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:19*/
#line 380 "weaver-interface-metafont.tex"

/*528:*/
#line 14820 "weaver-interface-metafont.tex"

struct _glyph;
/*:528*/
#line 381 "weaver-interface-metafont.tex"

/*60:*/
#line 1625 "weaver-interface-metafont.tex"

struct context{
/*74:*/
#line 1938 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:74*//*91:*/
#line 2290 "weaver-interface-metafont.tex"

void*variables;
/*:91*//*538:*/
#line 15202 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:538*/
#line 1627 "weaver-interface-metafont.tex"

};
/*:60*//*61:*/
#line 1638 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*87:*/
#line 2228 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:87*//*105:*/
#line 2628 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:105*//*114:*/
#line 2807 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:114*//*131:*/
#line 3196 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:131*//*141:*/
#line 3363 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:141*//*186:*/
#line 4525 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:186*//*473:*/
#line 13004 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:473*//*522:*/
#line 14664 "weaver-interface-metafont.tex"

int current_depth;
/*:522*//*525:*/
#line 14788 "weaver-interface-metafont.tex"

bool loading;
/*:525*//*531:*/
#line 14866 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:531*/
#line 1643 "weaver-interface-metafont.tex"

};
/*:61*/
#line 382 "weaver-interface-metafont.tex"

/*1:*/
#line 261 "weaver-interface-metafont.tex"

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
/*:1*//*3:*/
#line 301 "weaver-interface-metafont.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 315 "weaver-interface-metafont.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 337 "weaver-interface-metafont.tex"

void _Wfinish_weavefont(void);
/*:5*//*541:*/
#line 15380 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:541*//*545:*/
#line 15473 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:545*/
#line 383 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
