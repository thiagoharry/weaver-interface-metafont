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


/*520:*/
#line 14400 "weaver-interface-metafont.tex"

struct _glyph;
/*:520*/
#line 201 "weaver-interface-metafont.tex"

/*56:*/
#line 1319 "weaver-interface-metafont.tex"

struct context{
/*69:*/
#line 1624 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:69*//*85:*/
#line 1963 "weaver-interface-metafont.tex"

void*variables;
/*:85*//*528:*/
#line 14725 "weaver-interface-metafont.tex"

struct _glyph*current_glyph;
/*:528*/
#line 1321 "weaver-interface-metafont.tex"

};
/*:56*//*57:*/
#line 1332 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*81:*/
#line 1901 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:81*//*99:*/
#line 2295 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:99*//*108:*/
#line 2456 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:108*//*124:*/
#line 2833 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:124*//*134:*/
#line 2998 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:134*//*180:*/
#line 4169 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:180*//*467:*/
#line 12623 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:467*//*514:*/
#line 14242 "weaver-interface-metafont.tex"

int current_depth;
/*:514*//*517:*/
#line 14368 "weaver-interface-metafont.tex"

bool loading;
/*:517*//*522:*/
#line 14428 "weaver-interface-metafont.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
/*:522*/
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
#line 125 "weaver-interface-metafont.tex"

struct metafont*new_metafont(char*filename);
/*:3*//*4:*/
#line 136 "weaver-interface-metafont.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 158 "weaver-interface-metafont.tex"

void _Wfinish_metafont(void);
/*:5*//*531:*/
#line 14931 "weaver-interface-metafont.tex"

bool _Wupdate_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:531*/
#line 203 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
