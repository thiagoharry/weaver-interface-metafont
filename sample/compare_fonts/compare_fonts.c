//#include "metafont.c"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include "window.h"
#include "metafont.h"
#include "interface.h"

// In 96 dpi: 300 pt = 400 px

#define MIN_SIZE 400
#define MAX_SIZE 400

#define ZOOM 1.0

static int window_width, window_height;
static struct _Wkeyboard keyboard;
static struct _Wmouse mouse;


uint32_t utf8_to_utf32(unsigned char *c){
  uint32_t code_point = 0;
  if(c[0] < 128){
    code_point = c[0];
  }
  else if(c[0] >= 192 && c[0] <= 223 && c[1] >= 128 && c[1] <= 159){
    code_point = c[1] - 128;
    code_point += (c[0] - 192) * 64;
  }
  else if(c[0] >= 224 && c[0] <= 239 && c[1] >= 128 && c[1] <= 159 &&
          c[2] >= 128 && c[2] <= 159){
    code_point = c[2] - 128;
    code_point += (c[1] - 128) * 64;
    code_point += (c[0] - 224) * 4096;
  }
  else if(c[0] >= 240 && c[0] <= 247 && c[1] >= 128 && c[1] <= 159 &&
          c[2] >= 128 && c[2] <= 159 && c[3] >= 128 && c[3] <= 159){
    code_point = c[3] - 128;
    code_point += (c[2] - 128) * 64;
    code_point += (c[1] - 128) * 4096;
    code_point += (c[0] - 240) * 262144;
  }
  return code_point;
}

uint64_t empty(void){
  return 0;
}

