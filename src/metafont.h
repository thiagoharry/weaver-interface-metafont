/*5:*/
#line 157 "weaver-interface-metafont_en.tex"

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
#line 167 "weaver-interface-metafont_en.tex"


/*40:*/
#line 966 "weaver-interface-metafont_en.tex"

struct context{
/*52:*/
#line 1230 "weaver-interface-metafont_en.tex"

int nesting_level;
/*:52*//*62:*/
#line 1493 "weaver-interface-metafont_en.tex"

void*variables;
/*:62*/
#line 968 "weaver-interface-metafont_en.tex"

};
/*:40*//*41:*/
#line 980 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*58:*/
#line 1434 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:58*/
#line 985 "weaver-interface-metafont_en.tex"

};
/*:41*/
#line 169 "weaver-interface-metafont_en.tex"

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

void Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int pt);
/*:4*/
#line 170 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:5*/
