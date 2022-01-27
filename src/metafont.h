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


/*40:*/
#line 992 "weaver-interface-metafont.tex"

struct context{
/*52:*/
#line 1257 "weaver-interface-metafont.tex"

int nesting_level;
/*:52*//*63:*/
#line 1527 "weaver-interface-metafont.tex"

void*variables;
/*:63*/
#line 994 "weaver-interface-metafont.tex"

};
/*:40*//*41:*/
#line 1005 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*59:*/
#line 1468 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:59*/
#line 1010 "weaver-interface-metafont.tex"

};
/*:41*/
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
//*:5*/
