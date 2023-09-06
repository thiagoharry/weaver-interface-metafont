/*6:*/
#line 173 "weaver-interface-metafont_en.tex"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#include <stdbool.h>  
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
/*2:*/
#line 105 "weaver-interface-metafont_en.tex"

#include "interface.h"
/*:2*/
#line 183 "weaver-interface-metafont_en.tex"


/*523:*/
#line 14307 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:523*/
#line 185 "weaver-interface-metafont_en.tex"

/*56:*/
#line 1292 "weaver-interface-metafont_en.tex"

struct context{
/*70:*/
#line 1599 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:70*//*86:*/
#line 1935 "weaver-interface-metafont_en.tex"

void*variables;
/*:86*//*533:*/
#line 14691 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:533*/
#line 1294 "weaver-interface-metafont_en.tex"

};
/*:56*//*57:*/
#line 1306 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*82:*/
#line 1873 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:82*//*100:*/
#line 2269 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:100*//*109:*/
#line 2446 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:109*//*124:*/
#line 2809 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:124*//*134:*/
#line 2976 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:134*//*181:*/
#line 4140 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:181*//*468:*/
#line 12511 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:468*//*517:*/
#line 14152 "weaver-interface-metafont_en.tex"

int current_depth;
/*:517*//*520:*/
#line 14276 "weaver-interface-metafont_en.tex"

bool loading;
/*:520*//*526:*/
#line 14355 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:526*/
#line 1311 "weaver-interface-metafont_en.tex"

};
/*:57*/
#line 186 "weaver-interface-metafont_en.tex"

/*1:*/
#line 90 "weaver-interface-metafont_en.tex"

void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
/*:1*//*3:*/
#line 115 "weaver-interface-metafont_en.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 126 "weaver-interface-metafont_en.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 146 "weaver-interface-metafont_en.tex"

void _Wfinish_metafont(void);
/*:5*//*536:*/
#line 14871 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:536*//*540:*/
#line 14963 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:540*/
#line 187 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
