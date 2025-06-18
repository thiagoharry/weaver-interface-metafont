/*
Copyright (c) thiago, 2025

This file is part of weavefont_page.

weavefont_page is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

weavefont_page is distributed in the hope that it will be useful,
but WITHOUT ANY  WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS  FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more  details.

You should have received a copy of the GNU Affero General Public License
along with weavefont_page. If not, see <http://www.gnu.org/licenses/>.
*/

#include "game.h"

static struct user_interface *back, *w, *t, *e, *a, *v, *e2, *f, *o, *n;

void main_loop(void){ // The game loop
 LOOP_INIT:; // Code executed during loop initialization
  float height = W.height / 8, width;
  width = 0.8*height;
  back = W.new_interface(NULL, NULL,
		      W.width / 2, W.height / 2, 0.0,
		      W.width, W.height);
  w = W.new_interface(NULL, "w.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  e = W.new_interface(NULL, "e.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  a = W.new_interface(NULL, "a.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  v = W.new_interface(NULL, "v.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  e2 = W.new_interface(NULL, "e.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  f = W.new_interface(NULL, "f.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  o = W.new_interface(NULL, "o.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  n = W.new_interface(NULL, "n.mf",
		      W.width / 2, 3* W.height / 4, 2.0,
		      width, height);
  t = W.new_interface(NULL, "t.mf",
		      3 * W.width / 4, W.height / 4, 1.0,
		      width, height);
  if(t == NULL || w == NULL){
    printf("ERROR\n");
    exit(1);
  }
  W.move_interface(w, (w -> width)/2+10, W.height - (w -> height)/2 - 10, 1.0);
  W.move_interface(e, (w -> x) + (w -> width) + 10.0, w -> y, 1.0);
  W.move_interface(a, (e -> x) + (w -> width) + 10.0, w -> y, 1.0);
  W.move_interface(v, (a -> x) + (w -> width) + 10.0, w -> y, 1.0);
  W.move_interface(e2, (v -> x) + (w -> width) + 10.0, w -> y, 1.0);
  W.move_interface(f, (e2 -> x) + (w -> width) + 10.0, w -> y, 1.0);
  W.move_interface(o, (f -> x) + (w -> width) + 5.0, w -> y, 1.0);
  W.move_interface(n, (o -> x) + (w -> width) + 10.0, w -> y, 1.0);
  W.move_interface(t, (n -> x) + (w -> width) + 10.0, w -> y, 1.0);
 LOOP_BODY: // Code executed every loop iteration
  //if(W.keyboard[W_ANY])
  //      Wexit_loop();
 LOOP_END: // Code executed at the end of the loop
    return;
}

int main(void){
  Winit(); // Initializes Weaver
  Wloop(main_loop); // Enter a new game loop
  return 0;
}
