/*6:*/
#line 168 "weaver-interface-metafont_en.tex"

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
#line 100 "weaver-interface-metafont_en.tex"

#include "interface.h"
/*:2*/
#line 178 "weaver-interface-metafont_en.tex"


/*47:*/
#line 1067 "weaver-interface-metafont_en.tex"

struct context{
/*60:*/
#line 1366 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:60*//*76:*/
#line 1701 "weaver-interface-metafont_en.tex"

void*variables;
/*:76*/
#line 1069 "weaver-interface-metafont_en.tex"

};
/*:47*//*48:*/
#line 1081 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*72:*/
#line 1639 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:72*//*90:*/
#line 2032 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:90*//*99:*/
#line 2193 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:99*//*114:*/
#line 2561 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:114*//*124:*/
#line 2723 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:124*//*171:*/
#line 3887 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:171*//*490:*/
#line 13604 "weaver-interface-metafont_en.tex"

int current_depth;
/*:490*/
#line 1086 "weaver-interface-metafont_en.tex"

};
/*:48*/
#line 180 "weaver-interface-metafont_en.tex"

/*1:*/
#line 85 "weaver-interface-metafont_en.tex"

void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
/*:1*//*3:*/
#line 110 "weaver-interface-metafont_en.tex"

struct metafont*new_metafont(char*filename);
/*:3*//*4:*/
#line 120 "weaver-interface-metafont_en.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int pt);
/*:4*//*5:*/
#line 141 "weaver-interface-metafont_en.tex"

void _Wfinish_metafont(void);
/*:5*/
#line 181 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
