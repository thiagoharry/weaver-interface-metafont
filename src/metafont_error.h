/*702:*/
#line 19403 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19409 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*703:*/
#line 19432 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:703*//*706:*/
#line 19479 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:706*//*709:*/
#line 19501 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:709*//*712:*/
#line 19530 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:712*//*715:*/
#line 19575 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:715*//*718:*/
#line 19612 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:718*//*722:*/
#line 19654 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:722*//*725:*/
#line 19684 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:725*//*728:*/
#line 19715 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:728*//*731:*/
#line 19816 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:731*//*734:*/
#line 19850 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:734*//*737:*/
#line 19891 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:737*//*740:*/
#line 19939 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:740*//*743:*/
#line 19993 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:743*//*746:*/
#line 20023 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:746*//*749:*/
#line 20052 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:749*//*752:*/
#line 20079 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:752*//*755:*/
#line 20107 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:755*//*758:*/
#line 20135 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:758*//*761:*/
#line 20185 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:761*//*764:*/
#line 20217 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:764*//*767:*/
#line 20243 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:767*//*770:*/
#line 20271 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:770*//*773:*/
#line 20325 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:773*//*776:*/
#line 20359 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:776*//*779:*/
#line 20387 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:779*//*782:*/
#line 20422 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:782*//*785:*/
#line 20451 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:785*//*788:*/
#line 20488 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:788*//*791:*/
#line 20516 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:791*//*794:*/
#line 20548 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:794*//*797:*/
#line 20583 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:797*//*800:*/
#line 20614 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:800*//*803:*/
#line 20644 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:803*//*806:*/
#line 20674 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:806*//*809:*/
#line 20703 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:809*//*812:*/
#line 20745 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:812*//*815:*/
#line 20785 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:815*/
#line 19412 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1233 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2478 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2746 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5208 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5374 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5387 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5612 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5733 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 6017 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6345 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6897 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7037 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7433 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7587 "weaver-interface-metafont_en.cweb"

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
#line 9235 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9613 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10130 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10403 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11547 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11905 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12069 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12308 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12459 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12938 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13153 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13375 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*576:*/
#line 16227 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16346 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16427 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16481 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17685 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17788 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18061 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18211 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 19419 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19426 "weaver-interface-metafont_en.cweb"
#endif
#line 19427 "weaver-interface-metafont_en.cweb"
/*:702*/
