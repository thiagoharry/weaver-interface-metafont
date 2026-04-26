/*683:*/
#line 18977 "weaver-interface-metafont_en.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 18983 "weaver-interface-metafont_en.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*684:*/
#line 19006 "weaver-interface-metafont_en.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:684*//*687:*/
#line 19053 "weaver-interface-metafont_en.cweb"

ERROR_DIVISION_BY_ZERO,
/*:687*//*690:*/
#line 19075 "weaver-interface-metafont_en.cweb"

ERROR_DUPLICATE_GLYPH,
/*:690*//*693:*/
#line 19104 "weaver-interface-metafont_en.cweb"

ERROR_EMPTY_DELIMITER,
/*:693*//*696:*/
#line 19149 "weaver-interface-metafont_en.cweb"

ERROR_EXPECTED_FOUND,
/*:696*//*699:*/
#line 19186 "weaver-interface-metafont_en.cweb"

ERROR_FAILED_OPENING_FILE,
/*:699*//*703:*/
#line 19228 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:703*//*706:*/
#line 19258 "weaver-interface-metafont_en.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:706*//*709:*/
#line 19289 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_CHAR,
/*:709*//*712:*/
#line 19390 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_COMPARISON,
/*:712*//*715:*/
#line 19424 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:715*//*718:*/
#line 19465 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_NAME,
/*:718*//*721:*/
#line 19513 "weaver-interface-metafont_en.cweb"

ERROR_INVALID_TENSION,
/*:721*//*724:*/
#line 19567 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_EXPRESSION,
/*:724*//*727:*/
#line 19597 "weaver-interface-metafont_en.cweb"

ERROR_MISSING_TOKEN,
/*:727*//*730:*/
#line 19626 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:730*//*733:*/
#line 19653 "weaver-interface-metafont_en.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:733*//*736:*/
#line 19681 "weaver-interface-metafont_en.cweb"

ERROR_NESTED_BEGINCHAR,
/*:736*//*739:*/
#line 19709 "weaver-interface-metafont_en.cweb"

ERROR_NO_MEMORY,
/*:739*//*742:*/
#line 19759 "weaver-interface-metafont_en.cweb"

ERROR_NO_PICKUP_PEN,
/*:742*//*745:*/
#line 19791 "weaver-interface-metafont_en.cweb"

ERROR_NONCYCLICAL_PEN,
/*:745*//*748:*/
#line 19817 "weaver-interface-metafont_en.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:748*//*751:*/
#line 19845 "weaver-interface-metafont_en.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:751*//*754:*/
#line 19899 "weaver-interface-metafont_en.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:754*//*757:*/
#line 19933 "weaver-interface-metafont_en.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:757*//*760:*/
#line 19961 "weaver-interface-metafont_en.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:760*//*763:*/
#line 19996 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:763*//*766:*/
#line 20025 "weaver-interface-metafont_en.cweb"

ERROR_UNCLOSED_STRING,
/*:766*//*769:*/
#line 20062 "weaver-interface-metafont_en.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:769*//*772:*/
#line 20090 "weaver-interface-metafont_en.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:772*//*775:*/
#line 20122 "weaver-interface-metafont_en.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:775*//*778:*/
#line 20157 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:778*//*781:*/
#line 20188 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:781*//*784:*/
#line 20218 "weaver-interface-metafont_en.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:784*//*787:*/
#line 20248 "weaver-interface-metafont_en.cweb"

ERROR_UNOPENED_DELIMITER,
/*:787*//*790:*/
#line 20277 "weaver-interface-metafont_en.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:790*//*793:*/
#line 20319 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:793*//*796:*/
#line 20359 "weaver-interface-metafont_en.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:796*/
#line 18986 "weaver-interface-metafont_en.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,

/*39:*/
#line 1211 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2456 "weaver-interface-metafont_en.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2724 "weaver-interface-metafont_en.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*200:*/
#line 5186 "weaver-interface-metafont_en.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:200*//*204:*/
#line 5352 "weaver-interface-metafont_en.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:204*//*205:*/
#line 5365 "weaver-interface-metafont_en.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:205*//*212:*/
#line 5590 "weaver-interface-metafont_en.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:212*//*216:*/
#line 5711 "weaver-interface-metafont_en.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:216*//*232:*/
#line 5995 "weaver-interface-metafont_en.cweb"

TYPE_NORMALDEVIATE,
/*:232*//*246:*/
#line 6323 "weaver-interface-metafont_en.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:246*//*266:*/
#line 6875 "weaver-interface-metafont_en.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:266*//*273:*/
#line 7015 "weaver-interface-metafont_en.cweb"

TYPE_TRANSFORMED,
/*:273*//*292:*/
#line 7411 "weaver-interface-metafont_en.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:292*//*299:*/
#line 7565 "weaver-interface-metafont_en.cweb"

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
#line 9213 "weaver-interface-metafont_en.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:360*//*372:*/
#line 9591 "weaver-interface-metafont_en.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:372*//*394:*/
#line 10108 "weaver-interface-metafont_en.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:394*//*406:*/
#line 10381 "weaver-interface-metafont_en.cweb"

TYPE_MAKEPATH,
/*:406*//*450:*/
#line 11525 "weaver-interface-metafont_en.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:450*//*462:*/
#line 11883 "weaver-interface-metafont_en.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:462*//*468:*/
#line 12047 "weaver-interface-metafont_en.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:468*//*472:*/
#line 12286 "weaver-interface-metafont_en.cweb"

TYPE_OR,
/*:472*//*478:*/
#line 12437 "weaver-interface-metafont_en.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:478*//*486:*/
#line 12916 "weaver-interface-metafont_en.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:486*//*491:*/
#line 13131 "weaver-interface-metafont_en.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:491*//*500:*/
#line 13353 "weaver-interface-metafont_en.cweb"

TYPE_PICKUP,
/*:500*//*576:*/
#line 16205 "weaver-interface-metafont_en.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:576*//*584:*/
#line 16324 "weaver-interface-metafont_en.cweb"

TYPE_PICKCOLOR,
/*:584*//*587:*/
#line 16405 "weaver-interface-metafont_en.cweb"

TYPE_MONOWIDTH,
/*:587*//*592:*/
#line 16459 "weaver-interface-metafont_en.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:592*//*632:*/
#line 17663 "weaver-interface-metafont_en.cweb"

TYPE_SHIPIT,
/*:632*//*636:*/
#line 17766 "weaver-interface-metafont_en.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:636*//*645:*/
#line 18039 "weaver-interface-metafont_en.cweb"

TYPE_KERNING,
/*:645*//*651:*/
#line 18189 "weaver-interface-metafont_en.cweb"

TYPE_DEBUG,
/*:651*/
#line 18993 "weaver-interface-metafont_en.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19000 "weaver-interface-metafont_en.cweb"
#endif
#line 19001 "weaver-interface-metafont_en.cweb"
/*:683*/
