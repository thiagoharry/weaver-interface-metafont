/*6:*/
#line 336 "weaver-interface-metafont_en.tex"

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
#line 261 "weaver-interface-metafont_en.tex"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
/*:2*//*19:*/
#line 670 "weaver-interface-metafont_en.tex"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
/*:19*/
#line 350 "weaver-interface-metafont_en.tex"


/*532:*/
#line 14646 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:532*/
#line 352 "weaver-interface-metafont_en.tex"

/*63:*/
#line 1592 "weaver-interface-metafont_en.tex"

struct context{
/*77:*/
#line 1899 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:77*//*94:*/
#line 2253 "weaver-interface-metafont_en.tex"

void*variables;
/*:94*//*542:*/
#line 15030 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:542*/
#line 1594 "weaver-interface-metafont_en.tex"

};
/*:63*//*64:*/
#line 1606 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*90:*/
#line 2191 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:90*//*108:*/
#line 2587 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:108*//*117:*/
#line 2764 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:117*//*133:*/
#line 3136 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:133*//*143:*/
#line 3303 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:143*//*190:*/
#line 4466 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:190*//*477:*/
#line 12843 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:477*//*526:*/
#line 14489 "weaver-interface-metafont_en.tex"

int current_depth;
/*:526*//*529:*/
#line 14613 "weaver-interface-metafont_en.tex"

bool loading;
/*:529*//*535:*/
#line 14694 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:535*/
#line 1611 "weaver-interface-metafont_en.tex"

};
/*:64*/
#line 353 "weaver-interface-metafont_en.tex"

/*1:*/
#line 240 "weaver-interface-metafont_en.tex"

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
#line 277 "weaver-interface-metafont_en.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 290 "weaver-interface-metafont_en.tex"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 310 "weaver-interface-metafont_en.tex"

void _Wfinish_metafont(void);
/*:5*//*545:*/
#line 15210 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:545*//*549:*/
#line 15302 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:549*/
#line 354 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
