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
#include "window.h"

static struct _Wkeyboard keyboard;
static struct _Wmouse mouse;

#define ALMOST_EQUAL(a, b) (fabs((a) - (b)) < 0.001953)

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

void test_linar_algebra(void){
  double m[9] = {1, 2, 3, 2, 5, 2, 6, -3, 1};
  double x[3] = {0, 0, 0};
  double b[3] = {6, 4, 2};
  solve_linear_system(3, m, b, x);
  assert("Solving linear system", x[0] == 0.0 && x[1] == 0.0 && x[2] == 2.0);
}

void test_empty_programs(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  mf = init_metafont("tests/empty.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/empty.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  assert("Testing empty program", ret);
  free_token_list(first);
  lexer(mf,  "tests/empty_statements.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
  assert("Testing program with empty statements", ret);
}

void test_compound_statements(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  mf = init_metafont("tests/compound.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/compound.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  assert("Testing compound statements", ret);
  assert("Characters defined with 'beginchar' are stored",
	 mf -> first_glyph != NULL &&
	 mf -> first_glyph -> begin != NULL &&
	 mf -> first_glyph -> end != NULL);
  free_token_list(first);
  lexer(mf,  "tests/compound_wrong.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
  assert("Detecting wrong compound statements", !ret);
}

void test_variables(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  struct numeric_variable *n;
  struct pair_variable *p;
  struct named_variable *named;
  bool ret;
  mf = init_metafont("tests/variables.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/variables.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  ret = ret && (mf -> named_variables != NULL) &&
    (mf -> variables != NULL) &&
    (cx -> variables == NULL);
  if(!ret)
    _Wprint_metafont_error(mf);
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
  p = (struct pair_variable *) mf -> variables;
  assert("Testing pair expression", p -> type == TYPE_T_PAIR &&
         fabs(p -> x) < 0.00002 && fabs(p -> y - 3.0) < 0.00002);
  if(fabs(p -> x) >= 0.00002 && fabs(p -> y - 3.0) >= 0.00002){
    printf("ERROR: Exprected value: '(%f, %f)', Found value: '(%f,%f)'\n",
           0.0, 3.0, p -> x, p -> y);
  }
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_assignments(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  mf = init_metafont("tests/wrong_assignment.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/wrong_assignment.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  assert("Detecting wrong assignment", !ret);
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_lexer(void){
  struct generic_token *first, *last;
  void *p;
  bool ok = true;
  struct metafont *mf;
  struct context *cx;
  mf = init_metafont("tests/ridiculous.mf");
  lexer(mf, "tests/ridiculous.mf", &first, &last);
  cx = init_context(mf);
  p = first;
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
  ok = eval_program(mf, cx, first, last);
  assert("Wrong program not parsed", !ok);
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_path_expressions(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *p1, *p2, *p3, *p4, *p5, *p6, *p7, *p8, *p9,
    *quartercircle, *halfcircle, *fullcircle, *unitsquare, *a, *b, *c,
    *d, *e, *f, *g, *h, *i, *j, *k, *l, *n, *q, *r, *s, *m;
  struct path_variable *path_p1, *path_p2, *path_p3, *path_p4, *path_p5,
    *path_p6, *path_p7, *path_p8, *path_p9, *quartercircle_path,
    *halfcircle_path, *fullcircle_path, *unitsquare_path, *path_a,
    *path_b, *path_c, *path_d, *path_e, *path_f, *path_g, *path_h,
    *path_i, *path_j, *path_k, *path_l, *path_m;
  struct numeric_variable *numeric_n;
  struct pair_variable *pair_q, *pair_r, *pair_s;
  mf = init_metafont("tests/path_expressions.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/path_expressions.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
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
  m = s -> next;
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
  path_m = (struct path_variable *) m -> var;
  numeric_n = (struct numeric_variable *) n -> var;
  pair_q = (struct pair_variable *) q -> var;
  pair_r = (struct pair_variable *) r -> var;
  pair_s = (struct pair_variable *) s -> var;
  assert("Assigning pair literal to path",
	 path_p1 -> cyclic == false && path_p1 -> length == 1 &&
	 path_p1 -> number_of_points == 1 &&
	 path_p1 -> points[0].point.x == 1.0 &&
	 path_p1 -> points[0].point.y == 5.0 &&
	 path_p1 -> points[0].point.u_x == 1.0 &&
	 path_p1 -> points[0].point.u_y == 5.0 &&
	 path_p1 -> points[0].point.v_x == 1.0 &&
	 path_p1 -> points[0].point.v_y == 5.0);
  assert("Assigning between path variables",
	 path_p2 -> cyclic == false && path_p2 -> length == 1 &&
	 path_p2 -> number_of_points == 1 &&
	 path_p2 -> points[0].point.x == 1.0 && path_p2 -> points[0].point.y == 5.0 &&
	 path_p2 -> points[0].point.u_x == 1.0 && path_p2 -> points[0].point.u_y == 5.0 &&
	 path_p2 -> points[0].point.v_x == 1.0 && path_p2 -> points[0].point.v_y == 5.0);
  assert("Reversing single point",
	 path_p3 -> cyclic == false && path_p3 -> length == 1 &&
	 path_p3 -> number_of_points == 1 &&
	 path_p3 -> points[0].point.x == 1.0 &&
	 path_p3 -> points[0].point.y == 5.0 &&
	 path_p3 -> points[0].point.u_x == 1.0 &&
	 path_p3 -> points[0].point.u_y == 5.0 &&
	 path_p3 -> points[0].point.v_x == 1.0 &&
	 path_p3 -> points[0].point.v_y == 5.0);
  assert("Reversing bigger path",
	 path_h -> number_of_points == 5 &&	 
	 ALMOST_EQUAL(get_point(path_h, 0) -> point.x, -0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> point.u_x, -0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> point.u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> point.v_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 0) -> point.v_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> point.x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> point.u_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> point.u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> point.v_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 1) -> point.v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> point.y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> point.u_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> point.u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> point.v_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 2) -> point.v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> point.x, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> point.u_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> point.u_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> point.v_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 3) -> point.v_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> point.x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> point.u_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> point.v_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_h, 4) -> point.v_y, 0.0) &&
	 path_h -> cyclic == false);
  assert("Subpath of single point",
	 path_p4 != NULL &&
	 path_p4 -> cyclic == false &&
	 path_p4 -> length == 1 && path_p4 -> number_of_points == 1 &&
	 path_p4 -> points[0].point.x == 1.0 && path_p4 -> points[0].point.y == 5.0 &&
	 path_p4 -> points[0].point.u_x == 1.0 && path_p4 -> points[0].point.u_y == 5.0 &&
	 path_p4 -> points[0].point.v_x == 1.0 && path_p4 -> points[0].point.v_y == 5.0);
  assert("Dividing pair by numeric as path expression",
	 path_p5 -> cyclic == false && path_p5 -> length == 1 &&
	 path_p5 -> number_of_points == 1 &&
	 path_p5 -> points[0].point.x == 0.5 && path_p5 -> points[0].point.y == 2.5 &&
	 path_p5 -> points[0].point.u_x == 0.5 && path_p5 -> points[0].point.u_y == 2.5 &&
	 path_p5 -> points[0].point.v_x == 0.5 && path_p5 -> points[0].point.v_y == 2.5);
  assert("Multiplying numeric by pair as path expression",
	 path_p6 -> cyclic == false && path_p6 -> length == 1 &&
	 path_p6 -> number_of_points == 1 &&
	 path_p6 -> points[0].point.x == 2.0 && path_p6 -> points[0].point.y == 10.0 &&
	 path_p6 -> points[0].point.u_x == 2.0 && path_p6 -> points[0].point.u_y == 10.0 &&
	 path_p6 -> points[0].point.v_x == 2.0 && path_p6 -> points[0].point.v_y == 10.0);
  assert("Pair with transformer as path expression",
	 path_p7 -> cyclic == false && path_p7 -> length == 1 &&
	 path_p7 -> number_of_points == 1 &&
	 ALMOST_EQUAL(path_p7 -> points[0].point.x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].point.y, 1.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].point.u_x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].point.u_y, 1.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].point.v_x, 0.0) &&
	 ALMOST_EQUAL(path_p7 -> points[0].point.v_y, 1.0));
  assert("Tertiary pair expression as path expression",
	 path_p8 -> cyclic == false && path_p8 -> length == 1 &&
	 path_p8 -> number_of_points == 1 &&
	 path_p8 -> points[0].point.x == 1.0 && path_p8 -> points[0].point.y == 1.0 &&
	 path_p8 -> points[0].point.u_x == 1.0 && path_p8 -> points[0].point.u_y == 1.0 &&
	 path_p8 -> points[0].point.v_x == 1.0 && path_p8 -> points[0].point.v_y == 1.0);
  assert("Simple join with single control point between two path variables",
	 path_p9 -> cyclic == false && path_p9 -> length == 2 &&
	 path_p9 -> number_of_points == 2 &&
	 path_p9 -> points[0].point.x == 1.0 && path_p9 -> points[0].point.y == 5.0 &&
	 path_p9 -> points[0].point.u_x == 1.0 && path_p9 -> points[0].point.u_y == 3.0 &&
	 path_p9 -> points[0].point.v_x == 1.0 && path_p9 -> points[0].point.v_y == 3.0 &&
	 path_p9 -> points[1].point.x == 1.0 && path_p9 -> points[1].point.y == 1.0 &&
	 path_p9 -> points[1].point.u_x == 1.0 && path_p9 -> points[1].point.u_y == 1.0 &&
	 path_p9 -> points[1].point.v_x == 1.0 && path_p9 -> points[1].point.v_y == 1.0);
  assert("Simple join with double control points between two path variables",
	 quartercircle_path -> cyclic == false &&
	 quartercircle_path -> length == 3 &&
	 quartercircle_path -> number_of_points == 3 &&
	 quartercircle_path -> points[0].point.x == 0.5 &&
	 quartercircle_path -> points[0].point.y == 0.0 &&
	 quartercircle_path -> points[0].point.u_x == 0.5 &&
	 ALMOST_EQUAL(quartercircle_path -> points[0].point.u_y, 0.13261) &&
	 ALMOST_EQUAL(quartercircle_path -> points[0].point.v_x, 0.44733) &&
	 ALMOST_EQUAL(quartercircle_path -> points[0].point.v_y, 0.2598) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].point.x, 0.35356) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].point.y, 0.35356) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].point.u_x, 0.2598) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].point.u_y, 0.44733) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].point.v_x, 0.13261) &&
	 ALMOST_EQUAL(quartercircle_path -> points[1].point.v_y, 0.5) &&
	 quartercircle_path -> points[2].point.x == 0.0 &&
	 quartercircle_path -> points[2].point.y == 0.5 &&
	 quartercircle_path -> points[2].point.v_x == 0.0 &&
	 quartercircle_path -> points[2].point.v_y == 0.5 &&
	 quartercircle_path -> points[2].point.v_x == 0.0 &&
	 quartercircle_path -> points[2].point.v_y == 0.5);
  assert("Path concatenation and rotation",
	 halfcircle_path -> cyclic == false &&
	 halfcircle_path -> number_of_points == 5 &&
	 get_point(halfcircle_path, 0) -> point.x == 0.5 &&
	 get_point(halfcircle_path, 0) -> point.y == 0.0 &&
	 get_point(halfcircle_path, 0) -> point.u_x == 0.5 &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 0) -> point.u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 0) -> point.v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 0) -> point.v_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> point.x, 0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> point.u_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> point.u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> point.v_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 1) -> point.v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> point.y, 0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> point.u_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> point.u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> point.v_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 2) -> point.v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> point.x, -0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> point.u_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> point.u_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> point.v_x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> point.v_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> point.x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> point.u_x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> point.v_x, -0.5) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 4) -> point.v_y, 0.0));
  assert("Cyclic path concatenation and rotation",
	 fullcircle_path -> number_of_points == 9 &&
	 get_point(fullcircle_path, 0) -> point.x == 0.5 &&
	 get_point(fullcircle_path, 0) -> point.y == 0.0 &&
	 get_point(fullcircle_path, 0) -> point.u_x == 0.5 &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 0) -> point.u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 0) -> point.v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 0) -> point.v_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> point.x, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> point.u_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> point.u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> point.v_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 1) -> point.v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> point.y, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> point.u_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> point.u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> point.v_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 2) -> point.v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(halfcircle_path, 3) -> point.x, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> point.u_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> point.u_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> point.v_x, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 3) -> point.v_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> point.x, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> point.u_x, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> point.u_y, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> point.v_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 4) -> point.v_y, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> point.x, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> point.y, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> point.u_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> point.u_y, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> point.v_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 5) -> point.v_y, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> point.y, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> point.u_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> point.u_y, -0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> point.v_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 6) -> point.v_y, -0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> point.x, 0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> point.y, -0.35356) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> point.u_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> point.u_y, -0.2598) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> point.v_x, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 7) -> point.v_y, -0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> point.x, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> point.u_x, 0.5) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> point.u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> point.v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(fullcircle_path, 8) -> point.v_y, 0.2598) &&
	 fullcircle_path -> cyclic == true);
  assert("Path composed by straight lines",
	 unitsquare_path -> number_of_points == 5 &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> point.u_x, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> point.v_x, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 0) -> point.v_y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> point.x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> point.u_x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> point.u_y, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> point.v_x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 1) -> point.v_y, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> point.x, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> point.y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> point.u_x, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> point.u_y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> point.v_x, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 2) -> point.v_y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> point.y, 1.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> point.u_x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> point.u_y, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> point.v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 3) -> point.v_y, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> point.u_x, 0.33333) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> point.v_x, 0.66667) &&
	 ALMOST_EQUAL(get_point(unitsquare_path, 4) -> point.v_y, 0.0) &&
	 unitsquare_path -> cyclic == true);
  assert("Path composed by direction specifiers",
	 path_a -> number_of_points == 2 &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> point.u_x, 5.52284) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> point.v_x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 0) -> point.v_y, 4.47716) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> point.x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> point.y, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> point.u_x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> point.u_y, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> point.v_x, 10.0) &&
	 ALMOST_EQUAL(get_point(path_a, 1) -> point.v_y, 10.0) &&
	 path_a -> cyclic == false);
  assert("Cyclic path composed by minimal direction specifiers",
	 path_b -> number_of_points == 4 &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> point.u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 0) -> point.v_y, 0.89543) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> point.u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> point.u_y, 2.50372) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> point.v_x, 2.60619) &&
	 ALMOST_EQUAL(get_point(path_b, 1) -> point.v_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> point.x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> point.u_x, 17.31206) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> point.u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> point.v_x, -14.31206) &&
	 ALMOST_EQUAL(get_point(path_b, 2) -> point.v_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> point.u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_b, 3) -> point.v_y, 0.89543) &&
	 path_b -> cyclic == true);
  assert("Second cyclic path composed by minimal direction specifiers",
	 path_d -> number_of_points == 4 &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> point.u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 0) -> point.v_y, 0.89543) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> point.u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> point.u_y, 2.50372) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> point.v_x, 2.60619) &&
	 ALMOST_EQUAL(get_point(path_d, 1) -> point.v_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> point.x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> point.u_x, 17.31206) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> point.u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> point.v_x, -14.31206) &&
	 ALMOST_EQUAL(get_point(path_d, 2) -> point.v_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> point.u_x, 1.10457) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_d, 3) -> point.v_y, 0.89543) &&
	 path_d -> cyclic == true);
  assert("Path with direction derived from neighbor control point",
	 path_c -> number_of_points == 3 &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> point.u_x, -1.2818) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> point.u_y, -1.9227) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> point.v_x, 1.2532) &&
	 ALMOST_EQUAL(get_point(path_c, 0) -> point.v_y, 0.50641) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> point.u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> point.u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_c, 1) -> point.v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> point.u_x, -1.2818) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> point.u_y, -1.9227) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> point.v_x, 1.2532) &&
	 ALMOST_EQUAL(get_point(path_c, 2) -> point.v_y, 0.50641) &&
	 path_c -> cyclic == true);
  assert("Second path with directions derived from neighbor control points",
	 path_e -> number_of_points == 3 &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> point.u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> point.u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 0) -> point.v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> point.u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> point.u_y, 0.07417) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> point.v_x, -1.57869) &&
	 ALMOST_EQUAL(get_point(path_e, 1) -> point.v_y, -2.10492) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> point.u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> point.u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_e, 2) -> point.v_y, 3.0) &&
	 path_e -> cyclic == true);
  assert("Computing non-standard path tension",
	 path_f -> number_of_points == 2 &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> point.u_x, 1.47276) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> point.u_y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 0) -> point.v_y, 1.72386) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> point.u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> point.u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_f, 1) -> point.v_y, 2.0) &&
	 path_f -> cyclic == false);
  assert("Computing path tension with 'atleast' keyword",
	 path_g -> number_of_points == 2 &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> point.u_x, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> point.u_y, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> point.v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 0) -> point.v_y, 2.06097) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> point.y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> point.u_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> point.u_y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> point.v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_g, 1) -> point.v_y, 1.0) &&
	 path_g -> cyclic == false);
  assert("Creating subpath bigger than non-cyclic path",
	 path_i -> number_of_points == 2 &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> point.u_x, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> point.u_y, 0.42995) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> point.v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 0) -> point.v_y, 2.06097) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> point.y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> point.u_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> point.u_y, 1.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> point.v_x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_i, 1) -> point.v_y, 1.0) &&
	 path_i -> cyclic == false);
  assert("Creating subpath bigger than cyclic path",
	 path_j -> number_of_points == 5 &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> point.u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> point.u_y, 0.07417) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> point.v_x, -1.57869) &&
	 ALMOST_EQUAL(get_point(path_j, 0) -> point.v_y, -2.10492) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> point.u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> point.u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 1) -> point.v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> point.u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> point.u_y, 0.07417) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> point.v_x, -1.57869) &&
	 ALMOST_EQUAL(get_point(path_j, 2) -> point.v_y, -2.10492) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> point.u_x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> point.u_y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 3) -> point.v_y, 3.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> point.x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> point.y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> point.u_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> point.u_y, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> point.v_x, 2.0) &&
	 ALMOST_EQUAL(get_point(path_j, 4) -> point.v_y, 2.0) &&
	 path_j -> cyclic == false);
  assert("Creating subpath with reversed indices reverse the result",
	 path_k -> number_of_points == path_h -> number_of_points &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> point.x,
		      get_point(path_h, 0) -> point.x) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> point.y,
		      get_point(path_h, 0) -> point.y) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> point.u_x,
		      get_point(path_h, 0) -> point.u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> point.u_y,
		      get_point(path_h, 0) -> point.u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> point.v_x,
		      get_point(path_h, 0) -> point.v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 0) -> point.v_y,
		      get_point(path_h, 0) -> point.v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> point.x,
		      get_point(path_h, 1) -> point.x) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> point.y,
		      get_point(path_h, 1) -> point.y) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> point.u_x,
		      get_point(path_h, 1) -> point.u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> point.u_y,
		      get_point(path_h, 1) -> point.u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> point.v_x,
		      get_point(path_h, 1) -> point.v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 1) -> point.v_y,
		      get_point(path_h, 1) -> point.v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> point.x,
		      get_point(path_h, 2) -> point.x) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> point.y,
		      get_point(path_h, 2) -> point.y) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> point.u_x,
		      get_point(path_h, 2) -> point.u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> point.u_y,
		      get_point(path_h, 2) -> point.u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> point.v_x,
		      get_point(path_h, 2) -> point.v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 2) -> point.v_y,
		      get_point(path_h, 2) -> point.v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> point.x,
		      get_point(path_h, 3) -> point.x) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> point.y,
		      get_point(path_h, 3) -> point.y) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> point.u_x,
		      get_point(path_h, 3) -> point.u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> point.u_y,
		      get_point(path_h, 3) -> point.u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> point.v_x,
		      get_point(path_h, 3) -> point.v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 3) -> point.v_y,
		      get_point(path_h, 3) -> point.v_y) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> point.x,
		      get_point(path_h, 4) -> point.x) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> point.y,
		      get_point(path_h, 4) -> point.y) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> point.u_x,
		      get_point(path_h, 4) -> point.u_x) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> point.u_y,
		      get_point(path_h, 4) -> point.u_y) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> point.v_x,
		      get_point(path_h, 4) -> point.v_x) &&
	 ALMOST_EQUAL(get_point(path_k, 4) -> point.v_y,
		      get_point(path_h, 4) -> point.v_y) &&
	 path_k -> cyclic == false);
  assert("Creating subpath smaller than initial path",
	 path_l -> number_of_points == 3 &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> point.x, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> point.u_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> point.u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> point.v_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_l, 0) -> point.v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> point.y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> point.u_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> point.u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> point.v_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_l, 1) -> point.v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> point.x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> point.u_x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> point.u_y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> point.v_x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_l, 2) -> point.v_y, 0.35356) &&
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
  assert("Applying transforms over paths",
	 path_m -> number_of_points == 5 &&
	 ALMOST_EQUAL(get_point(path_m, 0) -> point.x, 3.0) &&
	 ALMOST_EQUAL(get_point(path_m, 0) -> point.y, 4.0) &&
	 ALMOST_EQUAL(get_point(path_m, 1) -> point.x, 8.0) &&
	 ALMOST_EQUAL(get_point(path_m, 1) -> point.y, 11.0) &&
	 ALMOST_EQUAL(get_point(path_m, 2) -> point.x, 14.0) &&
	 ALMOST_EQUAL(get_point(path_m, 2) -> point.y, 19.0) &&
	 ALMOST_EQUAL(get_point(path_m, 3) -> point.x, 9.0) &&
	 ALMOST_EQUAL(get_point(path_m, 3) -> point.y, 12.0) &&
	 path_m -> cyclic == true);
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_pen_expressions(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *p1, *p2, *p3, *p4, *penrazor, *p5, *p6, *p7, *p8, *p9,
    *p10, *p11, *p12, *p13, *p13_path, *p14, *p15, *p16, *p17, *p18, *p19;
  struct pen_variable *pen_p1, *pen_p2, *pen_p3, *pen_p4, *pen_penrazor,
    *pen_p5, *pen_p6, *pen_p7, *pen_p8, *pen_p13, *pen_p14, *pen_p15, *pen_p16,
    *pen_p17, *pen_p18, *pen_p19;
  struct path_variable *path_p9, *path_p10, *path_p11, *path_p12, *path_p13;
  mf = init_metafont("tests/pen_expressions.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/pen_expressions.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  p1 = (struct named_variable *) mf -> named_variables;
  p2 = p1 -> next;
  p3 = p2 -> next;
  p4 = p3 -> next;
  penrazor = p4 -> next;
  p5 = penrazor -> next;
  p6 = p5 -> next;
  p7 = p6 -> next;
  p8 = p7 -> next;
  p9 = p8 -> next;
  p10 = p9 -> next;
  p11 = p10 -> next;
  p12 = p11 -> next;
  p13 = p12 -> next;
  p13_path = p13 -> next;
  p14 = p13_path -> next;
  p15= p14 -> next;
  p16 = p15 -> next;
  p17 = p16 -> next;
  p18 = p17 -> next;
  p19 = p18 -> next;
  pen_p1 = (struct pen_variable *) p1 -> var;
  pen_p2 = (struct pen_variable *) p2 -> var;
  pen_p3 = (struct pen_variable *) p3 -> var;
  pen_p4 = (struct pen_variable *) p4 -> var;
  pen_penrazor = (struct pen_variable *) penrazor -> var;
  pen_p5 = (struct pen_variable *) p5 -> var;
  pen_p6 = (struct pen_variable *) p6 -> var;
  pen_p7 = (struct pen_variable *) p7 -> var;
  pen_p8 = (struct pen_variable *) p8 -> var;
  path_p9 = (struct path_variable *) p9 -> var;
  path_p10 = (struct path_variable *) p10 -> var;
  path_p11 = (struct path_variable *) p11 -> var;
  path_p12 = (struct path_variable *) p12 -> var;
  pen_p13 = (struct pen_variable *) p13 -> var;
  pen_p14 = (struct pen_variable *) p14 -> var;
  pen_p15 = (struct pen_variable *) p15 -> var;
  pen_p16 = (struct pen_variable *) p16 -> var;
  pen_p17 = (struct pen_variable *) p17 -> var;
  pen_p18 = (struct pen_variable *) p18 -> var;
  pen_p19 = (struct pen_variable *) p19 -> var;
  path_p13 = (struct path_variable *) p13_path -> var;
  assert("Interpreting program with pen expressions", ret);
  assert("Assigning pen variable",
	 pen_p1 -> format == NULL &&
	 pen_p1 -> flags == (FLAG_CONVEX | FLAG_SQUARE | FLAG_STRAIGHT) &&
	 pen_p1 -> referenced == NULL &&
	 pen_p1 -> gl_vbo == 0); // Not triangulated
  assert("Assigning nullpen",
	 pen_p2 -> format == NULL &&
	 pen_p2 -> flags == FLAG_NULL &&
	 pen_p2 -> referenced == NULL &&
	 pen_p2 -> gl_vbo == 0);
  assert("Assigning pencircle",
	 pen_p3 -> format == NULL &&
	 pen_p3 -> flags == (FLAG_CONVEX | FLAG_CIRCULAR) &&
	 pen_p3 -> referenced == NULL &&
	 pen_p3 -> gl_vbo == 0);
  assert("Pen expression with parenthesis",
	 pen_p4 -> format == NULL &&
	 pen_p4 -> flags == (FLAG_CONVEX | FLAG_CIRCULAR) &&
	 pen_p4 -> referenced == NULL &&
	 pen_p4 -> gl_vbo == 0 &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[0], 1.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[1], 0.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[2], 0.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[3], 0.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[4], 1.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[5], 0.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[6], 0.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[7], 0.0) &&
	 ALMOST_EQUAL(pen_p4 -> gl_matrix[8], 1.0));
  assert("Creating straight and convex pen",
	 pen_penrazor -> format != NULL &&
	 pen_penrazor -> format -> number_of_points == 3 &&
	 (pen_penrazor -> flags & FLAG_STRAIGHT) &&
	 (pen_penrazor -> flags & FLAG_CONVEX) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[0], 1.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[1], 0.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[2], 0.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[3], 0.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[4], 1.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[5], 0.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[6], 0.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[7], 0.0) &&
	 ALMOST_EQUAL(pen_penrazor -> gl_matrix[8], 1.0));
  assert("Creating straight and concave pen",
	 pen_p5 -> format != NULL &&
	 pen_p5 -> format -> number_of_points == 6 &&
	 (pen_p5 -> flags & FLAG_STRAIGHT) &&
	 !(pen_p5 -> flags & FLAG_CONVEX) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[0], 1.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[1], 0.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[2], 0.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[3], 0.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[4], 1.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[5], 0.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[6], 0.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[7], 0.0) &&
	 ALMOST_EQUAL(pen_p5 -> gl_matrix[8], 1.0));
  assert("Creating curved and convex pen",
	 pen_p6 -> format != NULL &&
	 pen_p6 -> format -> number_of_points == 4 &&
	 !(pen_p6 -> flags & FLAG_STRAIGHT) &&
	 (pen_p6 -> flags & FLAG_CONVEX) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[0], 1.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[1], 0.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[2], 0.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[3], 0.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[4], 1.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[5], 0.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[6], 0.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[7], 0.0) &&
	 ALMOST_EQUAL(pen_p6 -> gl_matrix[8], 1.0));
  assert("Creating curved and concave pen",
	 pen_p7 -> format != NULL &&
	 pen_p7 -> format -> number_of_points == 7 &&
	 !(pen_p7 -> flags & FLAG_STRAIGHT) &&
	 !(pen_p7 -> flags & FLAG_CONVEX) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[0], 1.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[1], 0.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[2], 0.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[3], 0.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[4], 1.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[5], 0.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[6], 0.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[7], 0.0) &&
	 ALMOST_EQUAL(pen_p7 -> gl_matrix[8], 1.0));
  // Código METAFONT para gerar os números abaixo:
  // path p;
  // p = (unitsquare shifted -(.5, .5)) shifted (1, 2);
  // message decimal xpart point 0 of p;
  // message decimal ypart point 0 of p;
  assert("Pen transformation (Shift)",
	 pen_p15 -> format == NULL &&
	 (pen_p15 -> flags & FLAG_STRAIGHT) &&
	 (pen_p15 -> flags & FLAG_CONVEX) &&
	 (pen_p15 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(0.5, -0.5 * pen_p15 -> gl_matrix[0] +
	 	      -0.5 * pen_p15 -> gl_matrix[3] +
	 	      1.0 * pen_p15 -> gl_matrix[6]) &&
	 ALMOST_EQUAL(1.5, -0.5 * pen_p15 -> gl_matrix[1] +
	 	      -0.5 * pen_p15 -> gl_matrix[4] +
	 	      1.0 * pen_p15 -> gl_matrix[7]));
  // Código METAFONT para gerar os números abaixo:
  // path p;
  // p = (unitsquare shifted -(.5, .5)) shifted (1, 2) scaled 0.5;
  // message decimal xpart point 0 of p;
  // message decimal ypart point 0 of p;
  assert("Pen transformation (Scale)",
	 pen_p16 -> format == NULL &&
	 (pen_p16 -> flags & FLAG_STRAIGHT) &&
	 (pen_p16 -> flags & FLAG_CONVEX) &&
	 (pen_p16 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(0.25, -0.5 * pen_p16 -> gl_matrix[0] +
	 	      -0.5 * pen_p16 -> gl_matrix[3] +
	 	      1.0 * pen_p16 -> gl_matrix[6]) &&
	 ALMOST_EQUAL(0.75, -0.5 * pen_p16 -> gl_matrix[1] +
	 	      -0.5 * pen_p16 -> gl_matrix[4] +
	 	      1.0 * pen_p16 -> gl_matrix[7]));
  // Código METAFONT para gerar os números abaixo:
  // path p;
  // p = (unitsquare shifted -(.5, .5)) shifted (1, 2) scaled 0.5 xscaled 3;
  // message decimal xpart point 0 of p;
  // message decimal ypart point 0 of p;
  assert("Pen transformation (X-Scale)",
	 pen_p17 -> format == NULL &&
	 (pen_p17 -> flags & FLAG_STRAIGHT) &&
	 (pen_p17 -> flags & FLAG_CONVEX) &&
	 (pen_p17 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(0.75, -0.5 * pen_p17 -> gl_matrix[0] +
	 	      -0.5 * pen_p17 -> gl_matrix[3] +
	 	      1.0 * pen_p17 -> gl_matrix[6]) &&
	 ALMOST_EQUAL(0.75, -0.5 * pen_p17 -> gl_matrix[1] +
	 	      -0.5 * pen_p17 -> gl_matrix[4] +
	 	      1.0 * pen_p17 -> gl_matrix[7]));
  // Código METAFONT para gerar os números abaixo:
  // path p;
  // p = (unitsquare shifted -(.5, .5)) shifted (1, 2) scaled 0.5 xscaled 3
  //     yscaled 4;
  // message decimal xpart point 0 of p;
  // message decimal ypart point 0 of p;
  assert("Pen transformation (Y-Scale)",
	 pen_p18 -> format == NULL &&
	 (pen_p18 -> flags & FLAG_STRAIGHT) &&
	 (pen_p18 -> flags & FLAG_CONVEX) &&
	 (pen_p18 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(0.75, -0.5 * pen_p18 -> gl_matrix[0] +
	 	      -0.5 * pen_p18 -> gl_matrix[3] +
	 	      1.0 * pen_p18 -> gl_matrix[6]) &&
	 ALMOST_EQUAL(3.0, -0.5 * pen_p18 -> gl_matrix[1] +
	 	      -0.5 * pen_p18 -> gl_matrix[4] +
	 	      1.0 * pen_p18 -> gl_matrix[7]));
  // Código METAFONT para gerar os números abaixo:
  // path p;
  // p = (unitsquare shifted -(.5, .5)) shifted (1, 2) scaled 0.5 xscaled 3
  //     yscaled 4 slanted 0.1;
  // message decimal xpart point 0 of p;
  // message decimal ypart point 0 of p;
  assert("Pen transformation (Slant)",
	 pen_p19 -> format == NULL &&
	 (pen_p19 -> flags & FLAG_STRAIGHT) &&
	 (pen_p19 -> flags & FLAG_CONVEX) &&
	 (pen_p19 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(1.05002, -0.5 * pen_p19 -> gl_matrix[0] +
	 	      -0.5 * pen_p19 -> gl_matrix[3] +
	 	      1.0 * pen_p19 -> gl_matrix[6]) &&
	 ALMOST_EQUAL(3.0, -0.5 * pen_p19 -> gl_matrix[1] +
	 	      -0.5 * pen_p19 -> gl_matrix[4] +
	 	      1.0 * pen_p19 -> gl_matrix[7]));
  assert("Pen transformation (Rotate)",
	 pen_p13 -> format == NULL &&
	 (pen_p8 -> flags & FLAG_STRAIGHT) &&
	 (pen_p8 -> flags & FLAG_CONVEX) &&
	 (pen_p8 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(path_p13 ->points[0].point.x, (1.0-sqrt(3.0))/4.0) &&
	 ALMOST_EQUAL(path_p13 ->points[0].point.y, (-1.0-sqrt(3.0))/4.0) &&
	 ALMOST_EQUAL(path_p13 ->points[1].point.x, (sqrt(3.0)+1.0)/4.0) &&
	 ALMOST_EQUAL(path_p13 ->points[1].point.y, (1.0-sqrt(3.0))/4.0) &&
	 ALMOST_EQUAL(path_p13 ->points[2].point.x, (sqrt(3.0)-1.0)/4.0) &&
	 ALMOST_EQUAL(path_p13 ->points[2].point.y, (1.0+sqrt(3.0))/4.0) &&
	 ALMOST_EQUAL(path_p13 ->points[3].point.x, (-sqrt(3.0)-1.0)/4.0) &&
	 ALMOST_EQUAL(path_p13 ->points[3].point.y, (-1.0+sqrt(3.0))/4.0));
  assert("Pen transformation (Z-Scale)",
	 pen_p8 -> format == NULL &&
	 (pen_p8 -> flags & FLAG_STRAIGHT) &&
	 (pen_p8 -> flags & FLAG_CONVEX) &&
	 (pen_p8 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(-8.78473, 0.5 * pen_p8 -> gl_matrix[0] +
	 	      -0.5 * pen_p8 -> gl_matrix[3] +
	 	      1.0 * pen_p8 -> gl_matrix[6]) &&
	 ALMOST_EQUAL(0.58345, 0.5 * pen_p8 -> gl_matrix[1] +
	 	      -0.5 * pen_p8 -> gl_matrix[4] +
	 	      1.0 * pen_p8 -> gl_matrix[7]));
  assert("Extracting path from 'nullpen'",
	 path_p9 -> length == 1 &&
	 path_p9 -> number_of_points == 1 &&
	 path_p9 -> points[0].point.x == 0.0 &&
	 path_p9 -> points[0].point.y == 0.0 &&
	 path_p9 -> points[0].point.u_x == 0.0 &&
	 path_p9 -> points[0].point.u_y == 0.0 &&
	 path_p9 -> points[0].point.v_x == 0.0 &&
	 path_p9 -> points[0].point.v_y == 0.0 &&
	 path_p9 -> cyclic == false);
  assert("Extracting path from 'pencircle'",
	 path_p10 -> number_of_points == 9 &&
	 ALMOST_EQUAL(get_point(path_p10, 0) -> point.x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 0) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_p10, 0) -> point.u_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 0) -> point.u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 0) -> point.v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 0) -> point.v_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 1) -> point.x, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 1) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 1) -> point.u_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 1) -> point.u_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 1) -> point.v_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 1) -> point.v_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 2) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_p10, 2) -> point.y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 2) -> point.u_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 2) -> point.u_y, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 2) -> point.v_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 2) -> point.v_y, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 3) -> point.x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 3) -> point.y, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 3) -> point.u_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 3) -> point.u_y, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 3) -> point.v_x, -0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 3) -> point.v_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 4) -> point.x, -0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 4) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_p10, 4) -> point.u_x, -0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 4) -> point.u_y, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 4) -> point.v_x, -0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 4) -> point.v_y, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 5) -> point.x, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 5) -> point.y, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 5) -> point.u_x, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 5) -> point.u_y, -0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 5) -> point.v_x, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 5) -> point.v_y, -0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 6) -> point.x, 0.0) &&
	 ALMOST_EQUAL(get_point(path_p10, 6) -> point.y, -0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 6) -> point.u_x, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 6) -> point.u_y, -0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 6) -> point.v_x, 0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 6) -> point.v_y, -0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 7) -> point.x, 0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 7) -> point.y, -0.35356) &&
	 ALMOST_EQUAL(get_point(path_p10, 7) -> point.u_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 7) -> point.u_y, -0.2598) &&
	 ALMOST_EQUAL(get_point(path_p10, 7) -> point.v_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 7) -> point.v_y, -0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 8) -> point.x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 8) -> point.y, 0.0) &&
	 ALMOST_EQUAL(get_point(path_p10, 8) -> point.u_x, 0.5) &&
	 ALMOST_EQUAL(get_point(path_p10, 8) -> point.u_y, 0.13261) &&
	 ALMOST_EQUAL(get_point(path_p10, 8) -> point.v_x, 0.44733) &&
	 ALMOST_EQUAL(get_point(path_p10, 8) -> point.v_y, 0.2598) &&
	 path_p10 -> cyclic == true);
  assert("Extracting path from 'pensquare'",
	 path_p11 -> number_of_points == 5 &&
	 ALMOST_EQUAL(path_p11 ->points[0].point.x, -6.78659) &&
	 ALMOST_EQUAL(path_p11 ->points[0].point.y, -2.11049) &&
	 ALMOST_EQUAL(path_p11 ->points[1].point.x, -8.78473) &&
	 ALMOST_EQUAL(path_p11 ->points[1].point.y, 0.58345) &&
	 ALMOST_EQUAL(path_p11 ->points[2].point.x, -12.64308) &&
	 ALMOST_EQUAL(path_p11 ->points[2].point.y, -1.72151) &&
	 ALMOST_EQUAL(path_p11 ->points[3].point.x, -10.64494) &&
	 ALMOST_EQUAL(path_p11 ->points[3].point.y, -4.41545) &&
	 path_p11 -> cyclic == true);
  assert("Extracting path from custom pen",
	 path_p12 -> number_of_points == 4 &&
	 ALMOST_EQUAL(path_p12 ->points[0].point.x, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[0].point.y, 0.0) &&
	 ALMOST_EQUAL(path_p12 ->points[0].point.u_x, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[0].point.u_y, 0.13261) &&
	 ALMOST_EQUAL(path_p12 ->points[0].point.v_x, 0.44733) &&
	 ALMOST_EQUAL(path_p12 ->points[0].point.v_y, 0.2598) &&
	 ALMOST_EQUAL(path_p12 ->points[1].point.x, 0.35356) &&
	 ALMOST_EQUAL(path_p12 ->points[1].point.y, 0.35356) &&
	 ALMOST_EQUAL(path_p12 ->points[1].point.u_x, 0.2598) &&
	 ALMOST_EQUAL(path_p12 ->points[1].point.u_y, 0.44733) &&
	 ALMOST_EQUAL(path_p12 ->points[1].point.v_x, 0.13261) &&
	 ALMOST_EQUAL(path_p12 ->points[1].point.v_y, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[2].point.x, 0.0) &&
	 ALMOST_EQUAL(path_p12 ->points[2].point.y, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[2].point.u_x, -1.60944) &&
	 ALMOST_EQUAL(path_p12 ->points[2].point.u_y, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[2].point.v_x, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[2].point.v_y, -1.60944) &&
	 ALMOST_EQUAL(path_p12 ->points[3].point.x, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[3].point.y, 0.0) &&
	 ALMOST_EQUAL(path_p12 ->points[3].point.u_x, 0.5) &&
	 ALMOST_EQUAL(path_p12 ->points[3].point.u_y, 0.13261) &&
	 ALMOST_EQUAL(path_p12 ->points[3].point.v_x, 0.44733) &&
	 ALMOST_EQUAL(path_p12 ->points[3].point.v_y, 0.2598) &&
	 path_p12 -> cyclic == true);
  assert("Using transfoms with pens",
	 pen_p14 -> format == NULL &&
	 (pen_p14 -> flags & FLAG_STRAIGHT) &&
	 (pen_p14 -> flags & FLAG_CONVEX) &&
	 (pen_p14 -> flags & FLAG_SQUARE) &&
	 ALMOST_EQUAL(2.5, 0.5 * pen_p14 -> gl_matrix[0] +
	 	      -0.5 * pen_p14 -> gl_matrix[3] +
	 	      1.0 * pen_p14 -> gl_matrix[6]) &&
	 ALMOST_EQUAL(3.5, 0.5 * pen_p14 -> gl_matrix[1] +
	 	      -0.5 * pen_p14 -> gl_matrix[4] +
	 	      1.0 * pen_p14 -> gl_matrix[7]));
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_numeric_expressions(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *a, *b, *c, *d, *e, *f, *g, *h;
  struct numeric_variable *numeric_a, *numeric_b, *numeric_c,
    *numeric_d, *numeric_e, *numeric_f, *numeric_g, *numeric_h;
  mf = init_metafont("tests/numeric_expressions.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/numeric_expressions.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  a = (struct named_variable *) mf -> named_variables;
  b = a -> next;
  c = b -> next;
  d = c -> next;
  e = d -> next;
  f = e -> next;
  g = f -> next;
  h = g -> next;
  numeric_a = (struct numeric_variable *) a -> var;
  numeric_b = (struct numeric_variable *) b -> var;
  numeric_c = (struct numeric_variable *) c -> var;
  numeric_d = (struct numeric_variable *) d -> var;
  numeric_e = (struct numeric_variable *) e -> var;
  numeric_f = (struct numeric_variable *) f -> var;
  numeric_g = (struct numeric_variable *) g -> var;
  numeric_h = (struct numeric_variable *) h -> var;
  assert("Interpreting program with numeric expressions", ret);
  assert("Evaluating transform values as numeric data",
	 ALMOST_EQUAL(numeric_a -> value, 1.0) &&
	 ALMOST_EQUAL(numeric_b -> value, 2.0) &&
	 ALMOST_EQUAL(numeric_c -> value, 3.0) &&
	 ALMOST_EQUAL(numeric_d -> value, 4.0) &&
	 ALMOST_EQUAL(numeric_e -> value, 5.0) &&
	 ALMOST_EQUAL(numeric_f -> value, 6.0));
  assert("Evaluating numeric width and height for pictures",
	 ALMOST_EQUAL(numeric_g -> value, 5.0) &&
	 ALMOST_EQUAL(numeric_h -> value, 6.0));
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_pair_expressions(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *a, *b;
  struct pair_variable *pair_a, *pair_b;
  mf = init_metafont("tests/pair_expressions.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/pair_expressions.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  a = (struct named_variable *) mf -> named_variables;
  b = a -> next;
  pair_a = (struct pair_variable *) a -> var;
  pair_b = (struct pair_variable *) b -> var;
  assert("Interpreting program with pair expressions", ret);
  assert("Evaluating transform over pairs",
	 ALMOST_EQUAL(pair_a -> x, 20.0) &&
	 ALMOST_EQUAL(pair_a -> y, 27.0));
  assert("Interpolating between two points",
	 ALMOST_EQUAL(pair_b -> x, 227.9591) &&
	 ALMOST_EQUAL(pair_b -> y, 74.94846));
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_transform_expressions(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
  struct transform_variable *transform_a, *transform_b, *transform_c,
    *transform_d, *transform_e, *transform_f, *transform_g, *transform_h,
    *transform_i, *transform_j;
  mf = init_metafont("tests/transform_expressions.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/transform_expressions.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  a = (struct named_variable *) mf -> named_variables;
  b = a -> next;
  c = b -> next;
  d = c -> next;
  e = d -> next;
  f = e -> next;
  g = f -> next;
  h = g -> next;
  i = h -> next;
  j = i -> next;
  transform_a = (struct transform_variable *) a -> var;
  transform_b = (struct transform_variable *) b -> var;
  transform_c = (struct transform_variable *) c -> var;
  transform_d = (struct transform_variable *) d -> var;
  transform_e = (struct transform_variable *) e -> var;
  transform_f = (struct transform_variable *) f -> var;
  transform_g = (struct transform_variable *) g -> var;
  transform_h = (struct transform_variable *) h -> var;
  transform_i = (struct transform_variable *) i -> var;
  transform_j = (struct transform_variable *) j -> var;
  assert("Interpreting program with transform expressions", ret);
  assert("Evaluating transform literal",
	 ALMOST_EQUAL(transform_a -> value[6], -1.0) &&
	 ALMOST_EQUAL(transform_a -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_a -> value[0], 0.2) &&
	 ALMOST_EQUAL(transform_a -> value[3], 0.4) &&
	 ALMOST_EQUAL(transform_a -> value[1], -0.4) &&
	 ALMOST_EQUAL(transform_a -> value[4], 0.2));
  assert("Evaluating identity variable as transform",
	 ALMOST_EQUAL(transform_b -> value[6], 0.0) &&
	 ALMOST_EQUAL(transform_b -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_b -> value[0], 1.0) &&
	 ALMOST_EQUAL(transform_b -> value[3], 0.0) &&
	 ALMOST_EQUAL(transform_b -> value[1], 0.0) &&
	 ALMOST_EQUAL(transform_b -> value[4], 1.0));
  assert("Evaluating rotation in transform expressions",
	 ALMOST_EQUAL(transform_c -> value[6], 0.0) &&
	 ALMOST_EQUAL(transform_c -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_c -> value[0], 0.86603) &&
	 ALMOST_EQUAL(transform_c -> value[3], -0.5) &&
	 ALMOST_EQUAL(transform_c -> value[1], 0.5) &&
	 ALMOST_EQUAL(transform_c -> value[4], 0.86603));
  assert("Evaluating shifting in transform expressions",
	 ALMOST_EQUAL(transform_d -> value[6], 5.0) &&
	 ALMOST_EQUAL(transform_d -> value[7], 8.0) &&
	 ALMOST_EQUAL(transform_d -> value[0], 1.0) &&
	 ALMOST_EQUAL(transform_d -> value[3], 0.0) &&
	 ALMOST_EQUAL(transform_d -> value[1], 0.0) &&
	 ALMOST_EQUAL(transform_d -> value[4], 1.0));
  assert("Evaluating scaling in transform expressions",
	 ALMOST_EQUAL(transform_e -> value[6], 0.0) &&
	 ALMOST_EQUAL(transform_e -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_e -> value[0], 5.0) &&
	 ALMOST_EQUAL(transform_e -> value[3], 0.0) &&
	 ALMOST_EQUAL(transform_e -> value[1], 0.0) &&
	 ALMOST_EQUAL(transform_e -> value[4], 5.0));
  assert("Evaluating slanting in transform expressions",
	 ALMOST_EQUAL(transform_f -> value[6], 0.0) &&
	 ALMOST_EQUAL(transform_f -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_f -> value[0], 1.0) &&
	 ALMOST_EQUAL(transform_f -> value[3], 5.0) &&
	 ALMOST_EQUAL(transform_f -> value[1], 0.0) &&
	 ALMOST_EQUAL(transform_f -> value[4], 1.0));
  assert("Evaluating x-scaling in transform expressions",
	 ALMOST_EQUAL(transform_g -> value[6], 0.0) &&
	 ALMOST_EQUAL(transform_g -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_g -> value[0], 10.0) &&
	 ALMOST_EQUAL(transform_g -> value[3], 0.0) &&
	 ALMOST_EQUAL(transform_g -> value[1], 0.0) &&
	 ALMOST_EQUAL(transform_g -> value[4], 1.0));
  assert("Evaluating y-scaling in transform expressions",
	 ALMOST_EQUAL(transform_h -> value[6], 0.0) &&
	 ALMOST_EQUAL(transform_h -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_h -> value[0], 1.0) &&
	 ALMOST_EQUAL(transform_h -> value[3], 0.0) &&
	 ALMOST_EQUAL(transform_h -> value[1], 0.0) &&
	 ALMOST_EQUAL(transform_h -> value[4], 3.0));
  assert("Evaluating z-scaling in transform expressions",
	 ALMOST_EQUAL(transform_i -> value[6], 0.0) &&
	 ALMOST_EQUAL(transform_i -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_i -> value[0], 8.0) &&
	 ALMOST_EQUAL(transform_i -> value[3], -2.0) &&
	 ALMOST_EQUAL(transform_i -> value[1], 2.0) &&
	 ALMOST_EQUAL(transform_i -> value[4], 8.0));
  assert("Evaluating generic transformation in transform expressions",
	 ALMOST_EQUAL(transform_j -> value[6], -1.0) &&
	 ALMOST_EQUAL(transform_j -> value[7], 0.0) &&
	 ALMOST_EQUAL(transform_j -> value[0], 0.2) &&
	 ALMOST_EQUAL(transform_j -> value[3], 0.4) &&
	 ALMOST_EQUAL(transform_j -> value[1], -0.4) &&
	 ALMOST_EQUAL(transform_j -> value[4], 0.2));
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_picture_expressions(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *a, *wa, *b, *wb, *c, *wc, *d, *wd, *e, *we, *f, *wf,
    *g, *wg, *h, *wh, *i, *wi, *j, *wj, *k, *wk, *l, *wl, *m, *wm;
  struct picture_variable *picture_a, *picture_b, *picture_c, *picture_d,
    *picture_e, *picture_f, *picture_g, *picture_h, *picture_i, *picture_j,
    *picture_k, *picture_l, *picture_m;
  struct numeric_variable *numeric_wa, *numeric_wb, *numeric_wc, *numeric_wd,
    *numeric_we, *numeric_wf, *numeric_wg, *numeric_wh, *numeric_wi,
    *numeric_wj, *numeric_wk, *numeric_wl, *numeric_wm;
  mf = init_metafont("tests/picture_expressions.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/picture_expressions.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  a = (struct named_variable *) mf -> named_variables;
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
  m = l -> next;
  wa = m -> next;
  wb = wa -> next;
  wc = wb -> next;
  wd = wc -> next;
  we = wd -> next;
  wf = we -> next;
  wg = wf -> next;
  wh = wg -> next;
  wi = wh -> next;
  wj = wi -> next;
  wk = wj -> next;
  wl = wk -> next;
  wm = wl -> next;
  picture_a = (struct picture_variable *) a -> var;
  picture_b = (struct picture_variable *) b -> var;
  picture_c = (struct picture_variable *) c -> var;
  picture_d = (struct picture_variable *) d -> var;
  picture_e = (struct picture_variable *) e -> var;
  picture_f = (struct picture_variable *) f -> var;
  picture_g = (struct picture_variable *) g -> var;
  picture_h = (struct picture_variable *) h -> var;
  picture_i = (struct picture_variable *) i -> var;
  picture_j = (struct picture_variable *) j -> var;
  picture_k = (struct picture_variable *) k -> var;
  picture_l = (struct picture_variable *) l -> var;
  picture_m = (struct picture_variable *) m -> var;
  numeric_wa = (struct numeric_variable *) wa -> var;
  numeric_wb = (struct numeric_variable *) wb -> var;
  numeric_wc = (struct numeric_variable *) wc -> var;
  numeric_wd = (struct numeric_variable *) wd -> var;
  numeric_we = (struct numeric_variable *) we -> var;
  numeric_wf = (struct numeric_variable *) wf -> var;
  numeric_wg = (struct numeric_variable *) wg -> var;
  numeric_wh = (struct numeric_variable *) wh -> var;
  numeric_wi = (struct numeric_variable *) wi -> var;
  numeric_wj = (struct numeric_variable *) wj -> var;
  numeric_wk = (struct numeric_variable *) wk -> var;
  numeric_wl = (struct numeric_variable *) wl -> var;
  numeric_wm = (struct numeric_variable *) wm -> var;
  //printf("k: %dx%d: %f:\n", picture_m -> width, picture_m -> height,
  // 	 numeric_wm -> value);
  //print_picture(picture_m);
  assert("Interpreting program with picture expressions", ret);
  assert("Generating nullpicture with correct size and weight",
	 picture_a -> width == 10 && picture_a -> height == 10 &&
	 ALMOST_EQUAL(numeric_wa -> value, 0.0));
  assert("Computing the inverse of a picture",
  	 picture_b -> width == 10 && picture_b -> height == 10 &&
  	 ALMOST_EQUAL(numeric_wb -> value, 100.0));
  assert("Subtracting pictures",
  	 picture_c -> width == 10 && picture_c -> height == 10 &&
  	 numeric_wc -> value == 80.0);
  //printf("d: %dx%d: %f:\n", picture_d -> width, picture_d -> height,
  // 	 numeric_wd -> value);
  //print_picture(picture_d);
  assert("Adding pictures",
  	 picture_d -> width == 10 && picture_d -> height == 10 &&
  	 numeric_wd -> value == 84.0);
  assert("Rotating pictures",
  	 picture_e -> width == 10 && picture_e -> height == 10 &&
  	 numeric_we -> value == 80.0);
  assert("Scaling pictures",
   	 picture_f -> width == 10 && picture_f -> height == 10 &&
  	 ALMOST_EQUAL(numeric_wf -> value, 72.480431));
  assert("X-Scaling pictures",
   	 picture_g -> width == 10 && picture_g -> height == 5 &&
  	 ALMOST_EQUAL(numeric_wg -> value, 72.480431/2.0));
  assert("Y-Scaling pictures",
   	 picture_h -> width == 5 && picture_h -> height == 10 &&
  	 ALMOST_EQUAL(numeric_wh -> value, 40.0));
  assert("Shifting pictures",
   	 picture_i -> width == 5 && picture_i -> height == 3 &&
  	 ALMOST_EQUAL(numeric_wi -> value, 1.0));
  assert("Slanting pictures",
   	 picture_j -> width == 6 && picture_j -> height == 3 &&
  	 ALMOST_EQUAL(numeric_wj -> value, 9.0));
  assert("Z-scaling pictures",
   	 picture_k -> width == 7 && picture_k -> height == 7 &&
  	 ALMOST_EQUAL(numeric_wk -> value, 25.0));
  assert("Generic transform over pictures",
   	 picture_l -> width == 7 && picture_l -> height == 7 &&
  	 ALMOST_EQUAL(numeric_wl -> value, 25.0));
  assert("Interpreting subpictures",
   	 picture_m -> width == 3 && picture_m -> height == 1 &&
  	 ALMOST_EQUAL(numeric_wm -> value, 1.0));
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_boolean_expressions(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *a0, *b0, *c0, *d0, *e0, *f0, *a1, *b1, *c1, *d1, *e1,
    *f1, *a2, *b2, *c2, *d2, *e2, *f2, *a3, *b3, *c3, *d3, *e3, *f3, *a4, *b4,
    *c4, *d4, *a5, *b5, *c5, *d5, *a6, *b6, *c6, *d6, *e6, *f6;
  struct boolean_variable *boolean_a0, *boolean_b0, *boolean_c0, *boolean_d0,
    *boolean_e0, *boolean_f0, *boolean_a1, *boolean_b1, *boolean_c1,
    *boolean_d1, *boolean_e1, *boolean_f1, *boolean_a2, *boolean_b2,
    *boolean_c2, *boolean_d2, *boolean_e2, *boolean_f2, *boolean_a3,
    *boolean_b3, *boolean_c3, *boolean_d3, *boolean_e3, *boolean_f3,
    *boolean_a4, *boolean_b4, *boolean_c4, *boolean_d4,
    *boolean_a5, *boolean_b5, *boolean_c5, *boolean_d5,
    *boolean_a6, *boolean_b6, *boolean_c6, *boolean_d6, *boolean_e6,
    *boolean_f6;
  mf = init_metafont("tests/boolean_expressions.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/boolean_expressions.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  a0 = (struct named_variable *) mf -> named_variables;
  b0 = a0 -> next; c0 = b0 -> next; d0 = c0 -> next; e0 = d0 -> next;
  f0 = e0 -> next; a1 = f0 -> next; b1 = a1 -> next; c1 = b1 -> next;
  d1 = c1 -> next; e1 = d1 -> next; f1 = e1 -> next; a2 = f1 -> next;
  b2 = a2 -> next; c2 = b2 -> next; d2 = c2 -> next; e2 = d2 -> next;
  f2 = e2 -> next; a3 = f2 -> next; b3 = a3 -> next; c3 = b3 -> next;
  d3 = c3 -> next; e3 = d3 -> next; f3 = e3 -> next; a4 = f3 -> next;
  b4 = a4 -> next; c4 = b4 -> next; d4 = c4 -> next; a5 = d4 -> next;
  b5 = a5 -> next; c5 = b5 -> next; d5 = c5 -> next; a6 = d5 -> next;
  b6 = a6 -> next; c6 = b6 -> next; d6 = c6 -> next; e6 = d6 -> next;
  f6 = e6 -> next;
  boolean_a0 = (struct boolean_variable *) a0 -> var;
  boolean_b0 = (struct boolean_variable *) b0 -> var;
  boolean_c0 = (struct boolean_variable *) c0 -> var;
  boolean_d0 = (struct boolean_variable *) d0 -> var;
  boolean_e0 = (struct boolean_variable *) e0 -> var;
  boolean_f0 = (struct boolean_variable *) f0 -> var;
  boolean_a1 = (struct boolean_variable *) a1 -> var;
  boolean_b1 = (struct boolean_variable *) b1 -> var;
  boolean_c1 = (struct boolean_variable *) c1 -> var;
  boolean_d1 = (struct boolean_variable *) d1 -> var;
  boolean_e1 = (struct boolean_variable *) e1 -> var;
  boolean_f1 = (struct boolean_variable *) f1 -> var;
  boolean_a2 = (struct boolean_variable *) a2 -> var;
  boolean_b2 = (struct boolean_variable *) b2 -> var;
  boolean_c2 = (struct boolean_variable *) c2 -> var;
  boolean_d2 = (struct boolean_variable *) d2 -> var;
  boolean_e2 = (struct boolean_variable *) e2 -> var;
  boolean_f2 = (struct boolean_variable *) f2 -> var;
  boolean_a3 = (struct boolean_variable *) a3 -> var;
  boolean_b3 = (struct boolean_variable *) b3 -> var;
  boolean_c3 = (struct boolean_variable *) c3 -> var;
  boolean_d3 = (struct boolean_variable *) d3 -> var;
  boolean_e3 = (struct boolean_variable *) e3 -> var;
  boolean_f3 = (struct boolean_variable *) f3 -> var;
  boolean_a4 = (struct boolean_variable *) a4 -> var;
  boolean_b4 = (struct boolean_variable *) b4 -> var;
  boolean_c4 = (struct boolean_variable *) c4 -> var;
  boolean_d4 = (struct boolean_variable *) d4 -> var;
  boolean_a5 = (struct boolean_variable *) a5 -> var;
  boolean_b5 = (struct boolean_variable *) b5 -> var;
  boolean_c5 = (struct boolean_variable *) c5 -> var;
  boolean_d5 = (struct boolean_variable *) d5 -> var;
  boolean_a6 = (struct boolean_variable *) a6 -> var;
  boolean_b6 = (struct boolean_variable *) b6 -> var;
  boolean_c6 = (struct boolean_variable *) c6 -> var;
  boolean_d6 = (struct boolean_variable *) d6 -> var;
  boolean_e6 = (struct boolean_variable *) e6 -> var;
  boolean_f6 = (struct boolean_variable *) f6 -> var;
  assert("Interpreting program with boolean expressions", ret);
  assert("Boolean comparisons between numerics",
	 boolean_a0 -> value && !(boolean_b0 -> value) && boolean_c0 -> value &&
	 !(boolean_d0 -> value) && boolean_e0 -> value && !(boolean_f0 -> value));
  assert("Boolean comparisons between pairs",
	 !(boolean_a1 -> value) && (boolean_b1 -> value) && !(boolean_c1 -> value) &&
	 (boolean_d1 -> value) && !(boolean_e1 -> value) && (boolean_f1 -> value));
  assert("Boolean comparisons between transforms",
	 boolean_a2 -> value && !(boolean_b2 -> value) && boolean_c2 -> value &&
	 !(boolean_d2 -> value) && boolean_e2 -> value && !(boolean_f2 -> value));
  assert("Boolean comparisons between booleans",
	 !(boolean_a3 -> value) && (boolean_b3 -> value) && (boolean_c3 -> value) &&
	 !(boolean_d3 -> value) && (boolean_e3 -> value) && (boolean_f3 -> value));
  assert("Testing Boolean OR",
	 !(boolean_a4 -> value) && (boolean_b4 -> value) && (boolean_c4 -> value) &&
	 (boolean_d4 -> value));
  assert("Testing Boolean AND",
	 !(boolean_a5 -> value) && !(boolean_b5 -> value) &&
	 !(boolean_c5 -> value) && (boolean_d5 -> value));
  assert("Testing De Morgan's Law", boolean_a6);
  assert("Testing Boolean Variable evaluation", boolean_b6);
  assert("Testing 'odd' operator", (!boolean_c6 -> value) && boolean_d6 -> value);
  assert("Testing 'cycle' operator", boolean_e6 -> value && !(boolean_f6 -> value));
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_if_statements(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *a, *b, *c;
  struct numeric_variable *numeric_a, *numeric_b, *numeric_c;
  mf = init_metafont("tests/if_statement.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/if_statement.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  a = (struct named_variable *) mf -> named_variables;
  b = a -> next;
  c = b -> next;
  numeric_a = (struct numeric_variable *) a -> var;
  numeric_b = (struct numeric_variable *) b -> var;
  numeric_c = (struct numeric_variable *) c -> var;
  assert("Interpreting program with 'if' statements", ret);
  assert("Interpreting 'if', 'elseif' and 'else'",
	 numeric_a -> value == 2 && numeric_b -> value == 11 &&
	 numeric_c -> value == 17);
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_drawing_commands(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  struct named_variable *a, *wa, *b, *wb, *c, *wc, *d, *wd, *e, *we, *f, *wf,
    *g, *wg, *pa1, *pa2, *pb1, *pb2, *pd1, *pd2, *pe1, *pe2, *pf1, *pf2, *pg1,
    *pg2, *ph1, *ph2;
  struct picture_variable *picture_a, *picture_b, *picture_c, *picture_d,
    *picture_e, *picture_f, *picture_g;
  struct numeric_variable *numeric_wa, *numeric_wb, *numeric_wc, *numeric_wd,
    *numeric_we, *numeric_wf, *numeric_wg;
  struct pair_variable *pair_pa1, *pair_pa2, *pair_pb1, *pair_pb2, *pair_pd1,
    *pair_pd2, *pair_pe1, *pair_pe2, *pair_pf1, *pair_pf2, *pair_pg1, *pair_pg2,
    *pair_ph1, *pair_ph2;
  mf = init_metafont("tests/drawing_commands.mf");
  cx = init_context(mf);
  lexer(mf,  "tests/drawing_commands.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  a = (struct named_variable *) mf -> named_variables;
  b = (struct named_variable *) (a -> next);
  c = (struct named_variable *) (b -> next);
  d = (struct named_variable *) (c -> next);
  e = (struct named_variable *) (d -> next);
  f = (struct named_variable *) (e -> next);
  g = (struct named_variable *) (f -> next);
  wa = (struct named_variable *) (g -> next);
  wb = (struct named_variable *) (wa -> next);
  wc = (struct named_variable *) (wb -> next);
  wd = (struct named_variable *) (wc -> next);
  we = (struct named_variable *) (wd -> next);
  wf = (struct named_variable *) (we -> next);
  wg = (struct named_variable *) (wf -> next);
  pa1 = (struct named_variable *) (wg -> next);
  pa2 = (struct named_variable *) (pa1 -> next);
  pb1 = (struct named_variable *) (pa2 -> next);
  pb2 = (struct named_variable *) (pb1 -> next);
  pd1 = (struct named_variable *) (pb2 -> next);
  pd2 = (struct named_variable *) (pd1 -> next);
  pe1 = (struct named_variable *) (pd2 -> next);
  pe2 = (struct named_variable *) (pe1 -> next);
  pf1 = (struct named_variable *) (pe2 -> next);
  pf2 = (struct named_variable *) (pf1 -> next);
  pg1 = (struct named_variable *) (pf2 -> next);
  pg2 = (struct named_variable *) (pg1 -> next);
  ph1 = (struct named_variable *) (pg2 -> next);
  ph2 = (struct named_variable *) (ph1 -> next);
  picture_a = (struct picture_variable *) a -> var;
  picture_b = (struct picture_variable *) b -> var;
  picture_c = (struct picture_variable *) c -> var;
  picture_d = (struct picture_variable *) d -> var;
  picture_e = (struct picture_variable *) e -> var;
  picture_f = (struct picture_variable *) f -> var;
  picture_g = (struct picture_variable *) g -> var;
  numeric_wa = (struct numeric_variable *) wa -> var;
  numeric_wb = (struct numeric_variable *) wb -> var;
  numeric_wc = (struct numeric_variable *) wc -> var;
  numeric_wd = (struct numeric_variable *) wd -> var;
  numeric_we = (struct numeric_variable *) we -> var;
  numeric_wf = (struct numeric_variable *) wf -> var;
  numeric_wg = (struct numeric_variable *) wg -> var;
  pair_pa1 = (struct pair_variable *) pa1 -> var;
  pair_pa2 = (struct pair_variable *) pa2 -> var;
  pair_pb1 = (struct pair_variable *) pb1 -> var;
  pair_pb2 = (struct pair_variable *) pb2 -> var;
  pair_pd1 = (struct pair_variable *) pd1 -> var;
  pair_pd2 = (struct pair_variable *) pd2 -> var;
  pair_pe1 = (struct pair_variable *) pe1 -> var;
  pair_pe2 = (struct pair_variable *) pe2 -> var;
  pair_pf1 = (struct pair_variable *) pf1 -> var;
  pair_pf2 = (struct pair_variable *) pf2 -> var;
  pair_pg1 = (struct pair_variable *) pg1 -> var;
  pair_pg2 = (struct pair_variable *) pg2 -> var;
  pair_ph1 = (struct pair_variable *) ph1 -> var;
  pair_ph2 = (struct pair_variable *) ph2 -> var;
  assert("Interpreting program with drawing commands", ret);
  assert("Drawing a simple square",
	 picture_a -> width == 6 && picture_a -> height == 6 &&
  	 ALMOST_EQUAL(numeric_wa -> value, 12.0) &&
	 // You can test the reference values with METAFONT code:
	 // pickup pensquare shifted (0.5, 0.5);
	 // message decimal xpart top lft (0, 0);
	 // message decimal ypart top lft (0, 0);
	 // message decimal xpart bot rt (0, 0);
	 // message decimal ypart bot rt (0, 0);
	 ALMOST_EQUAL(pair_pa1 -> x, 0.0) &&
	 ALMOST_EQUAL(pair_pa1 -> y, 1.0) &&
	 ALMOST_EQUAL(pair_pa2 -> x, 1.0) &&
	 ALMOST_EQUAL(pair_pa2 -> y, 0.0));
  assert("Using 'pickup' command pointing to a pen",
	 picture_b -> width == 6 && picture_b -> height == 6 &&
  	 ALMOST_EQUAL(numeric_wb -> value, 12.0) &&
	 ALMOST_EQUAL(pair_pb1 -> x, 0.0) &&
	 ALMOST_EQUAL(pair_pb1 -> y, 1.0) &&
	 ALMOST_EQUAL(pair_pb2 -> x, 1.0) &&
	 ALMOST_EQUAL(pair_pb2 -> y, 0.0));
  assert("Using 'erase' command",
	 picture_c -> width == 6 && picture_c -> height == 6 &&
  	 ALMOST_EQUAL(numeric_wc -> value, 0.0));
  assert("Drawing dot with circular pen",
	 picture_d -> width == 12 && picture_d -> height == 12 &&
  	 ALMOST_EQUAL(numeric_wd -> value, 112.0) &&
	 // You can test the reference values with METAFONT code:
	 // pickup pencircle scaled 12 rotated 20;
	 // message decimal xpart top lft (0, 0);
	 // message decimal ypart top lft (0, 0);
	 // message decimal xpart bot rt (0, 0);
	 // message decimal ypart bot rt (0, 0);
	 abs(pair_pd1 -> x + 6.0) < 0.2 &&
	 abs(pair_pd1 -> y - 6.0) < 0.2 &&
	 abs(pair_pd2 -> x - 6.0) < 0.2 &&
	 abs(pair_pd2 -> y + 6.0) < 0.2	 
	 //ALMOST_EQUAL(pair_pd1 -> point.x, -6.0) &&
	 //ALMOST_EQUAL(pair_pd1 -> point.y, 6.0) &&
	 //ALMOST_EQUAL(pair_pd2 -> point.x, 6.0) &&
	 //ALMOST_EQUAL(pair_pd2 -> point.y, -6.0));
	 );
  assert("Drawing dot with custom curved pen",
	 picture_e -> width == 12 && picture_e -> height == 12 &&
  	 ALMOST_EQUAL(numeric_we -> value, 112.0) &&
	 // You can test the reference values with METAFONT code:
	 // path tmp;
	 // tmp := (0.5, 0) .. controls (0.5, 0.13261) and (0.44733, 0.2598) .. (0.35356, 0.35356) .. controls (0.2598, 0.44733) and (0.13261, 0.5) .. (0, 0.5);
	 // tmp := tmp & tmp rotated 90;
	 // tmp := tmp & tmp rotated 180 & cycle;
	 // tmp := tmp scaled 12 rotated 30;
	 // pickup (makepen tmp);
	 // message decimal xpart top lft (0, 0); % Output: -5.7957
	 // message decimal ypart top lft (0, 0); % Output: 5.7957
	 // message decimal xpart bot rt (0, 0); % Output: 5.7957
	 // message decimal ypart bot rt (0, 0); % Output: -5.7957
	 // However METAFONT produces these values because it converts the
	 // pen to polygon, which changes the results. As we keep always
	 // treating them as curves, we should use the values below, which are
	 // the correct values, computed with high precision:
	 abs(pair_pe1 -> x + 5.92623739298447238162743669702386846) < 0.2 &&
	 abs(pair_pe1 -> y - 5.926255757660079919904343789205625362) < 0.2 &&
	 abs(pair_pe2 -> x - 5.926237392984472381627436697023868466) < 0.2 &&
	 abs(pair_pe2 -> y + 5.9262557576600799199043437892056253) < 0.2
	 //ALMOST_EQUAL(pair_pe1 -> point.x, -5.92623739298447238162743669702386846) &&
	 //ALMOST_EQUAL(pair_pe1 -> point.y, 5.926255757660079919904343789205625362) &&
	 //ALMOST_EQUAL(pair_pe2 -> point.x, 5.926237392984472381627436697023868466) &&
	 //ALMOST_EQUAL(pair_pe2 -> point.y, -5.9262557576600799199043437892056253));
	 );
  assert("Drawing a square with custom polygonal pen",
	 picture_f -> width == 6 && picture_f -> height == 6 &&
  	 ALMOST_EQUAL(numeric_wf -> value, 12.0) &&
	 ALMOST_EQUAL(pair_pf1 -> x, -0.5) &&
	 ALMOST_EQUAL(pair_pf1 -> y, 1.0) &&
	 ALMOST_EQUAL(pair_pf2 -> x, 0.5) &&
	 ALMOST_EQUAL(pair_pf2 -> y, 0.0));
  assert("nullpen does not produce drawing",
	 picture_g -> width == 6 && picture_g -> height == 6 &&
  	 ALMOST_EQUAL(numeric_wg -> value, 0.0) &&
	 // You can test the reference values with METAFONT code:
	 // pickup nullpen shifted (1, 1);
	 // message decimal xpart top lft (0, 0); % Output: 1
	 // message decimal ypart top lft (0, 0); % Output: 1
	 // message decimal xpart bot rt (0, 0);  % Output: 1
	 // message decimal ypart bot rt (0, 0);  % Output: 1
	 ALMOST_EQUAL(pair_pg1 -> x, 1.0) &&
	 ALMOST_EQUAL(pair_pg1 -> y, 1.0) &&
	 ALMOST_EQUAL(pair_pg2 -> x, 1.0) &&
	 ALMOST_EQUAL(pair_pg2 -> y, 1.0));
    assert("Commands 'top', 'bot', 'lft' and 'rt' on non-symetrical pen",
	 // You can test the reference values with METAFONT code:
	 // pickup pensquare xscaled 0.5 shifted (0.15, 0.1);
	 // message decimal xpart top lft (0, 0); % Output: -0.1
	 // message decimal ypart top lft (0, 0); % Output: 0.6
	 // message decimal xpart bot rt (0, 0);  % Output: 0.4
	 // message decimal ypart bot rt (0, 0);  % Output: -0.4
	 ALMOST_EQUAL(pair_ph1 -> x, -0.1) &&
	 ALMOST_EQUAL(pair_ph1 -> y, 0.6) &&
	 ALMOST_EQUAL(pair_ph2 -> x, 0.4) &&
	 ALMOST_EQUAL(pair_ph2 -> y, -0.4));
  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);
}

void test_font_rendering(void){
  struct generic_token *first, *last;
  struct metafont *mf;
  struct context *cx;
  bool ret;
  GLuint glyph = 0;
  int width = 0, height = 0, depth = -1, italcorr = -1, kerning = -1;
  mf = init_metafont("sample/compare_fonts/sample.mf");
  cx = init_context(mf);
  lexer(mf, "sample/compare_fonts/sample.mf", &first, &last);
  ret = eval_program(mf, cx, first, last);
  assert("Loading typographic font", ret);
  ret = _Wrender_glyph(mf, "0", NULL, &glyph, &width, &height,
  		       &depth, &italcorr, &kerning);
  assert("Loading glyph", ret && glyph != 0 && width > 0 && height > 0 &&
  	 depth >= 0 && italcorr == 0 && kerning == 0);
  ret = _Wrender_glyph(mf, " ", NULL, &glyph, &width, &height,
		       &depth, &italcorr, &kerning);
  assert("Detecting missing glyph", !ret);

  free_token_list(first);
  destroy_context(mf, cx);
  _Wdestroy_metafont(mf);

}

void test_opengl(void){
  assert("No errors in OpenGL", glGetError() == GL_NO_ERROR);
}

int main(int argc, char **argv){
  _Wcreate_window(&keyboard, &mouse);
  if(!_Winit_weavefont(malloc, free, malloc, free, my_rand, 2592)){
    fprintf(stderr, "ERROR: Test cannot be done. Initialization failed.\n");
    exit(1);
  }
  test_lexer();
  test_linar_algebra();
  test_empty_programs();
  test_compound_statements();
  test_variables();
  test_assignments();
  test_numeric_expressions();
  test_pair_expressions();
  test_transform_expressions();
  test_path_expressions();
  test_pen_expressions();
  test_picture_expressions();
  test_boolean_expressions();
  test_if_statements();
  test_drawing_commands();
  test_font_rendering();
  test_opengl();
  imprime_resultado();
  _Wfinish_weavefont();
  _Wdestroy_window();
  return 0;
}
