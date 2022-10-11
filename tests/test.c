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

#define ALMOST_EQUAL(a, b) (fabs(a - b) < 0.00004)

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
  struct named_variable *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9,
    *quartercircle, *halfcircle, *fullcircle, *unitsquare, *a, *b, *c,
    *d, *e, *f, *g, *h, *i, *j, *k, *l, *n, *q, *r, *s;
  struct path_variable *path_p1, *path_p2, *path_p3, *path_p4, *path_p5,
    *path_p6, *path_p7, *path_p8, *path_p9, *quartercircle_path,
    *halfcircle_path, *fullcircle_path, *unitsquare_path, *path_a,
    *path_b, *path_c, *path_d, *path_e, *path_f, *path_g, *path_h,
    *path_i, *path_j, *path_k, *path_l;
  struct numeric_variable *numeric_n;
  struct pair_variable *pair_q, *pair_r, *pair_s;
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
  quartercircle = p9 -> next;
  halfcircle = quartercircle -> next;
  fullcircle = halfcircle -> next;
  unitsquare = fullcircle -> next;
  a = unitsquare -> next;
  b = a -> next;
  c = b -> next;
  d = c -> next;
  e = d -> next;
  f = e -> next;
  g = f -> next;
  h = g -> next;
  i = h -> next;
  j = i -> next;
  k = j -> next;
  l = k -> next;
  n = l -> next;
  q = n -> next;
  r = q -> next;
  s = r -> next;
  path_p1 = (struct path_variable *) p1 -> var;
  path_p2 = (struct path_variable *) p2 -> var;
  path_p3 = (struct path_variable *) p3 -> var;
  path_p4 = (struct path_variable *) p4 -> var;
  path_p5 = (struct path_variable *) p5 -> var;
  path_p6 = (struct path_variable *) p6 -> var;
  path_p7 = (struct path_variable *) p7 -> var;
  path_p8 = (struct path_variable *) p8 -> var;
  path_p9 = (struct path_variable *) p9 -> var;
  quartercircle_path = (struct path_variable *) quartercircle -> var;
  halfcircle_path = (struct path_variable *) halfcircle -> var;
  fullcircle_path = (struct path_variable *) fullcircle -> var;
  unitsquare_path = (struct path_variable *) unitsquare -> var;
  path_a = (struct path_variable *) a -> var;
  path_b = (struct path_variable *) b -> var;
  path_c = (struct path_variable *) c -> var;
  path_d = (struct path_variable *) d -> var;
  path_e = (struct path_variable *) e -> var;
  path_f = (struct path_variable *) f -> var;
  path_g = (struct path_variable *) g -> var;
  path_h = (struct path_variable *) h -> var;
  path_i = (struct path_variable *) i -> var;
  path_j = (struct path_variable *) j -> var;
  path_k = (struct path_variable *) k -> var;
  path_l = (struct path_variable *) l -> var;
  numeric_n = (struct numeric_variable *) n -> var;
  pair_q = (struct pair_variable *) q -> var;
  pair_r = (struct pair_variable *) r -> var;
  pair_s = (struct pair_variable *) s -> var;
  assert("Assigning pair literal to path",
	 path_p1 -> cyclic == false && path_p1 -> length == 1 &&
	 path_p1 -> total_length == 1 &&
	 path_p1 -> points[0].x == 1.0 && path_p1 -> points[0].y == 5.0 &&
	 path_p1 -> points[0].u_x == 1.0 && path_p1 -> points[0].u_y == 5.0 &&
	 path_p1 -> points[0].v_x == 1.0 && path_p1 -> points[0].v_y == 5.0);
  assert("Assigning between path variables",
	 path_p2 -> cyclic == false && path_p2 -> length == 1 &&
	 path_p2 -> total_length == 1 &&
	 path_p2 -> points[0].x == 1.0 && path_p2 -> points[0].y == 5.0 &&
	 path_p2 -> points[0].u_x == 1.0 && path_p2 -> points[0].u_y == 5.0 &&
	 path_p2 -> points[0].v_x == 1.0 && path_p2 -> points[0].v_y == 5.0);
  assert("Reversing single point",
	 path_p3 -> cyclic == false && path_p3 -> length == 1 &&
	 path_p3 -> total_length == 1 &&
	 path_p3 -> points[0].x == 1.0 &&
	 path_p3 -> points[0].y == 5.0 &&
	 path_p3 -> points[0].u_x == 1.0 &&
	 path_p3 -> points[0].u_y == 5.0 &&
	 path_p3 -> points[0].v_x == 1.0 &&
	 path_p3 -> points[0].v_y == 5.0);
  assert("Reversing bigger path",
	 path_h -> total_length == 5 &&	 
	 ALMOST_EQUAL(get_point(path_h, 0) -> x, -0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> u_x, -0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> v_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> v_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> u_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> v_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> u_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> v_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> x, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> u_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> u_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> v_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> v_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> u_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> v_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> v_y, 0.0) &&
	 path_h -> cyclic == false);
  assert("Subpath of single point",
	 path_p4 != NULL &&
	 path_p4 -> cyclic == false &&
	 path_p4 -> length == 1 && path_p4 -> total_length == 1 &&
	 path_p4 -> points[0].x == 1.0 && path_p4 -> points[0].y == 5.0 &&
	 path_p4 -> points[0].u_x == 1.0 && path_p4 -> points[0].u_y == 5.0 &&
	 path_p4 -> points[0].v_x == 1.0 && path_p4 -> points[0].v_y == 5.0);
  assert("Dividing pair by numeric as path expression",
	 path_p5 -> cyclic == false && path_p5 -> length == 1 &&
	 path_p5 -> total_length == 1 &&
	 path_p5 -> points[0].x == 0.5 && path_p5 -> points[0].y == 2.5 &&
	 path_p5 -> points[0].u_x == 0.5 && path_p5 -> points[0].u_y == 2.5 &&
	 path_p5 -> points[0].v_x == 0.5 && path_p5 -> points[0].v_y == 2.5);
  assert("Multiplying numeric by pair as path expression",
	 path_p6 -> cyclic == false && path_p6 -> length == 1 &&
	 path_p6 -> total_length == 1 &&
	 path_p6 -> points[0].x == 2.0 && path_p6 -> points[0].y == 10.0 &&
	 path_p6 -> points[0].u_x == 2.0 && path_p6 -> points[0].u_y == 10.0 &&
	 path_p6 -> points[0].v_x == 2.0 && path_p6 -> points[0].v_y == 10.0);
  assert("Pair with transformer as path expression",
	 path_p7 -> cyclic == false && path_p7 -> length == 1 &&
	 path_p7 -> total_length == 1 &&
	 ALMOST_EQUAL(path_p7 -> points[0].x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].y, 1.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].u_x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].u_y, 1.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].v_x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].v_y, 1.0));
  assert("Tertiary pair expression as path expression",
	 path_p8 -> cyclic == false && path_p8 -> length == 1 &&
	 path_p8 -> total_length == 1 &&
	 path_p8 -> points[0].x == 1.0 && path_p8 -> points[0].y == 1.0 &&
	 path_p8 -> points[0].u_x == 1.0 && path_p8 -> points[0].u_y == 1.0 &&
	 path_p8 -> points[0].v_x == 1.0 && path_p8 -> points[0].v_y == 1.0);
  assert("Simple join with single control point between two path variables",
	 path_p9 -> cyclic == false && path_p9 -> length == 2 &&
	 path_p9 -> total_length == 2 &&
	 path_p9 -> points[0].x == 1.0 && path_p9 -> points[0].y == 5.0 &&
	 path_p9 -> points[0].u_x == 1.0 && path_p9 -> points[0].u_y == 3.0 &&
	 path_p9 -> points[0].v_x == 1.0 && path_p9 -> points[0].v_y == 3.0 &&
	 path_p9 -> points[1].x == 1.0 && path_p9 -> points[1].y == 1.0 &&
	 path_p9 -> points[1].u_x == 1.0 && path_p9 -> points[1].u_y == 1.0 &&
	 path_p9 -> points[1].v_x == 1.0 && path_p9 -> points[1].v_y == 1.0);
  assert("Simple join with double control points between two path variables",
	 quartercircle_path -> cyclic == false &&
	 quartercircle_path -> length == 3 &&
	 quartercircle_path -> total_length == 3 &&
	 quartercircle_path -> points[0].x == 0.5 &&
	 quartercircle_path -> points[0].y == 0.0 &&
	 quartercircle_path -> points[0].u_x == 0.5 &&
	 ALMOST_EQUAL(quartercircle_path -> points[0].u_y, 0.13261) &&
	 ALMOST_EQUAL(quartercircle_path -> points[0].v_x, 0.44733) &&
	 ALMOST_EQUAL(quartercircle_path -> points[0].v_y, 0.2598) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].x, 0.35356) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].y, 0.35356) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].u_x, 0.2598) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].u_y, 0.44733) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].v_x, 0.13261) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].v_y, 0.5) &&
	 quartercircle_path -> points[2].x == 0.0 &&
	 quartercircle_path -> points[2].y == 0.5 &&
	 quartercircle_path -> points[2].v_x == 0.0 &&
	 quartercircle_path -> points[2].v_y == 0.5 &&
	 quartercircle_path -> points[2].v_x == 0.0 &&
	 quartercircle_path -> points[2].v_y == 0.5);
  assert("Path concatenation and rotation",
	 halfcircle_path -> cyclic == false &&
	 halfcircle_path -> total_length == 5 &&
	 get_point(halfcircle_path, 0) -> x == 0.5 &&
	 get_point(halfcircle_path, 0) -> y == 0.0 &&
	 get_point(halfcircle_path, 0) -> u_x == 0.5 &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 0) -> u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 0) -> v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 0) -> v_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> x, 0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> u_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> v_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> y, 0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> u_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> v_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> x, -0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> u_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> u_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> v_x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> v_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> u_x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> v_x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> v_y, 0.0));
  assert("Cyclic path concatenation and rotation",
	 fullcircle_path -> total_length == 9 &&
	 get_point(fullcircle_path, 0) -> x == 0.5 &&
	 get_point(fullcircle_path, 0) -> y == 0.0 &&
	 get_point(fullcircle_path, 0) -> u_x == 0.5 &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 0) -> u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 0) -> v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 0) -> v_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> x, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> u_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> v_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> y, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> u_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> v_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> x, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> u_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> u_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> v_x, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> v_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> x, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> u_x, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> u_y, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> v_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> v_y, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> x, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> y, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> u_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> u_y, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> v_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> v_y, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> y, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> u_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> u_y, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> v_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> v_y, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> x, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> y, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> u_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> u_y, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> v_x, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> v_y, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> x, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> u_x, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> v_y, 0.2598) &&
	 fullcircle_path -> cyclic == true);
  assert("Path composed by straight lines",
	 unitsquare_path -> total_length == 5 &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> u_x, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> v_x, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> v_y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> u_x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> u_y, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> v_x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> v_y, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> u_x, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> u_y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> v_x, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> v_y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> u_x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> u_y, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> v_y, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> u_x, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> v_x, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> v_y, 0.0) &&
	 unitsquare_path -> cyclic == true);
  assert("Path composed by direction specifiers",
	 path_a -> total_length == 2 &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> u_x, 5.52284) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> v_x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> v_y, 4.47716) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> y, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> u_x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> u_y, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> v_x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> v_y, 10.0) &&
	 path_a -> cyclic == false);
  assert("Cyclic path composed by minimal direction specifiers",
	 path_b -> total_length == 4 &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> v_y, 0.89543) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> u_y, 2.50372) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> v_x, 2.60619) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> v_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> u_x, 17.31206) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> v_x, -14.31206) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> v_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> v_y, 0.89543) &&
	 path_b -> cyclic == true);
  assert("Second cyclic path composed by minimal direction specifiers",
	 path_d -> total_length == 4 &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> v_y, 0.89543) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> u_y, 2.50372) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> v_x, 2.60619) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> v_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> u_x, 17.31206) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> v_x, -14.31206) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> v_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> v_y, 0.89543) &&
	 path_d -> cyclic == true);
  assert("Path with direction derived from neighbor control point",
	 path_c -> total_length == 3 &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> u_x, -1.2818) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> u_y, -1.9227) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> v_x, 1.2532) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> v_y, 0.50641) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> u_x, -1.2818) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> u_y, -1.9227) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> v_x, 1.2532) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> v_y, 0.50641) &&
	 path_c -> cyclic == true);
  assert("Second path with directions derived from neighbor control points",
	 path_e -> total_length == 3 &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> u_y, 0.07417) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> v_x, -1.57869) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> v_y, -2.10492) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> v_y, 3.0) &&
	 path_e -> cyclic == true);
  assert("Computing non-standard path tension",
	 path_f -> total_length == 2 &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> u_x, 1.47276) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> v_y, 1.72386) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> v_y, 2.0) &&
	 path_f -> cyclic == false);
  assert("Computing path tension with 'atleast' keyword",
	 path_g -> total_length == 2 &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> u_x, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> u_y, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> v_y, 2.06097) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> u_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> u_y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> v_y, 1.0) &&
	 path_g -> cyclic == false);
  assert("Creating subpath bigger than non-cyclic path",
	 path_i -> total_length == 2 &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> u_x, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> u_y, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> v_y, 2.06097) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> u_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> u_y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> v_y, 1.0) &&
	 path_i -> cyclic == false);
  assert("Creating subpath bigger than cyclic path",
	 path_j -> total_length == 5 &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> u_y, 0.07417) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> v_x, -1.57869) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> v_y, -2.10492) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> u_y, 0.07417) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> v_x, -1.57869) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> v_y, -2.10492) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> v_y, 2.0) &&
	 path_j -> cyclic == false);
  assert("Creating subpath with reversed indices reverse the result",
	 path_k -> total_length == path_h -> total_length &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> x,
		      get_point(path_h, 0) -> x) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> y,
		      get_point(path_h, 0) -> y) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> u_x,
		      get_point(path_h, 0) -> u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> u_y,
		      get_point(path_h, 0) -> u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> v_x,
		      get_point(path_h, 0) -> v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> v_y,
		      get_point(path_h, 0) -> v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> x,
		      get_point(path_h, 1) -> x) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> y,
		      get_point(path_h, 1) -> y) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> u_x,
		      get_point(path_h, 1) -> u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> u_y,
		      get_point(path_h, 1) -> u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> v_x,
		      get_point(path_h, 1) -> v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> v_y,
		      get_point(path_h, 1) -> v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> x,
		      get_point(path_h, 2) -> x) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> y,
		      get_point(path_h, 2) -> y) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> u_x,
		      get_point(path_h, 2) -> u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> u_y,
		      get_point(path_h, 2) -> u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> v_x,
		      get_point(path_h, 2) -> v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> v_y,
		      get_point(path_h, 2) -> v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> x,
		      get_point(path_h, 3) -> x) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> y,
		      get_point(path_h, 3) -> y) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> u_x,
		      get_point(path_h, 3) -> u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> u_y,
		      get_point(path_h, 3) -> u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> v_x,
		      get_point(path_h, 3) -> v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> v_y,
		      get_point(path_h, 3) -> v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> x,
		      get_point(path_h, 4) -> x) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> y,
		      get_point(path_h, 4) -> y) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> u_x,
		      get_point(path_h, 4) -> u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> u_y,
		      get_point(path_h, 4) -> u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> v_x,
		      get_point(path_h, 4) -> v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> v_y,
		      get_point(path_h, 4) -> v_y) &&
	 path_k -> cyclic == false);
  assert("Creating subpath smaller than initial path",
	 path_l -> total_length == 3 &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> x, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> u_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> v_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> u_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> v_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> u_x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> u_y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> v_x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> v_y, 0.35356) &&
	 path_j -> cyclic == false);
  assert("Computing correctly the lenght of a path",
	 numeric_n -> value == 8.0);
  assert("Getting correct point in a path by index",
	 ALMOST_EQUAL(pair_q -> x, 0.0) &&
	 ALMOST_EQUAL(pair_q -> y, 0.5));
  assert("Getting correct precontrol point in a path by index",
	 ALMOST_EQUAL(pair_r -> x, -0.5) &&
	 ALMOST_EQUAL(pair_r -> y, 0.13261));
  assert("Getting correct postcontrol point in a path by index",
	 ALMOST_EQUAL(pair_s -> x, 0.2598) &&
	 ALMOST_EQUAL(pair_s -> y, 0.44733));
  free_token_list(free, p);
  destroy_metafont(mf);
  destroy_context(cx);
}

