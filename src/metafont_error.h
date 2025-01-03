/*663:*/
#line 18494 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18500 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*664:*/
#line 18523 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:664*//*667:*/
#line 18567 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:667*//*670:*/
#line 18589 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:670*//*673:*/
#line 18618 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:673*//*676:*/
#line 18663 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:676*//*679:*/
#line 18698 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:679*//*683:*/
#line 18740 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:683*//*686:*/
#line 18770 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:686*//*689:*/
#line 18801 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:689*//*692:*/
#line 18902 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:692*//*695:*/
#line 18934 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:695*//*698:*/
#line 18973 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:698*//*701:*/
#line 19019 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:701*//*704:*/
#line 19071 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:704*//*707:*/
#line 19101 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:707*//*710:*/
#line 19130 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:710*//*713:*/
#line 19157 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:713*//*716:*/
#line 19185 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:716*//*719:*/
#line 19213 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:719*//*722:*/
#line 19263 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:722*//*725:*/
#line 19295 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:725*//*728:*/
#line 19321 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:728*//*731:*/
#line 19349 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:731*//*734:*/
#line 19403 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:734*//*737:*/
#line 19437 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:737*//*740:*/
#line 19472 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:740*//*743:*/
#line 19501 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:743*//*746:*/
#line 19538 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:746*//*749:*/
#line 19566 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:749*//*752:*/
#line 19598 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:752*//*755:*/
#line 19631 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:755*//*758:*/
#line 19662 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:758*//*761:*/
#line 19692 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:761*//*764:*/
#line 19722 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:764*//*767:*/
#line 19751 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:767*//*770:*/
#line 19793 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:770*//*773:*/
#line 19833 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:773*/
#line 18503 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1195 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2439 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2707 "weaver-interface-metafont_en.cweb"

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
#line 11501 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11866 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12030 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12269 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12420 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12899 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13114 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13336 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*575:*/
#line 16108 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:575*//*583:*/
#line 16227 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:583*//*586:*/
#line 16308 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:586*//*591:*/
#line 16362 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:591*//*630:*/
#line 17554 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:630*//*634:*/
#line 17657 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:634*//*643:*/
#line 17931 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:643*/
#line 18510 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18517 "weaver-interface-metafont_en.cweb"
#endif
#line 18518 "weaver-interface-metafont_en.cweb"
/*:663*/
