/*6:*/
#line 173 "weaver-interface-metafont_en.tex"

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
#line 105 "weaver-interface-metafont_en.tex"

#include "interface.h"
/*:2*/
#line 183 "weaver-interface-metafont_en.tex"


/*520:*/
#line 14214 "weaver-interface-metafont_en.tex"

struct _glyph;
/*:520*/
#line 185 "weaver-interface-metafont_en.tex"

/*56:*/
#line 1287 "weaver-interface-metafont_en.tex"

struct context{
/*69:*/
#line 1586 "weaver-interface-metafont_en.tex"

int nesting_level;
struct generic_token*end_token_stack;
/*:69*//*85:*/
#line 1922 "weaver-interface-metafont_en.tex"

void*variables;
/*:85*/
#line 1289 "weaver-interface-metafont_en.tex"

};
/*:56*//*57:*/
#line 1301 "weaver-interface-metafont_en.tex"

struct metafont{
char*file;
void*(*alloc)(size_t);
void(*free)(void*);
/*81:*/
#line 1860 "weaver-interface-metafont_en.tex"

void*named_variables;
void*global_variables;
/*:81*//*99:*/
#line 2253 "weaver-interface-metafont_en.tex"

void*internal_numeric_variables;
/*:99*//*108:*/
#line 2412 "weaver-interface-metafont_en.tex"

struct transform_variable*internal_transform_variables;
/*:108*//*123:*/
#line 2775 "weaver-interface-metafont_en.tex"

struct pen_variable*internal_pen_variables;
/*:123*//*133:*/
#line 2940 "weaver-interface-metafont_en.tex"

struct picture_variable*internal_picture_variables;
/*:133*//*180:*/
#line 4104 "weaver-interface-metafont_en.tex"

bool have_stored_normaldeviate;
float normaldeviate;
/*:180*//*467:*/
#line 12459 "weaver-interface-metafont_en.tex"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:467*//*514:*/
#line 14059 "weaver-interface-metafont_en.tex"

int current_depth;
/*:514*//*517:*/
#line 14183 "weaver-interface-metafont_en.tex"

bool loading;
/*:517*//*522:*/
#line 14243 "weaver-interface-metafont_en.tex"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
/*:522*/
#line 1306 "weaver-interface-metafont_en.tex"

};
/*:57*/
#line 186 "weaver-interface-metafont_en.tex"

/*1:*/
#line 90 "weaver-interface-metafont_en.tex"

void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
/*:1*//*3:*/
#line 115 "weaver-interface-metafont_en.tex"

struct metafont*new_metafont(char*filename);
/*:3*//*4:*/
#line 125 "weaver-interface-metafont_en.tex"

bool _Winit_metafont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int pt);
/*:4*//*5:*/
#line 146 "weaver-interface-metafont_en.tex"

void _Wfinish_metafont(void);
/*:5*/
#line 187 "weaver-interface-metafont_en.tex"

#ifdef __cplusplus
}
#endif
#endif
/*:6*/
