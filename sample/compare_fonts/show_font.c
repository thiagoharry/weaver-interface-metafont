#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#if defined(__linux__) || defined(BSD) || defined(__EMSCRIPTEN__)
#include <GLES3/gl3.h>
#endif
#include "window.h"
#include "metafont.h"
#include "interface.h"

#define MARGIN 2.0
#define HEIGHT 2.0
#define MAX_X  40.0
#define ZOOM 1.0


static int window_width, window_height;
static struct _Wkeyboard keyboard;
static struct _Wmouse mouse;

uint64_t empty(void){
  return 0;
}

void test(struct metafont *mf, float weight, float italic, float size){
  int width, height, depth, italcorr, kerning;
  struct user_interface *next;
  GLuint t;
  bool ret;
  unsigned char c[4];
  float x, y;
  x = MARGIN * size; y = window_height - HEIGHT * size;
  _Wmark_history_interface();
  ret = _Wwrite_numeric_variable(mf, "size", (float) size);
  ret = _Wwrite_numeric_variable(mf, "weight", weight);
  ret = _Wwrite_numeric_variable(mf, "italic", italic);
  if(!ret){
    fprintf(stderr, "ERROR setting WEAVEFONT size.\n");
    exit(1);
  }
  { // ASCII + Latin1
    int i;
    for(i = 0; i <= 0x7f; i ++){
      //break;
      c[0] = i; c[1] = '\0';
      ret = _Wrender_glyph(mf, c, NULL, &t, &width, &height,
			   &depth, &italcorr, &kerning);
      next = _Wnew_interface(NULL, NULL,
			     x, y,
			     0.0, ZOOM * width, ZOOM * (height + depth));
      if(ret){
	//printf("%s\n", c);
	x += MARGIN * size;
	if(x > window_width - MARGIN * size){
	  x = MARGIN * size;
	  y -= HEIGHT * size;
	}
	next -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
	*(next -> _texture1) = t;
	next -> _loaded_texture = true;
      }
    }
  }

    { // 2 bytes
    unsigned long i;
    for(i = 0x80; i <= 0x7ff; i ++){
      c[0] = 0xc0; c[1] = 128;
      c[1] += i % 16;
      c[1] += (((i >> 4) % 4) << 4);
      c[0] += ((i >> 6) % 4);
      c[0] += (((i >> 8) % 8) << 2);
      c[2] = '\0';
      ret = _Wrender_glyph(mf, c, NULL, &t, &width, &height,
			   &depth, &italcorr, &kerning);
      next = _Wnew_interface(NULL, NULL,
			     x, y,
			     0.0, ZOOM * width, ZOOM * (height + depth));
      if(ret){
	//printf("%s\n", c);
	//printf("%lx\n", i);
	x += MARGIN * size;
	if(x > window_width - MARGIN * size){
	  x = MARGIN * size;
	  y -= HEIGHT * size;
	}
	next -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
	*(next -> _texture1) = t;
	next -> _loaded_texture = true;
      }
    }
  }

        { // 3 bytes
    unsigned long i;
    for(i = 0x800; i <= 0xffff; i ++){
      c[0] = 0xe0; c[1] = 0x80; c[2] = 0x80;
      c[2] += i % 16;
      c[2] += (((i >> 4) % 4) << 4);
      c[1] += ((i >> 6) % 4);
      c[1] += (((i >> 8) % 16) << 2);
      c[0] += i >> 12;
      c[3] = '\0';
      ret = _Wrender_glyph(mf, c, NULL, &t, &width, &height,
			   &depth, &italcorr, &kerning);
      next = _Wnew_interface(NULL, NULL,
			     x, y,
			     0.0, ZOOM * width, ZOOM * (height + depth));
      if(ret){
	//printf("%s\n", c);
	//printf("%lx\n", i);
	x += MARGIN * size;
	if(x > window_width - MARGIN * size){
	  x = MARGIN * size;
	  y -= HEIGHT * size;
	}
	next -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
	*(next -> _texture1) = t;
	next -> _loaded_texture = true;
      }
    }
  }

    
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glBindTexture(GL_TEXTURE_2D, 0);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glDisable(GL_BLEND);
  _Wflush_window_input(&keyboard, &mouse);
  {
    unsigned long loop = 0;
    do{
      glClear(GL_COLOR_BUFFER_BIT);
      _Wrender_interface(time(NULL));
      _Wget_window_input(time(NULL), &keyboard, &mouse);
      _Wrender_window();
      loop ++;
    } while((!keyboard.key[W_ANY] || loop < 10) && !keyboard.key[W_ESC]);
    _Wrestore_history_interface();
  }
}

int main(int argc, char **argv){
  struct metafont *mf;
  bool ret = true;
  if(argc < 1){
    fprintf(stderr, "ERROR: argv[1] must be a font size\n");
    return 1;
  }
  _Wcreate_window(&keyboard, &mouse);
  _Wget_window_size(&window_width, &window_height);
  // Initializing WEAVEFONT and the metafont
  ret = _Winit_weavefont(malloc, free, malloc, free, empty, 142);
  if(!ret){
    fprintf(stderr, "ERROR initializing WEAVEFONT library.\n");
    return 1;
  }
  _Winit_interface(&window_width, &window_height, malloc, free, malloc,
		   free, NULL, NULL, NULL);
  mf = _Wnew_metafont("sample.mf");
  test(mf, 1.0, 0.0, atoi(argv[1]));
  test(mf, 2.0, 0.0, atoi(argv[1]));
  test(mf, 1.0, 1.0, atoi(argv[1]));
  test(mf, 2.0, 1.0, atoi(argv[1]));
  return 0;
}
