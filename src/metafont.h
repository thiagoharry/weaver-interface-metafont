/*6:*/
#line 187 "weaver-interface-metafont.tex"

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
#line 197 "weaver-interface-metafont.tex"


/*46:*/
#line 1070 "weaver-interface-metafont.tex"

struct context{
/*59:*/
#line 1375 "weaver-interface-metafont.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:59*//*75:*/
#line 1713 "weaver-interface-metafont.tex"

void*variables;
/*:75*/
#line 1072 "weaver-interface-metafont.tex"

};
/*:46*//*47:*/
#line 1083 "weaver-interface-metafont.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*71:*/
#line 1651 "weaver-interface-metafont.tex"

void*named_variables;
void*global_variables;
/*:71*//*89:*/
#line 2045 "weaver-interface-metafont.tex"

void*internal_numeric_variables;
/*:89*//*98:*/
#line 2208 "weaver-interface-metafont.tex"

struct transform_variable*internal_transform_variables;
/*:98*//*114:*/
#line 2587 "weaver-interface-metafont.tex"

struct pen_variable*internal_pen_variables;
/*:114*//*123:*/
#line 2735 "weaver-interface-metafont.tex"

struct picture_variable*internal_picture_variables;
/*:123*//*169:*/
#line 3906 "weaver-interface-metafont.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:169*//*456:*/
#line 12876 "weaver-interface-metafont.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:456*//*487:*/
#line 13762 "weaver-interface-metafont.tex"

int current_depth;
/*:487*/
#line 1088 "weaver-interface-metafont.tex"

};
/*:47*/
#line 199 "weaver-interface-metafont.tex"

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
#line 134 "weaver-interface-metafont.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int pt);
/*:4*//*5:*/
#line 156 "weaver-interface-metafont.tex"

void _Wfinish_metafont(void);
/*:5*/
#line 200 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
