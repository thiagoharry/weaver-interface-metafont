CFLAGS+=$(shell pkg-config --cflags x11 egl)
LDFLAGS+=$(shell pkg-config --libs x11 egl)
FLAGS=-Wfatal-errors -Wall -O2 -Os -Wextra -Wshadow -Wundef -std=gnu99 -g
all:
	cd ../.. && $(MAKE) tangle
	cp ../../src/metafont.* .
	$(CC) $(CPPFLAGS) $(CFLAGS) ${FLAGS} -o compare_fonts window.c interface.c metafont.c compare_fonts.c `pkg-config --cflags freetype2` `pkg-config --libs freetype2` -lm -lpthread -lX11 -lEGL -lGLESv2 -DW_DEBUG_METAFONT $(LDFLAGS) #-DW_WEAVEFONT_DISABLE_MULTISAMPLE
en:
	cd ../.. && $(MAKE) tangle_en
	cp ../../src/metafont.* .
	$(CC) $(CPPFLAGS) $(CFLAGS) ${FLAGS} -o compare_fonts window.c interface.c metafont.c compare_fonts.c `pkg-config --cflags freetype2` `pkg-config --libs freetype2` -lm -lpthread -lX11 -lEGL -lGLESv2 -DW_DEBUG_METAFONT $(LDFLAGS) #-DW_WEAVEFONT_DISABLE_MULTISAMPLE
clean:
	rm -rf *~ *.o

