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


/*43:*/
#line 1008 "weaver-interface-metafont_en.tex"

struct context{
/*55:*/
#line 1248 "weaver-interface-metafont_en.tex"

int nesting_level;
/*:55*//*66:*/
#line 1485 "weaver-interface-metafont_en.tex"

void*variables;
/*:66*/
#line 1010 "weaver-interface-metafont_en.tex"

};
/*:43*//*44:*/
#line 1022 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*62:*/
#line 1423 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:62*//*80:*/
#line 1796 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:80*//*134:*/
#line 3157 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:134*/
#line 1027 "weaver-interface-metafont_en.tex"

};
/*:44*/
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
