/*724:*/
#line 19907 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19913 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*725:*/
#line 19936 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:725*//*728:*/
#line 19983 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:728*//*731:*/
#line 20005 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:731*//*734:*/
#line 20034 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:734*//*737:*/
#line 20079 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:737*//*740:*/
#line 20116 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:740*//*744:*/
#line 20158 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:744*//*747:*/
#line 20188 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:747*//*750:*/
#line 20219 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:750*//*753:*/
#line 20320 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:753*//*756:*/
#line 20354 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:756*//*759:*/
#line 20395 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:759*//*762:*/
#line 20443 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:762*//*765:*/
#line 20497 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:765*//*768:*/
#line 20527 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:768*//*771:*/
#line 20556 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:771*//*774:*/
#line 20583 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:774*//*777:*/
#line 20611 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:777*//*780:*/
#line 20639 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:780*//*783:*/
#line 20689 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:783*//*786:*/
#line 20721 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:786*//*789:*/
#line 20747 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:789*//*792:*/
#line 20775 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:792*//*795:*/
#line 20829 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:795*//*798:*/
#line 20863 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:798*//*801:*/
#line 20891 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:801*//*804:*/
#line 20926 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:804*//*807:*/
#line 20955 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:807*//*810:*/
#line 20992 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:810*//*813:*/
#line 21020 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:813*//*816:*/
#line 21052 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:816*//*819:*/
#line 21087 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:819*//*822:*/
#line 21118 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:822*//*825:*/
#line 21148 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:825*//*828:*/
#line 21178 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:828*//*831:*/
#line 21207 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:831*//*834:*/
#line 21249 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:834*//*837:*/
#line 21289 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:837*/
#line 19916 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1241 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2486 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2754 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5216 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5382 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5395 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5620 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5741 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 6025 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6353 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6905 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7045 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7441 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7595 "weaver-interface-metafont_en.cweb"

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
#line 9243 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9621 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10138 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10411 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11555 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11913 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12077 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12316 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12467 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12946 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13161 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13383 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*576:*/
#line 16235 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16354 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16435 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16489 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17693 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17796 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18069 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18219 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 19923 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19930 "weaver-interface-metafont_en.cweb"
#endif
#line 19931 "weaver-interface-metafont_en.cweb"
/*:724*/