void test_pen_expressions(void){
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *p1, *p2, *p3;
  struct pen_variable *pen_p1, *pen_p2, *pen_p3;
  mf = init_metafont(malloc, free, "tests/pen_expressions.mf");
  cx = init_context();
  void *p = lexer(mf, malloc, free, "tests/pen_expressions.mf");
  ret = eval_program(mf, cx, p);
  p1 = (struct named_variable *) mf -> named_variables;
  p2 = p1 -> next;
  p3 = p2 -> next;
  pen_p1 = (struct pen_variable *) p1 -> var;
  pen_p2 = (struct pen_variable *) p2 -> var;
  pen_p3 = (struct pen_variable *) p3 -> var;
  assert("Interpreting program with pen expressions", ret);
  assert("Assigning pen variable",
	 pen_p1 -> format == NULL &&
	 pen_p1 -> flags == (FLAG_CONVEX | FLAG_SQUARE | FLAG_STRAIGHT) &&
	 pen_p1 -> referenced == NULL &&
	 pen_p1 -> number_of_vertices == 0); // Not triangulated
  assert("Assigning nullpen",
	 pen_p2 -> format == NULL &&
	 pen_p2 -> flags == FLAG_NULL &&
	 pen_p2 -> referenced == NULL &&
	 pen_p2 -> number_of_vertices == 0);
  assert("Assigning pencircle",
	 pen_p3 -> format == NULL &&
	 pen_p3 -> flags == (FLAG_CONVEX | FLAG_CIRCULAR) &&
	 pen_p3 -> referenced == NULL &&
	 pen_p3 -> number_of_vertices == 0);
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
  test_pen_expressions();
  imprime_resultado();
  return 0;
}