void test(struct metafont *mf, char *font_name, char *c, int weight, int italic){
  int width, height, depth, italcorr, kerning;
  long int f_depth;
  int error, size;
  bool ret = true;
  float start, end, elapsed;
  FT_Library  library;
  FT_Face     face;
  uint32_t character;
  unsigned int glyph_index;
  GLuint t;
  // For parameter sugestion:
  double *y_values1, *y_values2, *y_values3;
  y_values1 = (double *) malloc(sizeof(double) * (MAX_SIZE-MIN_SIZE+1));
  y_values2 = (double *) malloc(sizeof(double) * (MAX_SIZE-MIN_SIZE+1));
  y_values3 = (double *) malloc(sizeof(double) * (MAX_SIZE-MIN_SIZE+1));
  if(y_values1 == NULL || y_values2 == NULL || y_values3 == NULL){
    fprintf(stderr, "ERROR: No memory.\n");
    exit(1);
  }
  ret = _Wwrite_numeric_variable(mf, "weight", (float) weight);
  ret = _Wwrite_numeric_variable(mf, "italic", (float) italic);
  character = utf8_to_utf32((unsigned char *) c);
  // Initializing Freetype2 and the OTF font
  start = (float)clock()/CLOCKS_PER_SEC;
  error = FT_Init_FreeType(&library);
  if(error){
    fprintf(stderr, "ERROR initializing FreeType library.\n");
    exit(1);
  }
  error = FT_New_Face(library, font_name, 0, &face);
  if (error == FT_Err_Unknown_File_Format){
    fprintf(stderr, "ERROR loading 'sample.ttf': Format unknown.\n");
    exit(1);
  }
  else if(error){
    fprintf(stderr, "ERROR loading 'sample.ttf': Unknown error.\n");
    exit(1);
  }
  end = (float)clock()/CLOCKS_PER_SEC;
  elapsed = end - start;
  printf("Freetype OTF font loaded in %f seconds (CPU time)\n", elapsed);

  // Dummy rendering for Freetype2:
  glyph_index = FT_Get_Char_Index(face, character);
  FT_Set_Char_Size(face, 0, (MIN_SIZE - 1) * 64, 96, 96);
  FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
  FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
  FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );
  // Dummy rendering of WEAVEFONT
  {
    _Wwrite_numeric_variable(mf, "size", (MIN_SIZE - 1));
    _Wrender_glyph(mf, c, NULL, &t, &width, &height,
    		   &depth, &italcorr, &kerning);
  }

  
  for(size = MIN_SIZE; size <= MAX_SIZE; size ++){
    error = FT_Set_Char_Size(face, 0, size * 64, 96, 96);
    if(error){
      fprintf(stderr, "ERROR setting dpi and size.\n");
      exit(1);
    }
    start = (float)clock()/CLOCKS_PER_SEC;
    error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
    if(error){
      fprintf(stderr, "ERROR %x loading glyph [%u:'%s'].\n", error, character, c);
      exit(1);
    }
    error = FT_Render_Glyph( face->glyph, FT_RENDER_MODE_NORMAL );
    if(error){
      fprintf(stderr, "ERROR rendering glyph [%u:'%s'].\n", character, c);
      exit(1);
    }
    end = (float)clock()/CLOCKS_PER_SEC;
    elapsed = end - start;
    f_depth = (face->glyph -> metrics.height -
	       face->glyph -> metrics.horiBearingY)/ 64;
    if(face->glyph -> bitmap.width != face->glyph -> metrics.width / 64 ||
       face->glyph -> bitmap.rows != face->glyph -> metrics.height / 64){
      fprintf(stderr,
	      "ERROR: Freetype: glyph with different logical (%lux%lu) and bitmap (%dx%d) sizes. Not handling this.\n",
	      face->glyph -> metrics.width / 64, face->glyph -> metrics.height / 64,
	      face->glyph -> bitmap.width, face->glyph -> bitmap.rows);
      exit(1);
    }
    else{
      y_values1[size-MIN_SIZE] = face->glyph -> bitmap.width;
      y_values2[size-MIN_SIZE] = face->glyph -> bitmap.rows - f_depth;
      y_values3[size-MIN_SIZE] = f_depth;
      printf("Freetype2 font: %dpt (%dx%ld)[depth: %ld]: %f seconds (CPU time)\n", size,
	     face->glyph -> bitmap.width, face->glyph -> bitmap.rows - f_depth,
	     f_depth, elapsed);
    }
    {
      ret = _Wwrite_numeric_variable(mf, "size", (float) size);
      if(!ret){
	fprintf(stderr, "ERROR setting WEAVEFONT size.\n");
	exit(1);
      }
      start = (float)clock()/CLOCKS_PER_SEC;
      ret = _Wrender_glyph(mf, c, NULL, &t, &width, &height,
			   &depth, &italcorr, &kerning);
      if(!ret){
	fprintf(stderr, "ERROR loading WEAVEFONT glyph ['%s'].\n", c);
	_Wprint_metafont_error(mf);
	exit(1);
      }
      end = (float)clock()/CLOCKS_PER_SEC;
      elapsed = end - start;
      printf("WEAVEFONT font: %dpt (%dx%d)[depth: %d]: %f seconds (CPU time)\n", size,
           width, height, depth, elapsed);
    }
    { // Screen rendering
      int i, j, p;
      struct user_interface *line, *f, *m, *h, *h1, *h2;
      _Wmark_history_interface(); 
      f = _Wnew_interface(NULL, NULL,
			  (window_width - ZOOM * face->glyph -> bitmap.width) / 2
			  - 1,
			  (window_height + ZOOM * face->glyph -> bitmap.rows) / 2 -
			  f_depth + 1,
		          0.0, ZOOM * (float) face->glyph -> bitmap.width,
			  ZOOM * (float) face->glyph -> bitmap.rows);
      m = _Wnew_interface(NULL, NULL,
			  (window_width + ZOOM * width) / 2 +1,
			  (window_height + ZOOM * (height+depth)) / 2 - depth + 1,
		          0.0, ZOOM * width, ZOOM * (height + depth));
      line = _Wnew_interface(NULL, NULL, window_width / 2, window_height / 2, 0.0, window_width, 1);
      h = _Wnew_interface(NULL, NULL, window_width / 2, window_height / 2, 0.0, 1, window_height);
      h1 = _Wnew_interface(NULL, NULL, (window_width - 2 * ZOOM * face->glyph -> bitmap.width) / 2, window_height / 2, 0.0, 1, window_height);
      h2 = _Wnew_interface(NULL, NULL, (window_width + 2 * ZOOM * width) / 2, window_height / 2, 0.0, 1, window_height);
      unsigned char *f_buffer;
      f_buffer = (unsigned char *) malloc(face->glyph -> bitmap.width * face->glyph -> bitmap.rows * 4);
      if(f_buffer == NULL){
	fprintf(stderr, "ERROR: No memory.\n");
	exit(1);
      }
      f_buffer[0] = 0; f_buffer[1] = 0; f_buffer[2] = 0; f_buffer[3] = 0; f_buffer[4] = 64;
      line -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
      glGenTextures(1, line -> _texture1);
      glBindTexture(GL_TEXTURE_2D, *(line -> _texture1));
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
		   GL_RGBA, GL_UNSIGNED_BYTE, f_buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_2D, 0);
      line -> _loaded_texture = true;
      h -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
      glGenTextures(1, h -> _texture1);
      glBindTexture(GL_TEXTURE_2D, *(h -> _texture1));
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
		   GL_RGBA, GL_UNSIGNED_BYTE, f_buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_2D, 0);
      h -> _loaded_texture = true;

      h1 -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
      glGenTextures(1, h1 -> _texture1);
      glBindTexture(GL_TEXTURE_2D, *(h1 -> _texture1));
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
		   GL_RGBA, GL_UNSIGNED_BYTE, f_buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_2D, 0);
      h1 -> _loaded_texture = true;

      h2 -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
      glGenTextures(1, h2 -> _texture1);
      glBindTexture(GL_TEXTURE_2D, *(h2 -> _texture1));
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0,
		   GL_RGBA, GL_UNSIGNED_BYTE, f_buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_2D, 0);
      h2 -> _loaded_texture = true;
      
      p = 0;
      for(i = 0; i < face->glyph -> bitmap.rows; i ++)
	for(j = 0; j < face->glyph -> bitmap.width; j ++){
	  f_buffer[p] = 255 - face -> glyph -> bitmap.buffer[(face->glyph -> bitmap.rows - i - 1) * face->glyph -> bitmap.width + j];
	  p++;
	  f_buffer[p] = 255 - face -> glyph -> bitmap.buffer[(face->glyph -> bitmap.rows - i - 1) * face->glyph -> bitmap.width + j];
	  p++;
	  f_buffer[p] = 255 - face -> glyph -> bitmap.buffer[(face->glyph -> bitmap.rows - i - 1) * face->glyph -> bitmap.width + j];
	  p++;
	  f_buffer[p] = face -> glyph -> bitmap.buffer[(face->glyph -> bitmap.rows - i - 1) * face->glyph -> bitmap.width + j];
	  //printf("[%d]", f_buffer[p]);
	  p ++;
	}
      f -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
      glGenTextures(1, f -> _texture1);
      glBindTexture(GL_TEXTURE_2D, *(f -> _texture1));
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, face->glyph -> bitmap.width,
      	   face->glyph -> bitmap.rows, 0,
      	   GL_RGBA, GL_UNSIGNED_BYTE, f_buffer);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glBindTexture(GL_TEXTURE_2D, 0);
      f -> _loaded_texture = true;
      m -> _texture1 = (GLuint *) malloc(sizeof(GLuint));
      *(m -> _texture1) = t;
      m -> _loaded_texture = true;
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      free(f_buffer);
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

  }

  
  {
    // Computing size suggestion:
    double x = 0.0, y = 0.0, xx = 0.0, xy = 0.0, m, b;
    int i;
    for(i = MIN_SIZE; i <= MAX_SIZE; i ++){
      x += (double) i;
      xx += (double) (i * i);
      y += (double) y_values1[i-MIN_SIZE];
      xy += (double) (i * y_values1[i-MIN_SIZE]);
    }
    x /= (MAX_SIZE-MIN_SIZE+1);
    xx /= (MAX_SIZE-MIN_SIZE+1);
    xy /= (MAX_SIZE-MIN_SIZE+1);
    y /= (MAX_SIZE-MIN_SIZE+1);
    m = (y-(xy/x))/(x-(xx/x));
    b = y - m * x;
    printf("Width suggestion: (%f * size + %f) * pt\n",
	   m / (96.0/72.0), b / (96.0/72.0));
    y = 0;
    xy = 0;
    for(i = MIN_SIZE; i <= MAX_SIZE; i ++){
      y += (double) y_values2[i-MIN_SIZE];
      xy += (double) (i * y_values2[i-MIN_SIZE]);
    }
    xy /= (MAX_SIZE-MIN_SIZE+1);
    y /= (MAX_SIZE-MIN_SIZE+1);
    m = (y-(xy/x))/(x-(xx/x));
    b = y - m * x;
    printf("Height suggestion: (%f * size + %f) * pt\n",
	   m / (96.0/72.0), b / (96.0/72.0));
    y = 0;
    xy = 0;
    for(i = MIN_SIZE; i <= MAX_SIZE; i ++){
      y += (double) y_values3[i-MIN_SIZE];
      xy += (double) (i * y_values3[i-MIN_SIZE]);
    }
    xy /= (MAX_SIZE-MIN_SIZE+1);
    y /= (MAX_SIZE-MIN_SIZE+1);
    m = (y-(xy/x))/(x-(xx/x));
    b = y - m * x;
    printf("Depth suggestion: (%f * size + %f) * pt\n",
	   m / (96.0/72.0), b / (96.0/72.0));
  }
  free(y_values1);
  free(y_values2);
  free(y_values3);
  FT_Done_FreeType(library);
}

