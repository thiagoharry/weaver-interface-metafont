/*673:*/
#line 18741 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18747 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*674:*/
#line 18770 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:674*//*677:*/
#line 18814 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:677*//*680:*/
#line 18836 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:680*//*683:*/
#line 18865 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:683*//*686:*/
#line 18910 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:686*//*689:*/
#line 18945 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:689*//*693:*/
#line 18987 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:693*//*696:*/
#line 19017 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:696*//*699:*/
#line 19048 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:699*//*702:*/
#line 19149 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:702*//*705:*/
#line 19181 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:705*//*708:*/
#line 19220 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:708*//*711:*/
#line 19266 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:711*//*714:*/
#line 19318 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:714*//*717:*/
#line 19348 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:717*//*720:*/
#line 19377 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:720*//*723:*/
#line 19404 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:723*//*726:*/
#line 19432 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:726*//*729:*/
#line 19460 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:729*//*732:*/
#line 19510 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:732*//*735:*/
#line 19542 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:735*//*738:*/
#line 19568 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:738*//*741:*/
#line 19596 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:741*//*744:*/
#line 19650 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:744*//*747:*/
#line 19684 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:747*//*750:*/
#line 19719 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:750*//*753:*/
#line 19748 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:753*//*756:*/
#line 19785 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:756*//*759:*/
#line 19813 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:759*//*762:*/
#line 19845 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:762*//*765:*/
#line 19878 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:765*//*768:*/
#line 19909 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:768*//*771:*/
#line 19939 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:771*//*774:*/
#line 19969 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:774*//*777:*/
#line 19998 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:777*//*780:*/
#line 20040 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:780*//*783:*/
#line 20080 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:783*/
#line 18750 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1197 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2442 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2710 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5171 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5337 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5350 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5575 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5696 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 5980 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6308 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6860 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7000 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7393 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7547 "weaver-interface-metafont_en.cweb"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,
TYPE_STRAIGHT_JOIN,
/*:299*//*360:*/
#line 9191 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9569 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10086 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10359 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11503 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11868 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12032 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12271 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12422 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12901 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13116 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13338 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*575:*/
#line 16110 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:575*//*583:*/
#line 16229 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:583*//*586:*/
#line 16310 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:586*//*591:*/
#line 16364 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:591*//*630:*/
#line 17556 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:630*//*634:*/
#line 17659 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:634*//*643:*/
#line 17933 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:643*//*649:*/
#line 18083 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:649*/
#line 18757 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18764 "weaver-interface-metafont_en.cweb"
#endif
#line 18765 "weaver-interface-metafont_en.cweb"
/*:673*/
