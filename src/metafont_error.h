/*685:*/
#line 19004 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19010 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*686:*/
#line 19033 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:686*//*689:*/
#line 19080 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:689*//*692:*/
#line 19102 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:692*//*695:*/
#line 19131 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:695*//*698:*/
#line 19176 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:698*//*701:*/
#line 19213 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:701*//*705:*/
#line 19255 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:705*//*708:*/
#line 19285 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:708*//*711:*/
#line 19316 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:711*//*714:*/
#line 19417 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:714*//*717:*/
#line 19451 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:717*//*720:*/
#line 19492 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:720*//*723:*/
#line 19540 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:723*//*726:*/
#line 19594 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:726*//*729:*/
#line 19624 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:729*//*732:*/
#line 19653 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:732*//*735:*/
#line 19680 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:735*//*738:*/
#line 19708 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:738*//*741:*/
#line 19736 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:741*//*744:*/
#line 19786 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:744*//*747:*/
#line 19818 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:747*//*750:*/
#line 19844 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:750*//*753:*/
#line 19872 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:753*//*756:*/
#line 19926 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:756*//*759:*/
#line 19960 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:759*//*762:*/
#line 19988 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:762*//*765:*/
#line 20023 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:765*//*768:*/
#line 20052 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:768*//*771:*/
#line 20089 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:771*//*774:*/
#line 20117 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:774*//*777:*/
#line 20149 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:777*//*780:*/
#line 20184 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:780*//*783:*/
#line 20215 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:783*//*786:*/
#line 20245 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:786*//*789:*/
#line 20275 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:789*//*792:*/
#line 20304 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:792*//*795:*/
#line 20346 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:795*//*798:*/
#line 20386 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:798*/
#line 19013 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1213 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2458 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2726 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5188 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5354 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5367 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5592 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5713 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 5997 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6325 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6877 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7017 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7413 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7567 "weaver-interface-metafont_en.cweb"

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
#line 9215 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9593 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10110 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10383 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11527 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11885 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12049 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12288 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12439 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12918 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13133 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13355 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*576:*/
#line 16207 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16326 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16407 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16461 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17665 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17768 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18041 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18191 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 19020 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19027 "weaver-interface-metafont_en.cweb"
#endif
#line 19028 "weaver-interface-metafont_en.cweb"
/*:685*/
