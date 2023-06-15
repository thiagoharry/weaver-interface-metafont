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


/*46:*/
#line 1041 "weaver-interface-metafont_en.tex"

struct context{
/*59:*/
#line 1340 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:59*//*75:*/
#line 1675 "weaver-interface-metafont_en.tex"

void*variables;
/*:75*/
#line 1043 "weaver-interface-metafont_en.tex"

};
/*:46*//*47:*/
#line 1055 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*71:*/
#line 1613 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:71*//*89:*/
#line 2006 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:89*//*98:*/
#line 2167 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:98*//*113:*/
#line 2522 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:113*//*122:*/
#line 2671 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:122*//*169:*/
#line 3835 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:169*//*479:*/
#line 13429 "weaver-interface-metafont_en.tex"

int current_depth;
/*:479*/
#line 1060 "weaver-interface-metafont_en.tex"

};
/*:47*/
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
