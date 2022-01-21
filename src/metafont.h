/*4:*/
#line 136 "weaver-interface-metafont_en.tex"

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
#line 146 "weaver-interface-metafont_en.tex"


/*37:*/
#line 907 "weaver-interface-metafont_en.tex"

struct context{
/*46:*/
#line 1102 "weaver-interface-metafont_en.tex"

int nesting_level;
/*:46*/
#line 909 "weaver-interface-metafont_en.tex"

};
/*:37*//*38:*/
#line 919 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;

};
/*:38*/
#line 148 "weaver-interface-metafont_en.tex"

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
/*:3*/
#line 149 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:4*/
