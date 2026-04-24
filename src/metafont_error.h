/*683:*/
#line 19263 "weaver-interface-metafont.cweb"

#ifndef __WEAVER_METAFONT_ERROR
#define __WEAVER_METAFONT_ERROR
#ifdef __cplusplus
extern"C"{
#endif
#line 19269 "weaver-interface-metafont.cweb"
 enum{
ERROR_NO_ERROR= 0,

/*684:*/
#line 19292 "weaver-interface-metafont.cweb"

ERROR_DISCONTINUOUS_PATH,
/*:684*//*687:*/
#line 19341 "weaver-interface-metafont.cweb"

ERROR_DIVISION_BY_ZERO,
/*:687*//*690:*/
#line 19363 "weaver-interface-metafont.cweb"

ERROR_DUPLICATE_GLYPH,
/*:690*//*693:*/
#line 19393 "weaver-interface-metafont.cweb"

ERROR_EMPTY_DELIMITER,
/*:693*//*696:*/
#line 19438 "weaver-interface-metafont.cweb"

ERROR_EXPECTED_FOUND,
/*:696*//*699:*/
#line 19474 "weaver-interface-metafont.cweb"

ERROR_FAILED_OPENING_FILE,
/*:699*//*703:*/
#line 19515 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_SOURCE,
/*:703*//*706:*/
#line 19545 "weaver-interface-metafont.cweb"

ERROR_INCOMPLETE_STATEMENT,
/*:706*//*709:*/
#line 19577 "weaver-interface-metafont.cweb"

ERROR_INVALID_CHAR,
/*:709*//*712:*/
#line 19682 "weaver-interface-metafont.cweb"

ERROR_INVALID_COMPARISON,
/*:712*//*715:*/
#line 19717 "weaver-interface-metafont.cweb"

ERROR_INVALID_DIMENSION_GLYPH,
/*:715*//*718:*/
#line 19759 "weaver-interface-metafont.cweb"

ERROR_INVALID_NAME,
/*:718*//*721:*/
#line 19807 "weaver-interface-metafont.cweb"

ERROR_INVALID_TENSION,
/*:721*//*724:*/
#line 19858 "weaver-interface-metafont.cweb"

ERROR_MISSING_EXPRESSION,
/*:724*//*727:*/
#line 19888 "weaver-interface-metafont.cweb"

ERROR_MISSING_TOKEN,
/*:727*//*730:*/
#line 19918 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_LOGARITHM,
/*:730*//*733:*/
#line 19946 "weaver-interface-metafont.cweb"

ERROR_NEGATIVE_SQUARE_ROOT,
/*:733*//*736:*/
#line 19973 "weaver-interface-metafont.cweb"

ERROR_NESTED_BEGINCHAR,
/*:736*//*739:*/
#line 20000 "weaver-interface-metafont.cweb"

ERROR_NO_MEMORY,
/*:739*//*742:*/
#line 20052 "weaver-interface-metafont.cweb"

ERROR_NO_PICKUP_PEN,
/*:742*//*745:*/
#line 20085 "weaver-interface-metafont.cweb"

ERROR_NONCYCLICAL_PEN,
/*:745*//*748:*/
#line 20111 "weaver-interface-metafont.cweb"

ERROR_NULL_VECTOR_ANGLE,
/*:748*//*751:*/
#line 20139 "weaver-interface-metafont.cweb"

ERROR_OPENGL_FRAMEBUFFER,
/*:751*//*754:*/
#line 20193 "weaver-interface-metafont.cweb"

ERROR_RECURSIVE_RENDERCHAR,
/*:754*//*757:*/
#line 20227 "weaver-interface-metafont.cweb"

ERROR_SELF_INTERSECTING_PEN,
/*:757*//*760:*/
#line 20256 "weaver-interface-metafont.cweb"

ERROR_UNBALANCED_ENDING_TOKEN,
/*:760*//*763:*/
#line 20292 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_DELIMITER,
/*:763*//*766:*/
#line 20320 "weaver-interface-metafont.cweb"

ERROR_UNCLOSED_STRING,
/*:766*//*769:*/
#line 20357 "weaver-interface-metafont.cweb"

ERROR_UNDECLARED_VARIABLE,
/*:769*//*772:*/
#line 20385 "weaver-interface-metafont.cweb"

ERROR_UNEXPECTED_TOKEN,
/*:772*//*775:*/
#line 20418 "weaver-interface-metafont.cweb"

ERROR_UNINITIALIZED_VARIABLE,
/*:775*//*778:*/
#line 20451 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_GLYPH_DEPENDENCY,
/*:778*//*781:*/
#line 20482 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_EXPRESSION,
/*:781*//*784:*/
#line 20513 "weaver-interface-metafont.cweb"

ERROR_UNKNOWN_STATEMENT,
/*:784*//*787:*/
#line 20544 "weaver-interface-metafont.cweb"

ERROR_UNOPENED_DELIMITER,
/*:787*//*790:*/
#line 20573 "weaver-interface-metafont.cweb"

ERROR_UNSUPORTED_LENGTH_OPERAND,
/*:790*//*793:*/
#line 20616 "weaver-interface-metafont.cweb"

ERROR_WRONG_NUMBER_OF_PARAMETERS,
/*:793*//*796:*/
#line 20654 "weaver-interface-metafont.cweb"

ERROR_WRONG_VARIABLE_TYPE,
/*:796*/
#line 19272 "weaver-interface-metafont.cweb"


ERROR_UNKNOWN
};
enum{
TYPE_NUMERIC= 1,TYPE_STRING,TYPE_SYMBOLIC,TYPE_FOR,TYPE_ENDFOR,


/*39:*/
#line 1262 "weaver-interface-metafont.cweb"

TYPE_OPEN_PARENTHESIS,
TYPE_CLOSE_PARENTHESIS,
TYPE_COMMA,
TYPE_SEMICOLON,
/*:39*//*84:*/
#line 2529 "weaver-interface-metafont.cweb"

TYPE_BEGINGROUP,
TYPE_ENDGROUP,
TYPE_IF,
TYPE_FI,
TYPE_BEGINCHAR,
TYPE_ENDCHAR,
/*:84*//*97:*/
#line 2795 "weaver-interface-metafont.cweb"

TYPE_T_BOOLEAN,
TYPE_T_PATH,
TYPE_T_PEN,
TYPE_T_PICTURE,
TYPE_T_TRANSFORM,
TYPE_T_PAIR,
TYPE_T_NUMERIC,
/*:97*//*201:*/
#line 5309 "weaver-interface-metafont.cweb"

TYPE_EQUAL,
TYPE_ASSIGNMENT,
/*:201*//*205:*/
#line 5477 "weaver-interface-metafont.cweb"

TYPE_SUM,
TYPE_SUBTRACT,
TYPE_PYTHAGOREAN_SUM,
TYPE_PYTHAGOREAN_SUBTRACT,
/*:205*//*206:*/
#line 5490 "weaver-interface-metafont.cweb"

TYPE_OPEN_BRACKETS,
TYPE_CLOSE_BRACKETS,
TYPE_OPEN_BRACES,
TYPE_CLOSE_BRACES,
/*:206*//*213:*/
#line 5727 "weaver-interface-metafont.cweb"

TYPE_MULTIPLICATION,
TYPE_DIVISION,
/*:213*//*217:*/
#line 5853 "weaver-interface-metafont.cweb"

TYPE_LENGTH,
TYPE_SQRT,
TYPE_SIND,
TYPE_COSD,
TYPE_LOG,
TYPE_EXP,
TYPE_FLOOR,
TYPE_UNIFORMDEVIATE,
/*:217*//*233:*/
#line 6141 "weaver-interface-metafont.cweb"

TYPE_NORMALDEVIATE,
/*:233*//*247:*/
#line 6472 "weaver-interface-metafont.cweb"

TYPE_ROTATED,
TYPE_SCALED,
TYPE_SHIFTED,
TYPE_SLANTED,
TYPE_XSCALED,
TYPE_YSCALED,
TYPE_ZSCALED,
/*:247*//*267:*/
#line 7028 "weaver-interface-metafont.cweb"

TYPE_XPART,
TYPE_YPART,
TYPE_ANGLE,
/*:267*//*274:*/
#line 7168 "weaver-interface-metafont.cweb"

TYPE_TRANSFORMED,
/*:274*//*293:*/
#line 7578 "weaver-interface-metafont.cweb"

TYPE_XXPART,
TYPE_XYPART,
TYPE_YXPART,
TYPE_YYPART,
/*:293*//*300:*/
#line 7734 "weaver-interface-metafont.cweb"

TYPE_CYCLE,
TYPE_AMPERSAND,
TYPE_JOIN,
TYPE_TENSION,
TYPE_AND,
TYPE_ATLEAST,
TYPE_CONTROLS,
TYPE_CURL,
TYPE_STRAIGHT_JOIN,
/*:300*//*361:*/
#line 9405 "weaver-interface-metafont.cweb"

TYPE_REVERSE,
TYPE_SUBPATH,
TYPE_OF,
/*:361*//*373:*/
#line 9784 "weaver-interface-metafont.cweb"

TYPE_POINT,
TYPE_PRECONTROL,
TYPE_POSTCONTROL,
/*:373*//*395:*/
#line 10305 "weaver-interface-metafont.cweb"

TYPE_NULLPEN,
TYPE_PENCIRCLE,
TYPE_PENSEMICIRCLE,
TYPE_MAKEPEN,
/*:395*//*407:*/
#line 10586 "weaver-interface-metafont.cweb"

TYPE_MAKEPATH,
/*:407*//*451:*/
#line 11740 "weaver-interface-metafont.cweb"

TYPE_NULLPICTURE,
TYPE_SUBPICTURE,
/*:451*//*463:*/
#line 12101 "weaver-interface-metafont.cweb"

TYPE_TOTALWEIGHT,
TYPE_WIDTH,
TYPE_HEIGHT,
/*:463*//*469:*/
#line 12268 "weaver-interface-metafont.cweb"

TYPE_LT,
TYPE_LEQ,
TYPE_GT,
TYPE_GEQ,
TYPE_NEQ,
/*:469*//*473:*/
#line 12507 "weaver-interface-metafont.cweb"

TYPE_OR,
/*:473*//*479:*/
#line 12658 "weaver-interface-metafont.cweb"

TYPE_TRUE,
TYPE_FALSE,
TYPE_ODD,
TYPE_NOT,
/*:479*//*487:*/
#line 13145 "weaver-interface-metafont.cweb"

TYPE_ELSEIF,
TYPE_ELSE,
TYPE_COLON,
/*:487*//*492:*/
#line 13349 "weaver-interface-metafont.cweb"

TYPE_STEP,
TYPE_UNTIL,
/*:492*//*501:*/
#line 13573 "weaver-interface-metafont.cweb"

TYPE_PICKUP,
/*:501*//*577:*/
#line 16493 "weaver-interface-metafont.cweb"

TYPE_BOT,
TYPE_TOP,
TYPE_LFT,
TYPE_RT,
/*:577*//*585:*/
#line 16613 "weaver-interface-metafont.cweb"

TYPE_PICKCOLOR,
/*:585*//*588:*/
#line 16695 "weaver-interface-metafont.cweb"

TYPE_MONOWIDTH,
/*:588*//*593:*/
#line 16749 "weaver-interface-metafont.cweb"

TYPE_DRAW,
TYPE_ERASE,
/*:593*//*633:*/
#line 17962 "weaver-interface-metafont.cweb"

TYPE_SHIPIT,
/*:633*//*637:*/
#line 18067 "weaver-interface-metafont.cweb"

TYPE_RENDERCHAR,
TYPE_BETWEEN,
/*:637*//*646:*/
#line 18339 "weaver-interface-metafont.cweb"

TYPE_KERNING,
/*:646*//*652:*/
#line 18492 "weaver-interface-metafont.cweb"

TYPE_DEBUG,
/*:652*/
#line 19280 "weaver-interface-metafont.cweb"


TYPE_INVALID_TOKEN
};
#ifdef __cplusplus
}
#endif
#line 19287 "weaver-interface-metafont.cweb"
#endif
#line 19288 "weaver-interface-metafont.cweb"
/*:683*/
