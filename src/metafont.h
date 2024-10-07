/*7:*/
#line 361 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT
#define __WEAVER_METAFONT
#ifdef __cplusplus
extern"C"{
#endif
#line 367 "weaver-interface-metafont_en.cweb"
#include <stdbool.h>  
#include <stdlib.h>  
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>  
#endif
#line 372 "weaver-interface-metafont_en.cweb"
#if !defined(_WIN32)
#include <sys/param.h>  
#endif
#line 375 "weaver-interface-metafont_en.cweb"
/*2:*/
#line 286 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
#include "interface.h"
#endif
#line 290 "weaver-interface-metafont_en.cweb"
/*:2*//*24:*/
#line 827 "weaver-interface-metafont_en.cweb"

#if defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#include <pthread.h> 
#endif
#line 831 "weaver-interface-metafont_en.cweb"
/*:24*/
#line 375 "weaver-interface-metafont_en.cweb"


/*678:*/
#line 17357 "weaver-interface-metafont_en.cweb"

struct _glyph;
/*:678*/
#line 377 "weaver-interface-metafont_en.cweb"

/*75:*/
#line 2102 "weaver-interface-metafont_en.cweb"

struct context{
char current_character[5];
/*91:*/
#line 2451 "weaver-interface-metafont_en.cweb"

int nesting_level;
struct linked_token*end_token_stack;
/*:91*//*116:*/
#line 2875 "weaver-interface-metafont_en.cweb"

struct variable*variables;
/*:116*//*134:*/
#line 3213 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:134*//*196:*/
#line 5009 "weaver-interface-metafont_en.cweb"

struct pen_variable*currentpen;
/*:196*//*209:*/
#line 5180 "weaver-interface-metafont_en.cweb"

struct picture_variable*currentpicture;
/*:209*//*569:*/
#line 13915 "weaver-interface-metafont_en.cweb"

float pen_lft,pen_rt,pen_top,pen_bot;
/*:569*//*648:*/
#line 16740 "weaver-interface-metafont_en.cweb"

float color[4];
/*:648*//*660:*/
#line 16916 "weaver-interface-metafont_en.cweb"

GLuint currentpicture_fb;
/*:660*//*675:*/
#line 17229 "weaver-interface-metafont_en.cweb"

int current_depth;
/*:675*//*691:*/
#line 17725 "weaver-interface-metafont_en.cweb"

struct _glyph*current_glyph;
/*:691*/
#line 2105 "weaver-interface-metafont_en.cweb"

};
/*:75*//*76:*/
#line 2119 "weaver-interface-metafont_en.cweb"

struct metafont{
/*23:*/
#line 815 "weaver-interface-metafont_en.cweb"

#if defined(_WIN32)
CRITICAL_SECTION mutex;
#elif defined(__linux__) || defined(BSD) || defined(W_ALWAYS_USE_THREADS)
#line 819 "weaver-interface-metafont_en.cweb"
pthread_mutex_t mutex;
#endif
#line 821 "weaver-interface-metafont_en.cweb"
/*:23*/
#line 2121 "weaver-interface-metafont_en.cweb"

char*file;
bool loading;
/*112:*/
#line 2818 "weaver-interface-metafont_en.cweb"

struct named_variable*named_variables;
struct variable*variables;
/*:112*//*133:*/
#line 3206 "weaver-interface-metafont_en.cweb"

struct numeric_variable*internal_numeric_variables;
/*:133*//*145:*/
#line 3417 "weaver-interface-metafont_en.cweb"

struct transform_variable*internal_transform_variables;
/*:145*//*197:*/
#line 5017 "weaver-interface-metafont_en.cweb"

struct pen_variable*internal_pen_variables;
/*:197*//*281:*/
#line 6521 "weaver-interface-metafont_en.cweb"

bool have_stored_normaldeviate;
float normaldeviate;
/*:281*//*655:*/
#line 16854 "weaver-interface-metafont_en.cweb"

void*mono_expr_begin,*mono_expr_end;
/*:655*//*681:*/
#line 17399 "weaver-interface-metafont_en.cweb"

struct _glyph*glyphs[332];
struct _glyph*first_glyph;
int number_of_glyphs;
/*:681*//*719:*/
#line 18540 "weaver-interface-metafont_en.cweb"

int err,errno_line;
char errno_character[5];
char*errno_str;
int errno_int;
/*:719*/
#line 2124 "weaver-interface-metafont_en.cweb"

};
/*:76*/
#line 378 "weaver-interface-metafont_en.cweb"

/*1:*/
#line 267 "weaver-interface-metafont_en.cweb"

#if defined(WEAVER_ENGINE)
void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
#endif
#line 278 "weaver-interface-metafont_en.cweb"
/*:1*//*3:*/
#line 300 "weaver-interface-metafont_en.cweb"

struct metafont*_Wnew_metafont(char*filename);
void _Wdestroy_metafont(struct metafont*mf);
/*:3*//*4:*/
#line 311 "weaver-interface-metafont_en.cweb"

bool _Winit_weavefont(void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
uint64_t(*rand)(void),int dpi);
/*:4*//*5:*/
#line 329 "weaver-interface-metafont_en.cweb"

void _Wfinish_weavefont(void);
/*:5*//*6:*/
#line 337 "weaver-interface-metafont_en.cweb"

void _Wprint_metafont_error(struct metafont*);
/*:6*//*697:*/
#line 17930 "weaver-interface-metafont_en.cweb"

bool _Wwrite_numeric_variable(struct metafont*mf,char*name,float value);
float _Wread_numeric_variable(struct metafont*mf,char*name);
/*:697*//*701:*/
#line 18027 "weaver-interface-metafont_en.cweb"

bool _Wrender_glyph(struct metafont*mf,char*glyph,
char*next_glyph,GLuint*texture,
int*width,int*height,int*depth,
int*italcorr,int*kerning);
/*:701*/
#line 379 "weaver-interface-metafont_en.cweb"

#ifdef __cplusplus
}
#endif
#line 383 "weaver-interface-metafont_en.cweb"
#endif
#line 384 "weaver-interface-metafont_en.cweb"
/*:7*/
