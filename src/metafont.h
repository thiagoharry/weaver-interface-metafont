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


/*525:*/
#line 14345 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:525*/
#line 185 "weaver-interface-metafont_en.tex"

/*56:*/
#line 1292 "weaver-interface-metafont_en.tex"

struct context{
/*70:*/
#line 1599 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:70*//*87:*/
#line 1953 "weaver-interface-metafont_en.tex"

void*variables;
/*:87*//*535:*/
#line 14729 "weaver-interface-metafont_en.tex"

struct _glyph*current_glyph;
/*:535*/
#line 1294 "weaver-interface-metafont_en.tex"

};
/*:56*//*57:*/
#line 1306 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*83:*/
#line 1891 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:83*//*101:*/
#line 2287 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:101*//*110:*/
#line 2464 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:110*//*126:*/
#line 2836 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:126*//*136:*/
#line 3003 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:136*//*183:*/
#line 4167 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:183*//*470:*/
#line 12544 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:470*//*519:*/
#line 14190 "weaver-interface-metafont_en.tex"

int current_depth;
/*:519*//*522:*/
#line 14314 "weaver-interface-metafont_en.tex"

bool loading;
/*:522*//*528:*/
#line 14393 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:528*/
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
/*:5*//*538:*/
#line 14909 "weaver-interface-metafont_en.tex"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:538*//*542:*/
#line 15001 "weaver-interface-metafont_en.tex"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:542*/
#line 187 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
