/*
  A program that evaluates Weaver-Metafont programs. Created to be
  used in benchmarks against original METAFONT program.
*/

#include "metafont.c"

#include <stdlib.h>
#include <math.h>
#if defined(_WIN32)
#include <Windows.h>
#else
#include <sys/time.h>
#endif

#if defined(__EMSCRIPTEN__)
#include <emscripten.h>
#endif

// Random number function
uint64_t my_rand(void){
  return 5;
}

int main(int argc, char **argv){
  struct metafont *mf;
  struct context *cx;
  void *p;
  bool ret;
  if(!_Winit_metafont(malloc, free, malloc, free, my_rand, 36)){
    fprintf(stderr, "ERROR: Test cannot be done. Initialization failed.\n");
    exit(1);
  }
  if(argc < 2){
    fprintf(stderr, "ERROR: No Weaver-Metafont program as argument.\n");
    exit(1);
  }
  mf = init_metafont(malloc, free, argv[1]);
  cx = init_context();
  p = lexer(mf, malloc, free, "tests/empty.mf");
  ret = eval_program(mf, cx, p);
  if(!ret){
    fprintf(stderr, "ERROR: Program failed.\n");
    exit(1);
  }
  free_token_list(free, p);
  destroy_metafont(mf);
  destroy_context(cx);
  _Wfinish_metafont();
  return 0;
}
