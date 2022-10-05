/*5:*/
#line 173 "weaver-interface-metafont.tex"

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
#line 183 "weaver-interface-metafont.tex"


/*43:*/
#line 1035 "weaver-interface-metafont.tex"

struct context{
/*55:*/
#line 1275 "weaver-interface-metafont.tex"

int nesting_level;
/*:55*//*66:*/
#line 1509 "weaver-interface-metafont.tex"

void*variables;
/*:66*/
#line 1037 "weaver-interface-metafont.tex"

};
/*:43*//*44:*/
#line 1048 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*62:*/
#line 1447 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:62*//*80:*/
#line 1831 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:80*//*98:*/
#line 2242 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:98*//*144:*/
#line 3480 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:144*/
#line 1053 "weaver-interface-metafont.tex"

};
/*:44*/
#line 185 "weaver-interface-metafont.tex"

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

void Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int pt);
/*:4*/
#line 186 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:5*/
