/*6:*/
#line 185 "weaver-interface-metafont.tex"

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
#line 110 "weaver-interface-metafont.tex"

#include "interface.h"
/*:2*/
#line 195 "weaver-interface-metafont.tex"


/*45:*/
#line 1061 "weaver-interface-metafont.tex"

struct context{
/*58:*/
#line 1336 "weaver-interface-metafont.tex"

int nesting_level;
/*:58*//*69:*/
#line 1570 "weaver-interface-metafont.tex"

void*variables;
/*:69*/
#line 1063 "weaver-interface-metafont.tex"

};
/*:45*//*46:*/
#line 1074 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*65:*/
#line 1508 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:65*//*83:*/
#line 1900 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:83*//*92:*/
#line 2063 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:92*//*108:*/
#line 2439 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:108*//*117:*/
#line 2587 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:117*//*165:*/
#line 3802 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:165*/
#line 1079 "weaver-interface-metafont.tex"

};
/*:46*/
#line 197 "weaver-interface-metafont.tex"

/*1:*/
#line 95 "weaver-interface-metafont.tex"

void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
/*:1*//*3:*/
#line 121 "weaver-interface-metafont.tex"

struct metafont*new_metafont(char*filename);
/*:3*//*4:*/
#line 132 "weaver-interface-metafont.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int pt);
/*:4*//*5:*/
#line 154 "weaver-interface-metafont.tex"

void _Wfinish_metafont(void);
/*:5*/
#line 198 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
