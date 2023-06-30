/*6:*/
#line 191 "weaver-interface-metafont.tex"

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
#line 201 "weaver-interface-metafont.tex"


/*56:*/
#line 1317 "weaver-interface-metafont.tex"

struct context{
/*69:*/
#line 1622 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:69*//*85:*/
#line 1960 "weaver-interface-metafont.tex"

void*variables;
/*:85*/
#line 1319 "weaver-interface-metafont.tex"

};
/*:56*//*57:*/
#line 1330 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*81:*/
#line 1898 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:81*//*99:*/
#line 2292 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:99*//*108:*/
#line 2453 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:108*//*124:*/
#line 2835 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:124*//*134:*/
#line 2997 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:134*//*180:*/
#line 4168 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:180*//*500:*/
#line 13568 "weaver-interface-metafont.tex"

int current_depth;
/*:500*/
#line 1335 "weaver-interface-metafont.tex"

};
/*:57*/
#line 203 "weaver-interface-metafont.tex"

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
#line 138 "weaver-interface-metafont.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int pt);
/*:4*//*5:*/
#line 160 "weaver-interface-metafont.tex"

void _Wfinish_metafont(void);
/*:5*/
#line 204 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
