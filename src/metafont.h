/*4:*/
#line 151 "weaver-interface-metafont.tex"

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
#line 111 "weaver-interface-metafont.tex"

#include "interface.h"
/*:2*/
#line 161 "weaver-interface-metafont.tex"


/*37:*/
#line 926 "weaver-interface-metafont.tex"

struct context{

};
/*:37*//*38:*/
#line 937 "weaver-interface-metafont.tex"

struct metafont{
char*file;

};
/*:38*/
#line 163 "weaver-interface-metafont.tex"

/*1:*/
#line 96 "weaver-interface-metafont.tex"

void _Wmetafont_loading(void*(*permanent_alloc)(size_t),
void(*permanent_free)(void*),
void*(*temporary_alloc)(size_t),
void(*temporary_free)(void*),
void(*before_loading_interface)(void),
void(*after_loading_interface)(void),
char*source_filename,
struct user_interface*target);
/*:1*//*3:*/
#line 122 "weaver-interface-metafont.tex"

struct metafont*new_metafont(char*filename);
/*:3*/
#line 164 "weaver-interface-metafont.tex"

#ifdef __cplusplus
}
#endif
#endif
//*:4*/
