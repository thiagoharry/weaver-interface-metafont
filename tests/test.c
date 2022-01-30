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

#include <string.h>

int numero_de_testes = 0, acertos = 0, falhas = 0;
void imprime_resultado(void){
  printf("\n%d tests: %d sucess, %d fails\n\n",
	 numero_de_testes, acertos, falhas);
}

void assert(char *descricao, bool valor){
  char pontos[72], *s = descricao;
  size_t tamanho_string = 0;
  int i;
  while(*s)
    tamanho_string += (*s++ & 0xC0) != 0x80;
  pontos[0] = ' ';
  for(i = 1; i < 71 - (int) tamanho_string; i ++)
    pontos[i] = '.';
  pontos[i] = '\0';
  numero_de_testes ++;
  printf("%s%s", descricao, pontos);
  if(valor){
#if defined(__unix__) && !defined(__EMSCRIPTEN__)
    printf("\e[32m[OK]\033[0m\n");
#else
    printf("[OK]\n");
#endif
    acertos ++;
  }
  else{
#if defined(__unix__) && !defined(__EMSCRIPTEN__)
    printf("\033[0;31m[FAIL]\033[0m\n");
#else
    printf("[FAIL]\n");
#endif
    falhas ++;
  }
}

// Random number function
uint64_t my_rand(void){
  return 5;
}

void test_empty_programs(void){
  struct metafont *mf;
  struct context *cx;
  bool ret;
  mf = init_metafont(malloc, free, "tests/empty.mf");
  cx = init_context();
  void *p = lexer(mf, malloc, free, "tests/empty.mf");
  ret = eval_program(mf, cx, p);
  assert("Testing empty program", ret);
  free_token_list(free, p);
  p = lexer(mf, malloc, free, "tests/empty_statements.mf");
  ret = eval_program(mf, cx, p);
  free_token_list(free, p);
  destroy_metafont(mf);
  destroy_context(cx);
  assert("Testing program with empty statements", ret);
}

void test_compound_statements(void){
  struct metafont *mf;
  struct context *cx;
  bool ret;
  mf = init_metafont(malloc, free, "tests/compound.mf");
  cx = init_context();
  void *p = lexer(mf, malloc, free, "tests/compound.mf");
  ret = eval_program(mf, cx, p);
  assert("Testing compound statements", ret);
  free_token_list(free, p);
  p = lexer(mf, malloc, free, "tests/compound_wrong.mf");
  ret = eval_program(mf, cx, p);
  free_token_list(free, p);
  destroy_metafont(mf);
  destroy_context(cx);
  assert("Detecting wrong compound statements", !ret);
}

void test_variables(void){
  struct metafont *mf;
  struct context *cx;
  bool ret;
  mf = init_metafont(malloc, free, "tests/variables.mf");
  cx = init_context();
  void *p = lexer(mf, malloc, free, "tests/variables.mf");
  ret = eval_program(mf, cx, p);
  ret = ret && (mf -> named_variables != NULL) &&
    (mf -> global_variables != NULL) &&
    (cx -> variables != NULL);
  assert("Testing variable declaration", ret);
  free_token_list(free, p);
  destroy_metafont(mf);
  destroy_context(cx);
}

void test_assignments(void){
 struct metafont *mf;
  struct context *cx;
  bool ret;
  mf = init_metafont(malloc, free, "tests/wrong_assignment.mf");
  cx = init_context();
  void *p = lexer(mf, malloc, free, "tests/wrong_assignment.mf");
  ret = eval_program(mf, cx, p);
  assert("Detecting wrong assignment", !ret);
  free_token_list(free, p);
  destroy_metafont(mf);
  destroy_context(cx);
}

void test_lexer(void){
  void *p, *token_pointer;
  bool ok = true;
  struct metafont *mf;
  struct context *cx;
  mf = init_metafont(malloc, free, "tests/ridiculous.mf");
  token_pointer = lexer(mf, malloc, free,
				  "tests/ridiculous.mf");
  cx = init_context();
  p = token_pointer;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "xx3")){
    printf("ERROR: Expected 'xx', found '%s'\n",
	   ((struct symbolic_token *) p) -> value);
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct numeric_token *) p) -> type != TYPE_NUMERIC){
    ok = false;
    goto test_lexer_end;
  }
  if(((struct numeric_token *) p) -> value - 0.1 > 0.00002){
    printf("ERROR: Expected '%.f', found '%.f'\n", 3.1,
	   ((struct numeric_token *) p) -> value);
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct numeric_token *) p) -> type != TYPE_NUMERIC){
    ok = false;
    goto test_lexer_end;
  }
  if(((struct numeric_token *) p) -> value - 0.6 > 0.00002){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    printf("ERROR: Expected '%d', found '%d'\n", TYPE_SYMBOLIC,
	   ((struct symbolic_token *) p) -> type);
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "..")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "[[")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "a")){
    printf("ERROR: Expected 'a', found '%s'\n",
	   ((struct symbolic_token *) p) -> value);
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "+-")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "bc_d")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "e")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_CLOSE_BRACKET){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_CLOSE_BRACKET){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct string_token *) p) -> type != TYPE_STRING){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct string_token *) p) -> value, "a %")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next; 
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "<|>")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_OPEN_PARENTHESIS){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_OPEN_PARENTHESIS){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_SYMBOLIC){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct symbolic_token *) p) -> value, "$")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct numeric_token *) p) -> type != TYPE_NUMERIC){
    ok = false;
    goto test_lexer_end;
  }
  if(((struct numeric_token *) p) -> value - 1.0 > 0.00002){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct numeric_token *) p) -> type != TYPE_NUMERIC){
    ok = false;
    goto test_lexer_end;
  }
  if(((struct numeric_token *) p) -> value - 5.0 > 0.00002){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct string_token *) p) -> type != TYPE_STRING){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct string_token *) p) -> value, "+-")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next; 
  if(((struct string_token *) p) -> type != TYPE_STRING){
    ok = false;
    goto test_lexer_end;
  }
  if(strcmp(((struct string_token *) p) -> value, "")){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next; 
  if(p != NULL){
    ok = false;
    goto test_lexer_end;
  } 
 test_lexer_end:
  assert("Testing METAFONT Lexer", ok);
  ok = eval_program(mf, cx, token_pointer);
  assert("Wrong program not parsed", !ok);
  free_token_list(free, token_pointer);
  destroy_metafont(mf);
  destroy_context(cx);
}


int main(int argc, char **argv){
  Winit_metafont(malloc, free, malloc, free, my_rand, 36);
  test_lexer();
  test_empty_programs();
  test_compound_statements();
  test_variables();
  test_assignments();
  imprime_resultado();
  return 0;
}
