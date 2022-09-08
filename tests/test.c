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

#define ALMOST_EQUAL(a, b) (fabs(a - b) < 0.00002)

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
  struct numeric_variable *n;
  struct pair_variable *p;
  struct named_variable *named;
  bool ret;
  mf = init_metafont(malloc, free, "tests/variables.mf");
  cx = init_context();
  void *tok = lexer(mf, malloc, free, "tests/variables.mf");
  ret = eval_program(mf, cx, tok);
  ret = ret && (mf -> named_variables != NULL) &&
    (mf -> global_variables != NULL) &&
    (cx -> variables != NULL);
  assert("Testing variable declaration", ret);
  named = (struct named_variable *) mf -> named_variables;
  n = (struct numeric_variable *) named -> var;
  assert("Testing numeric expression", n -> value == 116.0);
  if(n -> value != 116.0){
    printf("ERROR: Exprected value: '%f', Found value: '%f'\n",
           116.0, n -> value);
  }
  named = (struct named_variable *) named -> next;
  n = (struct numeric_variable *) named -> var;
  assert("Chained assignments are working", n -> value == 116.0);
  p = (struct pair_variable *) mf -> global_variables;
  assert("Testing pair expression", p -> type == TYPE_T_PAIR &&
         fabs(p -> x) < 0.00002 && fabs(p -> y - 3.0) < 0.00002);
  if(fabs(p -> x) >= 0.00002 && fabs(p -> y - 3.0) >= 0.00002){
    printf("ERROR: Exprected value: '(%f, %f)', Found value: '(%f,%f)'\n",
           0.0, 3.0, p -> x, p -> y);
  }
  free_token_list(free, tok);
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
  if(((struct symbolic_token *) p) -> type != TYPE_JOIN){
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
  if(((struct symbolic_token *) p) -> type != TYPE_CLOSE_BRACKETS){
    ok = false;
    goto test_lexer_end;
  }
  p = ((struct generic_token *) p) -> next;
  if(((struct symbolic_token *) p) -> type != TYPE_CLOSE_BRACKETS){
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

void test_path_expressions(void){
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9;
  struct path_variable *path_p1, *path_p2, *path_p3, *path_p4, *path_p5, *path_p6,
    *path_p7, *path_p8, *path_p9;
  mf = init_metafont(malloc, free, "tests/path_expressions.mf");
  cx = init_context();
  void *p = lexer(mf, malloc, free, "tests/path_expressions.mf");
  ret = eval_program(mf, cx, p);
  assert("Interpreting program with primary path expressions", ret);
  p1 = (struct named_variable *) mf -> named_variables;
  p2 = p1 -> next;
  p3 = p2 -> next;
  p4 = p3 -> next;
  p5 = p4 -> next;
  p6 = p5 -> next;
  p7 = p6 -> next;
  p8 = p7 -> next;
  p9 = p8 -> next;
  path_p1 = (struct path_variable *) p1 -> var;
  path_p2 = (struct path_variable *) p2 -> var;
  path_p3 = (struct path_variable *) p3 -> var;
  path_p4 = (struct path_variable *) p4 -> var;
  path_p5 = (struct path_variable *) p5 -> var;
  path_p6 = (struct path_variable *) p6 -> var;
  path_p7 = (struct path_variable *) p7 -> var;
  path_p8 = (struct path_variable *) p8 -> var;
  path_p9 = (struct path_variable *) p9 -> var;
  assert("Assigning pair literal to path",
	 path_p1 -> cyclic == false && path_p1 -> length == 1 &&
	 path_p1 -> points[0].x == 1.0 && path_p1 -> points[0].y == 5.0 &&
	 path_p1 -> points[0].u_x == 1.0 && path_p1 -> points[0].u_y == 5.0 &&
	 path_p1 -> points[0].v_x == 1.0 && path_p1 -> points[0].v_y == 5.0);
  assert("Assigning between path variables",
	 path_p2 -> cyclic == false && path_p2 -> length == 1 &&
	 path_p2 -> points[0].x == 1.0 && path_p2 -> points[0].y == 5.0 &&
	 path_p2 -> points[0].u_x == 1.0 && path_p2 -> points[0].u_y == 5.0 &&
	 path_p2 -> points[0].v_x == 1.0 && path_p2 -> points[0].v_y == 5.0);
  assert("Reversing single point",
	 path_p3 -> cyclic == false && path_p3 -> length == 1 &&
	 path_p3 -> points[0].x == 1.0 && path_p3 -> points[0].y == 5.0 &&
	 path_p3 -> points[0].u_x == 1.0 && path_p3 -> points[0].u_y == 5.0 &&
	 path_p3 -> points[0].v_x == 1.0 && path_p3 -> points[0].v_y == 5.0);
  //printf("path_p4: %p\n", path_p4);
  assert("Subpath of single point",
	 path_p4 != NULL &&
	 path_p4 -> cyclic == false &&
	 path_p4 -> length == 1 &&
	 path_p4 -> points[0].x == 1.0 && path_p4 -> points[0].y == 5.0 &&
	 path_p4 -> points[0].u_x == 1.0 && path_p4 -> points[0].u_y == 5.0 &&
	 path_p4 -> points[0].v_x == 1.0 && path_p4 -> points[0].v_y == 5.0);
  assert("Dividing pair by numeric as path expression",
	 path_p5 -> cyclic == false && path_p5 -> length == 1 &&
	 path_p5 -> points[0].x == 0.5 && path_p5 -> points[0].y == 2.5 &&
	 path_p5 -> points[0].u_x == 0.5 && path_p5 -> points[0].u_y == 2.5 &&
	 path_p5 -> points[0].v_x == 0.5 && path_p5 -> points[0].v_y == 2.5);
  assert("Multiplying numeric by pair as path expression",
	 path_p6 -> cyclic == false && path_p6 -> length == 1 &&
	 path_p6 -> points[0].x == 2.0 && path_p6 -> points[0].y == 10.0 &&
	 path_p6 -> points[0].u_x == 2.0 && path_p6 -> points[0].u_y == 10.0 &&
	 path_p6 -> points[0].v_x == 2.0 && path_p6 -> points[0].v_y == 10.0);
  assert("Pair with transformer as path expression",
	 path_p7 -> cyclic == false && path_p7 -> length == 1 &&
	 ALMOST_EQUAL(path_p7 -> points[0].x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].y, 1.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].u_x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].u_y, 1.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].v_x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].v_y, 1.0));
  assert("Tertiary pair expression as path expression",
	 path_p8 -> cyclic == false && path_p8 -> length == 1 &&
	 path_p8 -> points[0].x == 1.0 && path_p8 -> points[0].y == 1.0 &&
	 path_p8 -> points[0].u_x == 1.0 && path_p8 -> points[0].u_y == 1.0 &&
	 path_p8 -> points[0].v_x == 1.0 && path_p8 -> points[0].v_y == 1.0);
  assert("Simple join between two path variables",
	 path_p9 -> cyclic == false && path_p9 -> length == 2 &&
	 path_p9 -> points[0].x == 1.0 && path_p9 -> points[0].y == 5.0 &&
	 path_p9 -> points[0].u_x == 1.0 && path_p9 -> points[0].u_y == 3.0 &&
	 path_p9 -> points[0].v_x == 1.0 && path_p9 -> points[0].v_y == 2.0 &&
	 path_p9 -> points[1].x == 1.0 && path_p9 -> points[1].y == 1.0 &&
	 path_p9 -> points[1].u_x == 1.0 && path_p9 -> points[1].u_y == 1.0 &&
	 path_p9 -> points[1].v_x == 1.0 && path_p9 -> points[1].v_y == 1.0);
  free_token_list(free, p);
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
  test_path_expressions();
  imprime_resultado();
  return 0;
}
