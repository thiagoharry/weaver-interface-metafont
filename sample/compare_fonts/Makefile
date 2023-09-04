all:
	cd ../.. && $(MAKE) tangle
	cp ../../src/metafont.* .
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -g -Wall -o compare_fonts window.c interface.c metafont.c compare_fonts.c `pkg-config --cflags freetype2` `pkg-config --libs freetype2` -lm -lpthread -lX11 -lEGL -lGLESv2 -DW_DEBUG_METAFONT #-DW_WEAVEFONT_DISABLE_MULTISAMPLE
en:
	cd ../.. && $(MAKE) tangle_en
	cp ../../src/metafont.* .
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -g -Wall -o compare_fonts window.c interface.c metafont.c compare_fonts.c `pkg-config --cflags freetype2` `pkg-config --libs freetype2` -lm -lpthread -lX11 -lEGL -lGLESv2 -DW_DEBUG_METAFONT -DW_WEAVEFONT_DISABLE_MULTISAMPLE
clean:
	rm -rf *~ *.o

