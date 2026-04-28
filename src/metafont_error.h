/*691:*/
#line 19093 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19099 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*692:*/
#line 19122 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:692*//*695:*/
#line 19169 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:695*//*698:*/
#line 19191 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:698*//*701:*/
#line 19220 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:701*//*704:*/
#line 19265 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:704*//*707:*/
#line 19302 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:707*//*711:*/
#line 19344 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:711*//*714:*/
#line 19374 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:714*//*717:*/
#line 19405 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:717*//*720:*/
#line 19506 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:720*//*723:*/
#line 19540 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:723*//*726:*/
#line 19581 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:726*//*729:*/
#line 19629 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:729*//*732:*/
#line 19683 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:732*//*735:*/
#line 19713 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:735*//*738:*/
#line 19742 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:738*//*741:*/
#line 19769 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:741*//*744:*/
#line 19797 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:744*//*747:*/
#line 19825 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:747*//*750:*/
#line 19875 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:750*//*753:*/
#line 19907 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:753*//*756:*/
#line 19933 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:756*//*759:*/
#line 19961 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:759*//*762:*/
#line 20015 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:762*//*765:*/
#line 20049 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:765*//*768:*/
#line 20077 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:768*//*771:*/
#line 20112 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:771*//*774:*/
#line 20141 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:774*//*777:*/
#line 20178 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:777*//*780:*/
#line 20206 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:780*//*783:*/
#line 20238 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:783*//*786:*/
#line 20273 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:786*//*789:*/
#line 20304 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:789*//*792:*/
#line 20334 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:792*//*795:*/
#line 20364 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:795*//*798:*/
#line 20393 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:798*//*801:*/
#line 20435 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:801*//*804:*/
#line 20475 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:804*/
#line 19102 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1219 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2464 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2732 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5194 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5360 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5373 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5598 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5719 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 6003 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6331 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6883 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7023 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7419 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7573 "weaver-interface-metafont_en.cweb"

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
#line 9221 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9599 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10116 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10389 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11533 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11891 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12055 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12294 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12445 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12924 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13139 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13361 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*576:*/
#line 16213 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16332 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16413 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16467 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17671 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17774 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18047 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18197 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 19109 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19116 "weaver-interface-metafont_en.cweb"
#endif
#line 19117 "weaver-interface-metafont_en.cweb"
/*:691*/
