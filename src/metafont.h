/*6:*/
#line 189 "weaver-interface-metafont.tex"

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
#line 114 "weaver-interface-metafont.tex"

#include "interface.h"
/*:2*/
#line 199 "weaver-interface-metafont.tex"


/*521:*/
#line 14450 "weaver-interface-metafont.tex"

struct _glyph;
/*:521*/
#line 201 "weaver-interface-metafont.tex"

/*56:*/
#line 1319 "weaver-interface-metafont.tex"

struct context{
/*70:*/
#line 1632 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:70*//*86:*/
#line 1971 "weaver-interface-metafont.tex"

void*variables;
/*:86*//*531:*/
#line 14832 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:531*/
#line 1321 "weaver-interface-metafont.tex"

};
/*:56*//*57:*/
#line 1332 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*82:*/
#line 1909 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:82*//*100:*/
#line 2306 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:100*//*109:*/
#line 2485 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:109*//*125:*/
#line 2862 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:125*//*135:*/
#line 3027 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:135*//*181:*/
#line 4199 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:181*//*468:*/
#line 12667 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:468*//*515:*/
#line 14292 "weaver-interface-metafont.tex"

int current_depth;
/*:515*//*518:*/
#line 14418 "weaver-interface-metafont.tex"

bool loading;
/*:518*//*524:*/
#line 14496 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:524*/
#line 1337 "weaver-interface-metafont.tex"

};
/*:57*/
#line 202 "weaver-interface-metafont.tex"

/*1:*/
#line 99 "weaver-interface-metafont.tex"

void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
/*:1*//*3:*/
#line 126 "weaver-interface-metafont.tex"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 138 "weaver-interface-metafont.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 160 "weaver-interface-metafont.tex"

void _Wfinish_metafont(void);
/*:5*//*534:*/
#line 15004 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:534*//*538:*/
#line 15097 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:538*/
#line 203 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
