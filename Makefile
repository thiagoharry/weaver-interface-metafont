doc:
	magitex-cweb weaver-interface-metafont.tex
	dvipdf weaver-interface-metafont.dvi
doc_en:
	tex weaver-interface-metafont_en.tex
	dvipdf weaver-interface-metafont_en.dvi
benchmark:
	@ctangle weaver-interface-metafont.tex
	@cp src/metafont.* tests/
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -Wall -g -O2 tests/benchmark_mf.c  -o benchmark_mf -lX11 -lEGL -lGLESv2 -lm #-DW_DEBUG_METAFONT
	@bash tests/benchmark.sh
tangle:
	ctangle weaver-interface-metafont.tex
tangle_en:
	ctangle weaver-interface-metafont_en.tex
test: tangle
	cp src/metafont.* tests/
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -Wall -g -O2 tests/window.c tests/test.c -o test_metafont -lpthread -lX11 -lEGL -lGLESv2 -lm #-DW_DEBUG_METAFONT
	./test_metafont
test_en:
	ctangle weaver-interface-metafont_en.tex
	cp src/metafont.* tests/
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -Wall -g -O2 tests/window.c tests/test.c  -o test_metafont -lX11 -lEGL -lGLESv2 -lm #-DW_DEBUG_METAFONT
	./test_metafont
test_web:
	ctangle weaver-interface-metafont.tex
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c src/interface.c  -o docs/test_interface.html
test_web_en:
	ctangle weaver-interface-metafont_en.tex
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c src/interface.c  -o docs/test_interface.html
clean:
	rm -f *~ *.core *.scn *.dvi *.idx *.log 
