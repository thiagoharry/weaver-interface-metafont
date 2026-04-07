/*677:*/
#line 18849 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18855 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*678:*/
#line 18878 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:678*//*681:*/
#line 18925 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:681*//*684:*/
#line 18947 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:684*//*687:*/
#line 18976 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:687*//*690:*/
#line 19021 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:690*//*693:*/
#line 19058 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:693*//*697:*/
#line 19100 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:697*//*700:*/
#line 19130 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:700*//*703:*/
#line 19161 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:703*//*706:*/
#line 19262 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:706*//*709:*/
#line 19296 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:709*//*712:*/
#line 19337 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:712*//*715:*/
#line 19385 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:715*//*718:*/
#line 19439 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:718*//*721:*/
#line 19469 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:721*//*724:*/
#line 19498 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:724*//*727:*/
#line 19525 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:727*//*730:*/
#line 19553 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:730*//*733:*/
#line 19581 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:733*//*736:*/
#line 19631 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:736*//*739:*/
#line 19663 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:739*//*742:*/
#line 19689 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:742*//*745:*/
#line 19717 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:745*//*748:*/
#line 19771 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:748*//*751:*/
#line 19805 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:751*//*754:*/
#line 19833 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:754*//*757:*/
#line 19868 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:757*//*760:*/
#line 19897 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:760*//*763:*/
#line 19934 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:763*//*766:*/
#line 19962 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:766*//*769:*/
#line 19994 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:769*//*772:*/
#line 20029 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:772*//*775:*/
#line 20060 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:775*//*778:*/
#line 20090 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:778*//*781:*/
#line 20120 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:781*//*784:*/
#line 20149 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:784*//*787:*/
#line 20191 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:787*//*790:*/
#line 20231 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:790*/
#line 18858 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1201 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2446 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2714 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5176 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5342 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5355 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5580 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5701 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 5985 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6313 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6865 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7005 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7401 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7555 "weaver-interface-metafont_en.cweb"

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
#line 9199 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9577 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10094 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10367 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11511 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11869 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12033 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12272 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12423 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12902 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13117 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13339 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*575:*/
#line 16175 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:575*//*583:*/
#line 16294 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:583*//*586:*/
#line 16375 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:586*//*591:*/
#line 16429 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:591*//*631:*/
#line 17633 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:631*//*635:*/
#line 17736 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:635*//*644:*/
#line 18009 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:644*//*650:*/
#line 18159 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:650*/
#line 18865 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 18872 "weaver-interface-metafont_en.cweb"
#endif
#line 18873 "weaver-interface-metafont_en.cweb"
/*:677*/
