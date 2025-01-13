FLAGS=-Wfatal-errors -Wall -O2 -Os -Wextra -Wshadow -Wundef -std=gnu99
doc:
	magitex-cweb weaver-interface-metafont.cweb
	dvipdfm weaver-interface-metafont.dvi
doc_en:
	tex weaver-interface-metafont_en.cweb
	dvipdfm weaver-interface-metafont_en.dvi
tangle:
	ctangle weaver-interface-metafont.cweb
tangle_en:
	ctangle weaver-interface-metafont_en.cweb
test: tangle
	cp src/metafont.* tests/
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) ${FLAGS} tests/window.c tests/test.c -o test_metafont -lpthread -lX11 -lEGL -lGLESv2 -lm -DW_DEBUG_METAFONT -DWEAVER_ENGINE
	./test_metafont 2> /dev/null
test_en:
	ctangle weaver-interface-metafont_en.cweb
	cp src/metafont.* tests/
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) ${FLAGS} tests/window.c tests/test.c  -o test_metafont -lX11 -lEGL -lGLESv2 -lm -DW_DEBUG_METAFONT -DWEAVER_ENGINE
	./test_metafont 2> /dev/null
test_web:
	ctangle weaver-interface-metafont.cweb
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c src/interface.c  -o docs/test_interface.html
test_web_en:
	ctangle weaver-interface-metafont_en.cweb
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c src/interface.c  -o docs/test_interface.html
disassemble:
	$(CC) -g -c -o metafont.o src/metafont.c
clean:
	rm -f *~ *.core *.scn *.dvi *.idx *.log 
