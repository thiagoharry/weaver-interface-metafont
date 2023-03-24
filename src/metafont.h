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


/*45:*/
#line 1034 "weaver-interface-metafont_en.tex"

struct context{
/*58:*/
#line 1305 "weaver-interface-metafont_en.tex"

int nesting_level;
/*:58*//*69:*/
#line 1542 "weaver-interface-metafont_en.tex"

void*variables;
/*:69*/
#line 1036 "weaver-interface-metafont_en.tex"

};
/*:45*//*46:*/
#line 1048 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*65:*/
#line 1480 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:65*//*83:*/
#line 1871 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:83*//*92:*/
#line 2032 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:92*//*107:*/
#line 2387 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:107*//*116:*/
#line 2536 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:116*//*163:*/
#line 3700 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:163*/
#line 1053 "weaver-interface-metafont_en.tex"

};
/*:46*/
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
