/*697:*/
#line 19279 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19285 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*698:*/
#line 19308 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:698*//*701:*/
#line 19355 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:701*//*704:*/
#line 19377 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:704*//*707:*/
#line 19406 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:707*//*710:*/
#line 19451 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:710*//*713:*/
#line 19488 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:713*//*717:*/
#line 19530 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:717*//*720:*/
#line 19560 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:720*//*723:*/
#line 19591 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:723*//*726:*/
#line 19692 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:726*//*729:*/
#line 19726 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:729*//*732:*/
#line 19767 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:732*//*735:*/
#line 19815 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:735*//*738:*/
#line 19869 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:738*//*741:*/
#line 19899 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:741*//*744:*/
#line 19928 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:744*//*747:*/
#line 19955 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:747*//*750:*/
#line 19983 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:750*//*753:*/
#line 20011 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:753*//*756:*/
#line 20061 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:756*//*759:*/
#line 20093 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:759*//*762:*/
#line 20119 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:762*//*765:*/
#line 20147 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:765*//*768:*/
#line 20201 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:768*//*771:*/
#line 20235 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:771*//*774:*/
#line 20263 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:774*//*777:*/
#line 20298 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:777*//*780:*/
#line 20327 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:780*//*783:*/
#line 20364 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:783*//*786:*/
#line 20392 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:786*//*789:*/
#line 20424 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:789*//*792:*/
#line 20459 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:792*//*795:*/
#line 20490 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:795*//*798:*/
#line 20520 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:798*//*801:*/
#line 20550 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:801*//*804:*/
#line 20579 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:804*//*807:*/
#line 20621 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:807*//*810:*/
#line 20661 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:810*/
#line 19288 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1226 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2471 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2739 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5201 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5367 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5380 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5605 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5726 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 6010 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6338 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6890 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7030 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7426 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7580 "weaver-interface-metafont_en.cweb"

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
#line 9228 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9606 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10123 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10396 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11540 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11898 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12062 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12301 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12452 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12931 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13146 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13368 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*576:*/
#line 16220 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16339 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16420 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16474 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17678 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17781 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18054 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18204 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 19295 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19302 "weaver-interface-metafont_en.cweb"
#endif
#line 19303 "weaver-interface-metafont_en.cweb"
/*:697*/