int main(int argc, char **argv){
  struct metafont *mf;
  float start, end, elapsed;
  bool ret = true;
  _Wcreate_window(&keyboard, &mouse);
  if(argc <= 1){
    fprintf(stderr, "ERROR: argv[1] must be some UTF-8 symbol or character.\n");
    return 1;
  }
  _Wget_window_size(&window_width, &window_height);

  // Initializing WEAVEFONT and the metafont
  start = (float)clock()/CLOCKS_PER_SEC;
  ret = _Winit_weavefont(malloc, free, malloc, free, empty, 96);
  if(!ret){
    fprintf(stderr, "ERROR initializing WEAVEFONT library.\n");
    return 1;
  }
  _Winit_interface(&window_width, &window_height, malloc, free, malloc, free,
		       NULL, NULL, NULL);
  mf = _Wnew_metafont("sample.mf");
  if(mf == NULL){
    fprintf(stderr, "ERROR loading sample.mf.\n");
    return 1;
  }
  end = (float)clock()/CLOCKS_PER_SEC;
  elapsed = end - start;
  printf("WEAVEFONT font loaded in %f seconds (CPU time)\n", elapsed);
  printf("REGULAR TEST\n");
  test(mf, "sample.otf", argv[1], 1, 0);
  printf("BOLD TEST\n");
  test(mf, "sample_bold.otf", argv[1], 2, 0);
  printf("ITALIC TEST\n");
  test(mf, "sample_italic.otf", argv[1], 1, 1);
  printf("BOLD ITALIC TEST\n");
  test(mf, "sample_bold_italic.otf", argv[1], 2, 1);
  _Wdestroy_metafont(mf);
  _Wfinish_weavefont();
  _Wfinish_interface();
  _Wdestroy_window();
  return 0;
}
