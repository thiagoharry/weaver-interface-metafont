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
test_en: tangle
	cp src/metafont.* tests/
	cp src/metafont.* tests/
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) ${FLAGS} tests/window.c tests/test.c  -o test_metafont -lX11 -lEGL -lGLESv2 -lm -DW_DEBUG_METAFONT -DWEAVER_ENGINE
	./test_metafont 2> /dev/null
test_web:  tangle
	cp src/metafont.* tests/
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c -o docs/test_interface.html -DW_DEBUG_METAFONT -DWEAVER_ENGINE --embed-file tests/ridiculous.mf --embed-file tests/compound.mf --embed-file tests/compound_wrong.mf --embed-file tests/variables.mf --embed-file tests/wrong_assignment.mf --embed-file tests/path_expressions.mf --embed-file tests/pen_expressions.mf --embed-file tests/numeric_expressions.mf --embed-file tests/pair_expressions.mf --embed-file tests/transform_expressions.mf --embed-file tests/picture_expressions.mf --embed-file tests/boolean_expressions.mf --embed-file tests/if_statement.mf --embed-file tests/drawing_commands.mf --embed-file sample/compare_fonts/sample.mf  --embed-file tests/pen_rendering.mf --embed-file tests/prime.mf --embed-file tests/strange_font.mf
test_web_en:
	ctangle weaver-interface-metafont_en.cweb
	emcc $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -DW_FORCE_LANDSCAPE -s ASYNCIFY=1 -Wall -O2 tests/test.c tests/window.c src/interface.c  -o docs/test_interface.html
disassemble:
	$(CC) -g -c -o metafont.o src/metafont.c
clean:
	rm -f *~ *.core *.scn *.dvi *.idx *.log 
