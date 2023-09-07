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


/*525:*/
#line 14524 "weaver-interface-metafont.tex"

struct _glyph;
/*:525*/
#line 201 "weaver-interface-metafont.tex"

/*56:*/
#line 1322 "weaver-interface-metafont.tex"

struct context{
/*70:*/
#line 1635 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:70*//*87:*/
#line 1992 "weaver-interface-metafont.tex"

void*variables;
/*:87*//*535:*/
#line 14906 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:535*/
#line 1324 "weaver-interface-metafont.tex"

};
/*:56*//*57:*/
#line 1335 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*83:*/
#line 1930 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:83*//*101:*/
#line 2330 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:101*//*110:*/
#line 2509 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:110*//*127:*/
#line 2898 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:127*//*137:*/
#line 3065 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:137*//*183:*/
#line 4237 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:183*//*470:*/
#line 12709 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:470*//*519:*/
#line 14368 "weaver-interface-metafont.tex"

int current_depth;
/*:519*//*522:*/
#line 14492 "weaver-interface-metafont.tex"

bool loading;
/*:522*//*528:*/
#line 14570 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:528*/
#line 1340 "weaver-interface-metafont.tex"

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
/*:5*//*538:*/
#line 15084 "weaver-interface-metafont.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:538*//*542:*/
#line 15177 "weaver-interface-metafont.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:542*/
#line 203 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
